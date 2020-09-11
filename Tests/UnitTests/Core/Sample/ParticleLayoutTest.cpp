#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Aggregate/InterferenceFunction1DLattice.h"
#include "Core/Aggregate/InterferenceFunctionNone.h"
#include "Core/Basics/Units.h"
#include "Core/Export/INodeUtils.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Particle/IAbstractParticle.h"
#include "Core/Particle/Particle.h"
#include "Tests/GTestWrapper/google_test.h"

class ParticleLayoutTest : public ::testing::Test
{

protected:
    ~ParticleLayoutTest();
};

ParticleLayoutTest::~ParticleLayoutTest() = default;

TEST_F(ParticleLayoutTest, ParticleLayoutInitial)
{
    ParticleLayout particleDecoration;
    auto p_iff = INodeUtils::OnlyChildOfType<IInterferenceFunction>(particleDecoration);
    auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(particleDecoration);
    EXPECT_EQ(size_t(0), particles.size());
    EXPECT_EQ(nullptr, p_iff);
}

TEST_F(ParticleLayoutTest, ParticleLayoutInitByValue)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, 2.0);
    auto p_iff = INodeUtils::OnlyChildOfType<IInterferenceFunction>(particleDecoration);
    auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(particleDecoration);
    EXPECT_EQ(size_t(1), particles.size());
    EXPECT_EQ(nullptr, p_iff);

    const IAbstractParticle* p_particle = particles[0];
    EXPECT_TRUE(nullptr != p_particle);
    EXPECT_EQ(2.0, particleDecoration.getTotalAbundance());
}

TEST_F(ParticleLayoutTest, ParticleLayoutAddParticle)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationZ transform3(45. * Units::degree);
    RotationZ transform4(45. * Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.2);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0, 0, 0), transform3);
    particleDecoration.addParticle(particle4, 4.2, kvector_t(0, 0, 0), transform4);
    auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(particleDecoration);

    EXPECT_EQ(size_t(4), particles.size());

    const IAbstractParticle* p_particle1 = particles[0];
    EXPECT_TRUE(nullptr != p_particle1);
    EXPECT_EQ(1.0, p_particle1->abundance());

    const IAbstractParticle* p_particle2 = particles[1];
    EXPECT_TRUE(nullptr != p_particle2);
    EXPECT_EQ(2.2, p_particle2->abundance());

    const IAbstractParticle* p_particle3 = particles[2];
    EXPECT_TRUE(nullptr != p_particle3);
    EXPECT_EQ(1.0, p_particle3->abundance());

    const IAbstractParticle* p_particle4 = particles[3];
    EXPECT_TRUE(nullptr != p_particle4);
    EXPECT_EQ(4.2, p_particle4->abundance());
}

TEST_F(ParticleLayoutTest, ParticleLayoutAbundanceFraction)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45. * Units::degree);
    RotationZ transform4(45. * Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.0);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0, 0, 0), transform3);
    particleDecoration.addParticle(particle4, 4.0, kvector_t(0, 0, 0), transform4);
    EXPECT_EQ(8.0, particleDecoration.getTotalAbundance());
}

TEST_F(ParticleLayoutTest, ParticleLayoutClone)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45. * Units::degree);
    RotationZ transform4(45. * Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.0);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0, 0, 0), transform3);
    particleDecoration.addParticle(particle4, 4.0, kvector_t(0, 0, 0), transform4);

    Material mat5 = HomogeneousMaterial("core", 0, 0);
    Particle particle5(mat5);
    particleDecoration.addParticle(particle5, 0.0);

    InterferenceFunctionNone iff_none;
    particleDecoration.setInterferenceFunction(iff_none);
    particleDecoration.setInterferenceFunction(iff_none);
    particleDecoration.setInterferenceFunction(iff_none);

    ParticleLayout* clone = particleDecoration.clone();
    auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(*clone);

    const IAbstractParticle* p_particle1 = particles[0];
    EXPECT_TRUE(nullptr != p_particle1);
    EXPECT_EQ(1.0, p_particle1->abundance());

    const IAbstractParticle* p_particle2 = particles[1];
    EXPECT_TRUE(nullptr != p_particle2);
    EXPECT_EQ(2.0, p_particle2->abundance());

    const IAbstractParticle* p_particle3 = particles[2];
    EXPECT_TRUE(nullptr != p_particle3);
    EXPECT_EQ(1.0, p_particle3->abundance());

    const IAbstractParticle* p_particle4 = particles[3];
    EXPECT_TRUE(nullptr != p_particle4);
    EXPECT_EQ(4.0, p_particle4->abundance());

    const IAbstractParticle* p_particle5 = particles[4];
    EXPECT_TRUE(nullptr != p_particle5);
    EXPECT_EQ(0.0, p_particle5->abundance());

    auto p_iff = INodeUtils::OnlyChildOfType<IInterferenceFunction>(*clone);

    EXPECT_TRUE(nullptr != p_iff);
}

TEST_F(ParticleLayoutTest, ParticleLayoutInterferenceFunction)
{
    ParticleLayout particleDecoration;

    InterferenceFunctionNone iff_none;
    particleDecoration.setInterferenceFunction(iff_none);
    auto p_iff = INodeUtils::OnlyChildOfType<IInterferenceFunction>(particleDecoration);

    EXPECT_TRUE(nullptr != p_iff);
}

TEST_F(ParticleLayoutTest, getChildren)
{
    ParticleLayout layout;
    std::vector<const INode*> children = layout.getChildren();
    EXPECT_EQ(children.size(), 0u);

    layout.addParticle(Particle());
    layout.setInterferenceFunction(InterferenceFunction1DLattice(1.0, 2.0));
    children = layout.getChildren();
    EXPECT_EQ(children.size(), 2u);
}
