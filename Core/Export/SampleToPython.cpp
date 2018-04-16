// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleToPython.cpp
//! @brief     Implements class SampleToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleToPython.h"
#include "Crystal.h"
#include "IFormFactor.h"
#include "INodeUtils.h"
#include "InterferenceFunctions.h"
#include "Layer.h"
#include "Lattice.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "Material.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "ParameterUtils.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "PythonFormatting.h"
#include "SampleLabelHandler.h"
#include <iomanip>
#include <map>
#include <set>

using namespace PythonFormatting;

std::string SampleToPython::generateSampleCode(const MultiLayer& multilayer)
{
    initLabels(multilayer);
    return defineGetSample();
}

void SampleToPython::initLabels(const MultiLayer& multilayer)
{
    m_label.reset(new SampleLabelHandler());

    m_label->insertMultiLayer(&multilayer);

    for (auto x : multilayer.containedMaterials())
        m_label->insertMaterial(x);
    for (auto x : INodeUtils::AllDescendantsOfType<Layer>(multilayer))
        m_label->insertLayer(x);
    for (auto x : INodeUtils::AllDescendantsOfType<LayerRoughness>(multilayer))
        m_label->insertRoughness(x);
    for (auto x : INodeUtils::AllDescendantsOfType<IFormFactor>(multilayer))
        m_label->insertFormFactor(x);
    for (auto x : INodeUtils::AllDescendantsOfType<ILayout>(multilayer))
        m_label->insertLayout(x);
    for (auto x : INodeUtils::AllDescendantsOfType<IInterferenceFunction>(multilayer))
        m_label->insertInterferenceFunction(x);
    for (auto x : INodeUtils::AllDescendantsOfType<Particle>(multilayer))
        m_label->insertParticle(x);
    for (auto x : INodeUtils::AllDescendantsOfType<ParticleCoreShell>(multilayer))
        m_label->insertParticleCoreShell(x);
    for (auto x : INodeUtils::AllDescendantsOfType<ParticleComposition>(multilayer))
        m_label->insertParticleComposition(x);
    for (auto x : INodeUtils::AllDescendantsOfType<ParticleDistribution>(multilayer))
        m_label->insertParticleDistribution(x);
    for (auto x : INodeUtils::AllDescendantsOfType<Lattice>(multilayer))
        m_label->insertLattice(x);
    for (auto x : INodeUtils::AllDescendantsOfType<Crystal>(multilayer))
        m_label->insertCrystal(x);
    for (auto x : INodeUtils::AllDescendantsOfType<MesoCrystal>(multilayer))
        m_label->insertMesoCrystal(x);
    for (auto x : INodeUtils::AllDescendantsOfType<IRotation>(multilayer))
        m_label->insertRotation(x);
}

SampleToPython::SampleToPython() = default;

SampleToPython::~SampleToPython() = default;

std::string SampleToPython::defineGetSample() const
{
    return "def "+getSampleFunctionName()+"():\n" + defineMaterials() + defineLayers() + defineFormFactors()
           + defineParticles() + defineCoreShellParticles() + defineParticleCompositions()
           + defineLattices() + defineCrystals() + defineMesoCrystals()
           + defineParticleDistributions() + defineInterferenceFunctions() + defineParticleLayouts()
           + defineRoughnesses() + addLayoutsToLayers() + defineMultiLayers() + "\n\n";
}

const std::map<MATERIAL_TYPES, std::string> factory_names{
    {MATERIAL_TYPES::RefractiveMaterial, "HomogeneousMaterial"},
    {MATERIAL_TYPES::MaterialBySLD, "MaterialBySLD"}};

