// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DistributionItems.cpp
//! @brief     Implements class DistributionItem and several subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DistributionItems.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "GUI/coregui/Models/RealLimitsItems.h"
#include <cmath>

namespace
{
template <class DistrType>
std::unique_ptr<RangedDistribution>
createRangedDistribution(const SymmetricDistributionItem& distr_item, double scale);
}

const QString DistributionItem::P_NUMBER_OF_SAMPLES = "Number of samples";
const QString DistributionItem::P_SIGMA_FACTOR = "Sigma factor";
const QString DistributionItem::P_IS_INITIALIZED = "is initialized";
const QString DistributionItem::P_LIMITS = "Limits";

DistributionItem::DistributionItem(const QString& name) : SessionItem(name)
{
    addProperty(P_IS_INITIALIZED, false)->setVisible(false);
}

//! Provides initialization of the distribution with some reasonable parameters around given value.
//! Used by beamDistributionItem to propagate value from DistributionNone to the distribution
//! currently selected by GroupItem.

void DistributionItem::init_parameters(double value, const RealLimits& limits)
{
    if (getItemValue(P_IS_INITIALIZED).toBool())
        return;

    init_distribution(value);
    init_limits_group(limits);
    setItemValue(P_IS_INITIALIZED, true);
}

void DistributionItem::init_limits_group(const RealLimits& limits, double factor)
{
    if (!isTag(P_LIMITS))
        return;
    if (limits.isLimitless()) {
        setGroupProperty(P_LIMITS, "RealLimitsLimitless");
    } else if (limits.isPositive()) {
        setGroupProperty(P_LIMITS, "RealLimitsPositive");
    } else if (limits.isNonnegative()) {
        setGroupProperty(P_LIMITS, "RealLimitsNonnegative");
    } else if (limits.isLowerLimited()) {
        SessionItem* lim = setGroupProperty(P_LIMITS, "RealLimitsLowerLimited");
        lim->setItemValue(RealLimitsItem::P_XMIN, limits.lowerLimit() * factor);
    } else if (limits.isUpperLimited()) {
        SessionItem* lim = setGroupProperty(P_LIMITS, "RealLimitsUpperLimited");
        lim->setItemValue(RealLimitsItem::P_XMAX, limits.upperLimit() * factor);
    } else if (limits.isLimited()) {
        SessionItem* lim = setGroupProperty(P_LIMITS, "RealLimitsLimited");
        lim->setItemValue(RealLimitsItem::P_XMIN, limits.lowerLimit() * factor);
        lim->setItemValue(RealLimitsItem::P_XMAX, limits.upperLimit() * factor);
    }
}

void DistributionItem::register_number_of_samples()
{
    addProperty(P_NUMBER_OF_SAMPLES, 5)->setLimits(RealLimits::lowerLimited(1.0));
}

void DistributionItem::register_sigma_factor()
{
    addProperty(P_SIGMA_FACTOR, 2.0);
}

void DistributionItem::register_limits()
{
    addGroupProperty(P_LIMITS, "RealLimits group");
    setGroupProperty(P_LIMITS, "RealLimitsLimitless");
}

// --------------------------------------------------------------------------------------------- //

const QString SymmetricDistributionItem::P_MEAN = QString::fromStdString("Mean");

SymmetricDistributionItem::SymmetricDistributionItem(const QString& name) : DistributionItem(name)
{
}

void SymmetricDistributionItem::showMean(bool flag)
{
    getItem(P_MEAN)->setVisible(flag);
}

// --------------------------------------------------------------------------------------------- //

DistributionNoneItem::DistributionNoneItem() : SymmetricDistributionItem("DistributionNone")
{
    addProperty(P_MEAN, 0.1)->setLimits(RealLimits::limitless()).setDisplayName("Value");
    getItem(P_MEAN)->setDecimals(4);
}

std::unique_ptr<IDistribution1D> DistributionNoneItem::createDistribution(double scale) const
{
    Q_UNUSED(scale);
    return nullptr;
}

std::unique_ptr<RangedDistribution> DistributionNoneItem::createRangedDistribution(double) const
{
    return nullptr;
}

