#include "Core/SimulationElement/SimulationElement.h"
#include "Core/Basics/Units.h"
#include "Core/Binning/Bin.h"
#include "Core/Detector/SphericalPixel.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

namespace
{
const Bin1D alpha_bin(0.0 * Units::deg, 1.0 * Units::deg);
const Bin1D phi_bin(-0.5 * Units::deg, 0.5 * Units::deg);
const double wavelength = 42.0;
const double alpha_i = 0.2 * Units::deg;
const double phi_i = 0.0 * Units::deg;
} // namespace

class SimulationElementTest : public ::testing::Test
{
public:
    std::unique_ptr<IPixel> createPixel() const
    {
        return std::make_unique<SphericalPixel>(alpha_bin, phi_bin);
    }

    std::unique_ptr<SimulationElement> createElement() const
    {
        return std::make_unique<SimulationElement>(wavelength, alpha_i, phi_i, createPixel());
    }
};

TEST_F(SimulationElementTest, basicConstructor)
{
    SimulationElement element(wavelength, alpha_i, phi_i, createPixel());
    EXPECT_EQ(element.getWavelength(), wavelength);
    EXPECT_EQ(element.getAlphaI(), alpha_i);
    EXPECT_EQ(element.getPhiI(), phi_i);
    EXPECT_EQ(element.getIntensity(), 0.0);
    EXPECT_NEAR(element.getAlphaMean(), 0.5 * Units::deg, 1e-14);
    EXPECT_NEAR(element.getPhiMean(), 0.0 * Units::deg, 1e-14);
    EXPECT_EQ(element.getKi(), vecOfLambdaAlphaPhi(wavelength, alpha_i, phi_i));
    EXPECT_EQ(element.getMeanKf(), createPixel()->getK(0.5, 0.5, wavelength));
    EXPECT_FALSE(element.isSpecular());
}

TEST_F(SimulationElementTest, setIntensity)
{
    auto element = createElement();
    EXPECT_EQ(element->getIntensity(), 0.0);
    element->addIntensity(1.0);
    EXPECT_EQ(element->getIntensity(), 1.0);
    element->setIntensity(42.0);
    EXPECT_EQ(element->getIntensity(), 42.0);
}

TEST_F(SimulationElementTest, copyConstructor)
{
    auto orig = createElement();
    SimulationElement element(*orig);
    EXPECT_EQ(orig->getWavelength(), element.getWavelength());
    EXPECT_EQ(orig->getAlphaI(), element.getAlphaI());
    EXPECT_EQ(orig->getPhiI(), element.getPhiI());
    EXPECT_EQ(orig->getAlphaMean(), element.getAlphaMean());
    EXPECT_EQ(orig->getPhiMean(), element.getPhiMean());
    EXPECT_EQ(orig->getIntensity(), element.getIntensity());
    EXPECT_EQ(orig->getKi(), element.getKi());
    EXPECT_EQ(orig->getMeanKf(), element.getMeanKf());
    EXPECT_EQ(orig->getQ(0.5, 0.5), element.getQ(0.5, 0.5));
    EXPECT_EQ(orig->getIntegrationFactor(0.5, 0.5), element.getIntegrationFactor(0.5, 0.5));
    EXPECT_EQ(orig->getSolidAngle(), element.getSolidAngle());
    EXPECT_EQ(orig->getAlpha(0.5, 0.5), element.getAlpha(0.5, 0.5));
    EXPECT_EQ(orig->getPhi(0.5, 0.5), element.getPhi(0.5, 0.5));
    EXPECT_EQ(orig->isSpecular(), element.isSpecular());
}

