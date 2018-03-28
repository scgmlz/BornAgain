// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IFresnelMap.h
//! @brief     Defines class IFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IFRESNELMAP_H
#define IFRESNELMAP_H

#include "WinDllMacros.h"
#include <cstddef>
#include <memory>

template<class T> class BasicVector3D;
class ILayerRTCoefficients;
class MultiLayer;
class SimulationElement;
class SpecularSimulationElement;

typedef BasicVector3D<double> kvector_t;

//! Holds the necessary information to calculate the radiation wavefunction in every layer
//! for different incoming (outgoing) angles of the beam in the top layer
//! (these amplitudes correspond to the specular part of the wavefunction).
//! @ingroup algorithms_internal

class BA_CORE_API_ IFresnelMap
{
public:
    IFresnelMap();
    virtual ~IFresnelMap();

    //! Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector.
    virtual std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const = 0;

    //! Retrieves the amplitude coefficients for an incoming wavevector.
    template <typename T>
    std::unique_ptr<const ILayerRTCoefficients> getInCoefficients(const T& sim_element,
                                                                  size_t layer_index) const
    {
        return getCoefficients(sim_element.getKi(), layer_index);
    }

    //! Fills simulation element specular data
    virtual void fillSpecularData(SpecularSimulationElement& sim_element) const = 0;

    //! Sets the multilayer to be used for the Fresnel calculations.
    virtual void setMultilayer(const MultiLayer& multilayer);

    //! Disables caching of previously computed Fresnel coefficients
    void disableCaching();

protected:
    virtual std::unique_ptr<const ILayerRTCoefficients>
    getCoefficients(const kvector_t& kvec, size_t layer_index) const = 0;

    bool m_use_cache;
    std::unique_ptr<MultiLayer> mP_multilayer;
};

#endif // IFRESNELMAP_H
