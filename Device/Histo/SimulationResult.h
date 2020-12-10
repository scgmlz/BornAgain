//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/SimulationResult.h
//! @brief     Defines class SimulationResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_HISTO_SIMULATIONRESULT_H
#define BORNAGAIN_DEVICE_HISTO_SIMULATIONRESULT_H

#include "Base/Py/PyObject.h"
#include "Device/Unit/IUnitConverter.h"
#include <memory>
#include <vector>

class Histogram1D;
class Histogram2D;
class IAxis;
template <class T> class OutputData;

//! Information about an axis in specific units. Can be used for plotting.
//! @ingroup detector

struct AxisInfo {
    std::string m_name;
    double m_min;
    double m_max;
};

//! Wrapper around OutputData<double> that also provides unit conversions.
//! @ingroup detector

class SimulationResult {
public:
    SimulationResult() = default;
    SimulationResult(const OutputData<double>& data, const IUnitConverter& unit_converter);

    SimulationResult(const SimulationResult& other);
    SimulationResult(SimulationResult&& other);

    SimulationResult& operator=(const SimulationResult& other);
    SimulationResult& operator=(SimulationResult&& other);

#ifndef SWIG
    std::unique_ptr<OutputData<double>> data(Axes::Units units = Axes::Units::DEFAULT) const;
#endif

    Histogram2D* histogram2d(Axes::Units units = Axes::Units::DEFAULT) const;

    //! Provide AxisInfo for each axis and the given units
    std::vector<AxisInfo> axisInfo(Axes::Units units = Axes::Units::DEFAULT) const;

    //! Returns underlying unit converter
    const IUnitConverter& converter() const;

    //! Data element access
    double& operator[](size_t i);
    const double& operator[](size_t i) const;
    size_t size() const;
    double max() const;
    bool empty() const { return size() == 0; }

    //! returns intensity data as Python numpy array
#ifdef BORNAGAIN_PYTHON
    PyObject* array(Axes::Units units = Axes::Units::DEFAULT) const;
#endif

    std::vector<double> axis(Axes::Units units = Axes::Units::DEFAULT) const;

    //! Returns axis coordinates as a numpy array. With no parameters given
    //! returns coordinates of x-axis in default units.
    std::vector<double> axis(size_t i_axis, Axes::Units units = Axes::Units::DEFAULT) const;

private:
    void checkDimensions() const;

    std::unique_ptr<OutputData<double>> m_data;
    std::unique_ptr<IUnitConverter> m_unit_converter;
};

#endif // BORNAGAIN_DEVICE_HISTO_SIMULATIONRESULT_H
