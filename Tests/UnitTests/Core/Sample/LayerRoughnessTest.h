#ifndef LAYERROUGHNESSTEST_H
#define LAYERROUGHNESSTEST_H

#include "LayerRoughness.h"
#include "BornAgainNamespace.h"
#include "ParameterPattern.h"

class LayerRoughnessTest : public ::testing::Test
{
 protected:
    LayerRoughnessTest(){}
};

TEST_F(LayerRoughnessTest , LayerRoughnessInitial)
{
    //test with default parameter
    LayerRoughness roughness;
    EXPECT_EQ(0.0, roughness.getSigma());
    EXPECT_EQ(0.0, roughness.getHurstParameter());
    EXPECT_EQ(0.0, roughness.getLatteralCorrLength());
    EXPECT_EQ(BornAgain::LayerBasicRoughnessType, roughness.getName());

    //set new parameter
    roughness.setSigma(1.1);
    EXPECT_EQ(1.1, roughness.getSigma());

    roughness.setHurstParameter(1.2);
    EXPECT_EQ(1.2, roughness.getHurstParameter());

    roughness.setLatteralCorrLength(1.3);
    EXPECT_EQ(1.3, roughness.getLatteralCorrLength());

    //test with given parameter
    LayerRoughness roughness2(2.1, 2.2, 2.3);
    EXPECT_EQ(2.1, roughness2.getSigma());
    EXPECT_EQ(2.2, roughness2.getHurstParameter());
    EXPECT_EQ(2.3, roughness2.getLatteralCorrLength());
    EXPECT_EQ(BornAgain::LayerBasicRoughnessType, roughness.getName());
}

//test clone LayerRoughness
TEST_F(LayerRoughnessTest , LayerRoughnessClone)
{
    LayerRoughness original(3.1, 3.2, 3.3);

    LayerRoughness *clone = original.clone();
    EXPECT_EQ(clone->getSigma(), original.getSigma());
    EXPECT_EQ(clone->getHurstParameter(), original.getHurstParameter());
    EXPECT_EQ(clone->getLatteralCorrLength(), original.getLatteralCorrLength());
    EXPECT_EQ(clone->getName(), original.getName());
    delete clone;
}

//test parameter pool
TEST_F(LayerRoughnessTest , LayerRoughnessPool)
{
    LayerRoughness roughnessPool;
    EXPECT_EQ(0.0, roughnessPool.getSigma());
    EXPECT_EQ(0.0, roughnessPool.getHurstParameter());
    EXPECT_EQ(0.0, roughnessPool.getLatteralCorrLength());

    ParameterPattern pattern_sigma, pattern_hurst, pattern_corrlength;
    pattern_sigma.add(BornAgain::LayerBasicRoughnessType).add(BornAgain::Sigma);
    pattern_hurst.add(BornAgain::LayerBasicRoughnessType).add(BornAgain::Hurst);
    pattern_corrlength.add(BornAgain::LayerBasicRoughnessType).add(BornAgain::CorrelationLength);
    roughnessPool.setParameterValue(pattern_sigma.toStdString(), 4.1);
    roughnessPool.setParameterValue(pattern_hurst.toStdString(), 4.2);
    roughnessPool.setParameterValue(pattern_corrlength.toStdString(), 4.3);

    EXPECT_EQ(4.1, roughnessPool.getSigma());
    EXPECT_EQ(4.2, roughnessPool.getHurstParameter());
    EXPECT_EQ(4.3, roughnessPool.getLatteralCorrLength());
    EXPECT_EQ(BornAgain::LayerBasicRoughnessType, roughnessPool.getName());
}

#endif // LAYERROUGHNESSTEST_H
