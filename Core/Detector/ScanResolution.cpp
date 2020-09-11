// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/ScanResolution.cpp
//! @brief     Implements scan resolution class and derived ones.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/ScanResolution.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Core/Tools/PyFmt.h"

namespace
{
void checkIfEmpty(const std::vector<double>& input);
std::string printDeltas(const std::vector<double>& deltas);

const std::string relative_resolution = "ScanRelativeResolution";
const std::string absolute_resolution = "ScanAbsoluteResolution";

class ScanSingleRelativeResolution : public ScanResolution
{
public:
    ScanSingleRelativeResolution(const RangedDistribution& distr, double reldev)
        : ScanResolution(distr), m_reldev(reldev)
    {
    }
    ~ScanSingleRelativeResolution() override = default;

    ScanResolution* clone() const override
    {
        return new ScanSingleRelativeResolution(*distribution(), m_reldev);
    }

    DistrOutput generateSamples(double mean, size_t n_times) const override;
    DistrOutput generateSamples(const std::vector<double>& mean) const override;
    std::vector<double> stdDevs(double mean, size_t n_times) const override;
    std::vector<double> stdDevs(const std::vector<double>& mean) const override;

protected:
    std::string name() const override { return relative_resolution; }
    std::string printStdDevs() const override { return pyfmt::printDouble(m_reldev); }

private:
    double m_reldev; //!< deltas for computing resolutions
};

class ScanSingleAbsoluteResolution : public ScanResolution
{
public:
    ScanSingleAbsoluteResolution(const RangedDistribution& distr, double stddev)
        : ScanResolution(distr), m_stddev(stddev)
    {
    }
    ~ScanSingleAbsoluteResolution() override = default;

    ScanResolution* clone() const override
    {
        return new ScanSingleAbsoluteResolution(*distribution(), m_stddev);
    }

    DistrOutput generateSamples(double mean, size_t n_times) const override;
    DistrOutput generateSamples(const std::vector<double>& mean) const override;
    std::vector<double> stdDevs(double mean, size_t n_times) const override;
    std::vector<double> stdDevs(const std::vector<double>& mean) const override;

protected:
    std::string name() const override { return absolute_resolution; }
    std::string printStdDevs() const override { return pyfmt::printDouble(m_stddev); }

private:
    double m_stddev; //!< deltas for computing resolutions
};

class ScanVectorRelativeResolution : public ScanResolution
{
public:
    ScanVectorRelativeResolution(const RangedDistribution& distr, const std::vector<double>& reldev)
        : ScanResolution(distr), m_reldev(reldev)
    {
        checkIfEmpty(m_reldev);
    }
    ~ScanVectorRelativeResolution() override = default;

    ScanResolution* clone() const override
    {
        return new ScanVectorRelativeResolution(*distribution(), m_reldev);
    }

    DistrOutput generateSamples(double mean, size_t n_times) const override;
    DistrOutput generateSamples(const std::vector<double>& mean) const override;
    std::vector<double> stdDevs(double mean, size_t n_times) const override;
    std::vector<double> stdDevs(const std::vector<double>& mean) const override;

protected:
    std::string name() const override { return relative_resolution; }
    std::string printStdDevs() const override { return printDeltas(m_reldev); }

private:
    std::vector<double> m_reldev; //!< deltas for computing resolutions
};

class ScanVectorAbsoluteResolution : public ScanResolution
{
public:
    ScanVectorAbsoluteResolution(const RangedDistribution& distr, const std::vector<double>& stddev)
        : ScanResolution(distr), m_stddev(stddev)
    {
        checkIfEmpty(m_stddev);
    }
    ~ScanVectorAbsoluteResolution() override = default;

    ScanResolution* clone() const override
    {
        return new ScanVectorAbsoluteResolution(*distribution(), m_stddev);
    }

    DistrOutput generateSamples(double mean, size_t n_times) const override;
    DistrOutput generateSamples(const std::vector<double>& mean) const override;
    std::vector<double> stdDevs(double mean, size_t n_times) const override;
    std::vector<double> stdDevs(const std::vector<double>& mean) const override;

protected:
    std::string name() const override { return absolute_resolution; }
    std::string printStdDevs() const override { return printDeltas(m_stddev); }

private:
    std::vector<double> m_stddev; //!< deltas for computing resolutions
};

class ScanEmptyResolution : public ScanResolution
{
public:
    ScanEmptyResolution() : ScanResolution() {}

