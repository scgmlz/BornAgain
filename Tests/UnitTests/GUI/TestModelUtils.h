#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "VectorItem.h"
#include "LayerItem.h"
#include <QVector>
#include <QDebug>

class TestModelUtils : public QObject
{
    Q_OBJECT
private:

    //! Returns true if model contains given item using iterate_if procedure.
    bool modelContainsItem(SessionModel* model, SessionItem* selectedItem)
    {
        bool result = false;
        ModelUtils::iterate_if(QModelIndex(), model, [&](const QModelIndex& index) -> bool {
            SessionItem* item = model->itemForIndex(index);
            if(item == selectedItem)
                result = true;
            return item->isVisible();
        });
        return result;
    }

private slots:
    void test_emptyModel();
    void test_vectorItem();
    void test_iterateIf();
};

//! Testing iteration over empty model.

inline void TestModelUtils::test_emptyModel()
{
    SessionModel model("TestModel");

    QVector<QModelIndex> indices;

    ModelUtils::iterate(QModelIndex(), &model, [&](const QModelIndex& index){
        indices.push_back(index);
    });

    QCOMPARE(indices.size(), 0);
}

//! Testing iteration over the model with one VectorItem inserted.

inline void TestModelUtils::test_vectorItem()
{
    SessionModel model("TestModel");
    SessionItem* vectorItem = model.insertNewItem(Constants::VectorType);

    QVector<QModelIndex> indices;

    // checking indices visited during iteration
    ModelUtils::iterate(QModelIndex(), &model, [&](const QModelIndex& index){
        indices.push_back(index);
    });
    QCOMPARE(indices.size(), 8); // (VectorItem, P_X, P_Y, P_Z) x (row, col)

    indices.clear();
    ModelUtils::iterate(QModelIndex(), &model, [&](const QModelIndex& index){
        if (index.column() == 0)
            indices.push_back(index);
    });

    // checking SessionItems visited during the iteration
    QCOMPARE(indices.size(), 4); // (VectorItem, P_X, P_Y, P_Z) x (row, col)
    QCOMPARE(model.itemForIndex(indices.front()), vectorItem);
    QCOMPARE(model.itemForIndex(indices.back()), vectorItem->getItem(VectorItem::P_Z));
}

//! Tests iteration when some children is invisible.

inline void TestModelUtils::test_iterateIf()
{
    SessionModel model("TestModel");
    SessionItem* multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem* layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));
    SessionItem* thicknessItem = layer->getItem(LayerItem::P_THICKNESS);

    layer->setVisible(true);
    QVERIFY(modelContainsItem(&model, layer) == true);
    QVERIFY(modelContainsItem(&model, thicknessItem) == true);

    // Setting layer invisible will hide its children from iteration.
    // Layer itself still will be visible.
    layer->setVisible(false);

    layer->setVisible(false);
    QVERIFY(modelContainsItem(&model, layer) == true);
    QVERIFY(modelContainsItem(&model, thicknessItem) == false);
}
