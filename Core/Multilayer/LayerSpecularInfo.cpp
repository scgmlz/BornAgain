// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerSpecularInfo.cpp
//! @brief     Implements class LayerSpecularInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerSpecularInfo.h"
#include "ILayerRTCoefficients.h"
#include "ISpecularInfoMap.h"
#include "SimulationElement.h"

LayerSpecularInfo::LayerSpecularInfo() {}
LayerSpecularInfo::~LayerSpecularInfo() {}

LayerSpecularInfo* LayerSpecularInfo::clone() const
{
    LayerSpecularInfo* p_result = new LayerSpecularInfo;
    p_result->mP_coeff_map.reset(this->mP_coeff_map->clone());
    return p_result;
}

void LayerSpecularInfo::addRTCoefficients(ISpecularInfoMap* rt_coefficient_map)
{
    if (mP_coeff_map.get() != rt_coefficient_map)
        mP_coeff_map.reset(rt_coefficient_map);
}

const ILayerRTCoefficients*
LayerSpecularInfo::getOutCoefficients(const SimulationElement& sim_element) const
{
    return mP_coeff_map->getOutCoefficients(sim_element);
}

const ILayerRTCoefficients*
LayerSpecularInfo::getInCoefficients(const SimulationElement& sim_element) const
{
    return mP_coeff_map->getInCoefficients(sim_element);
}
