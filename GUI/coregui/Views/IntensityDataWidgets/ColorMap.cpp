// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMap.cpp
//! @brief     Implements class ColorMap
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include "Core/Basics/MathConstants.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Views/CommonWidgets/UpdateTimer.h"
#include "GUI/coregui/Views/FitWidgets/plot_constants.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PlotEventInfo.h"
#include "GUI/coregui/utils/StyleUtils.h"

namespace
{
const int replot_update_interval = 10;
const int colorbar_width_logz = 50;
const int colorbar_width = 80;
} // namespace

ColorMap::ColorMap(QWidget* parent)
    : ScientificPlot(parent, PLOT_TYPE::Plot2D), m_customPlot(new QCustomPlot), m_colorMap(nullptr),
      m_colorScale(nullptr), m_updateTimer(new UpdateTimer(replot_update_interval, this)),
      m_colorBarLayout(new QCPLayoutGrid), m_block_update(true)
{
    initColorMap();

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);

    setMouseTrackingEnabled(true);
    //    setFixedColorMapMargins();
}

QRectF ColorMap::viewportRectangleInWidgetCoordinates()
{
    QCPRange xrange = m_customPlot->xAxis->range();
    QCPRange yrange = m_customPlot->yAxis->range();
    double left = xrange.lower;
    double right = xrange.upper;
    double top = yrange.upper;
    double bottom = yrange.lower;

    return QRectF(xAxisCoordToPixel(left), yAxisCoordToPixel(top),
                  xAxisCoordToPixel(right) - xAxisCoordToPixel(left),
                  yAxisCoordToPixel(bottom) - yAxisCoordToPixel(top));
}

PlotEventInfo ColorMap::eventInfo(double xpos, double ypos) const
{
    PlotEventInfo result(plotType());
    if (!intensityItem())
        return result;

    int nx(0), ny(0);
    m_colorMap->data()->coordToCell(xpos, ypos, &nx, &ny);

    result.setX(xpos);
    result.setY(ypos);
    result.setNx(nx);
    result.setNy(ny);

    result.setInAxesRange(axesRangeContains(xpos, ypos));
    result.setValue(m_colorMap->data()->cell(result.nx(), result.ny()));
    result.setLogValueAxis(intensityItem()->isLogz());

    return result;
}

//! sets logarithmic scale
void ColorMap::setLogz(bool logz)
{
    m_colorBarLayout->setMinimumSize(logz ? colorbar_width_logz : colorbar_width, 10);
    ColorMapUtils::setLogz(m_colorScale, logz);
}

//! reset all axes min,max to initial value
void ColorMap::resetView()
{
    intensityItem()->resetView();
}

void ColorMap::onIntensityModified()
{
    setAxesRangeFromItem(intensityItem());
    setDataFromItem(intensityItem());
    replot();
}

//! updates color map depending on  IntensityDataItem properties
void ColorMap::onPropertyChanged(const QString& property_name)
{
    if (m_block_update)
        return;

    if (property_name == IntensityDataItem::P_GRADIENT) {
        m_colorMap->setGradient(ColorMapUtils::itemGradient(intensityItem()));
        replot();
    } else if (property_name == IntensityDataItem::P_IS_INTERPOLATED) {
        m_colorMap->setInterpolate(intensityItem()->isInterpolated());
        replot();
    } else if (property_name == DataItem::P_AXES_UNITS) {
        setAxesRangeFromItem(intensityItem());
        replot();
    }
}

void ColorMap::onAxisPropertyChanged(const QString& axisName, const QString& propertyName)
{
    if (m_block_update)
        return;

    if (propertyName == BasicAxisItem::P_TITLE
        || propertyName == BasicAxisItem::P_TITLE_IS_VISIBLE) {
        setAxesLabelsFromItem(intensityItem());
        replot();
    }

    if (axisName == IntensityDataItem::P_XAXIS) {
        if (propertyName == BasicAxisItem::P_MIN_DEG || propertyName == BasicAxisItem::P_MAX_DEG) {
            setAxesRangeConnected(false);
            m_customPlot->xAxis->setRange(ColorMapUtils::itemZoomX(intensityItem()));
            setAxesRangeConnected(true);
            replot();
        }
    } else if (axisName == IntensityDataItem::P_YAXIS) {
        if (propertyName == BasicAxisItem::P_MIN_DEG || propertyName == BasicAxisItem::P_MAX_DEG) {
            setAxesRangeConnected(false);
            m_customPlot->yAxis->setRange(ColorMapUtils::itemZoomY(intensityItem()));
            setAxesRangeConnected(true);
            replot();
        }
    }

    else if (axisName == IntensityDataItem::P_ZAXIS) {
        if (propertyName == BasicAxisItem::P_MIN_DEG || propertyName == BasicAxisItem::P_MAX_DEG) {
            setDataRangeFromItem(intensityItem());
            replot();
        } else if (propertyName == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLogz(intensityItem()->isLogz());
            replot();

        } else if (propertyName == BasicAxisItem::P_IS_VISIBLE) {
            setColorScaleVisible(intensityItem()
                                     ->getItem(IntensityDataItem::P_ZAXIS)
                                     ->getItemValue(BasicAxisItem::P_IS_VISIBLE)
                                     .toBool());
            replot();
        }
    }
}

