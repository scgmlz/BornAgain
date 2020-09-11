// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/FitOptions.cpp
//! @brief     Implements class FitOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/FitOptions.h"

FitOptions::FitOptions() : m_deriv_epsilon(1e-09), m_step_factor(0.01) {}

void FitOptions::setStepFactor(double step_factor)
{
    m_step_factor = step_factor;
}

double FitOptions::stepFactor() const
{
    return m_step_factor;
}

void FitOptions::setDerivEpsilon(double deriv_epsilon)
{
    m_deriv_epsilon = deriv_epsilon;
}

double FitOptions::derivEpsilon() const
{
    return m_deriv_epsilon;
}
