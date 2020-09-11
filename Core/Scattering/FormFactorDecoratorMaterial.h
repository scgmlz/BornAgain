// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/FormFactorDecoratorMaterial.h
//! @brief     Defines class FormFactorDecoratorMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORMATERIAL_H
#define BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORMATERIAL_H

#include "Core/Material/Material.h"
#include "Core/Scattering/IFormFactorDecorator.h"
#include <memory>

//! Decorates a scalar formfactor with the correct factor for the material's
//! refractive index and that of its surrounding material.
//! @ingroup formfactors_decorations

class BA_CORE_API_ FormFactorDecoratorMaterial : public IFormFactorDecorator
{
public:
    FormFactorDecoratorMaterial(const IFormFactor& form_factor);

    ~FormFactorDecoratorMaterial() override final;

    FormFactorDecoratorMaterial* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    //! Sets the material of the scatterer
    void setMaterial(Material material);

    //! Sets the ambient material
    void setAmbientMaterial(Material material) override;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override;
#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

private:
    complex_t getRefractiveIndexFactor(const WavevectorInfo& wavevectors) const;

    Material m_material;
    Material m_ambient_material;
};

#endif // BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORMATERIAL_H
