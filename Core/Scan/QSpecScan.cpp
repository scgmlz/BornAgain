//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scan/QSpecScan.cpp
//! @brief     Implements QSpecScan class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Scan/QSpecScan.h"
#include "Base/Axis/FixedBinAxis.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Core/Element/SpecularSimulationElement.h"
#include "Device/Resolution/ScanResolution.h"
#include "Param/Distrib/RangedDistributions.h"

QSpecScan::QSpecScan(std::vector<double> qs_nm)
    : m_qs(std::make_unique<PointwiseAxis>("qs", std::move(qs_nm)))
    , m_resolution(ScanResolution::scanEmptyResolution()) {
    checkInitialization();
}

QSpecScan::QSpecScan(const IAxis& qs_nm)
    : m_qs(qs_nm.clone()), m_resolution(ScanResolution::scanEmptyResolution()) {
    checkInitialization();
}

QSpecScan::QSpecScan(int nbins, double qz_min, double qz_max)
    : m_qs(std::make_unique<FixedBinAxis>("qs", nbins, qz_min, qz_max))
    , m_resolution(ScanResolution::scanEmptyResolution()) {
    checkInitialization();
}

QSpecScan::~QSpecScan() = default;

QSpecScan* QSpecScan::clone() const {
    auto* result = new QSpecScan(*m_qs);
    result->setQResolution(*m_resolution);
    return result;
}

//! Generates simulation elements for specular simulations
std::vector<SpecularSimulationElement>
QSpecScan::generateSimulationElements(const Instrument& instrument) const {
    const std::vector<double> qz = generateQzVector();

    std::vector<SpecularSimulationElement> result;
    result.reserve(qz.size());
    for (size_t i = 0, size = qz.size(); i < size; ++i)
        result.emplace_back(SpecularSimulationElement(-qz[i] / 2.0, instrument, qz[i] >= 0));
    return result;
}

std::vector<double> QSpecScan::footprint(size_t i, size_t n_elements) const {
    if (i + n_elements > numberOfSimulationElements())
        throw std::runtime_error("Error in QSpecScan::footprint: given index exceeds the "
                                 "number of simulation elements");
    return std::vector<double>(n_elements, 1.0);
}

//! Returns the number of simulation elements
size_t QSpecScan::numberOfSimulationElements() const {
    return m_qs->size() * m_resolution->nSamples();
}

std::vector<double>
QSpecScan::createIntensities(const std::vector<SpecularSimulationElement>& sim_elements) const {
    const size_t axis_size = m_qs->size();
    std::vector<double> result(axis_size, 0.0);

    const auto samples = applyQResolution();

    size_t elem_pos = 0;
    for (size_t i = 0; i < axis_size; ++i) {
        double& current = result[i];
        for (size_t j = 0, size = samples[i].size(); j < size; ++j) {
            current += sim_elements[elem_pos].intensity() * samples[i][j].weight;
            ++elem_pos;
        }
    }
    return result;
}

void QSpecScan::setQResolution(const ScanResolution& resolution) {
    m_resolution.reset(resolution.clone());
    m_q_res_cache.clear();
    m_q_res_cache.shrink_to_fit();
}

void QSpecScan::setRelativeQResolution(const IRangedDistribution& distr, double rel_dev) {
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanRelativeResolution(distr, rel_dev));
    setQResolution(*resolution);
}

void QSpecScan::setRelativeQResolution(const IRangedDistribution& distr,
                                       const std::vector<double>& rel_dev) {
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanRelativeResolution(distr, rel_dev));
    setQResolution(*resolution);
}

void QSpecScan::setAbsoluteQResolution(const IRangedDistribution& distr, double std_dev) {
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanAbsoluteResolution(distr, std_dev));
    setQResolution(*resolution);
}

void QSpecScan::setAbsoluteQResolution(const IRangedDistribution& distr,
                                       const std::vector<double>& std_dev) {
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanAbsoluteResolution(distr, std_dev));
    setQResolution(*resolution);
}

void QSpecScan::checkInitialization() {
    std::vector<double> axis_values = m_qs->binCenters();
    if (!std::is_sorted(axis_values.begin(), axis_values.end()))
        throw std::runtime_error("Error in QSpecScan::checkInitialization: q-vector values shall "
                                 "be sorted in ascending order.");

    if (axis_values.front() < 0)
        throw std::runtime_error("Error in QSpecScan::checkInitialization: q-vector values are out "
                                 "of acceptable range.");
}

std::vector<double> QSpecScan::generateQzVector() const {
    const auto samples = applyQResolution();

    std::vector<double> result;
    result.reserve(numberOfSimulationElements());
    for (size_t i = 0, size_out = samples.size(); i < size_out; ++i)
        for (size_t j = 0, size_in = samples[i].size(); j < size_in; ++j)
            result.push_back(samples[i][j].value);
    return result;
}

std::vector<std::vector<ParameterSample>> QSpecScan::applyQResolution() const {
    if (m_q_res_cache.empty())
        m_q_res_cache = m_resolution->generateSamples(m_qs->binCenters());
    return m_q_res_cache;
}
