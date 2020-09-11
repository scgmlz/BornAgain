#include "Core/Beam/FootprintGauss.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/PointwiseAxis.h"
#include "Core/Detector/ScanResolution.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Instrument/QSpecScan.h"
#include "Core/Multilayer/SpecularSimulationElement.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Tests/GTestWrapper/google_test.h"

class SpecularScanTest : public ::testing::Test
{
};

TEST_F(SpecularScanTest, AngularScanInit)
{
    auto check = [](const AngularSpecScan& scan, const IAxis& axis) {
        EXPECT_EQ(scan.wavelength(), 0.1);
        EXPECT_EQ(axis, *scan.coordinateAxis());
        EXPECT_EQ(scan.numberOfSimulationElements(), axis.size());
        EXPECT_EQ(scan.dataType(), ISpecularScan::angle);
        EXPECT_EQ(scan.footprintFactor(), nullptr);
        EXPECT_EQ(scan.footprint(0, 1), std::vector<double>{1.0});
        EXPECT_THROW(scan.footprint(1, axis.size()), std::runtime_error);
        EXPECT_NO_THROW(scan.footprint(0, axis.size()));
    };

    const PointwiseAxis pointwise_axis("inc_angles", std::vector<double>{0.1, 0.2, 0.3});
    AngularSpecScan scan(0.1, pointwise_axis);
    check(scan, pointwise_axis);

    AngularSpecScan scan2(0.1, std::vector<double>{0.1, 0.2, 0.3});
    check(scan, pointwise_axis);

    const FixedBinAxis fixed_axis("inc_angles", 3, 0.1, 0.3);
    AngularSpecScan scan3(0.1, fixed_axis);
    check(scan3, fixed_axis);

    AngularSpecScan scan4(0.1, 3, 0.1, 0.3);
    check(scan4, fixed_axis);
}

TEST_F(SpecularScanTest, AngularScanWithFootprint)
{
    AngularSpecScan scan(0.1, std::vector<double>{0.1, 0.2, 0.3});
    EXPECT_EQ(scan.footprintFactor(), nullptr);

    const IFootprintFactor& f_factor = FootprintGauss(0.1);
    scan.setFootprintFactor(&f_factor);

    EXPECT_EQ(scan.footprint(0, 1), std::vector<double>{f_factor.calculate(0.1)});
    EXPECT_NE(scan.footprintFactor(), &f_factor);

    scan.setFootprintFactor(nullptr);
    EXPECT_EQ(scan.footprintFactor(), nullptr);
    EXPECT_EQ(scan.footprint(0, 1), std::vector<double>{1.0});

    AngularSpecScan scan2(0.1, std::vector<double>{-0.1, 0.2, 0.3});
    scan2.setFootprintFactor(&f_factor);
    EXPECT_EQ(scan.footprint(0, 1), std::vector<double>{1.0});
}

TEST_F(SpecularScanTest, FootprintAndWavelengthResolution)
{
    AngularSpecScan scan(0.1, std::vector<double>{0.1, 0.2, 0.3});
    auto scan_res = std::unique_ptr<ScanResolution>(
        ScanResolution::scanRelativeResolution(RangedDistributionGate(3, 2.0), 0.1));
    scan.setWavelengthResolution(*scan_res);

    const IFootprintFactor& f_factor = FootprintGauss(0.1);
    scan.setFootprintFactor(&f_factor);

    std::vector<double> expected{
        f_factor.calculate(0.1), f_factor.calculate(0.1), f_factor.calculate(0.1),
        f_factor.calculate(0.2), f_factor.calculate(0.2), f_factor.calculate(0.2),
        f_factor.calculate(0.3), f_factor.calculate(0.3), f_factor.calculate(0.3)};
    std::vector<double> actual = scan.footprint(0, 9);

    EXPECT_EQ(expected.size(), actual.size());
    for (size_t i = 0; i < expected.size(); ++i)
        EXPECT_DOUBLE_EQ(expected[i], actual[i]);

    auto expected_part = std::vector<double>(expected.begin() + 1, expected.begin() + 8);
    actual = scan.footprint(1, 7);

    EXPECT_EQ(expected_part.size(), actual.size());
    for (size_t i = 0; i < expected_part.size(); ++i)
        EXPECT_DOUBLE_EQ(expected_part[i], actual[i]);
}

TEST_F(SpecularScanTest, FootprintAndAllResolutions)
{
    AngularSpecScan scan(0.1, std::vector<double>{0.1, 0.2, 0.3});
    auto wl_res = std::unique_ptr<ScanResolution>(
        ScanResolution::scanRelativeResolution(RangedDistributionGate(2, 2.0), 0.1));
    scan.setWavelengthResolution(*wl_res);
    auto inc_res = std::unique_ptr<ScanResolution>(
        ScanResolution::scanRelativeResolution(RangedDistributionGate(2, 2.0), 0.1));
    scan.setAngleResolution(*inc_res);

    const IFootprintFactor& f_factor = FootprintGauss(0.1);
    scan.setFootprintFactor(&f_factor);

    auto samples = inc_res->generateSamples(std::vector<double>{0.1, 0.2, 0.3});
    std::vector<double> expected{
        f_factor.calculate(samples[0][0].value), f_factor.calculate(samples[0][0].value),
        f_factor.calculate(samples[0][1].value), f_factor.calculate(samples[0][1].value),
        f_factor.calculate(samples[1][0].value), f_factor.calculate(samples[1][0].value),
        f_factor.calculate(samples[1][1].value), f_factor.calculate(samples[1][1].value),
        f_factor.calculate(samples[2][0].value), f_factor.calculate(samples[2][0].value),
        f_factor.calculate(samples[2][1].value), f_factor.calculate(samples[2][1].value)};
    std::vector<double> actual = scan.footprint(0, 12);

    EXPECT_EQ(expected.size(), actual.size());
    for (size_t i = 0; i < expected.size(); ++i)
        EXPECT_DOUBLE_EQ(expected[i], actual[i]);

    auto expected_part = std::vector<double>(expected.begin() + 1, expected.begin() + 8);
    actual = scan.footprint(1, 7);

    EXPECT_EQ(expected_part.size(), actual.size());
    for (size_t i = 0; i < expected_part.size(); ++i)
        EXPECT_DOUBLE_EQ(expected_part[i], actual[i]);
}

