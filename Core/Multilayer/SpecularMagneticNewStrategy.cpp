// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticNewStrategy.cpp
//! @brief     Implements class SpecularMagneticNewStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularMagneticNewStrategy.h"
#include "Core/Basics/PhysicalConstants.h"
#include "Core/Multilayer/KzComputation.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/Slice.h"

namespace
{
double magneticSLD(kvector_t B_field);
Eigen::Vector2cd eigenvalues(complex_t kz, double b_mag);
Eigen::Vector2cd checkForUnderflow(const Eigen::Vector2cd& eigenvs);

// The factor 1e-18 is here to have unit: 1/T*nm^-2
constexpr double magnetic_prefactor = PhysConsts::m_n * PhysConsts::g_factor_n * PhysConsts::mu_N
                                      / PhysConsts::h_bar / PhysConsts::h_bar / 4. / M_PI * 1e-18;
const auto eps = std::numeric_limits<double>::epsilon() * 10.;
const LayerRoughness* GetBottomRoughness(const std::vector<Slice>& slices,
                                         const size_t slice_index);
} // namespace

ISpecularStrategy::coeffs_t SpecularMagneticNewStrategy::Execute(const std::vector<Slice>& slices,
                                                                 const kvector_t& k) const
{
    return Execute(slices, KzComputation::computeReducedKz(slices, k));
}

ISpecularStrategy::coeffs_t
SpecularMagneticNewStrategy::Execute(const std::vector<Slice>& slices,
                                     const std::vector<complex_t>& kz) const
{
    if (slices.size() != kz.size())
        throw std::runtime_error("Number of slices does not match the size of the kz-vector");

    ISpecularStrategy::coeffs_t result;
    for (auto& coeff : computeTR(slices, kz))
        result.push_back(std::make_unique<MatrixRTCoefficients_v3>(coeff));

    return result;
}

std::vector<MatrixRTCoefficients_v3>
SpecularMagneticNewStrategy::computeTR(const std::vector<Slice>& slices,
                                       const std::vector<complex_t>& kzs) const
{
    const size_t N = slices.size();

    if (slices.size() != kzs.size())
        throw std::runtime_error(
            "Error in SpecularMagnetic_::execute: kz vector and slices size shall coinside.");
    if (slices.empty())
        return {};

    std::vector<MatrixRTCoefficients_v3> result;
    result.reserve(N);

    const double kz_sign = kzs.front().real() >= 0.0 ? 1.0 : -1.0; // save sign to restore it later

    auto B_0 = slices.front().bField();
    result.emplace_back(kz_sign, eigenvalues(kzs.front(), 0.0), kvector_t{0.0, 0.0, 0.0}, 0.0);
    for (size_t i = 1, size = slices.size(); i < size; ++i) {
        auto B = slices[i].bField() - B_0;
        auto magnetic_SLD = magneticSLD(B);
        result.emplace_back(kz_sign, checkForUnderflow(eigenvalues(kzs[i], magnetic_SLD)),
                            B.mag() > eps ? B / B.mag() : kvector_t{0.0, 0.0, 0.0}, magnetic_SLD);
    }

    if (N == 1) {
        result[0].m_T = Eigen::Matrix2cd::Identity();
        result[0].m_R = Eigen::Matrix2cd::Zero();
        return result;

    } else if (kzs[0] == 0.) {
        result[0].m_T = Eigen::Matrix2cd::Identity();
        result[0].m_R = -Eigen::Matrix2cd::Identity();
        for (size_t i = 1; i < N; ++i) {
            result[i].m_T.setZero();
            result[i].m_R.setZero();
        }
        return result;
    }

    calculateUpwards(result, slices);

    return result;
}

void SpecularMagneticNewStrategy::calculateUpwards(std::vector<MatrixRTCoefficients_v3>& coeff,
                                                   const std::vector<Slice>& slices) const
{
    const auto N = slices.size();
    std::vector<Eigen::Matrix2cd> SMatrices(N - 1);
    std::vector<complex_t> Normalization(N - 1);

    // bottom boundary condition
    coeff.back().m_T = Eigen::Matrix2cd::Identity();
    coeff.back().m_R = Eigen::Matrix2cd::Zero();

    for (int i = N - 2; i >= 0; --i) {
        double sigma = 0.;
        if (const auto roughness = GetBottomRoughness(slices, i))
            sigma = roughness->getSigma();

        // compute the 2x2 submatrices in the write-up denoted as P+, P- and delta
        const auto mpmm = computeBackwardsSubmatrices(coeff[i], coeff[i + 1], sigma);
        const Eigen::Matrix2cd mp = mpmm.first;
        const Eigen::Matrix2cd mm = mpmm.second;

        const Eigen::Matrix2cd delta = coeff[i].computeDeltaMatrix(slices[i].thickness());

        // compute the rotation matrix
        Eigen::Matrix2cd S, Si;
        Si = mp + mm * coeff[i + 1].m_R;
        S << Si(1, 1), -Si(0, 1), -Si(1, 0), Si(0, 0);
        const complex_t norm = S(0, 0) * S(1, 1) - S(0, 1) * S(1, 0);
        S = S * delta;

        // store the rotation matrix and normalization constant in order to rotate
        // the coefficients for all lower slices at the end of the computation
        SMatrices[i] = S;
        Normalization[i] = norm;

        // compute the reflection matrix and
        // rotate the polarization such that we have pure incoming states (T = I)
        S /= norm;

        // T is always equal to the identity at this point, no need to store
        coeff[i].m_R = delta * (mm + mp * coeff[i + 1].m_R) * S;
    }

    // now correct all amplitudes in forward direction by dividing with the remaining
    // normalization constants. In addition rotate the polarization by the amount
    // that was rotated above the current interface
    // if the normalization overflows, all amplitudes below that point are set to zero
    complex_t dumpingFactor = 1;
    Eigen::Matrix2cd S = Eigen::Matrix2cd::Identity();
    for (size_t i = 1; i < N; ++i) {
        dumpingFactor = dumpingFactor * Normalization[i - 1];
        S = SMatrices[i - 1] * S;

        if (std::isinf(std::norm(dumpingFactor))) {
            std::for_each(coeff.begin() + i, coeff.end(), [](auto& coeff) {
                coeff.m_T = Eigen::Matrix2cd::Zero();
                coeff.m_R = Eigen::Matrix2cd::Zero();
            });
            break;
        }

        coeff[i].m_T = S / dumpingFactor; // T * S omitted, since T is always I
        coeff[i].m_R *= S / dumpingFactor;
    }
}

namespace
{
double magneticSLD(kvector_t B_field)
{
    return magnetic_prefactor * B_field.mag();
}

Eigen::Vector2cd eigenvalues(complex_t kz, double magnetic_SLD)
{
    const complex_t a = kz * kz;
    return {std::sqrt(a - 4. * M_PI * magnetic_SLD), std::sqrt(a + 4. * M_PI * magnetic_SLD)};
}

Eigen::Vector2cd checkForUnderflow(const Eigen::Vector2cd& eigenvs)
{
    auto lambda = [](complex_t value) { return std::abs(value) < 1e-40 ? 1e-40 : value; };
    return {lambda(eigenvs(0)), lambda(eigenvs(1))};
}

const LayerRoughness* GetBottomRoughness(const std::vector<Slice>& slices, const size_t slice_index)
{
    if (slice_index + 1 < slices.size())
        return slices[slice_index + 1].topRoughness();
    return nullptr;
}
} // namespace
