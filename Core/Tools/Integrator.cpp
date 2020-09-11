// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Integrator.cpp
//! @brief     Implements classes RealIntegrator, ComplexIntegrator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Tools/Integrator.h"

RealIntegrator::RealIntegrator()
    : m_gsl_f{m_Cfunction, nullptr}, m_workspace{gsl_integration_workspace_alloc(200)}
{
}

RealIntegrator::~RealIntegrator()
{
    gsl_integration_workspace_free(m_workspace);
}

double RealIntegrator::integrate(const std::function<double(double)>& f, double lmin, double lmax)
{
    m_gsl_f.params = (void*)&f;
    double result, error;
    gsl_integration_qag(&m_gsl_f, lmin, lmax, 1e-10, 1e-8, 50, 1, m_workspace, &result, &error);
    // TODO check error
    return result;
}

complex_t ComplexIntegrator::integrate(const std::function<complex_t(double)>& f, double lmin,
                                       double lmax)
{
    return {realPart.integrate([f](double x) { return f(x).real(); }, lmin, lmax),
            imagPart.integrate([f](double x) { return f(x).imag(); }, lmin, lmax)};
}
