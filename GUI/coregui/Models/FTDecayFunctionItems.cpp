// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FTDecayFunctionItems.cpp
//! @brief     Implements FTDecayFunction1DItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FTDecayFunctionItems.h"
#include "Core/Basics/Units.h"

// --------------------------------------------------------------------------------------------- //

const QString FTDecayFunction1DItem::P_DECAY_LENGTH = QString::fromStdString("DecayLength");

FTDecayFunction1DItem::FTDecayFunction1DItem(const QString& name) : SessionItem(name) {}

void FTDecayFunction1DItem::add_decay_property()
{
    addProperty(P_DECAY_LENGTH, 1000.0)
        ->setToolTip("Decay length (half-width of the distribution in nanometers)");
}

// --------------------------------------------------------------------------------------------- //

FTDecayFunction1DCauchyItem::FTDecayFunction1DCauchyItem()
    : FTDecayFunction1DItem("FTDecayFunction1DCauchy")
{
    setToolTip("One-dimensional Cauchy decay function");
    add_decay_property();
}

std::unique_ptr<IFTDecayFunction1D> FTDecayFunction1DCauchyItem::createFTDecayFunction() const
{
    return std::make_unique<FTDecayFunction1DCauchy>(getItemValue(P_DECAY_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDecayFunction1DGaussItem::FTDecayFunction1DGaussItem()
    : FTDecayFunction1DItem("FTDecayFunction1DGauss")
{
    setToolTip("One-dimensional Gauss decay function");
    add_decay_property();
}

std::unique_ptr<IFTDecayFunction1D> FTDecayFunction1DGaussItem::createFTDecayFunction() const
{
    return std::make_unique<FTDecayFunction1DGauss>(getItemValue(P_DECAY_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

FTDecayFunction1DTriangleItem::FTDecayFunction1DTriangleItem()
    : FTDecayFunction1DItem("FTDecayFunction1DTriangle")
{
    setToolTip("One-dimensional triangle decay function");
    add_decay_property();
}

std::unique_ptr<IFTDecayFunction1D> FTDecayFunction1DTriangleItem::createFTDecayFunction() const
{
    return std::make_unique<FTDecayFunction1DTriangle>(getItemValue(P_DECAY_LENGTH).toDouble());
}

// --------------------------------------------------------------------------------------------- //

const QString FTDecayFunction1DVoigtItem::P_ETA = QString::fromStdString("Eta");

FTDecayFunction1DVoigtItem::FTDecayFunction1DVoigtItem()
    : FTDecayFunction1DItem("FTDecayFunction1DVoigt")
{
    setToolTip("One-dimensional pseudo-Voigt decay function");
    add_decay_property();
    addProperty(P_ETA, 0.5)
        ->setLimits(RealLimits::limited(0.0, 1.0))
        .setToolTip("Parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)");
}

std::unique_ptr<IFTDecayFunction1D> FTDecayFunction1DVoigtItem::createFTDecayFunction() const
{
    return std::make_unique<FTDecayFunction1DVoigt>(getItemValue(P_DECAY_LENGTH).toDouble(),
                                                    getItemValue(P_ETA).toDouble());
}

// --------------------------------------------------------------------------------------------- //

const QString FTDecayFunction2DItem::P_DECAY_LENGTH_X = QString::fromStdString("DecayLengthX");
const QString FTDecayFunction2DItem::P_DECAY_LENGTH_Y = QString::fromStdString("DecayLengthY");
const QString FTDecayFunction2DItem::P_GAMMA = QString::fromStdString("Gamma");
const QString FTDecayFunction2DItem::P_DELTA = QString::fromStdString("Delta");

FTDecayFunction2DItem::FTDecayFunction2DItem(const QString& name) : SessionItem(name) {}

void FTDecayFunction2DItem::add_decay_property()
{
    addProperty(P_DECAY_LENGTH_X, 1000.0)
        ->setToolTip("Decay length (half-width of the distribution in nanometers) "
                     "\nalong x-axis of the distribution");
    addProperty(P_DECAY_LENGTH_Y, 1000.0)
        ->setToolTip("Decay length (half-width of the distribution in nanometers) "
                     "\nalong y-axis of the distribution");
}

void FTDecayFunction2DItem::add_gammadelta_property()
{
    addProperty(P_GAMMA, 0.0)
        ->setToolTip(
            "Distribution orientation with respect to the first lattice vector in degrees");
    addProperty(P_DELTA, 90.0)->setVisible(false);
}

// --------------------------------------------------------------------------------------------- //

FTDecayFunction2DCauchyItem::FTDecayFunction2DCauchyItem()
    : FTDecayFunction2DItem("FTDecayFunction2DCauchy")
{
    setToolTip("Two-dimensional Cauchy decay function");
    add_decay_property();
    add_gammadelta_property();
}

std::unique_ptr<IFTDecayFunction2D> FTDecayFunction2DCauchyItem::createFTDecayFunction() const
{
    return std::make_unique<FTDecayFunction2DCauchy>(
        getItemValue(P_DECAY_LENGTH_X).toDouble(), getItemValue(P_DECAY_LENGTH_Y).toDouble(),
        Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
}

// --------------------------------------------------------------------------------------------- //

FTDecayFunction2DGaussItem::FTDecayFunction2DGaussItem()
    : FTDecayFunction2DItem("FTDecayFunction2DGauss")
{
    setToolTip("Two-dimensional Gauss decay function");
    add_decay_property();
    add_gammadelta_property();
}

std::unique_ptr<IFTDecayFunction2D> FTDecayFunction2DGaussItem::createFTDecayFunction() const
{
    return std::make_unique<FTDecayFunction2DGauss>(
        getItemValue(P_DECAY_LENGTH_X).toDouble(), getItemValue(P_DECAY_LENGTH_Y).toDouble(),
        Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
}

// --------------------------------------------------------------------------------------------- //

const QString FTDecayFunction2DVoigtItem::P_ETA = QString::fromStdString("Eta");

FTDecayFunction2DVoigtItem::FTDecayFunction2DVoigtItem()
    : FTDecayFunction2DItem("FTDecayFunction2DVoigt")
{
    setToolTip("Two-dimensional pseudo-Voigt decay function");
    add_decay_property();
    addProperty(P_ETA, 0.5)
        ->setLimits(RealLimits::limited(0.0, 1.0))
        .setToolTip("Parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)");
    add_gammadelta_property();
}

std::unique_ptr<IFTDecayFunction2D> FTDecayFunction2DVoigtItem::createFTDecayFunction() const
{
    return std::make_unique<FTDecayFunction2DVoigt>(
        getItemValue(P_DECAY_LENGTH_X).toDouble(), getItemValue(P_DECAY_LENGTH_Y).toDouble(),
        getItemValue(P_ETA).toDouble(), Units::deg2rad(getItemValue(P_GAMMA).toDouble()));
}
