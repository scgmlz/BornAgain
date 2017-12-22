// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/NormalizingSpecularComputationTerm.h
//! @brief     Defines class NormalizingSpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef NORMALIZINGSPECULARCOMPUTATIONTERM_H
#define NORMALIZINGSPECULARCOMPUTATIONTERM_H

#include "SpecularComputationTerm.h"

//! Computes the specular scattering.
//! Used by DWBAComputation. Differs from SpecularComputationTerm by multilying intensity by
//! normalization factor \f$sin \alpha / \Omega\f$.
//! @ingroup algorithms_internal

class NormalizingSpecularComputationTerm final : public SpecularComputationTerm
{
public:
    NormalizingSpecularComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

private:
    virtual void evalSingle(SimulationElement& iter) const override;
};

#endif // NORMALIZINGSPECULARCOMPUTATIONTERM_H
