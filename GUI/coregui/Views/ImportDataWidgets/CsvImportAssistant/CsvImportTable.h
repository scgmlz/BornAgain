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
#include "ScientificSpinBox.h"
#include <QMenu>
#include <QStringList>
#include <QTableWidget>
#include <set>

class CsvImportTable : public QTableWidget
{
    Q_OBJECT
public:
    CsvImportTable(QWidget* parent = nullptr);

    int selectedRow() const;
    std::set<int> selectedRows() const;
    int selectedColumn() const;
    int intensityColumn() const { return m_intensityCol->columnNumber(); }
    int coordinateColumn() const { return m_coordinateCol->columnNumber(); }
    int firstRow() { return int(m_firstRow) + rowOffset(); }
    int lastRow() { return int(m_lastRow) + rowOffset(); }
    double intensityMultiplier() const { return m_intensityCol->multiplier(); }
    double coordinateMultiplier() const { return m_coordinateCol->multiplier(); }
    std::set<int> rowsToDiscard() const { return m_rowsToDiscard; }
    csv::ColumnType coordinateName() const { return m_coordinateCol->name(); }
    AxesUnits coordinateUnits() const { return m_coordinateCol->units(); }
    bool dataLooksGood() const { return m_dataLooksGood; }

    void setData(const csv::DataArray data);
    void updateSelection();
    void applyMultipliers();
    void setColumnAs(int col, csv::ColumnType CoordOrInt, double multiplier = 1.0);
    void setFirstRow(size_t row);
    void setLastRow(size_t row);
    void discardRows(std::set<int> rows);
    void setCoordinateName(const csv::ColumnType coordName)
    {
        m_coordinateCol->setName(coordName);
        setHeaders();
    }
    void setMultiplierFields();

signals:
    void dataSanityChanged();

private:
    bool isRowDiscarded(const int row) const ;
    void runSanityChecks();
    bool runIntensitySanityChecks();
    bool runCoordinateSanityChecks();
    void greyoutDataToDiscard();
    void greyoutCell(int i, int j, bool yes, Qt::GlobalColor color = Qt::white);
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
    std::set<int> m_rowsToDiscard;
    bool m_dataLooksGood;
};

class CsvMultiplierField : public ScientificSpinBox
{
    Q_OBJECT
public:
    CsvMultiplierField(double multiplier = 1.0, bool enabled = false, QWidget* parent = nullptr)
        : ScientificSpinBox(parent)
    {
        if (enabled) {
            setMaximum(1e10);
            setMinimum(1e-10);
            setDecimals(10);
            setValue(multiplier);
        } else {
            setMaximum(1);
            setMinimum(1);
            setDecimals(1);
            setValue(multiplier);
        }
        setEnabled(enabled);
    }
};

#endif // CSVIMPORTTABLE_H
