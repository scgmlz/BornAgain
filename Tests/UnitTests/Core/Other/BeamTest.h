#ifndef BEAMTEST_H
#define BEAMTEST_H

#include "Beam.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "ParameterPool.h"

#include <memory>


class BeamTest : public ::testing::Test
{
protected:
    BeamTest() {}

    Beam m_empty_beam;
};

TEST_F(BeamTest, BeamInitialState)
{
    EXPECT_DOUBLE_EQ(M_TWOPI, m_empty_beam.getCentralK()[0]);
    EXPECT_EQ(0.0, m_empty_beam.getCentralK()[1]);
    EXPECT_EQ(0.0, m_empty_beam.getCentralK()[2]);
    EXPECT_EQ(0.0, m_empty_beam.getIntensity());
    /* TEMPORARILY DISABLED getParameterPool() 
    EXPECT_EQ(size_t(4), m_empty_beam.getParameterPool()->size());
    EXPECT_EQ(0.0, m_empty_beam.getParameterPool()->getParameter(BornAgain::Intensity).getValue());
    EXPECT_EQ(1.0, m_empty_beam.getParameterPool()->getParameter(BornAgain::Wavelength).getValue());
    EXPECT_EQ(0.0, m_empty_beam.getParameterPool()->getParameter(BornAgain::Alpha).getValue());
    EXPECT_EQ(0.0, m_empty_beam.getParameterPool()->getParameter(BornAgain::Phi).getValue());
    EXPECT_EQ(complex_t(0.5, 0.0), m_empty_beam.getPolarization()(0, 0));
    EXPECT_EQ(complex_t(0.5, 0.0), m_empty_beam.getPolarization()(1, 1));
    */
}

TEST_F(BeamTest, BeamAssignment)
{
    kvector_t polarization(0.0, 0.0, 0.2);

    std::unique_ptr<Beam> P_beam { new Beam() };

    P_beam->setCentralK(1.0, 1.0, 1.0);
    P_beam->setIntensity(2.0);
    P_beam->setPolarization(polarization);

    Beam beam_copy = *P_beam;
    EXPECT_NEAR(1.83423, beam_copy.getCentralK()[0], 0.00001);
    EXPECT_NEAR(-2.85664, beam_copy.getCentralK()[1], 0.00001);
    EXPECT_NEAR(-5.28712, beam_copy.getCentralK()[2], 0.00001);
    EXPECT_EQ(double(2.0), beam_copy.getIntensity());
    /* TEMPORARILY DISABLED getParameterPool() 
    EXPECT_EQ(size_t(4), beam_copy.getParameterPool()->size());
    EXPECT_EQ(double(2.0),
              beam_copy.getParameterPool()->getParameter(BornAgain::Intensity).getValue());
    EXPECT_EQ(complex_t(0.6, 0.0), beam_copy.getPolarization()(0, 0));
    EXPECT_EQ(complex_t(0.4, 0.0), beam_copy.getPolarization()(1, 1));
    */
}


#endif // BEAMTEST_H
