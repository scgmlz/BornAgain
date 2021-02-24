//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/QREDataLoader.cpp
//! @brief     Implements class QREDataLoader
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/QREDataLoader.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "Device/Unit/AxisNames.h"
#include "GUI/coregui/DataLoaders/QREDataLoaderProperties.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/utils/ImportDataInfo.h"
#include "qcustomplot.h"
#include "ui_QREDataLoaderProperties.h"
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

QREDataLoader::QREDataLoader() : m_propertiesWidget(nullptr)
{
    initWithDefaultProperties();
}

QString QREDataLoader::name() const
{
    return "CSV file (Reflectometry - Q/R/E)";
}

QString QREDataLoader::info() const
{
    return "Supports up to 3 columns (Q, R, E). Columns can be configured.";
}

QString QREDataLoader::persistentClassName() const
{
    return "QREDataLoader";
}

QString QREDataLoader::preview(const QString& filepath, QCustomPlot* plotWidget) const
{
    // -- create plot
    int dRCol = m_parsingResult.importSettings.m_columnDefinitions[DataType::dR].column;

    QVector<double> qVec;
    QVector<double> rVec;
    QVector<double> eVec;

    const bool addError = m_parsingResult.importSettings.m_columnDefinitions[DataType::dR].enabled
                          && (m_parsingResult.columnCount > dRCol);

    for (const auto d : m_parsingResult.qValues)
        qVec << d.second;

    for (const auto d : m_parsingResult.rValues)
        rVec << d.second;

    if (addError)
        for (const auto d : m_parsingResult.eValues)
            eVec << d.second;

    auto graph = plotWidget->addGraph();
    graph->addData(qVec, rVec);

    if (!eVec.empty()) {
        auto errorBars = new QCPErrorBars(plotWidget->xAxis, plotWidget->yAxis);

        errorBars->setData(eVec);
        errorBars->setDataPlottable(graph);
    }

    plotWidget->rescaleAxes();
    plotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plotWidget->xAxis->setLabel("Q [1/nm]");
    plotWidget->yAxis->setLabel("R");

    return "";
}

void QREDataLoader::populatePropertiesWidget(QWidget* parent)
{
    if (m_propertiesWidget == nullptr)
        m_propertiesWidget = new QREDataLoaderProperties;

    QHBoxLayout* l = new QHBoxLayout(parent);
    l->setContentsMargins(0, 0, 0, 0);
    parent->setLayout(l);
    l->addWidget(m_propertiesWidget);

    if (m_importSettings.m_separator == " ")
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText("<SPACE>");
    else if (m_importSettings.m_separator == "\t")
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText("<TAB>");
    else
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText(m_importSettings.m_separator);

    m_propertiesWidget->m_ui->headerPrefixEdit->setText(m_importSettings.m_headerPrefix);
    m_propertiesWidget->m_ui->linesToSkipEdit->setText(m_importSettings.m_linesToSkip);

    for (auto dataType : {DataType::Q, DataType::R, DataType::dR}) {
        m_propertiesWidget->columnSpinBox((int)dataType)
            ->setValue(m_importSettings.m_columnDefinitions[dataType].column
                       + 1); // view is 1-based

        m_propertiesWidget->factorSpinBox((int)dataType)
            ->setValue(m_importSettings.m_columnDefinitions[dataType].factor);
    }

    m_propertiesWidget->m_ui->enableErrorCheckBox->setChecked(
        m_importSettings.m_columnDefinitions[DataType::dR].enabled);

    if (m_importSettings.m_columnDefinitions[DataType::Q].unit == UnitInFile::perAngstrom)
        m_propertiesWidget->m_ui->qUnitCombo->setCurrentIndex(1);
    else
        m_propertiesWidget->m_ui->qUnitCombo->setCurrentIndex(0); // 1/nm

    QObject::connect(m_propertiesWidget, &QREDataLoaderProperties::propertiesChanged, [this]() {
        applyProperties();
        emit propertiesChanged();
    });
}

void QREDataLoader::initWithDefaultProperties()
{
    m_importSettings.m_separator = ";";
    m_importSettings.m_headerPrefix = "#,//";
    m_importSettings.m_linesToSkip = "";

    for (auto dataType : {DataType::Q, DataType::R, DataType::dR}) {
        m_importSettings.m_columnDefinitions[dataType].enabled = true;
        m_importSettings.m_columnDefinitions[dataType].column = (int)dataType;
        m_importSettings.m_columnDefinitions[dataType].unit = UnitInFile::none;
        m_importSettings.m_columnDefinitions[dataType].factor = 1.0;
    }

    m_importSettings.m_columnDefinitions[DataType::Q].unit = UnitInFile::perNanoMeter;
}

