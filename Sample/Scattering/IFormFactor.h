//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/IFormFactor.h
//! @brief     Defines and implements interface IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SCATTERING_IFORMFACTOR_H
#define BORNAGAIN_SAMPLE_SCATTERING_IFORMFACTOR_H

#include "Base/Types/Complex.h"
#include "Sample/Scattering/ISampleNode.h"
#include "Sample/Scattering/ZLimits.h"
#include <Eigen/Core>

class ILayerRTCoefficients;
class IRotation;
class Material;
class WavevectorInfo;

//! Abstract base class for all form factors.
//!
//! The actual form factor is returned by the complex valued function IFormFactor::evaluate,
//! which depends on the incoming and outgoing wave vectors ki and kf.
//! If it only depends on the scattering vector q=ki-kf, then it is a IBornFF.

//! @ingroup formfactors_internal

class IFormFactor : public ISampleNode {
public:
    IFormFactor() = default;
    IFormFactor(const NodeMeta& meta, const std::vector<double>& PValues);

    ~IFormFactor() = default;
    IFormFactor* clone() const override = 0;

    //! Creates a (possibly sliced) form factor with the given rotation and translation
    IFormFactor* createSlicedFormFactor(ZLimits limits, const IRotation& rot,
                                        kvector_t translation) const;

    //! Passes the material in which this particle is embedded.
    virtual void setAmbientMaterial(const Material&) = 0;

    //! Returns scattering amplitude for complex wavevectors ki, kf.
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const = 0;

#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

    //! Returns the total volume of the particle of this form factor's shape
    virtual double volume() const;

    //! Returns the (approximate in some cases) radial size of the particle of this
    //! form factor's shape. This is used for SSCA calculations
    virtual double radialExtension() const = 0;

    //! Returns the z-coordinate of the lowest point in this shape after a given rotation
    virtual double bottomZ(const IRotation& rotation) const = 0;

    //! Returns the z-coordinate of the lowest point in this shape after a given rotation
    virtual double topZ(const IRotation& rotation) const = 0;

#ifndef SWIG
    //! Sets reflection/transmission info
    virtual void setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients>,
                                 std::unique_ptr<const ILayerRTCoefficients>);
#endif

protected:
    //! Checks if slicing has a fast analytical solution
    virtual bool canSliceAnalytically(const IRotation& rot) const;

    //! Actually slices the form factor or throws an exception
    virtual IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                         kvector_t translation) const;

    static IFormFactor* createTransformedFormFactor(const IFormFactor& formfactor,
                                                    const IRotation& rot, kvector_t translation);
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_IFORMFACTOR_H
#endif // USER_API
