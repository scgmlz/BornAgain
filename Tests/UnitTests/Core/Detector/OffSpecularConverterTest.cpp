#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Detector/SphericalDetector.h"
#include "Core/Intensity/SimpleUnitConverters.h"
#include "Core/Vector/Vectors3D.h"
#include "Tests/GTestWrapper/google_test.h"

class OffSpecularConverterTest : public ::testing::Test
{
public:
    OffSpecularConverterTest();

protected:
    SphericalDetector m_detector;
    FixedBinAxis m_alpha_i_axis;
    Beam m_beam;
};

OffSpecularConverterTest::OffSpecularConverterTest()
    : m_detector(100, 0.0, 5.0 * Units::deg, 70, -2.0 * Units::deg, 1.5),
      m_alpha_i_axis("alpha_i", 51, 0.0, 7.0 * Units::deg), m_beam(1.0, 1.0 * Units::deg, 0.0, 1.0)
{
}

TEST_F(OffSpecularConverterTest, OffSpecularConverter)
{
    OffSpecularConverter converter(m_detector, m_beam, m_alpha_i_axis);

    EXPECT_EQ(converter.dimension(), 2u);

    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEFAULT), 7.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::NBINS), 51.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(7.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEGREES), 7.0);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEFAULT), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEFAULT), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);

    auto axis = converter.createConvertedAxis(0, AxesUnits::DEFAULT);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), converter.axisSize(0));
    EXPECT_EQ(axis->getMin(), converter.calculateMin(0, AxesUnits::DEFAULT));
    EXPECT_EQ(axis->getMax(), converter.calculateMax(0, AxesUnits::DEFAULT));

    auto axis2 = converter.createConvertedAxis(1, AxesUnits::RADIANS);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis2.get()));
    EXPECT_EQ(axis2->size(), converter.axisSize(1));
    EXPECT_EQ(axis2->getMin(), converter.calculateMin(1, AxesUnits::RADIANS));
    EXPECT_EQ(axis2->getMax(), converter.calculateMax(1, AxesUnits::RADIANS));

    EXPECT_THROW(converter.createConvertedAxis(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(1, AxesUnits::QSPACE), std::runtime_error);
}

TEST_F(OffSpecularConverterTest, OffSpecularConverterClone)
{
    OffSpecularConverter converter(m_detector, m_beam, m_alpha_i_axis);
    std::unique_ptr<OffSpecularConverter> P_clone(converter.clone());

    EXPECT_EQ(P_clone->dimension(), 2u);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_THROW(P_clone->calculateMin(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMin(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::DEFAULT), 7.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::NBINS), 51.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(7.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::DEGREES), 7.0);
    EXPECT_THROW(P_clone->calculateMax(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::DEFAULT), -2.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_THROW(P_clone->calculateMin(1, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::DEFAULT), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_THROW(P_clone->calculateMax(1, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(P_clone->calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}