QByteArray QREDataLoader::serialize() const
{
    // #badataloader ++ add version?

    QByteArray a;
    QDataStream s(&a, QIODevice::WriteOnly);

    s << m_importSettings.toByteArray();
    s << m_parsingResult.lines;
    s << m_parsingResult.originalEntriesAsDouble;
    s << m_parsingResult.qValues;
    s << m_parsingResult.rValues;
    s << m_parsingResult.eValues;
    s << m_parsingResult.columnCount;
    s << m_parsingResult.hashOfFile;
    s << m_parsingResult.errors;
    s << m_parsingResult.warnings;
    s << m_parsingResult.importSettings.toByteArray();

    return a;
}

void QREDataLoader::deserialize(const QByteArray& data)
{
    // #baimport ++ check version

    m_parsingResult.clear();
    QDataStream s(data);

    QByteArray b;
    s >> b;
    m_importSettings.fromByteArray(b);

    s >> m_parsingResult.lines;
    s >> m_parsingResult.originalEntriesAsDouble;
    s >> m_parsingResult.qValues;
    s >> m_parsingResult.rValues;
    s >> m_parsingResult.eValues;
    s >> m_parsingResult.columnCount;
    s >> m_parsingResult.hashOfFile;
    s >> m_parsingResult.errors;
    s >> m_parsingResult.warnings;

    b.clear();
    s >> b;
    m_parsingResult.importSettings.fromByteArray(b); // #badataloader ++ check result
}

AbstractDataLoader* QREDataLoader::clone() const
{
    auto loader = new QREDataLoader();
    loader->deserialize(serialize());
    return loader;
}

void QREDataLoader::importFile(const QString& filename, RealDataItem* item, QStringList* errors,
                               QStringList* warnings) const
{
    // Important: If the current options match the ones in m_parsingResult, then nothing should be
    // performed. Otherwise e.g. a linked instrument may have to be re-linked

    errors->clear();
    warnings->clear();

    // #baimport refactor all the error handling
    ASSERT(item != nullptr);
    ASSERT(item->isSpecularData());

    const auto invalidateItemData = [item]() {
        item->removeNativeData();
        item->specularDataItem()->setOutputData(nullptr);
    };

    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        m_parsingResult.clear();
        *errors << "File '" + filename + "' could not be opened";
        return;
    }

    QCryptographicHash hash(QCryptographicHash::Md5);
    if (!hash.addData(&file)) {
        m_parsingResult.clear();
        *errors << "File '" + filename + "' could not be read";
        return;
    }

    const bool fileChanged =
        m_parsingResult.hashOfFile.isEmpty() || (hash.result() != m_parsingResult.hashOfFile);
    const bool settingsChanged = m_parsingResult.importSettings != m_importSettings;
    const bool parsingSettingsChanged =
        m_parsingResult.importSettings.m_headerPrefix != m_importSettings.m_headerPrefix
        || m_parsingResult.importSettings.m_linesToSkip != m_importSettings.m_linesToSkip
        || m_parsingResult.importSettings.m_separator != m_importSettings.m_separator;
    const bool calculationSettingsChanged =
        m_parsingResult.importSettings.m_columnDefinitions != m_importSettings.m_columnDefinitions;
    const bool calculationIsNecessary =
        (fileChanged || parsingSettingsChanged || calculationSettingsChanged);
    const bool creationOfOutputDataIsNecessary = calculationIsNecessary;

    if (fileChanged || parsingSettingsChanged) {
        // everything has to be re-read
        m_parsingResult.clear();
        file.seek(0);
        parseFile(file);
        m_parsingResult.hashOfFile = hash.result();
    }

    if (calculationIsNecessary) {
        calculateFromParseResult();
    }

    m_parsingResult.importSettings = m_importSettings;

    // -- make a few checks (mainly for fulfilling PointwiseAxis::sanityCheck())
    if (m_parsingResult.qValues.size() < 2) {
        *errors << "At least two full rows must exist";
    }
    if (!std::is_sorted(m_parsingResult.qValues.begin(), m_parsingResult.qValues.end())) {
        *errors << "Q coordinates must be sorted in ascending order";
    }
    if (std::adjacent_find(m_parsingResult.qValues.begin(), m_parsingResult.qValues.end())
        != m_parsingResult.qValues.end()) {
        *errors << "Q coordinates must not contain duplicate values";
    }

    if (!errors->isEmpty()) {
        invalidateItemData();
        return;
    }

    if (creationOfOutputDataIsNecessary) {

        try {
            createOutputDataFromParsingResult(item);
        } catch (...) {
            *errors << "Import not successful - caught an exception.";
            invalidateItemData();
        }
    }
}

