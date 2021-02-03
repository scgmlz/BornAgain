//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/importfilewidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/dataloader/importfilewidget.h"
#include "gui2/core/app_constants.h"
#include "mvvm/utils/binutils.h"
#include "mvvm/utils/fileutils.h"
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QListView>
#include <QMessageBox>
#include <QSettings>
#include <QStringListModel>
#include <QVBoxLayout>

namespace gui2 {

namespace {
const QString current_workdir_key = "currentworkdir";

const QString workdir_setting_name()
{
    return Constants::DataLoaderGroupKey + "/" + current_workdir_key;
}

} // namespace

ImportFileWidget::ImportFileWidget(QWidget* parent)
    : QWidget(parent), m_listView(new QListView), m_listModel(new QStringListModel(this))
{
    readSettings();

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_listView);

    m_listView->setModel(m_listModel);
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listView->setAlternatingRowColors(true);
    m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &ImportFileWidget::fileSelectionChanged);
}

ImportFileWidget::~ImportFileWidget()
{
    writeSettings();
}

//! Summons dialog for file selections, update list view with file names.

void ImportFileWidget::onAddFilesRequest()
{
    QFileDialog dialog(this, "Select one or more files to load", m_currentWorkdir);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Text (*.txt *.csv *.dat);; Other (*.*)");
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    QStringList file_names = dialog.exec() ? dialog.selectedFiles() : QStringList();

    file_names = validateForBinaryFiles(file_names);

    if (file_names.empty())
        return;

    updateCurrentWorkdir(file_names);
    addFileNamesToModel(file_names);
}

//! Removes currently selected file

void ImportFileWidget::onRemoveFileRequest()
{
    auto selected = m_listView->selectionModel()->selectedIndexes();
    while (!selected.empty()) {
        m_listModel->removeRow(selected.back().row());
        selected = m_listView->selectionModel()->selectedIndexes();
    }

    emit fileNamesChanged();

    makeLastSelected();
}

//! Retuns the list of all file names imported by the user.

QStringList ImportFileWidget::fileNames() const
{
    return m_listModel->stringList();
}

//! Retuns the list of currently selected file names.

QStringList ImportFileWidget::selectedFileNames() const
{
    QStringList result;
    for (auto index : m_listView->selectionModel()->selectedIndexes())
        result.append(m_listModel->data(index).toString());
    return result;
}

//! Loads widget settings.

void ImportFileWidget::readSettings()
{
    QSettings settings;
    m_currentWorkdir = QDir::homePath();

    if (settings.contains(workdir_setting_name()))
        m_currentWorkdir = settings.value(workdir_setting_name()).toString();
}

//! Writes widget settings.

void ImportFileWidget::writeSettings()
{
    QSettings settings;
    settings.setValue(workdir_setting_name(), m_currentWorkdir);
}

//! Returns list validated for binary files.

QStringList ImportFileWidget::validateForBinaryFiles(const QStringList& file_names)
{
    QStringList result;
    for (const auto& file_name : file_names) {
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
}

//! Updates current working dir.

void ImportFileWidget::updateCurrentWorkdir(const QStringList& file_names)
{
    auto file_name = file_names.back();
    auto parent_path = ModelView::Utils::parent_path(file_name.toStdString());
    m_currentWorkdir = QString::fromStdString(parent_path);
}

//! Adds given list of file names to the model.

void ImportFileWidget::addFileNamesToModel(const QStringList& file_names)
{
    auto current_names = fileNames();
    QStringList updated_names = current_names + file_names;
    updated_names.removeDuplicates();
    m_listModel->setStringList(updated_names);

    emit fileNamesChanged();

    makeLastSelected();
}

void ImportFileWidget::makeLastSelected()
{
    if (m_listView->selectionModel()->selectedIndexes().empty()) {
        auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
        auto toSelect = m_listModel->index(m_listModel->rowCount() - 1);
        m_listView->selectionModel()->select(toSelect, flags);
    }
}

} // namespace gui2
