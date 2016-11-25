// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction1DLattice.cpp
//! @brief     Implements class InterferenceFunction1DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunction1DLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "FTDecayFunctions.h"
#include "ISampleVisitor.h"
#include "MathConstants.h"
#include "RealParameter.h"

//! @param length: Lattice length
//! @param xi: rotation of lattice with respect to x-axis
InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length, double xi)
    : InterferenceFunction1DLattice(Lattice1DParameters(length, xi))
{
}

InterferenceFunction1DLattice::InterferenceFunction1DLattice(
    const Lattice1DParameters& lattice_params)
    : m_lattice_params(lattice_params), mp_pdf(nullptr), m_na(0)
{
    setName(BornAgain::InterferenceFunction1DLatticeType);
    init_parameters();
}

InterferenceFunction1DLattice::~InterferenceFunction1DLattice() { delete mp_pdf; }

InterferenceFunction1DLattice* InterferenceFunction1DLattice::clone() const
{
    InterferenceFunction1DLattice* result = new InterferenceFunction1DLattice(m_lattice_params);
    if (mp_pdf)
        result->setDecayFunction(*mp_pdf);
    return result;
}

void InterferenceFunction1DLattice::setDecayFunction(const IFTDecayFunction1D& pdf)
{
    if (mp_pdf != &pdf) {
        delete mp_pdf;
        mp_pdf = pdf.clone();
    }
    double omega = mp_pdf->getOmega();
    double qa_max = (m_lattice_params.m_length / M_TWOPI) * nmax / omega;
    m_na = (int)(std::abs(qa_max) + 0.5);
}

double InterferenceFunction1DLattice::evaluate(const kvector_t q) const
{
    if (!mp_pdf)
        throw Exceptions::NullPointerException(
            "InterferenceFunction1DLattice::evaluate"
            " -> Error! No probability distribution function defined.");
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
    int qa_int = (int)(qx_prime / a_rec);
    qx_frac = qx_prime - qa_int * a_rec;

    for (int i = -m_na - 1; i < m_na + 2; ++i) {
        double qx = qx_frac + i * a_rec;
        result += mp_pdf->evaluate(qx);
    }
    return result / a;
}

void InterferenceFunction1DLattice::init_parameters()
{
    registerParameter(BornAgain::Length, &m_lattice_params.m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Xi, &m_lattice_params.m_xi).setUnit("rad");
}
