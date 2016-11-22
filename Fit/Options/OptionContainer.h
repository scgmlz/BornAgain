// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Options/OptionContainer.h
//! @brief     Declares class OptionContainer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OPTIONCONTAINER_H
#define OPTIONCONTAINER_H

#include "WinDllMacros.h"
#include "MultiOption.h"
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>

//! Stores multi option (int,double,string) in a container.
//! @ingroup fitting_internal

class BA_CORE_API_ OptionContainer
{
public:
    using option_t = std::shared_ptr<MultiOption>;
    using container_t = std::vector<option_t>;
    using iterator = container_t::iterator;
    using const_iterator = container_t::const_iterator;

    OptionContainer() {}
    OptionContainer(const OptionContainer& other);
    OptionContainer& operator=(const OptionContainer& other);

    template<class T>
    option_t addOption(const std::string& optionName, T value,
                       const std::string& description = std::string());

    option_t option(const std::string& optionName);
    const option_t option(const std::string& optionName) const;

    template<class T>
    T optionValue(const std::string& optionName) const;

    //! Sets the value of option. Option should hold same value type already.
    template<class T>
    void setOptionValue(const std::string& optionName, T value);

    iterator begin() { return m_options.begin(); }
    const_iterator begin() const { return m_options.begin(); }

    iterator end() { return m_options.end(); }
    const_iterator end() const { return m_options.end(); }

    size_t size() const { return m_options.size(); }

protected:
    bool exists(const std::string& name);
    void swapContent(OptionContainer& other);
    container_t m_options;
};

template<class T>
OptionContainer::option_t OptionContainer::addOption(
    const std::string& optionName, T value, const std::string& description)
{
    if(exists(optionName))
        throw std::runtime_error(
            "OptionContainer::addOption() -> Error. Option '" + optionName + "' exists.");

    option_t result(new MultiOption(optionName, value, description));
    m_options.push_back(result);
    return result;
}

template<class T>
T OptionContainer::optionValue(const std::string& optionName) const
{
    return option(optionName)->get<T>();
}

template<class T>
void OptionContainer::setOptionValue(const std::string& optionName, T value)
{
    option(optionName)->value() = value;
    if(option(optionName)->value().which() != option(optionName)->defaultValue().which())
        throw std::runtime_error(
            "OptionContainer::setOptionValue() -> Error. Attempt to set different"
            "type to option '"+optionName+"'");
}

#endif // OPTIONCONTAINER_H
