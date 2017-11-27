// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2D.cpp
//! @brief     Implements classes of Lattice2D family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Lattice2D.h"
#include "BornAgainNamespace.h"
#include "RealParameter.h"
#include "MathConstants.h"
#include "ParameterPool.h"
#include <cmath>

Lattice2D::Lattice2D(double rotation_angle)
    : m_xi(rotation_angle)
{}

Lattice2D::ReciprocalBases Lattice2D::reciprocalBases() const
{
    double sinalpha = std::sin(latticeAngle());
    double ainv = M_TWOPI / length1() / sinalpha;
    double binv = M_TWOPI / length2() / sinalpha;
    double xi = rotationAngle();
    double xialpha = xi + latticeAngle();

    return {+ainv * std::sin(xialpha),
            -ainv * std::cos(xialpha),
            -binv * std::sin(xi),
            +binv * std::cos(xi)};
}

void Lattice2D::onChange()
{
    if(parent())
        parent()->onChange();
}

Lattice2D::Lattice2D(const Lattice2D& other)
{
    m_xi = other.m_xi;
    setName(other.getName());
}

void Lattice2D::setRotationEnabled(bool enabled)
{
    if(enabled) {
        if(parameter(BornAgain::Xi))
            return;

        registerParameter(BornAgain::Xi, &m_xi).setUnit(BornAgain::UnitsRad);

    } else {
        removeParameter(BornAgain::Xi);
    }
}

// --------------------------------------------------------------------------------------------- //

BasicLattice::BasicLattice(double length1, double length2, double angle, double rotation_angle)
    : Lattice2D(rotation_angle)
    , m_length1(length1)
    , m_length2(length2)
    , m_angle(angle)
{
    if(m_length1 <= 0.0 || m_length2 <= 0.0)
        throw std::runtime_error("BasicLattice::BasicLattice() -> Error. Lattice length can't be "
                                 "negative or zero.");

    setName(BornAgain::BasicLatticeType);
    init_parameters();
}

BasicLattice* BasicLattice::clone() const
{
    return new BasicLattice(*this);
}

double BasicLattice::unitCellArea() const
{
    return std::abs(m_length1*m_length2*std::sin(m_angle));
}

BasicLattice::BasicLattice(const BasicLattice& other)
    : Lattice2D(other)
    , m_length1(other.m_length1)
    , m_length2(other.m_length2)
    , m_angle(other.m_angle)
{
    init_parameters();
}

void BasicLattice::init_parameters()
{
    registerParameter(BornAgain::LatticeLength1, &m_length1).setUnit(BornAgain::UnitsNm)
        .setPositive();
    registerParameter(BornAgain::LatticeLength2, &m_length2).setUnit(BornAgain::UnitsNm)
        .setPositive();
    registerParameter(BornAgain::LatticeAngle, &m_angle).setUnit(BornAgain::UnitsRad);
    registerParameter(BornAgain::Xi, &m_xi).setUnit(BornAgain::UnitsRad);
}

// --------------------------------------------------------------------------------------------- //

SquareLattice::SquareLattice(double length, double rotation_angle)
    : Lattice2D(rotation_angle)
    , m_length(length)
{
    if(m_length <= 0.0)
        throw std::runtime_error("SquareLattice::SquareLattice() -> Error. Lattice length can't be "
                                 "negative or zero.");

    setName(BornAgain::SquareLatticeType);
    init_parameters();
}

SquareLattice* SquareLattice::clone() const
{
    return new SquareLattice(*this);
}

double SquareLattice::latticeAngle() const
{
    return M_PI/2.0;
}

double SquareLattice::unitCellArea() const
{
    return std::abs(m_length*m_length);
}

SquareLattice::SquareLattice(const SquareLattice& other)
    : Lattice2D(other)
    , m_length(other.m_length)
{
    init_parameters();
}

void SquareLattice::init_parameters()
{
    registerParameter(BornAgain::LatticeLength, &m_length).setUnit(BornAgain::UnitsNm)
        .setPositive();
    registerParameter(BornAgain::Xi, &m_xi).setUnit(BornAgain::UnitsRad);
}

// --------------------------------------------------------------------------------------------- //

HexagonalLattice::HexagonalLattice(double length, double rotation_angle)
    : Lattice2D(rotation_angle)
    , m_length(length)
{
    if(m_length <= 0.0)
        throw std::runtime_error("HexagonalLattice::HexagonalLattice() -> Error. "
                                 "Lattice length can't be negative or zero.");

    setName(BornAgain::HexagonalLatticeType);
    init_parameters();
}

HexagonalLattice* HexagonalLattice::clone() const
{
    return new HexagonalLattice(*this);
}

double HexagonalLattice::latticeAngle() const
{
    return M_TWOPI/3.0;
}

double HexagonalLattice::unitCellArea() const
{
    static const double sinval = std::sin(latticeAngle());
    return std::abs(m_length*m_length*sinval);
}

HexagonalLattice::HexagonalLattice(const HexagonalLattice& other)
    : Lattice2D(other)
    , m_length(other.m_length)
{
    init_parameters();
}

void HexagonalLattice::init_parameters()
{
    registerParameter(BornAgain::LatticeLength, &m_length).setUnit(BornAgain::UnitsNm)
        .setPositive();
    registerParameter(BornAgain::Xi, &m_xi).setUnit(BornAgain::UnitsRad);
}
