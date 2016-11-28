#ifndef LLDATATEST_H
#define LLDATATEST_H

#include "LLData.h"
#include <algorithm>
#include "IMaterial.h"
#include "Complex.h"


class LLDataTest : public ::testing::Test
{
 protected:
    LLDataTest();
    virtual ~LLDataTest();


    LLData<int> *int_data_0d;
    LLData<float> *fl_data_1d;
    LLData<double> *db_data_3d;

    LLData<Eigen::Matrix2d> *matrix_data_2d;
};

LLDataTest::LLDataTest()
{
    int *dim0 = new int[0];

    int *dim1 = new int[1];
    dim1[0] = 10;

    int *dim3 = new int[3];
    dim3[0] = 10;
    dim3[1] = 15;
    dim3[2] = 20;

    int *dim2 = new int[2];
    dim2[0] = 20;
    dim2[1] = 30;

    int_data_0d = new LLData<int>(0u, dim0);
    fl_data_1d  = new LLData<float>(1u, dim1);
    db_data_3d  = new LLData<double>(3u, dim3);

    matrix_data_2d = new LLData<Eigen::Matrix2d>(2u, dim2);

}

LLDataTest::~LLDataTest()
{
}

TEST_F(LLDataTest, TotalSize)
{
    EXPECT_EQ(1u, int_data_0d->getTotalSize());
    EXPECT_EQ(10u, fl_data_1d->getTotalSize());
    EXPECT_EQ(3000u, db_data_3d->getTotalSize());

    EXPECT_EQ(600u, matrix_data_2d->getTotalSize());
}

TEST_F(LLDataTest, GetRank)
{
    EXPECT_EQ(0u, int_data_0d->getRank());
    EXPECT_EQ(1u, fl_data_1d->getRank());
    EXPECT_EQ(3u, db_data_3d->getRank());
    EXPECT_EQ(2u, matrix_data_2d->getRank());
}



TEST_F(LLDataTest, SetAll)
{
    db_data_3d->setAll(1.0);
    EXPECT_DOUBLE_EQ( (*db_data_3d)[0], 1.0);

    matrix_data_2d->setAll(Eigen::Matrix2d::Identity());
    EXPECT_EQ((*matrix_data_2d)[0], Eigen::Matrix2d::Identity());
}

TEST_F(LLDataTest, ScaleAll)
{
    db_data_3d->setAll(2.0);
    db_data_3d->scaleAll(2.5);
    EXPECT_DOUBLE_EQ( (*db_data_3d)[0], 5.0);

    matrix_data_2d->setAll(Eigen::Matrix2d::Identity());
    matrix_data_2d->scaleAll(3 * Eigen::Matrix2d::Identity());
    EXPECT_EQ((*matrix_data_2d)[0], 3 * Eigen::Matrix2d::Identity()*Eigen::Matrix2d::Identity());
}

TEST_F(LLDataTest, TotalSum)
{
    fl_data_1d->setAll(2.0);
    EXPECT_FLOAT_EQ( fl_data_1d->getTotalSum(), 20.0);

    db_data_3d->setAll(0.5);
    EXPECT_DOUBLE_EQ( db_data_3d->getTotalSum(), 1500.0);

    matrix_data_2d->setAll(Eigen::Matrix2d::Identity());
    EXPECT_EQ(600 * Eigen::Matrix2d::Identity(), matrix_data_2d->getTotalSum());
}

TEST_F(LLDataTest, GetDimensions) {
    EXPECT_EQ( int_data_0d->getDimensions(), (int*)0);
    EXPECT_EQ( fl_data_1d->getDimensions()[0], 10);
    EXPECT_EQ( db_data_3d->getDimensions()[1], 15);
    EXPECT_EQ( matrix_data_2d->getDimensions()[1], 30);
}

