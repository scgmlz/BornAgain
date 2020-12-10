//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Unit/IUnitConverter.h
//! @brief     Defines interface IUnitConverter and possible axis units.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_UNIT_IUNITCONVERTER_H
#define BORNAGAIN_DEVICE_UNIT_IUNITCONVERTER_H

#include "Base/Types/ICloneable.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class IAxis;
template <class T> class OutputData;

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup detector

class Axes {
public:
    enum Units { DEFAULT, NBINS, RADIANS, DEGREES, MM, QSPACE, QXQY, RQ4 };
};

const std::map<Axes::Units, const char*> axisUnitLabel = {
    {Axes::Units::DEFAULT, "undefined"}, {Axes::Units::NBINS, "bin"}, {Axes::Units::RADIANS, "rad"},
    {Axes::Units::DEGREES, "deg"},       {Axes::Units::MM, "mm"},     {Axes::Units::QSPACE, "1/nm"},
    {Axes::Units::QXQY, "1/nm"},         {Axes::Units::RQ4, "nm^-4?"}};

//! Interface to provide axis translations to different units for simulation output
//! @ingroup simulation_internal

class IUnitConverter : public ICloneable {
public:
    virtual ~IUnitConverter();

    virtual IUnitConverter* clone() const = 0;

    virtual size_t dimension() const = 0;

    virtual double calculateMin(size_t i_axis, Axes::Units units_type) const = 0;
    virtual double calculateMax(size_t i_axis, Axes::Units units_type) const = 0;
    virtual size_t axisSize(size_t i_axis) const = 0;

    std::string axisName(size_t i_axis, Axes::Units units_type = Axes::Units::DEFAULT) const;

    virtual std::vector<Axes::Units> availableUnits() const = 0;
    virtual Axes::Units defaultUnits() const = 0;
    Axes::Units substituteDefaultUnits(Axes::Units units) const;

#ifndef SWIG
    virtual std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, Axes::Units units) const = 0;

    //! Creates OutputData array in converter units.
    virtual std::unique_ptr<OutputData<double>> createConvertedData(const OutputData<double>& data,
                                                                    Axes::Units units) const;
#endif // USER_API

protected:
    void checkIndex(size_t i_axis) const;
#ifndef SWIG
    [[noreturn]] void throwUnitsError(std::string method, std::vector<Axes::Units> available) const;
#endif // USER_API

private:
    virtual std::vector<std::map<Axes::Units, std::string>> createNameMaps() const = 0;
};

#endif // BORNAGAIN_DEVICE_UNIT_IUNITCONVERTER_H
