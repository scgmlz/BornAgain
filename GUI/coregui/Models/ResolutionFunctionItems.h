// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ResolutionFunctionItems.h
//! @brief     Defines family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_RESOLUTIONFUNCTIONITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_RESOLUTIONFUNCTIONITEMS_H

#include "GUI/coregui/Models/SessionItem.h"
#include <memory>

class IResolutionFunction2D;

class BA_CORE_API_ ResolutionFunctionItem : public SessionItem
{

public:
    explicit ResolutionFunctionItem(const QString& name);
    virtual ~ResolutionFunctionItem() {}

    virtual std::unique_ptr<IResolutionFunction2D>
    createResolutionFunction(double scale = 1.0) const = 0;
};

class BA_CORE_API_ ResolutionFunctionNoneItem : public ResolutionFunctionItem
{

public:
    ResolutionFunctionNoneItem();
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction(double scale = 1.0) const;
};

class BA_CORE_API_ ResolutionFunction2DGaussianItem : public ResolutionFunctionItem
{

public:
    static const QString P_SIGMA_X;
    static const QString P_SIGMA_Y;
    ResolutionFunction2DGaussianItem();
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction(double scale = 1.0) const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_RESOLUTIONFUNCTIONITEMS_H
