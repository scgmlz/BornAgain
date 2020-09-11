// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.cpp
//! @brief     Implements RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/Units.h"
#include "Core/Particle/FormFactorCrystal.h"
#include "Core/Particle/IParticle.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/Scattering/IFormFactorDecorator.h"
#include "Core/Scattering/Rotations.h"
#include "Core/includeIncludes/InterferenceFunctions.h"
#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/RotationItems.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/TransformationItem.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/Views/RealSpaceWidgets/Particle3DContainer.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceCanvas.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceMesoCrystalUtils.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceModel.h"
#include "GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.h"
#include "GUI/coregui/mainwindow/AppSvc.h"

namespace
{
const double layerBorderWidth = 10.0;

const IFormFactor* getUnderlyingFormFactor(const IFormFactor* ff)
{
    // TRUE as long as ff is of IFormFactorDecorator (or its derived) type
    while (dynamic_cast<const IFormFactorDecorator*>(ff))
        ff = dynamic_cast<const IFormFactorDecorator*>(ff)->getFormFactor();

    return ff;
}

kvector_t to_kvector(const QVector3D& origin)
{
    return kvector_t(static_cast<double>(origin.x()), static_cast<double>(origin.y()),
                     static_cast<double>(origin.z()));
}

} // namespace

// compute cumulative abundances of particles
QVector<double> RealSpaceBuilderUtils::computeCumulativeAbundances(const SessionItem& layoutItem)
{
    // Retrieving abundances of particles
    double total_abundance = 0.0;
    QVector<double> cumulative_abundances;

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES)) {
        total_abundance =
            total_abundance + particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

        cumulative_abundances.append(total_abundance);
    }

    return cumulative_abundances;
}

void RealSpaceBuilderUtils::populateParticlesAtLatticePositions(
    const std::vector<std::vector<double>>& lattice_positions,
    const std::vector<Particle3DContainer>& particle3DContainer_vector, RealSpaceModel* model,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    double layer_size = sceneGeometry.layer_size();
    double layer_thickness =
        std::max(sceneGeometry.layer_top_thickness(), sceneGeometry.layer_bottom_thickness());

    for (std::vector<double> position : lattice_positions) {
        // for random selection of particles based on their abundances
        double rand_num = (rand() / static_cast<double>(RAND_MAX)); // (between 0 and 1)
        int k = 0;

        for (const auto& particle3DContainer : particle3DContainer_vector) {
            if (rand_num <= particle3DContainer.cumulativeAbundance()) {
                // lattice position + location (TO BE ADDED)
                double pos_x = position[0];
                double pos_y = position[1];
                double pos_z = 0;

                if (std::abs(pos_x) <= layer_size - layerBorderWidth
                    && std::abs(pos_y) <= layer_size - layerBorderWidth
                    && std::abs(pos_z) <= layer_thickness) {

                    builder3D->populateParticleFromParticle3DContainer(
                        model, particle3DContainer,
                        QVector3D(static_cast<float>(position[0]), static_cast<float>(position[1]),
                                  static_cast<float>(0)));
                }
                break;
            } else
                ++k;
        }
    }
}

// Implement Rotation of a 3D particle using parameters from IRotation Object
RealSpace::Vector3D
RealSpaceBuilderUtils::implementParticleRotationfromIRotation(const IRotation*& rotation)
{
    double alpha = 0.0;
    double beta = 0.0;
    double gamma = 0.0;

    if (auto rotX = dynamic_cast<const RotationX*>(rotation)) {
        beta = rotX->getAngle(); // about x-axis
    } else if (auto rotY = dynamic_cast<const RotationY*>(rotation)) {
        alpha = Units::deg2rad(90.0);
        beta = rotY->getAngle(); // about y-axis
        gamma = Units::deg2rad(-90.0);
    } else if (auto rotZ = dynamic_cast<const RotationZ*>(rotation)) {
        alpha = rotZ->getAngle(); // about z-axis
    } else if (auto rotEuler = dynamic_cast<const RotationEuler*>(rotation)) {
        alpha = rotEuler->getAlpha();
        beta = rotEuler->getBeta();
        gamma = rotEuler->getGamma();
    }
    return RealSpace::Vector3D(static_cast<float>(alpha), static_cast<float>(beta),
                               static_cast<float>(gamma));
}

