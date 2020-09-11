// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/Core/Threading.cpp
//! @brief     Implements MultiThreadPerformanceTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Basics/Units.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPattern.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/StandardSamples/CylindersBuilder.h"
#include "Core/StandardSamples/ParaCrystalBuilder.h"
#include "Tests/Performance/Core/ThreadingComponents.h"
#include <algorithm>
#include <boost/format.hpp>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include <vector>

using namespace TestComponents;

//! Functional test to validate multi-thread performance.
//! Two aspects are addressed: performance scaling with number of threads, influence of
//! simulation settings on scaling.

class MultiThreadPerformanceTest
{
public:
    bool runTest();

    struct TestResult {
        std::string simulation_type;
        size_t nrepetitions;
        size_t nthreads;
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
    TestResult test_case(const std::string& sim_type, size_t nrepetitions, size_t nthreads) const;
};

namespace
{

const auto now = std::chrono::high_resolution_clock::now;
const auto duration = [](auto time_interval) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(time_interval).count();
};

const std::string sim_simple = "Simple";
const std::string sim_realistic = "Real";
const std::string sim_heavy = "Heavy";
const std::string sim_large = "Large";
const std::string sim_wavelength = "Wave";
const std::string sim_mc = "MC";

const std::vector<std::string> available_sims = {sim_simple, sim_realistic,  sim_heavy,
                                                 sim_large,  sim_wavelength, sim_mc};

const std::map<std::string, std::string> sim_description = {
    {sim_simple, "Simple sample, small detector"},
    {sim_realistic, "Simple sample, realistic detector"},
    {sim_heavy, "Complex sample, realistic detector"},
    {sim_large, "Trivial sample, huge detector"},
    {sim_wavelength, "Trivial sample, tiny detector, huge wavelength distribution"},
    {sim_mc, "Complex sample, small detector, monte-carlo integration"}};

using builder_t = std::function<std::unique_ptr<Simulation>()>;
std::map<std::string, builder_t> builders{
    {sim_simple, CreateSimpleGISAS},           {sim_realistic, CreateRealisticGISAS},
    {sim_heavy, CreateRealisticAndHeavyGISAS}, {sim_large, CreateGiganticGISAS},
    {sim_wavelength, CreateWavelengthGISAS},   {sim_mc, CreateMCGISAS}};

//! Calculates scale factor (100% means perfect scaling with number of threads).
void normalize_to_single_thread(MultiThreadPerformanceTest::test_results_t& data)
{
    const double single_thread_performance = data[0].time_msec;
    for (auto& x : data)
        x.scale_par = 100.0 * single_thread_performance / (x.time_msec * x.nthreads);
}

//! Returns list of threads to measure. For system with 8 hardware threads
//! the list will be formed as {1, 2, 4, 6, 8},
//! for 32 threads {1, 2, 4, 8, 10, 12, 16, 20, 24, 28, 32}
std::vector<size_t> threads_to_measure()
{
    std::vector<size_t> result;
    auto max_threads = std::thread::hardware_concurrency();
    for (size_t n_thread = 1; n_thread <= max_threads; ++n_thread) {
        size_t div = (n_thread / 16 == 0) ? 2 : 4 * (n_thread / 16);
        if (n_thread % div == 0 || n_thread == 1 || n_thread == max_threads)
            result.push_back(n_thread);
    }
    return result;
}

} // namespace

bool MultiThreadPerformanceTest::runTest()
{
    std::cout << "MultiThreadPerformanceTest::runTest()" << std::endl;

    //    std::vector<SimData> sim_data = {{sim_realistic, 10}};
    //    std::vector<size_t> threads_data = {1};

    // define simulation sizes and number of threads
    std::vector<SimData> sim_data = {{sim_simple, 300}, {sim_realistic, 10}, {sim_heavy, 1},
                                     {sim_large, 1},    {sim_wavelength, 1}, {sim_mc, 1}};
    std::vector<size_t> threads_data = threads_to_measure();

    warm_up();

    auto results = run_measurements(threads_data, sim_data);

    // normalize results to single thread measurement
    for (auto& result : results)
        normalize_to_single_thread(result.second);

    fancy_print(results);

    return true;
}

//! Warm up all cores.
void MultiThreadPerformanceTest::warm_up() const
{
    std::cout << "Warming up" << std::endl;
    test_case(sim_simple, 500, std::thread::hardware_concurrency());
}

//! Runs all measurements.
MultiThreadPerformanceTest::test_map_t
MultiThreadPerformanceTest::run_measurements(std::vector<size_t> threads_data,
                                             std::vector<SimData> sim_data) const
{
    const auto start_time = now();

    test_map_t results;
    for (const auto& sim : sim_data) {
        for (auto n_thread : threads_data) {
            std::cout << "MultiThreadPerformanceTest::test_case() -> sim_type:'" << sim.name
                      << "', nrepetitions:" << sim.nrepetitions << " nthreads:" << n_thread << "\n";
            results[sim.name].push_back(test_case(sim.name, sim.nrepetitions, n_thread));
        }
    }

    std::cout << "Total time:" << duration(now() - start_time) / 1000. << " sec." << std::endl;
    return results;
}

//! Prints fancy table with results of measurements.
void MultiThreadPerformanceTest::fancy_print(const test_map_t& results) const
{
    // print results
    std::ostringstream ostr;
    ostr << "\nPerformance in msec and thread scaling efficiency for various simulations.\n";

    // extract vector with number of threads used
    std::vector<size_t> nthreads_data;
    auto first_sim_results = results.begin()->second;
    for (const auto& measurement : first_sim_results)
        nthreads_data.push_back(measurement.nthreads);

    // print performance table
    ostr << "n.t.  |";
    for (auto sim : available_sims) {
        if (results.find(sim) == results.end())
            continue;
        ostr << boost::format(" %-14s|") % sim;
    }
    ostr << "\n";
    for (size_t i = 0; i < nthreads_data.size(); ++i) {
        ostr << boost::format("%-4d  | ") % nthreads_data[i];
        for (auto sim : available_sims) {
            if (results.find(sim) == results.end())
                continue;
            auto vec = results.at(sim);
            ostr << boost::format("%-5d  %-5.1f  | ") % vec[i].time_msec % vec[i].scale_par;
        }
        ostr << "\n";
    }
    ostr << "\n";

    // print simulation description
    for (auto sim : available_sims) {
        if (results.find(sim) == results.end())
            continue;
        ostr << boost::format("%-10s : %s (%d times)\n") % sim % sim_description.at(sim)
                    % results.at(sim)[0].nrepetitions;
    }

    std::cout << ostr.str() << "\n";
}

//! Runs simulation of given type with fixed number of threads.

MultiThreadPerformanceTest::TestResult
MultiThreadPerformanceTest::test_case(const std::string& sim_type, size_t nrepetitions,
                                      size_t nthreads) const
{
    auto simulation = builders[sim_type]();
    simulation->getOptions().setNumberOfThreads(nthreads);

    const auto start_time = now();
    for (size_t i_rep = 0; i_rep < nrepetitions; i_rep++)
        simulation->runSimulation();

    return {sim_type, nrepetitions, nthreads, static_cast<int>(duration(now() - start_time)), 0.0};
}

int main()
{
    return !MultiThreadPerformanceTest().runTest();
}
