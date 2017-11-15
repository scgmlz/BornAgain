#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "ComponentProxyModel.h"
#include "VectorItem.h"
#include "ProxyModelStrategy.h"
#include "ComponentProxyStrategy.h"
#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "GroupItem.h"
#include <QSignalSpy>
#include <QDebug>

class TestComponentProxyModel : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_emptyModel();
    void test_setModel();
    void test_setModelWithItem();
    void test_setModelWithVector();
    void test_displayRole();
    void test_setData();
    void test_insertRows();
    void test_componentStrategy();
    void test_componentStrategyFormFactorChanges();
    void test_setRootPropertyItem();
    void test_setRootIndexLayer();
};

//! Empty proxy model.

inline void TestComponentProxyModel::test_emptyModel()
{
    ComponentProxyModel proxy;
    QCOMPARE(proxy.rowCount(QModelIndex()), 0);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QVERIFY(proxy.sourceModel() == nullptr);
}

//! Set empty model to proxy.

inline void TestComponentProxyModel::test_setModel()
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;

    QSignalSpy spy(&proxy, &ComponentProxyModel::modelReset);
    proxy.setSessionModel(&model);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(proxy.rowCount(QModelIndex()), 0);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QCOMPARE(proxy.sourceModel(), &model);
}

//! Set model to proxy. Model already contains simple item.

