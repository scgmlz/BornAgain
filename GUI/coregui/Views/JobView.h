// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobView.h
//! @brief     Defines class JobView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBVIEW_H

#include "Wrap/WinDllMacros.h"
#include "fancymainwindow.h"

class MainWindow;
class JobViewDocks;
class JobViewStatusBar;
class JobProgressAssistant;
class JobItem;

//! The JobView class is a main view to show list of jobs, job results and widgets for real time
//! and fitting activities.

class BA_CORE_API_ JobView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    JobView(MainWindow* mainWindow);

signals:
    void focusRequest(int);
    void activityChanged(int activity);

public slots:
    void onFocusRequest(JobItem* jobItem);
    void setActivity(int activity);
    void onDockMenuRequest();
    void onSelectionChanged(JobItem* jobItem);

protected:
    virtual void showEvent(QShowEvent* event);
    virtual void hideEvent(QHideEvent* event);

private:
    void connectSignals();
    void connectActivityRelated();
    void connectLayoutRelated();
    void connectJobRelated();

    void setAppropriateActivityForJob(JobItem* jobItem);

    JobViewDocks* m_docks;
    JobViewStatusBar* m_statusBar;
    JobProgressAssistant* m_progressAssistant;
    JobItem* m_currentItem;
    MainWindow* m_mainWindow;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBVIEW_H
