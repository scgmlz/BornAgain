// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ExportToPython.cpp
//! @brief     Implements class ExportToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ExportToPython.h"
#include "Beam.h"
#include "ConvolutionDetectorResolution.h"
#include "Crystal.h"
#include "Distributions.h"
#include "GISASSimulation.h"
#include "IFormFactor.h"
#include "INodeUtils.h"
#include "InterferenceFunctions.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "DWBAComputation.h"
#include "Material.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "PythonFormatting.h"
#include "RectangularDetector.h"
#include "ResolutionFunction2DGaussian.h"
#include "SampleLabelHandler.h"
#include "SphericalDetector.h"
#include "StringUtils.h"
#include "RegionOfInterest.h"
#include "BornAgainNamespace.h"
#include "ParameterUtils.h"
#include <iomanip>
#include <set>
#include <map>
#include <functional>

class IFormFactor;
class LayerRoughness;

using namespace PythonFormatting;
using namespace INodeUtils;

namespace {
    const std::string preamble =
        "import numpy\n"
        "import bornagain as ba\n"
        "from bornagain import deg, angstrom, nm, kvector_t\n\n";

    const std::string defineSimulate =
        "def run_simulation():\n"
        "    # Run Simulation\n"
        "    sample = getSample()\n"
        "    simulation = getSimulation()\n"
        "    simulation.setSample(sample)\n"
        "    simulation.runSimulation()\n"
        "    return simulation.getIntensityData()\n"
        "\n\n";

    //! Returns a function that converts a coordinate to a Python code snippet with appropiate unit
    std::function<std::string(double)> printFunc(const IDetector* detector)
    {
        if (detector->defaultAxesUnits() == AxesUnits::MM)
            return PythonFormatting::printDouble;
        if (detector->defaultAxesUnits() == AxesUnits::RADIANS)
            return PythonFormatting::printDegrees;
        throw Exceptions::RuntimeErrorException(
            "ExportToPython::defineMasks() -> Error. Unknown detector units.");
    }
} // namespace

ExportToPython::ExportToPython(){}

ExportToPython::~ExportToPython(){}

std::string ExportToPython::generateSampleCode(const MultiLayer& multilayer)
{
    initSample(multilayer);
    return defineGetSample();
}

//! Returns a Python script that sets up a simulation and runs it if invoked as main program.

std::string ExportToPython::generateSimulationCode(const GISASSimulation& simulation,
                                                   EMainType mainType)
{
    if (simulation.sample() == nullptr)
        throw std::runtime_error("ExportToPython::generateSimulationCode() -> Error. "
                                 "Simulation is not initialized.");

    initSample(*simulation.sample());

    return preamble
        + defineGetSample()
        + defineGetSimulation(&simulation)
        + defineSimulate
        + defineMain(mainType);
}

std::string ExportToPython::defineGetSimulation(const GISASSimulation* simulation) const
{
    std::ostringstream result;
    result << "def getSimulation():\n";
    //    result << indent() << "# Creating and returning GISAXS simulation\n";
    result << indent() << "simulation = ba.GISASSimulation()\n";
    result << defineDetector(simulation);
    result << defineDetectorResolutionFunction(simulation);
    result << defineDetectorPolarizationAnalysis(simulation);
    result << defineBeam(simulation);
    result << defineParameterDistributions(simulation);
    result << defineMasks(simulation);
    result << defineSimulationOptions(simulation);
    result << indent() << "return simulation\n\n\n";
    return result.str();
}

void ExportToPython::initSample(const MultiLayer& multilayer)
{
    m_label.reset(new SampleLabelHandler());

    m_label->insertMultiLayer(&multilayer);

    for( auto x: multilayer.containedMaterials() )
        m_label->insertMaterial(x);
    for( auto x: AllDescendantsOfType<Layer>(multilayer) )
        m_label->insertLayer(x);
    for( auto x: AllDescendantsOfType<LayerRoughness>(multilayer) )
        m_label->insertRoughness(x);
    for( auto x: AllDescendantsOfType<IFormFactor>(multilayer) )
        m_label->insertFormFactor(x);
    for( auto x: AllDescendantsOfType<ILayout>(multilayer) )
        m_label->insertLayout(x);
    for( auto x: AllDescendantsOfType<IInterferenceFunction>(multilayer) )
        m_label->insertInterferenceFunction(x);
    for( auto x: AllDescendantsOfType<Particle>(multilayer) )
        m_label->insertParticle(x);
    for( auto x: AllDescendantsOfType<ParticleCoreShell>(multilayer) )
        m_label->insertParticleCoreShell(x);
    for( auto x: AllDescendantsOfType<ParticleComposition>(multilayer) )
        m_label->insertParticleComposition(x);
    for( auto x: AllDescendantsOfType<ParticleDistribution>(multilayer) )
        m_label->insertParticleDistribution(x);
    for( auto x: AllDescendantsOfType<Lattice>(multilayer) )
        m_label->insertLattice(x);
    for( auto x: AllDescendantsOfType<Crystal>(multilayer) )
        m_label->insertCrystal(x);
    for( auto x: AllDescendantsOfType<MesoCrystal>(multilayer) )
        m_label->insertMesoCrystal(x);
    for( auto x: AllDescendantsOfType<IRotation>(multilayer) )
        m_label->insertRotation(x);
}

std::string ExportToPython::defineGetSample() const
{
    return "def getSample():\n"
        + defineMaterials()
        + defineLayers()
        + defineFormFactors()
        + defineParticles()
        + defineCoreShellParticles()
        + defineParticleCompositions()
        + defineLattices()
        + defineCrystals()
        + defineMesoCrystals()
        + defineParticleDistributions()
        + defineInterferenceFunctions()
        + defineParticleLayouts()
        + defineRoughnesses()
        + addLayoutsToLayers()
        + defineMultiLayers()
        + "\n";
}

const std::map<MATERIAL_TYPES, std::string> factory_names{
    {MATERIAL_TYPES::RefractiveMaterial, "HomogeneousMaterial"},
    {MATERIAL_TYPES::MaterialBySLD, "MaterialBySLD"}};

std::string ExportToPython::defineMaterials() const
{
    const auto themap = m_label->materialMap();
    if (themap->size() == 0)
        return "# No Materials.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << indent() << "# Defining Materials\n";
    std::set<std::string> visitedMaterials;
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
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

std::string ExportToPython::defineLayers() const
{
    const auto themap = m_label->layerMap();
    if (themap->size() == 0)
        return "# No Layers.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Layers\n";
    for (auto it=themap->begin(); it != themap->end(); ++it) {
        const Layer* layer = it->first;
        result << indent() << it->second << " = ba.Layer(" <<
            m_label->labelMaterial(layer->material());
        if (layer->thickness() != 0)
            result << ", " << layer->thickness();
        result << ")\n";
        if (layer->numberOfSlices()!=1)
            result << indent() << it->second << ".setNumberOfSlices("
                   << layer->numberOfSlices() << ")\n";
    }
    return result.str();
}

std::string ExportToPython::defineFormFactors() const
{
    const auto themap = m_label->formFactorMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Form Factors\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const IFormFactor* p_ff = it->first;
        result << indent() << it->second << " = ba.FormFactor" << p_ff->getName() << "("
               << argumentList(p_ff) << ")\n";
    }
    return result.str();
}

std::string ExportToPython::defineParticles() const
{
    const auto themap = m_label->particleMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Particles\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const Particle* p_particle = it->first;
        std::string particle_name = it->second;
        auto p_ff = OnlyChildOfType<IFormFactor>(*p_particle);
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

std::string ExportToPython::defineCoreShellParticles() const
{
    const auto themap = m_label->particleCoreShellMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Core Shell Particles\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const ParticleCoreShell* p_coreshell = it->first;
        result << "\n" << indent() << it->second << " = ba.ParticleCoreShell("
               << m_label->labelParticle(p_coreshell->shellParticle()) << ", "
               << m_label->labelParticle(p_coreshell->coreParticle()) << ")\n";
        std::string core_shell_name = it->second;
        setRotationInformation(p_coreshell, core_shell_name, result);
        setPositionInformation(p_coreshell, core_shell_name, result);
    }
    return result.str();
}

