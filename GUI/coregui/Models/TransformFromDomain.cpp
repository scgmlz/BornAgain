// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformFromDomain.cpp
//! @brief     Implements namespace TransformFromDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TransformFromDomain.h"
#include "AxesItems.h"
#include "Beam.h"
#include "BeamAngleItems.h"
#include "BeamItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "ConvolutionDetectorResolution.h"
#include "DetectorItems.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "FTDecayFunctionItems.h"
#include "FTDistributionItems.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "InfinitePlane.h"
#include "InterferenceFunctionItems.h"
#include "InterferenceFunctions.h"
#include "LatticeTypeItems.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerItem.h"
#include "LayerRoughness.h"
#include "LayerRoughnessItems.h"
#include "Line.h"
#include "MaskItems.h"
#include "ModelPath.h"
#include "Numeric.h"
#include "ParameterPattern.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "RegionOfInterest.h"
#include "RectangularDetector.h"
#include "ResolutionFunctionItems.h"
#include "SphericalDetector.h"
#include "Units.h"
#include "VectorItem.h"
#include <QDebug>
#include <limits>

void SetPDF1D(SessionItem* item, const IFTDistribution1D* pdf, QString group_name);
void setPDF2D(SessionItem* item, const IFTDistribution2D* pdf, QString group_name);
void SetDecayFunction1D(SessionItem* item, const IFTDecayFunction1D* pdf, QString group_name);
void SetDecayFunction2D(SessionItem* item, const IFTDecayFunction2D* pdf, QString group_name);

void set2DLatticeParameters(SessionItem* item, Lattice2DParameters lattice_params,
                            SessionItem* lattice_item);
void setDistribution(SessionItem* item, ParameterDistribution par_distr,
                     QString group_name, double factor = 1.0);

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunctionRadialParaCrystal* sample)
{
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE,
                                sample->getPeakDistance());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH,
                                sample->getDampingLength());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE,
                                sample->getDomainSize());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_KAPPA,
                                sample->getKappa());

    const IFTDistribution1D* ipdf = sample->getProbabilityDistribution();
    QString group_name = InterferenceFunctionRadialParaCrystalItem::P_PDF;
    qDebug() << "    group_name" << group_name;
    SetPDF1D(item, ipdf, group_name);
}

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunction2DParaCrystal* sample)
{
    SessionItem* lattice_item(0);
    Lattice2DParameters lattice_params = sample->getLatticeParameters();
    set2DLatticeParameters(item, lattice_params, lattice_item);

    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH,
                                sample->getDampingLength());
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1,
                                sample->getDomainSizes()[0]);
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2,
                                sample->getDomainSizes()[1]);
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION,
                                sample->getIntegrationOverXi());

    std::vector<const IFTDistribution2D*> pdfs = sample->getProbabilityDistributions();
    QStringList group_names;
    group_names << InterferenceFunction2DParaCrystalItem::P_PDF1
                << InterferenceFunction2DParaCrystalItem::P_PDF2;
    for (size_t i = 0; i < pdfs.size(); ++i) {
        qDebug() << "    group_name" << group_names[i];
        setPDF2D(item, pdfs[i], group_names[i]);
    }
}

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunction1DLattice* sample)
{
    Lattice1DParameters lattice_params = sample->getLatticeParameters();
    item->setItemValue(InterferenceFunction1DLatticeItem::P_LENGTH,
                                lattice_params.m_length);
    item->setItemValue(InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE,
                                Units::rad2deg(lattice_params.m_xi));

    const IFTDecayFunction1D* pdf = sample->getDecayFunction();
    QString group_name = InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION;
    qDebug() << "    group_name" << group_name;
    SetDecayFunction1D(item, pdf, group_name);
}

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunction2DLattice* sample)
{
    SessionItem* lattice_item(0);
    Lattice2DParameters lattice_params = sample->getLatticeParameters();
    set2DLatticeParameters(item, lattice_params, lattice_item);

    const IFTDecayFunction2D* p_pdf = sample->getDecayFunction();
    QString group_name = InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION;
    qDebug() << "    group_name" << group_name;
    SetDecayFunction2D(item, p_pdf, group_name);
}

