// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/MesoCrystalPerformanceTest.cpp
//! @brief     Implements MesoCrystalPerformanceTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MesoCrystalPerformanceTest.h"
#include "GISASSimulation.h"
#include "MesoCrystalPerformanceBuilder.h"
#include "FlatDetector.h"
#include "Units.h"
#include <iostream>

namespace {

const double m_distance(909.99);
const double m_pixel_size = 4 * 41.74e-3;
const int m_nx = 1024;
const int m_ny = 1024;
const double m_center_x = 108.2;
const double m_center_y = 942.0;

std::unique_ptr<FlatDetector> create_detector()
{
    double width = m_nx*m_pixel_size;
    double height = m_ny*m_pixel_size;
    double u0 = m_center_x*m_pixel_size;
    double v0 = (m_ny - m_center_y)*m_pixel_size;
    std::unique_ptr<FlatDetector> result = std::make_unique<FlatDetector>(m_nx, width, m_ny, height);
    result->setPerpendicularToDirectBeam(m_distance, u0, v0);
    return result;
}
}

bool MesoCrystalPerformanceTest::runTest()
{
    GISASSimulation simulation;

    simulation.setTerminalProgressMonitor();

    auto detector = create_detector();

    simulation.setDetector(*detector.get());

    simulation.setBeamParameters(1.77*Units::angstrom, 0.4*Units::deg, 0.0);
    simulation.setBeamIntensity(6.1e+12);

    std::shared_ptr<IMultiLayerBuilder> builder(new MesoCrystalPerformanceBuilder);
    simulation.setSampleBuilder(builder);

    simulation.setRegionOfInterest(40.0, 40.0, 41.0, 41.0);

    std::cout << "MesoCrystalPerformanceTest::runTest() -> Starting simulation\n";
    simulation.runSimulation();

    return true;
}
