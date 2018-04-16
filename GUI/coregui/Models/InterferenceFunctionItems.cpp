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

#include "InterferenceFunctionItems.h"
#include "BornAgainNamespace.h"
#include "Lattice2DItems.h"
#include "ModelPath.h"
#include "Units.h"
#include "FTDecayFunctionItems.h"
#include "FTDecayFunctions.h"
#include "FTDistributionItems.h"
#include "FTDistributions2D.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunctionFinite2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunction1DLattice.h"
#include "GroupItem.h"

namespace {
    const QString decay_function_tag = "Decay Function";
}

// TODO (when back compatibility will be broken  again)
// Make InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION and
// InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION rely on same constant

InterferenceFunctionItem::InterferenceFunctionItem(const QString& modelType)
    : SessionGraphicsItem(modelType)
{

}

InterferenceFunctionItem::~InterferenceFunctionItem(){}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE =
        QString::fromStdString(BornAgain::PeakDistance);
const QString InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH =
        QString::fromStdString(BornAgain::DampingLength);
const QString InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE =
        QString::fromStdString(BornAgain::DomainSize);
const QString InterferenceFunctionRadialParaCrystalItem::P_KAPPA =
        QString::fromStdString(BornAgain::SizeSpaceCoupling);
const QString InterferenceFunctionRadialParaCrystalItem::P_PDF = "PDF";

