// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/SelfConsistenceTest/SelfConsistenceTestService.cpp
//! @brief     Implements class SelfConsistenceTestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SelfConsistenceTestService.h"
#include "SelfConsistenceTest.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "SimulationFactory.h"
#include "TestUtils.h"

using sim_ptr = std::unique_ptr<Simulation>;
using builder_ptr = std::unique_ptr<IMultiLayerBuilder>;

bool SelfConsistenceTestService::execute(int argc, char** argv)
{
    StandardTestInfo info = TestUtils::testInfo(argc, argv);
    if (info.m_test_name.empty())
        return false;

    std::vector<sim_ptr> simulations;
    for (size_t i = 0, size = info.size(); i < size; ++i) {
        builder_ptr builder(SampleBuilderFactory().createItem(info.m_sample_builder_names[i]));
        sim_ptr simulation(SimulationFactory().createItem(info.m_simulation_names[i]));
        simulation->setSampleBuilder(std::move(builder));
        simulations.push_back(std::move(simulation));
    }

    auto test = std::make_unique<SelfConsistenceTest>(info.m_test_name, info.m_test_description,
                                                      std::move(simulations), info.m_threshold);
    return test->execute();
}
