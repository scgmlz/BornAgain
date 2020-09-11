// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformFromDomain.cpp
//! @brief     Implements namespace TransformFromDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/TransformFromDomain.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Beam/FootprintGauss.h"
#include "Core/Beam/FootprintSquare.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Correlations/FTDistributions1D.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "Core/Detector/ConvolutionDetectorResolution.h"
#include "Core/Detector/RectangularDetector.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/Detector/ResolutionFunction2DGaussian.h"
#include "Core/Detector/ScanResolution.h"
#include "Core/Detector/SphericalDetector.h"
#include "Core/Export/INodeUtils.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Mask/Ellipse.h"
#include "Core/Mask/InfinitePlane.h"
#include "Core/Mask/Line.h"
#include "Core/Mask/Polygon.h"
#include "Core/Mask/Rectangle.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPattern.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/includeIncludes/InterferenceFunctions.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BackgroundItems.h"
#include "GUI/coregui/Models/BeamAngleItems.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/FTDecayFunctionItems.h"
#include "GUI/coregui/Models/FTDistributionItems.h"
#include "GUI/coregui/Models/FootprintItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/LayerRoughnessItems.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "GUI/coregui/Models/ResolutionFunctionItems.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/SphericalDetectorItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

using namespace INodeUtils;
using SessionItemUtils::SetVectorItem;

namespace
{
void SetPDF1D(SessionItem* item, const IFTDistribution1D* pdf, QString group_name);
void setPDF2D(SessionItem* item, const IFTDistribution2D* pdf, QString group_name);
void SetDecayFunction1D(SessionItem* item, const IFTDecayFunction1D* pdf, QString group_name);
void SetDecayFunction2D(SessionItem* item, const IFTDecayFunction2D* pdf, QString group_name);

void set2DLatticeParameters(SessionItem* item, const Lattice2D& lattice);
void setPositionVariance(SessionItem* item, const IInterferenceFunction& iff);

void setDistribution(SessionItem* item, ParameterDistribution par_distr, QString group_name,
                     double factor = 1.0);

void addDistributionToBeamItem(const std::string& parameter_name, const QString& item_name,
                               const ParameterDistribution& distribution,
                               const BeamItem* beam_item);

void addRangedDistributionToItem(SessionItem* item, const RangedDistribution& ranged, double mean,
                                 double std_dev);
} // namespace

void TransformFromDomain::set1DLatticeItem(SessionItem* item,
                                           const InterferenceFunction1DLattice& sample)
{
    item->setItemValue(InterferenceFunction1DLatticeItem::P_LENGTH, sample.getLength());
    item->setItemValue(InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE,
                       Units::rad2deg(sample.getXi()));

    auto pdf = OnlyChildOfType<IFTDecayFunction1D>(sample);
    QString group_name = InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION;
    SetDecayFunction1D(item, pdf, group_name);
    setPositionVariance(item, sample);
}

void TransformFromDomain::set2DLatticeItem(SessionItem* item,
                                           const InterferenceFunction2DLattice& sample)
{
    set2DLatticeParameters(item, sample.lattice());

    item->setItemValue(InterferenceFunction2DLatticeItem::P_XI_INTEGRATION,
                       sample.integrationOverXi());

    auto p_pdf = OnlyChildOfType<IFTDecayFunction2D>(sample);
    QString group_name = InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION;
    SetDecayFunction2D(item, p_pdf, group_name);
    setPositionVariance(item, sample);
}

void TransformFromDomain::set2DParaCrystalItem(SessionItem* item,
                                               const InterferenceFunction2DParaCrystal& sample)
{
    set2DLatticeParameters(item, sample.lattice());

    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH,
                       sample.dampingLength());
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1,
                       sample.domainSizes()[0]);
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2,
                       sample.domainSizes()[1]);
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION,
                       sample.integrationOverXi());

    auto pdfs = ChildNodesOfType<IFTDistribution2D>(sample);
    QStringList group_names;
    group_names << InterferenceFunction2DParaCrystalItem::P_PDF1
                << InterferenceFunction2DParaCrystalItem::P_PDF2;
    for (unsigned i = 0; i < pdfs.size(); ++i)
        setPDF2D(item, pdfs[i], group_names[i]);
    setPositionVariance(item, sample);
}

void TransformFromDomain::setFinite2DLatticeItem(SessionItem* item,
                                                 const InterferenceFunctionFinite2DLattice& sample)
{
    set2DLatticeParameters(item, sample.lattice());

    item->setItemValue(InterferenceFunctionFinite2DLatticeItem::P_DOMAIN_SIZE_1,
                       sample.numberUnitCells1());
    item->setItemValue(InterferenceFunctionFinite2DLatticeItem::P_DOMAIN_SIZE_2,
                       sample.numberUnitCells2());
    item->setItemValue(InterferenceFunctionFinite2DLatticeItem::P_POSITION_VARIANCE,
                       sample.positionVariance());
    item->setItemValue(InterferenceFunctionFinite2DLatticeItem::P_XI_INTEGRATION,
                       sample.integrationOverXi());
    setPositionVariance(item, sample);
}