std::string SampleToPython::defineMaterials() const
{
    const auto themap = m_label->materialMap();
    if (themap->size() == 0)
        return "# No Materials.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << indent() << "# Defining Materials\n";
    std::set<std::string> visitedMaterials;
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        if (visitedMaterials.find(it->second) != visitedMaterials.end())
            continue;
        visitedMaterials.insert(it->second);
        const Material* p_material = it->first;
        const auto factory_name = factory_names.find(p_material->typeID());
        if (factory_name == factory_names.cend())
            throw std::runtime_error(
                "Error in ExportToPython::defineMaterials(): unknown material type");
        const complex_t& material_data = p_material->materialData();
        if (p_material->isScalarMaterial()) {
            result << indent() << m_label->labelMaterial(p_material) << " = ba."
                   << factory_name->second << "(\"" << p_material->getName() << "\", "
                   << printDouble(material_data.real()) << ", " << printDouble(material_data.imag())
                   << ")\n";
        } else {
            kvector_t magnetic_field = p_material->magnetization();
            result << indent() << "magnetic_field = kvector_t(" << magnetic_field.x() << ", "
                   << magnetic_field.y() << ", " << magnetic_field.z() << ")\n";
            result << indent() << m_label->labelMaterial(p_material) << " = ba."
                   << factory_name->second << "(\"" << p_material->getName();
            result << "\", " << printDouble(material_data.real()) << ", "
                   << printDouble(material_data.imag()) << ", "
                   << "magnetic_field)\n";
        }
    }
    return result.str();
}

