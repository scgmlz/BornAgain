// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleLabelHandler.h
//! @brief     Defines classes LabelMap and SampleLabelHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_EXPORT_SAMPLELABELHANDLER_H
#define BORNAGAIN_CORE_EXPORT_SAMPLELABELHANDLER_H

#include "Core/Basics/Exceptions.h"
#include "Core/Export/OrderedMap.h"

class Crystal;
class IAbstractParticle;
class IFormFactor;
class IInterferenceFunction;
class ILayout;
class Material;
class IRotation;
class Lattice;
class Layer;
class LayerRoughness;
class MultiLayer;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;
class MesoCrystal;

template <class Key> class LabelMap : public OrderedMap<Key, std::string>
{
};

//! The handler which construct labels for sample variables during python script generation.
//! @ingroup tools_internal

class SampleLabelHandler
{
public:
    typedef LabelMap<const Crystal*> crystals_t;
    typedef LabelMap<const IFormFactor*> formfactors_t;
    typedef LabelMap<const IInterferenceFunction*> interferences_t;
    typedef LabelMap<const Layer*> layers_t;
    typedef LabelMap<const ILayout*> layouts_t;
    typedef LabelMap<const Material*> materials_t;
    typedef LabelMap<const Lattice*> lattices_t;
    typedef LabelMap<const MesoCrystal*> mesocrystals_t;
    typedef LabelMap<const MultiLayer*> multilayers_t;
    typedef LabelMap<const ParticleComposition*> particlecompositions_t;
    typedef LabelMap<const ParticleDistribution*> particledistributions_t;
    typedef LabelMap<const Particle*> particles_t;
    typedef LabelMap<const ParticleCoreShell*> particlescoreshell_t;
    typedef LabelMap<const IRotation*> rotations_t;
    typedef LabelMap<const LayerRoughness*> roughnesses_t;

    SampleLabelHandler() {}
    crystals_t* crystalMap() { return &m_CrystalLabel; }
    formfactors_t* formFactorMap() { return &m_FormFactorLabel; }
    interferences_t* interferenceFunctionMap() { return &m_InterferenceFunctionLabel; }
    layers_t* layerMap() { return &m_LayerLabel; }
    layouts_t* particleLayoutMap() { return &m_ILayoutLabel; }
    materials_t* materialMap() { return &m_MaterialLabel; }
    lattices_t* latticeMap() { return &m_LatticeLabel; }
    mesocrystals_t* mesocrystalMap() { return &m_MesoCrystalLabel; }
    multilayers_t* multiLayerMap() { return &m_MultiLayerLabel; }
    particlecompositions_t* particleCompositionMap() { return &m_ParticleCompositionLabel; }
    particledistributions_t* particleDistributionsMap() { return &m_ParticleDistributionLabel; }
    particles_t* particleMap() { return &m_ParticleLabel; }
    particlescoreshell_t* particleCoreShellMap() { return &m_ParticleCoreShellLabel; }
    rotations_t* rotationsMap() { return &m_RotationsLabel; }
    roughnesses_t* layerRoughnessMap() { return &m_LayerRoughnessLabel; }

    std::string labelCrystal(const Crystal* sample);
    std::string labelFormFactor(const IFormFactor* sample);
    std::string labelInterferenceFunction(const IInterferenceFunction* sample);
    std::string labelLayer(const Layer* sample);
    std::string labelLayout(const ILayout* sample);
    std::string labelMaterial(const Material* sample);
    std::string labelLattice(const Lattice* sample);
    std::string labelMultiLayer(const MultiLayer* sample);
    std::string labelParticle(const IAbstractParticle* sample);
    std::string labelRotation(const IRotation* sample);
    std::string labelRoughness(const LayerRoughness* sample);

    void insertCrystal(const Crystal* sample);
    void insertFormFactor(const IFormFactor* sample);
    void insertInterferenceFunction(const IInterferenceFunction* sample);
    void insertLayer(const Layer* sample);
    void insertLayout(const ILayout* sample);
    void insertMaterial(const Material* sample);
    void insertLattice(const Lattice* sample);
    void insertMesoCrystal(const MesoCrystal* sample);
    void insertMultiLayer(const MultiLayer* sample);
    void insertParticleComposition(const ParticleComposition* sample);
    void insertParticleDistribution(const ParticleDistribution* sample);
    void insertParticle(const Particle* sample);
    void insertParticleCoreShell(const ParticleCoreShell* sample);
    void insertRotation(const IRotation* sample);
    void insertRoughness(const LayerRoughness* sample);

private:
    crystals_t m_CrystalLabel;
    formfactors_t m_FormFactorLabel;
    interferences_t m_InterferenceFunctionLabel;
    layers_t m_LayerLabel;
    layouts_t m_ILayoutLabel;
    materials_t m_MaterialLabel;
    lattices_t m_LatticeLabel;
    mesocrystals_t m_MesoCrystalLabel;
    multilayers_t m_MultiLayerLabel;
    particlecompositions_t m_ParticleCompositionLabel;
    particledistributions_t m_ParticleDistributionLabel;
    particles_t m_ParticleLabel;
    particlescoreshell_t m_ParticleCoreShellLabel;
    rotations_t m_RotationsLabel;
    roughnesses_t m_LayerRoughnessLabel;
};

#endif // BORNAGAIN_CORE_EXPORT_SAMPLELABELHANDLER_H
