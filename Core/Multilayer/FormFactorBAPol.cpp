// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorBAPol.cpp
//! @brief     Defines class FormFactorBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/FormFactorBAPol.h"
#include "Core/Vector/WavevectorInfo.h"
#include <stdexcept>

FormFactorBAPol::FormFactorBAPol(const IFormFactor& form_factor)
    : mP_form_factor(form_factor.clone())
{
    setName("FormFactorBAPol");
}

FormFactorBAPol::~FormFactorBAPol() = default;

FormFactorBAPol* FormFactorBAPol::clone() const
{
    return new FormFactorBAPol(*mP_form_factor);
}

complex_t FormFactorBAPol::evaluate(const WavevectorInfo&) const
{
    throw std::runtime_error("FormFactorBAPol::evaluate: "
                             "should never be called for matrix interactions");
}

Eigen::Matrix2cd FormFactorBAPol::evaluatePol(const WavevectorInfo& wavevectors) const
{
    Eigen::Matrix2cd ff_BA = mP_form_factor->evaluatePol(wavevectors);
    Eigen::Matrix2cd result;
    result(0, 0) = -ff_BA(1, 0);
    result(0, 1) = ff_BA(0, 0);
    result(1, 0) = -ff_BA(1, 1);
    result(1, 1) = ff_BA(0, 1);
    return result;
}

double FormFactorBAPol::bottomZ(const IRotation& rotation) const
{
    return mP_form_factor->bottomZ(rotation);
}

double FormFactorBAPol::topZ(const IRotation& rotation) const
{
    return mP_form_factor->topZ(rotation);
}
