// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewDocks.h
//! @brief     Defines class SampleViewDocks
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWDOCKS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWDOCKS_H

#include "GUI/coregui/Views/CommonWidgets/DocksController.h"

class SampleView;
class SampleWidgetBox;
class SampleTreeWidget;
class SamplePropertyWidget;
class SampleDesigner;
class ScriptPanel;
class RealSpacePanel;
class QAction;

//! Holds all docked widgets for SampleView.

class BA_CORE_API_ SampleViewDocks : public DocksController
{
    Q_OBJECT

public:
    enum ESubWindows {
        WIDGET_BOX,
        SAMPLE_TREE,
        PROPERTY_EDITOR,
        INFO,
        REALSPACEPANEL,
        NUMBER_OF_SUB_WINDOWS
    };

    SampleViewDocks(SampleView* parent = nullptr);

    SampleDesigner* sampleDesigner();
    SampleWidgetBox* widgetBox();
    SampleTreeWidget* treeWidget();
    SamplePropertyWidget* propertyWidget();

    void onResetLayout() override;

    void toggleDock(int id);

private:
    SampleDesigner* m_sampleDesigner;
    SampleWidgetBox* m_widgetBox;
    SampleTreeWidget* m_treeWidget;
    SamplePropertyWidget* m_propertyWidget;
    ScriptPanel* m_scriptPanel;
    RealSpacePanel* m_realSpacePanel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEVIEWDOCKS_H