inline void TestComponentProxyModel::test_setModelWithItem()
{
    SessionModel model("TestModel");
    model.insertNewItem(Constants::PropertyType);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    QCOMPARE(model.rowCount(QModelIndex()), 1);
    QCOMPARE(model.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
}

//! Set model to proxy. Model already contains VectorItem.

inline void TestComponentProxyModel::test_setModelWithVector()
{
    const int ncols = static_cast<int>(SessionModel::MAX_COLUMNS);

    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::VectorType);
    item->setItemValue(VectorItem::P_X, 1.0);
    item->setItemValue(VectorItem::P_Y, 2.0);
    item->setItemValue(VectorItem::P_Z, 3.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    // rows, cols of root index
    QCOMPARE(model.rowCount(QModelIndex()), 1);
    QCOMPARE(model.columnCount(QModelIndex()), ncols);
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
    QCOMPARE(proxy.columnCount(QModelIndex()), ncols);

    // mapFromSource, mapToSource for VectorItem
    QModelIndex sourceVector = model.index(0, 0, QModelIndex());
    QModelIndex proxyVector = proxy.index(0, 0, QModelIndex());
    QVERIFY(sourceVector != proxyVector);
    QVERIFY(sourceVector.internalPointer() == proxyVector.internalPointer());
    QCOMPARE(proxyVector, proxy.mapFromSource(sourceVector));
    QCOMPARE(sourceVector, proxy.mapToSource(proxyVector));

    // rows, cols of VectorItem
    QCOMPARE(model.rowCount(sourceVector), 3); // x,y,z
    QCOMPARE(model.columnCount(sourceVector), ncols);
    QCOMPARE(proxy.rowCount(proxyVector), 3); // x,y,z
    QCOMPARE(proxy.columnCount(proxyVector), ncols);

    // second col for VectorItem
    QModelIndex sourceVector1 = model.index(0, 1, QModelIndex());
    QModelIndex proxyVector1 = proxy.index(0, 1, QModelIndex());
    QVERIFY(sourceVector1 != proxyVector1);
    QVERIFY(sourceVector1.internalPointer() == proxyVector1.internalPointer());
    QCOMPARE(proxyVector1, proxy.mapFromSource(sourceVector1));
    QCOMPARE(sourceVector1, proxy.mapToSource(proxyVector1));
    QCOMPARE(model.rowCount(sourceVector1), 0);
    QCOMPARE(model.columnCount(sourceVector1), 0);
    QCOMPARE(proxy.rowCount(proxyVector1), 0);
    QCOMPARE(proxy.columnCount(proxyVector1), 0);

    // mapFromSource, mapToSource for P_X
    QModelIndex sourceX = model.index(0, 0, sourceVector);
    QModelIndex proxyX = proxy.index(0, 0, proxyVector);
    QVERIFY(sourceX != proxyX);
    QVERIFY(sourceX.internalPointer() == proxyX.internalPointer());
    QCOMPARE(proxyX, proxy.mapFromSource(sourceX));
    QCOMPARE(sourceX, proxy.mapToSource(proxyX));
    QVERIFY(model.parent(sourceX) == sourceVector);
    QVERIFY(proxy.parent(proxyX) == proxyVector);

    // rows, cols of P_X
    QCOMPARE(model.rowCount(sourceX), 0);
    QCOMPARE(model.columnCount(sourceX), ncols);
    QCOMPARE(proxy.rowCount(proxyX), 0);
    QCOMPARE(proxy.columnCount(proxyX), ncols);

    // second col for P_X
    QModelIndex sourceX1 = model.index(0, 1, sourceVector);
    QModelIndex proxyX1 = proxy.index(0, 1, proxyVector);
    QVERIFY(sourceX1 != proxyX1);
    QVERIFY(sourceX1.internalPointer() == proxyX1.internalPointer());
    QCOMPARE(proxyX1, proxy.mapFromSource(sourceX1));
    QCOMPARE(sourceX1, proxy.mapToSource(proxyX1));
    QCOMPARE(model.rowCount(sourceX1), 0);
    QCOMPARE(model.columnCount(sourceX1), 0);
    QCOMPARE(proxy.rowCount(proxyX1), 0);
    QCOMPARE(proxy.columnCount(proxyX1), 0);

    QVERIFY(sourceX.sibling(sourceX.row(), 1) == sourceX1);
    QVERIFY(proxyX.sibling(proxyX.row(), 1) == proxyX1);

    // mapFromSource, mapToSource for P_Z
    QModelIndex sourceZ = model.index(2, 0, sourceVector);
    QModelIndex proxyZ = proxy.index(2, 0, proxyVector);
    QVERIFY(sourceZ != proxyZ);
    QVERIFY(sourceZ.internalPointer() == proxyZ.internalPointer());
    QCOMPARE(proxyZ, proxy.mapFromSource(sourceZ));
    QCOMPARE(sourceZ, proxy.mapToSource(proxyZ));

    // rows, cols of P_Z
    QCOMPARE(model.rowCount(sourceZ), 0);
    QCOMPARE(model.columnCount(sourceZ), ncols);
    QCOMPARE(proxy.rowCount(proxyZ), 0);
    QCOMPARE(proxy.columnCount(proxyZ), ncols);
}

//! Set model to proxy. Model already contains two PropertyItems. Checking data() method.

inline void TestComponentProxyModel::test_displayRole()
{
    SessionModel model("TestModel");
    SessionItem* item1 = model.insertNewItem(Constants::PropertyType);
    item1->setValue(1.0);
    SessionItem* item2 = model.insertNewItem(Constants::PropertyType);
    item2->setValue(2.0);

    QCOMPARE(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    QCOMPARE(model.data(model.index(1, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    QCOMPARE(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    QCOMPARE(proxy.data(proxy.index(1, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);
}

//! Set model with item to proxy. Changing the data on source and checking change propagation.

inline void TestComponentProxyModel::test_setData()
{
    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::PropertyType);
    item->setValue(1.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    // checking initial data
    QCOMPARE(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    QCOMPARE(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);

    // changing data in source and listening
    QSignalSpy spySource(&model, &SessionModel::dataChanged);
    QSignalSpy spyProxy(&proxy, &ComponentProxyModel::dataChanged);
    QVERIFY(model.setData(model.index(0, 1, QModelIndex()), 2.0, Qt::DisplayRole));
    QCOMPARE(item->value().toDouble(), 2.0);

    // checking signaling of source
    QCOMPARE(spySource.count(), 1);
    QList<QVariant> arguments = spySource.takeFirst();
    QCOMPARE(arguments.size(), 3);
    QCOMPARE(arguments[0].toModelIndex(), model.index(0, 0, QModelIndex()));
    QCOMPARE(arguments[1].toModelIndex(), model.index(0, 1, QModelIndex()));

    // checking signaling of proxy
    QCOMPARE(spyProxy.count(), 1);
    QCOMPARE(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);

    // changing data in proxy
    QVERIFY(proxy.setData(proxy.index(0, 1, QModelIndex()), 3.0, Qt::DisplayRole));
    QCOMPARE(item->value().toDouble(), 3.0);
    QCOMPARE(spySource.count(), 1); // ?, sould be 2
    QCOMPARE(spyProxy.count(), 2);
    QCOMPARE(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 3.0);
    QCOMPARE(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 3.0);
}

//! Checks norification of proxy model then source inserts rows.

inline void TestComponentProxyModel::test_insertRows()
{
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    QVERIFY(model.hasChildren(QModelIndex()) == false);
    QVERIFY(proxy.hasChildren(QModelIndex()) == false);

    QSignalSpy spyProxy(&proxy, &ComponentProxyModel::layoutChanged);

    // inserting item in the source
    model.insertNewItem(Constants::PropertyType);
    QCOMPARE(spyProxy.count(), 1);
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
}

//! Checking the mapping of ComponentProxyStrategy in the case of ParticleItem inserted in
//! the source.

inline void TestComponentProxyModel::test_componentStrategy()
{
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting particle
    SessionItem* item = model.insertNewItem(Constants::ParticleType);
    auto group = dynamic_cast<GroupItem*>(item->getItem(ParticleItem::P_FORM_FACTOR));
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    QVERIFY(ffItem->parent() == group);
    QVERIFY(ffItem->modelType() == Constants::CylinderType);

    // original indices
    QModelIndex particleIndex = model.indexOfItem(item);
    QModelIndex groupIndex = model.indexOfItem(group);
    QModelIndex ffIndex = model.indexOfItem(ffItem);
    QModelIndex radiusIndex = model.indexOfItem(ffItem->getItem(CylinderItem::P_RADIUS));

    // proxy indices
    QModelIndex particleProxyIndex = proxy.mapFromSource(particleIndex);
    QVERIFY(particleProxyIndex.isValid());

    // Properties of CylinderItem should belong to group property
    QModelIndex groupProxyIndex = proxy.mapFromSource(groupIndex);
    QVERIFY(groupProxyIndex.isValid());
    QVERIFY(groupProxyIndex.parent() == particleProxyIndex);
    QCOMPARE(proxy.rowCount(groupProxyIndex), 2); // ff radius and height
    QCOMPARE(proxy.columnCount(groupProxyIndex), 2);

    // CylinderItem shouldn't exist anymore in proxy
    QModelIndex ffProxyIndex =  proxy.mapFromSource(ffIndex);
    QVERIFY(ffProxyIndex.isValid() == false);

    QModelIndex radiusProxyIndex = proxy.mapFromSource(radiusIndex);
    QVERIFY(radiusProxyIndex.isValid() == true);
    QVERIFY(radiusProxyIndex.parent() == groupProxyIndex);
}

//! Checking the mapping of ComponentProxyStrategy in the case of ParticleItem inserted in
//! the source. We are changing Particle's formfactor back and forth and checking for change
//! in GroupProperty.

inline void TestComponentProxyModel::test_componentStrategyFormFactorChanges()
{
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting particle
    SessionItem* item = model.insertNewItem(Constants::ParticleType);
    auto group = dynamic_cast<GroupItem*>(item->getItem(ParticleItem::P_FORM_FACTOR));
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    QVERIFY(ffItem->parent() == group);
    QVERIFY(ffItem->modelType() == Constants::CylinderType);

    // changing form factor type
    group->setCurrentType(Constants::FullSphereType);

    QModelIndex groupProxyIndex = proxy.mapFromSource(model.indexOfItem(group));
    QCOMPARE(proxy.rowCount(groupProxyIndex), 1); // sphere radius
    QCOMPARE(proxy.columnCount(groupProxyIndex), 2);

    // changing back to Cylinder
    group->setCurrentType(Constants::CylinderType);
    groupProxyIndex = proxy.mapFromSource(model.indexOfItem(group));
    QCOMPARE(proxy.rowCount(groupProxyIndex), 2); // cylinder radius, length
    QCOMPARE(proxy.columnCount(groupProxyIndex), 2);
}

//! Checking setRootIndex: proxy model should contain only items corresponding
//! to rootIndex and its children. Adding simple PropertyItem.

inline void TestComponentProxyModel::test_setRootPropertyItem()
{
    const int ncols = static_cast<int>(SessionModel::MAX_COLUMNS);
    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting simple property item
    SessionItem* item = model.insertNewItem(Constants::PropertyType);
    item->setValue(42.0);
    proxy.setRootIndex(model.indexOfItem(item));

    QCOMPARE(model.rowCount(QModelIndex()), 1);
    QCOMPARE(model.columnCount(QModelIndex()), ncols);
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
    QCOMPARE(proxy.columnCount(QModelIndex()), ncols);

    QVERIFY(proxy.index(0,0,QModelIndex()) == proxy.mapFromSource(model.index(0,0,QModelIndex())));
    QVERIFY(proxy.index(0,1,QModelIndex()) == proxy.mapFromSource(model.index(0,1,QModelIndex())));
    QVERIFY(model.index(0,0,QModelIndex()) == proxy.mapToSource(proxy.index(0,0,QModelIndex())));
    QVERIFY(proxy.index(0,1,QModelIndex()).isValid());
    QVERIFY(model.index(0,1,QModelIndex()) == proxy.mapToSource(proxy.index(0,1,QModelIndex())));

    QCOMPARE(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 42.0);
    QCOMPARE(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 42.0);
}

//! Checking setRootIndex: proxy model should contain only items corresponding
//! to rootIndex and its children. Adding MultiLayer with two layers and setting rootIndex
//! to one of the layer.

inline void TestComponentProxyModel::test_setRootIndexLayer()
{

    SessionModel model("TestModel");

    ComponentProxyModel proxy;
    proxy.setProxyStrategy(new ComponentProxyStrategy);
    proxy.setSessionModel(&model);

    // inserting multilayer with two layers
    SessionItem* multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem* layer1 = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));
    model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    proxy.setRootIndex(model.indexOfItem(layer1));
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
    QCOMPARE(proxy.columnCount(QModelIndex()), 2);

    QModelIndex multilayerProxyIndex = proxy.mapFromSource(model.indexOfItem(multilayer));
    QVERIFY(multilayerProxyIndex.isValid() == false);

    QModelIndex layerProxyIndex = proxy.mapFromSource(model.indexOfItem(layer1));
    QCOMPARE(proxy.rowCount(layerProxyIndex), 4); // thickness, material, slices, roughness
    QCOMPARE(proxy.columnCount(layerProxyIndex), 2);
    QVERIFY(layerProxyIndex.isValid());
    QVERIFY(layerProxyIndex.parent() == QModelIndex());
}
