//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunctionFinite3DLattice.cpp
//! @brief     Implements class InterferenceFunctionFinite2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Aggregate/InterferenceFunctionFinite3DLattice.h"
#include "Base/Math/Constants.h"
#include "Base/Math/Functions.h"
#include "Param/Base/RealParameter.h"

#include <limits>

InterferenceFunctionFinite3DLattice::InterferenceFunctionFinite3DLattice(const Lattice3D& lattice,
                                                                         unsigned N_1, unsigned N_2,
                                                                         unsigned N_3)
    : IInterferenceFunction(0), m_N_1(N_1), m_N_2(N_2), m_N_3(N_3) {
    setName("InterferenceFinite3DLattice");
    setLattice(lattice);
}

InterferenceFunctionFinite3DLattice::~InterferenceFunctionFinite3DLattice() = default;

InterferenceFunctionFinite3DLattice* InterferenceFunctionFinite3DLattice::clone() const {
    auto* ret = new InterferenceFunctionFinite3DLattice(*m_lattice, m_N_1, m_N_2, m_N_3);
    ret->setPositionVariance(m_position_var);
    return ret;
}

const Lattice3D& InterferenceFunctionFinite3DLattice::lattice() const {
    if (!m_lattice)
        throw std::runtime_error("InterferenceFunctionFinite3DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *m_lattice;
}

std::vector<const INode*> InterferenceFunctionFinite3DLattice::getChildren() const {
    return std::vector<const INode*>() << m_lattice;
}

double InterferenceFunctionFinite3DLattice::iff_without_dw(const kvector_t q) const {
    using Math::Laue;
    const double qadiv2 = q.dot(m_lattice->getBasisVectorA()) / 2.0;
    const double qbdiv2 = q.dot(m_lattice->getBasisVectorB()) / 2.0;
    const double qcdiv2 = q.dot(m_lattice->getBasisVectorC()) / 2.0;
    const double ampl = Laue(qadiv2, m_N_1) * Laue(qbdiv2, m_N_2) * Laue(qcdiv2, m_N_3);
    return ampl * ampl / (m_N_1 * m_N_2 * m_N_3);
}

void InterferenceFunctionFinite3DLattice::setLattice(const Lattice3D& lattice) {
    m_lattice = std::make_unique<Lattice3D>(lattice);
    registerChild(m_lattice.get());
}