bool QREDataLoader::fillImportDetailsTable(QTableWidget* table, bool fileContent, bool rawContent,
                                           bool processedContent) const
{
    bool showErrorColumn =
        m_parsingResult.importSettings.m_columnDefinitions[QREDataLoader::DataType::dR].enabled;
    QString qUnit = " [1/nm]";

    auto t = table;
    t->clear();

    int colCount = 0;
    if (fileContent)
        colCount++;

    if (rawContent)
        colCount += m_parsingResult.columnCount;

    if (processedContent)
        colCount += showErrorColumn ? 3 : 2;

    if (!fileContent && !rawContent && !processedContent) {
        t->setRowCount(0);
        return true;
    }

    t->setColumnCount(colCount);
    t->setRowCount(fileContent ? m_parsingResult.lines.size()
                               : m_parsingResult.originalEntriesAsDouble.size());

    const auto cell = [t](int row, int col, double s, const QColor& backColor) {
        auto tableItem = new QTableWidgetItem(QString::number(s));
        tableItem->setBackgroundColor(backColor);
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        t->setItem(row, col, tableItem);
    };

    QColor backgroundColorFileContent(239, 237, 248);
    QColor backgroundColorRawContent(247, 240, 210);
    QColor backgroundColorProcessedContent(191, 232, 242);

    int dataCol = 0;
    if (fileContent) {
        auto headerItem = new QTableWidgetItem("File content (text)");
        headerItem->setBackgroundColor(backgroundColorFileContent.darker(150));
        t->setHorizontalHeaderItem(0, headerItem);
        int row = 0;
        for (auto line : m_parsingResult.lines) {
            const bool skipped = line.first;
            QString lineContent = line.second;
            lineContent.replace("\t", " --> ");
            auto tableItem = new QTableWidgetItem(lineContent);
            if (skipped)
                tableItem->setTextColor(Qt::lightGray); // #baimport review
            tableItem->setBackgroundColor(backgroundColorFileContent);
            tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
            t->setItem(row++, 0, tableItem);
        }
        dataCol = 1;
    }

    if (rawContent) {
        for (int col = 0; col < m_parsingResult.columnCount; col++) {
            t->setHorizontalHeaderItem(dataCol + col,
                                       new QTableWidgetItem(QString("Column %1 raw").arg(col + 1)));
        }

        for (auto rowContent : m_parsingResult.originalEntriesAsDouble) {
            int lineNr = rowContent.first;
            int dataRow = lineNr - 1; // lineNr is 1-based

            for (auto v : rowContent.second)
                cell(dataRow, dataCol++, v, backgroundColorRawContent);
            dataCol -= rowContent.second.size();
        }
        dataCol += m_parsingResult.columnCount;
    }

    if (processedContent) {
        t->setHorizontalHeaderItem(dataCol, new QTableWidgetItem("Q" + qUnit));
        t->setHorizontalHeaderItem(dataCol + 1, new QTableWidgetItem("R"));
        if (showErrorColumn)
            t->setHorizontalHeaderItem(dataCol + 2, new QTableWidgetItem("E"));

        for (auto rowContent : m_parsingResult.qValues) {
            int lineNr = rowContent.first;
            int dataRow = lineNr - 1; // lineNr is 1-based
            auto v = rowContent.second;
            cell(dataRow, dataCol + 0, v, backgroundColorProcessedContent);
        }

        for (auto rowContent : m_parsingResult.rValues) {
            int lineNr = rowContent.first;
            int dataRow = lineNr - 1; // lineNr is 1-based
            auto v = rowContent.second;
            cell(dataRow, dataCol + 1, v, backgroundColorProcessedContent);
        }

        if (showErrorColumn) {
            for (auto rowContent : m_parsingResult.eValues) {
                int lineNr = rowContent.first;
                int dataRow = lineNr - 1; // lineNr is 1-based
                auto v = rowContent.second;
                cell(dataRow, dataCol + 2, v, backgroundColorProcessedContent);
            }
        }
    }

    t->resizeColumnsToContents();

    return true;
}

