#ifndef SPECULARMATRIXTEST_H
#define SPECULARMATRIXTEST_H

#include "SpecularMatrix.h"
#include "Units.h"

class SpecularMatrixTest : public ::testing :: Test
{
protected:
    SpecularMatrixTest();
    virtual ~SpecularMatrixTest(){}
};

SpecularMatrixTest::SpecularMatrixTest() {}

TEST_F(SpecularMatrixTest, initial)
{
    MultiLayer mLayer;
    kvector_t v;
    SpecularMatrix::MultiLayerCoeff_t coeff;

    // @Error: Throws exception (Layer index is out of bounds)
    //matrix.execute(mLayer, v, coeff);


    HomogeneousMaterial air("air",0,1.0);
    Layer layer0(air, 0*Units::nanometer);
    mLayer.addLayer(layer0);

    SpecularMatrix::execute(mLayer, v, coeff);
}

#endif // SPECULARMATRIXTEST_H
