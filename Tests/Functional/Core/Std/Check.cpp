//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Std/Check.cpp
//! @brief     Implements function checkSimulation for core standard test
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "BABuild.h"
#include "BATesting.h"
#include "Base/Utils/FileSystemUtils.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Device/Data/DataUtils.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/StandardSamples/SampleBuilderFactory.h"
#include <iostream>

//! Run simulation directly (in C+ core), and compare result with reference data.

bool checkSimulation(const std::string& name, const ISimulation& direct_simulation,
                     const double limit) {

    // Run simulation directly.
    const auto result_data = direct_simulation.result().data();

    std::unique_ptr<OutputData<double>> reference;

    // Load reference if available.
    ASSERT(name != "");
    try {
        const std::string refPath =
            FileSystemUtils::jointPath(BATesting::ReferenceDir_Std(), name + ".int.gz");
        std::cout << "- reference: " << refPath << "\n";
        reference.reset(IntensityDataIOFactory::readOutputData(refPath));
    } catch (const std::exception&) {
        std::cerr << "FAILED: cannot read reference\n";
    }

    // Compare with reference if available.
    if (reference) {
        std::cout << "- check diff" << std::endl;
        if (DataUtils::checkRelativeDifference(*reference, *result_data, limit)) {
            std::cout << "- success" << std::endl;
            return true; // regular exit
        }
    } else {
        std::cerr << "FAILED: reference not found\n";
    }

    // Save simulation, as it differs from reference.
    FileSystemUtils::createDirectories(BATesting::TestOutDir_Std());
    std::string out_fname =
        FileSystemUtils::jointPath(BATesting::TestOutDir_Std(), name + ".int.gz");
    IntensityDataIOFactory::writeOutputData(*result_data, out_fname);
    std::cout << "Notes:\n- to visualize an intensity map, use " << BABuild::buildBinDir()
              << "/plot_int.py\n"
              << "- to plot a difference image, use " << BABuild::buildBinDir()
              << "/plot_diff_int.py\n"
              << "- if the new simulation result\n"
              << out_fname << "\n"
              << "  is correct, then move it to the reference directory\n"
              << BATesting::ReferenceDir_Std() << "/\n\n";

    return false;
}
