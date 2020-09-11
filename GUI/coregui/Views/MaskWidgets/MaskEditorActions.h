// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorActions.h
//! @brief     Defines class MaskEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORACTIONS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORACTIONS_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include "Wrap/WinDllMacros.h"
#include <QList>
#include <QModelIndex>
#include <QObject>

class QAction;
class SessionModel;
class QItemSelectionModel;
class QMenu;
class QMenu;

//! Defines actions for MaskEditor which are related to selected MaskItem (toggle mask value,
//! lower/rize mask in the stack, delete mask). If more than one MaskItem is selected,
//! action will be applied to the whole selection, if possible.

class BA_CORE_API_ MaskEditorActions : public QObject
{
    Q_OBJECT
public:
    MaskEditorActions(QWidget* parent);

    void setModel(SessionModel* maskModel, const QModelIndex& rootIndex);
    void setSelectionModel(QItemSelectionModel* selectionModel);

    QAction* sendToBackAction();
    QAction* bringToFrontAction();

    QList<QAction*> topToolBarActions();

signals:
    void resetViewRequest();
    void propertyPanelRequest();
    void savePlotRequest();

public slots:
    void onItemContextMenuRequest(const QPoint& point);
    void onDeleteMaskAction();

private slots:
    void onToggleMaskValueAction();
    void onBringToFrontAction();
    void onSendToBackAction();

private:
    void initItemContextMenu(QMenu& menu);
    void changeMaskStackingOrder(MaskEditorFlags::Stacking value);
    bool isBringToFrontPossible() const;
    bool isSendToBackPossible() const;
    void setAllActionsEnabled(bool value);

    QAction* m_toggleMaskValueAction;
    QAction* m_bringToFrontAction;
    QAction* m_sendToBackAction;
    QAction* m_deleteMaskAction;

    QAction* m_resetViewAction;
    QAction* m_savePlotAction;
    QAction* m_togglePanelAction;

    SessionModel* m_maskModel;
    QModelIndex m_rootIndex; //! Index in the model corresponding to IntensityDataItem
    QItemSelectionModel* m_selectionModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORACTIONS_H
