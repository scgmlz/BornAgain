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

#include "Core/Aggregate/InterferenceFunction1DLattice.h"
#include "Core/Basics/Assert.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Correlations/FTDecay1D.h"
#include "Core/Correlations/FTDecay2D.h"
#include "Core/Parametrization/RealParameter.h"
#include <algorithm>

namespace
{
// maximum value for qx*Lambdax
static const int nmax = 20;
// minimum number of neighboring reciprocal lattice points to use
static const int min_points = 4;
} // namespace

//! Constructor of interference function of one-dimensional lattice.
//! @param length: lattice constant in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length, double xi)
    : IInterferenceFunction(0), m_length(length), m_xi(xi), m_na{0}
{
    setName("Interference1DLattice");
    registerParameter("Length", &m_length).setUnit("nm").setNonnegative();
    registerParameter("Xi", &m_xi).setUnit("rad");
}

InterferenceFunction1DLattice::~InterferenceFunction1DLattice() {}

InterferenceFunction1DLattice* InterferenceFunction1DLattice::clone() const
{
    auto* ret = new InterferenceFunction1DLattice(m_length, m_xi);
    ret->setPositionVariance(m_position_var);
    ret->m_na = m_na;
    if (mP_decay)
        ret->setDecayFunction(*mP_decay);
    return ret;
}

//! Sets one-dimensional decay function.
//! @param decay: one-dimensional decay function in reciprocal space
void InterferenceFunction1DLattice::setDecayFunction(const IFTDecayFunction1D& decay)
{
    mP_decay.reset(decay.clone());
    registerChild(mP_decay.get());
    double decay_length = mP_decay->decayLength();
    double qa_max = m_length * nmax / decay_length / M_TWOPI;
    m_na = static_cast<int>(std::lround(std::abs(qa_max) + 0.5));
    m_na = std::max(m_na, min_points);
}

std::vector<const INode*> InterferenceFunction1DLattice::getChildren() const
{
    return std::vector<const INode*>() << mP_decay;
}

double InterferenceFunction1DLattice::iff_without_dw(const kvector_t q) const
{
    ASSERT(mP_decay);
    double result = 0.0;
    double qxr = q.x();
    double qyr = q.y();
    double qx_frac;
    double xi = m_xi;
    double a = m_length;
    double a_rec = M_TWOPI / a;

    // rotate the q vector to xi angle
    // so that qx_prime is along the a axis of lattice
    double qx_prime = qxr * std::cos(xi) + qyr * std::sin(xi);

    // calculate reciprocal vector fraction
    int qa_int = static_cast<int>(qx_prime / a_rec);
    qx_frac = qx_prime - qa_int * a_rec;

    for (int i = -m_na; i < m_na + 1; ++i) {
        double qx = qx_frac + i * a_rec;
        result += mP_decay->evaluate(qx);
    }
    return result / a;
}
