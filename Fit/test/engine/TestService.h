// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/engine/TestService.h
//! @brief     Defines class TestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TESTSERVICE_H
#define TESTSERVICE_H

#include "ITestService.h"
#include <boost/format.hpp>
#include <iostream>
#include <string>

//! @class TestService
//! @ingroup standard_samples
//! @brief Main class to run standard functional test from standalone executable.
//! Test name is obtained from command line parameters and then constructed via templated factory.

template <typename T> class TestService : public ITestService
{
public:
    TestService() {}

    bool execute(int argc, char** argv)
    {
        std::string test_name = argc > 1 ? std::string(argv[1]) : std::string();

        if (!m_test_factory.contains(test_name)) {
            if (!test_name.empty())
                std::cout << "No test with name '" << test_name << "'.\n";
            for (auto it : m_test_factory)
                std::cout << boost::format("%-30s | %-50s\n") % it.first % it.second;
            return false;
        }

        auto test = m_test_factory.createTest(test_name);
        bool result = test->execute();

        std::cout << boost::format("%-15s | %-50s -> %-5s\n") % test->getName()
                         % test->description() % (result ? "OK" : "FAILED");

        return result;
    }

private:
    T m_test_factory;
};

#endif
