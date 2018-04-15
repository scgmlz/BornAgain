// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DParaCrystal.cpp
//! @brief     Implements class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunction2DParaCrystal.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "IntegratorReal.h"
#include "ParameterPool.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include <limits>

InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(const Lattice2D& lattice,
    double damping_length, double domain_size_1, double domain_size_2)
    : m_integrate_xi(false)
    , m_damping_length(damping_length)
{
    setName(BornAgain::InterferenceFunction2DParaCrystalType);
    setLattice(lattice);
    setDomainSizes(domain_size_1, domain_size_2);
    init_parameters();
}

//! Constructor of interference function of two-dimensional paracrystal.
//! @param length_1: length of first lattice vector in nanometers
//! @param length_2: length of second lattice vector in nanometers
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis (beam direction) in radians
//! @param damping_length: the damping (coherence) length of the paracrystal in nanometers

InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(double length_1,
    double length_2, double alpha, double xi, double damping_length)
    : m_integrate_xi(false)
    , m_damping_length(damping_length)
{
    setName(BornAgain::InterferenceFunction2DParaCrystalType);
    setLattice(BasicLattice(length_1, length_2, alpha, xi));
    setDomainSizes(0.0, 0.0);
    init_parameters();
}

InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal()
{
}

InterferenceFunction2DParaCrystal* InterferenceFunction2DParaCrystal::clone() const
{
    return new InterferenceFunction2DParaCrystal(*this);
}

//! Sets the probability distributions (Fourier transformed) for the two lattice directions.
//! @param pdf_1: probability distribution in first lattice direction
//! @param pdf_2: probability distribution in second lattice direction

void InterferenceFunction2DParaCrystal::setProbabilityDistributions(const IFTDistribution2D& pdf_1,
                                                                    const IFTDistribution2D& pdf_2)
{
    m_pdf1.reset(pdf_1.clone());
    registerChild(m_pdf1.get());
    m_pdf2.reset(pdf_2.clone());
    registerChild(m_pdf2.get());
}

//! Sets the damping length.
//! @param damping_length: the damping (coherence) length of the paracrystal in nanometers

void InterferenceFunction2DParaCrystal::setDampingLength(double damping_length)
{
    m_damping_length = damping_length;
}

double InterferenceFunction2DParaCrystal::evaluate(const kvector_t q) const
{
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(m_lattice->rotationAngle());
    return mP_integrator->integrate(0.0, M_TWOPI) / M_TWOPI;
}

double InterferenceFunction2DParaCrystal::getParticleDensity() const
{
    double area = m_lattice->unitCellArea();
    return area == 0.0 ? 0.0 : 1.0 / area;
}

std::vector<const INode*> InterferenceFunction2DParaCrystal::getChildren() const
{
    return std::vector<const INode*>() << m_pdf1 << m_pdf2 << m_lattice;
}

InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(
    const InterferenceFunction2DParaCrystal& other)
{
    setName(other.getName());

    m_damping_length = other.m_damping_length;

    if (other.m_lattice)
        setLattice(*other.m_lattice);

    if (other.m_pdf1 && other.m_pdf2)
        setProbabilityDistributions(*other.m_pdf1, *other.m_pdf2);

    setDomainSizes(other.m_domain_sizes[0], other.m_domain_sizes[1]);
    setIntegrationOverXi(other.m_integrate_xi);

    init_parameters();
}

void InterferenceFunction2DParaCrystal::setLattice(const Lattice2D& lattice)
{
    m_lattice.reset(lattice.clone());
    registerChild(m_lattice.get());
}

//! Creates square lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param damping_length: the damping (coherence) length of the paracrystal in nanometers
//! @param domain_size_1: size of the coherent domain along the first basis vector in nanometers
//! @param domain_size_2: size of the coherent domain along the second basis vector in nanometers

InterferenceFunction2DParaCrystal*
InterferenceFunction2DParaCrystal::createSquare(double lattice_length, double damping_length,
                                                double domain_size_1, double domain_size_2)
{
    auto result = new InterferenceFunction2DParaCrystal(
        SquareLattice(lattice_length), damping_length, domain_size_1, domain_size_2);
    result->setIntegrationOverXi(true);
    return result;
}

//! Creates hexagonal lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param damping_length: the damping (coherence) length of the paracrystal in nanometers
//! @param domain_size_1: size of the coherent domain along the first basis vector in nanometers
//! @param domain_size_2: size of the coherent domain along the second basis vector in nanometers

InterferenceFunction2DParaCrystal*
InterferenceFunction2DParaCrystal::createHexagonal(double lattice_length, double damping_length,
                                                   double domain_size_1, double domain_size_2)
{
    auto result = new InterferenceFunction2DParaCrystal(
        HexagonalLattice(lattice_length), damping_length, domain_size_1, domain_size_2);
    result->setIntegrationOverXi(true);
    return result;
}

//! Sets the sizes of coherence domains.
//! @param size_1: coherence domain size along the first basis vector in nanometers
//! @param size_2: coherence domain size along the second basis vector in nanometers

