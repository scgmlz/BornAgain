// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreIO/CoreIOTest.h
//! @brief     Defines CoreIOTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef COREIOPATHTEST_H
#define COREIOPATHTEST_H

#include "IFunctionalTest.h"

//! Functional test to validate read/write to files containing non-ascii characters in a path.

class CoreIOPathTest : public IFunctionalTest
{
public:
    CoreIOPathTest();

    bool runTest();

};

#endif // COREIOPATHTEST_H
