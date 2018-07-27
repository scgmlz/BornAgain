// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction1DLattice.cpp
//! @brief     Implements class InterferenceFunction1DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunction1DLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "FTDecayFunctions.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include <algorithm>

namespace {
// maximum value for qx*Lambdax
static const int nmax = 20;
// minimum number of neighboring reciprocal lattice points to use
static const int min_points = 4;
}

//! Constructor of interference function of one-dimensional lattice.
//! @param length: lattice constant in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length, double xi)
    : InterferenceFunction1DLattice(Lattice1DParameters(length, xi))
{}

InterferenceFunction1DLattice::InterferenceFunction1DLattice(
    const Lattice1DParameters& lattice_params)
    : m_lattice_params(lattice_params), m_na(0)
{
    setName(BornAgain::InterferenceFunction1DLatticeType);
    init_parameters();
}

InterferenceFunction1DLattice::~InterferenceFunction1DLattice() {}

InterferenceFunction1DLattice* InterferenceFunction1DLattice::clone() const
{
    InterferenceFunction1DLattice* result = new InterferenceFunction1DLattice(m_lattice_params);
    if (m_decay)
        result->setDecayFunction(*m_decay);
    return result;
}

//! Sets one-dimensional decay function.
//! @param decay: one-dimensional decay function in reciprocal space
void InterferenceFunction1DLattice::setDecayFunction(const IFTDecayFunction1D& decay)
{
    m_decay.reset(decay.clone());
    registerChild(m_decay.get());
    double decay_length = m_decay->decayLength();
    double qa_max = m_lattice_params.m_length * nmax / decay_length;
    m_na = static_cast<int>(std::lround(std::abs(qa_max) + 0.5));
    m_na = std::max(m_na, min_points);
}

double InterferenceFunction1DLattice::evaluate(const kvector_t q) const
{
    if (!m_decay)
        throw Exceptions::NullPointerException("InterferenceFunction1DLattice::evaluate"
                                               " -> Error! No decay function defined.");
    double result = 0.0;
    double qxr = q.x();
    double qyr = q.y();
    double qx_frac;
    double xi = m_lattice_params.m_xi;
    double a = m_lattice_params.m_length;
    double a_rec = M_TWOPI / a;

    // rotate the q vector to xi angle
    // so that qx_prime is along the a axis of lattice
    double qx_prime = qxr * std::cos(xi) + qyr * std::sin(xi);

    // calculate reciprocal vector fraction
    int qa_int = static_cast<int>(qx_prime / a_rec);
    qx_frac = qx_prime - qa_int * a_rec;

    for (int i = -m_na; i < m_na + 1; ++i) {
        double qx = qx_frac + i * a_rec;
        result += m_decay->evaluate(qx);
    }
    return result / a;
}

std::vector<const INode*> InterferenceFunction1DLattice::getChildren() const
{
    return std::vector<const INode*>() << m_decay;
}

void InterferenceFunction1DLattice::init_parameters()
{
    registerParameter(BornAgain::Length, &m_lattice_params.m_length)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::Xi, &m_lattice_params.m_xi).setUnit(BornAgain::UnitsRad);
}