TEST_F(LLDataTest, DataCopyingConstructor) {
    LLData<int> *other_int_data_0d = new LLData<int>(*int_data_0d);
    EXPECT_TRUE(HaveSameDimensions(*int_data_0d, *other_int_data_0d));

    fl_data_1d->setAll(1.2);
    LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
    EXPECT_TRUE(HaveSameDimensions(*fl_data_1d, *other_fl_data_1d));
    EXPECT_FLOAT_EQ( (*other_fl_data_1d)[0], 1.2f);
    EXPECT_FLOAT_EQ(fl_data_1d->getTotalSum(), other_fl_data_1d->getTotalSum());

    db_data_3d->setAll(1.17);
    LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
    EXPECT_TRUE(HaveSameDimensions(*db_data_3d, *other_db_data_3d));
    EXPECT_DOUBLE_EQ( (*other_db_data_3d)[10], 1.17);
    EXPECT_DOUBLE_EQ(db_data_3d->getTotalSum(), other_db_data_3d->getTotalSum());


    matrix_data_2d->setAll(Eigen::Matrix2d::Identity());
    LLData<Eigen::Matrix2d> *other_matrix_data_2d  = new LLData<Eigen::Matrix2d>(*matrix_data_2d);
    EXPECT_TRUE(HaveSameDimensions(*matrix_data_2d, *other_matrix_data_2d));
    EXPECT_EQ( (*other_matrix_data_2d)[7], Eigen::Matrix2d::Identity());
    //EXPECT_EQ(matrix_data_2d->getTotalSum(), other_matrix_data_2d->getTotalSum());

    delete other_int_data_0d;
    delete other_fl_data_1d;
    delete other_db_data_3d;
    delete other_matrix_data_2d;
}

TEST_F(LLDataTest, DataAssignment) {

    LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
    fl_data_1d->setAll(1.1f);
    (*other_fl_data_1d) =  (*fl_data_1d);
    EXPECT_FLOAT_EQ( (*other_fl_data_1d)[0], 1.1f);
    EXPECT_FLOAT_EQ(fl_data_1d->getTotalSum(), other_fl_data_1d->getTotalSum());

    LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
    db_data_3d->setAll(1.27);
    (*other_db_data_3d) =  (*db_data_3d);
    EXPECT_DOUBLE_EQ( (*other_db_data_3d)[11], 1.27);
    EXPECT_DOUBLE_EQ(db_data_3d->getTotalSum(), other_db_data_3d->getTotalSum());


    matrix_data_2d->setAll(Eigen::Matrix2d::Identity());
    LLData<Eigen::Matrix2d> *other_matrix_data_2d  = new LLData<Eigen::Matrix2d>(*matrix_data_2d);
    other_matrix_data_2d->setAll(10 * Eigen::Matrix2d::Identity());
    (* other_matrix_data_2d) = (* matrix_data_2d);
    EXPECT_TRUE( (*other_matrix_data_2d)[7].isIdentity());

    delete other_fl_data_1d;
    delete other_db_data_3d;
    delete other_matrix_data_2d;
}

TEST_F(LLDataTest, Addition) {

    LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
    fl_data_1d->setAll(1.1f);
    other_fl_data_1d->setAll(2.9f);
    (*other_fl_data_1d) +=  (*fl_data_1d);
    EXPECT_FLOAT_EQ( (*other_fl_data_1d)[0], 4.0f);
    EXPECT_FLOAT_EQ(other_fl_data_1d->getTotalSum(), 40.0f);

    LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
    db_data_3d->setAll(1.27);
    other_db_data_3d->setAll(0.73);
    (*other_db_data_3d) +=  (*db_data_3d);
    EXPECT_DOUBLE_EQ( (*other_db_data_3d)[11], 2.0);
    EXPECT_DOUBLE_EQ(other_db_data_3d->getTotalSum(), 6000.0);

    int *odim1 = new int[1];
    odim1[0] = 12;
    LLData<float>  *fl_data_1d2  = new LLData<float>(1u, odim1);
    fl_data_1d2->setAll(10.0);

    EXPECT_THROW((*fl_data_1d) += (*fl_data_1d2), Exceptions::RuntimeErrorException);


    LLData<Eigen::Matrix2d> *other_matrix_data_2d  = new LLData<Eigen::Matrix2d>(*matrix_data_2d);
    matrix_data_2d->setAll( Eigen::Matrix2d::Identity());
    other_matrix_data_2d->setAll( 5 * Eigen::Matrix2d::Identity());
    (*other_matrix_data_2d) += (*matrix_data_2d);
    EXPECT_EQ( (*other_matrix_data_2d)[5], 6 * Eigen::Matrix2d::Identity());


    delete fl_data_1d2;
    delete [] odim1;

    delete other_fl_data_1d;
    delete other_db_data_3d;

    delete other_matrix_data_2d;
}

