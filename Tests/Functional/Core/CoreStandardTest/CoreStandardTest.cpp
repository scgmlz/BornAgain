// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreStandardTest.cpp
//! @brief     Implements class CoreStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreStandardTest.h"
#include "FileSystemUtils.h"
#include "GISASSimulation.h"
#include "IntensityDataIOFactory.h"
#include "TestUtils.h"
#include "BABuild.h"

CoreStandardTest::CoreStandardTest(const std::string& name, const std::string& description,
                 const Simulation& simulation, double threshold)
    : IStandardTest(name, description, threshold)
    , m_reference_simulation(simulation.clone())
{}

bool CoreStandardTest::runTest()
{
    std::unique_ptr<OutputData<double>> reference;

    // Load reference if available
    try {
        reference.reset(IntensityDataIOFactory::readOutputData(
            FileSystemUtils::jointPath(CORE_STD_REF_DIR, getName() + ".int.gz")));
    } catch(const std::exception&) {
        std::cout << "No reference found, but we proceed with the simulation to create a new one\n";
    }

    // Run simulation.
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double>> result_data(m_reference_simulation->getDetectorIntensity());

    // Compare with reference if available.
    bool success = false;
    if (reference)
        success = TestUtils::isTheSame(*result_data, *reference, m_threshold) ? true : false;

    // Save simulation if different from reference.
    if (!success) {
        FileSystemUtils::createDirectory(CORE_STD_OUT_DIR);
        std::string out_fname = FileSystemUtils::jointPath(CORE_STD_OUT_DIR, getName() + ".int");
        IntensityDataIOFactory::writeOutputData(*result_data, out_fname);
        std::cout << "New simulation result stored in " << out_fname << ".\n"
                  << "To visualize an intensity map, use "
                  << BABuild::buildBinDir() << "/plot_intensity_data.py;"
                  << "   to plot a difference image, use "
                  << BABuild::buildBinDir() << "/plot_intensity_data_diff.py.\n"
                  << "If the new result is correct, then gzip it and move it to "
                  << CORE_STD_REF_DIR << "/.\n";
    }
    return success;
}
