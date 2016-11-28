#ifndef KVECTORTEST_H
#define KVECTORTEST_H

#include "Vectors3D.h"
#include "Transform3D.h"

class KVectorTest : public ::testing::Test
{
 protected:
    KVectorTest() {}
    virtual ~KVectorTest() {}
};

TEST_F(KVectorTest, BasicMethods)
{
    kvector_t v;
    EXPECT_EQ( double(0), v.x()); EXPECT_EQ( double(0), v.y()); EXPECT_EQ( double(0), v.z());
    kvector_t v2(1.,2.,3.);
    EXPECT_EQ( double(1.), v2.x()); EXPECT_EQ( double(2.), v2.y()); EXPECT_EQ( double(3.), v2.z());
    v2.setX(10.); v2.setY(20.); v2.setZ(30.);
    EXPECT_EQ( double(10.), v2.x()); EXPECT_EQ( double(20.), v2.y()); EXPECT_EQ( double(30.), v2.z());
    v2 = {1., 2., 3.};
    EXPECT_EQ( double(1.), v2.x()); EXPECT_EQ( double(2.), v2.y()); EXPECT_EQ( double(3.), v2.z());

    kvector_t v3(1.,2.,3.);
    EXPECT_DOUBLE_EQ( v3.mag2(), 1*1+2*2+3*3);
    EXPECT_DOUBLE_EQ( v3.mag2(), v3.mag()*v3.mag());
    EXPECT_DOUBLE_EQ( v3.magxy2(), 1*1+2*2);
    EXPECT_DOUBLE_EQ( v3.magxy2(), v3.magxy()*v3.magxy());
    EXPECT_DOUBLE_EQ( v3.magxy(), std::sqrt(1*1+2*2) );
    EXPECT_DOUBLE_EQ( v3.mag(), std::sqrt(1*1+2*2+3*3) );
}


