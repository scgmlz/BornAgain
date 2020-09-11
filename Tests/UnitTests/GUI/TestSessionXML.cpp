#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <memory>

namespace
{
QString itemToXML(SessionItem* item)
{
    QString result;
    QXmlStreamWriter writer(&result);
    SessionXML::writeTo(&writer, item);
    return result;
}

void itemFromXML(QString buffer, SessionItem* item)
{
    QXmlStreamReader reader(buffer);
    SessionXML::readItems(&reader, item);
}
} // namespace

class TestSessionXML : public ::testing::Test
{
};

//! Testing to/from xml: simple property item.

TEST_F(TestSessionXML, test_sessionItem)
{
    QString expected;

    SessionModel source("TestModel");
    source.insertNewItem("Property");

    expected = "<TestModel Name=\"DefaultName\">"
               "<Item ModelType=\"Property\" Tag=\"rootTag\" DisplayName=\"Property\"/>"
               "</TestModel>";
    EXPECT_EQ(itemToXML(source.rootItem()), expected);

    SessionModel target("TestModel");
    itemFromXML(expected, target.rootItem());

    EXPECT_EQ(target.rowCount(QModelIndex()), 1);
    SessionItem* newItem = target.itemForIndex(target.index(0, 0, QModelIndex()));
    EXPECT_EQ(newItem->modelType(), "Property");
    EXPECT_EQ(newItem->displayName(), "Property");
    EXPECT_FALSE(newItem->value().isValid());
}

//! Testing to/from xml: FullSphereItem

TEST_F(TestSessionXML, test_FullSphereItem)
{
    // source model, to xml
    SessionModel source("TestModel");
    SessionItem* sphere = source.insertNewItem("FullSphere");
    SessionItem* radius = sphere->getItem(FullSphereItem::P_RADIUS);
    QString buffer = itemToXML(source.rootItem());

    // target model, from xml
    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // checking top items in source and target models
    SessionItem* t_sphere = target.topItem();
    SessionItem* t_radius = t_sphere->getItem(FullSphereItem::P_RADIUS);

    EXPECT_EQ(sphere->parent()->tagFromItem(sphere), t_sphere->parent()->tagFromItem(t_sphere));
    EXPECT_EQ(sphere->displayName(), t_sphere->displayName());
    EXPECT_EQ(sphere->modelType(), t_sphere->modelType());
    EXPECT_EQ(sphere->numberOfChildren(), t_sphere->numberOfChildren());
    EXPECT_EQ(sphere->getItemValue(FullSphereItem::P_RADIUS),
              t_sphere->getItemValue(FullSphereItem::P_RADIUS));

    EXPECT_EQ(radius->parent()->tagFromItem(sphere), t_radius->parent()->tagFromItem(t_sphere));
    EXPECT_EQ(radius->displayName(), t_radius->displayName());
    EXPECT_EQ(radius->modelType(), t_radius->modelType());
    EXPECT_EQ(radius->numberOfChildren(), t_radius->numberOfChildren());
    EXPECT_EQ(radius->value().toDouble(), t_radius->value().toDouble());

    // final XML comparison
    EXPECT_EQ(buffer, itemToXML(target.rootItem()));
}

TEST_F(TestSessionXML, test_twoFullSphereItems)
{
    // source model, to xml
    SessionModel source("TestModel");
    SessionItem* sphere1 = source.insertNewItem("FullSphere");
    sphere1->setItemValue(FullSphereItem::P_RADIUS, 1.0);
    SessionItem* sphere2 = source.insertNewItem("FullSphere");
    sphere2->setItemValue(FullSphereItem::P_RADIUS, 2.0);
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    EXPECT_EQ(buffer, itemToXML(target.rootItem()));
}

TEST_F(TestSessionXML, test_emptyMultiLayer)
{
    SessionModel source("TestModel");
    source.insertNewItem("MultiLayer");
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    EXPECT_EQ(buffer, itemToXML(target.rootItem()));
}

TEST_F(TestSessionXML, test_Layer)
{
    SessionModel source("TestModel");
    source.insertNewItem("Layer");
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    EXPECT_EQ(buffer, itemToXML(target.rootItem()));
}

TEST_F(TestSessionXML, test_Particle)
{
    SessionModel source("TestModel");
    source.insertNewItem("Particle");
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    EXPECT_EQ(buffer, itemToXML(target.rootItem()));
}

TEST_F(TestSessionXML, test_ParticleWithFF)
{
    SessionModel source("TestModel");
    SessionItem* particle = source.insertNewItem("Particle");

    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, "AnisoPyramid");
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    EXPECT_EQ(buffer, itemToXML(target.rootItem()));
}
