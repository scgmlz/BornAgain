#ifndef CVECTORTEST_H
#define CVECTORTEST_H

#include "Vectors3D.h"
#include "EigenCore.h"
#include "Complex.h"

class CVectorTest : public ::testing::Test
{
 protected:
    CVectorTest() {}
    virtual ~CVectorTest() {}
};

TEST_F(CVectorTest, TrivialOperations)
{
    kvector_t vec_k(1.,2.,3.);
    EXPECT_EQ( vec_k.complex().z(), complex_t(3.,0.) );

    cvector_t vec_c(complex_t(1.,3.), complex_t(2.,-5.), complex_t(-3.,-4.));
    EXPECT_EQ( -vec_c.z(), complex_t(3.,4.) );
    EXPECT_DOUBLE_EQ( vec_c.mag(), 8. );
}

TEST_F(CVectorTest, BasicArithmetics)
{
    // Dot product with "Eigen" library
    Eigen::Vector3cd va(complex_t(1.,0.), complex_t(2.,0.), complex_t(3.,0.));
    Eigen::Vector3cd vc(complex_t(1.,1.), complex_t(2.,-5.), complex_t(3.,4.));
    EXPECT_TRUE(va.dot(vc) == complex_t(14.,3.));

    // Dot product defined in BasicVector3D
    cvector_t vec_a(complex_t(1.,0.), complex_t(2.,0.), complex_t(3.,0.));
    cvector_t vec_b(complex_t(2.,0.), complex_t(3.,0.), complex_t(4.,0.));
    cvector_t vec_c(complex_t(1.,1.), complex_t(2.,-5.), complex_t(3.,4.));
    EXPECT_TRUE(vec_a.dot(vec_b) == complex_t(20.,0));
    EXPECT_TRUE(vec_a.dot(vec_c) == complex_t(14.,3.));
    EXPECT_TRUE(vec_c.dot(vec_b) == complex_t(20.,-3.));
    EXPECT_TRUE(vec_a.dot(vec_a) == complex_t(14.,0));
    EXPECT_TRUE(vec_c.dot(vec_c) == complex_t(56.,0));

    // f = f_re + j*f_im
    cvector_t vec_e(1.,2.,3.);
    cvector_t vec_f(5.,6.,7.);
    EXPECT_EQ( vec_e+complex_t(0,1)*vec_f,
               cvector_t(complex_t(1.,5.), complex_t(2.,6), complex_t(3,7)) );
}

#endif // CVECTORTEST_H