//! Propagate zmin, zmax back to IntensityDataItem
void ColorMap::onDataRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    intensityItem()->setLowerAndUpperZ(newRange.lower, newRange.upper);
    m_block_update = false;
}

//! Propagate xmin, xmax back to IntensityDataItem
void ColorMap::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    intensityItem()->setLowerX(newRange.lower);
    intensityItem()->setUpperX(newRange.upper);
    m_block_update = false;
}

//! Propagate ymin, ymax back to IntensityDataItem
void ColorMap::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    intensityItem()->setLowerY(newRange.lower);
    intensityItem()->setUpperY(newRange.upper);
    m_block_update = false;
}

//! Schedule replot for later execution by onTimeReplot() slot.

void ColorMap::replot()
{
    m_updateTimer->scheduleUpdate();
}

//! Replots ColorMap.

void ColorMap::onTimeToReplot()
{
    m_customPlot->replot();
}

void ColorMap::subscribeToItem()
{
    setColorMapFromItem(intensityItem());

    intensityItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    intensityItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            if (item->modelType() == "BasicAxis" || item->modelType() == "AmplitudeAxis")
                onAxisPropertyChanged(item->itemName(), name);
        },
        this);

    intensityItem()->mapper()->setOnValueChange([this]() { onIntensityModified(); }, this);

    setConnected(true);
}

void ColorMap::unsubscribeFromItem()
{
    setConnected(false);
}

//! creates and initializes the color map
void ColorMap::initColorMap()
{
    m_colorMap = new QCPColorMap(m_customPlot->xAxis, m_customPlot->yAxis);
    m_colorScale = new QCPColorScale(m_customPlot);
    m_colorMap->setColorScale(m_colorScale);

    m_colorBarLayout->addElement(0, 0, m_colorScale);
    m_colorBarLayout->setMinimumSize(colorbar_width_logz, 10);
    auto base_size = StyleUtils::SizeOfLetterM(this).width() * 0.5;
    m_colorBarLayout->setMargins(QMargins(base_size, 0, base_size, 0));

    m_colorScale->axis()->axisRect()->setMargins(QMargins(0, 0, 0, 0));
    m_colorScale->axis()->axisRect()->setAutoMargins(QCP::msNone);

    m_colorScale->setBarWidth(Constants::plot_colorbar_size());
    m_colorScale->axis()->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size()));
    m_customPlot->xAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size()));
    m_customPlot->yAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size()));

    connect(m_customPlot, SIGNAL(afterReplot()), this, SLOT(marginsChangedNotify()));
}

void ColorMap::setConnected(bool isConnected)
{
    setAxesRangeConnected(isConnected);
    setDataRangeConnected(isConnected);
    setUpdateTimerConnected(isConnected);
}

//! Connects/disconnects signals related to ColorMap's X,Y axes rectangle change.

void ColorMap::setAxesRangeConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onXaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

        connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onYaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

    } else {
        disconnect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
                   SLOT(onXaxisRangeChanged(QCPRange)));

        disconnect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
                   SLOT(onYaxisRangeChanged(QCPRange)));
    }
}

//! Connects/disconnects signals related to ColorMap's Z-axis (min,max) change.

void ColorMap::setDataRangeConnected(bool isConnected)
{
    if (isConnected)
        connect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this,
                SLOT(onDataRangeChanged(QCPRange)), Qt::UniqueConnection);
    else
        disconnect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this,
                   SLOT(onDataRangeChanged(QCPRange)));
}

void ColorMap::setUpdateTimerConnected(bool isConnected)
{
    if (isConnected)
        connect(m_updateTimer, SIGNAL(timeToUpdate()), this, SLOT(onTimeToReplot()),
                Qt::UniqueConnection);
    else
        disconnect(m_updateTimer, SIGNAL(timeToUpdate()), this, SLOT(onTimeToReplot()));
}

//! to make fixed margins for whole colormap (change in axes labels wont affect axes rectangle)
void ColorMap::setFixedColorMapMargins()
{
    ColorMapUtils::setDefaultMargins(m_customPlot);
}

//! Sets initial state of ColorMap to match given intensity item.

