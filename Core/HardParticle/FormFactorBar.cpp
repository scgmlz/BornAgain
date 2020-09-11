// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorBar.cpp
//! @brief     Implements classes FormFactorBar*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorBar.h"
#include "Core/HardParticle/Ripples.h"

// ************************************************************************** //
// class FormFactorBarGauss
// ************************************************************************** //

FormFactorBarGauss::FormFactorBarGauss(const std::vector<double> P)
    : IProfileRectangularRipple({"BarGauss", "class_tooltip", {}}, P)
{
}

FormFactorBarGauss::FormFactorBarGauss(double length, double width, double height)
    : FormFactorBarGauss(std::vector<double>{length, width, height})
{
}

FormFactorBarGauss* FormFactorBarGauss::clone() const
{
    return new FormFactorBarGauss(m_length, m_width, m_height);
}

void FormFactorBarGauss::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorBarGauss::factor_x(complex_t qx) const
{
    return ripples::factor_x_Gauss(qx, m_length);
}

// ************************************************************************** //
// class FormFactorBarLorentz
// ************************************************************************** //

FormFactorBarLorentz::FormFactorBarLorentz(const std::vector<double> P)
    : IProfileRectangularRipple({"BarLorentz", "class_tooltip", {}}, P)
{
}

FormFactorBarLorentz::FormFactorBarLorentz(double length, double width, double height)
    : FormFactorBarLorentz(std::vector<double>{length, width, height})
{
}

FormFactorBarLorentz* FormFactorBarLorentz::clone() const
{
    return new FormFactorBarLorentz(m_length, m_width, m_height);
}

void FormFactorBarLorentz::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorBarLorentz::factor_x(complex_t qx) const
{
    return ripples::factor_x_Lorentz(qx, m_length);
}
