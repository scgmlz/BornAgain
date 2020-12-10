//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Residual/IChiSquaredModule.h
//! @brief     Defines interface IChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_INSTRUMENT_ICHISQUAREDMODULE_H
#define BORNAGAIN_DEVICE_INSTRUMENT_ICHISQUAREDMODULE_H

#include "Base/Types/ICloneable.h"
#include <memory>

class IVarianceFunction;
class IIntensityFunction;

//! Interface residual calculations.
//! @ingroup fitting_internal

class IChiSquaredModule : public ICloneable {
public:
    IChiSquaredModule();
    virtual ~IChiSquaredModule();

    //! clone method
    virtual IChiSquaredModule* clone() const = 0;

    //! Returns squared function
    const IVarianceFunction* varianceFunction() const;

    //! Sets squared function
    void setVarianceFunction(const IVarianceFunction& variance_function);

    //! Returns data rescaler.
    virtual const IIntensityFunction* getIntensityFunction() const;

    //! Sets data rescaler.
    virtual void setIntensityFunction(const IIntensityFunction& intensity_function);

    virtual double residual(double a, double b, double weight) = 0;

protected:
    IChiSquaredModule(const IChiSquaredModule& other);

    std::unique_ptr<IVarianceFunction> m_variance_function;
    std::unique_ptr<IIntensityFunction> m_intensity_function;
};

#endif // BORNAGAIN_DEVICE_INSTRUMENT_ICHISQUAREDMODULE_H
#endif // USER_API
