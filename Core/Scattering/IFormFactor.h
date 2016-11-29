// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactor.h
//! @brief     Defines and implements pure virtual interface IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H

#include "ISample.h"
#include "Complex.h"
#include "EigenCore.h"

class IMaterial;
class ILayerRTCoefficients;
class WavevectorPair;

//! Pure virtual base class for all form factors.
//!
//! The actual form factor is returned by the complex valued function IFormFactor::evaluate,
//! which depends on the incoming and outgoing wave vectors ki and kf.
//! If it only depends on the scattering vector q=ki-kf, then it is a IBornFormFactor.
//!
//! Other children besides IBornFormFactor are IFormFactorDecorator, FormFactorWeighted,
//! FormFactorDWBA, FormFactorDWBAPol and FormFactorCrystal.

//! @ingroup formfactors_internal

class BA_CORE_API_ IFormFactor : public ISample
{
public:
    IFormFactor() {}
    ~IFormFactor() override;
    IFormFactor* clone() const override=0;
    void accept(ISampleVisitor* visitor) const override=0;

    //! Passes the refractive index of the ambient material in which this particle is embedded.
    virtual void setAmbientMaterial(const IMaterial&) {}

    //! Returns scattering amplitude for complex wavevectors ki, kf.
    virtual complex_t evaluate(const WavevectorPair& wavevectors) const=0;

#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorPair& wavevectors) const;
#endif

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the (approximate in some cases) radial size of the particle of this
    //! form factor's shape. This is used for SSCA calculations
    virtual double getRadialExtension() const=0;

    //! Sets reflection/transmission info
    virtual void setSpecularInfo(const ILayerRTCoefficients*, const ILayerRTCoefficients*) {}
};

#endif // IFORMFACTOR_H
