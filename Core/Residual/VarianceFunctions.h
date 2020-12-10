//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Residual/VarianceFunctions.h
//! @brief     Defines IVarianceFunction classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_INSTRUMENT_VARIANCEFUNCTIONS_H
#define BORNAGAIN_DEVICE_INSTRUMENT_VARIANCEFUNCTIONS_H

//! Variance function interface.
//! @ingroup fitting_internal

class IVarianceFunction {
public:
    IVarianceFunction() = default;
    virtual ~IVarianceFunction() = default;
    IVarianceFunction(const IVarianceFunction&) = delete;
    IVarianceFunction& operator=(const IVarianceFunction&) = delete;

    virtual IVarianceFunction* clone() const = 0;
    virtual double variance(double real_value, double simulated_value) const = 0;
};

//! Returns 1.0 as variance value
//! @ingroup fitting

class VarianceConstantFunction : public IVarianceFunction {
public:
    VarianceConstantFunction* clone() const override;
    double variance(double, double) const override;
};

//! Returns max(sim, epsilon)
//! @ingroup fitting

class VarianceSimFunction : public IVarianceFunction {
public:
    explicit VarianceSimFunction(double epsilon = 1.0);
    VarianceSimFunction* clone() const override;
    double variance(double exp, double sim) const override;

private:
    double m_epsilon;
};

#endif // BORNAGAIN_DEVICE_INSTRUMENT_VARIANCEFUNCTIONS_H
