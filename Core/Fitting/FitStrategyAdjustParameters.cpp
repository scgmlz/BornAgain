// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitStrategyAdjustParameters.cpp
//! @brief     Implements class FitStrategyAdjustParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitStrategyAdjustParameters.h"
#include "FitSuiteImpl.h"
#include "FitParameter.h"
#include "FitParameterSet.h"
#include "Logger.h"
#include "Exceptions.h"

FitStrategyAdjustParameters::FitStrategyAdjustParameters(const FitStrategyAdjustParameters &other)
    : IFitStrategy(other)
    , m_fix_all(other.m_fix_all)
    , m_release_all(other.m_release_all)
    , m_pars_to_fix(other.m_pars_to_fix)
    , m_pars_to_release(other.m_pars_to_release)
    , m_preserve_original_values(other.m_preserve_original_values)
{
}

//! strategy which fixes/releases fit parameters and then call minimizer
void FitStrategyAdjustParameters::execute()
{
    if( !m_kernel )
        throw Exceptions::NullPointerException(
            "FitSuiteStrategyAdjustParameters::execute() -> FitSuite doesn't exists");
    FitParameterSet* fitParameters = m_kernel->fitParameters();

    // fixing all parameters at they current values
    if( m_fix_all ) {
        for(auto par: *fitParameters)
            par->limits().setFixed(true);
    }

    // releasing all parameters
    if( m_release_all ) {
        for(auto par: *fitParameters) {
            msglog(Logging::DEBUG2) << "FitSuiteStrategyAdjustParameters::execute() -> releasing "
                                << par->name();
            par->limits().setFixed(false);
        }
    }

    // fixing dedicated list of fit parameters
    for(auto name: m_pars_to_fix) {
        msglog(Logging::DEBUG2) << "FitSuiteStrategyAdjustParameters::execute() -> fixing " << name;
        fitParameters->fitParameter(name)->limits().setFixed(true);
    }

    // releasing dedicated list of fit parameters
    for(auto name: m_pars_to_release) {
        msglog(Logging::DEBUG2) << "FitSuiteStrategyAdjustParameters::execute() -> releasing "
                                << name;
        fitParameters->fitParameter(name)->limits().setFixed(false);
    }

    // saving original param values
    std::vector<double> original_param_values = fitParameters->values();

    // calling minimization
    m_kernel->minimize();

    // returning parameters to original values as they were before minimization
    if(m_preserve_original_values)
        fitParameters->setValues(original_param_values);
}
