#include "Fit/Tools/MultiOption.h"
#include "Tests/GTestWrapper/google_test.h"
#include <string>

class MultiOptionTest : public ::testing::Test
{
};

TEST_F(MultiOptionTest, Variant)
{
    MultiOption::variant_t v1(1);

    EXPECT_EQ(0, v1.which());
    //    EXPECT_EQ(1, v1.get<int>());
    EXPECT_EQ(1, boost::get<int>(v1));

    v1 = 2.0;
    EXPECT_EQ(1, v1.which());
    // EXPECT_EQ(2.0, v1.get<double>());
    EXPECT_EQ(2.0, boost::get<double>(v1));

    const std::string text("xxx");
    v1 = text;
    EXPECT_EQ(2, v1.which());
    //    EXPECT_EQ(text, v1.get<std::string>());
    EXPECT_EQ(text, boost::get<std::string>(v1));
}

TEST_F(MultiOptionTest, Construction)
{
    const std::string name("name");
    const std::string description("description");
    const double double_value(2.0);
    MultiOption opt(name, double_value, description);

    EXPECT_EQ(name, opt.name());
    EXPECT_EQ(description, opt.description());
    EXPECT_EQ(double_value, opt.get<double>());
    EXPECT_EQ(double_value, opt.getDefault<double>());

    // setting new value
    const double new_value = 3.0;
    opt.value() = new_value;
    EXPECT_EQ(new_value, opt.get<double>());
    EXPECT_EQ(double_value, opt.getDefault<double>());
}

TEST_F(MultiOptionTest, Copying)
{
    const std::string name("name");
    const std::string description("description");
    const double double_value(2.0);
    MultiOption opt(name, double_value, description);

    MultiOption copy(opt);
    EXPECT_EQ(name, copy.name());
    EXPECT_EQ(description, copy.description());
    EXPECT_EQ(double_value, copy.get<double>());
    EXPECT_EQ(double_value, copy.getDefault<double>());
}

TEST_F(MultiOptionTest, Assignment)
{
    const std::string name("name");
    const std::string description("description");
    const double double_value(2.0);
    MultiOption opt(name, double_value, description);

    MultiOption copy;
    copy = opt;

    const double new_value = 3.0;
    opt.value() = new_value;

    EXPECT_EQ(name, copy.name());
    EXPECT_EQ(description, copy.description());
    EXPECT_EQ(double_value, copy.get<double>());
    EXPECT_EQ(double_value, copy.getDefault<double>());
}

TEST_F(MultiOptionTest, SetFromString)
{
    MultiOption opt("name", 2.0);
    opt.setFromString("2.1");
    EXPECT_EQ(2.1, opt.get<double>());
    opt.setFromString("2");
    EXPECT_EQ(2.0, opt.get<double>());

    MultiOption opt2("name", 99);
    opt2.setFromString("100");
    EXPECT_EQ(100, opt2.get<int>());

    MultiOption opt3("name", "xxx");
    opt3.setFromString("yyy");
    EXPECT_EQ("yyy", opt3.get<std::string>());
}
