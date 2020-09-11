// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/OverlayLabelController.cpp
//! @brief     Implements class OverlayLabelController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/OverlayLabelController.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/InfoWidgets/OverlayLabelWidget.h"
#include <QAbstractScrollArea>
#include <QEvent>
#include <QRect>

OverlayLabelController::OverlayLabelController(QObject* parent)
    : QObject(parent), m_label(0), m_area(0)
{
}

void OverlayLabelController::setText(const QString& text)
{
    m_text = text;
}

void OverlayLabelController::setArea(QAbstractScrollArea* area)
{
    m_area = area;
    m_area->installEventFilter(this);
}

//! Shows/removes a label from the controlled widget

void OverlayLabelController::setShown(bool shown)
{
    if (shown) {
        ASSERT(m_area);
        if (!m_label) {
            m_label = new OverlayLabelWidget(m_area);
            m_label->setText(m_text);
            updateLabelGeometry();
            m_label->show();
        }

    } else {
        delete m_label;
        m_label = 0;
    }
}

bool OverlayLabelController::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Resize)
        updateLabelGeometry();

    return QObject::eventFilter(obj, event);
}

void OverlayLabelController::updateLabelGeometry()
{
    if (!m_label || !m_area)
        return;
    m_label->setRectangle(QRect(0, 0, m_area->width(), m_area->height()));
    m_label->setPosition(0, 0);
}
