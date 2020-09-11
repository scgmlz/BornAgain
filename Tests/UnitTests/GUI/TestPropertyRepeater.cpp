#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PropertyRepeater.h"
#include "Tests/GTestWrapper/google_test.h"

namespace
{

IntensityDataItem* createData(SessionModel& model)
{
    return dynamic_cast<IntensityDataItem*>(model.insertNewItem("IntensityData"));
}

BasicAxisItem* createAxis(SessionModel& model)
{
    return dynamic_cast<BasicAxisItem*>(model.insertNewItem("BasicAxis"));
}
} // namespace

class TestPropertyRepeater : public ::testing::Test
{
};

//! Repeater handles two items.

TEST_F(TestPropertyRepeater, test_twoItems)
{
    SessionModel model("test");

    auto item1 = createAxis(model);
    auto item2 = createAxis(model);

    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 2.0);
    item2->setItemValue(BasicAxisItem::P_MAX_DEG, 3.0);

    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2);

    // adding items to the repeater do not change values
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 2.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 3.0);

    // change of the value of one item leads to the change in another
    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 4.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 4.0);

    // clearing repeater will stop update
    repeater.clear();
    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 5.0);
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 5.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 4.0);
}

//! Repeater handles three items.

TEST_F(TestPropertyRepeater, test_threeItems)
{
    SessionModel model("test");

    auto item1 = createAxis(model);
    auto item2 = createAxis(model);
    auto item3 = createAxis(model);

    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 1.0);
    item2->setItemValue(BasicAxisItem::P_MAX_DEG, 2.0);
    item3->setItemValue(BasicAxisItem::P_MAX_DEG, 3.0);

    PropertyRepeater repeater;
    repeater.addItem(item1);
    repeater.addItem(item2);
    repeater.addItem(item3);

    // change of the value of one item leads to the change in two another
    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(item1->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 4.0);
    EXPECT_EQ(item2->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 4.0);
    EXPECT_EQ(item3->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble(), 4.0);
}

//! Checking repeater in "repeat childs properties" mode

TEST_F(TestPropertyRepeater, test_repeatAll)
{
    SessionModel model("test");

    auto item1 = createData(model);
    auto item2 = createData(model);

    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX_DEG, 2.0);
    item2->xAxisItem()->setItemValue(BasicAxisItem::P_MAX_DEG, 3.0);

    const bool repeat_child_properties = true;
    PropertyRepeater repeater(nullptr, repeat_child_properties);
    repeater.addItem(item1);
    repeater.addItem(item2);

    // adding items to the repeater do not change values
    EXPECT_EQ(item1->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), true);
    EXPECT_EQ(item2->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), true);
    EXPECT_EQ(item1->getUpperX(), 2.0);
    EXPECT_EQ(item2->getUpperX(), 3.0);

    // change of the value of one item leads to the change in another
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(item1->getUpperX(), 4.0);
    EXPECT_EQ(item2->getUpperX(), 4.0);

    item1->setItemValue(IntensityDataItem::P_IS_INTERPOLATED, false);
    EXPECT_EQ(item1->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), false);
    EXPECT_EQ(item2->getItemValue(IntensityDataItem::P_IS_INTERPOLATED).toBool(), false);

    // clearing repeater will stop update
    repeater.clear();
    item1->xAxisItem()->setItemValue(BasicAxisItem::P_MAX_DEG, 5.0);
    EXPECT_EQ(item1->getUpperX(), 5.0);
    EXPECT_EQ(item2->getUpperX(), 4.0);
}
