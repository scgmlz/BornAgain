#include "Core/Detector/RectangularDetector.h"
#include "Core/Basics/Units.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Fit/TestEngine/Numeric.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>
#include <memory>

class RectangularDetectorTest : public ::testing::Test
{
protected:
    //    double phi(DetectorElement& element, double wavelength);
    //    double alpha(DetectorElement& element, double wavelength);
    double phi(kvector_t k) { return k.phi() / Units::degree; }
    double alpha(kvector_t k) { return 90.0 - k.theta() / Units::degree; }

    bool isEqual(const kvector_t lhs, const kvector_t rhs)
    {
        bool is_equal = Numeric::AreAlmostEqual(lhs.x(), rhs.x())
                        && Numeric::AreAlmostEqual(lhs.y(), rhs.y())
                        && Numeric::AreAlmostEqual(lhs.z(), rhs.z());
        if (!is_equal) {
            std::cout << "lhs:" << lhs << " rhs:" << rhs << " diff:" << (lhs - rhs) << std::endl;
        }
        return is_equal;
    }
};

TEST_F(RectangularDetectorTest, InitialState)
{
    RectangularDetector det(50u, 10.0, 60u, 20.0);
    EXPECT_EQ(50u, det.getNbinsX());
    EXPECT_EQ(10.0, det.getWidth());
    EXPECT_EQ(60u, det.getNbinsY());
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
    RectangularDetector det(50u, 10.0, 60u, 20.0);
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
    size_t nbinsx(5u), nbinsy(4u);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    //    double dx = width / nbinsx;
    //    double dy = height / nbinsy;

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
    simulation.setBeamParameters(1.0, 10.0 * Units::degree, 0.0);
    det.init(simulation.getInstrument().getBeam());
    EXPECT_TRUE(kvector_t(distance, 0, 0) == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());

    // FIXME cleanup, replace with DetectorContext tests
    //    std::vector<DetectorElement> elements
    //        = det.createDetectorElements(simulation.getInstrument().getBeam());
    //    EXPECT_EQ(elements.size(), nbinsx * nbinsy);

    //    double wavelength = 1.0;
    //    // lower left bin
    //    kvector_t k(distance, u0 - dx / 2., (-v0 + dy / 2.));
    //    EXPECT_DOUBLE_EQ(phi(k), phi(elements[0], wavelength));
    //    EXPECT_NEAR(alpha(k), alpha(elements[0], wavelength), 1e-10 * std::abs(alpha(k)));

    //    // upper left bin
    //    k = kvector_t(distance, u0 - dx / 2., (height - v0 - dy / 2.));
    //    EXPECT_DOUBLE_EQ(phi(k), phi(elements[3], wavelength));
    //    EXPECT_NEAR(alpha(k), alpha(elements[3], wavelength), 1e-10 * std::abs(alpha(k)));

    //    // lower right bin
    //    k = kvector_t(distance, -(width - u0 - dx / 2.), (-v0 + dy / 2.));
    //    EXPECT_DOUBLE_EQ(phi(k), phi(elements[16], wavelength));
    //    EXPECT_NEAR(alpha(k), alpha(elements[16], wavelength), 1e-10 * std::abs(alpha(k)));

    //    // upper right bin
    //    k = kvector_t(distance, -(width - u0 - dx / 2.), (height - v0 - dy / 2.));
    //    EXPECT_DOUBLE_EQ(phi(k), phi(elements[19], wavelength));
    //    EXPECT_NEAR(alpha(k), alpha(elements[19], wavelength), 1e-10 * std::abs(alpha(k)));
}

