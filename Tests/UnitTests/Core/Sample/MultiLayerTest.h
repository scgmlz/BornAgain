#ifndef MULTILAYERTEST_H
#define MULTILAYERTEST_H

#include "BornAgainNamespace.h"
#include "HomogeneousMagneticMaterial.h"
#include "Layer.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"

class MultiLayerTest : public ::testing::Test
{
protected:
    MultiLayerTest()
        : air("air", 0, 1.0)
        , iron("iron", 0, 1.51)
        , chromium("chromium", 0, 3.68)
        , stone("stone", 0, 1.6)
        , topLayer(air, 0*Units::nanometer)
        , layer1(iron, 20*Units::nanometer)
        , layer2(chromium, 40*Units::nanometer)
        , substrate(stone, 0*Units::nanometer) {}
    void set_four() {
        mLayer.addLayer(topLayer);
        mLayer.addLayer(layer1);
        mLayer.addLayer(layer2);
        mLayer.addLayer(substrate);
    }

    MultiLayer mLayer;
    const HomogeneousMaterial air, iron, chromium, stone;
    Layer topLayer, layer1, layer2, substrate;
};

TEST_F(MultiLayerTest, BasicProperty)
{
    //check default properties
    EXPECT_EQ(BornAgain::MultiLayerType, mLayer.getName());
    EXPECT_EQ(0.0, mLayer.getCrossCorrLength());
    EXPECT_EQ(size_t(0), mLayer.getNumberOfLayers());
    EXPECT_EQ(size_t(0), mLayer.getNumberOfInterfaces());

    //set parameter
    mLayer.setParameterValue(BornAgain::CrossCorrelationLength, 2.54);
    EXPECT_EQ(2.54,mLayer.getCrossCorrLength());

    // adding layers
    mLayer.addLayer(topLayer);
    EXPECT_EQ(size_t(1), mLayer.getNumberOfLayers());
    EXPECT_EQ(size_t(0), mLayer.getNumberOfInterfaces());

    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(substrate);
    EXPECT_EQ(size_t(4), mLayer.getNumberOfLayers());
    EXPECT_EQ(size_t(3), mLayer.getNumberOfInterfaces());
}

TEST_F(MultiLayerTest, LayerThicknesses)
{
    set_four();

    //check layer thickness
    EXPECT_EQ( 0.0, mLayer.getLayerThickness(0));
    EXPECT_EQ(20.0, mLayer.getLayerThickness(1));
    EXPECT_EQ(40.0, mLayer.getLayerThickness(2));
    EXPECT_EQ( 0.0, mLayer.getLayerThickness(3));

    //check bottomZ value
    EXPECT_EQ(  0.0, mLayer.getLayerBottomZ(0));
    EXPECT_EQ(-20.0, mLayer.getLayerBottomZ(1));
    EXPECT_EQ(-60.0, mLayer.getLayerBottomZ(2));
    EXPECT_EQ(-60.0, mLayer.getLayerBottomZ(3));

    //set layer thickness
    mLayer.setLayerThickness(1, 45.0);
    EXPECT_EQ(45.0, mLayer.getLayerThickness(1));

    EXPECT_EQ(  0.0, mLayer.getLayerBottomZ(0));
    EXPECT_EQ(-45.0, mLayer.getLayerBottomZ(1));
    EXPECT_EQ(-85.0, mLayer.getLayerBottomZ(2));
    EXPECT_EQ(-85.0, mLayer.getLayerBottomZ(3));
}

TEST_F(MultiLayerTest, CheckAllLayers)
{
    set_four();

    //check individual layer
    const Layer* got0 = mLayer.getLayer(0);
    EXPECT_EQ(BornAgain::LayerType, got0->getName());
    EXPECT_EQ(0, got0->getThickness());
    EXPECT_EQ(topLayer.getMaterial()->getName(), got0->getMaterial()->getName());

    const Layer* got1 = mLayer.getLayer(1);
    EXPECT_EQ(BornAgain::LayerType, got1->getName());
    EXPECT_EQ(20, got1->getThickness());
    EXPECT_EQ(layer1.getMaterial()->getName(), got1->getMaterial()->getName());

    const Layer* got2 = mLayer.getLayer(2);
    EXPECT_EQ(BornAgain::LayerType, got2->getName());
    EXPECT_EQ(40, got2->getThickness());
    EXPECT_EQ(layer2.getMaterial()->getName(), got2->getMaterial()->getName());

    const Layer* got3 = mLayer.getLayer(3);
    EXPECT_EQ(BornAgain::LayerType, got3->getName());
    EXPECT_EQ(0, got3->getThickness());
    EXPECT_EQ(substrate.getMaterial()->getName(), got3->getMaterial()->getName());
}

