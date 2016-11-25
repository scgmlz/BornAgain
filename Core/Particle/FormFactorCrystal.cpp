// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorCrystal.cpp
//! @brief     Implements class FormFactorCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCrystal.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "WavevectorPair.h"

FormFactorCrystal::FormFactorCrystal(const Lattice& lattice, const IFormFactor& basis_form_factor,
                                     const IFormFactor& meso_form_factor)
    : m_lattice(lattice),
      mp_basis_form_factor(basis_form_factor.clone()),
      mp_meso_form_factor(meso_form_factor.clone())
{
    setName(BornAgain::FormFactorCrystalType);
    calculateLargestReciprocalDistance();
}

FormFactorCrystal::~FormFactorCrystal()
{
    delete mp_basis_form_factor;
    delete mp_meso_form_factor;
}

complex_t FormFactorCrystal::evaluate(const WavevectorPair& wavevectors) const
{
    // retrieve reciprocal lattice vectors within reasonable radius
    cvector_t q = wavevectors.getQ();
    double radius = 2.1 * m_max_rec_length;
    std::vector<kvector_t> rec_vectors =
        m_lattice.reciprocalLatticeVectorsWithinRadius(q.real(), radius);

    // perform convolution on these lattice vectors
    complex_t result(0.0, 0.0);
    for (const auto& rec: rec_vectors) {
        WavevectorPair basis_wavevectors(kvector_t(), -rec);
        complex_t basis_factor = mp_basis_form_factor->evaluate(basis_wavevectors);
        WavevectorPair meso_wavevectors(cvector_t(), rec.complex()-q);
        complex_t meso_factor = mp_meso_form_factor->evaluate(meso_wavevectors);
        result += basis_factor * meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    double volume = m_lattice.getVolume();
    return result / volume;
}

Eigen::Matrix2cd FormFactorCrystal::evaluatePol(const WavevectorPair& wavevectors) const
{
    // retrieve reciprocal lattice vectors within reasonable radius
    cvector_t q = wavevectors.getQ();
    double radius = 2.1 * m_max_rec_length;
    std::vector<kvector_t> rec_vectors =
        m_lattice.reciprocalLatticeVectorsWithinRadius(q.real(), radius);

    // perform convolution on these lattice vectors
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (const auto& rec: rec_vectors) {
        WavevectorPair basis_wavevectors(kvector_t(), -rec);
        Eigen::Matrix2cd basis_factor = mp_basis_form_factor->evaluatePol(basis_wavevectors);
        WavevectorPair meso_wavevectors(cvector_t(), rec.complex()-q);
        complex_t meso_factor = mp_meso_form_factor->evaluate(meso_wavevectors);
        result += basis_factor * meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    double volume = m_lattice.getVolume();
    return result / volume;
}

void FormFactorCrystal::calculateLargestReciprocalDistance()
{
    kvector_t a1 = m_lattice.getBasisVectorA();
    kvector_t a2 = m_lattice.getBasisVectorB();
    kvector_t a3 = m_lattice.getBasisVectorC();

    m_max_rec_length = std::max(M_PI / a1.mag(), M_PI / a2.mag());
    m_max_rec_length = std::max(m_max_rec_length, M_PI / a3.mag());
}
