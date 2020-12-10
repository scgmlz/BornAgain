//  ************************************************************************************************
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
//  ************************************************************************************************

#include "BABuild.h"
#include "BATesting.h"
#include "Base/Utils/FileSystemUtils.h"
#include "Core/Export/ExportToPython.h"
#include "Core/Simulation/ISimulation.h"
#include "Device/Data/DataUtils.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include <fstream>
#include <iostream>

namespace {

std::unique_ptr<OutputData<double>> domainData(const std::string& test_name,
                                               const ISimulation& direct_simulation) {
    const std::string output_name =
        FileSystemUtils::jointPath(BATesting::TestOutDir_PyStd(), test_name);
    const std::string output_path = output_name + ".ref.int.gz";
    std::remove(output_path.c_str());
    std::cout << "- removed old output " << output_path << std::endl;

    // Generate Python script
    const std::string pyscript_filename =
        FileSystemUtils::jointPath(BATesting::TestOutDir_PyStd(), test_name + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << ExportToPython::generateSimulationCode(direct_simulation);
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
    std::cout << "- system call: " << sys_command << std::endl;
    int ret = std::system(sys_command.c_str());
    if (ret != 0) {
        std::stringstream msg;
        msg << "System call returned non-zero value " << ret;
        throw std::runtime_error(msg.str());
    }

    return std::unique_ptr<OutputData<double>>(IntensityDataIOFactory::readOutputData(output_path));
}

} // namespace

//! Run simulation directly (in C+ core) and through Python export, and compare results.

bool checkSimulation(const std::string& name, const ISimulation& direct_simulation,
                     const double limit) {
    const std::unique_ptr<OutputData<double>> domain_data = domainData(name, direct_simulation);

    const std::unique_ptr<OutputData<double>> ref_data = direct_simulation.result().data();

    return DataUtils::checkRelativeDifference(*domain_data, *ref_data, limit);
}
