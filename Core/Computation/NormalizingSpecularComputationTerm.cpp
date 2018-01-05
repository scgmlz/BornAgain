// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/NormalizingSpecularComputationTerm.cpp
//! @brief     Implements class NormalizingSpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "NormalizingSpecularComputationTerm.h"
#include "SimulationElement.h"
#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"

NormalizingSpecularComputationTerm::NormalizingSpecularComputationTerm(const MultiLayer* p_multi_layer,
                                         const IFresnelMap* p_fresnel_map)
    : SpecularComputationTerm(p_multi_layer, p_fresnel_map)
{}

void NormalizingSpecularComputationTerm::evalSingle(SimulationElement& element) const
{
    if (!element.specularData())
        return;
    const double solid_angle = element.getSolidAngle();
    if (solid_angle <= 0.0)
        return;
    double sin_alpha_i = std::abs(std::sin(element.getAlphaI()));
    if (sin_alpha_i == 0.0)
        sin_alpha_i = 1.0;
    const complex_t R = mp_fresnel_map->getInCoefficients(element, 0)->getScalarR();
    const double intensity = std::norm(R) * sin_alpha_i / solid_angle;
    element.setIntensity(intensity);
}