void TransformFromDomain::setItemFromSample(SessionItem* layerItem, const Layer* layer,
                                            const LayerInterface* top_interface)
{
    layerItem->setItemValue(LayerItem::P_THICKNESS, layer->getThickness());
    layerItem->setGroupProperty(LayerItem::P_ROUGHNESS, Constants::LayerZeroRoughnessType);

    if (top_interface) {
        const LayerRoughness* roughness = top_interface->getRoughness();
        if (TransformFromDomain::isValidRoughness(roughness)) {
            SessionItem* roughnessItem = layerItem->setGroupProperty(
                LayerItem::P_ROUGHNESS, Constants::LayerBasicRoughnessType);
            TransformFromDomain::setItemFromSample(roughnessItem, roughness);
        }
    }
}

void TransformFromDomain::setItemFromSample(SessionItem* item, const LayerRoughness* sample)
{
    item->setItemValue(LayerBasicRoughnessItem::P_SIGMA, sample->getSigma());
    item->setItemValue(LayerBasicRoughnessItem::P_HURST, sample->getHurstParameter());
    item->setItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH,
                                sample->getLatteralCorrLength());
}

//! Initialization of ParticleDistributionItem
void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const ParticleDistribution* sample)
{
    item->setItemValue(ParticleItem::P_ABUNDANCE, sample->getAbundance());

    ParameterDistribution par_distr = sample->getParameterDistribution();
    QString main_distr_par_name = QString::fromStdString(par_distr.getMainParameterName());
    ComboProperty combo_property
        = item->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
              .value<ComboProperty>();
    combo_property.setCachedValue(main_distr_par_name);
    combo_property.setCacheContainsGUIFlag(false);
    item->setItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER,
                                combo_property.getVariant());

    QString group_name = ParticleDistributionItem::P_DISTRIBUTION;
    setDistribution(item, par_distr, group_name);
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

bool TransformFromDomain::isSquareLattice(double length1, double length2, double angle)
{
    return length1 == length2 && Numeric::areAlmostEqual(angle, M_PI / 2.0);
}

bool TransformFromDomain::isHexagonalLattice(double length1, double length2, double angle)
{
    return length1 == length2 && Numeric::areAlmostEqual(angle, M_TWOPI / 3.0);
}

void TransformFromDomain::setItemFromSample(BeamItem* beamItem, const GISASSimulation& simulation)
{
    Q_ASSERT(beamItem);
    Beam beam = simulation.getInstrument().getBeam();

    beamItem->setIntensity(beam.getIntensity());
    beamItem->setWavelength(beam.getWavelength());
    beamItem->setInclinationAngle(Units::rad2deg(beam.getAlpha()));
    beamItem->setAzimuthalAngle(Units::rad2deg(beam.getPhi()));

    // distribution parameters
    const DistributionHandler::Distributions_t distributions
        = simulation.getDistributionHandler().getDistributions();
    for (size_t i = 0; i < distributions.size(); ++i) {
        ParameterPattern pattern_wavelength;
        pattern_wavelength.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
        ParameterPattern pattern_alpha;
        pattern_alpha.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
        ParameterPattern pattern_phi;
        pattern_phi.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Azimuth);
        std::string mainParameterName = distributions[i].getMainParameterName();
        if (mainParameterName == pattern_wavelength.toStdString()) {
            BeamDistributionItem* beamWavelength = dynamic_cast<BeamDistributionItem*>(
                beamItem->getItem(BeamItem::P_WAVELENGTH));
            setItemFromSample(beamWavelength, distributions[i]);
        } else if (mainParameterName == pattern_alpha.toStdString()) {
            BeamDistributionItem* inclinationAngle = dynamic_cast<BeamDistributionItem*>(
                beamItem->getItem(BeamItem::P_INCLINATION_ANGLE));
            setItemFromSample(inclinationAngle, distributions[i]);
        } else if (mainParameterName == pattern_phi.toStdString()) {
            BeamDistributionItem* azimuthalAngle = dynamic_cast<BeamDistributionItem*>(
                beamItem->getItem(BeamItem::P_AZIMUTHAL_ANGLE));
            setItemFromSample(azimuthalAngle, distributions[i]);
        }
    }
}

