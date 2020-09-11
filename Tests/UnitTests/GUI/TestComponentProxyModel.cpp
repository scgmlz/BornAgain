#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/ComponentProxyModel.h"
#include "GUI/coregui/Models/ComponentProxyStrategy.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ProxyModelStrategy.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/Utils.h"
#include <QDebug>
#include <QSignalSpy>

class TestComponentProxyModel : public ::testing::Test
{
};

//! Empty proxy model.

TEST_F(TestComponentProxyModel, test_emptyModel)
{
    ComponentProxyModel proxy;
    EXPECT_EQ(proxy.rowCount(QModelIndex()), 0);
    EXPECT_EQ(proxy.columnCount(QModelIndex()), static_cast<int>(SessionFlags::MAX_COLUMNS));
    EXPECT_TRUE(proxy.sourceModel() == nullptr);
}

//! Set empty model to proxy.

TEST_F(TestComponentProxyModel, test_setModel)
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;

    QSignalSpy spy(&proxy, &ComponentProxyModel::modelReset);
    proxy.setSessionModel(&model);

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(proxy.rowCount(QModelIndex()), 0);
    EXPECT_EQ(proxy.columnCount(QModelIndex()), static_cast<int>(SessionFlags::MAX_COLUMNS));
    EXPECT_EQ(proxy.sourceModel(), &model);
}

//! Set model to proxy. Model already contains simple item.

TEST_F(TestComponentProxyModel, test_setModelWithItem)
{
    SessionModel model("TestModel");
    model.insertNewItem("Property");

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    EXPECT_EQ(model.rowCount(QModelIndex()), 1);
    EXPECT_EQ(model.columnCount(QModelIndex()), static_cast<int>(SessionFlags::MAX_COLUMNS));
    EXPECT_EQ(proxy.rowCount(QModelIndex()), 1);
    EXPECT_EQ(proxy.columnCount(QModelIndex()), static_cast<int>(SessionFlags::MAX_COLUMNS));
}

//! Set model to proxy. Model already contains VectorItem.

