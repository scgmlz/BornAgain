// ************************************************************************** //
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

bool checkSimulation(const std::string& name, const Simulation& direct_simulation,
                     const double limit)
{
    const auto result_data = direct_simulation.result().data();

    std::unique_ptr<OutputData<double>> reference;

    // Load reference if available
    ASSERT(name != "");
    try {
        reference.reset(IntensityDataIOFactory::readOutputData(
            FileSystemUtils::jointPath(BATesting::StdReferenceDir(), name + ".int.gz")));
    } catch (const std::exception&) {
        std::cout << "No reference found, but we proceed with the simulation to create a new one\n";
    }

    // Compare with reference if available.
    bool success = false;
    if (reference) {
        std::cout << "- check diff" << std::endl;
        success = IntensityDataFunctions::checkRelativeDifference(*reference, *result_data, limit);
    }

    // Save simulation if different from reference.
    if (!success) {
        std::cout << "- failure ..." << std::endl;
        FileSystemUtils::createDirectories(BATesting::StdOutputDir());
        std::string out_fname =
            FileSystemUtils::jointPath(BATesting::StdOutputDir(), name + ".int.gz");
        IntensityDataIOFactory::writeOutputData(*result_data, out_fname);
        std::cout << "New simulation result stored in " << out_fname << "\n"
                  << "To visualize an intensity map, use " << BABuild::buildBinDir()
                  << "/plot_intensity_data.py;"
                  << "   to plot a difference image, use " << BABuild::buildBinDir()
                  << "/plot_intensity_data_diff.py\n"
                  << "If the new result is correct, then move it to "
                  << BATesting::CoreReferenceDir() << "/\n";
    }

    return success;
}
