//  ************************************************************************************************
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
//  ************************************************************************************************

#include "Core/Export/SampleToPython.h"
#include "Core/Export/PyFmt.h"
#include "Base/Vector/Transform3D.h"
#include "Core/Export/INodeUtils.h"
#include "Core/Export/PyFmt2.h"
#include "Core/Export/SampleLabelHandler.h"
#include "Param/Varia/ParameterUtils.h"
#include "Sample/Aggregate/InterferenceFunctions.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/MesoCrystal.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/Particle/ParticleCoreShell.h"
#include "Sample/Particle/ParticleDistribution.h"
#include "Sample/Scattering/IFormFactor.h"
#include "Sample/Slice/LayerInterface.h"
#include "Sample/Slice/LayerRoughness.h"
#include <iomanip>
#include <map>
#include <set>

using pyfmt::indent;

namespace {

void setRotationInformation(const IParticle* particle, std::string name,
                                            std::ostringstream& result) {
    if (particle->rotation()) {
        switch (particle->rotation()->getTransform3D().getRotationType()) {
        case Transform3D::EULER: {
            double alpha, beta, gamma;
            particle->rotation()->getTransform3D().calculateEulerAngles(&alpha, &beta, &gamma);
            result << indent() << name << "_rotation = ba.RotationEuler("
                   << pyfmt::printDegrees(alpha) << ", " << pyfmt::printDegrees(beta) << ", "
                   << pyfmt::printDegrees(gamma) << ")\n";
            break;
        }
        case Transform3D::XAXIS: {
            double alpha = particle->rotation()->getTransform3D().calculateRotateXAngle();
            result << indent() << name << "_rotation = ba.RotationX(" << pyfmt::printDegrees(alpha)
                   << ")\n";
            break;
        }
        case Transform3D::YAXIS: {
            double alpha = particle->rotation()->getTransform3D().calculateRotateYAngle();
            result << indent() << name << "_rotation = ba.RotationY(" << pyfmt::printDegrees(alpha)
                   << ")\n";
            break;
        }
        case Transform3D::ZAXIS: {
            double alpha = particle->rotation()->getTransform3D().calculateRotateZAngle();
            result << indent() << name << "_rotation = ba.RotationZ(" << pyfmt::printDegrees(alpha)
                   << ")\n";
            break;
        }
        }
        result << indent() << name << ".setRotation(" << name << "_rotation)\n";
    }
}

void setPositionInformation(const IParticle* particle, std::string name,
                                            std::ostringstream& result) {
    kvector_t pos = particle->position();
    if (pos == kvector_t())
        return;

    result << indent() << name << "_position = kvector_t(" << pyfmt::printNm(pos.x()) << ", "
           << pyfmt::printNm(pos.y()) << ", " << pyfmt::printNm(pos.z()) << ")\n";
    result << indent() << name << ".setPosition(" << name << "_position)\n";
}

} // namespace

//  ************************************************************************************************
//  class SampleToPython
//  ************************************************************************************************

std::string SampleToPython::generateSampleCode(const MultiLayer& multilayer) {
    initLabels(multilayer);
    return defineGetSample();
}

void SampleToPython::initLabels(const MultiLayer& multilayer) {
    m_label.reset(new SampleLabelHandler());

    m_label->insertMultiLayer(&multilayer);

    for (const auto* x : multilayer.containedMaterials())
        m_label->insertMaterial(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Layer>(multilayer))
        m_label->insertLayer(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<LayerRoughness>(multilayer))
        m_label->insertRoughness(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<IFormFactor>(multilayer))
        m_label->insertFormFactor(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleLayout>(multilayer))
        m_label->insertLayout(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<IInterferenceFunction>(multilayer))
        m_label->insertInterferenceFunction(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Particle>(multilayer))
        m_label->insertParticle(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleCoreShell>(multilayer))
        m_label->insertParticleCoreShell(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleComposition>(multilayer))
        m_label->insertParticleComposition(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<ParticleDistribution>(multilayer))
        m_label->insertParticleDistribution(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Lattice2D>(multilayer))
        m_label->insertLattice2D(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Lattice3D>(multilayer))
        m_label->insertLattice3D(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<Crystal>(multilayer))
        m_label->insertCrystal(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<MesoCrystal>(multilayer))
        m_label->insertMesoCrystal(x);
    for (const auto* x : INodeUtils::AllDescendantsOfType<IRotation>(multilayer))
        m_label->insertRotation(x);
}

SampleToPython::SampleToPython() = default;

SampleToPython::~SampleToPython() = default;

std::string SampleToPython::defineGetSample() const {
    return "def get_sample():\n" + defineMaterials() + defineLayers() + defineFormFactors()
           + defineParticles() + defineCoreShellParticles() + defineParticleCompositions()
           + defineLattices2D() + defineLattices3D() + defineCrystals() + defineMesoCrystals()
           + defineParticleDistributions() + defineInterferenceFunctions() + defineParticleLayouts()
           + defineRoughnesses() + addLayoutsToLayers() + defineMultiLayers() + "\n\n";
}

const std::map<MATERIAL_TYPES, std::string> factory_names{
    {MATERIAL_TYPES::RefractiveMaterial, "HomogeneousMaterial"},
    {MATERIAL_TYPES::MaterialBySLD, "MaterialBySLD"}};

std::string SampleToPython::defineMaterials() const {
    const LabelMap<const Material*>* themap = m_label->materialMap();
    if (themap->empty())
        return "# No materials.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << indent() << "# Define materials\n";
    std::set<std::string> visitedMaterials;
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        if (visitedMaterials.find(it->second) != visitedMaterials.end())
            continue;
        visitedMaterials.insert(it->second);
        const Material* material = it->first;
        const auto factory_name = factory_names.find(material->typeID());
        if (factory_name == factory_names.cend())
            throw std::runtime_error(
                "Error in ExportToPython::defineMaterials(): unknown material type");
        const complex_t& material_data = material->materialData();
        if (material->isScalarMaterial()) {
            result << indent() << m_label->labelMaterial(material) << " = ba."
                   << factory_name->second << "(\"" << material->getName() << "\", "
                   << pyfmt::printDouble(material_data.real()) << ", "
                   << pyfmt::printDouble(material_data.imag()) << ")\n";
        } else {
            kvector_t magnetic_field = material->magnetization();
            result << indent() << "magnetic_field = kvector_t(" << magnetic_field.x() << ", "
                   << magnetic_field.y() << ", " << magnetic_field.z() << ")\n";
            result << indent() << m_label->labelMaterial(material) << " = ba."
                   << factory_name->second << "(\"" << material->getName();
            result << "\", " << pyfmt::printDouble(material_data.real()) << ", "
                   << pyfmt::printDouble(material_data.imag()) << ", "
                   << "magnetic_field)\n";
        }
    }
    return result.str();
}

