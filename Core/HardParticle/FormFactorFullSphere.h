// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSphere.h
//! @brief     Defines class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORFULLSPHERE_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORFULLSPHERE_H

#include "Core/Scattering/IFormFactorBorn.h"

//! A full sphere.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorFullSphere : public IFormFactorBorn
{
public:
    FormFactorFullSphere(const std::vector<double> P, bool position_at_center = false);
    FormFactorFullSphere(double radius, bool position_at_center = false);

    FormFactorFullSphere* clone() const override final
    {
        return new FormFactorFullSphere(m_radius, m_position_at_center);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getRadius() const { return m_radius; }

    double radialExtension() const override final { return m_radius; }

    double bottomZ(const IRotation& rotation) const override final;

    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    bool canSliceAnalytically(const IRotation&) const override final { return true; }

    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    const double& m_radius;
    bool m_position_at_center;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORFULLSPHERE_H
