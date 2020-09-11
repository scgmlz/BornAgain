#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QtTest>

using SessionItemUtils::ParentRow;

class TestMapperCases : public ::testing::Test
{
};

TEST_F(TestMapperCases, test_ParticeleCompositionUpdate)
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem("MultiLayer");
    SessionItem* layer = model.insertNewItem("Layer", multilayer->index());
    SessionItem* layout = model.insertNewItem("ParticleLayout", layer->index());

    // composition added to layout should have abundance enabled
    SessionItem* compositionFree = model.insertNewItem("ParticleComposition", layout->index());
    EXPECT_TRUE(compositionFree->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

    // composition added to distribution should have abundance disabled
    SessionItem* distribution = model.insertNewItem("ParticleDistribution", layout->index());
    SessionItem* composition = model.insertNewItem("ParticleComposition", distribution->index());
    EXPECT_TRUE(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);

    composition = distribution->takeRow(ParentRow(*composition));
    EXPECT_TRUE(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete composition;
}

TEST_F(TestMapperCases, test_SimulationOptionsComputationToggle)
{
    DocumentModel model;
    model.insertNewItem("SimulationOptions");

    SimulationOptionsItem* item = model.simulationOptionsItem();

    ComboProperty combo =
        item->getItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD).value<ComboProperty>();
    EXPECT_EQ(combo.getValue(), "Analytical");
    EXPECT_TRUE(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == false);

    combo.setValue("Monte-Carlo Integration");
    item->setItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD, combo.variant());
    EXPECT_TRUE(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == true);
}
