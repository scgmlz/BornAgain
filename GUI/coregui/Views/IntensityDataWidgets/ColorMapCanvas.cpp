// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvas.cpp
//! @brief     Declares class ColorMapCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ColorMapCanvas.h"
#include "ColorMap.h"
#include "ColorMapCanvasEvent.h"
#include "PlotStatusLabel.h"
#include "IntensityDataItem.h"
#include "StatusLabel.h"
#include <QLabel>
#include <QVBoxLayout>

ColorMapCanvas::ColorMapCanvas(QWidget *parent)
    : SessionItemWidget(parent)
    , m_colorMap(new ColorMap)
    , m_canvasEvent(new ColorMapCanvasEvent(this))
    , m_statusLabel(new PlotStatusLabel(m_colorMap, this))
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_colorMap);
    layout->addWidget(m_statusLabel);

    setLayout(layout);

    setStatusLabelEnabled(false);
}

void ColorMapCanvas::setItem(SessionItem* intensityDataItem)
{
    SessionItemWidget::setItem(intensityDataItem);
    m_colorMap->setItem(dynamic_cast<IntensityDataItem*>(intensityDataItem));
}

ColorMap* ColorMapCanvas::colorMap()
{
    return m_colorMap;
}

QCustomPlot* ColorMapCanvas::customPlot()
{
    return m_colorMap->customPlot();
}

void ColorMapCanvas::setStatusLabelEnabled(bool flag)
{
    m_statusLabel->setLabelEnabled(flag);
    m_statusLabel->setHidden(!flag);
}

void ColorMapCanvas::onStatusString(const QString& name)
{
    m_statusLabel->setText(name);
}
