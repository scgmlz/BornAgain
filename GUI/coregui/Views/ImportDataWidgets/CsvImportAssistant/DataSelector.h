// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/DataSelector.h
//! @brief     Defines class DataSelector
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATASELECTOR_H
#define DATASELECTOR_H

#include "CsvDataColumn.h"
#include "CsvImportAssistant.h"
#include "ImportDataInfo.h"
#include "WinDllMacros.h"
#include <QAction>
#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTableWidget>
#include <memory>

class QBoxLayout;

//! Dialog to hold DataSelector.
class DataSelector : public QDialog
{
    Q_OBJECT
public:
    DataSelector(csv::DataArray csvArray, QWidget* parent = nullptr);
    unsigned firstLine() const;
    unsigned lastLine() const;
    unsigned intensityColumn() const { return m_intensityCol; }
    unsigned coordinateColumn() const { return m_coordinateCol; }
    double intensityMultiplier() const { return m_intensityMultiplier; }
    double coordinateMultiplier() const { return m_coordinateMultiplier; }
    AxesUnits units() const;
    csv::ColumnType currentColumnType() const;
    void setDataArray(csv::DataArray csvArray)
    {
        m_data = csvArray;
        updateData();
        resetSelection();
    }
    void setSeparator(char newSeparator)
    {
        m_separatorField->setText(QString(QChar(newSeparator)));
    }

public slots:
    void onImportButton();
    void onCancelButton();
    void onColumnRightClick(const QPoint &position );
    void setColumnSlot(csv::ColumnType ct);

signals:
    void separatorChanged(char newSeparator);

private:
    unsigned maxLines() const;
    char separator() const;
    void setHeaders();
    void setColumnAs(csv::ColumnType coordOrInt);
    void setColumnAs(int col, csv::ColumnType coordOrInt);
    void setFirstRow();
    void setLastRow();
    void resetSelection();
    void updateSelection();
    bool updateData();
    QBoxLayout* createLayout();
    void setTableData();
    double currentMultiplier() const;
    void applyMultipliers();
    void multiplyColumn(size_t col, double multiplier);
    void populateUnitsComboBox(csv::ColumnType coordinate);
    void greyoutTableRegions();
    bool isInsideTable(QPoint point);
    bool dataLooksGood();
    bool needsGreyout(int iRow, int jCol);
    void greyoutCell(int i, int j, bool yes);
    void startContextMenu(const QPoint point);
    void populateContextMenu(QMenu &menu);

    csv::DataArray m_data;
    unsigned m_intensityCol;
    unsigned m_coordinateCol;
    double m_intensityMultiplier;
    double m_coordinateMultiplier;
    QString m_coordinateName;
    QTableWidget* m_tableWidget;
    QLineEdit* m_separatorField;
    QSpinBox* m_firstDataRowSpinBox;
    QSpinBox* m_lastDataRowSpinBox;

    QSpinBox* m_columnNumberSpinBox;
    QComboBox* m_columnTypeComboBox;
    QComboBox* m_coordinateUnitsComboBox;
    QLineEdit* m_multiplierField;

    QPushButton* m_importButton;
    QPushButton* m_cancelButton;
};
#endif // DATASELECTOR_H