TEST_F(SimulationElementTest, assignmentOperator)
{
    auto orig = createElement();
    SimulationElement element(1.0, 1.0, 1.0, createPixel());
    element = *orig;

    EXPECT_EQ(orig->getWavelength(), element.getWavelength());
    EXPECT_EQ(orig->getAlphaI(), element.getAlphaI());
    EXPECT_EQ(orig->getPhiI(), element.getPhiI());
    EXPECT_EQ(orig->getAlphaMean(), element.getAlphaMean());
    EXPECT_EQ(orig->getPhiMean(), element.getPhiMean());
    EXPECT_EQ(orig->getIntensity(), element.getIntensity());
    EXPECT_EQ(orig->getKi(), element.getKi());
    EXPECT_EQ(orig->getMeanKf(), element.getMeanKf());
    EXPECT_EQ(orig->getQ(0.5, 0.5), element.getQ(0.5, 0.5));
    EXPECT_EQ(orig->getIntegrationFactor(0.5, 0.5), element.getIntegrationFactor(0.5, 0.5));
    EXPECT_EQ(orig->getSolidAngle(), element.getSolidAngle());
    EXPECT_EQ(orig->getAlpha(0.5, 0.5), element.getAlpha(0.5, 0.5));
    EXPECT_EQ(orig->getPhi(0.5, 0.5), element.getPhi(0.5, 0.5));
    EXPECT_EQ(orig->isSpecular(), element.isSpecular());
}

TEST_F(SimulationElementTest, moveAssignment)
{
    SimulationElement for_move(1.0, 2.0, 3.0, createPixel());
    SimulationElement orig(1.0, 2.0, 3.0, createPixel());
    SimulationElement element = std::move(for_move);

    EXPECT_EQ(orig.getWavelength(), element.getWavelength());
    EXPECT_EQ(orig.getAlphaI(), element.getAlphaI());
    EXPECT_EQ(orig.getPhiI(), element.getPhiI());
    EXPECT_EQ(orig.getAlphaMean(), element.getAlphaMean());
    EXPECT_EQ(orig.getPhiMean(), element.getPhiMean());
    EXPECT_EQ(orig.getIntensity(), element.getIntensity());
    EXPECT_EQ(orig.getKi(), element.getKi());
    EXPECT_EQ(orig.getMeanKf(), element.getMeanKf());
    EXPECT_EQ(orig.getQ(0.5, 0.5), element.getQ(0.5, 0.5));
    EXPECT_EQ(orig.getIntegrationFactor(0.5, 0.5), element.getIntegrationFactor(0.5, 0.5));
    EXPECT_EQ(orig.getSolidAngle(), element.getSolidAngle());
    EXPECT_EQ(orig.getAlpha(0.5, 0.5), element.getAlpha(0.5, 0.5));
    EXPECT_EQ(orig.getPhi(0.5, 0.5), element.getPhi(0.5, 0.5));
    EXPECT_EQ(orig.isSpecular(), element.isSpecular());
}

TEST_F(SimulationElementTest, moveConstruction)
{
    SimulationElement for_move(1.0, 2.0, 3.0, createPixel());
    SimulationElement orig(1.0, 2.0, 3.0, createPixel());
    SimulationElement element(std::move(for_move));

    EXPECT_EQ(orig.getWavelength(), element.getWavelength());
    EXPECT_EQ(orig.getAlphaI(), element.getAlphaI());
    EXPECT_EQ(orig.getPhiI(), element.getPhiI());
    EXPECT_EQ(orig.getAlphaMean(), element.getAlphaMean());
    EXPECT_EQ(orig.getPhiMean(), element.getPhiMean());
    EXPECT_EQ(orig.getIntensity(), element.getIntensity());
    EXPECT_EQ(orig.getKi(), element.getKi());
    EXPECT_EQ(orig.getMeanKf(), element.getMeanKf());
    EXPECT_EQ(orig.getQ(0.5, 0.5), element.getQ(0.5, 0.5));
    EXPECT_EQ(orig.getIntegrationFactor(0.5, 0.5), element.getIntegrationFactor(0.5, 0.5));
    EXPECT_EQ(orig.getSolidAngle(), element.getSolidAngle());
    EXPECT_EQ(orig.getAlpha(0.5, 0.5), element.getAlpha(0.5, 0.5));
    EXPECT_EQ(orig.getPhi(0.5, 0.5), element.getPhi(0.5, 0.5));
    EXPECT_EQ(orig.isSpecular(), element.isSpecular());
}
