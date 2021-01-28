//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDialog.cpp
//! @brief     Implements class ImportDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/ImportDataWidgets/ImportDialog.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include "ui_ImportDialog.h"
#include <QAction>
#include <QFileDialog>
#include <QStringListModel>
#include <QTimer>

ImportDialog::ImportDialog(QWidget* parent /*= 0*/)
    : QDialog(parent), m_ui(new Ui::ImportDialog), m_listModel(new QStringListModel(this))
{
    m_ui->setupUi(this);

    m_ui->filesListView->setModel(m_listModel);

    QAction* add = new QAction(this);
    add->setText("Add files...");
    connect(add, &QAction::triggered, this, &ImportDialog::openFileSelectionDialog);
    m_ui->addToolButton->setDefaultAction(add);

    QAction* remove = new QAction(this);
    remove->setText("Remove files");
    connect(remove, &QAction::triggered, this, &ImportDialog::onRemoveFileRequest);
    m_ui->removeToolButton->setDefaultAction(remove);

    connect(m_ui->okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QStringList ImportDialog::fileNames() const
{
    return m_listModel->stringList();
}

void ImportDialog::openFileSelectionDialog()
{
    QFileDialog dialog(this, "Select one or more files to load",
                       AppSvc::projectManager()->userImportDir());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Text (*.txt *.csv);; Other (*.*)");

    QStringList filenames = dialog.exec() ? dialog.selectedFiles() : QStringList();

    if (filenames.empty())
        return;

    AppSvc::projectManager()->setImportDir(filenames.back());

    filenames = validateForBinaryFiles(filenames);
    addFileNamesToModel(filenames);
}

void ImportDialog::showEvent(QShowEvent* e)
{
    QDialog::showEvent(e);

    if (m_firstShowEvent) {
        m_firstShowEvent = false;

        QTimer::singleShot(
            0, this,
            &ImportDialog::openFileSelectionDialog); // delayed call so the ImportDialog shows first
    }
}

//! Returns list validated for binary files.

QStringList ImportDialog::validateForBinaryFiles(const QStringList& filenames)
{
    /* #migration: implement
    QStringList result;
    for (const auto& file_name : filenames) {
        if (ModelView::Utils::is_binary(file_name.toStdString())) {
            QMessageBox msgBox;
            msgBox.setText(file_name + "\nmay be a binary file. Open it anyway?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Yes)
                result.push_back(file_name);
        } else {
            result.push_back(file_name);
        }
    }
    return result;
    */

    return filenames;
}

//! Adds given list of file names to the model.

void ImportDialog::addFileNamesToModel(const QStringList& file_names)
{
    auto current_names = fileNames();
    QStringList updated_names = current_names + file_names;
    updated_names.removeDuplicates();
    m_listModel->setStringList(updated_names);

    emit fileNamesChanged();

    makeLastSelected();
}

void ImportDialog::makeLastSelected()
{
    if (m_ui->filesListView->selectionModel()->selectedIndexes().empty()) {
        auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
        auto toSelect = m_listModel->index(m_listModel->rowCount() - 1);
        m_ui->filesListView->selectionModel()->select(toSelect, flags);
    }
}

//! Removes currently selected file

void ImportDialog::onRemoveFileRequest()
{
    auto selected = m_ui->filesListView->selectionModel()->selectedIndexes();
    while (!selected.empty()) {
        m_listModel->removeRow(selected.back().row());
        selected = m_ui->filesListView->selectionModel()->selectedIndexes();
    }

    emit fileNamesChanged();

    makeLastSelected();
}
