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

QVector<QPair<int, int>> expandLineNumberPattern(const QString& pattern, bool* ok = nullptr)
{
    QVector<QPair<int, int>> result;

    // splitting "1, 2-3" first on comma-separated tokens
    for (const auto& token : pattern.split(",")) {
        const auto parts = token.split("-");
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

struct Palette {
    static QColor backgroundColorFileContent;
    static QColor backgroundColorRawContent;
    static QColor backgroundColorProcessedContent;
    static QColor backgroundColorErrors;
    static QColor skippedLineTextColor;
};

QColor Palette::backgroundColorFileContent(239, 237, 248);
QColor Palette::backgroundColorRawContent(247, 240, 210);
QColor Palette::backgroundColorProcessedContent(191, 232, 242);
QColor Palette::backgroundColorErrors(247, 140, 146);
QColor Palette::skippedLineTextColor(Qt::lightGray);

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

void QREDataLoader::previewOfGraph(QCustomPlot* plotWidget) const
{
    // -- create plot
    int dRCol = m_importResult.importSettings.columnDefinitions[DataType::dR].column;

    QVector<double> qVec;
    QVector<double> rVec;
    QVector<double> eVec;

    const bool addError = m_importResult.importSettings.columnDefinitions[DataType::dR].enabled
                          && (m_importResult.maxColumnCount > dRCol);

    for (const auto d : m_importResult.qValues)
        qVec << d.second;

    for (const auto d : m_importResult.rValues)
        rVec << d.second;

    if (addError)
        for (const auto d : m_importResult.eValues)
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
}

void QREDataLoader::populatePropertiesWidget(QWidget* parent)
{
    if (m_propertiesWidget == nullptr)
        m_propertiesWidget = new QREDataLoaderProperties;

    QHBoxLayout* l = new QHBoxLayout(parent);
    l->setContentsMargins(0, 0, 0, 0);
    parent->setLayout(l);
    l->addWidget(m_propertiesWidget);

    if (m_importSettings.separator == " ")
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText("<SPACE>");
    else if (m_importSettings.separator == "\t")
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText("<TAB>");
    else
        m_propertiesWidget->m_ui->separatorCombo->setCurrentText(m_importSettings.separator);

    m_propertiesWidget->m_ui->headerPrefixEdit->setText(m_importSettings.headerPrefix);
    m_propertiesWidget->m_ui->linesToSkipEdit->setText(m_importSettings.linesToSkip);

    for (const auto dataType : {DataType::Q, DataType::R, DataType::dR}) {
        m_propertiesWidget->columnSpinBox((int)dataType)
            ->setValue(m_importSettings.columnDefinitions[dataType].column + 1); // view is 1-based

        m_propertiesWidget->factorSpinBox((int)dataType)
            ->setValue(m_importSettings.columnDefinitions[dataType].factor);
    }

    m_propertiesWidget->m_ui->enableErrorCheckBox->setChecked(
        m_importSettings.columnDefinitions[DataType::dR].enabled);

    if (m_importSettings.columnDefinitions[DataType::Q].unit == UnitInFile::perAngstrom)
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
    m_importSettings.separator = ";";
    m_importSettings.headerPrefix = "#,//";
    m_importSettings.linesToSkip = "";

    for (const auto dataType : {DataType::Q, DataType::R, DataType::dR}) {
        m_importSettings.columnDefinitions[dataType].enabled = true;
        m_importSettings.columnDefinitions[dataType].column = (int)dataType;
        m_importSettings.columnDefinitions[dataType].unit = UnitInFile::none;
        m_importSettings.columnDefinitions[dataType].factor = 1.0;
    }

    m_importSettings.columnDefinitions[DataType::Q].unit = UnitInFile::perNanoMeter;
}

QByteArray QREDataLoader::serialize() const
{
    // #badataloader ++ add version?

    QByteArray a;
    QDataStream s(&a, QIODevice::WriteOnly);

    s << m_importSettings.toByteArray();
    s << m_importResult.lines;
    s << m_importResult.originalEntriesAsDouble;
    s << m_importResult.qValues;
    s << m_importResult.rValues;
    s << m_importResult.eValues;
    s << m_importResult.maxColumnCount;
    s << m_importResult.hashOfFile;
    s << m_importResult.calculationErrors;
    s << m_importResult.warnings;
    s << m_importResult.importSettings.toByteArray();

    return a;
}

void QREDataLoader::deserialize(const QByteArray& data)
{
    // #baimport ++ check version

    m_importResult.clear();
    QDataStream s(data);

    QByteArray b;
    s >> b;
    m_importSettings.fromByteArray(b);

    s >> m_importResult.lines;
    s >> m_importResult.originalEntriesAsDouble;
    s >> m_importResult.qValues;
    s >> m_importResult.rValues;
    s >> m_importResult.eValues;
    s >> m_importResult.maxColumnCount;
    s >> m_importResult.hashOfFile;
    s >> m_importResult.calculationErrors;
    s >> m_importResult.warnings;

    b.clear();
    s >> b;
    m_importResult.importSettings.fromByteArray(b); // #badataloader ++ check result
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

    ASSERT(item != nullptr);
    ASSERT(item->isSpecularData());

    const auto invalidateItemData = [item]() {
        item->removeNativeData();
        item->specularDataItem()->setOutputData(nullptr);
    };

    const bool fileWasAlreadyImported = !m_importResult.hashOfFile.isEmpty();

    QFile file(filename);
    const bool fileCouldBeOpened = file.open(QFile::ReadOnly | QIODevice::Text);

    if (!fileCouldBeOpened && !fileWasAlreadyImported) {
        m_importResult.clear();
        *errors << "File '" + filename + "' could not be opened";
        return;
    }

    QCryptographicHash hashOfFileOnDisk(QCryptographicHash::Md5);
    if (fileCouldBeOpened) {
        if (!hashOfFileOnDisk.addData(&file)) {
            m_importResult.clear();
            *errors << "File '" + filename + "' could not be read";
            return;
        }
    }

    const bool fileOnDiskChanged =
        fileCouldBeOpened && (hashOfFileOnDisk.result() != m_importResult.hashOfFile);
    const bool fileHasToBeReadFromDisk = fileOnDiskChanged;
    const bool settingsChanged = m_importResult.importSettings != m_importSettings;
    const bool parsingSettingsChanged =
        m_importResult.importSettings.headerPrefix != m_importSettings.headerPrefix
        || m_importResult.importSettings.linesToSkip != m_importSettings.linesToSkip
        || m_importResult.importSettings.separator != m_importSettings.separator;
    const bool calculationSettingsChanged =
        m_importResult.importSettings.columnDefinitions != m_importSettings.columnDefinitions;
    const bool calculationIsNecessary =
        (fileOnDiskChanged || parsingSettingsChanged || calculationSettingsChanged);
    const bool creationOfOutputDataIsNecessary = calculationIsNecessary;

    if (fileOnDiskChanged || parsingSettingsChanged) {
        // everything has to be re-parsed

        QString fileContent;
        if (fileHasToBeReadFromDisk) {
            file.seek(0);
            fileContent = file.readAll();
            file.close();
            parseFile(fileContent);
            m_importResult.hashOfFile = hashOfFileOnDisk.result();
        } else {
            for (const auto line : m_importResult.lines)
                fileContent.append(line.second + "\n");

            const auto backupHash = m_importResult.hashOfFile; // will be cleared while parsing
            parseFile(fileContent);
            m_importResult.hashOfFile = backupHash;
        }
    }

    if (calculationIsNecessary) {
        calculateFromParseResult();
        // #baimport calculation of values may issue errors. The respective lines are ignored. But
        // since this makes it possible to use files which may be corrupt in general, maybe in case
        // of calculation errors the whole file should be denied to load?
        // Ignore means more flexibility, but may hide that the data/file
        // is corrupted in general
    }

    m_importResult.importSettings = m_importSettings;

    // -- make a few checks (mainly for fulfilling PointwiseAxis::sanityCheck())
    if (m_importResult.qValues.size() < 2) {
        *errors << "At least two full rows must exist";
    }
    if (!std::is_sorted(m_importResult.qValues.begin(), m_importResult.qValues.end())) {
        *errors << "Q coordinates must be sorted in ascending order";
    }
    if (std::adjacent_find(m_importResult.qValues.begin(), m_importResult.qValues.end())
        != m_importResult.qValues.end()) {
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
        m_importResult.importSettings.columnDefinitions[QREDataLoader::DataType::dR].enabled;
    QString qUnit = " [1/nm]";

    auto t = table;
    t->clear();

    int colCount = 0;
    if (fileContent)
        colCount++;

    if (rawContent)
        colCount += m_importResult.maxColumnCount;

    if (processedContent)
        colCount += showErrorColumn ? 3 : 2;

    if (!m_importResult.calculationErrors.isEmpty())
        colCount++;

    if (!fileContent && !rawContent && !processedContent) {
        t->setRowCount(0);
        return true;
    }

    t->setColumnCount(colCount);
    // #baimport the following may be an improvement to hide empty lines, but then also info about
    // omitted lines is not available. If implementing this, then the filling of the table also has
    // to be reworked (also row -> lineNr in lambda "cell"!)
    /*
    t->setRowCount(fileContent ? m_importResult.lines.size()
                               : m_importResult.originalEntriesAsDouble.size());
    */
    t->setRowCount(m_importResult.lines.size());

    const auto cell = [this, t](int row, int col, double s, const QColor& backColor) {
        auto tableItem = new QTableWidgetItem(QString::number(s));
        tableItem->setBackgroundColor(backColor);
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        if (m_importResult.calculationErrors.contains(row))
            tableItem->setToolTip(m_importResult.calculationErrors[row]);
        t->setItem(row, col, tableItem);
    };

    int dataCol = 0;
    if (fileContent) {
        auto headerItem = new QTableWidgetItem("File content (text)");
        headerItem->setBackgroundColor(Palette::backgroundColorFileContent.darker(150));
        t->setHorizontalHeaderItem(0, headerItem);
        int row = 0;
        for (const auto line : m_importResult.lines) {
            const bool skipped = line.first;
            QString lineContent = line.second;
            lineContent.replace("\t", " --> ");
            auto tableItem = new QTableWidgetItem(lineContent);
            if (skipped)
                tableItem->setTextColor(Palette::skippedLineTextColor);
            tableItem->setBackgroundColor(Palette::backgroundColorFileContent);
            tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
            t->setItem(row++, 0, tableItem);
        }
        dataCol = 1;
    }

    if (rawContent) {
        for (int col = 0; col < m_importResult.maxColumnCount; col++) {
            t->setHorizontalHeaderItem(dataCol + col,
                                       new QTableWidgetItem(QString("Column %1 raw").arg(col + 1)));
        }

        for (const auto rowContent : m_importResult.originalEntriesAsDouble) {
            int lineNr = rowContent.first;
            int dataRow = lineNr - 1; // lineNr is 1-based

            for (const auto v : rowContent.second)
                cell(dataRow, dataCol++, v, Palette::backgroundColorRawContent);
            dataCol -= rowContent.second.size();
        }
        dataCol += m_importResult.maxColumnCount;
    }

    if (processedContent) {
        t->setHorizontalHeaderItem(dataCol, new QTableWidgetItem("Q" + qUnit));
        t->setHorizontalHeaderItem(dataCol + 1, new QTableWidgetItem("R"));
        if (showErrorColumn)
            t->setHorizontalHeaderItem(dataCol + 2, new QTableWidgetItem("E"));

        for (const auto rowContent : m_importResult.qValues) {
            int lineNr = rowContent.first;
            int dataRow = lineNr - 1; // lineNr is 1-based
            const auto v = rowContent.second;
            cell(dataRow, dataCol + 0, v, Palette::backgroundColorProcessedContent);
        }

        for (const auto rowContent : m_importResult.rValues) {
            int lineNr = rowContent.first;
            int dataRow = lineNr - 1; // lineNr is 1-based
            const auto v = rowContent.second;
            cell(dataRow, dataCol + 1, v, Palette::backgroundColorProcessedContent);
        }

        if (showErrorColumn) {
            for (const auto rowContent : m_importResult.eValues) {
                int lineNr = rowContent.first;
                int dataRow = lineNr - 1; // lineNr is 1-based
                const auto v = rowContent.second;
                cell(dataRow, dataCol + 2, v, Palette::backgroundColorProcessedContent);
            }
        }
        dataCol += showErrorColumn ? 3 : 2;
    }

    // - now the calculation errors if existing
    for (const auto lineNr : m_importResult.calculationErrors.keys()) {
        auto headerItem = new QTableWidgetItem("Parsing errors");
        headerItem->setBackgroundColor(Palette::backgroundColorErrors.darker(150));
        t->setHorizontalHeaderItem(dataCol, headerItem);

        for (const auto lineNr : m_importResult.calculationErrors.keys()) {
            const int dataRow = lineNr - 1; // lineNr is 1-based
            QString lineContent = m_importResult.calculationErrors[lineNr];

            auto tableItem = new QTableWidgetItem(lineContent);
            tableItem->setBackgroundColor(Palette::backgroundColorErrors);
            tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
            t->setItem(dataRow, dataCol, tableItem);
        }
    }

    t->resizeColumnsToContents();

    return true;
}

void QREDataLoader::guessSettings(const QString& filename)
{
    // #baimport implement estimateSettings (separator)
    // search for lines which have start with numbers, then try the separators
}

void QREDataLoader::parseFile(QString& fileContent) const
{
    m_importResult.clear();

    const QStringList headerPrefixes = (m_importSettings.headerPrefix.trimmed().isEmpty())
                                           ? QStringList()
                                           : m_importSettings.headerPrefix.split(",");

    const auto lineIsHeader = [headerPrefixes](const QString& line) {
        for (const auto prefix : headerPrefixes) {
            if (line.startsWith(prefix.trimmed()))
                return true;
        }

        return false;
    };

    const auto skippedLines = expandLineNumberPattern(m_importSettings.linesToSkip);
    const auto lineShouldBeSkipped = [skippedLines](int lineNr) {
        for (const auto pair : skippedLines) {
            if (lineNr >= pair.first && lineNr <= pair.second)
                return true;
        }
        return false;
    };

    QTextStream in(&fileContent);
    int lineNr = 0;
    int lastColumnCount = -1;
    // if separator is SPACE: e.g. three consecutive SPACEs do not represent 3 columns => delete
    // empty parts
    QString::SplitBehavior splitBehavior =
        m_importSettings.separator == " " ? QString::SkipEmptyParts : QString::KeepEmptyParts;

    while (!in.atEnd()) {
        lineNr++;

        QString line = in.readLine();

        const bool skip =
            lineIsHeader(line) || lineShouldBeSkipped(lineNr) || line.trimmed().isEmpty();

        m_importResult.lines << qMakePair(skip, line);
        if (skip)
            continue;

        QStringList lineEntries = line.split(m_importSettings.separator, splitBehavior);

        if (lastColumnCount == -1)
            lastColumnCount = lineEntries.count();
        else if (lastColumnCount
                 != lineEntries.count()) { // #baimport move this to error generation in importFile
            m_importResult.warnings
                << QString("Number of columns is not constant over all lines (found in line %1)")
                       .arg(lineNr);
        }

        m_importResult.maxColumnCount =
            std::max(m_importResult.maxColumnCount, lineEntries.count());

        QVector<double> rowEntriesAsDouble;

        for (int col = 0; col < lineEntries.count(); col++) {
            bool ok = false;
            double val = lineEntries[col].toDouble(&ok);
            if (!ok)
                val = std::numeric_limits<double>::quiet_NaN();

            rowEntriesAsDouble << val;
        }

        m_importResult.originalEntriesAsDouble << qMakePair(lineNr, rowEntriesAsDouble);
    }
}

void QREDataLoader::calculateFromParseResult() const
{
    m_importResult.clearCalculatedValues();

    // -- calculate the Q/R/E values (take from specified column, use factor)
    const auto& c = m_importSettings.columnDefinitions; // easier access
    const bool errorColumnIsEnabled = c[DataType::dR].enabled;
    const double unitFac = (c[DataType::Q].unit == UnitInFile::perAngstrom) ? 10.0 : 1.0;
    const double qFactor = c[DataType::Q].factor * unitFac;
    const double rFactor = c[DataType::R].factor;
    const double eFactor = c[DataType::dR].factor;

    const int qCol = c[DataType::Q].column;
    const int rCol = c[DataType::R].column;
    const int eCol = c[DataType::dR].column;

    QSet<double> foundQValues;

    for (const auto rowContent : m_importResult.originalEntriesAsDouble) {
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

        const bool lineContainsNaN =
            (std::isnan(q) || std::isnan(r) || (std::isnan(e) && errorColumnIsEnabled));

        if (std::isnan(q)) {
            m_importResult.calculationErrors[lineNr] =
                QString("Raw column %1 does not contain a valid number - line is discarded")
                    .arg(qCol + 1);
            continue;
        }

        if (std::isnan(r)) {
            m_importResult.calculationErrors[lineNr] =
                QString("Raw column %1 does not contain a valid number - line is discarded")
                    .arg(rCol + 1);
            continue;
        }

        if (std::isnan(e) && errorColumnIsEnabled) {
            m_importResult.calculationErrors[lineNr] =
                QString("Raw column %1 does not contain a valid number - line is discarded")
                    .arg(eCol + 1);
            continue;
        }

        if (foundQValues.contains(q)) {
            m_importResult.calculationErrors[lineNr] =
                QString("The value %1 for Q is duplicate - line is discarded").arg(q);
            continue;
        }

        if (r > 1.0) {
            m_importResult.calculationErrors[lineNr] =
                QString("The value %1 for R is greater than 1.0 - line is discarded").arg(r);
            continue;
        }

        if (r < 0.0) {
            m_importResult.calculationErrors[lineNr] =
                QString("The value %1 for R is less than 0 - line is discarded").arg(r);
            continue;
        }

        m_importResult.qValues << qMakePair(lineNr, q);
        m_importResult.rValues << qMakePair(lineNr, r);
        m_importResult.eValues << qMakePair(lineNr, e);
        foundQValues << q;
    }
}

void QREDataLoader::createOutputDataFromParsingResult(RealDataItem* item) const
{
    // -- create OutputData
    std::vector<double> qVec;
    std::vector<double> rVec;

    for (const auto d : m_importResult.qValues)
        qVec.push_back(d.second);

    for (const auto d : m_importResult.rValues)
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

    const auto ui = m_propertiesWidget->m_ui;

    m_importSettings.separator = ui->separatorCombo->currentText();
    if (m_importSettings.separator == "<TAB>")
        m_importSettings.separator = "\t";
    if (m_importSettings.separator == "<SPACE>")
        m_importSettings.separator = " ";

    m_importSettings.headerPrefix = ui->headerPrefixEdit->text();
    m_importSettings.linesToSkip = ui->linesToSkipEdit->text();

    for (const auto dataType : m_importSettings.columnDefinitions.keys()) {
        auto& colDef = m_importSettings.columnDefinitions[dataType];

        colDef.column = m_propertiesWidget->columnSpinBox((int)dataType)->value() - 1;
        colDef.factor = m_propertiesWidget->factor((int)dataType);
    }

    m_importSettings.columnDefinitions[DataType::Q].unit =
        m_propertiesWidget->m_ui->qUnitCombo->currentIndex() == 0 ? UnitInFile::perNanoMeter
                                                                  : UnitInFile::perAngstrom;

    m_importSettings.columnDefinitions[DataType::dR].enabled =
        m_propertiesWidget->m_ui->enableErrorCheckBox->isChecked();
}

void QREDataLoader::ParsingResult::clear()
{
    lines.clear();
    originalEntriesAsDouble.clear();
    qValues.clear();
    rValues.clear();
    eValues.clear();
    maxColumnCount = 0;
    hashOfFile.clear();
    calculationErrors.clear();
    warnings.clear();
    importSettings.columnDefinitions.clear(); // sufficient
}

void QREDataLoader::ParsingResult::clearCalculatedValues()
{
    qValues.clear();
    rValues.clear();
    eValues.clear();
    calculationErrors.clear();
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
    s << separator;
    s << headerPrefix;
    s << linesToSkip;

    s << (quint8)columnDefinitions.count();
    for (const auto dataType : columnDefinitions.keys()) {
        s << (quint8)dataType;
        s << columnDefinitions[dataType].enabled;
        s << columnDefinitions[dataType].column;
        s << (quint8)columnDefinitions[dataType].unit;
        s << columnDefinitions[dataType].factor;
    }

    return a;
}

bool QREDataLoader::ImportSettings::fromByteArray(const QByteArray& data)
{
    // #baimport ++ check version
    QDataStream s(data);
    s >> separator;
    s >> headerPrefix;
    s >> linesToSkip;

    columnDefinitions.clear();
    quint8 nDefs;
    s >> nDefs;
    for (int i = 0; i < nDefs; i++) {
        quint8 dataType;
        s >> dataType;
        auto& colDef = columnDefinitions[(DataType)dataType];
        s >> colDef.enabled;
        s >> colDef.column;
        quint8 unit;
        s >> unit;
        colDef.unit = UnitInFile(unit);
        s >> colDef.factor;
    }

    return true;
}

bool QREDataLoader::ColumnDefinition::operator==(const ColumnDefinition& other) const
{
    return enabled == other.enabled && column == other.column && unit == other.unit
           && factor == other.factor;
}
