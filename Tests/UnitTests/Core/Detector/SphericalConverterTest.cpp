#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Detector/SphericalDetector.h"
#include "Core/Intensity/SimpleUnitConverters.h"
#include "Core/Vector/Vectors3D.h"
#include "Tests/GTestWrapper/google_test.h"

class SphericalConverterTest : public ::testing::Test
{
public:
    SphericalConverterTest();

protected:
    SphericalDetector m_detector;
    Beam m_beam;
    double m_kiz, m_kfy, m_kfz1, m_kfz2;
};

SphericalConverterTest::SphericalConverterTest()
    : m_detector(100, 0.0, 5.0 * Units::deg, 70, -2.0 * Units::deg, 1.5),
      m_beam(1.0, 1.0 * Units::deg, 0.0, 1.0)
{
    const auto k_i = m_beam.getCentralK();
    m_kiz = k_i.z();
    const double K = 2.0 * M_PI / m_beam.getWavelength();
    m_kfy = K * std::sin(5.0 * Units::deg);
    m_kfz1 = K * std::sin(-2.0 * Units::deg);
    m_kfz2 = K * std::sin(1.5);
}

TEST_F(SphericalConverterTest, SphericalConverter)
{
    SphericalConverter converter(m_detector, m_beam);

    EXPECT_EQ(converter.dimension(), 2u);

    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::QSPACE), 0.0);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEFAULT), 5.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::NBINS), 100.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEGREES), 5.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::QSPACE), m_kfy);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEFAULT), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::QSPACE), m_kfz1 - m_kiz);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEFAULT), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::QSPACE), m_kfz2 - m_kiz);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);

    auto axis = converter.createConvertedAxis(0, AxesUnits::DEFAULT);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), converter.axisSize(0));
    EXPECT_EQ(axis->getMin(), converter.calculateMin(0, AxesUnits::DEFAULT));
    EXPECT_EQ(axis->getMax(), converter.calculateMax(0, AxesUnits::DEFAULT));

    auto axis2 = converter.createConvertedAxis(1, AxesUnits::QSPACE);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis2.get()));
    EXPECT_EQ(axis2->size(), converter.axisSize(1));
    EXPECT_EQ(axis2->getMin(), converter.calculateMin(1, AxesUnits::QSPACE));
    EXPECT_EQ(axis2->getMax(), converter.calculateMax(1, AxesUnits::QSPACE));

    EXPECT_THROW(converter.createConvertedAxis(2, AxesUnits::DEFAULT), std::runtime_error);
}

TEST_F(SphericalConverterTest, SphericalConverterClone)
{
    SphericalConverter converter(m_detector, m_beam);
    std::unique_ptr<SphericalConverter> P_clone(converter.clone());

    EXPECT_EQ(P_clone->dimension(), 2u);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::QSPACE), 0.0);
    EXPECT_THROW(P_clone->calculateMin(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::DEFAULT), 5.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::NBINS), 100.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::DEGREES), 5.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::QSPACE), m_kfy);
    EXPECT_THROW(P_clone->calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::DEFAULT), -2.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::QSPACE), m_kfz1 - m_kiz);
    EXPECT_THROW(P_clone->calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::DEFAULT), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::QSPACE), m_kfz2 - m_kiz);
    EXPECT_THROW(P_clone->calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(P_clone->calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}