void QREDataLoader::parseFile(QFile& file) const
{
    // #baimport optimize: check which import settings changed. E.g. if only q-factor changed, only
    // regenerate qValues
    // #baimport optimize: better error handling
    // #baimport ++ problem: errors/warnings can't be deleted separately for parsing and
    // calculation. When caching them, this results in wrong lists. Maybe they are obsolete anyway?
    // Only one error at a time? Or have parseErrors, calculationErrors?

    m_parsingResult.clear();

    const QStringList headerPrefixes = (m_importSettings.m_headerPrefix.trimmed().isEmpty())
                                           ? QStringList()
                                           : m_importSettings.m_headerPrefix.split(",");

    const auto lineIsHeader = [headerPrefixes](const QString& line) {
        for (auto prefix : headerPrefixes) {
            if (line.startsWith(prefix.trimmed()))
                return true;
        }

        return false;
    };

    const auto skippedLines = expandLineNumberPattern(m_importSettings.m_linesToSkip);
    const auto lineShouldBeSkipped = [skippedLines](int lineNr) {
        for (auto pair : skippedLines) {
            if (lineNr >= pair.first && lineNr <= pair.second)
                return true;
        }
        return false;
    };

    QTextStream in(&file);
    int lineNr = 0;
    int lastColumnCount = -1;
    // if separator is SPACE: e.g. three consecutive SPACEs do not represent 3 columns => delete
    // empty parts
    QString::SplitBehavior splitBehavior =
        m_importSettings.m_separator == " " ? QString::SkipEmptyParts : QString::KeepEmptyParts;

    while (!in.atEnd()) {
        lineNr++;

        QString line = in.readLine();

        const bool skip =
            lineIsHeader(line) || lineShouldBeSkipped(lineNr) || line.trimmed().isEmpty();

        m_parsingResult.lines << qMakePair(skip, line);
        if (skip)
            continue;

        QStringList lineEntries = line.split(m_importSettings.m_separator, splitBehavior);

        if (lastColumnCount == -1)
            lastColumnCount = lineEntries.count();
        else if (lastColumnCount != lineEntries.count()) {
            m_parsingResult.warnings
                << QString("Number of columns is not constant over all lines (found in line %1)")
                       .arg(lineNr);
        }

        m_parsingResult.columnCount = std::max(m_parsingResult.columnCount, lineEntries.count());

        QVector<double> rowEntriesAsDouble;

        for (int col = 0; col < lineEntries.count(); col++) {
            bool ok = false;
            double val = lineEntries[col].toDouble(&ok);
            if (!ok)
                val = std::numeric_limits<double>::quiet_NaN();

            rowEntriesAsDouble << val;
        }

        m_parsingResult.originalEntriesAsDouble << qMakePair(lineNr, rowEntriesAsDouble);
    }
}

void QREDataLoader::calculateFromParseResult() const
{
    m_parsingResult.clearCalculatedValues();

    // -- calculate the Q/R/E values (take from specified column, use factor)
    const auto& c = m_importSettings.m_columnDefinitions; // easier access
    const bool errorColumnIsEnabled = c[DataType::dR].enabled;
    const double unitFac = (c[DataType::Q].unit == UnitInFile::perAngstrom) ? 10.0 : 1.0;
    const double qFactor = c[DataType::Q].factor * unitFac;
    const double rFactor = c[DataType::R].factor;
    const double eFactor = c[DataType::dR].factor;

    const int qCol = c[DataType::Q].column;
    const int rCol = c[DataType::R].column;
    const int eCol = c[DataType::dR].column;

    QSet<double> foundQValues;

    for (auto rowContent : m_parsingResult.originalEntriesAsDouble) {
        int lineNr = rowContent.first;
        const auto& rawValues = rowContent.second;

        const bool qColIsValid = qCol >= 0 && qCol < rawValues.size();
        const bool rColIsValid = rCol >= 0 && rCol < rawValues.size();
        const bool eColIsValid = eCol >= 0 && eCol < rawValues.size();

        const double q =
            qColIsValid ? rawValues[qCol] * qFactor : std::numeric_limits<double>::quiet_NaN();
        const double r =
            rColIsValid ? rawValues[rCol] * rFactor : std::numeric_limits<double>::quiet_NaN();
        const double e =
            eColIsValid ? rawValues[eCol] * eFactor : std::numeric_limits<double>::quiet_NaN();

        const bool containsNaN =
            (std::isnan(q) || std::isnan(r) || (std::isnan(e) && errorColumnIsEnabled));

        const bool isDuplicateQ = foundQValues.contains(q);

        // #baimport lines could be ignored or loading could be refused. Ignore means more
        // flexibility, but may hide that the data/file is corrupted in general

        // ignore lines when a resulting value would be NAN or in case of duplicate Q values
        // #baimport make this dependent from a UI checkbox?
        if (!containsNaN && !isDuplicateQ) {
            m_parsingResult.qValues << qMakePair(lineNr, q);
            m_parsingResult.rValues << qMakePair(lineNr, r);
            m_parsingResult.eValues << qMakePair(lineNr, e);
            foundQValues << q;
        }
    }
}

