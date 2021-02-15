//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDialog.h
//! @brief     Defines class ImportDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_IMPORTDIALOG_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_IMPORTDIALOG_H

#include <QDialog>
#include <QWidget>

class QStringListModel;
class AbstractDataLoader;
class QCustomPlot;

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog {
    Q_OBJECT
public:
    explicit ImportDialog(QWidget* parent = 0);

    QStringList fileNames() const;

signals:
    void fileNamesChanged();

private:
    void openFileSelectionDialog();

    void showEvent(QShowEvent*) override;
    QStringList validateForBinaryFiles(const QStringList& file_names);

    void addFileNamesToModel(const QStringList& file_names);
    void makeLastSelected();
    void onRemoveFileRequest();

    void updatePropertiesEdits();
    AbstractDataLoader* selectedLoader();
    void onFormatSelectionChanged(int index);
    void updatePreview();
    QString currentFileName() const;

    void onCreateNewFormatButton();
    void fillLoaderCombo();

private:
    Ui::ImportDialog* m_ui = nullptr;
    bool m_firstShowEvent = true;
    QStringListModel* m_listModel = nullptr;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_IMPORTDIALOG_H
