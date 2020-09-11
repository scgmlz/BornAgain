// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2D.cpp
//! @brief     Implements classes of Lattice2D family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Lattice/Lattice2D.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include <cmath>

// ************************************************************************** //
// class Lattice2D
// ************************************************************************** //

Lattice2D::Lattice2D(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(meta, PValues)
{
}

Lattice2D::Lattice2D(double xi) : m_xi(xi)
{
    registerParameter("Xi", &m_xi).setUnit("rad");
}

Lattice2D::ReciprocalBases Lattice2D::reciprocalBases() const
{
    const double sinalpha = std::sin(latticeAngle());
    const double ainv = M_TWOPI / length1() / sinalpha;
    const double binv = M_TWOPI / length2() / sinalpha;
    const double xi = rotationAngle();
    const double xialpha = xi + latticeAngle();

    return {+ainv * std::sin(xialpha), -ainv * std::cos(xialpha), -binv * std::sin(xi),
            +binv * std::cos(xi)};
}

void Lattice2D::onChange()
{
    if (parent())
        parent()->onChange();
}

void Lattice2D::setRotationEnabled(bool enabled) // TODO ASAP replace by generic mechanism
{
    if (enabled) {
        if (parameter("Xi"))
            return;
        registerParameter("Xi", &m_xi).setUnit("rad");
    } else {
        removeParameter("Xi");
    }
}

// ************************************************************************** //
// class BasicLattice
// ************************************************************************** //

BasicLattice::BasicLattice(double length1, double length2, double angle, double xi)
    : Lattice2D(xi), m_length1(length1), m_length2(length2), m_angle(angle)
{
    if (m_length1 <= 0.0 || m_length2 <= 0.0)
        throw std::runtime_error("BasicLattice::BasicLattice() -> Error. Lattice length can't be "
                                 "negative or zero.");

    setName("BasicLattice");
    registerParameter("LatticeLength1", &m_length1).setUnit("nm").setPositive();
    registerParameter("LatticeLength2", &m_length2).setUnit("nm").setPositive();
    registerParameter("Alpha", &m_angle).setUnit("rad");
}

BasicLattice* BasicLattice::clone() const
{
    return new BasicLattice(m_length1, m_length2, m_angle, m_xi);
}

double BasicLattice::unitCellArea() const
{
    return std::abs(m_length1 * m_length2 * std::sin(m_angle));
}

// ************************************************************************** //
// class SquareLattice
// ************************************************************************** //

SquareLattice::SquareLattice(double length, double xi) : Lattice2D(xi), m_length(length)
{
    if (m_length <= 0.0)
        throw std::runtime_error("SquareLattice::SquareLattice() -> Error. Lattice length can't be "
                                 "negative or zero.");

    setName("SquareLattice");
    registerParameter("LatticeLength", &m_length).setUnit("nm").setPositive();
}

SquareLattice* SquareLattice::clone() const
{
    return new SquareLattice(m_length, m_xi);
}

double SquareLattice::latticeAngle() const
{
    return M_PI / 2.0;
}

double SquareLattice::unitCellArea() const
{
    return std::abs(m_length * m_length);
}

// ************************************************************************** //
// class HexagonalLattice
// ************************************************************************** //

HexagonalLattice::HexagonalLattice(double length, double xi) : Lattice2D(xi), m_length(length)
{
    if (m_length <= 0.0)
        throw std::runtime_error("HexagonalLattice::HexagonalLattice() -> Error. "
                                 "Lattice length can't be negative or zero.");

    setName("HexagonalLattice");
    registerParameter("LatticeLength", &m_length).setUnit("nm").setPositive();
}

HexagonalLattice* HexagonalLattice::clone() const
{
    return new HexagonalLattice(m_length, m_xi);
}

double HexagonalLattice::latticeAngle() const
{
    return M_TWOPI / 3.0;
}

double HexagonalLattice::unitCellArea() const
{
    static const double sinval = std::sin(latticeAngle());
    return std::abs(m_length * m_length * sinval);
}
