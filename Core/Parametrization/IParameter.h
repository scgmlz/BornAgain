// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IParameter.h
//! @brief     Defines and implements pure virtual base class IParameter<T>.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_IPARAMETER_H
#define BORNAGAIN_CORE_PARAMETRIZATION_IPARAMETER_H

#include <functional>
#include <stdexcept>
#include <string>

//! Pure virtual base class for parameter wrapper classes RealParameter, ComponentParameter.
//! Holds a pointer to the wrapped parameter, a name, and a callback function to be called
//! when the parameter is changed.
//! This class is templated on the data type of the wrapped parameter.
//! @ingroup tools_internal

template <class T> class IParameter
{
public:
    IParameter() = delete;
    IParameter(const std::string& name, T* data, const std::string& parent_name,
               const std::function<void()>& onChange);
    virtual ~IParameter() = default;

    virtual IParameter* clone(const std::string& new_name = "") const = 0;

    //! Returns true if wrapped parameter was not initialized with proper real value
    virtual bool isNull() const { return m_data ? false : true; }

    T& getData() const { return *m_data; }
    void setData(T& data)
    {
        m_data = &data;
        m_onChange();
    }

    bool hasSameData(const IParameter& other);
    const std::string& getName() const { return m_name; }

protected:
    const std::string m_name;
    T* m_data;
    const std::string m_parent_name;
    const std::function<void()> m_onChange;

    //! For use in error messages
    std::string fullName() const { return m_parent_name + "/" + m_name; }
};

template <class T>
IParameter<T>::IParameter(const std::string& name, T* data, const std::string& parent_name,
                          const std::function<void()>& onChange)
    : m_name(name), m_data(data), m_parent_name(parent_name), m_onChange(onChange)
{
    if (!m_data)
        throw std::runtime_error("Attempt to construct an IParameter with null data pointer");
}

//! Returns true if two parameters are pointing to the same raw data.

template <class T> bool IParameter<T>::hasSameData(const IParameter<T>& other)
{
    return &getData() == &other.getData();
}

#endif // BORNAGAIN_CORE_PARAMETRIZATION_IPARAMETER_H