TEST_F(MultiLayerTest, LayerInterfaces)
{
    set_four();

    //check interfaces
    const LayerInterface* interface0 = mLayer.getLayerInterface(0);
    EXPECT_TRUE(nullptr!=interface0);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface0->getName());
    EXPECT_EQ(nullptr, interface0->getRoughness());
    EXPECT_EQ(topLayer.getMaterial()->getName(),
              interface0->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer1.getMaterial()->getName(),
              interface0->getLayerBottom()->getMaterial()->getName());

    const LayerInterface* interface1 = mLayer.getLayerInterface(1);
    EXPECT_TRUE(nullptr!=interface1);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface1->getName());
    EXPECT_EQ(nullptr, interface1->getRoughness());
    EXPECT_EQ(layer1.getMaterial()->getName(),
              interface1->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer2.getMaterial()->getName(),
              interface1->getLayerBottom()->getMaterial()->getName());

    const LayerInterface* interface2 = mLayer.getLayerInterface(2);
    EXPECT_TRUE(nullptr!=interface2);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface2->getName());
    EXPECT_EQ(nullptr, interface2->getRoughness());
    EXPECT_EQ(layer2.getMaterial()->getName(),
              interface2->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(substrate.getMaterial()->getName(),
              interface2->getLayerBottom()->getMaterial()->getName());

    //bottom interface
    const LayerInterface* interfaceBottom = mLayer.getLayerBottomInterface(0);
    EXPECT_TRUE(nullptr!=interfaceBottom);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceBottom->getName());
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());
    EXPECT_EQ(topLayer.getMaterial()->getName(),
              interfaceBottom->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer1.getMaterial()->getName(),
              interfaceBottom->getLayerBottom()->getMaterial()->getName());

    //top interface
    const LayerInterface* interfaceTop = mLayer.getLayerTopInterface(3);
    EXPECT_TRUE(nullptr!=interfaceTop);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceTop->getName());
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());
    EXPECT_EQ(layer2.getMaterial()->getName(),
              interfaceTop->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(substrate.getMaterial()->getName(),
              interfaceTop->getLayerBottom()->getMaterial()->getName());

    //null interface
    const LayerInterface* interfaceTopNull = mLayer.getLayerTopInterface(0);
    EXPECT_TRUE(nullptr==interfaceTopNull);

    const LayerInterface* interfaceBottomNull = mLayer.getLayerBottomInterface(3);
    EXPECT_TRUE(nullptr==interfaceBottomNull);
}

