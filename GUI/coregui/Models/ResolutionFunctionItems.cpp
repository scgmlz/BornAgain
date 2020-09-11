// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ResolutionFunctionItems.cpp
//! @brief     Implements family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ResolutionFunctionItems.h"
#include "Core/Detector/ResolutionFunction2DGaussian.h"

ResolutionFunctionItem::ResolutionFunctionItem(const QString& name) : SessionItem(name) {}

/* --------------------------------------------------------------------------------------------- */

ResolutionFunctionNoneItem::ResolutionFunctionNoneItem()
    : ResolutionFunctionItem("ResolutionFunctionNone")
{
}

std::unique_ptr<IResolutionFunction2D>
ResolutionFunctionNoneItem::createResolutionFunction(double) const
{
    return std::unique_ptr<IResolutionFunction2D>();
}

/* --------------------------------------------------------------------------------------------- */

const QString ResolutionFunction2DGaussianItem::P_SIGMA_X = QString::fromStdString("SigmaX");
const QString ResolutionFunction2DGaussianItem::P_SIGMA_Y = QString::fromStdString("SigmaY");

ResolutionFunction2DGaussianItem::ResolutionFunction2DGaussianItem()
    : ResolutionFunctionItem("ResolutionFunction2DGaussian")
{
    addProperty(P_SIGMA_X, 0.02)
        ->setLimits(RealLimits::lowerLimited(0.0))
        .setDecimals(3)
        .setToolTip("Resolution along horizontal axis (in detector units)");
    addProperty(P_SIGMA_Y, 0.02)
        ->setLimits(RealLimits::lowerLimited(0.0))
        .setDecimals(3)
        .setToolTip("Resolution along vertical axis (in detector units)");
}

std::unique_ptr<IResolutionFunction2D>
ResolutionFunction2DGaussianItem::createResolutionFunction(double scale) const
{
    return std::make_unique<ResolutionFunction2DGaussian>(
        scale * getItemValue(P_SIGMA_X).toDouble(), scale * getItemValue(P_SIGMA_Y).toDouble());
}
