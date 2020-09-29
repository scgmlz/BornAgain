// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.h
//! @brief     Defines ColorMapUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAPUTILS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAPUTILS_H

#include "qcustomplot.h"
#include <QMap>
#include <QMargins>
#include <QString>

class IntensityDataItem;
class ColorMap;

//! Provides few helper functions for ColorMapPlot.

namespace ColorMapUtils
{

QCPColorGradient getGradient(const QString& gradientName);
QCPColorGradient itemGradient(const IntensityDataItem* item);

//! Returns x-axis range.
QCPRange itemXrange(const IntensityDataItem* item);

//! Returns x-axis vizible range (zoom).
QCPRange itemZoomX(const IntensityDataItem* item);

//! Returns y-axis range.
QCPRange itemYrange(const IntensityDataItem* item);

//! Returns y-axis vizible range (zoom).
QCPRange itemZoomY(const IntensityDataItem* item);

//! Returns z-axis data range.
QCPRange itemDataRange(const IntensityDataItem* item);

//! Returns z-axis visible range (zoom).
QCPRange itemDataZoom(const IntensityDataItem* item);

void setLogz(QCPColorScale* scale, bool isLogz);
void setLogz(QCPAxis* axis, bool isLogz);

//! Sets default margins for axes rectangle plot.
void setDefaultMargins(QCustomPlot* customPlot);

} // namespace ColorMapUtils

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAPUTILS_H
