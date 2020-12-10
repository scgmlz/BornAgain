//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/TRange.h
//! @brief     Defines and implements template classes TRange and TSampledRange.
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
#ifndef BORNAGAIN_SAMPLE_PARTICLE_TRANGE_H
#define BORNAGAIN_SAMPLE_PARTICLE_TRANGE_H

#include <cstddef>

//! An interval [lowerBound..upperBound[.
//! @ingroup tools_internal

template <class T> class TRange {
public:
    TRange(T lowerBound, T upperBound) : m_lower_bound(lowerBound), m_upper_bound(upperBound) {}
    virtual ~TRange() {}

    T getLowerBound() const { return m_lower_bound; }
    T getUpperBound() const { return m_upper_bound; }
    T getDifference() const { return m_upper_bound - m_lower_bound; }

    bool inRange(T value) const { return value >= m_lower_bound && value < m_upper_bound; }

private:
    T m_lower_bound, m_upper_bound;
};

//! An interval [lowerBound..upperBound[, and a number of samples.

template <class T> class TSampledRange : public TRange<T> {
public:
    TSampledRange(size_t n_samples, T lowerBound, T upperBound)
        : TRange<T>(lowerBound, upperBound), m_n_samples(n_samples) {}

    size_t getNSamples() const { return m_n_samples; }

private:
    size_t m_n_samples;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_TRANGE_H
#endif // USER_API