TEST_F(RectangularDetectorTest, PerpToDirectBeam)
{
    size_t nbinsx(5u), nbinsy(4u);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    //    double dx = width / nbinsx;
    //    double dy = height / nbinsy;
    double alpha_i(10.0 * Units::degree);

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
    kvector_t normal(distance * cos(alpha_i), 0.0, -1.0 * distance * sin(alpha_i));
    EXPECT_TRUE(isEqual(normal, det.getNormalVector()));
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());

    //    std::vector<DetectorElement> elements
    //        = det.createDetectorElements(simulation.getInstrument().getBeam());
    //    EXPECT_EQ(elements.size(), nbinsx * nbinsy);

    //    // lower left bin
    //    double wavelength = 1.0;
    //    double ds = v0 - dy / 2.;
    //    double alpha_x = alpha_i + std::atan(ds / distance);
    //    double c = distance * std::sin(alpha_i) + ds * std::cos(alpha_i);
    //    double x = c / std::tan(alpha_x);
    //    kvector_t k(x, u0 - dx / 2., -c);
    //    EXPECT_DOUBLE_EQ(phi(k), phi(elements[0], wavelength));
    //    EXPECT_NEAR(alpha(k), alpha(elements[0], wavelength), 1e-10 * std::abs(alpha(k)));
}

TEST_F(RectangularDetectorTest, PerpToReflectedBeam)
{
    size_t nbinsx(5u), nbinsy(4u);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    //    double dx = width / nbinsx;
    //    double dy = height / nbinsy;
    double alpha_i(10.0 * Units::degree);

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
    kvector_t normal(distance * cos(alpha_i), 0.0, 1.0 * distance * sin(alpha_i));
    EXPECT_TRUE(isEqual(normal, det.getNormalVector()));
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());

    //    // checking detector elements
    //    std::vector<DetectorElement> elements
    //        = det.createDetectorElements(simulation.getInstrument().getBeam());
    //    EXPECT_EQ(elements.size(), nbinsx * nbinsy);

    //    double ds = v0 - dy / 2.;
    //    double alpha_x = alpha_i - std::atan(ds / distance);
    //    double c = distance * std::sin(alpha_i) - std::cos(alpha_i) * ds;
    //    double x = c / std::tan(alpha_x);
    //    double wavelength = 1.0;

    //    kvector_t k(x, u0 - dx / 2., c);
    //    EXPECT_DOUBLE_EQ(phi(k), phi(elements[0], wavelength));
    //    EXPECT_NEAR(alpha(k), alpha(elements[0], wavelength), 1e-10 * std::abs(alpha(k)));
}

// detector perpendicular to reflected beam, when direct beam position is known
TEST_F(RectangularDetectorTest, PerpToReflectedBeamDpos)
{
    size_t nbinsx(5u), nbinsy(4u);
    double width(50.0), height(40.0);
    double distance(100.0), u0(20.0), v0(10.0);
    //    double dx = width / nbinsx;
    //    double dy = height / nbinsy;
    double alpha_i(10.0 * Units::degree);

    RectangularDetector det(nbinsx, width, nbinsy, height);

    // detector perpendicular to reflected beam
    det.setPerpendicularToReflectedBeam(distance);
    EXPECT_EQ(distance, det.getDistance());
    EXPECT_EQ(0.0, det.getU0());
    EXPECT_EQ(0.0, det.getV0());
    EXPECT_EQ(0.0, det.getDirectBeamU0());
    EXPECT_EQ(0.0, det.getDirectBeamV0());

    double dbeam_u0 = u0;
    double dbeam_v0 = -distance * std::tan(alpha_i * 2.0) + v0;
    det.setDirectBeamPosition(dbeam_u0, dbeam_v0);

    EXPECT_EQ(dbeam_u0, det.getDirectBeamU0());
    EXPECT_EQ(dbeam_v0, det.getDirectBeamV0());
    EXPECT_TRUE(kvector_t() == det.getNormalVector());
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());
    EXPECT_EQ(RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS,
              det.getDetectorArrangment());

    // initializing with the simulation
    GISASSimulation simulation;
    simulation.setBeamParameters(1.0, alpha_i, 0.0);
    det.init(simulation.getInstrument().getBeam());

    kvector_t normal(distance * cos(alpha_i), 0.0, 1.0 * distance * sin(alpha_i));
    EXPECT_TRUE(isEqual(normal, det.getNormalVector()));
    EXPECT_TRUE(kvector_t(0.0, -1.0, 0.0) == det.getDirectionVector());
    EXPECT_EQ(u0, det.getU0());
    EXPECT_EQ(v0, det.getV0());

    //    // checking detector elements
    //    std::vector<DetectorElement> elements
    //        = det.createDetectorElements(simulation.getInstrument().getBeam());
    //    EXPECT_EQ(elements.size(), nbinsx * nbinsy);

    //    double ds = v0 - dy / 2.;
    //    double alpha_x = alpha_i - std::atan(ds / distance);
    //    double c = distance * std::sin(alpha_i) - std::cos(alpha_i) * ds;
    //    double x = c / std::tan(alpha_x);
    //    double wavelength = 1.0;

    //    kvector_t k(x, u0 - dx / 2., c);
    //    EXPECT_DOUBLE_EQ(phi(k), phi(elements[0], wavelength));
    //    EXPECT_NEAR(alpha(k), alpha(elements[0], wavelength), 1e-10 * std::abs(alpha(k)));
}

