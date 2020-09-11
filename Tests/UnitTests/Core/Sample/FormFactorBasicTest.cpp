#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Scattering/IFormFactorBorn.h"
#include "Core/Scattering/Rotations.h"
#include "Core/includeIncludes/HardParticles.h"
#include "Tests/GTestWrapper/google_test.h"

class FormFactorBasicTest : public ::testing::Test
{
protected:
    void test_eps_q(const IFormFactorBorn* p, cvector_t qdir, double eps)
    {
        cvector_t q = eps * qdir;
        complex_t ff = p->evaluate_for_q(q);
        // std::cout<<"q="<<q<<" -> "<<std::setprecision(16)<<" ff0="<<V<<", ff ="<<ff<<"\n";
        EXPECT_LE(real(ff), V * (1 + 4e-16));
        if (R * R * R < V / 20 || R * R * R > 20 * V)
            // very excentric shape, the following tests cannot be expected to pass
            return;
        EXPECT_GT(real(ff), V * (1 - std::max(3e-16, 2 * eps * R * eps * R)));
        EXPECT_LT(std::abs(imag(ff)), 2 * eps * V * R);
    }
    void test_small_q(const IFormFactorBorn* p, complex_t x, complex_t y, complex_t z)
    {
        cvector_t q(x, y, z);
        test_eps_q(p, q, 1e-14);
        test_eps_q(p, q, 1e-11);
        test_eps_q(p, q, 1e-8);
        test_eps_q(p, q, 1e-5);
    }
    void test_ff(const IFormFactorBorn* p)
    {
        complex_t ff0 = p->evaluate_for_q(cvector_t(0., 0., 0.));
        EXPECT_EQ(imag(ff0), 0.);
        V = real(ff0);
        EXPECT_NEAR(p->volume(), V, 3e-16 * V);

        R = p->radialExtension();
        if (R * R * R < V / 20 || R * R * R > 20 * V) {
            std::cerr << "WARNING: very elongated particle, or wrong radius; some tests disabled\n";
            std::cerr << std::setprecision(16) << "  V  =" << V << "\n  R^3=" << R * R * R << "\n";
        }

        test_small_q(p, 1, 0, 0);
        test_small_q(p, -1, 0, 0);
        test_small_q(p, 0, 1, 0);
        test_small_q(p, 0, -1, 0);
        test_small_q(p, 0, 0, 1);
        test_small_q(p, 0, 0, -1);
        test_small_q(p, 1, 1, 0);
        test_small_q(p, 0, 1, 1);
        test_small_q(p, 1, 0, 1);
        test_small_q(p, 1, -1, 0);
        test_small_q(p, 0, 1, -1);
        test_small_q(p, -1, 0, 1);
        test_small_q(p, 1, 1, 1);
        test_small_q(p, .7, .8, .9);

        IFormFactorBorn* clone = p->clone();
        EXPECT_EQ(clone->volume(), V);
        cvector_t q(.1, .2, complex_t(.3, .004));
        EXPECT_EQ(clone->evaluate_for_q(q), p->evaluate_for_q(q));
    }
    double V, R;
};

