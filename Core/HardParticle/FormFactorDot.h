// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDot.h
//! @brief     Defines class FormFactorDot.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORDOT_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORDOT_H

#include "Core/Scattering/IFormFactorBorn.h"

//! A dot, with scattering power as a sphere of radius rscat, but with F(q)=const.
//! @ingroup hardParticle

class FormFactorDot : public IFormFactorBorn
{
public:
    FormFactorDot(const std::vector<double> P);
    FormFactorDot(double radius);

    FormFactorDot* clone() const override final { return new FormFactorDot(m_radius); }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getRadius() const { return m_radius; }

    double radialExtension() const override final { return 0; }

    double bottomZ(const IRotation&) const override final { return 0; }
    double topZ(const IRotation&) const override final { return 0; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    bool canSliceAnalytically(const IRotation&) const override final { return false; }

private:
    const double& m_radius;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORDOT_H
