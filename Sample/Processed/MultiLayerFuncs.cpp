//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Processed/MultiLayerFuncs.cpp
//! @brief     Global functions related to MultiLayers.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Processed/MultiLayerFuncs.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/Processed/ProfileHelper.h"
#include "Sample/RT/SimulationOptions.h"

std::vector<double> swigAPI::generateZValues(int n_points, double z_min, double z_max) {
    std::vector<double> result;
    if (n_points < 1)
        return result;
    double step = n_points > 1 ? (z_max - z_min) / (n_points - 1) : 0.0;
    for (int i = 0; i < n_points; ++i) {
        result.push_back(z_min + i * step);
    }
    return result;
}

std::vector<complex_t> swigAPI::materialProfileSLD(const MultiLayer& multilayer, int n_points,
                                                   double z_min, double z_max) {
    SimulationOptions options;
    options.setUseAvgMaterials(true);
    ProcessedSample sample(multilayer, options);
    ProfileHelper helper(sample);
    std::vector<double> z_values = generateZValues(n_points, z_min, z_max);
    return helper.calculateProfile(z_values);
}

std::pair<double, double> swigAPI::defaultMaterialProfileLimits(const MultiLayer& multilayer) {
    SimulationOptions options;
    options.setUseAvgMaterials(true);
    ProcessedSample sample(multilayer, options);
    ProfileHelper helper(sample);
    return helper.defaultLimits();
}
