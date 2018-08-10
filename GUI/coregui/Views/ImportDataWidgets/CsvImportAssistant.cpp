// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/CsvImportAssistant.cpp
//! @brief     Implements class CsvImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvImportAssistant.h"
#include "mainwindow_constants.h"
#include "StyleUtils.h"
#include <QAction>
#include <QPushButton>
#include <QTableWidget>
#include <QSettings>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

namespace
{
const QSize default_dialog_size(600, 800);
}

CsvImportAssistant::CsvImportAssistant(QString dir, QString file, QWidget* parent)
    : m_dirName(dir), m_fileName(file), QDialog(parent)
{
    setWindowTitle("Data Importer");
    setMinimumSize(128, 128);
    resize(600, 800);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(createLayout());

    setLayout(layout);

    StyleUtils::setResizable(this);
    m_filePathField->setText(m_fileName);
    if(!m_fileName.isEmpty())
        CsvImportAssistant::onReloadButton();
}



QBoxLayout* CsvImportAssistant::createLayout()
{
    auto result = new QVBoxLayout;
    auto preresult = new QHBoxLayout;

    auto exportButton = new QPushButton("Export");
    connect(exportButton, &QPushButton::clicked, this, &CsvImportAssistant::onExportButton);

    auto rejectButton = new QPushButton("Cancel");
    connect(rejectButton, &QPushButton::clicked, this, &CsvImportAssistant::onRejectButton);


    m_tableWidget = new QTableWidget();

    preresult->setMargin(10);
    //preresult->setSpacing(5);
    //preresult->addStretch(1);

    preresult->addWidget(rejectButton);
    preresult->addWidget(exportButton);


    result->setMargin(10);
    //result->setSpacing(5);
    //result->addStretch(1);
    result->addWidget(m_tableWidget);
    //
    result->addLayout(CsvImportAssistant::createFileDetailsLayout());
    //

    result->addLayout(preresult);





    return result;
}

QBoxLayout* CsvImportAssistant::createFileDetailsLayout(){
    auto result = new QVBoxLayout;
    result->setMargin(10);
    //result->setSpacing(5);
    //result->addStretch(1);

    auto labelFilepath = new QLabel("File to import: ");
    m_filePathField = new QLineEdit("",this);
    auto browseButton = new QPushButton("browse");
    connect(browseButton, &QPushButton::clicked, this, &CsvImportAssistant::onBrowseButton);
    auto lay1 = new QHBoxLayout;
    //lay1->setMargin(10);
    //lay1->setSpacing(5);
    //lay1->addStretch(1);
    lay1->addWidget(labelFilepath);
    lay1->addWidget(m_filePathField);
    lay1->addWidget(browseButton);

    result->addLayout(lay1);

    auto labelSeparator = new QLabel("Separator: ");
    m_separatorField = new QLineEdit(",");
    m_separatorField->setMaxLength(1);
    auto lay2 = new QHBoxLayout;
    //lay2->setMargin(10);
    //lay2->setSpacing(5);
    //lay2->addStretch(1);
    lay2->addWidget(labelSeparator);
    lay2->addWidget(m_separatorField);
    result->addLayout(lay2);

    auto labelHeaderRow = new QLabel("Headers row (zero for no headers): ");
    m_headersRowSpinBox = new QSpinBox();
    m_headersRowSpinBox->setMinimum(0);
    m_headersRowSpinBox->setMaximum(0);
    m_headersRowSpinBox->setValue(0);
    auto lay3 = new QHBoxLayout;
    //lay3->setMargin(10);
    //lay3->setSpacing(5);
    //lay3->addStretch(1);
    lay3->addWidget(labelHeaderRow);
    lay3->addWidget(m_headersRowSpinBox);
    result->addLayout(lay3);

    auto labelFirstDataRow = new QLabel("First data row: ");
    m_firstDataRowSpinBox = new QSpinBox();
    m_firstDataRowSpinBox->setMinimum(1);
    m_firstDataRowSpinBox->setMaximum(1);
    m_firstDataRowSpinBox->setValue(1);
    auto lay4 = new QHBoxLayout;
    //lay4->setMargin(10);
    //lay4->setSpacing(5);
    //lay4->addStretch(1);
    lay4->addWidget(labelFirstDataRow);
    lay4->addWidget(m_firstDataRowSpinBox);
    result->addLayout(lay4);

    auto labelLastDataRow = new QLabel("Last data row (zero to read until last row found): ");
    m_lastDataRowSpinBox = new QSpinBox();
    m_lastDataRowSpinBox->setMinimum(0);
    m_lastDataRowSpinBox->setMaximum(0);
    m_lastDataRowSpinBox->setValue(0);
    auto lay5 = new QHBoxLayout;
    //lay5->setMargin(10);
    //lay5->setSpacing(5);
    //lay5->addStretch(1);
    lay5->addWidget(labelLastDataRow);
    lay5->addWidget(m_lastDataRowSpinBox);
    result->addLayout(lay5);


    auto lay6 = new QVBoxLayout;
    auto reloadButton = new QPushButton("Reload");
    connect(reloadButton, &QPushButton::clicked, this, &CsvImportAssistant::onReloadButton);
    //lay6->setMargin(10);
    lay6->addWidget(reloadButton);

    result->addLayout(lay1);
    result->addLayout(lay2);
    result->addLayout(lay3);
    result->addLayout(lay4);
    result->addLayout(lay5);
    result->addLayout(lay6);

    return result;
}

