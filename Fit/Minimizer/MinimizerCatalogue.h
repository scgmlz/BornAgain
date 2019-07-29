// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerCatalogue.h
//! @brief     Defines class MinimizerCatalogue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERCATALOGUE_H
#define MINIMIZERCATALOGUE_H

#include "MinimizerInfo.h"
#include "WinDllMacros.h"
#include <map>

//! Hard-coded information about all minimizers available.
//! @ingroup fitting_internal

/*
--------------------------------------------------------------------------------
Minimizer      | Algorithms
--------------------------------------------------------------------------------
Minuit2        | Migrad Simplex Combined Scan Fumili
GSLMultiMin    | SteepestDescent ConjugateFR ConjugatePR BFGS BFGS2
GSLLMA         | Default
GSLSimAn       | Default
Genetic        | Default
Test           | Default
*/

class BA_CORE_API_ MinimizerCatalogue
{
public:
    MinimizerCatalogue();

    std::string toString() const;

    std::vector<std::string> minimizerNames() const;

    std::vector<std::string> algorithmNames(const std::string& minimizerName) const;

    std::vector<std::string> algorithmDescriptions(const std::string& minimizerName) const;

    const MinimizerInfo& minimizerInfo(const std::string& minimizerName) const;

private:
    void addMinimizerInfo(const MinimizerInfo& info);
    std::vector<MinimizerInfo> m_minimizers;
};

#endif // MINIMIZERCATALOGUE_H
