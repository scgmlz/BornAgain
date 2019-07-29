// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/SelfConsistenceTest/SelfConsistenceTest.h
//! @brief     Defines class SelfConsistenceTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CORESELFCONSISTENCYTEST_H
#define CORESELFCONSISTENCYTEST_H

#include "IFunctionalTest.h"
#include <memory>
#include <vector>

class Simulation;

//! A functional test of BornAgain/Core.
//! Performs given simulations and compares their results with each other.

class SelfConsistenceTest : public IFunctionalTest
{
public:
    SelfConsistenceTest(const std::string& name, const std::string& description,
                        std::vector<std::unique_ptr<Simulation>> simulations, double threshold);
    ~SelfConsistenceTest() override;

    bool runTest() override;

private:
    std::vector<std::unique_ptr<Simulation>> m_simulations;
    double m_threshold;
};

#endif // CORESELFCONSISTENCYTEST_H
