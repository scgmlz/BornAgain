#ifndef LATTICETEST_H
#define LATTICETEST_H

#include "Lattice.h"
#include "google_test.h"
#include "MathConstants.h"
#include "Transform3D.h"

class LatticeTest : public ::testing::Test
{
 protected:
    LatticeTest(){}
    virtual ~LatticeTest(){}
};


// tests the declaration of Lattice object, copy constructor and the getBasisVector_() functions
TEST_F(LatticeTest, declarationTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);

    Lattice l1(a1, a2, a3);
    EXPECT_EQ(a1, l1.getBasisVectorA());
    EXPECT_EQ(a2, l1.getBasisVectorB());
    EXPECT_EQ(a3, l1.getBasisVectorC());

    Lattice l2(l1);
    EXPECT_EQ(a1, l2.getBasisVectorA());
    EXPECT_EQ(a2, l2.getBasisVectorB());
    EXPECT_EQ(a3, l2.getBasisVectorC());

    // calls and tests copy constructor
    Lattice l3 = Lattice(l2);
    EXPECT_EQ(a1, l3.getBasisVectorA());
    EXPECT_EQ(a2, l3.getBasisVectorB());
    EXPECT_EQ(a3, l3.getBasisVectorC());

    // calls and tests copy constructor
    Lattice l4 = l3;
    EXPECT_EQ(a1, l4.getBasisVectorA());
    EXPECT_EQ(a2, l4.getBasisVectorB());
    EXPECT_EQ(a3, l4.getBasisVectorC());
}


// tests volume of the unit cell
TEST_F(LatticeTest, volumeTest)
{
    kvector_t a1(4,0,0), a2(0,2.1,0), a3(0,0,1);

    Lattice l1(a1, a2, a3);
    EXPECT_EQ(8.4, l1.volume()); // 8.4 is the expected volume for the given lattice vectors
}


// tests whether reciprocal lattice basis vectors have been initialized or not
TEST_F(LatticeTest, reciprocalTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    kvector_t b1, b2, b3, m_ra, m_rb, m_rc;

    // computing expected reciprocal lattice vectors
    kvector_t a23 = a2.cross(a3);
    kvector_t a31 = a3.cross(a1);
    kvector_t a12 = a1.cross(a2);
    m_ra = M_TWOPI/a1.dot(a23)*a23;
    m_rb = M_TWOPI/a2.dot(a31)*a31;
    m_rc = M_TWOPI/a3.dot(a12)*a12;

    l1.initialize();
    l1.getReciprocalLatticeBasis(b1, b2, b3);
    EXPECT_EQ(m_ra, b1);
    EXPECT_EQ(m_rb, b2);
    EXPECT_EQ(m_rc, b3);
}


// tests whether Lattice has been transformed correctly
TEST_F(LatticeTest, transformTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    // use rotation by 90 degrees around z axis as a transformation
    Transform3D tr = Transform3D::createRotateZ(M_TWOPI/4);
    Lattice ltr = l1.createTransformedLattice(tr);

    // use EXPECT_NEAR as transform (matrix multiplication) uses double value for rotation angle
    // e.g. Rotating the vector (1,0,0) by 2*PI about z would give something like (0.99999,0,0)
    EXPECT_NEAR(a2.x(), ltr.getBasisVectorA().x(), 1e-12);
    EXPECT_NEAR(a2.y(), ltr.getBasisVectorA().y(), 1e-12);
    EXPECT_NEAR(a2.z(), ltr.getBasisVectorA().z(), 1e-12);
    EXPECT_NEAR(-a1.x(), ltr.getBasisVectorB().x(), 1e-12);
    EXPECT_NEAR(-a1.y(), ltr.getBasisVectorB().y(), 1e-12);
    EXPECT_NEAR(-a1.z(), ltr.getBasisVectorB().z(), 1e-12);
    EXPECT_EQ(a3, ltr.getBasisVectorC());
}


// REAL = real/physical
// tests the nearest REAL LATTICE point to a given REAL SPACE vector
TEST_F(LatticeTest, NearestRealLatticeVectorCoordinatesTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    // vector_in is in REAL SPACE coordinates
    kvector_t vector_in(3.01,1.51,1.49);

    // point_expected is in REAL LATTICE coordinates
    ivector_t point_expected(3,2,1);

    EXPECT_EQ(point_expected, l1.getNearestLatticeVectorCoordinates(vector_in));
}


// REC. = reciprocal
// tests the nearest REC. LATTICE point to a given REC. SPACE vector
TEST_F(LatticeTest, NearestReciprocalLatticeVectorCoordinatesTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    // vector_in is in REC. SPACE coordinates
    kvector_t vector_in(2.8*M_TWOPI,0,0);

    // point_expected is in REC. LATTICE coordinates
    ivector_t point_expected(3,0,0);

    EXPECT_EQ(point_expected, l1.getNearestReciprocalLatticeVectorCoordinates(vector_in));
}


