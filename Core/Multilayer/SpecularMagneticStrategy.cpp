// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticStrategy.cpp
//! @brief     Implements class SpecularMagneticStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularMagneticStrategy.h"
#include "Core/Basics/PhysicalConstants.h"
#include "Core/Multilayer/KzComputation.h"
#include "Core/Multilayer/Slice.h"

namespace
{
kvector_t magneticImpact(kvector_t B_field);
Eigen::Vector2cd eigenvalues(complex_t kz, double b_mag);
Eigen::Vector2cd checkForUnderflow(const Eigen::Vector2cd& eigenvs);
complex_t GetImExponential(complex_t exponent);

// The factor 1e-18 is here to have unit: 1/T*nm^-2
constexpr double magnetic_prefactor = PhysConsts::m_n * PhysConsts::g_factor_n * PhysConsts::mu_N
                                      / PhysConsts::h_bar / PhysConsts::h_bar * 1e-18;
} // namespace

ISpecularStrategy::coeffs_t SpecularMagneticStrategy::Execute(const std::vector<Slice>& slices,
                                                              const kvector_t& k) const
{
    return Execute(slices, KzComputation::computeReducedKz(slices, k));
}

ISpecularStrategy::coeffs_t
SpecularMagneticStrategy::Execute(const std::vector<Slice>& slices,
                                  const std::vector<complex_t>& kz) const
{
    if (slices.size() != kz.size())
        throw std::runtime_error("Number of slices does not match the size of the kz-vector");

    ISpecularStrategy::coeffs_t result;
    for (auto& coeff : computeTR(slices, kz))
        result.push_back(std::make_unique<MatrixRTCoefficients_v2>(coeff));

    return result;
}

std::vector<MatrixRTCoefficients_v2>
SpecularMagneticStrategy::computeTR(const std::vector<Slice>& slices,
                                    const std::vector<complex_t>& kzs)
{
    if (slices.size() != kzs.size())
        throw std::runtime_error(
            "Error in SpecularMagnetic_::execute: kz vector and slices size shall coinside.");
    if (slices.empty())
        return {};

    std::vector<MatrixRTCoefficients_v2> result;
    result.reserve(slices.size());

    const double kz_sign = kzs.front().real() > 0.0 ? 1.0 : -1.0; // save sign to restore it later
    const kvector_t b_0 = magneticImpact(slices.front().bField());
    result.emplace_back(kz_sign, eigenvalues(kzs.front(), 0.0), kvector_t{0.0, 0.0, 0.0});
    for (size_t i = 1, size = slices.size(); i < size; ++i) {
        kvector_t b = magneticImpact(slices[i].bField()) - b_0;
        result.emplace_back(kz_sign, checkForUnderflow(eigenvalues(kzs[i], b.mag())), b);
    }

    if (result.front().m_lambda == Eigen::Vector2cd::Zero()) {
        std::for_each(result.begin(), result.end(), [](auto& coeff) { setNoTransmission(coeff); });
        return result;
    }

    std::for_each(result.begin(), result.end(), [](auto& coeff) { calculateTR(coeff); });
    nullifyBottomReflection(result.back());
    propagateBackwardsForwards(result, slices);

    return result;
}

void SpecularMagneticStrategy::calculateTR(MatrixRTCoefficients_v2& coeff)
{
    const double b = coeff.m_b.mag();
    if (b == 0.0) {
        calculateZeroFieldTR(coeff);
        return;
    }

    const double bpbz = b + coeff.m_b.z();
    const double bmbz = b - coeff.m_b.z();
    const complex_t bxmby = coeff.m_b.x() - I * coeff.m_b.y();
    const complex_t bxpby = coeff.m_b.x() + I * coeff.m_b.y();
    const complex_t l_1 = coeff.m_lambda(0);
    const complex_t l_2 = coeff.m_lambda(1);

    auto& T1 = coeff.T1;
    T1 << bmbz, -bxmby, -bmbz * l_1, bxmby * l_1, -bxpby, bpbz, bxpby * l_1, -bpbz * l_1,
        -bmbz / l_1, bxmby / l_1, bmbz, -bxmby, bxpby / l_1, -bpbz / l_1, -bxpby, bpbz;
    T1 /= 4.0 * b;

    auto& R1 = coeff.R1;
    R1 << T1(0, 0), T1(0, 1), -T1(0, 2), -T1(0, 3), T1(1, 0), T1(1, 1), -T1(1, 2), -T1(1, 3),
        -T1(2, 0), -T1(2, 1), T1(2, 2), T1(2, 3), -T1(3, 0), -T1(3, 1), T1(3, 2), T1(3, 3);

    auto& T2 = coeff.T2;
    T2 << bpbz, bxmby, -bpbz * l_2, -bxmby * l_2, bxpby, bmbz, -bxpby * l_2, -bmbz * l_2,
        -bpbz / l_2, -bxmby / l_2, bpbz, bxmby, -bxpby / l_2, -bmbz / l_2, bxpby, bmbz;
    T2 /= 4.0 * b;

    auto& R2 = coeff.R2;
    R2 << T2(0, 0), T2(0, 1), -T2(0, 2), -T2(0, 3), T2(1, 0), T2(1, 1), -T2(1, 2), -T2(1, 3),
        -T2(2, 0), -T2(2, 1), T2(2, 2), T2(2, 3), -T2(3, 0), -T2(3, 1), T2(3, 2), T2(3, 3);
}

