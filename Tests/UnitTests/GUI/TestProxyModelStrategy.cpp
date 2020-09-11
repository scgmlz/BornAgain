#include "GUI/coregui/Models/ComponentProxyModel.h"
#include "GUI/coregui/Models/ComponentProxyStrategy.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ProxyModelStrategy.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "Tests/GTestWrapper/google_test.h"

class TestProxyModelStrategy : public ::testing::Test
{
};

//! Checking the mapping in the case of PropertyItem inserted in the source.

TEST_F(TestProxyModelStrategy, test_identityStrategy)
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;
    IndentityProxyStrategy strategy;

    EXPECT_EQ(strategy.sourceToProxy().size(), 0);
    EXPECT_EQ(strategy.proxySourceParent().size(), 0);

    // building the map of empty source
    strategy.buildModelMap(&model, &proxy);
    EXPECT_EQ(strategy.sourceToProxy().size(), 0);
    EXPECT_EQ(strategy.proxySourceParent().size(), 0);

    // building map when simple item
    SessionItem* item = model.insertNewItem("Property");
    strategy.buildModelMap(&model, &proxy);
    EXPECT_EQ(strategy.sourceToProxy().size(), 2);
    EXPECT_EQ(strategy.proxySourceParent().size(), 2);

    // Checking of persistent indices of source and proxy
    auto it = strategy.sourceToProxy().begin();
    // index of source, col=0
    EXPECT_EQ(it.key().row(), 0);
    EXPECT_EQ(it.key().column(), 0);
    EXPECT_EQ(it.key().internalPointer(), item);
    // index of proxy, col=0
    EXPECT_EQ(it.value().row(), 0);
    EXPECT_EQ(it.value().column(), 0);
    EXPECT_EQ(it.value().internalPointer(), item);
    ++it;
    // index of source, col=1
    EXPECT_EQ(it.key().row(), 0);
    EXPECT_EQ(it.key().column(), 1);
    EXPECT_EQ(it.key().internalPointer(), item);
    // index of proxy, col=1
    EXPECT_EQ(it.value().row(), 0);
    EXPECT_EQ(it.value().column(), 1);
    EXPECT_EQ(it.value().internalPointer(), item);

    // Checking parent of proxy
    it = strategy.proxySourceParent().begin();
    EXPECT_EQ(it.key().row(), 0);
    EXPECT_EQ(it.key().column(), 0);
    EXPECT_EQ(it.key().internalPointer(), item);
    EXPECT_TRUE(it.value() == QModelIndex());
}

//! Checking the mapping in the case of ParticleItem inserted in the source.

TEST_F(TestProxyModelStrategy, test_identityStrategyParticle)
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;
    IndentityProxyStrategy strategy;

    SessionItem* item = model.insertNewItem("Particle");

    // building the map of source
    strategy.buildModelMap(&model, &proxy);
    SessionItem* group = item->getItem(ParticleItem::P_FORM_FACTOR);
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    EXPECT_TRUE(ffItem->parent() == group);
    EXPECT_TRUE(ffItem->modelType() == "Cylinder");

    // Checking "real" parent of proxy index related to form factor.
    // For identity model we are testing, it has to be just group property.
    auto ffProxyIndex = strategy.sourceToProxy().value(model.indexOfItem(ffItem));
    auto parentOfProxy = strategy.proxySourceParent().value(ffProxyIndex);
    EXPECT_TRUE(parentOfProxy == model.indexOfItem(group));

    // Checking "real" parent of Cylinders radius. It has to be CylinderItem
    SessionItem* radiusItem = ffItem->getItem(CylinderItem::P_RADIUS);
    auto radiusProxyIndex = strategy.sourceToProxy().value(model.indexOfItem(radiusItem));
    parentOfProxy = strategy.proxySourceParent().value(radiusProxyIndex);
    EXPECT_TRUE(parentOfProxy == model.indexOfItem(ffItem));
}

//! Checking the mapping of ComponentProxyStrategy in the case of ParticleItem inserted in
//! the source.