void CsvImportAssistant::onBrowseButton()
{
        const QString filter_string = "Intensity File (*.txt *.dat *.ascii *.int *.gz *.tif *.tiff *.csv);;All files (*.*)";
        QString fileName = QFileDialog::getOpenFileName(0, QStringLiteral("Open Intensity File"),
                                                        this->m_dirName, filter_string);
        if(fileName != NULL){
            m_filePathField->setText(fileName);
            m_fileName = fileName;
            CsvImportAssistant::onReloadButton();
        }

}

void CsvImportAssistant::onReloadButton()
{
    std::ifstream f(filepath().toStdString());
    if(f.good()){
        generate_table();
    }else{
        QMessageBox msgBox;
        std::string message = "There was a problem opening the file \"" + filepath().toStdString() + "\"";
        message += "\n Check for any errors in the path and try again.";
        msgBox.setText(QString::fromStdString(message));
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void CsvImportAssistant::onRejectButton(){
    reject();
}


void CsvImportAssistant::onExportButton()
{
    using namespace std;

    int nRows = m_tableWidget->rowCount();
    int nCols = m_tableWidget->columnCount();
    vector<vector<string>> A;
    vector<string> B;

    //save the values of the array
    for(int i = 0; i < nRows; i++){
        B.clear();
        for(int j = 0; j < nCols; j++){
           B.push_back( m_tableWidget->item(i,j) != NULL ? m_tableWidget->item(i,j)->text().toStdString() : "");
        }
        A.push_back(B);
    }

    setFilepath(filepath()+"-ba-exported.txt");
    ofstream output_file(filepath().toStdString());
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols - 1; j++){
            std::string a = A[i][j];
            output_file << a << " ";
        }
        std::string a = A[i][nCols - 1];
        output_file << a << '\n';
    }
    accept();
}


void CsvImportAssistant::generate_table()
{
    CSVFile* csvFile;
    try{
        csvFile = new CSVFile(filepath().toStdString(), separator(), headersLine());
    }
    catch(...){
        QMessageBox msgBox;
        std::string message = "There was a problem opening the file \"" + filepath().toStdString() + "\"";
        msgBox.setText(QString::fromStdString(message));
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
        return;
    }

    m_tableWidget->clearContents();
    m_tableWidget->setColumnCount(csvFile->NumberOfColumns());
    m_tableWidget->setRowCount(0);
    m_lastDataRowSpinBox->setMaximum(csvFile->NumberOfRows());
    m_firstDataRowSpinBox->setMaximum(csvFile->NumberOfRows());
    m_headersRowSpinBox->setMaximum(csvFile->NumberOfRows());

    set_table_headers(csvFile);
    set_table_data(csvFile);
    remove_blanks();

    return;
}

