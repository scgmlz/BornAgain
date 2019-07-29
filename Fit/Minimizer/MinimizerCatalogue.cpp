// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerCatalogue.cpp
//! @brief     Implements class MinimizerCatalogue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerCatalogue.h"
#include "MinimizerUtils.h"
#include <boost/format.hpp>
#include <sstream>

MinimizerCatalogue::MinimizerCatalogue()
{
    addMinimizerInfo(MinimizerInfo::buildMinuit2Info());
    addMinimizerInfo(MinimizerInfo::buildGSLMultiMinInfo());
    addMinimizerInfo(MinimizerInfo::buildGSLLMAInfo());
    addMinimizerInfo(MinimizerInfo::buildGSLSimAnInfo());
    addMinimizerInfo(MinimizerInfo::buildGeneticInfo());
    addMinimizerInfo(MinimizerInfo::buildTestMinimizerInfo());
}

//! Returns multiline string representing catalogue content.

std::string MinimizerCatalogue::toString() const
{
    const int text_width = 80;
    std::ostringstream result;

    result << std::string(text_width, '-') << "\n";
    result << boost::format("%-15s|%-65s\n") % "Minimizer" % " Algorithms";
    result << std::string(text_width, '-') << "\n";

    for (const auto& info : m_minimizers) {
        result << boost::format("%-15s| %-64s\n") % info.name()
                      % MinimizerUtils::toString(info.algorithmNames(), std::string(" "));
    }
    return result.str();
}

std::vector<std::string> MinimizerCatalogue::minimizerNames() const
{
    std::vector<std::string> result;
    for (const auto& info : m_minimizers)
        result.push_back(info.name());

    return result;
}

//! Returns list of algorithms defined for the minimizer with a given name.

std::vector<std::string> MinimizerCatalogue::algorithmNames(const std::string& minimizerName) const
{
    return minimizerInfo(minimizerName).algorithmNames();
}

//! Returns list of algorithm's descriptions for the minimizer with a given name    .

std::vector<std::string>
MinimizerCatalogue::algorithmDescriptions(const std::string& minimizerName) const
{
    return minimizerInfo(minimizerName).algorithmDescriptions();
}

//! Returns info for minimizer with given name.

const MinimizerInfo& MinimizerCatalogue::minimizerInfo(const std::string& minimizerName) const
{
    for (const auto& info : m_minimizers)
        if (info.name() == minimizerName)
            return info;

    throw std::runtime_error("MinimizerCatalogue::minimizerInfo -> Error. "
                             "No minimizer with the name '"
                             + minimizerName + "'");
}

//! Adds minimizer info to the catalogue.

void MinimizerCatalogue::addMinimizerInfo(const MinimizerInfo& info)
{
    m_minimizers.push_back(info);
}
