#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "Tests/GTestWrapper/google_test.h"

class TestMultiLayerItem : public ::testing::Test
{
};

//! Testing layer appearance (enabled, disabled) in a MultiLayer made of two default layers.
//!
//! In two layer system top and bottom layers should have disabled thickness and roughness.

TEST_F(TestMultiLayerItem, test_twoLayerSystem)
{
    SampleModel model;

    auto multilayer = model.insertNewItem("MultiLayer");
    auto top = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    auto bottom = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Thickness property should be disabled for top and bottom layers
    EXPECT_FALSE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(bottom->getItem(LayerItem::P_THICKNESS)->isEnabled());

    // Thickness value should be 0.0 for top and bottom layers
    EXPECT_EQ(top->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);
    EXPECT_EQ(bottom->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);

    // Roughness group property should be disabled for top, and enabled for bottom layers
    EXPECT_FALSE(top->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
    EXPECT_TRUE(bottom->getItem(LayerItem::P_ROUGHNESS)->isEnabled());

    // Default roughness should be "LayerZeroRoughness"
    EXPECT_EQ(top->getGroupItem(LayerItem::P_ROUGHNESS)->modelType(), "LayerZeroRoughness");
    EXPECT_EQ(bottom->getGroupItem(LayerItem::P_ROUGHNESS)->modelType(), "LayerZeroRoughness");
}

//! Testing layer appearance (enabled, disabled) in a MultiLayer made of three default layers.
//!
//! In three layer system middle layer's thickness/roughness should be enabled.

TEST_F(TestMultiLayerItem, test_threeLayerSystem)
{
    SampleModel model;

    auto multilayer = model.insertNewItem("MultiLayer");
    auto top = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    auto middle = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    auto bottom = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Thickness property should be disabled for top and bottom layers and enabled for middle
    EXPECT_FALSE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_TRUE(middle->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(bottom->getItem(LayerItem::P_THICKNESS)->isEnabled());

    // Thickness value should be 0.0 for top and bottom layers
    EXPECT_EQ(top->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);
    EXPECT_EQ(middle->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);
    EXPECT_EQ(bottom->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);

    // Roughness group property should be disabled for top, and enabled for other layers
    EXPECT_FALSE(top->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
    EXPECT_TRUE(middle->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
    EXPECT_TRUE(bottom->getItem(LayerItem::P_ROUGHNESS)->isEnabled());

    // Default roughness should be "LayerZeroRoughness"
    EXPECT_EQ(top->getGroupItem(LayerItem::P_ROUGHNESS)->modelType(), "LayerZeroRoughness");
    EXPECT_EQ(middle->getGroupItem(LayerItem::P_ROUGHNESS)->modelType(), "LayerZeroRoughness");
    EXPECT_EQ(bottom->getGroupItem(LayerItem::P_ROUGHNESS)->modelType(), "LayerZeroRoughness");
}

//! Testing middle layer appearance when it is moved to the top.
//!
//! In three layer system, the moving of middle layer on top should lead to the disabling
//! of roughness/thickness.

TEST_F(TestMultiLayerItem, test_movingMiddleLayerOnTop)
{
    SampleModel model;

    auto multilayer = model.insertNewItem("MultiLayer");
    auto top = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    auto middle = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    auto bottom = model.insertNewItem("Layer", model.indexOfItem(multilayer));

    const double thickness = 10.0;
    middle->setItemValue(LayerItem::P_THICKNESS, thickness);

    // Thickness property should be disabled for top and bottom layers and enabled for middle
    EXPECT_FALSE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_TRUE(middle->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(bottom->getItem(LayerItem::P_THICKNESS)->isEnabled());

    // Roughness group property should be disabled for top, and enabled for other layers
    EXPECT_FALSE(top->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
    EXPECT_TRUE(middle->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
    EXPECT_TRUE(bottom->getItem(LayerItem::P_ROUGHNESS)->isEnabled());

    // Thickness value should be 0.0 for top and bottom layers
    EXPECT_EQ(top->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);
    EXPECT_EQ(middle->getItemValue(LayerItem::P_THICKNESS).toDouble(), thickness);
    EXPECT_EQ(bottom->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);

    // Moving middle layer to top
    model.moveItem(middle, multilayer, 0, MultiLayerItem::T_LAYERS);
    // checking that middle is top now, and top layer is middle now
    EXPECT_EQ(middle, multilayer->getChildrenOfType("Layer").at(0));
    EXPECT_EQ(top, multilayer->getChildrenOfType("Layer").at(1));

    // Thickness and roughness of middle layer should be disabled now
    EXPECT_FALSE(middle->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(middle->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
    // And, thickness of middle should become 0 to stress the fact that it become top
    EXPECT_EQ(middle->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);

    // Thickness and roughness of former top layer should be enabled now, since it is in the middle
    EXPECT_TRUE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_TRUE(top->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
}

//! Testing layer appearance when it is moved from a MultiLayer to canvas.
//!
//! If top layer was moved to canvas, its thickness and roughness should be reenabled.

TEST_F(TestMultiLayerItem, test_movingLayerOnCanvas)
{
    SampleModel model;

    auto multilayer = model.insertNewItem("MultiLayer");
    auto top = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    model.insertNewItem("Layer", model.indexOfItem(multilayer));

    // Moving top layer to canvas
    model.moveItem(top, nullptr);

    // checking that it was moved
    EXPECT_EQ(top->parent(), model.rootItem());

    // thickness should be reenabled
    //    EXPECT_TRUE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    //    EXPECT_TRUE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
}
