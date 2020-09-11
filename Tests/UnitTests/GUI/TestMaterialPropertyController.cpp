#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/MaterialPropertyController.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QtTest>

class TestMaterialPropertyController : public ::testing::Test
{
};

// TEST_F(TestMaterialPropertyController, test_ControllerForLayer)
//{
//    MaterialModel materialModel;
//    auto mat1 = materialModel.addRefractiveMaterial("name1", 1.0, 2.0);
//    materialModel.addRefractiveMaterial("name2", 3.0, 4.0);

//    SampleModel sampleModel;
//    auto layer = sampleModel.insertNewItem("Layer");

//    int property_changed(0);
//    layer->mapper()->setOnPropertyChange(
//        [&property_changed](const QString& name) {
//            if (name == LayerItem::P_MATERIAL)
//                ++property_changed;
//        },
//        this);

//    MaterialPropertyController controller;
//    controller.setModels(&materialModel, &sampleModel);
//    EXPECT_EQ(property_changed, 0);

//    // changing name of MaterialItem in MaterialModel, looking for MaterialProperty change
//    mat1->setItemName("newname");
//    EXPECT_EQ(property_changed, 1);
//    ExternalProperty property
//        = layer->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
//    EXPECT_EQ(property.identifier(), mat1->identifier());
//    EXPECT_EQ(property.text(), mat1->itemName());
//    EXPECT_EQ(property.color(), mat1->color());

//    // changing color of MaterialItem
//    ExternalProperty colorProperty = MaterialItemUtils::colorProperty(QColor(Qt::red));
//    mat1->setItemValue(MaterialItem::P_COLOR, colorProperty.variant());
//    EXPECT_EQ(property_changed, 2);
//    property = layer->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
//    EXPECT_EQ(property.identifier(), mat1->identifier());
//    EXPECT_EQ(property.text(), mat1->itemName());
//    EXPECT_EQ(property.color(), mat1->color());
//    EXPECT_EQ(property.color(), QColor(Qt::red));

//    // removing material from the model, property should become undefined
//    materialModel.removeRows(0, 1, QModelIndex());
//    EXPECT_EQ(property_changed, 3);
//    property = layer->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
//    EXPECT_TRUE(property.isValid() == false);
//}

//! Test MaterialProperty update in sample items when working on model clone.

TEST_F(TestMaterialPropertyController, test_ControllerInEditorContext)
{
    MaterialModel materialModel;
    auto mat1 = materialModel.addRefractiveMaterial("name1", 1.0, 2.0);
    auto mat2 = materialModel.addRefractiveMaterial("name2", 1.0, 2.0);
    auto mat3 = materialModel.addRefractiveMaterial("name3", 1.0, 2.0);

    SampleModel sampleModel;
    auto layer1 = sampleModel.insertNewItem("Layer");
    auto layer2 = sampleModel.insertNewItem("Layer");
    auto layer3 = sampleModel.insertNewItem("Layer");

    MaterialPropertyController controller;
    controller.setModels(&materialModel, &sampleModel);

    layer1->setItemValue(LayerItem::P_MATERIAL,
                         MaterialItemUtils::materialProperty(*mat1).variant());
    layer2->setItemValue(LayerItem::P_MATERIAL,
                         MaterialItemUtils::materialProperty(*mat2).variant());
    layer3->setItemValue(LayerItem::P_MATERIAL,
                         MaterialItemUtils::materialProperty(*mat3).variant());

    // Making copy of material model
    std::unique_ptr<MaterialModel> materialsCopy(materialModel.createCopy());
    auto mat1copy = dynamic_cast<MaterialItem*>(
        materialsCopy->itemForIndex(materialsCopy->index(0, 0, QModelIndex())));
    auto mat2copy = dynamic_cast<MaterialItem*>(
        materialsCopy->itemForIndex(materialsCopy->index(1, 0, QModelIndex())));
    auto mat3copy = dynamic_cast<MaterialItem*>(
        materialsCopy->itemForIndex(materialsCopy->index(2, 0, QModelIndex())));
    EXPECT_EQ(mat1->color(), mat1copy->color());
    EXPECT_EQ(mat1->itemName(), mat1copy->itemName());
    EXPECT_EQ(mat1->identifier(), mat1copy->identifier());
    EXPECT_EQ(mat2->color(), mat2copy->color());
    EXPECT_EQ(mat2->itemName(), mat2copy->itemName());
    EXPECT_EQ(mat2->identifier(), mat2copy->identifier());
    EXPECT_EQ(mat3->itemName(), mat3copy->itemName());
    EXPECT_EQ(mat3->identifier(), mat3copy->identifier());

    // Removing mat2 from the copy
    materialsCopy->removeRows(1, 1, QModelIndex());
    mat1copy = dynamic_cast<MaterialItem*>(
        materialsCopy->itemForIndex(materialsCopy->index(0, 0, QModelIndex())));
    mat3copy = dynamic_cast<MaterialItem*>(
        materialsCopy->itemForIndex(materialsCopy->index(1, 0, QModelIndex())));
    EXPECT_EQ(mat1->color(), mat1copy->color());
    EXPECT_EQ(mat1->itemName(), mat1copy->itemName());
    EXPECT_EQ(mat3->color(), mat3copy->color());
    EXPECT_EQ(mat3->itemName(), mat3copy->itemName());

    // changing mat3
    mat3copy->setItemName("name3changed");

    // copying back to original model
    materialModel.clear();
    materialModel.initFrom(materialsCopy.get(), 0);
    materialModel.modelLoaded();

    // layer2 should have undefined material property
    ExternalProperty property =
        layer2->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
    EXPECT_TRUE(property.isValid() == false);

    // layer3 should have different MaterialProperty name
    property = layer3->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
    EXPECT_EQ(property.text(), "name3changed");
}
