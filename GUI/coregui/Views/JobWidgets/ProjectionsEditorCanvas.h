// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorCanvas.h
//! @brief     Defines class ProjectionsEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITORCANVAS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITORCANVAS_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include "Wrap/WinDllMacros.h"
#include <QModelIndex>
#include <QWidget>

class MaskGraphicsScene;
class MaskGraphicsView;
class SessionModel;
class IntensityDataItem;
class ColorMap;
class PlotStatusLabel;
class SessionItem;
class QItemSelectionModel;

//! Holds a graphics scene to draw projections on top of ColorMap. Being a part
//! of ProjectionEditor, provides interaction logic between graphics scene and ProjectionsWidget.

//! Particularly, it creates temporary ProjectionItem in projection container, when mouse
//! is inside ColorMap viewport.

class ProjectionsEditorCanvas : public QWidget
{
    Q_OBJECT

public:
    ProjectionsEditorCanvas(QWidget* parent = 0);

    void setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                    IntensityDataItem* intensityItem);

    void resetContext();

    void setSelectionModel(QItemSelectionModel* model);

    MaskGraphicsScene* getScene() { return m_scene; }

signals:
    void changeActivityRequest(MaskEditorFlags::Activity);
    void deleteSelectedRequest();
    void marginsChanged(double left, double right);

public slots:
    void onEnteringColorMap();
    void onLeavingColorMap();
    void onPositionChanged(double x, double y);
    void onResetViewRequest();
    void onActivityModeChanged(MaskEditorFlags::Activity value);

private:
    void setColorMap(ColorMap* colorMap);
    void setConnected(bool isConnected);

    MaskGraphicsScene* m_scene;
    MaskGraphicsView* m_view;
    ColorMap* m_colorMap;
    PlotStatusLabel* m_statusLabel;

    SessionItem* m_liveProjection; //!< temporary projection item matching mouse move
    SessionModel* m_model;
    QModelIndex m_containerIndex;
    IntensityDataItem* m_intensityDataItem;

    MaskEditorFlags::Activity m_currentActivity;
    bool m_block_update;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITORCANVAS_H
