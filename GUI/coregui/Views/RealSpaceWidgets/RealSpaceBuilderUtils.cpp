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

#include "RealSpaceBuilderUtils.h"
#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "RealSpaceCanvas.h"
#include "SessionItem.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "ParticleLayoutItem.h"
#include "ParticleItem.h"
#include "VectorItem.h"
#include "InterferenceFunctionItems.h"
#include "Lattice2DItems.h"
#include "Units.h"
#include "TransformationItem.h"
#include "RotationItems.h"
#include "Rotations.h"
#include "Particle.h"
#include <AppSvc.h>
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "ParticleCoreShell.h"
#include "Rotations.h"
#include "ParticleCompositionItem.h"
#include "IParticle.h"
#include "IFormFactorDecorator.h"
#include "Particle.h"
#include "ParticleCoreShellItem.h"
#include "TransformTo3D.h"
#include "ParticleDistribution.h"
#include "InterferenceFunctions.h"

namespace
{
    const IFormFactor* getUnderlyingFormFactor(const IFormFactor *ff)
    {
        // TRUE as long as ff is of IFormFactorDecorator (or its derived) type
        while(dynamic_cast<const IFormFactorDecorator*>(ff))
            ff = dynamic_cast<const IFormFactorDecorator*>(ff)->getFormFactor();

        return ff;
    }
}

Particle3DType::Particle3DType(const Particle3DType &p3D) :
    m_cumulative_abundance(p3D.m_cumulative_abundance),
    m_type(p3D.m_type)
{
    m_3Dparticles.resize(p3D.m_3Dparticles.size());
    for (int i = 0; i < m_3Dparticles.size(); ++i)
        m_3Dparticles[i] = new RealSpace::Particles::Particle(*p3D.m_3Dparticles[i]);
}

Particle3DType &Particle3DType::operator=(const Particle3DType &right)
{
    if (this == &right) return *this;

    clear3Dparticles();

    m_cumulative_abundance = right.m_cumulative_abundance;
    m_type = right.m_type;

    m_3Dparticles.resize(right.m_3Dparticles.size());
    for (int i = 0; i < m_3Dparticles.size(); ++i)
        m_3Dparticles[i] = new RealSpace::Particles::Particle(*right.m_3Dparticles[i]);
    return *this;
}

Particle3DType::~Particle3DType()
{
    clear3Dparticles();
}

void Particle3DType::clear3Dparticles()
{
    for (auto it = m_3Dparticles.begin(); it != m_3Dparticles.end(); ++it)
        delete(*it);

    m_3Dparticles.clear();
}

void Particle3DType::add3DParticle(RealSpace::Particles::Particle *particle3D)
{
    m_3Dparticles.append(particle3D);
}

void Particle3DType::setCumulativeAbundance(double cumulative_abundance)
{
    m_cumulative_abundance = cumulative_abundance;
}

void Particle3DType::setType(QString type)
{
    m_type = type;
}

std::unique_ptr<RealSpace::Particles::Particle> Particle3DType::createParticle(const int &index) const
{
    auto particle = new RealSpace::Particles::Particle(*m_3Dparticles.at(index));
    return std::unique_ptr<RealSpace::Particles::Particle>(particle);
}

// compute cumulative abundances of particles
QVector<double> RealSpaceBuilderUtils::computeCumulativeAbundances(const SessionItem &layoutItem)
{
    // Retrieving abundances of particles
    double total_abundance = 0.0;
    QVector<double> cumulative_abundances;

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    {
        total_abundance = total_abundance +
                particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

        cumulative_abundances.append(total_abundance);
    }

    return cumulative_abundances;
}

void RealSpaceBuilderUtils::populateParticlesAtLatticePositions(
        QVector<QVector<double>> lattice_positions, const QVector<Particle3DType> &particle3DType_vector,
        RealSpaceModel *model, const SceneGeometry& sceneGeometry, const RealSpaceBuilder *builder3D)
{
    double layer_size = sceneGeometry.layer_size();
    double layer_thickness = std::max(sceneGeometry.layer_top_thickness(),
                                      sceneGeometry.layer_bottom_thickness());

    for (QVector<double> position : lattice_positions)
    {
        // for random selection of particles based on their abundances
        double rand_num = (rand()/static_cast<double>(RAND_MAX)); // (between 0 and 1)
        int k = 0;

        for (auto& particle3DType : particle3DType_vector)
        {
            if (rand_num <= particle3DType.getCumulativeAbundance())
            {
                // lattice position + location (TO BE ADDED)
                double pos_x = position[0];
                double pos_y = position[1];
                double pos_z = 0;

                if (std::abs(pos_x) <= layer_size && std::abs(pos_y) <= layer_size
                        && std::abs(pos_z) <= layer_thickness)
                {
                    builder3D->populateParticleFromParticle3DType(model, particle3DType,
                                                QVector3D(static_cast<float>(position[0]),
                                                static_cast<float>(position[1]),
                                                static_cast<float>(0)));
                }
                break;
            }
            else
                ++k;
        }
     }
}

// No interference - random distribution of particles
void RealSpaceBuilderUtils::populateRandomDistribution(
        RealSpaceModel* model, const SessionItem& layoutItem,
        const QVector<Particle3DType> &particle3DType_vector, const SceneGeometry& sceneGeometry,
        const RealSpaceBuilder *builder3D)
{
    // get the lattice positions at which to populate the particles
    QVector<QVector<double>> lattice_positions =
            computeRandomDistributionLatticePositions(layoutItem, sceneGeometry);

    populateParticlesAtLatticePositions(lattice_positions, particle3DType_vector, model,
                                        sceneGeometry, builder3D);
}

QVector<QVector<double> > RealSpaceBuilderUtils::computeRandomDistributionLatticePositions(
        const SessionItem &layoutItem, const SceneGeometry& sceneGeometry)
{
    double layer_size = sceneGeometry.layer_size();
    QVector<QVector<double>> lattice_positions;
    QVector<double> position;

    // to compute total number of particles we use the total particle density
    // and multiply by the area of the layer
    double total_density = layoutItem.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble();
    int num_particles = static_cast<int>(total_density * (2*layer_size) * (2*layer_size));

    for (int i = 1; i <= num_particles; ++i)
    {
        // For calculating lattice coordinates we use random x and y coordinates
        position.push_back((rand()/static_cast<double>(RAND_MAX))*2*layer_size - layer_size); // x
        position.push_back((rand()/static_cast<double>(RAND_MAX))*2*layer_size - layer_size); // y

        // no need for z coordinate as all lattice positions are calculated in the xy plane

        lattice_positions.push_back(position);
        position.clear();
    }

    return lattice_positions;
}

// InterferenceFunction2DLatticeType
void RealSpaceBuilderUtils::populateInterference2DLatticeType(
        const IInterferenceFunction *interference, RealSpaceModel *model,
        const QVector<Particle3DType> &particle3DType_vector, const SceneGeometry& sceneGeometry,
        const RealSpaceBuilder *builder3D)
{
    auto interference2D = dynamic_cast<const InterferenceFunction2DLattice*>(interference);
    const Lattice2D& lattice2D = interference2D->lattice();

    QVector<QVector<double>> lattice_positions =
            computeInterference2DLatticePositions(lattice2D.length1(), lattice2D.length2(),
                                                  lattice2D.latticeAngle(), lattice2D.rotationAngle(),
                                                  sceneGeometry);

    populateParticlesAtLatticePositions(
                lattice_positions, particle3DType_vector, model, sceneGeometry, builder3D);
}



QVector<QVector<double>> RealSpaceBuilderUtils::computeInterference2DLatticePositions(
        double l1, double l2, double l_alpha, double l_xi, const SceneGeometry &sceneGeometry)
{
    double layer_size = sceneGeometry.layer_size();
    QVector<QVector<double>> lattice_positions;
    QVector<double> position;

    // Estimate the limit n1 and n2 of the integer multiple i and j of the lattice vectors required
    // for populating particles correctly within the 3D model's boundaries
    int n1 = 0, n2 = 0;
    n1 = static_cast<int>(layer_size*2)/static_cast<int>(l1*std::cos(l_xi));

    // This condition is required when this function is used to compute 1D Lattice positions
    if(l2 != 0)
    {
        n2 = static_cast<int>(layer_size*2)/
                static_cast<int>(l2*std::sin(l_alpha+l_xi));

        n1 = std::max(n1,n2);
        n2 = std::max(n1,n2);
    }

    for (int i = -n1; i <= n1; ++i)
    {
        for (int j = -n2; j <= n2; ++j)
        {
            // For calculating lattice position vector v, we use: v = i*l1 + j*l2
            // where l1 and l2 are the lattice vectors,
            // i and j are the integer multiples of l1 and l2 respectively

            position.push_back(i*l1*std::cos(l_xi)+ j*l2*std::cos(l_alpha + l_xi)); // x coordinate
            position.push_back(i*l1*std::sin(l_xi)+ j*l2*std::sin(l_alpha + l_xi)); // y coordinate

            // no need for z coordinate as all lattice positions are calculated in the xy plane

            lattice_positions.push_back(position);
            position.clear();
        }
    }

    return lattice_positions;
}

void RealSpaceBuilderUtils::populateInterference1DLatticeType(
        const IInterferenceFunction *interference, RealSpaceModel *model,
        const QVector<Particle3DType> &particle3DType_vector, const SceneGeometry &sceneGeometry,
        const RealSpaceBuilder *builder3D)
{
    auto interference1D = dynamic_cast<const InterferenceFunction1DLattice *>(interference);
    auto interference1DParameters = interference1D->getLatticeParameters();

    // Simply set the parameters l1 = l, l2 = 0, l_alpha = 0 and l_xi = l_xi in
    // computeInterference2DLatticePositions() to compute lattice positions for 1D Lattice
    QVector<QVector<double>> lattice_positions =
            computeInterference2DLatticePositions(interference1DParameters.m_length, 0.0, 0.0,
                                                  interference1DParameters.m_xi, sceneGeometry);

    populateParticlesAtLatticePositions(
                lattice_positions, particle3DType_vector, model, sceneGeometry, builder3D);
}

// Implement Rotation of a 3D particle using parameters from IRotation Object
QVector3D RealSpaceBuilderUtils::implementParticleRotationfromIRotation(const IRotation* &rotation)
{
    double alpha = 0.0;
    double beta = 0.0;
    double gamma = 0.0;

    if(auto rotX = dynamic_cast<const RotationX*>(rotation)) {
        beta = rotX->getAngle(); // about x-axis
    } else if(auto rotY = dynamic_cast<const RotationY*>(rotation)) {
        alpha = Units::deg2rad(90.0);
        beta = rotY->getAngle(); // about y-axis
        gamma = Units::deg2rad(-90.0);
    } else if(auto rotZ = dynamic_cast<const RotationZ*>(rotation)) {
        alpha = rotZ->getAngle(); // about z-axis
    } else if (auto rotEuler = dynamic_cast<const RotationEuler*>(rotation)) {
        alpha = rotEuler->getAlpha();
        beta = rotEuler->getBeta();
        gamma = rotEuler->getGamma();
    }
    return QVector3D(static_cast<float>(alpha),
                     static_cast<float>(beta),
                     static_cast<float>(gamma));
}

void RealSpaceBuilderUtils::applyParticleTransformations(const Particle* particle,
                                                         RealSpace::Particles::Particle* particle3D,
                                                         const QVector3D& origin)
{
    if (particle && particle3D)
    {
        // rotation
        RealSpace::Vector3D particle_rotate;
        const IRotation* rotation = particle->rotation();

        if(rotation)
            particle_rotate = implementParticleRotationfromIRotation(rotation);

        // translation
        float x = static_cast<float>(particle->position().x());
        float y = static_cast<float>(particle->position().y());
        float z = static_cast<float>(particle->position().z());
        RealSpace::Vector3D position(x + origin.x(), y + origin.y(), z + origin.z());

        // NOTE: If the particle belongs to a particle composition, along with the particle's
        // intrinsic transformations, position() and rotation() methods also account for the
        // translation and rotation (if present) of the particle composition as the
        // particleComposition's decompose() method already does this

        particle3D->addTransform(particle_rotate, position);
    }

    else
        return;
}

void RealSpaceBuilderUtils::applyParticleCoreShellTransformations(
        const Particle *particle, RealSpace::Particles::Particle *particle3D,
        const ParticleCoreShell *particleCoreShell, const QVector3D &origin)
{
    if (particle && particle3D && particleCoreShell)
    {
        std::unique_ptr<Particle> P_clone(particle->clone()); // clone of the current particle

        // rotation
        RealSpace::Vector3D particle_rotate;
        const IRotation* rotationCoreShell = particleCoreShell->rotation();

        if(rotationCoreShell)
            P_clone->rotate(*rotationCoreShell);

        const IRotation* rotation = P_clone->rotation();

        if(rotation)
            particle_rotate = implementParticleRotationfromIRotation(rotation);

        // translation
        kvector_t positionCoreShell = particleCoreShell->position();

        P_clone->translate(positionCoreShell);

        RealSpace::Vector3D position(static_cast<float>(P_clone->position().x()) + origin.x(),
                                     static_cast<float>(P_clone->position().y()) + origin.y(),
                                     static_cast<float>(P_clone->position().z()) + origin.z());

        particle3D->transform(particle_rotate, position);
    }

    else
        return;
}

void RealSpaceBuilderUtils::applyParticleColor(const Particle *particle,
                                               RealSpace::Particles::Particle *particle3D,
                                               double alpha)
{
    if (particle && particle3D)
    {
        // assign correct color to the particle from the knowledge of its material
        const Material* particle_material = particle->material();
        QString material_name = QString::fromStdString(particle_material->getName());
        auto materialItem = AppSvc::materialModel()->materialFromName(material_name);
        QColor color = materialItem->color();
        color.setAlphaF(alpha);
        particle3D->color = color;
    }

    else
        return;
}

void RealSpaceBuilderUtils::populateParticleComposition(
        RealSpaceModel *model, const ParticleComposition *particleComposition,
        const QVector3D &origin)
{
    SafePointerVector<IParticle> pc_vector = particleComposition->decompose();

    for (const IParticle* pc_particle : pc_vector)
    {
        if(dynamic_cast<const ParticleCoreShell*>(pc_particle))
        {
            auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pc_particle);
            populateParticleCoreShell(model, particleCoreShell, origin);
        }
        else
        {
            auto particle = dynamic_cast<const Particle*>(pc_particle);
            populateSingleParticle(model, particle, origin);
        }
    }
}

void RealSpaceBuilderUtils::populateParticleCoreShell(
        RealSpaceModel *model, const ParticleCoreShell *particleCoreShell, const QVector3D &origin)
{
    std::unique_ptr<const IFormFactor> coreParticleff(
                particleCoreShell->coreParticle()->createFormFactor());
    std::unique_ptr<const IFormFactor> shellParticleff(
                particleCoreShell->shellParticle()->createFormFactor());

    auto coreff = getUnderlyingFormFactor(coreParticleff.get());
    auto shellff = getUnderlyingFormFactor(shellParticleff.get());

    auto coreParticle3D = TransformTo3D::createParticlefromIFormFactor(coreff);
    auto shellParticle3D = TransformTo3D::createParticlefromIFormFactor(shellff);

    // core
    applyParticleCoreShellTransformations(particleCoreShell->coreParticle(), coreParticle3D.get(),
                                          particleCoreShell, origin);
    applyParticleColor(particleCoreShell->coreParticle(), coreParticle3D.get());

    // shell (set an alpha value of 0.5 for transparency)
    applyParticleCoreShellTransformations(particleCoreShell->shellParticle(), shellParticle3D.get(),
                                          particleCoreShell, origin);
    applyParticleColor(particleCoreShell->shellParticle(), shellParticle3D.get(), 0.5);

    if (coreParticle3D)
        model->add(coreParticle3D.release());

    if (shellParticle3D)
        model->addBlend(shellParticle3D.release()); // use addBlend() for transparent object
}

