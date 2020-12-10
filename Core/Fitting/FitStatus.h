//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitStatus.h
//! @brief     Defines class FitStatus.
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
#ifndef BORNAGAIN_CORE_FITTING_FITSTATUS_H
#define BORNAGAIN_CORE_FITTING_FITSTATUS_H

#include "Core/Fitting/FitObserver.h"
#include "Core/Fitting/IterationInfo.h"
#include <functional>
#include <vector>

namespace mumufit {
class MinimizerResult;
}
class FitObjective;
class FitPrintService;

//! Contains status of the fitting (running, interupted etc) and all intermediate
//! information which has to be collected during the fit.
//! Owned by FitObjective.

class FitStatus {
public:
    FitStatus(const FitObjective* fit_objective);
    ~FitStatus();

    void setInterrupted();
    bool isInterrupted() const;
    bool isCompleted() const;

    void update(const mumufit::Parameters& params, double chi2);

    void initPrint(int every_nth);

    void addObserver(int every_nth, fit_observer_t);

    IterationInfo iterationInfo() const;

    mumufit::MinimizerResult minimizerResult() const;

    //! Should be explicitely called on last iteration to notify all observers.
    void finalize(const mumufit::MinimizerResult& result);

private:
    enum EFitStatus { IDLE, RUNNING, COMPLETED, FAILED, INTERRUPTED };
    EFitStatus m_fit_status;
    FitObserver<FitObjective> m_observers;
    std::unique_ptr<FitPrintService> m_print_service;
    const FitObjective* m_fit_objective;
    IterationInfo m_iterationInfo;
    std::unique_ptr<mumufit::MinimizerResult> m_minimizer_result;
};

#endif // BORNAGAIN_CORE_FITTING_FITSTATUS_H
#endif // USER_API
