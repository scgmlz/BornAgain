#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>

class TestProjectUtils : public ::testing::Test
{
protected:
    //! Helper function to create test file in a given directory (directory should exist).
    void createTestFile(const QString& dirname, const QString& fileName)
    {
        QString filename = dirname.isEmpty() ? fileName : dirname + "/" + fileName;

        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw GUIHelpers::Error("TestProjectUtils::createTestFile() -> Error. "
                                    "Can't create file");

        QTextStream out(&file);
        out << "Test file " << 42 << "\n";
        file.close();
    }
};

TEST_F(TestProjectUtils, test_nonXMLDataInDir)
{
    const QString projectDir = "test_ProjectUtils";

    QDir dir(projectDir);
    if (dir.exists()) {
        EXPECT_TRUE(ProjectUtils::removeRecursively(projectDir) == true);
        EXPECT_TRUE(dir.exists() == false);
    }

    GUIHelpers::createSubdir(".", projectDir);
    EXPECT_TRUE(ProjectUtils::exists(projectDir));

    EXPECT_EQ(1, 1);
    QStringList test_nonxml_files{"jobdata_job2_0.int.gz", "refdata_job2_0.int.gz",
                                  "realdata_box_nanodots_0.int.gz", "realdata_untitled_0.int.gz"};

    QStringList test_some_other_files{"user_0.int.gz", "b.txt", "untitled.pro"};

    std::cout << "create files ..." << std::endl;
    for (auto name : test_nonxml_files + test_some_other_files) {
        createTestFile(projectDir, name);
        ASSERT_TRUE(ProjectUtils::exists(projectDir + "/" + name));
    }

    std::cout << "check nonXMLDataInDir ..." << std::endl;
    // Check nonXMLDataInDir method, should contain only files from test_nonxml_files.
    QStringList nonxml = ProjectUtils::nonXMLDataInDir(projectDir);

    std::cout << "sort files ..." << std::endl;
    nonxml.sort();
    test_nonxml_files.sort();
    EXPECT_EQ(nonxml.size(), 4);
    EXPECT_EQ(test_nonxml_files, nonxml);

    std::cout << "remove nonxml files ..." << std::endl;
    EXPECT_TRUE(ProjectUtils::removeFiles(projectDir, nonxml) == true);

    std::cout << "check that no files left ..." << std::endl;
    nonxml = ProjectUtils::nonXMLDataInDir(projectDir);
    EXPECT_EQ(nonxml.size(), 0);
}

//! Test substraction of two lists (scenario: old files on disk vs new files).

TEST_F(TestProjectUtils, test_stringListSubstraction)
{
    QStringList oldFiles = QStringList() << "a.int.gz"
                                         << "b.int.gz"
                                         << "c.int.gz";

    QStringList newFiles = QStringList() << "d.int.gz"
                                         << "b_renamed.int.gz"
                                         << "c.int.gz"
                                         << "a.int.gz";

    QStringList diff = ProjectUtils::substract(oldFiles, newFiles);
    EXPECT_EQ(diff.size(), 1);
    EXPECT_EQ(diff.at(0), "b.int.gz");
}