void TransformFromDomain::setHardDiskItem(SessionItem* item,
                                          const InterferenceFunctionHardDisk& sample)
{
    item->setItemValue(InterferenceFunctionHardDiskItem::P_RADIUS, sample.radius());
    item->setItemValue(InterferenceFunctionHardDiskItem::P_DENSITY, sample.density());
    setPositionVariance(item, sample);
}

void TransformFromDomain::setRadialParaCrystalItem(
    SessionItem* item, const InterferenceFunctionRadialParaCrystal& sample)
{
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE,
                       sample.peakDistance());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH,
                       sample.dampingLength());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE,
                       sample.domainSize());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_KAPPA, sample.kappa());

    auto ipdf = OnlyChildOfType<IFTDistribution1D>(sample);
    QString group_name = InterferenceFunctionRadialParaCrystalItem::P_PDF;
    SetPDF1D(item, ipdf, group_name);
    setPositionVariance(item, sample);
}

void TransformFromDomain::setLayerItem(SessionItem* layerItem, const Layer* layer,
                                       const LayerInterface* top_interface)
{
    layerItem->setItemValue(LayerItem::P_THICKNESS, layer->thickness());
    layerItem->setGroupProperty(LayerItem::P_ROUGHNESS, "LayerZeroRoughness");
    layerItem->setItemValue(LayerItem::P_NSLICES, (int)layer->numberOfSlices());

    if (top_interface) {
        const LayerRoughness* roughness = top_interface->getRoughness();
        if (TransformFromDomain::isValidRoughness(roughness)) {
            SessionItem* roughnessItem =
                layerItem->setGroupProperty(LayerItem::P_ROUGHNESS, "LayerBasicRoughness");
            TransformFromDomain::setRoughnessItem(roughnessItem, *roughness);
        }
    }
}

void TransformFromDomain::setRoughnessItem(SessionItem* item, const LayerRoughness& sample)
{
    item->setItemValue(LayerBasicRoughnessItem::P_SIGMA, sample.getSigma());
    item->setItemValue(LayerBasicRoughnessItem::P_HURST, sample.getHurstParameter());
    item->setItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH,
                       sample.getLatteralCorrLength());
}

//! Initialization of ParticleDistributionItem
void TransformFromDomain::setParticleDistributionItem(SessionItem* item,
                                                      const ParticleDistribution& sample)
{
    ParticleDistributionItem* distItem = dynamic_cast<ParticleDistributionItem*>(item);
    ASSERT(distItem);

    distItem->setItemValue(ParticleItem::P_ABUNDANCE, sample.abundance());

    ParameterDistribution par_distr = sample.parameterDistribution();
    QString main_distr_par_name = QString::fromStdString(par_distr.getMainParameterName());
    QStringList linked_pars = GUIHelpers::fromStdStrings(par_distr.getLinkedParameterNames());

    distItem->setDomainCacheNames(main_distr_par_name, linked_pars);

    double unit_factor(1.0);
    if (sample.mainUnits() == "rad")
        unit_factor = 1. / Units::degree;

    QString group_name = ParticleDistributionItem::P_DISTRIBUTION;
    setDistribution(distItem, par_distr, group_name, unit_factor);
}

//! Returns true if given roughness is non-zero roughness
bool TransformFromDomain::isValidRoughness(const LayerRoughness* roughness)
{
    if (!roughness)
        return false;
    if (roughness->getSigma() == 0 && roughness->getHurstParameter() == 0.0
        && roughness->getLatteralCorrLength() == 0.0)
        return false;
    return true;
}

void TransformFromDomain::setGISASBeamItem(BeamItem* beam_item, const GISASSimulation& simulation)
{
    ASSERT(beam_item);
    Beam beam = simulation.getInstrument().getBeam();

    beam_item->setIntensity(beam.getIntensity());
    beam_item->setWavelength(beam.getWavelength());
    beam_item->setInclinationAngle(Units::rad2deg(beam.getAlpha()));
    beam_item->setAzimuthalAngle(Units::rad2deg(beam.getPhi()));

    // distribution parameters
    const DistributionHandler::Distributions_t distributions =
        simulation.getDistributionHandler().getDistributions();
    for (size_t i = 0; i < distributions.size(); ++i) {
        addDistributionToBeamItem("Wavelength", BeamItem::P_WAVELENGTH, distributions[i],
                                  beam_item);
        addDistributionToBeamItem("InclinationAngle", BeamItem::P_INCLINATION_ANGLE,
                                  distributions[i], beam_item);
        addDistributionToBeamItem("AzimuthalAngle", BeamItem::P_AZIMUTHAL_ANGLE, distributions[i],
                                  beam_item);
    }

    // polarization parameters
    SetVectorItem(*beam_item, BeamItem::P_POLARIZATION, beam.getBlochVector());
}

