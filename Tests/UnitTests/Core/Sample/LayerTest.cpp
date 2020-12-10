#include "Sample/Multilayer/Layer.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Tests/GTestWrapper/google_test.h"

class LayerTest : public ::testing::Test {};

TEST_F(LayerTest, LayerGetAndSet) {
    Material vacuum = HomogeneousMaterial("Vacuum", 0, 0);
    Layer layer(vacuum, 10 * Units::nm);
    EXPECT_EQ(vacuum, *layer.material());
    EXPECT_EQ(0u, layer.layouts().size());
    EXPECT_EQ(10, layer.thickness());
    EXPECT_EQ(layer.numberOfLayouts(), 0u);

    layer.setThickness(20.0);
    EXPECT_EQ(vacuum, *layer.material());
    EXPECT_EQ(20, layer.thickness());

    std::unique_ptr<Layer> clone(layer.clone());
    EXPECT_EQ(vacuum, *clone->material());
    EXPECT_EQ(0u, clone->layouts().size());
    EXPECT_EQ(20, clone->thickness());
    EXPECT_EQ(clone->numberOfLayouts(), 0u);
}

TEST_F(LayerTest, LayerAndDecoration) {
    Material vacuum = HomogeneousMaterial("Vacuum", 0, 0);
    std::unique_ptr<ParticleLayout> layout1(new ParticleLayout());

    Layer layer(vacuum, 10 * Units::nm);
    layer.addLayout(*layout1);
    EXPECT_EQ(layer.numberOfLayouts(), 1u);

    ParticleLayout layout2;
    layer.addLayout(layout2);
    EXPECT_EQ(layer.numberOfLayouts(), 2u);
}

TEST_F(LayerTest, getChildren) {
    Layer layer(HomogeneousMaterial("Vacuum", 0.0, 0.0));

    std::vector<const INode*> children = layer.getChildren();
    EXPECT_EQ(children.size(), 0u);

    // children after adding layout
    layer.addLayout(ParticleLayout());
    layer.addLayout(ParticleLayout());

    children = layer.getChildren();
    EXPECT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0), layer.layouts()[0]);
    EXPECT_EQ(children.at(1), layer.layouts()[1]);
}
