#ifndef HOMOGENEOUSMATERIALTEST_H
#define HOMOGENEOUSMATERIALTEST_H

#include "HomogeneousMaterial.h"
#include "Rotations.h"
#include "Units.h"

class HomogeneousMaterialTest : public ::testing :: Test
{
public:
    HomogeneousMaterialTest() {}
    virtual ~HomogeneousMaterialTest(){}
};

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialWithRefIndex)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    HomogeneousMaterial material("Material1", refIndex);
    EXPECT_EQ("Material1", material.getName());
    EXPECT_EQ(refIndex, material.getRefractiveIndex());

    Eigen::Matrix2cd matrix = material.getScatteringMatrix(3.0);
    EXPECT_EQ(complex_t(-3.0,4.0), matrix(0,0));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(0,1));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(1,0));
    EXPECT_EQ(complex_t(-3.0,4.0), matrix(1,1));

    complex_t refIndex2 = complex_t(2.0, 3.0);
    material.setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, material.getRefractiveIndex());

    Eigen::Matrix2cd matrix2 = material.getScatteringMatrix(4.0);
    EXPECT_EQ(complex_t(-5.0,12.0), matrix2(0,0));
    EXPECT_EQ(complex_t(0.0,0.0), matrix2(0,1));
    EXPECT_EQ(complex_t(0.0,0.0), matrix2(1,0));
    EXPECT_EQ(complex_t(-5.0,12.0), matrix2(1,1));
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialWithRefIndexParam)
{
    HomogeneousMaterial material("Material1", 2.0, 2.0);
    EXPECT_EQ("Material1", material.getName());
    EXPECT_EQ(complex_t(-1.0,2.0), material.getRefractiveIndex());

    Eigen::Matrix2cd matrix = material.getScatteringMatrix(3.0);
    EXPECT_EQ(complex_t(-3.0,-4.0), matrix(0,0));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(0,1));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(1,0));
    EXPECT_EQ(complex_t(-3.0,-4.0), matrix(1,1));
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialTransform)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    HomogeneousMaterial material("Material1", refIndex);

    RotationZ transform(45.*Units::degree);
    const IMaterial * tMaterial = material.createTransformedMaterial(transform.getTransform3D());

    EXPECT_EQ("Material1", tMaterial->getName());
    EXPECT_EQ(refIndex, tMaterial->getRefractiveIndex());

    Eigen::Matrix2cd matrix = tMaterial->getScatteringMatrix(3.0);
    EXPECT_EQ(complex_t(-3.0,4.0), matrix(0,0));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(0,1));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(1,0));
    EXPECT_EQ(complex_t(-3.0,4.0), matrix(1,1));

    delete tMaterial;
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialClone)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    HomogeneousMaterial material("Material1", refIndex);

    HomogeneousMaterial * clone = material.clone();

    EXPECT_EQ("Material1", clone->getName());
    EXPECT_EQ(refIndex, clone->getRefractiveIndex());

    Eigen::Matrix2cd matrix = clone->getScatteringMatrix(3.0);
    EXPECT_EQ(complex_t(-3.0,4.0), matrix(0,0));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(0,1));
    EXPECT_EQ(complex_t(0.0,0.0), matrix(1,0));
    EXPECT_EQ(complex_t(-3.0,4.0), matrix(1,1));

    complex_t refIndex2 = complex_t(2.0, 3.0);
    clone->setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, clone->getRefractiveIndex());

    Eigen::Matrix2cd matrix2 = clone->getScatteringMatrix(4.0);
    EXPECT_EQ(complex_t(-5.0,12.0), matrix2(0,0));
    EXPECT_EQ(complex_t(0.0,0.0), matrix2(0,1));
    EXPECT_EQ(complex_t(0.0,0.0), matrix2(1,0));
    EXPECT_EQ(complex_t(-5.0,12.0), matrix2(1,1));

    RotationZ transform(45.*Units::degree);
    const IMaterial * tMaterial = clone->createTransformedMaterial(transform.getTransform3D());

    EXPECT_EQ("Material1", tMaterial->getName());
    EXPECT_EQ(refIndex2, tMaterial->getRefractiveIndex());

    delete tMaterial;
    delete clone;
}

#endif // HOMOGENEOUSMATERIALTEST_H