void TransformFromDomain::setOffSpecBeamItem(BeamItem* beam_item,
                                             const OffSpecSimulation& simulation)
{
    Beam beam = simulation.getInstrument().getBeam();

    beam_item->setIntensity(beam.getIntensity());
    beam_item->setWavelength(beam.getWavelength());
    beam_item->setInclinationAngle(Units::rad2deg(beam.getAlpha()));
    beam_item->setAzimuthalAngle(Units::rad2deg(beam.getPhi()));
    // TODO implement beam divergence
}

void TransformFromDomain::setSpecularBeamItem(SpecularBeamItem* beam_item,
                                              const SpecularSimulation& simulation)
{
    const Beam& beam = simulation.getInstrument().getBeam();

    beam_item->setIntensity(beam.getIntensity());
    beam_item->setWavelength(beam.getWavelength());
    beam_item->setInclinationAngle(0.0); // inclination angle is hardcoded
    beam_item->setAzimuthalAngle(0.0);   // azimuthal angle is hardcoded

    auto axis_item = beam_item->currentInclinationAxisItem();
    TransformFromDomain::setAxisItem(axis_item, *simulation.coordinateAxis(), 1. / Units::deg);

    setFootprintFactor(simulation.footprintFactor(), beam_item);

    const AngularSpecScan* scan = dynamic_cast<const AngularSpecScan*>(simulation.dataHandler());
    if (!scan)
        return;

    auto resolution = scan->wavelengthResolution();
    if (!resolution->empty()) {
        double mean = scan->wavelength();
        double std_dev = resolution->stdDevs(mean, 1).front();
        addRangedDistributionToItem(beam_item->getItem(SpecularBeamItem::P_WAVELENGTH),
                                    *resolution->distribution(), mean, std_dev);
    }

    resolution = scan->angleResolution();
    if (resolution && !resolution->empty()) {
        double std_dev = resolution->stdDevs(0.0, 1).front();
        addRangedDistributionToItem(beam_item->getItem(SpecularBeamItem::P_INCLINATION_ANGLE),
                                    *resolution->distribution(), 0.0, std_dev);
    }
}

void TransformFromDomain::setDetector(Instrument2DItem* instrument_item,
                                      const Simulation2D& simulation)
{
    const IDetector* p_detector = simulation.getInstrument().getDetector();
    setDetectorGeometry(instrument_item, *p_detector);

    auto detector_item = instrument_item->detectorItem();

    setDetectorResolution(detector_item, *p_detector);
    setDetectorProperties(detector_item, *p_detector);
    setDetectorMasks(detector_item, simulation);
}

void TransformFromDomain::setDetectorGeometry(Instrument2DItem* instrument_item,
                                              const IDetector& detector)
{
    if (auto det = dynamic_cast<const SphericalDetector*>(&detector)) {
        instrument_item->setDetectorGroup("SphericalDetector");
        auto item = dynamic_cast<SphericalDetectorItem*>(instrument_item->detectorItem());
        setSphericalDetector(item, *det);
    } else if (auto det = dynamic_cast<const RectangularDetector*>(&detector)) {
        instrument_item->setDetectorGroup("RectangularDetector");
        auto item = dynamic_cast<RectangularDetectorItem*>(instrument_item->detectorItem());
        setRectangularDetector(item, *det);
    } else {
        throw GUIHelpers::Error(
            "TransformFromDomain::setDetectorGeometry() -> Unknown detector type.");
    }
}

void TransformFromDomain::setDetectorResolution(DetectorItem* detector_item,
                                                const IDetector& detector)
{
    const IDetectorResolution* p_resfunc = detector.detectorResolution();

    if (!p_resfunc)
        return;

    if (auto p_convfunc = dynamic_cast<const ConvolutionDetectorResolution*>(p_resfunc)) {
        if (auto resfunc = dynamic_cast<const ResolutionFunction2DGaussian*>(
                p_convfunc->getResolutionFunction2D())) {
            SessionItem* item = detector_item->setGroupProperty(DetectorItem::P_RESOLUTION_FUNCTION,
                                                                "ResolutionFunction2DGaussian");
            double scale(1.0);
            if (detector_item->modelType() == "SphericalDetector")
                scale = 1. / Units::degree;
            item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_X,
                               scale * resfunc->getSigmaX());
            item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_Y,
                               scale * resfunc->getSigmaY());
        } else {
            throw GUIHelpers::Error("TransformFromDomain::setDetectorResolution() -> Error. "
                                    "Unknown detector resolution function");
        }
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setDetectorResolution() -> Error. "
                                "Not a ConvolutionDetectorResolution function");
    }
}

void TransformFromDomain::setDetectorProperties(DetectorItem* detector_item,
                                                const IDetector& detector)
{
    double total_transmission = detector.detectionProperties().analyzerTotalTransmission();
    if (total_transmission <= 0.0)
        return;

    kvector_t analyzer_dir = detector.detectionProperties().analyzerDirection();
    double efficiency = detector.detectionProperties().analyzerEfficiency();
    SetVectorItem(*detector_item, DetectorItem::P_ANALYZER_DIRECTION, analyzer_dir);
    detector_item->setItemValue(DetectorItem::P_ANALYZER_EFFICIENCY, efficiency);
    detector_item->setItemValue(DetectorItem::P_ANALYZER_TOTAL_TRANSMISSION, total_transmission);
}

