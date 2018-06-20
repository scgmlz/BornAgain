// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/GISASSpecularComputation.cpp
//! @brief     Implements class GISASSpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GISASSpecularComputation.h"
#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MultiLayer.h"
#include "SimulationElement.h"

GISASSpecularComputation::GISASSpecularComputation(const MultiLayer* p_multi_layer,
                                                           const IFresnelMap* p_fresnel_map)
    : m_multilayer_info(p_multi_layer, p_fresnel_map)
{}

void GISASSpecularComputation::compute(SimulationElement& elem) const
{
    auto p_multilayer = m_multilayer_info.mp_multilayer;
    if (p_multilayer->requiresMatrixRTCoefficients())
        return;

    auto p_fresnel_map = m_multilayer_info.mp_fresnel_map;
    if (elem.isSpecular()) {
        complex_t R = p_fresnel_map->getInCoefficients(elem, 0)->getScalarR();
        double sin_alpha_i = std::abs(std::sin(elem.getAlphaI()));
        if (sin_alpha_i == 0.0)
            sin_alpha_i = 1.0;
        const double solid_angle = elem.getSolidAngle();
        if (solid_angle <= 0.0)
            return;
        const double intensity = std::norm(R) * sin_alpha_i / solid_angle;
        elem.setIntensity(intensity);
    }
}
