// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyStandard/PyStandardTest.cpp
//! @brief     Implements class PyExportTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PyStandardTest.h"
#include "BATesting.h"
#include "ExportToPython.h"
#include "FileSystemUtils.h"
#include "IntensityDataIOFactory.h"
#include "Simulation.h"
#include "TestUtils.h"
#include <fstream>
#include <iostream>

//! Runs simulation via a Python script and directly, and returns true if the results agree.
bool PyStandardTest::runTest()
{
    // Set output data filename, and remove old output files
    std::string output_name
        = FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), getName());
    std::string output_path = output_name + ".ref.int.gz";
    std::remove(output_path.c_str());
    std::cout << "Removed old output " << output_path << "\n";

    // Generate Python script
    std::string pyscript_filename
        = FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), getName() + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << ExportToPython::generatePyExportTest(*m_reference_simulation);
    pythonFile.close();

    // Run Python script
    if (!TestUtils::runPython(pyscript_filename + " " + output_path))
        return false;

    // Run direct simulation
    std::cout << "Running simulation and comparing with result from Py script\n";
    m_reference_simulation->runSimulation();
    auto ref_result = m_reference_simulation->result();

    const std::unique_ptr<OutputData<double>> reference_data(ref_result.data());

    // Compare results
    const std::unique_ptr<OutputData<double>> domain_data(
        IntensityDataIOFactory::readOutputData(output_path));

    return TestUtils::isTheSame(*domain_data, *reference_data, m_threshold);
}
