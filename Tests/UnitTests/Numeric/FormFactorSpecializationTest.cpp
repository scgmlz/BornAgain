#include "Core/includeIncludes/HardParticles.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/Numeric/FormFactorTest.h"

//! Compare form factor for particle shapes A and B, where A is given special
//! parameter values so that it coincides with the more symmetric B.

class FFSpecializationTest : public testing::Test
{
protected:
    void run_test(IFormFactorBorn* p0, IFormFactorBorn* p1, double eps, double qmag1, double qmag2)
    {
        formFactorTest::run_test_for_many_q([&](cvector_t q) { test_ff_eq(q, p0, p1, eps); }, qmag1,
                                            qmag2);
    }

private:
    void test_ff_eq(cvector_t q, IFormFactorBorn* p0, IFormFactorBorn* p1, double eps)
    {
        complex_t f0 = p0->evaluate_for_q(q);
        complex_t f1 = p1->evaluate_for_q(q);
        double avge = (std::abs(f0) + std::abs(f1)) / 2;
        EXPECT_NEAR(real(f0), real(f1), eps * avge) << "q=" << q;
        EXPECT_NEAR(imag(f0), imag(f1), eps * avge) << "q=" << q;
    }
};

const double eps_polyh = 7.5e-13;

TEST_F(FFSpecializationTest, TruncatedCubeAsBox)
{
    const double L = .5;
    FormFactorTruncatedCube p0(L, 0);
    FormFactorBox p1(L, L, L);
    run_test(&p0, &p1, eps_polyh, 1e-99, 5e2);
}

TEST_F(FFSpecializationTest, AnisoPyramidAsPyramid)
{
    const double L = 1.5, H = .24, alpha = .6;
    FormFactorAnisoPyramid p0(L, L, H, alpha);
    FormFactorPyramid p1(L, H, alpha);
    run_test(&p0, &p1, eps_polyh, 1e-99, 50);
}

TEST_F(FFSpecializationTest, Pyramid3AsPrism)
{
    const double L = 1.8, H = .3;
    FormFactorTetrahedron p0(L, H, M_PI / 2);
    FormFactorPrism3 p1(L, H);
    run_test(&p0, &p1, eps_polyh, 1e-99, 50);
}

TEST_F(FFSpecializationTest, PyramidAsBox)
{
    const double L = 1.8, H = .3;
    FormFactorPyramid p0(L, H, M_PI / 2);
    FormFactorBox p1(L, L, H);
    run_test(&p0, &p1, eps_polyh, 1e-99, 5e2);
}

TEST_F(FFSpecializationTest, Cone6AsPrism)
{
    const double L = .8, H = 1.13;
    FormFactorCone6 p0(L, H, M_PI / 2);
    FormFactorPrism6 p1(L, H);
    run_test(&p0, &p1, eps_polyh, 1e-99, 5e2);
}

//*********** spheroids ***************

TEST_F(FFSpecializationTest, HemiEllipsoidAsTruncatedSphere)
{
    const double R = 1.07;
    FormFactorHemiEllipsoid p0(R, R, R);
    FormFactorTruncatedSphere p1(R, R, 0);
    run_test(&p0, &p1, 1e-10, 1e-99, 5e2);
}

TEST_F(FFSpecializationTest, EllipsoidalCylinderAsCylinder)
{
    const double R = .8, H = 1.2;
    FormFactorEllipsoidalCylinder p0(R, R, H);
    FormFactorCylinder p1(R, H);
    run_test(&p0, &p1, 1e-11, 1e-99, 50);
}

TEST_F(FFSpecializationTest, TruncatedSphereAsSphere)
{
    const double R = 1.;
    FormFactorTruncatedSphere p0(R, 2 * R, 0);
    FormFactorFullSphere p1(R);
    run_test(&p0, &p1, 1e-11, .02, 5e1);
}

TEST_F(FFSpecializationTest, SpheroidAsSphere)
{
    const double R = 1.;
    FormFactorFullSpheroid p0(R, 2 * R);
    FormFactorFullSphere p1(R);
    run_test(&p0, &p1, 1e-12, 1e-99, 50);
}
