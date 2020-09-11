// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterDistribution.h
//! @brief     Defines class ParameterDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERDISTRIBUTION_H
#define BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERDISTRIBUTION_H

#include "Core/Parametrization/IParameterized.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Fit/Tools/RealLimits.h"
#include <memory>
#include <vector>

class IDistribution1D;

//! A parametric distribution function, for use with any model parameter.

class BA_CORE_API_ ParameterDistribution : public IParameterized
{
public:
    ParameterDistribution(const std::string& par_name, const IDistribution1D& distribution,
                          size_t nbr_samples, double sigma_factor = 0.0,
                          const RealLimits& limits = RealLimits());

    ParameterDistribution(const std::string& par_name, const IDistribution1D& distribution,
                          size_t nbr_samples, double xmin, double xmax);

    ParameterDistribution(const ParameterDistribution& other);
    virtual ~ParameterDistribution();

    //! Overload assignment operator
    ParameterDistribution& operator=(const ParameterDistribution& other);

    ParameterDistribution& linkParameter(std::string par_name);

    //! get the main parameter's name
    std::string getMainParameterName() const { return m_name; }

    //! get number of samples for this distribution
    size_t getNbrSamples() const;

    //! get the sigma factor
    double getSigmaFactor() const { return m_sigma_factor; }

    const IDistribution1D* getDistribution() const;
    IDistribution1D* getDistribution();

    //! generate list of sampled values with their weight
    std::vector<ParameterSample> generateSamples() const;

    //! get list of linked parameter names
    std::vector<std::string> getLinkedParameterNames() const { return m_linked_par_names; }

    RealLimits getLimits() const { return m_limits; }

    double getMinValue() const { return m_xmin; }
    double getMaxValue() const { return m_xmax; }

private:
    std::string m_name;
    std::unique_ptr<IDistribution1D> mP_distribution;
    size_t m_nbr_samples;
    double m_sigma_factor;
    std::vector<std::string> m_linked_par_names;
    RealLimits m_limits;
    double m_xmin;
    double m_xmax;
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERDISTRIBUTION_H