void TransformFromDomain::setItemFromSample(DetectorItem* detectorItem,
                                            const GISASSimulation& simulation)
{
    Q_ASSERT(detectorItem);
    const IDetector2D* iDetector = simulation.getInstrument().getDetector();
    if(auto detector = dynamic_cast<const SphericalDetector*>(iDetector)) {
        auto item = dynamic_cast<SphericalDetectorItem*>
                (detectorItem->setGroupProperty(DetectorItem::P_DETECTOR,
                                             Constants::SphericalDetectorType));
        Q_ASSERT(item);
        setItemFromSample(item,* detector);
    }

    else if(auto detector = dynamic_cast<const RectangularDetector*>(iDetector)) {
        auto item = dynamic_cast<RectangularDetectorItem*>
                (detectorItem->setGroupProperty(DetectorItem::P_DETECTOR,
                                             Constants::RectangularDetectorType));
        Q_ASSERT(item);
        setItemFromSample(item,* detector);
    }

    else {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(DetectorItem*) -> Unknown detector type.");
    }
}


void TransformFromDomain::setItemFromSample(SphericalDetectorItem* detectorItem,
                                            const SphericalDetector& detector)
{
    // Axes
    const IAxis& phi_axis = detector.getAxis(0);
    const IAxis& alpha_axis = detector.getAxis(1);

    BasicAxisItem* phiAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(SphericalDetectorItem::P_PHI_AXIS));
    Q_ASSERT(phiAxisItem);
    phiAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)phi_axis.size());
    phiAxisItem->setItemValue(BasicAxisItem::P_MIN, Units::rad2deg(phi_axis.getMin()));
    phiAxisItem->setItemValue(BasicAxisItem::P_MAX, Units::rad2deg(phi_axis.getMax()));

    BasicAxisItem* alphaAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(SphericalDetectorItem::P_ALPHA_AXIS));
    Q_ASSERT(alphaAxisItem);
    alphaAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)alpha_axis.size());
    alphaAxisItem->setItemValue(BasicAxisItem::P_MIN, Units::rad2deg(alpha_axis.getMin()));
    alphaAxisItem->setItemValue(BasicAxisItem::P_MAX, Units::rad2deg(alpha_axis.getMax()));

    // detector resolution
    if (const IDetectorResolution* p_resfunc = detector.getDetectorResolutionFunction()) {
        if (const ConvolutionDetectorResolution* p_convfunc
            = dynamic_cast<const ConvolutionDetectorResolution*>(p_resfunc)) {
            if (const ResolutionFunction2DGaussian* resfunc
                = dynamic_cast<const ResolutionFunction2DGaussian*>(
                    p_convfunc->getResolutionFunction2D())) {
                SessionItem* item
                    = detectorItem->setGroupProperty(SphericalDetectorItem::P_RESOLUTION_FUNCTION,
                                                     Constants::ResolutionFunction2DGaussianType);
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_X,
                                            Units::rad2deg(resfunc->getSigmaX()));
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_Y,
                                            Units::rad2deg(resfunc->getSigmaY()));
            } else {
                throw GUIHelpers::Error("TransformFromDomain::setItemFromSample("
                                        "SphericalDetectorItem* detectorItem, const GISASSimulation "
                                        "&simulation) -> Error, unknown detector resolution "
                                        "function");
            }
        } else {
            throw GUIHelpers::Error(
                "TransformFromDomain::setItemFromSample(SphericalDetectorItem "
                "*detectorItem, const GISASSimulation& simulation) -> Error, not a "
                "ConvolutionDetectorResolution function");
        }
    }
}


