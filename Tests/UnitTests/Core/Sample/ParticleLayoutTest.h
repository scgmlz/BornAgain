#ifndef PARTICLELAYOUTTEST_H
#define PARTICLELAYOUTTEST_H

#include "ParticleLayout.h"
#include "InterferenceFunctionNone.h"

class ParticleLayoutTest : public :: testing :: Test {

protected:
    ParticleLayoutTest(){}
};

TEST_F(ParticleLayoutTest, ParticleLayoutInitial)
{
    ParticleLayout particleDecoration;

    EXPECT_EQ(BornAgain::ParticleLayoutType, particleDecoration.getName());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(nullptr, particleDecoration.getInterferenceFunction());
}

TEST_F(ParticleLayoutTest, ParticleLayoutInitByValue)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, 2.0);

    EXPECT_EQ(BornAgain::ParticleLayoutType, particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(nullptr, particleDecoration.getInterferenceFunction());


    const IAbstractParticle * p_particle = particleDecoration.getParticle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    EXPECT_EQ(nullptr, particleDecoration.getInterferenceFunction());
}

TEST_F(ParticleLayoutTest, ParticleLayoutInitByRef)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, -2.0);

    EXPECT_EQ(BornAgain::ParticleLayoutType, particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(nullptr, particleDecoration.getInterferenceFunction());


    const IAbstractParticle * p_particle = particleDecoration.getParticle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle);
    EXPECT_EQ(-2.0, particleDecoration.getAbundanceOfParticle(size_t(0)));
}

TEST_F(ParticleLayoutTest, ParticleLayoutAddParticle)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationZ transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.2);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0,0,0), transform3);
    particleDecoration.addParticle(particle4, -4.2, kvector_t(0,0,0), transform4);

    EXPECT_EQ(size_t(4), particleDecoration.getNumberOfParticles());

    const IAbstractParticle * p_particle1 = particleDecoration.getParticle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = particleDecoration.getParticle(size_t(1));
    EXPECT_TRUE(nullptr!=p_particle2);
    EXPECT_EQ(2.2, particleDecoration.getAbundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = particleDecoration.getParticle(size_t(2));
    EXPECT_TRUE(nullptr!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = particleDecoration.getParticle(size_t(3));
    EXPECT_TRUE(nullptr!=p_particle4);
    EXPECT_EQ(-4.2, particleDecoration.getAbundanceOfParticle(size_t(3)));
}

TEST_F(ParticleLayoutTest, ParticleLayoutAbundanceFraction)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    particleDecoration.addParticle(particle2, 2.0);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(1)));

    particleDecoration.addParticle(particle3, 1.0, kvector_t(0,0,0), transform3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    particleDecoration.addParticle(particle4, 4.0, kvector_t(0,0,0), transform4);
    EXPECT_EQ(4.0, particleDecoration.getAbundanceOfParticle(size_t(3)));
}

TEST_F(ParticleLayoutTest, ParticleLayoutClone)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.0);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0,0,0), transform3);
    particleDecoration.addParticle(particle4, 4.0, kvector_t(0,0,0), transform4);

    HomogeneousMaterial mat5("core", 0, 0);
    Particle particle5(mat5);
    particleDecoration.addParticle(particle5, 0.0);

    InterferenceFunctionNone iff_none;
    particleDecoration.addInterferenceFunction(iff_none);
    particleDecoration.addInterferenceFunction(iff_none);
    particleDecoration.addInterferenceFunction(iff_none);

    ParticleLayout * clone = particleDecoration.clone();

    EXPECT_EQ(BornAgain::ParticleLayoutType, clone->getName());

    const IAbstractParticle * p_particle1 = clone->getParticle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = clone->getParticle(size_t(1));
    EXPECT_TRUE(nullptr!=p_particle2);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = clone->getParticle(size_t(2));
    EXPECT_TRUE(nullptr!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = clone->getParticle(size_t(3));
    EXPECT_TRUE(nullptr!=p_particle4);
    EXPECT_EQ(4.0, particleDecoration.getAbundanceOfParticle(size_t(3)));

    const IAbstractParticle * p_particle5 = clone->getParticle(size_t(4));
    EXPECT_TRUE(nullptr!=p_particle5);
    EXPECT_EQ(0.0, particleDecoration.getAbundanceOfParticle(size_t(4)));

    EXPECT_TRUE(nullptr!=clone->getInterferenceFunction());
}

TEST_F(ParticleLayoutTest, ParticleLayoutCloneInvertB)
{
    ParticleLayout particleDecoration;

    HomogeneousMaterial mat1("Air",0,0);
    Particle particle1(mat1);

    HomogeneousMaterial mat2("Stone",0,0);
    Particle particle2(mat2);

    HomogeneousMaterial mat3("wood",0,0);
    Particle particle3(mat3);

    HomogeneousMaterial mat4("silica",0,0);
    Particle particle4(mat4);

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);


    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.0);
    particleDecoration.addParticle(particle3, 1.0, kvector_t(0,0,0), transform3);
    particleDecoration.addParticle(particle4, 4.0, kvector_t(0,0,0), transform4);

    HomogeneousMaterial mat5("core",0,0);
    Particle particle5(mat5);
    particleDecoration.addParticle(particle5, 0.0);

    InterferenceFunctionNone iff_none;
    particleDecoration.addInterferenceFunction(iff_none);

    ParticleLayout * clone = particleDecoration.cloneInvertB();

    EXPECT_EQ(BornAgain::ParticleLayoutType, clone->getName());

    const IAbstractParticle * p_particle1 = clone->getParticle(size_t(0));
    EXPECT_TRUE(nullptr!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = clone->getParticle(size_t(1));
    EXPECT_TRUE(nullptr!=p_particle2);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = clone->getParticle(size_t(2));
    EXPECT_TRUE(nullptr!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = clone->getParticle(size_t(3));
    EXPECT_TRUE(nullptr!=p_particle4);
    EXPECT_EQ(4.0, particleDecoration.getAbundanceOfParticle(size_t(3)));

    const IAbstractParticle * p_particle5 = clone->getParticle(size_t(4));
    EXPECT_TRUE(nullptr!=p_particle5);
    EXPECT_EQ(0.0, particleDecoration.getAbundanceOfParticle(size_t(4)));

    EXPECT_TRUE(nullptr!=clone->getInterferenceFunction());
}

TEST_F(ParticleLayoutTest, ParticleLayoutInterferenceFunction)
{
    ParticleLayout particleDecoration;

    InterferenceFunctionNone iff_none;
    particleDecoration.addInterferenceFunction(iff_none);

    EXPECT_TRUE(nullptr!=particleDecoration.getInterferenceFunction());
}

#endif // PARTICLELAYOUTTEST_H
