//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/Report.cpp
//! @brief     Implements report namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Adapter/Report.h"
#include "Fit/Adapter/MinimizerAdapter.h"
#include "Fit/Tools/MinimizerUtils.h"
#include <iomanip>
#include <sstream>

namespace {

const int column_width = 18;

template <typename T> std::string reportValue(const std::string& name, T value) {
    std::ostringstream result;
    result << std::setw(column_width) << std::left << name << ": " << value << std::endl;
    return result.str();
}

std::string reportDescription(const MinimizerAdapter& minimizer) {
    std::ostringstream result;
    result << reportValue("MinimizerType", minimizer.minimizerName());
    result << reportValue("AlgorithmName", minimizer.algorithmName());
    return result.str();
}

std::string reportOption(const MinimizerAdapter& minimizer) {
    if (minimizer.options().empty())
        return "";

    std::ostringstream result;
    result << mumufit::utils::sectionString("Options");
    for (auto option : minimizer.options()) {
        std::ostringstream opt;
        opt << std::setw(5) << std::left << option->value() << option->description();
        result << reportValue(option->name(), opt.str());
    }
    result << mumufit::utils::sectionString("OptionString");
    result << minimizer.options().toOptionString() << std::endl;

    return result.str();
}

std::string reportStatus(const MinimizerAdapter& minimizer) {
    std::ostringstream result;
    result << mumufit::utils::sectionString("Status");

    auto status = minimizer.statusMap();
    for (auto it : status)
        result << reportValue(it.first, it.second);

    return result.str();
}

} // namespace

//  ************************************************************************************************
//  implement API
//  ************************************************************************************************

std::string mumufit::internal::reportToString(const MinimizerAdapter& minimizer) {
    std::ostringstream result;

    result << mumufit::utils::sectionString();
    result << reportDescription(minimizer);
    result << reportOption(minimizer);
    result << reportStatus(minimizer);

    return result.str();
}
