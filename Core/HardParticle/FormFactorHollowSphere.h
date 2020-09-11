// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorHollowSphere.h
//! @brief     Defines class FormFactorHollowSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORHOLLOWSPHERE_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORHOLLOWSPHERE_H

#include "Core/HardParticle/FormFactorFullSphere.h"

//! Integrated full sphere form factor over a uniform distribution of radii.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorHollowSphere : public IFormFactorBorn
{
public:
    FormFactorHollowSphere(const std::vector<double> P);
    FormFactorHollowSphere(double mean, double full_width);

    FormFactorHollowSphere* clone() const override final
    {
        return new FormFactorHollowSphere(m_mean, m_full_width);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final { return m_mean; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    void onChange() override final;

private:
    bool checkParameters() const;
    const double& m_mean;       //!< This is the mean radius
    const double& m_full_width; //!< This is the full width of the radius distribution
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORHOLLOWSPHERE_H
