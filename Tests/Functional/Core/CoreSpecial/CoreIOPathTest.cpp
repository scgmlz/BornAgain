// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/CoreIOPathTest.cpp
//! @brief     Defines CoreIOTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BATesting.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Tools/FileSystemUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <memory>

namespace
{
std::unique_ptr<OutputData<double>> createTestData()
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis("x", 10, 0.0, 10.0);
    for (size_t i = 0; i < result->getAllocatedSize(); ++i)
        (*result)[i] = static_cast<double>(i);
    return result;
}

bool test_io(const OutputData<double>* data, const std::string& file_name)
{
    IntensityDataIOFactory::writeOutputData(*data, file_name);
    std::unique_ptr<OutputData<double>> loaded(IntensityDataIOFactory::readOutputData(file_name));
    return IntensityDataFunctions::getRelativeDifference(*data, *loaded) <= 1e-06;
}

} // namespace

class CoreIOPathTest : public ::testing::Test
{
};

TEST_F(CoreIOPathTest, CoreIOPath)
{
    const auto data = createTestData();
    const char filename_rus[] = "\xd0\xb4\xd0\xb0\xd0\xbd\xd0\xbd\xd1\x8b\xd0\xb5\x2e\x69\x6e\x74";
    const char dirname_rus[] =
        "\xd0\xb4\xd0\xb8\xd1\x80\xd0\xb5\xd0\xba\xd1\x82\xd0\xbe\xd1\x80\xd0\xb8\xd1\x8f";

    const boost::filesystem::path test_dir(BATesting::CoreOutputDir());
    const boost::filesystem::path test_subdir("test_CoreIOPathTest");

    FileSystemUtils::createDirectories((test_dir / test_subdir).string());

    // tests file writing when file name contains cyrillic characters
    boost::filesystem::path test_file(filename_rus);
    EXPECT_TRUE(test_io(data.get(), (test_dir / test_subdir / test_file).string()));

    // tests file writing and directory creation when dirname contains cyrillic characters
    boost::filesystem::path test_subdir_rus(dirname_rus);
    FileSystemUtils::createDirectories((test_dir / test_subdir / test_subdir_rus).string());
    EXPECT_TRUE(
        test_io(data.get(), (test_dir / test_subdir / test_subdir_rus / test_file).string()));
}
