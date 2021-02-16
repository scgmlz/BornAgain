//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AutomaticMultiRowDataLoader1D.cpp
//! @brief     Implements class AutomaticMultiRowDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/AutomaticMultiColumnDataLoader1D.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "GUI/coregui/DataLoaders/AutomaticMultiColumnDataLoader1DProperties.h"
#include "qcustomplot.h"
#include "ui_AutomaticMultiColumnDataLoader1DProperties.h"
#include <QFile>
#include <QString>
#include <QTextStream>

namespace {
QString bold(const QString& text)
{
    return "<b>" + text + "</b>";
}

QString table(int nColumns, const QStringList& entries, const QString& attributes /*= ""*/,
              bool bHasHorizontalHeader /*= false*/)
{
    QString result = "<table " + attributes + "><tr>";
    int col = 0;
    bool bShowAsHorizontalHeader = bHasHorizontalHeader;
    for (QStringList::size_type i = 0; i < entries.size(); i++) {
        if (bShowAsHorizontalHeader) {
            result += "<th>" + entries[i] + "</th>";
        } else {
            result += "<td valign=\"top\">" + entries[i] + "</td>";
        }

        col++;
        if ((col == nColumns) && (i < entries.size() - 1)) // start new line?
        {
            result += "</tr><tr>";
            col = 0;
            bShowAsHorizontalHeader = false;
        }
    }
    result += "</tr></table>";

    return result;
}

QVector<QPair<int, int>> expandLineNumberPattern(const QString& pattern, bool* ok = nullptr)
{
    QVector<QPair<int, int>> result;

    // splitting "1, 2-3" first on comma-separated tokens
    for (const auto& token : pattern.split(",")) {
        auto parts = token.split("-");
        // splitting on dash-separated tokens
        if (!parts.empty()) {
            // if no "-" is present, make from "1" a pair {1, 1}
            // if "-" is present, make from "1-2" a pair {1,2}
            bool ok2 = true;
            const auto conv0 = parts[0].toInt(&ok2);
            if (ok2) {
                const auto conv1 = parts.size() > 1 ? parts[1].toInt(&ok2) : conv0;
                if (ok2) {
                    result.push_back({conv0, conv1});
                } else {
                    if (ok != nullptr) {
                        *ok = false;
                    }
                    return {};
                }
            }
        }
    }

    return result;
}

} // namespace

AutomaticMultiColumnDataLoader1D::AutomaticMultiColumnDataLoader1D() : m_propertiesWidget(nullptr)
{
    initWithDefaultProperties();
}

QString AutomaticMultiColumnDataLoader1D::name() const
{
    return "Reflectometry file (multiple rows)";
}

QString AutomaticMultiColumnDataLoader1D::info() const
{
    return "Supports up to 3 columns (Q, R, dR). Columns can be configured.";
}

QString AutomaticMultiColumnDataLoader1D::persistentClassName() const
{
    return "AutomaticMultiColumnDataLoader1D";
}

