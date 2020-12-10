#include "Sample/Multilayer/MultiLayer.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayerUtils.h"
#include "Sample/Slice/LayerInterface.h"
#include "Sample/Slice/LayerRoughness.h"
#include "Tests/GTestWrapper/google_test.h"

class MultiLayerTest : public ::testing::Test {
protected:
    MultiLayerTest()
        // The following delta, beta are all unphysical. Values don't matter here.
        : air(HomogeneousMaterial("Vacuum", 1e-6, 9e-4))
        , iron(HomogeneousMaterial("iron", 2e-5, 8e-5))
        , chromium(HomogeneousMaterial("chromium", 3e-7, 7e-6))
        , stone(HomogeneousMaterial("stone", 4e-4, 8e-7))
        , topLayer(air, 0 * Units::nm)
        , layer1(iron, 20 * Units::nm)
        , layer2(chromium, 40 * Units::nm)
        , substrate(stone, 0 * Units::nm) {}
    void set_four() {
        mLayer.addLayer(topLayer);
        mLayer.addLayer(layer1);
        mLayer.addLayer(layer2);
        mLayer.addLayer(substrate);
    }

    MultiLayer mLayer;
    const Material air, iron, chromium, stone;
    Layer topLayer, layer1, layer2, substrate;
};

TEST_F(MultiLayerTest, BasicProperty) {
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

TEST_F(MultiLayerTest, LayerThicknesses) {
    set_four();

    // check layer thickness
    EXPECT_EQ(mLayer.layer(0)->thickness(), 0);
    EXPECT_EQ(mLayer.layer(1)->thickness(), 20);
    EXPECT_EQ(mLayer.layer(2)->thickness(), 40);
    EXPECT_EQ(mLayer.layer(3)->thickness(), 0);
}

TEST_F(MultiLayerTest, CheckAllLayers) {
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

TEST_F(MultiLayerTest, LayerInterfaces) {
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
}

TEST_F(MultiLayerTest, Clone) {
    set_four();

    MultiLayer* mLayerClone = mLayer.clone();

    // check properties
    EXPECT_EQ(0.0, mLayerClone->crossCorrLength());
    EXPECT_EQ(size_t(4), mLayerClone->numberOfLayers());

    // check layer thickness
    EXPECT_EQ(topLayer.thickness(), mLayerClone->layer(0)->thickness());
    EXPECT_EQ(layer1.thickness(), mLayerClone->layer(1)->thickness());
    EXPECT_EQ(layer2.thickness(), mLayerClone->layer(2)->thickness());
    EXPECT_EQ(substrate.thickness(), mLayerClone->layer(3)->thickness());

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

    delete mLayerClone;
}

TEST_F(MultiLayerTest, WithRoughness) {
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

TEST_F(MultiLayerTest, CloneWithRoughness) {
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

TEST_F(MultiLayerTest, MultiLayerCompositeTest) {
    MultiLayer mLayer;
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    Material magMaterial0 = HomogeneousMaterial("MagMat0", 6e-4, 2e-8, magnetic_field);
    Material magMaterial1 = HomogeneousMaterial("MagMat1", -5.6, 10, magnetic_field);

    Layer layer1(iron, 10 * Units::nm);
    Layer layer2(magMaterial0, 20 * Units::nm);
    Layer layer3(magMaterial1, 30 * Units::nm);
    Layer layer4(stone, 40 * Units::nm);

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
