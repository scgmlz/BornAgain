// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimpleUnitConverters.h
//! @brief     Defines interface UnitConverterSimple and its subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMPLEUNITCONVERTERS_H
#define SIMPLEUNITCONVERTERS_H

#include "IUnitConverter.h"
#include "Vectors3D.h"

class Beam;
class IDetector;
class IDetector2D;
class RectangularDetector;
class RectangularPixel;
class SphericalDetector;

//! Interface for objects that provide axis translations to different units for IDetector objects
//! @ingroup simulation_internal

class BA_CORE_API_ UnitConverterSimple : public IUnitConverter
{
public:
    UnitConverterSimple(const Beam& beam);
    virtual ~UnitConverterSimple() =default;

    virtual size_t dimension() const override;

    double calculateMin(size_t i_axis, AxesUnits units_type) const override;
    double calculateMax(size_t i_axis, AxesUnits units_type) const override;
    size_t axisSize(size_t i_axis) const override;

    std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, AxesUnits units) const override;

protected:
    UnitConverterSimple(const UnitConverterSimple& other);
    void addDetectorAxis(const IDetector& detector, size_t i_axis);

    void addAxisData(std::string name, double min, double max,
                     AxesUnits default_units, size_t nbins);
    void checkIndex(size_t i_axis) const;
    void checkDimension(size_t dim) const;

#ifndef SWIG
    struct AxisData {
        std::string name;
        double min, max;
        AxesUnits default_units;
        size_t nbins;
    };
    std::vector<AxisData> m_axis_data_table;
#endif
    double m_wavelength;
    double m_alpha_i;
    double m_phi_i;

private:
    virtual double calculateValue(size_t i_axis, AxesUnits units_type, double value) const=0;
};

//! IUnitConverter class that handles the unit translations for spherical detectors
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class BA_CORE_API_ SphericalConverter : public UnitConverterSimple
{
public:
    SphericalConverter(const SphericalDetector& detector, const Beam& beam);

    virtual ~SphericalConverter();

    SphericalConverter* clone() const override;

    AxesUnits defaultUnits() const override;

private:
    SphericalConverter(const SphericalConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const override;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;
};

//! IUnitConverter class that handles the unit translations for rectangular detectors
//! Its default units are mm for both axes
//! @ingroup simulation_internal

class BA_CORE_API_ RectangularConverter : public UnitConverterSimple
{
public:
    RectangularConverter(const RectangularDetector& detector, const Beam& beam);
    virtual ~RectangularConverter();

    RectangularConverter* clone() const override;

    AxesUnits defaultUnits() const override;

private:
    RectangularConverter(const RectangularConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const override;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;
    kvector_t normalizeToWavelength(kvector_t vector) const;
    double axisAngle(size_t i_axis, kvector_t k_f) const;
    std::unique_ptr<RectangularPixel> mP_detector_pixel;
};

//! IUnitConverter class that handles the unit translations for off-specular simulations
//! with a spherical detector
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class BA_CORE_API_ OffSpecularConverter : public UnitConverterSimple
{
public:
    OffSpecularConverter(const IDetector2D& detector, const Beam& beam, const IAxis& alpha_axis);
    virtual ~OffSpecularConverter();

    OffSpecularConverter* clone() const override;

    AxesUnits defaultUnits() const override;

private:
    OffSpecularConverter(const OffSpecularConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const override;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;
    void addDetectorYAxis(const IDetector2D& detector);
};

//! DepthProbeConverter class handles the unit translations for depth probe simulations
//! Its default units are radians for x-axis and nm for y-axis
//! @ingroup simulation_internal

class BA_CORE_API_ DepthProbeConverter : public UnitConverterSimple
{
public:
    DepthProbeConverter(const Beam& beam, const IAxis& alpha_axis, const IAxis& z_axis);
    virtual ~DepthProbeConverter();

    DepthProbeConverter* clone() const override;

    double calculateMin(size_t i_axis, AxesUnits units_type) const override;
    double calculateMax(size_t i_axis, AxesUnits units_type) const override;

    // TODO: remove axisName after implementing functionality for two axis in different units
    std::string axisName(size_t i_axis, AxesUnits units_type = AxesUnits::DEFAULT) const override;
    AxesUnits defaultUnits() const override { return AxesUnits::DEGREES; }
    std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, AxesUnits units) const override;

private:
    DepthProbeConverter(const DepthProbeConverter& other);
    void checkForDefaultUnits(AxesUnits units_type) const;
    double calculateValue(size_t, AxesUnits units_type, double value) const override;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;
    void addZAxis(const IAxis& z_axis);
};

#endif // SIMPLEUNITCONVERTERS_H
