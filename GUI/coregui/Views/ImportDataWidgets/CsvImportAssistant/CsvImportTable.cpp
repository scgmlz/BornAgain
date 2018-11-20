#include "CsvImportTable.h"
#include "QDoubleSpinBox"

CsvImportTable::CsvImportTable(QWidget* parent) : QTableWidget(parent)
{
    m_coordinateCol = new CsvCoordinateColumn();
    m_intensityCol = new CsvIntensityColumn();
    m_firstRow = 0;
    m_lastRow = 0;
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
        int coordCol = int(m_coordinateCol->columnNumber());
        this->setHorizontalHeaderItem(coordCol, new QTableWidgetItem(m_coordinateCol->name()));
    }
}

void CsvImportTable::setMultiplierFields()
{
    auto ncols = this->columnCount();
    auto intCol = m_intensityCol->columnNumber();
    auto intMult = m_intensityCol->multiplier();
    auto coordCol = m_coordinateCol->columnNumber();
    auto coordMult = m_coordinateCol->multiplier();

    for (auto n = 0; n < ncols; ++n) {
        // QWidget *multiplierField =
        QDoubleSpinBox* currentField = new QDoubleSpinBox();
        currentField->setValue(1.0);
        currentField->setDisabled(true);

        if (n == intCol) {
            currentField->setValue(intMult);
            currentField->setEnabled(true);
            connect(currentField, &QDoubleSpinBox::editingFinished, this, [this, currentField]() {
                m_intensityCol->setMultiplier(currentField->value());
                applyMultipliers();
                greyoutDataToDiscard();
            });
        }

        if (n == coordCol) {
            currentField->setValue(coordMult);
            currentField->setEnabled(true);
            connect(currentField, &QDoubleSpinBox::editingFinished, this, [this, currentField]() {
                m_coordinateCol->setMultiplier(currentField->value());
                applyMultipliers();
                greyoutDataToDiscard();
            });
        }

        this->setCellWidget(0, n, currentField);
    }

    int nRows = this->rowCount();

    QStringList vhlabels;
    vhlabels << "Multiplier: ";
    for (int i = rowOffset(); i < nRows; i++)
        vhlabels << QString::number(i);

    this->setVerticalHeaderLabels(vhlabels);
    applyMultipliers();
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
    m_firstRow = row;
    greyoutDataToDiscard();
}

void CsvImportTable::setLastRow(size_t row)
{
    m_lastRow = row;
    greyoutDataToDiscard();
}

void CsvImportTable::updateSelection()
{
    setHeaders();
    setMultiplierFields();
    greyoutDataToDiscard();
}

void CsvImportTable::restoreColumnValues(int col, csv::DataColumn colvals)
{
    for (size_t i = size_t(rowOffset()); i < colvals.size(); i++) {
        QString cellText = QString::fromStdString(colvals[i]);
        this->setItem(int(i), int(col), new QTableWidgetItem(cellText));
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

void CsvImportTable::greyoutCell(int i, int j, bool yes)
{
    if (yes) {
        QFont italicFont;
        italicFont.setItalic(true);
        italicFont.setStrikeOut(true);
        this->item(i, j)->setBackground(Qt::gray);
        this->item(i, j)->setFont(italicFont);
    } else {
        QFont standardFont;
        standardFont.setItalic(false);
        standardFont.setStrikeOut(false);
        this->item(i, j)->setBackground(Qt::white);
        this->item(i, j)->setFont(standardFont);
    }
}

bool CsvImportTable::needsGreyout(const int iRow, const int jCol) const
{
    bool greyTop = iRow < int(m_firstRow) + rowOffset();
    bool greyBott = iRow > int(m_lastRow) + rowOffset();
    bool greyCol = jCol != int(m_coordinateCol->columnNumber())
                   && jCol != int(m_intensityCol->columnNumber())
                   && int(m_intensityCol->columnNumber()) > 0;

    return greyTop || greyBott || greyCol;
}

void CsvImportTable::applyMultipliers()
{
    if (m_intensityCol->columnNumber() > -1) {
        multiplyColumn(m_intensityCol);
    }

    if (m_coordinateCol->columnNumber() > -1) {
        multiplyColumn(m_coordinateCol);
    }
}

void CsvImportTable::multiplyColumn(CsvIntensityColumn* col)
{
    auto colNum = col->columnNumber();
    if (colNum < 0)
        return;

    auto multiplier = col->multiplier();
    auto values = col->values();
    auto size = col->values().size();
    for (size_t i = 0; i < size; i++) {
        auto currentText = QString::fromStdString(values[i]);
        double number = multiplier * csv::atof(currentText);
        QString cellText = 0.0 == number ? currentText : QString::number(number);
        this->setItem(int(i), colNum, new QTableWidgetItem(cellText));
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
        m_coordinateCol->setName(csv::HeaderLabels[coordOrInt]);
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
        size_t rowCount = size_t(this->rowCount());
        result = csv::DataColumn(rowCount);
        for (size_t i = size_t(rowOffset()); i < rowCount; ++i) {
            auto currentText = this->item(int(i), int(col))->text();
            result[i] = currentText.toStdString();
        }
        return result;
    }
}
