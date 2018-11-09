// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/DataSelector.cpp
//! @brief     Implements class DataSelector
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataSelector.h"
#include "ImportDataInfo.h"
#include "mainwindow_constants.h"
#include "StyleUtils.h"
#include <QPushButton>
#include <QTableWidget>
#include <QSettings>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QFormLayout>

namespace
{
const QSize default_dialog_size(300, 400);
}

DataSelector::DataSelector(csv::DataArray csvArray, QWidget* parent):
        QDialog(parent)
      ,m_data(csvArray)
      ,m_intensityCol(0)
      ,m_coordinateCol(0)
      ,m_intensityMultiplier(1.0)
      ,m_coordinateMultiplier(1.0)
      ,m_coordinateName("")
      ,m_tableWidget(nullptr)
      ,m_separatorField(nullptr)
      ,m_firstDataRowSpinBox(nullptr)
      ,m_lastDataRowSpinBox(nullptr)
      ,m_columnNumberSpinBox(nullptr)
      ,m_columnTypeComboBox(nullptr)
      ,m_coordinateUnitsComboBox(nullptr)
      ,m_multiplierField(nullptr)
      ,m_importButton(nullptr)
      ,m_cancelButton(nullptr)
      ,m_setAsTheta(new QAction(HeaderLabels[_theta_],nullptr))
      ,m_setAsQ(new QAction(HeaderLabels[_q_],nullptr))
      ,m_setAsIntensity(new QAction("Set as " + HeaderLabels[_intensity_] + " column",nullptr))
{
    setWindowTitle("Data Importer");
    setMinimumSize(default_dialog_size);
    resize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    StyleUtils::setResizable(this);
    setLayout(createLayout());

    if(!updateData())
        return;
}

bool DataSelector::updateData(){
    size_t lastRow = m_data.size();

    if (lastRow < 1) {
        m_importButton->setDisabled(true);
        CsvImportAssistant::showErrorMessage("There is no data to show");
        return false;
    }

    m_firstDataRowSpinBox->setMaximum(int(lastRow));
    m_lastDataRowSpinBox->setMaximum(int(lastRow));
    m_lastDataRowSpinBox->setValue(int(lastRow));
    m_columnNumberSpinBox->setMaximum(int(m_data[firstLine()].size()));
    setTableData();

    return true;
}

void DataSelector::setTableData(){

    if(m_data.empty()){
        m_tableWidget->clearContents();
        m_tableWidget->setRowCount(0);
        return;
    }

    size_t nRows = m_data.size();
    size_t nCols = m_data[0].size();
    m_tableWidget->clearContents();
    m_tableWidget->setColumnCount(int(nCols));
    m_tableWidget->setRowCount(0);

    for(unsigned i = 0; i < nRows ; i++){
        m_tableWidget->insertRow(m_tableWidget->rowCount());
        unsigned I = unsigned(m_tableWidget->rowCount()) - 1;
        for(unsigned j = 0; j < m_data[i].size(); j++){
            m_tableWidget->setItem(int(I),int(j),new QTableWidgetItem(QString::fromStdString(m_data[i][j])));
        }
    }
}

void DataSelector::applyMultipliers(){
    if(m_intensityCol > 0){
        int col = int(m_intensityCol - 1);
        for(unsigned i = firstLine()-1; i < lastLine() ; i++){
            double number = m_intensityMultiplier * std::atof(m_data[i][col].c_str());
            m_tableWidget->setItem(int(i),int(col),new QTableWidgetItem(QString::number(number)));
        }
    }

    if(m_coordinateCol > 0){
        int col = int(m_coordinateCol - 1);
        for(unsigned i = firstLine()-1; i < lastLine() ; i++){
            double number = m_coordinateMultiplier * std::atof(m_data[i][col].c_str());
            m_tableWidget->setItem(int(i),int(col),new QTableWidgetItem(QString::number(number)));
        }
    }
}

