// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCone.h
//! @brief     Defines class FormFactorCone
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCONE_H
#define FORMFACTORCONE_H

#include "IFormFactorBorn.h"
#include "IntegratorComplex.h"

// Forward declaration to prevent IntegratorComplex.h to be parsed for Python API:
template <class T> class IntegratorComplex;

//! A conical frustum (cone truncated parallel to the base) with circular base.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorCone : public IFormFactorBorn
{
public:
    FormFactorCone(double radius, double height, double alpha);

    FormFactorCone* clone() const override final
    {
        return new FormFactorCone(m_radius, m_height, m_alpha);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }
    double getRadius() const { return m_radius; }

    double getRadialExtension() const override final { return m_radius; }

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    double m_alpha;
    double m_cot_alpha;
    mutable cvector_t m_q;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorCone>> mP_integrator;
#endif
};

#endif // FORMFACTORCONE_H
