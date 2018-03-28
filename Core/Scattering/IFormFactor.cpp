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

#include "IFormFactor.h"
#include "ILayerRTCoefficients.h"
#include "Exceptions.h"
#include "FormFactorDecoratorPositionFactor.h"
#include "FormFactorDecoratorRotation.h"
#include "Rotations.h"
#include "WavevectorInfo.h"
#include <memory>
#include <utility>

namespace {
bool ShapeIsContainedInLimits(const IFormFactor& formfactor, ZLimits limits,
                              const IRotation& rot, kvector_t translation);
}

IFormFactor::~IFormFactor() {}

IFormFactor* IFormFactor::createSlicedFormFactor(ZLimits limits, const IRotation& rot,
                                                kvector_t translation) const
{
    if (ShapeIsContainedInLimits(*this, limits, rot, translation))
        return CreateTransformedFormFactor(*this, rot, translation);
    if (canSliceAnalytically(rot))
        return sliceFormFactor(limits, rot, translation);
    throw std::runtime_error(getName() + "::createSlicedFormFactor error: not supported for "
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

bool IFormFactor::canSliceAnalytically(const IRotation&) const
{
    return false;
}

IFormFactor* IFormFactor::sliceFormFactor(ZLimits, const IRotation&, kvector_t) const
{
    throw std::runtime_error(getName() + "::sliceFormFactor error: not implemented!");
}

IFormFactor* CreateTransformedFormFactor(const IFormFactor& formfactor, const IRotation& rot,
                                        kvector_t translation)
{
    std::unique_ptr<IFormFactor> P_fftemp, P_result;
    if (!rot.isIdentity())
        P_fftemp.reset(new FormFactorDecoratorRotation(formfactor, rot));
    else
        P_fftemp.reset(formfactor.clone());
    if (translation!=kvector_t())
        P_result.reset(new FormFactorDecoratorPositionFactor(*P_fftemp, translation));
    else
        std::swap(P_fftemp, P_result);
    return P_result.release();
}

namespace {
bool ShapeIsContainedInLimits(const IFormFactor& formfactor, ZLimits limits,
                              const IRotation& rot, kvector_t translation)
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
}
