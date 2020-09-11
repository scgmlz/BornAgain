// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/GUIMessage.cpp
//! @brief     Implements class GUIMessage.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/utils/GUIMessage.h"
#include <QObject>

GUIMessage::GUIMessage(const QString& senderName, const QString& messageType,
                       const QString& messageDescription)
    : m_sender(nullptr), m_senderName(senderName), m_messageType(messageType),
      m_messageDescription(messageDescription)
{
}

GUIMessage::GUIMessage(const QObject* sender, const QString& messageType,
                       const QString& messageDescription)
    : m_sender(sender), m_messageType(messageType), m_messageDescription(messageDescription)
{
    m_senderName = sender->objectName();
}

QString GUIMessage::senderName() const
{
    return m_senderName;
}

QString GUIMessage::messageType() const
{
    return m_messageType;
}

QString GUIMessage::messageDescription() const
{
    return m_messageDescription;
}

QString GUIMessage::text() const
{
    QString result =
        QString("%1 %2 %3").arg(m_senderName).arg(m_messageType).arg(m_messageDescription);
    return result;
}

const QObject* GUIMessage::sender() const
{
    return m_sender;
}
