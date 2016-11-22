// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IParameter.h
//! @brief     Defines and implements pure virtual base class IParameter<T>.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARAMETER_H
#define IPARAMETER_H

#include "INoncopyable.h"
#include "INamed.h"
#include <functional>
#include <stdexcept>
#include <string>

//! Pure virtual base class for parameter wrapper classes RealParameter, ComponentParameter.
//! Holds a pointer to the wrapped parameter, a name, and a callback function to be called
//! when the parameter is changed.
//! This class is templated on the data type of the wrapped parameter.
//! @ingroup tools_internal

template<class T>
class BA_CORE_API_ IParameter : public INamed, public INoncopyable {
public:
    IParameter() =delete;
    IParameter(const std::string& name, volatile T* data, const std::string& parent_name,
               const std::function<void()>& onChange)
        : INamed(name), m_data(data), m_parent_name(parent_name), m_onChange(onChange) {
            if(!m_data)
                throw std::runtime_error(
                    "Bug: attempt to construct an IParameter with null data pointer"); }

    virtual IParameter* clone( const std::string& new_name="" ) const =0;

    //! Returns true if wrapped parameter was not initialized with proper real value
    virtual bool isNull() const { return m_data ? false : true; }

    volatile T& getData() const { return *m_data; }
    void setData(volatile T& data) { m_data = &data; m_onChange(); }

    //! Prints the parameter's address to an output stream
    friend std::ostream& operator<<(std::ostream& ostr, const IParameter& p) {
        ostr << p.m_data; return ostr; }

    bool operator==(const IParameter &other) const { return m_data == other.m_data; }
    bool operator!=(const IParameter &other) const { return !(*this == other); }

protected:
    volatile T* m_data;
    std::string m_parent_name;
    std::function<void()> m_onChange;

    //! For use in error messages
    std::string fullName() { return m_parent_name + "/" + getName(); }
};

#endif // IPARAMETER_H
