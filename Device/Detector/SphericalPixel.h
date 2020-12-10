//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/SphericalPixel.h
//! @brief     Defines class SphericalPixel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_DETECTOR_SPHERICALPIXEL_H
#define BORNAGAIN_DEVICE_DETECTOR_SPHERICALPIXEL_H

#include "Base/Pixel/IPixel.h"

struct Bin1D;

//! A pixel in a SphericalDetector

class SphericalPixel : public IPixel {
public:
    SphericalPixel(const Bin1D& alpha_bin, const Bin1D& phi_bin);

    SphericalPixel* clone() const override;
    SphericalPixel* createZeroSizePixel(double x, double y) const override;
    kvector_t getK(double x, double y, double wavelength) const override;
    double integrationFactor(double x, double y) const override;
    double solidAngle() const override;

private:
    const double m_alpha;
    const double m_phi;
    const double m_dalpha;
    const double m_dphi;
    mutable double m_solid_angle;
};

#endif // BORNAGAIN_DEVICE_DETECTOR_SPHERICALPIXEL_H
#endif // USER_API
