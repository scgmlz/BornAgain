// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Utils/Algorithms.h
//! @brief     Defines and implements namespace algo with some algorithms
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_BASE_UTILS_ALGORITHMS_H
#define BORNAGAIN_BASE_UTILS_ALGORITHMS_H

#include "Base/Utils/Assert.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

//! Some additions to standard library algorithms.

namespace algo
{

//! Returns true if two doubles agree within machine epsilon.
inline bool almostEqual(double a, double b)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    return std::abs(a - b) <= eps * std::max(eps, (std::abs(a) + std::abs(b)) / 2);
}

//! Returns the minimum value of function evaluate as applied to the elements of an iterator range.
template <typename Evaluator, typename Iterator>
double min_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate);

//! Returns the maximum value of function evaluate as applied to the elements of an iterator range.
template <typename Evaluator, typename Iterator>
double max_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate);

//! Returns the concatenation of two std::vector%s.
template <class T> std::vector<T> concat(const std::vector<T>& v1, const std::vector<T>& v2);

} // namespace algo

// ************************************************************************** //
// Implementation
// ************************************************************************** //

template <typename Evaluator, typename Iterator>
double algo::min_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate)
{
    ASSERT(begin != end);
    double ret = evaluate(*begin);
    Iterator it = begin;
    while (++it != end)
        ret = std::min(ret, evaluate(*it));
    return ret;
}

template <typename Evaluator, typename Iterator>
double algo::max_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate)
{
    ASSERT(begin != end);
    double ret = evaluate(*begin);
    Iterator it = begin;
    while (++it != end)
        ret = std::max(ret, evaluate(*it));
    return ret;
}

template <class T> std::vector<T> algo::concat(const std::vector<T>& v1, const std::vector<T>& v2)
{
    std::vector<T> v = v1;
    v.insert(v.end(), v2.begin(), v2.end());
    return v;
}

#endif // BORNAGAIN_BASE_UTILS_ALGORITHMS_H