void DataSelector::onColumnRightClick(const QPoint position)
{
    auto item = m_tableWidget->itemAt(position);
    if(!item) return;
    auto row = item->row();
    auto col = item->column();
    if(row*col < 0) return;

    QMenu menu;

    //Action "select from this row"
    QAction selectFromThisRowOn("Set as first data row",nullptr);
    menu.addAction(&selectFromThisRowOn);
    connect(&selectFromThisRowOn,&QAction::triggered,this,[this](){setFirstRow();});

    //Action "select until this row"
    QAction selectUntilThisRow("Set as last data row",nullptr);
    menu.addAction(&selectUntilThisRow);
    connect(&selectUntilThisRow,&QAction::triggered,this,[this](){setLastRow();});

    menu.addSeparator();

    //Set column as "Intensity".
    menu.addAction(m_setAsIntensity);
    connect(m_setAsIntensity,&QAction::triggered,this, [this](){setColumnAs(_intensity_);});

    //Coordinate menu disabled if a coordinate column is already set.
    QMenu *coordMenu = menu.addMenu("Set as coordinate column...");

    //Set column as "Theta".
    coordMenu->addAction(m_setAsTheta);
    connect(m_setAsTheta,&QAction::triggered,this, [this](){setColumnAs(_theta_);});

    //Set column as "q".
    coordMenu->addAction(m_setAsQ);
    connect(m_setAsQ,&QAction::triggered,this, [this](){setColumnAs(_q_);});

    menu.addSeparator();

    //Action "reset"
    QAction resetAction("reset",nullptr);
    menu.addAction(&resetAction);
    connect(&resetAction,&QAction::triggered, this, [this](){resetSelection(); updateSelection();});

    menu.exec(m_tableWidget->mapToGlobal(position));
}

void DataSelector::updateSelection()
{
    m_importButton->setEnabled(false);
    m_coordinateUnitsComboBox->setEnabled(false);
    greyoutTableRegions();

    //Enable import button only if the user has selected its columns for 1d import
    if( m_intensityCol > 0 )
        m_importButton->setEnabled(true);

    //Enable Coordinate Selector
    if( m_coordinateCol > 0 ){
        m_coordinateUnitsComboBox->setEnabled(true);
    }else{
        m_coordinateUnitsComboBox->clear();
        m_coordinateUnitsComboBox->addItem(UnitsLabels[AxesUnits::NBINS]);
    }
    applyMultipliers();


}

void DataSelector::greyoutTableRegions(){
    int nRows = m_tableWidget->rowCount();
    int nCols = m_tableWidget->columnCount();

    //Grey out columns
    for(int i = 0; i < nRows; i++)
        for(int j = 0; j < nCols; j++)
            greyoutCell(i,j,needsGreyout(i,j));
}

void DataSelector::greyoutCell(int i, int j, bool yes){
    if(yes){
        QFont italicFont;
        italicFont.setItalic(true);
        italicFont.setStrikeOut(true);
        m_tableWidget->item(i,j)->setBackground(Qt::gray);
        m_tableWidget->item(i,j)->setFont(italicFont);
    }
    else{
        QFont standardFont;
        standardFont.setItalic(false);
        standardFont.setStrikeOut(false);
        m_tableWidget->item(i,j)->setBackground(Qt::white);
        m_tableWidget->item(i,j)->setFont(standardFont);
    }
}

bool DataSelector::needsGreyout(int iRow, int jCol){

    bool greyTop  = iRow < int(firstLine() - 1);
    bool greyBott = iRow > int(lastLine()  - 1);
    bool greyCol  =  jCol+1 != int(m_coordinateCol) &&
                     jCol+1 != int(m_intensityCol) &&
                     m_intensityCol > 0;

    return greyTop || greyBott || greyCol;
}

void DataSelector::setColumnAs(ColumnType coordOrInt){
    auto selectedRanges = m_tableWidget->selectedRanges();
    if (selectedRanges.empty())
        return;
    auto front = selectedRanges.front();
    auto col = front.leftColumn();
    setColumnAs(col,coordOrInt);
}


