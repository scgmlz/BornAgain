// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/UpdateNotifier.h
//! @brief     Implements class UpdateNotifier
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_UPDATENOTIFIER_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_UPDATENOTIFIER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class BA_CORE_API_ UpdateNotifier : public QObject
{
    Q_OBJECT
public:
    UpdateNotifier(QObject* parent = 0);
    void checkForUpdates();

public slots:
    void replyFinished(QNetworkReply* reply);

    void setCheckUpdatesFlag(bool flag);

    bool updatesFlag() const;

    bool hasDefinedUpdatesFlag() const;

signals:
    void onUpdateNotification(const QString& text);

private:
    QNetworkAccessManager* m_networkAccessManager;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_UPDATENOTIFIER_H
