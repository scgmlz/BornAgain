// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorMaterial.h
//! @brief     Defines class FormFactorDecoratorMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORMATERIAL_H
#define FORMFACTORDECORATORMATERIAL_H

#include "FormFactorDecoratorFactor.h"
#include <memory>

class IMaterial;

//! Decorates a scalar formfactor with the correct factor for the material's
//! refractive index and that of its surrounding material.
//! @ingroup formfactors_decorations

class BA_CORE_API_ FormFactorDecoratorMaterial : public FormFactorDecoratorFactor
{
public:
    FormFactorDecoratorMaterial(const IFormFactor& form_factor);

    ~FormFactorDecoratorMaterial() override final;

    FormFactorDecoratorMaterial* clone() const override final;

    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    //! Sets the material of the scatterer
    void setMaterial(const IMaterial& material);

    //! Sets the ambient material
    void setAmbientMaterial(const IMaterial& material) override;

    complex_t getAmbientRefractiveIndex() const;

#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    Eigen::Matrix2cd evaluatePol(const WavevectorPair& wavevectors) const override final;
#endif

private:
    complex_t getRefractiveIndexFactor() const;

    std::unique_ptr<IMaterial> mP_material;
    std::unique_ptr<IMaterial> mP_ambient_material;
};

#endif // FORMFACTORDECORATORMATERIAL_H
