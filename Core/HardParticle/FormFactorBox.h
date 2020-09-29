// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorBox.h
//! @brief     Defines class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORBOX_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORBOX_H

#include "Core/HardParticle/IFormFactorPrism.h"

//! A rectangular prism (parallelepiped).
//! @ingroup hardParticle

class FormFactorBox : public IFormFactorPrism
{
public:
    FormFactorBox(const std::vector<double> P);
    FormFactorBox(double length, double width, double height);

    FormFactorBox* clone() const override final
    {
        return new FormFactorBox(m_length, m_width, m_height);
    }

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getWidth() const { return m_width; }

    double volume() const override final { return m_length * m_height * m_width; }
    double radialExtension() const override final { return m_length / 2.0; }
    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;
    double height() const final { return m_height; }

private:
    const double& m_length;
    const double& m_width;
    const double& m_height;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORBOX_H
