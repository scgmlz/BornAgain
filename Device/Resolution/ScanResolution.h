//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Resolution/ScanResolution.h
//! @brief     Defines scan resolution class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_RESOLUTION_SCANRESOLUTION_H
#define BORNAGAIN_DEVICE_RESOLUTION_SCANRESOLUTION_H

#include "Base/Types/ICloneable.h"
#include "Param/Varia/ParameterSample.h"
#include <memory>
#include <string>
#include <vector>

class IRangedDistribution;
class RealLimits;

//! Container for reflectivity resolution data.
class ScanResolution : public ICloneable {
protected:
    using DistrOutput = std::vector<std::vector<ParameterSample>>;

public:
    ~ScanResolution() override;
    static ScanResolution* scanRelativeResolution(const IRangedDistribution& distr, double stddev);
    static ScanResolution* scanRelativeResolution(const IRangedDistribution& distr,
                                                  const std::vector<double>& stddevs);
    static ScanResolution* scanAbsoluteResolution(const IRangedDistribution& distr, double stddev);
    static ScanResolution* scanAbsoluteResolution(const IRangedDistribution& distr,
                                                  const std::vector<double>& stddevs);
#ifndef SWIG
    static ScanResolution* scanEmptyResolution();

    ScanResolution* clone() const override = 0;
    const IRangedDistribution* distribution() const { return m_distr.get(); }
    size_t nSamples() const;

    virtual DistrOutput generateSamples(double mean, size_t n_times) const = 0;
    virtual DistrOutput generateSamples(const std::vector<double>& mean) const = 0;
    virtual std::vector<double> stdDevs(double mean, size_t n_times) const = 0;
    virtual std::vector<double> stdDevs(const std::vector<double>& mean) const = 0;
    bool empty() const { return !m_distr; }

    virtual std::string name() const = 0;
    virtual double delta() const = 0;

#endif // USER_API
protected:
    ScanResolution();
    ScanResolution(const IRangedDistribution& distr);

private:
    std::unique_ptr<IRangedDistribution> m_distr; //!< basic distribution function
};

#endif // BORNAGAIN_DEVICE_RESOLUTION_SCANRESOLUTION_H
