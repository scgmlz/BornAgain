// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProfileHelper.h
//! @brief     Defines class ProfileHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_PROFILEHELPER_H
#define BORNAGAIN_CORE_COMPUTATION_PROFILEHELPER_H

#include "Core/Basics/Complex.h"
#include "Core/Material/Material.h"
#include "Wrap/WinDllMacros.h"
#include <utility>
#include <vector>

class ProcessedSample;

//! Object that can generate the material profile of a sample as a function of depth.
//!
//! The generated profile contains the complex SLD for SLD materials and the parameters
//! delta and beta for refractive index materials
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ ProfileHelper
{
public:
    ProfileHelper(const ProcessedSample& sample);
    ~ProfileHelper();

    std::vector<complex_t> calculateProfile(const std::vector<double>& z_values) const;
    std::pair<double, double> defaultLimits() const;

private:
    std::vector<complex_t> m_materialdata;
    std::vector<double> m_zlimits;
    std::vector<double> m_sigmas;
};

#endif // BORNAGAIN_CORE_COMPUTATION_PROFILEHELPER_H