// Test retrieval of analyzer properties
TEST_F(RectangularDetectorTest, AnalyzerProperties)
{
    RectangularDetector detector(50u, 10.0, 60u, 20.0);

    kvector_t direction;
    double efficiency = 0.0;
    double total_transmission = 1.0;
    kvector_t unit_direction;

    // if direction is the zero vector, an exception is thrown
    EXPECT_THROW(detector.setAnalyzerProperties(direction, efficiency, total_transmission),
                 Exceptions::ClassInitializationException);

    // zero efficiency
    direction = kvector_t(1.0, 0.0, 0.0);
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties = detector.detectionProperties();

    EXPECT_NEAR(detect_properties.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties.analyzerTotalTransmission(), total_transmission, 1e-8);
    // direction vector returned is zero vector because efficiency is zero
    EXPECT_NEAR(detect_properties.analyzerDirection().x(), 0.0, 1e-8);
    EXPECT_NEAR(detect_properties.analyzerDirection().y(), 0.0, 1e-8);
    EXPECT_NEAR(detect_properties.analyzerDirection().z(), 0.0, 1e-8);

    // intermediate efficiency
    direction = kvector_t(1.0, 0.0, 0.0);
    efficiency = 0.5;
    total_transmission = 0.6;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties2 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties2.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerDirection().z(), unit_direction.z(), 1e-8);

    // maximum efficiency
    direction = kvector_t(1.0, 0.0, 0.0);
    efficiency = 1.0;
    total_transmission = 0.5;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties3 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties3.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerDirection().z(), unit_direction.z(), 1e-8);

    // non-axis direction
    direction = kvector_t(1.0, 2.0, 3.0);
    efficiency = 1.0;
    total_transmission = 0.5;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties4 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties4.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerDirection().z(), unit_direction.z(), 1e-8);

    // maximum efficiency and negative efficiency
    direction = kvector_t(0.0, -1.0, -1.0);
    efficiency = -1.0;
    total_transmission = 0.5;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties5 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties5.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerDirection().z(), unit_direction.z(), 1e-8);
}

// double RectangularDetectorTest::phi(DetectorElement& element, double wavelength)
//{
//    auto pixel = element.pixel();
//    auto k_f = pixel->getK(0.5, 0.5, wavelength);
//    return k_f.phi() / Units::degree;
//}

// double RectangularDetectorTest::alpha(DetectorElement& element, double wavelength)
//{
//    auto pixel = element.pixel();
//    auto k_f = pixel->getK(0.5, 0.5, wavelength);
//    return ( M_PI_2 - k_f.theta() ) / Units::degree;
//}
