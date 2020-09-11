// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/SessionItemWidget.h
//! @brief     Defines class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_SESSIONITEMWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_SESSIONITEMWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class SessionItem;
class QShowEvent;
class QHideEvent;
class SessionItemController;

//! The SessionItemWidget class is a base for all widgets representing the content
//! of SessionItem. It provides subscribe/unsibscribe mechanism on show/hide events.
//! The main purpose is to save performance, when item keeps changing its properties, while
//! widget is hidden.

class BA_CORE_API_ SessionItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SessionItemWidget(QWidget* parent = 0);
    virtual ~SessionItemWidget();

    virtual void setItem(SessionItem* item);
    virtual QList<QAction*> actionList();

    SessionItem* currentItem();
    const SessionItem* currentItem() const;

protected:
    virtual void subscribeToItem() {}
    virtual void unsubscribeFromItem() {}
    virtual void showEvent(QShowEvent*);
    virtual void hideEvent(QHideEvent*);

private:
    SessionItemController* m_itemController;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_SESSIONITEMWIDGET_H
