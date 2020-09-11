// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewFlags.h
//! @brief     Defines class JobViewFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWFLAGS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWFLAGS_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

//! The JobViewFlags class is a namespace for various flags used in JobView.

class JobViewFlags
{
public:
    enum EDocksId {
        JOB_LIST_DOCK,
        REAL_TIME_DOCK,
        FIT_PANEL_DOCK,
        JOB_MESSAGE_DOCK,
        NUMBER_OF_DOCKS
    };
    Q_DECLARE_FLAGS(Dock, EDocksId)

    enum EActivities {
        JOB_VIEW_ACTIVITY,
        REAL_TIME_ACTIVITY,
        FITTING_ACTIVITY,
    };
    Q_DECLARE_FLAGS(Activity, EActivities)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(JobViewFlags::Dock)
Q_DECLARE_OPERATORS_FOR_FLAGS(JobViewFlags::Activity)

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBVIEWFLAGS_H
