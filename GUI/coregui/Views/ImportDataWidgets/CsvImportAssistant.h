// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant.h
//! @brief     Defines class CsvImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVIMPORTASSISTANT_H
#define CSVIMPORTASSISTANT_H

#include "WinDllMacros.h"
#include "CsvReader.h"
#include "OutputData.h"
#include <QDialog>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <memory>

class QBoxLayout;

//! Dialog to hold ImportAssistant.

class BA_CORE_API_ CsvImportAssistant : public QDialog
{
    Q_OBJECT

public:
    CsvImportAssistant(QString dir = "./", QString file = "", QWidget* parent = nullptr);
    QString filepath() const;
    void setFilepath(QString fpath);
    char separator() const;
    unsigned headersLine() const;
    unsigned firstLine() const;
    unsigned lastLine() const;
    unsigned singleColumnImport() const;
    std::unique_ptr<OutputData<double>> getData();

public slots:
    void onImportButton();
    void onReloadButton();
    void onRejectButton();
    void onBrowseButton();


private:
    QBoxLayout* createLayout();
    QBoxLayout* createFileDetailsLayout();

    char guessSeparator() const;
    void generate_table();
    void set_table_data(CSVFile *csvFile);
    void convert_table();
    void remove_unwanted();
    void setRowNumbering();
    bool cell_is_blank(int iRow, int jCol);



    QString m_dirName;
    QString m_fileName;

    QTableWidget* m_tableWidget;
    QLineEdit* m_filePathField;
    QLineEdit* m_separatorField;
    //QSpinBox* m_headersRowSpinBox;
    QSpinBox* m_firstDataRowSpinBox;
    QSpinBox* m_lastDataRowSpinBox;
    QSpinBox* m_singleDataColSpinBox;
};

#endif // MATERIALEDITORDIALOG_H
