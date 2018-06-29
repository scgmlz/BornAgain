// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitTypes.h
//! @brief     Defines common types for fitting library.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITTYPES_H
#define FITTYPES_H

#include "WinDllMacros.h"
#include <functional>
#include <memory>

class Simulation;
namespace Fit { class Parameters; }

using simulation_builder_t = std::function<std::unique_ptr<Simulation>(const Fit::Parameters&)>;

#endif
