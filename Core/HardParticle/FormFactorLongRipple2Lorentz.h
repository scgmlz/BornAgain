// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongRipple2Lorentz.h
//! @brief     Defines class FormFactorLongRipple2Lorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLONGRIPPLE2LORENTZ_H
#define FORMFACTORLONGRIPPLE2LORENTZ_H

#include "IFormFactorBorn.h"

//! The formfactor for a triangular ripple.
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorLongRipple2Lorentz : public IFormFactorBorn
{
public:
    FormFactorLongRipple2Lorentz(double length, double width, double height, double asymmetry);

    FormFactorLongRipple2Lorentz* clone() const override final
    {
        return new FormFactorLongRipple2Lorentz(m_length, m_width, m_height, m_d);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double getLength() const { return m_length; }
    double getAsymmetry() const { return m_d; }

    double getRadialExtension() const override final;

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    void check_parameters() const;

    double m_length;
    double m_width;
    double m_height;
    double m_d;
    mutable cvector_t m_q;
};

#endif // FORMFACTORLONGRIPPLE2LORENTZ_H
