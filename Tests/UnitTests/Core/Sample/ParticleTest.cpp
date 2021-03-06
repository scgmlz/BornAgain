#include "Sample/Particle/Particle.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Scattering/FormFactorDecoratorMaterial.h"
#include "Sample/Scattering/Rotations.h"
#include "Tests/GTestWrapper/google_test.h"

class ParticleTest : public ::testing::Test {
};

TEST_F(ParticleTest, Clone)
{
    Material mat = HomogeneousMaterial("Any", 1e-4, 1e-6);
    Particle particle(mat);
    std::unique_ptr<Particle> clone(particle.clone());
    EXPECT_EQ(mat, *clone->material());
    EXPECT_EQ(nullptr, clone->createFormFactor());
    EXPECT_EQ(nullptr, clone->rotation());
}

TEST_F(ParticleTest, Constructors)
{
    Material mat = HomogeneousMaterial("Vacuum", 0, 0);
    FormFactorFullSphere sphere(1.0);
    RotationZ transform(45. * Units::deg);

    // construction with material
    std::unique_ptr<Particle> p1(new Particle(mat));
    EXPECT_EQ(mat, *p1->material());
    EXPECT_EQ(nullptr, p1->createFormFactor());
    EXPECT_EQ(nullptr, p1->rotation());

    // construction with form factor
    std::unique_ptr<Particle> p2(new Particle(mat, sphere));
    EXPECT_EQ(mat, *p2->material());
    auto p2_formfactor = std::unique_ptr<IFormFactor>(p2->createFormFactor());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial*>(p2_formfactor.get()));
    EXPECT_EQ(nullptr, p2->rotation());

    // construction with transformation
    std::unique_ptr<Particle> p3(new Particle(mat, sphere, transform));
    EXPECT_EQ(mat, *p3->material());
    auto p3_formfactor = std::unique_ptr<IFormFactor>(p3->createFormFactor());
    EXPECT_TRUE(dynamic_cast<FormFactorDecoratorMaterial*>(p3_formfactor.get()));
}

TEST_F(ParticleTest, setters)
{
    Material mat = HomogeneousMaterial("Any", 10e-2, 10e-5);
    FormFactorFullSphere sphere(2.1);
    RotationY transform(45. * Units::deg);

    Particle particle(mat);
    EXPECT_EQ(mat, *particle.material());
    EXPECT_EQ(nullptr, particle.rotation());

    particle.setRotation(transform);
    EXPECT_TRUE(nullptr != particle.rotation());

    std::unique_ptr<Particle> particle2(particle.clone());
    EXPECT_EQ(mat, *particle2->material());
    EXPECT_TRUE(nullptr != particle2->rotation());
}

TEST_F(ParticleTest, getChildren)
{
    Material mat = HomogeneousMaterial("Vacuum", 0, 0);
    FormFactorFullSphere sphere(2.1);

    // Checking children of particle (no rotation)
    std::unique_ptr<Particle> particle(new Particle(mat, sphere));
    std::vector<const INode*> children = particle->getChildren();
    EXPECT_EQ(children.size(), 1u);

    // Checking children of particle (with rotation)
    particle = std::make_unique<Particle>(mat, sphere, RotationY(45.));
    children = particle->getChildren();
    EXPECT_EQ(children.size(), 2u);
}
