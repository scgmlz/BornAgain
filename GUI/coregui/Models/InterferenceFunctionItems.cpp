// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InterferenceFunctionItems.cpp
//! @brief     Implements InterferenceFunctionItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "Core/Basics/Units.h"
#include "Core/Correlations/FTDecay1D.h"
#include "Core/Correlations/FTDecay2D.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "Core/includeIncludes/InterferenceFunctions.h"
#include "GUI/coregui/Models/FTDecayFunctionItems.h"
#include "GUI/coregui/Models/FTDistributionItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/ModelPath.h"

namespace
{
const QString decay_function_tag = "Decay Function";
}

// TODO (when back compatibility will be broken  again)
// Make InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION and
// InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION rely on same constant

const QString InterferenceFunctionItem::P_POSITION_VARIANCE =
    QString::fromStdString("PositionVariance");

InterferenceFunctionItem::InterferenceFunctionItem(const QString& modelType)
    : SessionGraphicsItem(modelType)
{
    addProperty(P_POSITION_VARIANCE, 0.0)
        ->setToolTip("Variance of the position in each dimension (nm^2)");
}

InterferenceFunctionItem::~InterferenceFunctionItem() {}

void InterferenceFunctionItem::setPositionVariance(IInterferenceFunction* p_iff) const
{
    p_iff->setPositionVariance(getItemValue(P_POSITION_VARIANCE).toDouble());
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction1DLatticeItem::P_LENGTH = QString::fromStdString("Length");
const QString InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE = QString::fromStdString("Xi");
const QString InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION = decay_function_tag;

InterferenceFunction1DLatticeItem::InterferenceFunction1DLatticeItem()
    : InterferenceFunctionItem("Interference1DLattice")
{
    setToolTip("Interference function of a 1D lattice");
    addProperty(P_LENGTH, 20.0 * Units::nanometer)->setToolTip("Lattice length in nanometers");
    addProperty(P_ROTATION_ANGLE, 0.0)
        ->setToolTip("Rotation of lattice with respect to x-axis of reference \n"
                     "frame (beam direction) in degrees ");
    addGroupProperty(P_DECAY_FUNCTION, "Decay function 1D")
        ->setToolTip("One-dimensional decay function (finite size effects)");
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunction1DLatticeItem::createInterferenceFunction() const
{
    auto result = std::make_unique<InterferenceFunction1DLattice>(
        getItemValue(P_LENGTH).toDouble(),
        Units::deg2rad(getItemValue(P_ROTATION_ANGLE).toDouble()));
    auto pdfItem = dynamic_cast<FTDecayFunction1DItem*>(
        getGroupItem(InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION));
    result->setDecayFunction(*pdfItem->createFTDecayFunction());
    setPositionVariance(result.get());
    return std::unique_ptr<IInterferenceFunction>(result.release());
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction2DLatticeItem::P_LATTICE_TYPE = "LatticeType";
const QString InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION = decay_function_tag;
const QString InterferenceFunction2DLatticeItem::P_XI_INTEGRATION = "Integration_over_xi";

InterferenceFunction2DLatticeItem::InterferenceFunction2DLatticeItem()
    : InterferenceFunctionItem("Interference2DLattice")
{
    setToolTip("Interference function of a 2D lattice");
    addGroupProperty(P_LATTICE_TYPE, "Lattice group")->setToolTip("Type of lattice");
    addGroupProperty(P_DECAY_FUNCTION, "Decay function 2D")
        ->setToolTip("Two-dimensional decay function (finite size effects)");
    addProperty(P_XI_INTEGRATION, false)
        ->setToolTip("Enables/disables averaging over the lattice rotation angle.");

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_XI_INTEGRATION && isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            update_rotation_availability();
        }
    });
    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString&) {
        if (item->modelType() == "GroupProperty"
            && item->displayName() == InterferenceFunction2DLatticeItem::P_LATTICE_TYPE) {
            update_rotation_availability();
        }
    });
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunction2DLatticeItem::createInterferenceFunction() const
{
    auto& latticeItem = groupItem<Lattice2DItem>(P_LATTICE_TYPE);
    std::unique_ptr<InterferenceFunction2DLattice> result(
        new InterferenceFunction2DLattice(*latticeItem.createLattice()));

    auto& pdfItem = groupItem<FTDecayFunction2DItem>(P_DECAY_FUNCTION);
    result->setDecayFunction(*pdfItem.createFTDecayFunction());
    result->setIntegrationOverXi(getItemValue(P_XI_INTEGRATION).toBool());
    setPositionVariance(result.get());

    return std::unique_ptr<IInterferenceFunction>(result.release());
}

void InterferenceFunction2DLatticeItem::update_rotation_availability()
{
    auto p_lattice_item = getGroupItem(P_LATTICE_TYPE);
    if (p_lattice_item) {
        auto angle_item = p_lattice_item->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);
        angle_item->setEnabled(!getItemValue(P_XI_INTEGRATION).toBool());
    }
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH =
    QString::fromStdString("DampingLength");
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1 =
    QString::fromStdString("DomainSize1");
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2 =
    QString::fromStdString("DomainSize2");
