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
#include "GUI/coregui/DataLoaders/AbstractDataLoader.h"
#include "GUI/coregui/DataLoaders/DataLoaders1D.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include "ui_ImportDialog.h"
#include <QAction>
#include <QFileDialog>
#include <QStringListModel>
#include <QTextStream>
#include <QTimer>

ImportDialog::ImportDialog(QWidget* parent /*= 0*/)
    : QDialog(parent), m_ui(new Ui::ImportDialog), m_listModel(new QStringListModel(this))
{
    m_ui->setupUi(this);

    m_ui->filesListView->setModel(m_listModel);

    if (DataLoaders1D::instance().loaders().isEmpty())
        DataLoaders1D::instance().initBuiltInLoaders();

    fillLoaderCombo();

    updatePropertiesEdits();

    QAction* add = new QAction(this);
    add->setText("Add files...");
    connect(add, &QAction::triggered, this, &ImportDialog::openFileSelectionDialog);
    //    m_ui->addToolButton->setDefaultAction(add);

    QAction* remove = new QAction(this);
    remove->setText("Remove files");
    connect(remove, &QAction::triggered, this, &ImportDialog::onRemoveFileRequest);
    //    m_ui->removeToolButton->setDefaultAction(remove);

    connect(m_ui->okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_ui->formatSelectionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ImportDialog::onFormatSelectionChanged);

    connect(m_ui->filesListView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &ImportDialog::updatePreview);

    connect(m_ui->createNewFormatButton, &QPushButton::clicked, this,
            &ImportDialog::onCreateNewFormatButton);
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
    dialog.setNameFilter("Text (*.txt *.csv *.dat);; Other (*.*)");

    QStringList filenames = dialog.exec() ? dialog.selectedFiles() : QStringList();

    if (filenames.empty())
        return;

    AppSvc::projectManager()->setImportDir(filenames.back());

    filenames = validateForBinaryFiles(filenames);
    addFileNamesToModel(filenames);
    updatePreview();
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
    updatePreview();
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

void ImportDialog::updatePropertiesEdits()
{
    for (auto child : m_ui->propertiesGroupBox->children()) {
        delete child;
    }

    if (m_ui->propertiesGroupBox->layout())
        delete m_ui->propertiesGroupBox->layout();

    if (selectedLoader()) {
        selectedLoader()->fillPropertiesGroupBox(m_ui->propertiesGroupBox);
    }

    const bool hasChildren = !m_ui->propertiesGroupBox->children().empty();

    m_ui->propertiesGroupBox->setVisible(hasChildren);
}

AbstractDataLoader* ImportDialog::selectedLoader()
{
    const QString name = m_ui->formatSelectionComboBox->currentText();

    for (auto loader : DataLoaders1D::instance().loaders())
        if (name == loader->name())
            return loader;

    return nullptr;
}

void ImportDialog::onFormatSelectionChanged(int /*index*/)
{
    // #TODO: disconnect() old loader?
    selectedLoader()->initWithDefaultProperties();
    updatePropertiesEdits();
    updatePreview();
    connect(selectedLoader(), &AbstractDataLoader::propertiesChanged, this,
            &ImportDialog::updatePreview);
}

void ImportDialog::updatePreview()
{
    m_ui->infoBrowser->clear();
    m_ui->fileContent->clear();
    m_ui->plotWidget->clearGraphs();

    if (selectedLoader() && !currentFileName().isEmpty()) {
        m_ui->infoBrowser->setHtml(selectedLoader()->preview(currentFileName(), m_ui->plotWidget));

        QFile file(currentFileName());
        if (file.open(QFile::ReadOnly))
            m_ui->fileContent->setText(QTextStream(&file).readAll());
    }

    m_ui->plotWidget->replot();
}

QString ImportDialog::currentFileName() const
{
    const auto currentIndex = m_ui->filesListView->currentIndex();
    return currentIndex.isValid() ? m_listModel->data(currentIndex).toString() : "";
}

void ImportDialog::onCreateNewFormatButton()
{
    bool ok;
    QString name = QInputDialog::getText(
        this, "New format", "Please enter a name for the new format", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty())
        return;

    DataLoaders1D::instance().cloneAsUserDefinedLoader(selectedLoader(), name);

    fillLoaderCombo();
    m_ui->formatSelectionComboBox->setCurrentText(name);
}

void ImportDialog::fillLoaderCombo()
{
    QSignalBlocker b(m_ui->formatSelectionComboBox);
    m_ui->formatSelectionComboBox->clear();
    for (auto loader : DataLoaders1D::instance().recentlyUsedLoaders()) {
        m_ui->formatSelectionComboBox->addItem(loader->name());
    }
    for (auto loader : DataLoaders1D::instance().loaders()) {
        m_ui->formatSelectionComboBox->addItem(loader->name());
    }
}
