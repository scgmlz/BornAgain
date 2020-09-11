// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamWavelengthItem.cpp
//! @brief     Implements class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/BeamWavelengthItem.h"

namespace
{
const double default_wl = 0.1;
}

BeamWavelengthItem::BeamWavelengthItem(const QString& model_type, const QString& distribution_group)
    : BeamDistributionItem(model_type, m_show_mean)
{
    register_distribution_group(distribution_group);

    SessionItem* valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_MEAN);
    valueItem->setLimits(RealLimits::positive());
    valueItem->setDecimals(4);
    valueItem->setValue(default_wl);
    valueItem->setEditorType("ScientificSpinBox");

    initDistributionItem(m_show_mean);
}

//! Returns wavelength. In the case of distribution applied, returns its mean.

double BeamWavelengthItem::wavelength() const
{
    return BeamDistributionItem::meanValue();
}

SpecularBeamWavelengthItem::SpecularBeamWavelengthItem()
    : BeamWavelengthItem("SpecularBeamWavelength", "Symmetric distribution group")
{
}

void SpecularBeamWavelengthItem::setToRange(const RealLimits& limits)
{
    SessionItem* valueItem =
        getGroupItem(P_DISTRIBUTION)->getItem(SymmetricDistributionItem::P_MEAN);
    if (!limits.isInRange(wavelength())) {
        const double new_value =
            limits.isLimited() ? (limits.upperLimit() - limits.lowerLimit()) / 2. : default_wl;
        valueItem->setValue(new_value);
    }
    valueItem->setLimits(limits);
}
