// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularScalarTanhStrategy.h
//! @brief     Defines class SpecularScalarTanhStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_SPECULARSCALARTANHSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_SPECULARSCALARTANHSTRATEGY_H

#include "Core/Multilayer/SpecularScalarStrategy.h"

class Slice;

//! Implements an tanh transition function to model roughness in a scaler computation.
//!
//! Implements the transition function that includes the analytical roughness model
//! of an tanh interface transition in the computation of the coefficients for
//! coherent wave propagation in a multilayer by applying modified Fresnel coefficients.
//!
//! @ingroup algorithms_internal
class BA_CORE_API_ SpecularScalarTanhStrategy : public SpecularScalarStrategy
{
private:
    //! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
    virtual Eigen::Vector2cd transition(complex_t kzi, complex_t kzi1, double sigma,
                                        double thickness,
                                        const Eigen::Vector2cd& t_r1) const override;
};

#endif // BORNAGAIN_CORE_MULTILAYER_SPECULARSCALARTANHSTRATEGY_H
