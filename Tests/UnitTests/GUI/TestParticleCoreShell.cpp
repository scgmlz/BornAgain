#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QtTest>

using namespace SessionItemUtils;

class TestParticleCoreShell : public ::testing::Test
{
};

TEST_F(TestParticleCoreShell, test_moveCoreAndShell)
{
    SampleModel model;
    SessionItem* coreshell = model.insertNewItem("ParticleCoreShell");
    SessionItem* particle1 = model.insertNewItem("Particle");
    SessionItem* particle2 = model.insertNewItem("Particle");
    SessionItem* particle3 = model.insertNewItem("Particle");

    // empty coreshell particle
    EXPECT_EQ(particle1->parent(), model.rootItem());
    EXPECT_EQ(particle2->parent(), model.rootItem());
    EXPECT_EQ(particle3->parent(), model.rootItem());
    EXPECT_EQ(coreshell->getItem(ParticleCoreShellItem::T_CORE), nullptr);
    EXPECT_EQ(coreshell->getItem(ParticleCoreShellItem::T_SHELL), nullptr);

    // adding core
    model.moveItem(particle1, coreshell, -1, ParticleCoreShellItem::T_CORE);
    EXPECT_EQ(particle1->parent(), coreshell);
    EXPECT_EQ(coreshell->getItem(ParticleCoreShellItem::T_CORE), particle1);

    // adding shell
    model.moveItem(particle2, coreshell, -1, ParticleCoreShellItem::T_SHELL);
    EXPECT_EQ(particle2->parent(), coreshell);
    EXPECT_EQ(coreshell->getItem(ParticleCoreShellItem::T_SHELL), particle2);

    // adding another core, previous one should deattach
    model.moveItem(particle3, coreshell, -1, ParticleCoreShellItem::T_CORE);
    EXPECT_EQ(particle3->parent(), coreshell);
    EXPECT_EQ(coreshell->getItem(ParticleCoreShellItem::T_CORE), particle3);
    //    EXPECT_EQ(particle1->parent(), model.rootItem());
}

//! Checking that adding and removing core/shell leads to enabling/disabling of their position
//! and abundance properties.

TEST_F(TestParticleCoreShell, test_propertyAppearance)
{
    SampleModel model;

    // empty coreshell particle
    SessionItem* coreshell = model.insertNewItem("ParticleCoreShell");
    EXPECT_TRUE(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_EQ(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);
    EXPECT_TRUE(coreshell->getItem(ParticleItem::P_POSITION)->isEnabled());
    kvector_t pos = GetVectorItem(*coreshell, ParticleItem::P_POSITION);
    EXPECT_EQ(pos.x(), 0.0);
    EXPECT_EQ(pos.y(), 0.0);
    EXPECT_EQ(pos.z(), 0.0);

    // adding core, and checking that abundance is disabled
    SessionItem* core =
        model.insertNewItem("Particle", coreshell->index(), -1, ParticleCoreShellItem::T_CORE);
    EXPECT_FALSE(core->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_TRUE(core->getItem(ParticleItem::P_POSITION)->isEnabled());

    // removing core, checking that abundance restored
    coreshell->takeRow(ParentRow(*core));
    EXPECT_TRUE(core->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_TRUE(core->getItem(ParticleItem::P_POSITION)->isEnabled());
    delete core;

    // creating shell (not yet attached to the coreshell)
    SessionItem* shell = model.insertNewItem("Particle");
    SessionItem* positionItem = shell->getItem(ParticleItem::P_POSITION);
    // putting some values to position and abundance
    shell->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    positionItem->setItemValue(VectorItem::P_X, 1.0);

    // attaching shell to coreshell and checking abundance disabled
    model.moveItem(shell, coreshell, -1, ParticleCoreShellItem::T_SHELL);
    EXPECT_FALSE(shell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_FALSE(shell->getItem(ParticleItem::P_POSITION)->isEnabled());
    // checking that position and abundance values were reset to defaults
    EXPECT_EQ(positionItem->getItemValue(VectorItem::P_X).toDouble(), 0.0);
    EXPECT_EQ(shell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing shell and checking abundance, position restored
    coreshell->takeRow(ParentRow(*shell));
    EXPECT_TRUE(shell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_TRUE(shell->getItem(ParticleItem::P_POSITION)->isEnabled());
    delete shell;
}

//! Checking that abundance gets disabled in particle distribution context.

TEST_F(TestParticleCoreShell, test_distributionContext)
{
    SampleModel model;

    // coreshell particle
    SessionItem* coreshell = model.insertNewItem("ParticleCoreShell");
    coreshell->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    EXPECT_TRUE(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    EXPECT_EQ(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // create distribution, adding coreshell to it
    SessionItem* distribution = model.insertNewItem("ParticleDistribution");
    model.moveItem(coreshell, distribution, -1, ParticleDistributionItem::T_PARTICLES);
    // checking abundance has switched to defaults
    EXPECT_FALSE(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_EQ(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing coreshell
    distribution->takeRow(ParentRow(*coreshell));
    EXPECT_TRUE(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete coreshell;
}

//! Checking that abundance gets disabled in particle composition context.

TEST_F(TestParticleCoreShell, test_compositionContext)
{
    SampleModel model;

    // coreshell particle
    SessionItem* coreshell = model.insertNewItem("ParticleCoreShell");
    coreshell->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    EXPECT_TRUE(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_EQ(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // create composition, adding coreshell to it
    SessionItem* composition = model.insertNewItem("ParticleComposition");
    model.moveItem(coreshell, composition, -1, ParticleCompositionItem::T_PARTICLES);
    // checking abundance has switched to defaults
    EXPECT_FALSE(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    EXPECT_EQ(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing coreshell
    composition->takeRow(ParentRow(*coreshell));
    EXPECT_TRUE(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete coreshell;
}
