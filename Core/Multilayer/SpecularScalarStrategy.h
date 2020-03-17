// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.h
//! @brief     Defines namespace SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARMATRIX_H
#define SPECULARMATRIX_H

#include "ISpecularStrategy.h"
#include "ScalarRTCoefficients.h"
#include "Vectors3D.h"
#include <vector>


class SpecularScalarStrategy : public ISpecularStrategy
{
public:
    //! Computes refraction angles and transmission/reflection coefficients
    //! for given coherent wave propagation in a multilayer.
    //! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
    virtual std::vector<ScalarRTCoefficients> eval(const std::vector<Slice>& slices,
                                                           kvector_t k) const;

    //! Computes transmission/reflection coefficients
    //! for given set of z-components of wave-vectors in a multilayer.
    //! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
    virtual std::vector<ScalarRTCoefficients> eval(const std::vector<Slice>& slices,
                                                           const std::vector<complex_t>& kz) const;

private:
    Eigen::Vector2cd transition(complex_t kzi, complex_t kzi1, double sigma, double thickness,
                                const Eigen::Vector2cd& t_r1) const;

    std::vector<ScalarRTCoefficients> computeTR(const std::vector<Slice>& slices,
                                                const std::vector<complex_t>& kz) const;

    void setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer) const;


    bool calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff,
                              const std::vector<Slice>& slices, const std::vector<complex_t>& kz,
                              size_t layer_index) const;
    size_t bisectRTcomputation(std::vector<ScalarRTCoefficients>& coeff,
                               const std::vector<Slice>& slices, const std::vector<complex_t>& kz,
                               const size_t lgood, const size_t lbad, const size_t l) const;
    const LayerRoughness* GetBottomRoughness(const std::vector<Slice>& slices,
                                             const size_t slice_index) const;

};

//class Slice;

//! Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer.
//! @ingroup algorithms_internal



#endif // SPECULARMATRIX_H
