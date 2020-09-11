// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/IUnitConverter.h
//! @brief     Defines interface IUnitConverter and possible axis units.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INTENSITY_IUNITCONVERTER_H
#define BORNAGAIN_CORE_INTENSITY_IUNITCONVERTER_H

#include "Core/Basics/ICloneable.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class IAxis;
template <class T> class OutputData;

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup detector

// workaround for SWIG (instead of just writing enum class AxesUnits...)
struct BA_CORE_API_ AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QSPACE, QXQY, RQ4 };
#ifndef SWIG
    // TODO: to automatize enum to string convertion, one can possibly use this solution
    // https://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
    static std::string unitName(AxesUnits unit);
#endif
};
typedef AxesUnitsWrap::AxesUnits AxesUnits;

//! Interface to provide axis translations to different units for simulation output
//! @ingroup simulation_internal

class BA_CORE_API_ IUnitConverter : public ICloneable
{
public:
    virtual ~IUnitConverter();

    virtual IUnitConverter* clone() const = 0;

    virtual size_t dimension() const = 0;

    virtual double calculateMin(size_t i_axis, AxesUnits units_type) const = 0;
    virtual double calculateMax(size_t i_axis, AxesUnits units_type) const = 0;
    virtual size_t axisSize(size_t i_axis) const = 0;

    std::string axisName(size_t i_axis, AxesUnits units_type = AxesUnits::DEFAULT) const;

    virtual std::vector<AxesUnits> availableUnits() const = 0;
    virtual AxesUnits defaultUnits() const = 0;
    AxesUnits substituteDefaultUnits(AxesUnits units) const;

#ifndef SWIG
    virtual std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, AxesUnits units) const = 0;

    //! Creates OutputData array in converter units.
    virtual std::unique_ptr<OutputData<double>> createConvertedData(const OutputData<double>& data,
                                                                    AxesUnits units) const;
#endif // SWIG

protected:
    void checkIndex(size_t i_axis) const;
#ifndef SWIG
    [[noreturn]] void throwUnitsError(std::string method, std::vector<AxesUnits> available) const;
#endif // SWIG

private:
    virtual std::vector<std::map<AxesUnits, std::string>> createNameMaps() const = 0;
};

#endif // BORNAGAIN_CORE_INTENSITY_IUNITCONVERTER_H
