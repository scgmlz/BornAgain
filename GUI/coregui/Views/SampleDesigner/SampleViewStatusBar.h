// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewStatusBar.h
//! @brief     Defines class SampleViewStatusBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWSTATUSBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWSTATUSBAR_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QToolButton;
class QComboBox;

//! Narrow status bar at very bottom of SampleView to access dock menu.

class BA_CORE_API_ SampleViewStatusBar : public QWidget
{
    Q_OBJECT
public:
    SampleViewStatusBar(MainWindow* mainWindow);

signals:
    void dockMenuRequest();

private:
    void initAppearance();

    QToolButton* m_dockMenuButton;
    MainWindow* m_mainWindow;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWSTATUSBAR_H