void TransformFromDomain::setSphericalDetector(SphericalDetectorItem* detector_item,
                                               const SphericalDetector& detector)
{
    // Axes
    const IAxis& phi_axis = detector.getAxis(0);
    const IAxis& alpha_axis = detector.getAxis(1);

    BasicAxisItem* phiAxisItem =
        dynamic_cast<BasicAxisItem*>(detector_item->getItem(SphericalDetectorItem::P_PHI_AXIS));
    ASSERT(phiAxisItem);
    phiAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)phi_axis.size());
    phiAxisItem->setItemValue(BasicAxisItem::P_MIN_DEG, Units::rad2deg(phi_axis.getMin()));
    phiAxisItem->setItemValue(BasicAxisItem::P_MAX_DEG, Units::rad2deg(phi_axis.getMax()));

    BasicAxisItem* alphaAxisItem =
        dynamic_cast<BasicAxisItem*>(detector_item->getItem(SphericalDetectorItem::P_ALPHA_AXIS));
    ASSERT(alphaAxisItem);
    alphaAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)alpha_axis.size());
    alphaAxisItem->setItemValue(BasicAxisItem::P_MIN_DEG, Units::rad2deg(alpha_axis.getMin()));
    alphaAxisItem->setItemValue(BasicAxisItem::P_MAX_DEG, Units::rad2deg(alpha_axis.getMax()));
}

void TransformFromDomain::setRectangularDetector(RectangularDetectorItem* detector_item,
                                                 const RectangularDetector& detector)
{
    // Axes
    BasicAxisItem* xAxisItem =
        dynamic_cast<BasicAxisItem*>(detector_item->getItem(RectangularDetectorItem::P_X_AXIS));
    ASSERT(xAxisItem);
    xAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)detector.getNbinsX());
    xAxisItem->setItemValue(BasicAxisItem::P_MAX_DEG, detector.getWidth());

    BasicAxisItem* yAxisItem =
        dynamic_cast<BasicAxisItem*>(detector_item->getItem(RectangularDetectorItem::P_Y_AXIS));
    ASSERT(yAxisItem);
    yAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)detector.getNbinsY());
    yAxisItem->setItemValue(BasicAxisItem::P_MAX_DEG, detector.getHeight());

    if (detector.getDetectorArrangment() == RectangularDetector::GENERIC) {
        detector_item->setDetectorAlignment("Generic");

        kvector_t normal = detector.getNormalVector();
        SetVectorItem(*detector_item, RectangularDetectorItem::P_NORMAL, normal);

        kvector_t direction = detector.getDirectionVector();
        SetVectorItem(*detector_item, RectangularDetectorItem::P_DIRECTION, direction);

        detector_item->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detector_item->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());
    }

    else if (detector.getDetectorArrangment() == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
        detector_item->setDetectorAlignment("Perpendicular to sample x-axis");
        detector_item->setItemValue(RectangularDetectorItem::P_DISTANCE, detector.getDistance());
        detector_item->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detector_item->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
        detector_item->setDetectorAlignment("Perpendicular to direct beam");
        detector_item->setItemValue(RectangularDetectorItem::P_DISTANCE, detector.getDistance());
        detector_item->setItemValue(RectangularDetectorItem::P_DBEAM_U0, detector.getU0());
        detector_item->setItemValue(RectangularDetectorItem::P_DBEAM_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
        detector_item->setDetectorAlignment("Perpendicular to reflected beam");
        detector_item->setItemValue(RectangularDetectorItem::P_DISTANCE, detector.getDistance());
        detector_item->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detector_item->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        detector_item->setDetectorAlignment("Perpendicular to reflected beam (dpos)");
        detector_item->setItemValue(RectangularDetectorItem::P_DISTANCE, detector.getDistance());
        detector_item->setItemValue(RectangularDetectorItem::P_DBEAM_U0,
                                    detector.getDirectBeamU0());
        detector_item->setItemValue(RectangularDetectorItem::P_DBEAM_V0,
                                    detector.getDirectBeamV0());

    } else {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(RectangularDetectorItem* detectorItem "
            "Error. Unknown detector arrangement");
    }
}

void TransformFromDomain::setDetectorMasks(DetectorItem* detector_item,
                                           const Simulation& simulation)
{
    const IDetector* detector = simulation.getInstrument().getDetector();
    if ((detector->detectorMask() && detector->detectorMask()->numberOfMasks())
        || detector->regionOfInterest()) {
        detector_item->createMaskContainer();

        double scale(1.0);
        if (detector_item->modelType() == "SphericalDetector")
            scale = 1. / Units::degree;

        setMaskContainer(detector_item->maskContainerItem(), *detector, scale);
    }
}

