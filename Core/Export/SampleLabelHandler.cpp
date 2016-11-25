// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleLabelHandler.cpp
//! @brief     Implement class SampleLabelHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleLabelHandler.h"
#include "HomogeneousMagneticMaterial.h"
#include "IInterferenceFunction.h"
#include "IMaterial.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"

std::string SampleLabelHandler::getLabelFormFactor(const IFormFactor* ff)
{
    return m_FormFactorLabel[ff];
}

std::string SampleLabelHandler::getLabelInterferenceFunction(const IInterferenceFunction* iff)
{
    return m_InterferenceFunctionLabel[iff];
}

std::string SampleLabelHandler::getLabelMaterial(const IMaterial* mat)
{
    return m_MaterialLabel[mat];
}

std::string SampleLabelHandler::getLabelLayer(const Layer* layer) { return m_LayerLabel[layer]; }

std::string SampleLabelHandler::getLabelRoughness(const LayerRoughness* roughness)
{
    return m_LayerRoughnessLabel[roughness];
}

std::string SampleLabelHandler::getLabelMultiLayer(const MultiLayer* ml)
{
    return m_MultiLayerLabel[ml];
}

std::string SampleLabelHandler::getLabelParticle(const IAbstractParticle* absparticle)
{
    if (const auto core_shell_particle = dynamic_cast<const ParticleCoreShell*>(absparticle))
        return m_ParticleCoreShellLabel[core_shell_particle];
    if (const auto particle = dynamic_cast<const Particle*>(absparticle))
        return m_ParticleLabel[particle];
    if (const auto particle = dynamic_cast<const ParticleDistribution*>(absparticle))
        return m_ParticleDistributionLabel[particle];
    if (const auto lattice_basis = dynamic_cast<const ParticleComposition*>(absparticle))
        return m_ParticleCompositionLabel[lattice_basis];
    throw Exceptions::NotImplementedException(
        "SampleLabelHandler::getLabel: called for unknown IParticle type");
}

std::string SampleLabelHandler::getLabelParticleCoreShell(const ParticleCoreShell* pcs)
{
    return m_ParticleCoreShellLabel[pcs];
}

std::string SampleLabelHandler::getLabelParticleDistribution(const ParticleDistribution* pd)
{
    return m_ParticleDistributionLabel[pd];
}

std::string SampleLabelHandler::getLabelLayout(const ILayout* layout)
{
    return m_ILayoutLabel[layout];
}

std::string SampleLabelHandler::getLabelParticleComposition(const ParticleComposition* pc)
{
    return m_ParticleCompositionLabel[pc];
}

std::string SampleLabelHandler::getLabelRotation(const IRotation* rot)
{
    return m_RotationsLabel[rot];
}

void SampleLabelHandler::insertMaterial(const IMaterial* mat)
{
    for (auto it = m_MaterialLabel.begin(); it != m_MaterialLabel.end(); ++it) {
        if (*(it->first) == *mat) {
            m_MaterialLabel.insert(std::make_pair(mat, it->second));
            return;
        }
    }
    // material not found => create new label
    std::ostringstream label_stream;
    label_stream << "material_" << m_MaterialLabel.size() + 1;
    m_MaterialLabel.insert(std::make_pair(mat, label_stream.str()));
}

void SampleLabelHandler::insertFormFactor(const IFormFactor* sample)
{
    std::ostringstream inter;
    inter << "formFactor_" << m_FormFactorLabel.size() + 1;
    m_FormFactorLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertInterferenceFunction(const IInterferenceFunction* sample)
{
    std::ostringstream inter;
    inter << "interference_" << m_InterferenceFunctionLabel.size() + 1;
    m_InterferenceFunctionLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertLayout(const ILayout* sample)
{
    std::ostringstream inter;
    inter << "layout_" << m_ILayoutLabel.size() + 1;
    m_ILayoutLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertLayer(const Layer* sample)
{
    std::ostringstream inter;
    inter << "layer_" << m_LayerLabel.size() + 1;
    m_LayerLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertRoughness(const LayerRoughness* sample)
{
    if (sample->getSigma() != 0 && sample->getHurstParameter() != 0
        && sample->getLatteralCorrLength() != 0) {
        std::ostringstream inter;
        inter << "layerRoughness_" << m_LayerRoughnessLabel.size() + 1;
        m_LayerRoughnessLabel.insert(sample, inter.str());
    }
}

void SampleLabelHandler::insertMultiLayer(const MultiLayer* sample)
{
    std::ostringstream inter;
    inter << "multiLayer_" << m_MultiLayerLabel.size() + 1;
    m_MultiLayerLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertParticle(const Particle* sample)
{
    std::ostringstream inter;
    inter << "particle_" << m_ParticleLabel.size() + 1;
    m_ParticleLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertParticleCoreShell(const ParticleCoreShell* sample)
{
    std::ostringstream inter;
    inter << "particleCoreShell_" << m_ParticleCoreShellLabel.size() + 1;
    m_ParticleCoreShellLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertParticleDistribution(const ParticleDistribution* sample)
{
    std::ostringstream inter;
    inter << "particleDistribution_" << m_ParticleDistributionLabel.size() + 1;
    m_ParticleDistributionLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertParticleComposition(const ParticleComposition* sample)
{
    std::ostringstream inter;
    inter << "particleComposition_" << m_ParticleCompositionLabel.size() + 1;
    m_ParticleCompositionLabel.insert(sample, inter.str());
}

void SampleLabelHandler::insertRotation(const IRotation* sample)
{
    std::ostringstream inter;
    inter << "rotation_" << m_RotationsLabel.size() + 1;
    m_RotationsLabel.insert(sample, inter.str());
}
