// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Precomputed.h
//! @brief     Defines classes Precomputed, providing precomputed constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PRECOMPUTED_H
#define PRECOMPUTED_H

#include "ISingleton.h"
#include "WinDllMacros.h"
#include <vector>

//! This class contains precomputed constants.

class BA_CORE_API_ Precomputed : public ISingleton<Precomputed>
{
    friend class ISingleton<Precomputed>;

public:
    std::vector<double> factorial; //!< factorial[k] = k! for k=0,1,...,170 (for IEEE double).
    std::vector<double> reciprocal_factorial; //!< 1/k!
private:
    Precomputed(); //!< Constructor, precomputes everything.
};

#endif // PRECOMPUTED_H
