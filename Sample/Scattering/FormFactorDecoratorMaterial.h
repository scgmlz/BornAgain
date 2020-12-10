//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/FormFactorDecoratorMaterial.h
//! @brief     Defines class FormFactorDecoratorMaterial.
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
#ifndef BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORMATERIAL_H
#define BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORMATERIAL_H

#include "Sample/Material/Material.h"
#include "Sample/Scattering/IFormFactorDecorator.h"
#include <memory>

//! Decorates a scalar formfactor with the correct factor for the material's
//! refractive index and that of its surrounding material.
//! @ingroup formfactors_decorations

class FormFactorDecoratorMaterial : public IFormFactorDecorator {
public:
    FormFactorDecoratorMaterial(const IFormFactor& ff);

    ~FormFactorDecoratorMaterial() override;

    FormFactorDecoratorMaterial* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Sets the material of the scatterer
    void setMaterial(const Material& material);

    //! Sets the ambient material
    void setAmbientMaterial(const Material& material) override;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override;
#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;
#endif

private:
    complex_t getRefractiveIndexFactor(const WavevectorInfo& wavevectors) const;

    Material m_material;
    Material m_ambient_material;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORMATERIAL_H
#endif // USER_API