void SpecularMagneticStrategy::calculateZeroFieldTR(MatrixRTCoefficients_v2& coeff)
{
    coeff.T1 = Eigen::Matrix4cd::Zero();
    coeff.R1 = Eigen::Matrix4cd::Zero();
    coeff.T2 = Eigen::Matrix4cd::Zero();
    coeff.R2 = Eigen::Matrix4cd::Zero();

    // lambda_1 == lambda_2, no difference which one to use
    const complex_t eigen_value = coeff.m_lambda(0);

    Eigen::Matrix3cd Tblock;
    Tblock << 0.5, 0.0, -0.5 * eigen_value, 0.0, 0.0, 0.0, -0.5 / eigen_value, 0.0, 0.5;

    Eigen::Matrix3cd Rblock;
    Rblock << 0.5, 0.0, 0.5 * eigen_value, 0.0, 0.0, 0.0, 0.5 / eigen_value, 0.0, 0.5;

    coeff.T1.block<3, 3>(1, 1) = Tblock;
    coeff.R1.block<3, 3>(1, 1) = Rblock;
    coeff.T2.block<3, 3>(0, 0) = Tblock;
    coeff.R2.block<3, 3>(0, 0) = Rblock;
}

void SpecularMagneticStrategy::setNoTransmission(MatrixRTCoefficients_v2& coeff)
{
    coeff.m_w_plus = Eigen::Vector4cd::Zero();
    coeff.m_w_min = Eigen::Vector4cd::Zero();
    coeff.T1 = Eigen::Matrix4cd::Identity() / 4.0;
    coeff.R1 = coeff.T1;
    coeff.T2 = coeff.T1;
    coeff.R2 = coeff.T1;
}

void SpecularMagneticStrategy::nullifyBottomReflection(MatrixRTCoefficients_v2& coeff)
{
    const complex_t l_1 = coeff.m_lambda(0);
    const complex_t l_2 = coeff.m_lambda(1);
    const double b_mag = coeff.m_b.mag();
    const kvector_t& b = coeff.m_b;

    if (b_mag == 0.0) {
        // both eigenvalues are the same, no difference which one to take
        coeff.m_w_plus << -l_1, 0.0, 1.0, 0.0;
        coeff.m_w_min << 0.0, -l_1, 0.0, 1.0;
        return;
    }

    // First basis vector that has no upward going wave amplitude
    coeff.m_w_min(0) = (b.x() - I * b.y()) * (l_1 - l_2) / 2.0 / b_mag;
    coeff.m_w_min(1) = b.z() * (l_2 - l_1) / 2.0 / b_mag - (l_1 + l_2) / 2.0;
    coeff.m_w_min(2) = 0.0;
    coeff.m_w_min(3) = 1.0;

    // Second basis vector that has no upward going wave amplitude
    coeff.m_w_plus(0) = -(l_1 + l_2) / 2.0 - b.z() / (l_1 + l_2);
    coeff.m_w_plus(1) = (b.x() + I * b.y()) * (l_1 - l_2) / 2.0 / b_mag;
    coeff.m_w_plus(2) = 1.0;
    coeff.m_w_plus(3) = 0.0;
}

