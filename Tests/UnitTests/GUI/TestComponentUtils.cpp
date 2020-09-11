#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QDebug>

class TestComponentUtils : public ::testing::Test
{
};

//! Testing component items of particle item.

TEST_F(TestComponentUtils, test_componentItems)
{
    SessionModel model("TestModel");

    SessionItem* particle = model.insertNewItem("Particle");
    SessionItem* group = particle->getItem(ParticleItem::P_FORM_FACTOR);
    SessionItem* ffItem = particle->getGroupItem(ParticleItem::P_FORM_FACTOR);

    QList<const SessionItem*> expectedList = QList<const SessionItem*>()
                                             << group << ffItem->getItem(CylinderItem::P_RADIUS)
                                             << ffItem->getItem(CylinderItem::P_HEIGHT)
                                             << particle->getItem(ParticleItem::P_MATERIAL)
                                             << particle->getItem(ParticleItem::P_ABUNDANCE)
                                             << particle->getItem(ParticleItem::P_POSITION);

    auto itemList = ComponentUtils::componentItems(*particle);
    EXPECT_EQ(itemList.size(), 6);
    EXPECT_EQ(itemList, expectedList);
}

TEST_F(TestComponentUtils, test_componentItemsFFChange)
{
    SessionModel model("TestModel");

    SessionItem* particle = model.insertNewItem("Particle");
    SessionItem* group = particle->getItem(ParticleItem::P_FORM_FACTOR);

    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, "FullSphere");
    SessionItem* sphereItem = particle->getGroupItem(ParticleItem::P_FORM_FACTOR);

    QList<const SessionItem*> expectedList =
        QList<const SessionItem*>() << group << sphereItem->getItem(FullSphereItem::P_RADIUS)
                                    << particle->getItem(ParticleItem::P_MATERIAL)
                                    << particle->getItem(ParticleItem::P_ABUNDANCE)
                                    << particle->getItem(ParticleItem::P_POSITION);

    auto itemList = ComponentUtils::componentItems(*particle);
    EXPECT_EQ(itemList.size(), 5);
    EXPECT_EQ(itemList, expectedList);
}
