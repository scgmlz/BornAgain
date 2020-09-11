// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/UpdateNotifierWidget.cpp
//! @brief     Implements class UpdateNotifierWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/UpdateNotifierWidget.h"
#include "GUI/coregui/mainwindow/UpdateNotifier.h"
#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QLabel>
#include <QSettings>
#include <QTimer>
#include <QUrl>

namespace
{
const QString yes = "yes";
const QString no = "no";

QString update_question()
{
    QString result = QString("Should BornAgain check for updates automatically? - "
                             " <a href=\"%1\">yes</a> /"
                             " <a href=\"%2\">no</a>")
                         .arg(yes, no);
    return result;
}
} // namespace

UpdateNotifierWidget::UpdateNotifierWidget(UpdateNotifier* updateNotifier, QWidget* parent)
    : QWidget(parent), m_updateNotifier(updateNotifier), m_updateLabel(new QLabel),
      m_check_for_updates(true)
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_updateLabel);
    setLayout(layout);

    m_updateLabel->setContentsMargins(30, 10, 0, 0);
    m_updateLabel->setOpenExternalLinks(false);
    m_updateLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_updateLabel->setTextFormat(Qt::RichText);
    m_updateLabel->setText("");

    m_updateNotifier = updateNotifier;
    connect(m_updateNotifier, &UpdateNotifier::onUpdateNotification, this,
            &UpdateNotifierWidget::onUpdateNotification);

    connect(m_updateLabel, &QLabel::linkActivated, this, &UpdateNotifierWidget::onLinkActivated);

    if (!m_updateNotifier->hasDefinedUpdatesFlag()) {
        m_updateLabel->setText(update_question());
        m_updateLabel->setToolTip("This setting can be changed later in the main window "
                                  "Settings menu.");
    }
}

//! Schedule check for updates if it was not done yet.

void UpdateNotifierWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if (m_check_for_updates) {
        m_check_for_updates = false;
        QTimer::singleShot(1000, this, [&]() { m_updateNotifier->checkForUpdates(); });
    }
}

//! Updates label when notification is coming.

void UpdateNotifierWidget::onUpdateNotification(const QString& text)
{
    m_updateLabel->setText(text);
}

//! Processes mouse click on update notification label.

void UpdateNotifierWidget::onLinkActivated(const QString& text)
{
    if (text == yes) {
        m_updateNotifier->setCheckUpdatesFlag(true);
        m_updateNotifier->checkForUpdates();
    } else if (text == no) {
        m_updateNotifier->setCheckUpdatesFlag(false);
        QTimer::singleShot(200, this, [&]() { m_updateLabel->setText(""); });
    } else {
        QDesktopServices::openUrl(QUrl(text));
    }
}
