// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SphericalDetector.h
//! @brief     Defines class SphericalDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTOR_H
#define SPHERICALDETECTOR_H

#include "IDetector2D.h"
#include "IPixelMap.h"

//! A spherical detector with axes and resolution function.
//! SphericalDetector
//! @ingroup simulation

class BA_CORE_API_ SphericalDetector : public IDetector2D
{
public:
    SphericalDetector();

    //! Spherical detector constructor using angle ranges
    //! @param n_phi number of phi-axis bins
    //! @param phi_min low edge of first phi-bin
    //! @param phi_max upper edge of last phi-bin
    //! @param n_alpha number of alpha-axis bins
    //! @param alpha_min low edge of first alpha-bin
    //! @param alpha_max upper edge of last alpha-bin
    SphericalDetector(
        size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min,
        double alpha_max);

    SphericalDetector(const SphericalDetector& other);

    SphericalDetector* clone() const override;

    ~SphericalDetector() override {}

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const override;

    //! returns vector of valid axes units
    std::vector<EAxesUnits> getValidAxesUnits() const override;

    //! return default axes units
    EAxesUnits getDefaultAxesUnits() const override;

protected:
    //! Create an IPixelMap for the given OutputData object and index
    IPixelMap* createPixelMap(size_t index) const override;

    void print(std::ostream& ostr) const override;

    //! Registers some class members for later access via parameter pool.
    void init_parameters() override {}

    //! Generates an axis with correct name and default binning for given index
    IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const override;

    //! Calculates axis range from original detector axes in given units (mm, rad, etc)
    virtual void calculateAxisRange(
        size_t axis_index, const Beam& beam, EAxesUnits units, double& amin,
        double& amax) const override;

    //! Returns the name for the axis with given index
    std::string getAxisName(size_t index) const override;

    //! Returns index of pixel that contains the specular wavevector.
    //! If no pixel contains this specular wavevector, the number of pixels is
    //! returned. This corresponds to an overflow index.
    size_t getIndexOfSpecular(const Beam& beam) const override;
};

class AngularPixelMap : public IPixelMap
{
public:
    AngularPixelMap(Bin1D alpha_bin, Bin1D phi_bin);
    virtual ~AngularPixelMap() {}

    AngularPixelMap* clone() const override;
    AngularPixelMap* createZeroSizeMap(double x, double y) const override;
    kvector_t getK(double x, double y, double wavelength) const override;
    double getIntegrationFactor(double x, double y) const override;
    double getSolidAngle() const override;

private:
    double m_alpha, m_phi;
    double m_dalpha, m_dphi;
    double m_solid_angle;
};

#endif // SPHERICALDETECTOR_H
