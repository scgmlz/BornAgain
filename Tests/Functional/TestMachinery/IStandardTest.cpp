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

#include "IStandardTest.h"

IStandardTest::IStandardTest(const std::string& name, const std::string& description,
                             double threshold)
    : IFunctionalTest(name, description)
    , m_threshold(threshold)
{

}

IStandardTest::~IStandardTest() = default;

