//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/TransformToDomain.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Scattering/IFormFactor.h"

using SessionItemUtils::SetVectorItem;

namespace {
const QString abundance_tooltip = "Proportion of this type of particles normalized to the \n"
                                  "total number of particles in the layout";

const QString position_tooltip = "Relative position of the particle's reference point \n"
                                 "in the coordinate system of the parent (nm)";

} // namespace

const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_ABUNDANCE = QString::fromStdString("Abundance");
const QString ParticleItem::P_MATERIAL = "Material";
const QString ParticleItem::P_POSITION = "Position Offset";
const QString ParticleItem::T_TRANSFORMATION = "Transformation Tag";

ParticleItem::ParticleItem() : SessionGraphicsItem("Particle") {
    addGroupProperty(P_FORM_FACTOR, "Form Factor");
    addProperty(P_MATERIAL, MaterialItemUtils::defaultMaterialProperty().variant())
        ->setToolTip("Material of particle")
        .setEditorType("ExtMaterialEditor");

    addProperty(P_ABUNDANCE, 1.0)
        ->setLimits(RealLimits::limited(0.0, 1.0))
        .setDecimals(3)
        .setToolTip(abundance_tooltip);
    addGroupProperty(P_POSITION, "Vector")->setToolTip(position_tooltip);

    registerTag(T_TRANSFORMATION, 0, 1, QStringList() << "Rotation");
    setDefaultTag(T_TRANSFORMATION);

    addTranslator(VectorParameterTranslator(P_POSITION, "Position"));
    addTranslator(RotationTranslator());

    mapper()->setOnParentChange(
        [this](SessionItem* newParent) { updatePropertiesAppearance(newParent); });
}

std::unique_ptr<Particle> ParticleItem::createParticle() const {
    auto& ffItem = groupItem<FormFactorItem>(ParticleItem::P_FORM_FACTOR);
    auto material = TransformToDomain::createDomainMaterial(*this);
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

    auto particle = std::make_unique<Particle>(*material, *ffItem.createFormFactor());
    particle->setAbundance(abundance);

    TransformToDomain::setTransformationInfo(particle.get(), *this);

    return particle;
}

QVector<SessionItem*> ParticleItem::materialPropertyItems() {
    auto item = getItem(P_MATERIAL);
    if (!item)
        return {};
    return {item};
}

//! Updates enabled/disabled for particle position and particle abundance depending on context.

void ParticleItem::updatePropertiesAppearance(SessionItem* newParent) {
    if (SessionItemUtils::HasOwnAbundance(newParent)) {
        setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
        getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
        if (isShellParticle()) {
            kvector_t zero_vector;
            SetVectorItem(*this, ParticleItem::P_POSITION, zero_vector);
            SessionItem* positionItem = getItem(ParticleItem::P_POSITION);
            positionItem->setEnabled(false);
        }
    } else {
        getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        getItem(ParticleItem::P_POSITION)->setEnabled(true);
    }
}

//! Returns true if this particle is a shell particle.

bool ParticleItem::isShellParticle() const {
    if (!parent())
        return false;

    return parent()->modelType() == "ParticleCoreShell"
           && parent()->tagFromItem(this) == ParticleCoreShellItem::T_SHELL;
}

//! Returns true if this particle is directly connected to a ParticleLayout

bool ParticleItem::parentIsParticleLayout() const {
    if (!parent())
        return false;

    return parent()->modelType() == "ParticleLayout";
}
