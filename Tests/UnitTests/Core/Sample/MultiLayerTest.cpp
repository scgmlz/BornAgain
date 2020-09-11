#include "Core/Multilayer/MultiLayer.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayerUtils.h"
#include "Tests/GTestWrapper/google_test.h"

using MultiLayerUtils::LayerBottomInterface;
using MultiLayerUtils::LayerThickness;
using MultiLayerUtils::LayerTopInterface;

class MultiLayerTest : public ::testing::Test
{
protected:
    MultiLayerTest()
        // The following delta, beta are all unphysical. Values don't matter here.
        : air(HomogeneousMaterial("air", 1e-6, 9e-4)),
          iron(HomogeneousMaterial("iron", 2e-5, 8e-5)),
          chromium(HomogeneousMaterial("chromium", 3e-7, 7e-6)),
          stone(HomogeneousMaterial("stone", 4e-4, 8e-7)), topLayer(air, 0 * Units::nanometer),
          layer1(iron, 20 * Units::nanometer), layer2(chromium, 40 * Units::nanometer),
          substrate(stone, 0 * Units::nanometer)
    {
    }
    void set_four()
    {
        mLayer.addLayer(topLayer);
        mLayer.addLayer(layer1);
        mLayer.addLayer(layer2);
        mLayer.addLayer(substrate);
    }

    MultiLayer mLayer;
    const Material air, iron, chromium, stone;
    Layer topLayer, layer1, layer2, substrate;
};

TEST_F(MultiLayerTest, BasicProperty)
{
    // check default properties
    EXPECT_EQ(0.0, mLayer.crossCorrLength());
    EXPECT_EQ(size_t(0), mLayer.numberOfLayers());

    // set parameter
    mLayer.setParameterValue("CrossCorrelationLength", 2.54);
    EXPECT_EQ(2.54, mLayer.crossCorrLength());

    // adding layers
    mLayer.addLayer(topLayer);
    EXPECT_EQ(size_t(1), mLayer.numberOfLayers());

    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(substrate);
    EXPECT_EQ(size_t(4), mLayer.numberOfLayers());
}

TEST_F(MultiLayerTest, LayerThicknesses)
{
    set_four();

    // check layer thickness
    EXPECT_EQ(0.0, LayerThickness(mLayer, 0));
    EXPECT_EQ(20.0, LayerThickness(mLayer, 1));
    EXPECT_EQ(40.0, LayerThickness(mLayer, 2));
    EXPECT_EQ(0.0, LayerThickness(mLayer, 3));
}

TEST_F(MultiLayerTest, CheckAllLayers)
{
    set_four();

    // check individual layer
    const Layer* got0 = mLayer.layer(0);
    EXPECT_EQ(0, got0->thickness());

    const Layer* got1 = mLayer.layer(1);
    EXPECT_EQ(20, got1->thickness());

    const Layer* got2 = mLayer.layer(2);
    EXPECT_EQ(40, got2->thickness());

    const Layer* got3 = mLayer.layer(3);
    EXPECT_EQ(0, got3->thickness());
}

TEST_F(MultiLayerTest, LayerInterfaces)
{
    set_four();

    // check interfaces
    const LayerInterface* interface0 = mLayer.layerInterface(0);
    EXPECT_TRUE(nullptr != interface0);
    EXPECT_EQ(nullptr, interface0->getRoughness());

    const LayerInterface* interface1 = mLayer.layerInterface(1);
    EXPECT_TRUE(nullptr != interface1);
    EXPECT_EQ(nullptr, interface1->getRoughness());

    const LayerInterface* interface2 = mLayer.layerInterface(2);
    EXPECT_TRUE(nullptr != interface2);
    EXPECT_EQ(nullptr, interface2->getRoughness());

    // bottom interface
    const LayerInterface* interfaceBottom = LayerBottomInterface(mLayer, 0);
    EXPECT_TRUE(nullptr != interfaceBottom);
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());

    // top interface
    const LayerInterface* interfaceTop = LayerTopInterface(mLayer, 3);
    EXPECT_TRUE(nullptr != interfaceTop);
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());

    // null interface
    const LayerInterface* interfaceTopNull = LayerTopInterface(mLayer, 0);
    EXPECT_TRUE(nullptr == interfaceTopNull);

    const LayerInterface* interfaceBottomNull = LayerBottomInterface(mLayer, 3);
    EXPECT_TRUE(nullptr == interfaceBottomNull);
}

