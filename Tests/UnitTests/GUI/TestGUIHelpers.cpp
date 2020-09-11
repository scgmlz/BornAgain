#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"

class TestGUIHelpers : public ::testing::Test
{
};

TEST_F(TestGUIHelpers, test_VersionString)
{
    int vmajor(0), vminor(0), vpatch(0);

    EXPECT_EQ(true, GUIHelpers::parseVersion("1.5.0", vmajor, vminor, vpatch));
    EXPECT_EQ(1, vmajor);
    EXPECT_EQ(5, vminor);
    EXPECT_EQ(0, vpatch);

    EXPECT_FALSE(GUIHelpers::parseVersion("15.0", vmajor, vminor, vpatch));

    QString min_version("1.5.0");
    EXPECT_EQ(GUIHelpers::isVersionMatchMinimal("1.5.0", min_version), true);
    EXPECT_EQ(GUIHelpers::isVersionMatchMinimal("1.5.1", min_version), true);
    EXPECT_EQ(GUIHelpers::isVersionMatchMinimal("1.6.0", min_version), true);
    EXPECT_EQ(GUIHelpers::isVersionMatchMinimal("2.4.9", min_version), true);

    EXPECT_EQ(GUIHelpers::isVersionMatchMinimal("1.4.9", min_version), false);
    EXPECT_EQ(GUIHelpers::isVersionMatchMinimal("0.6.9", min_version), false);
}
