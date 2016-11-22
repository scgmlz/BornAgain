// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.h
//! @brief     Defines class ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERPOOL_H
#define PARAMETERPOOL_H

#include "WinDllMacros.h"
#include <functional>
#include <ostream>
#include <string>
#include <vector>

class RealLimits;
class RealParameter;

//! Holds a map of pointers to parameters.
//! @ingroup tools_internal

//! Used in IParameterized, which has a member ParameterPool* m_pool.
//! So this is pimpl (pointer to implementation) idiom, with ParameterPool providing the
//! implementation of all the nontrivial functionality of IParameterized.
//!
//! Parameter names must be unique since we use them as map keys.

class BA_CORE_API_ ParameterPool
{
public:
    explicit ParameterPool(const std::string& name, const std::function<void()>& onChange);
    ParameterPool(const ParameterPool&) = delete;
    ParameterPool& operator=(const ParameterPool&) = delete;
    virtual ~ParameterPool();

    ParameterPool* clone() const;
    ParameterPool* cloneWithPrefix(const std::string& prefix) const;

    void copyToExternalPool(const std::string& prefix, ParameterPool* external_pool) const;

    void clear();

    std::string getName() const { return m_name; }

    //! Returns number of parameters in the pool.
    size_t size() const { return m_params.size(); }

    RealParameter& addParameter(RealParameter* par);

    RealParameter* getParameter(const std::string& name);

    const RealParameter* getParameter(const std::string& name) const;

    //! Returns full vector of parameters.
    const std::vector<RealParameter*> getParameters() const { return m_params; }

    std::vector<RealParameter*> getMatchedParameters(const std::string& wildcards) const;

    void setParameterValue(const std::string& name, double value);

    int setMatchedParametersValue(const std::string& wildcards, double value);

    std::vector<std::string> getParameterNames() const;

    friend std::ostream& operator<<(std::ostream& ostr, const ParameterPool& obj) {
        obj.print(ostr); return ostr; }

protected:
    //! Called from RealParameter, calls back to owning IParameterized.
    void onChange() const { m_onChange(); }

private:
    virtual void print(std::ostream& ostr) const;

    void report_find_matched_parameters_error(const std::string& pattern) const;
    void report_set_value_error(const std::string& parname, double value) const;

    std::string m_name; //!< The name of this pool, should be that of the owning IParameterized.
    std::vector<RealParameter*> m_params;     //!< The parameters in this pool.
    std::function<void()> m_onChange; //!< To be called whenever a parameter has changed.

    friend RealParameter; //!< allow call of onChange().
};

#endif // PARAMETERPOOL_H
