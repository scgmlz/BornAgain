// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/PyFittingCallbacks.cpp
//! @brief     Implements family of PyFittingCallbacks classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Fitting/PyFittingCallbacks.h"

// --- PyBuilderCallback ---

PyBuilderCallback::PyBuilderCallback() = default;

PyBuilderCallback::~PyBuilderCallback() = default;

Simulation* PyBuilderCallback::build_simulation(Fit::Parameters)
{
    throw std::runtime_error("PyBuilderCallback::build_simulation() -> Error. Not implemented");
}

// --- PyObserverCallback ---

PyObserverCallback::PyObserverCallback() = default;

PyObserverCallback::~PyObserverCallback() = default;

void PyObserverCallback::update(const FitObjective&)
{
    throw std::runtime_error("PyObserverCallback::update() -> Error. Not implemented");
}
