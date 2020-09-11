// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewActivities.h
//! @brief     Defines class JobViewActivities
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWACTIVITIES_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWACTIVITIES_H

#include "GUI/coregui/Views/JobWidgets/JobViewFlags.h"
#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QStringList>
#include <QVector>

//! The JobViewActivities class is a helper static class to get info related to JobView activities
//! (JobViewActivity, RealTimeActivity and FittingActivity).

class BA_CORE_API_ JobViewActivities
{

public:
    using activity_map_t = QMap<JobViewFlags::Activity, QVector<JobViewFlags::Dock>>;

    static QStringList activityList();

    static QVector<JobViewFlags::Dock> activeDocks(JobViewFlags::Activity activity);

private:
    static activity_map_t m_activityToDocks;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWACTIVITIES_H
