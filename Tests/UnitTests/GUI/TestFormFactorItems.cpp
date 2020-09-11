#include "Core/Basics/Units.h"
#include "Core/includeIncludes/FormFactors.h"
#include "Fit/TestEngine/Numeric.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "Tests/GTestWrapper/google_test.h"

class TestFormFactorItems : public ::testing::Test
{
};

TEST_F(TestFormFactorItems, test_AnisoPyramidItem)
{
    // to domain
    AnisoPyramidItem item;
    item.setItemValue(AnisoPyramidItem::P_LENGTH, 20.0);
    item.setItemValue(AnisoPyramidItem::P_WIDTH, 16.0);
    item.setItemValue(AnisoPyramidItem::P_HEIGHT, 13.0);
    item.setItemValue(AnisoPyramidItem::P_ALPHA, 60.0);
    auto P_ff = item.createFormFactor();
    FormFactorAnisoPyramid* p_ff = dynamic_cast<FormFactorAnisoPyramid*>(P_ff.get());
    EXPECT_TRUE(p_ff);
    EXPECT_EQ(p_ff->getLength(), 20.0);
    EXPECT_EQ(p_ff->getWidth(), 16.0);
    EXPECT_EQ(p_ff->getHeight(), 13.0);
    EXPECT_TRUE(Numeric::AreAlmostEqual(p_ff->getAlpha(), Units::deg2rad(60.0)));
}
