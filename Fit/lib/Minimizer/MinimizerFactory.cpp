// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerFactory.cpp
//! @brief     Implements class MinimizerFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerFactory.h"
#include "GSLLevenbergMarquardtMinimizer.h"
#include "GSLMultiMinimizer.h"
#include "GeneticMinimizer.h"
#include "MinimizerCatalogue.h"
#include "Minuit2Minimizer.h"
#include "SimAnMinimizer.h"
#include "TestMinimizer.h"
#include <boost/format.hpp>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

IMinimizer* MinimizerFactory::createMinimizer(const std::string& minimizerName,
                                              const std::string& algorithmType,
                                              const std::string& optionString)
{
    IMinimizer* result(0);

    if (minimizerName == MinimizerNames::Minuit2) {
        result = new Minuit2Minimizer(algorithmType);
    }

    else if (minimizerName == MinimizerNames::GSLLMA) {
        result = new GSLLevenbergMarquardtMinimizer();
    }

    else if (minimizerName == MinimizerNames::GSLSimAn) {
        result = new SimAnMinimizer();
    }

    else if (minimizerName == MinimizerNames::GSLMultiMin) {
        result = new GSLMultiMinimizer(algorithmType);
    }

    else if (minimizerName == MinimizerNames::Genetic) {
        result = new GeneticMinimizer();
    }

    else if (minimizerName == MinimizerNames::Test) {
        result = new TestMinimizer();
    }

    if (!result) {
        std::ostringstream ostr;
        ostr << "MinimizerFactory::MinimizerFactory() -> Error! Can't create minimizer for given "
                "collection name '"
             << minimizerName << "' or algorithm '" << algorithmType << "'" << std::endl;
        ostr << "Possible names are:" << std::endl;

        ostr << catalogue().toString();
        throw std::runtime_error(ostr.str());
    }

    if (!optionString.empty())
        result->setOptions(optionString);

    return result;
}

void MinimizerFactory::printCatalogue()
{
    std::cout << catalogueToString() << std::endl;
}

//! Returns multi-line string representing catalogue content: minimizer names and list of their
//! algorithms.

std::string MinimizerFactory::catalogueToString()
{
    return catalogue().toString();
}

//! Returns multi-line string representing detailed catalogue content:
//! minimizer names, list of their algorithms and description, list of minimizer options.

std::string MinimizerFactory::catalogueDetailsToString()
{
    const int text_width = 80;
    std::ostringstream result;
    const std::string fmt("%-20s| %-65s\n");

    for (const auto& minimizerName : catalogue().minimizerNames()) {
        // general info
        const MinimizerInfo& info = catalogue().minimizerInfo(minimizerName);
        result << std::string(text_width, '-') << "\n";
        result << boost::format(fmt) % info.name() % info.description();
        result << std::string(text_width, '-') << "\n";

        // algorithm names and description
        result << "\nAlgorithm names\n";
        auto algorithmNames = info.algorithmNames();
        auto algorithmDescription = info.algorithmDescriptions();
        for (size_t i = 0; i < algorithmNames.size(); ++i)
            result << boost::format(fmt) % algorithmNames[i] % algorithmDescription[i];
        if (algorithmNames.size() > 1)
            result << boost::format(fmt) % "Default algorithm" % info.algorithmName();

        // list of minimizer options
        std::unique_ptr<IMinimizer> minimizer(createMinimizer(minimizerName));
        if (auto rootMinimizer = dynamic_cast<RootMinimizerAdapter*>(minimizer.get())) {
            result << "\nOptions\n";
            for (auto option : rootMinimizer->options()) {
                std::ostringstream opt;
                opt << std::setw(5) << std::left << option->value() << option->description();
                result << boost::format(fmt) % option->name() % opt.str();
            }
        }

        result << "\n";
    }

    return result.str();
}

const MinimizerCatalogue& MinimizerFactory::catalogue()
{
    static MinimizerCatalogue s_catalogue = MinimizerCatalogue();
    return s_catalogue;
}
