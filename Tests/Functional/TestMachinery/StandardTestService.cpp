// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardTestService.h
//! @brief     Defines class StandardTestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardTestService.h"
#include "StandardTestCatalogue.h"
#include "IMultiLayerBuilder.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "SimulationFactory.h"
#include "MultiLayer.h"
#include "IFunctionalTest.h"
#include "TestUtils.h"
#include "BornAgainNamespace.h"
#include <iostream>

namespace {

//! Returns test full name, composed from the test name and the name of sample builder.

std::string fullTestName(const std::string& test_name, const std::string& builder_name)
{
    std::string result = test_name;

    if (builder_name != BornAgain::SampleBuilderType)
        result += "_" + builder_name;

    return result;
}

}

//! Runs test corresponding to given command line parameters, returns true if success.

bool StandardTestServiceBase::execute(int argc, char** argv)
{
    StandardTestInfo info = TestUtils::testInfo(argc, argv);
    if (info.m_test_name.empty())
        return false;

    std::unique_ptr<IMultiLayerBuilder> builder(
                SampleBuilderFactory().createItem(info.m_sample_builder_name) );

    size_t n_subtests = builder->size();
    int number_of_failed_tests = 0;

    for(size_t sample_index=0; sample_index<builder->size(); ++sample_index) {
        std::unique_ptr<Simulation> simulation(
                    SimulationFactory().createItem(info.m_simulation_name));

        std::unique_ptr<MultiLayer> sample(builder->createSample(sample_index));
        simulation->setSample(*sample);

        std::string test_name = fullTestName(info.m_test_name, builder->getName());

        std::unique_ptr<IFunctionalTest> test(createTest(test_name, info.m_test_description,
                                           *simulation, info.m_threshold));

        if(n_subtests)
            std::cout << "IStandardTest::execute() -> " << test_name << " " << sample_index+1
                      << "/" << n_subtests << " (" << builder->getName() << ")\n";

        if(!test->execute())
            ++number_of_failed_tests;

    }

    if(number_of_failed_tests)
        std::cout << "summary: " << number_of_failed_tests << " of "
                  << n_subtests << " subtests failed\n";

    return number_of_failed_tests==0;
}
