#include "Fit/Minimizer/MinimizerOptions.h"
#include "Tests/GTestWrapper/google_test.h"
#include <exception>

class MinimizerOptionsTest : public ::testing::Test
{
};

TEST_F(MinimizerOptionsTest, toOptionString)
{
    MinimizerOptions options;

    options.addOption("option_1", 99);
    options.addOption("option_2", 1.1);
    options.addOption("option_3", "xxx");

    EXPECT_EQ(options.toOptionString(), "option_1=99;option_2=1.1;option_3=xxx;");
}

TEST_F(MinimizerOptionsTest, setOptionsFromString)
{
    MinimizerOptions options;

    options.addOption("Strategy", 1);
    options.addOption("Tolerance", 0.01);
    options.addOption("Algorithm", "Default");
    EXPECT_EQ(1, options.optionValue<int>("Strategy"));
    EXPECT_EQ(0.01, options.optionValue<double>("Tolerance"));

    options.setOptionString("Strategy=2;");
    EXPECT_EQ(2, options.optionValue<int>("Strategy"));
    options.setOptionString("Strategy=3");
    EXPECT_EQ(3, options.optionValue<int>("Strategy"));
    EXPECT_EQ(0.01, options.optionValue<double>("Tolerance"));

    options.setOptionString("Strategy=5;Tolerance=0.0001;Algorithm=Unknown");
    EXPECT_EQ(5, options.optionValue<int>("Strategy"));
    EXPECT_EQ(0.0001, options.optionValue<double>("Tolerance"));
    EXPECT_EQ("Unknown", options.optionValue<std::string>("Algorithm"));

    EXPECT_THROW(options.setOptionString("Strategy=5;XXX=y;Tolerance=0.0001;"), std::runtime_error);
}
