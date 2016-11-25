// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ISpecularInfoMap.h
//! @brief     Defines and implements interface ISpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISPECULARINFOMAP_H
#define ISPECULARINFOMAP_H

#include "WinDllMacros.h"

class ILayerRTCoefficients;
class SimulationElement;

//! Interface class providing access to the reflection and transmittion coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ ISpecularInfoMap
{
public:
    ISpecularInfoMap() {}
    ISpecularInfoMap(const ISpecularInfoMap& other) = delete;
    virtual ~ISpecularInfoMap() {}
    ISpecularInfoMap& operator=(const ISpecularInfoMap& other) = delete;

    virtual ISpecularInfoMap* clone() const = 0;

    //! Retrieves the amplitude coefficients for the given angles
    virtual const ILayerRTCoefficients*
    getOutCoefficients(const SimulationElement& sim_element) const = 0;

    //! Retrieves the amplitude coefficients for the given angles
    virtual const ILayerRTCoefficients*
    getInCoefficients(const SimulationElement& sim_element) const = 0;
};

#endif // ISPECULARINFOMAP_H
