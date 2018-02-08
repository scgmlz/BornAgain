#include "google_test.h"
#include "BornAgainNamespace.h"
#include "Distributions.h"
#include "ParameterDistribution.h"
#include "PythonFormatting.h"
#include "RealLimits.h"
#include "Units.h"
#include "FixedBinAxis.h"

class PythonFormattingTest : public ::testing::Test
{
public:
    ~PythonFormattingTest();
};

PythonFormattingTest::~PythonFormattingTest() = default;

TEST_F(PythonFormattingTest, ValueTimesUnits)
{
    EXPECT_EQ("2.0*nm", PythonFormatting::printValue(2.0, BornAgain::UnitsNm));
    EXPECT_EQ("2.0*deg", PythonFormatting::printValue(2.0 * Units::deg, BornAgain::UnitsRad));
    EXPECT_EQ("2.0", PythonFormatting::printValue(2.0, BornAgain::UnitsNone));
}

TEST_F(PythonFormattingTest, RealLimits)
{
    EXPECT_EQ("RealLimits.positive()", PythonFormatting::printRealLimits(RealLimits::positive()));

    EXPECT_EQ("RealLimits.nonnegative()",
              PythonFormatting::printRealLimits(RealLimits::nonnegative()));

    EXPECT_EQ("RealLimits.lowerLimited(1.0)",
              PythonFormatting::printRealLimits(RealLimits::lowerLimited(1.0)));
    EXPECT_EQ("RealLimits.lowerLimited(1.0*nm)",
              PythonFormatting::printRealLimits(RealLimits::lowerLimited(1.0), BornAgain::UnitsNm));
    EXPECT_EQ("RealLimits.lowerLimited(1.0*deg)",
              PythonFormatting::printRealLimits(RealLimits::lowerLimited(1.0 * Units::deg),
                                                BornAgain::UnitsRad));

    EXPECT_EQ("RealLimits.upperLimited(1.0)",
              PythonFormatting::printRealLimits(RealLimits::upperLimited(1.0)));
    EXPECT_EQ("RealLimits.upperLimited(1.0*nm)",
              PythonFormatting::printRealLimits(RealLimits::upperLimited(1.0), BornAgain::UnitsNm));
    EXPECT_EQ("RealLimits.upperLimited(1.0*deg)",
              PythonFormatting::printRealLimits(RealLimits::upperLimited(1.0 * Units::deg),
                                                BornAgain::UnitsRad));

    EXPECT_EQ("RealLimits.limited(1.0, 2.0)",
              PythonFormatting::printRealLimits(RealLimits::limited(1.0, 2.0)));
    EXPECT_EQ("RealLimits.limited(1.0*nm, 2.0*nm)",
              PythonFormatting::printRealLimits(RealLimits::limited(1.0, 2.0), BornAgain::UnitsNm));
    EXPECT_EQ("RealLimits.limited(1.0*deg, 2.0*deg)",
              PythonFormatting::printRealLimits(
                  RealLimits::limited(1.0 * Units::deg, 2.0 * Units::deg), BornAgain::UnitsRad));

    // testing printing of real limits in the context of ParameterDistribution and similar
    EXPECT_EQ(", ba.RealLimits.limited(1.0*deg, 2.0*deg)",
              PythonFormatting::printRealLimitsArg(
                  RealLimits::limited(1.0 * Units::deg, 2.0 * Units::deg), BornAgain::UnitsRad));

    EXPECT_EQ("", PythonFormatting::printRealLimitsArg(RealLimits::limitless()));
}

TEST_F(PythonFormattingTest, printDistribution)
{
    EXPECT_EQ(PythonFormatting::printDistribution(DistributionGate(1.0, 2.0)),
              "ba.DistributionGate(1.0, 2.0)");

    EXPECT_EQ(PythonFormatting::printDistribution(DistributionGate(1.0, 2.0), BornAgain::UnitsNm),
              "ba.DistributionGate(1.0*nm, 2.0*nm)");

    EXPECT_EQ(PythonFormatting::printDistribution(
                  DistributionGate(1.0 * Units::deg, 2.0 * Units::deg), BornAgain::UnitsRad),
              "ba.DistributionGate(1.0*deg, 2.0*deg)");

    EXPECT_EQ(PythonFormatting::printDistribution(DistributionLogNormal(1.0 * Units::deg, 0.01),
                                                  BornAgain::UnitsRad),
              "ba.DistributionLogNormal(1.0*deg, 0.01)");
}

TEST_F(PythonFormattingTest, printParameterDistribution)
{

    DistributionGate gate(1.0, 2.0);
    ParameterDistribution dist("ParName", gate, 5, 2.0);

    // No RealLimits defined
    EXPECT_EQ(PythonFormatting::printParameterDistribution(dist, "distr_1"),
              "ba.ParameterDistribution(\"ParName\", distr_1, 5, 2.0)");

    // RealLimits defined, units unknown
    ParameterDistribution dist2("ParName", gate, 5, 2.0, RealLimits::limited(1.0, 2.0));
    EXPECT_EQ(PythonFormatting::printParameterDistribution(dist2, "distr_1"),
              "ba.ParameterDistribution(\"ParName\", distr_1, "
              "5, 2.0, ba.RealLimits.limited(1.0, 2.0))");

    // RealLimits defined, units explicetely set
    ParameterDistribution dist3("ParName", gate, 5, 2.0, RealLimits::limited(1.0, 2.0));
    EXPECT_EQ(PythonFormatting::printParameterDistribution(dist3, "distr_1", BornAgain::UnitsNm),
              "ba.ParameterDistribution(\"ParName\", distr_1, "
              "5, 2.0, ba.RealLimits.limited(1.0*nm, 2.0*nm))");

    // RealLimits defined, checking that method guess radians units correctly
    ParameterDistribution dist4("/Particle/ZRotation/Angle", gate, 5, 2.0,
                                RealLimits::limited(1.0 * Units::deg, 2.0 * Units::deg));
    EXPECT_EQ(PythonFormatting::printParameterDistribution(dist4, "distr_1", BornAgain::UnitsRad),
              "ba.ParameterDistribution(\"/Particle/ZRotation/Angle\", "
              "distr_1, 5, 2.0, ba.RealLimits.limited(1.0*deg, 2.0*deg))");
}

TEST_F(PythonFormattingTest, printAxis)
{
    FixedBinAxis axis1("axis0", 10, -1.0, 2.0);
    EXPECT_EQ(PythonFormatting::printAxis(axis1), "ba.FixedBinAxis(\"axis0\", 10, -1.0, 2.0)");

    FixedBinAxis axis2("axis0", 10, -1.0*Units::deg, 2.0*Units::deg);
    EXPECT_EQ(PythonFormatting::printAxis(axis2, BornAgain::UnitsRad),
              "ba.FixedBinAxis(\"axis0\", 10, -1.0*deg, 2.0*deg)");
}
