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
void set1DLatticeItem(SessionItem* item, const InterferenceFunction1DLattice& sample);

void set2DLatticeItem(SessionItem* item, const InterferenceFunction2DLattice& sample);

void set2DParaCrystalItem(SessionItem* item, const InterferenceFunction2DParaCrystal& sample);

void setFinite2DLatticeItem(SessionItem* item, const InterferenceFunctionFinite2DLattice& sample);

void setHardDiskItem(SessionItem* item, const InterferenceFunctionHardDisk& sample);

void setRadialParaCrystalItem(SessionItem* item,
                              const InterferenceFunctionRadialParaCrystal& sample);

void setLayerItem(SessionItem* layer_item, const Layer* layer, const LayerInterface* top_interface);

void setRoughnessItem(SessionItem* item, const LayerRoughness& sample);

void setParticleDistributionItem(SessionItem* item, const ParticleDistribution& sample);

bool isValidRoughness(const LayerRoughness* roughness);

void setGISASBeamItem(BeamItem* beam_item, const GISASSimulation& simulation);

void setOffSpecBeamItem(BeamItem* beam_item, const OffSpecSimulation& simulation);

void setSpecularBeamItem(SpecularBeamItem* beam_item, const SpecularSimulation& simulation);

void setDetector(Instrument2DItem* instrument_item, const Simulation2D& simulation);

void setDetectorGeometry(Instrument2DItem* instrument_item, const IDetector& detector);

void setDetectorResolution(DetectorItem* detector_item, const IDetector& detector);

void setDetectorProperties(DetectorItem* detector_item, const IDetector& detector);

void setSphericalDetector(SphericalDetectorItem* detector_item, const SphericalDetector& detector);

void setRectangularDetector(RectangularDetectorItem* detector_item,
                            const RectangularDetector& detector);

void setDetectorMasks(DetectorItem* detector_item, const Simulation& simulation);

void setMaskContainer(MaskContainerItem* container_item, const IDetector& detector, double scale);

void setItemFromSample(BeamDistributionItem* beam_distribution_item,
                       const ParameterDistribution& parameter_distribution);

void setBackground(InstrumentItem* instrument_item, const Simulation& simulation);

void setFootprintFactor(const IFootprintFactor* footprint, SpecularBeamItem* beam_item);

void setAxisItem(SessionItem* item, const IAxis& axis, double factor = 1.0);

} // namespace TransformFromDomain

#endif // BORNAGAIN_GUI_COREGUI_MODELS_TRANSFORMFROMDOMAIN_H
