#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "Tests/GTestWrapper/google_test.h"

class TestSessionItemUtils : public ::testing::Test
{
};

//! Test SessionItemUtils::ParentVisibleRow utility method.

TEST_F(TestSessionItemUtils, test_ParentVisibleRow)
{
    SessionModel model("TestModel");

    // 3 property items in root, all visible
    auto item1 = model.insertNewItem("Property");
    auto item2 = model.insertNewItem("Property");
    auto item3 = model.insertNewItem("Property");
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item1), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item2), 1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item3), 2);

    // one item become invisible
    item2->setVisible(false);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item1), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item2), -1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item3), 1);

    // two more items
    auto item4 = model.insertNewItem("Property");
    auto item5 = model.insertNewItem("Property");
    item5->setVisible(false);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item1), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item2), -1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item3), 1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item4), 2);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item5), -1);

    // adding vector item
    SessionItem* vector = model.insertNewItem("Vector");
    auto x = vector->getItem(VectorItem::P_X);
    auto y = vector->getItem(VectorItem::P_Y);
    auto z = vector->getItem(VectorItem::P_Z);
    x->setVisible(false);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*x), -1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*y), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*z), 1);
}

//! Comparing types of variant.

TEST_F(TestSessionItemUtils, VariantType)
{
    EXPECT_TRUE(SessionItemUtils::VariantType(QVariant::fromValue(1.0))
                == SessionItemUtils::VariantType(QVariant::fromValue(2.0)));
    EXPECT_FALSE(SessionItemUtils::VariantType(QVariant::fromValue(1.0))
                 == SessionItemUtils::VariantType(QVariant::fromValue(1)));
    EXPECT_FALSE(SessionItemUtils::VariantType(QVariant::fromValue(1.0))
                 == SessionItemUtils::VariantType(QVariant::fromValue(QString{"a"})));

    QVariant v1, v2;
    EXPECT_TRUE(SessionItemUtils::VariantType(v1) == SessionItemUtils::VariantType(v2));
    EXPECT_FALSE(SessionItemUtils::VariantType(v1)
                 == SessionItemUtils::VariantType(QVariant::fromValue(42.0)));

    ComboProperty c1, c2;
    EXPECT_TRUE(SessionItemUtils::VariantType(c1.variant())
                == SessionItemUtils::VariantType(c2.variant()));
    EXPECT_FALSE(SessionItemUtils::VariantType(c1.variant())
                 == SessionItemUtils::VariantType(QVariant::fromValue(42.0)));
    EXPECT_FALSE(SessionItemUtils::VariantType(c1.variant())
                 == SessionItemUtils::VariantType(QVariant()));

    ExternalProperty p1, p2;
    EXPECT_TRUE(SessionItemUtils::VariantType(p1.variant())
                == SessionItemUtils::VariantType(p2.variant()));
    EXPECT_FALSE(SessionItemUtils::VariantType(p1.variant())
                 == SessionItemUtils::VariantType(QVariant::fromValue(42.0)));
    EXPECT_FALSE(SessionItemUtils::VariantType(p1.variant())
                 == SessionItemUtils::VariantType(c1.variant()));
    EXPECT_FALSE(SessionItemUtils::VariantType(p1.variant())
                 == SessionItemUtils::VariantType(QVariant()));
}

//! Comparing types of variant.

TEST_F(TestSessionItemUtils, CompatibleVariantTypes)
{
    QVariant undefined;
    QVariant comboProperty = QVariant::fromValue(ComboProperty());
    QVariant externProperty = QVariant::fromValue(ExternalProperty());
    QVariant doubleProperty = QVariant::fromValue(42.0);

    EXPECT_TRUE(SessionItemUtils::CompatibleVariantTypes(undefined, comboProperty));
    EXPECT_TRUE(SessionItemUtils::CompatibleVariantTypes(undefined, externProperty));
    EXPECT_TRUE(SessionItemUtils::CompatibleVariantTypes(undefined, doubleProperty));

    EXPECT_TRUE(SessionItemUtils::CompatibleVariantTypes(comboProperty, comboProperty));
    EXPECT_TRUE(SessionItemUtils::CompatibleVariantTypes(externProperty, externProperty));
    EXPECT_TRUE(SessionItemUtils::CompatibleVariantTypes(doubleProperty, doubleProperty));

    EXPECT_FALSE(SessionItemUtils::CompatibleVariantTypes(doubleProperty, comboProperty));
    EXPECT_FALSE(SessionItemUtils::CompatibleVariantTypes(comboProperty, doubleProperty));
}

//! Test variant equality reported by SessionItemUtils::isTheSame

TEST_F(TestSessionItemUtils, IsTheSameVariant)
{
    // comparing undefined variants
    QVariant v1, v2;
    EXPECT_TRUE(SessionItemUtils::IsTheSame(v1, v2));

    // comparing QVariant based on double
    EXPECT_TRUE(SessionItemUtils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(1.0)));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(2.0)));

    // comparing QVariant based on strings
    EXPECT_TRUE(SessionItemUtils::IsTheSame(QVariant::fromValue(QString{"a"}),
                                            QVariant::fromValue(QString{"a"})));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(QVariant::fromValue(QString{"a"}),
                                             QVariant::fromValue(QString{"b"})));

    // comparing variants of different type
    EXPECT_FALSE(SessionItemUtils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(1)));

    // comparing custom variants (should be always false)
    ExternalProperty p1, p2;
    EXPECT_FALSE(SessionItemUtils::IsTheSame(p1.variant(), p2.variant()));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(p1.variant(), QVariant::fromValue(42.0)));

    ComboProperty c1, c2;
    EXPECT_FALSE(SessionItemUtils::IsTheSame(c1.variant(), c2.variant()));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(c1.variant(), QVariant::fromValue(42.0)));

    EXPECT_FALSE(SessionItemUtils::IsTheSame(p1.variant(), c1.variant()));
}
