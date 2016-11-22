// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Options/MinimizerOptions.cpp
//! @brief     Implements class MinimizerOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerOptions.h"
#include "StringUtils.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace {
    const std::string delimeter = ";";
}

std::string MinimizerOptions::toOptionString() const
{
    std::ostringstream result;
    for(auto option: m_options) {
        result << option->name() << std::string("=") << option->value() << delimeter;
    }
    return result.str();
}

void MinimizerOptions::setOptionString(const std::string& options)
{
    // splits multiple option string "Strategy=1;Tolerance=0.01;"
    std::vector<std::string> tokens = StringUtils::split(options, delimeter);
    try {
        for(std::string opt : tokens)
            if(opt.size())
                    processCommand(opt);
    } catch(std::exception &ex) {
        std::ostringstream ostr;
        ostr << "MinimizerOptions::setOptions() -> Error. Can't parse option string '"
             << options << "'.\n, error message '"
             << ex.what() << "'";
        throw std::runtime_error(ostr.str());
    }
}

//! Process single option string 'Tolerance=0.01' and sets the value
//! to corresponding MultiOption

void MinimizerOptions::processCommand(const std::string& command)
{
    std::vector<std::string> tokens = StringUtils::split(command, "=");
    if(tokens.size() != 2)
        throw std::runtime_error("MinimizerOptions::processOption() -> Can't parse option '"+
                                 command+"'");

    std::string name = tokens[0];
    std::string value = tokens[1];

    OptionContainer::option_t opt = option(name);
    opt->setFromString(value);
}
