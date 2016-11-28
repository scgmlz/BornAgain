#ifndef RECTANGULARDETECTORTEST_H
#define RECTANGULARDETECTORTEST_H

#include "RectangularDetector.h"
#include "GISASSimulation.h"
#include "SimulationElement.h"
#include "Numeric.h"
#include "Units.h"
#include <memory>
#include <iostream>

class RectangularDetectorTest : public ::testing::Test
{
 protected:
    RectangularDetectorTest(){}
    virtual ~RectangularDetectorTest(){}

    double phi(SimulationElement &element) {return element.getPhiMean()/Units::degree; }
    double alpha(SimulationElement &element) {return element.getAlphaMean()/Units::degree; }
    double phi(kvector_t k) {return k.phi()/Units::degree; }
    double alpha(kvector_t k) {return 90.0 - k.theta()/Units::degree; }

    bool isEqual(const kvector_t lhs, const kvector_t rhs) {
        bool is_equal = Numeric::areAlmostEqual(lhs.x(), rhs.x()) &&
                Numeric::areAlmostEqual(lhs.y(), rhs.y()) &&
                Numeric::areAlmostEqual(lhs.z(), rhs.z());
        if(!is_equal) {
            std::cout << "lhs:" << lhs << " rhs:" << rhs << " diff:" << (lhs-rhs) << std::endl;
        }
        return is_equal;
    }
};

TEST_F(RectangularDetectorTest, InitialState)
{
    RectangularDetector det(50, 10.0, 60, 20.0);
    EXPECT_EQ(size_t(50), det.getNbinsX());
    EXPECT_EQ(10.0, det.getWidth());
    EXPECT_EQ(size_t(60), det.getNbinsY());
    EXPECT_EQ(20.0, det.getHeight());

    EXPECT_EQ(0.0, det.getU0());
    EXPECT_EQ(0.0, det.getV0());
    EXPECT_EQ(0.0, det.getDistance());

    EXPECT_TRUE(kvector_t() == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());

    EXPECT_EQ(RectangularDetector::GENERIC, det.getDetectorArrangment());
}

TEST_F(RectangularDetectorTest, Clone)
{
    RectangularDetector det(50, 10.0, 60, 20.0);
    kvector_t normal(10.0, 20.0, 30.0);
    kvector_t direction(1.0, 2.0, 3.0);
    double u0(88.0), v0(99.0);
    det.setPosition(normal, u0, v0, direction);

    std::unique_ptr<RectangularDetector> clone(det.clone());
    EXPECT_EQ(u0, clone->getU0());
    EXPECT_EQ(v0, clone->getV0());
    EXPECT_TRUE(normal == clone->getNormalVector());
    EXPECT_TRUE(direction == clone->getDirectionVector());
    EXPECT_EQ(RectangularDetector::GENERIC, clone->getDetectorArrangment());
}

TEST_F(RectangularDetectorTest, PerpToSample)
{
    int nbinsx(5), nbinsy(4);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    double dx = width/nbinsx;
    double dy = height/nbinsy;

    RectangularDetector det(nbinsx, width, nbinsy, height);

    // detector perpendicular to sample
    det.setPerpendicularToSampleX(distance, u0, v0);
    EXPECT_EQ(distance, det.getDistance());
    EXPECT_EQ(u0, det.getU0());
    EXPECT_EQ(v0, det.getV0());
    EXPECT_TRUE(kvector_t() == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());
    EXPECT_EQ(RectangularDetector::PERPENDICULAR_TO_SAMPLE, det.getDetectorArrangment());

    // initializing with the simulation
    GISASSimulation simulation;
    simulation.setBeamParameters(1.0, 10.0*Units::degree, 0.0);
    det.init(simulation.getInstrument().getBeam());
    EXPECT_TRUE(kvector_t(distance, 0, 0) == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());

    std::vector<SimulationElement> elements = det.createSimulationElements(simulation.getInstrument().getBeam());
    EXPECT_EQ(elements.size(), size_t(nbinsx*nbinsy));

    // lower left bin
    kvector_t k(distance, u0-dx/2., (-v0+dy/2.));
    SimulationElement element = elements[0];
    EXPECT_DOUBLE_EQ(phi(k), phi(element));
    EXPECT_NEAR(alpha(k), alpha(element), 1e-10*std::abs(alpha(k)));

    // upper left bin
    k = kvector_t(distance, u0-dx/2., (height -  v0 - dy/2.));
    element = elements[3];
    EXPECT_DOUBLE_EQ(phi(k), phi(element));
    EXPECT_NEAR(alpha(k), alpha(element), 1e-10*std::abs(alpha(k)));

    // lower right bin
    k = kvector_t(distance, -(width-u0-dx/2.), (-v0+dy/2.));
    element = elements[16];
    EXPECT_DOUBLE_EQ(phi(k), phi(element));
    EXPECT_NEAR(alpha(k), alpha(element), 1e-10*std::abs(alpha(k)));

    // upper right bin
    k = kvector_t(distance, -(width-u0-dx/2.), (height -  v0 - dy/2.));
    element = elements[19];
    EXPECT_DOUBLE_EQ(phi(k), phi(element));
    EXPECT_NEAR(alpha(k), alpha(element), 1e-10*std::abs(alpha(k)));
}


