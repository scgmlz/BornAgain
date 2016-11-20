// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Options/MultiOption.cpp
//! @brief     Implements class MultiOption
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiOption.h"
#include <boost/lexical_cast.hpp>

MultiOption::MultiOption(const std::string& name)
    : m_name(name)
{
}

std::string MultiOption::name() const
{
    return m_name;
}

std::string MultiOption::description() const
{
    return m_description;
}

void MultiOption::setDescription(const std::string& description)
{
    m_description = description;
}

MultiOption::variant_t& MultiOption::value()
{
    return m_value;
}

MultiOption::variant_t& MultiOption::defaultValue()
{
    return m_default_value;
}

//! Sets the value of option from string.
//! TODO find more elegant way (without if/else and boost::lexical_cast

void MultiOption::setFromString(const std::string& value)
{
    if (m_value.which() == 0) {
        m_value = boost::lexical_cast<int>(value);
    } else if (m_value.which() == 1) {
        m_value = boost::lexical_cast<double>(value);
    } else {
        m_value = value;
    }
}
