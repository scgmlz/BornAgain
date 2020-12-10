#include "Sample/Particle/ParticleCoreShell.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Sample/HardParticle/HardParticles.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Scattering/Rotations.h"
#include "Tests/GTestWrapper/google_test.h"

class ParticleCoreShellTest : public ::testing::Test {
protected:
    ParticleCoreShellTest();
    virtual ~ParticleCoreShellTest();

    ParticleCoreShell* m_coreshell;
};

ParticleCoreShellTest::ParticleCoreShellTest() : m_coreshell(nullptr) {
    Material mat = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);
    Particle core(mat);
    Particle shell(mat);
    kvector_t position;
    m_coreshell = new ParticleCoreShell(shell, core, position);
}

ParticleCoreShellTest::~ParticleCoreShellTest() {
    delete m_coreshell;
}

TEST_F(ParticleCoreShellTest, InitialState) {
    EXPECT_EQ(nullptr, m_coreshell->createFormFactor());
    EXPECT_EQ(nullptr, m_coreshell->rotation());
}

TEST_F(ParticleCoreShellTest, Clone) {
    ParticleCoreShell* p_clone = m_coreshell->clone();
    EXPECT_EQ(nullptr, p_clone->createFormFactor());
    EXPECT_EQ(nullptr, p_clone->rotation());
    delete p_clone;
}

TEST_F(ParticleCoreShellTest, ComplexCoreShellClone) {
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
    coreshell.setRotation(RotationY(90 * Units::deg));
    coreshell.setPosition(kvector_t(0, 0, -10));

    ParticleCoreShell* clone = coreshell.clone();
    EXPECT_EQ(coreshell.coreParticle()->position(), relative_pos);
    EXPECT_EQ(clone->coreParticle()->position(), relative_pos);
}

TEST_F(ParticleCoreShellTest, getChildren) {
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
