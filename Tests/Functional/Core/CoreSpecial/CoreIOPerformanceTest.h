// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreIO/CoreIOTest.h
//! @brief     Defines CoreIOTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef COREIOPERFORMANCETEST_H
#define COREIOPERFORMANCETEST_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "Benchmark.h"
#include <memory>

//! Functional test to validate read/write of large data files.

class CoreIOPerformanceTest : public IFunctionalTest
{
public:
    CoreIOPerformanceTest() {}
    ~CoreIOPerformanceTest() {}

    bool runTest();

private:

    struct TestResults {
        int m_nx;
        int m_ny;
        std::string m_file_format;
        bool m_data_type;
        double m_create_data_time;
        double m_clone_data_time;
        double m_read_time;
        double m_write_time;
        double m_biggest_diff;
    };

    bool test_io(int nx, int ny, bool random_data, const std::string& ext);
    std::unique_ptr<OutputData<double>> createData(int nx, int ny, bool fill = false);
    double biggest_difference(const OutputData<double>& data, const OutputData<double>& ref);
    std::string report() const;

    std::vector<TestResults> m_test_results;
};

#endif // COREIOPERFORMANCETEST_H
