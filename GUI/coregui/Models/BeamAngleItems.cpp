// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamAngleItems.cpp
//! @brief     Implements class BeamAngleItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/BeamAngleItems.h"
#include "Core/Basics/Units.h"

BeamAzimuthalAngleItem::BeamAzimuthalAngleItem()
    : BeamDistributionItem("BeamAzimuthalAngle", m_show_mean)
{
    register_distribution_group("Distribution extended group");

    SessionItem* valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_MEAN);
    valueItem->setLimits(RealLimits::limited(-90.0, 90.0));
    valueItem->setDecimals(3);
    valueItem->setValue(0.0);

    initDistributionItem(m_show_mean);
}

//! Returns beam azimuthal angle. In the case of distribution applied, returns its mean.

double BeamAzimuthalAngleItem::azimuthalAngle() const
{
    return BeamDistributionItem::meanValue();
}

double BeamAzimuthalAngleItem::scaleFactor() const
{
    return Units::degree;
}

// ------------------------------------------------------------------------------------------------

BeamInclinationAngleItem::BeamInclinationAngleItem()
    : BeamDistributionItem("BeamInclinationAngle", m_show_mean)
{
    register_distribution_group("Distribution extended group");

    SessionItem* valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_MEAN);
    valueItem->setLimits(RealLimits::limited(0.0, 90.0));
    valueItem->setDecimals(3);
    valueItem->setValue(0.2);

    initDistributionItem(m_show_mean);
}

//! Returns beam inclination angle. In the case of distribution applied, returns its mean.

double BeamInclinationAngleItem::inclinationAngle() const
{
    return BeamDistributionItem::meanValue();
}

double BeamInclinationAngleItem::scaleFactor() const
{
    return Units::degree;
}