    ~ScanEmptyResolution() override = default;

    ScanResolution* clone() const override { return new ScanEmptyResolution(); }

    DistrOutput generateSamples(double mean, size_t n_times) const override;
    DistrOutput generateSamples(const std::vector<double>& mean) const override;
    std::vector<double> stdDevs(double mean, size_t n_times) const override;
    std::vector<double> stdDevs(const std::vector<double>& mean) const override;

protected:
    std::string name() const override;
    std::string printStdDevs() const override;
};
} // namespace

ScanResolution::~ScanResolution() = default;

ScanResolution* ScanResolution::scanRelativeResolution(const RangedDistribution& distr,
                                                       double stddev)
{
    return new ScanSingleRelativeResolution(distr, stddev);
}

ScanResolution* ScanResolution::scanRelativeResolution(const RangedDistribution& distr,
                                                       const std::vector<double>& stddevs)
{
    return new ScanVectorRelativeResolution(distr, stddevs);
}

ScanResolution* ScanResolution::scanAbsoluteResolution(const RangedDistribution& distr,
                                                       double stddev)
{
    return new ScanSingleAbsoluteResolution(distr, stddev);
}

ScanResolution* ScanResolution::scanAbsoluteResolution(const RangedDistribution& distr,
                                                       const std::vector<double>& stddevs)
{
    return new ScanVectorAbsoluteResolution(distr, stddevs);
}

ScanResolution* ScanResolution::scanEmptyResolution()
{
    return new ScanEmptyResolution();
}

size_t ScanResolution::nSamples() const
{
    if (m_distr)
        return m_distr->nSamples();
    return 1;
}

std::string ScanResolution::print() const
{
    std::stringstream result;
    result << *m_distr << "\n";
    result << pyfmt::indent() << "resolution = ";
    result << "ba." << name();
    result << "("
           << "distribution"
           << ", ";
    result << printStdDevs();
    result << ")";
    return result.str();
}

ScanResolution::ScanResolution() {}

ScanResolution::ScanResolution(const RangedDistribution& distr) : m_distr(distr.clone()) {}