void TransformFromDomain::setItemFromSample(RectangularDetectorItem* detectorItem,
                                            const RectangularDetector& detector)
{
    // Axes
    BasicAxisItem* xAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(RectangularDetectorItem::P_X_AXIS));
    Q_ASSERT(xAxisItem);
    xAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)detector.getNbinsX());
    xAxisItem->setItemValue(BasicAxisItem::P_MAX, detector.getWidth());

    BasicAxisItem* yAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(RectangularDetectorItem::P_Y_AXIS));
    Q_ASSERT(yAxisItem);
    yAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)detector.getNbinsY());
    yAxisItem->setItemValue(BasicAxisItem::P_MAX, detector.getHeight());

    if(detector.getDetectorArrangment() == RectangularDetector::GENERIC) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_GENERIC);

        kvector_t normal = detector.getNormalVector();
        detectorItem->getItem(RectangularDetectorItem::P_NORMAL)->setItemValue(
            VectorItem::P_X, normal.x());
        detectorItem->getItem(RectangularDetectorItem::P_NORMAL)->setItemValue(
            VectorItem::P_Y, normal.y());
        detectorItem->getItem(RectangularDetectorItem::P_NORMAL)->setItemValue(
            VectorItem::P_Z, normal.z());

        kvector_t direction = detector.getDirectionVector();
        detectorItem->getItem(RectangularDetectorItem::P_DIRECTION)->setItemValue(
            VectorItem::P_X, direction.x());
        detectorItem->getItem(RectangularDetectorItem::P_DIRECTION)->setItemValue(
            VectorItem::P_Y, direction.y());
        detectorItem->getItem(RectangularDetectorItem::P_DIRECTION)->setItemValue(
            VectorItem::P_Z, direction.z());

        detectorItem->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());
    }

    else if (detector.getDetectorArrangment() == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_SAMPLE);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_DIRECT_BEAM);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_REFLECTED_BEAM);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_U0,
                                            detector.getDirectBeamU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_V0,
                                            detector.getDirectBeamV0());

    } else {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(RectangularDetectorItem* detectorItem "
            "Error. Unknown detector arrangement");
    }

    // detector resolution
    if (const IDetectorResolution* p_resfunc = detector.getDetectorResolutionFunction()) {
        if (const ConvolutionDetectorResolution* p_convfunc
            = dynamic_cast<const ConvolutionDetectorResolution*>(p_resfunc)) {
            if (const ResolutionFunction2DGaussian* resfunc
                = dynamic_cast<const ResolutionFunction2DGaussian*>(
                    p_convfunc->getResolutionFunction2D())) {
                SessionItem* item
                    = detectorItem->setGroupProperty(RectangularDetectorItem::P_RESOLUTION_FUNCTION,
                                                     Constants::ResolutionFunction2DGaussianType);
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_X,
                                            resfunc->getSigmaX());
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_Y,
                                            resfunc->getSigmaY());
            } else {
                throw GUIHelpers::Error("TransformFromDomain::setItemFromSample("
                                        "RectangularDetectorItem* detectorItem, const GISASSimulation "
                                        "&simulation) -> Error, unknown detector resolution "
                                        "function");
            }
        } else {
            throw GUIHelpers::Error(
                "TransformFromDomain::setItemFromSample(RectangularDetectorItem "
                "*detectorItem, const GISASSimulation& simulation) -> Error, not a "
                "ConvolutionDetectorResolution function");
        }
    }
}


