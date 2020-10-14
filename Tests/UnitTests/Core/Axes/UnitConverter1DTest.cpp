#include "Core/Unit/UnitConverter1D.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Base/Axis/VariableBinAxis.h"
#include "Base/Const/MathConstants.h"
#include "Base/Const/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Data/OutputData.h"
#include "Core/Scan/QSpecScan.h"
#include "Tests/GTestWrapper/google_test.h"

class UnitConverter1DTest : public ::testing::Test
{
public:
    UnitConverter1DTest();

    double getQ(double angle) { return 4.0 * M_PI * std::sin(angle) / m_beam.getWavelength(); }

protected:
    void checkConventionalConverter(const UnitConverter1D& test_object);
    void checkQSpecConverter(const UnitConverter1D& test_object);
    FixedBinAxis m_axis;
    FixedBinAxis m_q_axis;
    QSpecScan m_qscan;
    Beam m_beam;
};

UnitConverter1DTest::UnitConverter1DTest()
    : m_axis("Angles", 5, 0.5, 1.0) // angles in radians
      ,
      m_q_axis("Q values", 5, 0.0, 1.0) // q axis in inv. nm
      ,
      m_qscan(m_q_axis), m_beam(Beam::horizontalBeam())
{
}

void UnitConverter1DTest::checkConventionalConverter(const UnitConverter1D& test_object)
{
    double expected_min = m_axis.getBinCenter(0);
    EXPECT_NEAR(test_object.calculateMin(0, Axes::Units::DEFAULT), Units::rad2deg(expected_min),
                Units::rad2deg(expected_min) * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, Axes::Units::NBINS), 0.0, 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, Axes::Units::RADIANS), expected_min,
                expected_min * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, Axes::Units::DEGREES), Units::rad2deg(expected_min),
                Units::rad2deg(expected_min) * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, Axes::Units::QSPACE), getQ(expected_min),
                getQ(expected_min) * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, Axes::Units::RQ4), getQ(expected_min),
                getQ(expected_min) * 1e-10);

    double expected_max = m_axis.getBinCenters().back();
    EXPECT_NEAR(test_object.calculateMax(0, Axes::Units::DEFAULT), Units::rad2deg(expected_max),
                Units::rad2deg(expected_max) * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, Axes::Units::NBINS), static_cast<double>(m_axis.size()),
                1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, Axes::Units::RADIANS), expected_max,
                expected_max * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, Axes::Units::DEGREES), Units::rad2deg(expected_max),
                Units::rad2deg(expected_max) * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, Axes::Units::QSPACE), getQ(expected_max),
                getQ(expected_max) * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, Axes::Units::RQ4), getQ(expected_max),
                getQ(expected_max) * 1e-10);

    // DEFAULT
    auto axis_default = test_object.createConvertedAxis(0, Axes::Units::DEFAULT);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis_default.get()));
    EXPECT_EQ(axis_default->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_default->getMin(), test_object.calculateMin(0, Axes::Units::DEFAULT));
    EXPECT_EQ(axis_default->getMax(), test_object.calculateMax(0, Axes::Units::DEFAULT));

    // QSPACE
    auto axis_qspace = test_object.createConvertedAxis(0, Axes::Units::QSPACE);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis_qspace.get()));
    EXPECT_EQ(axis_qspace->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_qspace->getMin(), test_object.calculateMin(0, Axes::Units::QSPACE));
    EXPECT_EQ(axis_qspace->getMax(), test_object.calculateMax(0, Axes::Units::QSPACE));

    // NBINS
    auto axis_nbins = test_object.createConvertedAxis(0, Axes::Units::NBINS);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis_nbins.get()));
    EXPECT_EQ(axis_nbins->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_nbins->getMin(), test_object.calculateMin(0, Axes::Units::NBINS));
    EXPECT_EQ(axis_nbins->getMax(), test_object.calculateMax(0, Axes::Units::NBINS));

    // RQ4
    auto axis_rq4 = test_object.createConvertedAxis(0, Axes::Units::RQ4);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis_rq4.get()));
    EXPECT_EQ(axis_rq4->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_rq4->getMin(), test_object.calculateMin(0, Axes::Units::RQ4));
    EXPECT_EQ(axis_rq4->getMax(), test_object.calculateMax(0, Axes::Units::RQ4));
    EXPECT_TRUE(*axis_rq4 == *axis_qspace);

    OutputData<double> fake_data;
    fake_data.addAxis(m_axis);
    std::vector<double> raw_fake(m_axis.size(), 1.0);
    fake_data.setRawDataVector(raw_fake);

    // NBINS
    auto data_nbins = test_object.createConvertedData(fake_data, Axes::Units::NBINS);
    EXPECT_EQ(data_nbins->getAxis(0), *axis_nbins);
    EXPECT_EQ(data_nbins->getAllocatedSize(), axis_nbins->size());
    EXPECT_EQ(raw_fake, data_nbins->getRawDataVector());

    // RQ4
    auto data_rq4 = test_object.createConvertedData(fake_data, Axes::Units::RQ4);
    EXPECT_EQ(data_rq4->getAxis(0), *axis_rq4);
    auto raw_data_rq4 = data_rq4->getRawDataVector();
    EXPECT_EQ(raw_data_rq4.size(), raw_fake.size());
    EXPECT_EQ(raw_data_rq4.size(), axis_rq4->size());
    for (size_t i = 0, size = raw_data_rq4.size(); i < size; ++i) {
        double value = raw_fake[i] * std::pow(axis_rq4->getBinCenter(i), 4);
        EXPECT_DOUBLE_EQ(raw_data_rq4[i], value);
    }
}