std::string ExportToPython::defineParticleDistributions() const
{
    const auto themap = m_label->particleDistributionsMap();
    if (themap->size() == 0)
        return "";

    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining particles with parameter following a distribution\n";

    int index(1);
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
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
        if(linked_pars.size()) {
            result << indent() << s_par_distr;
            for(size_t i=0; i<linked_pars.size(); ++i)
                result << ".linkParameter(\"" << linked_pars[i] << "\")";
            result << "\n";
        }

        auto p_particle = OnlyChildOfType<IParticle>(*p_particle_distr);
        if (!p_particle)
            continue;
        result << indent() << it->second << " = ba.ParticleDistribution("
               << m_label->labelParticle(p_particle)
               << ", " << s_par_distr << ")\n";
        index++;
    }
    return result.str();
}

std::string ExportToPython::defineParticleCompositions() const
{
    const auto themap = m_label->particleCompositionMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining composition of particles at specific positions\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const ParticleComposition* p_particle_composition = it->first;
        std::string particle_composition_name = it->second;
        result << indent() << particle_composition_name << " = ba.ParticleComposition()\n";
        auto particle_list = ChildNodesOfType<IParticle>(*p_particle_composition);
        for (auto p_particle : particle_list) {
            result << indent() << particle_composition_name << ".addParticle("
                   << m_label->labelParticle(p_particle)
            << ")\n";
        }
        setRotationInformation(p_particle_composition, particle_composition_name, result);
        setPositionInformation(p_particle_composition, particle_composition_name, result);
    }
    return result.str();
}

std::string ExportToPython::defineLattices() const
{
    const auto themap = m_label->latticeMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining 3D lattices\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const Lattice* p_lattice = it->first;
        std::string lattice_name = it->second;
        kvector_t bas_a = p_lattice->getBasisVectorA();
        kvector_t bas_b = p_lattice->getBasisVectorB();
        kvector_t bas_c = p_lattice->getBasisVectorC();
        result << indent() << lattice_name << " = ba.Lattice(\n";
        result << indent() << indent() << "ba.kvector_t("
               << printNm(bas_a.x()) << ", "
               << printNm(bas_a.y()) << ", "
               << printNm(bas_a.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t("
               << printNm(bas_b.x()) << ", "
               << printNm(bas_b.y()) << ", "
               << printNm(bas_b.z()) << "),\n";
        result << indent() << indent() << "ba.kvector_t("
               << printNm(bas_c.x()) << ", "
               << printNm(bas_c.y()) << ", "
               << printNm(bas_c.z()) << "))\n";
    }
    return result.str();
}

std::string ExportToPython::defineCrystals() const
{
    const auto themap = m_label->crystalMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining crystals: basis particle + lattice\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const Crystal* p_crystal = it->first;
        std::string crystal_name = it->second;
        auto p_lattice = OnlyChildOfType<Lattice>(*p_crystal);
        auto p_basis = OnlyChildOfType<IParticle>(*p_crystal);
        if (!p_lattice || !p_basis)
            continue;
        result << indent() << crystal_name << " = ba.Crystal(";
        result << m_label->labelParticle(p_basis) << ", ";
        result << m_label->labelLattice(p_lattice) << ")\n";
    }
    return result.str();
}

