// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/ScanResolution.h
//! @brief     Defines scan resolution class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_SCANRESOLUTION_H
#define BORNAGAIN_CORE_DETECTOR_SCANRESOLUTION_H

#include "Core/Basics/ICloneable.h"
#include "Core/Parametrization/ParameterSample.h"
#include <memory>
#include <string>
#include <vector>

class RangedDistribution;
class RealLimits;

//! Container for reflectivity resolution data.
class BA_CORE_API_ ScanResolution : public ICloneable
{
protected:
    using DistrOutput = std::vector<std::vector<ParameterSample>>;

public:
    ~ScanResolution() override;
    static ScanResolution* scanRelativeResolution(const RangedDistribution& distr, double stddev);
    static ScanResolution* scanRelativeResolution(const RangedDistribution& distr,
                                                  const std::vector<double>& stddevs);
    static ScanResolution* scanAbsoluteResolution(const RangedDistribution& distr, double stddev);
    static ScanResolution* scanAbsoluteResolution(const RangedDistribution& distr,
                                                  const std::vector<double>& stddevs);
#ifndef SWIG
    static ScanResolution* scanEmptyResolution();

    ScanResolution* clone() const override = 0;
    const RangedDistribution* distribution() const { return m_distr.get(); }
    size_t nSamples() const;

    virtual DistrOutput generateSamples(double mean, size_t n_times) const = 0;
    virtual DistrOutput generateSamples(const std::vector<double>& mean) const = 0;
    virtual std::vector<double> stdDevs(double mean, size_t n_times) const = 0;
    virtual std::vector<double> stdDevs(const std::vector<double>& mean) const = 0;
    bool empty() const { return !m_distr; }

    //! Prints object definition in python format.
    std::string print() const;
#endif // SWIG
protected:
    ScanResolution();
    ScanResolution(const RangedDistribution& distr);
    virtual std::string name() const = 0;
    virtual std::string printStdDevs() const = 0;

private:
    std::unique_ptr<RangedDistribution> m_distr; //!< basic distribution function
};

inline std::ostream& operator<<(std::ostream& os, const ScanResolution& scan_resolution)
{
    return os << scan_resolution.print();
}

#endif // BORNAGAIN_CORE_DETECTOR_SCANRESOLUTION_H
