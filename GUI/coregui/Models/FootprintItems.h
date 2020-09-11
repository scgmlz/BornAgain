// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FootprintItems.h
//! @brief     Declares FootprintItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FOOTPRINTITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FOOTPRINTITEMS_H

#include "GUI/coregui/Models/SessionItem.h"

class IFootprintFactor;

class BA_CORE_API_ FootprintItem : public SessionItem
{
public:
    virtual ~FootprintItem();
    virtual std::unique_ptr<IFootprintFactor> createFootprint() const = 0;

protected:
    explicit FootprintItem(const QString& model_type);
};

class BA_CORE_API_ FootprintNoneItem : public FootprintItem
{
public:
    FootprintNoneItem();
    virtual ~FootprintNoneItem();
    std::unique_ptr<IFootprintFactor> createFootprint() const override;
};

class BA_CORE_API_ FootprintGaussianItem : public FootprintItem
{
public:
    static const QString P_VALUE;

    FootprintGaussianItem();
    virtual ~FootprintGaussianItem();
    std::unique_ptr<IFootprintFactor> createFootprint() const override;
};

class BA_CORE_API_ FootprintSquareItem : public FootprintItem
{
public:
    static const QString P_VALUE;

    FootprintSquareItem();
    virtual ~FootprintSquareItem();
    std::unique_ptr<IFootprintFactor> createFootprint() const override;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FOOTPRINTITEMS_H
