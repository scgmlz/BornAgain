// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/KzComputation.cpp
//! @brief     Implements functions from KzComputation namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/KzComputation.h"
#include "Core/Basics/Units.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/Slice.h"

namespace
{
complex_t normalizedSLD(const Material& material);

// use small imaginary value if passed argument is very small
complex_t checkForUnderflow(complex_t val);
} // namespace

std::vector<complex_t> KzComputation::computeReducedKz(const std::vector<Slice>& slices,
                                                       kvector_t k)
{
    const size_t N = slices.size();
    const double n_ref = slices[0].material().refractiveIndex(2 * M_PI / k.mag()).real();
    const double k_base = k.mag() * (k.z() > 0.0 ? -1 : 1);

    std::vector<complex_t> kz(N);
    // Calculate refraction angle, expressed as k_z, for each layer.
    complex_t rad = slices[0].scalarReducedPotential(k, n_ref);
    kz[0] = k_base * std::sqrt(rad);
    for (size_t i = 1; i < N; ++i) {
        rad = checkForUnderflow(slices[i].scalarReducedPotential(k, n_ref));
        kz[i] = k_base * std::sqrt(rad);
    }
    return kz;
}

std::vector<complex_t> KzComputation::computeKzFromSLDs(const std::vector<Slice>& slices, double kz)
{
    const size_t N = slices.size();
    const double k_sign = kz > 0.0 ? -1 : 1;
    std::vector<complex_t> result(N);

    complex_t kz2_base = kz * kz + normalizedSLD(slices[0].material());
    result[0] = -kz;
    // Calculate refraction angle, expressed as k_z, for each layer.
    for (size_t i = 1; i < N; ++i) {
        complex_t kz2 = checkForUnderflow(kz2_base - normalizedSLD(slices[i].material()));
        result[i] = k_sign * std::sqrt(kz2);
    }
    return result;
}

std::vector<complex_t> KzComputation::computeKzFromRefIndices(const std::vector<Slice>& slices,
                                                              kvector_t k)
{
    const size_t N = slices.size();
    const double kz_val = k.z();
    const double k_sign = kz_val > 0.0 ? -1 : 1;
    const double k2 = k.mag2();
    const double kz2 = kz_val * kz_val;
    const double wl = 2 * M_PI / std::sqrt(k2);
    const complex_t n2_ref = slices[0].material().refractiveIndex2(wl);

    std::vector<complex_t> kz(N);
    kz[0] = -kz_val;
    for (size_t i = 1; i < N; ++i) {
        const complex_t n2_norm = slices[i].material().refractiveIndex2(wl) - n2_ref;
        kz[i] = k_sign * std::sqrt(checkForUnderflow(k2 * n2_norm + kz2));
    }
    return kz;
}

namespace
{
complex_t normalizedSLD(const Material& material)
{
    if (material.typeID() != MATERIAL_TYPES::MaterialBySLD)
        throw std::runtime_error("Error in normalizedSLD: passed material has wrong type");

    complex_t sld = std::conj(material.materialData()) / (Units::angstrom * Units::angstrom);
    sld *= 4.0 * M_PI;
    return sld;
}

complex_t checkForUnderflow(complex_t val)
{
    return std::norm(val) < 1e-80 ? complex_t(0.0, 1e-40) : val;
}
} // namespace