void DataSelector::setColumnAs(int col, ColumnType coordOrInt){

    if(coordOrInt == _intensity_) {
        //restore order before changing column:
        m_intensityMultiplier = 1.0;
        m_columnTypeComboBox->setCurrentIndex(coordOrInt);
        m_multiplierField->setText(QString::number(m_intensityMultiplier));
        m_intensityMultiplier = currentMultiplier();
        applyMultipliers();

        //ok, change column:
        m_intensityCol = unsigned(col + 1);
        m_columnNumberSpinBox->setValue(int(m_intensityCol));
        if (m_coordinateCol == m_intensityCol) {
            m_coordinateCol = 0;
            populateUnitsComboBox(coordOrInt);
        }
    }
    else{
        //restore order before changing column:
        m_coordinateMultiplier = 1.0;
        m_columnTypeComboBox->setCurrentIndex(coordOrInt);
        m_multiplierField->setText(QString::number(m_coordinateMultiplier));
        m_coordinateMultiplier = currentMultiplier();
        applyMultipliers();

        //ok, change column:
        m_coordinateCol = unsigned(col+1);
        m_columnNumberSpinBox->setValue(int(m_coordinateCol));
        m_coordinateName = HeaderLabels[coordOrInt];
        populateUnitsComboBox(coordOrInt);
        if(m_coordinateCol == m_intensityCol){
            m_intensityCol=0;
        }
    }
    updateSelection();
    setHeaders();
}

void DataSelector::populateUnitsComboBox(int coord){
    m_coordinateUnitsComboBox->clear();
    switch(coord){

    case _theta_:
        m_coordinateUnitsComboBox->addItem(UnitsLabels[AxesUnits::DEGREES]);
        m_coordinateUnitsComboBox->addItem(UnitsLabels[AxesUnits::RADIANS]);
        break;

    case _q_:
        m_coordinateUnitsComboBox->addItem(UnitsLabels[AxesUnits::QSPACE]);
        break;

    default:
        m_coordinateUnitsComboBox->addItem(UnitsLabels[AxesUnits::NBINS]);
        break;
    }
}



void DataSelector::setFirstRow(){
    //get selected column
    auto selectedRanges = m_tableWidget->selectedRanges();
    if (selectedRanges.empty())
        return;
    auto front = selectedRanges.front();
    auto row = front.topRow();
    auto currentMax = m_firstDataRowSpinBox->maximum();
    auto desiredVal = row+1;
    auto newMax = std::max(currentMax,desiredVal);
    m_firstDataRowSpinBox->setMaximum(newMax);
    m_firstDataRowSpinBox->setValue(desiredVal);
}

void DataSelector::setLastRow(){
    //get selected column
    auto selectedRanges = m_tableWidget->selectedRanges();
    if (selectedRanges.empty())
        return;
    auto front = selectedRanges.front();
    auto row = front.topRow();
    auto currentMin = m_firstDataRowSpinBox->minimum();
    auto desiredVal = row+1;
    auto newMin = std::min(currentMin,desiredVal);
    m_lastDataRowSpinBox->setMinimum(newMin);
    m_lastDataRowSpinBox->setValue(desiredVal);
}

void DataSelector::resetSelection(){
    m_intensityCol = 0;
    m_coordinateCol = 0;
    m_coordinateName = "";
    m_firstDataRowSpinBox->setValue(0);
    m_lastDataRowSpinBox->setValue(int(maxLines()));
    setHeaders();
    m_coordinateUnitsComboBox->clear();
    m_coordinateUnitsComboBox->addItem(UnitsLabels[AxesUnits::NBINS]);
}

void DataSelector::setHeaders(){
    //Reset header labels
    QStringList headers;

    for(int j = 0; j < m_tableWidget->columnCount(); j++)
        headers.append(QString::number(j + 1));

    m_tableWidget->setHorizontalHeaderLabels(headers);

    if(m_intensityCol > 0){
        int intCol = int(m_intensityCol) - 1;
        m_tableWidget->setHorizontalHeaderItem(intCol , new QTableWidgetItem( HeaderLabels[_intensity_]) );
    }
    if(m_coordinateCol > 0){
        int coordCol = int(m_coordinateCol) - 1;
        m_tableWidget->setHorizontalHeaderItem(coordCol , new QTableWidgetItem( m_coordinateName ));
    }
}

