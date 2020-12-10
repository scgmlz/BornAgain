//  ************************************************************************************************
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
//  ************************************************************************************************

#include "Core/Computation/GISASSpecularComputation.h"
#include "Base/Pixel/SimulationElement.h"
#include "Sample/Fresnel/IFresnelMap.h"
#include "Sample/RT/ILayerRTCoefficients.h"

GISASSpecularComputation::GISASSpecularComputation(const IFresnelMap* p_fresnel_map)
    : m_fresnel_map{p_fresnel_map} {}

void GISASSpecularComputation::compute(SimulationElement& elem) const {
    if (!elem.isSpecular())
        return;
    complex_t R = m_fresnel_map->getInCoefficients(elem, 0)->getScalarR();
    double sin_alpha_i = std::abs(std::sin(elem.getAlphaI()));
    if (sin_alpha_i == 0.0)
        sin_alpha_i = 1.0;
    const double solid_angle = elem.solidAngle();
    if (solid_angle <= 0.0)
        return;
    const double intensity = std::norm(R) * sin_alpha_i / solid_angle;
    elem.setIntensity(intensity);
}
