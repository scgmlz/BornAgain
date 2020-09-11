// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.cpp
//! @brief     Implements ColorMapUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/ColorMapUtils.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/StyleUtils.h"

using gradient_map_t = QMap<QString, QCPColorGradient::GradientPreset>;

namespace
{
gradient_map_t createGradientMap()
{
    gradient_map_t result;

    result["Grayscale"] = QCPColorGradient::gpGrayscale;
    result["Hot"] = QCPColorGradient::gpHot;
    result["Cold"] = QCPColorGradient::gpCold;
    result["Night"] = QCPColorGradient::gpNight;
    result["Candy"] = QCPColorGradient::gpCandy;
    result["Geography"] = QCPColorGradient::gpGeography;
    result["Ion"] = QCPColorGradient::gpIon;
    result["Thermal"] = QCPColorGradient::gpThermal;
    result["Polar"] = QCPColorGradient::gpPolar;
    result["Spectrum"] = QCPColorGradient::gpSpectrum;
    result["Jet"] = QCPColorGradient::gpJet;
    result["Hues"] = QCPColorGradient::gpHues;

    return result;
}

// Converts xmin (low edge of first bin) and xmax (upper edge of last bin) to the
// range expected by QCPColorMapData::setRange.
QCPRange qcpRange(double xmin, double xmax, int nbins)
{
    double dx = (xmax - xmin) / nbins;
    return QCPRange(xmin + dx / 2., xmax - dx / 2.);
}

QMargins defaultMargins(const QWidget& widget)
{
    auto base_size = StyleUtils::SizeOfLetterM(&widget);
    int left = static_cast<int>(base_size.width() * 6.0);
    int top = static_cast<int>(base_size.height() * 1.5);
    int right = static_cast<int>(base_size.width() * 1.2);
    int bottom = static_cast<int>(base_size.height() * 4.5);
    return QMargins(left, top, right, bottom);
}

} // namespace

QCPColorGradient ColorMapUtils::getGradient(const QString& gradientName)
{
    static gradient_map_t gradient_map = createGradientMap();

    auto it = gradient_map.find(gradientName);
    if (it == gradient_map.end()) {
        throw GUIHelpers::Error("ColorMapHelper::getGradient() -> Error. No such gradient"
                                + gradientName);
    }
    return QCPColorGradient(it.value());
}

QCPColorGradient ColorMapUtils::itemGradient(const IntensityDataItem* item)
{
    return getGradient(item->getGradient());
}

QCPRange ColorMapUtils::itemXrange(const IntensityDataItem* item)
{
    return qcpRange(item->getXmin(), item->getXmax(), item->getNbinsX());
}

QCPRange ColorMapUtils::itemZoomX(const IntensityDataItem* item)
{
    return QCPRange(item->getLowerX(), item->getUpperX());
}

QCPRange ColorMapUtils::itemYrange(const IntensityDataItem* item)
{
    return qcpRange(item->getYmin(), item->getYmax(), item->getNbinsY());
}

QCPRange ColorMapUtils::itemZoomY(const IntensityDataItem* item)
{
    return QCPRange(item->getLowerY(), item->getUpperY());
}

QCPRange ColorMapUtils::itemDataRange(const IntensityDataItem* item)
{
    QPair<double, double> range = item->dataRange();
    return QCPRange(range.first, range.second);
}

QCPRange ColorMapUtils::itemDataZoom(const IntensityDataItem* item)
{
    return QCPRange(item->getLowerZ(), item->getUpperZ());
}

void ColorMapUtils::setLogz(QCPColorScale* scale, bool isLogz)
{
    if (isLogz && scale->dataScaleType() != QCPAxis::stLogarithmic)
        scale->setDataScaleType(QCPAxis::stLogarithmic);

    else if (!isLogz && scale->dataScaleType() != QCPAxis::stLinear)
        scale->setDataScaleType(QCPAxis::stLinear);

    setLogz(scale->axis(), isLogz);
}

void ColorMapUtils::setLogz(QCPAxis* axis, bool isLogz)
{
    if (isLogz) {
        axis->setNumberFormat("eb");
        axis->setNumberPrecision(0);
        axis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTickerLog);
        axis->setTicker(ticker);
    } else {
        axis->setNumberFormat("f");
        axis->setNumberPrecision(0);
        axis->setScaleType(QCPAxis::stLinear);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
        axis->setTicker(ticker);
    }
}

void ColorMapUtils::setDefaultMargins(QCustomPlot* customPlot)
{
    auto* axisRectangle = customPlot->axisRect();
    axisRectangle->setAutoMargins(QCP::msTop | QCP::msBottom);
    axisRectangle->setMargins(defaultMargins(*customPlot));
}