std::string SampleToPython::defineLayers() const {
    const auto* themap = m_label->layerMap();
    if (themap->empty())
        return "# No Layers.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define layers\n";
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

std::string SampleToPython::defineFormFactors() const {
    const auto* themap = m_label->formFactorMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define form factors\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const IFormFactor* ff = it->first;
        result << indent() << it->second << " = ba.FormFactor" << ff->getName() << "("
               << pyfmt2::argumentList(ff) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineParticles() const {
    const auto* themap = m_label->particleMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Particle* particle = it->first;
        std::string particle_name = it->second;
        const auto* ff = INodeUtils::OnlyChildOfType<IFormFactor>(*particle);
        if (!ff)
            continue;
        result << indent() << particle_name << " = ba.Particle("
               << m_label->labelMaterial(particle->material()) << ", "
               << m_label->labelFormFactor(ff) << ")\n";
        setRotationInformation(particle, particle_name, result);
        setPositionInformation(particle, particle_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineCoreShellParticles() const {
    const auto* themap = m_label->particleCoreShellMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define core shell particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleCoreShell* coreshell = it->first;
        result << "\n"
               << indent() << it->second << " = ba.ParticleCoreShell("
               << m_label->labelParticle(coreshell->shellParticle()) << ", "
               << m_label->labelParticle(coreshell->coreParticle()) << ")\n";
        std::string core_shell_name = it->second;
        setRotationInformation(coreshell, core_shell_name, result);
        setPositionInformation(coreshell, core_shell_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineParticleDistributions() const {
    const auto* themap = m_label->particleDistributionsMap();
    if (themap->empty())
        return "";

    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define particles with parameter following a distribution\n";

    int index(1);
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleDistribution* particle_distr = it->first;

        const std::string units = particle_distr->mainUnits();

        ParameterDistribution par_distr = particle_distr->parameterDistribution();

        // building distribution functions
        std::string s_distr = "distr_" + std::to_string(index);
        result << indent() << s_distr << " = "
               << pyfmt2::printDistribution(*par_distr.getDistribution(), units) << "\n";

        // building parameter distribution
        std::string s_par_distr = "par_distr_" + std::to_string(index);

        result << indent() << s_par_distr << " = "
               << pyfmt2::printParameterDistribution(par_distr, s_distr, units) << "\n";

        // linked parameters
        std::vector<std::string> linked_pars = par_distr.getLinkedParameterNames();
        if (!linked_pars.empty()) {
            result << indent() << s_par_distr;
            for (size_t i = 0; i < linked_pars.size(); ++i)
                result << ".linkParameter(\"" << linked_pars[i] << "\")";
            result << "\n";
        }

        auto particle = INodeUtils::OnlyChildOfType<IParticle>(*particle_distr);
        if (!particle)
            continue;
        result << indent() << it->second << " = ba.ParticleDistribution("
               << m_label->labelParticle(particle) << ", " << s_par_distr << ")\n";
        index++;
    }
    return result.str();
}

std::string SampleToPython::defineParticleCompositions() const {
    const auto* themap = m_label->particleCompositionMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define composition of particles at specific positions\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleComposition* particle_composition = it->first;
        std::string particle_composition_name = it->second;
        result << indent() << particle_composition_name << " = ba.ParticleComposition()\n";
        const auto particle_list = INodeUtils::ChildNodesOfType<IParticle>(*particle_composition);
        for (const auto* particle : particle_list) {
            result << indent() << particle_composition_name << ".addParticle("
                   << m_label->labelParticle(particle) << ")\n";
        }
        setRotationInformation(particle_composition, particle_composition_name, result);
        setPositionInformation(particle_composition, particle_composition_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineLattices2D() const {
    const auto* themap = m_label->lattice2DMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define 2D lattices\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Lattice2D* lattice = it->first;
        std::string lattice_name = it->second;
        result << indent() << lattice_name << " = ba.BasicLattice2D(\n";
        result << indent() << indent() << pyfmt::printNm(lattice->length1()) << ", "
               << pyfmt::printNm(lattice->length2()) << ", "
               << pyfmt::printDegrees(lattice->latticeAngle()) << ", "
               << pyfmt::printDegrees(lattice->rotationAngle()) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineLattices3D() const {
    const auto* themap = m_label->lattice3DMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define 3D lattices\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Lattice3D* lattice = it->first;
        std::string lattice_name = it->second;
        kvector_t bas_a = lattice->getBasisVectorA();
        kvector_t bas_b = lattice->getBasisVectorB();
        kvector_t bas_c = lattice->getBasisVectorC();
        result << indent() << lattice_name << " = ba.Lattice3D(\n";
        result << indent() << indent() << "ba.kvector_t(" << pyfmt::printNm(bas_a.x()) << ", "
               << pyfmt::printNm(bas_a.y()) << ", " << pyfmt::printNm(bas_a.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t(" << pyfmt::printNm(bas_b.x()) << ", "
               << pyfmt::printNm(bas_b.y()) << ", " << pyfmt::printNm(bas_b.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t(" << pyfmt::printNm(bas_c.x()) << ", "
               << pyfmt::printNm(bas_c.y()) << ", " << pyfmt::printNm(bas_c.z()) << "))\n";
    }
    return result.str();
}

std::string SampleToPython::defineCrystals() const {
    const auto* themap = m_label->crystalMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define crystals: basis particle + lattice\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const Crystal* crystal = it->first;
        std::string crystal_name = it->second;
        const auto* lattice = INodeUtils::OnlyChildOfType<Lattice3D>(*crystal);
        const auto* basis = INodeUtils::OnlyChildOfType<IParticle>(*crystal);
        if (!lattice || !basis)
            continue;
        result << indent() << crystal_name << " = ba.Crystal(";
        result << m_label->labelParticle(basis) << ", ";
        result << m_label->labelLattice3D(lattice) << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineMesoCrystals() const {
    const auto* themap = m_label->mesocrystalMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define mesocrystals\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const MesoCrystal* mesocrystal = it->first;
        std::string mesocrystal_name = it->second;
        auto crystal = INodeUtils::OnlyChildOfType<Crystal>(*mesocrystal);
        auto outer_shape = INodeUtils::OnlyChildOfType<IFormFactor>(*mesocrystal);
        if (!crystal || !outer_shape)
            continue;
        result << indent() << mesocrystal_name << " = ba.MesoCrystal(";
        result << m_label->labelCrystal(crystal) << ", ";
        result << m_label->labelFormFactor(outer_shape) << ")\n";
        setRotationInformation(mesocrystal, mesocrystal_name, result);
        setPositionInformation(mesocrystal, mesocrystal_name, result);
    }
    return result.str();
}

std::string SampleToPython::defineInterferenceFunctions() const {
    const auto* themap = m_label->interferenceFunctionMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define interference functions\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const IInterferenceFunction* interference = it->first;

        if (dynamic_cast<const InterferenceFunctionNone*>(interference))
            result << indent() << it->second << " = ba.InterferenceFunctionNone()\n";

        else if (const auto* iff =
                     dynamic_cast<const InterferenceFunction1DLattice*>(interference)) {
            result << indent() << it->second << " = ba.InterferenceFunction1DLattice("
                   << pyfmt::printNm(iff->getLength()) << ", " << pyfmt::printDegrees(iff->getXi())
                   << ")\n";

            const auto* pdf = INodeUtils::OnlyChildOfType<IFTDecayFunction1D>(*iff);

            if (pdf->decayLength() != 0.0)
                result << indent() << it->second << "_pdf  = ba." << pdf->getName() << "("
                       << pyfmt2::argumentList(pdf) << ")\n"
                       << indent() << it->second << ".setDecayFunction(" << it->second << "_pdf)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(interference)) {
            result << indent() << it->second << " = ba.InterferenceFunctionRadialParaCrystal("
                   << pyfmt::printNm(iff->peakDistance()) << ", "
                   << pyfmt::printNm(iff->dampingLength()) << ")\n";

            if (iff->kappa() != 0.0)
                result << indent() << it->second << ".setKappa(" << pyfmt::printDouble(iff->kappa())
                       << ")\n";

            if (iff->domainSize() != 0.0)
                result << indent() << it->second << ".setDomainSize("
                       << pyfmt::printDouble(iff->domainSize()) << ")\n";

            const auto* pdf = INodeUtils::OnlyChildOfType<IFTDistribution1D>(*iff);

            if (pdf->omega() != 0.0)
                result << indent() << it->second << "_pdf  = ba." << pdf->getName() << "("
                       << pyfmt2::argumentList(pdf) << ")\n"
                       << indent() << it->second << ".setProbabilityDistribution(" << it->second
                       << "_pdf)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunction2DLattice*>(interference)) {
            const auto* lattice = INodeUtils::OnlyChildOfType<Lattice2D>(*iff);

            result << indent() << it->second << " = ba.InterferenceFunction2DLattice("
                   << m_label->labelLattice2D(lattice) << ")\n";

            const auto* pdf = INodeUtils::OnlyChildOfType<IFTDecayFunction2D>(*iff);

            result << indent() << it->second << "_pdf  = ba." << pdf->getName() << "("
                   << pyfmt2::argumentList(pdf) << ")\n"
                   << indent() << it->second << ".setDecayFunction(" << it->second << "_pdf)\n";

            if (iff->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunctionFinite2DLattice*>(interference)) {
            const auto* lattice = INodeUtils::OnlyChildOfType<Lattice2D>(*iff);

            result << indent() << it->second << " = ba.InterferenceFunctionFinite2DLattice("
                   << m_label->labelLattice2D(lattice) << ", " << iff->numberUnitCells1() << ", "
                   << iff->numberUnitCells2() << ")\n";

            if (iff->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";

        } else if (const auto* iff =
                       dynamic_cast<const InterferenceFunction2DParaCrystal*>(interference)) {
            const auto* lattice = INodeUtils::OnlyChildOfType<Lattice2D>(*iff);
            std::vector<double> domainSize = iff->domainSizes();

            result << indent() << it->second << " = ba.InterferenceFunction2DParaCrystal("
                   << m_label->labelLattice2D(lattice) << ", "
                   << pyfmt::printNm(iff->dampingLength()) << ", " << pyfmt::printNm(domainSize[0])
                   << ", " << pyfmt::printNm(domainSize[1]) << ")\n";

            if (iff->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";

            const auto pdf_vector = INodeUtils::ChildNodesOfType<IFTDistribution2D>(*iff);
            if (pdf_vector.size() != 2)
                continue;
            const IFTDistribution2D* pdf = pdf_vector[0];

            result << indent() << it->second << "_pdf_1  = ba." << pdf->getName() << "("
                   << pyfmt2::argumentList(pdf) << ")\n";

            pdf = pdf_vector[1];

            result << indent() << it->second << "_pdf_2  = ba." << pdf->getName() << "("
                   << pyfmt2::argumentList(pdf) << ")\n";
            result << indent() << it->second << ".setProbabilityDistributions(" << it->second
                   << "_pdf_1, " << it->second << "_pdf_2)\n";

        } else if (const auto* lattice_hd =
                       dynamic_cast<const InterferenceFunctionHardDisk*>(interference)) {
            result << indent() << it->second << " = ba.InterferenceFunctionHardDisk("
                   << pyfmt::printNm(lattice_hd->radius()) << ", "
                   << pyfmt::printDouble(lattice_hd->density()) << ")\n";

        } else
            throw std::runtime_error(
                "Bug: ExportToPython::defineInterferenceFunctions() called with unexpected "
                "IInterferenceFunction "
                + interference->getName());

        if (interference->positionVariance() > 0.0) {
            result << indent() << it->second << ".setPositionVariance("
                   << pyfmt::printNm2(interference->positionVariance()) << ")\n";
        }
    }
    return result.str();
}

std::string SampleToPython::defineParticleLayouts() const {
    const auto* themap = m_label->particleLayoutMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define particle layouts and adding particles\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        const ParticleLayout* iLayout = it->first;
        if (const ParticleLayout* particleLayout = dynamic_cast<const ParticleLayout*>(iLayout)) {
            result << indent() << it->second << " = ba.ParticleLayout()\n";
            const auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(*particleLayout);

            for (const auto* particle : particles) {
                double abundance = particle->abundance();
                result << indent() << it->second << ".addParticle("
                       << m_label->labelParticle(particle) << ", " << pyfmt::printDouble(abundance)
                       << ")\n";
            }
            if (const auto* iff =
                    INodeUtils::OnlyChildOfType<IInterferenceFunction>(*particleLayout))
                result << indent() << it->second << ".setInterferenceFunction("
                       << m_label->labelInterferenceFunction(iff) << ")\n";
            result << indent() << it->second << ".setWeight(" << particleLayout->weight() << ")\n";
            result << indent() << it->second << ".setTotalParticleSurfaceDensity("
                   << particleLayout->totalParticleSurfaceDensity() << ")\n";
        }
    }
    return result.str();
}

std::string SampleToPython::defineRoughnesses() const {
    const auto* themap = m_label->layerRoughnessMap();
    if (themap->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define roughness parameters\n";
    for (auto it = themap->begin(); it != themap->end(); ++it)
        result << indent() << it->second << " = ba.LayerRoughness("
               << pyfmt2::argumentList(it->first) << ")\n";
    return result.str();
}

std::string SampleToPython::addLayoutsToLayers() const {
    if (m_label->particleLayoutMap()->empty())
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Add layouts to layers";
    const auto layermap = m_label->layerMap();
    for (auto it = layermap->begin(); it != layermap->end(); ++it) {
        const Layer* layer = it->first;
        for (const auto* layout : layer->layouts())
            result << "\n"
                   << indent() << it->second << ".addLayout(" << m_label->labelLayout(layout)
                   << ")\n";
    }
    return result.str();
}

std::string SampleToPython::defineMultiLayers() const {
    const auto* themap = m_label->multiLayerMap();
    if (themap->empty())
        return "# No MultiLayers.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Define multilayers\n";
    for (auto it = themap->begin(); it != themap->end(); ++it) {
        result << indent() << it->second << " = ba.MultiLayer()\n";
        double ccl = it->first->crossCorrLength();
        if (ccl > 0.0)
            result << indent() << it->second << ".setCrossCorrLength(" << ccl << ")\n";
        auto external_field = it->first->externalField();
        if (external_field.mag() > 0.0) {
            std::string field_name = it->second + "_external_field";
            result << indent() << field_name << " = kvector_t("
                   << pyfmt::printScientificDouble(external_field.x()) << ", "
                   << pyfmt::printScientificDouble(external_field.y()) << ", "
                   << pyfmt::printScientificDouble(external_field.z()) << ")\n";
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
        result << "\n" << indent() << "return " << it->second << "\n";
    }
    return result.str();
}
