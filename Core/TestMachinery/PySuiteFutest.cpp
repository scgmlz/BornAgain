// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/PySuiteFutest.cpp
//! @brief     Implements class PySuiteFutest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <memory>
#include <fstream>
#include <cstdio>
#include <cassert>

#include "SimulationFactory.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataFunctions.h"
#include "PyGenTools.h"
#include "BAPython.h"
#include "FileSystem.h"
#include "Utils.h"
#include "PySuiteFutest.h"

namespace {
const std::string directory_name_for_failed_tests = "00_failed_tests";
}

PySuiteFutest::PySuiteFutest(
    const std::string& name, const std::string& description,
    GISASSimulation* reference_simulation, double threshold)
    : IFutest(name, description)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(0)
    , m_threshold(threshold)
    , m_difference(0)
    , m_pyscript_filename( "pyscript_" + name + ".py" )
    , m_output_filename( "pyscript_" + name + "_out" )
{
}

PySuiteFutest::~PySuiteFutest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void PySuiteFutest::runTest()
{
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();

    // Generate contents of Python script
    std::ostringstream ostr;
    ostr << "# Functional test settings, generated by PySuiteFutest::runTest():\n"
         << "import sys, os\n"
         << "sys.path.append(os.path.abspath(os.path.join(os.path.split(\n"
         << "    os.path.realpath(__file__))[0],'..', '..', '..', '..', 'lib')))\n\n"
         << "# Simulation script, generated by PyGenTools::genPyScript(..):\n"
         << PyGenTools::genPyScript(m_reference_simulation, m_output_filename);

    // Create and run Python script
    std::ofstream pythonFile(m_pyscript_filename);
    pythonFile << ostr.str();
    pythonFile.close();

    std::string command = std::string(BORNAGAIN_PYTHON_EXE) + " " + m_pyscript_filename;
    std::cout << "Core simulation will be compared with " << m_output_filename <<
        " generated by command '" << command << "'\n";
    int script_result = std::system(command.c_str()); // run python script
    (void)script_result; // ignore return value
}

int PySuiteFutest::analyseResults()
{
    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(m_output_filename+".int"));
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = m_difference > m_threshold ? FAILED_DIFF : SUCCESS;
    if (m_result != SUCCESS) {
        // Move failed Python script to failed tests directory
        Utils::FileSystem::CreateDirectory(directory_name_for_failed_tests);
        std::rename( m_pyscript_filename.c_str(), getPySuiteFileNameAndPath().c_str());
    }
    return m_result;
}

void PySuiteFutest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
    if (m_result != SUCCESS)
        ostr << "--> " << getPySuiteFileNameAndPath();
}

std::string PySuiteFutest::getPySuiteFileNameAndPath() const
{
    std::string result
        = Utils::FileSystem::GetJoinPath(directory_name_for_failed_tests, m_pyscript_filename);
    return result;
}
