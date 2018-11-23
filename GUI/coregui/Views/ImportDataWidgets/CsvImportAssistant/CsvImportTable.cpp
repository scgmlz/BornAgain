// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportTable.cpp
//! @brief     Implements class CsvImportTable
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvImportTable.h"

CsvImportTable::CsvImportTable(QWidget* parent) : QTableWidget(parent)
{
    m_coordinateCol = std::make_unique<CsvCoordinateColumn>();
    m_intensityCol = std::make_unique<CsvCoordinateColumn>();
    m_firstRow = 0;
    m_lastRow = 0;
    m_dataLooksGood = false;
}

int CsvImportTable::selectedRow() const
{
    auto selectedRanges = this->selectedRanges();
    if (selectedRanges.empty())
        return -1;
    auto front = selectedRanges.front();
    auto row = front.topRow();
    return row - rowOffset();
}

std::set<int> CsvImportTable::selectedRows() const
{
    std::set<int> accumulator;

    auto selection = selectedRanges();
    if (selection.empty())
        return {};

    int size = selection.size();
    for (int rangenumber = 0; rangenumber < size; ++rangenumber) {
        int row0 = selectedRanges()[rangenumber].topRow() - rowOffset();
        int rowN = selectedRanges()[rangenumber].bottomRow() - rowOffset();
        for (int r = row0; r <= rowN; ++r) {
            accumulator.insert(r);
        }
    }
    return accumulator;
}

int CsvImportTable::selectedColumn() const
{
    auto selectedRanges = this->selectedRanges();
    if (selectedRanges.empty())
        return -1;
    auto front = selectedRanges.front();
    auto col = front.leftColumn();
    return col;
}

void CsvImportTable::setHeaders()
{
    // Reset header labels
    QStringList headers;

    for (int j = 0; j < this->columnCount(); j++)
        headers.append(QString::number(j + 1));

    this->setHorizontalHeaderLabels(headers);

    if (m_intensityCol->columnNumber() > -1) {
        int intCol = int(m_intensityCol->columnNumber());
        this->setHorizontalHeaderItem(intCol,
                                      new QTableWidgetItem(csv::HeaderLabels[csv::_intensity_]));
    }
    if (m_coordinateCol->columnNumber() > -1) {
        QString label = csv::HeaderLabels[m_coordinateCol->name()];
        int coordCol = int(m_coordinateCol->columnNumber());
        this->setHorizontalHeaderItem(coordCol, new QTableWidgetItem(label));
    }
}

void CsvImportTable::setMultiplierFields()
{
    auto ncols = this->columnCount();
    auto intCol = m_intensityCol->columnNumber();
    auto intMult = m_intensityCol->multiplier();
    auto coordCol = m_coordinateCol->columnNumber();
    auto coordMult = m_coordinateCol->multiplier();

    for (int n = 0; n < ncols; ++n) {
        CsvMultiplierField* currentField;
        if (n == intCol) {
            currentField = new CsvMultiplierField(intMult, true);
            connect(currentField, &CsvMultiplierField::editingFinished, this,
                    [this, currentField]() {
                        m_intensityCol->setMultiplier(currentField->value());
                        updateSelection();
                    });
        } else if (n == coordCol) {
            currentField = new CsvMultiplierField(coordMult, true);
            connect(currentField, &CsvMultiplierField::editingFinished, this,
                    [this, currentField]() {
                        m_coordinateCol->setMultiplier(currentField->value());
                        updateSelection();
                    });
        } else {
            currentField = new CsvMultiplierField();
        }
        this->setCellWidget(0, n, currentField);
    }

    int nRows = this->rowCount();

    QStringList vhlabels;
    vhlabels << "Multiplier: ";
    for (int i = rowOffset(); i < nRows; i++)
        vhlabels << QString::number(i);

    this->setVerticalHeaderLabels(vhlabels);
}

