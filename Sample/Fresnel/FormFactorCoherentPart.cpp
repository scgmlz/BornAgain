//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Fresnel/FormFactorCoherentPart.cpp
//! @brief     Implements class FormFactorCoherentPart.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Fresnel/FormFactorCoherentPart.h"
#include "Base/Pixel/SimulationElement.h"
#include "Sample/FFCompute/IComputeFF.h"
#include "Sample/Fresnel/IFresnelMap.h"
#include "Sample/Material/WavevectorInfo.h"
#include "Sample/RT/ILayerRTCoefficients.h"

FormFactorCoherentPart::FormFactorCoherentPart(IComputeFF* ff) : m_ff(ff) {}

FormFactorCoherentPart::FormFactorCoherentPart(const FormFactorCoherentPart& other)
    : m_ff(std::unique_ptr<IComputeFF>(other.m_ff->clone()))
    , m_fresnel_map(other.m_fresnel_map)
    , m_layer_index(other.m_layer_index) {}

FormFactorCoherentPart& FormFactorCoherentPart::operator=(const FormFactorCoherentPart& other) {
    m_ff.reset(other.m_ff->clone());
    m_fresnel_map = other.m_fresnel_map;
    m_layer_index = other.m_layer_index;
    return *this;
}

FormFactorCoherentPart& FormFactorCoherentPart::operator=(FormFactorCoherentPart&&) = default;

FormFactorCoherentPart::FormFactorCoherentPart(FormFactorCoherentPart&&) = default;

FormFactorCoherentPart::~FormFactorCoherentPart() = default;

complex_t FormFactorCoherentPart::evaluate(const SimulationElement& sim_element) const {
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf(),
                               sim_element.wavelength());

    auto in_coeffs = m_fresnel_map->getInCoefficients(sim_element, m_layer_index);
    auto out_coeffs = m_fresnel_map->getOutCoefficients(sim_element, m_layer_index);
    m_ff->setSpecularInfo(std::move(in_coeffs), std::move(out_coeffs));
    return m_ff->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorCoherentPart::evaluatePol(const SimulationElement& sim_element) const {
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf(),
                               sim_element.wavelength());

    auto in_coeffs = m_fresnel_map->getInCoefficients(sim_element, m_layer_index);
    auto out_coeffs = m_fresnel_map->getOutCoefficients(sim_element, m_layer_index);
    m_ff->setSpecularInfo(std::move(in_coeffs), std::move(out_coeffs));
    return m_ff->evaluatePol(wavevectors);
}

void FormFactorCoherentPart::setSpecularInfo(const IFresnelMap* fresnel_map, size_t layer_index) {
    m_fresnel_map = fresnel_map;
    m_layer_index = layer_index;
}

double FormFactorCoherentPart::radialExtension() const {
    return m_ff->radialExtension();
}
