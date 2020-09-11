// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/ObjectiveMetric.h
//! @brief     Defines ObjectiveMetric classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_FITTING_OBJECTIVEMETRIC_H
#define BORNAGAIN_CORE_FITTING_OBJECTIVEMETRIC_H

#include "Core/Basics/ICloneable.h"
#include <functional>
#include <memory>
#include <vector>

class SimDataPair;

//! Base class for metric implementations
class BA_CORE_API_ ObjectiveMetric : public ICloneable
{
public:
    ObjectiveMetric(std::function<double(double)> norm);

    ObjectiveMetric* clone() const override = 0;

    //! Computes metric value from SimDataPair object. Calls computeFromArrays internally.
    //! @param data_pair: SimDataPair object. Can optionally contain data uncertainties
    //! @param use_weights: boolean, defines if data uncertainties should be taken into account
    virtual double compute(const SimDataPair& data_pair, bool use_weights) const;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors and uncertainties.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param uncertainties: array with experimental data uncertainties.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    virtual double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                                     std::vector<double> uncertainties,
                                     std::vector<double> weight_factors) const = 0;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    virtual double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                                     std::vector<double> weight_factors) const = 0;

    void setNorm(std::function<double(double)> norm);

    //! Returns a copy of the normalization function used.
    auto norm() const { return m_norm; }

private:
    std::function<double(double)> m_norm; //! normalization function.
};

//! Implementation of the standard \f$ \chi^2 \f$ metric
//! derived from maximum likelihood with Gaussian uncertainties.
//! With default L2 norm corresponds to the formula
//! \f[\chi^2 = \sum \frac{(I - D)^2}{\delta_D^2}\f]
class BA_CORE_API_ Chi2Metric : public ObjectiveMetric
{
public:
    Chi2Metric();
    Chi2Metric* clone() const override;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors and uncertainties.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param uncertainties: array with experimental data uncertainties.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                             std::vector<double> uncertainties,
                             std::vector<double> weight_factors) const override;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                             std::vector<double> weight_factors) const override;
};

//! Implementation of \f$ \chi^2 \f$ metric
//! with standard deviation\f$\sigma = max(\sqrt{I}, 1)\f$,
//! where \f$I\f$ is the simulated intensity.
//! With default L2 norm corresponds to the formula
//! \f[\chi^2 = \sum \frac{(I - D)^2}{max(I, 1)}\f]
//! for unweighted experimental data. Falls to standard
//! Chi2Metric when data uncertainties are taken into account.
class BA_CORE_API_ PoissonLikeMetric : public Chi2Metric
{
public:
    PoissonLikeMetric();
    PoissonLikeMetric* clone() const override;

    using Chi2Metric::computeFromArrays;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                             std::vector<double> weight_factors) const override;
};

//! Implementation of the standard \f$ \chi^2 \f$ metric with intensity \f$I\f$
//! and experimental data \f$D\f$
//! being replaced by \f$ \log_{10} I \f$ and \f$\log_{10} D\f$ accordingly.
//! With default L2 norm corresponds to the formula
//! \f[\chi^2 = \sum \frac{(\log_{10} I - log_{10} D)^2 D^2 \ln^2{10}}{\delta_D^2}\f]
class BA_CORE_API_ LogMetric : public ObjectiveMetric
{
public:
    LogMetric();
    LogMetric* clone() const override;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors and uncertainties.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param uncertainties: array with experimental data uncertainties.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                             std::vector<double> uncertainties,
                             std::vector<double> weight_factors) const override;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                             std::vector<double> weight_factors) const override;
};

//! Implementation of relative difference metric.
//! With default L2 norm and weighting off corresponds to the formula
//! \f[Result = \sum \frac{(I - D)^2}{(I + D)^2}\f]
//! where \f$I\f$ is the simulated intensity, \f$D\f$ - experimental data.
//! If weighting is on, falls back to the standard \f$\chi^2\f$ metric.
class BA_CORE_API_ RelativeDifferenceMetric : public Chi2Metric
{
public:
    RelativeDifferenceMetric();
    RelativeDifferenceMetric* clone() const override;

    using Chi2Metric::computeFromArrays;

    //! Computes metric value from data arrays. Negative values in exp_data
    //! are ignored as well as non-positive weight_factors.
    //! All arrays involved in the computation must be of the same size.
    //! @param sim_data: array with simulated intensities.
    //! @param exp_data: array with intensity values obtained from an experiment.
    //! @param weight_factors: user-defined weighting factors. Used linearly, no matter which norm
    //! is chosen.
    double computeFromArrays(std::vector<double> sim_data, std::vector<double> exp_data,
                             std::vector<double> weight_factors) const override;
};

//! Implementation of relative difference metric.
//! With default L2 norm and weighting off corresponds to the formula
//! \f[Result = \sum (I \cdot Q^4 - D \cdot Q^4)^2\f]
//! where \f$Q\f$ is the scattering vector magnitude. If weighting is on,
//! coincides with the metric provided by Chi2Metric class.
class BA_CORE_API_ RQ4Metric : public Chi2Metric
{
public:
    RQ4Metric();
    RQ4Metric* clone() const override;
    //! Computes metric value from SimDataPair object. Calls computeFromArrays internally.
    //! @param data_pair: SimDataPair object. Can optionally contain data uncertainties
    //! @param use_weights: boolean, defines if data uncertainties should be taken into account
    double compute(const SimDataPair& data_pair, bool use_weights) const override;
};

#endif // BORNAGAIN_CORE_FITTING_OBJECTIVEMETRIC_H