void TransformFromDomain::setDetectorMasks(DetectorItem* detectorItem, const GISASSimulation& simulation)
{
    Q_ASSERT(detectorItem);

    double scale(1.0);
    if(detectorItem->getGroupItem(DetectorItem::P_DETECTOR)->modelType()
            == Constants::SphericalDetectorType)
        scale = 1./Units::degree;

    const IDetector2D* detector = simulation.getInstrument().getDetector();
    const DetectorMask* detectorMask = detector->getDetectorMask();
    if(detectorMask && detectorMask->numberOfMasks()) {
        MaskContainerItem* containerItem = new MaskContainerItem();
        detectorItem->insertItem(-1, containerItem);
        for(size_t i_mask=0; i_mask<detectorMask->numberOfMasks(); ++i_mask) {
            bool mask_value(false);
            const IShape2D* shape = detectorMask->getMaskShape(i_mask, mask_value);
            if(const Ellipse* ellipse = dynamic_cast<const Ellipse*>(shape)) {
                EllipseItem* ellipseItem = new EllipseItem();
                ellipseItem->setItemValue(EllipseItem::P_XCENTER, scale*ellipse->getCenterX());
                ellipseItem->setItemValue(EllipseItem::P_YCENTER, scale*ellipse->getCenterY());
                ellipseItem->setItemValue(EllipseItem::P_XRADIUS, scale*ellipse->getRadiusX());
                ellipseItem->setItemValue(EllipseItem::P_YRADIUS, scale*ellipse->getRadiusY());
                ellipseItem->setItemValue(EllipseItem::P_ANGLE, scale*ellipse->getTheta());
                ellipseItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertItem(0, ellipseItem);

            }
            else if(const Rectangle* rectangle = dynamic_cast<const Rectangle*>(shape)) {
                RectangleItem* rectangleItem = new RectangleItem();
                rectangleItem->setItemValue(RectangleItem::P_XLOW, scale*rectangle->getXlow());
                rectangleItem->setItemValue(RectangleItem::P_YLOW, scale*rectangle->getYlow());
                rectangleItem->setItemValue(RectangleItem::P_XUP, scale*rectangle->getXup());
                rectangleItem->setItemValue(RectangleItem::P_YUP, scale*rectangle->getYup());
                rectangleItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertItem(0, rectangleItem);

            }
            else if(const Polygon* polygon = dynamic_cast<const Polygon*>(shape)) {
                PolygonItem* polygonItem = new PolygonItem();
                std::vector<double> xpos, ypos;
                polygon->getPoints(xpos, ypos);
                for(size_t i_point=0; i_point<xpos.size(); ++i_point) {
                    PolygonPointItem* pointItem = new PolygonPointItem();
                    pointItem->setItemValue(PolygonPointItem::P_POSX, scale*xpos[i_point]);
                    pointItem->setItemValue(PolygonPointItem::P_POSY, scale*ypos[i_point]);
                    polygonItem->insertItem(-1, pointItem);
                }

                polygonItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
                polygonItem->setItemValue(PolygonItem::P_ISCLOSED, true);

                containerItem->insertItem(0, polygonItem);
            }
            else if(const VerticalLine* vline = dynamic_cast<const VerticalLine*>(shape)) {
                VerticalLineItem* lineItem = new VerticalLineItem();
                lineItem->setItemValue(VerticalLineItem::P_POSX, scale*vline->getXpos());
                lineItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertItem(0, lineItem);
            }
            else if(const HorizontalLine* hline = dynamic_cast<const HorizontalLine*>(shape)) {
                HorizontalLineItem* lineItem = new HorizontalLineItem();
                lineItem->setItemValue(HorizontalLineItem::P_POSY, scale*hline->getYpos());
                lineItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertItem(0, lineItem);
            }
            else if(const InfinitePlane* plane = dynamic_cast<const InfinitePlane*>(shape)) {
                Q_UNUSED(plane);
                MaskAllItem* planeItem = new MaskAllItem();
                planeItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertItem(-1, planeItem);
            }
            else {
                throw GUIHelpers::Error("TransformFromDomain::setDetectorMasks() -> Error. "
                                        "Unknown shape");
            }
        }
    }

    if(detector->regionOfInterest()) {
        SessionItem* containerItem = detectorItem->getChildOfType(Constants::MaskContainerType);
        if(!containerItem) {
            containerItem = new MaskContainerItem();
            detectorItem->insertItem(-1, containerItem);
        }

        RegionOfInterestItem *roiItem = new RegionOfInterestItem();
        roiItem->setItemValue(RectangleItem::P_XLOW, scale*detector->regionOfInterest()->getXlow());
        roiItem->setItemValue(RectangleItem::P_YLOW, scale*detector->regionOfInterest()->getYlow());
        roiItem->setItemValue(RectangleItem::P_XUP, scale*detector->regionOfInterest()->getXup());
        roiItem->setItemValue(RectangleItem::P_YUP, scale*detector->regionOfInterest()->getYup());
        containerItem->insertItem(-1, roiItem);
    }
}

