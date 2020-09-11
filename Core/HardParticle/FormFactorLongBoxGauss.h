// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongBoxGauss.h
//! @brief     Defines class FormFactorLongBoxGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORLONGBOXGAUSS_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORLONGBOXGAUSS_H

#include "Core/Scattering/IFormFactorBorn.h"

//! The form factor for a long rectangular box.
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorLongBoxGauss : public IFormFactorBorn
{
public:
    //! @brief Box constructor
    //! @param length of Box's base
    //! @param width of Box's base
    //! @param height of Box
    FormFactorLongBoxGauss(const std::vector<double> P);
    FormFactorLongBoxGauss(double length, double width, double height);

    FormFactorLongBoxGauss* clone() const override final
    {
        return new FormFactorLongBoxGauss(m_length, m_width, m_height);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double radialExtension() const override final { return m_length / 2.0; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    const double& m_length;
    const double& m_width;
    const double& m_height;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORLONGBOXGAUSS_H
