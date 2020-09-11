#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"

class TestSessionItem : public ::testing::Test
{
};

TEST_F(TestSessionItem, initialState)
{
    const QString modeltype = "This is the model type";
    std::unique_ptr<SessionItem> item(new SessionItem(modeltype));
    EXPECT_TRUE(item->modelType() == modeltype);
    EXPECT_TRUE(item->model() == nullptr);
    EXPECT_TRUE(item->parent() == nullptr);
    // TODO add some more tests for children, roles, tags ...
}

TEST_F(TestSessionItem, defaultTag)
{
    const QString modelType = "TestItem";

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));
    EXPECT_TRUE(item->defaultTag().isEmpty());

    // insertion without tag is forbidden
    SessionItem* child = new SessionItem(modelType);
    EXPECT_DEATH(item->insertItem(0, child), ".*");
    delete child;
    EXPECT_EQ(item->numberOfChildren(), 0);
}

TEST_F(TestSessionItem, singleTagAndItems)
{
    const QString tag1 = "TAG1";
    const QString modelType = "TestItem";

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));

    // before using a tag, it must be registered
    EXPECT_TRUE(item->registerTag(tag1));
    EXPECT_TRUE(item->isTag(tag1));

    // register twice returns false
    EXPECT_FALSE(item->registerTag(tag1));

    // register empty string returns false
    EXPECT_FALSE(item->registerTag(""));

    // getting non-existing items from tag
    EXPECT_TRUE(item->getItem(tag1) == nullptr);
    EXPECT_TRUE(item->getItems(tag1) == QVector<SessionItem*>());

    // inserting single item
    SessionItem* child = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(0, child, tag1));
    // double insertion is forbidden
    EXPECT_DEATH(item->insertItem(0, child, tag1), ".*");
    EXPECT_TRUE(child->parent() == item.get());
    EXPECT_EQ(item->numberOfChildren(), 1);

    // checking list of children
    auto expected = QVector<SessionItem*>() << child;
    EXPECT_EQ(item->children(), expected);

    // checking getItems method
    EXPECT_EQ(item->getItems(), QVector<SessionItem*>());
    EXPECT_EQ(item->getItems(tag1), expected);

    // checking getItem method
    EXPECT_EQ(item->getItem(tag1), child);

    // adding second child at the beginning
    SessionItem* child1 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(0, child1, tag1));

    expected = QVector<SessionItem*>() << child1 << child;
    EXPECT_EQ(item->children(), expected);
    EXPECT_EQ(item->getItems(), QVector<SessionItem*>());
    EXPECT_EQ(item->getItems(tag1), expected);
    EXPECT_EQ(item->getItem(tag1, 0), child1);
    EXPECT_EQ(item->getItem(tag1, 1), child);
    EXPECT_EQ(item->getItem(tag1, 2), nullptr);

    // adding third item at the end
    SessionItem* child2 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(-1, child2, tag1));
    expected = QVector<SessionItem*>() << child1 << child << child2;
    EXPECT_EQ(item->children(), expected);
    EXPECT_EQ(item->getItems(), QVector<SessionItem*>());
    EXPECT_EQ(item->getItems(tag1), expected);
    EXPECT_EQ(item->getItem(tag1, 0), child1);
    EXPECT_EQ(item->getItem(tag1, 1), child);
    EXPECT_EQ(item->getItem(tag1, 2), child2);
}

TEST_F(TestSessionItem, insertAndTake)
{
    const QString tag1 = "TAG1";
    const QString modelType = "TestItem";

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));
    EXPECT_TRUE(item->registerTag(tag1));

    // inserting two children
    SessionItem* child1 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(-1, child1, tag1));
    SessionItem* child2 = new SessionItem(modelType);
    EXPECT_TRUE(item->insertItem(-1, child2, tag1));
    auto expected = QVector<SessionItem*>() << child1 << child2;
    EXPECT_EQ(item->getItems(tag1), expected);

    // taking first
    SessionItem* first = item->takeItem(0, tag1);
    EXPECT_EQ(first, child1);
    EXPECT_TRUE(first->parent() == nullptr);
    expected = QVector<SessionItem*>() << child2;
    EXPECT_EQ(item->getItems(tag1), expected);
    delete first;
}

TEST_F(TestSessionItem, tagWithLimits)
{
    const QString tag1 = "TAG1";
    const QString modelType = "TestItem";
    const int maxItems(3);

    std::unique_ptr<SessionItem> item(new SessionItem(modelType));
    EXPECT_TRUE(item->registerTag(tag1, 0, maxItems));

    QVector<SessionItem*> expected;
    for (int i = 0; i < maxItems; ++i) {
        auto child = new SessionItem(modelType);
        expected.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag1));
    }
    auto extra = new SessionItem(modelType);
    EXPECT_DEATH(item->insertItem(-1, extra, tag1), ".*");
}