void RealSpaceBuilderUtils::applyParticleTransformations(const Particle& particle,
                                                         RealSpace::Particles::Particle& particle3D,
                                                         const kvector_t& origin)
{
    // rotation
    RealSpace::Vector3D particle_rotate;
    const IRotation* rotation = particle.rotation();

    if (rotation)
        particle_rotate = implementParticleRotationfromIRotation(rotation);

    // translation
    float x = static_cast<float>(particle.position().x());
    float y = static_cast<float>(particle.position().y());
    float z = static_cast<float>(particle.position().z());
    RealSpace::Vector3D position(x + static_cast<float>(origin.x()),
                                 y + static_cast<float>(origin.y()),
                                 z + static_cast<float>(origin.z()));

    // If the particle belongs to a particle composition, along with the particle's
    // intrinsic transformations, position() and rotation() methods also account for the
    // translation and rotation (if present) of the particle composition as the
    // particleComposition's decompose() method already does this

    particle3D.addTransform(particle_rotate, position);
}

void RealSpaceBuilderUtils::applyParticleCoreShellTransformations(
    const Particle& particle, RealSpace::Particles::Particle& particle3D,
    const ParticleCoreShell& particleCoreShell, const kvector_t& origin)
{
    std::unique_ptr<Particle> P_clone(particle.clone()); // clone of the current particle

    // rotation
    RealSpace::Vector3D particle_rotate;
    const IRotation* rotationCoreShell = particleCoreShell.rotation();

    if (rotationCoreShell)
        P_clone->rotate(*rotationCoreShell);

    const IRotation* rotation = P_clone->rotation();

    if (rotation)
        particle_rotate = implementParticleRotationfromIRotation(rotation);

    // translation
    kvector_t positionCoreShell = particleCoreShell.position();

    P_clone->translate(positionCoreShell);

    RealSpace::Vector3D position(static_cast<float>(P_clone->position().x() + origin.x()),
                                 static_cast<float>(P_clone->position().y() + origin.y()),
                                 static_cast<float>(P_clone->position().z() + origin.z()));

    particle3D.transform(particle_rotate, position);
}

void RealSpaceBuilderUtils::applyParticleColor(const Particle& particle,
                                               RealSpace::Particles::Particle& particle3D,
                                               double alpha)
{
    // assign correct color to the particle from the knowledge of its material
    const Material* particle_material = particle.material();
    QString material_name = QString::fromStdString(particle_material->getName());
    auto materialItem = AppSvc::materialModel()->materialFromName(material_name);
    QColor color = materialItem->color();
    color.setAlphaF(alpha);
    particle3D.color = color;
}

std::vector<Particle3DContainer>
RealSpaceBuilderUtils::particle3DContainerVector(const SessionItem& layoutItem,
                                                 const QVector3D& origin)
{
    std::vector<Particle3DContainer> particle3DContainer_vector;

    double total_abundance = computeCumulativeAbundances(layoutItem).last();

    double cumulative_abundance = 0;

    for (auto particleItem : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES)) {

        Particle3DContainer particle3DContainer;

        if (particleItem->modelType() == "Particle") {
            auto pItem = dynamic_cast<const ParticleItem*>(particleItem);
            auto particle = pItem->createParticle();
            particle3DContainer = singleParticle3DContainer(*particle, total_abundance, origin);
        } else if (particleItem->modelType() == "ParticleCoreShell") {
            auto particleCoreShellItem = dynamic_cast<const ParticleCoreShellItem*>(particleItem);
            // If there is no CORE or SHELL to populate inside ParticleCoreShellItem
            if (!particleCoreShellItem->getItem(ParticleCoreShellItem::T_CORE)
                || !particleCoreShellItem->getItem(ParticleCoreShellItem::T_SHELL))
                continue;
            auto particleCoreShell = particleCoreShellItem->createParticleCoreShell();
            particle3DContainer =
                particleCoreShell3DContainer(*particleCoreShell, total_abundance, origin);
        } else if (particleItem->modelType() == "ParticleComposition") {
            auto particleCompositionItem =
                dynamic_cast<const ParticleCompositionItem*>(particleItem);
            // If there is no particle to populate inside ParticleCompositionItem
            if (!particleCompositionItem->getItem(ParticleCompositionItem::T_PARTICLES))
                continue;
            auto particleComposition = particleCompositionItem->createParticleComposition();
            particle3DContainer =
                particleComposition3DContainer(*particleComposition, total_abundance, origin);
        } else if (particleItem->modelType() == "ParticleDistribution") {
            auto particleDistributionItem =
                dynamic_cast<const ParticleDistributionItem*>(particleItem);
            // If there is no particle to populate inside ParticleDistributionItem
            if (!particleDistributionItem->getItem(ParticleDistributionItem::T_PARTICLES))
                continue;
            auto particleDistribution = particleDistributionItem->createParticleDistribution();
            std::vector<Particle3DContainer> pd_ContainerVector =
                particleDistribution3DContainer(*particleDistribution, total_abundance, origin);
            for (size_t i = 0; i < pd_ContainerVector.size(); ++i) {
                cumulative_abundance += pd_ContainerVector[i].cumulativeAbundance();
                pd_ContainerVector[i].setCumulativeAbundance(cumulative_abundance);
                particle3DContainer_vector.emplace_back(std::move(pd_ContainerVector[i]));
            }
            continue;
        } else if (particleItem->modelType() == "MesoCrystal") {
            auto mesoCrystalItem = dynamic_cast<const MesoCrystalItem*>(particleItem);
            // If there is no particle to populate inside MesoCrystalItem
            if (!mesoCrystalItem->getItem(MesoCrystalItem::T_BASIS_PARTICLE))
                continue;
            particle3DContainer = RealSpaceBuilderUtils::mesoCrystal3DContainer(
                *mesoCrystalItem, total_abundance, origin);
        }

        cumulative_abundance += particle3DContainer.cumulativeAbundance();
        particle3DContainer.setCumulativeAbundance(cumulative_abundance);
        particle3DContainer_vector.emplace_back(std::move(particle3DContainer));
    }

    return particle3DContainer_vector;
}

