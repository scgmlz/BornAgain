#include "Core/Basics/MathConstants.h"
#include "Core/includeIncludes/HardParticles.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/Numeric/FormFactorTest.h"

//! Check that form factors are invariant when q is transformed according to particle symmetry.

class FFSymmetryTest : public testing::Test
{
private:
    using transform_t = std::function<cvector_t(const cvector_t&)>;

    void test_qq_eq(cvector_t q, IFormFactorBorn* p, transform_t trafo, double eps = 1e-12)
    {
        complex_t f0 = p->evaluate_for_q(q);
        complex_t f1 = p->evaluate_for_q(trafo(q));
        double avge = (std::abs(f0) + std::abs(f1)) / 2;
        EXPECT_NEAR(real(f0), real(f1), eps * avge) << "q=" << q;
        EXPECT_NEAR(imag(f0), imag(f1), eps * avge) << "q=" << q;
    }

protected:
    void run_test(IFormFactorBorn* p, transform_t trafo, double eps, double qmag1, double qmag2)
    {
        formFactorTest::run_test_for_many_q([&](cvector_t q) { test_qq_eq(q, p, trafo, eps); },
                                            qmag1, qmag2);
    }
};

//*********** polyhedra ***************

TEST_F(FFSymmetryTest, Prism3)
{
    FormFactorPrism3 p(.83, .45);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_TWOPI / 3); }, 1e-12, 1e-99,
        2e2);
}

TEST_F(FFSymmetryTest, Prism6)
{
    FormFactorPrism6 p(1.33, .42);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_PI / 3); }, 1e-12, 1e-99, 50);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(-M_TWOPI / 3); }, 3.8e-12,
        1e-99, 50);
}

TEST_F(FFSymmetryTest, Tetrahedron)
{
    FormFactorTetrahedron p(8.43, .25, .53);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_TWOPI / 3); }, 6e-12, 1e-99,
        2e2);
    // Linux: 3e-12, relaxed for Mac
}

TEST_F(FFSymmetryTest, Cone6_flat)
{
    // TODO for larger q, imag(ff) is nan
    FormFactorCone6 p(4.3, .09, .1);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(-M_PI / 3); }, 1e-11, 1e-99,
        50);
}

TEST_F(FFSymmetryTest, Cone6_steep)
{
    FormFactorCone6 p(.23, 3.5, .999 * M_PI / 2);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(-M_PI / 3); }, 1e-11, 1e-99,
        50);
}

//*********** spheroids ***************

TEST_F(FFSymmetryTest, HemiEllipsoid)
{
    FormFactorHemiEllipsoid p(.53, .78, 1.3);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return cvector_t(-q.x(), q.y(), q.z()); }, 1e-12,
        1e-99, 2e2);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return cvector_t(q.x(), -q.y(), q.z()); }, 1e-12,
        1e-99, 2e2);
}

TEST_F(FFSymmetryTest, TruncatedSphere)
{
    FormFactorTruncatedSphere p(.79, .34, 0);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_PI / 3.13698); }, 1e-10,
        1e-99, 2e2);
}

TEST_F(FFSymmetryTest, FullSpheroid)
{
    FormFactorFullSpheroid p(.73, .36);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(.123); }, 1e-12, 1e-99, 2e2);
}

// ****** TODO: tests that do not pass for the full q range *********
