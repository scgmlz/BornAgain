//  ************************************************************************************************
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
//  ************************************************************************************************

#ifndef BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADINGCOMPONENTS_H
#define BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADINGCOMPONENTS_H

#include <memory>

class ISimulation;

//! Collection of simulations for MultiThreadPerformanceTest.
namespace TestComponents {

std::unique_ptr<ISimulation> CreateSimpleGISAS();

std::unique_ptr<ISimulation> CreateRealisticGISAS();

std::unique_ptr<ISimulation> CreateRealisticAndHeavyGISAS();

std::unique_ptr<ISimulation> CreateGiganticGISAS();

std::unique_ptr<ISimulation> CreateWavelengthGISAS();

std::unique_ptr<ISimulation> CreateMCGISAS();

} // namespace TestComponents

#endif // BORNAGAIN_TESTS_PERFORMANCE_CORE_THREADINGCOMPONENTS_H
