// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/export/PyStandardTest.cpp
//! @brief     Implements class PyExportTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyStandardTest.h"
#include "FileSystemUtils.h"
#include "GISASSimulation.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "TestUtils.h"
#include <fstream>
#include <iostream>

PyStandardTest::PyStandardTest(const std::string& name, const std::string& description,
                               const Simulation& simulation, double threshold)
    : IStandardTest(name, description, threshold)
{
    if (const auto gisas = dynamic_cast<const GISASSimulation*>(&simulation))
        m_reference_simulation.reset(gisas->clone());
    else
        throw std::runtime_error("Error in PyStandardTest: wrong simulation type.");
}

//! Runs simulation via a Python script and directly, and returns true if the results agree.
bool PyStandardTest::runTest()
{
    // Set output data filename, and remove old output files
    std::string output_name = FileSystemUtils::jointPath(PYEXPORT_TMP_DIR, getName());
    std::string output_path = output_name + ".ref.int.gz";
    std::remove( output_path.c_str() );
    std::cout << "Removed old output " << output_path << "n";

    // Generate Python script
    std::string pyscript_filename = FileSystemUtils::jointPath(PYEXPORT_TMP_DIR, getName() + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << PythonFormatting::generatePyExportTest(*m_reference_simulation);
    pythonFile.close();

    // Run Python script
    if (!TestUtils::runPython(pyscript_filename + " " + output_path))
        return false;

    // Run direct simulation
    std::cout << "Running simulation and comparing with result from Py script\n";
    m_reference_simulation->runSimulation();

    const std::unique_ptr<OutputData<double> > reference_data(
        m_reference_simulation->getDetectorIntensity());

    // Compare results
    const std::unique_ptr<OutputData<double> > domain_data(
        IntensityDataIOFactory::readOutputData(output_path));

    return TestUtils::isTheSame(*domain_data, *reference_data, m_threshold);
}
