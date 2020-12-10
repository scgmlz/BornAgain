#include "Sample/Particle/Crystal.h"
#include "Sample/Lattice/BakeLattice.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Tests/GTestWrapper/google_test.h"

class CrystalTest : public ::testing::Test {};

TEST_F(CrystalTest, getChildren) {
    Lattice3D lattice = bake::HexagonalLattice(1.0, 2.0);
    ParticleComposition composition;
    Crystal crystal(composition, lattice);

    std::vector<const INode*> children = crystal.getChildren();
    ASSERT_EQ(children.size(), 2u);
}
