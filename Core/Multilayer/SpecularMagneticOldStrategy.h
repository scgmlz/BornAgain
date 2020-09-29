// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticOldStrategy.h
//! @brief     Defines class SpecularMagneticOldStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICOLDSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICOLDSTRATEGY_H

#include "Core/Multilayer/ISpecularStrategy.h"
#include "Core/RT/MatrixRTCoefficients.h"
#include "Core/Vector/Vectors3D.h"
#include <memory>
#include <vector>

class Slice;

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization.
//! @ingroup algorithms_internal

class SpecularMagneticOldStrategy : public ISpecularStrategy
{
public:
    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and wavevector k
    coeffs_t Execute(const std::vector<Slice>& slices, const kvector_t& k) const;

    coeffs_t Execute(const std::vector<Slice>& slices, const std::vector<complex_t>& kz) const;

}; // class SpecularMagneticOldStrategy

#endif // BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICOLDSTRATEGY_H
