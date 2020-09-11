// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/FormFactorDecoratorRotation.h
//! @brief     Defines class FormFactorDecoratorRotation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORROTATION_H
#define BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORROTATION_H

#include "Core/Scattering/IFormFactorDecorator.h"
#include "Core/Scattering/Rotations.h"
#include "Core/Vector/Transform3D.h"

//! Equips a form factor with a rotation.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorRotation : public IFormFactorDecorator
{
public:
    //! Constructor, setting form factor and rotation.
    FormFactorDecoratorRotation(const IFormFactor& form_factor, const IRotation& rotation);

    FormFactorDecoratorRotation* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double bottomZ(const IRotation& rotation) const override final;

    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

private:
    Transform3D m_transform;
    //! Private constructor for cloning.
    FormFactorDecoratorRotation(const IFormFactor& form_factor, const Transform3D& transform);
};

#endif // BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORROTATION_H
