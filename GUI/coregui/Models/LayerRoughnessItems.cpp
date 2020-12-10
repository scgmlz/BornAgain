//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerRoughnessItems.cpp
//! @brief     Implements classes LayerRoughnessItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/LayerRoughnessItems.h"

namespace {
const QString hurst_tooltip =
    "Hurst parameter which describes how jagged the interface,\n "
    "dimensionless [0.0, 1.0], where 0.0 gives more spikes, \n1.0 more smoothness.";
}

LayerZeroRoughnessItem::LayerZeroRoughnessItem() : SessionItem("LayerZeroRoughness") {}

const QString LayerBasicRoughnessItem::P_SIGMA = QString::fromStdString("Sigma");
const QString LayerBasicRoughnessItem::P_HURST = QString::fromStdString("Hurst");
const QString LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH =
    QString::fromStdString("CorrelationLength");

LayerBasicRoughnessItem::LayerBasicRoughnessItem() : SessionItem("LayerBasicRoughness") {
    setToolTip("A roughness of interface between two layers.");
    addProperty(P_SIGMA, 1.0)->setToolTip("rms of the roughness in nanometers");
    addProperty(P_HURST, 0.3)->setLimits(RealLimits::limited(0.0, 1.0)).setToolTip(hurst_tooltip);
    getItem(P_HURST)->setDecimals(3);
    addProperty(P_LATERAL_CORR_LENGTH, 5.0)
        ->setToolTip("Lateral correlation length of the roughness in nanometers");
}
