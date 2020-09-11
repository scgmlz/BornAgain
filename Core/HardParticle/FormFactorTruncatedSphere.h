// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedSphere.h
//! @brief     Defines class FormFactorTruncatedSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTRUNCATEDSPHERE_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTRUNCATEDSPHERE_H

#include "Core/Scattering/IFormFactorBorn.h"

//! A truncated Sphere.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorTruncatedSphere : public IFormFactorBorn
{
public:
    FormFactorTruncatedSphere(const std::vector<double> P);
    FormFactorTruncatedSphere(double radius, double height, double dh);

    FormFactorTruncatedSphere* clone() const override final
    {
        return new FormFactorTruncatedSphere(m_radius, m_height, m_dh);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getRadius() const { return m_radius; }
    double getRemovedTop() const { return m_dh; }

    double radialExtension() const override final { return m_radius; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    bool check_initialization() const;
    complex_t Integrand(double Z) const;

    const double& m_radius;
    const double& m_height;
    const double& m_dh;
    mutable cvector_t m_q;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTRUNCATEDSPHERE_H
