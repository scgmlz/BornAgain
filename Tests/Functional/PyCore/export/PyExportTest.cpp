// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/export/PyExportTest.cpp
//! @brief     Implements class PyExportTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyExportTest.h"
#include "FileSystemUtils.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include <cassert>
#include <cstdio>
#include <fstream>

PyExportTest::PyExportTest(
    const std::string& name, const std::string& description,
    GISASSimulation* reference_simulation, double threshold)
    : IReferencedTest(name, description, threshold)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(nullptr)
{
}

PyExportTest::~PyExportTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

//! Runs simulation via a Python script and directly, and returns true if the results agree.
bool PyExportTest::runTest()
{
    // Set output data filename, and remove old output files
    std::string output_name = FileSystemUtils::jointPath(PYEXPORT_TMP_DIR, getName());
    std::string output_path = output_name + ".ref.int";
    std::remove( output_path.c_str() );
    std::cout << "Removed old output " << output_path << "n";

    // Generate Python script
    std::string pyscript_filename = FileSystemUtils::jointPath(PYEXPORT_TMP_DIR, getName() + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << PythonFormatting::simulationToPython(m_reference_simulation);
    pythonFile.close();

    // Run Python script
    assert(std::string(BUILD_LIB_DIR)!="");
    if (!runPython(pyscript_filename + " " + output_name))
        return false;

    // Run direct simulation
    std::cout <<
        "Now going to directly run the simulation, and to compare with result from Py script\n";
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());

    // Compare results
    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(output_path));
    return compareIntensityMaps(*P_domain_data, *P_reference_data);
}
