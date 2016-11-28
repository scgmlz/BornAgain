// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/export/PyExportTest.h
//! @brief     Defines class PyExportTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYEXPORTTEST_H
#define PYEXPORTTEST_H

#include "IReferencedTest.h"
#include "OutputData.h"

//! A functional test of PyCore (the Python wrapper of BornAgain/Core).
//!   Performs a given standard simulation, both directly and from a Python dump.
//!   Invoked from PyExportStandardTest.

class PyExportTest : public IReferencedTest
{
public:
    PyExportTest(const std::string& name, const std::string& description,
                 class GISASSimulation* reference_simulation, double threshold);
    virtual ~PyExportTest();

    bool runTest() final;

private:
    std::string getPySuiteFileNameAndPath() const;

    class GISASSimulation* m_reference_simulation;
    class GISASSimulation* m_domain_simulation;
};

#endif // PYEXPORTTEST_H
