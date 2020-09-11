// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlotCanvas.cpp
//! @brief     Declares class SpecularPlotCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SpecularDataWidgets/SpecularPlotCanvas.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Views/IntensityDataWidgets/FontScalingEvent.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PlotStatusLabel.h"
#include "GUI/coregui/Views/SpecularDataWidgets/SpecularPlot.h"
#include <QVBoxLayout>

SpecularPlotCanvas::SpecularPlotCanvas(QWidget* parent)
    : SessionItemWidget(parent), m_plot(new SpecularPlot),
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

void SpecularPlotCanvas::setItem(SessionItem* specularDataItem)
{
    SessionItemWidget::setItem(specularDataItem);
    m_plot->setItem(dynamic_cast<SpecularDataItem*>(specularDataItem));
}

SpecularPlot* SpecularPlotCanvas::specularPlot()
{
    return m_plot;
}

QCustomPlot* SpecularPlotCanvas::customPlot()
{
    return m_plot->customPlot();
}

void SpecularPlotCanvas::setStatusLabelEnabled(bool flag)
{
    m_statusLabel->setLabelEnabled(flag);
    m_statusLabel->setHidden(!flag);
}

void SpecularPlotCanvas::onStatusString(const QString& name)
{
    m_statusLabel->setText(name);
}
