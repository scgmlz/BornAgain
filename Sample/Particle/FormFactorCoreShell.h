//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/FormFactorCoreShell.h
//! @brief     Defines class FormFactorCoreShell.
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
#ifndef BORNAGAIN_SAMPLE_PARTICLE_FORMFACTORCORESHELL_H
#define BORNAGAIN_SAMPLE_PARTICLE_FORMFACTORCORESHELL_H

#include "Sample/Scattering/IFormFactor.h"

#include <memory>

//! Form Factor for a core shell particle.
//!
//! Used by ParticleCoreShell.

//! @ingroup formfactors_internal

class FormFactorCoreShell : public IFormFactor {
public:
    FormFactorCoreShell(IFormFactor* core, IFormFactor* shell);
    ~FormFactorCoreShell() override;

    FormFactorCoreShell* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double radialExtension() const override;

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override;

    void setAmbientMaterial(const Material& material) override;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

#ifndef SWIG
    //! Calculates and returns a polarized form factor calculation in DWBA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;
#endif

protected:
    std::unique_ptr<IFormFactor> m_core;
    std::unique_ptr<IFormFactor> m_shell;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_FORMFACTORCORESHELL_H
#endif // USER_API
