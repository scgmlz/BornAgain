// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/SessionItemController.h
//! @brief     Defines class SessionItemController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_SESSIONITEMCONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_SESSIONITEMCONTROLLER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <functional>

class SessionItem;

//! Provides subscribe/unsubscribe mechanism for any QObject to track
//! time of life of SessionItem. Mainly intended for SessionItemWidget.

class BA_CORE_API_ SessionItemController : public QObject
{
    Q_OBJECT
public:
    using callback_t = std::function<void(void)>;

    explicit SessionItemController(QObject* prt);
    ~SessionItemController();

    void setItem(SessionItem* item);

    SessionItem* currentItem();

    void setSubscribeCallback(callback_t fun);
    void setUnsubscribeCallback(callback_t fun);

    void subscribe();
    void unsubscribe();

private:
    void onItemDestroy();
    void onControllerDestroy();
    void subscribeParent();
    void unsubscribeParent();

    callback_t m_subscribe_callback;
    callback_t m_unsubscribe_callback;
    SessionItem* m_item;
    bool m_parent_subscribed;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_SESSIONITEMCONTROLLER_H
