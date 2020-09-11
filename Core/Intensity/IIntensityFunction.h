// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/IIntensityFunction.h
//! @brief     Defines and implements the interface class IIntensityFunction
//!            and its child classes IntensityFunctionLog, IntensityFunctionSqrt
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INTENSITY_IINTENSITYFUNCTION_H
#define BORNAGAIN_CORE_INTENSITY_IINTENSITYFUNCTION_H

#include "Wrap/WinDllMacros.h"

//! Interface for applying arbitrary function to the measured intensity.
//! @ingroup algorithms_internal

class BA_CORE_API_ IIntensityFunction
{
public:
    virtual ~IIntensityFunction();
    virtual IIntensityFunction* clone() const = 0;
    virtual double evaluate(double value) const = 0;
};

//! Algorithm for applying log function to the measured intensity.
//! @ingroup algorithms_internal

class BA_CORE_API_ IntensityFunctionLog : public IIntensityFunction
{
public:
    virtual IntensityFunctionLog* clone() const;
    virtual double evaluate(double value) const;
};

//! Algorithm for applying sqrt function to the measured intensity.
//! @ingroup algorithms_internal

class BA_CORE_API_ IntensityFunctionSqrt : public IIntensityFunction
{
public:
    virtual IntensityFunctionSqrt* clone() const;
    virtual double evaluate(double value) const;
};

#endif // BORNAGAIN_CORE_INTENSITY_IINTENSITYFUNCTION_H
