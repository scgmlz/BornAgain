//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Pixel/SimulationElement.h
//! @brief     Defines class SimulationElement.
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
#ifndef BORNAGAIN_BASE_PIXEL_SIMULATIONELEMENT_H
#define BORNAGAIN_BASE_PIXEL_SIMULATIONELEMENT_H

#include "Base/Pixel/PolarizationHandler.h"
#include "Base/Types/Complex.h"
#include "Base/Vector/Vectors3D.h"
#include <memory>

class IPixel;

//! Data stucture containing both input and output of a single detector cell.
//! @ingroup simulation

class SimulationElement {
public:
    SimulationElement() = delete;
    SimulationElement(double wavelength, double alpha_i, double phi_i,
                      std::unique_ptr<IPixel> pixel, const Eigen::Matrix2cd& beam_polarization,
                      const Eigen::Matrix2cd& analyzer, bool isSpecular_);
    SimulationElement(const SimulationElement& other);
    SimulationElement(SimulationElement&& other);
    SimulationElement& operator=(const SimulationElement&) = delete;
    ~SimulationElement();

    //! Returns copy of this SimulationElement with k_f given by in-pixel coordinate x,y.
    SimulationElement pointElement(double x, double y) const;

    //! Returns assigned PolarizationHandler
    const PolarizationHandler& polarizationHandler() const { return m_polarization; }

    double wavelength() const { return m_wavelength; }
    double getAlphaI() const { return m_alpha_i; }
    double getPhiI() const { return m_phi_i; }
    double getAlphaMean() const { return getAlpha(0.5, 0.5); }
    double getPhiMean() const { return getPhi(0.5, 0.5); }
    void setIntensity(double intensity) { m_intensity = intensity; }
    void addIntensity(double intensity) { m_intensity += intensity; }
    double intensity() const { return m_intensity; }
    kvector_t getKi() const;
    kvector_t getMeanKf() const;
    kvector_t meanQ() const;
    kvector_t getQ(double x, double y) const;

    double integrationFactor(double x, double y) const;

    double solidAngle() const;

    double getAlpha(double x, double y) const;
    double getPhi(double x, double y) const;

    //! Tells if simulation element corresponds to a specular peak
    bool isSpecular() const { return m_is_specular; }

private:
    kvector_t getKf(double x, double y) const;

    const PolarizationHandler m_polarization;
    const double m_wavelength; //!< wavelength of beam
    const double m_alpha_i;    //!< incident grazing angle
    const double m_phi_i;      //!< incident angle in xy plane
    const kvector_t m_k_i;     //!< cached value of k_i
    const kvector_t m_mean_kf; //!< cached value of mean_kf
    mutable std::unique_ptr<IPixel> m_pixel;
    const bool m_is_specular;
    double m_intensity; //!< simulated intensity for detector cell
};

#endif // BORNAGAIN_BASE_PIXEL_SIMULATIONELEMENT_H
#endif // USER_API
