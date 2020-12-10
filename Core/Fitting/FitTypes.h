//  ************************************************************************************************
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
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_FITTING_FITTYPES_H
#define BORNAGAIN_CORE_FITTING_FITTYPES_H

#include <functional>
#include <memory>

class ISimulation;
namespace mumufit {
class Parameters;
}
class FitObjective;

using simulation_builder_t =
    std::function<std::unique_ptr<ISimulation>(const mumufit::Parameters&)>;

using fit_observer_t = std::function<void(const FitObjective&)>;

#endif // BORNAGAIN_CORE_FITTING_FITTYPES_H
#endif // USER_API
