// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DSuperLattice.cpp
//! @brief     Implements class InterferenceFunction2DSuperLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Core/Aggregate/InterferenceFunctionNone.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/Integrator.h"
#include "Core/Tools/MathFunctions.h"

#include <limits>

InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(const Lattice2D& lattice,
                                                                       unsigned size_1,
                                                                       unsigned size_2)
    : IInterferenceFunction(0), m_integrate_xi(false), mP_substructure(nullptr), m_size_1(size_1),
      m_size_2(size_2)
{
    setName("Interference2DSuperLattice");
    setLattice(lattice);
    setSubstructureIFF(InterferenceFunctionNone());
}

//! Constructor of two-dimensional interference function.
//! @param length_1: length of first lattice vector in nanometers
//! @param length_2: length of second lattice vector  in nanometers
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis (beam direction) in radians
InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(
    double length_1, double length_2, double alpha, double xi, unsigned size_1, unsigned size_2)
    : InterferenceFunction2DSuperLattice(BasicLattice(length_1, length_2, alpha, xi), size_1,
                                         size_2)
{
}

InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice() = default;

InterferenceFunction2DSuperLattice* InterferenceFunction2DSuperLattice::clone() const
{
    auto* ret = new InterferenceFunction2DSuperLattice(*mP_lattice, m_size_1, m_size_2);
    ret->setPositionVariance(m_position_var);
    ret->setSubstructureIFF(*mP_substructure);
    ret->setIntegrationOverXi(integrationOverXi());
    return ret;
}

void InterferenceFunction2DSuperLattice::setSubstructureIFF(const IInterferenceFunction& sub_iff)
{
    mP_substructure.reset(sub_iff.clone());
    registerChild(mP_substructure.get());
}

const IInterferenceFunction& InterferenceFunction2DSuperLattice::substructureIFF() const
{
    return *mP_substructure;
}

//! Creates square lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DSuperLattice*
InterferenceFunction2DSuperLattice::createSquare(double lattice_length, double xi, unsigned size_1,
                                                 unsigned size_2)
{
    return new InterferenceFunction2DSuperLattice(SquareLattice(lattice_length, xi), size_1,
                                                  size_2);
}

//! Creates hexagonal lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DSuperLattice*
InterferenceFunction2DSuperLattice::createHexagonal(double lattice_length, double xi,
                                                    unsigned size_1, unsigned size_2)
{
    return new InterferenceFunction2DSuperLattice(HexagonalLattice(lattice_length, xi), size_1,
                                                  size_2);
}

double InterferenceFunction2DSuperLattice::evaluate(const kvector_t q, double outer_iff) const
{
    m_outer_iff = outer_iff;
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(mP_lattice->rotationAngle());
    return RealIntegrator().integrate([&](double xi) -> double { return interferenceForXi(xi); },
                                      0.0, M_TWOPI)
           / M_TWOPI;
}

void InterferenceFunction2DSuperLattice::setIntegrationOverXi(bool integrate_xi)
{
    m_integrate_xi = integrate_xi;
    mP_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunction2DSuperLattice::lattice() const
{
    if (!mP_lattice)
        throw std::runtime_error("InterferenceFunctionFinite2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *mP_lattice;
}

std::vector<const INode*> InterferenceFunction2DSuperLattice::getChildren() const
{
    return std::vector<const INode*>() << mP_lattice << mP_substructure;
}

double InterferenceFunction2DSuperLattice::iff_without_dw(const kvector_t q) const
{
    using MathFunctions::Laue;

    const double a = mP_lattice->length1();
    const double b = mP_lattice->length2();
    const double xialpha = m_xi + mP_lattice->latticeAngle();

    const double qadiv2 = (q.x() * a * std::cos(m_xi) + q.y() * a * std::sin(m_xi)) / 2.0;
    const double qbdiv2 = (q.x() * b * std::cos(xialpha) + q.y() * b * std::sin(xialpha)) / 2.0;
    const double ampl = Laue(qadiv2, m_size_1) * Laue(qbdiv2, m_size_2);
    return ampl * ampl / (m_size_1 * m_size_2);
}

void InterferenceFunction2DSuperLattice::setLattice(const Lattice2D& lattice)
{
    mP_lattice.reset(lattice.clone());
    registerChild(mP_lattice.get());
}

double InterferenceFunction2DSuperLattice::interferenceForXi(double xi) const
{
    m_xi = xi; // TODO ASAP don't set as collateratel effect; rm mutable
    const kvector_t q = kvector_t(m_qx, m_qy, 0.0);
    const double outer_iff = iff_no_inner(q, m_outer_iff);
    const double delta_xi = xi - mP_lattice->rotationAngle();
    return mP_substructure->evaluate(q.rotatedZ(-delta_xi), outer_iff);
}
