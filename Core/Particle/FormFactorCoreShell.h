// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorCoreShell.h
//! @brief     Defines class FormFactorCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_FORMFACTORCORESHELL_H
#define BORNAGAIN_CORE_PARTICLE_FORMFACTORCORESHELL_H

#include "Core/Scattering/IFormFactor.h"

#include <memory>

//! Form Factor for a core shell particle.
//!
//! Used by ParticleCoreShell.

//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorCoreShell : public IFormFactor
{
public:
    FormFactorCoreShell(IFormFactor* core, IFormFactor* shell);
    ~FormFactorCoreShell() override final;

    FormFactorCoreShell* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final;

    double bottomZ(const IRotation& rotation) const override final;

    double topZ(const IRotation& rotation) const override final;

    void setAmbientMaterial(Material material) override final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;

#ifndef SWIG
    //! Calculates and returns a polarized form factor calculation in DWBA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

protected:
    std::unique_ptr<IFormFactor> mP_core;
    std::unique_ptr<IFormFactor> mP_shell;
};

#endif // BORNAGAIN_CORE_PARTICLE_FORMFACTORCORESHELL_H
