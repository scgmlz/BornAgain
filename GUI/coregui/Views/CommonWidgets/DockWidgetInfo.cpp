// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/DockWidgetInfo.cpp
//! @brief     Implements class DockWidgetInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/DockWidgetInfo.h"
#include <QDockWidget>
#include <QWidget>

DockWidgetInfo::DockWidgetInfo() : m_dock(nullptr), m_widget(nullptr), m_area(Qt::NoDockWidgetArea)
{
}

DockWidgetInfo::DockWidgetInfo(QDockWidget* dock, QWidget* widget, Qt::DockWidgetArea area)
    : m_dock(dock), m_widget(widget), m_area(area)
{
}

QDockWidget* DockWidgetInfo::dock()
{
    return m_dock;
}

QWidget* DockWidgetInfo::widget()
{
    return m_widget;
}

Qt::DockWidgetArea DockWidgetInfo::area()
{
    return m_area;
}
