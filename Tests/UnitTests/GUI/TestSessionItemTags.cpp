#include "GUI/coregui/Models/SessionItemTags.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"

class TestSessionItemTags : public ::testing::Test
{
};

TEST_F(TestSessionItemTags, initialState)
{
    SessionItemTags tags;
    EXPECT_FALSE(tags.isValid(QString()));
    EXPECT_FALSE(tags.isValid("abc"));
}

TEST_F(TestSessionItemTags, registerTag)
{
    SessionItemTags tags;

    // registering tag
    EXPECT_TRUE(tags.registerTag("tag1", 0, 1, QStringList() << "Particle"));
    EXPECT_TRUE(tags.isValid("tag1"));
    EXPECT_TRUE(tags.isValid("tag1", "Particle"));
    EXPECT_FALSE(tags.isValid("tag1", "wrongModelType"));
    QStringList expected = QStringList() << "Particle";
    EXPECT_EQ(tags.modelTypesForTag("tag1"), expected);

    // registering tag twice
    EXPECT_FALSE(tags.registerTag("tag1", 0, 1, QStringList() << "Particle"));

    // registering another tag
    EXPECT_TRUE(tags.registerTag("tag2", 0, 1,
                                 QStringList() << "Particle"
                                               << "Layer"));
    expected = QStringList() << "Particle"
                             << "Layer";
    EXPECT_EQ(tags.modelTypesForTag("tag2"), expected);
}

TEST_F(TestSessionItemTags, modelTypesForTag)
{
    SessionItemTags tags;

    QStringList expected = QStringList() << "Particle"
                                         << "Layer";

    EXPECT_TRUE(tags.registerTag("tag1", 0, 1, expected));
    EXPECT_EQ(tags.modelTypesForTag("tag1"), expected);

    EXPECT_TRUE(tags.registerTag("tag2", 0, 1, QStringList()));
    EXPECT_EQ(tags.modelTypesForTag("tag2"), QStringList());

    EXPECT_EQ(tags.modelTypesForTag("tag3"), QStringList());
}

TEST_F(TestSessionItemTags, tagStartIndex)
{
    SessionItemTags tags;

    // registering tags
    EXPECT_TRUE(tags.registerTag("tag1", 0, 2, QStringList() << "Particle"));
    EXPECT_EQ(tags.childCount("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);

    EXPECT_TRUE(tags.registerTag("tag2", 0, 1,
                                 QStringList() << "Particle"
                                               << "Layer"));
    EXPECT_EQ(tags.childCount("tag2"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 0);

    // adding child
    tags.addChild("tag1");
    tags.addChild("tag1");
    EXPECT_EQ(tags.childCount("tag1"), 2);
    EXPECT_EQ(tags.childCount("tag2"), 0);
    // attempt to add too much
    EXPECT_THROW(tags.addChild("tag1"), GUIHelpers::Error);

    // checking start index
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 2);

    // removing child
    tags.removeChild("tag1");
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 1);

    // removing too much child
    tags.removeChild("tag1");
    EXPECT_THROW(tags.removeChild("tag1"), GUIHelpers::Error);
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 0);
}

TEST_F(TestSessionItemTags, indexFromTagRow)
{
    SessionItemTags tags;
    tags.registerTag("tag1", 0, -1, QStringList() << "Particle");
    tags.registerTag("tag2", 0, 2, QStringList() << "Particle");

    tags.addChild("tag1"); // index=0, row=0
    tags.addChild("tag1"); // index=1, row=1
    tags.addChild("tag1"); // index=2, row=2
    tags.addChild("tag2"); // index=3, row=0
    tags.addChild("tag2"); // index=4, row=1

    EXPECT_EQ(tags.indexFromTagRow("tag1", 0), 0);
    EXPECT_EQ(tags.indexFromTagRow("tag1", 1), 1);
    EXPECT_EQ(tags.indexFromTagRow("tag1", 2), 2);
    EXPECT_THROW(tags.indexFromTagRow("tag1", 3), GUIHelpers::Error);
    EXPECT_THROW(tags.indexFromTagRow("tag1", -1), GUIHelpers::Error);

    EXPECT_EQ(tags.indexFromTagRow("tag2", 0), 3);
    EXPECT_EQ(tags.indexFromTagRow("tag2", 1), 4);
}

TEST_F(TestSessionItemTags, tagFromIndex)
{
    SessionItemTags tags;
    tags.registerTag("tag1", 0, -1, QStringList() << "Particle");
    tags.registerTag("tag2", 0, 2, QStringList() << "Particle");

    tags.addChild("tag1"); // index=0
    tags.addChild("tag1"); // index=1
    tags.addChild("tag1"); // index=2
    tags.addChild("tag2"); // index=3
    tags.addChild("tag2"); // index=4

    EXPECT_EQ(tags.tagFromIndex(0), "tag1");
    EXPECT_EQ(tags.tagFromIndex(1), "tag1");
    EXPECT_EQ(tags.tagFromIndex(2), "tag1");
    EXPECT_EQ(tags.tagFromIndex(3), "tag2");
    EXPECT_EQ(tags.tagFromIndex(4), "tag2");

    EXPECT_EQ(tags.tagFromIndex(-1), QString());
    EXPECT_EQ(tags.tagFromIndex(5), QString());
}

//! Testing the method calculating insert index.

TEST_F(TestSessionItemTags, insertIndexFromTagRow)
{
    SessionItemTags tags;
    tags.registerTag("tag1", 0, -1, QStringList() << "Particle");
    tags.registerTag("tag2", 0, 2, QStringList() << "Particle");

    tags.addChild("tag1"); // index=0, row=0
    tags.addChild("tag1"); // index=1, row=1
    tags.addChild("tag1"); // index=2, row=2
    tags.addChild("tag2"); // index=3, row=0

    EXPECT_EQ(tags.insertIndexFromTagRow("tag1", 0), 0);
    EXPECT_EQ(tags.insertIndexFromTagRow("tag1", -1), 3);
    EXPECT_EQ(tags.insertIndexFromTagRow("tag1", 3), 3);
    EXPECT_EQ(tags.insertIndexFromTagRow("tag1", 4), -1);

    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", 0), 3);
    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", -1), 4);
    tags.addChild("tag2");                                 // index=4, row=1
    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", 0), -1);  // maximum reached
    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", -1), -1); // maximum reached
}
