// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/MinimizerResultsHelper.cpp
//! @brief     Implements class MinimizerResultsHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerResultsHelper.h"
#include "RootMinimizerAdapter.h"
#include "FitParameterSet.h"
#include "FitParameter.h"
#include "MinimizerUtils.h"
#include <boost/format.hpp>
#include <iomanip>
#include <sstream>

namespace {

    const int column_width = 18;

    template<typename T>
    std::string reportValue(const std::string& name, T value)
    {
        std::ostringstream result;
        result << std::setw(column_width) << std::left << name  << ": " << value << std::endl;
        return result.str();
    }

} // namespace


std::string MinimizerResultsHelper::reportOutcome(const RootMinimizerAdapter* minimizer)
{
    std::ostringstream result;

    result << MinimizerUtils::sectionString();
    result << reportDescription(minimizer);
    result << reportOption(minimizer);
    result << reportStatus(minimizer);

    return result.str();
}

std::string MinimizerResultsHelper::reportParameters(const FitParameterSet* parameters)
{
    std::ostringstream result;

    result << MinimizerUtils::sectionString("FitParameters");

    result << "Npar Name        StartValue  Limits           FitValue  Error" << std::endl;

    int npar(0);
    for(const FitParameter* par : *parameters) {
        result << boost::format("#%-2d  %-10s  %-6.4f      %-15s  %-6.4f    %5.4f \n")
                  % npar
                  % par->name()
                  % par->startValue()
                  % par->limits().toString()
                  % par->value()
                  % par->error();
        ++npar;
    }

    FitParameterSet::corr_matrix_t matrix = parameters->correlationMatrix();
    if(matrix.size()) {
        result << MinimizerUtils::sectionString("Correlations");
        for(size_t i=0; i<matrix.size(); ++i) {
            result << boost::format("#%-2d       ") %i;
            for(size_t j=0; j<matrix[i].size(); ++j)
                result << boost::format("%_7.4f    ") % matrix[i][j];
            result << std::endl;
        }

    }

    return result.str();
}

std::string MinimizerResultsHelper::reportDescription(const RootMinimizerAdapter* minimizer)
{
    std::ostringstream result;
    result << reportValue("MinimizerType", minimizer->minimizerName());
    result << reportValue("AlgorithmName", minimizer->algorithmName());
    return result.str();
}

std::string MinimizerResultsHelper::reportOption(const RootMinimizerAdapter* minimizer)
{
    if(minimizer->options().size() == 0)
        return "";

    std::ostringstream result;
    result << MinimizerUtils::sectionString("Options");
    for(auto option : minimizer->options()) {
        std::ostringstream opt;
        opt << std::setw(5) << std::left << option->value() << option->description();
        result << reportValue(option->name(), opt.str());
    }
    result << MinimizerUtils::sectionString("OptionString");
    result << minimizer->options().toOptionString() << std::endl;

    return result.str();
}

std::string MinimizerResultsHelper::reportStatus(const RootMinimizerAdapter* minimizer)
{
    std::ostringstream result;
    result << MinimizerUtils::sectionString("Status");

    auto status = minimizer->statusMap();
    for(auto it : status)
        result << reportValue(it.first, it.second);

    return result.str();
}