unsigned DataSelector::firstLine() const{
    return unsigned(m_firstDataRowSpinBox->value());
}

unsigned DataSelector::lastLine() const{
    return unsigned(m_lastDataRowSpinBox->value());
}

unsigned DataSelector::maxLines() const{
    return unsigned(m_lastDataRowSpinBox->maximum());
}

AxesUnits DataSelector::units() const{
    AxesUnits defaultUnits = AxesUnits::NBINS;
    for(auto i = 0; i < UnitsLabels.size(); i++)
        if(m_coordinateUnitsComboBox->currentText() == UnitsLabels[i])
            return AxesUnits(i);
    return defaultUnits;
}

ColumnType DataSelector::currentColumnType() const{
    ColumnType defaultColumnType = ColumnType::_intensity_;
    for(auto i = 0; i < HeaderLabels.size(); i++)
        if(m_columnTypeComboBox->currentText() == HeaderLabels[i])
            return ColumnType(i);
    return defaultColumnType;
}

double DataSelector::currentMultiplier() const{
    return std::atof(m_multiplierField->text().toStdString().c_str());
}

char DataSelector::separator() const{
    char separator;
    QString tmpstr = m_separatorField->text();
    if(tmpstr.size() < 1){
        separator = '\0';
    }
    else{
        separator = tmpstr.at(0).toLatin1();
    }
    return separator;
}

void DataSelector::onCancelButton()
{
    reject();
}

void DataSelector::onImportButton()
{
    if(dataLooksGood()){
        accept();
    }
}

bool DataSelector::dataLooksGood(){
    int iCol = int(m_intensityCol)-1;
    int cCol = int(m_coordinateCol)-1;
    try{
        for(int i = int(firstLine()) - 1; i < int(lastLine()); i++){
            CsvImportAssistant::stringToDouble(
                                    m_tableWidget->item(i,iCol)->text().toStdString()
                                    );
        }
        if(m_coordinateCol > 0)
            for(int i = int(firstLine()) - 1; i < int(lastLine()); i++){
                CsvImportAssistant::stringToDouble(
                                        m_tableWidget->item(i,cCol)->text().toStdString()
                                        );
            }
    } catch(std::exception& e){
        QString message = QString("Unable to import, the following exception was thrown:\n") + QString::fromStdString(e.what());
        QMessageBox::warning(nullptr, "Wrong data format", message);
        return false;
    }
    return true;
}

