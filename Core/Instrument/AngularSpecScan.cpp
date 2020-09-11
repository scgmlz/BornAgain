// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/AngularSpecScan.cpp
//! @brief     Implements AngularSpecScan class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Beam/IFootprintFactor.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/PointwiseAxis.h"
#include "Core/Detector/ScanResolution.h"
#include "Core/Multilayer/SpecularSimulationElement.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Core/PyIO/PythonFormatting.h"
#include "Core/Tools/PyFmt.h"
#include "Fit/Tools/RealLimits.h"

namespace
{
std::vector<std::vector<double>>
extractValues(std::vector<std::vector<ParameterSample>> samples,
              const std::function<double(const ParameterSample&)> extractor);

const RealLimits wl_limits = RealLimits::nonnegative();
const RealLimits inc_limits = RealLimits::limited(0.0, M_PI_2);
} // namespace

AngularSpecScan::AngularSpecScan(double wl, std::vector<double> inc_angle)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle), m_wl(wl),
      m_inc_angle(std::make_unique<PointwiseAxis>("inc_angles", std::move(inc_angle))),
      m_wl_resolution(ScanResolution::scanEmptyResolution()),
      m_inc_resolution(ScanResolution::scanEmptyResolution())
{
    checkInitialization();
}

AngularSpecScan::AngularSpecScan(double wl, const IAxis& inc_angle)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle), m_wl(wl), m_inc_angle(inc_angle.clone()),
      m_wl_resolution(ScanResolution::scanEmptyResolution()),
      m_inc_resolution(ScanResolution::scanEmptyResolution())
{
    checkInitialization();
}

AngularSpecScan::AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle), m_wl(wl),
      m_inc_angle(std::make_unique<FixedBinAxis>("inc_angles", nbins, alpha_i_min, alpha_i_max)),
      m_wl_resolution(ScanResolution::scanEmptyResolution()),
      m_inc_resolution(ScanResolution::scanEmptyResolution())
{
    checkInitialization();
}

AngularSpecScan* AngularSpecScan::clone() const
{
    auto result = std::make_unique<AngularSpecScan>(m_wl, *m_inc_angle);
    result->setFootprintFactor(m_footprint.get());
    result->setWavelengthResolution(*m_wl_resolution);
    result->setAngleResolution(*m_inc_resolution);
    return result.release();
}

AngularSpecScan::~AngularSpecScan() = default;

std::vector<SpecularSimulationElement> AngularSpecScan::generateSimulationElements() const
{
    std::vector<SpecularSimulationElement> result;
    const std::vector<WlAnglePair> paired_values = generateWlAnglePairs();

    const size_t res_size = paired_values.size();
    result.reserve(res_size);
    for (size_t i = 0; i < res_size; ++i) {
        const double wl = paired_values[i].first;
        const double inc = paired_values[i].second;
        result.emplace_back(wl, -inc);
        if (!wl_limits.isInRange(wl) || !inc_limits.isInRange(inc))
            result.back().setCalculationFlag(false); // false = exclude from calculations
    }

    return result;
}

void AngularSpecScan::setFootprintFactor(const IFootprintFactor* f_factor)
{
    m_footprint.reset(f_factor ? f_factor->clone() : nullptr);
}

void AngularSpecScan::setWavelengthResolution(const ScanResolution& resolution)
{
    m_wl_resolution.reset(resolution.clone());
    m_wl_res_cache.clear();
    m_wl_res_cache.shrink_to_fit();
}

void AngularSpecScan::setRelativeWavelengthResolution(const RangedDistribution& distr,
                                                      double rel_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanRelativeResolution(distr, rel_dev));
    setWavelengthResolution(*resolution);
}

void AngularSpecScan::setRelativeWavelengthResolution(const RangedDistribution& distr,
                                                      const std::vector<double>& rel_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanRelativeResolution(distr, rel_dev));
    setWavelengthResolution(*resolution);
}

void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution& distr,
                                                      double std_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanAbsoluteResolution(distr, std_dev));
    setWavelengthResolution(*resolution);
}

void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution& distr,
                                                      const std::vector<double>& std_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanAbsoluteResolution(distr, std_dev));
    setWavelengthResolution(*resolution);
}

void AngularSpecScan::setAngleResolution(const ScanResolution& resolution)
{
    m_inc_resolution.reset(resolution.clone());
    m_inc_res_cache.clear();
    m_inc_res_cache.shrink_to_fit();
}

void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution& distr, double rel_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanRelativeResolution(distr, rel_dev));
    setAngleResolution(*resolution);
}

void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution& distr,
                                                   const std::vector<double>& rel_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanRelativeResolution(distr, rel_dev));
    setAngleResolution(*resolution);
}

void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution& distr, double std_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanAbsoluteResolution(distr, std_dev));
    setAngleResolution(*resolution);
}

void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution& distr,
                                                   const std::vector<double>& std_dev)
{
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanAbsoluteResolution(distr, std_dev));
    setAngleResolution(*resolution);
}

std::vector<double> AngularSpecScan::footprint(size_t start, size_t n_elements) const
{
    if (start + n_elements > numberOfSimulationElements())
        throw std::runtime_error("Error in AngularSpecScan::footprint: given index exceeds the "
                                 "number of simulation elements");

    std::vector<double> result(n_elements, 1.0);
    if (!m_footprint)
        return result;

    const size_t n_wl_samples = m_wl_resolution->nSamples();
    const size_t n_inc_samples = m_inc_resolution->nSamples();

    const auto sample_values = extractValues(
        applyIncResolution(), [](const ParameterSample& sample) { return sample.value; });

    size_t pos_out = start / (n_wl_samples * n_inc_samples);
    size_t pos_inc = (start - pos_out * n_wl_samples * n_inc_samples) / n_wl_samples;
    size_t pos_wl = (start - pos_inc * n_wl_samples);
    int left = static_cast<int>(n_elements);
    size_t pos_res = 0;
    for (size_t i = pos_out; left > 0; ++i)
        for (size_t k = pos_inc; k < n_inc_samples && left > 0; ++k) {
            pos_inc = 0;
            double angle = sample_values[i][k];
            double footprint = inc_limits.isInRange(angle) ? m_footprint->calculate(angle) : 1.0;
            for (size_t j = pos_wl; j < n_wl_samples && left > 0; ++j) {
                pos_wl = 0;
                result[pos_res] = footprint;
                ++pos_res;
                --left;
            }
        }
    return result;
}

