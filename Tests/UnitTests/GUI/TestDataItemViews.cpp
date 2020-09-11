#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DataProperties.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/MessageService.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/Utils.h"

class TestDataItemViews : public ::testing::Test
{
public:
    DataItem* insertNewDataItem(SessionModel& model, double val);
};

DataItem* TestDataItemViews::insertNewDataItem(SessionModel& model, double val)
{
    DataItem* item = dynamic_cast<DataItem*>(model.insertNewItem("SpecularData"));
    auto data = GuiUnittestUtils::createData(val, GuiUnittestUtils::DIM::D1);
    item->setOutputData(data.release());
    return item;
}

TEST_F(TestDataItemViews, testDataLinking)
{
    SessionModel model("TempModel");
    auto view_item =
        dynamic_cast<DataPropertyContainer*>(model.insertNewItem("DataPropertyContainer"));
    DataItem* item = insertNewDataItem(model, 0.0);
    view_item->addItem(item);

    auto stored_items = view_item->propertyItems();
    EXPECT_EQ(stored_items.size(), 1);
    EXPECT_EQ(stored_items[0]->dataItem(), item);
}

TEST_F(TestDataItemViews, testLinkingSeveralItems)
{
    SessionModel model("TempModel");
    auto view_item =
        dynamic_cast<DataPropertyContainer*>(model.insertNewItem("DataPropertyContainer"));
    DataItem* item = insertNewDataItem(model, 0.0);
    DataItem* item2 = insertNewDataItem(model, 1.0);
    DataItem* item3 = insertNewDataItem(model, 2.0);
    view_item->addItem(item);
    view_item->addItem(item2);
    view_item->addItem(item3);

    auto stored_items = view_item->propertyItems();
    EXPECT_EQ(stored_items.size(), 3);
    EXPECT_EQ(stored_items[0]->dataItem(), item);
    EXPECT_EQ(stored_items[1]->dataItem(), item2);
    EXPECT_EQ(stored_items[2]->dataItem(), item3);
}

TEST_F(TestDataItemViews, testColors)
{
    SessionModel model("TempModel");
    auto view_item =
        dynamic_cast<DataPropertyContainer*>(model.insertNewItem("DataPropertyContainer"));
    DataItem* item = insertNewDataItem(model, 0.0);
    DataItem* item2 = insertNewDataItem(model, 1.0);
    DataItem* item3 = insertNewDataItem(model, 2.0);
    DataItem* item4 = insertNewDataItem(model, 3.0);
    DataItem* item5 = insertNewDataItem(model, 4.0);
    DataItem* item6 = insertNewDataItem(model, 5.0);
    DataItem* item7 = insertNewDataItem(model, 6.0);
    view_item->addItem(item);
    view_item->addItem(item2);
    view_item->addItem(item3);
    view_item->addItem(item4);
    view_item->addItem(item5);
    view_item->addItem(item6);
    view_item->addItem(item7);

    auto stored_items = view_item->propertyItems();
    auto getColorName = [](SessionItem* item) {
        QString P_COLOR = Data1DProperties::P_COLOR; // analogue of using
        auto name = item->getItemValue(P_COLOR).value<ComboProperty>().getValue();
        return name;
    };

    EXPECT_EQ(stored_items.size(), 7);
    EXPECT_EQ(getColorName(stored_items[0]), "Black");
    EXPECT_EQ(getColorName(stored_items[1]), "Blue");
    EXPECT_EQ(getColorName(stored_items[2]), "Red");
    EXPECT_EQ(getColorName(stored_items[3]), "Cyan");
    EXPECT_EQ(getColorName(stored_items[4]), "Gray");
    EXPECT_EQ(getColorName(stored_items[5]), "Magenta");
    EXPECT_EQ(getColorName(stored_items[6]), "Black");
}

TEST_F(TestDataItemViews, testBrokenLink)
{
    SessionModel model("TempModel");
    auto view_item =
        dynamic_cast<DataPropertyContainer*>(model.insertNewItem("DataPropertyContainer"));
    DataItem* item = insertNewDataItem(model, 0.0);
    view_item->addItem(item);

    auto stored_items = view_item->propertyItems();
    EXPECT_EQ(stored_items.size(), 1);
    EXPECT_EQ(stored_items[0]->dataItem(), item);

    DataItem* item2 = insertNewDataItem(model, 1.0);
    view_item->addItem(item2);
    EXPECT_THROW(view_item->propertyItem(0)->dataItem(), GUIHelpers::Error);
}

TEST_F(TestDataItemViews, testWrongHostingModel)
{
    SessionModel model("TempModel");
    DataItem* item = insertNewDataItem(model, 0.0);
    auto view_item =
        dynamic_cast<DataPropertyContainer*>(model.insertNewItem("DataPropertyContainer"));
    view_item->addItem(item);

    SessionModel model2("TempModel2");
    DataItem* item2 = insertNewDataItem(model2, 1.0);
    EXPECT_THROW(view_item->addItem(item2), GUIHelpers::Error);

    auto stored_items = view_item->propertyItems();
    EXPECT_EQ(stored_items.size(), 1);
    EXPECT_EQ(stored_items[0]->dataItem(), item);
}

TEST_F(TestDataItemViews, testSavingLinkedData)
{
    const QString projectDir("test_savingLinkedData");
    GuiUnittestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");
    {
        ApplicationModels models;
        ProjectDocument document;

        SessionModel* real_data_model = models.realDataModel();
        DataItem* item = insertNewDataItem(*real_data_model, 0.0);
        DataItem* item2 = insertNewDataItem(*real_data_model, 1.0);
        auto view_item = dynamic_cast<DataPropertyContainer*>(
            real_data_model->insertNewItem("DataPropertyContainer"));
        view_item->addItem(item);
        view_item->addItem(item2);

        document.setApplicationModels(&models);
        document.save(projectFileName);
    }

    ApplicationModels models;
    MessageService message_service;
    ProjectDocument document;
    document.setApplicationModels(&models);
    document.setLogger(&message_service);
    document.load(projectFileName);

    SessionModel* real_data_model = models.realDataModel();
    auto view_item = real_data_model->topItem<DataPropertyContainer>();
    EXPECT_TRUE(view_item);

    auto linked_items = view_item->propertyItems();
    auto model_items = real_data_model->topItems<DataItem>();
    EXPECT_EQ(linked_items.size(), 2);
    EXPECT_EQ(model_items.size(), 2);
    for (auto item : model_items) {
        auto data_item = dynamic_cast<DataItem*>(item);
        EXPECT_TRUE(data_item);
        EXPECT_TRUE(data_item == linked_items[0]->dataItem()
                    || data_item == linked_items[1]->dataItem());
    }
}