void InterferenceFunction2DParaCrystal::setDomainSizes(double size_1, double size_2)
{
    m_domain_sizes[0] = size_1;
    m_domain_sizes[1] = size_2;
}

void InterferenceFunction2DParaCrystal::transformToPrincipalAxes(double qx, double qy, double gamma,
                                                                 double delta, double& q_pa_1,
                                                                 double& q_pa_2) const
{
    q_pa_1 = qx * std::cos(gamma) + qy * std::sin(gamma);
    q_pa_2 = qx * std::cos(gamma + delta) + qy * std::sin(gamma + delta);
}

void InterferenceFunction2DParaCrystal::init_parameters()
{
    mP_integrator
        = make_integrator_real(this, &InterferenceFunction2DParaCrystal::interferenceForXi);

    registerParameter(BornAgain::DampingLength, &m_damping_length).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::DomainSize1, &m_domain_sizes[0]).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::DomainSize2, &m_domain_sizes[1]).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
}

//! Returns interference function for fixed angle xi.
double InterferenceFunction2DParaCrystal::interferenceForXi(double xi) const
{
    double result = interference1D(m_qx, m_qy, xi, 0)
                    * interference1D(m_qx, m_qy, xi + m_lattice->latticeAngle(), 1);
    return result;
}

//! Returns interference function for fixed xi in the dimension determined by the given index.
double InterferenceFunction2DParaCrystal::interference1D(double qx, double qy, double xi,
                                                         size_t index) const
{
    if (index > 1)
        throw Exceptions::OutOfBoundsException(
            "InterferenceFunction2DParaCrystal::"
            "interference1D() -> Error! Index of interference function "
            "probability must be < 2");
    if (!m_pdf1 || !m_pdf2)
        throw Exceptions::NullPointerException(
            "InterferenceFunction2DParaCrystal::"
            "interference1D() -> Error! Probability distributions for "
            "interference function not properly initialized");

    double result(0.0);
    double length = index ? m_lattice->length2() : m_lattice->length1();
    int n = (int)std::abs(m_domain_sizes[index] / length);
    double nd = (double)n;
    complex_t fp = FTPDF(qx, qy, xi, index);
    if (n < 1) {
        result = ((1.0 + fp) / (1.0 - fp)).real();
    } else {
        if (std::norm(1.0 - fp) < std::numeric_limits<double>::epsilon())
            result = nd;
        // for (1-fp)*nd small, take the series expansion to second order in nd*(1-fp)
        else if (std::abs(1.0 - fp) * nd < 2e-4) {
            complex_t intermediate
                = (nd - 1.0) / 2.0 + (nd * nd - 1.0) * (fp - 1.0) / 6.0
                  + (nd * nd * nd - 2.0 * nd * nd - nd + 2.0) * (fp - 1.0) * (fp - 1.0) / 24.0;
            result = 1.0 + 2.0 * intermediate.real();
        } else {
            complex_t tmp;
            if (std::abs(fp) == 0.0
                || std::log(std::abs(fp)) * nd < std::log(std::numeric_limits<double>::min()))
                tmp = 0.0;
            else
                tmp = std::pow(fp, n);
            complex_t intermediate
                = fp / (1.0 - fp) - fp * (1.0 - tmp) / nd / (1.0 - fp) / (1.0 - fp);
            result = 1.0 + 2.0 * intermediate.real();
        }
    }
    return result;
}

complex_t InterferenceFunction2DParaCrystal::FTPDF(double qx, double qy, double xi,
                                                   size_t index) const
{
    double length = (index ? m_lattice->length2() : m_lattice->length1());

    const IFTDistribution2D* pdf = (index ? m_pdf2.get() : m_pdf1.get());
    double qa = qx * length * std::cos(xi) + qy * length * std::sin(xi);
    complex_t phase = exp_I(qa);
    // transform q to principal axes:
    double qp1, qp2;
    double gamma = xi + pdf->gamma();
    double delta = pdf->delta();
    transformToPrincipalAxes(qx, qy, gamma, delta, qp1, qp2);
    double amplitude = pdf->evaluate(qp1, qp2);
    complex_t result = phase * amplitude;
    if (m_damping_length != 0.0)
        result *= std::exp(-length / m_damping_length);
    return result;
}

std::vector<double> InterferenceFunction2DParaCrystal::domainSizes() const
{
    return {m_domain_sizes[0], m_domain_sizes[1]};
}

//! Enables/disables averaging over the lattice rotation angle.
//! @param integrate_xi: integration flag

void InterferenceFunction2DParaCrystal::setIntegrationOverXi(bool integrate_xi)
{
    m_integrate_xi = integrate_xi;
    m_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunction2DParaCrystal::lattice() const
{
    if (!m_lattice)
        throw std::runtime_error("InterferenceFunction2DParaCrystal::lattice() -> Error. "
                                 "No lattice defined.");
    return *m_lattice;
}
