//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/SpecularDetector1D.h
//! @brief     Defines a detector for specular simulations.
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
#ifndef BORNAGAIN_DEVICE_DETECTOR_SPECULARDETECTOR1D_H
#define BORNAGAIN_DEVICE_DETECTOR_SPECULARDETECTOR1D_H

#include "Device/Detector/IDetector.h"

class SpecularSimulationElement;

//! 1D detector for specular simulations. Use of this detector is deprecated.
//! @ingroup detector

class SpecularDetector1D : public IDetector {
public:
    SpecularDetector1D(const IAxis& axis);
    virtual ~SpecularDetector1D();

    SpecularDetector1D* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Returns detector masks container.
    const DetectorMask* detectorMask() const override { return nullptr; }

    //! Returns region of interest if exists.
    const RegionOfInterest* regionOfInterest() const override { return nullptr; }

    void resetRegionOfInterest() override {}

    //! Return default axes units
    Axes::Units defaultAxesUnits() const override;

protected:
    SpecularDetector1D(const SpecularDetector1D& other);

    //! Returns the name for the axis with given index
    std::string axisName(size_t index) const override;

    void initialize();
};

#endif // BORNAGAIN_DEVICE_DETECTOR_SPECULARDETECTOR1D_H
#endif // USER_API
