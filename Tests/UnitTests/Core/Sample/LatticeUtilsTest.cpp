#include "Core/Lattice/LatticeUtils.h"
#include "Core/Lattice/ILatticeOrientation.h"
#include "Tests/GTestWrapper/google_test.h"

class LatticeUtilsTest : public ::testing::Test
{
};

// tests the creation of an FCC lattice with the primitive cube aligned along the q-axes
TEST_F(LatticeUtilsTest, cubeAlignedFCCTest)
{
    MillerIndexOrientation q_aligned(MillerIndexOrientation::QZ, {0, 0, 1},
                                     MillerIndexOrientation::QY, {0, 1, 0});
    auto lattice = LatticeUtils::CreateFCCLattice(2.0, q_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    kvector_t v1{0.0, 1.0, 1.0};
    kvector_t v2{1.0, 0.0, 1.0};
    kvector_t v3{1.0, 1.0, 0.0};

    EXPECT_EQ(a1, v1);
    EXPECT_EQ(a2, v2);
    EXPECT_EQ(a3, v3);
}

// tests the creation of an FCC lattice with the primitive cube aligned along Miller indices
TEST_F(LatticeUtilsTest, diagonalAlignedFCCTest)
{
    MillerIndexOrientation diagonal_aligned(MillerIndexOrientation::QZ, {1, 1, 1},
                                            MillerIndexOrientation::QX, {1, 1, 0});
    auto lattice = LatticeUtils::CreateFCCLattice(2.0, diagonal_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    EXPECT_NEAR(a1.z(), a2.z(), 1e-10);
    EXPECT_NEAR(a2.z(), a3.z(), 1e-10);
    EXPECT_NEAR(a1.x(), a2.x(), 1e-10);
    EXPECT_NEAR(a1.y(), -a2.y(), 1e-10);
}

// tests the creation of an HCP lattice with a trivial orientation
TEST_F(LatticeUtilsTest, trivialAlignedHCPTest)
{
    MillerIndexOrientation trivial_aligned(MillerIndexOrientation::QZ, {0, 0, 1},
                                           MillerIndexOrientation::QX, {2, -1, 0});
    auto lattice = LatticeUtils::CreateHCPLattice(2.0, 4.0, trivial_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    kvector_t v1{2.0, 0.0, 0.0};
    kvector_t v2{-1.0, std::sqrt(3.0), 0.0};
    kvector_t v3{1.0, 1.0 / std::sqrt(3.0), 2.0};

    EXPECT_EQ(a1, v1);
    EXPECT_EQ(a2, v2);
    EXPECT_EQ(a3, v3);
}

// tests the creation of an BCT lattice with the primitive tetragonal aligned along the q-axes
TEST_F(LatticeUtilsTest, tetraAlignedFCCTest)
{
    MillerIndexOrientation q_aligned(MillerIndexOrientation::QZ, {0, 0, 1},
                                     MillerIndexOrientation::QY, {0, 1, 0});
    auto lattice = LatticeUtils::CreateBCTLattice(2.0, 2.0, q_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    kvector_t v1{2.0, 0.0, 0.0};
    kvector_t v2{0.0, 2.0, 0.0};
    kvector_t v3{1.0, 1.0, 1.0};

    EXPECT_EQ(a1, v1);
    EXPECT_EQ(a2, v2);
    EXPECT_EQ(a3, v3);
}

// tests the creation of an BCT lattice with the primitive tetragonal aligned along Miller indices
TEST_F(LatticeUtilsTest, diagonalAlignedBCTTest)
{
    MillerIndexOrientation diagonal_aligned(MillerIndexOrientation::QZ, {1, 1, 1},
                                            MillerIndexOrientation::QX, {1, 1, 0});
    auto lattice = LatticeUtils::CreateBCTLattice(2.0, 2.0, diagonal_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    EXPECT_NEAR(a1.z(), a2.z(), 1e-10);
    EXPECT_NEAR(a1.x(), a2.x(), 1e-10);
    EXPECT_NEAR(a1.y(), -a2.y(), 1e-10);
    EXPECT_NEAR(a3.x(), 0.0, 1e-10);
    EXPECT_NEAR(a3.y(), 0.0, 1e-10);
    EXPECT_NEAR(a3.z(), std::sqrt(3.0), 1e-10);
}
