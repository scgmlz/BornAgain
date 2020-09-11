// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/Plot1D.cpp
//! @brief     Implements class Plot1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/Plot1D.h"
#include "Core/Basics/MathConstants.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DataProperties.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Views/CommonWidgets/UpdateTimer.h"
#include "GUI/coregui/Views/FitWidgets/plot_constants.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PlotEventInfo.h"

namespace
{
const int replot_update_interval = 10;

int getBin(double x, const QCPGraph* graph);
} // namespace

Plot1D::Plot1D(QWidget* parent)
    : ScientificPlot(parent, PLOT_TYPE::Plot1D), m_custom_plot(new QCustomPlot),
      m_update_timer(new UpdateTimer(replot_update_interval, this)), m_block_update(false)
{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_custom_plot);
    setLayout(vlayout);

    m_custom_plot->xAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size()));
    m_custom_plot->yAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size()));

    setMouseTrackingEnabled(true);
}

PlotEventInfo Plot1D::eventInfo(double xpos, double ypos) const
{
    PlotEventInfo result(plotType());
    if (!viewItem())
        return result;

    result.setX(xpos);
    result.setValue(ypos);

    result.setInAxesRange(axesRangeContains(xpos, ypos));
    result.setNx(getBin(result.x(), m_custom_plot->graph()));

    return result;
}

void Plot1D::setLog(bool log)
{
    ColorMapUtils::setLogz(m_custom_plot->yAxis, log);
    ColorMapUtils::setLogz(m_custom_plot->yAxis2, log);
}

void Plot1D::resetView()
{
    viewItem()->resetView();
}

void Plot1D::onPropertyChanged(const QString& property_name)
{
    if (m_block_update)
        return;

    if (property_name == Data1DViewItem::P_AXES_UNITS) {
        setAxesRangeFromItem(viewItem());
        updateAllGraphs();
        replot();
    }
}

void Plot1D::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    viewItem()->setLowerX(newRange.lower);
    viewItem()->setUpperX(newRange.upper);
    m_block_update = false;
}

void Plot1D::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    viewItem()->setLowerY(newRange.lower);
    viewItem()->setUpperY(newRange.upper);
    m_block_update = false;
}

void Plot1D::onTimeToReplot()
{
    m_custom_plot->replot();
}

void Plot1D::subscribeToItem()
{
    initPlots();
    refreshPlotData();

    viewItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    viewItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            if (dynamic_cast<BasicAxisItem*>(item))
                modifyAxesProperties(item->itemName(), name);
        },
        this);

    std::for_each(m_graph_map.begin(), m_graph_map.end(), [caller = this](auto pair) {
        auto property_item = pair.first;
        property_item->dataItem()->mapper()->setOnValueChange(
            [caller]() { caller->refreshPlotData(); }, caller);
    });

    setConnected(true);
}

void Plot1D::unsubscribeFromItem()
{
    m_custom_plot->clearGraphs();
    std::for_each(m_graph_map.begin(), m_graph_map.end(), [caller = this](auto pair) {
        pair.first->dataItem()->mapper()->unsubscribe(caller);
    });
    m_graph_map.clear();
    setConnected(false);
}

void Plot1D::initPlots()
{
    auto property_items = viewItem()->propertyContainerItem()->propertyItems();
    std::for_each(property_items.begin(), property_items.end(), [this](Data1DProperties* item) {
        auto graph = m_custom_plot->addGraph();
        graph->setLineStyle(QCPGraph::lsLine);
        graph->setPen(QPen(item->color()));
        m_graph_map[item] = graph;
    });
}

void Plot1D::setConnected(bool isConnected)
{
    setAxesRangeConnected(isConnected);
    setUpdateTimerConnected(isConnected);
}

void Plot1D::setAxesRangeConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_custom_plot->xAxis,
                static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                &Plot1D::onXaxisRangeChanged, Qt::UniqueConnection);

        connect(m_custom_plot->yAxis,
                static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                &Plot1D::onYaxisRangeChanged, Qt::UniqueConnection);

    } else {
        disconnect(m_custom_plot->xAxis,
                   static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                   &Plot1D::onXaxisRangeChanged);

        disconnect(m_custom_plot->yAxis,
                   static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                   &Plot1D::onYaxisRangeChanged);
    }
}

