// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorPositionFactor.h
//! @brief     Defines class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORPOSITIONFACTOR_H
#define FORMFACTORDECORATORPOSITIONFACTOR_H

#include "IFormFactorDecorator.h"
#include "Vectors3D.h"

//! Decorates a formfactor with a position dependent phase factor.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor& form_factor, const kvector_t& position);

    FormFactorDecoratorPositionFactor* clone() const override final {
        return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position); }

    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    complex_t evaluate(const WavevectorPair& wavevectors) const override final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorPair& wavevectors) const override final;
#endif

private:
    complex_t getPositionFactor(const WavevectorPair& wavevectors) const;

    kvector_t m_position;
};

#endif // FORMFACTORDECORATORPOSITIONFACTOR_H