void TransformFromDomain::setItemFromSample(BeamDistributionItem* beamDistributionItem,
                                            const ParameterDistribution& parameterDistribution)
{
    Q_ASSERT(beamDistributionItem);

    if (parameterDistribution.getMinValue() < parameterDistribution.getMaxValue()) {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(BeamDistributionItem* beamDistributionItem,"
            "const ParameterDistribution& parameterDistribution) -> Error. ParameterDistribution "
            "with defined min,max are not yet implemented in GUI");
    }

    double unit_factor(1.0);
    if (beamDistributionItem->modelType() == Constants::BeamAzimuthalAngleType
        || beamDistributionItem->modelType() == Constants::BeamInclinationAngleType) {
        unit_factor = 1. / Units::degree;
    }
    QString group_name = BeamDistributionItem::P_DISTRIBUTION;
    setDistribution(beamDistributionItem, parameterDistribution, group_name, unit_factor);
}

QString TransformFromDomain::translateParameterNameToGUI(SessionItem* item,
                                                         const QString& par_name)
{
    QStringList gui_par_list = ModelPath::getParameterTreeList(item);
    for (QString gui_par_name : gui_par_list) {
        QString domain_par_name = QString::fromStdString(
                    ModelPath::translateParameterName(item, gui_par_name));
        if (domain_par_name == par_name) {
            return gui_par_name;
        }
    }
    return {};
}

void SetPDF1D(SessionItem* item, const IFTDistribution1D* ipdf, QString group_name)
{
    if (const FTDistribution1DCauchy* pdf = dynamic_cast<const FTDistribution1DCauchy*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DCauchyType);
        pdfItem->setItemValue(FTDistribution1DCauchyItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DGauss* pdf
               = dynamic_cast<const FTDistribution1DGauss*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DGaussType);
        pdfItem->setItemValue(FTDistribution1DGaussItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DGate* pdf = dynamic_cast<const FTDistribution1DGate*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DGateType);
        pdfItem->setItemValue(FTDistribution1DGateItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DTriangle* pdf
               = dynamic_cast<const FTDistribution1DTriangle*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DTriangleType);
        pdfItem->setItemValue(FTDistribution1DTriangleItem::P_CORR_LENGTH,
                                       pdf->getOmega());
    } else if (const FTDistribution1DCosine* pdf
               = dynamic_cast<const FTDistribution1DCosine*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DCosineType);
        pdfItem->setItemValue(FTDistribution1DCosineItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DVoigt* pdf
               = dynamic_cast<const FTDistribution1DVoigt*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DVoigtType);
        pdfItem->setItemValue(FTDistribution1DVoigtItem::P_CORR_LENGTH, pdf->getOmega());
        pdfItem->setItemValue(FTDistribution1DVoigtItem::P_ETA, pdf->getEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setPDF1D: -> Error");
    }
}

