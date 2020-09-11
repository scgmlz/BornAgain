// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.h
//! @brief     Defines class RealDataSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORACTIONS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORACTIONS_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class RealDataModel;
class QAction;
class QItemSelectionModel;

//! The RealDataSelectorActions class contains actions to run/remove real data.
//! Actions are used by the toolbar and context menu of selector list.

class BA_CORE_API_ RealDataSelectorActions : public QObject
{
    Q_OBJECT
public:
    RealDataSelectorActions(QObject* parent = nullptr);

    void setRealDataModel(RealDataModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

public slots:
    void onImport1dDataAction();
    void onImport2dDataAction();
    void onRemoveDataAction();
    void onRotateDataRequest();
    void onContextMenuRequest(const QPoint& point, const QModelIndex& indexAtPoint);

private:
    void setAllActionsEnabled(bool value);
    void updateSelection();
    void importDataLoop(int ndim);

    QAction* m_import2dDataAction;
    QAction* m_import1dDataAction;
    QAction* m_removeDataAction;
    QAction* m_rotateDataAction;
    RealDataModel* m_realDataModel;
    QItemSelectionModel* m_selectionModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORACTIONS_H
