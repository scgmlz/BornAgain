// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/SphericalPixel.h
//! @brief     Defines class SphericalPixel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_SPHERICALPIXEL_H
#define BORNAGAIN_CORE_DETECTOR_SPHERICALPIXEL_H

#include "Core/Binning/IPixel.h"

struct Bin1D;

//! A pixel in a SphericalDetector

class SphericalPixel : public IPixel
{
public:
    SphericalPixel(const Bin1D& alpha_bin, const Bin1D& phi_bin);

    SphericalPixel* clone() const override;
    SphericalPixel* createZeroSizePixel(double x, double y) const override;
    kvector_t getK(double x, double y, double wavelength) const override;
    double getIntegrationFactor(double x, double y) const override;
    double getSolidAngle() const override;

private:
    double m_alpha, m_phi;
    double m_dalpha, m_dphi;
    double m_solid_angle;
};

#endif // BORNAGAIN_CORE_DETECTOR_SPHERICALPIXEL_H
