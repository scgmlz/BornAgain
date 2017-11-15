#include <QtTest>
#include "SessionItemUtils.h"
#include "SessionModel.h"
#include "SessionItem.h"
#include "VectorItem.h"
#include "item_constants.h"

class TestSessionItemUtils : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_ParentVisibleRow();
};

//! Test SessionItemUtils::ParentVisibleRow utility method.

inline void TestSessionItemUtils::test_ParentVisibleRow()
{
    SessionModel model("TestModel");

    // 3 property items in root, all visible
    auto item1 = model.insertNewItem(Constants::PropertyType);
    auto item2 = model.insertNewItem(Constants::PropertyType);
    auto item3 = model.insertNewItem(Constants::PropertyType);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item1), 0);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item2), 1);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item3), 2);

    // one item become invisible
    item2->setVisible(false);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item1), 0);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item2), -1);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item3), 1);

    // two more items
    auto item4 = model.insertNewItem(Constants::PropertyType);
    auto item5 = model.insertNewItem(Constants::PropertyType);
    item5->setVisible(false);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item1), 0);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item2), -1);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item3), 1);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item4), 2);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*item5), -1);

    // adding vector item
    SessionItem* vector = model.insertNewItem(Constants::VectorType);
    auto x = vector->getItem(VectorItem::P_X);
    auto y = vector->getItem(VectorItem::P_Y);
    auto z = vector->getItem(VectorItem::P_Z);
    x->setVisible(false);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*x), -1);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*y), 0);
    QCOMPARE(SessionItemUtils::ParentVisibleRow(*z), 1);
}
