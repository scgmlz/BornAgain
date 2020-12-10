//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Base/IParametricComponent.h
//! @brief     Defines interface IParametricComponent.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_PARAM_BASE_IPARAMETRICCOMPONENT_H
#define BORNAGAIN_PARAM_BASE_IPARAMETRICCOMPONENT_H

#include "Base/Vector/Vectors3D.h"
#include "Param/Base/IComponent.h"
#include <memory>

class RealLimits;
class ParameterPool;
class RealParameter;

//! Manages a local parameter pool, and a tree of child pools.
//! @ingroup tools_internal

class IParametricComponent : public IComponent {
public:
    IParametricComponent(const std::string& name = "");
    IParametricComponent(const IParametricComponent& other);
    virtual ~IParametricComponent();

    IParametricComponent& operator=(const IParametricComponent& other) = delete;

    //! Returns pointer to the parameter pool.
    ParameterPool* parameterPool() const { return m_pool.get(); } // has non-const usages!

    //! Creates new parameter pool, with all local parameters and those of its children.
    virtual ParameterPool* createParameterTree() const;

    //! Returns multiline string representing available parameters.
    std::string parametersToString() const;

    RealParameter& registerParameter(const std::string& name, double* parpointer);

    void registerVector(const std::string& base_name, kvector_t* p_vec,
                        const std::string& units = "nm");

    void setParameterValue(const std::string& name, double value);

    void setVectorValue(const std::string& base_name, kvector_t value);

    RealParameter* parameter(const std::string& name) const;

    //! Action to be taken in inherited class when a parameter has changed.
    virtual void onChange() {}

    void removeParameter(const std::string& name);

    void removeVector(const std::string& base_name);

    static std::string XComponentName(const std::string& base_name);
    static std::string YComponentName(const std::string& base_name);
    static std::string ZComponentName(const std::string& base_name);

    void setName(const std::string& name) { m_name = name; }
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
    std::unique_ptr<ParameterPool> m_pool; //!< parameter pool (kind of pointer-to-implementation)
};

#endif // BORNAGAIN_PARAM_BASE_IPARAMETRICCOMPONENT_H
#endif // USER_API
