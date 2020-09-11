// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorToolBar.h
//! @brief     Defines class JobSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORTOOLBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORTOOLBAR_H

#include "GUI/coregui/mainwindow/StyledToolBar.h"

class QAction;
class QToolButton;
class JobSelectorActions;

//! Styled tool bar on top of JobSelector with run/remove job buttons.

class BA_CORE_API_ JobSelectorToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit JobSelectorToolBar(JobSelectorActions* actions, QWidget* parent = nullptr);

private:
    QToolButton* m_runJobButton;
    QToolButton* m_removeJobButton;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORTOOLBAR_H
