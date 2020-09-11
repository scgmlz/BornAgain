// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobRealTimeWidget.h
//! @brief     Defines class JobRealTimeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBREALTIMEWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBREALTIMEWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/ItemStackPresenter.h"

class JobModel;
class JobItem;
class ParameterTuningWidget;

//! The JobRealTimeWidget class provides tuning of sample parameters in real time.
//! Located on the right side of JobView and is visible when realtime activity is selected.

class BA_CORE_API_ JobRealTimeWidget : public QWidget
{
    Q_OBJECT
public:
    JobRealTimeWidget(JobModel* jobModel, QWidget* parent = nullptr);

    ParameterTuningWidget* parameterTuningWidget(JobItem* jobItem);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void setItem(JobItem* jobItem);

private:
    bool isValidJobItem(JobItem* item);

    ItemStackPresenter<ParameterTuningWidget>* m_stackedWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBREALTIMEWIDGET_H
