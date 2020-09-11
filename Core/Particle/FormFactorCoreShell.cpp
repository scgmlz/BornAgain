// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorCoreShell.cpp
//! @brief     Implements class FormFactorCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Particle/FormFactorCoreShell.h"

FormFactorCoreShell::FormFactorCoreShell(IFormFactor* core, IFormFactor* shell)
    : mP_core(core), mP_shell(shell)
{
    setName("FormFactorCoreShell");
}

FormFactorCoreShell::~FormFactorCoreShell() {}

FormFactorCoreShell* FormFactorCoreShell::clone() const
{
    return new FormFactorCoreShell(mP_core->clone(), mP_shell->clone());
}

double FormFactorCoreShell::radialExtension() const
{
    return mP_shell->radialExtension();
}

double FormFactorCoreShell::bottomZ(const IRotation& rotation) const
{
    return mP_shell->bottomZ(rotation);
}

double FormFactorCoreShell::topZ(const IRotation& rotation) const
{
    return mP_shell->topZ(rotation);
}

void FormFactorCoreShell::setAmbientMaterial(Material material)
{
    mP_shell->setAmbientMaterial(std::move(material));
}

complex_t FormFactorCoreShell::evaluate(const WavevectorInfo& wavevectors) const
{
    return mP_shell->evaluate(wavevectors) + mP_core->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorCoreShell::evaluatePol(const WavevectorInfo& wavevectors) const
{
    return mP_shell->evaluatePol(wavevectors) + mP_core->evaluatePol(wavevectors);
}