TEST_F(TestSessionItem, tagsAndModelTypes)
{
    const QString tag1 = "tag1";
    const QString tag2 = "tag2";
    const QString modelType1 = "ModelType1";
    const QString modelType2 = "ModelType2";
    const int maxItems1(3);
    const int maxItems2(4);

    std::unique_ptr<SessionItem> item(new SessionItem("ModelType"));
    EXPECT_TRUE(item->registerTag(tag1, 0, -1, QStringList() << modelType1));
    EXPECT_TRUE(item->registerTag(tag2, 0, -1, QStringList() << modelType2));

    // adding two types of items under different tags
    QVector<SessionItem*> expected1;
    for (int i = 0; i < maxItems1; ++i) {
        auto child = new SessionItem(modelType1);
        expected1.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag1));
    }

    QVector<SessionItem*> expected2;
    for (int i = 0; i < maxItems2; ++i) {
        auto child = new SessionItem(modelType2);
        expected2.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag2));
    }

    // checking list of children separated according tag
    EXPECT_EQ(item->getItems(tag1), expected1);
    EXPECT_EQ(item->getItems(tag2), expected2);

    // removing child from tag1, tag2 should remain intact
    auto taken = item->takeItem(0, tag1);
    EXPECT_EQ(taken, expected1.front());
    EXPECT_EQ(item->getItems(tag2), expected2);
}

TEST_F(TestSessionItem, takeRow)
{
    const QString tag1 = "tag1";
    const QString tag2 = "tag2";
    const QString modelType1 = "ModelType1";
    const QString modelType2 = "ModelType2";
    const int maxItems1(3);
    const int maxItems2(4);

    std::unique_ptr<SessionItem> item(new SessionItem("ModelType"));
    EXPECT_TRUE(item->registerTag(tag1, 0, -1, QStringList() << modelType1));
    EXPECT_TRUE(item->registerTag(tag2, 0, -1, QStringList() << modelType2));

    // adding two types of items under different tags
    QVector<SessionItem*> expected1;
    for (int i = 0; i < maxItems1; ++i) {
        auto child = new SessionItem(modelType1);
        expected1.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag1));
    }

    QVector<SessionItem*> expected2;
    for (int i = 0; i < maxItems2; ++i) {
        auto child = new SessionItem(modelType2);
        expected2.push_back(child);
        EXPECT_TRUE(item->insertItem(-1, child, tag2));
    }

    auto taken1 = item->takeRow(1);
    EXPECT_EQ(taken1, expected1.at(1));
    EXPECT_TRUE(taken1->parent() == nullptr);
    delete taken1;

    auto taken2 = item->takeRow(maxItems1 - 1); // one item less already
    EXPECT_EQ(taken2, expected2.at(0));
    delete taken2;

    expected1.removeAll(taken1);
    expected2.pop_front();

    EXPECT_EQ(item->getItems(tag1), expected1);
    EXPECT_EQ(item->getItems(tag2), expected2);
}

TEST_F(TestSessionItem, dataRoles)
{
    std::unique_ptr<SessionItem> item(new SessionItem("Some model type"));
    item->setRoleProperty(Qt::DisplayRole, 1234);
    EXPECT_TRUE(item->roleProperty(Qt::DisplayRole) == 1234);
    EXPECT_TRUE(item->roleProperty(Qt::EditRole) == 1234);
    item->setRoleProperty(Qt::EditRole, 5432);
    EXPECT_TRUE(item->roleProperty(Qt::DisplayRole) == 5432);
    EXPECT_TRUE(item->roleProperty(Qt::EditRole) == 5432);
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(item->roleProperty(SessionFlags::EndSessionRoles + i).isValid() == false);
        item->setRoleProperty(SessionFlags::EndSessionRoles + i, i);
        EXPECT_TRUE(item->roleProperty(SessionFlags::EndSessionRoles + i) == i);
    }
}

TEST_F(TestSessionItem, modelTypes)
{
    const QString model1 = "modeltype 1";
    const QString model2 = "modeltype 2";
    const QString model3 = "modeltype 3";
    const QString model4 = "modeltype 4";
    const QString model5 = "modeltype 5";

    std::unique_ptr<SessionItem> item(new SessionItem("modeltype does not matter"));
    EXPECT_TRUE(item->registerTag("Tag1", 0, -1, QStringList() << model1 << model2));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model1), "Tag1"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model2), "Tag1"));

    auto child = new SessionItem(model3);
    EXPECT_DEATH(item->insertItem(0, child, "Tag1"), ".*");
    delete child;

    child = new SessionItem(model4);
    EXPECT_DEATH(item->insertItem(0, child, "Tag1"), ".*");
    delete child;

    child = new SessionItem(model5);
    EXPECT_DEATH(item->insertItem(0, child, "Tag1"), ".*");
    delete child;

    EXPECT_TRUE(item->registerTag("Tag2", 0, -1, QStringList() << model3 << model4 << model5));

    child = new SessionItem(model1);
    EXPECT_DEATH(item->insertItem(0, child, "Tag2"), ".*");
    delete child;

    child = new SessionItem(model2);
    EXPECT_DEATH(item->insertItem(0, child, "Tag2"), ".*");
    delete child;

    EXPECT_TRUE(item->insertItem(0, new SessionItem(model3), "Tag2"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model4), "Tag2"));
    EXPECT_TRUE(item->insertItem(0, new SessionItem(model5), "Tag2"));
}
