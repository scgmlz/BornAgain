#ifndef CONSTKBINAXISTEST_H
#define CONSTKBINAXISTEST_H

#include "ConstKBinAxis.h"
#include "DataFormatUtils.h"
#include "Units.h"
#include <vector>

class ConstKBinAxisTest: public ::testing::Test
{
protected:
    ConstKBinAxisTest()
        : m_nbins(10)
        , m_start(-5.0*Units::degree)
        , m_end(5.0*Units::degree)
        , m_axis("name", m_nbins, m_start, m_end)
    {
        double start_sin = std::sin(m_start);
        double end_sin = std::sin(m_end);
        double step = (end_sin-start_sin)/m_nbins;

        for(size_t i=0; i<m_nbins; ++i) {
            m_centers.push_back( (std::asin(start_sin + step*i) +  std::asin(start_sin + step*(i+1)))/2.0 );
        }

        for(size_t i=0; i<m_nbins+1; ++i) {
            m_boundaries.push_back( std::asin(start_sin + step*i) );
        }

    }

    size_t m_nbins;
    double m_start;
    double m_end;
    ConstKBinAxis m_axis;
    std::vector<double> m_centers;
    std::vector<double> m_boundaries;
};


//[-5.0, -3.99816897832528, -2.9975609824866662, -1.99786732193833, -0.9987818274427882, 0.0, 0.9987818274427874, 1.9978673219383292, 2.997560982486666, 3.998168978325279, 5.0]
TEST_F(ConstKBinAxisTest, TypicalAxis)
{
    EXPECT_EQ(m_nbins, m_axis.size());
    EXPECT_EQ(m_start, m_axis.getMin());
    EXPECT_EQ(m_end, m_axis.getMax());

    EXPECT_DOUBLE_EQ(m_start, m_axis.getBinBoundaries().front());
    EXPECT_DOUBLE_EQ(m_end, m_axis.getBinBoundaries().back());

    for(size_t i=0; i<m_axis.size(); ++i) {
        EXPECT_DOUBLE_EQ( m_centers[i], m_axis[i]);
    }

    for(size_t i=0; i<m_axis.size(); ++i) {
        EXPECT_DOUBLE_EQ( m_boundaries[i], m_axis.getBin(i).m_lower);
        EXPECT_DOUBLE_EQ( m_boundaries[i+1], m_axis.getBin(i).m_upper);
    }

}


TEST_F(ConstKBinAxisTest, CheckClone)
{
    ConstKBinAxis *clone=m_axis.clone();
    EXPECT_TRUE(m_axis == *clone);
    delete clone;
}


TEST_F(ConstKBinAxisTest, IOStream)
{
    std::ostringstream oss;
    oss << m_axis;

    ConstKBinAxis *result = dynamic_cast<ConstKBinAxis *>(DataFormatUtils::createFixedBinAxis(oss.str()));
    EXPECT_TRUE(m_axis == *result);
    delete result;
}

//[-5.0, -3.99816897832528, -2.9975609824866662, -1.99786732193833, -0.9987818274427882, 0.0, 0.9987818274427874, 1.9978673219383292, 2.997560982486666, 3.998168978325279, 5.0]

TEST_F(ConstKBinAxisTest, ClippedAxis)
{
    ConstKBinAxis *clip1 = m_axis.createClippedAxis(Units::deg2rad(-10.0), Units::deg2rad(10.0));
    EXPECT_TRUE(*clip1 == m_axis);
    delete clip1;

    ConstKBinAxis *clip2 = m_axis.createClippedAxis(Units::deg2rad(-3.0), Units::deg2rad(3.0));
    EXPECT_EQ(clip2->size(), size_t(8));
    std::vector<double> boundaries = clip2->getBinBoundaries();
    for(size_t i=0; i<boundaries.size(); ++i) {
        EXPECT_EQ(boundaries[i], m_axis.getBin(1+i).m_lower);
//        EXPECT_NEAR(boundaries[i], m_axis.getBin(1+i).m_lower, 1e-10);
    }
    delete clip2;
}

#endif // CONSTKBINAXISTEST_H
