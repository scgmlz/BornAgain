#ifndef LAYERTEST_H
#define LAYERTEST_H

#include "Layer.h"
#include "HomogeneousMaterial.h"
#include "ParticleLayout.h"
#include "Units.h"

class LayerTest : public ::testing::Test
{
 protected:
    LayerTest(){}
    virtual ~LayerTest(){}
};

TEST_F(LayerTest, LayerInitialState)
{
    Layer layer;
    EXPECT_EQ(nullptr, layer.getMaterial());
    EXPECT_EQ(nullptr, layer.getLayout(0));
    EXPECT_EQ(0, layer.getThickness());
    EXPECT_FALSE(layer.hasComputation());
    EXPECT_EQ(complex_t(1.0, 0.0), layer.getRefractiveIndex());
    EXPECT_EQ(0.0, layer.getTotalParticleSurfaceDensity(0));
    EXPECT_EQ("Layer", layer.getName());

    Layer* new_layer = layer.clone();
    EXPECT_EQ(nullptr, new_layer->getMaterial());
    EXPECT_EQ(nullptr, new_layer->getLayout(0));
    EXPECT_EQ(0, new_layer->getThickness());
    EXPECT_FALSE(new_layer->hasComputation());
    EXPECT_EQ(complex_t(1.0, 0.0), new_layer->getRefractiveIndex());
    EXPECT_EQ(0.0, new_layer->getTotalParticleSurfaceDensity(0));
    EXPECT_EQ("Layer", new_layer->getName());

    delete new_layer;
}

TEST_F(LayerTest, LayerGetAndSet)
{
    HomogeneousMaterial air("air",0,0);
    HomogeneousMaterial something("something",0,0.5);

    Layer layer(air, 10*Units::nanometer);
    EXPECT_EQ(air.getName(), layer.getMaterial()->getName());
    EXPECT_EQ(nullptr, layer.getLayout(0));
    EXPECT_EQ(10, layer.getThickness());
    EXPECT_FALSE(layer.hasComputation());
    EXPECT_EQ(complex_t(1,0), layer.getRefractiveIndex());
    EXPECT_EQ(0.0, layer.getTotalParticleSurfaceDensity(0));
    EXPECT_EQ("Layer", layer.getName());

    layer.setThickness(20.0);
    EXPECT_EQ(20, layer.getThickness());
    layer.setMaterial(something);
    EXPECT_EQ(something.getName(), layer.getMaterial()->getName());
    EXPECT_EQ("Layer", layer.getName());
    EXPECT_EQ(complex_t(1,0.5), layer.getRefractiveIndex());

    Layer* new_layer = layer.clone();
    EXPECT_EQ(something.getName(), new_layer->getMaterial()->getName());
    EXPECT_EQ(nullptr, new_layer->getLayout(0));
    EXPECT_EQ(20, new_layer->getThickness());
    EXPECT_FALSE(new_layer->hasComputation());
    EXPECT_EQ(complex_t(1,0.5), new_layer->getRefractiveIndex());
    EXPECT_EQ(0.0, new_layer->getTotalParticleSurfaceDensity(0));
    EXPECT_EQ("Layer", new_layer->getName());
    delete new_layer;
}


TEST_F(LayerTest, LayerAndDecoration)
{
    HomogeneousMaterial air("air",0,0);
    ParticleLayout* p_layout1 = new ParticleLayout();

    Layer layer(air, 10*Units::nanometer);
    layer.addLayout(*p_layout1);
    //EXPECT_EQ(decoration1, layer.getLayout());
    EXPECT_TRUE(layer.hasComputation());

    ParticleLayout layout2;
    layer.addLayout(layout2);
    EXPECT_EQ("ParticleLayout", layer.getLayout(1)->getName());
}

#endif // LAYERTEST_H
