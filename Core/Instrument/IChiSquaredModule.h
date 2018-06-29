// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IChiSquaredModule.h
//! @brief     Defines class IChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ICHISQUAREDMODULE_H
#define ICHISQUAREDMODULE_H

#include "FitElement.h"
#include "IIntensityFunction.h"
#include "IIntensityNormalizer.h"
#include "ISquaredFunction.h"
#include "ICloneable.h"

//! Interface for ChiSquaredModule for chi2 calculations.
//! @ingroup fitting_internal
//! Until BornAgain-1.1, there was another child, ChiSquaredFrequency.

class BA_CORE_API_ IChiSquaredModule : public ICloneable
{
public:
    IChiSquaredModule();
    virtual ~IChiSquaredModule();

    //! clone method
    virtual IChiSquaredModule* clone() const = 0;

    //! Returns squared function
    const ISquaredFunction* getSquaredFunction() const { return mp_squared_function; }

    //! Sets squared function // TODO: merge these two functions (SWIG warning 509)
    void setChiSquaredFunction(ISquaredFunction* squared_function);
    void setChiSquaredFunction(const ISquaredFunction& squared_function);

    //! Returns data normalizer.
    virtual const IIntensityNormalizer* getIntensityNormalizer() const {
        return mp_data_normalizer; }

    //! Returns data normalizer, non-const version needed to set internals.
    virtual IIntensityNormalizer* getIntensityNormalizer() {  return mp_data_normalizer; }

    //! Sets data normalizer
    virtual void setIntensityNormalizer(const IIntensityNormalizer& data_normalizer);

    //! Returns data rescaler.
    virtual const IIntensityFunction* getIntensityFunction() const { return mp_intensity_function; }

    //! Sets data rescaler.
    virtual void setIntensityFunction(const IIntensityFunction& intensity_function);

    virtual void processFitElements(std::vector<FitElement>::iterator,
                                    std::vector<FitElement>::iterator){}

    virtual double residual(double a, double b, double weight) = 0;

protected:
    IChiSquaredModule(const IChiSquaredModule& other);

    ISquaredFunction* mp_squared_function;
    IIntensityNormalizer* mp_data_normalizer;
    IIntensityFunction* mp_intensity_function;
};

#endif // ICHISQUAREDMODULE_H