TEST_F(KVectorTest, BasicArithmetics)
{
    // assignment, self assignment, copy constructor
    kvector_t v1;
    kvector_t v2(v1);
    EXPECT_EQ( double(0), v2.x()); EXPECT_EQ( double(0), v2.y()); EXPECT_EQ( double(0), v2.z());
    v2 = { 1., 2., 3. };
    EXPECT_EQ( double(1), v2.x()); EXPECT_EQ( double(2), v2.y()); EXPECT_EQ( double(3), v2.z());
    kvector_t v3(v2);
    EXPECT_EQ( double(1), v3.x()); EXPECT_EQ( double(2), v3.y()); EXPECT_EQ( double(3), v3.z());
    kvector_t v4 = v3;
    EXPECT_EQ( double(1), v4.x()); EXPECT_EQ( double(2), v4.y()); EXPECT_EQ( double(3), v4.z());
    // +=
    kvector_t a(1., 2., 3.);
    kvector_t b(10., 20., 30.);
    a+=b;
    EXPECT_EQ( double(11), a.x()); EXPECT_EQ( double(22), a.y()); EXPECT_EQ( double(33), a.z());
    EXPECT_EQ( double(10), b.x()); EXPECT_EQ( double(20), b.y()); EXPECT_EQ( double(30), b.z());
    a = kvector_t(1., 2., 3.);
    a+=a;
    EXPECT_EQ( double(2.), a.x()); EXPECT_EQ( double(4.), a.y()); EXPECT_EQ( double(6.), a.z());
    // -=
    a = kvector_t(1., 2., 3.);
    a-=a;
    EXPECT_EQ( double(0.), a.x()); EXPECT_EQ( double(0.), a.y()); EXPECT_EQ( double(0.), a.z());
    b = kvector_t(1., 2., 3.);
    a-=b;
    EXPECT_EQ( double(-1.), a.x()); EXPECT_EQ( double(-2.), a.y()); EXPECT_EQ( double(-3.), a.z());
    // *= and /= with scalar
    a *= 10.0;
    EXPECT_EQ( double(-10.), a.x()); EXPECT_EQ( double(-20.), a.y()); EXPECT_EQ( double(-30.), a.z());
    a /= 10.;
    EXPECT_EQ( double(-1.), a.x()); EXPECT_EQ( double(-2.), a.y()); EXPECT_EQ( double(-3.), a.z());
    // unary minus
    a = kvector_t(1., 2., 3.);
    b = -a;
    EXPECT_EQ( double(1.), a.x()); EXPECT_EQ( double(2.), a.y()); EXPECT_EQ( double(3.), a.z() );
    EXPECT_EQ( double(-1.), b.x()); EXPECT_EQ( double(-2.), b.y()); EXPECT_EQ( double(-3.), b.z() );
    // addition of two vector
    a = kvector_t(1., 2., 3.);
    b = kvector_t(10., 20., 30.);
    kvector_t c =  a + b;
    EXPECT_EQ( double(1.), a.x()); EXPECT_EQ( double(2.), a.y()); EXPECT_EQ( double(3.), a.z() );
    EXPECT_EQ( double(10.), b.x()); EXPECT_EQ( double(20.), b.y()); EXPECT_EQ( double(30.), b.z() );
    EXPECT_EQ( double(11.), c.x()); EXPECT_EQ( double(22.), c.y()); EXPECT_EQ( double(33.), c.z() );
    // substraction of two vectors
    c = b - a;
    EXPECT_EQ( double(9.), c.x()); EXPECT_EQ( double(18.), c.y()); EXPECT_EQ( double(27.), c.z() );
    // multiplication by a scalar
    a = { 1., 2., 3. };
    c = 2*a*2;
    EXPECT_EQ( double(1.), a.x()); EXPECT_EQ( double(2.), a.y()); EXPECT_EQ( double(3.), a.z() );
    EXPECT_EQ( double(4.), c.x()); EXPECT_EQ( double(8.), c.y()); EXPECT_EQ( double(12.), c.z() );
    // scalar product of two vectors
    a = { 1., 2., 3. };
    b = { 10., 10., 10. };
    EXPECT_EQ( double(60), a.dot(b) );
    // crossproduct
    c = a.cross(b);
    EXPECT_EQ(c.x(), a.y()*b.z() - a.z()*b.y());
    EXPECT_EQ(c.y(), a.z()*b.x() - a.x()*b.z());
    EXPECT_EQ(c.z(), a.x()*b.y() - a.y()*b.x());
    // equality
    a = { 1.,2.,3.};
    EXPECT_TRUE( a == kvector_t(1., 2., 3.) );
    EXPECT_TRUE( a != kvector_t(1., 1., 3.) );
}


TEST_F(KVectorTest, BasicTransformation)
{
    const double epsilon=1e-12;
    kvector_t a, v;

    // rotation via transformation
    a = kvector_t(std::sqrt(3.)/2., 2., 0.5);
    Transform3D m2 = Transform3D::createRotateY(M_PI/6.);
    v = m2.transformed(a);
    ASSERT_NEAR(      v.x(), 1.0, epsilon );
    EXPECT_DOUBLE_EQ( v.y(), 2.0 );
    ASSERT_NEAR(      v.z(), 0.0, epsilon );

    a = kvector_t(0.5, std::sqrt(3.)/2., 2.);
    Transform3D m3 = Transform3D::createRotateZ(M_PI/6.);
    v = m3.transformed(a);
    ASSERT_NEAR(      v.x(), 0.0, epsilon );
    ASSERT_NEAR(      v.y(), 1.0, epsilon );
    EXPECT_DOUBLE_EQ( v.z(), 2.0 );
    Transform3D m4 = m3.getInverse();
    v = m4.transformed(v);
    ASSERT_NEAR( v.x(), a.x(), epsilon );
    ASSERT_NEAR( v.y(), a.y(), epsilon );
    ASSERT_NEAR( v.z(), a.z(), epsilon );
}

#endif // KVECTORTEST_H
