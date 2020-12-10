//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Math/Precomputed.h
//! @brief     Defines namespace Math::Precomputed, providing precomputed constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_BASE_MATH_PRECOMPUTED_H
#define BORNAGAIN_BASE_MATH_PRECOMPUTED_H

#include <array>
#include <utility>
#include <vector>

namespace Math::internal {

template <size_t N> struct ReciprocalFactorial {
    static constexpr double value = ReciprocalFactorial<N - 1>::value / N;
};

template <> struct ReciprocalFactorial<0> { static constexpr double value = 1.0; };

template <template <size_t> class F, size_t... I>
constexpr std::array<double, sizeof...(I)> generateArrayHelper(std::index_sequence<I...>) {
    return {F<I>::value...};
};

} // namespace Math::internal
namespace Math {

//! Returns a compile-time generated std::array of reciprocal factorials.

template <size_t N, typename Indices = std::make_index_sequence<N>>
constexpr std::array<double, N> generateReciprocalFactorialArray() {
    return internal::generateArrayHelper<internal::ReciprocalFactorial>(Indices{});
};
} // namespace Math

#endif // BORNAGAIN_BASE_MATH_PRECOMPUTED_H
#endif // USER_API
