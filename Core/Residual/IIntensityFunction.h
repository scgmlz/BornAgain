//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Residual/IIntensityFunction.h
//! @brief     Defines and implements the interface class IIntensityFunction
//!            and its child classes IntensityFunctionLog, IntensityFunctionSqrt
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_INTENSITY_IINTENSITYFUNCTION_H
#define BORNAGAIN_DEVICE_INTENSITY_IINTENSITYFUNCTION_H

//! Interface for applying arbitrary function to the measured intensity.
//! @ingroup algorithms_internal

class IIntensityFunction {
public:
    virtual ~IIntensityFunction();
    virtual IIntensityFunction* clone() const = 0;
    virtual double evaluate(double value) const = 0;
};

//! Algorithm for applying log function to the measured intensity.
//! @ingroup algorithms_internal

class IntensityFunctionLog : public IIntensityFunction {
public:
    virtual IntensityFunctionLog* clone() const;
    virtual double evaluate(double value) const;
};

//! Algorithm for applying sqrt function to the measured intensity.
//! @ingroup algorithms_internal

class IntensityFunctionSqrt : public IIntensityFunction {
public:
    virtual IntensityFunctionSqrt* clone() const;
    virtual double evaluate(double value) const;
};

#endif // BORNAGAIN_DEVICE_INTENSITY_IINTENSITYFUNCTION_H
#endif // USER_API
