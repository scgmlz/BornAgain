// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerFactory.h
//! @brief     Defines class MinimizerFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERFACTORY_H
#define MINIMIZERFACTORY_H

#include "MinimizerCatalogue.h"
#include "WinDllMacros.h"
#include <string>

class IMinimizer;

//! Factory to create minimizers.
//! @ingroup fitting

class BA_CORE_API_ MinimizerFactory
{
public:
    static IMinimizer* createMinimizer(const std::string& minimizerName,
                                       const std::string& algorithmType = "",
                                       const std::string& optionString = "");

    static void printCatalogue();

    static std::string catalogueToString();

    static std::string catalogueDetailsToString();

    static const MinimizerCatalogue& catalogue();
};

#endif // MINIMIZERFACTORY_H
