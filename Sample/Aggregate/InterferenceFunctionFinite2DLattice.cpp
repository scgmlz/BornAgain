//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunctionFinite2DLattice.cpp
//! @brief     Implements class InterferenceFunctionFinite2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Aggregate/InterferenceFunctionFinite2DLattice.h"
#include "Base/Math/Constants.h"
#include "Base/Math/Functions.h"
#include "Base/Math/IntegratorGK.h"
#include "Param/Base/RealParameter.h"

#include <limits>

using Math::Laue;

//! Constructor of two-dimensional finite lattice interference function.
//! @param lattice: object specifying a 2d lattice structure
//! @param N_1: number of lattice cells in the first lattice direction
//! @param N_2: number of lattice cells in the second lattice direction
InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice(const Lattice2D& lattice,
                                                                         unsigned N_1, unsigned N_2)
    : IInterferenceFunction(0), m_integrate_xi(false), m_N_1(N_1), m_N_2(N_2) {
    setName("InterferenceFinite2DLattice");
    m_lattice.reset(lattice.clone());
    registerChild(m_lattice.get());
}

InterferenceFunctionFinite2DLattice::~InterferenceFunctionFinite2DLattice() = default;

InterferenceFunctionFinite2DLattice* InterferenceFunctionFinite2DLattice::clone() const {
    auto* ret = new InterferenceFunctionFinite2DLattice(*m_lattice, m_N_1, m_N_2);
    ret->setPositionVariance(m_position_var);
    ret->setIntegrationOverXi(integrationOverXi());
    return ret;
}

void InterferenceFunctionFinite2DLattice::setIntegrationOverXi(bool integrate_xi) {
    m_integrate_xi = integrate_xi;
    m_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunctionFinite2DLattice::lattice() const {
    if (!m_lattice)
        throw std::runtime_error("InterferenceFunctionFinite2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *m_lattice;
}

double InterferenceFunctionFinite2DLattice::getParticleDensity() const {
    double area = m_lattice->unitCellArea();
    return area == 0.0 ? 0.0 : 1.0 / area;
}

std::vector<const INode*> InterferenceFunctionFinite2DLattice::getChildren() const {
    return std::vector<const INode*>() << m_lattice;
}

double InterferenceFunctionFinite2DLattice::iff_without_dw(const kvector_t q) const {
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(m_lattice->rotationAngle());
    return RealIntegrator().integrate([&](double xi) -> double { return interferenceForXi(xi); },
                                      0.0, M_TWOPI)
           / M_TWOPI;
}

double InterferenceFunctionFinite2DLattice::interferenceForXi(double xi) const {
    double a = m_lattice->length1();
    double b = m_lattice->length2();
    double xialpha = xi + m_lattice->latticeAngle();

    double qadiv2 = (m_qx * a * std::cos(xi) + m_qy * a * std::sin(xi)) / 2.0;
    double qbdiv2 = (m_qx * b * std::cos(xialpha) + m_qy * b * std::sin(xialpha)) / 2.0;
    double ampl = Laue(qadiv2, m_N_1) * Laue(qbdiv2, m_N_2);
    double lattice_factor = ampl * ampl / (m_N_1 * m_N_2);

    return lattice_factor;
}
