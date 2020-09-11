#include "Core/Parametrization/ParameterPattern.h"
#include "Tests/GTestWrapper/google_test.h"
#include <string>

class ParameterPatternTest : public ::testing::Test
{
};

TEST_F(ParameterPatternTest, declarationTest)
{
    ParameterPattern p1;
    EXPECT_EQ("", p1.toStdString());

    ParameterPattern p2("home");
    EXPECT_EQ("/home", p2.toStdString());
}

TEST_F(ParameterPatternTest, beginsWithTest)
{
    ParameterPattern p1("Downloads");
    EXPECT_EQ("/Downloads", p1.toStdString());

    p1.beginsWith("Desktop");
    EXPECT_EQ("Desktop", p1.toStdString());
}

TEST_F(ParameterPatternTest, addTest)
{
    ParameterPattern p1("Desktop");
    EXPECT_EQ("/Desktop", p1.toStdString());

    p1.add("BornAgain");
    EXPECT_EQ("/Desktop/BornAgain", p1.toStdString());

    p1.add("Core").add("Tests");
    EXPECT_EQ("/Desktop/BornAgain/Core/Tests", p1.toStdString());

    p1.add("UnitTests").beginsWith("user");
    EXPECT_EQ("user", p1.toStdString());
}

TEST_F(ParameterPatternTest, copyTest)
{
    ParameterPattern p1("Desktop");
    p1.add("BornAgain").add("Core").add("Tests");
    EXPECT_EQ("/Desktop/BornAgain/Core/Tests", p1.toStdString());

    ParameterPattern p2("user");
    EXPECT_EQ("/user", p2.toStdString());

    // calls assignment operator
    p2 = p1;
    EXPECT_EQ("/Desktop/BornAgain/Core/Tests", p2.toStdString());

    // calls copy constructor
    ParameterPattern p3(p2);
    EXPECT_EQ("/Desktop/BornAgain/Core/Tests", p3.toStdString());

    // calls copy constructor
    ParameterPattern p4 = {p2};
    EXPECT_EQ("/Desktop/BornAgain/Core/Tests", p4.toStdString());
}
