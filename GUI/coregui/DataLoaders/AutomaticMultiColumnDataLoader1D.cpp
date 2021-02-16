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
} // namespace

AutomaticMultiColumnDataLoader1D::AutomaticMultiColumnDataLoader1D() : m_propertiesWidget(nullptr)
{
    m_separator = ";";

    for (int col = 0; col < 4; col++) {
        m_columnDefinitions[col].dataType = 0;
        m_columnDefinitions[col].unit = "";
        m_columnDefinitions[col].factor = 1.0;
    }
}

QString AutomaticMultiColumnDataLoader1D::name() const
{
    return "Reflectometry file (multiple rows)";
}

QString AutomaticMultiColumnDataLoader1D::info() const
{
    return "Supports up to 4 columns (Q, R, dR, dQ). Columns can be configured.";
}

QString AutomaticMultiColumnDataLoader1D::persistentClassName() const
{
    return "AutomaticMultiColumnDataLoader1D";
}

QVector<QVector<QString>> AutomaticMultiColumnDataLoader1D::parsedData() const
{
    return QVector<QVector<QString>>();
}

QString AutomaticMultiColumnDataLoader1D::preview(const QString& filepath,
                                                  QCustomPlot* plotWidget) const
{
    std::string line;
    std::vector<std::vector<double>> vecVec;
    std::map<double, double> QvsR;
    std::map<double, double> QvsDR;
    std::map<double, double> QvsDQ;

    // Read numbers from file:
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

        QStringList lineEntries = line.split(m_separator.trimmed()); // #TODO: optimize

        if (lastColumnCount == -1)
            lastColumnCount = lineEntries.count();
        else if (lastColumnCount != lineEntries.count())
            return QString(
                       "Error: number of columns is not constant over all lines (found in line %1)")
                .arg(lineNr);

        QVector<double> rowEntriesAsDouble;

        for (auto entry : lineEntries) {
            bool ok = false;
            double val = entry.toDouble(&ok);
            if (!ok)
                val = NAN; // #TODO: review

            rowEntriesAsDouble << val;
        }

        entriesAsDouble << rowEntriesAsDouble;
        entriesAsString << lineEntries;
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
    typeStr[3] = "dQ";
    typeStr[4] = "ignored";

    for (int col = 0; col < ncols; col++) {
        if (m_columnDefinitions.contains(col))
            tableEntries << typeStr[m_columnDefinitions[col].dataType];
        else
            tableEntries << typeStr[4];
    }

    for (auto line : entriesAsString)
        tableEntries << line;

    QString s = bold("Data table:");

    s += table((int)ncols, tableEntries, "border=\"1\" cellpadding=\"10\" cellspacing=\"0\"", true);

    // -- create plot
    int qCol = 0; // #TODO: correct column!
    int rCol = 1;

    QVector<double> qVec;
    QVector<double> rVec;

    for (const auto lineAsDoubles : entriesAsDouble) {
        qVec << lineAsDoubles[qCol];
        rVec << lineAsDoubles[rCol];
    }

    auto graph = plotWidget->addGraph();
    graph->addData(qVec, rVec);
    plotWidget->rescaleAxes();

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

    for (int column = 0; column < 4; column++) {
        if (m_columnDefinitions.contains(column)) {
            const auto d = m_columnDefinitions[column];
            m_propertiesWidget->setType(column, d.dataType);
            m_propertiesWidget->m_unitCombos[column]->setCurrentText(d.unit);
            m_propertiesWidget->m_factors[column]->setValue(d.factor);
        } else {
            m_propertiesWidget->setType(column, 4);
        }
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

    m_columnDefinitions[0].dataType = 0;
    m_columnDefinitions[0].unit = "";
    m_columnDefinitions[0].factor = 1.0;

    m_columnDefinitions[1].dataType = 1;
    m_columnDefinitions[1].unit = "";
    m_columnDefinitions[1].factor = 1.0;

    m_columnDefinitions[2].dataType = 2;
    m_columnDefinitions[2].unit = "";
    m_columnDefinitions[2].factor = 1.0;

    m_columnDefinitions[3].dataType = 3;
    m_columnDefinitions[3].unit = "";
    m_columnDefinitions[3].factor = 1.0;
}

QByteArray AutomaticMultiColumnDataLoader1D::serialize() const
{
    QByteArray a;
    QDataStream s(&a, QIODevice::WriteOnly);
    s << m_separator;
    s << m_headerPrefix;
    s << m_linesToSkip;

    s << (quint8)m_columnDefinitions.count();
    for (quint8 column : m_columnDefinitions.keys()) {
        s << column;
        s << m_columnDefinitions[column].dataType;
        s << m_columnDefinitions[column].unit;
        s << m_columnDefinitions[column].factor;
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
    quint8 nColumns;
    s >> nColumns;
    for (int i = 0; i < nColumns; i++) {
        quint8 column;
        s >> column;
        s >> m_columnDefinitions[column].dataType;
        s >> m_columnDefinitions[column].unit;
        s >> m_columnDefinitions[column].factor;
    }
}

QVector<QPair<int, int>>
AutomaticMultiColumnDataLoader1D::expandLineNumberPattern(const QString& pattern, bool* ok) const
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

    m_columnDefinitions.clear();

    for (int col = 0; col < 4; col++) {
        const bool isIgnored = (m_propertiesWidget->m_typeCombos[col]->currentIndex() == 4);
        if (!isIgnored) {
            m_columnDefinitions[col].dataType =
                m_propertiesWidget->m_typeCombos[col]->currentIndex();
            m_columnDefinitions[col].unit = m_propertiesWidget->unit(col);
            m_columnDefinitions[col].factor = m_propertiesWidget->factor(col);
        }
    }
}
