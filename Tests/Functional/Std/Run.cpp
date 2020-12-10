//  ************************************************************************************************
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
//  ************************************************************************************************

#include "Tests/Functional/Std/Run.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/StandardSamples/SampleBuilderFactory.h"
#include "Tests/Functional/Std/StandardTests.h" // provides F_TEST macros to be executed by gtest
#include <iostream>

//! This function, called from run, has different implementations in Core/Py/Gui tests:
bool checkSimulation(const std::string& name, const ISimulation& direct_simulation,
                     const double limit);

//! This function is called through EXPECT_TRUE macros in StandardTests.h.
//! It runs a standard simulation.
//! It then compares with reference data, or with results from Py or GUI runs.

int run(const std::string& test_name, const std::string& sim_name,
        const std::string& sample_builder_name, const double limit) {
    std::cout << "run std test " << test_name << std::endl;
    std::cout << "- create sim " << sim_name << std::endl;
    std::unique_ptr<ISimulation> simulation{SimulationFactory().createItem(sim_name)};
    ASSERT(simulation);

    std::cout << "- sample builder " << sample_builder_name << std::endl;
    std::unique_ptr<ISampleBuilder> builder{SampleBuilderFactory().createItem(sample_builder_name)};
    std::cout << "- builder name " << builder->getName() << std::endl;

    int number_of_failed_tests = 0;
    for (size_t iSample = 0; iSample < builder->size(); ++iSample) {
        std::unique_ptr<MultiLayer> sample(builder->createSampleByIndex(iSample));
        simulation->setSample(*sample);

        std::cout << "- run subtest " << iSample << "/" << builder->size() << ": "
                  << builder->getName() << "\n";

        std::string full_name = test_name;
        if (builder->getName() != "SampleBuilder")
            full_name += "_" + builder->getName();

        simulation->runSimulation();

        if (!checkSimulation(full_name, *simulation, limit))
            ++number_of_failed_tests;
    }

    return !number_of_failed_tests;
}