std::string ExportToPython::defineMesoCrystals() const
{
    const auto themap = m_label->mesocrystalMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining mesocrystals\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const MesoCrystal* p_mesocrystal = it->first;
        std::string mesocrystal_name = it->second;
        auto p_crystal = OnlyChildOfType<Crystal>(*p_mesocrystal);
        auto p_outer_shape = OnlyChildOfType<IFormFactor>(*p_mesocrystal);
        if (!p_crystal || ! p_outer_shape)
            continue;
        result << indent() << mesocrystal_name << " = ba.MesoCrystal(";
        result << m_label->labelCrystal(p_crystal) << ", ";
        result << m_label->labelFormFactor(p_outer_shape) << ")\n";
        setRotationInformation(p_mesocrystal, mesocrystal_name, result);
        setPositionInformation(p_mesocrystal, mesocrystal_name, result);
    }
    return result.str();
}

std::string ExportToPython::defineInterferenceFunctions() const
{
    const auto themap = m_label->interferenceFunctionMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Interference Functions\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const IInterferenceFunction* interference = it->first;

        if (dynamic_cast<const InterferenceFunctionNone*>(interference))
            result << indent() << it->second << " = ba.InterferenceFunctionNone()\n";
        else if (auto p_lattice_1d
                 = dynamic_cast<const InterferenceFunction1DLattice*>(interference)) {
            const Lattice1DParameters latticeParameters = p_lattice_1d->getLatticeParameters();
            result << indent() << it->second << " = ba.InterferenceFunction1DLattice("
                   << printNm(latticeParameters.m_length) << ", "
                   << printDegrees(latticeParameters.m_xi) << ")\n";

            auto pdf = OnlyChildOfType<IFTDecayFunction1D>(*p_lattice_1d);

            if (pdf->decayLength() != 0.0)
                result << indent() << it->second << "_pdf  = ba." << pdf->getName()
                       << "(" << argumentList(pdf) << ")\n"
                       << indent() << it->second << ".setDecayFunction(" << it->second << "_pdf)\n";
        }
        else if (auto p_para_radial
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

            auto pdf = OnlyChildOfType<IFTDistribution1D>(*p_para_radial);

            if (pdf->omega() != 0.0)
                result << indent() << it->second << "_pdf  = ba." << pdf->getName()
                       << "(" << argumentList(pdf) << ")\n"
                       << indent() << it->second << ".setProbabilityDistribution(" << it->second
                       << "_pdf)\n";
        }
        else if (auto p_lattice_2d
                 = dynamic_cast<const InterferenceFunction2DLattice*>(interference)) {
            const Lattice2D& lattice = p_lattice_2d->lattice();
            result << indent() << it->second << " = ba.InterferenceFunction2DLattice("
                   << printNm(lattice.length1()) << ", "
                   << printNm(lattice.length2()) << ", "
                   << printDegrees(lattice.latticeAngle()) << ", "
                   << printDegrees(lattice.rotationAngle()) << ")\n";

            auto pdf = OnlyChildOfType<IFTDecayFunction2D>(*p_lattice_2d);

            result << indent() << it->second << "_pdf  = ba." << pdf->getName()
                   << "(" << argumentList(pdf) << ")\n"
                   << indent() << it->second << ".setDecayFunction(" << it->second << "_pdf)\n";

            if (p_lattice_2d->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";
        }
        else if (auto p_para_2d
                 = dynamic_cast<const InterferenceFunction2DParaCrystal*>(interference)) {
            std::vector<double> domainSize = p_para_2d->domainSizes();
            const Lattice2D& lattice = p_para_2d->lattice();
            result << indent() << it->second << " = ba.InterferenceFunction2DParaCrystal("
                   << printNm(lattice.length1())
                   << ", "
                   << printNm(lattice.length2())
                   << ", "
                   << printDegrees(lattice.latticeAngle())
                   << ", "
                   << printDegrees(lattice.rotationAngle())
                   << ", "
                   << printNm(p_para_2d->dampingLength()) << ")\n";

            if (domainSize[0] != 0.0 || domainSize[1] != 0.0)
                result << indent() << it->second << ".setDomainSizes("
                       << printNm(domainSize[0]) << ", "
                                                 << printNm(domainSize[1]) << ")\n";
            if (p_para_2d->integrationOverXi() == true)
                result << indent() << it->second << ".setIntegrationOverXi(True)\n";

            auto pdf_vector = ChildNodesOfType<IFTDistribution2D>(*p_para_2d);
            if (pdf_vector.size()!=2)
                continue;
            const IFTDistribution2D* pdf = pdf_vector[0];

            result << indent() << it->second << "_pdf_1  = ba." << pdf->getName()
                   << "(" << argumentList(pdf) << ")\n";

            pdf = pdf_vector[1];

            result << indent() << it->second << "_pdf_2  = ba." << pdf->getName()
                   << "(" << argumentList(pdf) << ")\n";
            result << indent() << it->second << ".setProbabilityDistributions(" << it->second
                   << "_pdf_1, " << it->second << "_pdf_2)\n";
        }
        else
            throw Exceptions::NotImplementedException(
                "Bug: ExportToPython::defineInterferenceFunctions() called with unexpected "
                "IInterferenceFunction " + interference->getName());
    }
    return result.str();
}

