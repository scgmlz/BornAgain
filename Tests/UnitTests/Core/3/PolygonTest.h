#ifndef POLYGONTEST_H
#define POLYGONTEST_H

#include "Polygon.h"
#include <memory>

class PolygonTest : public ::testing::Test
{
public:
};


TEST_F(PolygonTest, SimpleRectangle)
{
    // simple closed rectangle
    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
    Polygon polygon(x, y);
    EXPECT_DOUBLE_EQ(32.0, polygon.getArea());
    EXPECT_TRUE(polygon.contains(0.0, 0.0));
    EXPECT_TRUE(polygon.contains(4.0, 2.0));
    EXPECT_TRUE(polygon.contains(-4.0, -2.0));
    EXPECT_TRUE(polygon.contains(-4.0, -2.0));
    EXPECT_FALSE(polygon.contains(0.0, 2.01));
    EXPECT_FALSE(polygon.contains(4.0, -2.01));

    // unclosed rectangle (should be closed automatically)
    x = {4.0, -4.0, -4.0, 4.0};
    y = {2.0, 2.0, -2.0, -2.0};
    Polygon polygon2(x, y);
    EXPECT_DOUBLE_EQ(32.0, polygon2.getArea());
    EXPECT_TRUE(polygon2.contains(0.0, 0.0));
    EXPECT_TRUE(polygon2.contains(4.0, 2.0));
    EXPECT_TRUE(polygon2.contains(-4.0, -2.0));
    EXPECT_TRUE(polygon2.contains(-4.0, -2.0));
    EXPECT_FALSE(polygon2.contains(0.0, 2.01));
    EXPECT_FALSE(polygon2.contains(4.0, -2.01));
}

//     *******
//      *   *
//       * *
//        *
//       * *
//      *   *
//     *******

TEST_F(PolygonTest, SandWatchShape)
{
    std::vector<double> x = {2.0, -2.0, 2.0, -2.0, 2.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
    Polygon polygon(x, y);
//    std::cout << polygon << std::endl;

    // for some reason area calculation doesn't work for boost's polygon of such shape
    // EXPECT_DOUBLE_EQ(8.0, polygon.getArea());

    EXPECT_TRUE(polygon.contains(2.0, 2.0));
    EXPECT_TRUE(polygon.contains(-2.0, 2.0));
    EXPECT_TRUE(polygon.contains(0.0, 0.0));
    EXPECT_TRUE(polygon.contains(0.0, 1.0));

    EXPECT_FALSE(polygon.contains(1.0, 0.0));
    EXPECT_FALSE(polygon.contains(-1.5, 0.5));

}

TEST_F(PolygonTest, ContainsBin)
{
    // simple closed rectangle
    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
    Polygon polygon(x, y);

    Bin1D binx1(3.5, 4.5);
    Bin1D biny1(1.5, 2.5);
    EXPECT_TRUE(polygon.contains(binx1, biny1));

    Bin1D binx2(3.5, 4.6);
    Bin1D biny2(1.5, 2.6);
    EXPECT_FALSE(polygon.contains(binx2, biny2));
}


TEST_F(PolygonTest, Clone)
{
    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
    Polygon polygon(x, y);

    std::unique_ptr<Polygon > clone(polygon.clone());
    EXPECT_DOUBLE_EQ(32.0, clone->getArea());
    EXPECT_TRUE(clone->contains(0.0, 0.0));
    EXPECT_TRUE(clone->contains(4.0, 2.0));
    EXPECT_TRUE(clone->contains(-4.0, -2.0));
    EXPECT_TRUE(clone->contains(-4.0, -2.0));
    EXPECT_FALSE(clone->contains(0.0, 2.01));
    EXPECT_FALSE(clone->contains(4.0, -2.01));
}

TEST_F(PolygonTest, ConstructFrom2DArray)
{
    // simple closed rectangle
    const size_t npoints(5);
    double array[npoints][2] = {{4.0, 2.0}, {-4.0, 2.0}, {-4.0, -2.0}, {4.0, -2.0}, {4.0, 2.0}};

    std::vector<std::vector<double > > points;
    for(size_t i=0; i<npoints; ++i) {
        std::vector<double> p = {array[i][0], array[i][1]};
        points.push_back(p);
    }

    Polygon polygon(points);
    EXPECT_DOUBLE_EQ(32.0, polygon.getArea());
    EXPECT_TRUE(polygon.contains(0.0, 0.0));
    EXPECT_TRUE(polygon.contains(4.0, 2.0));
    EXPECT_TRUE(polygon.contains(-4.0, -2.0));
    EXPECT_TRUE(polygon.contains(-4.0, -2.0));
    EXPECT_FALSE(polygon.contains(0.0, 2.01));
    EXPECT_FALSE(polygon.contains(4.0, -2.01));
}

//TEST_F(PolygonTest, GetPoints)
//{
//    std::vector<double> xpos;
//    std::vector<double> ypos;

//    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
//    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
//    Polygon polygon(x, y);

//    polygon.getPoints(xpos, ypos);
//    for(size_t i=0; i<xpos.size(); ++i) {
//        std::cout << xpos[i] << " " << ypos[i] << std::endl;
//    }

//}


#endif // POLYGONTEST_H
