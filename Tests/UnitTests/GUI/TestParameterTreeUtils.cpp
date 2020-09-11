#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/ParameterTreeUtils.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "Tests/GTestWrapper/google_test.h"

namespace
{
const QStringList expectedParticleParameterNames = {
    "Particle/Cylinder/Radius",   "Particle/Cylinder/Height",   "Particle/Abundance",
    "Particle/Position Offset/X", "Particle/Position Offset/Y", "Particle/Position Offset/Z"};

const QStringList expectedParticleParameterTranslations = {
    "Particle/Cylinder/Radius", "Particle/Cylinder/Height", "Particle/Abundance",
    "Particle/PositionX",       "Particle/PositionY",       "Particle/PositionZ"};

} // namespace

class TestParameterTreeUtils : public ::testing::Test
{
};

//! Tests parameter names of given item.

TEST_F(TestParameterTreeUtils, test_parameterTreeNames)
{
    SampleModel model;

    SessionItem* layer = model.insertNewItem("Layer");
    EXPECT_EQ(ParameterTreeUtils::parameterTreeNames(layer), QStringList() << "Layer/Thickness");

    SessionItem* particle = model.insertNewItem("Particle");
    EXPECT_EQ(ParameterTreeUtils::parameterTreeNames(particle), expectedParticleParameterNames);
}

//! Tests translated parameter names of given item.

TEST_F(TestParameterTreeUtils, test_parameterTranslatedNames)
{
    SampleModel model;

    SessionItem* particle = model.insertNewItem("Particle");

    EXPECT_EQ(ParameterTreeUtils::translatedParameterTreeNames(particle),
              expectedParticleParameterTranslations);
}

//! Tests translated parameter names of given item.

TEST_F(TestParameterTreeUtils, test_linkItemFromParameterName)
{
    SampleModel model;

    SessionItem* particle = model.insertNewItem("Particle");

    auto ffItem = static_cast<FormFactorItem*>(particle->getGroupItem(ParticleItem::P_FORM_FACTOR));
    ASSERT(ffItem);
    EXPECT_EQ(ffItem->modelType(), "Cylinder");

    EXPECT_EQ(ffItem->getItem(CylinderItem::P_RADIUS),
              ParameterTreeUtils::parameterNameToLinkedItem("Particle/Cylinder/Radius", particle));
    EXPECT_EQ(ffItem->getItem(CylinderItem::P_HEIGHT),
              ParameterTreeUtils::parameterNameToLinkedItem("Particle/Cylinder/Height", particle));
    EXPECT_EQ(
        particle->getItem(ParticleItem::P_POSITION)->getItem(VectorItem::P_X),
        ParameterTreeUtils::parameterNameToLinkedItem("Particle/Position Offset/X", particle));
}
