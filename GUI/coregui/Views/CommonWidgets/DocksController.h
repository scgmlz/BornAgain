// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/DocksController.h
//! @brief     Defines class DocksController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_DOCKSCONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_DOCKSCONTROLLER_H

#include "GUI/coregui/Views/CommonWidgets/DockWidgetInfo.h"
#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <QSize>
#include <map>

namespace Manhattan
{
class FancyMainWindow;
}

//! Handles appearance of docked widgets in the context of FancyMainWindow.

class BA_CORE_API_ DocksController : public QObject
{
    Q_OBJECT

public:
    DocksController(Manhattan::FancyMainWindow* mainWindow);

    void addWidget(int id, QWidget* widget, Qt::DockWidgetArea area);

    virtual void onResetLayout();

    QDockWidget* findDock(int id);

    QDockWidget* findDock(QWidget* widget);

    void show_docks(const std::vector<int>& docks_to_show);

public slots:
    void setDockHeightForWidget(int height);
    void dockToMinMaxSizes();
    void onWidgetCloseRequest();

protected:
    Manhattan::FancyMainWindow* mainWindow();

private:
    struct DockSizeInfo {
        DockSizeInfo() : m_dock(nullptr) {}
        QDockWidget* m_dock;
        QSize m_min_size;
        QSize m_max_size;
    };

    DockWidgetInfo get_info(int id);

    Manhattan::FancyMainWindow* m_mainWindow;
    std::map<int, DockWidgetInfo> m_docks;
    DockSizeInfo m_dock_info;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_DOCKSCONTROLLER_H
