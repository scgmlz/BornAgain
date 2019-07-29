// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ProjectionsPlot.cpp
//! @brief     Defines class ProjectionCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ProjectionsPlot.h"
#include "qcustomplot.h"
#include "plot_constants.h"
#include "ProjectionItems.h"
#include "SessionItem.h"
#include "ModelMapper.h"
#include "IntensityDataItem.h"
#include "Histogram1D.h"
#include "Histogram2D.h"
#include "MaskItems.h"
#include "ColorMapUtils.h"
#include "AxesItems.h"

ProjectionsPlot::ProjectionsPlot(const QString& projectionType, QWidget* parent)
    : SessionItemWidget(parent)
    , m_projectionType(projectionType)
    , m_customPlot(new QCustomPlot)
    , m_block_plot_update(false)
{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);

    m_customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));
    m_customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));

    ColorMapUtils::setDefaultMargins(m_customPlot);
}

ProjectionsPlot::~ProjectionsPlot()
{
    unsubscribeFromChildren();
}

void ProjectionsPlot::onMarginsChanged(double left, double right)
{
    QMargins orig = m_customPlot->axisRect()->margins();
    m_customPlot->axisRect()->setMargins(QMargins(left, orig.top(), right, orig.bottom()));
    replot();
}

void ProjectionsPlot::subscribeToItem()
{
    // Update projection plot on new item appearance
    projectionContainerItem()->mapper()->setOnChildrenChange(
        [this](SessionItem* item) {
            if(item)
                updateProjections();
        }, this);

    // Remove projection plot
    projectionContainerItem()->mapper()->setOnAboutToRemoveChild(
        [this](SessionItem* item) {
            clearProjection(item);
        }, this);

    // Update projection position
    projectionContainerItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString& name) {
            onProjectionPropertyChanged(item, name);
        }, this);

    // Values of intensity changed, regenerate everything.
    intensityItem()->mapper()->setOnValueChange(
        [this]() {
            updateProjectionsData();
            updateProjections();
        }, this);

    // IntensityItem property (e.g. interpolation changed)
    intensityItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            onIntensityItemPropertyChanged(name);
        }, this);

    // Update to changed IntensityDataItem axes
    intensityItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            if(item->modelType() == Constants::BasicAxisType ||
               item->modelType() == Constants::AmplitudeAxisType)
                onAxisPropertyChanged(item->itemName(), name);
        }, this);

    updateProjectionsData();
    updateProjections();
}

void ProjectionsPlot::unsubscribeFromItem()
{
    unsubscribeFromChildren();
    clearProjections();
}

void ProjectionsPlot::onProjectionPropertyChanged(SessionItem* item, const QString& property)
{
    if(m_block_plot_update)
        return;

    m_block_plot_update = true;

    if (property == HorizontalLineItem::P_POSY || property == VerticalLineItem::P_POSX) {
        if(auto graph = graphForItem(item))
            setGraphFromItem(graph, item);

        replot();
    }

    m_block_plot_update = false;
}

