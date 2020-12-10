//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/Lattice2D.cpp
//! @brief     Implements classes of Lattice2D family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Lattice/Lattice2D.h"
#include "Base/Math/Constants.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include <cmath>

//  ************************************************************************************************
//  class Lattice2D
//  ************************************************************************************************

Lattice2D::Lattice2D(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(meta, PValues) {}

Lattice2D::Lattice2D(double xi) : m_xi(xi) {
    registerParameter("Xi", &m_xi).setUnit("rad");
}

Lattice2D::ReciprocalBases Lattice2D::reciprocalBases() const {
    const double sinalpha = std::sin(latticeAngle());
    const double ainv = M_TWOPI / length1() / sinalpha;
    const double binv = M_TWOPI / length2() / sinalpha;
    const double xi = rotationAngle();
    const double xialpha = xi + latticeAngle();

    return {+ainv * std::sin(xialpha), -ainv * std::cos(xialpha), -binv * std::sin(xi),
            +binv * std::cos(xi)};
}

void Lattice2D::onChange() {
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

//  ************************************************************************************************
//  class BasicLattice2D
//  ************************************************************************************************

BasicLattice2D::BasicLattice2D(double length1, double length2, double angle, double xi)
    : Lattice2D(xi), m_length1(length1), m_length2(length2), m_angle(angle) {
    if (m_length1 <= 0.0 || m_length2 <= 0.0)
        throw std::runtime_error(
            "BasicLattice2D::BasicLattice2D() -> Error. Lattice length can't be "
            "negative or zero.");

    setName("BasicLattice2D");
    registerParameter("LatticeLength1", &m_length1).setUnit("nm").setPositive();
    registerParameter("LatticeLength2", &m_length2).setUnit("nm").setPositive();
    registerParameter("Alpha", &m_angle).setUnit("rad");
}

BasicLattice2D* BasicLattice2D::clone() const {
    return new BasicLattice2D(m_length1, m_length2, m_angle, m_xi);
}

double BasicLattice2D::unitCellArea() const {
    return std::abs(m_length1 * m_length2 * std::sin(m_angle));
}

//  ************************************************************************************************
//  class SquareLattice2D
//  ************************************************************************************************

SquareLattice2D::SquareLattice2D(double length, double xi) : Lattice2D(xi), m_length(length) {
    if (m_length <= 0.0)
        throw std::runtime_error(
            "SquareLattice2D::SquareLattice2D() -> Error. Lattice length can't be "
            "negative or zero.");

    setName("SquareLattice2D");
    registerParameter("LatticeLength", &m_length).setUnit("nm").setPositive();
}

SquareLattice2D* SquareLattice2D::clone() const {
    return new SquareLattice2D(m_length, m_xi);
}

double SquareLattice2D::latticeAngle() const {
    return M_PI / 2.0;
}

double SquareLattice2D::unitCellArea() const {
    return std::abs(m_length * m_length);
}

//  ************************************************************************************************
//  class HexagonalLattice2D
//  ************************************************************************************************

HexagonalLattice2D::HexagonalLattice2D(double length, double xi) : Lattice2D(xi), m_length(length) {
    if (m_length <= 0.0)
        throw std::runtime_error("HexagonalLattice2D::HexagonalLattice2D() -> Error. "
                                 "Lattice length can't be negative or zero.");

    setName("HexagonalLattice2D");
    registerParameter("LatticeLength", &m_length).setUnit("nm").setPositive();
}

HexagonalLattice2D* HexagonalLattice2D::clone() const {
    return new HexagonalLattice2D(m_length, m_xi);
}

double HexagonalLattice2D::latticeAngle() const {
    return M_TWOPI / 3.0;
}

double HexagonalLattice2D::unitCellArea() const {
    static const double sinval = std::sin(latticeAngle());
    return std::abs(m_length * m_length * sinval);
}
