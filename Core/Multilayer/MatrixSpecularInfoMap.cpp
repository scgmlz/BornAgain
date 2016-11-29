// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixSpecularInfoMap.cpp
//! @brief     Implements class ScalarSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MatrixSpecularInfoMap.h"
#include "ILayerRTCoefficients.h"
#include "MatrixRTCoefficients.h"
#include "ISpecularInfoMap.h"
#include "MultiLayer.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"

MatrixSpecularInfoMap::MatrixSpecularInfoMap(const MultiLayer* multilayer, int layer)
    : m_layer(layer)
{
    if (multilayer) {
        mP_multilayer.reset((multilayer->clone()));
        mP_inverted_multilayer.reset(multilayer->cloneInvertB());
    }
}

MatrixSpecularInfoMap* MatrixSpecularInfoMap::clone() const
{
    MatrixSpecularInfoMap* result = new MatrixSpecularInfoMap(nullptr, m_layer);
    if (mP_multilayer)  {
        result->mP_multilayer.reset(mP_multilayer->clone());
        result->mP_inverted_multilayer.reset(mP_inverted_multilayer->clone());
    }
    return result;
}

// TODO factor out common private function as done in the Scalar.. case ?

const ILayerRTCoefficients* MatrixSpecularInfoMap::getOutCoefficients(
        const SimulationElement& sim_element) const
{
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    SpecularMagnetic::execute(*mP_inverted_multilayer, -sim_element.getMeanKf(), coeffs);
    return new MatrixRTCoefficients(coeffs[m_layer]);
}

const ILayerRTCoefficients* MatrixSpecularInfoMap::getInCoefficients(
        const SimulationElement& sim_element) const
{
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    SpecularMagnetic::execute(*mP_multilayer, sim_element.getKi(), coeffs);
    return new MatrixRTCoefficients(coeffs[m_layer]);
}