void TransformFromDomain::setMaskContainer(MaskContainerItem* container_item,
                                           const IDetector& detector, double scale)
{
    auto detectorMask = detector.detectorMask();
    for (size_t i_mask = 0; i_mask < detectorMask->numberOfMasks(); ++i_mask) {
        bool mask_value(false);
        const IShape2D* shape = detectorMask->getMaskShape(i_mask, mask_value);

        if (const Ellipse* ellipse = dynamic_cast<const Ellipse*>(shape)) {
            EllipseItem* ellipseItem = new EllipseItem();
            ellipseItem->setItemValue(EllipseItem::P_XCENTER, scale * ellipse->getCenterX());
            ellipseItem->setItemValue(EllipseItem::P_YCENTER, scale * ellipse->getCenterY());
            ellipseItem->setItemValue(EllipseItem::P_XRADIUS, scale * ellipse->getRadiusX());
            ellipseItem->setItemValue(EllipseItem::P_YRADIUS, scale * ellipse->getRadiusY());
            ellipseItem->setItemValue(EllipseItem::P_ANGLE, scale * ellipse->getTheta());
            ellipseItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            container_item->insertItem(0, ellipseItem);
        }

        else if (const Rectangle* rectangle = dynamic_cast<const Rectangle*>(shape)) {
            RectangleItem* rectangleItem = new RectangleItem();
            rectangleItem->setItemValue(RectangleItem::P_XLOW, scale * rectangle->getXlow());
            rectangleItem->setItemValue(RectangleItem::P_YLOW, scale * rectangle->getYlow());
            rectangleItem->setItemValue(RectangleItem::P_XUP, scale * rectangle->getXup());
            rectangleItem->setItemValue(RectangleItem::P_YUP, scale * rectangle->getYup());
            rectangleItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            container_item->insertItem(0, rectangleItem);

        }

        else if (const Polygon* polygon = dynamic_cast<const Polygon*>(shape)) {
            PolygonItem* polygonItem = new PolygonItem();
            std::vector<double> xpos, ypos;
            polygon->getPoints(xpos, ypos);
            for (size_t i_point = 0; i_point < xpos.size(); ++i_point) {
                PolygonPointItem* pointItem = new PolygonPointItem();
                pointItem->setItemValue(PolygonPointItem::P_POSX, scale * xpos[i_point]);
                pointItem->setItemValue(PolygonPointItem::P_POSY, scale * ypos[i_point]);
                polygonItem->insertItem(-1, pointItem);
            }

            polygonItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            polygonItem->setItemValue(PolygonItem::P_ISCLOSED, true);

            container_item->insertItem(0, polygonItem);
        }

        else if (const VerticalLine* vline = dynamic_cast<const VerticalLine*>(shape)) {
            VerticalLineItem* lineItem = new VerticalLineItem();
            lineItem->setItemValue(VerticalLineItem::P_POSX, scale * vline->getXpos());
            lineItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            container_item->insertItem(0, lineItem);
        }

        else if (const HorizontalLine* hline = dynamic_cast<const HorizontalLine*>(shape)) {
            HorizontalLineItem* lineItem = new HorizontalLineItem();
            lineItem->setItemValue(HorizontalLineItem::P_POSY, scale * hline->getYpos());
            lineItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            container_item->insertItem(0, lineItem);
        }

        else if (const InfinitePlane* plane = dynamic_cast<const InfinitePlane*>(shape)) {
            Q_UNUSED(plane);
            MaskAllItem* planeItem = new MaskAllItem();
            planeItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            container_item->insertItem(-1, planeItem);
        }

        else {
            throw GUIHelpers::Error("TransformFromDomain::setDetectorMasks() -> Error. "
                                    "Unknown shape");
        }
    }

    if (detector.regionOfInterest()) {
        RegionOfInterestItem* roiItem = new RegionOfInterestItem();
        roiItem->setItemValue(RectangleItem::P_XLOW,
                              scale * detector.regionOfInterest()->getXlow());
        roiItem->setItemValue(RectangleItem::P_YLOW,
                              scale * detector.regionOfInterest()->getYlow());
        roiItem->setItemValue(RectangleItem::P_XUP, scale * detector.regionOfInterest()->getXup());
        roiItem->setItemValue(RectangleItem::P_YUP, scale * detector.regionOfInterest()->getYup());
        container_item->insertItem(-1, roiItem);
    }
}

void TransformFromDomain::setItemFromSample(BeamDistributionItem* beam_distribution_item,
                                            const ParameterDistribution& parameter_distribution)
{
    ASSERT(beam_distribution_item);

    if (parameter_distribution.getMinValue() < parameter_distribution.getMaxValue()) {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(BeamDistributionItem* beamDistributionItem,"
            "const ParameterDistribution& parameterDistribution) -> Error. ParameterDistribution "
            "with defined min,max are not yet implemented in GUI");
    }

    const double unit_factor = 1.0 / beam_distribution_item->scaleFactor();
    QString group_name = BeamDistributionItem::P_DISTRIBUTION;
    setDistribution(beam_distribution_item, parameter_distribution, group_name, unit_factor);
}

