// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/DistributionHandler.cpp
//! @brief     Implements class DistributionHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/DistributionHandler.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/ParameterSample.h"

DistributionHandler::DistributionHandler() : m_nbr_combinations(1)
{
    setName("DistributionHandler");
}

DistributionHandler::~DistributionHandler() {}

void DistributionHandler::addParameterDistribution(const ParameterDistribution& par_distr)
{
    if (par_distr.getNbrSamples() > 0) {
        m_distributions.push_back(par_distr);
        m_nbr_combinations *= par_distr.getNbrSamples();
        m_cached_samples.push_back(par_distr.generateSamples());
    }
}

size_t DistributionHandler::getTotalNumberOfSamples() const
{
    return m_nbr_combinations;
}

double DistributionHandler::setParameterValues(ParameterPool* p_parameter_pool, size_t index)
{
    if (index >= m_nbr_combinations)
        throw Exceptions::RuntimeErrorException(
            "DistributionWeighter::setParameterValues: "
            "index must be smaller than the total number of parameter combinations");
    size_t n_distr = m_distributions.size();
    double weight = 1.0;
    if (n_distr == 0)
        return weight;
    for (size_t param_index = n_distr - 1;; --param_index) {
        size_t remainder = index % m_distributions[param_index].getNbrSamples();
        index /= m_distributions[param_index].getNbrSamples();
        int changed = p_parameter_pool->setMatchedParametersValue(
            m_distributions[param_index].getMainParameterName(),
            m_cached_samples[param_index][remainder].value);
        if (changed != 1) {
            throw Exceptions::RuntimeErrorException("DistributionWeighter::setParameterValues: "
                                                    "parameter name matches nothing or more than "
                                                    "one parameter");
        }
        weight *= m_cached_samples[param_index][remainder].weight;
        if (param_index == 0)
            break;
    }
    return weight;
}

void DistributionHandler::setParameterToMeans(ParameterPool* p_parameter_pool) const
{
    for (auto& distribution : m_distributions) {
        const std::string par_name = distribution.getMainParameterName();
        const double mean_val = distribution.getDistribution()->getMean();
        if (p_parameter_pool->setMatchedParametersValue(par_name, mean_val) != 1)
            throw std::runtime_error("Error in DistributionHandler::setParameterToMeans: parameter "
                                     "name matches nothing or more than "
                                     "one parameter");
    }
}

const DistributionHandler::Distributions_t& DistributionHandler::getDistributions() const
{
    return m_distributions;
}
