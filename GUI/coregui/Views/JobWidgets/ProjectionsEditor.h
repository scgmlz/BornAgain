// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditor.h
//! @brief     Defines class ProjectionsEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITOR_H

#include "Wrap/WinDllMacros.h"
#include <QMainWindow>

class SessionModel;
class QModelIndex;
class IntensityDataItem;
class ProjectionsToolBar;
class ProjectionsEditorActions;
class ProjectionsActions;
class ProjectionsEditorCanvas;
class ProjectionsPropertyPanel;
class ProjectionsWidget;
class QItemSelectionModel;
class QSplitter;
namespace Manhattan
{
class MiniSplitter;
}

//! Editor to draw projections on top of intensity plot. Part of

class BA_CORE_API_ ProjectionsEditor : public QMainWindow
{
    Q_OBJECT

public:
    ProjectionsEditor(QWidget* parent = nullptr);

    void setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                    IntensityDataItem* intensityItem);

    void resetContext();

    QList<QAction*> topToolBarActions();

private:
    void setup_connections();

    ProjectionsEditorActions* m_editorActions;
    ProjectionsToolBar* m_toolBar;                //! main tool bar with bottoms at the right
    ProjectionsEditorCanvas* m_projectionsCanvas; //! canvas with color map at the top
    ProjectionsWidget* m_projectionsWidget;       //! bottom widget to draw projections plot
    ProjectionsPropertyPanel* m_propertyPanel;    //! pannel at the right with properties
    QItemSelectionModel* m_selectionModel;
    Manhattan::MiniSplitter* m_rightSplitter;
    QSplitter* m_bottomSplitter;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITOR_H
