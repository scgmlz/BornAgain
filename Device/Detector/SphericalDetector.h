//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/SphericalDetector.h
//! @brief     Defines class SphericalDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_DETECTOR_SPHERICALDETECTOR_H
#define BORNAGAIN_DEVICE_DETECTOR_SPHERICALDETECTOR_H

#include "Device/Detector/IDetector2D.h"

class IPixel;
class SphericalPixel;

//! A spherical detector with axes and resolution function.
//! @ingroup detector

class SphericalDetector : public IDetector2D {
public:
    SphericalDetector();

    //! Spherical detector constructor using angle ranges
    //! @param n_phi number of phi-axis bins
    //! @param phi_min low edge of first phi-bin
    //! @param phi_max upper edge of last phi-bin
    //! @param n_alpha number of alpha-axis bins
    //! @param alpha_min low edge of first alpha-bin
    //! @param alpha_max upper edge of last alpha-bin
    SphericalDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha,
                      double alpha_min, double alpha_max);

    //! Spherical detector constructor with quadratic angle ranges
    //! @param n_bin number of bins per direction
    //! @param width angular width
    //! @param phi   central phi angle
    //! @param alpha central alpha angle
    SphericalDetector(size_t n_bin, double width, double phi, double alpha);

    SphericalDetector(const SphericalDetector& other);

    SphericalDetector* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    ~SphericalDetector() override {}

    //! return default axes units
    Axes::Units defaultAxesUnits() const override;

protected:
    //! Creates an IPixel for the given OutputData object and index
    IPixel* createPixel(size_t index) const override;

    //! Returns the name for the axis with given index
    std::string axisName(size_t index) const override;

    //! Returns index of pixel that contains the specular wavevector.
    //! If no pixel contains this specular wavevector, the number of pixels is
    //! returned. This corresponds to an overflow index.
    size_t indexOfSpecular(const Beam& beam) const override;
};

#endif // BORNAGAIN_DEVICE_DETECTOR_SPHERICALDETECTOR_H
