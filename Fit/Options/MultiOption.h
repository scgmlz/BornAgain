// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Options/MultiOption.h
//! @brief     Declares class MultiOption
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTIOPTION_H
#define MULTIOPTION_H

#include "WinDllMacros.h"
#include <boost/variant.hpp>
#include <string>

//! Stores a single option for minimization algorithm. Int, double, string values are available.
//! Relies on boost::variant, will be switched to std::variant in C++-17.
//! @ingroup fitting_internal

class BA_CORE_API_ MultiOption
{
public:
    using variant_t = boost::variant<int, double, std::string>;

    explicit MultiOption(const std::string& name = std::string());

    template<typename T>
    explicit MultiOption(const std::string& name, const T& t,
                         const std::string& descripion = std::string());

    std::string name() const;

    std::string description() const;
    void setDescription(const std::string& description);

    variant_t& value();
    variant_t& defaultValue();

    //! Returns the option's value
    template<typename T>
    T get() const;

    //! Returns the option's default value (i.e. used during construction)
    template<typename T>
    T getDefault() const;

    void setFromString(const std::string& value);

private:
    std::string m_name;
    std::string m_description;
    variant_t m_value;
    variant_t m_default_value;
};


template<typename T>
MultiOption::MultiOption(const std::string& name, const T& t, const std::string& descripion)
{
    m_name = name;
    m_description = descripion;
    m_value = t;
    m_default_value = t;
}

template<typename T>
T MultiOption::get() const
{
    return boost::get<T>(m_value);
}

template<typename T>
T MultiOption::getDefault() const
{
    return boost::get<T>(m_default_value);
}

#endif // MULTIOPTION_H
