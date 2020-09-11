// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/WarningSign.cpp
//! @brief     Implements class WarningSign
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/WarningSign.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/InfoWidgets/WarningSignWidget.h"
#include <QAbstractScrollArea>
#include <QEvent>
#include <QScrollBar>
#include <QTimer>

namespace
{
const int xpos_offset = 40;
const int ypos_offset = 40;
} // namespace

WarningSign::WarningSign(QWidget* parent)
    : QObject(parent), m_warning_header("Houston, we have a problem."), m_warningWidget(0),
      m_area(nullptr), m_clear_just_had_happened(false)
{
    setArea(parent);
}

//! Clears warning message;

void WarningSign::clear()
{
    delete m_warningWidget;
    m_warningWidget = 0;
    m_warning_message.clear();

    m_clear_just_had_happened = true;
    QTimer::singleShot(10, this, [=]() { m_clear_just_had_happened = false; });
}

void WarningSign::setWarningHeader(const QString& warningHeader)
{
    m_warning_header = warningHeader;
}

//! Shows warning sign on the screen. If clear of previous warning sign had happened just
//! few msec ago, make a small delay, to stress its reapearance.

void WarningSign::setWarningMessage(const QString& warningMessage)
{
    ASSERT(m_area);

    if (m_clear_just_had_happened) {
        m_clear_just_had_happened = false;
        QTimer::singleShot(50, this, [=]() { setWarningMessage(warningMessage); });
    } else {

        m_warning_message = warningMessage;

        if (!m_warningWidget)
            m_warningWidget = new WarningSignWidget(m_area);

        m_warningWidget->setWarningMessage(m_warning_message);
        updateLabelGeometry();
        m_warningWidget->show();
    }
}

void WarningSign::setArea(QWidget* area)
{
    m_area = area;
    m_area->installEventFilter(this);
}

bool WarningSign::isShown() const
{
    return (m_warningWidget == nullptr ? false : true);
}

bool WarningSign::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Resize)
        updateLabelGeometry();

    return QObject::eventFilter(obj, event);
}

void WarningSign::updateLabelGeometry()
{
    if (!m_warningWidget || !m_area)
        return;

    QPoint pos = positionForWarningSign();
    m_warningWidget->setPosition(pos.x(), pos.y());
}

QPoint WarningSign::positionForWarningSign() const
{
    ASSERT(m_area);

    int x = m_area->width() - xpos_offset;
    int y = m_area->height() - ypos_offset;

    if (QAbstractScrollArea* scrollArea = dynamic_cast<QAbstractScrollArea*>(m_area)) {

        if (QScrollBar* horizontal = scrollArea->horizontalScrollBar()) {
            if (horizontal->isVisible())
                y -= horizontal->height();
        }

        if (QScrollBar* vertical = scrollArea->verticalScrollBar()) {
            if (vertical->isVisible())
                x -= vertical->width();
        }
    }

    return QPoint(x, y);
}
