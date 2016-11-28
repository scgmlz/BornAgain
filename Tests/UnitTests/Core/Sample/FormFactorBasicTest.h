// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/UnitTests/Core/1/FormFactorBasicTest.h
//! @brief     Trvial and basic unit tests for particle-shape form factors.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MathConstants.h"
#include "BornAgainNamespace.h"
#include "IFormFactorBorn.h"
#include "HardParticles.h"

class FormFactorBasicTest : public ::testing::Test
{
protected:
    FormFactorBasicTest() {}
    void test_eps_q( const IFormFactorBorn* p, const cvector_t qdir, double eps )
    {
        cvector_t q = eps*qdir;
        complex_t ff = p->evaluate_for_q( q );
        //std::cout<<"q="<<q<<" -> "<<std::setprecision(16)<<" ff0="<<V<<", ff ="<<ff<<"\n";
        EXPECT_LE( real(ff), V*(1+4e-16) );
        if ( R*R*R<V/20 || R*R*R>20*V )
            // very excentric shape, the following tests cannot be expected to pass
            return;
        EXPECT_GT( real(ff), V*(1-std::max(3e-16,2*eps*R*eps*R)) );
        EXPECT_LT( std::abs(imag(ff)), 2*eps*V*R );
    }
    void test_small_q( const IFormFactorBorn* p, complex_t x, complex_t y, complex_t z )
    {
        cvector_t q(x, y, z);
        test_eps_q( p, q, 1e-14 );
        test_eps_q( p, q, 1e-11 );
        test_eps_q( p, q, 1e-8 );
        test_eps_q( p, q, 1e-5 );
    }
    void test_ff( const IFormFactorBorn* p )
    {
        complex_t ff0 = p->evaluate_for_q( cvector_t(0.,0.,0.) );
        EXPECT_EQ( imag(ff0), 0. );
        V = real(ff0);
        EXPECT_NEAR( p->getVolume(), V, 3e-16*V );

        R = p->getRadialExtension();
        if ( R*R*R<V/20 || R*R*R>20*V ) {
            std::cerr<<"WARNING: very elongated particle, or wrong radius; some tests disabled\n";
            std::cerr<<std::setprecision(16)<<"  V  ="<<V<<"\n  R^3="<<R*R*R<<"\n";
        }

        test_small_q( p,  1, 0, 0 );
        test_small_q( p, -1, 0, 0 );
        test_small_q( p,  0, 1, 0 );
        test_small_q( p,  0,-1, 0 );
        test_small_q( p,  0, 0, 1 );
        test_small_q( p,  0, 0,-1 );
        test_small_q( p,  1, 1, 0 );
        test_small_q( p,  0, 1, 1 );
        test_small_q( p,  1, 0, 1 );
        test_small_q( p,  1,-1, 0 );
        test_small_q( p,  0, 1,-1 );
        test_small_q( p, -1, 0, 1 );
        test_small_q( p,  1, 1, 1 );
        test_small_q( p, .7,.8,.9 );

        IFormFactorBorn* clone = p->clone();
        EXPECT_EQ(clone->getName(), p->getName());
        EXPECT_EQ(clone->getVolume(), V);
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
    double volume = height*
        (length*width - (length + width)*height/tga + 4.0/3.0*height*height/(tga*tga));

    FormFactorAnisoPyramid anisopyramid(length, width, height, alpha);

    EXPECT_EQ(BornAgain::FFAnisoPyramidType, anisopyramid.getName());
    EXPECT_DOUBLE_EQ(volume, anisopyramid.getVolume());
    EXPECT_EQ(12., anisopyramid.getLength());
    EXPECT_EQ(14., anisopyramid.getWidth());
    EXPECT_EQ(5., anisopyramid.getHeight());
    EXPECT_EQ(0.8, anisopyramid.getAlpha());

    test_ff( &anisopyramid );
}

TEST_F(FormFactorBasicTest, HemiEllipsoid)
{
    double radius_a = 6.;
    double radius_b = 7.;
    double height = 5.;

    double volume = M_TWOPI*radius_a*radius_b*height/3.;

    FormFactorHemiEllipsoid hemiellipsoid(radius_a, radius_b, height);

    EXPECT_EQ(BornAgain::FFHemiEllipsoidType, hemiellipsoid.getName());
    EXPECT_EQ(6., hemiellipsoid.getRadiusX());
    EXPECT_EQ(7., hemiellipsoid.getRadiusY());
    EXPECT_EQ(5., hemiellipsoid.getHeight());
    EXPECT_DOUBLE_EQ(volume, hemiellipsoid.getVolume());

    test_ff( &hemiellipsoid );
}

TEST_F(FormFactorBasicTest, Box)
{
    double length = 6.;
    double height = 5.;
    double width = 7.;
    double volume = length*height*width;

    FormFactorBox box(length, width, height);

    EXPECT_EQ(BornAgain::FFBoxType, box.getName());
    EXPECT_EQ(7., box.getWidth());
    EXPECT_EQ(5., box.getHeight());
    EXPECT_EQ(3., box.getRadialExtension());
    EXPECT_DOUBLE_EQ(volume, box.getVolume());

    test_ff( &box );
}

TEST_F(FormFactorBasicTest, Cone)
{
    double radius = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = height/tga/radius;
    double volume = M_PI/3.*tga*radius*radius*radius*
            (1. - (1.- HdivRtga)*(1.- HdivRtga)*(1.- HdivRtga));

    FormFactorCone cone(radius, height, alpha);

    EXPECT_EQ(BornAgain::FFConeType, cone.getName());
    EXPECT_EQ(6., cone.getRadius());
    EXPECT_EQ(5., cone.getHeight());
    EXPECT_EQ(0.8, cone.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cone.getVolume());

    test_ff( &cone );
}

TEST_F(FormFactorBasicTest, Cone6)
{
    double base_edge = 6.;
    double height = 5.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double HdivRtga = 2.*height/tga/base_edge/std::sqrt(3.);
    double volume = 3./4.*tga*base_edge*base_edge*base_edge*
            (1. - (1.- HdivRtga)*(1.- HdivRtga)*(1.- HdivRtga));

    FormFactorCone6 cone6(base_edge, height, alpha);

    EXPECT_EQ(BornAgain::FFCone6Type, cone6.getName());
    EXPECT_EQ(6., cone6.getBaseEdge());
    EXPECT_EQ(5., cone6.getHeight());
    EXPECT_EQ(0.8, cone6.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cone6.getVolume());

    test_ff( &cone6 );
}

TEST_F(FormFactorBasicTest, Cuboctahedron)
{
    double length = 10.;
    double height = 4;
    double height_ratio = 1.;
    double alpha = 0.8;

    double tga = std::tan(alpha);
    double H2divLtga = height*2./length/tga;
    double ratioH2divLtga = height_ratio*height*2./length/tga;
    double volume = 1./6.*tga*length*length*length*
        ( 2. - (1. - H2divLtga)*(1. - H2divLtga)*(1. - H2divLtga)
          - (1. - ratioH2divLtga)*(1. - ratioH2divLtga)*(1. - ratioH2divLtga));

    FormFactorCuboctahedron cuboctahedron(length, height, height_ratio, alpha);

    EXPECT_EQ(BornAgain::FFCuboctahedronType, cuboctahedron.getName());
    EXPECT_EQ(4., cuboctahedron.getHeight());
    EXPECT_EQ(10., cuboctahedron.getLength());
    EXPECT_EQ(1., cuboctahedron.getHeightRatio());
    EXPECT_EQ(0.8, cuboctahedron.getAlpha());
    EXPECT_DOUBLE_EQ(volume, cuboctahedron.getVolume());

    test_ff( &cuboctahedron );
}

TEST_F(FormFactorBasicTest, Cylinder)
{
    double radius = 3.;
    double height = 5.;
    double volume = M_PI*radius*radius*height;

    FormFactorCylinder cylinder(radius,height);

    EXPECT_EQ(BornAgain::FFCylinderType, cylinder.getName());
    EXPECT_EQ(5., cylinder.getHeight());
    EXPECT_EQ(3., cylinder.getRadius());
    EXPECT_DOUBLE_EQ(volume, cylinder.getVolume());

    test_ff( &cylinder );
}

TEST_F(FormFactorBasicTest, Dodecahedron)
{
    double edge = 3.;
    double volume = (15+7*sqrt(5))/4*pow(edge,3);

    FormFactorDodecahedron dodecahedron(edge);
    EXPECT_EQ(BornAgain::FFDodecahedronType, dodecahedron.getName());
    EXPECT_EQ(edge, dodecahedron.getEdge());
    EXPECT_DOUBLE_EQ(volume, dodecahedron.getVolume());

    test_ff( &dodecahedron );
}

TEST_F(FormFactorBasicTest, EllipsoidalCylinder)
{
    double radius_a = 3.;
    double radius_b = 5.;
    double height = 4;
    double volume = M_PI*radius_a*radius_b*height;

    FormFactorEllipsoidalCylinder ellipscyl(radius_a, radius_b, height);

    EXPECT_EQ(BornAgain::FFEllipsoidalCylinderType, ellipscyl.getName());
    EXPECT_EQ(4., ellipscyl.getHeight());
    EXPECT_EQ(3., ellipscyl.getRadiusX());
    EXPECT_EQ(5., ellipscyl.getRadiusY());
    EXPECT_DOUBLE_EQ(volume, ellipscyl.getVolume());

    test_ff( &ellipscyl );
}

TEST_F(FormFactorBasicTest, FullSphere)
{
    double radius = 5.;
    double volume = 4./3.*M_PI*radius*radius*radius;

    FormFactorFullSphere fullsphere(radius);
    EXPECT_EQ(BornAgain::FFFullSphereType, fullsphere.getName());
    EXPECT_EQ(5., fullsphere.getRadius());
    EXPECT_DOUBLE_EQ(volume, fullsphere.getVolume());

    test_ff( &fullsphere );
}

TEST_F(FormFactorBasicTest, FullSpheroid)
{
    double radius = 3.;
    double height = 5.;
    double volume = 2./3.*M_PI*radius*radius*height;

    FormFactorFullSpheroid fullspheroid(radius,height);

    EXPECT_EQ(BornAgain::FFFullSpheroidType, fullspheroid.getName());
    EXPECT_EQ(3., fullspheroid.getRadius());
    EXPECT_EQ(5., fullspheroid.getHeight());
    EXPECT_DOUBLE_EQ(volume, fullspheroid.getVolume());

    test_ff( &fullspheroid );
}

TEST_F(FormFactorBasicTest, Icosahedron)
{
    double edge = 7.;
    double volume = 5*(3+sqrt(5))/12*pow(edge,3);

    FormFactorIcosahedron icosahedron(edge);

    EXPECT_EQ(BornAgain::FFIcosahedronType, icosahedron.getName());
    EXPECT_EQ(edge, icosahedron.getEdge());
    EXPECT_DOUBLE_EQ(volume, icosahedron.getVolume());

    test_ff( &icosahedron );
}

TEST_F(FormFactorBasicTest, Prism3)
{
    double height = 4.;
    double base_edge = 6.;
    double volume = sqrt(3.)/4.*height*base_edge*base_edge;

    FormFactorPrism3 prism3(base_edge, height);

    EXPECT_EQ(BornAgain::FFPrism3Type, prism3.getName());
    EXPECT_EQ(4., prism3.getHeight());
    EXPECT_EQ(6., prism3.getBaseEdge());
    EXPECT_DOUBLE_EQ(volume, prism3.getVolume());

    test_ff( &prism3 );
}

TEST_F(FormFactorBasicTest, Prism6)
{
    double height = 4.;
    double base_edge = 3.;
    double volume = 3.*sqrt(3.)/2.*height*base_edge*base_edge;

    FormFactorPrism6 prism6(base_edge, height);

    EXPECT_EQ(BornAgain::FFPrism6Type, prism6.getName());
    EXPECT_EQ(4., prism6.getHeight());
    EXPECT_EQ(3., prism6.getBaseEdge());
    EXPECT_DOUBLE_EQ(volume, prism6.getVolume());

    test_ff( &prism6 );
}

TEST_F(FormFactorBasicTest, Pyramid)
{
    double height = 4.;
    double length = 10.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double H2divLtga = height*2./length/tga;
    double volume = 1./6.*tga*length* length*length*
        ( 1. - (1. - H2divLtga)*(1. - H2divLtga)*(1. - H2divLtga));

    FormFactorPyramid pyramid(length, height, alpha);

    EXPECT_EQ(BornAgain::FFPyramidType, pyramid.getName());
    EXPECT_EQ(4., pyramid.getHeight());
    EXPECT_EQ(10., pyramid.getBaseEdge());
    EXPECT_EQ(0.8, pyramid.getAlpha());
    EXPECT_DOUBLE_EQ(volume, pyramid.getVolume());

    test_ff( &pyramid );
}

TEST_F(FormFactorBasicTest, TruncatedSphere)
{
    double radius = 5.;
    double height = 3.;
    double HdivR = height/radius;
    double volume = M_PI/3.*radius*radius*radius*
            (3.*HdivR -1. - (HdivR - 1.)*(HdivR - 1.)*(HdivR - 1.));

    FormFactorTruncatedSphere trsphere(radius, height);

    EXPECT_EQ(BornAgain::FFTruncatedSphereType, trsphere.getName());
    EXPECT_EQ(3., trsphere.getHeight());
    EXPECT_DOUBLE_EQ(volume, trsphere.getVolume());

    test_ff( &trsphere );
}

TEST_F(FormFactorBasicTest, TruncatedSpheroid)
{
    double radius = 3.;
    double height = 5.;
    double flattening = 1.5;
    double volume = M_PI*radius*height*height/flattening*
            (1.-height/(3.*flattening*radius));

    FormFactorTruncatedSpheroid trspheroid(radius, height, flattening);

    EXPECT_EQ(BornAgain::FFTruncatedSpheroidType, trspheroid.getName());
    EXPECT_EQ(5., trspheroid.getHeight());
    EXPECT_EQ(3., trspheroid.getRadius());
    EXPECT_DOUBLE_EQ(volume, trspheroid.getVolume());

    test_ff( &trspheroid );
}

TEST_F(FormFactorBasicTest, Tetrahedron)
{
    double base_edge = 16.;
    double height = 4.;
    double alpha = 0.8;
    double tga = std::tan(alpha);
    double sqrt3H2divLtga = std::sqrt(3.)*2.*height/base_edge/tga;
    double volume = tga/24.*base_edge*base_edge*base_edge*(
     1.- (1. - sqrt3H2divLtga)*(1. - sqrt3H2divLtga)*(1. - sqrt3H2divLtga));

    FormFactorTetrahedron tetrahedron(base_edge, height, alpha);

    EXPECT_EQ(BornAgain::FFTetrahedronType, tetrahedron.getName());
    EXPECT_EQ(4., tetrahedron.getHeight());
    EXPECT_EQ(16., tetrahedron.getBaseEdge());
    EXPECT_EQ(0.8, tetrahedron.getAlpha());
    EXPECT_DOUBLE_EQ(volume, tetrahedron.getVolume());

    test_ff( &tetrahedron );
}

TEST_F(FormFactorBasicTest, Ripple1)
{
    double width = 20.;
    double height = 4.;
    double length = 100.0;
    double volume = 0.5*height*width*length;

    FormFactorRipple1 ripple1(length, width, height);

    EXPECT_EQ(BornAgain::FFRipple1Type, ripple1.getName());
    EXPECT_EQ(4., ripple1.getHeight());
    EXPECT_EQ(20., ripple1.getWidth());
    EXPECT_EQ(100., ripple1.getLength());
    EXPECT_DOUBLE_EQ(volume, ripple1.getVolume());

    test_ff( &ripple1 );
}

TEST_F(FormFactorBasicTest, TruncatedCube)
{
    double length = 15.;
    double t = 6.; // side length of removed trirectangular tetrahedron at each vertex
    double volume = length*length*length - 4./3.*t*t*t;

    FormFactorTruncatedCube trcube(length, t);

    EXPECT_EQ(BornAgain::FFTruncatedCubeType,trcube.getName());
    EXPECT_EQ(length, trcube.getLength());
    EXPECT_DOUBLE_EQ(t, trcube.getRemovedLength());
    EXPECT_DOUBLE_EQ(trcube.getVolume(), volume);

    test_ff( &trcube );
}

TEST_F(FormFactorBasicTest, Ripple2)
{
    double width = 20.;
    double height = 4.;
    double length = 100.0;
    double d = 0.3; // asymmetry
    double volume = 0.5*height*width*length;

    FormFactorRipple2 ripple2(length, width, height, d);

    EXPECT_EQ(BornAgain::FFRipple2Type, ripple2.getName());
    EXPECT_EQ(4., ripple2.getHeight());
    EXPECT_DOUBLE_EQ(volume, ripple2.getVolume());

    // test_ff( &ripple2 ); WAITING: restore once getRadius returns the umkreis radius
}
