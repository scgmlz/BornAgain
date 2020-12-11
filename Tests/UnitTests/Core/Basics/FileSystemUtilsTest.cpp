#include "Base/Utils/FileSystemUtils.h"
#include "BATesting.h"
#include "Tests/GTestWrapper/google_test.h"
#include <filesystem>
#include <fstream>

class FileSystemUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        FileSystemUtils::createDirectories(BATesting::TestOutDir_Core());
        ASSERT_TRUE(std::filesystem::exists(BATesting::TestOutDir_Core()));
        ASSERT_TRUE(assureNonExistingTestCasePath());
    }

    void TearDown() override {
        EXPECT_TRUE(assureNonExistingTestCasePath());
        // by design no removing of BATesting::TestOutDir_Core() which may have been
        // created in SetUp
    }

    std::string testCaseFolderName() const {
        const auto test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        return test_info->test_case_name() + std::string("_") + test_info->name();
    }

    std::string testCasePath() const {
        return FileSystemUtils::jointPath(BATesting::TestOutDir_Core(), testCaseFolderName());
    }

    //! Assures the test case specific path is not existent. Removes it if necessary.
    bool assureNonExistingTestCasePath() const {
        // current dir must not be the dir to be removed
        std::filesystem::current_path(BATesting::TestOutDir_Core());
        std::filesystem::remove_all(testCasePath());
        return !std::filesystem::exists(testCasePath());
    }
};

TEST_F(FileSystemUtilsTest, extension) {
    EXPECT_EQ(FileSystemUtils::extension(""), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/."), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.."), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.hidden"), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.hidden.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt.gz"), ".gz");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt.GZ"), ".GZ");
}

TEST_F(FileSystemUtilsTest, extensions) {
    EXPECT_EQ(FileSystemUtils::extensions(""), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/."), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.."), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.hidden"), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.hidden.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.hidden.txt.gz"), ".txt.gz");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/f"), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/f.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/file.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/file.txt.gz"), ".txt.gz");
}

TEST_F(FileSystemUtilsTest, filename) {
    EXPECT_EQ(FileSystemUtils::filename(""), "");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/."), ".");   // sic! according to C++17
    EXPECT_EQ(FileSystemUtils::filename("/home/james/.."), ".."); // sic! according to C++17
    EXPECT_EQ(FileSystemUtils::filename("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file.txt"), "file.txt");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file"), "file");
}

TEST_F(FileSystemUtilsTest, stem) {
    EXPECT_EQ(FileSystemUtils::stem(""), "");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/."), ".");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.."), "..");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden.txt"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden.txt.gz"), ".hidden.txt");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt.gz"), "filename.txt");
}

TEST_F(FileSystemUtilsTest, stem_ext) {
    EXPECT_EQ(FileSystemUtils::stem_ext(""), "");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/."), ".");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.."), "..");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden.txt"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden.txt.gz"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename"), "filename");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt.gz"), "filename");
}

TEST_F(FileSystemUtilsTest, createDirectory) {
    // with absolute path
    EXPECT_TRUE(FileSystemUtils::createDirectory(testCasePath()));
    EXPECT_FALSE(FileSystemUtils::createDirectory(testCasePath()));

    // with relative path
    std::filesystem::current_path(testCasePath());
    EXPECT_TRUE(FileSystemUtils::createDirectory("sub"));
    EXPECT_FALSE(FileSystemUtils::createDirectory("sub"));
    EXPECT_TRUE(std::filesystem::exists("sub"));
    EXPECT_TRUE(std::filesystem::exists(FileSystemUtils::jointPath(testCasePath(), "sub")));
}

TEST_F(FileSystemUtilsTest, createDirectories) {
    // with absolute path
    const auto sub1 = FileSystemUtils::jointPath(testCasePath(), "sub1");
    const auto sub2 = FileSystemUtils::jointPath(sub1, "sub2");

    EXPECT_TRUE(FileSystemUtils::createDirectories(sub2));
    EXPECT_FALSE(FileSystemUtils::createDirectories(sub2));
    EXPECT_TRUE(std::filesystem::exists(testCasePath()));
    EXPECT_TRUE(std::filesystem::exists(sub1));
    EXPECT_TRUE(std::filesystem::exists(sub2));

    // with relative path
    const auto sub4 = "sub3/sub4";
    std::filesystem::current_path(sub2);
    EXPECT_TRUE(FileSystemUtils::createDirectories(sub4));
    EXPECT_FALSE(FileSystemUtils::createDirectories(sub4));
    EXPECT_TRUE(std::filesystem::exists("sub3"));
    EXPECT_TRUE(std::filesystem::exists("sub3/sub4"));
    EXPECT_TRUE(std::filesystem::exists(FileSystemUtils::jointPath(sub2, sub4)));
}

TEST_F(FileSystemUtilsTest, jointPath) {
#ifdef _WIN32
    EXPECT_EQ(FileSystemUtils::jointPath("a", "b"), "a\\b");
#else
    EXPECT_EQ(FileSystemUtils::jointPath("a", "b"), "a/b");
#endif

    EXPECT_ANY_THROW(FileSystemUtils::jointPath("", ""));
    EXPECT_ANY_THROW(FileSystemUtils::jointPath("a", ""));
    EXPECT_ANY_THROW(FileSystemUtils::jointPath("", "b"));
}

TEST_F(FileSystemUtilsTest, filesInDirectory_IsFileExists) {
    EXPECT_ANY_THROW(FileSystemUtils::filesInDirectory("non-existent/directory"));

    // assure clean preconditions
    ASSERT_TRUE(FileSystemUtils::createDirectories(testCasePath()));
    EXPECT_TRUE(FileSystemUtils::filesInDirectory(testCasePath()).empty());

    // create a few files
    std::filesystem::current_path(testCasePath());
    std::ofstream("file1.txt");
    std::ofstream("file2.txt");
    std::ofstream("file3.txt");

    EXPECT_EQ(FileSystemUtils::filesInDirectory(testCasePath()).size(), 3); // abs
    EXPECT_EQ(FileSystemUtils::filesInDirectory(".").size(), 3);            // rel
    const auto files = FileSystemUtils::filesInDirectory(".");
    EXPECT_TRUE(std::find(files.begin(), files.end(), "file1.txt") != files.end());
    EXPECT_TRUE(std::find(files.begin(), files.end(), "file2.txt") != files.end());
    EXPECT_TRUE(std::find(files.begin(), files.end(), "file3.txt") != files.end());

    // tests for IsFileExists
    EXPECT_TRUE(FileSystemUtils::IsFileExists("file1.txt"));
    EXPECT_TRUE(FileSystemUtils::IsFileExists("file2.txt"));
    EXPECT_TRUE(FileSystemUtils::IsFileExists("file3.txt"));
    EXPECT_FALSE(FileSystemUtils::IsFileExists("nonexisting.txt"));
}