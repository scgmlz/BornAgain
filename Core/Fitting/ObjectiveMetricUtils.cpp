// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/ObjectiveMetricUtils.cpp
//! @brief     Implements ObjectiveMetric utilities.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Fitting/ObjectiveMetricUtils.h"
#include "Core/Fitting/ObjectiveMetric.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>

namespace
{
const std::function<double(double)> l1_norm = [](double term) { return std::abs(term); };
const std::function<double(double)> l2_norm = [](double term) { return term * term; };

const std::map<std::string, std::function<std::unique_ptr<ObjectiveMetric>()>> metric_factory = {
    {"chi2", []() { return std::make_unique<Chi2Metric>(); }},
    {"poisson-like", []() { return std::make_unique<PoissonLikeMetric>(); }},
    {"log", []() { return std::make_unique<LogMetric>(); }},
    {"reldiff", []() { return std::make_unique<RelativeDifferenceMetric>(); }},
    {"rq4", []() { return std::make_unique<RQ4Metric>(); }}};
const std::string default_metric_name = "poisson-like";

const std::map<std::string, std::function<double(double)>> norm_factory = {{"l1", l1_norm},
                                                                           {"l2", l2_norm}};
const std::string default_norm_name = "l2";

template <class U> std::vector<std::string> keys(const std::map<std::string, U>& map)
{
    std::vector<std::string> result;
    result.reserve(map.size());
    for (auto& item : map)
        result.push_back(item.first);
    return result;
}
} // namespace

const std::function<double(double)> ObjectiveMetricUtils::l1Norm()
{
    return l1_norm;
}

const std::function<double(double)> ObjectiveMetricUtils::l2Norm()
{
    return l2_norm;
}

std::unique_ptr<ObjectiveMetric> ObjectiveMetricUtils::createMetric(const std::string& metric)
{
    return createMetric(metric, defaultNormName());
}

std::unique_ptr<ObjectiveMetric> ObjectiveMetricUtils::createMetric(std::string metric,
                                                                    std::string norm)
{
    std::transform(metric.begin(), metric.end(), metric.begin(), ::tolower);
    std::transform(norm.begin(), norm.end(), norm.begin(), ::tolower);
    const auto metric_iter = metric_factory.find(metric);
    const auto norm_iter = norm_factory.find(norm);
    if (metric_iter == metric_factory.end() || norm_iter == norm_factory.end()) {
        std::stringstream ss;
        ss << "Error in ObjectiveMetricUtils::createMetric: either metric (" << metric
           << ") or norm (" << norm << ") name is unknown.\n";
        ss << availableMetricOptions();
        throw std::runtime_error(ss.str());
    }

    auto result = metric_iter->second();
    result->setNorm(norm_iter->second);
    return result;
}

std::string ObjectiveMetricUtils::availableMetricOptions()
{
    std::stringstream ss;
    ss << "Available metrics:\n";
    for (auto& item : metricNames())
        ss << "\t" << item << "\n";
    ss << "default metric: " << defaultMetricName() << "\n";
    ss << "Available norms:\n";
    for (auto& item : normNames())
        ss << "\t" << item << "\n";
    ss << "default norm: " << defaultNormName() << "\n";
    return ss.str();
}

std::vector<std::string> ObjectiveMetricUtils::normNames()
{
    return keys(norm_factory);
}

std::vector<std::string> ObjectiveMetricUtils::metricNames()
{
    return keys(metric_factory);
}

std::string ObjectiveMetricUtils::defaultNormName()
{
    return default_norm_name;
}

std::string ObjectiveMetricUtils::defaultMetricName()
{
    return default_metric_name;
}
