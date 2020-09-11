// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/Parameters.h
//! @brief     Defines class Parameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_KERNEL_PARAMETERS_H
#define BORNAGAIN_FIT_KERNEL_PARAMETERS_H

#include "Fit/Kernel/Parameter.h"
#include "Wrap/WinDllMacros.h"
#include <vector>

namespace Fit
{

//! A collection of fit parameters.
//! @ingroup fitting

class BA_CORE_API_ Parameters
{
public:
    using parameters_t = std::vector<Parameter>;
    using const_iterator = parameters_t::const_iterator;
    using iterator = parameters_t::iterator;
    using corr_matrix_t = std::vector<std::vector<double>>;

    Parameters() = default;

    void add(const Parameter& par);

    const_iterator begin() const;
    const_iterator end() const;

    iterator begin();
    iterator end();

    size_t size() const;

    std::vector<double> values() const;
    void setValues(const std::vector<double>& values);

    std::vector<double> errors() const;
    void setErrors(const std::vector<double>& errors);

    const Parameter& operator[](const std::string& name) const;
    const Parameter& operator[](size_t index) const;

    corr_matrix_t correlationMatrix() const;
    void setCorrelationMatrix(const corr_matrix_t& matrix);

    size_t freeParameterCount() const;

private:
    bool exists(const std::string& parameter_name) const;
    void check_array_size(const std::vector<double>& values) const;
    size_t check_index(size_t index) const;

    parameters_t m_parameters;
    corr_matrix_t m_corr_matrix; //!< correlation matrix
};

} // namespace Fit

#endif // BORNAGAIN_FIT_KERNEL_PARAMETERS_H
