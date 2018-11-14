#ifndef CSVIMPORTTABLE_H
#define CSVIMPORTTABLE_H

#include "IUnitConverter.h"
#include "CsvNamespace.h"
#include <QStringList>
#include <QMenu>
#include <QTableWidget>

class CsvImportTable: public QTableWidget
{
    Q_OBJECT
public:
    CsvImportTable(QWidget* parent = nullptr);

public slots:
    //void setFirstRowSlot();
    //void setLastRowSlot();
    //void setColumnSlot(csv::ColumnType);
    //void resetTableSlot();

private:


};

#endif // CSVIMPORTTABLE_H
