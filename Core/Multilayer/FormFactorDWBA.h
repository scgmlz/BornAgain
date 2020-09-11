// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorDWBA.h
//! @brief     Defines class FormFactorDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_FORMFACTORDWBA_H
#define BORNAGAIN_CORE_MULTILAYER_FORMFACTORDWBA_H

#include "Core/Scattering/IFormFactor.h"
#include <memory>

class ILayerRTCoefficients;

//! Evaluates the coherent sum of the four DWBA terms in a scalar IFormFactor.
//! @ingroup formfactors_internal

class FormFactorDWBA final : public IFormFactor
{
public:
    FormFactorDWBA(const IFormFactor& form_factor);
    ~FormFactorDWBA() override;

    FormFactorDWBA* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setAmbientMaterial(Material material) override
    {
        mP_form_factor->setAmbientMaterial(std::move(material));
    }

    //! Calculates and returns a form factor calculation in DWBA
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    double volume() const override { return mP_form_factor->volume(); }

    double radialExtension() const override { return mP_form_factor->radialExtension(); }

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override;

    void setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients> p_in_coeffs,
                         std::unique_ptr<const ILayerRTCoefficients> p_out_coeffs) override;

    friend class TestPolarizedDWBATerms;

private:
    //! The form factor for BA
    std::unique_ptr<IFormFactor> mP_form_factor;

    std::unique_ptr<const ILayerRTCoefficients> mp_in_coeffs;
    std::unique_ptr<const ILayerRTCoefficients> mp_out_coeffs;
};

#endif // BORNAGAIN_CORE_MULTILAYER_FORMFACTORDWBA_H
