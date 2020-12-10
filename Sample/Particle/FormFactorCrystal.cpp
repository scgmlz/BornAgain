//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/FormFactorCrystal.cpp
//! @brief     Implements class FormFactorCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Particle/FormFactorCrystal.h"
#include "Base/Math/Constants.h"
#include "Sample/Material/WavevectorInfo.h"

FormFactorCrystal::FormFactorCrystal(const Lattice3D& lattice, const IFormFactor& basis_form_factor,
                                     const IFormFactor& meso_form_factor, double position_variance)
    : m_lattice(lattice)
    , m_basis_form_factor(basis_form_factor.clone())
    , m_meso_form_factor(meso_form_factor.clone())
    , m_position_variance(position_variance) {
    setName("FormFactorCrystal");
    calculateLargestReciprocalDistance();
}

FormFactorCrystal::~FormFactorCrystal() {
    delete m_basis_form_factor;
    delete m_meso_form_factor;
}

double FormFactorCrystal::bottomZ(const IRotation& rotation) const {
    return m_meso_form_factor->bottomZ(rotation);
}

double FormFactorCrystal::topZ(const IRotation& rotation) const {
    return m_meso_form_factor->topZ(rotation);
}

complex_t FormFactorCrystal::evaluate(const WavevectorInfo& wavevectors) const {
    // retrieve reciprocal lattice vectors within reasonable radius
    cvector_t q = wavevectors.getQ();
    double radius = 2.1 * m_max_rec_length;
    std::vector<kvector_t> rec_vectors =
        m_lattice.reciprocalLatticeVectorsWithinRadius(q.real(), radius);

    // perform convolution on these lattice vectors
    complex_t result(0.0, 0.0);
    for (const auto& rec : rec_vectors) {
        auto dw_factor = debyeWallerFactor(rec);
        WavevectorInfo basis_wavevectors(kvector_t(), -rec, wavevectors.wavelength());
        complex_t basis_factor = m_basis_form_factor->evaluate(basis_wavevectors);
        WavevectorInfo meso_wavevectors(cvector_t(), rec.complex() - q, wavevectors.wavelength());
        complex_t meso_factor = m_meso_form_factor->evaluate(meso_wavevectors);
        result += dw_factor * basis_factor * meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    return result / m_lattice.unitCellVolume();
}

Eigen::Matrix2cd FormFactorCrystal::evaluatePol(const WavevectorInfo& wavevectors) const {
    // retrieve reciprocal lattice vectors within reasonable radius
    cvector_t q = wavevectors.getQ();
    double radius = 2.1 * m_max_rec_length;
    std::vector<kvector_t> rec_vectors =
        m_lattice.reciprocalLatticeVectorsWithinRadius(q.real(), radius);

    // perform convolution on these lattice vectors
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (const auto& rec : rec_vectors) {
        auto dw_factor = debyeWallerFactor(rec);
        WavevectorInfo basis_wavevectors(kvector_t(), -rec, wavevectors.wavelength());
        Eigen::Matrix2cd basis_factor = m_basis_form_factor->evaluatePol(basis_wavevectors);
        WavevectorInfo meso_wavevectors(cvector_t(), rec.complex() - q, wavevectors.wavelength());
        complex_t meso_factor = m_meso_form_factor->evaluate(meso_wavevectors);
        result += dw_factor * basis_factor * meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    return result / m_lattice.unitCellVolume();
}

void FormFactorCrystal::calculateLargestReciprocalDistance() {
    kvector_t a1 = m_lattice.getBasisVectorA();
    kvector_t a2 = m_lattice.getBasisVectorB();
    kvector_t a3 = m_lattice.getBasisVectorC();

    m_max_rec_length = std::max(M_PI / a1.mag(), M_PI / a2.mag());
    m_max_rec_length = std::max(m_max_rec_length, M_PI / a3.mag());
}

complex_t FormFactorCrystal::debyeWallerFactor(const kvector_t& q_i) const {
    auto q2 = q_i.mag2();
    return std::exp(-q2 * m_position_variance / 2.0);
}
