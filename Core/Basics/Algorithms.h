// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Algorithms
//! @brief     Defines and implements namespace algo with some algorithms
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <algorithm>
#include <functional>
#include <vector>
#include <cassert>

//! Some additions to standard library algorithms.

namespace algo {

//! Returns the minimum value of function evaluate as applied to the elements of an iterator range.
template<typename Evaluator, typename Iterator>
double min_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate);

//! Returns the maximum value of function evaluate as applied to the elements of an iterator range.
template<typename Evaluator, typename Iterator>
double max_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate);

} // namespace algo


// ************************************************************************** //
// Implementation
// ************************************************************************** //

template<typename Evaluator, typename Iterator>
double algo::min_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate)
{
    assert(begin != end);
    double ret = evaluate(*begin);
    Iterator it = begin;
    while (++it != end)
        ret = std::min(ret, evaluate(*it));
    return ret;
}

template<typename Evaluator, typename Iterator>
double algo::max_value(const Iterator& begin, const Iterator& end, const Evaluator& evaluate)
{
    assert(begin != end);
    double ret = evaluate(*begin);
    Iterator it = begin;
    while (++it != end)
        ret = std::max(ret, evaluate(*it));
    return ret;
}


#endif // ALGORITHMS_H
