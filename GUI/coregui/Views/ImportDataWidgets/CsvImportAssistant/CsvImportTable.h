// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportTable.h
//! @brief     Defines class CsvImportTable
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVIMPORTTABLE_H
#define CSVIMPORTTABLE_H

#include "CsvDataColumn.h"
#include "CsvNamespace.h"
#include "IUnitConverter.h"
#include <QDoubleSpinBox>
#include <QMenu>
#include <QStringList>
#include <QTableWidget>

class CsvImportTable : public QTableWidget
{
    Q_OBJECT
public:
    CsvImportTable(QWidget* parent = nullptr);

    int selectedRow() const;
    std::vector<int> selectedRows() const;
    int selectedColumn() const;
    int intensityColumn() const { return m_intensityCol->columnNumber(); }
    int coordinateColumn() const { return m_coordinateCol->columnNumber(); }
    int firstRow() { return int(m_firstRow) + rowOffset(); }
    int lastRow() { return int(m_lastRow) + rowOffset(); }
    double intensityMultiplier() const { return m_intensityCol->multiplier(); }
    double coordinateMultiplier() const { return m_coordinateCol->multiplier(); }
    std::vector<int> rowsToDiscard() const { return m_rowsToDiscard;}
    csv::ColumnType coordinateName() const { return m_coordinateCol->name(); }
    AxesUnits coordinateUnits() const { return m_coordinateCol->units(); }

    void setData(const csv::DataArray data);
    void updateSelection();
    void applyMultipliers();
    void setColumnAs(int col, csv::ColumnType CoordOrInt, double multiplier = 1.0);
    void setFirstRow(size_t row);
    void setLastRow(size_t row);
    void discardRows(std::vector<int> rows);
    void setCoordinateName(const csv::ColumnType coordName)
    {
        m_coordinateCol->setName(coordName);
        setHeaders();
    }
    void setMultiplierFields();
    void resetSelection();

private:
    void greyoutDataToDiscard();
    void greyoutCell(int i, int j, bool yes, Qt::GlobalColor color = Qt::white);
    void runSanityChecks();
    bool needsGreyout(const int iRow, const int jCol) const;
    void multiplyColumn(const CsvIntensityColumn& col);
    void restoreColumnValues(int col, csv::DataColumn colvals);
    csv::DataColumn valuesFromColumn(int col);
    void setHeaders();
    int rowOffset() const { return 1; } // this comes from the multipliers in the first row

    std::unique_ptr<CsvIntensityColumn> m_intensityCol;
    std::unique_ptr<CsvCoordinateColumn> m_coordinateCol;
    size_t m_firstRow;
    size_t m_lastRow;
    std::vector<int> m_rowsToDiscard;
};

class CsvMultiplierField : public QDoubleSpinBox
{
    Q_OBJECT
public:
    CsvMultiplierField(double multiplier = 1.0, bool enabled = false, QWidget* parent = nullptr)
            : QDoubleSpinBox(parent)
    {
        if(enabled){
            setMaximum(1e10);
            setMinimum(1e-10);
            setDecimals(10);
            setValue(multiplier);
        }
        else{
            setMaximum(1);
            setMinimum(1);
            setDecimals(1);
            setValue(multiplier);
        }
        setEnabled(enabled);
    }
};

#endif // CSVIMPORTTABLE_H
