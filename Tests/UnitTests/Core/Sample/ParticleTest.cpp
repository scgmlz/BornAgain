#include "Core/Particle/Particle.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Tests/GTestWrapper/google_test.h"

class ParticleTest : public ::testing::Test
{
protected:
    ~ParticleTest();
};

ParticleTest::~ParticleTest() = default;

TEST_F(ParticleTest, InitialState)
{
    Particle particle;
    EXPECT_EQ(HomogeneousMaterial(), *particle.material());
    EXPECT_EQ(nullptr, particle.createFormFactor());
    EXPECT_EQ(nullptr, particle.rotation());
}

TEST_F(ParticleTest, Clone)
{
    Particle particle;
    std::unique_ptr<Particle> clone(particle.clone());
    EXPECT_EQ(HomogeneousMaterial(), *clone->material());
    EXPECT_EQ(nullptr, clone->createFormFactor());
    EXPECT_EQ(nullptr, clone->rotation());
}

TEST_F(ParticleTest, Constructors)
{
    Material mat = HomogeneousMaterial("Air", 0, 0);
    FormFactorFullSphere sphere(1.0);
    RotationZ transform(45. * Units::degree);

    // construction with material
    std::unique_ptr<Particle> p1(new Particle(mat));
    EXPECT_EQ(mat, *p1->material());
    EXPECT_EQ(nullptr, p1->createFormFactor());
    EXPECT_EQ(nullptr, p1->rotation());

    // construction with form factor
    std::unique_ptr<Particle> p2(new Particle(mat, sphere));
    EXPECT_EQ(mat, *p2->material());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial*>(p2->createFormFactor()));
    EXPECT_EQ(nullptr, p2->rotation());

    // construction with transformation
    std::unique_ptr<Particle> p3(new Particle(mat, sphere, transform));
    EXPECT_EQ(mat, *p3->material());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial*>(p3->createFormFactor()));
}

TEST_F(ParticleTest, setters)
{
    Material mat = HomogeneousMaterial("Air", 0, 0);
    FormFactorFullSphere sphere(2.1);
    RotationY transform(45. * Units::degree);

    Particle particle;
    Material vacuum = HomogeneousMaterial();
    EXPECT_EQ(vacuum, *particle.material());
    EXPECT_EQ(nullptr, particle.rotation());

    particle.setRotation(transform);
    EXPECT_TRUE(nullptr != particle.rotation());

    std::unique_ptr<Particle> particle2(particle.clone());
    EXPECT_EQ(vacuum, *particle2->material());
    EXPECT_TRUE(nullptr != particle2->rotation());
}

TEST_F(ParticleTest, getChildren)
{
    Material mat = HomogeneousMaterial("Air", 0, 0);
    FormFactorFullSphere sphere(2.1);

    // Checking children of particle (no rotation)
    std::unique_ptr<Particle> particle(new Particle(mat, sphere));
    std::vector<const INode*> children = particle->getChildren();
    EXPECT_EQ(children.size(), 1u);

    // Checking children of particle (with rotation)
    particle.reset(new Particle(mat, sphere, RotationY(45.)));
    children = particle->getChildren();
    EXPECT_EQ(children.size(), 2u);
}
