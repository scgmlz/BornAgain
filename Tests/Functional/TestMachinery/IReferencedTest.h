// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IReferencedTest.h
//! @brief     Defines pure virtual base class IReferencedTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IREFERENCEDTEST_H
#define IREFERENCEDTEST_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include <map>
#include <string>

//! Base class for tests that compare results with reference data.
//! @ingroup standard_samples

class BA_CORE_API_ IReferencedTest : public IFunctionalTest
{
public:
    IReferencedTest();
    IReferencedTest(const std::string& name, const std::string& description, double threshold)
        : IFunctionalTest(name, description), m_threshold(threshold) {}
    virtual ~IReferencedTest() {}

    bool runTest() =0;

protected:
    double m_threshold;

    bool compareIntensityMaps(const OutputData<double>& dat, const OutputData<double>& ref) const;
    static bool runPython(const std::string& py_command);
};

#endif // IREFERENCEDTEST_H
