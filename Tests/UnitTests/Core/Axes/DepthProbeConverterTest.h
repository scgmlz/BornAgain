#include "google_test.h"
#include "Beam.h"
#include "FixedBinAxis.h"
#include "MathConstants.h"
#include "SimpleUnitConverters.h"
#include "Units.h"

class DepthProbeConverterTest : public ::testing::Test
{
public:
    DepthProbeConverterTest();
    ~DepthProbeConverterTest();

protected:
    void checkMainFunctionality(const DepthProbeConverter& test_object);
    void checkAlphaAxis(AxesUnits units, const DepthProbeConverter& test_object);
    void checkZAxis(AxesUnits units, const DepthProbeConverter& test_object);
    const double m_alpha_start = 0.5; // first axis value in rads
    const double m_alpha_end = 1.0; // last axis value in rads
    const double m_z_start = -30.0;
    const double m_z_end = 10.0;
    const size_t m_nbins = 100;
    Beam m_beam;
    FixedBinAxis m_inclination_axis;
    FixedBinAxis m_z_axis;
};

DepthProbeConverterTest::DepthProbeConverterTest()
    : m_inclination_axis("Angles", m_nbins, m_alpha_start, m_alpha_end) // angles in radians
    , m_z_axis("Positions", m_nbins, m_z_start, m_z_end) // z positions in nm
{
    m_beam.setCentralK(1.0, 0.0, 0.0); // wavelength = 1.0 nm
}

DepthProbeConverterTest::~DepthProbeConverterTest() = default;

void DepthProbeConverterTest::checkMainFunctionality(const DepthProbeConverter& test_object)
{
    EXPECT_EQ(test_object.dimension(), 2u);

    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::DEFAULT), Units::rad2deg(m_alpha_start),
                Units::rad2deg(m_alpha_start) * 1e-10);

    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::DEFAULT), Units::rad2deg(m_alpha_end),
                Units::rad2deg(m_alpha_end) * 1e-10);

    checkAlphaAxis(AxesUnits::DEFAULT, test_object);
    checkZAxis(AxesUnits::DEFAULT, test_object);
}

void DepthProbeConverterTest::checkAlphaAxis(AxesUnits units,
                                             const DepthProbeConverter& test_object)
{
    auto axis = test_object.createConvertedAxis(0, units);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), test_object.axisSize(0));
    EXPECT_EQ(axis->size(), m_nbins);
    EXPECT_EQ(axis->getName(), test_object.axisName(0, units));
    EXPECT_EQ(axis->getMin(), test_object.calculateMin(0, units));
    EXPECT_EQ(axis->getMax(), test_object.calculateMax(0, units));
}

void DepthProbeConverterTest::checkZAxis(AxesUnits units, const DepthProbeConverter& test_object)
{
    auto axis = test_object.createConvertedAxis(1, units);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), test_object.axisSize(1));
    EXPECT_EQ(axis->size(), m_nbins);
    EXPECT_EQ(axis->getName(), test_object.axisName(1, units));
    EXPECT_EQ(axis->getMin(), test_object.calculateMin(1, units));
    EXPECT_NEAR(axis->getMin(), m_z_start, std::abs(m_z_start) * 1e-10);
    EXPECT_EQ(axis->getMax(), test_object.calculateMax(1, units));
    EXPECT_NEAR(axis->getMax(), m_z_end, std::abs(m_z_end) * 1e-10);
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
    EXPECT_THROW(converter.axisName(0, AxesUnits::DEGREES), std::runtime_error);
    EXPECT_THROW(converter.axisName(0, AxesUnits::RADIANS), std::runtime_error);
    EXPECT_THROW(converter.axisName(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.axisName(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.axisName(2, AxesUnits::DEFAULT), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::DEGREES), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::RADIANS), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);

    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::DEGREES), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::RADIANS), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, AxesUnits::RADIANS), std::runtime_error);

    EXPECT_THROW(converter.createConvertedAxis(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(0, AxesUnits::DEGREES), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(0, AxesUnits::RADIANS), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(0, AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(2, AxesUnits::DEFAULT), std::runtime_error);
}

TEST_F(DepthProbeConverterTest, DepthProbeConverterClone)
{
    DepthProbeConverter converter(m_beam, m_inclination_axis, m_z_axis);
    std::unique_ptr<DepthProbeConverter> converter_clone(converter.clone());
    checkMainFunctionality(*converter_clone);
}
