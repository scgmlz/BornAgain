#ifndef CSVIMPORTTABLE_H
#define CSVIMPORTTABLE_H

#include "CsvDataColumn.h"
#include "CsvNamespace.h"
#include "IUnitConverter.h"
#include <QMenu>
#include <QStringList>
#include <QTableWidget>

class CsvImportTable : public QTableWidget
{
    Q_OBJECT
public:
    CsvImportTable(QWidget* parent = nullptr);

    int selectedRow() const;
    int selectedColumn() const;
    int intensityColumn() const { return m_intensityCol->columnNumber(); }
    int coordinateColumn() const { return m_coordinateCol->columnNumber(); }
    double intensityMultiplier() const { return m_intensityCol->multiplier(); }
    double coordinateMultiplier() const { return m_coordinateCol->multiplier(); }
    QString coordinateName() const {return m_coordinateCol->name();}

    void setData(const csv::DataArray data);
    void updateSelection();
    void applyMultipliers();
    void setColumnAs(int col, csv::ColumnType CoordOrInt, double multiplier = 1.0);
    void setFirstRow(size_t row);
    void setLastRow(size_t row);
    void setCoordinateName(const QString coordName){m_coordinateCol->setName(coordName); setHeaders();}

public slots:
    // void setFirstRowSlot();
    // void setLastRowSlot();
    // void setColumnSlot(csv::ColumnType);
    // void resetTableSlot();

private:
    void greyoutDataToDiscard();
    void greyoutCell(int i, int j, bool yes);
    bool needsGreyout(const int iRow, const int jCol) const;
    void multiplyColumn(int col, double multiplier);
    void restoreColumnValues(int col, csv::DataColumn colvals);
    csv::DataColumn valuesFromColumn(int col);
    void setHeaders();

    CsvIntensityColumn* m_intensityCol;
    CsvCoordinateColumn* m_coordinateCol;
    size_t m_firstRow;
    size_t m_lastRow;
};

#endif // CSVIMPORTTABLE_H
