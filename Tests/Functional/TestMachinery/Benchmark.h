// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/Benchmark.h
//! @brief     Defines Benchmark class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "WinDllMacros.h"
#include "TimeInterval.h"
#include "OrderedMap.h"
#include <string>
#include <map>
#include <functional>

class BA_CORE_API_ Duration {
public:
    Duration() : m_totalTime(0){}

    void start() { m_time_interval.start(); }
    void stop()  { m_time_interval.stop(); m_totalTime += m_time_interval.runTime();}
    double runTime() const { return m_totalTime; }

private:
    TimeInterval m_time_interval;
    double m_totalTime;
};

//! Benchmark tool to measure duration of several processes.

class BA_CORE_API_ Benchmark
{
    typedef OrderedMap<std::string, Duration*> BenchmarkMap;
public:
    Benchmark() {}
    ~Benchmark();

    void start(const std::string& name);
    void stop(const std::string& name);
    double runTime(const std::string& name);
    std::string report() const;
    const BenchmarkMap& retrieveData() const {return m_data;}

    void test_method(const std::string& name, std::function<void(void)> f, int ntries);

private:
    BenchmarkMap m_data;
};

#endif // COREIOTEST_H