void TransformFromDomain::setBackground(InstrumentItem* instrument_item,
                                        const Simulation& simulation)
{
    auto p_bg = simulation.background();
    if (auto p_constant_bg = dynamic_cast<const ConstantBackground*>(p_bg)) {
        auto constant_bg_item =
            instrument_item->setGroupProperty(InstrumentItem::P_BACKGROUND, "ConstantBackground");
        double value = p_constant_bg->backgroundValue();
        constant_bg_item->setItemValue(ConstantBackgroundItem::P_VALUE, value);
    } else if (dynamic_cast<const PoissonNoiseBackground*>(p_bg)) {
        instrument_item->setGroupProperty(InstrumentItem::P_BACKGROUND, "PoissonNoiseBackground");
    }
}

void TransformFromDomain::setFootprintFactor(const IFootprintFactor* footprint,
                                             SpecularBeamItem* beam_item)
{
    if (!footprint)
        return;
    if (const auto gaussian_fp = dynamic_cast<const FootprintGauss*>(footprint)) {
        auto gaussian_fp_item =
            beam_item->setGroupProperty(SpecularBeamItem::P_FOOPTPRINT, "GaussianFootrpint");
        const double value = gaussian_fp->widthRatio();
        gaussian_fp_item->setItemValue(FootprintGaussianItem::P_VALUE, value);
    } else if (const auto square_fp = dynamic_cast<const FootprintSquare*>(footprint)) {
        auto square_fp_item =
            beam_item->setGroupProperty(SpecularBeamItem::P_FOOPTPRINT, "SquareFootprint");
        const double value = square_fp->widthRatio();
        square_fp_item->setItemValue(FootprintSquareItem::P_VALUE, value);
    }
}

void TransformFromDomain::setAxisItem(SessionItem* item, const IAxis& axis, double factor)
{
    if (item->modelType() != "BasicAxis")
        throw GUIHelpers::Error("TransformFromDomain::setAxisItem() -> Error. Unexpected item.");

    if (!dynamic_cast<const FixedBinAxis*>(&axis))
        throw GUIHelpers::Error("TransformFromDomain::setAxisItem() -> Error. Unexpected axis");

    item->setItemValue(BasicAxisItem::P_NBINS, static_cast<int>(axis.size()));
    item->setItemValue(BasicAxisItem::P_MIN_DEG, factor * axis.getMin());
    item->setItemValue(BasicAxisItem::P_MAX_DEG, factor * axis.getMax());
    item->setItemValue(BasicAxisItem::P_TITLE, QString::fromStdString(axis.getName()));
}

namespace
{
void SetPDF1D(SessionItem* item, const IFTDistribution1D* ipdf, QString group_name)
{
    if (const FTDistribution1DCauchy* pdf = dynamic_cast<const FTDistribution1DCauchy*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution1DCauchy");
        pdfItem->setItemValue(FTDistribution1DCauchyItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DGauss* pdf =
                   dynamic_cast<const FTDistribution1DGauss*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution1DGauss");
        pdfItem->setItemValue(FTDistribution1DGaussItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DGate* pdf = dynamic_cast<const FTDistribution1DGate*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution1DGate");
        pdfItem->setItemValue(FTDistribution1DGateItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DTriangle* pdf =
                   dynamic_cast<const FTDistribution1DTriangle*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution1DTriangle");
        pdfItem->setItemValue(FTDistribution1DTriangleItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DCosine* pdf =
                   dynamic_cast<const FTDistribution1DCosine*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution1DCosine");
        pdfItem->setItemValue(FTDistribution1DCosineItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DVoigt* pdf =
                   dynamic_cast<const FTDistribution1DVoigt*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution1DVoigt");
        pdfItem->setItemValue(FTDistribution1DVoigtItem::P_OMEGA, pdf->omega());
        pdfItem->setItemValue(FTDistribution1DVoigtItem::P_ETA, pdf->eta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setPDF1D: -> Error");
    }
}

void setPDF2D(SessionItem* item, const IFTDistribution2D* pdf, QString group_name)
{
    if (const FTDistribution2DCauchy* pdf_cauchy =
            dynamic_cast<const FTDistribution2DCauchy*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution2DCauchy");
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_OMEGA_X, pdf_cauchy->omegaX());
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_OMEGA_Y, pdf_cauchy->omegaY());
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_GAMMA,
                              Units::rad2deg(pdf_cauchy->gamma()));
    } else if (const FTDistribution2DGauss* pdf_gauss =
                   dynamic_cast<const FTDistribution2DGauss*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution2DGauss");
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_OMEGA_X, pdf_gauss->omegaX());
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_OMEGA_Y, pdf_gauss->omegaY());
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_GAMMA,
                              Units::rad2deg(pdf_gauss->gamma()));
    } else if (const FTDistribution2DGate* pdf_gate =
                   dynamic_cast<const FTDistribution2DGate*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution2DGate");
        pdfItem->setItemValue(FTDistribution2DGateItem::P_OMEGA_X, pdf_gate->omegaX());
        pdfItem->setItemValue(FTDistribution2DGateItem::P_OMEGA_Y, pdf_gate->omegaY());
        pdfItem->setItemValue(FTDistribution2DGateItem::P_GAMMA, Units::rad2deg(pdf_gate->gamma()));
    } else if (const FTDistribution2DCone* pdf_cone =
                   dynamic_cast<const FTDistribution2DCone*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution2DCone");
        pdfItem->setItemValue(FTDistribution2DConeItem::P_OMEGA_X, pdf_cone->omegaX());
        pdfItem->setItemValue(FTDistribution2DConeItem::P_OMEGA_Y, pdf_cone->omegaY());
        pdfItem->setItemValue(FTDistribution2DConeItem::P_GAMMA, Units::rad2deg(pdf_cone->gamma()));
    } else if (const FTDistribution2DVoigt* pdf_voigt =
                   dynamic_cast<const FTDistribution2DVoigt*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDistribution2DVoigt");
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_OMEGA_X, pdf_voigt->omegaX());
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_OMEGA_Y, pdf_voigt->omegaY());
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_GAMMA,
                              Units::rad2deg(pdf_voigt->gamma()));
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_ETA, pdf_voigt->eta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setPDF2D: -> Error");
    }
}