TEST_F(TestProxyModelStrategy, test_componentStrategyParticle)
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;
    ComponentProxyStrategy strategy;

    SessionItem* item = model.insertNewItem("Particle");

    // building the map of  source
    strategy.buildModelMap(&model, &proxy);
    SessionItem* group = item->getItem(ParticleItem::P_FORM_FACTOR);
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    EXPECT_TRUE(ffItem->parent() == group);
    EXPECT_TRUE(ffItem->modelType() == "Cylinder");

    // original indices
    QModelIndex particleIndex = model.indexOfItem(item);
    QModelIndex groupIndex = model.indexOfItem(group);
    QModelIndex ffIndex = model.indexOfItem(ffItem);
    QModelIndex radiusIndex = model.indexOfItem(ffItem->getItem(CylinderItem::P_RADIUS));

    // proxy indices
    QModelIndex particleProxyIndex = strategy.sourceToProxy().value(particleIndex);
    QModelIndex groupProxyIndex = strategy.sourceToProxy().value(groupIndex);
    QModelIndex ffProxyIndex = strategy.sourceToProxy().value(ffIndex);
    QModelIndex radiusProxyIndex = strategy.sourceToProxy().value(radiusIndex);
    EXPECT_TRUE(particleProxyIndex.isValid());
    EXPECT_TRUE(groupProxyIndex.isValid());
    EXPECT_TRUE(ffProxyIndex.isValid() == false); // ff is excluded from hierarchy
    EXPECT_TRUE(radiusProxyIndex.isValid());

    // Checking "real" parents of indices
    EXPECT_TRUE(strategy.proxySourceParent().value(ffProxyIndex) == QModelIndex());
    EXPECT_TRUE(strategy.proxySourceParent().value(radiusProxyIndex) == groupIndex);
    EXPECT_TRUE(strategy.proxySourceParent().value(groupProxyIndex) == particleIndex);
}

//! Checking setRootIndex: proxy model should contain only items corresponding
//! to rootIndex and its children.

TEST_F(TestProxyModelStrategy, test_setRootIndex)
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;
    ComponentProxyStrategy strategy;

    SessionItem* item = model.insertNewItem("Particle");
    SessionItem* group = item->getItem(ParticleItem::P_FORM_FACTOR);
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);

    QModelIndex particleIndex = model.indexOfItem(item);
    QModelIndex groupIndex = model.indexOfItem(group);
    QModelIndex ffIndex = model.indexOfItem(ffItem);
    QModelIndex radiusIndex = model.indexOfItem(ffItem->getItem(CylinderItem::P_RADIUS));

    // building the map of  source, groupItem will be rootIndex
    strategy.setRootIndex(model.indexOfItem(group));
    strategy.buildModelMap(&model, &proxy);

    // proxy indices
    QModelIndex particleProxyIndex = strategy.sourceToProxy().value(particleIndex);
    QModelIndex groupProxyIndex = strategy.sourceToProxy().value(groupIndex);
    QModelIndex ffProxyIndex = strategy.sourceToProxy().value(ffIndex);
    QModelIndex radiusProxyIndex = strategy.sourceToProxy().value(radiusIndex);
    EXPECT_TRUE(particleProxyIndex.isValid() == false); // particle is not in a tree
    EXPECT_TRUE(groupProxyIndex.isValid());
    EXPECT_EQ(groupProxyIndex.row(), 0);
    EXPECT_EQ(groupProxyIndex.column(), 0);
    EXPECT_TRUE(groupProxyIndex.parent() == QModelIndex());
    EXPECT_TRUE(ffProxyIndex.isValid() == false); // ff is excluded from hierarchy
    EXPECT_TRUE(radiusProxyIndex.isValid());

    // checking that new parent of groupItem is root
    EXPECT_TRUE(strategy.proxySourceParent().value(groupProxyIndex) == QModelIndex());
    EXPECT_TRUE(strategy.proxySourceParent().value(ffProxyIndex) == QModelIndex());
    EXPECT_TRUE(strategy.proxySourceParent().value(radiusProxyIndex) == groupIndex);
}