void CsvImportTable::setData(const csv::DataArray data)
{
    if (data.empty()) {
        this->clearContents();
        this->setRowCount(0);
        return;
    }

    size_t nRows = data.size();
    size_t nCols = data[0].size();
    this->clearContents();
    this->setColumnCount(int(nCols));
    this->setRowCount(0);

    this->insertRow(this->rowCount());

    for (size_t i = 0; i < nRows; i++) {
        this->insertRow(this->rowCount());
        size_t I = size_t(this->rowCount()) - 1;
        for (size_t j = 0; j < data[i].size(); j++) {
            this->setItem(int(I), int(j), new QTableWidgetItem(QString::fromStdString(data[i][j])));
        }
    }

    setMultiplierFields();
}

void CsvImportTable::setFirstRow(size_t row)
{
    if (row != m_firstRow) {
        m_firstRow = row;
        updateSelection();
    }
}

void CsvImportTable::setLastRow(size_t row)
{
    if (m_lastRow != row) {
        m_lastRow = row;
        updateSelection();
    }
}

void CsvImportTable::discardRows(std::set<int> rows)
{
    if (rows.empty()) {
        m_rowsToDiscard.clear();
    } else {
        for (auto row : rows) {
            if (isRowDiscarded(row)) {
                m_rowsToDiscard.erase(row);
            } else {
                m_rowsToDiscard.insert(row);
            }
       }
    }
    updateSelection();
}

void CsvImportTable::updateSelection()
{
    setHeaders();
    setMultiplierFields();
    applyMultipliers();
    greyoutDataToDiscard();
    runSanityChecks();
}

void CsvImportTable::restoreColumnValues(int col, csv::DataColumn colvals)
{
    for (size_t i = 0; i < colvals.size(); i++) {
        QString originalText = QString::fromStdString(colvals[i]);
        setItem(int(i) + rowOffset(), int(col), new QTableWidgetItem(originalText));
    }
}

