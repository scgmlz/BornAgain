// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultiLayerFuncs.cpp
//! @brief     Global functions related to MultiLayers.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/MultiLayerFuncs.h"
#include "Core/Computation/ProcessedSample.h"
#include "Core/Computation/ProfileHelper.h"
#include "Core/Parametrization/SimulationOptions.h"

std::vector<complex_t> MaterialProfile(const MultiLayer& multilayer, int n_points, double z_min,
                                       double z_max)
{
    SimulationOptions options;
    options.setUseAvgMaterials(true);
    ProcessedSample sample(multilayer, options);
    ProfileHelper helper(sample);
    std::vector<double> z_values = GenerateZValues(n_points, z_min, z_max);
    return helper.calculateProfile(z_values);
}

std::pair<double, double> DefaultMaterialProfileLimits(const MultiLayer& multilayer)
{
    SimulationOptions options;
    options.setUseAvgMaterials(true);
    ProcessedSample sample(multilayer, options);
    ProfileHelper helper(sample);
    return helper.defaultLimits();
}

std::vector<double> GenerateZValues(int n_points, double z_min, double z_max)
{
    std::vector<double> result;
    if (n_points < 1)
        return result;
    double step = n_points > 1 ? (z_max - z_min) / (n_points - 1) : 0.0;
    for (int i = 0; i < n_points; ++i) {
        result.push_back(z_min + i * step);
    }
    return result;
}
