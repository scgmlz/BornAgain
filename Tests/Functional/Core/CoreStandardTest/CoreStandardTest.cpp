// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreStandardTest/CoreStandardTest.cpp
//! @brief     Implements class CoreStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CoreStandardTest.h"
#include "FileSystemUtils.h"
#include "IntensityDataIOFactory.h"
#include "TestUtils.h"
#include "Simulation.h"
#include "BABuild.h"
#include "BATesting.h"

bool CoreStandardTest::runTest()
{
    std::unique_ptr<OutputData<double>> reference;

    // Load reference if available
    try {
        reference.reset(IntensityDataIOFactory::readOutputData(
            FileSystemUtils::jointPath(BATesting::CoreReferenceDir(), getName() + ".int.gz")));
    } catch(const std::exception&) {
        std::cout << "No reference found, but we proceed with the simulation to create a new one\n";
    }

    // Run simulation.
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();
    auto sim_result = m_reference_simulation->result();
    const std::unique_ptr<OutputData<double>> result_data(sim_result.data());

    // Compare with reference if available.
    bool success = false;
    if (reference)
        success = TestUtils::isTheSame(*result_data, *reference, m_threshold) ? true : false;

    // Save simulation if different from reference.
    if (!success) {
        FileSystemUtils::createDirectories(BATesting::CoreOutputDir());
        std::string out_fname = FileSystemUtils::jointPath(BATesting::CoreOutputDir(), getName() + ".int.gz");
        IntensityDataIOFactory::writeOutputData(*result_data, out_fname);
        std::cout << "New simulation result stored in " << out_fname << "\n"
                  << "To visualize an intensity map, use "
                  << BABuild::buildBinDir() << "/plot_intensity_data.py;"
                  << "   to plot a difference image, use "
                  << BABuild::buildBinDir() << "/plot_intensity_data_diff.py\n"
                  << "If the new result is correct, then move it to "
                  << BATesting::CoreReferenceDir() << "/\n";
    }
    return success;
}
