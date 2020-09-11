// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/Std/Check.cpp
//! @brief     Implements function checkSimulation for Python standard test
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
#include "Core/Export/ExportToPython.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Tools/FileSystemUtils.h"
#include <fstream>
#include <iostream>

std::unique_ptr<OutputData<double>> domainData(const std::string& test_name,
                                               const Simulation& direct_simulation)
{
    const std::string output_name =
        FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), test_name);
    const std::string output_path = output_name + ".ref.int.gz";
    std::remove(output_path.c_str());
    std::cout << "- removed old output " << output_path << "\n";

    // Generate Python script
    const std::string pyscript_filename =
        FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), test_name + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << ExportToPython::generatePyExportTest(direct_simulation);
    pythonFile.close();

    // Run Python script
    const std::string py_command = pyscript_filename + " " + output_path;
#ifndef _WIN32
    const std::string sys_command = std::string("PYTHONPATH=") + BABuild::buildLibDir() + " "
                                    + std::string("NOPLOT=TRUE") + " " + BABuild::pythonExecutable()
                                    + " -B " + py_command;
#else
    const std::string sys_command = std::string("set PYTHONPATH=") + BABuild::buildLibDir() + " & "
                                    + std::string("set NOPLOT=TRUE") + " & \""
                                    + BABuild::pythonExecutable() + "\" -B " + py_command;
#endif
    std::cout << "- system call: " << sys_command << std::endl; // note: endl = \n + flush
    int ret = std::system(sys_command.c_str());
    if (ret != 0) {
        std::stringstream msg;
        msg << "System call returned non-zero value " << ret;
        throw std::runtime_error(msg.str());
    }

    return std::unique_ptr<OutputData<double>>(IntensityDataIOFactory::readOutputData(output_path));
}

bool checkSimulation(const std::string& name, const Simulation& direct_simulation,
                     const double limit)
{
    const std::unique_ptr<OutputData<double>> domain_data = domainData(name, direct_simulation);

    const std::unique_ptr<OutputData<double>> ref_data = direct_simulation.result().data();

    return IntensityDataFunctions::checkRelativeDifference(*domain_data, *ref_data, limit);
}