TEST_F(RectangularDetectorTest, PerpToDirectBeam)
{
    int nbinsx(5), nbinsy(4);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    double dx = width/nbinsx;
    double dy = height/nbinsy;
    double alpha_i(10.0*Units::degree);

    RectangularDetector det(nbinsx, width, nbinsy, height);

    // detector perpendicular to direct beam
    det.setPerpendicularToDirectBeam(distance, u0, v0);
    EXPECT_EQ(distance, det.getDistance());
    EXPECT_EQ(u0, det.getU0());
    EXPECT_EQ(v0, det.getV0());
    EXPECT_TRUE(kvector_t() == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());
    EXPECT_EQ(RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM, det.getDetectorArrangment());

    // initializing with the simulation
    GISASSimulation simulation;
    simulation.setBeamParameters(1.0, alpha_i, 0.0);
    det.init(simulation.getInstrument().getBeam());
    kvector_t normal(distance*cos(alpha_i), 0.0, -1.0*distance*sin(alpha_i));
    EXPECT_TRUE(isEqual(normal, det.getNormalVector()));
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());

    std::vector<SimulationElement> elements = det.createSimulationElements(simulation.getInstrument().getBeam());
    EXPECT_EQ(elements.size(), size_t(nbinsx*nbinsy));

    // lower left bin
    double ds = v0 - dy/2.;
    double alpha_x = alpha_i+std::atan(ds/distance);
    double c = distance*std::sin(alpha_i) + ds*std::cos(alpha_i);
    double x = c/std::tan(alpha_x);
    kvector_t k(x, u0-dx/2., -c);
    SimulationElement element = elements[0];
    EXPECT_DOUBLE_EQ(phi(k), phi(element));
    EXPECT_NEAR(alpha(k), alpha(element), 1e-10*std::abs(alpha(k)));
}


TEST_F(RectangularDetectorTest, PerpToReflectedBeam)
{
    int nbinsx(5), nbinsy(4);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    double dx = width/nbinsx;
    double dy = height/nbinsy;
    double alpha_i(10.0*Units::degree);

    RectangularDetector det(nbinsx, width, nbinsy, height);

    // detector perpendicular to reflected beam
    det.setPerpendicularToReflectedBeam(distance, u0, v0);
    EXPECT_EQ(distance, det.getDistance());
    EXPECT_EQ(u0, det.getU0());
    EXPECT_EQ(v0, det.getV0());
    EXPECT_TRUE(kvector_t() == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());
    EXPECT_EQ(RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM, det.getDetectorArrangment());

    // initializing with the simulation
    GISASSimulation simulation;
    simulation.setBeamParameters(1.0, alpha_i, 0.0);
    det.init(simulation.getInstrument().getBeam());
    kvector_t normal(distance*cos(alpha_i), 0.0, 1.0*distance*sin(alpha_i));
    EXPECT_TRUE(isEqual(normal, det.getNormalVector()));
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());

    // checking detector elements
    std::vector<SimulationElement> elements = det.createSimulationElements(simulation.getInstrument().getBeam());
    EXPECT_EQ(elements.size(), size_t(nbinsx*nbinsy));

    double ds = v0 - dy/2.;
    double alpha_x = alpha_i - std::atan(ds/distance);
    double c = distance*std::sin(alpha_i) - std::cos(alpha_i)*ds;
    double x = c/std::tan(alpha_x);

    kvector_t k(x, u0-dx/2., c);
    SimulationElement element = elements[0];
    EXPECT_DOUBLE_EQ(phi(k), phi(element));
    EXPECT_NEAR(alpha(k), alpha(element), 1e-10*std::abs(alpha(k)));
}

// detector perpendicular to reflected beam, when direct beam position is known
TEST_F(RectangularDetectorTest, PerpToReflectedBeamDpos)
{
    int nbinsx(5), nbinsy(4);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    double dx = width/nbinsx;
    double dy = height/nbinsy;
    double alpha_i(10.0*Units::degree);

    RectangularDetector det(nbinsx, width, nbinsy, height);

    // detector perpendicular to reflected beam
    det.setPerpendicularToReflectedBeam(distance);
    EXPECT_EQ(distance, det.getDistance());
    EXPECT_EQ(0.0, det.getU0());
    EXPECT_EQ(0.0, det.getV0());
    EXPECT_EQ(0.0, det.getDirectBeamU0());
    EXPECT_EQ(0.0, det.getDirectBeamV0());

    double dbeam_u0 = u0;
    double dbeam_v0 = -distance*std::tan(alpha_i*2.0) + v0;
    det.setDirectBeamPosition(dbeam_u0, dbeam_v0);

    EXPECT_EQ(dbeam_u0, det.getDirectBeamU0());
    EXPECT_EQ(dbeam_v0, det.getDirectBeamV0());
    EXPECT_TRUE(kvector_t() == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());
    EXPECT_EQ(RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS, det.getDetectorArrangment());

    // initializing with the simulation
    GISASSimulation simulation;
    simulation.setBeamParameters(1.0, alpha_i, 0.0);
    det.init(simulation.getInstrument().getBeam());

    kvector_t normal(distance*cos(alpha_i), 0.0, 1.0*distance*sin(alpha_i));
    EXPECT_TRUE(isEqual(normal, det.getNormalVector()));
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());
    EXPECT_EQ(u0, det.getU0());
    EXPECT_EQ(v0, det.getV0());

    // checking detector elements
    std::vector<SimulationElement> elements = det.createSimulationElements(simulation.getInstrument().getBeam());
    EXPECT_EQ(elements.size(), size_t(nbinsx*nbinsy));

    double ds = v0 - dy/2.;
    double alpha_x = alpha_i - std::atan(ds/distance);
    double c = distance*std::sin(alpha_i) - std::cos(alpha_i)*ds;
    double x = c/std::tan(alpha_x);

    kvector_t k(x, u0-dx/2., c);
    SimulationElement element = elements[0];
    EXPECT_DOUBLE_EQ(phi(k), phi(element));
    EXPECT_NEAR(alpha(k), alpha(element), 1e-10*std::abs(alpha(k)));
}


#endif // RECTANGULARDETECTORTEST_H
