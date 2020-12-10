//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/OptionContainer.h
//! @brief     Declares class OptionContainer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_FIT_TOOLS_OPTIONCONTAINER_H
#define BORNAGAIN_FIT_TOOLS_OPTIONCONTAINER_H

#include "Fit/Tools/MultiOption.h"
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

//! Stores multi option (int,double,string) in a container.
//! @ingroup fitting_internal

class OptionContainer {
public:
    using option_t = std::shared_ptr<MultiOption>;
    using container_t = std::vector<option_t>;
    using iterator = container_t::iterator;
    using const_iterator = container_t::const_iterator;

    OptionContainer() {}
    OptionContainer(const OptionContainer& other);
    OptionContainer& operator=(const OptionContainer& other);

    template <class T>
    option_t addOption(const std::string& optionName, T value, const std::string& description = "");

    option_t option(const std::string& optionName);
    const option_t option(const std::string& optionName) const;

    template <class T> T optionValue(const std::string& optionName) const;

    //! Sets the value of option. Option should hold same value type already.
    template <class T> void setOptionValue(const std::string& optionName, T value);

    iterator begin() { return m_options.begin(); }
    const_iterator begin() const { return m_options.begin(); }

    iterator end() { return m_options.end(); }
    const_iterator end() const { return m_options.end(); }

    size_t size() const { return m_options.size(); }
    bool empty() const { return size() == 0; }

protected:
    bool exists(const std::string& name);
    void swapContent(OptionContainer& other);
    container_t m_options;
};

template <class T>
OptionContainer::option_t OptionContainer::addOption(const std::string& optionName, T value,
                                                     const std::string& description) {
    if (exists(optionName))
        throw std::runtime_error("OptionContainer::addOption() -> Error. Option '" + optionName
                                 + "' exists.");

    option_t result(new MultiOption(optionName, value, description));
    m_options.push_back(result);
    return result;
}

template <class T> T OptionContainer::optionValue(const std::string& optionName) const {
    return option(optionName)->get<T>();
}

template <class T> void OptionContainer::setOptionValue(const std::string& optionName, T value) {
    option(optionName)->value() = value;
    if (option(optionName)->value().which() != option(optionName)->defaultValue().which())
        throw std::runtime_error(
            "OptionContainer::setOptionValue() -> Error. Attempt to set different"
            "type to option '"
            + optionName + "'");
}

#endif // BORNAGAIN_FIT_TOOLS_OPTIONCONTAINER_H
#endif // USER_API
