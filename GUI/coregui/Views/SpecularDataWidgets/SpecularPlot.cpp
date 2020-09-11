// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlot.cpp
//! @brief     Implements class SpecularPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SpecularDataWidgets/SpecularPlot.h"
#include "Core/Basics/MathConstants.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Views/CommonWidgets/UpdateTimer.h"
#include "GUI/coregui/Views/FitWidgets/plot_constants.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PlotEventInfo.h"

namespace
{
const int replot_update_interval = 10;

int getBin(double x, const QCPGraph* graph);
} // namespace

SpecularPlot::SpecularPlot(QWidget* parent)
    : ScientificPlot(parent, PLOT_TYPE::Plot1D), m_custom_plot(new QCustomPlot),
      m_update_timer(new UpdateTimer(replot_update_interval, this)), m_block_update(true)
{
    initPlot();

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_custom_plot);
    setLayout(vlayout);

    setMouseTrackingEnabled(true);
}

PlotEventInfo SpecularPlot::eventInfo(double xpos, double ypos) const
{
    PlotEventInfo result(plotType());
    if (!specularItem())
        return result;

    result.setX(xpos);
    result.setValue(ypos);

    result.setInAxesRange(axesRangeContains(xpos, ypos));
    result.setNx(getBin(result.x(), m_custom_plot->graph()));

    return result;
}

void SpecularPlot::setLog(bool log)
{
    ColorMapUtils::setLogz(m_custom_plot->yAxis, log);
    ColorMapUtils::setLogz(m_custom_plot->yAxis2, log);
}

void SpecularPlot::resetView()
{
    specularItem()->resetView();
}

void SpecularPlot::onPropertyChanged(const QString& property_name)
{
    if (m_block_update)
        return;

    if (property_name == DataItem::P_AXES_UNITS) {
        setAxesRangeFromItem(specularItem());
        replot();
    }
}

void SpecularPlot::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    specularItem()->setLowerX(newRange.lower);
    specularItem()->setUpperX(newRange.upper);
    m_block_update = false;
}

void SpecularPlot::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    specularItem()->setLowerY(newRange.lower);
    specularItem()->setUpperY(newRange.upper);
    m_block_update = false;
}

void SpecularPlot::onTimeToReplot()
{
    m_custom_plot->replot();
}

void SpecularPlot::subscribeToItem()
{
    setPlotFromItem(specularItem());

    specularItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    specularItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            if (item->modelType() == "BasicAxis" || item->modelType() == "AmplitudeAxis")
                modifyAxesProperties(item->itemName(), name);
        },
        this);

    specularItem()->mapper()->setOnValueChange([this]() { setPlotFromItem(this->specularItem()); },
                                               this);

    setConnected(true);
}

void SpecularPlot::unsubscribeFromItem()
{
    setConnected(false);
}

void SpecularPlot::initPlot()
{
    m_custom_plot->addGraph();

    QPen pen(QColor(0, 0, 255, 200));
    m_custom_plot->graph()->setLineStyle(QCPGraph::lsLine);
    m_custom_plot->graph()->setPen(pen);

    m_custom_plot->xAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size()));
    m_custom_plot->yAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size()));
}

void SpecularPlot::setConnected(bool isConnected)
{
    setAxesRangeConnected(isConnected);
    setUpdateTimerConnected(isConnected);
}

void SpecularPlot::setAxesRangeConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_custom_plot->xAxis,
                static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                &SpecularPlot::onXaxisRangeChanged, Qt::UniqueConnection);

        connect(m_custom_plot->yAxis,
                static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                &SpecularPlot::onYaxisRangeChanged, Qt::UniqueConnection);

    } else {
        disconnect(m_custom_plot->xAxis,
                   static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                   &SpecularPlot::onXaxisRangeChanged);

        disconnect(m_custom_plot->yAxis,
                   static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                   &SpecularPlot::onYaxisRangeChanged);
    }
}

