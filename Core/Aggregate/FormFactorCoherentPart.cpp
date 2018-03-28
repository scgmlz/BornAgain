// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorCoherentPart.cpp
//! @brief     Implements class FormFactorCoherentPart.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorCoherentPart.h"
#include "IFresnelMap.h"
#include "IFormFactor.h"
#include "SimulationElement.h"
#include "WavevectorInfo.h"
#include "ILayerRTCoefficients.h"


FormFactorCoherentPart::FormFactorCoherentPart(IFormFactor* p_ff)
    : mP_ff(p_ff)
{
}

FormFactorCoherentPart::FormFactorCoherentPart(const FormFactorCoherentPart& other)
    : mP_ff(other.mP_ff->clone())
    , mp_fresnel_map(other.mp_fresnel_map)
    , m_layer_index(other.m_layer_index)
{
}

FormFactorCoherentPart::~FormFactorCoherentPart() {}

complex_t FormFactorCoherentPart::evaluate(const SimulationElement& sim_element) const
{
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf(),
                               sim_element.getWavelength());

    auto P_in_coeffs = mp_fresnel_map->getInCoefficients(sim_element, m_layer_index);
    auto P_out_coeffs = mp_fresnel_map->getOutCoefficients(sim_element, m_layer_index);
    mP_ff->setSpecularInfo(std::move(P_in_coeffs), std::move(P_out_coeffs));
    return mP_ff->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorCoherentPart::evaluatePol(const SimulationElement& sim_element) const
{
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf(),
                               sim_element.getWavelength());

    auto P_in_coeffs = mp_fresnel_map->getInCoefficients(sim_element, m_layer_index);
    auto P_out_coeffs = mp_fresnel_map->getOutCoefficients(sim_element, m_layer_index);
    mP_ff->setSpecularInfo(std::move(P_in_coeffs), std::move(P_out_coeffs));
    return mP_ff->evaluatePol(wavevectors);
}

void FormFactorCoherentPart::setSpecularInfo(const IFresnelMap* p_fresnel_map, size_t layer_index)
{
    mp_fresnel_map = p_fresnel_map;
    m_layer_index = layer_index;
}

double FormFactorCoherentPart::radialExtension() const
{
    return mP_ff->radialExtension();
}