void UnitConverter1DTest::checkQSpecConverter(const UnitConverter1D& test_object)
{
    double expected_min = m_q_axis.getBinCenter(0);
    EXPECT_EQ(test_object.calculateMin(0, Axes::Units::DEFAULT), expected_min);
    EXPECT_NEAR(test_object.calculateMin(0, Axes::Units::NBINS), 0.0, 1e-10);
    EXPECT_EQ(test_object.calculateMin(0, Axes::Units::QSPACE), expected_min);
    EXPECT_EQ(test_object.calculateMin(0, Axes::Units::RQ4), expected_min);

    double expected_max = m_q_axis.getBinCenters().back();
    EXPECT_EQ(test_object.calculateMax(0, Axes::Units::DEFAULT), expected_max);
    EXPECT_NEAR(test_object.calculateMax(0, Axes::Units::NBINS),
                static_cast<double>(m_q_axis.size()), 1e-10);
    EXPECT_EQ(test_object.calculateMax(0, Axes::Units::QSPACE), expected_max);
    EXPECT_EQ(test_object.calculateMax(0, Axes::Units::RQ4), expected_max);

    // DEFAULT
    auto axis_default = test_object.createConvertedAxis(0, Axes::Units::DEFAULT);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis_default.get()));
    EXPECT_EQ(axis_default->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_default->getMin(), test_object.calculateMin(0, Axes::Units::DEFAULT));
    EXPECT_EQ(axis_default->getMax(), test_object.calculateMax(0, Axes::Units::DEFAULT));

    // QSPACE
    auto axis_qspace = test_object.createConvertedAxis(0, Axes::Units::QSPACE);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis_qspace.get()));
    EXPECT_EQ(axis_qspace->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_qspace->getMin(), test_object.calculateMin(0, Axes::Units::QSPACE));
    EXPECT_EQ(axis_qspace->getMax(), test_object.calculateMax(0, Axes::Units::QSPACE));
    EXPECT_EQ(*axis_default, *axis_qspace);

    // NBINS
    auto axis_nbins = test_object.createConvertedAxis(0, Axes::Units::NBINS);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis_nbins.get()));
    EXPECT_EQ(axis_nbins->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_nbins->getMin(), test_object.calculateMin(0, Axes::Units::NBINS));
    EXPECT_EQ(axis_nbins->getMax(), test_object.calculateMax(0, Axes::Units::NBINS));

    // RQ4
    auto axis_rq4 = test_object.createConvertedAxis(0, Axes::Units::RQ4);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis_rq4.get()));
    EXPECT_EQ(axis_rq4->size(), test_object.axisSize(0));
    EXPECT_EQ(axis_rq4->getMin(), test_object.calculateMin(0, Axes::Units::RQ4));
    EXPECT_EQ(axis_rq4->getMax(), test_object.calculateMax(0, Axes::Units::RQ4));
    EXPECT_TRUE(*axis_rq4 == *axis_qspace);

    OutputData<double> fake_data;
    fake_data.addAxis(m_axis);
    std::vector<double> raw_fake(m_axis.size(), 1.0);
    fake_data.setRawDataVector(raw_fake);

    // NBINS
    auto data_nbins = test_object.createConvertedData(fake_data, Axes::Units::NBINS);
    EXPECT_EQ(data_nbins->getAxis(0), *axis_nbins);
    EXPECT_EQ(data_nbins->getAllocatedSize(), axis_nbins->size());
    EXPECT_EQ(raw_fake, data_nbins->getRawDataVector());

    // RQ4
    auto data_rq4 = test_object.createConvertedData(fake_data, Axes::Units::RQ4);
    EXPECT_EQ(data_rq4->getAxis(0), *axis_rq4);
    auto raw_data_rq4 = data_rq4->getRawDataVector();
    EXPECT_EQ(raw_data_rq4.size(), raw_fake.size());
    EXPECT_EQ(raw_data_rq4.size(), axis_rq4->size());
    for (size_t i = 0, size = raw_data_rq4.size(); i < size; ++i) {
        double value = raw_fake[i] * std::pow(axis_rq4->getBinCenter(i), 4);
        EXPECT_DOUBLE_EQ(raw_data_rq4[i], value);
    }
}