namespace
{
ScanResolution::DistrOutput ScanSingleRelativeResolution::generateSamples(double mean,
                                                                          size_t n_times) const
{
    const double stddev = mean * m_reldev;
    return DistrOutput(n_times, distribution()->generateSamples(mean, stddev));
}

ScanResolution::DistrOutput
ScanSingleRelativeResolution::generateSamples(const std::vector<double>& mean) const
{
    checkIfEmpty(mean);
    DistrOutput result;
    result.reserve(mean.size());
    for (size_t i = 0, size = mean.size(); i < size; ++i)
        result.push_back(distribution()->generateSamples(mean[i], mean[i] * m_reldev));
    return result;
}

std::vector<double> ScanSingleRelativeResolution::stdDevs(double mean, size_t n_times) const
{
    return std::vector<double>(n_times, mean * m_reldev);
}

std::vector<double> ScanSingleRelativeResolution::stdDevs(const std::vector<double>& mean) const
{
    checkIfEmpty(mean);
    std::vector<double> result;
    result.reserve(mean.size());
    for (size_t i = 0, size = mean.size(); i < size; ++i)
        result.push_back(mean[i] * m_reldev);
    return result;
}

ScanResolution::DistrOutput ScanVectorRelativeResolution::generateSamples(double mean,
                                                                          size_t n_times) const
{
    return generateSamples(std::vector<double>(n_times, mean));
}

ScanResolution::DistrOutput
ScanVectorRelativeResolution::generateSamples(const std::vector<double>& mean) const
{
    const std::vector<double> stddevs = stdDevs(mean);
    return distribution()->generateSamples(mean, stddevs);
}

std::vector<double> ScanVectorRelativeResolution::stdDevs(double mean, size_t n_times) const
{
    return stdDevs(std::vector<double>(n_times, mean));
}

std::vector<double> ScanVectorRelativeResolution::stdDevs(const std::vector<double>& mean) const
{
    const size_t result_size = mean.size();
    if (result_size != m_reldev.size())
        throw std::runtime_error(
            "Error in ScanVectorRelativeResolution::stdDevs: passed mean values vector "
            "size shall be of the same size with relative deviations vector");

    std::vector<double> stddevs(result_size);
    for (size_t i = 0; i < result_size; ++i)
        stddevs[i] = m_reldev[i] * mean[i];
    return stddevs;
}

ScanResolution::DistrOutput ScanSingleAbsoluteResolution::generateSamples(double mean,
                                                                          size_t n_times) const
{
    return DistrOutput(n_times, distribution()->generateSamples(mean, m_stddev));
}

ScanResolution::DistrOutput
ScanSingleAbsoluteResolution::generateSamples(const std::vector<double>& mean) const
{
    checkIfEmpty(mean);
    DistrOutput result;
    result.reserve(mean.size());
    for (size_t i = 0, size = mean.size(); i < size; ++i)
        result.push_back(distribution()->generateSamples(mean[i], m_stddev));
    return result;
}

std::vector<double> ScanSingleAbsoluteResolution::stdDevs(double, size_t n_times) const
{
    return std::vector<double>(n_times, m_stddev);
}

std::vector<double> ScanSingleAbsoluteResolution::stdDevs(const std::vector<double>& mean) const
{
    checkIfEmpty(mean);
    return std::vector<double>(mean.size(), m_stddev);
}

ScanResolution::DistrOutput ScanVectorAbsoluteResolution::generateSamples(double mean,
                                                                          size_t n_times) const
{
    return generateSamples(std::vector<double>(n_times, mean));
}

ScanResolution::DistrOutput
ScanVectorAbsoluteResolution::generateSamples(const std::vector<double>& mean) const
{
    const size_t result_size = mean.size();
    if (result_size != m_stddev.size())
        throw std::runtime_error(
            "Error in ScanVectorAbsoluteResolution::generateSamples: passed mean values vector "
            "size shall be of the same size with standard deviations vector");
    return distribution()->generateSamples(mean, m_stddev);
}

std::vector<double> ScanVectorAbsoluteResolution::stdDevs(double mean, size_t n_times) const
{
    return stdDevs(std::vector<double>(n_times, mean));
}

std::vector<double> ScanVectorAbsoluteResolution::stdDevs(const std::vector<double>& mean) const
{
    const size_t result_size = mean.size();
    if (result_size != m_stddev.size())
        throw std::runtime_error(
            "Error in ScanVectorAbsoluteResolution::generateSamples: passed mean values vector "
            "size shall be of the same size with standard deviations vector");
    return m_stddev;
}

ScanEmptyResolution::DistrOutput ScanEmptyResolution::generateSamples(double mean,
                                                                      size_t n_times) const
{
    return DistrOutput(n_times, std::vector<ParameterSample>{ParameterSample(mean, 1.)});
}

ScanEmptyResolution::DistrOutput
ScanEmptyResolution::generateSamples(const std::vector<double>& mean) const
{
    DistrOutput result;
    result.reserve(mean.size());
    for (size_t i = 0, size = mean.size(); i < size; ++i)
        result.push_back({ParameterSample(mean[i], 1.0)});
    return result;
}

std::vector<double> ScanEmptyResolution::stdDevs(double, size_t n_times) const
{
    return std::vector<double>(n_times, 0.0);
}

std::vector<double> ScanEmptyResolution::stdDevs(const std::vector<double>& mean) const
{
    return std::vector<double>(mean.size(), 0.0);
}

std::string ScanEmptyResolution::name() const
{
    throw std::runtime_error(
        "Error in ScanEmptyResolution::name: attempt to get a name of an empty resolution object.");
}

std::string ScanEmptyResolution::printStdDevs() const
{
    throw std::runtime_error("Error in ScanEmptyResolution::printStdDevs: attempt to print data "
                             "from empty resolution object.");
}

std::string printDeltas(const std::vector<double>&)
{
    throw std::runtime_error("Error in printDeltas: function is not implemented");
}

void checkIfEmpty(const std::vector<double>& input)
{
    if (input.empty())
        throw std::runtime_error("Error in ScanResolution: passed vector is empty");
}
} // namespace
