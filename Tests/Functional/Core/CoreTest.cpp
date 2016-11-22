// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreTest.cpp
//! @brief     Implements class CoreTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreTest.h"
#include "FileSystemUtils.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"

CoreTest::CoreTest(
    const std::string& name, const std::string& description, GISASSimulation* simulation,
    double threshold)
    : IReferencedTest(name, description, threshold)
    , m_simulation(simulation)
{}

CoreTest::~CoreTest()
{
    delete m_simulation;
    delete m_reference;
}

bool CoreTest::runTest()
{
    // Load reference if available
    try {
        m_reference = IntensityDataIOFactory::readOutputData(
            FileSystemUtils::jointPath(CORE_STD_REF_DIR, getName() + ".int.gz"));
    } catch(const std::exception& ex) {
        m_reference = nullptr;
        std::cout << "No reference found, but we proceed with the simulation to create a new one\n";
    }

    // Run simulation.
    assert(m_simulation);
    m_simulation->runSimulation();
    const std::unique_ptr<OutputData<double>> result_data(m_simulation->getDetectorIntensity());
    result_data->setVariability(m_threshold);

    // Compare with reference if available.
    bool success = false;
    if (m_reference)
        success = compareIntensityMaps(*result_data.get(), *m_reference);
    // Save simulation if different from reference.
    if (!success) {
        FileSystemUtils::createDirectory(CORE_STD_OUT_DIR);
        std::string out_fname = FileSystemUtils::jointPath(CORE_STD_OUT_DIR, getName() + ".int");
        IntensityDataIOFactory::writeOutputData(*result_data, out_fname);
        std::cout << "New simulation result stored in " << out_fname << ".\n"
                  << "To visualize an intensity map, use " << BUILD_BIN_DIR << "/view1.py;"
                  << "   to plot a difference image, use " << BUILD_BIN_DIR << "/view2.py.\n"
                  << "If the new result is correct, then gzip it and move it to "
                  << CORE_STD_REF_DIR << "/.\n";
    }
    return success;
}
