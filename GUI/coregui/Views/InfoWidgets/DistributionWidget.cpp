// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/DistributionWidget.cpp
//! @brief     Implements class DistributionWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/DistributionWidget.h"
#include "Core/Parametrization/Distributions.h"
#include "GUI/coregui/Models/DistributionItems.h"
#include "GUI/coregui/Models/RealLimitsItems.h"
#include "GUI/coregui/Views/InfoWidgets/WarningSign.h"
#include "qcustomplot.h"
#include <QLabel>
#include <QVBoxLayout>
#include <algorithm>

namespace
{
const QPair<double, double> default_xrange(-0.1, 0.1);
const QPair<double, double> default_yrange(0.0, 1.1);

QPair<double, double> xRangeForValue(double value);
QPair<double, double> xRangeForValues(double value1, double value2);
QPair<double, double> xRangeForValues(const QVector<double>& xvec);
QPair<double, double> yRangeForValues(const QVector<double>& yvec);
double optimalBarWidth(double xmin, double xmax, int nbars = 1);

} // namespace

DistributionWidget::DistributionWidget(QWidget* parent)
    : QWidget(parent), m_plot(new QCustomPlot), m_item(0), m_label(new QLabel),
      m_resetAction(new QAction(this)), m_warningSign(new WarningSign(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_resetAction->setText("Reset View");
    connect(m_resetAction, SIGNAL(triggered()), this, SLOT(resetView()));

    m_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_label->setStyleSheet("background-color:white;");
    m_label->setMargin(3);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_plot, 1);
    mainLayout->addWidget(m_label);
    setLayout(mainLayout);

    setStyleSheet("background-color:white;");
    connect(m_plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onMousePress(QMouseEvent*)));
    connect(m_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
}

DistributionWidget::~DistributionWidget()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

void DistributionWidget::setItem(DistributionItem* item)
{
    if (m_item == item) {
        return;

    } else {
        if (m_item) {
            disconnect();
            m_item->mapper()->unsubscribe(this);
        }

        m_item = item;
        if (!m_item)
            return;

        plotItem();

        m_item->mapper()->setOnPropertyChange([this](QString) { plotItem(); }, this);

        m_item->mapper()->setOnItemDestroy([this](SessionItem*) { m_item = 0; }, this);
    }
}

void DistributionWidget::plotItem()
{
    init_plot();

    try {
        plot_distributions();

    } catch (const std::exception& ex) {
        init_plot();

        QString message = QString("Wrong parameters\n\n").append(QString::fromStdString(ex.what()));
        m_warningSign->setWarningMessage(message);
    }

    m_plot->replot();
}

//! Generates label with current mouse position.

void DistributionWidget::onMouseMove(QMouseEvent* event)
{
    QPoint point = event->pos();
    double xPos = m_plot->xAxis->pixelToCoord(point.x());
    double yPos = m_plot->yAxis->pixelToCoord(point.y());

    if (m_plot->xAxis->range().contains(xPos) && m_plot->yAxis->range().contains(yPos)) {
        QString text = QString("[x:%1, y:%2]").arg(xPos).arg(yPos);
        m_label->setText(text);
    }
}

void DistributionWidget::onMousePress(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        QPoint point = event->globalPos();
        QMenu menu;
        menu.addAction(m_resetAction);
        menu.exec(point);
    }
}

//! Reset zoom range to initial state.

void DistributionWidget::resetView()
{
    m_plot->xAxis->setRange(m_xRange);
    m_plot->yAxis->setRange(m_yRange);
    m_plot->replot();
}

//! Clears all plottables, resets axes to initial state.

void DistributionWidget::init_plot()
{
    m_warningSign->clear();

    m_plot->clearGraphs();
    m_plot->clearItems();
    m_plot->clearPlottables();
    m_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes
                            | QCP::iSelectLegend | QCP::iSelectPlottables);
    m_plot->yAxis->setLabel("probability");
    m_plot->xAxis2->setVisible(true);
    m_plot->yAxis2->setVisible(true);
    m_plot->xAxis2->setTickLabels(false);
    m_plot->yAxis2->setTickLabels(false);
    m_plot->xAxis2->setTicks(false);
    m_plot->yAxis2->setTicks(false);

    setPlotRange(default_xrange, default_yrange);
}

void DistributionWidget::plot_distributions()
{
    if (m_item->modelType() == "DistributionNone")
        plot_single_value();

    else
        plot_multiple_values();
}

//! Plots a single bar corresponding to the value in DistributionNoteItem.

void DistributionWidget::plot_single_value()
{
    ASSERT(m_item->displayName() == "DistributionNone");

    double value = m_item->getItemValue(DistributionNoneItem::P_MEAN).toDouble();

    QVector<double> xPos = QVector<double>() << value;
    QVector<double> yPos = QVector<double>() << 1.0;
    plotBars(xPos, yPos);

    plotVerticalLine(value, default_yrange.first, value, default_yrange.second);
}

