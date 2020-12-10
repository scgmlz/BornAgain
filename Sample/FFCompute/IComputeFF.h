//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/IComputeFF.h
//! @brief     Defines and implements interface IFormFactor.
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
#ifndef BORNAGAIN_SAMPLE_FFCOMPUTE_ICOMPUTEFF_H
#define BORNAGAIN_SAMPLE_FFCOMPUTE_ICOMPUTEFF_H

#include "Base/Types/Complex.h"
#include <Eigen/Core>
#include <memory>

class IFormFactor;
class ILayerRTCoefficients;
class IRotation;
class Material;
class WavevectorInfo;

//! Abstract base class for form factor evaluations.
//!
//! Wraps an IFormFactor, and provides functions evaluate or evaluatePol.

//! @ingroup formfactors_internal

class IComputeFF {

public:
    IComputeFF() = delete;
    virtual ~IComputeFF();
    virtual IComputeFF* clone() const = 0;

    virtual void setAmbientMaterial(const Material& material);

    virtual double volume() const;
    virtual double radialExtension() const;
    virtual double bottomZ(const IRotation& rotation) const;
    virtual double topZ(const IRotation& rotation) const;
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const = 0;
#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
    //! Sets reflection/transmission info
    virtual void setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients>,
                                 std::unique_ptr<const ILayerRTCoefficients>);
#endif

protected:
    IComputeFF(const IFormFactor&);

    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_SAMPLE_FFCOMPUTE_ICOMPUTEFF_H
#endif // USER_API
