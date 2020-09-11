// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/MessageService.cpp
//! @brief     Implements MessageService class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/utils/MessageService.h"
#include "GUI/coregui/utils/GUIMessage.h"
#include <QObject>
#include <QSet>

namespace
{
const QString message_error_type = "Error";
const QString message_warning_type = "Warning";
} // namespace

MessageService::~MessageService()
{
    clear();
}

void MessageService::clear()
{
    for (auto message : m_messages)
        delete message;

    m_messages.clear();
}

void MessageService::send_message(QObject* sender, const QString& message_type,
                                  const QString& description)
{
    m_messages.append(new GUIMessage(sender, message_type, description));
}

void MessageService::send_error(QObject* sender, const QString& description)
{
    send_message(sender, message_error_type, description);
}

void MessageService::send_warning(QObject* sender, const QString& description)
{
    send_message(sender, message_warning_type, description);
}

const QList<GUIMessage*> MessageService::messages() const
{
    return m_messages;
}

QStringList MessageService::senderList() const
{
    QSet<QString> set;
    for (auto message : messages())
        set.insert(message->senderName());

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    return set.values();
#else
    return set.toList();
#endif
}

//! Reports number of messages of given type reported by the sender.
//! If message_type.isEmpty, count all messages of given sender.

int MessageService::messageCount(const QObject* sender, const QString& message_type) const
{
    int result(0);
    for (auto message : messages())
        if (sender && message->sender() == sender) {
            if (message_type.isEmpty())
                ++result;
            else if (message->messageType() == message_type)
                ++result;
        } else if (sender == nullptr) {
            if (message_type.isEmpty())
                ++result;
            else if (message->messageType() == message_type)
                ++result;
        }

    return result;
}

//! Returns number of warnings for given sender.
//! If sender is nullptr, report total number of warnings.

int MessageService::warningCount(const QObject* sender) const
{
    return messageCount(sender, message_warning_type);
}

//! Returns number of errors for given sender.
//! If sender is nullptr, report total number of errors.

int MessageService::errorCount(const QObject* sender) const
{
    return messageCount(sender, message_error_type);
}

//! Returns multi-line string representing error messages of given sender.

QStringList MessageService::errorDescriptionList(const QObject* sender) const
{
    QStringList result;

    for (auto message : messages())
        if (message->sender() == sender && message->messageType() == message_error_type)
            result.push_back(message->messageDescription());

    return result;
}
