//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Term/DepthProbeComputationTerm.h
//! @brief     Defines functor DepthProbeComputationTerm.
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
#ifndef BORNAGAIN_CORE_TERM_DEPTHPROBECOMPUTATIONTERM_H
#define BORNAGAIN_CORE_TERM_DEPTHPROBECOMPUTATIONTERM_H

#include <memory>

class DelayedProgressCounter;
class ProcessedSample;
class ProgressHandler;
class DepthProbeElement;

class DepthProbeComputationTerm {
public:
    DepthProbeComputationTerm(const ProcessedSample* p_sample);
    ~DepthProbeComputationTerm();

    void setProgressHandler(ProgressHandler* p_progress);

    void compute(DepthProbeElement& elem) const;

private:
    const ProcessedSample* m_sample;
    std::unique_ptr<DelayedProgressCounter> m_progress_counter;
};

#endif // BORNAGAIN_CORE_TERM_DEPTHPROBECOMPUTATIONTERM_H
#endif // USER_API