// tests the list of REC. LATTICE vectors (in REC. SPACE coords) computed within a specified
// radius of a given REC. SPACE vector
TEST_F(LatticeTest, reciprocalLatticeVectorsWithinRadiusTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    kvector_t b1, b2, b3;
    l1.getReciprocalLatticeBasis(b1, b2, b3);

    // vector_in is in REC. SPACE coordinates
    kvector_t vector_in(2.5*M_TWOPI,0,0);

    // list of REC. LATTICE vectors expected within given radius
    std::vector<kvector_t> vectors_expected;
    kvector_t expected_1 = 2*b1;
    kvector_t expected_2 = 3*b1;

    vectors_expected.push_back(expected_1);
    vectors_expected.push_back(expected_2);

    EXPECT_EQ(vectors_expected, l1.reciprocalLatticeVectorsWithinRadius(vector_in, M_TWOPI));

    EXPECT_EQ(vectors_expected, l1.reciprocalLatticeVectorsWithinRadius(vector_in, M_TWOPI-0.1));
}


// tests FCC lattice creation
TEST_F(LatticeTest, FCCLatticeTest)
{
    // creates FCC lattice onto a new Lattice instance l1
    Lattice l1 = Lattice::createFCCLattice(1);

    kvector_t fcc1(0,0.5,0.5), fcc2(0.5,0,0.5), fcc3(0.5,0.5,0);

    EXPECT_EQ(fcc1, l1.getBasisVectorA());
    EXPECT_EQ(fcc2, l1.getBasisVectorB());
    EXPECT_EQ(fcc3, l1.getBasisVectorC());
}


// tests trigonal lattice creation
TEST_F(LatticeTest, TrigonalLatticeTest)
{
    Lattice l1 = Lattice::createTrigonalLattice(1,4);

    kvector_t tri1(1, 0.0, 0.0);
    kvector_t tri2(-1/2.0, std::sqrt(3.0)*1/2.0, 0);
    kvector_t tri3(0.0, 0.0, 4);

    EXPECT_EQ(tri1, l1.getBasisVectorA());
    EXPECT_EQ(tri2, l1.getBasisVectorB());
    EXPECT_EQ(tri3, l1.getBasisVectorC());
}


// tests whether basis and reciprocal vectors are returned correctly when the basis
// vectors are manually changed using the setVectorValue method
TEST_F(LatticeTest, onChangeTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    kvector_t b1, b2, b3, m_ra, m_rb, m_rc;

    // computing expected reciprocal lattice vectors
    kvector_t a23 = a2.cross(a3);
    kvector_t a31 = a3.cross(a1);
    kvector_t a12 = a1.cross(a2);
    m_ra = M_TWOPI/a1.dot(a23)*a23;
    m_rb = M_TWOPI/a2.dot(a31)*a31;
    m_rc = M_TWOPI/a3.dot(a12)*a12;

    //l1.initialize();
    l1.getReciprocalLatticeBasis(b1, b2, b3);
    EXPECT_EQ(m_ra, b1);
    EXPECT_EQ(m_rb, b2);
    EXPECT_EQ(m_rc, b3);

    // The new changed lattice vectors
    kvector_t c1(2,0,0), c2(0,2,0), c3(0,0,2);

    l1.setVectorValue(BornAgain::BasisVector_A, c1);
    l1.setVectorValue(BornAgain::BasisVector_B, c2);
    l1.setVectorValue(BornAgain::BasisVector_C, c3);
    EXPECT_EQ(c1, l1.getBasisVectorA());
    EXPECT_EQ(c2, l1.getBasisVectorB());
    EXPECT_EQ(c3, l1.getBasisVectorC());

    kvector_t d1, d2, d3, mc_ra, mc_rb, mc_rc;

    // computing the expected changed reciprocal lattice vectors
    kvector_t c23 = c2.cross(c3);
    kvector_t c31 = c3.cross(c1);
    kvector_t c12 = c1.cross(c2);
    mc_ra = M_TWOPI/c1.dot(c23)*c23;
    mc_rb = M_TWOPI/c2.dot(c31)*c31;
    mc_rc = M_TWOPI/c3.dot(c12)*c12;

    l1.getReciprocalLatticeBasis(d1, d2, d3);
    EXPECT_EQ(mc_ra, d1);
    EXPECT_EQ(mc_rb, d2);
    EXPECT_EQ(mc_rc, d3);
}

#endif // LATTICETEST_H
