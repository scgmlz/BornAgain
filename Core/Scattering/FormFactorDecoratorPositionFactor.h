// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/FormFactorDecoratorPositionFactor.h
//! @brief     Defines class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORPOSITIONFACTOR_H
#define BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORPOSITIONFACTOR_H

#include "Core/Scattering/IFormFactorDecorator.h"
#include "Core/Vector/Vectors3D.h"

//! Decorates a form factor with a position dependent phase factor.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor& form_factor, const kvector_t& position);

    FormFactorDecoratorPositionFactor* clone() const override final
    {
        return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position);
    }

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double bottomZ(const IRotation& rotation) const override final;

    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

private:
    complex_t getPositionFactor(const WavevectorInfo& wavevectors) const;

    kvector_t m_position;
};

#endif // BORNAGAIN_CORE_SCATTERING_FORMFACTORDECORATORPOSITIONFACTOR_H
