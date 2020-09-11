// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformFromDomain.h
//! @brief     Defines namespace TransformFromDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_TRANSFORMFROMDOMAIN_H
#define BORNAGAIN_GUI_COREGUI_MODELS_TRANSFORMFROMDOMAIN_H

#include "Wrap/WinDllMacros.h"
#include <QString>

class BeamDistributionItem;
class BeamItem;
class Simulation;
class GISASSimulation;
class IFootprintFactor;
class InterferenceFunction1DLattice;
class InterferenceFunction2DLattice;
class InterferenceFunction2DParaCrystal;
class InterferenceFunctionFinite2DLattice;
class InterferenceFunctionHardDisk;
class InterferenceFunctionRadialParaCrystal;
class Layer;
class LayerInterface;
class LayerRoughness;
class ParameterDistribution;
class ParticleDistribution;
class RectangularDetector;
class RectangularDetectorItem;
class SessionItem;
class SpecularBeamItem;
class SpecularSimulation;
class SphericalDetector;
class SphericalDetectorItem;
class DetectorItem;
class MaskContainerItem;
class IDetector;
class GISASInstrumentItem;
class Instrument2DItem;
class InstrumentItem;
class Simulation2D;
class OffSpecSimulation;
class IAxis;

namespace TransformFromDomain
{
BA_CORE_API_ void set1DLatticeItem(SessionItem* item, const InterferenceFunction1DLattice& sample);

BA_CORE_API_ void set2DLatticeItem(SessionItem* item, const InterferenceFunction2DLattice& sample);

BA_CORE_API_ void set2DParaCrystalItem(SessionItem* item,
                                       const InterferenceFunction2DParaCrystal& sample);

BA_CORE_API_ void setFinite2DLatticeItem(SessionItem* item,
                                         const InterferenceFunctionFinite2DLattice& sample);

BA_CORE_API_ void setHardDiskItem(SessionItem* item, const InterferenceFunctionHardDisk& sample);

BA_CORE_API_ void setRadialParaCrystalItem(SessionItem* item,
                                           const InterferenceFunctionRadialParaCrystal& sample);

BA_CORE_API_ void setLayerItem(SessionItem* layer_item, const Layer* layer,
                               const LayerInterface* top_interface);

BA_CORE_API_ void setRoughnessItem(SessionItem* item, const LayerRoughness& sample);

BA_CORE_API_ void setParticleDistributionItem(SessionItem* item,
                                              const ParticleDistribution& sample);

BA_CORE_API_ bool isValidRoughness(const LayerRoughness* roughness);

BA_CORE_API_ void setGISASBeamItem(BeamItem* beam_item, const GISASSimulation& simulation);

BA_CORE_API_ void setOffSpecBeamItem(BeamItem* beam_item, const OffSpecSimulation& simulation);

BA_CORE_API_ void setSpecularBeamItem(SpecularBeamItem* beam_item,
                                      const SpecularSimulation& simulation);

BA_CORE_API_ void setDetector(Instrument2DItem* instrument_item, const Simulation2D& simulation);

BA_CORE_API_ void setDetectorGeometry(Instrument2DItem* instrument_item, const IDetector& detector);

BA_CORE_API_ void setDetectorResolution(DetectorItem* detector_item, const IDetector& detector);

BA_CORE_API_ void setDetectorProperties(DetectorItem* detector_item, const IDetector& detector);

BA_CORE_API_ void setSphericalDetector(SphericalDetectorItem* detector_item,
                                       const SphericalDetector& detector);

BA_CORE_API_ void setRectangularDetector(RectangularDetectorItem* detector_item,
                                         const RectangularDetector& detector);

BA_CORE_API_ void setDetectorMasks(DetectorItem* detector_item, const Simulation& simulation);

BA_CORE_API_ void setMaskContainer(MaskContainerItem* container_item, const IDetector& detector,
                                   double scale);

BA_CORE_API_ void setItemFromSample(BeamDistributionItem* beam_distribution_item,
                                    const ParameterDistribution& parameter_distribution);

BA_CORE_API_ void setBackground(InstrumentItem* instrument_item, const Simulation& simulation);

BA_CORE_API_ void setFootprintFactor(const IFootprintFactor* footprint,
                                     SpecularBeamItem* beam_item);

BA_CORE_API_ void setAxisItem(SessionItem* item, const IAxis& axis, double factor = 1.0);

} // namespace TransformFromDomain

#endif // BORNAGAIN_GUI_COREGUI_MODELS_TRANSFORMFROMDOMAIN_H
