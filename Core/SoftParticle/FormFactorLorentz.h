// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorLorentz.h
//! @brief     Defines class FormFactorLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLORENTZ_H
#define FORMFACTORLORENTZ_H

#include "IFormFactorBorn.h"

//! The formfactor of a lorentzian.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorLorentz : public IFormFactorBorn
{
public:
    FormFactorLorentz(double length);
    FormFactorLorentz(double width, double height);

    FormFactorLorentz* clone() const override final
    {
        return new FormFactorLorentz(m_width, m_height);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

    double getRadialExtension() const override final;

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    double m_width;
    double m_height;
    void initialize();
};

#endif // FORMFACTORLORENTZ_H
