// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/FancyLabel.cpp
//! @brief     Implements class FancyLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/utils/FancyLabel.h"
#include <QTimer>

FancyLabel::FancyLabel(const QString& text, QWidget* parent) : QLabel(text, parent)
{
    init_fancy_label();
}

FancyLabel::FancyLabel(QWidget* parent) : QLabel(parent)
{
    init_fancy_label();
}

void FancyLabel::setTextAnimated(const QString& animated_text)
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }

    if (animated_text == text())
        return;

    if (animated_text.isEmpty()) {
        setText(animated_text);
        return;
    }

    m_text = animated_text;
    m_current_index = 0;

    m_timer->setInterval(m_total_effect_duration / m_text.size());

    m_timer->start();
}

void FancyLabel::timeout()
{
    if (m_current_index <= m_text.size()) {
        setText(m_text.left(m_current_index));
        m_current_index++;
        return;
    }
    m_timer->stop();
}

void FancyLabel::init_fancy_label()
{
    m_total_effect_duration = 200; // in msec
    m_current_index = 0;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}
