// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/SelfConsistenceTest/SelfConsistenceTestService.h
//! @brief     Defines class SelfConsistenceTestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SELFCONSISTENCETESTSERVICE_H
#define SELFCONSISTENCETESTSERVICE_H

//! @class SelfConsistenceTestService
//! @brief Contains static method to run self-consistence functional test from standalone
//! executable.

class SelfConsistenceTestService
{
public:
    static bool execute(int argc, char** argv);
};

#endif // SELFCONSISTENCETESTSERVICE_H
