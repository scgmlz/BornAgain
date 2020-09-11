// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitActivityPanel.h
//! @brief     Defines class FitActivityPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITACTIVITYPANEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITACTIVITYPANEL_H

#include "GUI/coregui/Views/CommonWidgets/ItemStackPresenter.h"
#include <QWidget>

class JobModel;
class JobItem;
class FitSessionWidget;
class JobRealTimeWidget;
class RunFitControlWidget;
class JobMessagePanel;
class FitSessionManager;

//! The FitActivityPanel class is a main widget to run the fitting.
//! Occupies bottom right corner of JobView, contains stack of FitSuiteWidgets for every
//! JobItem which is suitable for fitting.

class BA_CORE_API_ FitActivityPanel : public QWidget
{
    Q_OBJECT
public:
    FitActivityPanel(JobModel* jobModel, QWidget* parent = 0);

    void setRealTimeWidget(JobRealTimeWidget* realTimeWidget);
    void setJobMessagePanel(JobMessagePanel* jobMessagePanel);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void setItem(JobItem* item);

private:
    bool isValidJobItem(JobItem* item);
    FitSessionWidget* currentFitSuiteWidget();

    ItemStackPresenter<FitSessionWidget>* m_stackedWidget;
    JobRealTimeWidget* m_realTimeWidget;
    JobMessagePanel* m_jobMessagePanel;
    FitSessionManager* m_fitSessionManager;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITACTIVITYPANEL_H
