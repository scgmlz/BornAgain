// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/Benchmark.cpp
//! @brief     Implements Benchmark class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Performance/Benchmark.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Benchmark::~Benchmark()
{
    for (auto it = m_data.begin(); it != m_data.end(); ++it) {
        delete it->second;
    }
}

void Benchmark::start(const std::string& name)
{
    std::cout << "Benchmark::start() -> Starting '" << name << "'" << std::endl;
    if (m_data.find(name) == m_data.end())
        m_data.insert(name, new Duration());

    m_data[name]->start();
}

void Benchmark::stop(const std::string& name)
{
    if (m_data.find(name) == m_data.end())
        throw std::runtime_error("Benchmark::stop() -> No such process '" + name + "'");

    m_data[name]->stop();
}

double Benchmark::runTime(const std::string& name)
{
    if (m_data.find(name) == m_data.end())
        throw std::runtime_error("Benchmark::stop() -> No such process '" + name + "'");

    return m_data[name]->runTime();
}

std::string Benchmark::report() const
{
    std::ostringstream result;

    for (auto it = m_data.begin(); it != m_data.end(); ++it) {
        std::string name(it->first);
        name.resize(30, ' ');
        result << name << " : " << std::setprecision(6) << it->second->runTime() << "\n";
    }

    return result.str();
}

//! Tests method by running it several times.

void Benchmark::test_method(const std::string& name, std::function<void()> f, int ntries)
{
    std::cout << "   " << name << " trying " << std::to_string(ntries) << " times\n";

    // warming up
    for (int i = 0; i < ntries / 10; ++i)
        f();

    start(name);

    for (int i = 0; i < ntries; ++i)
        f();

    stop(name);
}
