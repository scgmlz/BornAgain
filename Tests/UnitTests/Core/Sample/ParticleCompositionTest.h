#ifndef PARTICLECOMPOSITIONTEST_H
#define PARTICLECOMPOSITIONTEST_H

#include "FormFactorFullSphere.h"
#include "HomogeneousMaterial.h"
#include "MathConstants.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include <iostream>

class ParticleCompositionTest : public ::testing::Test
{
protected:
    ParticleCompositionTest()
    {
    }
    virtual ~ParticleCompositionTest()
    {
    }
};

TEST_F(ParticleCompositionTest, ParticleCompositionDefaultConstructor)
{
    ParticleComposition *lb = new ParticleComposition();
    std::vector<kvector_t> positions;
    positions.push_back(kvector_t(0.0, 0.0, 0.0));
    EXPECT_EQ("ParticleComposition", lb->getName());
    EXPECT_EQ(nullptr, lb->getAmbientMaterial());
    EXPECT_EQ(size_t(0), lb->getNbrParticles());

    delete lb;
}

TEST_F(ParticleCompositionTest, ParticleCompositionConstructorWithOneParameter)
{
    Particle particle;
    ParticleComposition *lb = new ParticleComposition(particle);
    kvector_t position;
    EXPECT_EQ("ParticleComposition", lb->getName());
    lb->addParticle(particle, position);
    EXPECT_EQ(particle.getMaterial(), lb->getParticle(0)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), lb->getParticle(0)->getName());
    EXPECT_EQ(particle.getRotation(), lb->getParticle(0)->getRotation());
    EXPECT_EQ(particle.getMaterial(), lb->getParticle(1)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), lb->getParticle(1)->getName());
    EXPECT_EQ(particle.getRotation(), lb->getParticle(1)->getRotation());
    EXPECT_EQ(position, lb->getParticlePosition(0));
    EXPECT_EQ(position, lb->getParticlePosition(1));

    HomogeneousMaterial material("Air", 0.0, 0.0);
    lb->setAmbientMaterial(material);
    EXPECT_EQ("Air", lb->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, lb->getAmbientMaterial()->getRefractiveIndex());

    delete lb;
}

TEST_F(ParticleCompositionTest, ParticleCompositionConstructorWithTwoParameter)
{
    Particle particle;
    kvector_t position = kvector_t(1.0, 1.0, 1.0);
    ParticleComposition *lb = new ParticleComposition(particle, position);

    EXPECT_EQ("ParticleComposition", lb->getName());
    lb->addParticle(particle, position);
    EXPECT_EQ(particle.getMaterial(), lb->getParticle(0)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), lb->getParticle(0)->getName());
    EXPECT_EQ(particle.getRotation(), lb->getParticle(0)->getRotation());
    EXPECT_EQ(particle.getMaterial(), lb->getParticle(1)->getAmbientMaterial());
    EXPECT_EQ(particle.getName(), lb->getParticle(1)->getName());
    EXPECT_EQ(particle.getRotation(), lb->getParticle(1)->getRotation());
    EXPECT_EQ(position, lb->getParticlePosition(0));
    EXPECT_EQ(position, lb->getParticlePosition(1));

    HomogeneousMaterial material("Air", 0.0, 0.0);
    lb->setAmbientMaterial(material);
    EXPECT_EQ("Air", lb->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, lb->getAmbientMaterial()->getRefractiveIndex());

    delete lb;
}

TEST_F(ParticleCompositionTest, ParticleCompositionClone)
{
    ParticleComposition *lb = new ParticleComposition();
    Particle particle;
    kvector_t position = kvector_t(1.0, 1.0, 1.0);
    HomogeneousMaterial material("Air", 0.0, 0.0);
    lb->addParticle(particle, position);
    lb->setAmbientMaterial(material);
    ParticleComposition *lbClone = lb->clone();

    EXPECT_EQ(lbClone->getName(), lb->getName());

    EXPECT_EQ(lbClone->getParticle(0)->getAmbientMaterial()->getRefractiveIndex(),
              lb->getParticle(0)->getAmbientMaterial()->getRefractiveIndex());
    EXPECT_EQ(lbClone->getParticle(0)->getName(), lb->getParticle(0)->getName());
    EXPECT_EQ(lbClone->getParticle(0)->getRotation(),
              lb->getParticle(0)->getRotation());
    EXPECT_EQ(position, lb->getParticlePosition(0));

    EXPECT_EQ("Air", lb->getAmbientMaterial()->getName());
    EXPECT_EQ(1.0, lb->getAmbientMaterial()->getRefractiveIndex());

    delete lb;
    delete lbClone;
}

#endif // PARTICLECOMPOSITIONTEST_H