void SetDecayFunction1D(SessionItem* item, const IFTDecayFunction1D* ipdf, QString group_name)
{
    if (const FTDecayFunction1DCauchy* pdf = dynamic_cast<const FTDecayFunction1DCauchy*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDecayFunction1DCauchy");
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->decayLength());
    } else if (const FTDecayFunction1DGauss* pdf =
                   dynamic_cast<const FTDecayFunction1DGauss*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDecayFunction1DGauss");
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->decayLength());
    } else if (const FTDecayFunction1DTriangle* pdf =
                   dynamic_cast<const FTDecayFunction1DTriangle*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDecayFunction1DTriangle");
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->decayLength());
    } else if (const FTDecayFunction1DVoigt* pdf =
                   dynamic_cast<const FTDecayFunction1DVoigt*>(ipdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDecayFunction1DVoigt");
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->decayLength());
        pdfItem->setItemValue(FTDecayFunction1DVoigtItem::P_ETA, pdf->eEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::SetDecayFunction1D: -> Error");
    }
}

void SetDecayFunction2D(SessionItem* item, const IFTDecayFunction2D* pdf, QString group_name)
{
    if (const FTDecayFunction2DCauchy* pdf_cauchy =
            dynamic_cast<const FTDecayFunction2DCauchy*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDecayFunction2DCauchy");
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X, pdf_cauchy->decayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y, pdf_cauchy->decayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA, Units::rad2deg(pdf_cauchy->gamma()));
    } else if (const FTDecayFunction2DGauss* pdf_gauss =
                   dynamic_cast<const FTDecayFunction2DGauss*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDecayFunction2DGauss");
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X, pdf_gauss->decayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y, pdf_gauss->decayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA, Units::rad2deg(pdf_gauss->gamma()));
    } else if (const FTDecayFunction2DVoigt* pdf_voigt =
                   dynamic_cast<const FTDecayFunction2DVoigt*>(pdf)) {
        SessionItem* pdfItem = item->setGroupProperty(group_name, "FTDecayFunction2DVoigt");
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X, pdf_voigt->decayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y, pdf_voigt->decayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA, Units::rad2deg(pdf_voigt->gamma()));
        pdfItem->setItemValue(FTDecayFunction2DVoigtItem::P_ETA, pdf_voigt->eta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::SetDecayFunction2D: -> Error");
    }
}

void set2DLatticeParameters(SessionItem* item, const Lattice2D& lattice)
{
    SessionItem* latticeItem(nullptr);
    if (lattice.getName() == "SquareLattice") {
        latticeItem = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                             "SquareLattice");
        latticeItem->setItemValue(SquareLatticeItem::P_LATTICE_LENGTH, lattice.length1());

    } else if (lattice.getName() == "HexagonalLattice") {
        latticeItem = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                             "HexagonalLattice");
        latticeItem->setItemValue(HexagonalLatticeItem::P_LATTICE_LENGTH, lattice.length1());

    } else {
        latticeItem = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                             "BasicLattice");
        latticeItem->setItemValue(BasicLatticeItem::P_LATTICE_LENGTH1, lattice.length1());
        latticeItem->setItemValue(BasicLatticeItem::P_LATTICE_LENGTH2, lattice.length2());
        latticeItem->setItemValue(BasicLatticeItem::P_LATTICE_ANGLE,
                                  Units::rad2deg(lattice.latticeAngle()));
    }
    latticeItem->setItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE,
                              Units::rad2deg(lattice.rotationAngle()));
}

