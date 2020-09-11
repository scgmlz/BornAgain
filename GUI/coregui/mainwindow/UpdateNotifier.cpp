// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/UpdateNotifier.cpp
//! @brief     Implements class UpdateNotifier
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/UpdateNotifier.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QtNetwork>

UpdateNotifier::UpdateNotifier(QObject* parent)
    : QObject(parent), m_networkAccessManager(new QNetworkAccessManager(parent))
{
    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this,
            &UpdateNotifier::replyFinished);
}

void UpdateNotifier::checkForUpdates()
{
    if (hasDefinedUpdatesFlag()) {
        if (updatesFlag()) {
            QString address(Constants::S_VERSION_URL);
            QUrl url(address);
            QNetworkRequest networkRequest(url);
            networkRequest.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                                        QNetworkRequest::AlwaysNetwork);
            QString text = QString("Mozilla/5.0 (BornAgainGUI-%1)")
                               .arg(GUIHelpers::getBornAgainVersionString());
            networkRequest.setRawHeader(QByteArray("User-Agent"), text.toLatin1());
            m_networkAccessManager->get(networkRequest);
        } else {
            emit onUpdateNotification("");
        }
    }
}

void UpdateNotifier::replyFinished(QNetworkReply* reply)
{
    QString replyString;
    if (reply->error() == QNetworkReply::NoError) {
        if (reply->isReadable()) {
            // Reading the first line of ChangeLog
            replyString = QString::fromUtf8(reply->readLine().data());
            int versionIndex = replyString.indexOf("-") + 1;
            int versionIndexEnd = replyString.indexOf(",", versionIndex);
            QString versionString = replyString.mid(versionIndex, versionIndexEnd - versionIndex);
            QString myVersion = GUIHelpers::getBornAgainVersionString();

            // Testwise degrade version
            // myVersion = "1.1.0";

            if (GUIHelpers::versionCode(versionString) > GUIHelpers::versionCode(myVersion)) {
                QString message("New version is available: <a href=\"");
                message.append(Constants::S_DOWNLOAD_LINK);
                message.append("\">");
                message.append(replyString);
                message.append("</a>");
                emit onUpdateNotification(message);
            } else {
                emit onUpdateNotification("");
            }
        }
    };
    reply->deleteLater();
}

void UpdateNotifier::setCheckUpdatesFlag(bool flag)
{
    QSettings settings;
    settings.beginGroup(Constants::S_UPDATES);
    settings.setValue(Constants::S_CHECKFORUPDATES, flag);
    settings.endGroup();
}

//! Returns true if there is defined flag requiring check for updates.

bool UpdateNotifier::updatesFlag() const
{
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_UPDATES)) {
        settings.beginGroup(Constants::S_UPDATES);
        return settings.value(Constants::S_CHECKFORUPDATES).toBool();
    }
    return false;
}

//! Returns true if settings contain record about user choice for updates.

bool UpdateNotifier::hasDefinedUpdatesFlag() const
{
    QSettings settings;
    return settings.childGroups().contains(Constants::S_UPDATES);
}