QBoxLayout* DataSelector::createLayout()
{
    //table Widget
    m_tableWidget = new QTableWidget();
    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &DataSelector::onColumnRightClick);

    //Import button
    m_importButton = new QPushButton("Import");
    m_importButton->setDefault(true);
    connect(m_importButton, &QPushButton::clicked, this, &DataSelector::onImportButton);

    //Reject button
    m_cancelButton = new QPushButton("Cancel");
    connect(m_cancelButton, &QPushButton::clicked, this, [this](){reject();});

    //Separator field -- This needs to communicate with importAssistant
    m_separatorField = new QLineEdit(QString(""));
    m_separatorField->setMaxLength(1);
    m_separatorField->setMaximumWidth(100);
    connect(m_separatorField, &QLineEdit::editingFinished, this,
            [this]()
            {
                emit separatorChanged(separator());
            }
    );

    //First Row SpinBox
    m_firstDataRowSpinBox = new QSpinBox();
    m_firstDataRowSpinBox->setMinimum(1);
    m_firstDataRowSpinBox->setMaximum(1);
    m_firstDataRowSpinBox->setValue(1);
    m_firstDataRowSpinBox->setMaximumWidth(100);
    connect(m_firstDataRowSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
            [this]()
            {
                m_lastDataRowSpinBox->setMinimum(m_firstDataRowSpinBox->value());
                updateSelection();
            }
    );

    //Last Row SpinBox
    m_lastDataRowSpinBox = new QSpinBox();
    m_lastDataRowSpinBox->setMinimum(1);
    m_lastDataRowSpinBox->setMaximum(1);
    m_lastDataRowSpinBox->setValue(1);
    m_lastDataRowSpinBox->setMaximumWidth(100);
    connect(m_lastDataRowSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
            [this]()
            {
                m_firstDataRowSpinBox->setMaximum(m_lastDataRowSpinBox->value());
                updateSelection();
            }
    );

    //Coordinate units selector:
    m_coordinateUnitsComboBox = new QComboBox();
    m_coordinateUnitsComboBox->setMaximumWidth(100);
    m_coordinateUnitsComboBox->addItem(UnitsLabels[AxesUnits::NBINS]);

    //Column number selector:
    m_columnNumberSpinBox = new QSpinBox();
    m_columnNumberSpinBox->setMinimum(0);
    m_columnNumberSpinBox->setMaximum(0);
    m_columnNumberSpinBox->setValue(0);
    m_columnNumberSpinBox->setMaximumWidth(100);
    connect(m_columnNumberSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
            [this]()
            {
                auto col = m_columnNumberSpinBox->value();
                if(int(m_intensityCol) != col)
                    if(int(m_coordinateCol) != col)
                        setColumnAs(col-1, currentColumnType());
            }
    );



    //Column type (Intensity / Data / ...) selector:
    m_columnTypeComboBox = new QComboBox();
    m_columnTypeComboBox ->setMaximumWidth(100);
    m_columnTypeComboBox ->addItems(HeaderLabels);
    connect(m_columnTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            [this](int columnType)
    {
        if(columnType == _intensity_){
            m_columnNumberSpinBox->setValue(int(m_intensityCol));
            m_multiplierField->setText(QString::number(m_intensityMultiplier));
        }
        else{
            m_columnNumberSpinBox->setValue(int(m_coordinateCol));
            m_multiplierField->setText(QString::number(m_coordinateMultiplier));
        }
    }
            );

    m_multiplierField = new QLineEdit();
    m_multiplierField = new QLineEdit(QString("1.0"));
    m_multiplierField ->setMaxLength(16);
    m_multiplierField ->setMaximumWidth(100);
    connect(m_multiplierField, &QLineEdit::editingFinished, this,
            [this]()
            {
        if(currentColumnType() == _intensity_){
                m_intensityMultiplier = currentMultiplier();
        }
        else{
                m_coordinateMultiplier = currentMultiplier();
        }
        applyMultipliers();
            }

    );

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    //place table Widget
    auto tableLayout = new QVBoxLayout;
    tableLayout->setMargin(10);
    tableLayout->addWidget(new QLabel("Right click on the table to select what will be imported"));
    tableLayout->addWidget(m_tableWidget);

    //place separator_field, first and last data rows:
    auto controlsLayout = new QFormLayout;
    controlsLayout->addRow(tr("&Separator: "), m_separatorField);
    controlsLayout->addRow(tr("&From row: "), m_firstDataRowSpinBox);
    controlsLayout->addRow(tr("&To row: "), m_lastDataRowSpinBox);

    //Column handling controls:
    auto columnSelectionLayout = new QFormLayout;
    columnSelectionLayout->addRow(tr("&Import "), m_columnTypeComboBox);
    columnSelectionLayout->addRow(tr("&from column "), m_columnNumberSpinBox);
    columnSelectionLayout->addRow(tr("&Coordinate units "), m_coordinateUnitsComboBox);
    columnSelectionLayout->addRow(tr("&Multiply by "), m_multiplierField);

    //buttons layout
    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_importButton);
    buttonsLayout->addWidget(m_cancelButton);

    //place controls and import/reject buttons
    auto controlsAndButtonsGrid = new QGridLayout;
    controlsAndButtonsGrid->setMargin(10);
    controlsAndButtonsGrid->addItem(new QSpacerItem(10000,1),1,1,2,1);
    controlsAndButtonsGrid->addLayout(controlsLayout, 1, 2, 1, 1, Qt::AlignRight);
    controlsAndButtonsGrid->addLayout(columnSelectionLayout,1,1, Qt::AlignLeft);
    controlsAndButtonsGrid->addLayout(buttonsLayout, 3, 2, 1, 1, Qt::AlignLeft);

    //build all the layout
    layout->addLayout(tableLayout);
    layout->addLayout(controlsAndButtonsGrid);

    return layout;
}