TEST_F(TestComponentProxyModel, test_setModelWithVector)
{
    const int ncols = static_cast<int>(SessionFlags::MAX_COLUMNS);

    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("Vector");
    item->setItemValue(VectorItem::P_X, 1.0);
    item->setItemValue(VectorItem::P_Y, 2.0);
    item->setItemValue(VectorItem::P_Z, 3.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    // rows, cols of root index
    EXPECT_EQ(model.rowCount(QModelIndex()), 1);
    EXPECT_EQ(model.columnCount(QModelIndex()), ncols);
    EXPECT_EQ(proxy.rowCount(QModelIndex()), 1);
    EXPECT_EQ(proxy.columnCount(QModelIndex()), ncols);

    // mapFromSource, mapToSource for VectorItem
    QModelIndex sourceVector = model.index(0, 0, QModelIndex());
    QModelIndex proxyVector = proxy.index(0, 0, QModelIndex());
    EXPECT_TRUE(sourceVector != proxyVector);
    EXPECT_TRUE(sourceVector.internalPointer() == proxyVector.internalPointer());
    EXPECT_EQ(proxyVector, proxy.mapFromSource(sourceVector));
    EXPECT_EQ(sourceVector, proxy.mapToSource(proxyVector));

    // rows, cols of VectorItem
    EXPECT_EQ(model.rowCount(sourceVector), 3); // x,y,z
    EXPECT_EQ(model.columnCount(sourceVector), ncols);
    EXPECT_EQ(proxy.rowCount(proxyVector), 3); // x,y,z
    EXPECT_EQ(proxy.columnCount(proxyVector), ncols);

    // second col for VectorItem
    QModelIndex sourceVector1 = model.index(0, 1, QModelIndex());
    QModelIndex proxyVector1 = proxy.index(0, 1, QModelIndex());
    EXPECT_TRUE(sourceVector1 != proxyVector1);
    EXPECT_TRUE(sourceVector1.internalPointer() == proxyVector1.internalPointer());
    EXPECT_EQ(proxyVector1, proxy.mapFromSource(sourceVector1));
    EXPECT_EQ(sourceVector1, proxy.mapToSource(proxyVector1));
    EXPECT_EQ(model.rowCount(sourceVector1), 0);
    EXPECT_EQ(model.columnCount(sourceVector1), 0);
    EXPECT_EQ(proxy.rowCount(proxyVector1), 0);
    EXPECT_EQ(proxy.columnCount(proxyVector1), 0);

    // mapFromSource, mapToSource for P_X
    QModelIndex sourceX = model.index(0, 0, sourceVector);
    QModelIndex proxyX = proxy.index(0, 0, proxyVector);
    EXPECT_TRUE(sourceX != proxyX);
    EXPECT_TRUE(sourceX.internalPointer() == proxyX.internalPointer());
    EXPECT_EQ(proxyX, proxy.mapFromSource(sourceX));
    EXPECT_EQ(sourceX, proxy.mapToSource(proxyX));
    EXPECT_TRUE(model.parent(sourceX) == sourceVector);
    EXPECT_TRUE(proxy.parent(proxyX) == proxyVector);

    // rows, cols of P_X
    EXPECT_EQ(model.rowCount(sourceX), 0);
    EXPECT_EQ(model.columnCount(sourceX), ncols);
    EXPECT_EQ(proxy.rowCount(proxyX), 0);
    EXPECT_EQ(proxy.columnCount(proxyX), ncols);

    // second col for P_X
    QModelIndex sourceX1 = model.index(0, 1, sourceVector);
    QModelIndex proxyX1 = proxy.index(0, 1, proxyVector);
    EXPECT_TRUE(sourceX1 != proxyX1);
    EXPECT_TRUE(sourceX1.internalPointer() == proxyX1.internalPointer());
    EXPECT_EQ(proxyX1, proxy.mapFromSource(sourceX1));
    EXPECT_EQ(sourceX1, proxy.mapToSource(proxyX1));
    EXPECT_EQ(model.rowCount(sourceX1), 0);
    EXPECT_EQ(model.columnCount(sourceX1), 0);
    EXPECT_EQ(proxy.rowCount(proxyX1), 0);
    EXPECT_EQ(proxy.columnCount(proxyX1), 0);

    EXPECT_TRUE(sourceX.sibling(sourceX.row(), 1) == sourceX1);
    EXPECT_TRUE(proxyX.sibling(proxyX.row(), 1) == proxyX1);

    // mapFromSource, mapToSource for P_Z
    QModelIndex sourceZ = model.index(2, 0, sourceVector);
    QModelIndex proxyZ = proxy.index(2, 0, proxyVector);
    EXPECT_TRUE(sourceZ != proxyZ);
    EXPECT_TRUE(sourceZ.internalPointer() == proxyZ.internalPointer());
    EXPECT_EQ(proxyZ, proxy.mapFromSource(sourceZ));
    EXPECT_EQ(sourceZ, proxy.mapToSource(proxyZ));

    // rows, cols of P_Z
    EXPECT_EQ(model.rowCount(sourceZ), 0);
    EXPECT_EQ(model.columnCount(sourceZ), ncols);
    EXPECT_EQ(proxy.rowCount(proxyZ), 0);
    EXPECT_EQ(proxy.columnCount(proxyZ), ncols);
}

//! Set model to proxy. Model already contains two PropertyItems. Checking data() method.

TEST_F(TestComponentProxyModel, test_displayRole)
{
    SessionModel model("TestModel");
    SessionItem* item1 = model.insertNewItem("Property");
    item1->setValue(1.0);
    SessionItem* item2 = model.insertNewItem("Property");
    item2->setValue(2.0);

    EXPECT_EQ(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    EXPECT_EQ(model.data(model.index(1, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    EXPECT_EQ(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    EXPECT_EQ(proxy.data(proxy.index(1, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);
}

//! Set model with item to proxy. Changing the data on source and checking change propagation.

TEST_F(TestComponentProxyModel, test_setData)
{
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem("Property");
    item->setValue(1.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    // checking initial data
    EXPECT_EQ(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    EXPECT_EQ(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);

    // changing data in source and listening
    QSignalSpy spySource(&model, &SessionModel::dataChanged);
    QSignalSpy spyProxy(&proxy, &ComponentProxyModel::dataChanged);
    EXPECT_TRUE(model.setData(model.index(0, 1, QModelIndex()), 2.0, Qt::DisplayRole));
    EXPECT_EQ(item->value().toDouble(), 2.0);

    // checking signaling of source
    EXPECT_EQ(spySource.count(), 1);
    QList<QVariant> arguments = spySource.takeFirst();
    EXPECT_EQ(arguments.size(), 3);
    EXPECT_EQ(arguments[0].toModelIndex(), model.index(0, 0, QModelIndex()));
    EXPECT_EQ(arguments[1].toModelIndex(), model.index(0, 1, QModelIndex()));

    // checking signaling of proxy
    EXPECT_EQ(spyProxy.count(), 1);
    EXPECT_EQ(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);

    // changing data in proxy
    EXPECT_TRUE(proxy.setData(proxy.index(0, 1, QModelIndex()), 3.0, Qt::DisplayRole));
    EXPECT_EQ(item->value().toDouble(), 3.0);
    EXPECT_EQ(spySource.count(), 1); // ?, sould be 2
    EXPECT_EQ(spyProxy.count(), 2);
    EXPECT_EQ(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 3.0);
    EXPECT_EQ(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 3.0);
}

//! Checks norification of proxy model then source inserts rows.

TEST_F(TestComponentProxyModel, test_insertRows)
{
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    EXPECT_TRUE(model.hasChildren(QModelIndex()) == false);
    EXPECT_TRUE(proxy.hasChildren(QModelIndex()) == false);

    QSignalSpy spyProxy(&proxy, &ComponentProxyModel::layoutChanged);

    // inserting item in the source
    model.insertNewItem("Property");
    EXPECT_EQ(spyProxy.count(), 1);
    EXPECT_EQ(proxy.rowCount(QModelIndex()), 1);
}

//! Checking the mapping of ComponentProxyStrategy in the case of ParticleItem inserted in
//! the source.

TEST_F(TestComponentProxyModel, test_componentStrategy)
{
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting particle
    SessionItem* item = model.insertNewItem("Particle");
    auto group = dynamic_cast<GroupItem*>(item->getItem(ParticleItem::P_FORM_FACTOR));
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    EXPECT_TRUE(ffItem->parent() == group);
    EXPECT_TRUE(ffItem->modelType() == "Cylinder");

    // original indices
    QModelIndex particleIndex = model.indexOfItem(item);
    QModelIndex groupIndex = model.indexOfItem(group);
    QModelIndex ffIndex = model.indexOfItem(ffItem);
    QModelIndex radiusIndex = model.indexOfItem(ffItem->getItem(CylinderItem::P_RADIUS));

    // proxy indices
    QModelIndex particleProxyIndex = proxy.mapFromSource(particleIndex);
    EXPECT_TRUE(particleProxyIndex.isValid());

    // Properties of CylinderItem should belong to group property
    QModelIndex groupProxyIndex = proxy.mapFromSource(groupIndex);
    EXPECT_TRUE(groupProxyIndex.isValid());
    EXPECT_TRUE(groupProxyIndex.parent() == particleProxyIndex);
    EXPECT_EQ(proxy.rowCount(groupProxyIndex), 2); // ff radius and height
    EXPECT_EQ(proxy.columnCount(groupProxyIndex), 2);

    // CylinderItem shouldn't exist anymore in proxy
    QModelIndex ffProxyIndex = proxy.mapFromSource(ffIndex);
    EXPECT_TRUE(ffProxyIndex.isValid() == false);

    QModelIndex radiusProxyIndex = proxy.mapFromSource(radiusIndex);
    EXPECT_TRUE(radiusProxyIndex.isValid() == true);
    EXPECT_TRUE(radiusProxyIndex.parent() == groupProxyIndex);
}

//! Checking the mapping of ComponentProxyStrategy in the case of ParticleItem inserted in
//! the source. We are changing Particle's form factor back and forth and checking for change
//! in GroupProperty.

TEST_F(TestComponentProxyModel, test_componentStrategyFormFactorChanges)
{
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting particle
    SessionItem* item = model.insertNewItem("Particle");
    auto group = dynamic_cast<GroupItem*>(item->getItem(ParticleItem::P_FORM_FACTOR));
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    EXPECT_TRUE(ffItem->parent() == group);
    EXPECT_TRUE(ffItem->modelType() == "Cylinder");

    // changing form factor type
    group->setCurrentType("FullSphere");

    QModelIndex groupProxyIndex = proxy.mapFromSource(model.indexOfItem(group));
    EXPECT_EQ(proxy.rowCount(groupProxyIndex), 1); // sphere radius
    EXPECT_EQ(proxy.columnCount(groupProxyIndex), 2);

    // changing back to Cylinder
    group->setCurrentType("Cylinder");
    groupProxyIndex = proxy.mapFromSource(model.indexOfItem(group));
    EXPECT_EQ(proxy.rowCount(groupProxyIndex), 2); // cylinder radius, length
    EXPECT_EQ(proxy.columnCount(groupProxyIndex), 2);
}

//! Checking setRootIndex: proxy model should contain only items corresponding
//! to rootIndex and its children. Adding simple PropertyItem.

TEST_F(TestComponentProxyModel, test_setRootPropertyItem)
{
    const int ncols = static_cast<int>(SessionFlags::MAX_COLUMNS);
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting simple property item
    SessionItem* item = model.insertNewItem("Property");
    item->setValue(42.0);
    proxy.setRootIndex(model.indexOfItem(item));

    EXPECT_EQ(model.rowCount(QModelIndex()), 1);
    EXPECT_EQ(model.columnCount(QModelIndex()), ncols);
    EXPECT_EQ(proxy.rowCount(QModelIndex()), 1);
    EXPECT_EQ(proxy.columnCount(QModelIndex()), ncols);

    EXPECT_TRUE(proxy.index(0, 0, QModelIndex())
                == proxy.mapFromSource(model.index(0, 0, QModelIndex())));
    EXPECT_TRUE(proxy.index(0, 1, QModelIndex())
                == proxy.mapFromSource(model.index(0, 1, QModelIndex())));
    EXPECT_TRUE(model.index(0, 0, QModelIndex())
                == proxy.mapToSource(proxy.index(0, 0, QModelIndex())));
    EXPECT_TRUE(proxy.index(0, 1, QModelIndex()).isValid());
    EXPECT_TRUE(model.index(0, 1, QModelIndex())
                == proxy.mapToSource(proxy.index(0, 1, QModelIndex())));

    EXPECT_EQ(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 42.0);
    EXPECT_EQ(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 42.0);
}

//! Checking setRootIndex: proxy model should contain only items corresponding
//! to rootIndex and its children. Adding MultiLayer with two layers and setting rootIndex
//! to one of the layer.

TEST_F(TestComponentProxyModel, test_setRootIndexLayer)
{

    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting multilayer with two layers
    auto multilayer = model.insertNewItem("MultiLayer");
    auto layer1 = model.insertNewItem("Layer", model.indexOfItem(multilayer));
    auto layout = model.insertNewItem("ParticleLayout", model.indexOfItem(layer1));
    model.insertNewItem("Layer", model.indexOfItem(multilayer));

    proxy.setRootIndex(model.indexOfItem(layer1));
    EXPECT_EQ(proxy.rowCount(QModelIndex()), 1);
    EXPECT_EQ(proxy.columnCount(QModelIndex()), 2);

    QModelIndex multilayerProxyIndex = proxy.mapFromSource(model.indexOfItem(multilayer));
    EXPECT_TRUE(multilayerProxyIndex.isValid() == false);

    QModelIndex layerProxyIndex = proxy.mapFromSource(model.indexOfItem(layer1));
    EXPECT_EQ(proxy.rowCount(layerProxyIndex), 4); // thickness, material, slices, roughness
    EXPECT_EQ(proxy.columnCount(layerProxyIndex), 2);
    EXPECT_TRUE(layerProxyIndex.isValid());
    EXPECT_TRUE(layerProxyIndex.parent() == QModelIndex());

    // ParticleLayout should be excluded from proxy tree
    QModelIndex layoutProxyIndex = proxy.mapFromSource(model.indexOfItem(layout));
    EXPECT_TRUE(layoutProxyIndex.isValid() == false);
}
