#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Particle/Particle.h"
#include "Core/Scattering/Rotations.h"
#include "Core/includeIncludes/HardParticles.h"
#include "Tests/GTestWrapper/google_test.h"

class ParticleCoreShellTest : public ::testing::Test
{
protected:
    ParticleCoreShellTest();
    virtual ~ParticleCoreShellTest();

    ParticleCoreShell* mp_coreshell;
};

ParticleCoreShellTest::ParticleCoreShellTest() : mp_coreshell(nullptr)
{
    Particle core;
    Particle shell;
    kvector_t position;
    mp_coreshell = new ParticleCoreShell(shell, core, position);
}

ParticleCoreShellTest::~ParticleCoreShellTest()
{
    delete mp_coreshell;
}

TEST_F(ParticleCoreShellTest, InitialState)
{
    EXPECT_EQ(nullptr, mp_coreshell->createFormFactor());
    EXPECT_EQ(nullptr, mp_coreshell->rotation());
}

TEST_F(ParticleCoreShellTest, Clone)
{
    ParticleCoreShell* p_clone = mp_coreshell->clone();
    EXPECT_EQ(nullptr, p_clone->createFormFactor());
    EXPECT_EQ(nullptr, p_clone->rotation());
    delete p_clone;
}

TEST_F(ParticleCoreShellTest, ComplexCoreShellClone)
{
    Material mCore = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);
    Material mShell = HomogeneousMaterial("AgO2", 8.600e-6, 3.442e-7);

    double shell_length(50);
    double shell_width(20);
    double shell_height(10);
    double core_length = shell_length / 2;
    double core_width = shell_width / 2;
    double core_height = shell_height / 2;

    Particle core(mCore, FormFactorBox(core_length, core_width, core_height));
    Particle shell(mShell, FormFactorBox(shell_length, shell_width, shell_height));
    kvector_t relative_pos(0, 0, (shell_height - core_height) / 2);
    ParticleCoreShell coreshell(shell, core, relative_pos);
    coreshell.setRotation(RotationY(90 * Units::degree));
    coreshell.setPosition(kvector_t(0, 0, -10));

    ParticleCoreShell* clone = coreshell.clone();
    EXPECT_EQ(coreshell.coreParticle()->position(), relative_pos);
    EXPECT_EQ(clone->coreParticle()->position(), relative_pos);
}

TEST_F(ParticleCoreShellTest, getChildren)
{
    Material mat = HomogeneousMaterial("mat", 0.0, 0.0);
    Particle core(mat, FormFactorBox(1.0, 1.0, 1.0));
    Particle shell(mat, FormFactorFullSphere(1.0));
    ParticleCoreShell coreshell(shell, core);

    std::vector<const INode*> children = coreshell.getChildren();
    ASSERT_EQ(children.size(), 2u);

    // adding rotation and checking children again
    coreshell.setRotation(RotationZ(0.1));
    children = coreshell.getChildren();
    EXPECT_EQ(children.size(), 3u);
}
