// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvDataColumn.h
//! @brief     Defines classes CsvIntensityColumn and CsvCoordinateColumn
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_CSVIMPORTASSISTANT_CSVDATACOLUMN_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_CSVIMPORTASSISTANT_CSVDATACOLUMN_H

#include "Core/Unit/IUnitConverter.h"
#include "GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvNamespace.h"

class CsvIntensityColumn
{
public:
    // Constructors:
    CsvIntensityColumn();
    CsvIntensityColumn(const CsvIntensityColumn& toCopy);
    CsvIntensityColumn(int colNum, double multiplier, csv::DataColumn values);

    // Getters:
    int columnNumber() const;
    double multiplier() const;
    csv::DataColumn values() const;

    // Setters:
    void setColNum(int const colNum);
    void setMultiplier(double const multiplier);
    void setValues(csv::DataColumn const values);
    void resetColumn(int colNum = -1, double multiplier = 1., csv::DataColumn values = {});

private:
    int m_colNum;
    double m_multiplier;
    csv::DataColumn m_values;
};

class CsvCoordinateColumn : public CsvIntensityColumn
{
public:
    // Constructors:
    CsvCoordinateColumn();
    CsvCoordinateColumn(const CsvCoordinateColumn& toCopy);
    CsvCoordinateColumn(int colNum, double multiplier, csv::DataColumn values, Axes::Units units);

    // Getters:
    Axes::Units units() const;
    csv::ColumnType name() const { return m_name; }

    // Setters:
    void setUnits(Axes::Units const units);
    void setName(csv::ColumnType const name);
    void resetColumn(int colNum = -1, double multiplier = 1., csv::DataColumn values = {},
                     Axes::Units units = Axes::Units::NBINS,
                     csv::ColumnType name = csv::_intensity_);

private:
    Axes::Units m_units;
    csv::ColumnType m_name;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_CSVIMPORTASSISTANT_CSVDATACOLUMN_H