void SpecularPlot::setUpdateTimerConnected(bool isConnected)
{
    if (isConnected)
        connect(m_update_timer, &UpdateTimer::timeToUpdate, this, &SpecularPlot::onTimeToReplot,
                Qt::UniqueConnection);
    else
        disconnect(m_update_timer, &UpdateTimer::timeToUpdate, this, &SpecularPlot::onTimeToReplot);
}

void SpecularPlot::setPlotFromItem(SpecularDataItem* specularItem)
{
    ASSERT(specularItem);

    m_block_update = true;

    m_custom_plot->graph(0)->data()->clear();
    setAxesRangeFromItem(specularItem);
    setAxesLabelsFromItem(specularItem);
    setDataFromItem(specularItem);

    replot();

    m_block_update = false;
}

void SpecularPlot::setAxesRangeFromItem(SpecularDataItem* item)
{
    m_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_custom_plot->axisRect()->setupFullAxesBox(true);

    setAxesRangeConnected(false);
    m_custom_plot->xAxis->setRange(item->getLowerX(), item->getUpperX());
    m_custom_plot->yAxis->setRange(item->getLowerY(), item->getUpperY());
    setLog(item->isLog());
    setAxesRangeConnected(true);
}

void SpecularPlot::setAxesLabelsFromItem(SpecularDataItem* item)
{
    setLabel(item->xAxisItem(), m_custom_plot->xAxis, item->getXaxisTitle());
    setLabel(item->yAxisItem(), m_custom_plot->yAxis, item->getYaxisTitle());
}

void SpecularPlot::setLabel(const BasicAxisItem* item, QCPAxis* axis, QString label)
{
    ASSERT(item && axis);
    if (item->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        axis->setLabel(std::move(label));
    else
        axis->setLabel(QString());
}

void SpecularPlot::setDataFromItem(SpecularDataItem* item)
{
    ASSERT(item);
    auto data = item->getOutputData();
    if (!data)
        return;

    for (size_t i = 0, size = data->getAllocatedSize(); i < size; ++i) {
        double x = data->getAxisValue(i, 0);
        double y = data->operator[](i);
        m_custom_plot->graph()->addData(x, y);
    }
}

SpecularDataItem* SpecularPlot::specularItem()
{
    return const_cast<SpecularDataItem*>(static_cast<const SpecularPlot*>(this)->specularItem());
}

const SpecularDataItem* SpecularPlot::specularItem() const
{
    const auto result = dynamic_cast<const SpecularDataItem*>(currentItem());
    return result;
}

void SpecularPlot::modifyAxesProperties(const QString& axisName, const QString& propertyName)
{
    if (m_block_update)
        return;

    if (propertyName == BasicAxisItem::P_TITLE
        || propertyName == BasicAxisItem::P_TITLE_IS_VISIBLE) {
        setAxesLabelsFromItem(specularItem());
        replot();
    }

    if (axisName == SpecularDataItem::P_XAXIS) {
        if (propertyName == BasicAxisItem::P_MIN_DEG || propertyName == BasicAxisItem::P_MAX_DEG) {
            setAxesRangeConnected(false);
            m_custom_plot->xAxis->setRange(specularItem()->getLowerX(),
                                           specularItem()->getUpperX());
            setAxesRangeConnected(true);
            replot();
        }
    } else if (axisName == SpecularDataItem::P_YAXIS) {
        if (propertyName == BasicAxisItem::P_MIN_DEG || propertyName == BasicAxisItem::P_MAX_DEG) {
            setAxesRangeConnected(false);
            m_custom_plot->yAxis->setRange(specularItem()->getLowerY(),
                                           specularItem()->getUpperY());
            setAxesRangeConnected(true);
            replot();
        } else if (propertyName == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLog(specularItem()->isLog());
            replot();
        }
    }
}

void SpecularPlot::replot()
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
