#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/ModelMapper.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "Tests/GTestWrapper/google_test.h"

class TestLayerItems : public ::testing::Test
{
};

//! Checking default material of the layer.

TEST_F(TestLayerItems, test_LayerDefaultMaterial)
{
    ApplicationModels models;
    auto layer = models.sampleModel()->insertNewItem("Layer");
    auto materials = models.materialModel()->topItems();
    auto defMaterial = materials.front();

    ExternalProperty material =
        layer->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
    EXPECT_EQ(material.text(), "Default");
    EXPECT_EQ(material.identifier(),
              defMaterial->getItemValue(MaterialItem::P_IDENTIFIER).toString());
}