TEST_F(FormFactorBasicTest, AnisoPyramid)
{
    double length = 12.;
    double height = 5.;
    double width = 14.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double volume = height
                    * (length * width - (length + width) * height / tga
                       + 4.0 / 3.0 * height * height / (tga * tga));

    FormFactorAnisoPyramid particle(length, width, height, alpha);
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(length, particle.getLength());
    EXPECT_EQ(width, particle.getWidth());
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(alpha, particle.getAlpha());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, HemiEllipsoid)
{
    double radiusx = 6.;
    double radiusy = 7.;
    double height = 5.;

    double volume = M_TWOPI * radiusx * radiusy * height / 3.;

    FormFactorHemiEllipsoid particle(radiusx, radiusy, height);
    EXPECT_EQ(radiusx, particle.getRadiusX());
    EXPECT_EQ(radiusy, particle.getRadiusY());
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_DOUBLE_EQ(volume, particle.volume());

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Box)
{
    double length = 6.;
    double height = 5.;
    double width = 7.;
    double volume = length * height * width;

    FormFactorBox particle(length, width, height);
    EXPECT_EQ(width, particle.getWidth());
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(3., particle.radialExtension());
    EXPECT_DOUBLE_EQ(volume, particle.volume());

    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    EXPECT_EQ(0., particle.bottomZ(RotationZ(17 * Units::degree)));
    EXPECT_EQ(height, particle.topZ(RotationZ(39 * Units::degree)));

    EXPECT_NEAR(-width / 2, particle.bottomZ(RotationX(90 * Units::degree)), 1e-12);
    EXPECT_NEAR(-length / 2, particle.bottomZ(RotationY(90 * Units::degree)), 1e-12);

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Cone)
{
    double radius = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = height / tga / radius;
    double volume = M_PI / 3. * tga * radius * radius * radius
                    * (1. - (1. - HdivRtga) * (1. - HdivRtga) * (1. - HdivRtga));

    FormFactorCone particle(radius, height, alpha);
    EXPECT_EQ(radius, particle.getRadius());
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(alpha, particle.getAlpha());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Cone6)
{
    double base_edge = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = 2. * height / tga / base_edge / std::sqrt(3.);
    double volume = 3. / 4. * tga * base_edge * base_edge * base_edge
                    * (1. - (1. - HdivRtga) * (1. - HdivRtga) * (1. - HdivRtga));

    FormFactorCone6 particle(base_edge, height, alpha);
    EXPECT_EQ(base_edge, particle.getBaseEdge());
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(alpha, particle.getAlpha());
    EXPECT_DOUBLE_EQ(volume, particle.volume());

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Cuboctahedron)
{
    double length = 10.;
    double height = 4;
    double height_ratio = .7;
    double alpha = 0.8;

    double tga = std::tan(alpha);
    double H2divLtga = height * 2. / length / tga;
    double ratioH2divLtga = height_ratio * height * 2. / length / tga;
    double volume = 1. / 6. * tga * length * length * length
                    * (2. - (1. - H2divLtga) * (1. - H2divLtga) * (1. - H2divLtga)
                       - (1. - ratioH2divLtga) * (1. - ratioH2divLtga) * (1. - ratioH2divLtga));

    FormFactorCuboctahedron particle(length, height, height_ratio, alpha);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(length, particle.getLength());
    EXPECT_EQ(height_ratio, particle.getHeightRatio());
    EXPECT_EQ(alpha, particle.getAlpha());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height * (1 + height_ratio), particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Cylinder)
{
    double radius = 3.;
    double height = 5.;
    double volume = M_PI * radius * radius * height;

    FormFactorCylinder particle(radius, height);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(radius, particle.getRadius());
    EXPECT_DOUBLE_EQ(volume, particle.volume());

    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    EXPECT_NEAR(-radius, particle.bottomZ(RotationX(90 * Units::degree)), 1e-13);
    EXPECT_NEAR(+radius, particle.topZ(RotationX(90 * Units::degree)), 1e-13);
    EXPECT_NEAR(-radius, particle.bottomZ(RotationY(90 * Units::degree)), 1e-13);
    EXPECT_NEAR(+radius, particle.topZ(RotationY(90 * Units::degree)), 1e-13);

    EXPECT_NEAR(-height, particle.bottomZ(RotationY(180 * Units::degree)), 1e-13);
    EXPECT_NEAR(0, particle.topZ(RotationY(180 * Units::degree)), 1e-13);

    for (double gamma : {1.123, -2.34, 7.5, -9.})
        // 7.5deg is worst case for 24-vertex circle
        EXPECT_NEAR(-radius,
                    particle.bottomZ(RotationEuler(0, 90 * Units::degree, gamma * Units::degree)),
                    3e-2); // TODO decrease epsilon after replacement of vertex-based approximation

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Dodecahedron)
{
    double edge = 3.;
    double volume = (15 + 7 * sqrt(5)) / 4 * pow(edge, 3);

    FormFactorDodecahedron particle(edge);
    EXPECT_EQ(edge, particle.getEdge());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_NEAR(2 * 1.11352 * edge, particle.topZ(RotationZ(.42)), 1e-4);
    // height=2*inradius from web ressource

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, EllipsoidalCylinder)
{
    double radiusx = 3.;
    double radiusy = 5.;
    double height = 4;
    double volume = M_PI * radiusx * radiusy * height;

    FormFactorEllipsoidalCylinder particle(radiusx, radiusy, height);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(radiusx, particle.getRadiusX());
    EXPECT_EQ(radiusy, particle.getRadiusY());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, CantellatedCube)
{
    double L = 10.;
    double t = 2.; // side length of removed trirectangular tetrahedron at each vertex
    double volume = L * L * L - 6 * L * t * t + 16 * t * t * t / 3;

    FormFactorCantellatedCube particle(L, t);

    EXPECT_EQ(L, particle.getLength());
    EXPECT_DOUBLE_EQ(t, particle.getRemovedLength());
    EXPECT_DOUBLE_EQ(particle.volume(), volume);
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(L, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, FullSphere)
{
    double radius = 5.;
    double volume = 4. / 3. * M_PI * radius * radius * radius;

    FormFactorFullSphere particle(radius);
    EXPECT_EQ(radius, particle.getRadius());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(2 * radius, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, FullSpheroid)
{
    double radius = 3.;
    double height = 5.;
    double volume = 2. / 3. * M_PI * radius * radius * height;

    FormFactorFullSpheroid particle(radius, height);
    EXPECT_EQ(radius, particle.getRadius());
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Icosahedron)
{
    double edge = 7.;
    double volume = 5 * (3 + sqrt(5)) / 12 * pow(edge, 3);

    FormFactorIcosahedron particle(edge);
    EXPECT_EQ(edge, particle.getEdge());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_NEAR(2 * 0.755761 * edge, particle.topZ(RotationZ(.42)), 1e-4);
    // height=2*inradius from web ressource

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Prism3)
{
    double height = 4.;
    double base_edge = 6.;
    double volume = sqrt(3.) / 4. * height * base_edge * base_edge;

    FormFactorPrism3 particle(base_edge, height);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(base_edge, particle.getBaseEdge());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Prism6)
{
    double height = 4.;
    double base_edge = 3.;
    double volume = 3. * sqrt(3.) / 2. * height * base_edge * base_edge;

    FormFactorPrism6 particle(base_edge, height);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(base_edge, particle.getBaseEdge());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Pyramid)
{
    double height = 4.;
    double base_edge = 10.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double H2divLtga = height * 2. / base_edge / tga;
    double volume = 1. / 6. * tga * base_edge * base_edge * base_edge
                    * (1. - (1. - H2divLtga) * (1. - H2divLtga) * (1. - H2divLtga));

    FormFactorPyramid particle(base_edge, height, alpha);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(base_edge, particle.getBaseEdge());
    EXPECT_EQ(alpha, particle.getAlpha());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, TruncatedSphere)
{
    double radius = 5.;
    double height = 3.;
    double HdivR = height / radius;
    double volume = M_PI / 3. * radius * radius * radius
                    * (3. * HdivR - 1. - (HdivR - 1.) * (HdivR - 1.) * (HdivR - 1.));

    FormFactorTruncatedSphere particle(radius, height, 0);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, TruncatedSpheroid)
{
    double radius = 3.;
    double height = 5.;
    double flattening = 1.5;
    double volume =
        M_PI * radius * height * height / flattening * (1. - height / (3. * flattening * radius));

    FormFactorTruncatedSpheroid particle(radius, height, flattening, 0);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(radius, particle.getRadius());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, Tetrahedron)
{
    double base_edge = 16.;
    double height = 4.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double sqrt3H2divLtga = std::sqrt(3.) * 2. * height / base_edge / tga;
    double volume = tga / 24. * base_edge * base_edge * base_edge
                    * (1. - (1. - sqrt3H2divLtga) * (1. - sqrt3H2divLtga) * (1. - sqrt3H2divLtga));

    FormFactorTetrahedron particle(base_edge, height, alpha);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(base_edge, particle.getBaseEdge());
    EXPECT_EQ(alpha, particle.getAlpha());
    EXPECT_DOUBLE_EQ(volume, particle.volume());

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, CosineRippleBox)
{
    double width = 20.;
    double height = 4.;
    double length = 100.0;
    double volume = 0.5 * height * width * length;

    FormFactorCosineRippleBox particle(length, width, height);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_EQ(width, particle.getWidth());
    EXPECT_EQ(length, particle.getLength());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, TruncatedCube)
{
    double length = 15.;
    double t = 6.; // side length of removed trirectangular tetrahedron at each vertex
    double volume = length * length * length - 4. / 3. * t * t * t;

    FormFactorTruncatedCube particle(length, t);
    EXPECT_EQ(length, particle.getLength());
    EXPECT_DOUBLE_EQ(t, particle.getRemovedLength());
    EXPECT_DOUBLE_EQ(particle.volume(), volume);
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(length, particle.topZ(RotationZ(.42)));

    test_ff(&particle);
}

TEST_F(FormFactorBasicTest, SawtoothRippleBox)
{
    double width = 20.;
    double height = 4.;
    double length = 100.0;
    double d = 0.3; // asymmetry
    double volume = 0.5 * height * width * length;

    FormFactorSawtoothRippleBox particle(length, width, height, d);
    EXPECT_EQ(height, particle.getHeight());
    EXPECT_DOUBLE_EQ(volume, particle.volume());
    EXPECT_EQ(0., particle.bottomZ(RotationZ(.42)));
    EXPECT_EQ(height, particle.topZ(RotationZ(.42)));

    // test_ff( &particle ); WAITING: restore once getRadius returns the umkreis radius
}
