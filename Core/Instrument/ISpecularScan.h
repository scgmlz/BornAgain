// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISpecularScan.h
//! @brief     Declares ISpecularScan abstract class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INSTRUMENT_ISPECULARSCAN_H
#define BORNAGAIN_CORE_INSTRUMENT_ISPECULARSCAN_H

#include "Core/Basics/ICloneable.h"

#include <sstream>
#include <string>
#include <vector>

class IAxis;
class IFootprintFactor;
class SpecularSimulationElement;

//! Base abstract class for all types of specular scans.
class BA_CORE_API_ ISpecularScan : public ICloneable
{
public:
    enum SPECULAR_DATA_TYPE { angle, q };

    ISpecularScan(SPECULAR_DATA_TYPE data_type);
    ~ISpecularScan() override;
    ISpecularScan* clone() const override = 0;

#ifndef SWIG
    //! Generates simulation elements for specular simulations
    virtual std::vector<SpecularSimulationElement> generateSimulationElements() const = 0;

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

    //! Print scan definition in python format
    virtual std::string print() const = 0;
#endif // SWIG

    SPECULAR_DATA_TYPE dataType() const { return m_data_type; }

private:
    SPECULAR_DATA_TYPE m_data_type;
};

inline std::ostream& operator<<(std::ostream& os, const ISpecularScan& scan)
{
    return os << scan.print();
}
#endif // BORNAGAIN_CORE_INSTRUMENT_ISPECULARSCAN_H
