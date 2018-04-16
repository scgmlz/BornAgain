// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionFinite2DLattice.cpp
//! @brief     Implements class InterferenceFunctionFinite2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunctionFinite2DLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "IntegratorReal.h"
#include "Macros.h"
#include "MathConstants.h"
#include "RealParameter.h"

#include <limits>

namespace {
double SinNx_Div_Sinx(double x, unsigned N);
double DebyeWallerFactor(double variance, double q2);
}


InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice(
        const Lattice2D& lattice, unsigned size_1, unsigned size_2)
    : m_sigma2(0.0)
    , m_integrate_xi(false)
    , m_size_1(size_1)
    , m_size_2(size_2)
{
    setName(BornAgain::InterferenceFunctionFinite2DLatticeType);
    setLattice(lattice);
    init_parameters();
}

//! Constructor of two-dimensional interference function.
//! @param length_1: length of first lattice vector in nanometers
//! @param length_2: length of second lattice vector  in nanometers
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis (beam direction) in radians
InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice(
        double length_1, double length_2, double alpha, double xi, unsigned size_1, unsigned size_2)
    : m_sigma2(0.0)
    , m_integrate_xi(false)
    , m_size_1(size_1)
    , m_size_2(size_2)
{
    setName(BornAgain::InterferenceFunctionFinite2DLatticeType);
    setLattice(BasicLattice(length_1, length_2, alpha, xi));
    init_parameters();
}

InterferenceFunctionFinite2DLattice::~InterferenceFunctionFinite2DLattice() =default;

InterferenceFunctionFinite2DLattice* InterferenceFunctionFinite2DLattice::clone() const
{
    return new InterferenceFunctionFinite2DLattice(*this);
}

//! Creates square lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunctionFinite2DLattice* InterferenceFunctionFinite2DLattice::createSquare(
    double lattice_length, double xi, unsigned size_1, unsigned size_2)
{
    return new InterferenceFunctionFinite2DLattice(SquareLattice(lattice_length, xi),
                                                   size_1, size_2);
}

//! Creates hexagonal lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunctionFinite2DLattice* InterferenceFunctionFinite2DLattice::createHexagonal(
    double lattice_length, double xi, unsigned size_1, unsigned size_2)
{
    return new InterferenceFunctionFinite2DLattice(HexagonalLattice(lattice_length, xi),
                                                   size_1, size_2);
}

double InterferenceFunctionFinite2DLattice::evaluate(const kvector_t q) const
{
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(m_lattice->rotationAngle());
    return mP_integrator->integrate(0.0, M_TWOPI) / M_TWOPI;
}

void InterferenceFunctionFinite2DLattice::setIntegrationOverXi(bool integrate_xi)
{
    m_integrate_xi = integrate_xi;
    m_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunctionFinite2DLattice::lattice() const
{
    if(!m_lattice)
        throw std::runtime_error("InterferenceFunctionFinite2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *m_lattice;
}

double InterferenceFunctionFinite2DLattice::getParticleDensity() const
{
    double area = m_lattice->unitCellArea();
    return area == 0.0 ? 0.0 : 1.0/area;
}

std::vector<const INode*> InterferenceFunctionFinite2DLattice::getChildren() const
{
    return std::vector<const INode*>() << m_lattice;
}

InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice(
        const InterferenceFunctionFinite2DLattice& other)
    : m_sigma2(other.m_sigma2)
    , m_size_1(other.m_size_1)
    , m_size_2(other.m_size_2)
{
    setName(other.getName());
    if(other.m_lattice)
        setLattice(*other.m_lattice);
    setIntegrationOverXi(other.integrationOverXi());
    init_parameters();
}

void InterferenceFunctionFinite2DLattice::setLattice(const Lattice2D& lattice)
{
    m_lattice.reset(lattice.clone());
    registerChild(m_lattice.get());
}

void InterferenceFunctionFinite2DLattice::init_parameters()
{
    registerParameter(BornAgain::PositionVariance, &m_sigma2).setNonnegative();
    mP_integrator
        = make_integrator_real(this, &InterferenceFunctionFinite2DLattice::interferenceForXi);
}

double InterferenceFunctionFinite2DLattice::interferenceForXi(double xi) const
{
    double a = m_lattice->length1();
    double b = m_lattice->length2();
    double xialpha = xi + m_lattice->latticeAngle();

    double qadiv2 = (m_qx*a*std::cos(xi) + m_qy*a*std::sin(xi)) / 2.0;
    double qbdiv2 = (m_qx*b*std::cos(xialpha) + m_qy*b*std::sin(xialpha)) / 2.0;
    double ampl = SinNx_Div_Sinx(qadiv2, m_size_1)*SinNx_Div_Sinx(qbdiv2, m_size_2);
    double lattice_factor = ampl*ampl / (m_size_1*m_size_2);
    double DW_factor = DebyeWallerFactor(m_sigma2, m_qx*m_qx + m_qy*m_qy);

    return 1.0 + DW_factor*(lattice_factor - 1.0);
}

namespace {
double SinNx_Div_Sinx(double x, unsigned N) {
    static const double SQRT6DOUBLE_EPS = std::sqrt(6.0*std::numeric_limits<double>::epsilon());
    auto nd = static_cast<double>(N);
    if(std::abs(nd*x) < SQRT6DOUBLE_EPS)
        return nd;
    double num = std::sin(nd*x);
    double den = std::sin(x);
    return num/den;
}
double DebyeWallerFactor(double variance, double q2) {
    return std::exp(-q2*variance/2.0);
}
}

