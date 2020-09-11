#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/GroupInfo.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/Utils.h"

class TestGroupItem : public ::testing::Test
{
};

TEST_F(TestGroupItem, test_groupInfo)
{
    GroupInfo info("Group");
    info.add("BBB", "b_label");
    info.add("AAA", "a_label");
    info.add("CCC", "c_label");
    info.setDefaultType("AAA");

    // sorted group (default behavior)
    EXPECT_EQ(info.groupType(), "Group");
    EXPECT_EQ(info.defaultType(), "AAA");
    EXPECT_EQ(info.itemTypes(), QStringList() << "AAA"
                                              << "BBB"
                                              << "CCC");
    EXPECT_EQ(info.itemLabels(), QStringList() << "a_label"
                                               << "b_label"
                                               << "c_label");

    // unsorted group
    info = GroupInfo("Group2", false);
    info.add("BBB2", "b_label2");
    info.add("AAA2", "a_label2");
    info.add("CCC2", "c_label2");
    info.setDefaultType("AAA2");
    EXPECT_EQ(info.defaultType(), "AAA2");
    EXPECT_EQ(info.itemTypes(), QStringList() << "BBB2"
                                              << "AAA2"
                                              << "CCC2");
    EXPECT_EQ(info.itemLabels(), QStringList() << "b_label2"
                                               << "a_label2"
                                               << "c_label2");

    // attempt to set non-existing default type
    EXPECT_THROW(info.setDefaultType("XXX"), GUIHelpers::Error);

    // attempt to add same info twice
    EXPECT_THROW(info.add("CCC2", "c_label2"), GUIHelpers::Error);
}

TEST_F(TestGroupItem, test_CreateGroup)
{
    SessionModel model("TestModel");

    GroupInfo groupInfo = SessionItemUtils::GetGroupInfo("Form Factor");
    EXPECT_EQ(groupInfo.defaultType(), "Cylinder");

    auto groupItem = dynamic_cast<GroupItem*>(model.insertNewItem("GroupProperty"));
    EXPECT_EQ(groupItem->children().size(), 0);
    EXPECT_TRUE(groupItem->currentItem() == nullptr);
    EXPECT_FALSE(groupItem->value().isValid());

    // setting group property and checking currentItem
    groupItem->setGroupInfo(groupInfo);

    // setting group info twice
    EXPECT_THROW(groupItem->setGroupInfo(groupInfo), GUIHelpers::Error);

    // checking current item
    EXPECT_EQ(groupItem->children().size(), 1);
    EXPECT_EQ(groupItem->children()[0], groupItem->currentItem());
    SessionItem* ffItem = groupItem->currentItem();
    EXPECT_EQ(ffItem->modelType(), "Cylinder");

    // checking current variant
    QVariant value = groupItem->value();
    EXPECT_TRUE(value.canConvert<ComboProperty>() == true);
    ComboProperty combo = value.value<ComboProperty>();
    EXPECT_EQ(combo.getValues(), groupInfo.itemLabels());
    int index = groupInfo.itemTypes().indexOf(groupInfo.defaultType());
    EXPECT_EQ(combo.currentIndex(), index);
    EXPECT_EQ(combo.getValue(), groupInfo.itemLabels().at(index));

    // changing current item
    SessionItem* newItem = groupItem->setCurrentType("FullSphere");
    EXPECT_EQ(newItem, groupItem->currentItem());
    EXPECT_EQ(newItem->modelType(), "FullSphere");
    EXPECT_EQ(groupItem->children().size(), 2);

    // checking current variant
    combo = groupItem->value().value<ComboProperty>();
    EXPECT_EQ(combo.getValues(), groupInfo.itemLabels());
    index = groupInfo.itemTypes().indexOf("FullSphere");
    EXPECT_EQ(combo.currentIndex(), index);
    EXPECT_EQ(combo.getValue(), groupInfo.itemLabels().at(index));

    // returning back to previous item
    EXPECT_EQ(groupItem->setCurrentType("Cylinder"), ffItem);
    EXPECT_EQ(groupItem->currentItem(), ffItem);
    EXPECT_EQ(groupItem->children().size(), 2);
}

//! Checking that GroupProperty stays functional if displayName of currentItem is changed.

TEST_F(TestGroupItem, test_groupPropertyWithDisplayNames)
{
    GroupInfo groupInfo = SessionItemUtils::GetGroupInfo("Distribution group");

    GroupItem groupItem;
    groupItem.setGroupInfo(groupInfo);

    SessionItem* cosineItem = groupItem.currentItem();
    cosineItem->setDisplayName("DistributionCosine" + QString::number(0));

    EXPECT_EQ(groupItem.currentItem(), cosineItem);
}
