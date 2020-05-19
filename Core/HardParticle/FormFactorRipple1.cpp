// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple1.cpp
//! @brief     Implements classes FormFactorRipple1*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorRipple1.h"
#include "Ripples.h"

// ************************************************************************** //
// class FormFactorRipple1Box
// ************************************************************************** //

FormFactorRipple1Box::FormFactorRipple1Box(double length, double width, double height)
    : ProfileRipple1{length, width, height}
{
    setName(BornAgain::FFRipple1BoxType);
}

FormFactorRipple1Box* FormFactorRipple1Box::clone() const
{
    return new FormFactorRipple1Box(m_length, m_width, m_height);
}

void FormFactorRipple1Box::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorRipple1Box::factor_x(complex_t qx) const
{
    return ripples::factor_x_box(qx, m_length);
}

// ************************************************************************** //
// class FormFactorRipple1Gauss
// ************************************************************************** //

FormFactorRipple1Gauss::FormFactorRipple1Gauss(double length, double width, double height)
    : ProfileRipple1{length, width, height}
{
    setName(BornAgain::FFRipple1GaussType);
}

FormFactorRipple1Gauss* FormFactorRipple1Gauss::clone() const
{
    return new FormFactorRipple1Gauss(m_length, m_width, m_height);
}

void FormFactorRipple1Gauss::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorRipple1Gauss::factor_x(complex_t qx) const
{
    return ripples::factor_x_Gauss(qx, m_length);
}

// ************************************************************************** //
// class FormFactorRipple1Lorentz
// ************************************************************************** //

FormFactorRipple1Lorentz::FormFactorRipple1Lorentz(double length, double width, double height)
    : ProfileRipple1{length, width, height}
{
    setName(BornAgain::FFRipple1LorentzType);
}

FormFactorRipple1Lorentz* FormFactorRipple1Lorentz::clone() const
{
    return new FormFactorRipple1Lorentz(m_length, m_width, m_height);
}

void FormFactorRipple1Lorentz::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorRipple1Lorentz::factor_x(complex_t qx) const
{
    return ripples::factor_x_Lorentz(qx, m_length);
}
