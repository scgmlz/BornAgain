// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/DistributionHandler.h
//! @brief     Defines class DistributionHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_DISTRIBUTIONHANDLER_H
#define BORNAGAIN_CORE_PARAMETRIZATION_DISTRIBUTIONHANDLER_H

#include "Core/Parametrization/ParameterDistribution.h"
#include <vector>

//! Provides the functionality to average over parameter distributions with weights.

//! @ingroup algorithms_internal
class BA_CORE_API_ DistributionHandler : public IParameterized
{
public:
    typedef std::vector<ParameterDistribution> Distributions_t;
    DistributionHandler();
    virtual ~DistributionHandler();

    //! add a sampled parameter distribution
    void addParameterDistribution(const std::string& param_name,
                                  const IDistribution1D& distribution, size_t nbr_samples,
                                  double sigma_factor = 0.0,
                                  const RealLimits& limits = RealLimits());

    void addParameterDistribution(const ParameterDistribution& par_distr);

    //! get the total number of parameter value combinations (product
    //! of the individual sizes of each parameter distribution
    size_t getTotalNumberOfSamples() const;

    //! set the parameter values of the simulation object to a specific
    //! combination of values, determined by the index (which must be smaller
    //! than the total number of combinations) and returns the weight
    //! associated with this combination of parameter values
    double setParameterValues(ParameterPool* p_parameter_pool, size_t index);

    //! Sets mean distribution values to the parameter pool.
    void setParameterToMeans(ParameterPool* p_parameter_pool) const;

    const Distributions_t& getDistributions() const;

private:
    size_t m_nbr_combinations;
    Distributions_t m_distributions;
    std::vector<std::vector<ParameterSample>> m_cached_samples;
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_DISTRIBUTIONHANDLER_H
