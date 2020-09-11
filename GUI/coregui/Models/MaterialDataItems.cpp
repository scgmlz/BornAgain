// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialDataItems.cpp
//! @brief     Implements MaterialDataItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MaterialDataItems.h"

MaterialDataItem::MaterialDataItem(const QString& modelType) : SessionItem(modelType)
{
    setEditable(false); // empty label, non-editable
}

// ------------------------------------------------------------------------------------------------

const QString MaterialRefractiveDataItem::P_DELTA = "Delta";
const QString MaterialRefractiveDataItem::P_BETA = "Beta";

MaterialRefractiveDataItem::MaterialRefractiveDataItem()
    : MaterialDataItem("MaterialRefractiveData")
{
    addProperty(P_DELTA, 0.0)
        ->setEditorType("ScientificDouble")
        .setLimits(RealLimits::limitless())
        .setToolTip("Delta of refractive index (n = 1 - delta + i*beta)");
    addProperty(P_BETA, 0.0)
        ->setEditorType("ScientificDouble")
        .setLimits(RealLimits::limitless())
        .setToolTip("Beta of refractive index (n = 1 - delta + i*beta)");
}

// ------------------------------------------------------------------------------------------------

const QString MaterialSLDDataItem::P_SLD_REAL = "SLD, real";
const QString MaterialSLDDataItem::P_SLD_IMAG = "SLD, imaginary";

MaterialSLDDataItem::MaterialSLDDataItem() : MaterialDataItem("MaterialSLDData")
{
    addProperty(P_SLD_REAL, 0.0)
        ->setEditorType("ScientificDouble")
        .setLimits(RealLimits::limitless())
        .setToolTip("Real part of SLD (SLD = real - i*imag), AA^{-2}");
    addProperty(P_SLD_IMAG, 0.0)
        ->setEditorType("ScientificDouble")
        .setLimits(RealLimits::limitless())
        .setToolTip("Imaginary part of SLD (SLD = real - i*imag), AA^{-2}");
}
