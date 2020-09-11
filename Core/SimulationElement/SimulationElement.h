// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/SimulationElement.h
//! @brief     Defines class SimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATIONELEMENT_SIMULATIONELEMENT_H
#define BORNAGAIN_CORE_SIMULATIONELEMENT_SIMULATIONELEMENT_H

#include "Core/Basics/Complex.h"
#include "Core/Binning/IPixel.h"
#include "Core/SimulationElement/PolarizationHandler.h"
#include "Core/Vector/Vectors3D.h"
#include <memory>

class IPixel;

//! Data stucture containing both input and output of a single detector cell.
//! @ingroup simulation

class BA_CORE_API_ SimulationElement
{
public:
    SimulationElement(double wavelength, double alpha_i, double phi_i,
                      std::unique_ptr<IPixel> pixel);
    SimulationElement(const SimulationElement& other);
    SimulationElement& operator=(const SimulationElement& other);

    //! Construct SimulationElement from other element and restrict k_f to specific value in
    //! the original detector pixel
    SimulationElement(const SimulationElement& other, double x, double y);

    SimulationElement(SimulationElement&& other) noexcept;

    ~SimulationElement();

    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd& polarization)
    {
        m_polarization.setPolarization(polarization);
    }

    //! Sets the polarization analyzer operator (in spin basis along z-axis)
    void setAnalyzerOperator(const Eigen::Matrix2cd& polarization_operator)
    {
        m_polarization.setAnalyzerOperator(polarization_operator);
    }

    //! Returns assigned PolarizationHandler
    const PolarizationHandler& polarizationHandler() const { return m_polarization; }

    double getWavelength() const { return m_wavelength; }
    double getAlphaI() const { return m_alpha_i; }
    double getPhiI() const { return m_phi_i; }
    double getAlphaMean() const { return getAlpha(0.5, 0.5); }
    double getPhiMean() const { return getPhi(0.5, 0.5); }
    void setIntensity(double intensity) { m_intensity = intensity; }
    void addIntensity(double intensity) { m_intensity += intensity; }
    double getIntensity() const { return m_intensity; }
    kvector_t getKi() const;
    kvector_t getMeanKf() const;
    kvector_t getMeanQ() const;
    kvector_t getQ(double x, double y) const;

    double getIntegrationFactor(double x, double y) const;

    double getSolidAngle() const;

    double getAlpha(double x, double y) const;
    double getPhi(double x, double y) const;

    //! Set specularity indication on/off.
    void setSpecular(bool is_specular) { m_is_specular = is_specular; }

    //! Tells if simulation element corresponds to a specular peak
    bool isSpecular() const { return m_is_specular; }

private:
    void swapContent(SimulationElement& other);

    kvector_t getKf(double x, double y) const;

    PolarizationHandler m_polarization;
    double m_wavelength, m_alpha_i, m_phi_i; //!< wavelength and angles of beam
    kvector_t m_k_i;                         //!< cached value of k_i
    kvector_t m_mean_kf;                     //!< cached value of mean_kf
    double m_intensity;                      //!< simulated intensity for detector cell
    std::unique_ptr<IPixel> mP_pixel;
    bool m_is_specular;
};

#endif // BORNAGAIN_CORE_SIMULATIONELEMENT_SIMULATIONELEMENT_H
