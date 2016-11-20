// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerCatalogue.h
//! @brief     Defines class MinimizerCatalogue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERCATALOGUE_H
#define MINIMIZERCATALOGUE_H

#include "WinDllMacros.h"
#include "MinimizerInfo.h"
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

class BA_CORE_API_ MinimizerCatalogue {
public:
    MinimizerCatalogue();

    std::string toString() const;

    std::vector<std::string> algorithmNames(const std::string& minimizerName) const;

    std::vector<std::string> algorithmDescriptions(const std::string& minimizerName) const;

private:
    MinimizerInfo minimizerInfo(const std::string& minimizerName) const;

    void addMinimizerInfo(const MinimizerInfo& info);
    std::vector<MinimizerInfo> m_minimizers;
};

#endif // MINIMIZERCATALOGUE_H