void CsvImportAssistant::set_table_headers(CSVFile* csvFile){
    QStringList titulos;

    CSVRow headers = csvFile->get_headers();

    for(uint j = 0; j < headers.size(); j++){
        std::string header = headers[j].empty() ? std::string("Column ") + std::to_string(j+1) : headers[j];
        titulos << QString::fromStdString(header);
    }
    m_tableWidget->setHorizontalHeaderLabels(titulos);
    return;
}


void CsvImportAssistant::set_table_data(CSVFile* csvFile){

    uint firstDataLine = firstLine() - 1;
    uint lastDataLine = lastLine() == 0 ? csvFile->NumberOfRows() : lastLine();

    for(uint i = firstDataLine; i < lastDataLine; i++){
        m_tableWidget->insertRow(m_tableWidget->rowCount());
        uint I = m_tableWidget->rowCount() - 1;
        for(uint j = 0; j < csvFile->NumberOfColumns(); j++){
           std::string aasdf = csvFile->operator [](i)[j];
           m_tableWidget->setItem(I,j,new QTableWidgetItem(QString::fromStdString(aasdf)));
        }
    }
}

void CsvImportAssistant::remove_blanks(){
    using namespace std;

    int nRows = m_tableWidget->rowCount();
    int nCols = m_tableWidget->columnCount();
    vector<vector<string>> A;
    vector<string> B;
    vector<int> blank_cols;

    //save the inices of blank cols
    for(int j = 0; j < nCols; j++){
        int i = 0;
        bool this_col_is_blank = cell_is_blank(i,j);
        while(this_col_is_blank && i < nRows  ){
            this_col_is_blank = cell_is_blank(i,j);
            i++;
        }
        if(i == nRows){
            blank_cols.push_back(j);
        }
    }

    //save the values of the array
    for(int i = 0; i < nRows; i++){
        B.clear();
        for(int j = 0; j < nCols; j++){
           B.push_back( m_tableWidget->item(i,j) != NULL ? m_tableWidget->item(i,j)->text().toStdString() : "");
        }
        A.push_back(B);
    }

    //put them into a new table
    m_tableWidget->clearContents();
    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(nCols-blank_cols.size());
    for(int i = 0; i < nRows; i++){
        m_tableWidget->insertRow(m_tableWidget->rowCount());
        int J = 0;
        for(int j = 0; j < nCols; j++){
               if( std::find(blank_cols.begin(), blank_cols.end(), j) == blank_cols.end()){
                    std::string a = A[i][j];
                    m_tableWidget->setItem(i,J,new QTableWidgetItem(QString::fromStdString(a)));
                    J++;
               }
         }

    }
}

bool CsvImportAssistant::cell_is_blank(int iRow, int jCol){

    if ( m_tableWidget->item(iRow,jCol) == NULL)
        return true;

    if ( m_tableWidget->item(iRow,jCol)->text() == NULL)
        return true;

    if( m_tableWidget->item(iRow,jCol)->text().trimmed() == "")
        return true;

    return false;
}

QString CsvImportAssistant::filepath() const{
        return m_filePathField->text().trimmed();
}

void CsvImportAssistant::setFilepath(QString fpath){
    m_fileName = fpath;
    m_filePathField->setText(m_fileName);
}

char CsvImportAssistant::separator() const{
        char separator;
        QString tmpstr = m_separatorField->text();
        if(tmpstr.size() < 1){
                separator = ' ';
                QMessageBox msgBox;
                msgBox.setText("There was a problem with the separator given.\n Replacing it by ' ' [space]");
                msgBox.setIcon(msgBox.Information);
                msgBox.exec();
                m_separatorField->setText(QString(QChar::fromLatin1(separator)));
        }
        else{
                separator = tmpstr.at(0).toLatin1();
        }
        return separator;
}

uint CsvImportAssistant::headersLine() const{
       return m_headersRowSpinBox->value();
}

uint CsvImportAssistant::firstLine() const{
        return m_firstDataRowSpinBox->value();
}

uint CsvImportAssistant::lastLine() const{
        return m_lastDataRowSpinBox->value();
}

