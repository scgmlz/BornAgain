#include "Base/Const/Units.h"
#include "Device/Beam/Beam.h"
#include "Device/Detector/SimpleUnitConverters.h"
#include "Device/Detector/SphericalDetector.h"
#include "Tests/GTestWrapper/google_test.h"

class OffSpecularConverterTest : public ::testing::Test {
public:
    OffSpecularConverterTest();

protected:
    SphericalDetector m_detector;
    FixedBinAxis m_alpha_i_axis;
    Beam m_beam;
};

OffSpecularConverterTest::OffSpecularConverterTest()
    : m_detector(100, 0.0, 5.0 * Units::deg, 70, -2.0 * Units::deg, 1.5)
    , m_alpha_i_axis("alpha_i", 51, 0.0, 7.0 * Units::deg)
    , m_beam(1.0, 1.0, {1.0 * Units::deg, 0.0}) {}

TEST_F(OffSpecularConverterTest, OffSpecularConverter) {
    OffSpecularConverter converter(m_detector, m_beam, m_alpha_i_axis);

    EXPECT_EQ(converter.dimension(), 2u);

    EXPECT_DOUBLE_EQ(converter.calculateMin(0, Axes::Units::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, Axes::Units::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, Axes::Units::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, Axes::Units::DEGREES), 0.0);
    EXPECT_THROW(converter.calculateMin(0, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(0, Axes::Units::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(0, Axes::Units::DEFAULT), 7.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, Axes::Units::NBINS), 51.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, Axes::Units::RADIANS), Units::deg2rad(7.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, Axes::Units::DEGREES), 7.0);
    EXPECT_THROW(converter.calculateMax(0, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(0, Axes::Units::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, Axes::Units::DEFAULT), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, Axes::Units::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, Axes::Units::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, Axes::Units::DEGREES), -2.0);
    EXPECT_THROW(converter.calculateMin(1, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(1, Axes::Units::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, Axes::Units::DEFAULT), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, Axes::Units::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, Axes::Units::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, Axes::Units::DEGREES), Units::rad2deg(1.5));
    EXPECT_THROW(converter.calculateMax(1, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(1, Axes::Units::MM), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(2, Axes::Units::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, Axes::Units::DEFAULT), std::runtime_error);

    auto axis = converter.createConvertedAxis(0, Axes::Units::DEFAULT);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), converter.axisSize(0));
    EXPECT_EQ(axis->lowerBound(), converter.calculateMin(0, Axes::Units::DEFAULT));
    EXPECT_EQ(axis->upperBound(), converter.calculateMax(0, Axes::Units::DEFAULT));

    auto axis2 = converter.createConvertedAxis(1, Axes::Units::RADIANS);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis2.get()));
    EXPECT_EQ(axis2->size(), converter.axisSize(1));
    EXPECT_EQ(axis2->lowerBound(), converter.calculateMin(1, Axes::Units::RADIANS));
    EXPECT_EQ(axis2->upperBound(), converter.calculateMax(1, Axes::Units::RADIANS));

    EXPECT_THROW(converter.createConvertedAxis(2, Axes::Units::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(1, Axes::Units::QSPACE), std::runtime_error);
}

TEST_F(OffSpecularConverterTest, OffSpecularConverterClone) {
    OffSpecularConverter converter(m_detector, m_beam, m_alpha_i_axis);
    std::unique_ptr<OffSpecularConverter> P_clone(converter.clone());

    EXPECT_EQ(P_clone->dimension(), 2u);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, Axes::Units::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, Axes::Units::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, Axes::Units::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, Axes::Units::DEGREES), 0.0);
    EXPECT_THROW(P_clone->calculateMin(0, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMin(0, Axes::Units::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, Axes::Units::DEFAULT), 7.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, Axes::Units::NBINS), 51.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, Axes::Units::RADIANS), Units::deg2rad(7.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, Axes::Units::DEGREES), 7.0);
    EXPECT_THROW(P_clone->calculateMax(0, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(0, Axes::Units::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, Axes::Units::DEFAULT), -2.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, Axes::Units::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, Axes::Units::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, Axes::Units::DEGREES), -2.0);
    EXPECT_THROW(P_clone->calculateMin(1, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMin(1, Axes::Units::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, Axes::Units::DEFAULT), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, Axes::Units::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, Axes::Units::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, Axes::Units::DEGREES), Units::rad2deg(1.5));
    EXPECT_THROW(P_clone->calculateMax(1, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(1, Axes::Units::MM), std::runtime_error);

    EXPECT_THROW(P_clone->calculateMin(2, Axes::Units::DEFAULT), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(2, Axes::Units::DEFAULT), std::runtime_error);
}
