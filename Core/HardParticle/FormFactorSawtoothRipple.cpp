// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorSawtoothRipple.cpp
//! @brief     Implements classes FormFactorSawtoothRipple*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorSawtoothRipple.h"
#include "Core/HardParticle/Ripples.h"

// ************************************************************************** //
// class FormFactorSawtoothRippleBox
// ************************************************************************** //

FormFactorSawtoothRippleBox::FormFactorSawtoothRippleBox(const std::vector<double> P)
    : ISawtoothRipple({"SawtoothRippleBox", "class_tooltip", {}}, P)
{
}

FormFactorSawtoothRippleBox::FormFactorSawtoothRippleBox(double length, double width, double height,
                                                         double asymmetry)
    : FormFactorSawtoothRippleBox(std::vector<double>{length, width, height, asymmetry})
{
}

FormFactorSawtoothRippleBox* FormFactorSawtoothRippleBox::clone() const
{
    return new FormFactorSawtoothRippleBox(m_length, m_width, m_height, m_asymmetry);
}

void FormFactorSawtoothRippleBox::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorSawtoothRippleBox::factor_x(complex_t qx) const
{
    return ripples::factor_x_box(qx, m_length);
}

// ************************************************************************** //
// class FormFactorSawtoothRippleGauss
// ************************************************************************** //

FormFactorSawtoothRippleGauss::FormFactorSawtoothRippleGauss(const std::vector<double> P)
    : ISawtoothRipple({"SawtoothRippleGauss", "class_tooltip", {}}, P)
{
}

FormFactorSawtoothRippleGauss::FormFactorSawtoothRippleGauss(double length, double width,
                                                             double height, double asymmetry)
    : FormFactorSawtoothRippleGauss(std::vector<double>{length, width, height, asymmetry})
{
}

FormFactorSawtoothRippleGauss* FormFactorSawtoothRippleGauss::clone() const
{
    return new FormFactorSawtoothRippleGauss(m_length, m_width, m_height, m_asymmetry);
}

void FormFactorSawtoothRippleGauss::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorSawtoothRippleGauss::factor_x(complex_t qx) const
{
    return ripples::factor_x_Gauss(qx, m_length);
}

// ************************************************************************** //
// class FormFactorSawtoothRippleLorentz
// ************************************************************************** //

FormFactorSawtoothRippleLorentz::FormFactorSawtoothRippleLorentz(const std::vector<double> P)
    : ISawtoothRipple({"SawtoothRippleLorentz", "class_tooltip", {}}, P)
{
}

FormFactorSawtoothRippleLorentz::FormFactorSawtoothRippleLorentz(double length, double width,
                                                                 double height, double asymmetry)
    : FormFactorSawtoothRippleLorentz(std::vector<double>{length, width, height, asymmetry})
{
}

FormFactorSawtoothRippleLorentz* FormFactorSawtoothRippleLorentz::clone() const
{
    return new FormFactorSawtoothRippleLorentz(m_length, m_width, m_height, m_asymmetry);
}

void FormFactorSawtoothRippleLorentz::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorSawtoothRippleLorentz::factor_x(complex_t qx) const
{
    return ripples::factor_x_Lorentz(qx, m_length);
}
