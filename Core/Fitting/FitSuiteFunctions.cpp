// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteFunctions.cpp
//! @brief     Implements classes FitSuiteChiSquaredFunction and FitSuiteGradientFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteFunctions.h"
#include "FitSuiteImpl.h"
#include "Logger.h"
#include <cassert>
#include <stdexcept>

//! evaluate chi squared value
double FitSuiteChiSquaredFunction::evaluate(const std::vector<double> &pars)
{
    assert(m_kernel != nullptr);
    if (m_kernel->isInterrupted())
        throw std::runtime_error("Fitting was interrupted by the user.");

    m_kernel->fitParameters()->setValues(pars);
    m_kernel->fitObjects()->runSimulations();
    double chi_squared = m_kernel->fitObjects()->getChiSquaredValue();
    m_kernel->notifyObservers();
    m_ncall++;
    return chi_squared;
}

//! evaluate residual and derivative for given data element
// (calculations are done for all dataset when index==0, when index!=0 already
// calculated data just returned
double FitSuiteGradientFunction::evaluate(
    const std::vector<double>& pars, unsigned int index, std::vector<double>& gradients)
{
    assert(m_kernel != nullptr);
    if (m_kernel->isInterrupted())
        throw std::runtime_error("Fitting was interrupted by the user.");

    bool parameters_changed(true);
    if(m_ncalls_total != 0)
        parameters_changed = m_kernel->fitParameters()->valuesDifferFrom(pars, 2.);

    verify_arrays();
    verify_minimizer_logic(parameters_changed, (int)index);

    if(parameters_changed)
        calculate_residuals(pars);

    if(gradients.size()) {
        if(index == 0 || parameters_changed ) {
            calculate_gradients(pars);
            m_ncalls_gradient++;
        }
        for(size_t i_par=0; i_par<m_npars; ++i_par)
            gradients[i_par] = m_gradients[i_par][index];
    }

    m_ncalls_total++;
    if(index == 0 ) {
        m_kernel->notifyObservers();
        m_ncall++;
    }
    return m_residuals[index];
}

void FitSuiteGradientFunction::verify_arrays()
{
    if ( m_npars == m_kernel->fitParameters()->size() &&
         m_ndatasize == m_kernel->fitObjects()->getSizeOfDataSet() )
        return;
    m_npars = m_kernel->fitParameters()->size();
    m_ndatasize = m_kernel->fitObjects()->getSizeOfDataSet();
    m_residuals.clear();
    m_residuals.resize(m_ndatasize, 0.0);
    m_gradients.clear();
    m_gradients.resize(m_npars);
    for(size_t i_par=0; i_par<m_npars; ++i_par)
        m_gradients[i_par].resize(m_ndatasize, 0.0);
}

void FitSuiteGradientFunction::verify_minimizer_logic(
    bool parameters_have_changed, int current_index)
{
    int index_difference = current_index - m_prev_index;
    if(index_difference != 1 && (current_index!=0 && int(m_prev_index)!= int(m_ndatasize-1) ) ) {
        msglog(Logging::WARNING)
            << "FitSuiteGradientFunction::verify_minimizer_logic() -> Warning! "
            << "Non sequential access to elements.";
        msglog(Logging::WARNING) << " current_index:" << current_index
                             << " prev_index:" << m_prev_index;
    }
    if(parameters_have_changed && current_index != 0) {
        msglog(Logging::WARNING)
            << "FitSuiteGradientFunction::verify_minimizer_logic() -> Warning! "
            << "Parameters have changed while current_index!=0";
        msglog(Logging::WARNING) << " current_index:" << current_index
                             << " prev_index:" << m_prev_index;
    }
    if(parameters_have_changed && current_index == m_prev_index) {
        msglog(Logging::WARNING)
            << "FitSuiteGradientFunction::verify_minimizer_logic() -> Warning! "
            << "Parameters have changed while index remained the same";
        msglog(Logging::WARNING) << " current_index:" << current_index <<
            " prev_index:" << m_prev_index;
    }
    m_prev_index = current_index;
}

void FitSuiteGradientFunction::calculate_residuals(const std::vector<double>& pars)
{
    runSimulation(pars);
    for(size_t i_data=0; i_data<m_ndatasize; ++i_data)
        m_residuals[i_data] = m_kernel->fitObjects()->getResidualValue(i_data);
}

void FitSuiteGradientFunction::calculate_gradients(const std::vector<double>& pars)
{
    // FIXME get kEps from outside fit_suite->getMinimizer()->getPrecision();
    const double kEps = 1.0E-9; // Good for Fumili
    //const double kEps = 1.0E-5;
    for(size_t i_par=0; i_par<m_npars; ++i_par ) {
        std::vector<double > pars_deriv = pars; // values of parameters for derivative calculation
        pars_deriv[i_par] += kEps;

        runSimulation(pars_deriv);

        std::vector<double> residuals2;
        residuals2.resize(m_ndatasize);
        for(size_t i_data=0; i_data<m_ndatasize; ++i_data)
            residuals2[i_data] = m_kernel->fitObjects()->getResidualValue(i_data);
        for(size_t i_data=0; i_data <m_ndatasize; ++i_data)
            m_gradients[i_par][i_data] = (residuals2[i_data] - m_residuals[i_data])/kEps;
    }
    // returning back old parameters
    m_kernel->fitParameters()->setValues(pars);
    runSimulation(pars);
}

void FitSuiteGradientFunction::runSimulation(const std::vector<double> &pars){
    assert(m_kernel);
    m_kernel->fitParameters()->setValues(pars);
    m_kernel->fitObjects()->runSimulations();
}
