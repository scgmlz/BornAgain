// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongBoxGauss.h
//! @brief     Defines class FormFactorLongBoxGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLONGBOXGAUSS_H
#define FORMFACTORLONGBOXGAUSS_H

#include "IFormFactorBorn.h"

//! The formfactor for a long rectangular box.
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorLongBoxGauss : public IFormFactorBorn
{
public:
    //! @brief Box constructor
    //! @param length of Box's base
    //! @param width of Box's base
    //! @param height of Box
    FormFactorLongBoxGauss(double length, double width, double height);

    FormFactorLongBoxGauss* clone() const override final
    {
        return new FormFactorLongBoxGauss(m_length, m_width, m_height);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double getRadialExtension() const override final { return m_length / 2.0; }

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    double m_length;
    double m_width;
    double m_height;
};

#endif // FORMFACTORLONGBOXGAUSS_H
