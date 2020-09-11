// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/Plot1DCanvas.cpp
//! @brief     Implements class Plot1DCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SpecularDataWidgets/Plot1DCanvas.h"
#include "GUI/coregui/Views/IntensityDataWidgets/FontScalingEvent.h"
#include "GUI/coregui/Views/IntensityDataWidgets/Plot1D.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PlotStatusLabel.h"
#include <QVBoxLayout>

Plot1DCanvas::Plot1DCanvas(QWidget* parent)
    : SessionItemWidget(parent), m_plot(new Plot1D),
      m_canvasEvent(new FontScalingEvent(m_plot, this)),
      m_statusLabel(new PlotStatusLabel(m_plot, this))
{
    this->installEventFilter(m_canvasEvent);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_plot);
    layout->addWidget(m_statusLabel);

    setLayout(layout);

    setStatusLabelEnabled(false);
}

void Plot1DCanvas::setItem(SessionItem* dataItemView)
{
    SessionItemWidget::setItem(dataItemView);
    m_plot->setItem(dataItemView);
}

Plot1D* Plot1DCanvas::plot1D()
{
    return m_plot;
}

QCustomPlot* Plot1DCanvas::customPlot()
{
    return m_plot->customPlot();
}

void Plot1DCanvas::setStatusLabelEnabled(bool flag)
{
    m_statusLabel->setLabelEnabled(flag);
    m_statusLabel->setHidden(!flag);
}

void Plot1DCanvas::onStatusString(const QString& name)
{
    m_statusLabel->setText(name);
}
