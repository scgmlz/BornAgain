// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/InterferenceFunction2DParaCrystal.cpp
//! @brief     Implements class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunction2DParaCrystal.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "MemberFunctionIntegrator.h"
#include "Exceptions.h"

#include <functional>

using namespace BornAgain;

InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(
        double length_1, double length_2, double alpha_lattice, double xi,
        double damping_length)
    : m_integrate_xi(false)
    , m_damping_length(damping_length)
    , m_use_damping_length(true)
{
    m_lattice_params.m_length_1 = length_1;
    m_lattice_params.m_length_2 = length_2;
    m_lattice_params.m_angle = alpha_lattice;
    m_lattice_params.m_xi = xi;
    m_pdfs[0] = 0;
    m_pdfs[1] = 0;
    m_domain_sizes[0] = 0.0;
    m_domain_sizes[1] = 0.0;
    setName(InterferenceFunction2DParaCrystalType);
    if (m_damping_length==0.0) {
        m_use_damping_length = false;
    }
    init_parameters();
}

InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal()
{
    for (size_t i=0; i<2; ++i) delete m_pdfs[i];
}

InterferenceFunction2DParaCrystal *InterferenceFunction2DParaCrystal::clone() const
{
    InterferenceFunction2DParaCrystal *result = new InterferenceFunction2DParaCrystal(
        m_lattice_params.m_length_1, m_lattice_params.m_length_2, m_lattice_params.m_angle,
        m_lattice_params.m_xi, m_damping_length);
    result->setDomainSizes(m_domain_sizes[0], m_domain_sizes[1]);
    if (m_pdfs[0] && m_pdfs[1])
        result->setProbabilityDistributions(*m_pdfs[0], *m_pdfs[1]);
    result->setIntegrationOverXi(m_integrate_xi);
    return result;
}

void InterferenceFunction2DParaCrystal::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

void InterferenceFunction2DParaCrystal::setProbabilityDistributions(
        const IFTDistribution2D& pdf_1, const IFTDistribution2D& pdf_2)
{
    for (size_t i=0; i<2; ++i) delete m_pdfs[i];
    m_pdfs[0] = pdf_1.clone();
    m_pdfs[1] = pdf_2.clone();
}

double InterferenceFunction2DParaCrystal::evaluate(const kvector_t& q) const
{
    m_qx = q.x();
    m_qy = q.y();
    double result;
    if (m_integrate_xi) {
        MemberFunctionIntegrator<InterferenceFunction2DParaCrystal>::
            mem_function p_member_function =
                    &InterferenceFunction2DParaCrystal::interferenceForXi;
        MemberFunctionIntegrator<InterferenceFunction2DParaCrystal>
            integrator(p_member_function, this);
        result = integrator.integrate(0.0, Units::PI2, nullptr)/Units::PI2;
   }
    else {
        result = interferenceForXi(m_lattice_params.m_xi, nullptr);
    }
    return result;
}

Lattice2DParameters InterferenceFunction2DParaCrystal::getLatticeParameters() const
{
    return m_lattice_params;
}

std::string InterferenceFunction2DParaCrystal::addParametersToExternalPool(
        std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(
            path, external_pool, copy_number);

    // add parameters of the probability density functions
    if (m_pdfs[0]) {
        m_pdfs[0]->addParametersToExternalPool(new_path, external_pool, 0);
    }
    if (m_pdfs[1]) {
        m_pdfs[1]->addParametersToExternalPool(new_path, external_pool, 1);
    }
    return new_path;
}

double InterferenceFunction2DParaCrystal::getParticleDensity() const
{
    double area = getUnitCellArea(m_lattice_params);
    if (area == 0.0) {
        return 0.0;
    }
    return 1.0/area;
}

InterferenceFunction2DParaCrystal* InterferenceFunction2DParaCrystal::
    createSquare(double peak_distance, double damping_length, double domain_size_1,
        double domain_size_2)
{
    InterferenceFunction2DParaCrystal *p_new =
            new InterferenceFunction2DParaCrystal(peak_distance, peak_distance,
                    Units::PID2, 0.0, damping_length);
    p_new->setDomainSizes(domain_size_1, domain_size_2);
    p_new->setIntegrationOverXi(true);
    return p_new;
}

InterferenceFunction2DParaCrystal* InterferenceFunction2DParaCrystal::
    createHexagonal(double peak_distance, double damping_length,
            double domain_size_1, double domain_size_2)
{
    InterferenceFunction2DParaCrystal *p_new =
            new InterferenceFunction2DParaCrystal(peak_distance, peak_distance,
                    2.0*Units::PI/3.0, 0.0, damping_length);
    p_new->setDomainSizes(domain_size_1, domain_size_2);
    p_new->setIntegrationOverXi(true);
    return p_new;
}

