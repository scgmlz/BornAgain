// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarSpecularInfoMap.h
//! @brief     Defines class ScalarSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SCALARSPECULARINFOMAP_H
#define SCALARSPECULARINFOMAP_H

#include "ISpecularInfoMap.h"
#include "Vectors3D.h"

class MultiLayer;
class ILayerRTCoefficients;
class ScalarRTCoefficients;
class SimulationElement;

//! Implementation of ISpecularInfoMap for scalar valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ ScalarSpecularInfoMap : public ISpecularInfoMap
{
public:
    ScalarSpecularInfoMap(const MultiLayer* multilayer, int layer);
    ~ScalarSpecularInfoMap() final {}

    ScalarSpecularInfoMap* clone() const final
    {
        return new ScalarSpecularInfoMap(mp_multilayer, m_layer);
    }

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients*
    getOutCoefficients(const SimulationElement& sim_element) const final;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getInCoefficients(const SimulationElement& sim_element) const final;

private:
    const MultiLayer* mp_multilayer;
    const int m_layer;
    const ScalarRTCoefficients* getCoefficients(kvector_t kvec) const;
};

#endif // SCALARSPECULARINFOMAP_H
