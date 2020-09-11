// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformToDomain.h
//! @brief     Defines class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_TRANSFORMTODOMAIN_H
#define BORNAGAIN_GUI_COREGUI_MODELS_TRANSFORMTODOMAIN_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Beam/Beam.h"
#include "Core/Instrument/Instrument.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/Distributions.h" // for IDistribution1D
#include "Core/Particle/IParticle.h"
#include "Core/Particle/ParticleDistribution.h"
#include <memory>

class AngularSpecScan;
class BeamDistributionItem;
class GISASSimulation;
class Material;
class MaterialItemContainer;
class SessionItem;
class Simulation;

namespace TransformToDomain
{
BA_CORE_API_ std::unique_ptr<Material> createDomainMaterial(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<IParticle> createIParticle(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<Layer> createLayer(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<LayerRoughness> createLayerRoughness(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<MultiLayer> createMultiLayer(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<ParticleDistribution>
createParticleDistribution(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<ParticleLayout> createParticleLayout(const SessionItem& item);

BA_CORE_API_ void addDistributionParametersToSimulation(const SessionItem& beam_item,
                                                        GISASSimulation& simulation);
BA_CORE_API_ void addBeamDivergencesToScan(const SessionItem& beam_item,
                                           AngularSpecScan& simulation);

BA_CORE_API_ void setBeamDistribution(const std::string& parameter_name,
                                      const BeamDistributionItem& item, Simulation& simulation);

BA_CORE_API_ void setSimulationOptions(Simulation* simulation, const SessionItem& item);
BA_CORE_API_ void setTransformationInfo(IParticle* result, const SessionItem& item);
BA_CORE_API_ void setPositionInfo(IParticle* result, const SessionItem& item);
BA_CORE_API_ void setRotationInfo(IParticle* result, const SessionItem& item);
} // namespace TransformToDomain

#endif // BORNAGAIN_GUI_COREGUI_MODELS_TRANSFORMTODOMAIN_H
