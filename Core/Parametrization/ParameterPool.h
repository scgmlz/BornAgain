// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.h
//! @brief     Defines class ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERPOOL_H
#define BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERPOOL_H

#include "Core/Basics/ICloneable.h"
#include <ostream>
#include <string>
#include <vector>

class RealLimits;
class RealParameter;

//! Container with parameters for IParameterized object.
//! @ingroup tools_internal

class BA_CORE_API_ ParameterPool : public ICloneable
{
public:
    ParameterPool();
    virtual ~ParameterPool();

    ParameterPool* clone() const;

    void copyToExternalPool(const std::string& prefix, ParameterPool* other_pool) const;

    void clear();

    //! Returns number of parameters in the pool.
    size_t size() const { return m_params.size(); }

    RealParameter& addParameter(RealParameter* newPar);

    RealParameter* parameter(const std::string& name);

    const RealParameter* parameter(const std::string& name) const;

    //! Returns full vector of parameters.
    const std::vector<RealParameter*> parameters() const { return m_params; }

    std::vector<RealParameter*> getMatchedParameters(const std::string& pattern) const;
    RealParameter* getUniqueMatch(const std::string& pattern) const;

    void setParameterValue(const std::string& name, double value);

    int setMatchedParametersValue(const std::string& wildcards, double value);
    void setUniqueMatchValue(const std::string& pattern, double value);

    std::vector<std::string> parameterNames() const;

    friend std::ostream& operator<<(std::ostream& ostr, const ParameterPool& obj)
    {
        obj.print(ostr);
        return ostr;
    }

    void removeParameter(const std::string& name);

    const RealParameter* operator[](size_t index) const;
    RealParameter* operator[](size_t index);

private:
    virtual void print(std::ostream& ostr) const;
#ifndef SWIG
    [[noreturn]] void report_find_matched_parameters_error(const std::string& pattern) const;
    [[noreturn]] void report_set_value_error(const std::string& parname, double value,
                                             std::string message = {}) const;
#endif
    size_t check_index(size_t index) const;

    std::vector<RealParameter*> m_params;
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERPOOL_H
