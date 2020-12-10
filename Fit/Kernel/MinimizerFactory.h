//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerFactory.h
//! @brief     Defines class MinimizerFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_FIT_KERNEL_MINIMIZERFACTORY_H
#define BORNAGAIN_FIT_KERNEL_MINIMIZERFACTORY_H

#include "Fit/Minimizer/MinimizerCatalog.h"
#include <string>

class IMinimizer;

//! Factory to create minimizers.
//! @ingroup fitting

class MinimizerFactory {
public:
    static IMinimizer* createMinimizer(const std::string& minimizerName,
                                       const std::string& algorithmType = "",
                                       const std::string& optionString = "");

    static void printCatalog();

    static std::string catalogToString();

    static std::string catalogDetailsToString();

    static const MinimizerCatalog& catalog();
};

#endif // BORNAGAIN_FIT_KERNEL_MINIMIZERFACTORY_H
