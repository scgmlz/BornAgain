// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewStatusBar.h
//! @brief     Defines class JobViewStatusBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWSTATUSBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWSTATUSBAR_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QToolButton;
class QComboBox;

//! Narrow status bar at very bottom of JobView to switch between activities.
//! Added to the status bar of MainWindow when JobView is shown.

class BA_CORE_API_ JobViewStatusBar : public QWidget
{
    Q_OBJECT
public:
    JobViewStatusBar(MainWindow* mainWindow);

signals:
    void toggleJobSelectorRequest();
    void changeActivityRequest(int);
    void dockMenuRequest();

public slots:
    void onActivityChanged(int activity);

private:
    void initAppearance();

    QToolButton* m_toggleJobListButton;
    QComboBox* m_activityCombo;
    QToolButton* m_dockMenuButton;
    MainWindow* m_mainWindow;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWSTATUSBAR_H