InterferenceFunctionRadialParaCrystalItem::InterferenceFunctionRadialParaCrystalItem()
    : InterferenceFunctionItem(Constants::InterferenceFunctionRadialParaCrystalType)
{
    setToolTip(QStringLiteral("Interference function of a radial paracrystal"));
    addProperty(P_PEAK_DISTANCE, 20.0*Units::nanometer)
        ->setToolTip(QStringLiteral("Average distance to the next neighbor in nanometers"));
    addProperty(P_DAMPING_LENGTH, 1000.0*Units::nanometer)
        ->setToolTip(QStringLiteral("The damping (coherence) length of the paracrystal "
                                    "in nanometers"));
    addProperty(P_DOMAIN_SIZE, 0.0)
        ->setToolTip(QStringLiteral("Size of coherence domain along the lattice main axis "
                                    "in nanometers"));
    addProperty(P_KAPPA, 0.0)
        ->setToolTip(QStringLiteral("Size spacing coupling parameter of the Size Spacing "
                                    "Correlation Approximation"));
    addGroupProperty(P_PDF, Constants::FTDistribution1DGroup)
        ->setToolTip(QStringLiteral("One-dimensional probability distribution"));
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
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH =
        QString::fromStdString(BornAgain::DampingLength);
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1 =
        QString::fromStdString(BornAgain::DomainSize1);
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2 =
        QString::fromStdString(BornAgain::DomainSize2);
const QString InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION = "Integration_over_xi";
const QString InterferenceFunction2DParaCrystalItem::P_PDF1 = "PDF #1";
const QString InterferenceFunction2DParaCrystalItem::P_PDF2 = "PDF #2";

InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem()
    : InterferenceFunctionItem(Constants::InterferenceFunction2DParaCrystalType)
{
    setToolTip(QStringLiteral("Interference function of a two-dimensional paracrystal"));

    addGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, Constants::LatticeGroup)
        ->setToolTip(QStringLiteral("Type of lattice"));
    getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
        ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE)->setEnabled(false);
    addProperty(P_XI_INTEGRATION, true)->setToolTip(
        QStringLiteral("Enables/disables averaging over the lattice rotation angle."));

    addProperty(P_DAMPING_LENGTH, 0.0)->setToolTip(
        QStringLiteral("The damping (coherence) length of the paracrystal in nanometers"));

    addProperty(P_DOMAIN_SIZE1, 20.0 * Units::micrometer)->setToolTip(
        QStringLiteral("Size of the coherent domain along the first basis vector in nanometers"));
    addProperty(P_DOMAIN_SIZE2, 20.0 * Units::micrometer)->setToolTip(
        QStringLiteral("Size of the coherent domain along the second basis vector in nanometers"));
    addGroupProperty(P_PDF1, Constants::FTDistribution2DGroup)->setToolTip(
        QStringLiteral("Probability distribution in first lattice direction"));
    addGroupProperty(P_PDF2, Constants::FTDistribution2DGroup)->setToolTip(
                QStringLiteral("Probability distribution in second lattice direction"));

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_XI_INTEGRATION && isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            update_rotation_availability();
        }
    });

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString& property) {
        if (item->modelType() == Constants::GroupItemType && item->displayName() ==
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE) {
            update_rotation_availability();
        }
        if (item->modelType() == Constants::GroupItemType && property == GroupItem::T_ITEMS
            && isTag(P_PDF1) && isTag(P_PDF2))
            update_distribution_displaynames();
    });

    update_distribution_displaynames();
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunction2DParaCrystalItem::createInterferenceFunction() const
{
    auto& latticeItem = groupItem<Lattice2DItem>(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);

    std::unique_ptr<InterferenceFunction2DParaCrystal> result(
        new InterferenceFunction2DParaCrystal(*latticeItem.createLattice()));

    result->setDampingLength(getItemValue(P_DAMPING_LENGTH).toDouble());
    result->setDomainSizes(getItemValue(P_DOMAIN_SIZE1).toDouble(),
                           getItemValue(P_DOMAIN_SIZE2).toDouble());
    result->setIntegrationOverXi(getItemValue(P_XI_INTEGRATION).toBool());

    auto& pdf1Item = groupItem<FTDistribution2DItem>(InterferenceFunction2DParaCrystalItem::P_PDF1);
    auto& pdf2Item = groupItem<FTDistribution2DItem>(InterferenceFunction2DParaCrystalItem::P_PDF2);
    result->setProbabilityDistributions(*pdf1Item.createFTDistribution(),
                                        *pdf2Item.createFTDistribution());

    return std::move(result);
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
    GroupItem *group1 = dynamic_cast<GroupItem*>(getItem(P_PDF1));
    GroupItem *group2 = dynamic_cast<GroupItem*>(getItem(P_PDF2));

    if(!group1 || !group2)
        return;

    SessionItem *pdf1 = group1->currentItem();
    SessionItem *pdf2 = group2->currentItem();

    if(pdf1 && pdf2) {
        if(pdf1->modelType() == pdf2->modelType()) {
            pdf1->setDisplayName(pdf1->modelType()+QString::number(0));
            pdf2->setDisplayName(pdf2->modelType()+QString::number(1));
        } else {
            pdf1->setDisplayName(pdf1->modelType());
            pdf2->setDisplayName(pdf2->modelType());
        }
    }
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction1DLatticeItem::P_LENGTH =
        QString::fromStdString(BornAgain::Length);
const QString InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE =
        QString::fromStdString(BornAgain::Xi);
const QString InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION = decay_function_tag;

InterferenceFunction1DLatticeItem::InterferenceFunction1DLatticeItem()
    : InterferenceFunctionItem(Constants::InterferenceFunction1DLatticeType)
{
    setToolTip(QStringLiteral("Interference function of a 1D lattice"));
    addProperty(P_LENGTH, 20.0 * Units::nanometer)
            ->setToolTip(QStringLiteral("Lattice length in nanometers"));
    addProperty(P_ROTATION_ANGLE, 0.0)
        ->setToolTip(QStringLiteral("Rotation of lattice with respect to x-axis of reference \n"
                                    "frame (beam direction) in degrees "));
    addGroupProperty(P_DECAY_FUNCTION, Constants::FTDecayFunction1DGroup)
        ->setToolTip(QStringLiteral("One-dimensional decay function (finite size effects)"));
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
    return std::move(result);
}

// --------------------------------------------------------------------------------------------- //

const QString InterferenceFunction2DLatticeItem::P_LATTICE_TYPE = "LatticeType";
const QString InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION = decay_function_tag;
const QString InterferenceFunction2DLatticeItem::P_XI_INTEGRATION = "Integration_over_xi";

InterferenceFunction2DLatticeItem::InterferenceFunction2DLatticeItem()
    : InterferenceFunctionItem(Constants::InterferenceFunction2DLatticeType)
{
    setToolTip(QStringLiteral("Interference function of a 2D lattice"));
    addGroupProperty(P_LATTICE_TYPE, Constants::LatticeGroup)->setToolTip("Type of lattice");
    addGroupProperty(P_DECAY_FUNCTION, Constants::FTDecayFunction2DGroup)
        ->setToolTip("Two-dimensional decay function (finite size effects)");
    addProperty(P_XI_INTEGRATION, false)->setToolTip(
        QStringLiteral("Enables/disables averaging over the lattice rotation angle."));

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_XI_INTEGRATION && isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            update_rotation_availability();
        }
    });
    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString&) {
        if (item->modelType() == Constants::GroupItemType && item->displayName() ==
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE) {
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

    return std::move(result);
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

const QString InterferenceFunctionFinite2DLatticeItem::P_XI_INTEGRATION = "Integration_over_xi";
const QString InterferenceFunctionFinite2DLatticeItem::P_DOMAIN_SIZE_1 = "Domain_size_1";
const QString InterferenceFunctionFinite2DLatticeItem::P_DOMAIN_SIZE_2 = "Domain_size_2";
const QString InterferenceFunctionFinite2DLatticeItem::P_POSITION_VARIANCE = "Position_variance";

InterferenceFunctionFinite2DLatticeItem::InterferenceFunctionFinite2DLatticeItem()
    : InterferenceFunctionItem(Constants::InterferenceFunctionFinite2DLatticeType)
{
    setToolTip(QStringLiteral("Interference function of a finite 2D lattice"));
    addGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                     Constants::LatticeGroup)->setToolTip("Type of lattice");
    addProperty(P_XI_INTEGRATION, false)->setToolTip(
        QStringLiteral("Enables/disables averaging over the lattice rotation angle."));
    addProperty(P_DOMAIN_SIZE_1, 100u)->setToolTip(
        QStringLiteral("Domain size 1 in number of unit cells"));
    addProperty(P_DOMAIN_SIZE_2, 100u)->setToolTip(
        QStringLiteral("Domain size 2 in number of unit cells"));
    addProperty(P_POSITION_VARIANCE, 0.0)->setToolTip(
        QStringLiteral("Variance of position for DW factor"));

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_XI_INTEGRATION
            && isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            update_rotation_availability();
        }
    });
    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString&) {
        if (item->modelType() == Constants::GroupItemType && item->displayName() ==
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE) {
            update_rotation_availability();
        }
    });
}

std::unique_ptr<IInterferenceFunction>
InterferenceFunctionFinite2DLatticeItem::createInterferenceFunction() const
{
    auto& latticeItem = groupItem<Lattice2DItem>(
                            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    auto size_1 = getItemValue(P_DOMAIN_SIZE_1).toUInt();
    auto size_2 = getItemValue(P_DOMAIN_SIZE_2).toUInt();
    std::unique_ptr<InterferenceFunctionFinite2DLattice> result(
        new InterferenceFunctionFinite2DLattice(*latticeItem.createLattice(), size_1, size_2));

    result->setPositionVariance(getItemValue(P_POSITION_VARIANCE).toDouble());
    result->setIntegrationOverXi(getItemValue(P_XI_INTEGRATION).toBool());

    return std::move(result);
}

void InterferenceFunctionFinite2DLatticeItem::update_rotation_availability()
{
    auto p_lattice_item = getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    if (p_lattice_item) {
        auto angle_item = p_lattice_item->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);
        angle_item->setEnabled(!getItemValue(P_XI_INTEGRATION).toBool());
    }
}
