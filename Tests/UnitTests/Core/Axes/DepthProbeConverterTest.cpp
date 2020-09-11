#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Intensity/SimpleUnitConverters.h"
#include "Tests/GTestWrapper/google_test.h"

class DepthProbeConverterTest : public ::testing::Test
{
protected:
    DepthProbeConverterTest();

    void checkMainFunctionality(const DepthProbeConverter& test_object);
    void checkAlphaAxis(AxesUnits units, const DepthProbeConverter& test_object);
    void checkZAxis(AxesUnits units, const DepthProbeConverter& test_object);
    const double m_alpha_start = 0.5; // first axis value in rads
    const double m_alpha_end = 1.0;   // last axis value in rads
    const double m_z_start = -30.0;
    const double m_z_end = 10.0;
    const size_t m_nbins = 100;
    FixedBinAxis m_inclination_axis;
    FixedBinAxis m_z_axis;
    Beam m_beam;
};

DepthProbeConverterTest::DepthProbeConverterTest()
    : m_inclination_axis("Angles", m_nbins, m_alpha_start, m_alpha_end) // angles in radians
      ,
      m_z_axis("Positions", m_nbins, m_z_start, m_z_end) // z positions in nm
      ,
      m_beam(Beam::horizontalBeam())
{
}

void DepthProbeConverterTest::checkMainFunctionality(const DepthProbeConverter& test_object)
{
    EXPECT_EQ(test_object.dimension(), 2u);

    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::DEFAULT), 2.8647889757e+1,
                2.8647889757e+1 * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::DEGREES), 2.8647889757e+1,
                2.8647889757e+1 * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::QSPACE), 6.0246390001, 6.0246390001 * 1e-10);
    EXPECT_EQ(test_object.calculateMin(0, AxesUnits::RADIANS), m_alpha_start);
    EXPECT_EQ(test_object.calculateMin(0, AxesUnits::NBINS), 0.0);

    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::DEFAULT), 5.7295779513e+1,
                5.7295779513e+1 * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::DEGREES), 5.7295779513e+1,
                5.7295779513e+1 * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::QSPACE), 1.0574236256e+1,
                1.0574236256e+1 * 1e-10);
    EXPECT_EQ(test_object.calculateMax(0, AxesUnits::RADIANS), m_alpha_end);
    const double n_bins = static_cast<double>(m_nbins);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::NBINS), n_bins, n_bins * 1e-10);

    checkAlphaAxis(AxesUnits::DEFAULT, test_object);
    checkAlphaAxis(AxesUnits::DEGREES, test_object);
    checkAlphaAxis(AxesUnits::RADIANS, test_object);
    checkAlphaAxis(AxesUnits::QSPACE, test_object);
    checkAlphaAxis(AxesUnits::NBINS, test_object);

    checkZAxis(AxesUnits::DEFAULT, test_object);
    checkZAxis(AxesUnits::DEGREES, test_object);
    checkZAxis(AxesUnits::RADIANS, test_object);
    checkZAxis(AxesUnits::QSPACE, test_object);
    checkZAxis(AxesUnits::NBINS, test_object);
}

void DepthProbeConverterTest::checkAlphaAxis(AxesUnits units,
                                             const DepthProbeConverter& test_object)
{
    auto axis = test_object.createConvertedAxis(0, units);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), test_object.axisSize(0));
    EXPECT_EQ(axis->size(), m_nbins);
    EXPECT_EQ(axis->getMin(), test_object.calculateMin(0, units));
    EXPECT_EQ(axis->getMax(), test_object.calculateMax(0, units));
}

void DepthProbeConverterTest::checkZAxis(AxesUnits units, const DepthProbeConverter& test_object)
{
    auto axis = test_object.createConvertedAxis(1, units);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), test_object.axisSize(1));
    EXPECT_EQ(axis->size(), m_nbins);

    EXPECT_EQ(axis->getMin(), test_object.calculateMin(1, units));
    const double test_min = units == AxesUnits::NBINS ? 0 : m_z_start;
    EXPECT_NEAR(axis->getMin(), test_min, std::abs(test_min) * 1e-10);

    EXPECT_EQ(axis->getMax(), test_object.calculateMax(1, units));
    const double test_max = units == AxesUnits::NBINS ? m_nbins : m_z_end;
    EXPECT_NEAR(axis->getMax(), test_max, std::abs(test_max) * 1e-10);
}

TEST_F(DepthProbeConverterTest, DepthProbeConverter)
{
    DepthProbeConverter converter(m_beam, m_inclination_axis, m_z_axis);
    checkMainFunctionality(converter);
}

TEST_F(DepthProbeConverterTest, DepthProbeConverterExceptions)
{
    DepthProbeConverter converter(m_beam, m_inclination_axis, m_z_axis);

    EXPECT_THROW(converter.axisName(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.axisName(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.axisName(2, AxesUnits::DEFAULT), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);

    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, AxesUnits::RADIANS), std::runtime_error);

    EXPECT_THROW(converter.createConvertedAxis(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(2, AxesUnits::DEFAULT), std::runtime_error);
}

TEST_F(DepthProbeConverterTest, DepthProbeConverterClone)
{
    DepthProbeConverter converter(m_beam, m_inclination_axis, m_z_axis);
    std::unique_ptr<DepthProbeConverter> converter_clone(converter.clone());
    checkMainFunctionality(*converter_clone);
}
