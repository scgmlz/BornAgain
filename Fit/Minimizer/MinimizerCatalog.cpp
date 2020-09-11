// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerCatalog.cpp
//! @brief     Implements class MinimizerCatalog.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Minimizer/MinimizerCatalog.h"
#include "Fit/Tools/MinimizerUtils.h"
#include <boost/format.hpp>
#include <sstream>

MinimizerCatalog::MinimizerCatalog()
{
    addMinimizerInfo(MinimizerInfo::buildMinuit2Info());
    addMinimizerInfo(MinimizerInfo::buildGSLMultiMinInfo());
    addMinimizerInfo(MinimizerInfo::buildGSLLMAInfo());
    addMinimizerInfo(MinimizerInfo::buildGSLSimAnInfo());
    addMinimizerInfo(MinimizerInfo::buildGeneticInfo());
    addMinimizerInfo(MinimizerInfo::buildTestMinimizerInfo());
}

//! Returns multiline string representing catalog content.

std::string MinimizerCatalog::toString() const
{
    const int text_width = 80;
    std::ostringstream result;

    result << std::string(text_width, '-') << "\n";
    result << boost::format("%-15s|%-65s\n") % "Minimizer" % " Algorithms";
    result << std::string(text_width, '-') << "\n";

    for (const auto& info : m_minimizers) {
        result << boost::format("%-15s| %-64s\n") % info.name()
                      % MinimizerUtils::toString(info.algorithmNames(), " ");
    }
    return result.str();
}

std::vector<std::string> MinimizerCatalog::minimizerNames() const
{
    std::vector<std::string> result;
    for (const auto& info : m_minimizers)
        result.push_back(info.name());

    return result;
}

//! Returns list of algorithms defined for the minimizer with a given name.

std::vector<std::string> MinimizerCatalog::algorithmNames(const std::string& minimizerName) const
{
    return minimizerInfo(minimizerName).algorithmNames();
}

//! Returns list of algorithm's descriptions for the minimizer with a given name    .

std::vector<std::string>
MinimizerCatalog::algorithmDescriptions(const std::string& minimizerName) const
{
    return minimizerInfo(minimizerName).algorithmDescriptions();
}

//! Returns info for minimizer with given name.

const MinimizerInfo& MinimizerCatalog::minimizerInfo(const std::string& minimizerName) const
{
    for (const auto& info : m_minimizers)
        if (info.name() == minimizerName)
            return info;

    throw std::runtime_error("MinimizerCatalog::minimizerInfo -> Error. "
                             "No minimizer with the name '"
                             + minimizerName + "'");
}

//! Adds minimizer info to the catalog.

void MinimizerCatalog::addMinimizerInfo(const MinimizerInfo& info)
{
    m_minimizers.push_back(info);
}
