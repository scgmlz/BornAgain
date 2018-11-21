// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongBox.h
//! @brief     Defines class FormFactorLongBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORLONGBOX_H
#define FORMFACTORLONGBOX_H

#include "IFormFactorBorn.h"

//! The formfactor for a long rectangular box.
//! Approximates the rapidly oscillating sinc function by the square root of a Lorentzian
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorLongBox : public IFormFactorBorn
{
public:
    //! @brief Box constructor
    //! @param length of Box's base
    //! @param width of Box's base
    //! @param height of Box
    FormFactorLongBox( double length, double width, double height);

    FormFactorLongBox *clone() const override final {
        return new FormFactorLongBox(m_length, m_width, m_height); }
    void accept(INodeVisitor *visitor) const override final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double radialExtension() const override final{ return m_length/2.0; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    double m_length;
    double m_width;
    double m_height;
};

#endif // FORMFACTORLONGBOX_H