void setPDF2D(SessionItem* item, const IFTDistribution2D* pdf, QString group_name)
{
    if (const FTDistribution2DCauchy* pdf_cauchy
        = dynamic_cast<const FTDistribution2DCauchy*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DCauchyType);
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_COHER_LENGTH_X,
                                       pdf_cauchy->getCoherenceLengthX());
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_COHER_LENGTH_Y,
                                       pdf_cauchy->getCoherenceLengthY());
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_GAMMA,
                                       Units::rad2deg(pdf_cauchy->getGamma()));
    } else if (const FTDistribution2DGauss* pdf_gauss
               = dynamic_cast<const FTDistribution2DGauss*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DGaussType);
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_COHER_LENGTH_X,
                                       pdf_gauss->getCoherenceLengthX());
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_COHER_LENGTH_Y,
                                       pdf_gauss->getCoherenceLengthY());
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_GAMMA,
                                       Units::rad2deg(pdf_gauss->getGamma()));
    } else if (const FTDistribution2DGate* pdf_gate
               = dynamic_cast<const FTDistribution2DGate*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DGateType);
        pdfItem->setItemValue(FTDistribution2DGateItem::P_COHER_LENGTH_X,
                                       pdf_gate->getCoherenceLengthX());
        pdfItem->setItemValue(FTDistribution2DGateItem::P_COHER_LENGTH_Y,
                                       pdf_gate->getCoherenceLengthY());
        pdfItem->setItemValue(FTDistribution2DGateItem::P_GAMMA,
                                       Units::rad2deg(pdf_gate->getGamma()));
    } else if (const FTDistribution2DCone* pdf_cone
               = dynamic_cast<const FTDistribution2DCone*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DConeType);
        pdfItem->setItemValue(FTDistribution2DConeItem::P_COHER_LENGTH_X,
                                       pdf_cone->getCoherenceLengthX());
        pdfItem->setItemValue(FTDistribution2DConeItem::P_COHER_LENGTH_Y,
                                       pdf_cone->getCoherenceLengthY());
        pdfItem->setItemValue(FTDistribution2DConeItem::P_GAMMA,
                                       Units::rad2deg(pdf_cone->getGamma()));
    } else if (const FTDistribution2DVoigt* pdf_voigt
               = dynamic_cast<const FTDistribution2DVoigt*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DVoigtType);
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_COHER_LENGTH_X,
                                       pdf_voigt->getCoherenceLengthX());
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_COHER_LENGTH_Y,
                                       pdf_voigt->getCoherenceLengthY());
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_GAMMA,
                                       Units::rad2deg(pdf_voigt->getGamma()));
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_ETA, pdf_voigt->getEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setPDF2D: -> Error");
    }
}

void SetDecayFunction1D(SessionItem* item, const IFTDecayFunction1D* ipdf, QString group_name)
{
    if (const FTDecayFunction1DCauchy* pdf = dynamic_cast<const FTDecayFunction1DCauchy*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DCauchyType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->getOmega());
    } else if (const FTDecayFunction1DGauss* pdf
               = dynamic_cast<const FTDecayFunction1DGauss*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DGaussType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->getOmega());
    } else if (const FTDecayFunction1DTriangle* pdf
               = dynamic_cast<const FTDecayFunction1DTriangle*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DTriangleType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH,
                                       pdf->getOmega());
    } else if (const FTDecayFunction1DVoigt* pdf
               = dynamic_cast<const FTDecayFunction1DVoigt*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DVoigtType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->getOmega());
        pdfItem->setItemValue(FTDecayFunction1DVoigtItem::P_ETA, pdf->getEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::SetDecayFunction1D: -> Error");
    }
}

void SetDecayFunction2D(SessionItem* item, const IFTDecayFunction2D* pdf, QString group_name)
{
    if (const FTDecayFunction2DCauchy* pdf_cauchy
        = dynamic_cast<const FTDecayFunction2DCauchy*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction2DCauchyType);
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X,
                                       pdf_cauchy->getDecayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y,
                                       pdf_cauchy->getDecayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA,
                                       Units::rad2deg(pdf_cauchy->getGamma()));
    } else if (const FTDecayFunction2DGauss* pdf_gauss
               = dynamic_cast<const FTDecayFunction2DGauss*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction2DGaussType);
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X,
                                       pdf_gauss->getDecayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y,
                                       pdf_gauss->getDecayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA,
                                       Units::rad2deg(pdf_gauss->getGamma()));
    } else if (const FTDecayFunction2DVoigt* pdf_voigt
               = dynamic_cast<const FTDecayFunction2DVoigt*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction2DVoigtType);
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X,
                                       pdf_voigt->getDecayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y,
                                       pdf_voigt->getDecayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA,
                                       Units::rad2deg(pdf_voigt->getGamma()));
        pdfItem->setItemValue(FTDecayFunction2DVoigtItem::P_ETA, pdf_voigt->getEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::SetDecayFunction2D: -> Error");
    }
}