void DistributionWidget::plot_multiple_values()
{
    ASSERT(m_item->displayName() != "DistributionNone");

    int numberOfSamples = m_item->getItemValue(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigmafactor(0.0);
    if (m_item->isTag(DistributionItem::P_SIGMA_FACTOR))
        sigmafactor = m_item->getItemValue(DistributionItem::P_SIGMA_FACTOR).toDouble();

    RealLimits limits;
    if (m_item->isTag(DistributionItem::P_LIMITS)) {
        auto& limitsItem = m_item->groupItem<RealLimitsItem>(DistributionItem::P_LIMITS);
        limits = limitsItem.createRealLimits();
    }
    plotLimits(limits);

    auto dist = m_item->createDistribution();

    // Calculating bars
    std::vector<double> xp = dist->equidistantPoints(numberOfSamples, sigmafactor, limits);
    std::vector<double> yp(xp.size());
    std::transform(xp.begin(), xp.end(), yp.begin(),
                   [&](double value) { return dist->probabilityDensity(value); });
    double sumOfWeights = std::accumulate(yp.begin(), yp.end(), 0.0);
    ASSERT(sumOfWeights != 0.0);

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QVector<double> xBar(xp.begin(), xp.end());
#else
    QVector<double> xBar = QVector<double>::fromStdVector(xp);
#endif

    QVector<double> yBar(xBar.size());
    std::transform(yp.begin(), yp.end(), yBar.begin(),
                   [&](double value) { return value / sumOfWeights; });

    plotBars(xBar, yBar);

    // calculating function points (for interval, bigger than bars)
    auto xRange = xRangeForValues(xBar);
    const int number_of_points = 400;
    std::vector<double> xf =
        dist->equidistantPointsInRange(number_of_points, xRange.first, xRange.second);
    std::vector<double> yf(xf.size());
    std::transform(xf.begin(), xf.end(), yf.begin(),
                   [&](double value) { return dist->probabilityDensity(value); });

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QVector<double> xFunc(xf.begin(), xf.end());
#else
    QVector<double> xFunc = QVector<double>::fromStdVector(xf);
#endif
    QVector<double> yFunc(xFunc.size());
    std::transform(yf.begin(), yf.end(), yFunc.begin(),
                   [&](double value) { return value / sumOfWeights; });

    plotFunction(xFunc, yFunc);
}

void DistributionWidget::setPlotRange(const QPair<double, double>& xRange,
                                      const QPair<double, double>& yRange)
{
    m_xRange = QCPRange(xRange.first, xRange.second);
    m_yRange = QCPRange(yRange.first, yRange.second);
    m_plot->xAxis->setRange(m_xRange);
    m_plot->yAxis->setRange(m_yRange);
}

void DistributionWidget::plotBars(const QVector<double>& xbars, const QVector<double>& ybars)
{
    ASSERT(xbars.size() > 0);

    auto xRange = xRangeForValues(xbars);
    auto yRange = yRangeForValues(ybars);
    setPlotRange(xRange, yRange);

    double barWidth(0.0);
    if (xbars.size() == 1)
        barWidth = optimalBarWidth(xRange.first, xRange.second, xbars.size());
    else
        barWidth = optimalBarWidth(xbars.front(), xbars.back(), xbars.size());

    QCPBars* bars = new QCPBars(m_plot->xAxis, m_plot->yAxis);

    bars->setWidth(barWidth);
    bars->setData(xbars, ybars);
}

void DistributionWidget::plotFunction(const QVector<double>& xFunc, const QVector<double>& yFunc)
{
    auto xRange = xRangeForValues(xFunc);
    auto yRange = yRangeForValues(yFunc);
    setPlotRange(xRange, yRange);

    m_plot->addGraph();
    m_plot->graph(0)->setData(xFunc, yFunc);
}

void DistributionWidget::plotVerticalLine(double xMin, double yMin, double xMax, double yMax,
                                          const QColor& color)
{
    QCPItemLine* line = new QCPItemLine(m_plot);

    QPen pen(color, 1, Qt::DashLine);
    line->setPen(pen);
    line->setSelectable(true);

    line->start->setCoords(xMin, yMin);
    line->end->setCoords(xMax, yMax);
}

//! Plots red line denoting lower and upper limits, if any.

void DistributionWidget::plotLimits(const RealLimits& limits)
{
    if (limits.hasLowerLimit()) {
        double value = limits.lowerLimit();
        plotVerticalLine(value, default_yrange.first, value, default_yrange.second, Qt::red);
    }

    if (limits.hasUpperLimit()) {
        double value = limits.upperLimit();
        plotVerticalLine(value, default_yrange.first, value, default_yrange.second, Qt::red);
    }
}

void DistributionWidget::setXAxisName(const QString& xAxisName)
{
    m_plot->xAxis->setLabel(xAxisName);
}

namespace
{
//! Returns (xmin, xmax) of x-axis to display single value.
QPair<double, double> xRangeForValue(double value)
{
    const double range_factor(0.1);

    double dr = (value == 0.0 ? 1.0 * range_factor : std::abs(value) * range_factor);
    double xmin = value - dr;
    double xmax = value + dr;

    return QPair<double, double>(xmin, xmax);
}

//! Returns (xmin, xmax) of x-axis to display two values.

QPair<double, double> xRangeForValues(double value1, double value2)
{
    const double range_factor(0.1);
    double dr = (value2 - value1) * range_factor;
    ASSERT(dr > 0.0);

    return QPair<double, double>(value1 - dr, value2 + dr);
}

QPair<double, double> xRangeForValues(const QVector<double>& xvec)
{
    ASSERT(!xvec.isEmpty());
    return xvec.size() == 1 ? xRangeForValue(xvec.front())
                            : xRangeForValues(xvec.front(), xvec.back());
}

QPair<double, double> yRangeForValues(const QVector<double>& yvec)
{
    const double range_factor(1.1);
    double ymax = *std::max_element(yvec.begin(), yvec.end());
    return QPair<double, double>(default_yrange.first, ymax * range_factor);
}

//! Returns width of the bar, which will be optimally looking for x-axis range (xmin, xmax)

double optimalBarWidth(double xmin, double xmax, int nbars)
{
    double optimalWidth = (xmax - xmin) / 40.;
    double width = (xmax - xmin) / nbars;

    return optimalWidth < width ? optimalWidth : width;
}

} // namespace
