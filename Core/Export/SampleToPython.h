//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleToPython.h
//! @brief     Defines class SampleToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_EXPORT_SAMPLETOPYTHON_H
#define BORNAGAIN_CORE_EXPORT_SAMPLETOPYTHON_H

#include <memory>
#include <string>

class IParticle;
class MultiLayer;
class ComponentKeyHandler;
class MaterialKeyHandler;

//! Generates Python code snippet from domain (C++) objects representing sample construction.

class SampleToPython {
public:
    SampleToPython();
    ~SampleToPython();

    std::string generateSampleCode(const MultiLayer& multilayer);

private:
    void initLabels(const MultiLayer& multilayer);

    std::string defineGetSample() const;
    std::string defineMaterials() const;
    std::string defineLayers() const;
    std::string defineFormFactors() const;
    std::string defineParticles() const;
    std::string defineCoreShellParticles() const;
    std::string defineParticleDistributions() const;
    std::string defineParticleCompositions() const;
    std::string defineLattices2D() const;
    std::string defineLattices3D() const;
    std::string defineCrystals() const;
    std::string defineMesoCrystals() const;
    std::string defineInterferenceFunctions() const;
    std::string defineParticleLayouts() const;
    std::string defineRoughnesses() const;
    std::string defineMultiLayers() const;

    std::unique_ptr<ComponentKeyHandler> m_objs;
    std::unique_ptr<MaterialKeyHandler> m_materials;
};

#endif // BORNAGAIN_CORE_EXPORT_SAMPLETOPYTHON_H
#endif // USER_API
