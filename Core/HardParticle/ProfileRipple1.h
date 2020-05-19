// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/ProfileRipple1.h
//! @brief     Defines class ProfileRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PROFILERIPPLE1_H
#define PROFILERIPPLE1_H

#include "IFormFactorBorn.h"
#include "IntegratorComplex.h"

//! Base class for form factors with a cosine ripple profile in the yz plane.

class BA_CORE_API_ ProfileRipple1 : public IFormFactorBorn
{
public:
    ProfileRipple1(double length, double width, double height);

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }

    double radialExtension() const override final;

    complex_t evaluate_for_q(cvector_t q) const override final
    {
        return factor_x(q.x()) * factor_yz(q.y(), q.z());
    }

protected:
    void onChange() override final;
    virtual complex_t factor_x(complex_t qx) const = 0;

    double m_length;
    double m_width;
    double m_height;

private:
    complex_t factor_yz(complex_t qy, complex_t qz) const;
    complex_t Integrand(double u) const;
    bool check_initialization() const;

    mutable complex_t m_ay;
    mutable complex_t m_az;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<ProfileRipple1>> mP_integrator;
#endif
};

#endif // PROFILERIPPLE1_H