void RealSpaceBuilderUtils::populateParticleDistribution(
        RealSpaceModel *model, const ParticleDistribution *particleDistribution,
        const QVector3D &origin)
{
    auto pd_vector = particleDistribution->generateParticles();

    // Retrieving abundances of particles
    double total_abundance = 0.0;
    QVector<double> cumulative_abundances;

    for (auto pd_particle : pd_vector)
    {
        total_abundance = total_abundance + pd_particle->abundance();
        cumulative_abundances.append(total_abundance);
    }

    double rand_num = (rand()/static_cast<double>(RAND_MAX)); // (between 0 and 1)
    int k = 0;

    // randomly pick and populate a single particle from pd_vector using the particle's
    // abundance which has been computed according to the associated distribution
    for (auto pd_particle : pd_vector)
    {
        if (rand_num <= cumulative_abundances.at(k)/cumulative_abundances.last())
        {
            if(dynamic_cast<const ParticleComposition*>(pd_particle))
            {
                auto particleComposition = dynamic_cast<const ParticleComposition*>(pd_particle);
                populateParticleComposition(model, particleComposition, origin);
            }
            else if(dynamic_cast<const ParticleCoreShell*>(pd_particle))
            {
                auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pd_particle);
                populateParticleCoreShell(model, particleCoreShell, origin);
            }
            else
            {
                auto particle = dynamic_cast<const Particle*>(pd_particle);
                populateSingleParticle(model, particle, origin);
            }
            break;
        }
        else
            ++k;
    }

    cumulative_abundances.clear();
}

void RealSpaceBuilderUtils::populateSingleParticle(
        RealSpaceModel *model, const Particle *particle, const QVector3D &origin)
{
    std::unique_ptr<const IFormFactor> particleff(particle->createFormFactor());
    auto ff = getUnderlyingFormFactor(particleff.get());

    auto particle3D = TransformTo3D::createParticlefromIFormFactor(ff);

    applyParticleTransformations(particle, particle3D.get(), origin);
    applyParticleColor(particle, particle3D.get());

    if (particle3D)
        model->add(particle3D.release());
}

QVector<Particle3DType> RealSpaceBuilderUtils::getParticle3DTypeVector(const SessionItem &layoutItem)
{
    QVector<Particle3DType> particle3DType_vector;

    double total_abundance = computeCumulativeAbundances(layoutItem).last();

    double cumulative_abundance = 0;

    for (auto particleItem : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    {
        if(particleItem->modelType() == Constants::ParticleType)
        {
            auto singleParticle3DType =
                    getSingleParticle3DType(particleItem, total_abundance);

            cumulative_abundance += singleParticle3DType.getCumulativeAbundance();

            singleParticle3DType.setCumulativeAbundance(cumulative_abundance);

            particle3DType_vector.append(singleParticle3DType);
        }
    }

    return particle3DType_vector;
}

Particle3DType RealSpaceBuilderUtils::getSingleParticle3DType(const SessionItem* particleItem,
                                                             double total_abundance)
{
    auto pItem = dynamic_cast<const ParticleItem*>(particleItem);
    auto particle = pItem->createParticle();
    std::unique_ptr<const IFormFactor> particleff(particle->createFormFactor());
    auto ff = getUnderlyingFormFactor(particleff.get());

    auto particle3D = TransformTo3D::createParticlefromIFormFactor(ff);

    const auto origin =  QVector3D();

    applyParticleTransformations(particle.get(), particle3D.get(), origin);
    applyParticleColor(particle.get(), particle3D.get());

    Particle3DType singleParticle3DType;

    singleParticle3DType.add3DParticle(particle3D.release());
    singleParticle3DType.setCumulativeAbundance(particle->abundance()/total_abundance);
    singleParticle3DType.setType(Constants::ParticleType);

    return singleParticle3DType;
}
