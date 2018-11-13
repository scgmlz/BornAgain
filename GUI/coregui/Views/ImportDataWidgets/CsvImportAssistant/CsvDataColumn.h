#ifndef CSVDATACOLUMN_H
#define CSVDATACOLUMN_H

#include "IUnitConverter.h"
#include "CsvNamespace.h"
#include <QStringList>


class CsvDataColumn
{
public:
    // Constructors:
    CsvDataColumn() : m_units(AxesUnits::NBINS), m_multiplier(1.0), m_values({}) {}

    CsvDataColumn(CsvDataColumn& toCopy)
        : m_units(toCopy.units()), m_multiplier(toCopy.multiplier()), m_values(toCopy.values())
    {
    }

    CsvDataColumn(AxesUnits units, double multiplier, csv::DataColumn values)
        : m_units(units), m_multiplier(multiplier), m_values(values)
    {
    }

    // Getters:
    AxesUnits units() { return m_units; }
    double multiplier() { return m_multiplier; }
    csv::DataColumn values() { return m_values; }

    // Setters:
    void setUnits(AxesUnits units) { m_units = units; }
    void setMultiplier(double multiplier) { m_multiplier = multiplier; }
    void setValues(csv::DataColumn values) { m_values = values; }

private:
    AxesUnits m_units;
    double m_multiplier;
    csv::DataColumn m_values;
};

#endif // CSVDATACOLUMN_H
