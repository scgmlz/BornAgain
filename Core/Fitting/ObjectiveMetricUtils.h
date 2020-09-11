// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/ObjectiveMetricUtils.h
//! @brief     Defines ObjectiveMetric utilities and corresponding namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_FITTING_OBJECTIVEMETRICUTILS_H
#define BORNAGAIN_CORE_FITTING_OBJECTIVEMETRICUTILS_H

#include "Wrap/WinDllMacros.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

class ObjectiveMetric;

namespace ObjectiveMetricUtils
{
//! Returns L1 normalization function.
BA_CORE_API_ const std::function<double(double)> l1Norm();
//! Returns L2 normalization function.
BA_CORE_API_ const std::function<double(double)> l2Norm();

//! Creates the specified metric with the default norm.
BA_CORE_API_ std::unique_ptr<ObjectiveMetric> createMetric(const std::string& metric);

//! Creates the metric with the specified norm
BA_CORE_API_ std::unique_ptr<ObjectiveMetric> createMetric(std::string metric, std::string norm);

//! Prints available metric options
BA_CORE_API_ std::string availableMetricOptions();

//! Returns the names of the norms used by ObjectiveMetric.
BA_CORE_API_ std::vector<std::string> normNames();

//! Returns the names of the objective metrics used.
BA_CORE_API_ std::vector<std::string> metricNames();

//! Returns default norm name.
BA_CORE_API_ std::string defaultNormName();

//! Returns default metric name.
BA_CORE_API_ std::string defaultMetricName();
} // namespace ObjectiveMetricUtils

#endif // BORNAGAIN_CORE_FITTING_OBJECTIVEMETRICUTILS_H
