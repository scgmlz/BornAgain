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

#ifndef BORNAGAIN_FIT_MINIMIZER_MINIMIZERFACTORY_H
#define BORNAGAIN_FIT_MINIMIZER_MINIMIZERFACTORY_H

#include "Fit/Minimizer/MinimizerCatalog.h"
#include "Wrap/WinDllMacros.h"
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

    static void printCatalog();

    static std::string catalogToString();

    static std::string catalogDetailsToString();

    static const MinimizerCatalog& catalog();
};

#endif // BORNAGAIN_FIT_MINIMIZER_MINIMIZERFACTORY_H
