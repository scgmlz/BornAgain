// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/RT/ILayerRTCoefficients.h
//! @brief     Defines and implements class ILayerRTCoefficients.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_RT_ILAYERRTCOEFFICIENTS_H
#define BORNAGAIN_CORE_RT_ILAYERRTCOEFFICIENTS_H

#include "Core/Basics/Complex.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Vector/EigenCore.h"

//! Interface to access reflection/transmission coefficients.
//! @ingroup algorithms_internal

class ILayerRTCoefficients
{
public:
    virtual ~ILayerRTCoefficients() {}

    virtual ILayerRTCoefficients* clone() const = 0;

#ifndef SWIG
    //! The following functions return the transmitted and reflected amplitudes
    //! for different incoming beam polarizations and eigenmodes
    virtual Eigen::Vector2cd T1plus() const = 0;
    virtual Eigen::Vector2cd R1plus() const = 0;
    virtual Eigen::Vector2cd T2plus() const = 0;
    virtual Eigen::Vector2cd R2plus() const = 0;
    virtual Eigen::Vector2cd T1min() const = 0;
    virtual Eigen::Vector2cd R1min() const = 0;
    virtual Eigen::Vector2cd T2min() const = 0;
    virtual Eigen::Vector2cd R2min() const = 0;
    //! Returns z-part of the two wavevector eigenmodes
    virtual Eigen::Vector2cd getKz() const = 0;
    //! Scalar value getters; these throw errors by default as they should only
    //! be used when the derived object is really scalar
#endif
    virtual complex_t getScalarT() const
    {
        throw Exceptions::NotImplementedException("ILayerRTCoefficients::"
                                                  "getScalarT(): coefficients are not scalar.");
    }
    virtual complex_t getScalarR() const
    {
        throw Exceptions::NotImplementedException("ILayerRTCoefficients::"
                                                  "getScalarR(): coefficients are not scalar.");
    }
    virtual complex_t getScalarKz() const
    {
        throw Exceptions::NotImplementedException("ILayerRTCoefficients::"
                                                  "getScalarKz(): coefficients are not scalar.");
    }

    virtual Eigen::Matrix2cd getReflectionMatrix() const
    {
        throw Exceptions::NotImplementedException("Only defined for Matrix coefficeints");
    }
};

#endif // BORNAGAIN_CORE_RT_ILAYERRTCOEFFICIENTS_H
