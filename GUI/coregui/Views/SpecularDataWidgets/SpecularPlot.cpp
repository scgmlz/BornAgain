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

#include "SpecularPlot.h"
#include "AxesItems.h"
#include "ColorMapUtils.h"
#include "MathConstants.h"
#include "PlotStatusDescriptors.h"
#include "plot_constants.h"
#include "SpecularDataItem.h"
#include "UpdateTimer.h"

namespace {
const int replot_update_interval = 10;
}

SpecularPlot::SpecularPlot(QWidget* parent)
    : DescriptedPlot(parent)
    , m_custom_plot(new QCustomPlot)
    , m_update_timer(new UpdateTimer(replot_update_interval, this))
    , m_block_update(true)
{
    initPlot();

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_custom_plot);
    setLayout(vlayout);

    setMouseTrackingEnabled(true);
}

std::unique_ptr<IPlotDescriptor> SpecularPlot::plotDescriptor(double xpos, double ypos) const
{
    std::unique_ptr<SpecularPlotDescriptor> result(new SpecularPlotDescriptor);
    if (!specularItem())
        return result;

    result->x() = xpos;
    result->y() = ypos;

    result->inAxesRange() = axesRangeContains(xpos, ypos);
    result->nx() = m_custom_plot->graph()->findBegin(result->x());

    return result;
}

void SpecularPlot::setLog(bool log)
{
    ColorMapUtils::setLogz(m_custom_plot->yAxis, log);
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
            if(item->modelType() == Constants::BasicAxisType ||
               item->modelType() == Constants::AmplitudeAxisType)
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
        QFont(QFont().family(), Constants::plot_tick_label_size));
    m_custom_plot->yAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size));

    m_custom_plot->xAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
    m_custom_plot->yAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));

    ColorMapUtils::setDefaultMargins(m_custom_plot);
}

void SpecularPlot::setConnected(bool isConnected)
{
    setAxesRangeConnected(isConnected);
    setUpdateTimerConnected(isConnected);
}

void SpecularPlot::setAxesRangeConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_custom_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onXaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

        connect(m_custom_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onYaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

    } else {
        disconnect(m_custom_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
                   SLOT(onXaxisRangeChanged(QCPRange)));

        disconnect(m_custom_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
                   SLOT(onYaxisRangeChanged(QCPRange)));
    }
}

void SpecularPlot::setUpdateTimerConnected(bool isConnected)
{
    if (isConnected)
        connect(m_update_timer, SIGNAL(timeToUpdate()), this, SLOT(onTimeToReplot()),
                Qt::UniqueConnection);
    else
        disconnect(m_update_timer, SIGNAL(timeToUpdate()), this, SLOT(onTimeToReplot()));
}

void SpecularPlot::setPlotFromItem(SpecularDataItem* specularItem)
{
    Q_ASSERT(specularItem);

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
    Q_ASSERT(item && axis);
    if(item->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        axis->setLabel(std::move(label));
    else
        axis->setLabel(QString());
}

void SpecularPlot::setDataFromItem(SpecularDataItem* item)
{
    Q_ASSERT(item);
    auto data = item->getOutputData();
    Q_ASSERT(data);
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
    return const_cast<SpecularDataItem*>(
        static_cast<const SpecularPlot*>(this)->specularItem());
}

const SpecularDataItem* SpecularPlot::specularItem() const
{
    const auto result = dynamic_cast<const SpecularDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

void SpecularPlot::modifyAxesProperties(const QString& axisName, const QString& propertyName)
{
    if (m_block_update)
        return;

    if (propertyName == BasicAxisItem::P_TITLE  ||
        propertyName == BasicAxisItem::P_TITLE_IS_VISIBLE) {
        setAxesLabelsFromItem(specularItem());
        replot();
    }

    if (axisName == SpecularDataItem::P_XAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_custom_plot->xAxis->setRange(specularItem()->getLowerX(), specularItem()->getUpperX());
            setAxesRangeConnected(true);
            replot();
        }
    } else if (axisName == SpecularDataItem::P_YAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_custom_plot->yAxis->setRange(specularItem()->getLowerY(), specularItem()->getUpperY());
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
