// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationUtils.h
//! @brief     Declares utility functions for IComputation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ICOMPUTATIONUTILS_H
#define ICOMPUTATIONUTILS_H

#include <map>
#include <memory>
#include <vector>

class HomogeneousRegion;
class IFresnelMap;
class MultiLayer;
class SimulationOptions;

namespace IComputationUtils {
std::unique_ptr<IFresnelMap> CreateFresnelMap(const MultiLayer& multilayer,
                                              const SimulationOptions& sim_options,
                                              bool allow_average_layers=true);
// creates a multilayer that contains averaged materials, for use in Fresnel calculations
std::unique_ptr<MultiLayer> CreateAveragedMultilayer(
        const MultiLayer& multilayer,
        const std::map<size_t, std::vector<HomogeneousRegion>>& region_map = {});
std::map<size_t, std::vector<HomogeneousRegion>> GetRegionMap(const MultiLayer& multilayer);
void MergeRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& dest,
                    const std::map<size_t, std::vector<HomogeneousRegion>>& source);
}

#endif  // ICOMPUTATIONUTILS_H
