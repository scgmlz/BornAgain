// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.cpp
//! @brief     Implements class RealSpaceBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h"
#include "Core/Basics/Units.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/includeIncludes/InterferenceFunctions.h"
#include "GUI/ba3d/model/layer.h"
#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/RealSpaceWidgets/Particle3DContainer.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceCanvas.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceModel.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpacePositionBuilder.h"
#include "GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.h"
#include <QDebug>

namespace
{
std::unique_ptr<IInterferenceFunction> GetInterferenceFunction(const SessionItem& layoutItem);
}

RealSpaceBuilder::RealSpaceBuilder(QWidget* parent) : QWidget(parent) {}

RealSpaceBuilder::~RealSpaceBuilder() {}

void RealSpaceBuilder::populate(RealSpaceModel* model, const SessionItem& item,
                                const SceneGeometry& sceneGeometry,
                                const RealSpace::Camera::Position& cameraPosition)
{
    // default value of cameraPosition is in RealSpaceBuilder.h

    model->defCamPos = cameraPosition;

    if (item.modelType() == "MultiLayer")
        populateMultiLayer(model, item, sceneGeometry);

    else if (item.modelType() == "Layer")
        populateLayer(model, item, sceneGeometry);

    else if (item.modelType() == "ParticleLayout")
        populateLayout(model, item, sceneGeometry);

    else if (item.modelType() == "Particle")
        populateParticleFromParticleItem(model, item);

    else if (item.modelType() == "ParticleComposition")
        populateParticleFromParticleItem(model, item);

    else if (item.modelType() == "ParticleCoreShell")
        populateParticleFromParticleItem(model, item);

    else if (item.modelType() == "ParticleDistribution")
        populateParticleFromParticleItem(model, item);

    else if (item.modelType() == "MesoCrystal")
        populateParticleFromParticleItem(model, item);
}

void RealSpaceBuilder::populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                                          const SceneGeometry& sceneGeometry, const QVector3D&)
{
    double total_height(0.0);
    int index(0);
    for (auto layer : item.getItems(MultiLayerItem::T_LAYERS)) {

        bool isTopLayer = index == 0 ? true : false;
        populateLayer(model, *layer, sceneGeometry,
                      QVector3D(0, 0, static_cast<float>(-total_height)), isTopLayer);

        if (index != 0)
            total_height += TransformTo3D::visualLayerThickness(*layer, sceneGeometry);

        ++index;
    }
}

void RealSpaceBuilder::populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                                     const SceneGeometry& sceneGeometry, const QVector3D& origin,
                                     const bool isTopLayer)
{
    auto layer = TransformTo3D::createLayer(layerItem, sceneGeometry, origin);
    if (layer && !isTopLayer)
        model->addBlend(layer.release());

    for (auto layout : layerItem.getItems(LayerItem::T_LAYOUTS))
        populateLayout(model, *layout, sceneGeometry, origin);
}

void RealSpaceBuilder::populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                                      const SceneGeometry& sceneGeometry, const QVector3D& origin)
{
    ASSERT(layoutItem.modelType() == "ParticleLayout");

    // If there is no particle to populate
    if (!layoutItem.getItem(ParticleLayoutItem::T_PARTICLES))
        return;

    double layer_size = sceneGeometry.layer_size();
    double total_density = layoutItem.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble();

    auto particle3DContainer_vector =
        RealSpaceBuilderUtils::particle3DContainerVector(layoutItem, origin);

    auto interference = GetInterferenceFunction(layoutItem);

    RealSpacePositionBuilder pos_builder;
    interference->accept(&pos_builder);
    std::vector<std::vector<double>> lattice_positions =
        pos_builder.generatePositions(layer_size, total_density);
    RealSpaceBuilderUtils::populateParticlesAtLatticePositions(
        lattice_positions, particle3DContainer_vector, model, sceneGeometry, this);
}

void RealSpaceBuilder::populateParticleFromParticleItem(RealSpaceModel* model,
                                                        const SessionItem& particleItem) const
{
    Particle3DContainer particle3DContainer;
    if (particleItem.modelType() == "Particle") {
        auto pItem = dynamic_cast<const ParticleItem*>(&particleItem);
        auto particle = pItem->createParticle();
        particle3DContainer = RealSpaceBuilderUtils::singleParticle3DContainer(*particle);
    } else if (particleItem.modelType() == "ParticleCoreShell") {
        auto particleCoreShellItem = dynamic_cast<const ParticleCoreShellItem*>(&particleItem);
        // If there is no CORE or SHELL to populate inside ParticleCoreShellItem
        if (!particleCoreShellItem->getItem(ParticleCoreShellItem::T_CORE)
            || !particleCoreShellItem->getItem(ParticleCoreShellItem::T_SHELL))
            return;
        auto particleCoreShell = particleCoreShellItem->createParticleCoreShell();
        particle3DContainer =
            RealSpaceBuilderUtils::particleCoreShell3DContainer(*particleCoreShell);
    } else if (particleItem.modelType() == "ParticleComposition") {
        auto particleCompositionItem = dynamic_cast<const ParticleCompositionItem*>(&particleItem);
        // If there is no particle to populate inside ParticleCompositionItem
        if (!particleCompositionItem->getItem(ParticleCompositionItem::T_PARTICLES))
            return;
        auto particleComposition = particleCompositionItem->createParticleComposition();
        particle3DContainer =
            RealSpaceBuilderUtils::particleComposition3DContainer(*particleComposition);
    } else if (particleItem.modelType() == "ParticleDistribution") {
        auto particleDistributionItem =
            dynamic_cast<const ParticleDistributionItem*>(&particleItem);
        // If there is no particle to populate inside ParticleDistributionItem
        if (!particleDistributionItem->getItem(ParticleDistributionItem::T_PARTICLES))
            return;
        // show nothing when ParticleDistributionItem is selected
    } else if (particleItem.modelType() == "MesoCrystal") {
        auto mesoCrystalItem = dynamic_cast<const MesoCrystalItem*>(&particleItem);
        // If there is no particle to populate inside MesoCrystalItem
        if (!mesoCrystalItem->getItem(MesoCrystalItem::T_BASIS_PARTICLE))
            return;
        particle3DContainer = RealSpaceBuilderUtils::mesoCrystal3DContainer(*mesoCrystalItem);
    }

    populateParticleFromParticle3DContainer(model, particle3DContainer);
}

void RealSpaceBuilder::populateParticleFromParticle3DContainer(
    RealSpaceModel* model, const Particle3DContainer& particle3DContainer,
    const QVector3D& lattice_position) const
{
    if (particle3DContainer.containerSize()) {
        for (size_t i = 0; i < particle3DContainer.containerSize(); ++i) {
            auto particle3D = particle3DContainer.createParticle(i);
            particle3D->addTranslation(lattice_position);
            if (particle3D) {
                if (!particle3DContainer.particle3DBlend(i))
                    model->add(particle3D.release());
                else
                    model->addBlend(particle3D.release()); // use addBlend() for transparent object
            }
        }
    }
}

namespace
{
std::unique_ptr<IInterferenceFunction> GetInterferenceFunction(const SessionItem& layoutItem)
{
    auto interferenceLattice = layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE);
    if (interferenceLattice) {
        auto interferenceItem = static_cast<const InterferenceFunctionItem*>(interferenceLattice);
        auto P_interference = interferenceItem->createInterferenceFunction();
        if (P_interference)
            return std::unique_ptr<IInterferenceFunction>(P_interference.release());
    }
    return std::make_unique<InterferenceFunctionNone>();
}
} // namespace
