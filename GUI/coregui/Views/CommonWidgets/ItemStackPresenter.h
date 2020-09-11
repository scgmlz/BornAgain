// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemStackPresenter.h
//! @brief     Defines class ItemStackPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMSTACKPRESENTER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMSTACKPRESENTER_H

#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/CommonWidgets/ItemStackWidget.h"
#include <QDebug>
#include <QMap>
#include <QStackedWidget>

class SessionItem;

//! The ItemStackPresenter templated class extends ItemStackWidget so it could operate with
//! SesionItem editor's of specified type, while still keeping signal/slots alive.

template <class T> class BA_CORE_API_ ItemStackPresenter : public ItemStackWidget
{
public:
    ItemStackPresenter(bool single_widget = false) : m_single_widget(single_widget) {}

    //! Shows the widget for given item (and hides previous one).
    //! If no widget yet exists, it will be created (flag isNew will become 'true' in this case).
    template <class U> void setItem(U* item, bool* isNew = 0);

    T* currentWidget();
    T* itemWidget(SessionItem* item);
    void hideWidgets();

protected:
    void removeWidgetForItem(SessionItem* item);
    void removeWidgets();

private:
    QMap<SessionItem*, T*> m_itemToWidget;
    bool m_single_widget; //!< Different items will be served by same widget
};

template <class T> template <class U> void ItemStackPresenter<T>::setItem(U* item, bool* isNew)
{
    validateItem(item);

    if (isNew)
        *isNew = false;

    if (!item) {
        hideWidgets();
        return;
    }

    T* widget = itemWidget(item);

    if (!widget) {
        widget = new T();
        if (isNew)
            *isNew = true;
        m_stackedWidget->addWidget(widget);
        m_itemToWidget[item] = widget;
    }

    m_stackedWidget->setCurrentWidget(widget);
    if (widget->isHidden())
        widget->show();

    widget->setItem(item);
}

template <class T> T* ItemStackPresenter<T>::currentWidget()
{
    return dynamic_cast<T*>(m_stackedWidget->currentWidget());
}

template <class T> T* ItemStackPresenter<T>::itemWidget(SessionItem* item)
{
    if (m_single_widget) {
        if (m_itemToWidget.size())
            return m_itemToWidget.first();
    } else {
        return m_itemToWidget[item];
    }

    return nullptr;
}

template <class T> void ItemStackPresenter<T>::hideWidgets()
{
    if (m_stackedWidget->currentWidget())
        m_stackedWidget->currentWidget()->hide();
}

template <class T> void ItemStackPresenter<T>::removeWidgetForItem(SessionItem* item)
{
    ASSERT(item);

    if (m_single_widget)
        return;

    T* widget = m_itemToWidget[item];
    if (!widget)
        return;

    typename QMap<SessionItem*, T*>::iterator it = m_itemToWidget.begin();
    while (it != m_itemToWidget.end()) {
        if (it.value() == widget)
            it = m_itemToWidget.erase(it);
        else
            ++it;
    }

    m_stackedWidget->removeWidget(widget);
    delete widget;
}

template <class T> void ItemStackPresenter<T>::removeWidgets()
{
    typename QMap<SessionItem*, T*>::iterator it = m_itemToWidget.begin();
    while (it != m_itemToWidget.end()) {
        m_stackedWidget->removeWidget(it.value());
        delete it.value();
        ++it;
    }
    m_itemToWidget.clear();
}

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMSTACKPRESENTER_H
