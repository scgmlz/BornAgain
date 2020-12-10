#include "Sample/Particle/ParticleDistribution.h"
#include "Base/Const/Units.h"
#include "Param/Distrib/Distributions.h"
#include "Sample/HardParticle/FormFactorCone.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Particle/Particle.h"
#include "Tests/GTestWrapper/google_test.h"

class ParticleDistributionTest : public ::testing::Test {
protected:
    ~ParticleDistributionTest();
};

ParticleDistributionTest::~ParticleDistributionTest() = default;

TEST_F(ParticleDistributionTest, getChildren) {
    Particle particle(HomogeneousMaterial("Vacuum", 0.0, 0.0), FormFactorFullSphere(1.0));
    ParameterDistribution parameter("name", DistributionGate(1.0, 2.0), 5, 0.0, 1.0);
    ParticleDistribution distr(particle, parameter);

    std::vector<const INode*> children = distr.getChildren();

    EXPECT_EQ(children.size(), 2u);
}

TEST_F(ParticleDistributionTest, mainParameterUnits) {
    Material mat = HomogeneousMaterial("Vacuum", 0.0, 0.0);
    DistributionGate gate(1.0, 2.0);

    ParameterDistribution par("/Particle/FullSphere/Radius", gate, 5);
    ParticleDistribution distr(Particle(mat, FormFactorFullSphere(1.0)), par);
    EXPECT_EQ(distr.mainUnits(), "nm");

    par = ParameterDistribution("/Particle/Cone/Alpha", gate, 5);
    ParticleDistribution distr2(Particle(mat, FormFactorCone(10.0, 20.0, 70.0 * Units::deg)), par);
    EXPECT_EQ(distr2.mainUnits(), "rad");
}