void ColorMap::setColorMapFromItem(IntensityDataItem* intensityItem)
{
    ASSERT(intensityItem);

    m_block_update = true;

    setAxesRangeFromItem(intensityItem);
    setAxesZoomFromItem(intensityItem);
    setAxesLabelsFromItem(intensityItem);
    setDataFromItem(intensityItem);
    setColorScaleAppearanceFromItem(intensityItem);
    setDataRangeFromItem(intensityItem);

    replot();

    m_block_update = false;
}

//! Sets (xmin,xmax,nbins) and (ymin,ymax,nbins) of ColorMap from intensity item.

void ColorMap::setAxesRangeFromItem(IntensityDataItem* item)
{
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_customPlot->axisRect()->setupFullAxesBox(true);
    m_colorMap->data()->setSize(item->getNbinsX(), item->getNbinsY());
    m_colorMap->data()->setRange(ColorMapUtils::itemXrange(item), ColorMapUtils::itemYrange(item));
}

//! Sets zoom range of X,Y axes as in intensity item.

void ColorMap::setAxesZoomFromItem(IntensityDataItem* item)
{
    setAxesRangeConnected(false);
    m_customPlot->xAxis->setRange(item->getLowerX(), item->getUpperX());
    m_customPlot->yAxis->setRange(item->getLowerY(), item->getUpperY());
    setAxesRangeConnected(true);
}

//! Sets X,Y axes labels from item

void ColorMap::setAxesLabelsFromItem(IntensityDataItem* item)
{
    auto xaxis = item->xAxisItem();
    if (xaxis->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        m_customPlot->xAxis->setLabel(item->getXaxisTitle());
    else
        m_customPlot->xAxis->setLabel(QString());

    m_colorScale->setMargins(QMargins(0, 0, 0, 0));

    auto yaxis = item->yAxisItem();
    if (yaxis->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        m_customPlot->yAxis->setLabel(item->getYaxisTitle());
    else
        m_customPlot->yAxis->setLabel(QString());
}

//! Sets the intensity values to ColorMap.

void ColorMap::setDataFromItem(IntensityDataItem* item)
{
    auto data = item->getOutputData();
    if (!data) {
        m_colorMap->data()->clear();
        return;
    }

    int nx(item->getNbinsX()); // outside of the loop because of slow retrieval
    int ny(item->getNbinsY());
    for (int ix = 0; ix < nx; ++ix)
        for (int iy = 0; iy < ny; ++iy)
            m_colorMap->data()->setCell(ix, iy, (*data)[iy + ny * ix]);
}

//! Sets the appearance of color scale (visibility, gradient type) from intensity item.

void ColorMap::setColorScaleAppearanceFromItem(IntensityDataItem* item)
{
    setColorScaleVisible(item->getItem(IntensityDataItem::P_ZAXIS)
                             ->getItemValue(BasicAxisItem::P_IS_VISIBLE)
                             .toBool());
    m_colorMap->setGradient(ColorMapUtils::itemGradient(intensityItem()));
    m_colorMap->setInterpolate(intensityItem()->isInterpolated());
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they
    // line up):
    QCPMarginGroup* marginGroup = new QCPMarginGroup(m_customPlot);
    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    m_colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
}

void ColorMap::setDataRangeFromItem(IntensityDataItem* item)
{
    setDataRangeConnected(false);
    m_colorMap->setDataRange(ColorMapUtils::itemDataZoom(item));
    setLogz(item->isLogz());
    setDataRangeConnected(true);
}

void ColorMap::setColorScaleVisible(bool visibility_flag)
{
    m_colorBarLayout->setVisible(visibility_flag);
    if (visibility_flag) {
        // add it to the right of the main axis rect
        m_customPlot->plotLayout()->addElement(0, 1, m_colorBarLayout);
    } else {
        m_customPlot->plotLayout()->take(m_colorBarLayout);
        m_customPlot->plotLayout()->simplify();
    }
}

//! Calculates left, right margins around color map to report to projection plot.

void ColorMap::marginsChangedNotify()
{
    QMargins axesMargins = m_customPlot->axisRect()->margins();
    //    QMargins colorBarMargins = m_colorScale->margins();
    //    QMargins colorScaleMargins = m_colorScale->axis()->axisRect()->margins();

    double left = axesMargins.left();
    //    double right = axesMargins.right() + colorBarMargins.right() + m_colorScale->barWidth()
    //            + colorScaleMargins.right() + m_colorBarLayout->rect().width();

    double right = axesMargins.right() + m_colorBarLayout->rect().width();

    emit marginsChanged(left, right);
}

IntensityDataItem* ColorMap::intensityItem()
{
    return const_cast<IntensityDataItem*>(static_cast<const ColorMap*>(this)->intensityItem());
}

const IntensityDataItem* ColorMap::intensityItem() const
{
    return dynamic_cast<const IntensityDataItem*>(currentItem());
}
