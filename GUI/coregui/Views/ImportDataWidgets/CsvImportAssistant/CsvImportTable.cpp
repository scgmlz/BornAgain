#include "CsvImportTable.h"

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
    return row;
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

    for (size_t i = 0; i < nRows; i++) {
        this->insertRow(this->rowCount());
        size_t I = size_t(this->rowCount()) - 1;
        for (size_t j = 0; j < data[i].size(); j++) {
            this->setItem(int(I), int(j),
                                   new QTableWidgetItem(QString::fromStdString(data[i][j])));
        }
    }
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
    applyMultipliers();
    greyoutDataToDiscard();
    setHeaders();
}

void CsvImportTable::restoreColumnValues(int col, csv::DataColumn colvals)
{
    for (size_t i = 0; i < colvals.size(); i++) {
        QString cellText = QString::fromStdString(colvals[i]);
        this->setItem(int(i), int(col), new QTableWidgetItem(cellText));
    }
}

void CsvImportTable::greyoutDataToDiscard()
{
    int nRows = this->rowCount();
    int nCols = this->columnCount();

    // Grey out columns
    for (int i = 0; i < nRows; i++)
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
    bool greyTop = iRow < int(m_firstRow);
    bool greyBott = iRow > int(m_lastRow);
    bool greyCol =
        jCol != int(m_coordinateCol->columnNumber()) && jCol != int(m_intensityCol->columnNumber()) && int(m_intensityCol->columnNumber()) > 0;

    return greyTop || greyBott || greyCol;
}

void CsvImportTable::applyMultipliers()
{
    if (m_intensityCol->columnNumber() > -1) {
        multiplyColumn(m_intensityCol->columnNumber(), m_intensityCol->multiplier());
    }

    if (m_coordinateCol->columnNumber() > -1) {
        multiplyColumn(m_coordinateCol->columnNumber(), m_coordinateCol->multiplier());
    }
}

void CsvImportTable::multiplyColumn(int col, double multiplier)
{
    if(col < 0)
        return;

    for (size_t i = 0; i < size_t(this->rowCount()); i++) {
        auto currentText = this->item(int(i), int(col))->text();
        double number = multiplier * csv::atof(currentText);
        QString cellText =
            0.0 == number ? currentText : QString::number(number);
        this->setItem(int(i), int(col), new QTableWidgetItem(cellText));
    }
}

void CsvImportTable::setColumnAs(int col, csv::ColumnType coordOrInt, double multiplier){
    csv::DataColumn buffer = valuesFromColumn(col);
    if(coordOrInt == csv::_intensity_){
        restoreColumnValues(m_intensityCol->columnNumber(),m_intensityCol->values());
        m_intensityCol->setColNum(col);
        m_intensityCol->setMultiplier(multiplier);
        m_intensityCol->setValues(buffer);
    }
    else{
        restoreColumnValues(m_coordinateCol->columnNumber(),m_coordinateCol->values());
        m_coordinateCol->setColNum(col);
        m_coordinateCol->setMultiplier(multiplier);
        m_coordinateCol->setValues(buffer);
        m_coordinateCol->setName(csv::HeaderLabels[coordOrInt]);
    }
    updateSelection();
}

csv::DataColumn CsvImportTable::valuesFromColumn(int col){
    if(col < 0){
        return {};
    }
    else{
        csv::DataColumn result;
        size_t rowCount = size_t(this->rowCount());
        result = csv::DataColumn(rowCount);
        for (size_t i = 0; i < rowCount; ++i) {
            auto currentText = this->item(int(i), int(col))->text();
            result[i] = currentText.toStdString();
        }
        return result;
    }
}
