// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/Core/Threading.h
//! @brief     Defines MultiThreadPerformanceTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADING_H
#define BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADING_H

#include <map>
#include <vector>

//! Functional test to validate multi-thread performance.
//! Two aspects are addressed: performance scaling with number of threads, influence of
//! simulation settings on scaling.

class MultiThreadPerformanceTest
{
public:
    bool runTest();

    struct TestResult {
        std::string simulation_type;
        int nrepetitions;
        int nthreads;
        long time_msec;
        double scale_par;
    };

    struct SimData {
        std::string name;
        size_t nrepetitions;
    };

    using test_results_t = std::vector<TestResult>;
    using test_map_t = std::map<std::string, test_results_t>;

private:
    void warm_up() const;
    test_map_t run_measurements(std::vector<size_t> threads_data,
                                std::vector<SimData> sim_data) const;
    void fancy_print(const test_map_t& results) const;
    TestResult test_case(const std::string& sim_type, int nrepetitions, int nthreads) const;
};

#endif // BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADING_H
