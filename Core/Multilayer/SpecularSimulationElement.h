// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularSimulationElement.h
//! @brief     Declares the class SpecularSimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_SPECULARSIMULATIONELEMENT_H
#define BORNAGAIN_CORE_MULTILAYER_SPECULARSIMULATIONELEMENT_H

#include "Core/Basics/Complex.h"
#include "Core/SimulationElement/PolarizationHandler.h"
#include "Core/Vector/Vectors3D.h"
#include <memory>
#include <vector>

class IKzComputation;
class MultiLayer;
class Slice;

//! Data stucture containing both input and output of a single image pixel
//! for specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulationElement
{
public:
    SpecularSimulationElement(double kz);
    SpecularSimulationElement(double wavelength, double alpha);

    SpecularSimulationElement(const SpecularSimulationElement& other);
    SpecularSimulationElement(SpecularSimulationElement&& other) noexcept;

    ~SpecularSimulationElement();

    SpecularSimulationElement& operator=(const SpecularSimulationElement& other);

    //! Assigns PolarizationHandler.
    void setPolarizationHandler(PolarizationHandler handler);

    //! Returns assigned PolarizationHandler.
    const PolarizationHandler& polarizationHandler() const { return m_polarization; }

    double getIntensity() const { return m_intensity; }
    void setIntensity(double intensity) { m_intensity = intensity; }

    //! Set calculation flag (if it's false, zero intensity is assigned to the element)
    void setCalculationFlag(bool calculation_flag) { m_calculation_flag = calculation_flag; }
    bool isCalculated() const { return m_calculation_flag; }

    //! Returns kz values for Abeles computation of reflection/transition coefficients
    std::vector<complex_t> produceKz(const std::vector<Slice>& slices);

private:
    void swapContent(SpecularSimulationElement& other);

    PolarizationHandler m_polarization;
    double m_intensity; //!< simulated intensity for detector cell
    bool m_calculation_flag;
    std::function<std::vector<complex_t>(const std::vector<Slice>&)> m_kz_computation;
};

#endif // BORNAGAIN_CORE_MULTILAYER_SPECULARSIMULATIONELEMENT_H
