#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItemTags.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QSignalSpy>
#include <QXmlStreamWriter>
#include <memory>

class TestSessionModel : public ::testing::Test
{
};

//! Testing SessionModel::setData notifications.

TEST_F(TestSessionModel, setData)
{
    SessionModel model("TestModel");
    auto item = model.insertNewItem("Property");

    QSignalSpy spy(&model, &SessionModel::dataChanged);

    QVariant data(42.0);

    // setting the data and checking that signal was emmitted only once
    EXPECT_TRUE(model.setData(model.indexOfItem(item), data, Qt::DisplayRole));
    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(item->value().toDouble(), 42.0);
    QList<QVariant> arguments = spy.takeFirst();
    EXPECT_EQ(arguments.at(0).toModelIndex(), model.indexOfItem(item));

    // setting the same data second time
    EXPECT_FALSE(model.setData(model.indexOfItem(item), data, Qt::DisplayRole));
    EXPECT_EQ(spy.count(), 0);

    // setting another data
    EXPECT_TRUE(model.setData(model.indexOfItem(item), QVariant(43.0), Qt::DisplayRole));
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(TestSessionModel, SampleModelCopy)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel model1;
    SessionItem* multilayer = model1.insertNewItem("MultiLayer");
    multilayer->setItemName("multilayer");
    model1.insertNewItem("Layer", model1.indexOfItem(multilayer));
    SessionItem* multilayer2 = model1.insertNewItem("MultiLayer");
    multilayer2->setItemName("multilayer2");

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1.writeTo(&writer1);

    std::unique_ptr<SampleModel> model2(model1.createCopy());
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    EXPECT_EQ(buffer1, buffer2);
}

TEST_F(TestSessionModel, SampleModelPartialCopy)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel model1;
    SessionItem* multilayer1 = model1.insertNewItem("MultiLayer");
    multilayer1->setItemName("multilayer1");
    model1.insertNewItem("Layer", model1.indexOfItem(multilayer1));

    SessionItem* multilayer2 = model1.insertNewItem("MultiLayer");
    multilayer2->setItemName("multilayer2");

    std::unique_ptr<SampleModel> model2(model1.createCopy(multilayer1));
    SessionItem* result = model2->itemForIndex(model2->index(0, 0, QModelIndex()));

    EXPECT_EQ(result->itemName(), multilayer1->itemName());
    EXPECT_EQ(result->modelType(), multilayer1->modelType());
}

TEST_F(TestSessionModel, InstrumentModelCopy)
{
    InstrumentModel model1;
    SessionItem* instrument1 = model1.insertNewItem("GISASInstrument");
    instrument1->setItemName("instrument1");

    SessionItem* instrument2 = model1.insertNewItem("GISASInstrument");
    instrument2->setItemName("instrument2");

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1.writeTo(&writer1);

    std::unique_ptr<InstrumentModel> model2(model1.createCopy());
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    EXPECT_EQ(buffer1, buffer2);
}

TEST_F(TestSessionModel, InstrumentModelPartialCopy)
{
    InstrumentModel model1;
    SessionItem* instrument1 = model1.insertNewItem("GISASInstrument");
    instrument1->setItemName("instrument1");

    SessionItem* instrument2 = model1.insertNewItem("GISASInstrument");
    instrument2->setItemName("instrument2");

    std::unique_ptr<InstrumentModel> model2(model1.createCopy(instrument2));
    SessionItem* result = model2->itemForIndex(model2->index(0, 0, QModelIndex()));
    EXPECT_EQ(result->modelType(), instrument2->modelType());
}

//! Test if SessionItem can be copied from one model to another. Particularly, we test
//! here if a MultiLayerItem can be copied from SampleModel to the JobItem of JobModel

