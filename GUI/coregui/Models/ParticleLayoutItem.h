// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleLayoutItem.h
//! @brief     Defines class ParticleLayoutItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARTICLELAYOUTITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARTICLELAYOUTITEM_H

#include "GUI/coregui/Models/SessionGraphicsItem.h"

class BA_CORE_API_ ParticleLayoutItem : public SessionGraphicsItem
{
public:
    static const QString P_TOTAL_DENSITY;
    static const QString P_WEIGHT;
    static const QString T_PARTICLES;
    static const QString T_INTERFERENCE;
    ParticleLayoutItem();

private:
    void updateDensityAppearance();
    void updateDensityValue();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARTICLELAYOUTITEM_H
