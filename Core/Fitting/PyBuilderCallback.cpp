// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/PyBuilderCallback.cpp
//! @brief     Implements class PyBuilderCallback.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PyBuilderCallback.h"
#include <stdexcept>

PyBuilderCallback::PyBuilderCallback() = default;

PyBuilderCallback::~PyBuilderCallback() = default;

Simulation* PyBuilderCallback::build_simulation(Fit::Parameters)
{
    throw std::runtime_error("PyBuilderCallback::build_simulation() -> Error. Not implemented");
}
