// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IStandardTest.h
//! @brief     Defines pure virtual base class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISTANDARDTEST_H
#define ISTANDARDTEST_H

#include "IFunctionalTest.h"
#include <string>
#include <memory>

//! Base class for tests that compare results with reference data.
//! @ingroup standard_samples

class BA_CORE_API_ IStandardTest : public IFunctionalTest
{
public:
    IStandardTest(const std::string& name, const std::string& description,
                  double threshold);

    ~IStandardTest();

    bool runTest() =0;

protected:
    double m_threshold;
};

#endif // ISTANDARDTEST_H