std::string SampleToPython::defineLayers() const
{
    const auto themap = m_label->layerMap();
    if (themap->size() == 0)
        return "# No Layers.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Layers\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Layer* layer = it->first;
        result << indent() << it->second << " = ba.Layer("
               << m_label->labelMaterial(layer->material());
        if (layer->thickness() != 0)
            result << ", " << layer->thickness();
        result << ")\n";
        if (layer->numberOfSlices() != 1)
            result << indent() << it->second << ".setNumberOfSlices(" << layer->numberOfSlices()
                   << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineFormFactors() const
{
    const auto themap = m_label->formFactorMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Form Factors\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const IFormFactor* p_ff = it->first;
        result << indent() << it->second << " = ba.FormFactor" << p_ff->getName() << "("
               << argumentList(p_ff) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineParticles() const
{
    const auto themap = m_label->particleMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Particle* p_particle = it->first;
        std::string particle_name = it->second;
        auto p_ff = INodeUtils::OnlyChildOfType<IFormFactor>(*p_particle);
        if (!p_ff)
            continue;
        result << indent() << particle_name << " = ba.Particle("
               << m_label->labelMaterial(p_particle->material()) << ", "
               << m_label->labelFormFactor(p_ff) << ")\n";
        setRotationInformation(p_particle, particle_name, result);
        setPositionInformation(p_particle, particle_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineCoreShellParticles() const
{
    const auto themap = m_label->particleCoreShellMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Core Shell Particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleCoreShell* p_coreshell = it->first;
        result << "\n"
               << indent() << it->second << " = ba.ParticleCoreShell("
               << m_label->labelParticle(p_coreshell->shellParticle()) << ", "
               << m_label->labelParticle(p_coreshell->coreParticle()) << ")\n";
        std::string core_shell_name = it->second;
        setRotationInformation(p_coreshell, core_shell_name, result);
        setPositionInformation(p_coreshell, core_shell_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineParticleDistributions() const
{
    const auto themap = m_label->particleDistributionsMap();
    if (themap->size() == 0)
        return "";

    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining particles with parameter following a distribution\n";

    int index(1);
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleDistribution* p_particle_distr = it->first;
        std::string units = ParameterUtils::mainParUnits(*p_particle_distr);
        ParameterDistribution par_distr = p_particle_distr->parameterDistribution();

        // building distribution functions
        std::string s_distr = "distr_" + std::to_string(index);
        result << indent() << s_distr << " = "
               << printDistribution(*par_distr.getDistribution(), units) << "\n";

        // building parameter distribution
        std::string s_par_distr = "par_distr_" + std::to_string(index);

        result << indent() << s_par_distr << " = "
               << printParameterDistribution(par_distr, s_distr, units) << "\n";

        // linked parameters
        std::vector<std::string> linked_pars = par_distr.getLinkedParameterNames();
        if (linked_pars.size()) {
            result << indent() << s_par_distr;
            for (size_t i = 0; i < linked_pars.size(); ++i)
                result << ".linkParameter(\"" << linked_pars[i] << "\")";
            result << "\n";
        }

        auto p_particle = INodeUtils::OnlyChildOfType<IParticle>(*p_particle_distr);
        if (!p_particle)
            continue;
        result << indent() << it->second << " = ba.ParticleDistribution("
               << m_label->labelParticle(p_particle) << ", " << s_par_distr << ")\n";
        index++;
    }
    return result.str();
}

std::string SampleToPython::defineParticleCompositions() const
{
    const auto themap = m_label->particleCompositionMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining composition of particles at specific positions\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleComposition* p_particle_composition = it->first;
        std::string particle_composition_name = it->second;
        result << indent() << particle_composition_name << " = ba.ParticleComposition()\n";
        auto particle_list = INodeUtils::ChildNodesOfType<IParticle>(*p_particle_composition);
        for (auto p_particle : particle_list) {
            result << indent() << particle_composition_name << ".addParticle("
                   << m_label->labelParticle(p_particle) << ")\n";
        }
        setRotationInformation(p_particle_composition, particle_composition_name, result);
        setPositionInformation(p_particle_composition, particle_composition_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineLattices() const
{
    const auto themap = m_label->latticeMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining 3D lattices\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Lattice* p_lattice = it->first;
        std::string lattice_name = it->second;
        kvector_t bas_a = p_lattice->getBasisVectorA();
        kvector_t bas_b = p_lattice->getBasisVectorB();
        kvector_t bas_c = p_lattice->getBasisVectorC();
        result << indent() << lattice_name << " = ba.Lattice(\n";
        result << indent() << indent() << "ba.kvector_t(" << printNm(bas_a.x()) << ", "
               << printNm(bas_a.y()) << ", " << printNm(bas_a.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t(" << printNm(bas_b.x()) << ", "
               << printNm(bas_b.y()) << ", " << printNm(bas_b.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t(" << printNm(bas_c.x()) << ", "
               << printNm(bas_c.y()) << ", " << printNm(bas_c.z()) << "))\n";
    }
    return result.str();
}

std::string SampleToPython::defineCrystals() const
{
    const auto themap = m_label->crystalMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining crystals: basis particle + lattice\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Crystal* p_crystal = it->first;
        std::string crystal_name = it->second;
        auto p_lattice = INodeUtils::OnlyChildOfType<Lattice>(*p_crystal);
        auto p_basis = INodeUtils::OnlyChildOfType<IParticle>(*p_crystal);
        if (!p_lattice || !p_basis)
            continue;
        result << indent() << crystal_name << " = ba.Crystal(";
        result << m_label->labelParticle(p_basis) << ", ";
        result << m_label->labelLattice(p_lattice) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineMesoCrystals() const
{
    const auto themap = m_label->mesocrystalMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining mesocrystals\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const MesoCrystal* p_mesocrystal = it->first;
        std::string mesocrystal_name = it->second;
        auto p_crystal = INodeUtils::OnlyChildOfType<Crystal>(*p_mesocrystal);
        auto p_outer_shape = INodeUtils::OnlyChildOfType<IFormFactor>(*p_mesocrystal);
        if (!p_crystal || !p_outer_shape)
            continue;
        result << indent() << mesocrystal_name << " = ba.MesoCrystal(";
        result << m_label->labelCrystal(p_crystal) << ", ";
        result << m_label->labelFormFactor(p_outer_shape) << ")\n";
        setRotationInformation(p_mesocrystal, mesocrystal_name, result);
        setPositionInformation(p_mesocrystal, mesocrystal_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineInterferenceFunctions() const
{
    const auto themap = m_label->interferenceFunctionMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Interference Functions\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const IInterferenceFunction* interference = it->first;

        if (dynamic_cast<const InterferenceFunctionNone*>(interference))
            result << indent() << it->second << " = ba.InterferenceFunctionNone()\n";
        else if (auto p_lattice_1d
                 = dynamic_cast<const InterferenceFunction1DLattice*>(interference)) {
            const Lattice1DParameters latticeParameters = p_lattice_1d->getLatticeParameters();
            result << indent() << it->second << " = ba.InterferenceFunction1DLattice("
                   << printNm(latticeParameters.m_length) << ", "
                   << printDegrees(latticeParameters.m_xi) << ")\n";

            auto pdf = INodeUtils::OnlyChildOfType<IFTDecayFunction1D>(*p_lattice_1d);

            if (pdf->decayLength() != 0.0)
                result << indent() << it->second << "_pdf  = ba." << pdf->getName() << "("
                       << argumentList(pdf) << ")\n"
                       << indent() << it->second << ".setDecayFunction(" << it->second << "_pdf)\n";
        } else if (auto p_para_radial
                   = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(interference)) {
            result << indent() << it->second << " = ba.InterferenceFunctionRadialParaCrystal("
                   << printNm(p_para_radial->peakDistance()) << ", "
                   << printNm(p_para_radial->dampingLength()) << ")\n";

            if (p_para_radial->kappa() != 0.0)
                result << indent() << it->second << ".setKappa("
                       << printDouble(p_para_radial->kappa()) << ")\n";

            if (p_para_radial->domainSize() != 0.0)
                result << indent() << it->second << ".setDomainSize("
                       << printDouble(p_para_radial->domainSize()) << ")\n";

            auto pdf = INodeUtils::OnlyChildOfType<IFTDistribution1D>(*p_para_radial);

            if (pdf->omega() != 0.0)
                result << indent() << it->second << "_pdf  = ba." << pdf->getName() << "("
                       << argumentList(pdf) << ")\n"
                       << indent() << it->second << ".setProbabilityDistribution(" << it->second
                       << "_pdf)\n";
        } else if (auto p_lattice_2d
                   = dynamic_cast<const InterferenceFunction2DLattice*>(interference)) {
            const Lattice2D& lattice = p_lattice_2d->lattice();
            result << indent() << it->second << " = ba.InterferenceFunction2DLattice("
                   << printNm(lattice.length1()) << ", " << printNm(lattice.length2()) << ", "
                   << printDegrees(lattice.latticeAngle()) << ", "
                   << printDegrees(lattice.rotationAngle()) << ")\n";

            auto pdf = INodeUtils::OnlyChildOfType<IFTDecayFunction2D>(*p_lattice_2d);

            result << indent() << it->second << "_pdf  = ba." << pdf->getName() << "("
                   << argumentList(pdf) << ")\n"
                   << indent() << it->second << ".setDecayFunction(" << it->second << "_pdf)\n";

            if (p_lattice_2d->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";
        } else if (auto p_lattice_2d
                   = dynamic_cast<const InterferenceFunctionFinite2DLattice*>(interference)) {
            const Lattice2D& lattice = p_lattice_2d->lattice();
            result << indent() << it->second << " = ba.InterferenceFunctionFinite2DLattice("
                   << printNm(lattice.length1()) << ", " << printNm(lattice.length2()) << ", "
                   << printDegrees(lattice.latticeAngle()) << ", "
                   << printDegrees(lattice.rotationAngle()) << ", "
                   << p_lattice_2d->domainSize1() << ", " << p_lattice_2d->domainSize2() << ")\n";

            if (p_lattice_2d->positionVariance()>0.0) {
                result << indent() << it->second << ".setPositionVariance("
                       << p_lattice_2d->positionVariance() << ")\n";
            }
            if (p_lattice_2d->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";
        } else if (auto p_para_2d
                   = dynamic_cast<const InterferenceFunction2DParaCrystal*>(interference)) {
            std::vector<double> domainSize = p_para_2d->domainSizes();
            const Lattice2D& lattice = p_para_2d->lattice();
            result << indent() << it->second << " = ba.InterferenceFunction2DParaCrystal("
                   << printNm(lattice.length1()) << ", " << printNm(lattice.length2()) << ", "
                   << printDegrees(lattice.latticeAngle()) << ", "
                   << printDegrees(lattice.rotationAngle()) << ", "
                   << printNm(p_para_2d->dampingLength()) << ")\n";

            if (domainSize[0] != 0.0 || domainSize[1] != 0.0)
                result << indent() << it->second << ".setDomainSizes(" << printNm(domainSize[0])
                       << ", " << printNm(domainSize[1]) << ")\n";
            if (p_para_2d->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";

            auto pdf_vector = INodeUtils::ChildNodesOfType<IFTDistribution2D>(*p_para_2d);
            if (pdf_vector.size() != 2)
                continue;
            const IFTDistribution2D* pdf = pdf_vector[0];

            result << indent() << it->second << "_pdf_1  = ba." << pdf->getName() << "("
                   << argumentList(pdf) << ")\n";

            pdf = pdf_vector[1];

            result << indent() << it->second << "_pdf_2  = ba." << pdf->getName() << "("
                   << argumentList(pdf) << ")\n";
            result << indent() << it->second << ".setProbabilityDistributions(" << it->second
                   << "_pdf_1, " << it->second << "_pdf_2)\n";
        } else
            throw Exceptions::NotImplementedException(
                "Bug: ExportToPython::defineInterferenceFunctions() called with unexpected "
                "IInterferenceFunction "
                + interference->getName());
    }
    return result.str();
}

std::string SampleToPython::defineParticleLayouts() const
{
    const auto themap = m_label->particleLayoutMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Particle Layouts and adding Particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ILayout* iLayout = it->first;
        if (const ParticleLayout* particleLayout = dynamic_cast<const ParticleLayout*>(iLayout)) {
            result << indent() << it->second << " = ba.ParticleLayout()\n";
            auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(*particleLayout);

            for (auto p_particle : particles) {
                double abundance = p_particle->abundance();
                result << indent() << it->second << ".addParticle("
                       << m_label->labelParticle(p_particle) << ", " << printDouble(abundance)
                       << ")\n";
            }
            if (auto p_iff = INodeUtils::OnlyChildOfType<IInterferenceFunction>(*particleLayout))
                result << indent() << it->second << ".setInterferenceFunction("
                       << m_label->labelInterferenceFunction(p_iff) << ")\n";

            switch (particleLayout->getApproximation()) {
            case ILayout::DA:
                break;
            case ILayout::SSCA:
                result << indent() << it->second << ".setApproximation(ba.ILayout.SSCA)\n";
                break;
            }
            result << indent() << it->second << ".setTotalParticleSurfaceDensity("
                   << it->first->totalParticleSurfaceDensity() << ")\n";
        }
    }
    return result.str();
}

std::string SampleToPython::defineRoughnesses() const
{
    const auto themap = m_label->layerRoughnessMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Roughness Parameters\n";
    for (auto it = themap->begin(); it != themap->end(); ++it)
        result << indent() << it->second << " = ba.LayerRoughness(" << argumentList(it->first)
               << ")\n";
    return result.str();
}

std::string SampleToPython::addLayoutsToLayers() const
{
    if (m_label->particleLayoutMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Adding layouts to layers";
    const auto layermap = m_label->layerMap();
    for (auto it = layermap->begin(); it != layermap->end(); ++it) {
        const Layer* layer = it->first;
        for (auto p_layout : layer->layouts())
            result << "\n"
                   << indent() << it->second << ".addLayout(" << m_label->labelLayout(p_layout)
                   << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineMultiLayers() const
{
    const auto themap = m_label->multiLayerMap();
    if (themap->size() == 0)
        return "# No MultiLayers.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Multilayers\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        result << indent() << it->second << " = ba.MultiLayer()\n";
        double ccl = it->first->crossCorrLength();
        if (ccl > 0.0)
            result << indent() << it->second << ".setCrossCorrLength(" << ccl << ")\n";
        auto external_field = it->first->externalField();
        if (external_field.mag() > 0.0) {
            std::string field_name = it->second + "_external_field";
            result << indent() << field_name << " = kvector_t("
                   << printScientificDouble(external_field.x()) << ", "
                   << printScientificDouble(external_field.y()) << ", "
                   << printScientificDouble(external_field.z()) << ")\n";
            result << indent() << it->second << ".setExternalField(" << field_name << ")\n";
        }
        size_t numberOfLayers = it->first->numberOfLayers();
        if (numberOfLayers) {
            result << indent() << it->second << ".addLayer("
                   << m_label->labelLayer(it->first->layer(0)) << ")\n";

            size_t layerIndex = 1;
            while (layerIndex != numberOfLayers) {
                const LayerInterface* layerInterface = it->first->layerInterface(layerIndex - 1);
                if (m_label->layerRoughnessMap()->find(layerInterface->getRoughness())
                    == m_label->layerRoughnessMap()->end())
                    result << indent() << it->second << ".addLayer("
                           << m_label->labelLayer(it->first->layer(layerIndex)) << ")\n";
                else
                    result << indent() << it->second << ".addLayerWithTopRoughness("
                           << m_label->labelLayer(it->first->layer(layerIndex)) << ", "
                           << m_label->labelRoughness(layerInterface->getRoughness()) << ")\n";
                layerIndex++;
            }
        }
        result << indent() << "return " << it->second << "\n";
    }
    return result.str();
}

std::string SampleToPython::indent() const { return "    "; }

void SampleToPython::setRotationInformation(const IParticle* p_particle, std::string name,
                                            std::ostringstream& result) const
{
    if (p_particle->rotation()) {
        switch (p_particle->rotation()->getTransform3D().getRotationType()) {
        case Transform3D::EULER: {
            double alpha, beta, gamma;
            p_particle->rotation()->getTransform3D().calculateEulerAngles(&alpha, &beta, &gamma);
            result << indent() << name << "_rotation = ba.RotationEuler(" << printDegrees(alpha)
                   << ", " << printDegrees(beta) << ", " << printDegrees(gamma) << ")\n";
            break;
        }
        case Transform3D::XAXIS: {
            double alpha = p_particle->rotation()->getTransform3D().calculateRotateXAngle();
            result << indent() << name << "_rotation = ba.RotationX(" << printDegrees(alpha)
                   << ")\n";
            break;
        }
        case Transform3D::YAXIS: {
            double alpha = p_particle->rotation()->getTransform3D().calculateRotateYAngle();
            result << indent() << name << "_rotation = ba.RotationY(" << printDegrees(alpha)
                   << ")\n";
            break;
        }
        case Transform3D::ZAXIS: {
            double alpha = p_particle->rotation()->getTransform3D().calculateRotateZAngle();
            result << indent() << name << "_rotation = ba.RotationZ(" << printDegrees(alpha)
                   << ")\n";
            break;
        }
        }
        result << indent() << name << ".setRotation(" << name << "_rotation)\n";
    }
}

void SampleToPython::setPositionInformation(const IParticle* p_particle, std::string name,
                                            std::ostringstream& result) const
{
    kvector_t pos = p_particle->position();
    bool has_position_info = (pos != kvector_t());

    if (has_position_info) {
        result << indent() << name << "_position = kvector_t(" << printNm(pos.x()) << ", "
               << printNm(pos.y()) << ", " << printNm(pos.z()) << ")\n";

        result << indent() << name << ".setPosition(" << name << "_position)\n";
    }
}
