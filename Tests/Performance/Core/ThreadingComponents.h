// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/Core/ThreadingComponents.h
//! @brief     Defines TestComponents namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADINGCOMPONENTS_H
#define BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADINGCOMPONENTS_H

#include <memory>

class Simulation;

//! Collection of simulations for MultiThreadPerformanceTest.
namespace TestComponents
{

std::unique_ptr<Simulation> CreateSimpleGISAS();

std::unique_ptr<Simulation> CreateRealisticGISAS();

std::unique_ptr<Simulation> CreateRealisticAndHeavyGISAS();

std::unique_ptr<Simulation> CreateGiganticGISAS();

std::unique_ptr<Simulation> CreateWavelengthGISAS();

std::unique_ptr<Simulation> CreateMCGISAS();

} // namespace TestComponents

#endif // BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADINGCOMPONENTS_H
