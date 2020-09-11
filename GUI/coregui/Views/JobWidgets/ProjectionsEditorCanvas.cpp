// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorCanvas.cpp
//! @brief     Implements class ProjectionsEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/ProjectionsEditorCanvas.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PlotStatusLabel.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlotEvent.h"
#include "GUI/coregui/Views/MaskWidgets/MaskGraphicsScene.h"
#include "GUI/coregui/Views/MaskWidgets/MaskGraphicsView.h"
#include <QItemSelectionModel>
#include <QVBoxLayout>

ProjectionsEditorCanvas::ProjectionsEditorCanvas(QWidget* parent)
    : QWidget(parent), m_scene(new MaskGraphicsScene(this)), m_view(new MaskGraphicsView(m_scene)),
      m_colorMap(nullptr), m_statusLabel(new PlotStatusLabel(nullptr, this)),
      m_liveProjection(nullptr), m_model(nullptr), m_intensityDataItem(nullptr),
      m_currentActivity(MaskEditorFlags::HORIZONTAL_LINE_MODE), m_block_update(false)
{
    setObjectName("MaskEditorCanvas");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(m_statusLabel);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    connect(m_view, SIGNAL(changeActivityRequest(MaskEditorFlags::Activity)), this,
            SIGNAL(changeActivityRequest(MaskEditorFlags::Activity)));
    connect(m_view, SIGNAL(deleteSelectedRequest()), this, SIGNAL(deleteSelectedRequest()));
}

void ProjectionsEditorCanvas::setContext(SessionModel* model,
                                         const QModelIndex& shapeContainerIndex,
                                         IntensityDataItem* intensityItem)
{
    m_model = model;
    m_scene->setMaskContext(model, shapeContainerIndex, intensityItem);
    m_view->updateSize(m_view->size());

    m_containerIndex = shapeContainerIndex;
    m_intensityDataItem = intensityItem;

    setColorMap(m_scene->colorMap());

    getScene()->onActivityModeChanged(m_currentActivity);
}

void ProjectionsEditorCanvas::resetContext()
{
    m_intensityDataItem = nullptr;
    m_containerIndex = {};
    setConnected(false);
    m_colorMap = nullptr;
    m_scene->resetContext();
}

void ProjectionsEditorCanvas::setSelectionModel(QItemSelectionModel* model)
{
    getScene()->setSelectionModel(model);
}

void ProjectionsEditorCanvas::onEnteringColorMap()
{
    if (m_liveProjection || m_block_update)
        return;

    m_block_update = true;

    if (m_currentActivity == MaskEditorFlags::HORIZONTAL_LINE_MODE)
        m_liveProjection = m_model->insertNewItem("HorizontalLineMask", m_containerIndex);
    else if (m_currentActivity == MaskEditorFlags::VERTICAL_LINE_MODE)
        m_liveProjection = m_model->insertNewItem("VerticalLineMask", m_containerIndex);

    if (m_liveProjection)
        m_liveProjection->setItemValue(MaskItem::P_IS_VISIBLE, false);

    m_block_update = false;
}

void ProjectionsEditorCanvas::onLeavingColorMap()
{
    if (m_block_update)
        return;

    m_block_update = true;

    if (m_liveProjection) {
        m_liveProjection->parent()->takeRow(
            m_liveProjection->parent()->rowOfChild(m_liveProjection));
        delete m_liveProjection;
        m_liveProjection = nullptr;
    }

    m_block_update = false;
}

void ProjectionsEditorCanvas::onPositionChanged(double x, double y)
{
    if (m_block_update)
        return;

    m_block_update = true;

    if (m_liveProjection) {
        if (m_currentActivity == MaskEditorFlags::HORIZONTAL_LINE_MODE)
            m_liveProjection->setItemValue(HorizontalLineItem::P_POSY, y);
        else if (m_currentActivity == MaskEditorFlags::VERTICAL_LINE_MODE)
            m_liveProjection->setItemValue(VerticalLineItem::P_POSX, x);
    }

    m_block_update = false;
}

void ProjectionsEditorCanvas::onResetViewRequest()
{
    m_view->onResetViewRequest();
    m_intensityDataItem->resetView();
}

void ProjectionsEditorCanvas::onActivityModeChanged(MaskEditorFlags::Activity value)
{
    m_currentActivity = value;
    getScene()->onActivityModeChanged(value);
    onLeavingColorMap();
}

void ProjectionsEditorCanvas::setColorMap(ColorMap* colorMap)
{
    ASSERT(colorMap);
    setConnected(false);

    m_colorMap = colorMap;
    setConnected(true);

    m_statusLabel->reset();
    m_statusLabel->addPlot(colorMap);
}

void ProjectionsEditorCanvas::setConnected(bool isConnected)
{
    if (!m_colorMap)
        return;

    if (isConnected) {
        connect(m_colorMap->plotEvent(), &ScientificPlotEvent::enteringPlot, this,
                &ProjectionsEditorCanvas::onEnteringColorMap, Qt::UniqueConnection);
        connect(m_colorMap->plotEvent(), &ScientificPlotEvent::leavingPlot, this,
                &ProjectionsEditorCanvas::onLeavingColorMap, Qt::UniqueConnection);
        connect(m_colorMap->plotEvent(), &ScientificPlotEvent::positionChanged, this,
                &ProjectionsEditorCanvas::onPositionChanged, Qt::UniqueConnection);
        connect(m_colorMap, &ColorMap::marginsChanged, this,
                &ProjectionsEditorCanvas::marginsChanged, Qt::UniqueConnection);
    }

    else {
        disconnect(m_colorMap->plotEvent(), &ScientificPlotEvent::enteringPlot, this,
                   &ProjectionsEditorCanvas::onEnteringColorMap);
        disconnect(m_colorMap->plotEvent(), &ScientificPlotEvent::leavingPlot, this,
                   &ProjectionsEditorCanvas::onLeavingColorMap);
        disconnect(m_colorMap->plotEvent(), &ScientificPlotEvent::positionChanged, this,
                   &ProjectionsEditorCanvas::onPositionChanged);
        disconnect(m_colorMap, &ColorMap::marginsChanged, this,
                   &ProjectionsEditorCanvas::marginsChanged);
    }
}
