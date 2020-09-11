// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/DocksController.cpp
//! @brief     Implements class DocksController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/DocksController.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "fancymainwindow.h"
#include <QAbstractItemView>
#include <QAction>
#include <QDockWidget>
#include <QTimer>

DocksController::DocksController(Manhattan::FancyMainWindow* mainWindow)
    : QObject(mainWindow), m_mainWindow(mainWindow)
{
    m_mainWindow->setDocumentMode(true);
    m_mainWindow->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    m_mainWindow->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    m_mainWindow->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void DocksController::addWidget(int id, QWidget* widget, Qt::DockWidgetArea area)
{
    if (m_docks.find(id) != m_docks.end())
        throw GUIHelpers::Error("DocksController::addWidget() -> Error. "
                                "Attempt to add widget id twice");

    auto dock = m_mainWindow->addDockForWidget(widget);
    m_docks[id] = DockWidgetInfo(dock, widget, area);

    QList<QAbstractItemView*> frames = widget->findChildren<QAbstractItemView*>();
    for (int i = 0; i < frames.count(); ++i)
        frames[i]->setFrameStyle(QFrame::NoFrame);
}

void DocksController::onResetLayout()
{
    m_mainWindow->setTrackingEnabled(false);
    QList<QDockWidget*> dockWidgetList = m_mainWindow->dockWidgets();
    for (QDockWidget* dockWidget : dockWidgetList) {
        dockWidget->setFloating(false);
        m_mainWindow->removeDockWidget(dockWidget);
    }

    for (auto& it : m_docks)
        m_mainWindow->addDockWidget(it.second.area(), it.second.dock());

        // Fixes issue: https://bugreports.qt.io/browse/QTBUG-65592
#if QT_VERSION >= 0x050600
    dockWidgetList = m_mainWindow->dockWidgets();
    if (dockWidgetList.size() > 0)
        m_mainWindow->resizeDocks({dockWidgetList.first()}, {10}, Qt::Horizontal);
#endif

    for (QDockWidget* dockWidget : dockWidgetList)
        dockWidget->show();

    m_mainWindow->setTrackingEnabled(true);
}

QDockWidget* DocksController::findDock(int id)
{
    return get_info(id).dock();
}

QDockWidget* DocksController::findDock(QWidget* widget)
{
    for (auto& it : m_docks)
        if (it.second.widget() == widget)
            return it.second.dock();

    throw GUIHelpers::Error("DocksController::findDock() -> Can't find dock for widget");
}

//! Show docks with id's from the list. Other docks will be hidden.

void DocksController::show_docks(const std::vector<int>& docks_to_show)
{
    for (auto& it : m_docks) {
        if (std::find(docks_to_show.begin(), docks_to_show.end(), it.first) != docks_to_show.end())
            it.second.dock()->show();
        else
            it.second.dock()->hide();
    }
}

//! A hack to request update of QDockWidget size if its child (e.g. InfoWidget) wants it.
//! The problem bypassed here is that there is no direct method to QMainWindow to recalculate
//! position of splitters surrounding given QDockWidget. So our child QWidget requests here
//! the change of Min/Max size of QDockWidget, this will trigger recalculation of QDockWidget
//! layout and will force QDockWidget to respect sizeHints provided by ChildWidget. Later (in one
//! single timer shot) we return min/max sizes of QDockWidget back to re-enable splitters
//! functionality.

void DocksController::setDockHeightForWidget(int height)
{
    QWidget* widget = qobject_cast<QWidget*>(sender());
    ASSERT(widget);
    QDockWidget* dock = findDock(widget);
    ASSERT(dock);

    m_dock_info.m_dock = dock;
    m_dock_info.m_min_size = dock->minimumSize();
    m_dock_info.m_max_size = dock->maximumSize();

    if (height > 0) {
        if (dock->height() < height)
            dock->setMinimumHeight(height);
        else
            dock->setMaximumHeight(height);
    }

    QTimer::singleShot(1, this, &DocksController::dockToMinMaxSizes);
}

void DocksController::dockToMinMaxSizes()
{
    ASSERT(m_dock_info.m_dock);
    m_dock_info.m_dock->setMinimumSize(m_dock_info.m_min_size);
    m_dock_info.m_dock->setMaximumSize(m_dock_info.m_max_size);
    m_dock_info.m_dock = nullptr;
}

void DocksController::onWidgetCloseRequest()
{
    QWidget* widget = qobject_cast<QWidget*>(sender());
    ASSERT(widget);
    QDockWidget* dock = findDock(widget);
    ASSERT(dock);

    dock->toggleViewAction()->trigger();
}

Manhattan::FancyMainWindow* DocksController::mainWindow()
{
    return m_mainWindow;
}

DockWidgetInfo DocksController::get_info(int id)
{
    if (m_docks.find(id) == m_docks.end())
        throw GUIHelpers::Error("DocksController::addWidget() -> Error. Non existing id.");

    return m_docks[id];
}
