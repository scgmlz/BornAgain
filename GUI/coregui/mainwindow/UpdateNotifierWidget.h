// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/UpdateNotifierWidget.h
//! @brief     Defines class UpdateNotifierWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_UPDATENOTIFIERWIDGET_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_UPDATENOTIFIERWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class UpdateNotifier;
class QLabel;
class QShowEvent;

//! Small on WelcomeView for notofications about updates.

class BA_CORE_API_ UpdateNotifierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateNotifierWidget(UpdateNotifier* updateNotifier, QWidget* parent = nullptr);

protected:
    void showEvent(QShowEvent* event);

private slots:
    void onUpdateNotification(const QString& text);
    void onLinkActivated(const QString& text);

private:
    UpdateNotifier* m_updateNotifier;
    QLabel* m_updateLabel;
    bool m_check_for_updates;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_UPDATENOTIFIERWIDGET_H
