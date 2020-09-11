// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FTDistributionItems.h
//! @brief     Defines FTDistribution1DItem's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FTDISTRIBUTIONITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FTDISTRIBUTIONITEMS_H

#include "Core/Correlations/FTDistributions1D.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "GUI/coregui/Models/SessionItem.h"

class BA_CORE_API_ FTDistribution1DItem : public SessionItem
{
public:
    static const QString P_OMEGA;
    explicit FTDistribution1DItem(const QString& name);
    virtual std::unique_ptr<IFTDistribution1D> createFTDistribution() const = 0;
    virtual ~FTDistribution1DItem() {}

protected:
    void add_omega_property();
};

class BA_CORE_API_ FTDistribution1DCauchyItem : public FTDistribution1DItem
{
public:
    FTDistribution1DCauchyItem();
    std::unique_ptr<IFTDistribution1D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DGaussItem : public FTDistribution1DItem
{
public:
    FTDistribution1DGaussItem();
    std::unique_ptr<IFTDistribution1D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DGateItem : public FTDistribution1DItem
{
public:
    FTDistribution1DGateItem();
    std::unique_ptr<IFTDistribution1D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DTriangleItem : public FTDistribution1DItem
{
public:
    FTDistribution1DTriangleItem();
    std::unique_ptr<IFTDistribution1D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DCosineItem : public FTDistribution1DItem
{
public:
    FTDistribution1DCosineItem();
    std::unique_ptr<IFTDistribution1D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution1DVoigtItem : public FTDistribution1DItem
{
public:
    static const QString P_ETA;
    FTDistribution1DVoigtItem();
    std::unique_ptr<IFTDistribution1D> createFTDistribution() const;
};

// --------------------------------------------------------------------------------------------- //

class BA_CORE_API_ FTDistribution2DItem : public SessionItem
{
public:
    static const QString P_OMEGA_X;
    static const QString P_OMEGA_Y;
    static const QString P_GAMMA;
    explicit FTDistribution2DItem(const QString& name);
    virtual std::unique_ptr<IFTDistribution2D> createFTDistribution() const = 0;

protected:
    void add_omega_properties();
    void add_gamma_property();
    void add_properties();
};

class BA_CORE_API_ FTDistribution2DCauchyItem : public FTDistribution2DItem
{
public:
    FTDistribution2DCauchyItem();
    std::unique_ptr<IFTDistribution2D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution2DGaussItem : public FTDistribution2DItem
{
public:
    FTDistribution2DGaussItem();
    std::unique_ptr<IFTDistribution2D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution2DGateItem : public FTDistribution2DItem
{
public:
    FTDistribution2DGateItem();
    std::unique_ptr<IFTDistribution2D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution2DConeItem : public FTDistribution2DItem
{
public:
    FTDistribution2DConeItem();
    std::unique_ptr<IFTDistribution2D> createFTDistribution() const;
};

class BA_CORE_API_ FTDistribution2DVoigtItem : public FTDistribution2DItem
{

public:
    static const QString P_ETA;
    FTDistribution2DVoigtItem();
    std::unique_ptr<IFTDistribution2D> createFTDistribution() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FTDISTRIBUTIONITEMS_H
