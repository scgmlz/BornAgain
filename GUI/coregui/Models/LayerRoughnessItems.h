// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerRoughnessItems.h
//! @brief     Defines classes LayerRoughnessItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_LAYERROUGHNESSITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_LAYERROUGHNESSITEMS_H

#include "GUI/coregui/Models/SessionItem.h"

class BA_CORE_API_ LayerZeroRoughnessItem : public SessionItem
{
public:
    LayerZeroRoughnessItem();
};

class BA_CORE_API_ LayerBasicRoughnessItem : public SessionItem
{
public:
    static const QString P_SIGMA;
    static const QString P_HURST;
    static const QString P_LATERAL_CORR_LENGTH;
    LayerBasicRoughnessItem();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_LAYERROUGHNESSITEMS_H