TEST_F(MultiLayerTest, Clone)
{
    set_four();

    MultiLayer* mLayerClone = mLayer.clone();

    //check properties
    EXPECT_EQ(BornAgain::MultiLayerType, mLayerClone->getName());
    EXPECT_EQ(0.0,mLayerClone->getCrossCorrLength());
    EXPECT_EQ(size_t(4), mLayerClone->getNumberOfLayers());
    EXPECT_EQ(size_t(3), mLayerClone->getNumberOfInterfaces());

    //check layer thickness
    EXPECT_EQ(topLayer.getThickness(), mLayerClone->getLayerThickness(0));
    EXPECT_EQ(layer1.getThickness(), mLayerClone->getLayerThickness(1));
    EXPECT_EQ(layer2.getThickness(), mLayerClone->getLayerThickness(2));
    EXPECT_EQ(substrate.getThickness(), mLayerClone->getLayerThickness(3));

    //check bottomZ value
    EXPECT_EQ(mLayer.getLayerBottomZ(0), mLayerClone->getLayerBottomZ(0));
    EXPECT_EQ(mLayer.getLayerBottomZ(1), mLayerClone->getLayerBottomZ(1));
    EXPECT_EQ(mLayer.getLayerBottomZ(2), mLayerClone->getLayerBottomZ(2));
    EXPECT_EQ(mLayer.getLayerBottomZ(3), mLayerClone->getLayerBottomZ(3));

    //check individual layer
    const Layer* layerCopy0 = mLayerClone->getLayer(0);
    EXPECT_EQ(topLayer.getName(), layerCopy0->getName());
    EXPECT_EQ(topLayer.getThickness(), layerCopy0->getThickness());
    EXPECT_EQ(topLayer.getMaterial()->getName(), layerCopy0->getMaterial()->getName());

    const Layer* layerCopy1 = mLayerClone->getLayer(1);
    EXPECT_EQ(layer1.getName(), layerCopy1->getName());
    EXPECT_EQ(layer1.getThickness(), layerCopy1->getThickness());
    EXPECT_EQ(layer1.getMaterial()->getName(), layerCopy1->getMaterial()->getName());

    const Layer* layerCopy2 = mLayerClone->getLayer(2);
    EXPECT_EQ(layer2.getName(), layerCopy2->getName());
    EXPECT_EQ(layer2.getThickness(), layerCopy2->getThickness());
    EXPECT_EQ(layer2.getMaterial()->getName(), layerCopy2->getMaterial()->getName());

    const Layer* layerCopy3 = mLayerClone->getLayer(3);
    EXPECT_EQ(substrate.getName(), layerCopy3->getName());
    EXPECT_EQ(substrate.getThickness(), layerCopy3->getThickness());
    EXPECT_EQ(substrate.getMaterial()->getName(), layerCopy3->getMaterial()->getName());

    //check interfaces
    const LayerInterface* interface0 = mLayerClone->getLayerInterface(0);
    EXPECT_TRUE(nullptr!=interface0);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface0->getName());
    EXPECT_EQ(nullptr, interface0->getRoughness());
    EXPECT_EQ(topLayer.getMaterial()->getName(), interface0->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer1.getMaterial()->getName(), interface0->getLayerBottom()->getMaterial()->getName());

    const LayerInterface* interface1 = mLayerClone->getLayerInterface(1);
    EXPECT_TRUE(nullptr!=interface1);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface1->getName());
    EXPECT_EQ(nullptr, interface1->getRoughness());
    EXPECT_EQ(layer1.getMaterial()->getName(), interface1->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer2.getMaterial()->getName(), interface1->getLayerBottom()->getMaterial()->getName());

    const LayerInterface* interface2 = mLayerClone->getLayerInterface(2);
    EXPECT_TRUE(nullptr!=interface2);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface2->getName());
    EXPECT_EQ(nullptr, interface2->getRoughness());
    EXPECT_EQ(layer2.getMaterial()->getName(), interface2->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(substrate.getMaterial()->getName(), interface2->getLayerBottom()->getMaterial()->getName());

    //top interface
    const LayerInterface* interfaceBottom = mLayerClone->getLayerTopInterface(1);
    EXPECT_TRUE(nullptr!=interfaceBottom);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceBottom->getName());
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());
    EXPECT_EQ(topLayer.getMaterial()->getName(), interfaceBottom->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer1.getMaterial()->getName(), interfaceBottom->getLayerBottom()->getMaterial()->getName());

    //Bottom interface
    const LayerInterface* interfaceTop = mLayerClone->getLayerBottomInterface(2);
    EXPECT_TRUE(nullptr!=interfaceTop);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceTop->getName());
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());
    EXPECT_EQ(layer2.getMaterial()->getName(), interfaceTop->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(substrate.getMaterial()->getName(), interfaceTop->getLayerBottom()->getMaterial()->getName());

    //null interface
    const LayerInterface* interfaceTopNull = mLayerClone->getLayerTopInterface(0);
    EXPECT_TRUE(nullptr==interfaceTopNull);

    const LayerInterface* interfaceBottomNull = mLayerClone->getLayerBottomInterface(3);
    EXPECT_TRUE(nullptr==interfaceBottomNull);

    delete mLayerClone;
}

TEST_F(MultiLayerTest, CloneInvertB)
{
    set_four();

    MultiLayer* mLayerClone = mLayer.cloneInvertB();

    //check properties
    EXPECT_EQ(BornAgain::MultiLayerType, mLayerClone->getName());
    EXPECT_EQ(0.0,mLayerClone->getCrossCorrLength());
    EXPECT_EQ(size_t(4), mLayerClone->getNumberOfLayers());
    EXPECT_EQ(size_t(3), mLayerClone->getNumberOfInterfaces());

    //check layer thickness
    EXPECT_EQ(topLayer.getThickness(), mLayerClone->getLayerThickness(0));
    EXPECT_EQ(layer1.getThickness(), mLayerClone->getLayerThickness(1));
    EXPECT_EQ(layer2.getThickness(), mLayerClone->getLayerThickness(2));
    EXPECT_EQ(substrate.getThickness(), mLayerClone->getLayerThickness(3));

    //check bottomZ value
    EXPECT_EQ(mLayer.getLayerBottomZ(0), mLayerClone->getLayerBottomZ(0));
    EXPECT_EQ(mLayer.getLayerBottomZ(1), mLayerClone->getLayerBottomZ(1));
    EXPECT_EQ(mLayer.getLayerBottomZ(2), mLayerClone->getLayerBottomZ(2));
    EXPECT_EQ(mLayer.getLayerBottomZ(3), mLayerClone->getLayerBottomZ(3));

    //check individual layer
    const Layer* layerCopy0 = mLayerClone->getLayer(0);
    EXPECT_EQ(topLayer.getName(), layerCopy0->getName());
    EXPECT_EQ(topLayer.getThickness(), layerCopy0->getThickness());
    EXPECT_EQ(topLayer.getMaterial()->getName(), layerCopy0->getMaterial()->getName());

    const Layer* layerCopy1 = mLayerClone->getLayer(1);
    EXPECT_EQ(layer1.getName(), layerCopy1->getName());
    EXPECT_EQ(layer1.getThickness(), layerCopy1->getThickness());
    EXPECT_EQ(layer1.getMaterial()->getName(), layerCopy1->getMaterial()->getName());

    const Layer* layerCopy2 = mLayerClone->getLayer(2);
    EXPECT_EQ(layer2.getName(), layerCopy2->getName());
    EXPECT_EQ(layer2.getThickness(), layerCopy2->getThickness());
    EXPECT_EQ(layer2.getMaterial()->getName(), layerCopy2->getMaterial()->getName());

    const Layer* layerCopy3 = mLayerClone->getLayer(3);
    EXPECT_EQ(substrate.getName(), layerCopy3->getName());
    EXPECT_EQ(substrate.getThickness(), layerCopy3->getThickness());
    EXPECT_EQ(substrate.getMaterial()->getName(), layerCopy3->getMaterial()->getName());

    //check interfaces
    const LayerInterface* interface0 = mLayerClone->getLayerInterface(0);
    EXPECT_TRUE(nullptr!=interface0);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface0->getName());
    EXPECT_EQ(nullptr, interface0->getRoughness());
    EXPECT_EQ(topLayer.getMaterial()->getName(), interface0->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer1.getMaterial()->getName(), interface0->getLayerBottom()->getMaterial()->getName());

    const LayerInterface* interface1 = mLayerClone->getLayerInterface(1);
    EXPECT_TRUE(nullptr!=interface1);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface1->getName());
    EXPECT_EQ(nullptr, interface1->getRoughness());
    EXPECT_EQ(layer1.getMaterial()->getName(), interface1->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer2.getMaterial()->getName(), interface1->getLayerBottom()->getMaterial()->getName());

    const LayerInterface* interface2 = mLayerClone->getLayerInterface(2);
    EXPECT_TRUE(nullptr!=interface2);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface2->getName());
    EXPECT_EQ(nullptr, interface2->getRoughness());
    EXPECT_EQ(layer2.getMaterial()->getName(), interface2->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(substrate.getMaterial()->getName(), interface2->getLayerBottom()->getMaterial()->getName());

    //top interface
    const LayerInterface* interfaceBottom = mLayerClone->getLayerTopInterface(1);
    EXPECT_TRUE(nullptr!=interfaceBottom);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceBottom->getName());
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());
    EXPECT_EQ(topLayer.getMaterial()->getName(), interfaceBottom->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(layer1.getMaterial()->getName(), interfaceBottom->getLayerBottom()->getMaterial()->getName());

    //Bottom interface
    const LayerInterface* interfaceTop = mLayerClone->getLayerBottomInterface(2);
    EXPECT_TRUE(nullptr!=interfaceTop);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceTop->getName());
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());
    EXPECT_EQ(layer2.getMaterial()->getName(), interfaceTop->getLayerTop()->getMaterial()->getName());
    EXPECT_EQ(substrate.getMaterial()->getName(), interfaceTop->getLayerBottom()->getMaterial()->getName());

    //null interface
    const LayerInterface* interfaceTopNull = mLayerClone->getLayerTopInterface(0);
    EXPECT_TRUE(nullptr==interfaceTopNull);

    const LayerInterface* interfaceBottomNull = mLayerClone->getLayerBottomInterface(3);
    EXPECT_TRUE(nullptr==interfaceBottomNull);

    delete mLayerClone;
}

TEST_F(MultiLayerTest, WithRoughness)
{
    //LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength);
    LayerRoughness lr(1.1, -7.3, 0.1);
    mLayer.addLayer(topLayer);
    mLayer.addLayerWithTopRoughness(layer1,lr);
    mLayer.addLayer(substrate);

    const LayerInterface* interface0 = mLayer.getLayerInterface(0);
    const LayerInterface* interface1 = mLayer.getLayerInterface(1);

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
    mLayer.addLayerWithTopRoughness(layer1,lr0);
    mLayer.addLayerWithTopRoughness(substrate,lr1);

    MultiLayer* mLayerClone = mLayer.clone();

    const LayerInterface* interface0 = mLayerClone->getLayerInterface(0);
    const LayerInterface* interface1 = mLayerClone->getLayerInterface(1);
    const LayerRoughness* roughness0 = interface0->getRoughness();
    const LayerRoughness* roughness1 = interface1->getRoughness();

    EXPECT_TRUE(roughness0);
    EXPECT_TRUE(roughness1);

    EXPECT_EQ( -2.1, roughness0->getSigma());
    EXPECT_EQ(  7.3, roughness0->getHurstParameter());
    EXPECT_EQ( 12.1, roughness0->getLatteralCorrLength());

    EXPECT_EQ(  1.1, roughness1->getSigma());
    EXPECT_EQ( -7.3, roughness1->getHurstParameter());
    EXPECT_EQ(  0.1, roughness1->getLatteralCorrLength());

    delete mLayerClone;
}

TEST_F(MultiLayerTest, CloneInvertBWithRoughness)
{
    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(stone, 5*Units::nanometer);

    //LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength);
    LayerRoughness lr0(-2.1, 7.3,  12.1);
    LayerRoughness lr1(1.1, -7.3, 0.1);

    mLayer.addLayer(topLayer);
    mLayer.addLayerWithTopRoughness(layer1,lr0);
    mLayer.addLayerWithTopRoughness(layer2,lr1);

    MultiLayer* mLayerClone = mLayer.cloneInvertB();

    const LayerInterface* interface0 = mLayerClone->getLayerInterface(0);
    const LayerInterface* interface1 = mLayerClone->getLayerInterface(1);
    const LayerRoughness* roughness0 = interface0->getRoughness();
    const LayerRoughness* roughness1 = interface1->getRoughness();

    EXPECT_EQ( -2.1, roughness0->getSigma());
    EXPECT_EQ(  7.3, roughness0->getHurstParameter());
    EXPECT_EQ( 12.1, roughness0->getLatteralCorrLength());

    EXPECT_EQ(  1.1, roughness1->getSigma());
    EXPECT_EQ( -7.3, roughness1->getHurstParameter());
    EXPECT_EQ(  0.1, roughness1->getLatteralCorrLength());

    delete mLayerClone;
}

TEST_F(MultiLayerTest, WithMagneticMaterial)
{
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);
    HomogeneousMagneticMaterial magMaterial1("MagMat1", -5.6, 10, magnetic_field);

    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(stone, 30*Units::nanometer);
    Layer layer3(magMaterial0, 20*Units::nanometer);
    Layer layer4(magMaterial1, 0*Units::nanometer);

    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    EXPECT_FALSE(mLayer.containsMagneticMaterial());

    mLayer.addLayer(layer3);
    mLayer.addLayer(layer4);
    EXPECT_TRUE(mLayer.containsMagneticMaterial());
}

