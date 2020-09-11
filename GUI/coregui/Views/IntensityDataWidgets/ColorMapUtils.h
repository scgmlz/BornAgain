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

#include "Wrap/WinDllMacros.h"
#include "qcustomplot.h"
#include <QMap>
#include <QMargins>
#include <QString>

class IntensityDataItem;
class ColorMap;

//! Provides few helper functions for ColorMapPlot.

namespace ColorMapUtils
{

BA_CORE_API_ QCPColorGradient getGradient(const QString& gradientName);
BA_CORE_API_ QCPColorGradient itemGradient(const IntensityDataItem* item);

//! Returns x-axis range.
BA_CORE_API_ QCPRange itemXrange(const IntensityDataItem* item);

//! Returns x-axis vizible range (zoom).
BA_CORE_API_ QCPRange itemZoomX(const IntensityDataItem* item);

//! Returns y-axis range.
BA_CORE_API_ QCPRange itemYrange(const IntensityDataItem* item);

//! Returns y-axis vizible range (zoom).
BA_CORE_API_ QCPRange itemZoomY(const IntensityDataItem* item);

//! Returns z-axis data range.
BA_CORE_API_ QCPRange itemDataRange(const IntensityDataItem* item);

//! Returns z-axis visible range (zoom).
BA_CORE_API_ QCPRange itemDataZoom(const IntensityDataItem* item);

BA_CORE_API_ void setLogz(QCPColorScale* scale, bool isLogz);
BA_CORE_API_ void setLogz(QCPAxis* axis, bool isLogz);

//! Sets default margins for axes rectangle plot.
BA_CORE_API_ void setDefaultMargins(QCustomPlot* customPlot);

} // namespace ColorMapUtils

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAPUTILS_H
