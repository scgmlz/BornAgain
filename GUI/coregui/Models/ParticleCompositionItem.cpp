// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleCompositionItem.cpp
//! @brief     Implements class ParticleCompositionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/TransformToDomain.h"

namespace
{
const QString abundance_tooltip = "Proportion of this type of particles normalized to the \n"
                                  "total number of particles in the layout";

const QString position_tooltip = "Relative position of the particle's reference point \n"
                                 "in the coordinate system of the parent (nm)";
} // namespace

const QString ParticleCompositionItem::T_PARTICLES = "Particle Tag";

// TODO make ParticleCoreShellItem and ParticleItem to derive from common base.

ParticleCompositionItem::ParticleCompositionItem() : SessionGraphicsItem("ParticleComposition")
{
    setToolTip("Composition of particles with fixed positions");

    addProperty(ParticleItem::P_ABUNDANCE, 1.0)
        ->setLimits(RealLimits::limited(0.0, 1.0))
        .setDecimals(3)
        .setToolTip(abundance_tooltip);

    addGroupProperty(ParticleItem::P_POSITION, "Vector")->setToolTip(position_tooltip);

    registerTag(T_PARTICLES, 0, -1,
                QStringList() << "Particle"
                              << "ParticleCoreShell"
                              << "ParticleComposition"
                              << "MesoCrystal");
    setDefaultTag(T_PARTICLES);
    registerTag(ParticleItem::T_TRANSFORMATION, 0, 1, QStringList() << "Rotation");

    addTranslator(VectorParameterTranslator(ParticleItem::P_POSITION, "Position"));
    addTranslator(RotationTranslator());

    mapper()->setOnParentChange([this](SessionItem* parent) {
        if (SessionItemUtils::HasOwnAbundance(parent)) {
            setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
        } else {
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        }
    });
}

std::unique_ptr<ParticleComposition> ParticleCompositionItem::createParticleComposition() const
{
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    auto P_composition = std::make_unique<ParticleComposition>();
    P_composition->setAbundance(abundance);
    QVector<SessionItem*> childlist = children();
    for (int i = 0; i < childlist.size(); ++i) {
        if (childlist[i]->modelType() == "Particle") {
            auto* particle_item = static_cast<ParticleItem*>(childlist[i]);
            auto P_particle = particle_item->createParticle();
            if (P_particle) {
                P_composition->addParticle(*P_particle);
            }
        } else if (childlist[i]->modelType() == "ParticleCoreShell") {
            auto* particle_coreshell_item = static_cast<ParticleCoreShellItem*>(childlist[i]);
            auto P_particle_coreshell = particle_coreshell_item->createParticleCoreShell();
            if (P_particle_coreshell) {
                P_composition->addParticle(*P_particle_coreshell);
            }
        } else if (childlist[i]->modelType() == "ParticleComposition") {
            auto* particlecomposition_item = static_cast<ParticleCompositionItem*>(childlist[i]);
            auto P_child_composition = particlecomposition_item->createParticleComposition();
            if (P_child_composition) {
                P_composition->addParticle(*P_child_composition);
            }
        } else if (childlist[i]->modelType() == "MesoCrystal") {
            auto* mesocrystal_item = static_cast<MesoCrystalItem*>(childlist[i]);
            auto P_child_meso = mesocrystal_item->createMesoCrystal();
            if (P_child_meso) {
                P_composition->addParticle(*P_child_meso);
            }
        }
    }
    TransformToDomain::setTransformationInfo(P_composition.get(), *this);

    return P_composition;
}