TEST_F(MultiLayerTest, CloneWithMagneticMaterial)
{
    kvector_t magnetic_field(1.1, 2.1, -5.1);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);

    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(magMaterial0, 20*Units::nanometer);
    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);

    MultiLayer* mLayerClone = mLayer.clone();
    EXPECT_TRUE(mLayerClone->containsMagneticMaterial());
    delete mLayerClone;
}

TEST_F(MultiLayerTest, CloneInvertBMagneticMaterial)
{
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);

    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(magMaterial0, 20*Units::nanometer);

    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);

    MultiLayer* mLayerClone = mLayer.cloneInvertB();
    EXPECT_TRUE(mLayerClone->containsMagneticMaterial());
    delete mLayerClone;
}

TEST_F(MultiLayerTest, MultiLayerCompositeTest)
{
    MultiLayer mLayer;
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);
    HomogeneousMagneticMaterial magMaterial1("MagMat1", -5.6, 10, magnetic_field);

    Layer layer1(iron, 10*Units::nanometer);
    Layer layer2(magMaterial0, 20*Units::nanometer);
    Layer layer3(magMaterial1, 30*Units::nanometer);
    Layer layer4(stone, 40*Units::nanometer);

    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(layer3);
    mLayer.addLayer(layer4);

    std::vector<Layer *> layer_buffer;
    std::vector<LayerInterface *> interface_buffer;
    int counter(0);
    for(size_t index=0; index<mLayer.size();++index)
    {
        ISample *sample = mLayer[index];
        if(counter%2 == 1)
        {
            LayerInterface *interface = dynamic_cast<LayerInterface *>(sample);
            EXPECT_TRUE(nullptr != interface);
            interface_buffer.push_back(interface);
        } else {
            Layer *layer = dynamic_cast<Layer *>(sample);
            EXPECT_TRUE(nullptr != layer);
            layer_buffer.push_back(layer);
        }
        counter++;
    }
    EXPECT_EQ( size_t(5), layer_buffer.size());
    EXPECT_EQ( size_t(4), interface_buffer.size());
    for(size_t i=0; i<layer_buffer.size(); ++i) {
        EXPECT_EQ( double(i*10), layer_buffer[i]->getThickness());
    }
    for(size_t i=0; i<interface_buffer.size(); ++i) {
        EXPECT_EQ( double((i+1)*10), interface_buffer[i]->getLayerBottom()->getThickness());
    }
}

TEST_F(MultiLayerTest, MultiLayerZtoIndex)
{
    MultiLayer mLayer;

    // index_0
    // -----------------  0.0
    // index_1
    // -----------------  -10.0
    // index_2
    // -----------------  -30.0
    // index_3
    // -----------------  -60.0
    // index_4
    Layer layer1(air, 10*Units::nanometer);
    Layer layer2(air, 20*Units::nanometer);
    Layer layer3(air, 30*Units::nanometer);
    Layer layer4(air, 0*Units::nanometer);
    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(layer3);
    mLayer.addLayer(layer4);

    EXPECT_EQ(size_t(0), mLayer.zToLayerIndex(1.0));
    EXPECT_EQ(size_t(0), mLayer.zToLayerIndex(0.0));
    EXPECT_EQ(size_t(1), mLayer.zToLayerIndex(-1.0));
    EXPECT_EQ(size_t(1), mLayer.zToLayerIndex(-9.0));
    EXPECT_EQ(size_t(1), mLayer.zToLayerIndex(-10.0));
    EXPECT_EQ(size_t(2), mLayer.zToLayerIndex(-11.0));
    EXPECT_EQ(size_t(2), mLayer.zToLayerIndex(-30.0));
    EXPECT_EQ(size_t(3), mLayer.zToLayerIndex(-31.0));
    EXPECT_EQ(size_t(3), mLayer.zToLayerIndex(-60.0));
    EXPECT_EQ(size_t(4), mLayer.zToLayerIndex(-61.0));
}

#endif // MULTILAYERTEST_H
