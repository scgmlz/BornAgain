#ifndef HOMOGENEOUSMAGNETICMATERIALTEST_H
#define HOMOGENEOUSMAGNETICMATERIALTEST_H

#include "HomogeneousMagneticMaterial.h"
#include "Rotations.h"
#include "Units.h"

class HomogeneousMagneticMaterialTest : public ::testing::Test
{
public:
    HomogeneousMagneticMaterialTest() {}
    virtual ~HomogeneousMagneticMaterialTest() {}
};

TEST_F(HomogeneousMagneticMaterialTest, HomogeneousMagneticMaterialWithRefIndex)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMagneticMaterial material("MagMaterial", refIndex, magnetism);
    EXPECT_EQ("MagMaterial", material.getName());
    EXPECT_EQ(refIndex, material.getRefractiveIndex());
    EXPECT_EQ(magnetism, material.getMagneticField());

    Eigen::Matrix2cd matrix = material.getScatteringMatrix(-2.91042993836710484e-3);
    EXPECT_EQ(complex_t(2,4.0), matrix(0,0));
    EXPECT_EQ(complex_t(3.0,-4.0), matrix(0,1));
    EXPECT_EQ(complex_t(3.0, 4.0), matrix(1,0));
    EXPECT_EQ(complex_t(-8,4.0), matrix(1,1));

    complex_t refIndex2 = complex_t(2.0, 3.0);
    material.setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, material.getRefractiveIndex());

    Eigen::Matrix2cd matrix2 = material.getScatteringMatrix(-2.91042993836710484e-3);
    EXPECT_EQ(complex_t(0.0,12.0), matrix2(0,0));
    EXPECT_EQ(complex_t(3.0, -4.0), matrix2(0,1));
    EXPECT_EQ(complex_t(3.0,4.0), matrix2(1,0));
    EXPECT_EQ(complex_t(-10.0,12.0), matrix2(1,1));

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    material.setMagneticField(magnetism2);
    EXPECT_EQ(magnetism2, material.getMagneticField());
}

TEST_F(HomogeneousMagneticMaterialTest, HomogeneousMagneticMaterialWithRefIndexAndMagField)
{
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMagneticMaterial material("MagMaterial", 2.0, 2.0, magnetism);
    EXPECT_EQ("MagMaterial", material.getName());
    EXPECT_EQ(complex_t(-1.0, 2.0), material.getRefractiveIndex());
    EXPECT_EQ(magnetism, material.getMagneticField());

    Eigen::Matrix2cd matrix = material.getScatteringMatrix(-2.91042993836710484e-3);
    EXPECT_EQ(complex_t(2,-4.0), matrix(0,0));
    EXPECT_EQ(complex_t(3.0,-4.0), matrix(0,1));
    EXPECT_EQ(complex_t(3.0, 4.0), matrix(1,0));
    EXPECT_EQ(complex_t(-8,-4.0), matrix(1,1));

    complex_t refIndex2 = complex_t(2.0, 3.0);
    material.setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, material.getRefractiveIndex());

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    material.setMagneticField(magnetism2);
    EXPECT_EQ(magnetism2, material.getMagneticField());
}

TEST_F(HomogeneousMagneticMaterialTest, HomogeneousMagneticMaterialTransform)
{
    complex_t refIndex = complex_t(0.0, 0.0);
    kvector_t magnetism = kvector_t(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial material("MagMaterial", refIndex, magnetism);

    RotationZ transform(45.*Units::degree);
    const IMaterial * tMaterial = material.createTransformedMaterial(transform.getTransform3D());

    EXPECT_EQ("MagMaterial", tMaterial->getName());
    EXPECT_EQ(refIndex, tMaterial->getRefractiveIndex());

    Eigen::Matrix2cd matrix = tMaterial->getScatteringMatrix(-2.91042993836710484e-3);
    EXPECT_EQ(complex_t(0.0, 0.0), matrix(0,0));
    EXPECT_EQ(complex_t(0.0, 0.0), matrix(0,1));
    EXPECT_EQ(complex_t(0.0, 0.0), matrix(1,0));
    EXPECT_EQ(complex_t(0.0, 0.0), matrix(1,1));

    delete tMaterial;
}

TEST_F(HomogeneousMagneticMaterialTest, HomogeneousMagneticMaterialClone)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMagneticMaterial material("MagMaterial", refIndex, magnetism);

    HomogeneousMagneticMaterial * clone = material.clone();

    EXPECT_EQ("MagMaterial", clone->getName());
    EXPECT_EQ(refIndex, clone->getRefractiveIndex());
    EXPECT_EQ(magnetism, clone->getMagneticField());

    Eigen::Matrix2cd matrix = clone->getScatteringMatrix(-2.91042993836710484e-3);
    EXPECT_EQ(complex_t(2,4.0), matrix(0,0));
    EXPECT_EQ(complex_t(3.0,-4.0), matrix(0,1));
    EXPECT_EQ(complex_t(3.0, 4.0), matrix(1,0));
    EXPECT_EQ(complex_t(-8,4.0), matrix(1,1));

    complex_t refIndex2 = complex_t(2.0, 3.0);
    clone->setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, clone->getRefractiveIndex());

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    clone->setMagneticField(magnetism2);
    EXPECT_EQ(magnetism2, clone->getMagneticField());

    RotationZ transform(45.*Units::degree);
    const IMaterial * tMaterial = clone->createTransformedMaterial(transform.getTransform3D());

    EXPECT_EQ("MagMaterial", tMaterial->getName());
    EXPECT_EQ(refIndex2, tMaterial->getRefractiveIndex());

    delete tMaterial;
    delete clone;
}

#endif // HOMOGENEOUSMAGNETICMATERIALTEST_H
