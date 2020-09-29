// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/SimpleUnitConverters.h
//! @brief     Defines interface UnitConverterSimple and its subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INTENSITY_SIMPLEUNITCONVERTERS_H
#define BORNAGAIN_CORE_INTENSITY_SIMPLEUNITCONVERTERS_H

#include "Core/Intensity/IUnitConverter.h"
#include "Core/Vector/Vectors3D.h"

class Beam;
class IDetector;
class IDetector2D;
class RectangularDetector;
class RectangularPixel;
class SphericalDetector;

//! Interface for objects that provide axis translations to different units for IDetector objects
//! @ingroup simulation_internal

class UnitConverterSimple : public IUnitConverter
{
public:
    UnitConverterSimple(const Beam& beam);
    ~UnitConverterSimple() override = default;

    virtual size_t dimension() const final;

    double calculateMin(size_t i_axis, AxesUnits units_type) const final;
    double calculateMax(size_t i_axis, AxesUnits units_type) const final;
    size_t axisSize(size_t i_axis) const final;

    //! Returns the list of all available units
    std::vector<AxesUnits> availableUnits() const override;

    std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, AxesUnits units) const final;

protected:
    UnitConverterSimple(const UnitConverterSimple& other);
    void addDetectorAxis(const IDetector& detector, size_t i_axis);

    void addAxisData(std::string name, double min, double max, AxesUnits default_units,
                     size_t nbins);

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
    virtual double calculateValue(size_t i_axis, AxesUnits units_type, double value) const = 0;
};

//! IUnitConverter class that handles the unit translations for spherical detectors
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class SphericalConverter : public UnitConverterSimple
{
public:
    SphericalConverter(const SphericalDetector& detector, const Beam& beam);

    ~SphericalConverter() final;

    SphericalConverter* clone() const final;

    //! Returns the list of all available units
    std::vector<AxesUnits> availableUnits() const final;

    AxesUnits defaultUnits() const final;

private:
    SphericalConverter(const SphericalConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const final;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const final;
};

//! IUnitConverter class that handles the unit translations for rectangular detectors
//! Its default units are mm for both axes
//! @ingroup simulation_internal

class RectangularConverter : public UnitConverterSimple
{
public:
    RectangularConverter(const RectangularDetector& detector, const Beam& beam);
    ~RectangularConverter() final;

    RectangularConverter* clone() const final;

    //! Returns the list of all available units
    std::vector<AxesUnits> availableUnits() const final;

    AxesUnits defaultUnits() const final;

private:
    RectangularConverter(const RectangularConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const final;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const final;
    kvector_t normalizeToWavelength(kvector_t vector) const;
    double axisAngle(size_t i_axis, kvector_t k_f) const;
    std::unique_ptr<RectangularPixel> mP_detector_pixel;
};

//! IUnitConverter class that handles the unit translations for off-specular simulations
//! with a spherical detector
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class OffSpecularConverter : public UnitConverterSimple
{
public:
    OffSpecularConverter(const IDetector2D& detector, const Beam& beam, const IAxis& alpha_axis);
    ~OffSpecularConverter() final;

    OffSpecularConverter* clone() const final;

    AxesUnits defaultUnits() const final;

private:
    OffSpecularConverter(const OffSpecularConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const final;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const final;
    void addDetectorYAxis(const IDetector2D& detector);
};

//! DepthProbeConverter class handles the unit translations for depth probe simulations
//! Its default units are radians for x-axis and nm for y-axis
//! @ingroup simulation_internal

class DepthProbeConverter : public UnitConverterSimple
{
public:
    DepthProbeConverter(const Beam& beam, const IAxis& alpha_axis, const IAxis& z_axis);
    ~DepthProbeConverter() final;

    DepthProbeConverter* clone() const final;

    //! Returns the list of all available units
    std::vector<AxesUnits> availableUnits() const final;

    AxesUnits defaultUnits() const final { return AxesUnits::DEGREES; }

private:
    DepthProbeConverter(const DepthProbeConverter& other);
    double calculateValue(size_t, AxesUnits units_type, double value) const final;
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const final;
    void checkUnits(AxesUnits units_type) const;
};

#endif // BORNAGAIN_CORE_INTENSITY_SIMPLEUNITCONVERTERS_H
