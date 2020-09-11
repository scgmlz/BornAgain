#include "Core/Basics/Units.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/VariableBinAxis.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/PropertyItem.h"
#include "GUI/coregui/Models/TransformFromDomain.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"

class TestAxesItems : public ::testing::Test
{
};

TEST_F(TestAxesItems, transformFromDomain)
{
    BasicAxisItem item;

    // transform domain axis without scale factor
    FixedBinAxis axis0("axis0", 99, -42.0, 42.0);
    TransformFromDomain::setAxisItem(&item, axis0);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_NBINS), static_cast<int>(axis0.size()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MIN_DEG), static_cast<int>(axis0.getMin()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MAX_DEG), static_cast<int>(axis0.getMax()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_TITLE), QString::fromStdString(axis0.getName()));

    // transform domain axis with limits given in radians
    FixedBinAxis axis1("axis1", 42, -42.0 * Units::deg, 42.0 * Units::deg);
    const double scale = 1. / Units::deg;
    TransformFromDomain::setAxisItem(&item, axis1, scale);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_NBINS), static_cast<int>(axis1.size()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MIN_DEG), -42.0);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MAX_DEG), 42.0);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_TITLE), QString::fromStdString(axis1.getName()));

    // transform to unexpected item
    PropertyItem property;
    EXPECT_THROW(TransformFromDomain::setAxisItem(&property, axis1), GUIHelpers::Error);

    // transform from unexpected axis
    std::vector<double> bins = {1.0, 2.0, 3.0};
    VariableBinAxis varaxis("axis", bins.size() - 1, bins);
    EXPECT_THROW(TransformFromDomain::setAxisItem(&item, varaxis), GUIHelpers::Error);
}
