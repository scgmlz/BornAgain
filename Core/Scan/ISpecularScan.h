//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scan/ISpecularScan.h
//! @brief     Declares and implements interface ISpecularScan.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_CORE_SCAN_ISPECULARSCAN_H
#define BORNAGAIN_CORE_SCAN_ISPECULARSCAN_H

#include "Base/Types/ICloneable.h"

#include <sstream>
#include <string>
#include <vector>

class IAxis;
class IFootprintFactor;
class Instrument;
class SpecularSimulationElement;

//! Abstract base class for all types of specular scans.

class ISpecularScan : public ICloneable {
public:
    ISpecularScan* clone() const override = 0;

#ifndef SWIG
    //! Generates simulation elements for specular simulations
    virtual std::vector<SpecularSimulationElement>
    generateSimulationElements(const Instrument& instrument) const = 0;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const = 0;

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const = 0;

    //! Returns footprint correction factor for a range of simulation elements of size _n_elements_
    //! and starting from element with index _i_.
    virtual std::vector<double> footprint(size_t i, size_t n_elements) const = 0;

    //! Returns the number of simulation elements
    virtual size_t numberOfSimulationElements() const = 0;

    //! Returns intensity vector corresponding to convolution of given simulation elements
    virtual std::vector<double>
    createIntensities(const std::vector<SpecularSimulationElement>& sim_elements) const = 0;

#endif // USER_API
};

#endif // BORNAGAIN_CORE_SCAN_ISPECULARSCAN_H
#endif // USER_API
