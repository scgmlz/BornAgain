#ifndef SHAPE2DTEST_H
#define SHAPE2DTEST_H

#include "Rectangle.h"
#include "Ellipse.h"
#include "Line.h"
#include "MathConstants.h"
#include <memory>

class Shape2DTest : public ::testing::Test
{
public:
};


TEST_F(Shape2DTest, Rectangle)
{
    Rectangle rect(-4.0, -2.0, 4.0, 2.0);
    EXPECT_DOUBLE_EQ(32.0, rect.getArea());
    EXPECT_TRUE(rect.contains(0.0, 0.0));
    EXPECT_TRUE(rect.contains(4.0, 2.0));
    EXPECT_TRUE(rect.contains(-4.0, -2.0));
    EXPECT_TRUE(rect.contains(-4.0, -2.0));
    EXPECT_FALSE(rect.contains(0.0, 2.01));
    EXPECT_FALSE(rect.contains(4.0, -2.01));

    Bin1D binx1(3.5, 4.5);
    Bin1D biny1(1.5, 2.5);
    EXPECT_TRUE(rect.contains(binx1, biny1));

    Bin1D binx2(3.5, 4.6);
    Bin1D biny2(1.5, 2.6);
    EXPECT_FALSE(rect.contains(binx2, biny2));

    std::unique_ptr<Rectangle> clone(rect.clone());
    EXPECT_DOUBLE_EQ(32.0, clone->getArea());
    EXPECT_TRUE(clone->contains(0.0, 0.0));
    EXPECT_TRUE(clone->contains(4.0, 2.0));
    EXPECT_TRUE(clone->contains(-4.0, -2.0));
    EXPECT_TRUE(clone->contains(-4.0, -2.0));
    EXPECT_FALSE(clone->contains(0.0, 2.01));
    EXPECT_FALSE(clone->contains(4.0, -2.01));
    EXPECT_TRUE(clone->contains(binx1, biny1));
    EXPECT_FALSE(clone->contains(binx2, biny2));
}

TEST_F(Shape2DTest, Ellipse)
{
    Ellipse ellipse(10.0, 1.0, 8.0, 4.0);
    EXPECT_TRUE(ellipse.contains(10.0, 1.0));
    EXPECT_TRUE(ellipse.contains(18.0, 1.0));
    EXPECT_FALSE(ellipse.contains(18.01, 1.0));

    EXPECT_TRUE(ellipse.contains(10.0, -3.0));
    EXPECT_FALSE(ellipse.contains(10.0, -3.01));

    EXPECT_FALSE(ellipse.contains(4.0, -2.0));
    EXPECT_TRUE(ellipse.contains(6.0, -2.0));

    Ellipse ellipse2(10.0, 1.0, 8.0, 4.0, 45.0*Units::degree);
    EXPECT_TRUE(ellipse2.contains(10.0, 1.0));
    EXPECT_FALSE(ellipse2.contains(15.0, 0.0));
    EXPECT_TRUE(ellipse2.contains(7.0, 3.0));

    std::unique_ptr<Ellipse> clone(ellipse2.clone());
    EXPECT_TRUE(clone->contains(10.0, 1.0));
    EXPECT_FALSE(clone->contains(15.0, 0.0));
    EXPECT_TRUE(clone->contains(7.0, 3.0));
}

TEST_F(Shape2DTest, Line)
{
    Line line(0.0, 0.0, 1.0, 0.0);
    EXPECT_TRUE(line.contains(0.0, 0.0));
    EXPECT_TRUE(line.contains(0.5, 0.0));
    EXPECT_TRUE(line.contains(1.0, 0.0));
    EXPECT_FALSE(line.contains(1.01, 0.0));

    Line line2(0.0, 0.0, 1.0, 1.0);
    EXPECT_TRUE(line2.contains(Bin1D(0.5, 1.0),Bin1D(0.0, 0.5)));
    EXPECT_FALSE(line2.contains(Bin1D(0.51, 1.0),Bin1D(0.0, 0.49)));

    std::unique_ptr<Line> clone(line2.clone());
    EXPECT_TRUE(clone->contains(Bin1D(0.5, 1.0),Bin1D(0.0, 0.5)));
    EXPECT_FALSE(clone->contains(Bin1D(0.51, 1.0),Bin1D(0.0, 0.49)));
}

TEST_F(Shape2DTest, VerticalLine)
{
    VerticalLine line(1.0);
    EXPECT_TRUE(line.contains(1.0, 0.0));
    EXPECT_FALSE(line.contains(1.01, 0.0));

    EXPECT_TRUE(line.contains(Bin1D(0.5, 1.5), Bin1D(0.0, 1.0)));
    EXPECT_FALSE(line.contains(Bin1D(1.01, 2.0), Bin1D(0.0, 1.0)));
}

TEST_F(Shape2DTest, HorizontalLine)
{
    HorizontalLine line(1.0);
    EXPECT_TRUE(line.contains(0.0, 1.0));
    EXPECT_FALSE(line.contains(0.0, 1.01));

    EXPECT_TRUE(line.contains(Bin1D(0.0, 1.0), Bin1D(0.5, 1.5)));
    EXPECT_FALSE(line.contains(Bin1D(0.0, 1.0), Bin1D(1.01, 2.0)));
}

#endif // SHAPE2DTEST_H
