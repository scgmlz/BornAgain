#include "Sample/Particle/ParticleComposition.h"
#include "Base/Math/Constants.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Scattering/Rotations.h"
#include "Tests/GTestWrapper/google_test.h"

class ParticleCompositionTest : public ::testing::Test {};

TEST_F(ParticleCompositionTest, ParticleCompositionDefaultConstructor) {
    std::unique_ptr<ParticleComposition> composition(new ParticleComposition());
    std::vector<kvector_t> positions;
    positions.push_back(kvector_t(0.0, 0.0, 0.0));
    EXPECT_EQ(0u, composition->nbrParticles());
}

TEST_F(ParticleCompositionTest, ParticleCompositionClone) {
    ParticleComposition composition;
    kvector_t position = kvector_t(1.0, 1.0, 1.0);
    Material material = HomogeneousMaterial("Vacuum", 0.0, 0.0);
    Particle particle(material);
    composition.addParticle(particle, position);

    std::unique_ptr<ParticleComposition> clone(composition.clone());
    std::vector<const INode*> children = clone->getChildren();
    EXPECT_EQ(children.size(), 1u);
    auto p_particle = dynamic_cast<const IParticle*>(children[0]);
    EXPECT_EQ(p_particle->rotation(), nullptr);
    EXPECT_EQ(p_particle->position(), position);
}

TEST_F(ParticleCompositionTest, getChildren) {
    Material material = HomogeneousMaterial("Vacuum", 0.0, 0.0);

    ParticleComposition composition;
    composition.addParticle(Particle(material, FormFactorFullSphere(1.0)));
    composition.addParticle(Particle(material, FormFactorFullSphere(1.0)));
    composition.setRotation(RotationY(45.));

    std::vector<const INode*> children = composition.getChildren();
    EXPECT_EQ(children.size(), 3u);
}
