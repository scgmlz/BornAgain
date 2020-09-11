// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCosineRipple.cpp
//! @brief     Implements classes FormFactorCosineRipple*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorCosineRipple.h"
#include "Core/HardParticle/Ripples.h"

// ************************************************************************** //
// class FormFactorCosineRippleBox
// ************************************************************************** //

FormFactorCosineRippleBox::FormFactorCosineRippleBox(const std::vector<double> P)
    : ICosineRipple({"CosineRippleBox", "class_tooltip", {}}, P)
{
}

FormFactorCosineRippleBox::FormFactorCosineRippleBox(double length, double width, double height)
    : FormFactorCosineRippleBox(std::vector<double>{length, width, height})
{
}

FormFactorCosineRippleBox* FormFactorCosineRippleBox::clone() const
{
    return new FormFactorCosineRippleBox(m_length, m_width, m_height);
}

void FormFactorCosineRippleBox::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorCosineRippleBox::factor_x(complex_t qx) const
{
    return ripples::factor_x_box(qx, m_length);
}

// ************************************************************************** //
// class FormFactorCosineRippleGauss
// ************************************************************************** //

FormFactorCosineRippleGauss::FormFactorCosineRippleGauss(const std::vector<double> P)
    : ICosineRipple({"CosineRippleGauss", "class_tooltip", {}}, P)
{
}

FormFactorCosineRippleGauss::FormFactorCosineRippleGauss(double length, double width, double height)
    : FormFactorCosineRippleGauss(std::vector<double>{length, width, height})
{
}

FormFactorCosineRippleGauss* FormFactorCosineRippleGauss::clone() const
{
    return new FormFactorCosineRippleGauss(m_length, m_width, m_height);
}

void FormFactorCosineRippleGauss::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorCosineRippleGauss::factor_x(complex_t qx) const
{
    return ripples::factor_x_Gauss(qx, m_length);
}

// ************************************************************************** //
// class FormFactorCosineRippleLorentz
// ************************************************************************** //

FormFactorCosineRippleLorentz::FormFactorCosineRippleLorentz(const std::vector<double> P)
    : ICosineRipple({"CosineRippleLorentz", "class_tooltip", {}}, P)
{
}

FormFactorCosineRippleLorentz::FormFactorCosineRippleLorentz(double length, double width,
                                                             double height)
    : FormFactorCosineRippleLorentz(std::vector<double>{length, width, height})
{
}

FormFactorCosineRippleLorentz* FormFactorCosineRippleLorentz::clone() const
{
    return new FormFactorCosineRippleLorentz(m_length, m_width, m_height);
}

void FormFactorCosineRippleLorentz::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorCosineRippleLorentz::factor_x(complex_t qx) const
{
    return ripples::factor_x_Lorentz(qx, m_length);
}
