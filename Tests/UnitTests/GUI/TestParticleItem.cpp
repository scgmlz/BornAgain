#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "Tests/GTestWrapper/google_test.h"

using namespace SessionItemUtils;

class TestParticleItem : public ::testing::Test
{
};

TEST_F(TestParticleItem, test_InitialState)
{
    SampleModel model;
    SessionItem* item = model.insertNewItem("Particle");

    EXPECT_EQ(item->displayName(), "Particle");
    EXPECT_EQ(item->displayName(), item->itemName());
    // xpos, ypos, P_FORM_FACTOR, P_MATERIAL, P_ABUNDANCE, P_POSITION
    EXPECT_EQ(item->children().size(), 6);
    EXPECT_EQ(item->defaultTag(), ParticleItem::T_TRANSFORMATION);

    GroupItem* group = dynamic_cast<GroupItem*>(item->getItem(ParticleItem::P_FORM_FACTOR));
    EXPECT_EQ(group->displayName(), ParticleItem::P_FORM_FACTOR);
    EXPECT_EQ(group->children().size(), 1);
}

TEST_F(TestParticleItem, test_compositionContext)
{
    SampleModel model;
    SessionItem* particle = model.insertNewItem("Particle");
    particle->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    EXPECT_TRUE(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // adding particle to composition, checking that abundance is default
    SessionItem* composition = model.insertNewItem("ParticleComposition");
    model.moveItem(particle, composition, -1, ParticleCompositionItem::T_PARTICLES);
    EXPECT_FALSE(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing particle, checking that abundance is enabled again
    composition->takeRow(ParentRow(*particle));
    EXPECT_TRUE(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete particle;
}

TEST_F(TestParticleItem, test_distributionContext)
{
    SampleModel model;
    SessionItem* particle = model.insertNewItem("Particle");
    particle->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    EXPECT_TRUE(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // adding particle to distribution, checking that abundance is default
    SessionItem* distribution = model.insertNewItem("ParticleDistribution");
    model.moveItem(particle, distribution, -1, ParticleDistributionItem::T_PARTICLES);
    EXPECT_TRUE(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);
    EXPECT_EQ(particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing particle, checking that abundance is enabled again
    distribution->takeRow(ParentRow(*particle));
    EXPECT_TRUE(particle->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    delete particle;
}
