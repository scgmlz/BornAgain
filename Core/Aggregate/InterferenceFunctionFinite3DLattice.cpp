// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionFinite3DLattice.cpp
//! @brief     Implements class InterferenceFunctionFinite2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunctionFinite3DLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "Macros.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"

#include <limits>

using MathFunctions::Laue;

//! Constructor of three-dimensional finite lattice interference function.
//! @param lattice: object specifying a 2d lattice structure
//! @param N_1: number of lattice cells in the first lattice direction
//! @param N_2: number of lattice cells in the second lattice direction
InterferenceFunctionFinite3DLattice::InterferenceFunctionFinite3DLattice(
        const Lattice& lattice, unsigned N_1, unsigned N_2, unsigned N_3)
    : m_N_1(N_1), m_N_2(N_2), m_N_3(N_3)
{
    setName(BornAgain::InterferenceFunctionFinite3DLatticeType);
    setLattice(lattice);
}

InterferenceFunctionFinite3DLattice::~InterferenceFunctionFinite3DLattice() = default;

InterferenceFunctionFinite3DLattice* InterferenceFunctionFinite3DLattice::clone() const
{
    return new InterferenceFunctionFinite3DLattice(*this);
}

const Lattice& InterferenceFunctionFinite3DLattice::lattice() const
{
    if (!mP_lattice)
        throw std::runtime_error("InterferenceFunctionFinite3DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *mP_lattice;
}

std::vector<const INode*> InterferenceFunctionFinite3DLattice::getChildren() const
{
    return std::vector<const INode*>() << mP_lattice;
}

double InterferenceFunctionFinite3DLattice::iff_without_dw(const kvector_t q) const
{
    double qadiv2 = q.dot(mP_lattice->getBasisVectorA()) / 2.0;
    double qbdiv2 = q.dot(mP_lattice->getBasisVectorB()) / 2.0;
    double qcdiv2 = q.dot(mP_lattice->getBasisVectorC()) / 2.0;
    double ampl = Laue(qadiv2, m_N_1) * Laue(qbdiv2, m_N_2) * Laue(qcdiv2, m_N_3);
    return ampl * ampl / (m_N_1 * m_N_2 * m_N_3);
}

InterferenceFunctionFinite3DLattice::InterferenceFunctionFinite3DLattice(
    const InterferenceFunctionFinite3DLattice& other)
    : IInterferenceFunction(other), m_N_1(other.m_N_1), m_N_2(other.m_N_2), m_N_3(other.m_N_3)
{
    setName(other.getName());
    if (other.mP_lattice)
        setLattice(*other.mP_lattice);
}

void InterferenceFunctionFinite3DLattice::setLattice(const Lattice& lattice)
{
    mP_lattice.reset(new Lattice(lattice));
    registerChild(mP_lattice.get());
}
