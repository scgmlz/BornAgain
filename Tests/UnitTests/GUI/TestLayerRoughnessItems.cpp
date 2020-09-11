#include "Core/Multilayer/LayerRoughness.h"
#include "GUI/coregui/Models/LayerRoughnessItems.h"
#include "GUI/coregui/Models/TransformFromDomain.h"
#include "GUI/coregui/Models/TransformToDomain.h"
#include "Tests/GTestWrapper/google_test.h"

class TestLayerRoughnessItems : public ::testing::Test
{
};

TEST_F(TestLayerRoughnessItems, test_LayerRoughnessToDomain)
{
    LayerBasicRoughnessItem roughnessItem;
    roughnessItem.setItemValue(LayerBasicRoughnessItem::P_SIGMA, 10.0);
    roughnessItem.setItemValue(LayerBasicRoughnessItem::P_HURST, 20.0);
    roughnessItem.setItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH, 30.0);

    auto P_roughness = TransformToDomain::createLayerRoughness(roughnessItem);
    EXPECT_EQ(P_roughness->getSigma(),
              roughnessItem.getItemValue(LayerBasicRoughnessItem::P_SIGMA).toDouble());
    EXPECT_EQ(P_roughness->getHurstParameter(),
              roughnessItem.getItemValue(LayerBasicRoughnessItem::P_HURST).toDouble());
    EXPECT_EQ(
        P_roughness->getLatteralCorrLength(),
        roughnessItem.getItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());

    LayerZeroRoughnessItem zeroRoughnessItem;
    EXPECT_TRUE(TransformToDomain::createLayerRoughness(zeroRoughnessItem) == nullptr);
}

TEST_F(TestLayerRoughnessItems, test_LayerRoughnessFromDomain)
{
    LayerRoughness roughness(10.0, 20.0, 30.0);
    LayerBasicRoughnessItem roughnessItem;
    TransformFromDomain::setRoughnessItem(&roughnessItem, roughness);
    EXPECT_EQ(roughness.getSigma(),
              roughnessItem.getItemValue(LayerBasicRoughnessItem::P_SIGMA).toDouble());
    EXPECT_EQ(roughness.getHurstParameter(),
              roughnessItem.getItemValue(LayerBasicRoughnessItem::P_HURST).toDouble());
    EXPECT_EQ(
        roughness.getLatteralCorrLength(),
        roughnessItem.getItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());
}
