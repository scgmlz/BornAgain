#ifndef CSVDATACOLUMN_H
#define CSVDATACOLUMN_H

#include "CsvNamespace.h"
#include "IUnitConverter.h"
#include <QStringList>

class CsvIntensityColumn
{
public:
    // Constructors:
    CsvIntensityColumn() : m_colNum(-1), m_multiplier(1.0), m_values({})
    {
    }

    CsvIntensityColumn(CsvIntensityColumn& toCopy)
        : m_colNum(toCopy.columnNumber())
        , m_multiplier(toCopy.multiplier())
        , m_values(toCopy.values())
    {
    }

    CsvIntensityColumn(int colNum, double multiplier,
                       csv::DataColumn values)
        : m_colNum(colNum),  m_multiplier(multiplier),
          m_values(values)
    {
    }

    // Getters:
    int columnNumber() const { return m_colNum; }
    double multiplier() const { return m_multiplier; }
    csv::DataColumn values() const { return m_values; }

    // Setters:
    void setColNum(int const colNum) { m_colNum = colNum; }
    void setMultiplier(double const multiplier) { m_multiplier = multiplier; }
    void setValues(csv::DataColumn const values) { m_values = values; }
    void resetColumn(int colNum = -1, double multiplier = 1.,
                     csv::DataColumn values = {})
    {
        m_colNum = colNum;
        m_multiplier = multiplier;
        m_values = values;
    }
    CsvIntensityColumn& operator =(const CsvIntensityColumn colToRep){
        m_colNum = colToRep.columnNumber() ;
        m_multiplier = colToRep.multiplier();
        m_values = colToRep.values();
        return *this;
    }


private:
    int m_colNum;
    double m_multiplier;
    csv::DataColumn m_values;
};

class CsvCoordinateColumn : public CsvIntensityColumn
{
public:
    // Constructors:
    CsvCoordinateColumn() : CsvIntensityColumn(), m_units(AxesUnits::NBINS) {}

    CsvCoordinateColumn(CsvCoordinateColumn& toCopy)
        : CsvIntensityColumn(toCopy), m_units(toCopy.units())
    {
    }

    CsvCoordinateColumn(int colNum, double multiplier,
                        csv::DataColumn values, AxesUnits units)

        : CsvIntensityColumn(colNum, multiplier, values), m_units(units)
    {
    }
    // Getters:
    AxesUnits units() const { return m_units; }
    QString name() const { return m_name; }
    // Setters:
    void setUnits(AxesUnits const units) { m_units = units; }
    void setName(QString const name) { m_name = name; }
    void resetColumn(int colNum = -1, double multiplier = 1.,
                     csv::DataColumn values = {}, AxesUnits units = AxesUnits::NBINS, QString name = ""){
        CsvIntensityColumn::resetColumn(colNum,multiplier,values);
        m_units = units;
        m_name = name;
    }
    CsvCoordinateColumn& operator =(const CsvCoordinateColumn colToRep){
        m_units = colToRep.units();
        m_name = colToRep.name();
        return *this;
    }


private:
    AxesUnits m_units;
    QString m_name;
};

#endif // CSVDATACOLUMN_H