TEST_F(LLDataTest, Substraction) {

    LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
    fl_data_1d->setAll(1.15f);
    other_fl_data_1d->setAll(5.15f);
    (*other_fl_data_1d) -=  (*fl_data_1d);
    EXPECT_FLOAT_EQ( (*other_fl_data_1d)[0], 4.0f);
    EXPECT_FLOAT_EQ(other_fl_data_1d->getTotalSum(), 40.0f);

    LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
    db_data_3d->setAll(1.27);
    other_db_data_3d->setAll(1.77);
    (*other_db_data_3d) -=  (*db_data_3d);
    EXPECT_DOUBLE_EQ( (*other_db_data_3d)[11], 0.5);
    EXPECT_DOUBLE_EQ(other_db_data_3d->getTotalSum(), 1500.0);

    int *odim1 = new int[1];
    odim1[0] = 12;
    LLData<float>  *fl_data_1d2  = new LLData<float>(1u, odim1);
    fl_data_1d2->setAll(10.0);

    EXPECT_THROW((*fl_data_1d) -= (*fl_data_1d2), Exceptions::RuntimeErrorException);

    LLData<Eigen::Matrix2d> *other_matrix_data_2d  = new LLData<Eigen::Matrix2d>(*matrix_data_2d);
    matrix_data_2d->setAll( Eigen::Matrix2d::Identity());
    other_matrix_data_2d->setAll( 5 * Eigen::Matrix2d::Identity());
    (*other_matrix_data_2d) -= (*matrix_data_2d);
    EXPECT_EQ( (*other_matrix_data_2d)[5], 4 * Eigen::Matrix2d::Identity());

    delete fl_data_1d2;
    delete [] odim1;

    delete other_fl_data_1d;
    delete other_db_data_3d;
    delete other_matrix_data_2d;
}

TEST_F(LLDataTest, Multiplication) {

    LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
    fl_data_1d->setAll(1.15f);
    other_fl_data_1d->setAll(2.0f);
    (*other_fl_data_1d) *=  (*fl_data_1d);
    EXPECT_FLOAT_EQ( (*other_fl_data_1d)[0], 2.30f);
    EXPECT_FLOAT_EQ(other_fl_data_1d->getTotalSum(), 23.0f);

    LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
    db_data_3d->setAll(1.25);
    other_db_data_3d->setAll(2.0);
    (*other_db_data_3d) *=  (*db_data_3d);
    EXPECT_DOUBLE_EQ( (*other_db_data_3d)[11], 2.5);
    EXPECT_DOUBLE_EQ(other_db_data_3d->getTotalSum(), 7500.0);

    int *odim1 = new int[1];
    odim1[0] = 12;
    LLData<float>  *fl_data_1d2  = new LLData<float>(1u, odim1);
    fl_data_1d2->setAll(10.0);

    EXPECT_THROW((*fl_data_1d) *= (*fl_data_1d2), Exceptions::RuntimeErrorException);

    LLData<Eigen::Matrix2d> *other_matrix_data_2d  = new LLData<Eigen::Matrix2d>(*matrix_data_2d);
    matrix_data_2d->setAll( 2*Eigen::Matrix2d::Identity());
    other_matrix_data_2d->setAll( 5 * Eigen::Matrix2d::Identity());
    (*other_matrix_data_2d) *= (*matrix_data_2d);
    EXPECT_EQ( (*other_matrix_data_2d)[5], 10 * Eigen::Matrix2d::Identity());

    delete fl_data_1d2;
    delete [] odim1;

    delete other_fl_data_1d;
    delete other_db_data_3d;
    delete other_matrix_data_2d;
}