void set2DLatticeParameters(SessionItem* item, Lattice2DParameters lattice_params,
                            SessionItem* lattice_item)
{
    if (TransformFromDomain::isSquareLattice(lattice_params.m_length_1, lattice_params.m_length_2,
                                             lattice_params.m_angle)) {
        lattice_item = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                                 Constants::SquareLatticeType);
        lattice_item->setItemValue(SquareLatticeTypeItem::P_LATTICE_LENGTH,
                                               lattice_params.m_length_1);
    } else if (TransformFromDomain::isHexagonalLattice(
                   lattice_params.m_length_1, lattice_params.m_length_2, lattice_params.m_angle)) {
        lattice_item = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                                 Constants::HexagonalLatticeType);
        lattice_item->setItemValue(HexagonalLatticeTypeItem::P_LATTICE_LENGTH,
                                               lattice_params.m_length_1);
    } else {
        lattice_item = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                                 Constants::BasicLatticeType);
        lattice_item->setItemValue(BasicLatticeTypeItem::P_LATTICE_LENGTH1,
                                               lattice_params.m_length_1);
        lattice_item->setItemValue(BasicLatticeTypeItem::P_LATTICE_LENGTH2,
                                               lattice_params.m_length_2);
        lattice_item->setItemValue(BasicLatticeTypeItem::P_LATTICE_ANGLE,
                                               Units::rad2deg(lattice_params.m_angle));
    }
    item->setItemValue(InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE,
                                Units::rad2deg(lattice_params.m_xi));
}

void setDistribution(SessionItem* item, ParameterDistribution par_distr,
                     QString group_name, double factor)
{
    const IDistribution1D* p_distribution = par_distr.getDistribution();
    SessionItem* pdfItem = 0;
    if (const DistributionGate* distr = dynamic_cast<const DistributionGate*>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionGateType);
        pdfItem->setItemValue(DistributionGateItem::P_MIN, factor*distr->getMin());
        pdfItem->setItemValue(DistributionGateItem::P_MAX, factor*distr->getMax());
    } else if (const DistributionLorentz* distr
               = dynamic_cast<const DistributionLorentz*>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionLorentzType);
        pdfItem->setItemValue(DistributionLorentzItem::P_MEAN, factor*distr->getMean());
        pdfItem->setItemValue(DistributionLorentzItem::P_HWHM, factor*distr->getHWHM());
    } else if (const DistributionGaussian* distr
               = dynamic_cast<const DistributionGaussian*>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionGaussianType);
        pdfItem->setItemValue(DistributionGaussianItem::P_MEAN, factor*distr->getMean());
        pdfItem->setItemValue(DistributionGaussianItem::P_STD_DEV, factor*distr->getStdDev());
    } else if (const DistributionLogNormal* distr
               = dynamic_cast<const DistributionLogNormal*>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionLogNormalType);
        pdfItem->setItemValue(DistributionLogNormalItem::P_MEDIAN, factor*distr->getMedian());
        pdfItem->setItemValue(DistributionLogNormalItem::P_SCALE_PAR,
                                       distr->getScalePar());
    } else if (const DistributionCosine* distr
               = dynamic_cast<const DistributionCosine*>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionCosineType);
        pdfItem->setItemValue(DistributionCosineItem::P_MEAN, factor*distr->getMean());
        pdfItem->setItemValue(DistributionCosineItem::P_SIGMA, factor*distr->getSigma());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setDistribution: -> unknown distribution");
    }
    if (pdfItem) {
        pdfItem->setItemValue(DistributionItem::P_NUMBER_OF_SAMPLES,
                                       (int)par_distr.getNbrSamples());
        pdfItem->setItemValue(DistributionItem::P_SIGMA_FACTOR,
                                       par_distr.getSigmaFactor());
    }
}
