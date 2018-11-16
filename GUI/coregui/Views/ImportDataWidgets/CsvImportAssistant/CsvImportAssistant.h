// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant.h
//! @brief     Defines class CsvImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVIMPORTASSISTANT_H
#define CSVIMPORTASSISTANT_H

#include "CsvDataColumn.h"
#include "CsvReader.h"
#include "DataFormatUtils.h"
#include "ImportDataInfo.h"
#include "WinDllMacros.h"
#include <QStringList>
#include <QWidget>
#include <memory>
//! Logic for importing intensity data from csv files
class BA_CORE_API_ CsvImportAssistant : public QObject
{
    Q_OBJECT
public:
    CsvImportAssistant(const QString& file, const bool useGUI = false, QWidget* parent = nullptr);
    ImportDataInfo getData() { return m_dataAvailable ? fillData() : ImportDataInfo(); }
    static void showErrorMessage(std::string message);
    void setIntensityColumn(size_t iCol, double multiplier = 1.0);
    void setCoordinateColumn(size_t iCol, AxesUnits units, double multiplier = 1.0);
    void setFirstRow(size_t iRow);
    void setLastRow(size_t iRow);
    size_t columnCount() { return size_t(m_csvArray[0].size()); }
    char separator() { return m_separator; }

private:
    bool loadCsvFile();
    ImportDataInfo fillData();
    bool hasEqualLengthLines(csv::DataArray& dataArray);
    char guessSeparator() const;
    void removeBlankColumns();
    void runDataSelector(QWidget* parent);
    std::vector<double> getValuesFromColumn(size_t jcol, double multiplier = 1.0);
    void resetSelection();
    void resetAssistant();

    QString m_fileName;
    std::unique_ptr<CSVFile> m_csvFile;
    csv::DataArray m_csvArray;
    char m_separator;
    size_t m_intensityColNum;
    double m_intensityMultiplier;
    size_t m_coordinateColNum;
    double m_coordinateMultiplier;
    size_t m_firstRow;
    size_t m_lastRow;
    AxesUnits m_units;
    bool m_dataAvailable;
};
#endif // CSVIMPORTASSISTANT_H
