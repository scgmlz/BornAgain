#include "Base/Const/Units.h"
#include "Core/Export/PyFmt.h"
#include "Core/Export/PyFmt2.h"
#include "Core/Export/PyFmtLimits.h"
#include "Param/Distrib/Distributions.h"
#include "Param/Distrib/ParameterDistribution.h"
#include "Tests/GTestWrapper/google_test.h"

class PythonFormattingTest : public ::testing::Test {};

TEST_F(PythonFormattingTest, ValueTimesUnits) {
    EXPECT_EQ("2.0*nm", pyfmt::printValue(2.0, "nm"));
    EXPECT_EQ("2.0*deg", pyfmt::printValue(2.0 * Units::deg, "rad"));
    EXPECT_EQ("2.0", pyfmt::printValue(2.0, ""));
}

TEST_F(PythonFormattingTest, RealLimits) {
    EXPECT_EQ("RealLimits.lowerLimited(1.0)",
              pyfmt::printRealLimits(RealLimits::lowerLimited(1.0)));
    EXPECT_EQ("RealLimits.lowerLimited(1.0*nm)",
              pyfmt::printRealLimits(RealLimits::lowerLimited(1.0), "nm"));
    EXPECT_EQ("RealLimits.lowerLimited(1.0*deg)",
              pyfmt::printRealLimits(RealLimits::lowerLimited(1.0 * Units::deg), "rad"));

    EXPECT_EQ("RealLimits.upperLimited(1.0)",
              pyfmt::printRealLimits(RealLimits::upperLimited(1.0)));
    EXPECT_EQ("RealLimits.upperLimited(1.0*nm)",
              pyfmt::printRealLimits(RealLimits::upperLimited(1.0), "nm"));
    EXPECT_EQ("RealLimits.upperLimited(1.0*deg)",
              pyfmt::printRealLimits(RealLimits::upperLimited(1.0 * Units::deg), "rad"));

    EXPECT_EQ("RealLimits.limited(1.0, 2.0)",
              pyfmt::printRealLimits(RealLimits::limited(1.0, 2.0)));
    EXPECT_EQ("RealLimits.limited(1.0*nm, 2.0*nm)",
              pyfmt::printRealLimits(RealLimits::limited(1.0, 2.0), "nm"));
    EXPECT_EQ(
        "RealLimits.limited(1.0*deg, 2.0*deg)",
        pyfmt::printRealLimits(RealLimits::limited(1.0 * Units::deg, 2.0 * Units::deg), "rad"));

    // testing printing of real limits in the context of ParameterDistribution and similar
    EXPECT_EQ(
        ", ba.RealLimits.limited(1.0*deg, 2.0*deg)",
        pyfmt::printRealLimitsArg(RealLimits::limited(1.0 * Units::deg, 2.0 * Units::deg), "rad"));

    EXPECT_EQ("", pyfmt::printRealLimitsArg(RealLimits::limitless()));
}

TEST_F(PythonFormattingTest, printDistribution) {
    EXPECT_EQ(pyfmt2::printDistribution(DistributionGate(1.0, 2.0)),
              "ba.DistributionGate(1.0, 2.0)");

    EXPECT_EQ(pyfmt2::printDistribution(DistributionGate(1.0, 2.0), "nm"),
              "ba.DistributionGate(1.0*nm, 2.0*nm)");

    EXPECT_EQ(
        pyfmt2::printDistribution(DistributionGate(1.0 * Units::deg, 2.0 * Units::deg), "rad"),
        "ba.DistributionGate(1.0*deg, 2.0*deg)");

    EXPECT_EQ(pyfmt2::printDistribution(DistributionLogNormal(1.0 * Units::deg, 0.01), "rad"),
              "ba.DistributionLogNormal(1.0*deg, 0.01)");
}

TEST_F(PythonFormattingTest, printParameterDistribution) {

    DistributionGate gate(1.0, 2.0);
    ParameterDistribution dist("ParName", gate, 5, 2.0);

    // No RealLimits defined
    EXPECT_EQ(pyfmt2::printParameterDistribution(dist, "distr_1"),
              "ba.ParameterDistribution(\"ParName\", distr_1, 5, 2.0)");

    // RealLimits defined, units unknown
    ParameterDistribution dist2("ParName", gate, 5, 2.0, RealLimits::limited(1.0, 2.0));
    EXPECT_EQ(pyfmt2::printParameterDistribution(dist2, "distr_1"),
              "ba.ParameterDistribution(\"ParName\", distr_1, "
              "5, 2.0, ba.RealLimits.limited(1.0, 2.0))");

    // RealLimits defined, units explicetely set
    ParameterDistribution dist3("ParName", gate, 5, 2.0, RealLimits::limited(1.0, 2.0));
    EXPECT_EQ(pyfmt2::printParameterDistribution(dist3, "distr_1", "nm"),
              "ba.ParameterDistribution(\"ParName\", distr_1, "
              "5, 2.0, ba.RealLimits.limited(1.0*nm, 2.0*nm))");

    // RealLimits defined, checking that method guess radians units correctly
    ParameterDistribution dist4("/Particle/ZRotation/Angle", gate, 5, 2.0,
                                RealLimits::limited(1.0 * Units::deg, 2.0 * Units::deg));
    EXPECT_EQ(pyfmt2::printParameterDistribution(dist4, "distr_1", "rad"),
              "ba.ParameterDistribution(\"/Particle/ZRotation/Angle\", "
              "distr_1, 5, 2.0, ba.RealLimits.limited(1.0*deg, 2.0*deg))");
}
