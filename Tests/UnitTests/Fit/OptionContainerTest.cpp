#include "Fit/Tools/OptionContainer.h"
#include "Tests/GTestWrapper/google_test.h"
#include <exception>

class OptionContainerTest : public ::testing::Test
{
};

TEST_F(OptionContainerTest, addOption)
{
    OptionContainer test;

    const double option_value(1.0);
    const std::string option_name("option");
    const std::string option_description("description");

    // adding option
    OptionContainer::option_t option = test.addOption(option_name, option_value);
    option->setDescription(option_description);
    EXPECT_EQ(option_value, option->get<double>());
    EXPECT_EQ(option_name, option->name());
    EXPECT_EQ(option_description, option->description());
    EXPECT_EQ(option_value, test.optionValue<double>(option_name));

    // accessing option directly
    EXPECT_EQ(option.get(), test.option(option_name).get());

    // getting non-existing option
    EXPECT_THROW(test.option("non-existing-option"), std::runtime_error);

    // adding same option twice
    EXPECT_THROW(test.addOption(option_name, 1.0), std::runtime_error);
}

TEST_F(OptionContainerTest, getOptionValue)
{
    OptionContainer test;

    test.addOption("option #1", 99, "description #1");
    test.addOption("option #2", 1.1, "description #2");
    test.addOption("option #3", "xxx", "description #3");

    EXPECT_EQ(99, test.optionValue<int>("option #1"));
    EXPECT_EQ(1.1, test.optionValue<double>("option #2"));
    EXPECT_EQ("xxx", test.optionValue<std::string>("option #3"));
}

TEST_F(OptionContainerTest, setOptionValue)
{
    OptionContainer test;

    test.addOption("option #1", 99, "description #1");
    test.addOption("option #2", 1.1, "description #2");
    test.addOption("option #3", "xxx", "description #3");

    test.setOptionValue("option #1", 88);
    EXPECT_EQ(88, test.optionValue<int>("option #1"));

    test.setOptionValue("option #2", 2.2);
    EXPECT_EQ(2.2, test.optionValue<double>("option #2"));

    test.setOptionValue("option #3", "yyy");
    EXPECT_EQ("yyy", test.optionValue<std::string>("option #3"));

    // setting wrong type to the option
    EXPECT_THROW(test.setOptionValue("option #1", 99.0), std::runtime_error);
}

TEST_F(OptionContainerTest, Copying)
{
    OptionContainer test;

    test.addOption("option #1", 99, "description #1");
    test.addOption("option #2", 1.1, "description #2");
    test.addOption("option #3", "xxx", "description #3");

    // copying and checking values
    OptionContainer copy(test);

    EXPECT_EQ(99, copy.optionValue<int>("option #1"));
    EXPECT_EQ(1.1, copy.optionValue<double>("option #2"));
    EXPECT_EQ("xxx", copy.optionValue<std::string>("option #3"));

    // changing values of copy
    copy.setOptionValue("option #1", 88);
    EXPECT_EQ(88, copy.optionValue<int>("option #1"));
    copy.setOptionValue("option #2", 2.2);
    EXPECT_EQ(2.2, copy.optionValue<double>("option #2"));
    copy.setOptionValue("option #3", "yyy");
    EXPECT_EQ("yyy", copy.optionValue<std::string>("option #3"));

    // checking the value of original
    EXPECT_EQ(99, test.optionValue<int>("option #1"));
    EXPECT_EQ(1.1, test.optionValue<double>("option #2"));
    EXPECT_EQ("xxx", test.optionValue<std::string>("option #3"));
}

TEST_F(OptionContainerTest, Assignment)
{
    OptionContainer test;

    test.addOption("option #1", 99, "description #1");
    test.addOption("option #2", 1.1, "description #2");
    test.addOption("option #3", "xxx", "description #3");

    // copying and checking values
    OptionContainer copy;
    copy = test;

    EXPECT_EQ(99, copy.optionValue<int>("option #1"));
    EXPECT_EQ(1.1, copy.optionValue<double>("option #2"));
    EXPECT_EQ("xxx", copy.optionValue<std::string>("option #3"));

    // changing values of copy
    copy.setOptionValue("option #1", 88);
    EXPECT_EQ(88, copy.optionValue<int>("option #1"));
    copy.setOptionValue("option #2", 2.2);
    EXPECT_EQ(2.2, copy.optionValue<double>("option #2"));
    copy.setOptionValue("option #3", "yyy");
    EXPECT_EQ("yyy", copy.optionValue<std::string>("option #3"));

    // checking the value of original
    EXPECT_EQ(99, test.optionValue<int>("option #1"));
    EXPECT_EQ(1.1, test.optionValue<double>("option #2"));
    EXPECT_EQ("xxx", test.optionValue<std::string>("option #3"));
}
