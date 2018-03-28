// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.h
//! @brief     Defines class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATRIXFRESNELMAP_H
#define MATRIXFRESNELMAP_H

#include "HashKVector.h"
#include "IFresnelMap.h"
#include <memory>
#include <unordered_map>
#include <vector>

class ILayerRTCoefficients;
class MatrixRTCoefficients;
class MultiLayer;
class SimulationElement;

//! Implementation of IFresnelMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixFresnelMap : public IFresnelMap
{
public:
    MatrixFresnelMap();
    virtual ~MatrixFresnelMap();

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element,
                       size_t layer_index) const final override;

    void setMultilayer(const MultiLayer& multilayer) final override;

    //! Fills simulation element specular data
    void fillSpecularData(SpecularSimulationElement& sim_element) const override;

    typedef std::unordered_map<kvector_t, std::vector<MatrixRTCoefficients>, HashKVector>
        CoefficientHash;

private:
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index,
                                                                const MultiLayer& multilayer,
                                                                CoefficientHash& hash_table) const;

    std::unique_ptr<MultiLayer> mP_inverted_multilayer;
    mutable CoefficientHash m_hash_table_out;
    mutable CoefficientHash m_hash_table_in;
};

#endif // MATRIXFRESNELMAP_H
