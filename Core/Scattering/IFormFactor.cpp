// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactor.cpp
//! @brief     Implements interface class IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Scattering/IFormFactor.h"
#include "Core/Basics/Exceptions.h"
#include "Core/RT/ILayerRTCoefficients.h"
#include "Core/Scattering/FormFactorDecoratorPositionFactor.h"
#include "Core/Scattering/FormFactorDecoratorRotation.h"
#include "Core/Scattering/Rotations.h"
#include "Core/Vector/WavevectorInfo.h"
#include <memory>
#include <utility>

namespace
{
bool ShapeIsContainedInLimits(const IFormFactor& formfactor, ZLimits limits, const IRotation& rot,
                              kvector_t translation);
bool ShapeOutsideLimits(const IFormFactor& formfactor, ZLimits limits, const IRotation& rot,
                        kvector_t translation);
} // namespace

IFormFactor::IFormFactor(const NodeMeta& meta, const std::vector<double>& PValues)
    : ISample(meta, PValues)
{
}

IFormFactor* IFormFactor::createSlicedFormFactor(ZLimits limits, const IRotation& rot,
                                                 kvector_t translation) const
{
    if (ShapeIsContainedInLimits(*this, limits, rot, translation))
        return createTransformedFormFactor(*this, rot, translation);
    if (ShapeOutsideLimits(*this, limits, rot, translation))
        return nullptr;
    if (canSliceAnalytically(rot))
        return sliceFormFactor(limits, rot, translation);
    throw std::runtime_error(getName()
                             + "::createSlicedFormFactor error: not supported for "
                               "the given rotation!");
}

Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo&) const
{
    // Throws to prevent unanticipated behaviour
    throw Exceptions::NotImplementedException(
        "IFormFactor::evaluatePol: is not implemented by default");
}

double IFormFactor::volume() const
{
    auto zero_wavevectors = WavevectorInfo::GetZeroQ();
    return std::abs(evaluate(zero_wavevectors));
}

void IFormFactor::setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients>,
                                  std::unique_ptr<const ILayerRTCoefficients>)
{
}

bool IFormFactor::canSliceAnalytically(const IRotation&) const
{
    return false;
}

IFormFactor* IFormFactor::sliceFormFactor(ZLimits, const IRotation&, kvector_t) const
{
    throw std::runtime_error(getName() + "::sliceFormFactor error: not implemented!");
}

IFormFactor* createTransformedFormFactor(const IFormFactor& formfactor, const IRotation& rot,
                                         kvector_t translation)
{
    std::unique_ptr<IFormFactor> P_fftemp, P_result;
    if (!rot.isIdentity())
        P_fftemp.reset(new FormFactorDecoratorRotation(formfactor, rot));
    else
        P_fftemp.reset(formfactor.clone());
    if (translation != kvector_t())
        P_result.reset(new FormFactorDecoratorPositionFactor(*P_fftemp, translation));
    else
        std::swap(P_fftemp, P_result);
    return P_result.release();
}

namespace
{
bool ShapeIsContainedInLimits(const IFormFactor& formfactor, ZLimits limits, const IRotation& rot,
                              kvector_t translation)
{
    double zbottom = formfactor.bottomZ(rot) + translation.z();
    double ztop = formfactor.topZ(rot) + translation.z();
    OneSidedLimit lower_limit = limits.lowerLimit();
    OneSidedLimit upper_limit = limits.upperLimit();
    if (!upper_limit.m_limitless && ztop > upper_limit.m_value)
        return false;
    if (!lower_limit.m_limitless && zbottom < lower_limit.m_value)
        return false;
    return true;
}
bool ShapeOutsideLimits(const IFormFactor& formfactor, ZLimits limits, const IRotation& rot,
                        kvector_t translation)
{
    double zbottom = formfactor.bottomZ(rot) + translation.z();
    double ztop = formfactor.topZ(rot) + translation.z();
    OneSidedLimit lower_limit = limits.lowerLimit();
    OneSidedLimit upper_limit = limits.upperLimit();
    if (!upper_limit.m_limitless && zbottom >= upper_limit.m_value)
        return true;
    if (!lower_limit.m_limitless && ztop <= lower_limit.m_value)
        return true;
    return false;
}
} // namespace
