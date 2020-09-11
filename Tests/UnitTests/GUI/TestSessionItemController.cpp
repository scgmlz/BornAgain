#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/CommonWidgets/SessionItemController.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/TestSessionItemControllerHelper.h"
#include <QObject>

class TestSessionItemController : public ::testing::Test
{
};

//! Testing helper classes which will be used for controller testing.

TEST_F(TestSessionItemController, test_InitialState)
{
    TestListener listener;
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);

    TestObject object(&listener);
    EXPECT_TRUE(object.currentItem() == nullptr);
    EXPECT_EQ(object.m_is_subscribed, false);

    // setting null item
    object.setItem(nullptr);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);
    EXPECT_TRUE(object.currentItem() == nullptr);
    EXPECT_EQ(object.m_is_subscribed, false);

    object.setVisible(true);
    EXPECT_TRUE(object.currentItem() == nullptr);
    EXPECT_EQ(object.m_is_subscribed, false);
}

//! Setting item and doing nothing.

TEST_F(TestSessionItemController, test_setItem)
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("BasicAxis");

    object.setItem(item);
    EXPECT_EQ(object.currentItem(), item);
    EXPECT_EQ(object.m_is_subscribed, false);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);
}

//! Setting item and subscribing to it.

TEST_F(TestSessionItemController, test_setItemAndSubscribeItem)
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("BasicAxis");

    object.setItem(item);
    object.setVisible(true);
    EXPECT_EQ(object.currentItem(), item);
    EXPECT_EQ(object.m_is_subscribed, true);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);
}

//! Setting item properties when widget is in hidden/shown state.

TEST_F(TestSessionItemController, test_onPropertyChange)
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("BasicAxis");

    object.setItem(item);
    EXPECT_EQ(object.currentItem(), item);
    EXPECT_EQ(object.m_is_subscribed, false);

    // changing item, should be no reaction
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 3.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);

    // setting visible and changing item
    object.setVisible(true);
    EXPECT_EQ(object.m_is_subscribed, true);
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);

    // same value, no change expected
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);

    // new value
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.1);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 2);

    // setting same item once again, setting visible, and then checking that no double subscription
    object.setItem(item);
    object.setVisible(true);
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.2);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 3);

    // setting invisible and changing item, no reaction on item value change expected
    object.setVisible(false);
    EXPECT_EQ(object.m_is_subscribed, false);
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 5.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 3);
}

//! Deleting item when widget is visible.

TEST_F(TestSessionItemController, test_onItemDestroyWidgetVisible)
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("BasicAxis");

    object.setItem(item);
    object.setVisible(true);

    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);

    // item deletion should lead to automatic unsubscription
    delete item->parent()->takeRow(0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 1);
    EXPECT_EQ(object.m_is_subscribed, false);
    EXPECT_TRUE(object.currentItem() == nullptr);

    object.setVisible(false);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 1);
    EXPECT_EQ(object.m_is_subscribed, false);
    EXPECT_TRUE(object.currentItem() == nullptr);
}

TEST_F(TestSessionItemController, test_onItemDestroyWidgetHidden)
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("BasicAxis");

    object.setItem(item);
    object.setVisible(true);

    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);

    object.setVisible(false);

    // Deleting item when widget is hidden.
    // Widget itself shouldn't notice onItemDestroy because of hidden state.
    // But the controller should notice, and unsubscribe the widget.

    delete item->parent()->takeRow(0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(object.m_is_subscribed, false);
    EXPECT_TRUE(object.currentItem() == nullptr);

    object.setVisible(true);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(object.m_is_subscribed, false);
    EXPECT_TRUE(object.currentItem() == nullptr);
}

//! Typical scenario when one item follows the other.

TEST_F(TestSessionItemController, test_onTwoItems)
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item1 = model.insertNewItem("BasicAxis");
    SessionItem* item2 = model.insertNewItem("BasicAxis");

    object.setItem(item1);
    EXPECT_EQ(object.currentItem(), item1);
    object.setVisible(true);

    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);

    // changing the item
    object.setItem(item2);
    EXPECT_EQ(object.currentItem(), item2);
    // since by design setting the item doesn't lead to automatic subscription, we have to subscribe
    object.setVisible(true);

    // changing the value of previous item, widget shouldn't react
    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 5.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);

    // changing the value of new item, widget should react
    item2->setItemValue(BasicAxisItem::P_MAX_DEG, 6.0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 2);
}

//! Settings two items one after another, when widget stays hidden

TEST_F(TestSessionItemController, test_onTwoItemsWhenHidden)
{
    TestListener listener;
    TestObject object(&listener);
    SessionModel model("TestModel");
    SessionItem* item1 = model.insertNewItem("BasicAxis");
    SessionItem* item2 = model.insertNewItem("BasicAxis");

    object.setVisible(false);

    object.setItem(item1);
    EXPECT_EQ(object.currentItem(), item1);

    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);

    // changing the item
    object.setItem(item2);
    EXPECT_EQ(object.currentItem(), item2);

    // changing the value of previous item, widget shouldn't react
    item1->setItemValue(BasicAxisItem::P_MAX_DEG, 5.0);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);

    // changing the value of new item, widget shouldn't react
    item2->setItemValue(BasicAxisItem::P_MAX_DEG, 6.0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 0);
}

//! Deleting the widget when item still alive.

TEST_F(TestSessionItemController, test_deleteWidget)
{
    TestListener listener;
    TestObject* object = new TestObject(&listener);
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("BasicAxis");

    object->setItem(item);
    object->setVisible(true);

    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.0);

    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);
    EXPECT_EQ(listener.m_onWidgetDestroyed, 0);

    delete object;

    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);
    EXPECT_EQ(listener.m_onWidgetDestroyed, 1);

    item->setItemValue(BasicAxisItem::P_MAX_DEG, 4.1);
    EXPECT_EQ(listener.m_onItemDestroyedCount, 0);
    EXPECT_EQ(listener.m_onPropertyChangeCount, 1);
}
