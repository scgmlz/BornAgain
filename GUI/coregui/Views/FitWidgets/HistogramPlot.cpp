// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/HistogramPlot.cpp
//! @brief     Implements class HistogramPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "HistogramPlot.h"
#include "plot_constants.h"

HistogramPlot::HistogramPlot(QWidget* parent) : QWidget(parent), m_customPlot(new QCustomPlot)

{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);
    setStyleSheet("background-color:white;");

    initGraph();

    m_customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));
    m_customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));

    m_customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    m_customPlot->yAxis->setNumberFormat("eb");
    m_customPlot->yAxis->setNumberPrecision(0);

    m_customPlot->xAxis->setLabel("iteration");
    m_customPlot->yAxis->setLabel("chi2");

    m_customPlot->xAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
    m_customPlot->yAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
}

void HistogramPlot::addData(double x, double y)
{
    m_customPlot->graph()->addData(x, y);
    m_customPlot->graph()->rescaleAxes();
    m_customPlot->replot();
}

void HistogramPlot::addData(const QVector<double>& x, const QVector<double>& y)
{
    m_customPlot->graph()->addData(x, y);
    m_customPlot->graph()->rescaleAxes();
    m_customPlot->replot();
}

void HistogramPlot::setData(const QVector<double>& x, const QVector<double>& y)
{
    m_customPlot->graph()->setData(x, y);
    m_customPlot->graph()->rescaleAxes();
    m_customPlot->replot();
}

void HistogramPlot::clearData()
{
    m_customPlot->removeGraph(m_customPlot->graph());
    initGraph();
    m_customPlot->replot();
}

void HistogramPlot::initGraph()
{
    m_customPlot->addGraph();

    QPen pen(QColor(0, 0, 255, 200));
    m_customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    m_customPlot->graph()->setPen(pen);
    m_customPlot->graph()->setBrush(QBrush(QColor(255 / 4, 160, 50, 150)));

    QFontMetrics fontMetric(font());
    auto em = fontMetric.width('M'), fontAscent = fontMetric.ascent();
    auto* axisRectangle = m_customPlot->axisRect();
    axisRectangle->setAutoMargins(QCP::msTop | QCP::msBottom);
    axisRectangle->setMargins(QMargins(em*4, fontAscent*2, em*2, fontAscent*2));
}
