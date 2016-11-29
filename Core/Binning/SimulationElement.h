// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/SimulationElement.h
//! @brief     Defines class SimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONELEMENT_H
#define SIMULATIONELEMENT_H

#include "Complex.h"
#include "EigenCore.h"
#include "Vectors3D.h"
#include "IPixelMap.h"
#include <memory>
#include <vector>

class IPixelMap;

//! Data stucture containing both input and output of a single detector cell.
//! @ingroup simulation

class BA_CORE_API_ SimulationElement
{
public:
    SimulationElement(double wavelength, double alpha_i, double phi_i,
                      std::unique_ptr<IPixelMap> pixelmap);
    SimulationElement(const SimulationElement& other);
    SimulationElement &operator=(const SimulationElement &other);

    //! Construct SimulationElement from other element and restrict k_f to specific value in
    //! the original detector pixel
    SimulationElement(const SimulationElement& other, double x, double y);

    SimulationElement(SimulationElement&& other) noexcept;

    ~SimulationElement();

#ifndef SWIG
    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd& polarization) { m_polarization = polarization; }

    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const { return m_polarization; }

    //! Sets the polarization analyzer operator (in spin basis along z-axis)
    void setAnalyzerOperator(const Eigen::Matrix2cd& polarization_operator) {
        m_analyzer_operator = polarization_operator; }

    //! Gets the polarization analyzer operator (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const { return m_analyzer_operator; }
#endif

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

    //! check if element contains given wavevector
    bool containsSpecularWavevector() const;

    //! indicate that this element contains the specular wavevector
    void setSpecular(bool contains_specular);

private:
    void swapContent(SimulationElement &other);
    void initPolarization();

    kvector_t getKf(double x, double y) const;

    double m_wavelength, m_alpha_i, m_phi_i;             //!< wavelength and angles of beam
    double m_intensity;  //!< simulated intensity for detector cell
#ifndef SWIG
    Eigen::Matrix2cd m_polarization;      //!< polarization density matrix
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
#endif
    std::unique_ptr<IPixelMap> mP_pixel_map;
    bool m_contains_specular;
};


//! Add element vector to element vector with weight
void addElementsWithWeight(std::vector<SimulationElement>::const_iterator first,
                           std::vector<SimulationElement>::const_iterator last,
                           std::vector<SimulationElement>::iterator result,
                           double weight);

//! Set all element intensities to given value
void setAllElementIntensities(std::vector<SimulationElement>::iterator first,
                              std::vector<SimulationElement>::iterator last, double intensity);

#endif // SIMULATIONELEMENT_H
