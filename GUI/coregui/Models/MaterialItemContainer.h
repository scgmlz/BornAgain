// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItemContainer.h
//! @brief     Defines class MaterialItemContainer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MATERIALITEMCONTAINER_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MATERIALITEMCONTAINER_H

#include "GUI/coregui/Models/SessionItem.h"

class MaterialItem;

class MaterialItemContainer : public SessionItem
{
public:
    static const QString T_MATERIALS;

    MaterialItemContainer();

    //! Copies MaterialItem, inserts it into the container
    //! and returns a pointer to the copy.
    MaterialItem* insertCopy(MaterialItem* material_item);

    const MaterialItem* findMaterialById(QString id) const;
    MaterialItem* findMaterialById(QString id);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MATERIALITEMCONTAINER_H
