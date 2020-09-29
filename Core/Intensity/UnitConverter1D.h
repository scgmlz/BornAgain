// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/UnitConverter1D.h
//! @brief     Defines UnitConverter1D class and derived classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INTENSITY_UNITCONVERTER1D_H
#define BORNAGAIN_CORE_INTENSITY_UNITCONVERTER1D_H

#include "Core/Intensity/IUnitConverter.h"

#include <functional>

class Beam;
class ISpecularScan;
class AngularSpecScan;
class QSpecScan;

//! Conversion of axis units for the case of 1D simulation result.

class UnitConverter1D : public IUnitConverter
{
public:
    //! Factory function to create unit converter for particular type of specular data
    static std::unique_ptr<UnitConverter1D> createUnitConverter(const ISpecularScan& handler);

    ~UnitConverter1D() override = default;

    UnitConverter1D* clone() const override = 0;

    //! Returns dimensionality of converted canvas.
    size_t dimension() const override;

    //! Calculates minimum on-axis value in given units.
    double calculateMin(size_t i_axis, AxesUnits units_type) const override;

    //! Calculates maximum on-axis value in given units.
    double calculateMax(size_t i_axis, AxesUnits units_type) const override;

    //! Creates axis in converted units.
    std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, AxesUnits units) const override;

    //! Creates OutputData array in converter units.
    std::unique_ptr<OutputData<double>> createConvertedData(const OutputData<double>& data,
                                                            AxesUnits units) const override;

protected:
    //! Returns translating functional (rads --> output units)
    virtual std::function<double(double)> getTraslatorTo(AxesUnits units_type) const = 0;

    virtual const IAxis* coordinateAxis() const = 0;
};

//! Conversion of axis units for the case of conventional (angle-based) reflectometry.
class UnitConverterConvSpec : public UnitConverter1D
{
public:
    //! Constructs the object for unit conversion.
    UnitConverterConvSpec(const Beam& beam, const IAxis& axis,
                          AxesUnits axis_units = AxesUnits::RADIANS);
    UnitConverterConvSpec(const AngularSpecScan& handler);
    ~UnitConverterConvSpec() override;

    UnitConverterConvSpec* clone() const override;

    //! Returns the size of underlying axis.
    size_t axisSize(size_t i_axis) const override;

    //! Returns the list of all available units
    std::vector<AxesUnits> availableUnits() const override;

    //! Returns default units to convert to.
    AxesUnits defaultUnits() const override;

protected:
    UnitConverterConvSpec(const UnitConverterConvSpec& other);

    //! Creates name map for axis in various units
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;

    //! Returns translating functional (input units --> rads)
    std::function<double(double)> getTraslatorFrom(AxesUnits units_type) const;

    //! Returns translating functional (rads --> desired units)
    std::function<double(double)> getTraslatorTo(AxesUnits units_type) const override;

    const IAxis* coordinateAxis() const override { return m_axis.get(); }

    double m_wavelength;           //!< basic wavelength in nm (for translation to q-space).
    std::unique_ptr<IAxis> m_axis; //!< basic inclination angles (in rads).
};

//! Conversion of axis units for the case of q-defined reflectometry.
class UnitConverterQSpec : public UnitConverter1D
{
public:
    UnitConverterQSpec(const QSpecScan& handler);
    ~UnitConverterQSpec() override;

    UnitConverterQSpec* clone() const override;

    //! Returns the size of underlying axis.
    size_t axisSize(size_t i_axis) const override;

    //! Returns the list of all available units
    std::vector<AxesUnits> availableUnits() const override;

    //! Returns default units to convert to.
    AxesUnits defaultUnits() const override;

protected:
    UnitConverterQSpec(const UnitConverterQSpec& other);

    //! Creates name map for axis in various units
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;

    //! Returns translating functional (inv. nm --> desired units)
    std::function<double(double)> getTraslatorTo(AxesUnits units_type) const override;

    const IAxis* coordinateAxis() const override { return m_axis.get(); }

    std::unique_ptr<IAxis> m_axis; //!< qz values (in inv. nm).
};
#endif // BORNAGAIN_CORE_INTENSITY_UNITCONVERTER1D_H