TEST_F(UnitConverter1DTest, MainFunctionality)
{
    checkConventionalConverter(UnitConverterConvSpec(m_beam, m_axis));
    checkQSpecConverter(UnitConverterQSpec(m_qscan));
}

TEST_F(UnitConverter1DTest, Exceptions)
{
    UnitConverterConvSpec converter(m_beam, m_axis);

    EXPECT_THROW(converter.calculateMin(0, Axes::Units::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(1, Axes::Units::RADIANS), std::runtime_error);

    EXPECT_THROW(converter.calculateMax(0, Axes::Units::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(1, Axes::Units::RADIANS), std::runtime_error);

    EXPECT_THROW(converter.createConvertedAxis(0, Axes::Units::MM), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(1, Axes::Units::DEFAULT), std::runtime_error);

    FixedBinAxis axis("Angles", 100, 0.0, 2.0 * M_PI);
    EXPECT_THROW(UnitConverterConvSpec converter2(m_beam, axis), std::runtime_error);

    UnitConverterQSpec converter2(m_qscan);
    // wrong units
    EXPECT_THROW(converter2.calculateMin(0, Axes::Units::MM), std::runtime_error);
    EXPECT_THROW(converter2.calculateMin(0, Axes::Units::RADIANS), std::runtime_error);
    EXPECT_THROW(converter2.calculateMin(0, Axes::Units::DEGREES), std::runtime_error);
    EXPECT_THROW(converter2.calculateMax(0, Axes::Units::MM), std::runtime_error);
    EXPECT_THROW(converter2.calculateMax(0, Axes::Units::RADIANS), std::runtime_error);
    EXPECT_THROW(converter2.calculateMax(0, Axes::Units::DEGREES), std::runtime_error);
    EXPECT_THROW(converter2.createConvertedAxis(0, Axes::Units::MM), std::runtime_error);

    // wrong axis index
    EXPECT_THROW(converter2.calculateMin(1, Axes::Units::QSPACE), std::runtime_error);
    EXPECT_THROW(converter2.calculateMax(1, Axes::Units::RQ4), std::runtime_error);
    EXPECT_THROW(converter2.createConvertedAxis(1, Axes::Units::DEFAULT), std::runtime_error);
}

TEST_F(UnitConverter1DTest, Clone)
{
    UnitConverterConvSpec converter(m_beam, m_axis);
    std::unique_ptr<UnitConverter1D> converter_clone(converter.clone());
    checkConventionalConverter(*converter_clone);

    UnitConverterQSpec converterQ(m_qscan);
    std::unique_ptr<UnitConverter1D> converterQ_clone(converterQ.clone());
    checkQSpecConverter(*converterQ_clone);
}

TEST_F(UnitConverter1DTest, NonDefaultUnitsInInput)
{
    PointwiseAxis axis("x", std::vector<double>{0.0, 0.5, 1.0});

    EXPECT_THROW(UnitConverterConvSpec(m_beam, axis, Axes::Units::NBINS), std::runtime_error);

    UnitConverterConvSpec converter(m_beam, axis, Axes::Units::DEGREES);
    auto axis_deg_output = converter.createConvertedAxis(0, Axes::Units::DEGREES);
    EXPECT_TRUE(axis.size() == axis_deg_output->size());
    EXPECT_DOUBLE_EQ(axis[0], (*axis_deg_output)[0]);
    EXPECT_DOUBLE_EQ(axis[1], (*axis_deg_output)[1]);
    EXPECT_DOUBLE_EQ(axis[2], (*axis_deg_output)[2]);

    auto values = axis.getBinCenters();
    std::for_each(values.begin(), values.end(), [this](double& value) { value = getQ(value); });
    PointwiseAxis q_axis("q", values);
    UnitConverterConvSpec converter2(m_beam, q_axis, Axes::Units::QSPACE);
    auto axis_rad_output = converter2.createConvertedAxis(0, Axes::Units::RADIANS);
    EXPECT_TRUE(axis.size() == axis_rad_output->size());
    EXPECT_DOUBLE_EQ(axis[0], (*axis_rad_output)[0]);
    EXPECT_DOUBLE_EQ(axis[1], (*axis_rad_output)[1]);
    EXPECT_DOUBLE_EQ(axis[2], (*axis_rad_output)[2]);

    EXPECT_THROW(UnitConverterConvSpec(m_beam, q_axis, Axes::Units::RQ4), std::runtime_error);
}
