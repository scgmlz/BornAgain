// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobOutputDataWidget.h
//! @brief     Defines class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBOUTPUTDATAWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBOUTPUTDATAWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/ItemStackPresenter.h"

class JobResultsPresenter;
class JobModel;
class JobItem;

//! The JobOutputDataWidget class is a central widget of JobView, shows results of the simulation.

class BA_CORE_API_ JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    JobOutputDataWidget(JobModel* jobModel, QWidget* parent = nullptr);

public slots:
    void setItem(JobItem* jobItem);
    void onActivityChanged(int activity);

protected:
    virtual bool isValidJobItem(JobItem* item);

private:
    ItemStackPresenter<JobResultsPresenter>* m_stackedWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBOUTPUTDATAWIDGET_H
