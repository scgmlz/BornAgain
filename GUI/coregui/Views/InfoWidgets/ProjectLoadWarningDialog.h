// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/ProjectLoadWarningDialog.h
//! @brief     Defines class ProjectLoadWarningDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_PROJECTLOADWARNINGDIALOG_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_PROJECTLOADWARNINGDIALOG_H

#include "Wrap/WinDllMacros.h"
#include <QDialog>
#include <QStringList>

class MessageService;
class QTableWidget;
class QLabel;
class QLayout;
class QTableWidgetItem;

//! @class ProjectLoadWarningDialog
//! @brief The dialog to inform user about encountered problems during the loading of old project

class BA_CORE_API_ ProjectLoadWarningDialog : public QDialog
{
    Q_OBJECT

public:
    ProjectLoadWarningDialog(QWidget* parent, const MessageService* messageService = 0,
                             const QString& documentVersion = "");

private:
    QWidget* createTopPanel();
    QWidget* createModelInfoPanel();
    QWidget* createExplanationPanel();
    QWidget* createDetailsPanel();
    QTableWidget* createTableWidget();
    QLayout* buttonLayout();

    int numberOfTableRows() const;
    QStringList tableHeaderLabels() const;
    QTableWidgetItem* createTableItem(const QString& name);

    QString explanationText() const;

    const MessageService* m_messageService;
    QString m_projectDocumentVersion;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_PROJECTLOADWARNINGDIALOG_H
