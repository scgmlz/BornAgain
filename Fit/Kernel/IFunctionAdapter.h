// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/IFunctionAdapter.h
//! @brief     Defines class IFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_KERNEL_IFUNCTIONADAPTER_H
#define BORNAGAIN_FIT_KERNEL_IFUNCTIONADAPTER_H

#include "Wrap/WinDllMacros.h"

namespace Fit
{

//! Base class for objective function adapters, which converts user functions
//! to minimize into the function which minimization machinery expects.

class BA_CORE_API_ IFunctionAdapter
{
public:
    IFunctionAdapter();
    virtual ~IFunctionAdapter();

    int numberOfCalls() const;
    int numberOfGradientCalls() const;

protected:
    int m_number_of_calls;
    int m_number_of_gradient_calls;
};

} // namespace Fit

#endif // BORNAGAIN_FIT_KERNEL_IFUNCTIONADAPTER_H
