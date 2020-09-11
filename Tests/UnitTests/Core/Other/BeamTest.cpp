#include "Core/Beam/Beam.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Beam/FootprintGauss.h"
#include "Core/Beam/FootprintSquare.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Tests/GTestWrapper/google_test.h"

#include <memory>

class BeamTest : public ::testing::Test
{
};

TEST_F(BeamTest, BeamInitialState)
{
    Beam beam = Beam::horizontalBeam();
    EXPECT_DOUBLE_EQ(M_TWOPI, beam.getCentralK()[0]);
    EXPECT_EQ(0.0, beam.getCentralK()[1]);
    EXPECT_EQ(0.0, beam.getCentralK()[2]);
    EXPECT_EQ(1.0, beam.getIntensity());
    // EXPECT_EQ(size_t(4), beam.parameterPool()->size());
    //    EXPECT_EQ(1.0, beam.parameterPool()->parameter("Intensity")->value());
    //    EXPECT_EQ(1.0, beam.parameterPool()->parameter("Wavelength")->value());
    //    EXPECT_EQ(0.0, beam.parameterPool()->parameter("Alpha")->value());
    //    EXPECT_EQ(0.0, beam.parameterPool()->parameter("Phi")->value());
    //    EXPECT_EQ(complex_t(0.5, 0.0), beam.getPolarization()(0, 0));
    //    EXPECT_EQ(complex_t(0.5, 0.0), beam.getPolarization()(1, 1));
}

TEST_F(BeamTest, BeamAssignment)
{
    kvector_t polarization(0.0, 0.0, 0.2);

    std::unique_ptr<Beam> P_beam{new Beam(1.0, 1.0, 1.0, 2.0)};
    P_beam->setPolarization(polarization);

    Beam beam_copy = *P_beam;
    EXPECT_NEAR(1.83423, beam_copy.getCentralK()[0], 0.00001);
    EXPECT_NEAR(-2.85664, beam_copy.getCentralK()[1], 0.00001);
    EXPECT_NEAR(-5.28712, beam_copy.getCentralK()[2], 0.00001);
    EXPECT_EQ(double(2.0), beam_copy.getIntensity());
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ(size_t(4), beam_copy.getParameterPool()->size());
    EXPECT_EQ(double(2.0),
              beam_copy.getParameterPool()->getParameter("Intensity").getValue());
    EXPECT_EQ(complex_t(0.6, 0.0), beam_copy.getPolarization()(0, 0));
    EXPECT_EQ(complex_t(0.4, 0.0), beam_copy.getPolarization()(1, 1));
    */
}

TEST_F(BeamTest, BeamPolarization)
{
    Beam beam = Beam::horizontalBeam();
    kvector_t polarization(0.1, -0.2, 0.4);
    beam.setPolarization(polarization);

    kvector_t bloch_vector = beam.getBlochVector();
    EXPECT_NEAR(0.1, bloch_vector.x(), 1e-8);
    EXPECT_NEAR(-0.2, bloch_vector.y(), 1e-8);
    EXPECT_NEAR(0.4, bloch_vector.z(), 1e-8);
}

TEST_F(BeamTest, FootprintBehaviour)
{
    Beam beam = Beam::horizontalBeam();
    EXPECT_EQ(nullptr, beam.footprintFactor());
    EXPECT_THROW(beam.setWidthRatio(1.0), std::runtime_error);

    FootprintSquare square_ff(0.0);
    beam.setFootprintFactor(square_ff);
    beam.setWidthRatio(1.0);
    EXPECT_EQ(1.0, beam.footprintFactor()->widthRatio());

    Beam beam4 = beam;
    FootprintGauss gaussian_ff(1.0);
    beam4.setFootprintFactor(gaussian_ff);

    const double r0 = beam.footprintFactor()->widthRatio();
    const double r4 = beam4.footprintFactor()->widthRatio();
    EXPECT_EQ(r0, r4);

    EXPECT_EQ(beam.footprintFactor()->parent(), static_cast<INode*>(&beam));
    EXPECT_EQ(beam4.footprintFactor()->parent(), static_cast<INode*>(&beam4));
}
