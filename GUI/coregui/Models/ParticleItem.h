// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleItem.h
//! @brief     Defines class ParticleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARTICLEITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARTICLEITEM_H

#include "GUI/coregui/Models/SessionGraphicsItem.h"

class Particle;

class BA_CORE_API_ ParticleItem : public SessionGraphicsItem
{
public:
    static const QString P_FORM_FACTOR;
    static const QString P_ABUNDANCE;
    static const QString P_MATERIAL;
    static const QString P_POSITION;
    static const QString T_TRANSFORMATION;

    ParticleItem();

    std::unique_ptr<Particle> createParticle() const;
    QVector<SessionItem*> materialPropertyItems();

private:
    void updatePropertiesAppearance(SessionItem*);
    bool isShellParticle() const;
    bool parentIsParticleLayout() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARTICLEITEM_H