TEST_F(MultiLayerTest, Clone)
{
    set_four();

    MultiLayer* mLayerClone = mLayer.clone();

    // check properties
    EXPECT_EQ(0.0, mLayerClone->crossCorrLength());
    EXPECT_EQ(size_t(4), mLayerClone->numberOfLayers());

    // check layer thickness
    EXPECT_EQ(topLayer.thickness(), LayerThickness(*mLayerClone, 0));
    EXPECT_EQ(layer1.thickness(), LayerThickness(*mLayerClone, 1));
    EXPECT_EQ(layer2.thickness(), LayerThickness(*mLayerClone, 2));
    EXPECT_EQ(substrate.thickness(), LayerThickness(*mLayerClone, 3));

    // check individual layer
    const Layer* layerCopy0 = mLayerClone->layer(0);
    EXPECT_EQ(topLayer.thickness(), layerCopy0->thickness());

    const Layer* layerCopy1 = mLayerClone->layer(1);
    EXPECT_EQ(layer1.thickness(), layerCopy1->thickness());

    const Layer* layerCopy2 = mLayerClone->layer(2);
    EXPECT_EQ(layer2.thickness(), layerCopy2->thickness());

    const Layer* layerCopy3 = mLayerClone->layer(3);
    EXPECT_EQ(substrate.thickness(), layerCopy3->thickness());

    // check interfaces
    const LayerInterface* interface0 = mLayerClone->layerInterface(0);
    EXPECT_TRUE(nullptr != interface0);
    EXPECT_EQ(nullptr, interface0->getRoughness());

    const LayerInterface* interface1 = mLayerClone->layerInterface(1);
    EXPECT_TRUE(nullptr != interface1);
    EXPECT_EQ(nullptr, interface1->getRoughness());

    const LayerInterface* interface2 = mLayerClone->layerInterface(2);
    EXPECT_TRUE(nullptr != interface2);
    EXPECT_EQ(nullptr, interface2->getRoughness());

    // top interface
    const LayerInterface* interfaceBottom = LayerTopInterface(*mLayerClone, 1);
    EXPECT_TRUE(nullptr != interfaceBottom);
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());

    // Bottom interface
    const LayerInterface* interfaceTop = LayerBottomInterface(*mLayerClone, 2);
    EXPECT_TRUE(nullptr != interfaceTop);
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());

    // null interface
    const LayerInterface* interfaceTopNull = LayerTopInterface(*mLayerClone, 0);
    EXPECT_TRUE(nullptr == interfaceTopNull);

    const LayerInterface* interfaceBottomNull = LayerBottomInterface(*mLayerClone, 3);
    EXPECT_TRUE(nullptr == interfaceBottomNull);

    delete mLayerClone;
}

TEST_F(MultiLayerTest, WithRoughness)
{
    // LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength);
    LayerRoughness lr(1.1, -7.3, 0.1);
    mLayer.addLayer(topLayer);
    mLayer.addLayerWithTopRoughness(layer1, lr);
    mLayer.addLayer(substrate);

    const LayerInterface* interface0 = mLayer.layerInterface(0);
    const LayerInterface* interface1 = mLayer.layerInterface(1);

    const LayerRoughness* roughness0 = interface0->getRoughness();
    const LayerRoughness* roughness1 = interface1->getRoughness();

    EXPECT_TRUE(roughness0);
    EXPECT_EQ(nullptr, roughness1);

    EXPECT_EQ(1.1, roughness0->getSigma());
    EXPECT_EQ(-7.3, roughness0->getHurstParameter());
    EXPECT_EQ(0.1, roughness0->getLatteralCorrLength());
}

TEST_F(MultiLayerTest, CloneWithRoughness)
{
    LayerRoughness lr0(-2.1, 7.3, 12.1);
    LayerRoughness lr1(1.1, -7.3, 0.1);

    mLayer.addLayer(topLayer);
    mLayer.addLayerWithTopRoughness(layer1, lr0);
    mLayer.addLayerWithTopRoughness(substrate, lr1);

    MultiLayer* mLayerClone = mLayer.clone();

    const LayerInterface* interface0 = mLayerClone->layerInterface(0);
    const LayerInterface* interface1 = mLayerClone->layerInterface(1);
    const LayerRoughness* roughness0 = interface0->getRoughness();
    const LayerRoughness* roughness1 = interface1->getRoughness();

    EXPECT_TRUE(roughness0);
    EXPECT_TRUE(roughness1);

    EXPECT_EQ(-2.1, roughness0->getSigma());
    EXPECT_EQ(7.3, roughness0->getHurstParameter());
    EXPECT_EQ(12.1, roughness0->getLatteralCorrLength());

    EXPECT_EQ(1.1, roughness1->getSigma());
    EXPECT_EQ(-7.3, roughness1->getHurstParameter());
    EXPECT_EQ(0.1, roughness1->getLatteralCorrLength());

    delete mLayerClone;
}

TEST_F(MultiLayerTest, MultiLayerCompositeTest)
{
    MultiLayer mLayer;
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    Material magMaterial0 = HomogeneousMaterial("MagMat0", 6e-4, 2e-8, magnetic_field);
    Material magMaterial1 = HomogeneousMaterial("MagMat1", -5.6, 10, magnetic_field);

    Layer layer1(iron, 10 * Units::nanometer);
    Layer layer2(magMaterial0, 20 * Units::nanometer);
    Layer layer3(magMaterial1, 30 * Units::nanometer);
    Layer layer4(stone, 40 * Units::nanometer);

    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(layer3);
    mLayer.addLayer(layer4);

    std::vector<const Layer*> layer_buffer;
    std::vector<const LayerInterface*> interface_buffer;
    int counter(0);

    std::vector<const INode*> children = mLayer.getChildren();
    for (size_t index = 0; index < children.size(); ++index) {
        const INode* sample = children[index];
        if (counter % 2 == 1) {
            const LayerInterface* interface = dynamic_cast<const LayerInterface*>(sample);
            EXPECT_TRUE(nullptr != interface);
            interface_buffer.push_back(interface);
        } else {
            const Layer* layer = dynamic_cast<const Layer*>(sample);
            EXPECT_TRUE(nullptr != layer);
            layer_buffer.push_back(layer);
        }
        counter++;
    }
    EXPECT_EQ(size_t(5), layer_buffer.size());
    EXPECT_EQ(size_t(4), interface_buffer.size());
    for (size_t i = 0; i < layer_buffer.size(); ++i) {
        EXPECT_EQ(double(i * 10), layer_buffer[i]->thickness());
    }
    for (size_t i = 0; i < interface_buffer.size(); ++i) {
        EXPECT_EQ(double((i + 1) * 10), interface_buffer[i]->bottomLayer()->thickness());
    }
}
