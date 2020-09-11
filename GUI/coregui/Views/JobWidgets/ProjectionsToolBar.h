// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsToolBar.h
//! @brief     Defines class ProjectionsToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSTOOLBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSTOOLBAR_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include "Wrap/WinDllMacros.h"
#include <QToolBar>

class ProjectionsEditorActions;
class QButtonGroup;

//! Toolbar with projections buttons (horizontal projections, vertical projections, select, zoom)
//! located at the right-hand side of ProjectionsEditor (part of JobProjectionsWidget).

class ProjectionsToolBar : public QToolBar
{
    Q_OBJECT

public:
    ProjectionsToolBar(ProjectionsEditorActions* editorActions, QWidget* parent = 0);

public slots:
    void onChangeActivityRequest(MaskEditorFlags::Activity value);
    void onProjectionTabChange(MaskEditorFlags::Activity value);

signals:
    void activityModeChanged(MaskEditorFlags::Activity);

private slots:
    void onActivityGroupChange(int);

private:
    void setup_selection_group();
    void setup_shapes_group();
    void setup_extratools_group();
    void add_separator();
    MaskEditorFlags::Activity currentActivity() const;
    void setCurrentActivity(MaskEditorFlags::Activity value);

    ProjectionsEditorActions* m_editorActions;
    QButtonGroup* m_activityButtonGroup;
    MaskEditorFlags::Activity m_previousActivity;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSTOOLBAR_H
