// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpecularDetector1D.h
//! @brief     Defines a detector for specular simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARDETECTOR1D_H_
#define SPECULARDETECTOR1D_H_

#include "IDetector.h"

//! 1D detector for specular simulations
//! @ingroup simulation

class BA_CORE_API_ SpecularDetector1D : public IDetector {
public:
    SpecularDetector1D(const IAxis& axis);
    virtual ~SpecularDetector1D();

    virtual SpecularDetector1D* clone() const override;

    virtual void accept(INodeVisitor* visitor) const override {visitor->visit(this);}

    //! Returns detector masks container.
    virtual const DetectorMask* detectorMask() const override {return nullptr;}

#ifndef SWIG
    //! Create a vector of SimulationElement objects according to the detector and its mask
    virtual std::vector<SimulationElement> createSimulationElements(const Beam& beam) override;
#endif // SWIG

    //! Returns region of interest if exists.
    virtual const RegionOfInterest* regionOfInterest() const override {return nullptr;}

    virtual void resetRegionOfInterest() override {}

    //! Return default axes units
    virtual AxesUnits defaultAxesUnits() const override;

    //! Returns vector of valid axes units
    virtual std::vector<AxesUnits> validAxesUnits() const override;

protected:
    SpecularDetector1D(const SpecularDetector1D& other);

    //! Returns the name for the axis with given index
    virtual std::string axisName(size_t index) const override;

    //! Calculates axis range from original detector axes in given units (mm, rad, etc)
    virtual void calculateAxisRange(size_t axis_index, const Beam& beam, AxesUnits units,
                                    double& amin, double& amax) const override;

private:
    double alphaI(size_t index) const;
};

#endif /* SPECULARDETECTOR1D_H_ */
