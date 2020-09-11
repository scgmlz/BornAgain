// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/Core/Multilayer.cpp
//! @brief     Implements class MultilayerPerformanceTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/Simulation/StandardSimulations.h"
#include "Core/StandardSamples/PlainMultiLayerBySLDBuilder.h"
#include <chrono>

using Results = std::vector<std::pair<int, long>>;

namespace
{
const std::vector<int> n_layers = {10, 100, 200, 500, 1000};

const auto now = std::chrono::high_resolution_clock::now;
const auto duration = [](auto time_interval) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(time_interval).count();
};

void report(const Results& results)
{
    for (auto& pair : results)
        std::cout << "n_layers = " << pair.first << ",\t time = " << pair.second << " ms\n";
}
} // namespace

int main()
{
    Results results;
    results.reserve(n_layers.size());

    for (int layer_mult : n_layers) {
        const auto start_time = now();
        std::unique_ptr<MultiLayer> sample(PlainMultiLayerBySLDBuilder(layer_mult).buildSample());
        std::unique_ptr<SpecularSimulation> simulation(StandardSimulations::BasicSpecular());
        simulation->setSample(*sample);

        simulation->runSimulation();

        results.push_back({layer_mult, duration(now() - start_time)});
    }

    report(results);
    return 0;
}
