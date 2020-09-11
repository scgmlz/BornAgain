// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Precomputed.h
//! @brief     Defines namespace Precomputed, providing precomputed constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_TOOLS_PRECOMPUTED_H
#define BORNAGAIN_CORE_TOOLS_PRECOMPUTED_H

#include "Wrap/WinDllMacros.h"
#include <array>
#include <utility>
#include <vector>

//! Compile-time generated std::array of reciprocal factorials
namespace Precomputed
{
template <size_t N> struct ReciprocalFactorial {
    static constexpr double value = ReciprocalFactorial<N - 1>::value / N;
};

template <> struct ReciprocalFactorial<0> {
    static constexpr double value = 1.0;
};

template <template <size_t> class F, size_t... I>
constexpr std::array<double, sizeof...(I)> GenerateArrayHelper(std::index_sequence<I...>)
{
    return {F<I>::value...};
};

template <size_t N, typename Indices = std::make_index_sequence<N>>
constexpr std::array<double, N> GenerateReciprocalFactorialArray()
{
    return GenerateArrayHelper<ReciprocalFactorial>(Indices{});
};
} // namespace Precomputed

#endif // BORNAGAIN_CORE_TOOLS_PRECOMPUTED_H
