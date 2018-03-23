// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/DepthProbeElement.h
//! @brief     Defines class DepthProbeElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DEPTHPROBEELEMENT_H
#define DEPTHPROBEELEMENT_H

#include <valarray>

#include "Vectors3D.h"

class IAxis;

class BA_CORE_API_ DepthProbeElement
{
public:
    DepthProbeElement(double wavelength, double alpha_i, const IAxis* z_positions);
    DepthProbeElement(const DepthProbeElement& other);
    DepthProbeElement(DepthProbeElement&& other) noexcept;

    ~DepthProbeElement();

    DepthProbeElement& operator=(const DepthProbeElement& other);

    double getWavelength() const { return m_wavelength; }
    double getAlphaI() const { return m_alpha_i; }
    kvector_t getKi() const;

    template <typename T> void setIntensities(T&& intensities)
    {
        static_assert(
            std::is_assignable<std::valarray<double>, typename std::decay<T>::type>::value,
            "Error in DepthProbeElement::setIntensities: wrong type of input data.");
        m_intensities = std::forward<T>(intensities);
    }

    void addIntensities(const std::valarray<double>& intensities) { m_intensities += intensities; }

    const std::valarray<double>& getIntensities() const { return m_intensities; }
    const IAxis* getZPositions() const {return m_z_positions;}

    size_t size() {return m_intensities.size();}

    //! Set calculation flag (if it's false, zero intensity is assigned to the element)
    void setCalculationFlag(bool calculation_flag) {m_calculation_flag = calculation_flag;}
    bool isCalculated() const {return m_calculation_flag;}

private:
    void swapContent(DepthProbeElement& other);

    double m_wavelength, m_alpha_i;  //!< the wavelength and the incident angle of the beam
    std::valarray<double> m_intensities; //!< simulated intensity for the set of z positions
    const IAxis* m_z_positions; //!< positions (lower z corresponds to a greater depth)
    bool m_calculation_flag;
};

#endif // DEPTHPROBEELEMENT_H
