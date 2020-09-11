// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/GroupInfoBox.cpp
//! @brief     Implements class GroupInfoBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/GroupInfoBox.h"
#include "GUI/coregui/utils/hostosinfo.h"
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QStyleOptionGroupBox>
#include <QStylePainter>
#include <QToolTip>
#include <iostream>

namespace
{
int imageWidth = 16;
int imageheigth = 16;
int offset_of_tooltip_position = 20;
int offset_of_icon_position = 24;
} // namespace

GroupInfoBox::GroupInfoBox(QWidget* parent) : QGroupBox(parent), m_xImage(0), m_yImage(0)
{
    init_box();
}

GroupInfoBox::GroupInfoBox(const QString& title, QWidget* parent)
    : QGroupBox(title, parent), m_title(title)
{
    init_box();
}

void GroupInfoBox::setButtonToolTip(const QString& text)
{
    m_toolTipText = text;
}

void GroupInfoBox::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        QStyleOptionGroupBox option;
        initStyleOption(&option);
        QRect buttonArea(m_xImage, m_yImage, imageWidth, imageheigth);
        if (buttonArea.contains(e->pos()))
            emit clicked(true);
    }
}

void GroupInfoBox::mouseMoveEvent(QMouseEvent* event)
{
    QRect buttonArea(m_xImage, m_yImage, imageWidth, imageheigth);

    if (buttonArea.contains(event->pos())) {
        QToolTip::showText(
            this->mapToGlobal(QPoint(m_xImage + offset_of_tooltip_position, m_yImage)),
            m_toolTipText);
    }
}

void GroupInfoBox::init_box()
{
    setMouseTracking(true);
    m_toolTipText = "Gives access to the extended distribution viewer.";
}

void GroupInfoBox::paintEvent(QPaintEvent*)
{
    QStylePainter paint(this);
    QStyleOptionGroupBox option;
    initStyleOption(&option);
    paint.drawComplexControl(QStyle::CC_GroupBox, option);

    m_xImage = this->geometry().topRight().x() - offset_of_icon_position;
    m_yImage = 0;

    // draw groupbox
    int shift(1);
    if (GUI_OS_Utils::HostOsInfo::isLinuxHost())
        shift = 3;

    paint.drawItemPixmap(option.rect.adjusted(0, shift, 0, 0), Qt::AlignTop | Qt::AlignRight,
                         QPixmap(":/images/magnifier.png"));
}