void SpecularMagneticStrategy::propagateBackwardsForwards(
    std::vector<MatrixRTCoefficients_v2>& coeff, const std::vector<Slice>& slices)
{
    const int size = static_cast<int>(coeff.size());
    std::vector<Eigen::Matrix2cd> SMatrices(coeff.size());
    std::vector<complex_t> Normalization(coeff.size());

    for (int index = size - 2; index >= 0; --index) {
        const size_t i = static_cast<size_t>(index);
        const double t = slices[i].thickness();
        const auto kz = coeff[i].getKz();
        const Eigen::Matrix4cd l = coeff[i].R1 * GetImExponential(kz(0) * t)
                             + coeff[i].T1 * GetImExponential(-kz(0) * t)
                             + coeff[i].R2 * GetImExponential(kz(1) * t)
                             + coeff[i].T2 * GetImExponential(-kz(1) * t);
        coeff[i].m_w_plus = l * coeff[i + 1].m_w_plus;
        coeff[i].m_w_min = l * coeff[i + 1].m_w_min;

        // rotate and normalize polarization
        const auto Snorm = findNormalizationCoefficients(coeff[i]);
        auto S = Snorm.first;
        auto norm = Snorm.second;

        SMatrices[i] = S;
        Normalization[i] = norm;

        const complex_t a_plus = S(0, 0) / norm;
        const complex_t b_plus = S(1, 0) / norm;
        const complex_t a_min = S(0, 1) / norm;
        const complex_t b_min = S(1, 1) / norm;

        const Eigen::Vector4cd w_plus = a_plus * coeff[i].m_w_plus + b_plus * coeff[i].m_w_min;
        const Eigen::Vector4cd w_min = a_min * coeff[i].m_w_plus + b_min * coeff[i].m_w_min;

        coeff[i].m_w_plus = std::move(w_plus);
        coeff[i].m_w_min = std::move(w_min);
    }

    complex_t dumpingFactor = 1;
    Eigen::Matrix2cd S = Eigen::Matrix2cd::Identity();
    for (size_t i = 1; i < coeff.size(); ++i) {
        dumpingFactor = dumpingFactor * Normalization[i - 1];
        S = SMatrices[i - 1] * S;

        if (std::isinf(std::norm(dumpingFactor))) {
            // not entirely sure, whether this is the correct edge case
            std::for_each(coeff.begin() + i, coeff.end(),
                          [](auto& coeff) { setNoTransmission(coeff); });
            break;
        }

        const complex_t a_plus = S(0, 0) / dumpingFactor;
        const complex_t b_plus = S(1, 0) / dumpingFactor;
        const complex_t a_min = S(0, 1) / dumpingFactor;
        const complex_t b_min = S(1, 1) / dumpingFactor;

        Eigen::Vector4cd w_plus = a_plus * coeff[i].m_w_plus + b_plus * coeff[i].m_w_min;
        Eigen::Vector4cd w_min = a_min * coeff[i].m_w_plus + b_min * coeff[i].m_w_min;

        coeff[i].m_w_plus = std::move(w_plus);
        coeff[i].m_w_min = std::move(w_min);
    }
}

std::pair<Eigen::Matrix2cd, complex_t>
SpecularMagneticStrategy::findNormalizationCoefficients(const MatrixRTCoefficients_v2& coeff)
{
    const Eigen::Vector2cd Ta = coeff.T1plus() + coeff.T2plus();
    const Eigen::Vector2cd Tb = coeff.T1min() + coeff.T2min();

    Eigen::Matrix2cd S;
    S << Ta(0), Tb(0), Ta(1), Tb(1);

    Eigen::Matrix2cd SInverse;
    SInverse << S(1, 1), -S(0, 1), -S(1, 0), S(0, 0);
    const complex_t d1 = S(1, 1) - S(0, 1);
    const complex_t d2 = S(1, 0) - S(0, 0);
    const complex_t denominator = S(0, 0) * d1 - d2 * S(0, 1);

    return {SInverse, denominator};
}

namespace
{
kvector_t magneticImpact(kvector_t B_field)
{
    return -magnetic_prefactor * B_field;
}

Eigen::Vector2cd eigenvalues(complex_t kz, double b_mag)
{
    const complex_t a = kz * kz;
    return {I * std::sqrt(a + b_mag), I * std::sqrt(a - b_mag)};
}

Eigen::Vector2cd checkForUnderflow(const Eigen::Vector2cd& eigenvs)
{
    auto lambda = [](complex_t value) { return std::abs(value) < 1e-40 ? 1e-40 : value; };
    return {lambda(eigenvs(0)), lambda(eigenvs(1))};
}

complex_t GetImExponential(complex_t exponent)
{
    if (exponent.imag() > -std::log(std::numeric_limits<double>::min()))
        return 0.0;
    return std::exp(I * exponent);
}
} // namespace
