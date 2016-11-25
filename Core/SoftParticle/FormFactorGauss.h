// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorGauss.h
//! @brief     Defines class FormFactorGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORGAUSS_H
#define FORMFACTORGAUSS_H

#include "IFormFactorBorn.h"

//! The formfactor of a gaussian.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorGauss : public IFormFactorBorn
{
public:
    FormFactorGauss(double length);
    FormFactorGauss(double width, double height);

    FormFactorGauss* clone() const override final { return new FormFactorGauss(m_width, m_height); }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

    double getRadialExtension() const override final { return m_width; }

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    double m_width;
    double m_height;
    double m_max_ql;
    void initialize();
};

#endif // FORMFACTORGAUSS_H
