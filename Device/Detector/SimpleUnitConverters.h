//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/SimpleUnitConverters.h
//! @brief     Defines interface UnitConverterSimple and its subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_DETECTOR_SIMPLEUNITCONVERTERS_H
#define BORNAGAIN_DEVICE_DETECTOR_SIMPLEUNITCONVERTERS_H

#include "Base/Vector/Vectors3D.h"
#include "Device/Unit/IUnitConverter.h"

class Beam;
class IDetector;
class IDetector2D;
class RectangularDetector;
class RectangularPixel;
class SphericalDetector;

//! Interface for objects that provide axis translations to different units for IDetector objects
//! @ingroup simulation_internal

class UnitConverterSimple : public IUnitConverter {
public:
    UnitConverterSimple(const Beam& beam);
    ~UnitConverterSimple() override = default;

    virtual size_t dimension() const override;

    double calculateMin(size_t i_axis, Axes::Units units_type) const override;
    double calculateMax(size_t i_axis, Axes::Units units_type) const override;
    size_t axisSize(size_t i_axis) const override;

    //! Returns the list of all available units
    std::vector<Axes::Units> availableUnits() const override;

    std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, Axes::Units units) const override;

protected:
    UnitConverterSimple(const UnitConverterSimple& other);
    void addDetectorAxis(const IDetector& detector, size_t i_axis);

    void addAxisData(std::string name, double min, double max, Axes::Units default_units,
                     size_t nbins);

#ifndef SWIG
    struct AxisData {
        std::string name;
        double min, max;
        Axes::Units default_units;
        size_t nbins;
    };
    std::vector<AxisData> m_axis_data_table;
#endif
    double m_wavelength;
    double m_alpha_i;
    double m_phi_i;

private:
    virtual double calculateValue(size_t i_axis, Axes::Units units_type, double value) const = 0;
};

//! IUnitConverter class that handles the unit translations for spherical detectors
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class SphericalConverter : public UnitConverterSimple {
public:
    SphericalConverter(const SphericalDetector& detector, const Beam& beam);

    ~SphericalConverter() override;

    SphericalConverter* clone() const override;

    //! Returns the list of all available units
    std::vector<Axes::Units> availableUnits() const override;

    Axes::Units defaultUnits() const override;

private:
    SphericalConverter(const SphericalConverter& other);
    double calculateValue(size_t i_axis, Axes::Units units_type, double value) const override;
    std::vector<std::map<Axes::Units, std::string>> createNameMaps() const override;
};

//! IUnitConverter class that handles the unit translations for rectangular detectors
//! Its default units are mm for both axes
//! @ingroup simulation_internal

class RectangularConverter : public UnitConverterSimple {
public:
    RectangularConverter(const RectangularDetector& detector, const Beam& beam);
    ~RectangularConverter() override;

    RectangularConverter* clone() const override;

    //! Returns the list of all available units
    std::vector<Axes::Units> availableUnits() const override;

    Axes::Units defaultUnits() const override;

private:
    RectangularConverter(const RectangularConverter& other);
    double calculateValue(size_t i_axis, Axes::Units units_type, double value) const override;
    std::vector<std::map<Axes::Units, std::string>> createNameMaps() const override;
    kvector_t normalizeToWavelength(kvector_t vector) const;
    double axisAngle(size_t i_axis, kvector_t k_f) const;
    std::unique_ptr<RectangularPixel> m_detector_pixel;
};

//! IUnitConverter class that handles the unit translations for off-specular simulations
//! with a spherical detector
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class OffSpecularConverter : public UnitConverterSimple {
public:
    OffSpecularConverter(const IDetector2D& detector, const Beam& beam, const IAxis& alpha_axis);
    ~OffSpecularConverter() override;

    OffSpecularConverter* clone() const override;

    Axes::Units defaultUnits() const override;

private:
    OffSpecularConverter(const OffSpecularConverter& other);
    double calculateValue(size_t i_axis, Axes::Units units_type, double value) const override;
    std::vector<std::map<Axes::Units, std::string>> createNameMaps() const override;
    void addDetectorYAxis(const IDetector2D& detector);
};

//! DepthProbeConverter class handles the unit translations for depth probe simulations
//! Its default units are radians for x-axis and nm for y-axis
//! @ingroup simulation_internal

class DepthProbeConverter : public UnitConverterSimple {
public:
    DepthProbeConverter(const Beam& beam, const IAxis& alpha_axis, const IAxis& z_axis);
    ~DepthProbeConverter() override;

    DepthProbeConverter* clone() const override;

    //! Returns the list of all available units
    std::vector<Axes::Units> availableUnits() const override;

    Axes::Units defaultUnits() const override { return Axes::Units::DEGREES; }

private:
    DepthProbeConverter(const DepthProbeConverter& other);
    double calculateValue(size_t, Axes::Units units_type, double value) const override;
    std::vector<std::map<Axes::Units, std::string>> createNameMaps() const override;
    void checkUnits(Axes::Units units_type) const;
};

#endif // BORNAGAIN_DEVICE_DETECTOR_SIMPLEUNITCONVERTERS_H
#endif // USER_API
