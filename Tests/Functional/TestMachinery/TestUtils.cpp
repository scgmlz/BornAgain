// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.cpp
//! @brief     Implements TestUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestUtils.h"
#include "StandardTestCatalogue.h"
#include "IntensityDataFunctions.h"
#include "BABuild.h"
#include <iostream>
#include <cstdlib>

StandardTestInfo TestUtils::testInfo(int argc, char** argv)
{
    static StandardTestCatalogue catalogue = StandardTestCatalogue();

    std::string test_name = argc>1 ? std::string(argv[1]) : std::string();

    if (!catalogue.contains(test_name)) {
        std::cout<<"There is no test named '"<< test_name << "'\n";
        std::cout << "Available tests:\n";
        catalogue.printCatalogue(std::cout);
        return StandardTestInfo();
    }

    return catalogue.testInfo(test_name);
}

bool TestUtils::isTheSame(const OutputData<double>& dat, const OutputData<double>& ref,
                          double threshold)
{
    double diff = IntensityDataFunctions::getRelativeDifference(dat, ref);
    if ( diff > threshold ) {
        std::cerr << "Failed: Relative difference between dat and ref = " << diff
                  << " is above given threshold = " << threshold << "\n";
        return false;
    }
    std::cout << "Relative difference between dat and ref = " << diff
              << " is within given threshold = " << threshold << "\n";
    return true;
}


//! Runs a python command, prints messages, returns true unless the system call failed.
bool TestUtils::runPython(const std::string& py_command)
{
#ifndef _WIN32
    std::string sys_command = std::string("PYTHONPATH=") + BABuild::buildLibDir() + " " +
        std::string("NOPLOT=TRUE") + " " + BABuild::pythonExecutable() + " -B " + py_command;
#else
    std::string sys_command = std::string("set PYTHONPATH=") + BABuild::buildLibDir() + " & " +
        std::string("set NOPLOT=TRUE") + " & " +BABuild::pythonExecutable() + " -B " + py_command;
#endif
    std::cout << sys_command << std::endl/*sic*/; // flush output before calling std::system
    int ret = std::system(sys_command.c_str());
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << "\n";
        return false;
    }
    return true;
}
