// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorFactor.h
//! @brief     Defines class FormFactorDecoratorFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORFACTOR_H
#define FORMFACTORDECORATORFACTOR_H

#include "IFormFactorDecorator.h"

//! Decorates a formfactor with a constant factor.
//!   Base class of FormFactorDecoratorMaterial.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorFactor(const IFormFactor& form_factor, const complex_t factor);
    FormFactorDecoratorFactor* clone() const override {
        return new FormFactorDecoratorFactor(*mp_form_factor, m_factor); }

    void accept(ISampleVisitor* visitor) const override { visitor->visit(this); }

    complex_t evaluate(const WavevectorPair& wavevectors) const override;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorPair& wavevectors) const override;
#endif

protected:
    complex_t m_factor;
};

#endif // FORMFACTORDECORATORFACTOR_H