QString AutomaticMultiColumnDataLoader1D::preview(const QString& filepath,
                                                  QCustomPlot* plotWidget) const
{
    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        return "File '" + filepath + "' could not be opened";
    }

    const QStringList headerPrefixes =
        (m_headerPrefix.trimmed().isEmpty()) ? QStringList() : m_headerPrefix.split(",");

    const auto lineIsHeader = [headerPrefixes](const QString& line) {
        for (auto prefix : headerPrefixes) {
            if (line.startsWith(prefix.trimmed()))
                return true;
        }

        return false;
    };

    const auto skippedLines = expandLineNumberPattern(m_linesToSkip);
    const auto lineShouldBeSkipped = [skippedLines](int lineNr) {
        for (auto pair : skippedLines) {
            if (lineNr >= pair.first && lineNr <= pair.second)
                return true;
        }
        return false;
    };

    // calc map with factors
    // #TODO: wrong result when more than one dataType points to same column with different factors
    QMap<int, double> factorsOfColumns;
    for (auto dataType : m_columnDefinitions.keys()) {
        const auto& colDef = m_columnDefinitions[dataType];
        if (colDef.enabled)
            factorsOfColumns[colDef.column] = colDef.factor;
    }

    QVector<QVector<double>> entriesAsDouble;
    QVector<QStringList> entriesAsString;
    QTextStream in(&file);
    int lineNr = 0;
    int lastColumnCount = -1;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        lineNr++;

        if (lineIsHeader(line) || lineShouldBeSkipped(lineNr) || line.isEmpty())
            continue;

        QStringList lineEntries = line.split(m_separator);

        if (lastColumnCount == -1)
            lastColumnCount = lineEntries.count();
        else if (lastColumnCount != lineEntries.count())
            return QString(
                       "Error: number of columns is not constant over all lines (found in line %1)")
                .arg(lineNr);

        QVector<double> rowEntriesAsDouble;
        QStringList rowEntriesAsString; // already with factors

        for (int col = 0; col < lineEntries.count(); col++) {
            bool ok = false;
            double val = lineEntries[col].toDouble(&ok);
            if (!ok)
                val = NAN; // #TODO: review
            else
                val *= factorsOfColumns.value(col, 1.0);

            rowEntriesAsDouble << val;
            rowEntriesAsString << QString::number(val);
        }

        entriesAsDouble << rowEntriesAsDouble;
        entriesAsString << rowEntriesAsString;
    }

    // validate - There is at least one row and at least two columns
    size_t nrows = entriesAsDouble.size();
    if (nrows < 1)
        return "Error: no numerical values found";
    size_t ncols = entriesAsDouble[0].size();
    if (ncols < 2)
        return "Error: Minimum 2 columns required";

    // Assign Q vs R, dR, dQ:
    QStringList tableEntries;

    QMap<int, QString> typeStr;
    typeStr[0] = "Q";
    typeStr[1] = "R";
    typeStr[2] = "dR";
    typeStr[3] = "ignored";

    for (int col = 0; col < ncols; col++) {
        QString headerText = typeStr[3];
        for (auto dataType : m_columnDefinitions.keys()) {
            if (m_columnDefinitions[dataType].column == col
                && m_columnDefinitions[dataType].enabled) {
                headerText = typeStr[(int)dataType];
                break;
            }
        }

        tableEntries << headerText;
    }

    for (auto line : entriesAsString)
        tableEntries << line;

    QString s = bold("Data table:");

    s += table((int)ncols, tableEntries, "border=\"1\" cellpadding=\"10\" cellspacing=\"0\"", true);

    // -- create plot
    int qCol = m_columnDefinitions[DataType::Q].column;
    int rCol = m_columnDefinitions[DataType::R].column;
    int dRCol = m_columnDefinitions[DataType::dR].column;

    QVector<double> qVec;
    QVector<double> rVec;
    QVector<double> drVec;

    const bool addDR = m_columnDefinitions[DataType::dR].enabled && (ncols > dRCol);

    for (const auto lineAsDoubles : entriesAsDouble) {
        qVec << lineAsDoubles[qCol];
        rVec << lineAsDoubles[rCol];
        if (addDR)
            drVec << lineAsDoubles[dRCol];
    }

    auto graph = plotWidget->addGraph();
    graph->addData(qVec, rVec);

    if (!drVec.empty()) {
        auto errorBars = new QCPErrorBars(plotWidget->xAxis, plotWidget->yAxis);

        errorBars->setData(drVec);
        errorBars->setDataPlottable(graph);
    }

    plotWidget->rescaleAxes();
    plotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plotWidget->xAxis->setLabel("Q [" + m_columnDefinitions[DataType::Q].unit + "]");
    plotWidget->yAxis->setLabel("R");

    return "<p>" + bold("<h>Information: </h>") + info() + "</p><p>" + s + "</p>";
}

