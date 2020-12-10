//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/IsGISAXSDetector.h
//! @brief     Defines class IsGISAXSDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_DETECTOR_ISGISAXSDETECTOR_H
#define BORNAGAIN_DEVICE_DETECTOR_ISGISAXSDETECTOR_H

#include "Device/Detector/SphericalDetector.h"

//! A spherical detector used for validation with IsGISAXS results.
//! @ingroup detector

class IsGISAXSDetector : public SphericalDetector {
public:
    IsGISAXSDetector();
    IsGISAXSDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min,
                     double alpha_max);
    IsGISAXSDetector(const IsGISAXSDetector& other);

    IsGISAXSDetector* clone() const override;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

protected:
    //! Generates an axis with correct name and default binning for given index
    std::unique_ptr<IAxis> createAxis(size_t index, size_t n_bins, double min,
                                      double max) const override;

    //! Returns index of pixel that contains the specular wavevector.
    //! If no pixel contains this specular wavevector, the number of pixels is
    //! returned. This corresponds to an overflow index.
    size_t indexOfSpecular(const Beam& beam) const override;
};

#endif // BORNAGAIN_DEVICE_DETECTOR_ISGISAXSDETECTOR_H
