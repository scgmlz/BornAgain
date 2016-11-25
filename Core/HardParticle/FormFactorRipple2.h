// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple2.h
//! @brief     Defines class FormFactorRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE2_H
#define FORMFACTORRIPPLE2_H

#include "IFormFactorBorn.h"

//! The formfactor for a triangular ripple.
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorRipple2 : public IFormFactorBorn
{
public:
    //! @brief Ripple2 constructor
    //! @param length of Ripple2
    //! @param width of triangular cross section
    //! @param height of triangular cross section
    //! @param asymmetry length of triangular cross section
    FormFactorRipple2(double length, double width, double height, double asymmetry);

    FormFactorRipple2* clone() const override final
    {
        return new FormFactorRipple2(m_length, m_width, m_height, m_d);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double getLength() const { return m_length; }
    double getAsymmetry() const { return m_d; }

    double getRadialExtension() const override final;

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    bool check_initialization() const;
    double m_length;
    double m_width;
    double m_height;
    double m_d;
    mutable cvector_t m_q;
};

#endif // FORMFACTORRIPPLE2_H
