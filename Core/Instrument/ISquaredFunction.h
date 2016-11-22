// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISquaredFunction.h
//! @brief     Defines classes ISquaredFunction, SquaredFunctionDefault, ...
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISQUAREDFUNCTION_H
#define ISQUAREDFUNCTION_H

#include "Numeric.h" // TODO rm this from .h

//! Interface providing measures for deviation between two values.
//! Used By ChiSquaredModule for chi2 calculations.
//! @ingroup fitting_internal

class BA_CORE_API_ ISquaredFunction
{
public:
    ISquaredFunction(){}
    virtual ~ISquaredFunction() {}
    virtual ISquaredFunction* clone() const=0;
    virtual double calculateSquaredDifference(
                double real_value, double simulated_value) const=0;
    virtual double calculateSquaredError(
                double real_value, double simulated_value = 0.0) const = 0;

private:
    ISquaredFunction(const ISquaredFunction& );
    ISquaredFunction& operator=(const ISquaredFunction& );
};


//! Squared difference between two values.
//! value = (a-b)*(a-b)/norm, where norm = max(b, 1.0), a = simulated values, b = real_values.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionDefault : public ISquaredFunction
{
public:
    SquaredFunctionDefault() {}
    virtual ~SquaredFunctionDefault() {}
    virtual SquaredFunctionDefault* clone() const { return new SquaredFunctionDefault(); }

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const
    {
        if (Numeric::areAlmostEqual(real_value, simulated_value))
            return 0.;
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        double normalization = calculateSquaredError(real_value);
        return diff_squared/normalization;
    }

    virtual double calculateSquaredError(double real_value, double simulated_value = 0) const
    {
        (void) simulated_value;
        return std::max(real_value,1.0);
    }
};


//! Squared difference between two values.
//! value = (a-b)*(a-b)/norm, where norm = max(a, 1.0), a = simulated values, b = real_values.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionSimError : public ISquaredFunction
{
public:
    SquaredFunctionSimError() {}
    virtual ~SquaredFunctionSimError() {}
    virtual SquaredFunctionSimError *clone() const { return new SquaredFunctionSimError(); }
    virtual double calculateSquaredDifference(double real_value, double simulated_value) const {
        if (Numeric::areAlmostEqual(real_value, simulated_value))
            return 0.0;
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        double normalization = calculateSquaredError(real_value, simulated_value);
        return diff_squared/normalization;
    }
    virtual double calculateSquaredError(double /* real_value */, double simulated_value) const {
        return std::max(simulated_value,1.0);
    }
};


//! Squared difference between two values normalized by mean squared error.
//! value = (a-b)*(a-b)/norm, where norm = sqrt(sigma1*sigma1 + sigma2*sigma2),
//! sigma1=max(a, 1.0), sigma2=max(b,1.0)
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionMeanSquaredError : public ISquaredFunction
{
public:
    SquaredFunctionMeanSquaredError() {}
    virtual ~SquaredFunctionMeanSquaredError() {}
    virtual SquaredFunctionMeanSquaredError *clone() const {
        return new SquaredFunctionMeanSquaredError(); }
    virtual double calculateSquaredDifference(double real_value, double simulated_value) const {
        if (Numeric::areAlmostEqual(real_value, simulated_value)) return 0.0;
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        double normalization = calculateSquaredError(real_value, simulated_value);
        return diff_squared/normalization;
    }
    virtual double calculateSquaredError(double real_value, double simulated_value) const {
        (void) simulated_value;
        double sigma1 = std::max(real_value,1.0);
        double sigma2 = std::max(simulated_value,1.0);
        return std::sqrt(sigma1*sigma1 + sigma2*sigma2);
    }
};


//! Squared difference between two values normalized by systematic error.
//! value = (a-b)*(a-b)/norm, where norm = max(error, 1.0), error = b + (epsilon*b)**2.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionSystematicError : public ISquaredFunction
{
public:
    SquaredFunctionSystematicError(double epsilon = 0.08) : m_epsilon(epsilon){}
    virtual ~SquaredFunctionSystematicError() {}
    virtual SquaredFunctionSystematicError *clone() const {
        return new SquaredFunctionSystematicError(m_epsilon); }
    virtual double calculateSquaredDifference(double real_value, double simulated_value) const {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        double normalization = calculateSquaredError(real_value, simulated_value);
        return diff_squared/normalization;
    }
    virtual double calculateSquaredError(double real_value, double /* simulated_value */) const {
        return std::max(std::abs(real_value) + (m_epsilon*real_value)*(m_epsilon*real_value),1.0);
    }
private:
    double m_epsilon;
};


//! Squared difference between two values with gaussian error.
//! value = (a-b)*(a-b)/norm, where norm = sigma*sigma; sigma is set by user.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionGaussianError : public ISquaredFunction
{
public:
    SquaredFunctionGaussianError(double sigma = 0.01) : m_sigma(sigma){}
    virtual ~SquaredFunctionGaussianError() {}
    virtual SquaredFunctionGaussianError *clone() const {
        return new SquaredFunctionGaussianError(m_sigma); }
    virtual double calculateSquaredDifference(double real_value, double simulated_value) const {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        double sigma_squared = m_sigma*m_sigma;
        return diff_squared/sigma_squared;
    }
    virtual double calculateSquaredError(double, double) const {
        return m_sigma*m_sigma;
    }
private:
    double m_sigma;
};

#endif // ISQUAREDFUNCTION_H
