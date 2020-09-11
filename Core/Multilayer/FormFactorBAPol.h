// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorBAPol.h
//! @brief     Defines class FormFactorBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_FORMFACTORBAPOL_H
#define BORNAGAIN_CORE_MULTILAYER_FORMFACTORBAPOL_H

#include "Core/Scattering/IFormFactor.h"
#include <memory>

//! Evaluates the matrix BA term in a polarized IFormFactor.

//! @ingroup formfactors_internal

class FormFactorBAPol final : public IFormFactor
{
public:
    FormFactorBAPol(const IFormFactor& form_factor);
    ~FormFactorBAPol() override;

    FormFactorBAPol* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setAmbientMaterial(Material material) override
    {
        mP_form_factor->setAmbientMaterial(std::move(material));
    }

    //! Throws not-implemented exception
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    //! Calculates and returns a polarized form factor calculation in BA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;

    double volume() const override { return mP_form_factor->volume(); }

    double radialExtension() const override { return mP_form_factor->radialExtension(); }

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override;

private:
    //! The form factor for BA
    std::unique_ptr<IFormFactor> mP_form_factor;
};

#endif // BORNAGAIN_CORE_MULTILAYER_FORMFACTORBAPOL_H
