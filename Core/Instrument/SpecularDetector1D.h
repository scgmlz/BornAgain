// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpecularDetector1D.h
//! @brief     Defines a detector for specular simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDETECTOR1D_H_
#define SPECULARDETECTOR1D_H_

#include "IDetector.h"

class SpecularSimulationElement;

//! 1D detector for specular simulations. Use of this detector is deprecated.
//! @ingroup detector

class BA_CORE_API_ SpecularDetector1D : public IDetector
{
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
    AxesUnits defaultAxesUnits() const override;

protected:
    SpecularDetector1D(const SpecularDetector1D& other);

    //! Returns the name for the axis with given index
    std::string axisName(size_t index) const override;

    void initialize();
};

#endif /* SPECULARDETECTOR1D_H_ */
