// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleCompositionItem.h
//! @brief     Defines class ParticleCompositionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARTICLECOMPOSITIONITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARTICLECOMPOSITIONITEM_H

#include "Core/Particle/ParticleComposition.h"
#include "GUI/coregui/Models/SessionGraphicsItem.h"

class BA_CORE_API_ ParticleCompositionItem : public SessionGraphicsItem
{
public:
    const static QString T_PARTICLES;
    ParticleCompositionItem();
    std::unique_ptr<ParticleComposition> createParticleComposition() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARTICLECOMPOSITIONITEM_H
