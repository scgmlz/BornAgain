#ifndef PARTICLETEST_H
#define PARTICLETEST_H

#include "Particle.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "HomogeneousMaterial.h"
#include "FormFactorFullSphere.h"

#include <iostream>

class ParticleTest : public ::testing::Test
{
protected:
    ParticleTest(){}
};


TEST_F(ParticleTest, InitialState)
{
    Particle particle;
    EXPECT_EQ(nullptr, particle.getMaterial());
    EXPECT_EQ(complex_t(0,0), particle.getRefractiveIndex());
    EXPECT_EQ(nullptr, particle.getFormFactor());
    EXPECT_EQ(nullptr, particle.createFormFactor());
    EXPECT_EQ(BornAgain::ParticleType, particle.getName());
}

TEST_F(ParticleTest, Clone)
{
    Particle particle;
    Particle *particle2 = particle.clone();
    EXPECT_EQ(nullptr, particle2->getMaterial());
    EXPECT_EQ(complex_t(0,0), particle2->getRefractiveIndex());
    EXPECT_EQ(nullptr, particle2->getFormFactor());
    EXPECT_EQ(nullptr, particle2->createFormFactor());
    EXPECT_EQ(BornAgain::ParticleType, particle2->getName());
    delete particle2;
}

TEST_F(ParticleTest, CloneInvertB)
{
    Particle particle;
    Particle *particle2 = particle.cloneInvertB();
    EXPECT_EQ(nullptr, particle2->getMaterial());
    EXPECT_EQ(complex_t(0,0), particle2->getRefractiveIndex());
    EXPECT_EQ(nullptr, particle2->getFormFactor());
    EXPECT_EQ(nullptr, particle2->createFormFactor());
    EXPECT_EQ(BornAgain::ParticleType, particle2->getName());
    delete particle2;
}

TEST_F(ParticleTest, Constructors)
{
    HomogeneousMaterial mat("Air",0,0);

    Particle *p1 = new Particle(mat);
    EXPECT_EQ("Air", p1->getMaterial()->getName());
    EXPECT_EQ(complex_t(1,0), p1->getRefractiveIndex());
    EXPECT_EQ(nullptr, p1->getFormFactor());
    EXPECT_EQ(nullptr, p1->createFormFactor());
    EXPECT_EQ( nullptr, p1->getRotation());

    delete p1;

    FormFactorFullSphere sphere(1.0);
    Particle *p2 = new Particle(mat, sphere);
    EXPECT_EQ(BornAgain::FFFullSphereType, p2->getFormFactor()->getName());
    EXPECT_EQ(1, p2->getFormFactor()->getRadialExtension());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial *>(
            p2->createFormFactor()));
    EXPECT_EQ(complex_t(1,0),
              dynamic_cast<FormFactorDecoratorMaterial *>(
                      p2->createFormFactor())->getAmbientRefractiveIndex());
    delete p2;

    FormFactorFullSphere sphere3(1.0);
    Particle *p3 = new Particle(mat, sphere3);
    EXPECT_EQ(sphere3.getName(), p3->getFormFactor()->getName());
    EXPECT_EQ(sphere3.getRadialExtension(), p3->getFormFactor()->getRadialExtension());

    Particle *p4 = p3->clone();
    EXPECT_EQ(BornAgain::FFFullSphereType, p4->getFormFactor()->getName());

    delete p3;
    delete p4;
}

TEST_F(ParticleTest, Transform)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(1.0);
    RotationZ transform(45.*Units::degree);
    Particle *particle = new Particle(mat, sphere, transform);

    EXPECT_EQ("Air", particle->getMaterial()->getName());

    EXPECT_TRUE(nullptr != particle->getRotation());

    delete particle;
}

TEST_F(ParticleTest, SetParam)
{
    HomogeneousMaterial mat("Air",0,0);
    FormFactorFullSphere sphere(2.1);
    RotationY transform(45.*Units::degree);

    Particle particle;
    EXPECT_EQ(nullptr, particle.getMaterial());
    EXPECT_EQ(nullptr, particle.getFormFactor());
    EXPECT_EQ(nullptr, particle.getRotation());

    particle.setMaterial(mat);
    EXPECT_EQ("Air", particle.getMaterial()->getName());
    EXPECT_EQ(complex_t(1.0), particle.getRefractiveIndex());

    particle.setFormFactor(sphere);
    EXPECT_EQ(BornAgain::FFFullSphereType, particle.getFormFactor()->getName());
    EXPECT_EQ(2.1, particle.getFormFactor()->getRadialExtension());

    particle.setRotation(transform);
    EXPECT_TRUE(nullptr != particle.getRotation());
    Particle *particle2 = particle.clone();
    EXPECT_EQ(BornAgain::ParticleType, particle2->getName());
    EXPECT_EQ("Air", particle2->getMaterial()->getName());
    EXPECT_EQ(complex_t(1.0), particle2->getRefractiveIndex());
    EXPECT_TRUE(nullptr != particle2->getFormFactor());
    EXPECT_EQ(2.1, particle2->getFormFactor()->getRadialExtension());
    EXPECT_TRUE(nullptr != particle2->getRotation());

    delete particle2;
}

#endif // PARTICLETEST_H