TEST_F(TestSessionModel, copyItem)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel sampleModel;
    SessionItem* multilayer1 = sampleModel.insertNewItem("MultiLayer");
    multilayer1->setItemName("multilayer1");
    sampleModel.insertNewItem("Layer", sampleModel.indexOfItem(multilayer1));

    InstrumentModel instrumentModel;
    SessionItem* instrument1 = instrumentModel.insertNewItem("GISASInstrument");
    instrument1->setItemName("instrument1");

    JobModel jobModel;
    SessionItem* jobItem = jobModel.insertNewItem("JobItem");

    jobModel.copyItem(multilayer1, jobItem, JobItem::T_SAMPLE);
    EXPECT_EQ(jobItem->sessionItemTags()->childCount(JobItem::T_SAMPLE), 1);

    jobModel.copyItem(instrument1, jobItem, JobItem::T_INSTRUMENT);
    EXPECT_EQ(jobItem->sessionItemTags()->childCount(JobItem::T_INSTRUMENT), 1);
}

TEST_F(TestSessionModel, moveItemFromRoot)
{
    SessionModel model("TestModel");
    auto poly = model.insertNewItem("PolygonMask");
    auto point = model.insertNewItem("PolygonPoint");

    EXPECT_EQ(poly->parent(), model.rootItem());
    EXPECT_EQ(point->parent(), model.rootItem());
    EXPECT_EQ(model.rootItem()->numberOfChildren(), 2);

    // moving from rootItem to poly
    auto moved = model.moveItem(point, poly);
    EXPECT_EQ(model.rootItem()->numberOfChildren(), 1);
    EXPECT_EQ(moved, point);
    EXPECT_EQ(point->parent(), poly);
    EXPECT_EQ(poly->getItem(), point);

    // moving from poly to rootItem
    moved = model.moveItem(point, 0);
    EXPECT_EQ(model.rootItem()->numberOfChildren(), 2);
    EXPECT_EQ(moved, point);
    EXPECT_EQ(point->parent(), model.rootItem());
    EXPECT_EQ(poly->getItem(), nullptr);
}

TEST_F(TestSessionModel, moveBetweenParents)
{
    SessionModel model("TestModel");
    auto poly1 = model.insertNewItem("PolygonMask");
    auto point11 = model.insertNewItem("PolygonPoint", model.indexOfItem(poly1));
    auto point12 = model.insertNewItem("PolygonPoint", model.indexOfItem(poly1));
    auto poly2 = model.insertNewItem("PolygonMask");

    EXPECT_EQ(point11->parent(), poly1);
    EXPECT_EQ(point12->parent(), poly1);
    EXPECT_EQ(poly1->getItem(), point11);

    auto moved = model.moveItem(point11, poly2);
    EXPECT_EQ(moved, point11);
    EXPECT_EQ(point11->parent(), poly2);
    EXPECT_EQ(poly1->getItem(), point12);
}

TEST_F(TestSessionModel, moveWithinSameParent)
{
    SessionModel model("TestModel");
    auto poly = model.insertNewItem("PolygonMask");
    auto pA = model.insertNewItem("PolygonPoint", model.indexOfItem(poly));
    auto pB = model.insertNewItem("PolygonPoint", model.indexOfItem(poly));
    auto pC = model.insertNewItem("PolygonPoint", model.indexOfItem(poly));
    auto pD = model.insertNewItem("PolygonPoint", model.indexOfItem(poly));
    auto pE = model.insertNewItem("PolygonPoint", model.indexOfItem(poly));

    // 0  pA -> pA
    // 1  pB -> pC
    // 2  pC -> pB
    // 3  pD -> pD
    // 4  pE -> pE

    model.moveItem(pB, poly, 3);
    EXPECT_EQ(poly->getItems().indexOf(pA), 0);
    EXPECT_EQ(poly->getItems().indexOf(pB), 2);
    EXPECT_EQ(poly->getItems().indexOf(pC), 1);
    EXPECT_EQ(poly->getItems().indexOf(pD), 3);
    EXPECT_EQ(poly->getItems().indexOf(pE), 4);
}
