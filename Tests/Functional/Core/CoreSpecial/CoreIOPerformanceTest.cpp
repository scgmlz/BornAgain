// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/CoreIOPerformanceTest.cpp
//! @brief     Implements CoreIOTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CoreIOPerformanceTest.h"
#include "IntensityDataIOFactory.h"
#include "Benchmark.h"
#include "Numeric.h"
#include <iostream>
#include <cassert>
#include <random>
#include <iomanip>
#include <boost/format.hpp>

bool CoreIOPerformanceTest::runTest()
{
    std::cout << "CoreIOTest::runTest()" << std::endl;

    bool success(true);

    // 1024x768, zeros
    success &= test_io(1024, 768, false, "int");
    success &= test_io(1024, 768, false, "int.gz");
    success &= test_io(1024, 768, false, "int.bz2");

    // 1024x768, random data
    success &= test_io(1024, 768, true, "int");
    success &= test_io(1024, 768, true, "int.gz");
    success &= test_io(1024, 768, true, "int.bz2");

    // 2048x2048, random data
    success &= test_io(2048, 2048, true, "int");
    success &= test_io(2048, 2048, true, "int.gz");
    success &= test_io(2048, 2048, true, "int.bz2");

    std::cout << report() << std::endl;

    return success;
}

bool CoreIOPerformanceTest::test_io(int nx, int ny, bool random_data, const std::string& ext)
{
    std::cout << "Test " << nx << "x" << ny << ", "
              << (random_data ? "random data" : "zeros")
              << ", file_format: " << ext << "\n";

    TestResults result;
    result.m_nx = nx;
    result.m_ny = ny;
    result.m_data_type = random_data;
    result.m_file_format = ext;

    Benchmark mb;

    std::string test_name("create_data");
    mb.start(test_name);
    auto ref_data = createData(nx, ny, random_data);
    mb.stop(test_name);
    result.m_create_data_time = mb.runTime(test_name);

    test_name = "clone_data";
    mb.start(test_name);
    auto cloned_data = std::unique_ptr<OutputData<double>>(ref_data->clone());
    mb.stop(test_name);
    result.m_clone_data_time = mb.runTime(test_name);

    test_name = "write";
    mb.start(test_name);
    IntensityDataIOFactory::writeOutputData(*ref_data, "xxx."+ext);
    mb.stop(test_name);
    result.m_write_time = mb.runTime(test_name);

    test_name = "read";
    mb.start(test_name);
    auto data = IntensityDataIOFactory::readOutputData("xxx."+ext);
    mb.stop(test_name);
    result.m_read_time = mb.runTime(test_name);

    result.m_biggest_diff = biggest_difference(*data, *ref_data);;

    std::cout << mb.report() << std::endl;
    std::cout << "Diff: " << result.m_biggest_diff << std::endl;

    m_test_results.push_back(result);

    bool success = result.m_biggest_diff  < 1e-10 ? true : false;
    return success;
}

std::unique_ptr<OutputData<double>> CoreIOPerformanceTest::createData(int nx, int ny, bool fill)
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis("x", nx, 0.0, static_cast<double>(nx));
    result->addAxis("y", ny, 0.0, static_cast<double>(ny));

    if (fill) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 12);
        for (size_t i = 0; i < result->getAllocatedSize(); ++i) {
            double value = std::pow(10, dis(gen));
            (*result)[i] = value;
        }
    }

    return result;
}

//! Returns biggest element difference found.

double CoreIOPerformanceTest::biggest_difference(const OutputData<double>& data, const OutputData<double>& ref)
{
    if (data.getAllocatedSize() != ref.getAllocatedSize())
        throw std::runtime_error("CoreIOTest::biggest_difference() -> Error. Size is different.");

    double max_diff = std::numeric_limits<double>::min();

    for (size_t i = 0; i < data.getAllocatedSize(); ++i) {
        double diff = Numeric::GetRelativeDifference(data[i], ref[i]);
        max_diff = std::max(diff, max_diff);
    }
    return max_diff;
}

std::string CoreIOPerformanceTest::report() const
{
    std::ostringstream result;

    result << "--- CoreIOTest::report() ---\n";
    result << "Size      | format     | data  | create  clone   read    write   | diff \n";
    for(auto res : m_test_results) {
        result << boost::format("%-4dx%-4d | %-10s |   %1d   | %-7.3f %-7.3f %-7.3f %-7.3f | %g \n")
                  % res.m_nx % res.m_ny %res.m_file_format
                  % res.m_data_type
                  % res.m_create_data_time % res.m_clone_data_time
                  % res.m_read_time % res.m_write_time
                  % res.m_biggest_diff;
    }

    return result.str();
}
