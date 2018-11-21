// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvDataColumn.cpp
//! @brief     Implements classes CsvIntensityColumn and CsvCoordinateColumn
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvDataColumn.h"

/*Csv Intensity Column*/

// Constructors:
CsvIntensityColumn::CsvIntensityColumn() : m_colNum(-1), m_multiplier(1.0), m_values({})
{
}

CsvIntensityColumn::CsvIntensityColumn(const CsvIntensityColumn& toCopy)
    : m_colNum(toCopy.columnNumber()), m_multiplier(toCopy.multiplier()), m_values(toCopy.values())
{
}

CsvIntensityColumn::CsvIntensityColumn(int colNum, double multiplier, csv::DataColumn values)
    : m_colNum(colNum), m_multiplier(multiplier), m_values(values)
{
}

// Getters:
int CsvIntensityColumn::columnNumber() const
{
    return m_colNum;
}
double CsvIntensityColumn::multiplier() const
{
    return m_multiplier;
}
csv::DataColumn CsvIntensityColumn::values() const
{
    return m_values;
}

// Setters:
void CsvIntensityColumn::setColNum(int const colNum)
{
    m_colNum = colNum;
}
void CsvIntensityColumn::setMultiplier(double const multiplier)
{
    m_multiplier = multiplier;
}
void CsvIntensityColumn::setValues(csv::DataColumn const values)
{
    m_values = std::move(values);
}
void CsvIntensityColumn::resetColumn(int colNum, double multiplier, csv::DataColumn values)
{
    m_colNum = colNum;
    m_multiplier = multiplier;
    m_values = std::move(values);
}
CsvIntensityColumn& CsvIntensityColumn::operator=(const CsvIntensityColumn colToRep)
{
    m_colNum = colToRep.columnNumber();
    m_multiplier = colToRep.multiplier();
    m_values = colToRep.values();
    return *this;
}

/*Csv Coordinate Column*/

// Constructors:
CsvCoordinateColumn::CsvCoordinateColumn() : CsvIntensityColumn(), m_units(AxesUnits::NBINS)
{
}

CsvCoordinateColumn::CsvCoordinateColumn(const CsvCoordinateColumn& toCopy)
    : CsvIntensityColumn(toCopy), m_units(toCopy.units())
{
}

CsvCoordinateColumn::CsvCoordinateColumn(int colNum, double multiplier, csv::DataColumn values,
                                         AxesUnits units)

    : CsvIntensityColumn(colNum, multiplier, values), m_units(units)
{
}
// Getters:
AxesUnits CsvCoordinateColumn::units() const
{
    return m_units;
}
QString CsvCoordinateColumn::name() const
{
    return m_name;
}
// Setters:
void CsvCoordinateColumn::setUnits(AxesUnits const units)
{
    m_units = units;
}
void CsvCoordinateColumn::setName(QString const name)
{
    m_name = name;
}
void CsvCoordinateColumn::resetColumn(int colNum, double multiplier, csv::DataColumn values,
                                      AxesUnits units, QString name)
{
    CsvIntensityColumn::resetColumn(colNum, multiplier, values);
    m_units = units;
    m_name = name;
}
CsvCoordinateColumn& CsvCoordinateColumn::operator=(const CsvCoordinateColumn colToRep)
{
    m_units = colToRep.units();
    m_name = colToRep.name();
    return *this;
}
