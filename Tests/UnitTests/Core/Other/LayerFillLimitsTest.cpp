#include "Core/Multilayer/LayerFillLimits.h"
#include "Tests/GTestWrapper/google_test.h"
#include <stdexcept>

class LayerFillLimitsTest : public ::testing::Test
{
protected:
    LayerFillLimitsTest();

    LayerFillLimits m_fill_limits;
    std::vector<double> layers_bottomz;
};

LayerFillLimitsTest::LayerFillLimitsTest() : m_fill_limits({})
{
    std::vector<double> layers_bottomz = {0, -5, -20};
    m_fill_limits = LayerFillLimits(layers_bottomz);
}

TEST_F(LayerFillLimitsTest, LayerFillLimitsEmptyConstructor)
{
    LayerFillLimits layer_limits({});
    EXPECT_EQ(1u, layer_limits.layerZLimits().size());
    EXPECT_EQ(layer_limits.layerZLimits()[0], ZLimits());
}

TEST_F(LayerFillLimitsTest, LayerFillLimitsConstructor)
{
    std::vector<ZLimits> limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_EQ(limits[0], ZLimits());
    EXPECT_EQ(limits[1], ZLimits());
    EXPECT_EQ(limits[2], ZLimits());
    EXPECT_EQ(limits[3], ZLimits());
}

TEST_F(LayerFillLimitsTest, LayerFillLimitsWrongUpdate)
{
    EXPECT_THROW(m_fill_limits.update({1, 0}), std::runtime_error);
    std::vector<ZLimits> limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_EQ(limits[0], ZLimits());
    EXPECT_EQ(limits[1], ZLimits());
    EXPECT_EQ(limits[2], ZLimits());
    EXPECT_EQ(limits[3], ZLimits());
}

TEST_F(LayerFillLimitsTest, LayerFillLimitsUpdate)
{
    m_fill_limits.update({1, 1.5});
    std::vector<ZLimits> limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_EQ(limits[0], ZLimits(1, 1.5));
    EXPECT_EQ(limits[1], ZLimits());
    EXPECT_EQ(limits[2], ZLimits());
    EXPECT_EQ(limits[3], ZLimits());

    m_fill_limits.update({-6, -3});
    limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_EQ(limits[0], ZLimits(1, 1.5));
    EXPECT_EQ(limits[1], ZLimits(-5, -3));
    EXPECT_EQ(limits[2], ZLimits(-1, 0));
    EXPECT_EQ(limits[3], ZLimits());

    m_fill_limits.update({-10, -7});
    limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_EQ(limits[0], ZLimits(1, 1.5));
    EXPECT_EQ(limits[1], ZLimits(-5, -3));
    EXPECT_EQ(limits[2], ZLimits(-5, 0));
    EXPECT_EQ(limits[3], ZLimits());

    m_fill_limits.update({-30, -25});
    limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_EQ(limits[0], ZLimits(1, 1.5));
    EXPECT_EQ(limits[1], ZLimits(-5, -3));
    EXPECT_EQ(limits[2], ZLimits(-5, 0));
    EXPECT_EQ(limits[3], ZLimits(-10, -5));
}
