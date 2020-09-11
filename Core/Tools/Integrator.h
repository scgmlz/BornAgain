// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Integrator.h
//! @brief     Defines classes RealIntegrator, ComplexIntegrator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_TOOLS_INTEGRATOR_H
#define BORNAGAIN_CORE_TOOLS_INTEGRATOR_H

#include "Core/Basics/Complex.h"
#include "Wrap/WinDllMacros.h"
#include <functional>
#include <gsl/gsl_integration.h>

//! To integrate a real function of a real variable.
class BA_CORE_API_ RealIntegrator
{
public:
    RealIntegrator();
    ~RealIntegrator();
    double integrate(const std::function<double(double)>& f, double lmin, double lmax);

private:
    static double m_Cfunction(double x, void* p)
    {
        return (*(const std::function<double(double)>*)(p))(x);
    };
    gsl_function m_gsl_f;
    gsl_integration_workspace* m_workspace;
};

//! To integrate a complex function of a real variable.
class BA_CORE_API_ ComplexIntegrator
{
public:
    complex_t integrate(const std::function<complex_t(double)>& f, double lmin, double lmax);

private:
    RealIntegrator realPart;
    RealIntegrator imagPart;
};

#endif // BORNAGAIN_CORE_TOOLS_INTEGRATOR_H