TEST_F(SpecularScanTest, QScanInit)
{
    auto check = [](const QSpecScan& scan, const IAxis& axis) {
        EXPECT_EQ(axis, *scan.coordinateAxis());
        EXPECT_EQ(scan.numberOfSimulationElements(), axis.size());
        EXPECT_EQ(scan.dataType(), ISpecularScan::q);
        EXPECT_EQ(scan.footprintFactor(), nullptr);
        EXPECT_EQ(scan.footprint(0, 1), std::vector<double>{1.0});
        EXPECT_THROW(scan.footprint(1, axis.size()), std::runtime_error);
        EXPECT_NO_THROW(scan.footprint(0, axis.size()));
    };

    const PointwiseAxis pointwise_axis("qs", std::vector<double>{0.1, 0.2, 0.3});
    QSpecScan scan(pointwise_axis);
    check(scan, pointwise_axis);

    QSpecScan scan2(std::vector<double>{0.1, 0.2, 0.3});
    check(scan, pointwise_axis);

    const FixedBinAxis fixed_axis("qs", 3, 0.1, 0.3);
    QSpecScan scan3(fixed_axis);
    check(scan3, fixed_axis);

    QSpecScan scan4(3, 0.1, 0.3);
    check(scan4, fixed_axis);
}

TEST_F(SpecularScanTest, AngularScanClone)
{
    AngularSpecScan scan(0.1, std::vector<double>{0.1, 0.2, 0.3});

    std::unique_ptr<AngularSpecScan> scan_clone(scan.clone());
    EXPECT_EQ(*scan_clone->coordinateAxis(), *scan.coordinateAxis());
    EXPECT_NE(scan_clone->coordinateAxis(), scan.coordinateAxis());
    EXPECT_EQ(scan_clone->dataType(), scan.dataType());
    EXPECT_EQ(scan_clone->wavelength(), scan.wavelength());
    EXPECT_EQ(scan_clone->footprintFactor(), nullptr);

    const IFootprintFactor& f_factor = FootprintGauss(0.1);
    scan.setFootprintFactor(&f_factor);

    std::unique_ptr<AngularSpecScan> scan_clone2(scan.clone());
    EXPECT_EQ(*scan_clone2->coordinateAxis(), *scan.coordinateAxis());
    EXPECT_EQ(scan_clone2->dataType(), scan.dataType());
    EXPECT_EQ(scan_clone2->wavelength(), scan.wavelength());

    EXPECT_EQ(scan_clone2->footprintFactor()->widthRatio(), f_factor.widthRatio());
    EXPECT_NE(scan_clone2->footprintFactor(), scan.footprintFactor());
    EXPECT_NE(scan_clone2->footprintFactor(), &f_factor);
    EXPECT_NE(dynamic_cast<const FootprintGauss*>(scan_clone2->footprintFactor()), nullptr);
}

TEST_F(SpecularScanTest, QScanClone)
{
    QSpecScan scan(std::vector<double>{0.1, 0.2, 0.3});

    std::unique_ptr<QSpecScan> scan_clone(scan.clone());
    EXPECT_EQ(*scan_clone->coordinateAxis(), *scan.coordinateAxis());
    EXPECT_NE(scan_clone->coordinateAxis(), scan.coordinateAxis());
    EXPECT_EQ(scan_clone->dataType(), scan.dataType());
    EXPECT_EQ(scan_clone->footprintFactor(), nullptr);
}

TEST_F(SpecularScanTest, GenerateSimElements)
{
    AngularSpecScan scan(0.1, std::vector<double>{0.0, 0.2, 0.3});
    std::vector<SpecularSimulationElement> sim_elements = scan.generateSimulationElements();
    EXPECT_EQ(sim_elements.size(), scan.numberOfSimulationElements());
    EXPECT_EQ(scan.numberOfSimulationElements(), 3u);
    for (size_t i = 0; i < sim_elements.size(); ++i)
        EXPECT_TRUE(sim_elements[i].isCalculated());

    QSpecScan scan2(std::vector<double>{0.0, 0.2, 0.3});
    std::vector<SpecularSimulationElement> sim_elements2 = scan.generateSimulationElements();
    EXPECT_EQ(sim_elements2.size(), scan2.numberOfSimulationElements());
    EXPECT_EQ(scan2.numberOfSimulationElements(), 3u);
    for (size_t i = 0; i < sim_elements2.size(); ++i)
        EXPECT_TRUE(sim_elements2[i].isCalculated());
}

TEST_F(SpecularScanTest, ErrorInput)
{
    EXPECT_THROW(AngularSpecScan(-0.1, std::vector<double>{0.0, 0.2, 0.3}), std::runtime_error);
    EXPECT_THROW(AngularSpecScan(0.1, std::vector<double>{0.1, 0.3, 0.2}), std::runtime_error);
    EXPECT_THROW(QSpecScan(std::vector<double>{-0.01, 0.2, 0.3}), std::runtime_error);
    EXPECT_THROW(QSpecScan(std::vector<double>{0.1, 0.3, 0.2}), std::runtime_error);
}