Particle3DContainer RealSpaceBuilderUtils::singleParticle3DContainer(const Particle& particle,
                                                                     double total_abundance,
                                                                     const QVector3D& origin)
{
    std::unique_ptr<Particle> P_clone(particle.clone()); // clone of the particle

    std::unique_ptr<const IFormFactor> particleff(P_clone->createFormFactor());
    auto ff = getUnderlyingFormFactor(particleff.get());

    auto particle3D = TransformTo3D::createParticlefromIFormFactor(ff);
    applyParticleTransformations(*P_clone, *particle3D, to_kvector(origin));
    applyParticleColor(*P_clone, *particle3D);

    Particle3DContainer singleParticle3DContainer;
    singleParticle3DContainer.addParticle(particle3D.release(), false);
    singleParticle3DContainer.setCumulativeAbundance(P_clone->abundance() / total_abundance);
    singleParticle3DContainer.setParticleType("Particle");

    return singleParticle3DContainer;
}

Particle3DContainer
RealSpaceBuilderUtils::particleCoreShell3DContainer(const ParticleCoreShell& particleCoreShell,
                                                    double total_abundance, const QVector3D& origin)
{
    // clone of the particleCoreShell
    std::unique_ptr<ParticleCoreShell> PCS_clone(particleCoreShell.clone());

    std::unique_ptr<const IFormFactor> coreParticleff(
        PCS_clone->coreParticle()->createFormFactor());
    std::unique_ptr<const IFormFactor> shellParticleff(
        PCS_clone->shellParticle()->createFormFactor());

    auto coreff = getUnderlyingFormFactor(coreParticleff.get());
    auto shellff = getUnderlyingFormFactor(shellParticleff.get());

    auto coreParticle3D = TransformTo3D::createParticlefromIFormFactor(coreff);
    auto shellParticle3D = TransformTo3D::createParticlefromIFormFactor(shellff);

    // core
    applyParticleCoreShellTransformations(*PCS_clone->coreParticle(), *coreParticle3D, *PCS_clone,
                                          to_kvector(origin));
    applyParticleColor(*PCS_clone->coreParticle(), *coreParticle3D);

    // shell (set an alpha value of 0.5 for transparency)
    applyParticleCoreShellTransformations(*PCS_clone->shellParticle(), *shellParticle3D, *PCS_clone,
                                          to_kvector(origin));
    applyParticleColor(*PCS_clone->shellParticle(), *shellParticle3D, 0.5);

    Particle3DContainer particleCoreShell3DContainer;

    particleCoreShell3DContainer.addParticle(coreParticle3D.release(), false); // index 0
    particleCoreShell3DContainer.addParticle(shellParticle3D.release(), true); // index 1
    particleCoreShell3DContainer.setCumulativeAbundance(PCS_clone->abundance() / total_abundance);
    particleCoreShell3DContainer.setParticleType("ParticleCoreShell");

    return particleCoreShell3DContainer;
}

Particle3DContainer RealSpaceBuilderUtils::particleComposition3DContainer(
    const ParticleComposition& particleComposition, double total_abundance, const QVector3D& origin)
{
    // clone of the particleComposition
    std::unique_ptr<ParticleComposition> PC_clone(particleComposition.clone());

    SafePointerVector<IParticle> pc_vector = PC_clone->decompose();

    Particle3DContainer particleComposition3DContainer;

    for (const IParticle* pc_particle : pc_vector) {
        Particle3DContainer particle3DContainer;
        // no abundances are associated with the individual components of ParticleComposition
        if (dynamic_cast<const ParticleCoreShell*>(pc_particle)) {
            auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pc_particle);
            particle3DContainer = particleCoreShell3DContainer(*particleCoreShell, 1.0, origin);
        } else if (dynamic_cast<const MesoCrystal*>(pc_particle)) {
            // TODO: Implement method to populate MesoCrystal from CORE and NOT from MesoCrystalItem
            // as it is done currently in RealSpaceBuilderUtils::mesoCrystal3DContainer
            std::ostringstream ostr;
            ostr << "Sorry, MesoCrystal inside ParticleComposition not yet implemented";
            ostr << "\n\nStay tuned!";
            throw Exceptions::ClassInitializationException(ostr.str());
        } else {
            auto particle = dynamic_cast<const Particle*>(pc_particle);
            particle3DContainer = singleParticle3DContainer(*particle, 1.0, origin);
        }
        // add particles from 3Dcontainer of core-shell/particle into particleComposition3DContainer
        for (size_t i = 0; i < particle3DContainer.containerSize(); ++i) {
            particleComposition3DContainer.addParticle(
                particle3DContainer.createParticle(i).release(),
                particle3DContainer.particle3DBlend(i));
        }
    }
    // set the correct abundance for the entire ParticleComposition
    particleComposition3DContainer.setCumulativeAbundance(PC_clone->abundance() / total_abundance);
    particleComposition3DContainer.setParticleType("ParticleComposition");
    return particleComposition3DContainer;
}

std::vector<Particle3DContainer> RealSpaceBuilderUtils::particleDistribution3DContainer(
    const ParticleDistribution& particleDistribution, double total_abundance,
    const QVector3D& origin)
{
    auto pd_vector = particleDistribution.generateParticles();

    std::vector<Particle3DContainer> particleDistribution3DContainer_vector;

    for (auto pd_particle : pd_vector) {
        Particle3DContainer particle3DContainer;
        if (dynamic_cast<const ParticleComposition*>(pd_particle)) {
            auto particleComposition = dynamic_cast<const ParticleComposition*>(pd_particle);
            particle3DContainer =
                particleComposition3DContainer(*particleComposition, total_abundance, origin);
        } else if (dynamic_cast<const ParticleCoreShell*>(pd_particle)) {
            auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pd_particle);
            particle3DContainer =
                particleCoreShell3DContainer(*particleCoreShell, total_abundance, origin);
        } else if (dynamic_cast<const MesoCrystal*>(pd_particle)) {
            // TODO: Implement method to populate MesoCrystal from CORE and NOT from MesoCrystalItem
            // as it is done currently in RealSpaceBuilderUtils::mesoCrystal3DContainer
            std::ostringstream ostr;
            ostr << "Sorry, MesoCrystal inside ParticleDistribution not yet implemented";
            ostr << "\n\nStay tuned!";
            throw Exceptions::ClassInitializationException(ostr.str());
        } else {
            auto particle = dynamic_cast<const Particle*>(pd_particle);
            particle3DContainer = singleParticle3DContainer(*particle, total_abundance, origin);
        }
        particleDistribution3DContainer_vector.emplace_back(std::move(particle3DContainer));
    }
    return particleDistribution3DContainer_vector;
}

Particle3DContainer
RealSpaceBuilderUtils::mesoCrystal3DContainer(const MesoCrystalItem& mesoCrystalItem,
                                              double total_abundance, const QVector3D& origin)
{
    RealSpaceMesoCrystal mesoCrystalUtils(&mesoCrystalItem, total_abundance, origin);

    Particle3DContainer mesoCrystal3DContainer = mesoCrystalUtils.populateMesoCrystal();

    return mesoCrystal3DContainer;
}
