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
    static double stringToDouble(std::string string_to_parse);
    void setIntensityColumn(unsigned iCol, double multiplier = 1.0);
    void setCoordinateColumn(unsigned iCol, AxesUnits units, double multiplier = 1.0);
    void setFirstRow(unsigned iRow);
    void setLastRow(unsigned iRow);
    unsigned columnCount() { return unsigned(m_csvArray[0].size()); }
    char separator() { return m_separator; }

private:
    bool loadCsvFile();
    ImportDataInfo fillData();
    bool hasEqualLengthLines(csv::DataArray& dataArray);
    char guessSeparator() const;
    void removeBlankColumns();
    void runDataSelector(QWidget* parent);
    std::vector<double> getValuesFromColumn(size_t jcol);
    void resetSelection();
    void resetAssistant();

    QString m_fileName;
    std::unique_ptr<CSVFile> m_csvFile;
    csv::DataArray m_csvArray;
    char m_separator;
    unsigned m_intensityColNum;
    double m_intensityMultiplier;
    unsigned m_coordinateColNum;
    double m_coordinateMultiplier;
    unsigned m_firstRow;
    unsigned m_lastRow;
    AxesUnits m_units;
    bool m_dataAvailable;
};
#endif // CSVIMPORTASSISTANT_H
