// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularScalarStrategy.cpp
//! @brief     Implements class SpecularScalarStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularScalarStrategy.h"
#include "Core/Multilayer/KzComputation.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/Slice.h"
#include <Eigen/Dense>
#include <stdexcept>

namespace
{
const LayerRoughness* GetBottomRoughness(const std::vector<Slice>& slices,
                                         const size_t slice_index);
} // namespace

ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector<Slice>& slices,
                                                            const kvector_t& k) const
{
    std::vector<complex_t> kz = KzComputation::computeReducedKz(slices, k);
    return Execute(slices, kz);
}

ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector<Slice>& slices,
                                                            const std::vector<complex_t>& kz) const
{
    if (slices.size() != kz.size())
        throw std::runtime_error("Number of slices does not match the size of the kz-vector");

    ISpecularStrategy::coeffs_t result;
    for (auto& coeff : computeTR(slices, kz))
        result.push_back(std::make_unique<ScalarRTCoefficients>(coeff));

    return result;
}

std::vector<ScalarRTCoefficients>
SpecularScalarStrategy::computeTR(const std::vector<Slice>& slices,
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
    calculateUpFromLayer(coeff, slices, kz);
    return coeff;
}

void SpecularScalarStrategy::setZeroBelow(std::vector<ScalarRTCoefficients>& coeff,
                                          size_t current_layer)
{
    size_t N = coeff.size();
    for (size_t i = current_layer + 1; i < N; ++i) {
        coeff[i].t_r.setZero();
    }
}

void SpecularScalarStrategy::calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff,
                                                  const std::vector<Slice>& slices,
                                                  const std::vector<complex_t>& kz) const
{
    auto N = slices.size();

    coeff.back().t_r(0) = 1.0;
    coeff.back().t_r(1) = 0.0;
    std::vector<complex_t> factors(N - 1);
    for (int i = N - 2; i >= 0; i--) {
        double sigma = 0.0;
        if (const auto roughness = GetBottomRoughness(slices, i))
            sigma = roughness->getSigma();

        const auto mpmm = transition(kz[i], kz[i + 1], sigma);
        const complex_t mp = mpmm.first;
        const complex_t mm = mpmm.second;

        const complex_t delta = exp_I(kz[i] * slices[i].thickness());

        complex_t S = mp + mm * coeff[i + 1].t_r(1);
        S = 1. / S * delta;
        factors[i] = S;

        coeff[i].t_r(1) = delta * (mm + mp * coeff[i + 1].t_r(1)) * S;
    }

    // now correct all amplitudes by dividing the with the remaining factors in forward direction
    // at some point this divison underflows, which is the point when all further amplitudes are set
    // to zero
    complex_t dumpingFactor = 1;
    for (size_t j = 1; j < N; ++j) {
        dumpingFactor = dumpingFactor * factors[j - 1];

        coeff[j].t_r(0) = dumpingFactor;
        coeff[j].t_r(1) *= dumpingFactor;
    }
}

namespace
{
const LayerRoughness* GetBottomRoughness(const std::vector<Slice>& slices, const size_t slice_index)
{
    if (slice_index + 1 < slices.size())
        return slices[slice_index + 1].topRoughness();
    return nullptr;
}
} // namespace
