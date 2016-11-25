// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorDebyeWaller.h
//! @brief     Defines and implements class FormFactorDecoratorDebyeWaller.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORDEBYEWALLER_H
#define FORMFACTORDECORATORDEBYEWALLER_H

#include "IFormFactorDecorator.h"

//! Debye-Waller factors in radial and z directions.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorDebyeWaller : public IFormFactorDecorator
{
public:
    //! Anisotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(const IFormFactor& form_factor, double dw_h_factor,
                                   double dw_r_factor);

    //! Isotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(const IFormFactor& form_factor, double dw_factor);

    FormFactorDecoratorDebyeWaller* clone() const override final {
        return new FormFactorDecoratorDebyeWaller(*mp_form_factor, m_h_dw_factor, m_r_dw_factor); }

    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    complex_t evaluate(const WavevectorPair& wavevectors) const override final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorPair& wavevectors) const override final;
#endif

private:
    double m_h_dw_factor; //!< the Debye-Waller factor in the z-direction
    double m_r_dw_factor; //!< the Debye-Waller factor in the radial direction
    double getDWFactor(const WavevectorPair& wavevectors) const;
};

#endif // FORMFACTORDECORATORDEBYEWALLER_H
