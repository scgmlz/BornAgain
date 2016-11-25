// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixSpecularInfoMap.h
//! @brief     Defines class MatrixSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATRIXSPECULARINFOMAP_H
#define MATRIXSPECULARINFOMAP_H

#include "ISpecularInfoMap.h"
#include <memory>

class ILayerRTCoefficients;
class MultiLayer;
class SimulationElement;

//! Implementation of ISpecularInfoMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixSpecularInfoMap : public ISpecularInfoMap
{
public:
    MatrixSpecularInfoMap(const MultiLayer* multilayer, int layer);
    ~MatrixSpecularInfoMap() final {}

    MatrixSpecularInfoMap* clone() const final;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients*
    getOutCoefficients(const SimulationElement& sim_element) const final;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getInCoefficients(const SimulationElement& sim_element) const final;

private:
    std::unique_ptr<MultiLayer> mP_multilayer;
    std::unique_ptr<MultiLayer> mP_inverted_multilayer;
    const int m_layer;
};

#endif // MATRIXSPECULARINFOMAP_H
