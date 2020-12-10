//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Distrib/ParameterDistribution.cpp
//! @brief     Implements class ParameterDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Param/Distrib/ParameterDistribution.h"
#include "Param/Distrib/Distributions.h"

ParameterDistribution::ParameterDistribution(const std::string& par_name,
                                             const IDistribution1D& distribution,
                                             size_t nbr_samples, double sigma_factor,
                                             const RealLimits& limits)
    : IParametricComponent("ParameterDistribution")
    , m_parname(par_name)
    , m_nbr_samples(nbr_samples)
    , m_sigma_factor(sigma_factor)
    , m_limits(limits)
    , m_xmin(1.0)
    , m_xmax(-1.0) {
    m_distribution.reset(distribution.clone());
    if (m_sigma_factor < 0.0)
        throw std::runtime_error("ParameterDistribution::ParameterDistribution() -> Error."
                                 "sigma factor cannot be negative");
    if (nbr_samples == 0)
        throw std::runtime_error("ParameterDistribution::ParameterDistribution() -> Error."
                                 "Number of samples can't be zero.");
}

ParameterDistribution::ParameterDistribution(const std::string& par_name,
                                             const IDistribution1D& distribution,
                                             size_t nbr_samples, double xmin, double xmax)
    : IParametricComponent("ParameterDistribution")
    , m_parname(par_name)
    , m_nbr_samples(nbr_samples)
    , m_sigma_factor(0.0)
    , m_xmin(xmin)
    , m_xmax(xmax) {
    m_distribution.reset(distribution.clone());
    if (m_sigma_factor < 0.0)
        throw std::runtime_error("ParameterDistribution::ParameterDistribution() -> Error."
                                 "sigma factor cannot be negative");
    if (nbr_samples == 0)
        throw std::runtime_error("ParameterDistribution::ParameterDistribution() -> Error."
                                 "Number of samples can't be zero.");
    if (xmin >= xmax)
        throw std::runtime_error("ParameterDistribution::ParameterDistribution() -> Error."
                                 "xmin>=xmax");
}

ParameterDistribution::ParameterDistribution(const ParameterDistribution& other)
    : IParametricComponent("ParameterDistribution")
    , m_parname(other.m_parname)
    , m_nbr_samples(other.m_nbr_samples)
    , m_sigma_factor(other.m_sigma_factor)
    , m_linked_par_names(other.m_linked_par_names)
    , m_limits(other.m_limits)
    , m_xmin(other.m_xmin)
    , m_xmax(other.m_xmax) {
    m_distribution.reset(other.m_distribution->clone());
}

ParameterDistribution::~ParameterDistribution() = default;

ParameterDistribution& ParameterDistribution::operator=(const ParameterDistribution& other) {
    if (this != &other) {
        this->m_parname = other.m_parname;
        m_nbr_samples = other.m_nbr_samples;
        m_sigma_factor = other.m_sigma_factor;
        m_distribution.reset(other.m_distribution->clone());
        m_linked_par_names = other.m_linked_par_names;
        m_limits = other.m_limits;
        m_xmin = other.m_xmin;
        m_xmax = other.m_xmax;
    }
    return *this;
}

ParameterDistribution& ParameterDistribution::linkParameter(std::string par_name) {
    m_linked_par_names.push_back(par_name);
    return *this;
}

size_t ParameterDistribution::getNbrSamples() const {
    if (m_distribution && m_distribution->isDelta())
        return 1;
    return m_nbr_samples;
}

std::vector<ParameterSample> ParameterDistribution::generateSamples() const {
    if (m_xmin < m_xmax)
        return m_distribution->equidistantSamplesInRange(m_nbr_samples, m_xmin, m_xmax);
    return m_distribution->equidistantSamples(m_nbr_samples, m_sigma_factor, m_limits);
}

const IDistribution1D* ParameterDistribution::getDistribution() const {
    return m_distribution.get();
}

IDistribution1D* ParameterDistribution::getDistribution() {
    return m_distribution.get();
}