void setPositionVariance(SessionItem* item, const IInterferenceFunction& iff)
{
    double pos_var = iff.positionVariance();
    item->setItemValue(InterferenceFunctionItem::P_POSITION_VARIANCE, pos_var);
}

void setDistribution(SessionItem* part_distr_item, ParameterDistribution par_distr,
                     QString group_name, double factor)
{
    const IDistribution1D* p_distribution = par_distr.getDistribution();

    SessionItem* item = 0;
    if (const DistributionGate* distr = dynamic_cast<const DistributionGate*>(p_distribution)) {
        item = part_distr_item->setGroupProperty(group_name, "DistributionGate");
        item->setItemValue(DistributionGateItem::P_MIN, factor * distr->getMin());
        item->setItemValue(DistributionGateItem::P_MAX, factor * distr->getMax());
    } else if (const DistributionLorentz* distr =
                   dynamic_cast<const DistributionLorentz*>(p_distribution)) {
        item = part_distr_item->setGroupProperty(group_name, "DistributionLorentz");
        item->setItemValue(DistributionLorentzItem::P_MEAN, factor * distr->getMean());
        item->setItemValue(DistributionLorentzItem::P_HWHM, factor * distr->getHWHM());
    } else if (const DistributionGaussian* distr =
                   dynamic_cast<const DistributionGaussian*>(p_distribution)) {
        item = part_distr_item->setGroupProperty(group_name, "DistributionGaussian");
        item->setItemValue(DistributionGaussianItem::P_MEAN, factor * distr->getMean());
        item->setItemValue(DistributionGaussianItem::P_STD_DEV, factor * distr->getStdDev());
    } else if (const DistributionLogNormal* distr =
                   dynamic_cast<const DistributionLogNormal*>(p_distribution)) {
        item = part_distr_item->setGroupProperty(group_name, "DistributionLogNormal");
        item->setItemValue(DistributionLogNormalItem::P_MEDIAN, factor * distr->getMedian());
        item->setItemValue(DistributionLogNormalItem::P_SCALE_PAR, distr->getScalePar());
    } else if (const DistributionCosine* distr =
                   dynamic_cast<const DistributionCosine*>(p_distribution)) {
        item = part_distr_item->setGroupProperty(group_name, "DistributionCosine");
        item->setItemValue(DistributionCosineItem::P_MEAN, factor * distr->getMean());
        item->setItemValue(DistributionCosineItem::P_SIGMA, factor * distr->getSigma());
    } else if (const DistributionTrapezoid* distr =
                   dynamic_cast<const DistributionTrapezoid*>(p_distribution)) {
        item = part_distr_item->setGroupProperty(group_name, "DistributionTrapezoid");
        item->setItemValue(DistributionTrapezoidItem::P_CENTER, factor * distr->getMean());
        item->setItemValue(DistributionTrapezoidItem::P_LEFTWIDTH, factor * distr->getLeftWidth());
        item->setItemValue(DistributionTrapezoidItem::P_MIDDLEWIDTH,
                           factor * distr->getMiddleWidth());
        item->setItemValue(DistributionTrapezoidItem::P_RIGHTWIDTH,
                           factor * distr->getRightWidth());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setDistribution: -> unknown distribution");
    }

    DistributionItem* distItem = dynamic_cast<DistributionItem*>(item);
    ASSERT(distItem);

    distItem->setItemValue(DistributionItem::P_NUMBER_OF_SAMPLES, (int)par_distr.getNbrSamples());

    if (distItem->isTag(DistributionItem::P_SIGMA_FACTOR))
        distItem->setItemValue(DistributionItem::P_SIGMA_FACTOR, par_distr.getSigmaFactor());

    // TODO It's wrong if domain distribution made for angles.
    if (distItem->isTag(DistributionItem::P_LIMITS))
        distItem->init_limits_group(par_distr.getLimits(), factor);
}

void addDistributionToBeamItem(const std::string& parameter_name, const QString& item_name,
                               const ParameterDistribution& distribution, const BeamItem* beam_item)
{
    ParameterPattern pattern;
    pattern.beginsWith("*").add("Beam").add(parameter_name);
    if (distribution.getMainParameterName() != pattern.toStdString())
        return;

    const auto beam_parameter = dynamic_cast<BeamDistributionItem*>(beam_item->getItem(item_name));
    TransformFromDomain::setItemFromSample(beam_parameter, distribution);
}

void addRangedDistributionToItem(SessionItem* item, const RangedDistribution& ranged, double mean,
                                 double std_dev)
{
    auto distr_item = dynamic_cast<BeamDistributionItem*>(item);
    if (!distr_item)
        return;
    ParameterDistribution par_distr("", *ranged.distribution(mean, std_dev), ranged.nSamples(),
                                    ranged.sigmaFactor(), ranged.limits());
    TransformFromDomain::setItemFromSample(distr_item, par_distr);
}
} // unnamed namespace
