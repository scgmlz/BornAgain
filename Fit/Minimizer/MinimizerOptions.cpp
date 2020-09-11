// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerOptions.cpp
//! @brief     Implements class MinimizerOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Minimizer/MinimizerOptions.h"
#include "Fit/Tools/StringUtils.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
const std::string delimeter = ";";
}

std::string MinimizerOptions::toOptionString() const
{
    std::ostringstream result;
    for (auto option : m_options) {
        result << option->name() << "=" << option->value() << delimeter;
    }
    return result.str();
}

void MinimizerOptions::setOptionString(const std::string& options)
{
    // splits multiple option string "Strategy=1;Tolerance=0.01;"
    std::vector<std::string> tokens = StringUtils::split(options, delimeter);
    try {
        for (std::string opt : tokens)
            if (opt.size())
                processCommand(opt);
    } catch (std::exception& ex) {
        std::ostringstream ostr;
        ostr << "MinimizerOptions::setOptions() -> Error. Can't parse option string '" << options
             << "'.\n, error message '" << ex.what() << "'";
        throw std::runtime_error(ostr.str());
    }
}

//! Process single option string 'Tolerance=0.01' and sets the value
//! to corresponding MultiOption

void MinimizerOptions::processCommand(const std::string& command)
{
    std::vector<std::string> tokens = StringUtils::split(command, "=");
    if (tokens.size() != 2)
        throw std::runtime_error("MinimizerOptions::processOption() -> Can't parse option '"
                                 + command + "'");

    std::string name = tokens[0];
    std::string value = tokens[1];

    OptionContainer::option_t opt = option(name);
    opt->setFromString(value);
}
