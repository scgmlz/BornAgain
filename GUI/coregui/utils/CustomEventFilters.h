// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/CustomEventFilters.h
//! @brief     Defines classes releted to event filtering
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_CUSTOMEVENTFILTERS_H
#define BORNAGAIN_GUI_COREGUI_UTILS_CUSTOMEVENTFILTERS_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

//! Filter out space bar key events, which is special case for dialog windows.

class BA_CORE_API_ SpaceKeyEater : public QObject
{
    Q_OBJECT
public:
    SpaceKeyEater(QObject* parent = 0);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

//! Event filter to install on combo boxes and spin boxes to not
//! to react on wheel events during scrolling of InstrumentComponentWidget.

class BA_CORE_API_ WheelEventEater : public QObject
{
    Q_OBJECT
public:
    WheelEventEater(QObject* parent = 0);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

//! Lisens for press-del-key events

class DeleteEventFilter : public QObject
{
    Q_OBJECT
public:
    DeleteEventFilter(QObject* parent = 0) : QObject(parent) {}

protected:
    bool eventFilter(QObject* dist, QEvent* event);

signals:
    void removeItem();
};

//! Event filter to prevent lost of focus by custom material editor.

class BA_CORE_API_ LostFocusFilter : public QObject
{
    Q_OBJECT
public:
    LostFocusFilter(QObject* parent = 0);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

//! Event filter for global tracking of shortcodes.

class BA_CORE_API_ ShortcodeFilter : public QObject
{
    Q_OBJECT
public:
    ShortcodeFilter(const QString& shortcode, QObject* parent = 0);

signals:
    void found();

protected:
    bool eventFilter(QObject* obj, QEvent* event);
    QString m_shortcode;
    int m_index;
};

//! Filter out right mouse button events.

class BA_CORE_API_ RightMouseButtonEater : public QObject
{
    Q_OBJECT
public:
    RightMouseButtonEater(QObject* parent = 0);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

//! Propagate tab events from focusProxy to parent.

class BA_CORE_API_ TabFromFocusProxy : public QObject
{
    Q_OBJECT
public:
    TabFromFocusProxy(QWidget* parent = 0);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
    QWidget* m_parent;
};

#endif // BORNAGAIN_GUI_COREGUI_UTILS_CUSTOMEVENTFILTERS_H
