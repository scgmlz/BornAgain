// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/RectangularDetector.h
//! @brief     Defines class RectangularDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef RECTANGULARDETECTOR_H
#define RECTANGULARDETECTOR_H

#include "IDetector2D.h"
#include "IPixel.h"

class RectangularPixel;

//! A flat rectangular detector with axes and resolution function.
//! @ingroup simulation

class BA_CORE_API_ RectangularDetector : public IDetector2D
{
public:
    enum EDetectorArrangement {
        GENERIC,
        PERPENDICULAR_TO_SAMPLE,
        PERPENDICULAR_TO_DIRECT_BEAM,
        PERPENDICULAR_TO_REFLECTED_BEAM,
        PERPENDICULAR_TO_REFLECTED_BEAM_DPOS
    };

    //! Rectangular detector constructor
    //! @param nxbins Number of bins (pixels) in x-direction
    //! @param width Width of the detector in mm along x-direction
    //! @param nybins Number of bins (pixels) in y-direction
    //! @param height Height of the detector in mm along y-direction
    RectangularDetector(size_t nxbins, double width, size_t nybins, double height);

    RectangularDetector(const RectangularDetector& other);

    RectangularDetector* clone() const override;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    ~RectangularDetector();

    void init(const Beam& beam) override;

    void setPosition(const kvector_t normal_to_detector, double u0, double v0,
                     const kvector_t direction = kvector_t(0.0, -1.0, 0.0));

    void setPerpendicularToSampleX(double distance, double u0, double v0);

    void setPerpendicularToDirectBeam(double distance, double u0, double v0);
    void setPerpendicularToReflectedBeam(double distance, double u0 = 0.0, double v0 = 0.0);
    void setDirectBeamPosition(double u0, double v0);

    double getWidth() const;
    double getHeight() const;
    size_t getNbinsX() const;
    size_t getNbinsY() const;
    kvector_t getNormalVector() const;
    double getU0() const;
    double getV0() const;
    kvector_t getDirectionVector() const;
    double getDistance() const;
    double getDirectBeamU0() const;
    double getDirectBeamV0() const;
    EDetectorArrangement getDetectorArrangment() const;

    //! return default axes units
    AxesUnits defaultAxesUnits() const override;

    RectangularPixel* regionOfInterestPixel() const;

protected:
    //! Create an IPixel for the given OutputData object and index
    IPixel* createPixel(size_t index) const override;

    //! Returns the name for the axis with given index
    std::string axisName(size_t index) const override;

    //! Returns index of pixel that contains the specular wavevector.
    //! If no pixel contains this specular wavevector, the number of pixels is
    //! returned. This corresponds to an overflow index.
    size_t getIndexOfSpecular(const Beam& beam) const override;

    //! swap function
    void swapContent(RectangularDetector& other);
private:
    void setDistanceAndOffset(double distance, double u0, double v0);
    void initNormalVector(const kvector_t central_k);
    void initUandV(double alpha_i);

    kvector_t m_normal_to_detector;
    double m_u0, m_v0; //!< position of normal vector hitting point in detector coordinates
    kvector_t m_direction; //!< direction vector of detector coordinate system
    double m_distance; //!< distance from sample origin to the detector plane
    double m_dbeam_u0, m_dbeam_v0; //!< position of direct beam in detector coordinates
    EDetectorArrangement m_detector_arrangement;
    kvector_t m_u_unit;
    kvector_t m_v_unit;
};

class RectangularPixel : public IPixel
{
public:
    RectangularPixel(kvector_t corner_pos, kvector_t width, kvector_t height);
    virtual ~RectangularPixel() {}

    RectangularPixel* clone() const override;
    RectangularPixel* createZeroSizePixel(double x, double y) const override;
    kvector_t getK(double x, double y, double wavelength) const override;
    kvector_t getPosition(double x, double y) const;
    double getIntegrationFactor(double x, double y) const override;
    double getSolidAngle() const override;
private:
    kvector_t normalizeLength(const kvector_t direction, double length) const;
    double calculateSolidAngle() const;
    kvector_t m_corner_pos;
    kvector_t m_width;
    kvector_t m_height;
    double m_solid_angle;
    kvector_t m_normal;
};

#endif // RECTANGULARDETECTOR_H
