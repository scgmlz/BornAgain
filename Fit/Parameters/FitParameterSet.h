// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitParameterSet.h
//! @brief     Defines class FitParameterSet.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERSET_H
#define FITPARAMETERSET_H

#include "WinDllMacros.h"
#include <vector>
#include <string>

class FitParameter;

//! The set of fit parameters.
//! @ingroup fitting_internal

class BA_CORE_API_ FitParameterSet
{
 public:
    typedef std::vector<FitParameter*> container_t;
    typedef container_t::iterator iterator;
    typedef container_t::const_iterator const_iterator;
    typedef std::vector<std::vector<double>> corr_matrix_t;

    FitParameterSet() {}
    ~FitParameterSet();

    void clear();
    size_t size() const;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    void addFitParameter(FitParameter* par);

    // Access fit parameters

    const FitParameter* fitParameter(const std::string& name) const;
    FitParameter* fitParameter(const std::string& name);
    const FitParameter* operator[](const std::string& name) const;
    FitParameter* operator[](const std::string& name);
    const FitParameter* operator[](size_t index) const;
    FitParameter* operator[](size_t index);

    // Fit parameter's values and errors

    std::vector<double> values() const;
    void setValues(const std::vector<double>& pars_values);
    bool valuesDifferFrom(const std::vector<double>& par_values, double tolerance = 2.0) const;
    std::vector<double> errors() const;
    void setErrors(const std::vector<double>& pars_errors);

    // Make parameters fixed and free

    size_t freeFitParameterCount() const;
    void fixAll();
    void releaseAll();
    void setFixed(const std::vector<std::string>& pars, bool is_fixed);

    // Printing and reporting

    std::string parametersToString() const;

    corr_matrix_t correlationMatrix() const { return m_corr_matrix; }
    void setCorrelationMatrix(const corr_matrix_t& matrix);

    bool isExistingName(const std::string& name) const;

private:
    size_t check_index(size_t index) const;
    void check_array_size(const std::vector<double>& values) const;
    container_t m_parameters; //!< collection of fit parameters
    corr_matrix_t m_corr_matrix; //!< correlation matrix
};

#endif // FITPARAMETERSET_H
