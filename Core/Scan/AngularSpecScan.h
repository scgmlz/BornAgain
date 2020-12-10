//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scan/AngularSpecScan.h
//! @brief     Declares AngularSpecScan class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_SCAN_ANGULARSPECSCAN_H
#define BORNAGAIN_CORE_SCAN_ANGULARSPECSCAN_H

#include "Core/Scan/ISpecularScan.h"
#include <memory>

class ParameterSample;
class IRangedDistribution;
class ScanResolution;

//! Scan type with inclination angles as coordinate values and a unique wavelength.
//! Features footprint correction.
class AngularSpecScan : public ISpecularScan {
public:
    AngularSpecScan(double wl, std::vector<double> inc_angle);
    AngularSpecScan(double wl, const IAxis& inc_angle);
    //! Sets angle-defined specular scan. The first parameter is always a wavelength in nm.
    //! Second parameter is either a numpy array of incident angles in radians or an IAxis object
    //! with angle values. Alternatively an axis can be defined in-place, then
    //! the second passed parameter is the number of bins, third - minimum on-axis angle value,
    //! fourth - maximum on-axis  angle value.
    AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max);
    ~AngularSpecScan() override;
    AngularSpecScan* clone() const override;

#ifndef SWIG
    //! Generates simulation elements for specular simulations
    std::vector<SpecularSimulationElement>
    generateSimulationElements(const Instrument& instrument) const override;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const override { return m_inc_angle.get(); }

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const override { return m_footprint.get(); }

    //! Returns footprint correction factor for a range of simulation elements of size _n_elements_
    //! and starting from element with index _i_.
    std::vector<double> footprint(size_t i, size_t n_elements) const override;

    //! Returns the number of simulation elements
    size_t numberOfSimulationElements() const override;

    //! Returns intensity vector corresponding to convolution of given simulation elements
    std::vector<double>
    createIntensities(const std::vector<SpecularSimulationElement>& sim_elements) const override;

    double wavelength() const { return m_wl; }

    // TODO: remove these getters after transition to the new resolution machinery is finished
    const ScanResolution* wavelengthResolution() const { return m_wl_resolution.get(); }
    const ScanResolution* angleResolution() const { return m_inc_resolution.get(); }
#endif // USER_API

    //! Sets footprint correction factor
    void setFootprintFactor(const IFootprintFactor* f_factor);

    //! Sets wavelength resolution values via ScanResolution object.
    void setWavelengthResolution(const ScanResolution& resolution);

    void setRelativeWavelengthResolution(const IRangedDistribution& distr, double rel_dev);
    //! Sets wavelength resolution values via IRangedDistribution and values of relative deviations
    //! (that is, _rel_dev_ equals standard deviation divided by the mean value).
    //! _rel_dev_ can be either single-valued or a numpy array. In the latter case the length of the
    //! array should coinside with the length of the inclination angle axis.
    void setRelativeWavelengthResolution(const IRangedDistribution& distr,
                                         const std::vector<double>& rel_dev);

    void setAbsoluteWavelengthResolution(const IRangedDistribution& distr, double std_dev);
    //! Sets wavelength resolution values via IRangedDistribution and values of standard deviations.
    //! _std_dev_ can be either single-valued or a numpy array. In the latter case the length of the
    //! array should coinside with the length of the inclination angle axis.
    void setAbsoluteWavelengthResolution(const IRangedDistribution& distr,
                                         const std::vector<double>& std_dev);

    //! Sets angle resolution values via ScanResolution object.
    void setAngleResolution(const ScanResolution& resolution);

    void setRelativeAngularResolution(const IRangedDistribution& distr, double rel_dev);
    //! Sets angular resolution values via IRangedDistribution and values of relative deviations
    //! (that is, _rel_dev_ equals standard deviation divided by the mean value).
    //! _rel_dev_ can be either single-valued or a numpy array. In the latter case the length of the
    //! array should coinside with the length of the inclination angle axis.
    void setRelativeAngularResolution(const IRangedDistribution& distr,
                                      const std::vector<double>& rel_dev);

    void setAbsoluteAngularResolution(const IRangedDistribution& distr, double std_dev);
    //! Sets angular resolution values via IRangedDistribution and values of standard deviations.
    //! _std_dev_ can be either single-valued or a numpy array. In the latter case the length of the
    //! array should coinside with the length of the inclination angle axis.
    void setAbsoluteAngularResolution(const IRangedDistribution& distr,
                                      const std::vector<double>& std_dev);

private:
    using DistrOutput = std::vector<std::vector<ParameterSample>>;

    void checkInitialization();
    DistrOutput applyWlResolution() const;
    DistrOutput applyIncResolution() const;

    const double m_wl;
    const std::unique_ptr<IAxis> m_inc_angle;
    std::unique_ptr<IFootprintFactor> m_footprint;

    std::unique_ptr<ScanResolution> m_wl_resolution;
    mutable DistrOutput m_wl_res_cache;

    std::unique_ptr<ScanResolution> m_inc_resolution;
    mutable DistrOutput m_inc_res_cache;
};

#endif // BORNAGAIN_CORE_SCAN_ANGULARSPECSCAN_H
