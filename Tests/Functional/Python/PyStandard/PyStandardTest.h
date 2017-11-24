// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/export/PyStandardTest.h
//! @brief     Defines class PyStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSTANDARDTEST_H
#define PYSTANDARDTEST_H

#include "IStandardTest.h"

class Simulation;
class GISASSimulation;

//! A functional test of PyCore (the Python wrapper of BornAgain/Core).
//! Performs a given standard simulation, both directly and from a Python dump.

class PyStandardTest : public IStandardTest
{
public:
    PyStandardTest(const std::string& name, const std::string& description,
                   const Simulation& simulation, double threshold);

    bool runTest() final;

private:
    std::unique_ptr<GISASSimulation> m_reference_simulation;
};

#endif // PYSTANDARDTEST_H