void CsvImportTable::greyoutDataToDiscard()
{
    int nRows = this->rowCount();
    int nCols = this->columnCount();

    // Grey out columns
    for (int i = rowOffset(); i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            greyoutCell(i, j, needsGreyout(i, j));
}

void CsvImportTable::runSanityChecks()
{
    bool dataLooksGood = true;
    int jCol = m_coordinateCol->columnNumber();
    csv::DataRow values = m_coordinateCol->values();
    size_t size = m_coordinateCol->values().size();
    double greatestNumber = 0;
    for (int i = 0; i < int(size) - 1; i++) {
        bool userDiscard = isRowDiscarded(i);
        if (i < firstRow() - rowOffset() || i > lastRow() || userDiscard)
            continue;

        size_t I = size_t(i);
        auto cellText = QString::fromStdString(values[I]);
        auto nextCellText = QString::fromStdString(values[I + 1]);
        double number = cellText.toDouble();

        double nextNumber = nextCellText.toDouble();
        greatestNumber = std::max(number, greatestNumber);

        // if two consecutive values are non-increasing:
        if (number - greatestNumber < 0) {
            bool alreadyDiscarded = needsGreyout(i + rowOffset(), jCol);
            greyoutCell(i + rowOffset(), jCol, alreadyDiscarded, Qt::red);
            if (!alreadyDiscarded)
                dataLooksGood = false;
        }

        if (nextNumber - number < 1e-14) {
            bool alreadyDiscarded = needsGreyout(i + 1 + rowOffset(), jCol);
            greyoutCell(i + 1 + rowOffset(), jCol, alreadyDiscarded, Qt::red);
            if (!alreadyDiscarded)
                dataLooksGood = false;
        }
    }

    if (dataLooksGood != m_dataLooksGood) {
        m_dataLooksGood = dataLooksGood;
        emit dataSanityChanged();
    }
}

void CsvImportTable::greyoutCell(int i, int j, bool yes, Qt::GlobalColor color)
{
    if (yes) {
        QFont italicFont;
        italicFont.setItalic(true);
        italicFont.setStrikeOut(true);
        item(i, j)->setBackground(Qt::gray);
        item(i, j)->setFont(italicFont);
    } else {
        QFont standardFont;
        standardFont.setItalic(false);
        standardFont.setStrikeOut(false);
        item(i, j)->setBackground(color);
        item(i, j)->setFont(standardFont);
    }
}

bool CsvImportTable::needsGreyout(const int iRow, const int jCol) const
{
    int vecRow = iRow - rowOffset();
    bool userDiscard = isRowDiscarded(vecRow);
    bool greyTop = vecRow < int(m_firstRow);
    bool greyBott = vecRow > int(m_lastRow);
    bool greyCol = jCol != int(m_coordinateCol->columnNumber())
                   && jCol != int(m_intensityCol->columnNumber())
                   && int(m_intensityCol->columnNumber()) > 0;

    return greyTop || greyBott || greyCol || userDiscard;
}

void CsvImportTable::applyMultipliers()
{
    if (m_intensityCol->columnNumber() > -1) {
        multiplyColumn(*m_intensityCol);
    }

    if (m_coordinateCol->columnNumber() > -1) {
        multiplyColumn(*m_coordinateCol);
    }
}

void CsvImportTable::multiplyColumn(const CsvIntensityColumn& col)
{
    auto colNum = col.columnNumber();
    if (colNum < 0)
        return;

    double multiplier = col.multiplier();
    csv::DataColumn values = col.values();
    size_t size = col.values().size();
    int idx0 = rowOffset();
    for (size_t i = 0; i < size; i++) {
        auto currentText = QString::fromStdString(values[i]);
        double number = multiplier * currentText.toDouble();
        QString textToWrite = 0.0 == number ? currentText : QString::number(number);
        this->setItem(int(i) + idx0, colNum, new QTableWidgetItem(textToWrite));
    }
}

void CsvImportTable::setColumnAs(int col, csv::ColumnType coordOrInt, double multiplier)
{
    csv::DataColumn buffer = valuesFromColumn(col);
    if (coordOrInt == csv::_intensity_) {
        restoreColumnValues(m_intensityCol->columnNumber(), m_intensityCol->values());
        m_intensityCol->setColNum(col);
        m_intensityCol->setMultiplier(multiplier);
        m_intensityCol->setValues(buffer);
        if (col == m_coordinateCol->columnNumber())
            m_coordinateCol->resetColumn();
    } else {
        restoreColumnValues(m_coordinateCol->columnNumber(), m_coordinateCol->values());
        m_coordinateCol->setColNum(col);
        m_coordinateCol->setMultiplier(multiplier);
        m_coordinateCol->setValues(buffer);
        m_coordinateCol->setName(coordOrInt);
        if (col == m_intensityCol->columnNumber())
            m_intensityCol->resetColumn();
    }
    updateSelection();
}

csv::DataColumn CsvImportTable::valuesFromColumn(int col)
{
    if (col < 0) {
        return {};
    } else if (m_intensityCol->columnNumber() == col) {
        return m_intensityCol->values();
    } else if (m_coordinateCol->columnNumber() == col) {
        return m_coordinateCol->values();
    } else {
        csv::DataColumn result;
        size_t rowCount = size_t(this->rowCount() - rowOffset());
        result = csv::DataColumn(rowCount);
        int idx0 = rowOffset();
        for (size_t i = 0; i < rowCount; ++i) {
            int I = int(i) + idx0;
            auto currentText = this->item(I, int(col))->text();
            result[i] = currentText.toStdString();
        }
        return result;
    }
}

bool CsvImportTable::isRowDiscarded(const int row) const
{
    return std::find(m_rowsToDiscard.begin(), m_rowsToDiscard.end(), row) != m_rowsToDiscard.end();
}
