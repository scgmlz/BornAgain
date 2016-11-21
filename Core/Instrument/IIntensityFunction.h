// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IIntensityFunction.h
//! @brief     Defines and implements the interface class IIntensityFunction
//!            and its child classes IntensityFunctionLog, IntensityFunctionSqrt
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IINTENSITYFUNCTION_H
#define IINTENSITYFUNCTION_H

#include "WinDllMacros.h"

//! Interface for applying arbitrary function to the measured intensity.
//! @ingroup algorithms_internal

class BA_CORE_API_ IIntensityFunction
{
public:
    virtual ~IIntensityFunction() {}
    virtual IIntensityFunction *clone() const =0;
    virtual double evaluate(double value) const =0;
};


//! Algorithm for applying log function to the measured intensity.
//! @ingroup algorithms_internal

class BA_CORE_API_ IntensityFunctionLog : public IIntensityFunction
{
public:
    virtual ~IntensityFunctionLog() {}
    virtual IntensityFunctionLog *clone() const { return new IntensityFunctionLog(); }
    virtual double evaluate(double value) const;
};


//! Algorithm for applying sqrt function to the measured intensity.
//! @ingroup algorithms_internal

class BA_CORE_API_ IntensityFunctionSqrt : public IIntensityFunction
{
public:
    virtual ~IntensityFunctionSqrt() {}
    virtual IntensityFunctionSqrt *clone() const { return new IntensityFunctionSqrt(); }
    virtual double evaluate(double value) const;
};

#endif // IINTENSITYFUNCTION_H
