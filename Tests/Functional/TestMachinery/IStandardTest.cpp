// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IStandardTest.cpp
//! @brief     Defines pure virtual base class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IStandardTest.h"
#include "GISASSimulation.h"

IStandardTest::IStandardTest(const std::string& name, const std::string& description,
                             const Simulation& simulation, double threshold)
    : IFunctionalTest(name, description)
    , m_reference_simulation(simulation.clone())
    , m_threshold(threshold)
{}

IStandardTest::~IStandardTest() = default;

