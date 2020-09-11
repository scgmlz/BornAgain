// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/StatusLabel.cpp
//! @brief     Implements class StatusLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/StatusLabel.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QColor>
#include <QFont>
#include <QPainter>

namespace
{
int default_text_size()
{
    return StyleUtils::SystemPointSize();
}
int default_label_height()
{
    return StyleUtils::SizeOfLetterM().height() * 1.75;
}
} // namespace

StatusLabel::StatusLabel(QWidget* parent)
    : QFrame(parent), m_font("Monospace", default_text_size(), QFont::Normal, false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(default_label_height());
}

void StatusLabel::setText(const QString& text)
{
    m_text = text;
    update();
}

void StatusLabel::setFont(const QFont& font)
{
    m_font = font;
    update();
}

void StatusLabel::setPointSize(int pointSize)
{
    m_font.setPointSize(pointSize);
    update();
}

void StatusLabel::setAlignment(Qt::Alignment alignment)
{
    m_alignment = alignment;
    update();
}

void StatusLabel::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(QColor(Qt::black));
    painter.setPen(QColor(Qt::black));
    painter.setFont(m_font);

    QRect textRect(0, 0, geometry().width(), geometry().height());
    painter.fillRect(textRect, QColor(Qt::white));
    painter.drawText(textRect, m_alignment, m_text);
}
