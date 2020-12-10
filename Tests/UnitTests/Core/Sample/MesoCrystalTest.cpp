#include "Sample/Particle/MesoCrystal.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/Lattice/BakeLattice.h"
#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/Scattering/Rotations.h"
#include "Tests/GTestWrapper/google_test.h"

class MesoCrystalTest : public ::testing::Test {};

TEST_F(MesoCrystalTest, getChildren) {
    Lattice3D lattice = bake::HexagonalLattice(1.0, 2.0);
    ParticleComposition composition;
    Crystal crystal(composition, lattice);
    MesoCrystal meso(crystal, FormFactorFullSphere(1.0));

    std::vector<const INode*> children = meso.getChildren();
    EXPECT_EQ(children.size(), 2u);

    // children when rotation is set
    meso.setRotation(RotationY(45.));
    children = meso.getChildren();
    EXPECT_EQ(children.size(), 3u);
}
