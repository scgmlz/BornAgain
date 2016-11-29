// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarSpecularInfoMap.cpp
//! @brief     Implements class ScalarSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ScalarSpecularInfoMap.h"
#include "ISpecularInfoMap.h"
#include "MultiLayer.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "SpecularMatrix.h"

ScalarSpecularInfoMap::ScalarSpecularInfoMap(const MultiLayer* multilayer, int layer)
    : mp_multilayer(multilayer)
    , m_layer(layer)
{}

const ILayerRTCoefficients* ScalarSpecularInfoMap::getOutCoefficients(
        const SimulationElement& sim_element) const
{
    return getCoefficients(-sim_element.getMeanKf());
}

const ILayerRTCoefficients* ScalarSpecularInfoMap::getInCoefficients(
        const SimulationElement& sim_element) const
{
    return getCoefficients(sim_element.getKi());
}

const ScalarRTCoefficients* ScalarSpecularInfoMap::getCoefficients(kvector_t kvec) const
{
    SpecularMatrix::MultiLayerCoeff_t coeffs;
    SpecularMatrix::execute(*mp_multilayer, kvec, coeffs);
    auto layer_coeffs = coeffs[m_layer];
    return new ScalarRTCoefficients(layer_coeffs);
}
