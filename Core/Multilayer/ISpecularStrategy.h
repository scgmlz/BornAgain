// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ISpecularStrategy.h
//! @brief     Defines and implements class ISpecularStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_ISPECULARSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_ISPECULARSTRATEGY_H

#include "Core/Multilayer/Slice.h"
#include "Core/RT/ILayerRTCoefficients.h"

//! Interface for the Fresnel computations, both in the scalar and magnetic case
//!
//! Inherited by SpecularScalarStrategy, SpecularMagneticOldStrategy,
//! SpecularMagneticStrategy, SpecularMagneticNewStrategy

//! @ingroup algorithms_internal

class ISpecularStrategy
{
public:
    virtual ~ISpecularStrategy() = default;
    ISpecularStrategy() = default;
    ISpecularStrategy& operator=(const ISpecularStrategy& other) = delete;
    ISpecularStrategy(const ISpecularStrategy& other) = delete;

    using coefficient_type = ILayerRTCoefficients;
    using coefficient_pointer_type = std::unique_ptr<const coefficient_type>;
    using coeffs_t = std::vector<coefficient_pointer_type>;

    virtual coeffs_t Execute(const std::vector<Slice>& slices, const kvector_t& k) const = 0;

    virtual coeffs_t Execute(const std::vector<Slice>& slices,
                             const std::vector<complex_t>& kz) const = 0;
};

#endif // BORNAGAIN_CORE_MULTILAYER_ISPECULARSTRATEGY_H