const QString InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION = "Integration_over_xi";
const QString InterferenceFunction2DParaCrystalItem::P_PDF1 = "PDF #1";
const QString InterferenceFunction2DParaCrystalItem::P_PDF2 = "PDF #2";

InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem()
    : InterferenceFunctionItem("Interference2DParaCrystal")
{
    setToolTip("Interference function of a two-dimensional paracrystal");

    addGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, "Lattice group")
        ->setToolTip("Type of lattice");
    getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
        ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE)
        ->setEnabled(false);
    addProperty(P_XI_INTEGRATION, true)
        ->setToolTip("Enables/disables averaging over the lattice rotation angle.");

    addProperty(P_DAMPING_LENGTH, 0.0)
        ->setToolTip("The damping (coherence) length of the paracrystal in nanometers");

    addProperty(P_DOMAIN_SIZE1, 20.0 * Units::micrometer)
        ->setToolTip("Size of the coherent domain along the first basis vector in nanometers");
    addProperty(P_DOMAIN_SIZE2, 20.0 * Units::micrometer)
        ->setToolTip("Size of the coherent domain along the second basis vector in nanometers");
    addGroupProperty(P_PDF1, "PDF 2D")
        ->setToolTip("Probability distribution in first lattice direction");
    addGroupProperty(P_PDF2, "PDF 2D")
        ->setToolTip("Probability distribution in second lattice direction");

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_XI_INTEGRATION && isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            update_rotation_availability();
        }
    });

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString& property) {
        if (item->modelType() == "GroupProperty"
            && item->displayName() == InterferenceFunction2DLatticeItem::P_LATTICE_TYPE) {
            update_rotation_availability();
        }
        if (item->modelType() == "GroupProperty" && property == GroupItem::T_ITEMS && isTag(P_PDF1)
            && isTag(P_PDF2))
            update_distribution_displaynames();
    });

    update_distribution_displaynames();
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunction2DParaCrystalItem::createInterferenceFunction() const
{
    auto& latticeItem = groupItem<Lattice2DItem>(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);

    std::unique_ptr<InterferenceFunction2DParaCrystal> result(
        new InterferenceFunction2DParaCrystal(*latticeItem.createLattice(), 0, 0, 0));

    result->setDampingLength(getItemValue(P_DAMPING_LENGTH).toDouble());
    result->setDomainSizes(getItemValue(P_DOMAIN_SIZE1).toDouble(),
                           getItemValue(P_DOMAIN_SIZE2).toDouble());
    result->setIntegrationOverXi(getItemValue(P_XI_INTEGRATION).toBool());

    auto& pdf1Item = groupItem<FTDistribution2DItem>(InterferenceFunction2DParaCrystalItem::P_PDF1);
    auto& pdf2Item = groupItem<FTDistribution2DItem>(InterferenceFunction2DParaCrystalItem::P_PDF2);
    result->setProbabilityDistributions(*pdf1Item.createFTDistribution(),
                                        *pdf2Item.createFTDistribution());

    setPositionVariance(result.get());
    return std::unique_ptr<IInterferenceFunction>(result.release());
}

//! Sets rotation property of the lattice enabled/disabled depending on integration flag.

void InterferenceFunction2DParaCrystalItem::update_rotation_availability()
{
    auto p_lattice_item = getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    if (p_lattice_item) {
        auto angle_item = p_lattice_item->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);
        angle_item->setEnabled(!getItemValue(P_XI_INTEGRATION).toBool());
    }
}

