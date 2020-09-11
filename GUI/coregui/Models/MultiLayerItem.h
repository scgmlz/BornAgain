// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MultiLayerItem.h
//! @brief     Defines class MultiLayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MULTILAYERITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MULTILAYERITEM_H

#include "GUI/coregui/Models/SessionGraphicsItem.h"

class BA_CORE_API_ MultiLayerItem : public SessionGraphicsItem
{
public:
    static const QString P_CROSS_CORR_LENGTH;
    static const QString P_EXTERNAL_FIELD;
    static const QString T_LAYERS;
    MultiLayerItem();

    QVector<SessionItem*> materialPropertyItems();

private:
    void updateLayers();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MULTILAYERITEM_H