void Plot1D::setUpdateTimerConnected(bool isConnected)
{
    if (isConnected)
        connect(m_update_timer, &UpdateTimer::timeToUpdate, this, &Plot1D::onTimeToReplot,
                Qt::UniqueConnection);
    else
        disconnect(m_update_timer, &UpdateTimer::timeToUpdate, this, &Plot1D::onTimeToReplot);
}

void Plot1D::refreshPlotData()
{
    if (m_block_update)
        return;

    m_block_update = true;

    auto view_item = viewItem();
    ASSERT(view_item);

    setAxesRangeFromItem(view_item);
    setAxesLabelsFromItem(view_item);
    updateAllGraphs();

    replot();

    m_block_update = false;
}

void Plot1D::setAxesRangeFromItem(Data1DViewItem* item)
{
    m_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_custom_plot->axisRect()->setupFullAxesBox(true);

    setAxesRangeConnected(false);
    m_custom_plot->xAxis->setRange(item->getLowerX(), item->getUpperX());
    m_custom_plot->yAxis->setRange(item->getLowerY(), item->getUpperY());
    setLog(item->isLog());
    setAxesRangeConnected(true);
}

void Plot1D::setAxesLabelsFromItem(Data1DViewItem* item)
{
    setLabel(item->xAxisItem(), m_custom_plot->xAxis, item->getXaxisTitle());
    setLabel(item->yAxisItem(), m_custom_plot->yAxis, item->getYaxisTitle());
}

void Plot1D::setLabel(const BasicAxisItem* item, QCPAxis* axis, QString label)
{
    ASSERT(item && axis);
    if (item->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        axis->setLabel(std::move(label));
    else
        axis->setLabel(QString());
}

void Plot1D::updateAllGraphs()
{
    auto property_items = viewItem()->propertyContainerItem()->propertyItems();
    std::for_each(property_items.begin(), property_items.end(),
                  [this](Data1DProperties* item) { updateGraph(item); });
}

void Plot1D::updateGraph(Data1DProperties* item)
{
    auto data_points = viewItem()->graphData(item);

    auto graph = m_graph_map.at(item);
    graph->setData(data_points.first, data_points.second, /*sorted =*/true);
}

Data1DViewItem* Plot1D::viewItem()
{
    return const_cast<Data1DViewItem*>(static_cast<const Plot1D*>(this)->viewItem());
}

const Data1DViewItem* Plot1D::viewItem() const
{
    const auto result = dynamic_cast<const Data1DViewItem*>(currentItem());
    ASSERT(result);
    return result;
}

void Plot1D::modifyAxesProperties(const QString& axisName, const QString& propertyName)
{
    if (m_block_update)
        return;

    if (propertyName == BasicAxisItem::P_TITLE
        || propertyName == BasicAxisItem::P_TITLE_IS_VISIBLE) {
        setAxesLabelsFromItem(viewItem());
        replot();
    }

    if (axisName == Data1DViewItem::P_XAXIS) {
        if (propertyName == BasicAxisItem::P_MIN_DEG || propertyName == BasicAxisItem::P_MAX_DEG) {
            setAxesRangeConnected(false);
            m_custom_plot->xAxis->setRange(viewItem()->getLowerX(), viewItem()->getUpperX());
            setAxesRangeConnected(true);
            replot();
        }
    } else if (axisName == Data1DViewItem::P_YAXIS) {
        if (propertyName == BasicAxisItem::P_MIN_DEG || propertyName == BasicAxisItem::P_MAX_DEG) {
            setAxesRangeConnected(false);
            m_custom_plot->yAxis->setRange(viewItem()->getLowerY(), viewItem()->getUpperY());
            setAxesRangeConnected(true);
            replot();
        } else if (propertyName == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLog(viewItem()->isLog());
            replot();
        }
    }
}

void Plot1D::replot()
{
    m_update_timer->scheduleUpdate();
}

namespace
{
int getBin(double x, const QCPGraph* graph)
{
    const int key_start = graph->findBegin(x);
    const int key_end = graph->findBegin(x, false); // false = do not expand range
    if (key_end == key_start || key_end == graph->dataCount())
        return key_start;
    return (x - graph->dataSortKey(key_start)) <= (graph->dataSortKey(key_end) - x) ? key_start
                                                                                    : key_end;
}
} // namespace
