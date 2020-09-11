#include "GUI/coregui/Models/MaterialDataItems.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

class TestMaterialModel : public ::testing::Test
{
};

TEST_F(TestMaterialModel, addRefractiveMaterial)
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    EXPECT_EQ(model->rowCount(QModelIndex()), 0);

    const double delta(0.2), beta(0.1);
    const QString name("MaterialName");
    auto material = model->addRefractiveMaterial(name, delta, beta);

    EXPECT_EQ(model->rowCount(QModelIndex()), 1);
    EXPECT_EQ(model->itemForIndex(material->index()), material);
    EXPECT_EQ(model->rowCount(QModelIndex()), 1);

    EXPECT_EQ(material->itemName(), name);
    auto materialData = material->getGroupItem(MaterialItem::P_MATERIAL_DATA);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_DELTA), delta);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_BETA), beta);
}

TEST_F(TestMaterialModel, addSLDMaterial)
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    EXPECT_EQ(model->rowCount(QModelIndex()), 0);

    const double sld_real(0.2), sld_imag(0.1);
    const QString name("MaterialName");
    auto material = model->addSLDMaterial(name, sld_real, sld_imag);

    EXPECT_EQ(model->rowCount(QModelIndex()), 1);
    EXPECT_EQ(model->itemForIndex(material->index()), material);
    EXPECT_EQ(model->rowCount(QModelIndex()), 1);

    EXPECT_EQ(material->itemName(), name);
    auto materialData = material->getGroupItem(MaterialItem::P_MATERIAL_DATA);
    EXPECT_EQ(materialData->getItemValue(MaterialSLDDataItem::P_SLD_REAL), sld_real);
    EXPECT_EQ(materialData->getItemValue(MaterialSLDDataItem::P_SLD_IMAG), sld_imag);
}

TEST_F(TestMaterialModel, cloneMaterial)
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    EXPECT_EQ(model->rowCount(QModelIndex()), 0);

    const double delta(0.2), beta(0.1);
    const QString name("MaterialName");
    auto material = model->addRefractiveMaterial(name, delta, beta);
    const QString origIdentifier = material->identifier();

    auto clonedMaterial = model->cloneMaterial(material->index());
    EXPECT_EQ(model->rowCount(QModelIndex()), 2);

    // clone should not change identifier of original material (as it once happened)
    EXPECT_EQ(material->identifier(), origIdentifier);

    // cloned material should have different identifier
    EXPECT_TRUE(clonedMaterial->identifier() != material->identifier());

    // checking name of cloned material
    EXPECT_EQ(material->itemName() + " (clone)", clonedMaterial->itemName());

    auto materialData = clonedMaterial->getGroupItem(MaterialItem::P_MATERIAL_DATA);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_DELTA), delta);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_BETA), beta);
}

//! Checks the method which returns MaterialItem from known identifier.

TEST_F(TestMaterialModel, materialFromIdentifier)
{
    MaterialModel model;
    auto material1 = model.addRefractiveMaterial("aaa", 1.0, 2.0);
    auto material2 = model.addRefractiveMaterial("bbb", 3.0, 4.0);
    EXPECT_TRUE(material1 == model.materialFromIdentifier(material1->identifier()));
    EXPECT_TRUE(material2 == model.materialFromIdentifier(material2->identifier()));
    EXPECT_TRUE(nullptr == model.materialFromIdentifier("non-existing-identifier"));
}

//! Checks the method which returns MaterialItem from material name.

TEST_F(TestMaterialModel, test_materialFromName)
{
    MaterialModel model;
    auto material1 = model.addRefractiveMaterial("aaa", 1.0, 2.0);
    auto material2 = model.addRefractiveMaterial("bbb", 3.0, 4.0);
    EXPECT_TRUE(material1 == model.materialFromName(material1->itemName()));
    EXPECT_TRUE(material2 == model.materialFromName(material2->itemName()));
    EXPECT_TRUE(nullptr == model.materialFromName("non-existing-name"));
}

//! Checks the method which construct MaterialProperty from MaterialItem.

TEST_F(TestMaterialModel, test_materialPropertyFromMaterial)
{
    MaterialModel model;
    auto material = model.addRefractiveMaterial("Something", 1.0, 2.0);

    ExternalProperty property = MaterialItemUtils::materialProperty(*material);
    EXPECT_EQ(property.text(), "Something");
    EXPECT_EQ(property.color(), material->color());
    EXPECT_EQ(property.identifier(), material->identifier());
}

//! Default MaterialProperty construction.

TEST_F(TestMaterialModel, defaultMaterialProperty)
{
    MaterialModel model;

    // testing default material property from MaterialItemUtils
    // in the absence of any materials, property should be in invalid state
    ExternalProperty property = MaterialItemUtils::defaultMaterialProperty();
    EXPECT_TRUE(property.isValid() == false);

    // adding materials to the model, default property should refer to first material in a model
    auto mat1 = model.addRefractiveMaterial("Something1", 1.0, 2.0);
    model.addRefractiveMaterial("Something2", 3.0, 4.0);
    ExternalProperty property2 = MaterialItemUtils::defaultMaterialProperty();
    EXPECT_EQ(property2.text(), "Something1");
    EXPECT_EQ(property2.color(), mat1->color());
    EXPECT_EQ(property2.identifier(), mat1->identifier());
}
