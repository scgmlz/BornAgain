//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunction2DSuperLattice.cpp
//! @brief     Implements class InterferenceFunction2DSuperLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Base/Math/Constants.h"
#include "Base/Math/Functions.h"
#include "Base/Math/IntegratorGK.h"
#include "Param/Base/RealParameter.h"
#include "Sample/Aggregate/InterferenceFunctionNone.h"

#include <limits>

InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(const Lattice2D& lattice,
                                                                       unsigned size_1,
                                                                       unsigned size_2)
    : IInterferenceFunction(0)
    , m_integrate_xi(false)
    , m_substructure(nullptr)
    , m_size_1(size_1)
    , m_size_2(size_2) {
    setName("Interference2DSuperLattice");
    m_lattice.reset(lattice.clone());
    registerChild(m_lattice.get());
    setSubstructureIFF(InterferenceFunctionNone());
}

//! Constructor of two-dimensional interference function.
//! @param length_1: length of first lattice vector in nanometers
//! @param length_2: length of second lattice vector  in nanometers
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis (beam direction) in radians
//! @param size_1: correlation length in direction 1
//! @param size_2: correlation length in direction 2
InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(
    double length_1, double length_2, double alpha, double xi, unsigned size_1, unsigned size_2)
    : InterferenceFunction2DSuperLattice(BasicLattice2D(length_1, length_2, alpha, xi), size_1,
                                         size_2) {}

InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice() = default;

InterferenceFunction2DSuperLattice* InterferenceFunction2DSuperLattice::clone() const {
    auto* ret = new InterferenceFunction2DSuperLattice(*m_lattice, m_size_1, m_size_2);
    ret->setPositionVariance(m_position_var);
    ret->setSubstructureIFF(*m_substructure);
    ret->setIntegrationOverXi(integrationOverXi());
    return ret;
}

void InterferenceFunction2DSuperLattice::setSubstructureIFF(const IInterferenceFunction& sub_iff) {
    m_substructure.reset(sub_iff.clone());
    registerChild(m_substructure.get());
}

const IInterferenceFunction& InterferenceFunction2DSuperLattice::substructureIFF() const {
    return *m_substructure;
}

double InterferenceFunction2DSuperLattice::evaluate(const kvector_t q, double outer_iff) const {
    m_outer_iff = outer_iff;
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(m_lattice->rotationAngle());
    return RealIntegrator().integrate([&](double xi) -> double { return interferenceForXi(xi); },
                                      0.0, M_TWOPI)
           / M_TWOPI;
}

void InterferenceFunction2DSuperLattice::setIntegrationOverXi(bool integrate_xi) {
    m_integrate_xi = integrate_xi;
    m_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunction2DSuperLattice::lattice() const {
    if (!m_lattice)
        throw std::runtime_error("InterferenceFunctionFinite2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *m_lattice;
}

std::vector<const INode*> InterferenceFunction2DSuperLattice::getChildren() const {
    return std::vector<const INode*>() << m_lattice << m_substructure;
}

double InterferenceFunction2DSuperLattice::iff_without_dw(const kvector_t q) const {
    using Math::Laue;

    const double a = m_lattice->length1();
    const double b = m_lattice->length2();
    const double xialpha = m_xi + m_lattice->latticeAngle();

    const double qadiv2 = (q.x() * a * std::cos(m_xi) + q.y() * a * std::sin(m_xi)) / 2.0;
    const double qbdiv2 = (q.x() * b * std::cos(xialpha) + q.y() * b * std::sin(xialpha)) / 2.0;
    const double ampl = Laue(qadiv2, m_size_1) * Laue(qbdiv2, m_size_2);
    return ampl * ampl / (m_size_1 * m_size_2);
}

double InterferenceFunction2DSuperLattice::interferenceForXi(double xi) const {
    m_xi = xi; // TODO ASAP don't set as collateratel effect; rm mutable
    const kvector_t q = kvector_t(m_qx, m_qy, 0.0);
    const double outer_iff = iff_no_inner(q, m_outer_iff);
    const double delta_xi = xi - m_lattice->rotationAngle();
    return m_substructure->evaluate(q.rotatedZ(-delta_xi), outer_iff);
}
