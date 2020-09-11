// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FTDecayFunctionItems.h
//! @brief     Defines FTDecayFunction1DItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FTDECAYFUNCTIONITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FTDECAYFUNCTIONITEMS_H

#include "Core/Correlations/FTDecay1D.h"
#include "Core/Correlations/FTDecay2D.h"
#include "GUI/coregui/Models/SessionItem.h"

class BA_CORE_API_ FTDecayFunction1DItem : public SessionItem
{
public:
    static const QString P_DECAY_LENGTH;
    explicit FTDecayFunction1DItem(const QString& name);
    virtual std::unique_ptr<IFTDecayFunction1D> createFTDecayFunction() const = 0;
    virtual ~FTDecayFunction1DItem() {}

protected:
    void add_decay_property();
};

class BA_CORE_API_ FTDecayFunction1DCauchyItem : public FTDecayFunction1DItem
{
public:
    FTDecayFunction1DCauchyItem();
    std::unique_ptr<IFTDecayFunction1D> createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DGaussItem : public FTDecayFunction1DItem
{
public:
    FTDecayFunction1DGaussItem();
    std::unique_ptr<IFTDecayFunction1D> createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DTriangleItem : public FTDecayFunction1DItem
{
public:
    FTDecayFunction1DTriangleItem();
    std::unique_ptr<IFTDecayFunction1D> createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DVoigtItem : public FTDecayFunction1DItem
{
public:
    static const QString P_ETA;
    FTDecayFunction1DVoigtItem();
    std::unique_ptr<IFTDecayFunction1D> createFTDecayFunction() const;
};

// --------------------------------------------------------------------------------------------- //

class BA_CORE_API_ FTDecayFunction2DItem : public SessionItem
{
public:
    static const QString P_DECAY_LENGTH_X;
    static const QString P_DECAY_LENGTH_Y;
    static const QString P_GAMMA;
    static const QString P_DELTA;
    explicit FTDecayFunction2DItem(const QString& name);
    virtual std::unique_ptr<IFTDecayFunction2D> createFTDecayFunction() const = 0;
    virtual ~FTDecayFunction2DItem() {}

protected:
    void add_decay_property();
    void add_gammadelta_property();
};

class BA_CORE_API_ FTDecayFunction2DCauchyItem : public FTDecayFunction2DItem
{
public:
    FTDecayFunction2DCauchyItem();
    std::unique_ptr<IFTDecayFunction2D> createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction2DGaussItem : public FTDecayFunction2DItem
{
public:
    FTDecayFunction2DGaussItem();
    std::unique_ptr<IFTDecayFunction2D> createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction2DVoigtItem : public FTDecayFunction2DItem
{
public:
    static const QString P_ETA;
    FTDecayFunction2DVoigtItem();
    std::unique_ptr<IFTDecayFunction2D> createFTDecayFunction() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FTDECAYFUNCTIONITEMS_H