double DistributionNoneItem::deviation(double) const
{
    return 0.0;
}

void DistributionNoneItem::init_distribution(double value)
{
    setItemValue(DistributionNoneItem::P_MEAN, value);
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionGateItem::P_MIN = QString::fromStdString("Min");
const QString DistributionGateItem::P_MAX = QString::fromStdString("Max");

DistributionGateItem::DistributionGateItem() : DistributionItem("DistributionGate")
{
    addProperty(P_MIN, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_MAX, 1.0)->setLimits(RealLimits::limitless());
    register_number_of_samples();
    register_limits();
    getItem(P_LIMITS)->setVisible(false);
}

std::unique_ptr<IDistribution1D> DistributionGateItem::createDistribution(double scale) const
{
    double min = getItemValue(P_MIN).toDouble();
    double max = getItemValue(P_MAX).toDouble();
    return std::make_unique<DistributionGate>(scale * min, scale * max);
}

void DistributionGateItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;
    setItemValue(P_MIN, value - sigma);
    setItemValue(P_MAX, value + sigma);
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionLorentzItem::P_HWHM = QString::fromStdString("HWHM");

DistributionLorentzItem::DistributionLorentzItem()
    : SymmetricDistributionItem("DistributionLorentz")
{
    addProperty(P_MEAN, 1.0)->setLimits(RealLimits::limitless());
    addProperty(P_HWHM, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionLorentzItem::createDistribution(double scale) const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double hwhm = getItemValue(P_HWHM).toDouble();
    return std::make_unique<DistributionLorentz>(scale * mean, scale * hwhm);
}

std::unique_ptr<RangedDistribution>
DistributionLorentzItem::createRangedDistribution(double scale) const
{
    return ::createRangedDistribution<RangedDistributionLorentz>(*this, scale);
}

double DistributionLorentzItem::deviation(double scale) const
{
    return getItemValue(P_HWHM).toDouble() * scale;
}

void DistributionLorentzItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_HWHM, sigma);
    getItem(P_HWHM)->setLimits(RealLimits::lowerLimited(0.0));
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionGaussianItem::P_STD_DEV = QString::fromStdString("StdDev");

DistributionGaussianItem::DistributionGaussianItem()
    : SymmetricDistributionItem("DistributionGaussian")
{
    addProperty(P_MEAN, 1.0)->setLimits(RealLimits::limitless());
    addProperty(P_STD_DEV, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionGaussianItem::createDistribution(double scale) const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double std_dev = getItemValue(P_STD_DEV).toDouble();
    return std::make_unique<DistributionGaussian>(scale * mean, scale * std_dev);
}

std::unique_ptr<RangedDistribution>
DistributionGaussianItem::createRangedDistribution(double scale) const
{
    return ::createRangedDistribution<RangedDistributionGaussian>(*this, scale);
}

double DistributionGaussianItem::deviation(double scale) const
{
    return getItemValue(P_STD_DEV).toDouble() * scale;
}

void DistributionGaussianItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_STD_DEV, sigma);
    getItem(P_STD_DEV)->setLimits(RealLimits::lowerLimited(0.0));
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionLogNormalItem::P_MEDIAN = QString::fromStdString("Median");
const QString DistributionLogNormalItem::P_SCALE_PAR = QString::fromStdString("ScaleParameter");

DistributionLogNormalItem::DistributionLogNormalItem() : DistributionItem("DistributionLogNormal")
{
    addProperty(P_MEDIAN, 1.0);
    addProperty(P_SCALE_PAR, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionLogNormalItem::createDistribution(double scale) const
{
    double median = getItemValue(P_MEDIAN).toDouble();
    double scale_par = getItemValue(P_SCALE_PAR).toDouble();
    return std::make_unique<DistributionLogNormal>(scale * median, scale_par);
}

void DistributionLogNormalItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEDIAN, value);
    setItemValue(P_SCALE_PAR, sigma);
    getItem(P_SCALE_PAR)->setLimits(RealLimits::lowerLimited(0.0));
}

void DistributionLogNormalItem::showMean(bool flag)
{
    getItem(P_MEDIAN)->setVisible(flag);
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionCosineItem::P_SIGMA = QString::fromStdString("Sigma");

DistributionCosineItem::DistributionCosineItem() : SymmetricDistributionItem("DistributionCosine")
{
    addProperty(P_MEAN, 1.0)->setLimits(RealLimits::limitless());
    addProperty(P_SIGMA, 1.0);
    register_number_of_samples();
    register_sigma_factor();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionCosineItem::createDistribution(double scale) const
{
    double mean = getItemValue(P_MEAN).toDouble();
    double sigma = getItemValue(P_SIGMA).toDouble();
    return std::make_unique<DistributionCosine>(scale * mean, scale * sigma);
}

std::unique_ptr<RangedDistribution>
DistributionCosineItem::createRangedDistribution(double scale) const
{
    return ::createRangedDistribution<RangedDistributionCosine>(*this, scale);
}

double DistributionCosineItem::deviation(double scale) const
{
    return getItemValue(P_SIGMA).toDouble() * scale;
}

void DistributionCosineItem::init_distribution(double value)
{
    double sigma(0.1 * std::abs(value));
    if (sigma == 0.0)
        sigma = 0.1;

    setItemValue(P_MEAN, value);
    setItemValue(P_SIGMA, sigma);
    getItem(P_SIGMA)->setLimits(RealLimits::lowerLimited(0.0));
}

// --------------------------------------------------------------------------------------------- //

const QString DistributionTrapezoidItem::P_CENTER = QString::fromStdString("Center");
const QString DistributionTrapezoidItem::P_LEFTWIDTH = QString::fromStdString("LeftWidth");
const QString DistributionTrapezoidItem::P_MIDDLEWIDTH = QString::fromStdString("MiddleWidth");
const QString DistributionTrapezoidItem::P_RIGHTWIDTH = QString::fromStdString("RightWidth");

DistributionTrapezoidItem::DistributionTrapezoidItem() : DistributionItem("DistributionTrapezoid")
{
    addProperty(P_CENTER, 1.0)->setLimits(RealLimits::limitless());
    addProperty(P_LEFTWIDTH, 1.0);
    addProperty(P_MIDDLEWIDTH, 1.0);
    addProperty(P_RIGHTWIDTH, 1.0);
    register_number_of_samples();
    register_limits();
}

std::unique_ptr<IDistribution1D> DistributionTrapezoidItem::createDistribution(double scale) const
{
    double center = getItemValue(P_CENTER).toDouble();
    double left = getItemValue(P_LEFTWIDTH).toDouble();
    double middle = getItemValue(P_MIDDLEWIDTH).toDouble();
    double right = getItemValue(P_RIGHTWIDTH).toDouble();
    return std::make_unique<DistributionTrapezoid>(scale * center, scale * left, scale * middle,
                                                   scale * right);
}

void DistributionTrapezoidItem::init_distribution(double value)
{
    double width(0.1 * std::abs(value));
    if (width == 0.0)
        width = 0.1;
    setItemValue(P_CENTER, value);
    setItemValue(P_LEFTWIDTH, width);
    setItemValue(P_MIDDLEWIDTH, width);
    setItemValue(P_RIGHTWIDTH, width);
}

void DistributionTrapezoidItem::showMean(bool flag)
{
    getItem(P_CENTER)->setVisible(flag);
}

namespace
{
template <class DistrType>
std::unique_ptr<RangedDistribution>
createRangedDistribution(const SymmetricDistributionItem& distr_item, double scale)
{
    int n_samples = distr_item.getItemValue(SymmetricDistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double n_sig = distr_item.getItemValue(SymmetricDistributionItem::P_SIGMA_FACTOR).toDouble();

    auto limits_item = distr_item.getGroupItem(SymmetricDistributionItem::P_LIMITS);
    const RealLimits limits =
        limits_item ? dynamic_cast<RealLimitsItem*>(limits_item)->createRealLimits(scale)
                    : RealLimits::limitless();

    return std::make_unique<DistrType>(n_samples, n_sig, limits);
}
} // namespace
