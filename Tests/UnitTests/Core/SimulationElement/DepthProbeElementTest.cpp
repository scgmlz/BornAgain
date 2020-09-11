#include "Core/SimulationElement/DepthProbeElement.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Tests/GTestWrapper/google_test.h"

class DepthProbeElementTest : public ::testing::Test
{
protected:
    DepthProbeElementTest();
    DepthProbeElement createDefaultElement();

    void compareEqualElements(const DepthProbeElement& lhs, const DepthProbeElement& rhs);

    std::unique_ptr<FixedBinAxis> m_z_positions;
};

DepthProbeElementTest::DepthProbeElementTest() : m_z_positions(new FixedBinAxis("z", 10, 0.0, 10.0))
{
}

DepthProbeElement DepthProbeElementTest::createDefaultElement()
{
    const double wavelength = 1.0;
    const double angle = 2.0;
    return DepthProbeElement(wavelength, angle, m_z_positions.get());
}

void DepthProbeElementTest::compareEqualElements(const DepthProbeElement& lhs,
                                                 const DepthProbeElement& rhs)
{
    EXPECT_EQ(lhs.getWavelength(), rhs.getWavelength());
    EXPECT_EQ(lhs.getAlphaI(), rhs.getAlphaI());
    bool intensity_comparison_result = (lhs.getIntensities() == rhs.getIntensities()).min();
    EXPECT_TRUE(intensity_comparison_result);
    EXPECT_EQ(lhs.getKi(), rhs.getKi());
    EXPECT_EQ(lhs.isCalculated(), rhs.isCalculated());
}

TEST_F(DepthProbeElementTest, InitialState)
{
    const double wavelength = 1.0;
    const double angle = 2.0;
    const double phi = 0.0;
    const kvector_t k_i = vecOfLambdaAlphaPhi(wavelength, angle, phi);
    const DepthProbeElement& element = createDefaultElement();

    EXPECT_EQ(wavelength, element.getWavelength());
    EXPECT_EQ(angle, element.getAlphaI());
    bool intensity_comparison_result = (element.getIntensities() == 0.0).min();
    EXPECT_TRUE(intensity_comparison_result);
    EXPECT_EQ(k_i, element.getKi());
    EXPECT_TRUE(element.isCalculated());
}

TEST_F(DepthProbeElementTest, CopyMoveAssign)
{
    auto element = createDefaultElement();

    element.setCalculationFlag(false);

    DepthProbeElement element2 = element;

    compareEqualElements(element, element2);

    auto element3 = createDefaultElement();
    element3 = element;

    compareEqualElements(element, element3);

    auto element4 = std::move(element);

    compareEqualElements(element2, element4);

    auto element5 = createDefaultElement();
    element5 = std::move(element2);

    compareEqualElements(element5, element3);
}
