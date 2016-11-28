// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IReferencedTest.cpp
//! @brief     Implements pure virtual base class IReferencedTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IReferencedTest.h"
#include "IntensityDataFunctions.h"
#include <iostream>
#include <cstdlib>

//! Compares two intensity maps, and returns true unless they disagree beyond their variability.
bool IReferencedTest::compareIntensityMaps(
    const OutputData<double>& dat, const OutputData<double>& ref) const
{
    double diff = IntensityDataFunctions::getRelativeDifference(dat, ref);
    if ( diff > m_threshold ) {
        std::cerr << "Failed: Relative difference between dat and ref = " << diff
                  << " is above given threshold = " << m_threshold << "\n";
        return false;
    }
    std::cout << "Relative difference between dat and ref = " << diff
              << " is within given threshold = " << m_threshold << "\n";
    return true;
}

#ifdef PYTHON_EXECUTABLE
//! Runs a python command, prints messages, returns true unless the system call failed.
bool IReferencedTest::runPython(const std::string& py_command)
{
#ifndef _WIN32
    std::string sys_command = std::string("PYTHONPATH=") + BUILD_LIB_DIR + " " +
        PYTHON_EXECUTABLE + " " + py_command;
#else
    std::string sys_command = std::string("set PYTHONPATH=") + BUILD_LIB_DIR + " & " +
        PYTHON_EXECUTABLE + " " + py_command;
#endif
    std::cout << sys_command << std::endl/*sic*/; // flush output before calling std::system
    int ret = std::system(sys_command.c_str());
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << "\n";
        return false;
    }
    return true;
}
#endif