std::string ExportToPython::defineParticleLayouts() const
{
    const auto themap = m_label->particleLayoutMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Particle Layouts and adding Particles\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        const ILayout* iLayout = it->first;
        if (const ParticleLayout* particleLayout = dynamic_cast<const ParticleLayout*>(iLayout)) {
            result << indent() << it->second << " = ba.ParticleLayout()\n";
            auto particles = ChildNodesOfType<IAbstractParticle>(*particleLayout);

            for (auto p_particle : particles) {
                double abundance = p_particle->abundance();
                result << indent() << it->second << ".addParticle("
                       << m_label->labelParticle(p_particle) << ", "
                       << printDouble(abundance) << ")\n";
            }
            if( auto p_iff = OnlyChildOfType<IInterferenceFunction>(*particleLayout) )
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

std::string ExportToPython::defineRoughnesses() const
{
    const auto themap = m_label->layerRoughnessMap();
    if (themap->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Roughness Parameters\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it)
        result << indent() << it->second << " = ba.LayerRoughness("
               <<  argumentList(it->first) << ")\n";
    return result.str();
}

std::string ExportToPython::addLayoutsToLayers() const
{
    if (m_label->particleLayoutMap()->size() == 0)
        return "";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Adding layouts to layers";
    const auto layermap = m_label->layerMap();
    for (auto it=layermap->begin(); it!=layermap->end(); ++it) {
        const Layer* layer = it->first;
        for (auto p_layout : layer->layouts())
            result << "\n" << indent() << it->second << ".addLayout("
                   << m_label->labelLayout(p_layout) << ")\n";
    }
    return result.str();
}

std::string ExportToPython::defineMultiLayers() const
{
    const auto themap = m_label->multiLayerMap();
    if (themap->size() == 0)
        return "# No MultiLayers.\n\n";
    std::ostringstream result;
    result << std::setprecision(12);
    result << "\n" << indent() << "# Defining Multilayers\n";
    for (auto it=themap->begin(); it!=themap->end(); ++it) {
        result << indent() << it->second << " = ba.MultiLayer()\n";
        double ccl = it->first->crossCorrLength();
        if (ccl > 0.0)
            result << indent() << it->second << ".setCrossCorrLength(" << ccl << ")\n";
        auto external_field = it->first->externalField();
        if (external_field.mag()>0.0) {
            std::string field_name = it->second + "_external_field";
            result << indent() << field_name << " = kvector_t("
                   << printScientificDouble(external_field.x()) << ", "
                   << printScientificDouble(external_field.y()) << ", "
                   << printScientificDouble(external_field.z()) << ")\n";
            result << indent() << it->second << ".setExternalField("
                   << field_name << ")\n";
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

std::string ExportToPython::defineDetector(const GISASSimulation* simulation) const
{
    const IDetector* iDetector = simulation->getInstrument().getDetector();

    if (iDetector->dimension() != 2)
        throw Exceptions::RuntimeErrorException("ExportToPython::defineDetector: "
                                                "detector must be two-dimensional for GISAS");
    std::ostringstream result;
    result << std::setprecision(12);

    if(auto detector = dynamic_cast<const SphericalDetector*>(iDetector)) {
        result << indent() << "simulation.setDetectorParameters(";
        for(size_t index=0; index<detector->dimension(); ++index) {
            if (index != 0) result << ", ";
            result << detector->getAxis(index).size() << ", "
                   << printDegrees(detector->getAxis(index).getMin()) << ", "
                   << printDegrees(detector->getAxis(index).getMax());
        }
        result << ")\n";
    } else if(auto detector = dynamic_cast<const RectangularDetector*>(iDetector)) {
        result << indent() << "\n";
        result << indent() << "detector = ba.RectangularDetector("
               << detector->getNbinsX() << ", "
               << printDouble(detector->getWidth()) << ", "
               << detector->getNbinsY() << ", "
               << printDouble(detector->getHeight()) << ")\n";
        if(detector->getDetectorArrangment() == RectangularDetector::GENERIC) {
            result << indent() << "detector.setPosition("
                   << printKvector(detector->getNormalVector()) << ", "
                   << printDouble(detector->getU0()) << ", "
                   << printDouble(detector->getV0());
            if(!isDefaultDirection(detector->getDirectionVector()))
                result << ", " << printKvector(detector->getDirectionVector());
            result << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
            result << indent() << "detector.setPerpendicularToSampleX("
                   << printDouble(detector->getDistance()) << ", "
                   << printDouble(detector->getU0()) << ", "
                   << printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
            result << indent() << "detector.setPerpendicularToDirectBeam("
                   << printDouble(detector->getDistance()) << ", "
                   << printDouble(detector->getU0()) << ", "
                   << printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << printDouble(detector->getDistance()) << ", "
                   << printDouble(detector->getU0()) << ", "
                   << printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << printDouble(detector->getDistance()) << ")\n";
            result << indent() << "detector.setDirectBeamPosition("
                   << printDouble(detector->getDirectBeamU0()) << ", "
                   << printDouble(detector->getDirectBeamV0()) << ")\n";
        } else
            throw Exceptions::RuntimeErrorException(
                "ExportToPython::defineDetector: unknown alignment");

        result << indent() << "simulation.setDetector(detector)\n";
    } else
        throw Exceptions::RuntimeErrorException("ExportToPython::defineDetector: unknown detector");
    if(iDetector->regionOfInterest()) {
        result << indent() << "simulation.setRegionOfInterest("
               << printFunc(iDetector)(iDetector->regionOfInterest()->getXlow()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getYlow()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getXup()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getYup()) << ")\n";
    }
    result << indent() << "\n";
    return result.str();
}

std::string ExportToPython::defineDetectorResolutionFunction(
    const GISASSimulation* simulation) const
{
    std::ostringstream result;
    const IDetector* detector = simulation->getInstrument().getDetector();

    if (const IDetectorResolution* p_resfunc = detector->detectorResolution()) {
        if ( auto* p_convfunc = dynamic_cast<const ConvolutionDetectorResolution*>(p_resfunc)) {
            if (auto* resfunc = dynamic_cast<const ResolutionFunction2DGaussian*>(
                    p_convfunc->getResolutionFunction2D())) {
                result << indent() << "simulation.setDetectorResolutionFunction(";
                result << "ba.ResolutionFunction2DGaussian(";
                result << printFunc(detector)(resfunc->getSigmaX()) << ", ";
                result << printFunc(detector)(resfunc->getSigmaY()) << "))\n";
            } else
                throw Exceptions::RuntimeErrorException(
                    "ExportToPython::defineDetectorResolutionFunction() -> Error. "
                    "Unknown detector resolution function");
        } else
            throw Exceptions::RuntimeErrorException(
                "ExportToPython::defineDetectorResolutionFunction() -> Error. "
                "Not a ConvolutionDetectorResolution function");
    }
    return result.str();
}

std::string ExportToPython::defineDetectorPolarizationAnalysis(
        const GISASSimulation* simulation) const
{
    std::ostringstream result;
    const IDetector* detector = simulation->getInstrument().getDetector();
    kvector_t analyzer_direction = detector->detectionProperties().analyzerDirection();
    double analyzer_efficiency = detector->detectionProperties().analyzerEfficiency();
    double analyzer_total_transmission = detector->detectionProperties().analyzerTotalTransmission();

    if (analyzer_direction.mag()>0.0) {
        std::string direction_name = "analyzer_direction";
        result << indent() << direction_name << " = kvector_t("
               << printDouble(analyzer_direction.x()) << ", "
               << printDouble(analyzer_direction.y()) << ", "
               << printDouble(analyzer_direction.z()) << ")\n";
        result << indent() << "simulation.setAnalyzerProperties("
               << direction_name << ", "
               << printDouble(analyzer_efficiency) << ", "
               << printDouble(analyzer_total_transmission) << ")\n";
    }
    return result.str();
}

std::string ExportToPython::defineBeam(const GISASSimulation* simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);
    // result << indent() << "# Defining Beam Parameters\n";
    const Beam& beam = simulation->getInstrument().getBeam();
    result << indent() << "simulation.setBeamParameters("
           << printNm(beam.getWavelength()) << ", "
           << printDegrees(beam.getAlpha()) << ", "
           << printDegrees(beam.getPhi()) << ")\n";
    auto bloch_vector = beam.getBlochVector();
    if (bloch_vector.mag()>0.0) {
        std::string beam_polarization = "beam_polarization";
        result << indent() << beam_polarization << " = kvector_t("
               << printDouble(bloch_vector.x()) << ", "
               << printDouble(bloch_vector.y()) << ", "
               << printDouble(bloch_vector.z()) << ")\n";
        result << indent() << "simulation.setBeamPolarization("
               << beam_polarization << ")\n";
    }
    double beam_intensity = beam.getIntensity();
    if(beam_intensity > 0.0)
        result << indent() << "simulation.setBeamIntensity("
               << printScientificDouble(beam_intensity) << ")\n";
    return result.str();
}

std::string ExportToPython::defineParameterDistributions(const GISASSimulation* simulation) const
{
    std::ostringstream result;
    const std::vector<ParameterDistribution>& distributions =
            simulation->getDistributionHandler().getDistributions();
    if (distributions.size()==0) return "";
    for (size_t i=0; i<distributions.size(); ++i) {
        std::string main_par_name = distributions[i].getMainParameterName();

        std::string mainParUnits = ParameterUtils::poolParameterUnits(*simulation, main_par_name);

        size_t nbr_samples = distributions[i].getNbrSamples();
        double sigma_factor = distributions[i].getSigmaFactor();

        std::string s_distr = "distr_" + std::to_string(i+1);
        result << indent() << s_distr << " = "
               << printDistribution(*distributions[i].getDistribution(), mainParUnits) << "\n";

        result << indent() << "simulation.addParameterDistribution(\"" << main_par_name << "\", "
               << s_distr << ", " << nbr_samples << ", "
               << printDouble(sigma_factor)
               << printRealLimitsArg(distributions[i].getLimits(), mainParUnits)
               << ")\n";
    }
    return result.str();
}

std::string ExportToPython::defineMasks(const GISASSimulation* simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);

    const IDetector* detector = simulation->getInstrument().getDetector();
    const DetectorMask* detectorMask = detector->detectorMask();
    if(detectorMask && detectorMask->numberOfMasks()) {
        result << "\n";
        for(size_t i_mask=0; i_mask<detectorMask->numberOfMasks(); ++i_mask) {
            bool mask_value(false);
            const IShape2D* shape = detectorMask->getMaskShape(i_mask, mask_value);
            result << representShape2D(indent(), shape, mask_value, printFunc(detector));
        }
        result << "\n";
    }
    return result.str();
}

std::string ExportToPython::defineSimulationOptions(const GISASSimulation* simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);

    const SimulationOptions& options = simulation->getOptions();
    if (options.getHardwareConcurrency() != options.getNumberOfThreads())
        result << indent() << "simulation.getOptions().setNumberOfThreads("
               << options.getNumberOfThreads() << ")\n";
    if (options.isIntegrate())
        result << indent() << "simulation.getOptions().setMonteCarloIntegration(True, "
               << options.getMcPoints() << ")\n";
    if (options.useAvgMaterials())
        result << indent() << "simulation.getOptions().setUseAvgMaterials(True)\n";
    if (options.includeSpecular())
        result << indent() << "simulation.getOptions().setIncludeSpecular(True)\n";
    return result.str();
}

std::string ExportToPython::defineMain(ExportToPython::EMainType mainType)
{
    std::string result;
    if(mainType == RUN_SIMULATION) {
        result = "if __name__ == '__main__': \n"
                 "    result = run_simulation()\n"
                 "    ba.plot_intensity_data(result)\n";
    } else if(mainType == SAVE_DATA) {
        result = "if __name__ == '__main__': \n"
                 "    result = run_simulation()\n"
                 "    import sys\n"
                 "    if len(sys.argv)<2:\n"
                 "        exit(\"File name is required\")\n"
                 "    ba.IntensityDataIOFactory.writeIntensityData(result, sys.argv[1])\n";
    } else {
        throw std::runtime_error("ExportToPython::defineMain() -> Error. Unknown main type.");
    }
    return result;
}

std::string ExportToPython::indent() const
{
    return "    ";
}

void ExportToPython::setRotationInformation(
    const IParticle* p_particle, std::string name, std::ostringstream& result) const
{
    if (p_particle->rotation()) {
        switch (p_particle->rotation()->getTransform3D().getRotationType()) {
        case Transform3D::EULER:
        {
            double alpha, beta, gamma;
            p_particle->rotation()->getTransform3D().calculateEulerAngles(&alpha, &beta, &gamma);
            result << indent() << name << "_rotation = ba.RotationEuler("
                   << printDegrees(alpha) << ", " << printDegrees(beta)
                   << ", " << printDegrees(gamma) << ")\n";
            break;
        }
        case Transform3D::XAXIS:
        {
            double alpha = p_particle->rotation()->getTransform3D().calculateRotateXAngle();
            result << indent() << name << "_rotation = ba.RotationX("
                   << printDegrees(alpha) << ")\n";
            break;
        }
        case Transform3D::YAXIS:
        {
            double alpha = p_particle->rotation()->getTransform3D().calculateRotateYAngle();
            result << indent() << name << "_rotation = ba.RotationY("
                   << printDegrees(alpha) << ")\n";
            break;
        }
        case Transform3D::ZAXIS:
        {
            double alpha = p_particle->rotation()->getTransform3D().calculateRotateZAngle();
            result << indent() << name << "_rotation = ba.RotationZ("
                   << printDegrees(alpha) << ")\n";
            break;
        }
        }
        result << indent() << name << ".setRotation(" << name << "_rotation)\n";
    }
}

void ExportToPython::setPositionInformation(
    const IParticle* p_particle, std::string name, std::ostringstream& result) const
{
    kvector_t pos = p_particle->position();
    bool has_position_info = (pos != kvector_t());

    if (has_position_info) {
        result << indent() << name
               << "_position = kvector_t("
               << printNm(pos.x()) << ", "
               << printNm(pos.y()) << ", "
               << printNm(pos.z()) << ")\n";

        result << indent()
               << name << ".setPosition("
               << name << "_position)\n";
    }
}