void InterferenceFunction2DParaCrystal::setDomainSizes(double size_1, double size_2)
{
    m_domain_sizes[0] = size_1;
    m_domain_sizes[1] = size_2;
}

void InterferenceFunction2DParaCrystal::transformToPrincipalAxes(
        double qx, double qy, double gamma, double delta, double& q_pa_1, double& q_pa_2) const
{
    q_pa_1 = qx*std::cos(gamma) + qy*std::sin(gamma);
    q_pa_2 = qx*std::cos(gamma+delta) + qy*std::sin(gamma+delta);
}

void InterferenceFunction2DParaCrystal::init_parameters()
{
    clearParameterPool();
    registerParameter(LatticeLength1, &m_lattice_params.m_length_1);
    registerParameter(LatticeLength2, &m_lattice_params.m_length_2);
    registerParameter(Alpha, &m_lattice_params.m_angle);
    registerParameter(Xi, &m_lattice_params.m_xi);
    registerParameter(DampingLength, &m_damping_length);
    registerParameter(DomainSize1, &m_domain_sizes[0]);
    registerParameter(DomainSize2, &m_domain_sizes[1]);
}

double InterferenceFunction2DParaCrystal::interferenceForXi(double xi, void *) const
{
    double result = interference1D(m_qx, m_qy, xi, 0)*interference1D(m_qx, m_qy,
            xi + m_lattice_params.m_angle, 1);
    return result;
}

double InterferenceFunction2DParaCrystal::interference1D(double qx, double qy,
        double xi, size_t index) const
{
    if (index > 1) {
        throw OutOfBoundsException("InterferenceFunction2DParaCrystal::"
                "interference1D() -> Error! Index of interference function "
                "probability must be < 2");
    }
    if (!m_pdfs[0] || !m_pdfs[1]) {
        throw NullPointerException("InterferenceFunction2DParaCrystal::"
                "interference1D() -> Error! Probability distributions for "
                "interference funtion not properly initialized");
    }
    double result;
    double length = (index ? m_lattice_params.m_length_2 : m_lattice_params.m_length_1);
    int n = (int)std::abs(m_domain_sizes[index]/length);
    double nd = (double)n;
    complex_t fp = FTPDF(qx, qy, xi, index);
    if (n<1) {
        result = ((1.0 + fp)/(1.0 - fp)).real();
    } else {
        if (std::norm(1.0-fp) < Numeric::double_epsilon ) {
            result = nd;
        }
        // for (1-fp)*nd small, take the series expansion to second order in nd*(1-fp)
        else if (std::abs(1.0-fp)*nd < 2e-4) {
            complex_t intermediate = (nd-1.0)/2.0 + (nd*nd-1.0)*(fp-1.0)/6.0
                    + (nd*nd*nd-2.0*nd*nd-nd+2.0)*(fp-1.0)*(fp-1.0)/24.0;
            result = 1.0 + 2.0*intermediate.real();
        }
        else {
            complex_t tmp;
            if (std::abs(fp)==0.0
             || std::log(std::abs(fp))*nd < std::log(std::numeric_limits<double>::min())) {
                            tmp = complex_t(0.0, 0.0);
                        } else {
                            tmp = std::pow(fp,n);
                        }
            complex_t intermediate = fp/(1.0-fp) - fp*(1.0-tmp)/nd/(1.0-fp)/(1.0-fp);
            result = 1.0 + 2.0*intermediate.real();
        }
    }
    return result;
}

complex_t InterferenceFunction2DParaCrystal::FTPDF(double qx, double qy,
        double xi, size_t index) const
{
    double length = (index ? m_lattice_params.m_length_2 : m_lattice_params.m_length_1);
    double qa = qx*length*std::cos(xi) + qy*length*std::sin(xi);
    complex_t phase = std::exp(complex_t(0.0, 1.0)*qa);
    // transform q to principal axes:
    double qp1, qp2;
    double gamma = xi + m_pdfs[index]->getGamma();
    double delta = m_pdfs[index]->getDelta();
    transformToPrincipalAxes(qx, qy, gamma, delta, qp1, qp2);
    double amplitude = m_pdfs[index]->evaluate(qp1, qp2);
    complex_t result = phase*amplitude;
    if (m_use_damping_length) {
        result *= std::exp(-length/m_damping_length);
    }
    return result;
}

std::vector<double> InterferenceFunction2DParaCrystal::getDomainSizes() const
{
    std::vector<double> result;
    result.resize(2);
    result[0] = m_domain_sizes[0];
    result[1] = m_domain_sizes[1];
    return result;
}

std::vector<const IFTDistribution2D *> InterferenceFunction2DParaCrystal::getProbabilityDistributions() const
{
    std::vector<const IFTDistribution2D *>  result;
    result.resize(2);
    result[0] = m_pdfs[0];
    result[1] = m_pdfs[1];
    return result;
}
