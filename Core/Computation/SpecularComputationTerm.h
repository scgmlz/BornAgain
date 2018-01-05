// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.h
//! @brief     Defines class SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARCOMPUTATIONTERM_H_
#define SPECULARCOMPUTATIONTERM_H_

#include "IComputationTerm.h"

//! Computes the specular scattering.
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularComputationTerm : public IComputationTerm
{
public:
    SpecularComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

private:
    virtual void evalSingle(SimulationElement& element) const override;
    virtual bool checkComputation() const override;
};

#endif /* SPECULARCOMPUTATIONTERM_H_ */