void AutomaticMultiColumnDataLoader1D::fillPropertiesGroupBox(QGroupBox* parent)
{
    if (m_propertiesWidget == nullptr)
        m_propertiesWidget = new AutomaticMultiColumnDataLoader1DProperties;

    QHBoxLayout* l = new QHBoxLayout(parent);
    parent->setLayout(l);
    l->addWidget(m_propertiesWidget);

    if (m_separator == " ")
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText("<SPACE>");
    else if (m_separator == "\t")
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText("<TAB>");
    else
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText(m_separator);

    m_propertiesWidget->m_ui->headerPrefixEdit->setText(m_headerPrefix);
    m_propertiesWidget->m_ui->linesToSkipEdit->setText(m_linesToSkip);

    for (auto dataType : {DataType::Q, DataType::R, DataType::dR}) {
        m_propertiesWidget->setDataType((int)dataType, m_columnDefinitions[dataType].enabled,
                                        m_columnDefinitions[dataType].column,
                                        m_columnDefinitions[dataType].unit,
                                        m_columnDefinitions[dataType].factor);
    }

    QObject::connect(m_propertiesWidget,
                     &AutomaticMultiColumnDataLoader1DProperties::propertiesChanged, [this]() {
                         applyProperties();
                         emit propertiesChanged();
                     });
}

void AutomaticMultiColumnDataLoader1D::initWithDefaultProperties()
{
    m_separator = ";";
    m_headerPrefix = "";
    m_linesToSkip = "";

    for (auto dataType : {DataType::Q, DataType::R, DataType::dR}) {
        m_columnDefinitions[dataType].enabled = true;
        m_columnDefinitions[dataType].column = (int)dataType;
        m_columnDefinitions[dataType].unit = "";
        m_columnDefinitions[dataType].factor = 1.0;
    }

    m_columnDefinitions[DataType::Q].unit = "1/nm";
}

QByteArray AutomaticMultiColumnDataLoader1D::serialize() const
{
    QByteArray a;
    QDataStream s(&a, QIODevice::WriteOnly);
    s << m_separator;
    s << m_headerPrefix;
    s << m_linesToSkip;

    s << (quint8)m_columnDefinitions.count();
    for (auto dataType : m_columnDefinitions.keys()) {
        s << (quint8)dataType;
        s << m_columnDefinitions[dataType].enabled;
        s << m_columnDefinitions[dataType].column;
        s << m_columnDefinitions[dataType].unit;
        s << m_columnDefinitions[dataType].factor;
    }

    return a;
}

void AutomaticMultiColumnDataLoader1D::deserialize(const QByteArray& data)
{
    QDataStream s(data);
    s >> m_separator;
    s >> m_headerPrefix;
    s >> m_linesToSkip;

    m_columnDefinitions.clear();
    quint8 nDefs;
    s >> nDefs;
    for (int i = 0; i < nDefs; i++) {
        quint8 dataType;
        s >> dataType;
        auto& colDef = m_columnDefinitions[(DataType)dataType];
        s >> colDef.enabled;
        s >> colDef.column;
        s >> colDef.unit;
        s >> colDef.factor;
    }
}

AbstractDataLoader* AutomaticMultiColumnDataLoader1D::clone() const
{
    auto loader = new AutomaticMultiColumnDataLoader1D();
    loader->deserialize(serialize());
    return loader;
}

void AutomaticMultiColumnDataLoader1D::applyProperties()
{
    if (!m_propertiesWidget)
        return;

    auto ui = m_propertiesWidget->m_ui;

    m_separator = ui->separatorCombo->currentText();
    if (m_separator == "<TAB>")
        m_separator = "\t";
    if (m_separator == "<SPACE>")
        m_separator = " ";

    m_headerPrefix = ui->headerPrefixEdit->text();
    m_linesToSkip = ui->linesToSkipEdit->text();

    for (auto dataType : m_columnDefinitions.keys()) {
        auto& colDef = m_columnDefinitions[dataType];

        colDef.enabled = m_propertiesWidget->enablingCheckBox((int)dataType)->isChecked();
        colDef.column = m_propertiesWidget->columnSpinBox((int)dataType)->value() - 1;
        colDef.unit = m_propertiesWidget->unit((int)dataType);
        colDef.factor = m_propertiesWidget->factor((int)dataType);
    }
}
