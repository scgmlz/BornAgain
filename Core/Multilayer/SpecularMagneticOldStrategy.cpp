// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticOldStrategy.cpp
//! @brief     Implements class SpecularMagneticOldStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularMagneticOldStrategy.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/Slice.h"
#include "Core/Vector/WavevectorInfo.h"
#include <Eigen/LU>

namespace
{
void CalculateEigenvalues(const std::vector<Slice>& slices, const kvector_t k,
                          std::vector<MatrixRTCoefficients>& coeff);
void CalculateTransferAndBoundary(const std::vector<Slice>& slices,
                                  std::vector<MatrixRTCoefficients>& coeff);
void SetForNoTransmission(std::vector<MatrixRTCoefficients>& coeff);
complex_t GetImExponential(complex_t exponent);
const complex_t I(0, 1);
} // namespace

ISpecularStrategy::coeffs_t SpecularMagneticOldStrategy::Execute(const std::vector<Slice>& slices,
                                                                 const kvector_t& k) const
{
    std::vector<MatrixRTCoefficients> result(slices.size());
    CalculateEigenvalues(slices, k, result);
    CalculateTransferAndBoundary(slices, result);

    coeffs_t resultConvert;
    for (auto& coeff : result)
        resultConvert.push_back(std::make_unique<MatrixRTCoefficients>(coeff));

    return resultConvert;
}

ISpecularStrategy::coeffs_t
SpecularMagneticOldStrategy::Execute(const std::vector<Slice>&, const std::vector<complex_t>&) const
{
    throw std::runtime_error("Not implemented");
}

namespace
{
void CalculateEigenvalues(const std::vector<Slice>& slices, const kvector_t k,
                          std::vector<MatrixRTCoefficients>& coeff)
{
    double mag_k = k.mag();
    double n_ref = slices[0].material().refractiveIndex(2 * M_PI / mag_k).real();
    double sign_kz = k.z() > 0.0 ? -1.0 : 1.0;
    for (size_t i = 0; i < coeff.size(); ++i) {
        coeff[i].m_scatt_matrix = slices[i].polarizedReducedPotential(k, n_ref);
        coeff[i].m_kt = mag_k * slices[i].thickness();
        coeff[i].m_a = coeff[i].m_scatt_matrix.trace() / 2.0;
        coeff[i].m_b_mag =
            sqrt(coeff[i].m_a * coeff[i].m_a - coeff[i].m_scatt_matrix.determinant());
        coeff[i].m_bz = (coeff[i].m_scatt_matrix(0, 0) - coeff[i].m_scatt_matrix(1, 1)) / 2.0;
        complex_t rad0 = coeff[i].m_a - coeff[i].m_b_mag;
        complex_t rad1 = coeff[i].m_a + coeff[i].m_b_mag;
        // use small absorptive component for layers with i>0 if radicand becomes very small:
        if (i > 0) {
            if (std::abs(rad0) < 1e-40)
                rad0 = I * 1e-40;
            if (std::abs(rad1) < 1e-40)
                rad1 = I * 1e-40;
        }
        coeff[i].lambda(0) = sqrt(rad0);
        coeff[i].lambda(1) = sqrt(rad1);
        coeff[i].kz = mag_k * coeff[i].lambda * sign_kz;
    }
}

// todo: avoid overflows (see SpecularMatrix.cpp)
void CalculateTransferAndBoundary(const std::vector<Slice>& slices,
                                  std::vector<MatrixRTCoefficients>& coeff)
{
    size_t N = coeff.size();
    if (coeff[0].lambda == Eigen::Vector2cd::Zero() && N > 1) {
        SetForNoTransmission(coeff);
        return;
    }

    // First, initialize bottom layer values to have no reflection
    coeff[N - 1].initializeBottomLayerPhiPsi();
    if (N > 1)
        coeff[N - 1].calculateTRMatrices();

    coeff[0].calculateTRMatrices();
    for (int signed_index = static_cast<int>(N) - 2; signed_index > 0; --signed_index) {
        size_t i = static_cast<size_t>(signed_index);
        double t = slices[i].thickness();
        coeff[i].calculateTRMatrices();
        Eigen::Matrix4cd l = coeff[i].R1m * GetImExponential(coeff[i].kz(0) * t)
                             + coeff[i].T1m * GetImExponential(-coeff[i].kz(0) * t)
                             + coeff[i].R2m * GetImExponential(coeff[i].kz(1) * t)
                             + coeff[i].T2m * GetImExponential(-coeff[i].kz(1) * t);
        coeff[i].phi_psi_plus = l * coeff[i + 1].phi_psi_plus;
        coeff[i].phi_psi_min = l * coeff[i + 1].phi_psi_min;
    }
    // If more than one layer, impose normalization and correct correspondence
    // for spin-z polarization in top layer
    if (N > 1) {
        // First layer boundary is also top layer boundary:
        coeff[0].phi_psi_plus = coeff[1].phi_psi_plus;
        coeff[0].phi_psi_min = coeff[1].phi_psi_min;
        // Normalize all boundary values such that top layer has unit wave
        // amplitude for both spin up and down (and does not contain a
        // transmitted wave amplitude for the opposite polarization)
        Eigen::Vector2cd T0basisA = coeff[0].T1plus() + coeff[0].T2plus();
        Eigen::Vector2cd T0basisB = coeff[0].T1min() + coeff[0].T2min();
        complex_t cpA, cpB, cmA, cmB;
        cpA = T0basisB(1);
        cpB = -T0basisA(1);
        cmA = T0basisB(0);
        cmB = -T0basisA(0);
        Eigen::Vector4cd phipsitemp = cpA * coeff[0].phi_psi_plus + cpB * coeff[0].phi_psi_min;
        coeff[0].phi_psi_min = cmA * coeff[0].phi_psi_plus + cmB * coeff[0].phi_psi_min;
        coeff[0].phi_psi_plus = phipsitemp;
        Eigen::Vector2cd T0plusV = coeff[0].T1plus() + coeff[0].T2plus();
        Eigen::Vector2cd T0minV = coeff[0].T1min() + coeff[0].T2min();
        complex_t T0plus = T0plusV(0);
        complex_t T0min = T0minV(1);
        coeff[0].phi_psi_min = coeff[0].phi_psi_min / T0min;
        coeff[0].phi_psi_plus = coeff[0].phi_psi_plus / T0plus;
        for (size_t i = 1; i < N; ++i) {
            phipsitemp = (cpA * coeff[i].phi_psi_plus + cpB * coeff[i].phi_psi_min) / T0plus;
            coeff[i].phi_psi_min =
                (cmA * coeff[i].phi_psi_plus + cmB * coeff[i].phi_psi_min) / T0min;
            coeff[i].phi_psi_plus = phipsitemp;
        }
    }
}

void SetForNoTransmission(std::vector<MatrixRTCoefficients>& coeff)
{
    size_t N = coeff.size();
    for (size_t i = 0; i < N; ++i) {
        coeff[i].phi_psi_plus.setZero();
        coeff[i].phi_psi_min.setZero();
        coeff[i].T1m = Eigen::Matrix4cd::Identity() / 4.0;
        coeff[i].R1m = coeff[i].T1m;
        coeff[i].T2m = coeff[i].T1m;
        coeff[i].R2m = coeff[i].T1m;
    }
}

complex_t GetImExponential(complex_t exponent)
{
    if (exponent.imag() > -std::log(std::numeric_limits<double>::min()))
        return 0.0;
    return std::exp(I * exponent);
}
} // unnamed namespace
