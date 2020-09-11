// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/OptionContainer.cpp
//! @brief     Implements class OptionContainer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Tools/OptionContainer.h"
#include <sstream>

//! Returns true if option with such name already exists.
OptionContainer::OptionContainer(const OptionContainer& other)
{
    for (const auto& option : other.m_options)
        m_options.push_back(option_t(new MultiOption(*option)));
}

OptionContainer& OptionContainer::operator=(const OptionContainer& other)
{
    if (this != &other) {
        OptionContainer tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

OptionContainer::option_t OptionContainer::option(const std::string& optionName)
{
    for (const auto& option : m_options) {
        if (option->name() == optionName)
            return option;
    }

    throw std::runtime_error("Configurable::getOption() -> Error. No option with name '"
                             + optionName + "'.");
}

const OptionContainer::option_t OptionContainer::option(const std::string& optionName) const
{
    for (const auto& option : m_options) {
        if (option->name() == optionName)
            return option;
    }

    throw std::runtime_error("Configurable::getOption() -> Error. No option with name '"
                             + optionName + "'.");
}

bool OptionContainer::exists(const std::string& name)
{
    for (const auto& option : m_options) {
        if (option->name() == name)
            return true;
    }
    return false;
}

void OptionContainer::swapContent(OptionContainer& other)
{
    std::swap(m_options, other.m_options);
}
