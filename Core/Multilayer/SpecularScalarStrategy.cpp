// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.cpp
//! @brief     Implements class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularScalarStrategy.h"
#include "KzComputation.h"
#include "Layer.h"
#include "LayerRoughness.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "Slice.h"
#include <Eigen/Dense>
#include <stdexcept>
#include <valarray>


const double pi2_15 = std::pow(M_PI_2, 1.5);

std::vector<ScalarRTCoefficients> SpecularScalarStrategy::eval(const std::vector<Slice>& slices,
                                                          kvector_t k) const
{
    std::vector<complex_t> kz = KzComputation::computeReducedKz(slices, k);
    return computeTR(slices, kz);
}

std::vector<ScalarRTCoefficients> SpecularScalarStrategy::eval(const std::vector<Slice>& slices,
                                                          const std::vector<complex_t>& kz) const
{
    if(slices.size() != kz.size())
        throw std::logic_error( "Number of Slices must be equal to the number of kz components" );

    return computeTR(slices, kz);
}


Eigen::Vector2cd SpecularScalarStrategy::transition(complex_t kzi, complex_t kzi1, double sigma, double thickness,
                            const Eigen::Vector2cd& t_r1) const
{
    complex_t roughness = 1;
    if (sigma > 0.0) {
        const double sigeff = pi2_15 * sigma;
        roughness =
            std::sqrt(MathFunctions::tanhc(sigeff * kzi1) / MathFunctions::tanhc(sigeff * kzi));
    }
    const complex_t inv_roughness = 1.0 / roughness;
    const complex_t phase_shift = exp_I(kzi * thickness);
    const complex_t kz_ratio = kzi1 / kzi * roughness;

    const complex_t a00 = 0.5 * (inv_roughness + kz_ratio);
    const complex_t a01 = 0.5 * (inv_roughness - kz_ratio);

    Eigen::Vector2cd result;
    result << (a00 * t_r1(0) + a01 * t_r1(1)) / phase_shift,
        (a01 * t_r1(0) + a00 * t_r1(1)) * phase_shift;
    return result;
}

std::vector<ScalarRTCoefficients> SpecularScalarStrategy::computeTR(const std::vector<Slice>& slices,
                                            const std::vector<complex_t>& kz) const
{
    const size_t N = slices.size();
    std::vector<ScalarRTCoefficients> coeff(N);

    for (size_t i = 0; i < N; ++i)
        coeff[i].kz = kz[i];

    if (N == 1) { // If only one layer present, there's nothing left to calculate
        coeff[0].t_r = {1.0, 0.0};
        return coeff;
    } else if (kz[0] == 0.0) { // If kz in layer 0 is zero, R0 = -T0 and all others equal to 0
        coeff[0].t_r = {1.0, -1.0};
        for (size_t i = 1; i < N; ++i)
            coeff[i].t_r.setZero();
        return coeff;
    }

    // Calculate transmission/refraction coefficients t_r for each layer, from bottom to top.
    size_t start_index = N - 2;
    if (!calculateUpFromLayer(coeff, slices, kz, start_index)) {
        // If excessive damping leads to infinite amplitudes, then use bisection to determine
        // the maximum number of layers for which results remain finite.
        start_index = bisectRTcomputation(coeff, slices, kz, 0, N - 2, (N - 2) / 2);
    }
    setZeroBelow(coeff, start_index + 1);

    // Normalize to incoming downward travelling amplitude = 1.
    complex_t T0 = coeff[0].t_r(0);
    // This trick is used to avoid overflows in the intermediate steps of
    // complex division:
    double tmax = std::max(std::abs(T0.real()), std::abs(T0.imag()));
    if (std::isinf(tmax))
        throw std::runtime_error("Unexpected tmax=infty");
    for (size_t i = 0; i < N; ++i) {
        coeff[i].t_r(0) /= tmax;
        coeff[i].t_r(1) /= tmax;
    }

    // Now the real normalization to T_0 proceeds
    T0 = coeff[0].t_r(0);
    if (std::isinf(abs(T0)))
        throw std::runtime_error("Unexpected tmax=infty");
    for (size_t i = 0; i < N; ++i)
        coeff[i].t_r = coeff[i].t_r / T0;

    return coeff;
}

void SpecularScalarStrategy::setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer) const
{
    size_t N = coeff.size();
    for (size_t i = current_layer + 1; i < N; ++i) {
        coeff[i].t_r.setZero();
    }
}

bool SpecularScalarStrategy::calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff,
                          const std::vector<Slice>& slices, const std::vector<complex_t>& kz,
                          size_t slice_index) const
{
    coeff[slice_index + 1].t_r(0) = 1.0;
    coeff[slice_index + 1].t_r(1) = 0.0;
    for (size_t j = 0; j <= slice_index; ++j) {
        size_t i = slice_index - j; // start from bottom
        double sigma = 0.0;
        if (const auto roughness = GetBottomRoughness(slices, i))
            sigma = roughness->getSigma();

        coeff[i].t_r = transition(kz[i], kz[i + 1], sigma, slices[i].thickness(), coeff[i + 1].t_r);
        if (std::isinf(std::norm(coeff[i].t_r(0))))
            return false; // overflow => retry calulation starting from a higher layer
    }
    return true; // no overflow => result is definitive
}

//! Recursive bisection to determine the number of the deepest layer where RT computation
//! can be started without running into overflow.
//! Computes coeff, and returns largest possible start layer index.
size_t SpecularScalarStrategy::bisectRTcomputation(std::vector<ScalarRTCoefficients>& coeff,
                           const std::vector<Slice>& slices, const std::vector<complex_t>& kz,
                           const size_t lgood, const size_t lbad, const size_t l) const
{
    if (calculateUpFromLayer(coeff, slices, kz, l)) {
        // success => highest valid l must be in l..lbad-1
        if (l + 1 == lbad)
            return l;
        return bisectRTcomputation(coeff, slices, kz, l, lbad, (l + lbad) / 2);
    } else {
        // failure => highest valid l must be in lgood..l-1
        if (l - 1 == lgood) {
            if (!calculateUpFromLayer(coeff, slices, kz, l - 1))
                throw std::runtime_error(
                    "Bisection failed: Unexpected non-monotonicity in RT computation");
            return l - 1;
        }
        return bisectRTcomputation(coeff, slices, kz, lgood, l, (lgood + l) / 2);
    }
}

const LayerRoughness* SpecularScalarStrategy::GetBottomRoughness(const std::vector<Slice>& slices, const size_t slice_index) const
{
    if (slice_index + 1 < slices.size())
        return slices[slice_index + 1].topRoughness();
    return nullptr;
}
