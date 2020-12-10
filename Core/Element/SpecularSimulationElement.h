//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Element/SpecularSimulationElement.h
//! @brief     Declares the class SpecularSimulationElement.
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
#ifndef BORNAGAIN_CORE_ELEMENT_SPECULARSIMULATIONELEMENT_H
#define BORNAGAIN_CORE_ELEMENT_SPECULARSIMULATIONELEMENT_H

#include "Base/Pixel/PolarizationHandler.h"
#include "Base/Types/Complex.h"
#include "Base/Vector/Vectors3D.h"
#include <memory>
#include <vector>

class Instrument;
class Slice;

//! Data stucture containing both input and output of a single image pixel for specular simulation.
//! @ingroup simulation

class SpecularSimulationElement {
public:
    SpecularSimulationElement(double kz, const Instrument& instrument, bool computable);
    SpecularSimulationElement(double wavelength, double alpha, const Instrument& instrument,
                              bool computable);

    SpecularSimulationElement(const SpecularSimulationElement& other);
    SpecularSimulationElement(SpecularSimulationElement&& other) noexcept;

    ~SpecularSimulationElement();

    SpecularSimulationElement& operator=(const SpecularSimulationElement& other) = delete;

    //! Returns assigned PolarizationHandler.
    const PolarizationHandler& polarizationHandler() const { return m_polarization; }

    double intensity() const { return m_intensity; }
    void setIntensity(double intensity) { m_intensity = intensity; }

    //! Returns calculation flag (if it's false, zero intensity is assigned to the element)
    bool isCalculated() const { return m_computable; }

    //! Returns kz values for Abeles computation of reflection/transition coefficients
    std::vector<complex_t> produceKz(const std::vector<Slice>& slices);

private:
    const PolarizationHandler m_polarization;
    double m_intensity; //!< simulated intensity for detector cell
    const bool m_computable;
    const std::function<std::vector<complex_t>(const std::vector<Slice>&)> m_kz_computation;
};

#endif // BORNAGAIN_CORE_ELEMENT_SPECULARSIMULATIONELEMENT_H
#endif // USER_API