TEST_F(LLDataTest, Division) {

    LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
    fl_data_1d->setAll(1.15f);
    other_fl_data_1d->setAll(2.3f);
    (*other_fl_data_1d) /=  (*fl_data_1d);
    EXPECT_FLOAT_EQ( (*other_fl_data_1d)[0], 2.0f);
    EXPECT_FLOAT_EQ(other_fl_data_1d->getTotalSum(), 20.0f);

    LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
    db_data_3d->setAll(1.25);
    other_db_data_3d->setAll(2.5);
    (*other_db_data_3d) /=  (*db_data_3d);
    EXPECT_DOUBLE_EQ( (*other_db_data_3d)[11], 2.0);
    EXPECT_DOUBLE_EQ(other_db_data_3d->getTotalSum(), 6000.0);

    int *odim1 = new int[1];
    odim1[0] = 12;
    LLData<float>  *fl_data_1d2  = new LLData<float>(1u, odim1);
    fl_data_1d2->setAll(10.0);

    EXPECT_THROW((*fl_data_1d) /= (*fl_data_1d2), Exceptions::RuntimeErrorException);


    delete fl_data_1d2;
    delete [] odim1;
    delete other_fl_data_1d;
    delete other_db_data_3d;
}

TEST_F (LLDataTest, HaveSameDimensions) {
    int *odim0 = new int[0];

    int *odim1 = new int[1];
    odim1[0] = 10;

    int *odim3 = new int[3];
    odim3[0] = 10;
    odim3[1] = 15;
    odim3[2] = 20;

    int *odim2 = new int[2];
    odim2[0] = 20;
    odim2[1] = 30;


    LLData<int>    *other_int_data_0d = new LLData<int>(0u, odim0);
    LLData<float>  *other_fl_data_1d  = new LLData<float>(1u, odim1);
    LLData<double> *other_db_data_3d  = new LLData<double>(3u, odim3);
    LLData<Eigen::Matrix2d> *other_matrix_data_2d = new LLData<Eigen::Matrix2d>(2u, odim2);

    EXPECT_TRUE(HaveSameDimensions(*int_data_0d, *other_int_data_0d));
    EXPECT_TRUE(HaveSameDimensions(*fl_data_1d, *other_fl_data_1d));
    EXPECT_TRUE(HaveSameDimensions(*db_data_3d, *other_db_data_3d));
    EXPECT_TRUE(HaveSameDimensions(*other_matrix_data_2d, *matrix_data_2d));

    odim3[1] = 25;
    LLData<double> *some_other_db_data_3d  = new LLData<double>(3u, odim3);
    EXPECT_FALSE(HaveSameDimensions(*db_data_3d, *some_other_db_data_3d));

    delete other_int_data_0d;
    delete other_fl_data_1d;
    delete other_db_data_3d;
    delete some_other_db_data_3d;
    delete other_matrix_data_2d;
    delete [] odim0;
    delete [] odim1;
    delete [] odim3;
    delete [] odim2;
}

TEST_F(LLDataTest, Accessors) {
    for (size_t i=0; i < fl_data_1d->getTotalSize(); ++i) {
        (*fl_data_1d)[i] = 0.5f*i;
    }
    EXPECT_FLOAT_EQ((*fl_data_1d)[2], 1.0f);

    int *coordinate = new int[1];
    coordinate[0] = 2;
    EXPECT_FLOAT_EQ(fl_data_1d->atCoordinate(coordinate), 1.0f);
    EXPECT_FLOAT_EQ(fl_data_1d->getTotalSum(), 22.5f);

    for (size_t i=0; i < db_data_3d->getTotalSize(); ++i) {
        (*db_data_3d)[i] = 0.2*i;
    }

    EXPECT_DOUBLE_EQ((*db_data_3d)[2], 0.4);
    int *coordinate3d = new int[3];
    coordinate3d[0] = 0;
    coordinate3d[1] = 0;
    coordinate3d[2] = 2;

    EXPECT_DOUBLE_EQ(db_data_3d->atCoordinate(coordinate3d), 0.4);
    EXPECT_DOUBLE_EQ(db_data_3d->getTotalSum(), 899700.0);



    for (size_t i=0; i < matrix_data_2d->getTotalSize(); ++i) {
        (*matrix_data_2d)[i] = i *  Eigen::Matrix2d::Identity();
    }

    EXPECT_EQ((*matrix_data_2d)[2], 2 * Eigen::Matrix2d::Identity());
    int *coordinate2d = new int[2];
    coordinate2d[0] = 0;
    coordinate2d[1] = 2;

    EXPECT_EQ(matrix_data_2d->atCoordinate(coordinate2d), 2 * Eigen::Matrix2d::Identity());

    delete [] coordinate;
    delete [] coordinate3d;
    delete [] coordinate2d;

}


#endif // LLDATATEST_H