size_t AngularSpecScan::numberOfSimulationElements() const
{
    return m_inc_angle->size() * m_wl_resolution->nSamples() * m_inc_resolution->nSamples();
}

std::vector<double>
AngularSpecScan::createIntensities(const std::vector<SpecularSimulationElement>& sim_elements) const
{
    const size_t axis_size = m_inc_angle->size();
    std::vector<double> result(axis_size, 0.0);

    auto wl_weights = extractValues(applyWlResolution(),
                                    [](const ParameterSample& sample) { return sample.weight; });
    auto inc_weights = extractValues(applyIncResolution(),
                                     [](const ParameterSample& sample) { return sample.weight; });

    size_t elem_pos = 0;
    for (size_t i = 0; i < axis_size; ++i) {
        double& current = result[i];
        for (size_t k = 0, size_incs = inc_weights[i].size(); k < size_incs; ++k) {
            const double inc_weight = inc_weights[i][k];
            for (size_t j = 0, size_wls = wl_weights[i].size(); j < size_wls; ++j) {
                current += sim_elements[elem_pos].getIntensity() * inc_weight * wl_weights[i][j];
                ++elem_pos;
            }
        }
    }
    return result;
}

std::string AngularSpecScan::print() const
{
    std::stringstream result;
    result << "\n" << pyfmt::indent() << "# Defining specular scan:\n";
    const std::string axis_def = pyfmt::indent() + "axis = ";
    result << axis_def << pyfmt2::printAxis(*coordinateAxis(), "rad", axis_def.size()) << "\n";

    result << pyfmt::indent() << "scan = ";
    result << "ba.AngularSpecScan(" << pyfmt::printDouble(m_wl) << ", axis)\n";

    if (m_footprint) {
        result << *m_footprint << "\n";
        result << pyfmt::indent() << "scan.setFootprintFactor(footprint)\n";
    }
    if (!m_inc_resolution->empty()) {
        result << "\n" << pyfmt::indent() << "# Defining angular resolution\n";
        result << *m_inc_resolution << "\n";
        result << pyfmt::indent() << "scan.setAngleResolution(resolution)\n";
    }
    if (!m_wl_resolution->empty()) {
        result << "\n" << pyfmt::indent() << "# Defining wavelength resolution\n";
        result << *m_wl_resolution << "\n";
        result << pyfmt::indent() << "scan.setWavelengthResolution(resolution)\n";
    }
    return result.str();
}

void AngularSpecScan::checkInitialization()
{
    if (m_wl <= 0.0)
        throw std::runtime_error(
            "Error in AngularSpecScan::checkInitialization: wavelength shell be positive");

    std::vector<double> axis_values = m_inc_angle->getBinCenters();
    if (!std::is_sorted(axis_values.begin(), axis_values.end()))
        throw std::runtime_error("Error in AngularSpecScan::checkInitialization: q-vector values "
                                 "shall be sorted in ascending order.");

    // TODO: check for inclination angle limits after switching to pointwise resolution.
}

std::vector<AngularSpecScan::WlAnglePair> AngularSpecScan::generateWlAnglePairs() const
{
    std::vector<WlAnglePair> result;
    result.reserve(numberOfSimulationElements());

    const size_t axis_size = m_inc_angle->size();
    const auto wls = extractValues(applyWlResolution(),
                                   [](const ParameterSample& sample) { return sample.value; });
    const auto incs = extractValues(applyIncResolution(),
                                    [](const ParameterSample& sample) { return sample.value; });

    for (size_t i = 0; i < axis_size; ++i)
        for (size_t k = 0, size_incs = incs[i].size(); k < size_incs; ++k)
            for (size_t j = 0, size_wls = wls[i].size(); j < size_wls; ++j)
                result.emplace_back(wls[i][j], incs[i][k]);

    return result;
}

AngularSpecScan::DistrOutput AngularSpecScan::applyWlResolution() const
{
    if (m_wl_res_cache.empty())
        m_wl_res_cache = m_wl_resolution->generateSamples(m_wl, m_inc_angle->size());
    return m_wl_res_cache;
}

AngularSpecScan::DistrOutput AngularSpecScan::applyIncResolution() const
{
    if (m_inc_res_cache.empty())
        m_inc_res_cache = m_inc_resolution->generateSamples(m_inc_angle->getBinCenters());
    return m_inc_res_cache;
}

namespace
{
std::vector<std::vector<double>>
extractValues(std::vector<std::vector<ParameterSample>> samples,
              const std::function<double(const ParameterSample&)> extractor)
{
    std::vector<std::vector<double>> result;
    result.resize(samples.size());
    for (size_t i = 0, size = result.size(); i < size; ++i) {
        auto& sample_row = samples[i];
        auto& result_row = result[i];
        result_row.reserve(sample_row.size());
        std::for_each(sample_row.begin(), sample_row.end(),
                      [&result_row, &extractor](const ParameterSample& sample) {
                          result_row.push_back(extractor(sample));
                      });
    }
    return result;
}
} // namespace
