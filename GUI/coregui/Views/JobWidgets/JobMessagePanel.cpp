// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobMessagePanel.cpp
//! @brief     Implements class JobMessagePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/JobMessagePanel.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QScrollBar>
#include <QStackedWidget>
#include <QTextEdit>
#include <QVBoxLayout>

JobMessagePanel::JobMessagePanel(QWidget* parent) : InfoPanel(parent), m_plainLog(new QTextEdit)
{
    setWindowTitle(Constants::JobMessagePanelName);
    setObjectName("JobMessagePanel");

    m_plainLog->setReadOnly(true);
    //    m_plainLog->setMaximumBlockCount(100000);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    m_plainLog->setFont(f);

    m_stackedWidget->addWidget(m_plainLog);

    setContentVisible(false);
}

void JobMessagePanel::onClearLog()
{
    m_plainLog->clear();
}

void JobMessagePanel::onMessage(const QString& message, const QColor& color)
{
    QScrollBar* scrollbar = m_plainLog->verticalScrollBar();
    bool autoscroll = scrollbar->value() == scrollbar->maximum();
    //    m_plainLog->appendPlainText(message);
    m_plainLog->setTextColor(color);
    m_plainLog->append(message);
    if (autoscroll) {
        QTextCursor c = m_plainLog->textCursor();
        c.movePosition(QTextCursor::End);
        m_plainLog->setTextCursor(c);
    }
}
