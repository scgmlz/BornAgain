#include "Core/Tools/FileSystemUtils.h"
#include "Tests/GTestWrapper/google_test.h"

class FileSystemUtilsTest : public ::testing::Test
{
};

TEST_F(FileSystemUtilsTest, extention)
{
    EXPECT_EQ(FileSystemUtils::extension(""), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt.gz"), ".gz");
}

TEST_F(FileSystemUtilsTest, extentions)
{
    EXPECT_EQ(FileSystemUtils::extensions(""), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/file.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/file.txt.gz"), ".txt.gz");
}

TEST_F(FileSystemUtilsTest, filename)
{
    EXPECT_EQ(FileSystemUtils::filename(""), "");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file.txt"), "file.txt");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file"), "file");
}

TEST_F(FileSystemUtilsTest, stem)
{
    EXPECT_EQ(FileSystemUtils::stem(""), "");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt.gz"), "filename.txt");
}

TEST_F(FileSystemUtilsTest, stem_ext)
{
    EXPECT_EQ(FileSystemUtils::stem_ext(""), "");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt.gz"), "filename");
}