IntensityDataItem* ProjectionsPlot::intensityItem()
{
    IntensityDataItem* result = dynamic_cast<IntensityDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

ProjectionContainerItem* ProjectionsPlot::projectionContainerItem()
{
    ProjectionContainerItem* result = dynamic_cast<ProjectionContainerItem*>(
                intensityItem()->getItem(IntensityDataItem::T_PROJECTIONS));
    Q_ASSERT(result);
    return result;
}

QVector<SessionItem*> ProjectionsPlot::projectionItems()
{
    return projectionContainerItem()->getChildrenOfType(m_projectionType);
}

QCPGraph* ProjectionsPlot::graphForItem(SessionItem* item)
{
    if(item->modelType() != m_projectionType)
        return nullptr;

    QCPGraph *graph = m_item_to_graph[item];
    if (!graph) {
        graph = m_customPlot->addGraph();
        QPen pen;
        pen.setColor(QColor(0, 0, 255, 200));
        graph->setLineStyle(intensityItem()->isInterpolated() ? QCPGraph::lsLine
                                                              : QCPGraph::lsStepCenter);
        graph->setPen(pen);
        m_item_to_graph[item] = graph;
    }

    return graph;
}

void ProjectionsPlot::unsubscribeFromChildren()
{
    if(currentItem())
        projectionContainerItem()->mapper()->unsubscribe(this);
}

//! Creates cached 2D histogram for later projection calculations.

void ProjectionsPlot::updateProjectionsData()
{
    m_hist2d.reset(new Histogram2D(*intensityItem()->getOutputData()));
    updateAxesRange();
    updateAxesTitle();
    setLogz(intensityItem()->isLogz());
}

//! Runs through all projection items and generates missed plots.

void ProjectionsPlot::updateProjections()
{
    if(m_block_plot_update)
        return;

    m_block_plot_update = true;

    for(auto projItem : projectionItems())
        setGraphFromItem(graphForItem(projItem), projItem);

    replot();

    m_block_plot_update = false;
}

//! Updates canva's axes to match current zoom level of IntensityDataItem

void ProjectionsPlot::updateAxesRange()
{
    if (isHorizontalType())
        m_customPlot->xAxis->setRange(ColorMapUtils::itemZoomX(intensityItem()));
    else
        m_customPlot->xAxis->setRange(ColorMapUtils::itemZoomY(intensityItem()));

    m_customPlot->yAxis->setRange(ColorMapUtils::itemDataZoom(intensityItem()));
}

void ProjectionsPlot::updateAxesTitle()
{
    if (isHorizontalType())
        m_customPlot->xAxis->setLabel(intensityItem()->getXaxisTitle());
    else
        m_customPlot->xAxis->setLabel(intensityItem()->getYaxisTitle());
}

//! Clears all graphs corresponding to projection items.

void ProjectionsPlot::clearProjections()
{
    m_block_plot_update = true;

    m_customPlot->clearPlottables();
    m_item_to_graph.clear();

    replot();

    m_block_plot_update = false;
}

//! Removes plot corresponding to given projection item.

void ProjectionsPlot::clearProjection(SessionItem* item)
{
    if (auto graph = graphForItem(item)) {
        m_block_plot_update = true;
        m_customPlot->removePlottable(graph);
        m_item_to_graph.remove(item);
        replot();
        m_block_plot_update = false;
    }
}

//! Updates projection appearance (line style, etc)

void ProjectionsPlot::onIntensityItemPropertyChanged(const QString& propertyName)
{
    if (propertyName == IntensityDataItem::P_IS_INTERPOLATED) {
        setInterpolate(intensityItem()->isInterpolated());
        replot();
    }
}

//! Updates zoom of projections in accordance with IntensityDataItem.

void ProjectionsPlot::onAxisPropertyChanged(const QString& axisName, const QString& propertyName)
{
    Q_UNUSED(axisName);

    if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX)
        updateAxesRange();
    else if (propertyName == BasicAxisItem::P_TITLE)
        updateAxesTitle();
    else if (propertyName == AmplitudeAxisItem::P_IS_LOGSCALE)
        setLogz(intensityItem()->isLogz());

    replot();
}

//! Sets the data to graph from given projection iten.

void ProjectionsPlot::setGraphFromItem(QCPGraph* graph, SessionItem* item)
{
    std::unique_ptr<Histogram1D> hist;

    if (item->modelType() == Constants::HorizontalLineMaskType) {
        double value  = item->getItemValue(HorizontalLineItem::P_POSY).toDouble();
        hist.reset(m_hist2d->projectionX(value));
    } else {
        double value  = item->getItemValue(VerticalLineItem::P_POSX).toDouble();
        hist.reset(m_hist2d->projectionY(value));
    }

    graph->setData(QVector<double>::fromStdVector(hist->getBinCenters()),
                   QVector<double>::fromStdVector(hist->getBinValues()));
}

void ProjectionsPlot::setInterpolate(bool isInterpolated)
{
    for(auto graph : m_item_to_graph)
        graph->setLineStyle(isInterpolated ? QCPGraph::lsLine : QCPGraph::lsStepCenter);
}

void ProjectionsPlot::setLogz(bool isLogz)
{
    ColorMapUtils::setLogz(m_customPlot->yAxis, isLogz);
}

void ProjectionsPlot::replot()
{
    m_customPlot->replot();
}

//! Returns true, if widget is intended for horizontal projections.

bool ProjectionsPlot::isHorizontalType()
{
    return m_projectionType == Constants::HorizontalLineMaskType;
}
