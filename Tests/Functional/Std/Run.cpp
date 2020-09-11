// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Std/Run.cpp
//! @brief     Implements function run for use in standard tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BABuild.h"
#include "BATesting.h"
#include "Core/Basics/Assert.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Tools/FileSystemUtils.h"
#include <iostream>

// implemented differently for Core/Py/Gui tests:
bool checkSimulation(const std::string& name, const Simulation& direct_simulation,
                     const double limit);

int run(const std::string& test_name, const std::string& sim_name,
        const std::string& sample_builder_name, const double limit)
{
    std::cout << "run std test " << test_name << std::endl;
    std::cout << "- create sim " << sim_name << std::endl;
    std::unique_ptr<Simulation> simulation{SimulationFactory().createItem(sim_name)};
    ASSERT(simulation);

    std::cout << "- sample builder " << sample_builder_name << std::endl;
    std::unique_ptr<IMultiLayerBuilder> builder{
        SampleBuilderFactory().createItem(sample_builder_name)};
    std::cout << "- builder name " << builder->getName() << std::endl;

    int number_of_failed_tests = 0;
    for (size_t iSample = 0; iSample < builder->size(); ++iSample) {
        std::cout << "- run subtest " << iSample << "/" << builder->size() << ": "
                  << builder->getName() << "\n";

        std::unique_ptr<MultiLayer> sample(builder->createSample(iSample));
        simulation->setSample(*sample);

        std::string full_name = test_name;
        if (builder->getName() != "SampleBuilder")
            full_name += "_" + builder->getName();

        simulation->runSimulation();

        if (!checkSimulation(full_name, *simulation, limit))
            ++number_of_failed_tests;
    }

    return !number_of_failed_tests;
}
