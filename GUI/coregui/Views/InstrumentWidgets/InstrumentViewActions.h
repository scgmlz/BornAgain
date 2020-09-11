// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewActions.h
//! @brief     Defines class InstrumentViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTVIEWACTIONS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTVIEWACTIONS_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QObject>

class QAction;
class SessionModel;
class QItemSelectionModel;
class QModelIndex;
class QMenu;

//! Collection of actions to add/remove/clone instrument.

class BA_CORE_API_ InstrumentViewActions : public QObject
{
    Q_OBJECT

public:
    explicit InstrumentViewActions(QWidget* parent = nullptr);
    ~InstrumentViewActions();

    void setModel(SessionModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

    QMenu* instrumentMenu();

public slots:
    void onAddInstrument();
    void onRemoveInstrument();
    void onCloneInstrument();
    void onContextMenuRequest(const QPoint& point, const QModelIndex& indexAtPoint);

private:
    void setAllActionsEnabled(bool value);
    void updateSelection();
    QString suggestInstrumentName(const QString& currentName);
    QMap<QString, int> mapOfNames();
    void initAddInstrumentMenu();

    QMenu* m_addInstrumentMenu;
    QAction* m_removeInstrumentAction;
    QAction* m_cloneInstrumentAction;
    SessionModel* m_model;
    QItemSelectionModel* m_selectionModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTVIEWACTIONS_H
