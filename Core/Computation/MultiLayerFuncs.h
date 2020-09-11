// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultiLayerFuncs.h
//! @brief     Global functions related to MultiLayers.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_MULTILAYERFUNCS_H
#define BORNAGAIN_CORE_COMPUTATION_MULTILAYERFUNCS_H

#include "Core/Basics/Complex.h"
#include "Wrap/WinDllMacros.h"
#include <utility>
#include <vector>

class MultiLayer;

//! @ingroup materials

//! Calculate average material profile for given multilayer
BA_CORE_API_ std::vector<complex_t> MaterialProfile(const MultiLayer& multilayer, int n_points,
                                                    double z_min, double z_max);

//! Get default z limits for generating a material profile
BA_CORE_API_ std::pair<double, double> DefaultMaterialProfileLimits(const MultiLayer& multilayer);

//! Generate z values (equidistant) for use in MaterialProfile
BA_CORE_API_ std::vector<double> GenerateZValues(int n_points, double z_min, double z_max);

#endif // BORNAGAIN_CORE_COMPUTATION_MULTILAYERFUNCS_H