void QREDataLoader::createOutputDataFromParsingResult(RealDataItem* item) const
{
    // -- create OutputData
    std::vector<double> qVec;
    std::vector<double> rVec;

    for (const auto d : m_parsingResult.qValues)
        qVec.push_back(d.second);

    for (const auto d : m_parsingResult.rValues)
        rVec.push_back(d.second);

    OutputData<double>* oData = new OutputData<double>();
    oData->addAxis(PointwiseAxis("qVector", qVec));
    oData->setRawDataVector(rVec);

    // -- Replacement of item->setImportData(std::move(data));
    item->initNativeData();

    QString units_name = JobItemUtils::nameFromAxesUnits(Axes::Units::QSPACE);

    // -- Replacement of specularItem->reset(std::move(data));
    SpecularDataItem* specularItem = item->specularDataItem();
    ComboProperty combo = ComboProperty() << units_name;

    specularItem->setItemValue(SpecularDataItem::P_AXES_UNITS, combo.variant());
    specularItem->getItem(SpecularDataItem::P_AXES_UNITS)->setVisible(true);

    auto label_map = AxisNames::InitSpecAxis();
    const auto xAxisTitle = QString::fromStdString(label_map[Axes::Units::QSPACE]);
    const auto yAxisTitle = "Signal [a.u.]"; // taken from ImportDataInfo::axisLabel

    specularItem->setXaxisTitle(xAxisTitle);
    specularItem->setYaxisTitle(yAxisTitle);
    specularItem->setOutputData(oData); // takes ownership of odata
    specularItem->setAxesRangeToData();

    item->setNativeDataUnits(units_name);
    item->setNativeOutputData(oData->clone()); // takes ownership of odata
}

void QREDataLoader::applyProperties()
{
    if (!m_propertiesWidget)
        return;

    auto ui = m_propertiesWidget->m_ui;

    m_importSettings.m_separator = ui->separatorCombo->currentText();
    if (m_importSettings.m_separator == "<TAB>")
        m_importSettings.m_separator = "\t";
    if (m_importSettings.m_separator == "<SPACE>")
        m_importSettings.m_separator = " ";

    m_importSettings.m_headerPrefix = ui->headerPrefixEdit->text();
    m_importSettings.m_linesToSkip = ui->linesToSkipEdit->text();

    for (auto dataType : m_importSettings.m_columnDefinitions.keys()) {
        auto& colDef = m_importSettings.m_columnDefinitions[dataType];

        colDef.column = m_propertiesWidget->columnSpinBox((int)dataType)->value() - 1;
        colDef.factor = m_propertiesWidget->factor((int)dataType);
    }

    m_importSettings.m_columnDefinitions[DataType::Q].unit =
        m_propertiesWidget->m_ui->qUnitCombo->currentIndex() == 0 ? UnitInFile::perNanoMeter
                                                                  : UnitInFile::perAngstrom;

    m_importSettings.m_columnDefinitions[DataType::dR].enabled =
        m_propertiesWidget->m_ui->enableErrorCheckBox->isChecked();
}

void QREDataLoader::ParsingResult::clear()
{
    lines.clear();
    originalEntriesAsDouble.clear();
    qValues.clear();
    rValues.clear();
    eValues.clear();
    columnCount = 0;
    hashOfFile.clear();
    errors.clear();
    warnings.clear();
    importSettings.m_columnDefinitions.clear(); // sufficient
}

void QREDataLoader::ParsingResult::clearCalculatedValues()
{
    qValues.clear();
    rValues.clear();
    eValues.clear();
}

bool QREDataLoader::ImportSettings::operator!=(const ImportSettings& other) const
{
    return toByteArray() != other.toByteArray();
}

QByteArray QREDataLoader::ImportSettings::toByteArray() const
{
    // #badataloader ++ add version
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
        s << (quint8)m_columnDefinitions[dataType].unit;
        s << m_columnDefinitions[dataType].factor;
    }

    return a;
}

bool QREDataLoader::ImportSettings::fromByteArray(const QByteArray& data)
{
    // #baimport ++ check version
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
        quint8 unit;
        s >> unit;
        colDef.unit = UnitInFile(unit);
        s >> colDef.factor;
    }

    return true;
}

// #baimport why is this necessary?
bool QREDataLoader::ColumnDefinition::operator==(const ColumnDefinition& other) const
{
    return enabled == other.enabled && column == other.column && unit == other.unit
           && factor == other.factor;
}
