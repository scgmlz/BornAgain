// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/FitOptions.h
//! @brief     Defines class FitOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_KERNEL_FITOPTIONS_H
#define BORNAGAIN_FIT_KERNEL_FITOPTIONS_H

#include "Wrap/WinDllMacros.h"

//! General fitting options.

class BA_CORE_API_ FitOptions
{
public:
    FitOptions();

    double derivEpsilon() const;
    void setDerivEpsilon(double deriv_epsilon);

    double stepFactor() const;
    void setStepFactor(double step_factor);

private:
    double m_deriv_epsilon; //!< epsilon for derivative calculation
    double m_step_factor;   //!< default relative parameter step
};

#endif // BORNAGAIN_FIT_KERNEL_FITOPTIONS_H
