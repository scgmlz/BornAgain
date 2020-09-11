// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/FontScalingEvent.cpp
//! @brief     Implements class FontScalingEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/FontScalingEvent.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h"
#include "qcustomplot.h"
#include <QResizeEvent>

namespace
{
const QString tick_font = "tick-font-key";
const int widget_size_to_switch_font = 500;
} // namespace

FontScalingEvent::FontScalingEvent(ScientificPlot* plot, QWidget* parent)
    : QObject(parent), m_plot(plot)
{
}

bool FontScalingEvent::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Resize) {
        QResizeEvent* resizeEvent = static_cast<QResizeEvent*>(event);
        ASSERT(resizeEvent);

        if (!m_fonts.contains(tick_font)) {
            backupFonts();

        } else {
            if (resizeEvent->size().width() < widget_size_to_switch_font) {
                scaleFonts(0.8);
            } else {
                restoreFonts();
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

//! Backup all fonts.

void FontScalingEvent::backupFonts()
{
    m_fonts[tick_font] = m_plot->customPlot()->xAxis->tickLabelFont();
}

void FontScalingEvent::restoreFonts()
{
    QFont ff = m_fonts[tick_font];
    setTickLabelFont(ff);
}

void FontScalingEvent::scaleFonts(double factor)
{
    QFont ff = m_fonts[tick_font];
    ff.setPointSizeF(ff.pointSizeF() * factor);
    setTickLabelFont(ff);
}

void FontScalingEvent::setTickLabelFont(const QFont& font)
{
    m_plot->customPlot()->xAxis->setTickLabelFont(font);
    m_plot->customPlot()->yAxis->setTickLabelFont(font);
    if (m_plot->plotType() != ScientificPlot::PLOT_TYPE::Plot2D)
        return;

    auto color_map = dynamic_cast<ColorMap*>(m_plot);
    color_map->colorScale()->axis()->setTickLabelFont(font);
}
