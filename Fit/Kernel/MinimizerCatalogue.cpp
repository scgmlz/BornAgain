// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerCatalogue.cpp
//! @brief     Implements class MinimizerCatalogue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerCatalogue.h"
#include "MinimizerUtils.h"
#include <sstream>
#include <boost/format.hpp>

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

    for(MinimizerInfo minimizer : m_minimizers) {
        result << boost::format("%-15s| %-64s\n")
                  % minimizer.name()
                  % MinimizerUtils::toString(minimizer.algorithmNames(), std::string(" "));

    }
    return result.str();
}

//! Returns list of algorithms defined for the minimizer with a given name.

std::vector<std::string> MinimizerCatalogue::algorithmNames(const std::string& minimizerName) const
{
    return minimizerInfo(minimizerName).algorithmNames();
}

//! Returns list of algorithm's descriptions for the minimizer with a given name    .

std::vector<std::string> MinimizerCatalogue::algorithmDescriptions(
    const std::string& minimizerName) const
{
    return minimizerInfo(minimizerName).algorithmDescriptions();
}

//! Returns info for minimizer with given name.

MinimizerInfo MinimizerCatalogue::minimizerInfo(const std::string& minimizerName) const
{
    for(auto info : m_minimizers)
        if(info.name() == minimizerName)
            return info;

    throw std::runtime_error("MinimizerCatalogue::minimizerInfo -> Error. "
                             "No minimizer with the name '"+minimizerName+"'");
}

//! Adds minimizer info to the catalogue.

void MinimizerCatalogue::addMinimizerInfo(const MinimizerInfo& info)
{
    m_minimizers.push_back(info);
}