void InterferenceFunction2DParaCrystalItem::update_distribution_displaynames()
{
    GroupItem* group1 = dynamic_cast<GroupItem*>(getItem(P_PDF1));
    GroupItem* group2 = dynamic_cast<GroupItem*>(getItem(P_PDF2));

    if (!group1 || !group2)
        return;

    SessionItem* pdf1 = group1->currentItem();
    SessionItem* pdf2 = group2->currentItem();

    if (pdf1 && pdf2) {
        if (pdf1->modelType() == pdf2->modelType()) {
            pdf1->setDisplayName(pdf1->modelType() + QString::number(0));
            pdf2->setDisplayName(pdf2->modelType() + QString::number(1));
        } else {
            pdf1->setDisplayName(pdf1->modelType());
            pdf2->setDisplayName(pdf2->modelType());
        }
    }
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunctionFinite2DLatticeItem::P_XI_INTEGRATION = "Integration_over_xi";
const QString InterferenceFunctionFinite2DLatticeItem::P_DOMAIN_SIZE_1 = "Domain_size_1";
const QString InterferenceFunctionFinite2DLatticeItem::P_DOMAIN_SIZE_2 = "Domain_size_2";

InterferenceFunctionFinite2DLatticeItem::InterferenceFunctionFinite2DLatticeItem()
    : InterferenceFunctionItem("InterferenceFinite2DLattice")
{
    setToolTip("Interference function of a finite 2D lattice");
    addGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, "Lattice group")
        ->setToolTip("Type of lattice");
    addProperty(P_XI_INTEGRATION, false)
        ->setToolTip("Enables/disables averaging over the lattice rotation angle.");
    addProperty(P_DOMAIN_SIZE_1, 100u)->setToolTip("Domain size 1 in number of unit cells");
    addProperty(P_DOMAIN_SIZE_2, 100u)->setToolTip("Domain size 2 in number of unit cells");

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_XI_INTEGRATION && isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            update_rotation_availability();
        }
    });
    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString&) {
        if (item->modelType() == "GroupProperty"
            && item->displayName() == InterferenceFunction2DLatticeItem::P_LATTICE_TYPE) {
            update_rotation_availability();
        }
    });
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunctionFinite2DLatticeItem::createInterferenceFunction() const
{
    auto& latticeItem = groupItem<Lattice2DItem>(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    auto size_1 = getItemValue(P_DOMAIN_SIZE_1).toUInt();
    auto size_2 = getItemValue(P_DOMAIN_SIZE_2).toUInt();
    std::unique_ptr<InterferenceFunctionFinite2DLattice> result(
        new InterferenceFunctionFinite2DLattice(*latticeItem.createLattice(), size_1, size_2));

    result->setIntegrationOverXi(getItemValue(P_XI_INTEGRATION).toBool());
    setPositionVariance(result.get());

    return std::unique_ptr<IInterferenceFunction>(result.release());
}

void InterferenceFunctionFinite2DLatticeItem::update_rotation_availability()
{
    auto p_lattice_item = getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    if (p_lattice_item) {
        auto angle_item = p_lattice_item->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);
        angle_item->setEnabled(!getItemValue(P_XI_INTEGRATION).toBool());
    }
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunctionHardDiskItem::P_RADIUS = QString::fromStdString("Radius");
const QString InterferenceFunctionHardDiskItem::P_DENSITY =
    QString::fromStdString("TotalParticleDensity");

InterferenceFunctionHardDiskItem::InterferenceFunctionHardDiskItem()
    : InterferenceFunctionItem("InterferenceHardDisk")
{
    setToolTip("Interference function for hard disk Percus-Yevick");
    addProperty(P_RADIUS, 5.0 * Units::nanometer)->setToolTip("Hard disk radius in nanometers");
    addProperty(P_DENSITY, 0.002)->setToolTip("Particle density in particles per square nanometer");
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunctionHardDiskItem::createInterferenceFunction() const
{
    auto result = std::make_unique<InterferenceFunctionHardDisk>(
        getItemValue(P_RADIUS).toDouble(), getItemValue(P_DENSITY).toDouble());
    setPositionVariance(result.get());
    return std::unique_ptr<IInterferenceFunction>(result.release());
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE =
    QString::fromStdString("PeakDistance");
const QString InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH =
    QString::fromStdString("DampingLength");
const QString InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE =
    QString::fromStdString("DomainSize");
const QString InterferenceFunctionRadialParaCrystalItem::P_KAPPA =
    QString::fromStdString("SizeSpaceCoupling");
const QString InterferenceFunctionRadialParaCrystalItem::P_PDF = "PDF";

InterferenceFunctionRadialParaCrystalItem::InterferenceFunctionRadialParaCrystalItem()
    : InterferenceFunctionItem("InterferenceRadialParaCrystal")
{
    setToolTip("Interference function of a radial paracrystal");
    addProperty(P_PEAK_DISTANCE, 20.0 * Units::nanometer)
        ->setToolTip("Average distance to the next neighbor in nanometers");
    addProperty(P_DAMPING_LENGTH, 1000.0 * Units::nanometer)
        ->setToolTip("The damping (coherence) length of the paracrystal "
                     "in nanometers");
    addProperty(P_DOMAIN_SIZE, 0.0)
        ->setToolTip("Size of coherence domain along the lattice main axis "
                     "in nanometers");
    addProperty(P_KAPPA, 0.0)
        ->setToolTip("Size spacing coupling parameter of the Size Spacing "
                     "Correlation Approximation");
    addGroupProperty(P_PDF, "PDF 1D")->setToolTip("One-dimensional probability distribution");
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunctionRadialParaCrystalItem::createInterferenceFunction() const
{
    auto result = std::make_unique<InterferenceFunctionRadialParaCrystal>(
        getItemValue(P_PEAK_DISTANCE).toDouble(), getItemValue(P_DAMPING_LENGTH).toDouble());
    result->setDomainSize(getItemValue(P_DOMAIN_SIZE).toDouble());
    result->setKappa(getItemValue(P_KAPPA).toDouble());

    auto& pdfItem = groupItem<FTDistribution1DItem>(P_PDF);
    result->setProbabilityDistribution(*pdfItem.createFTDistribution());
    setPositionVariance(result.get());
    return std::unique_ptr<IInterferenceFunction>(result.release());
}
