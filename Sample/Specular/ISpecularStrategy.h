//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/ISpecularStrategy.h
//! @brief     Defines and implements class ISpecularStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SPECULAR_ISPECULARSTRATEGY_H
#define BORNAGAIN_SAMPLE_SPECULAR_ISPECULARSTRATEGY_H

#include "Base/Types/Complex.h"
#include "Base/Vector/Vectors3D.h"
#include <memory>
#include <vector>

class ILayerRTCoefficients;
class Slice;

//! Interface for the Fresnel computations, both in the scalar and magnetic case
//!
//! Inherited by SpecularScalarStrategy, SpecularMagneticOldStrategy,
//! SpecularMagneticStrategy, SpecularMagneticNewStrategy

//! @ingroup algorithms_internal

class ISpecularStrategy {
public:
    ISpecularStrategy() = default;
    virtual ~ISpecularStrategy() = default;
    ISpecularStrategy(const ISpecularStrategy& other) = delete;

    using coeffs_t = std::vector<std::unique_ptr<const ILayerRTCoefficients>>;

    virtual coeffs_t Execute(const std::vector<Slice>& slices, const kvector_t& k) const = 0;

    virtual coeffs_t Execute(const std::vector<Slice>& slices,
                             const std::vector<complex_t>& kz) const = 0;
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_ISPECULARSTRATEGY_H
#endif // USER_API
