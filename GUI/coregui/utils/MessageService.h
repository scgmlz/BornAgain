// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/MessageService.h
//! @brief     Defines MessageService class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_MESSAGESERVICE_H
#define BORNAGAIN_GUI_COREGUI_UTILS_MESSAGESERVICE_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QStringList>

class MessageContainer;
class QObject;
class GUIMessage;

//! @class MessageService
//! @brief The service to collect messages from different senders.

class BA_CORE_API_ MessageService
{
public:
    virtual ~MessageService();

    void clear();

    void send_message(QObject* sender, const QString& message_type, const QString& description);
    void send_error(QObject* sender, const QString& description);
    void send_warning(QObject* sender, const QString& description);

    const QList<GUIMessage*> messages() const;

    QStringList senderList() const;

    int messageCount(const QObject* sender, const QString& message_type = "") const;
    int warningCount(const QObject* sender = 0) const;
    int errorCount(const QObject* sender = 0) const;

    QStringList errorDescriptionList(const QObject* sender = 0) const;

private:
    QList<GUIMessage*> m_messages;
};

#endif // BORNAGAIN_GUI_COREGUI_UTILS_MESSAGESERVICE_H
