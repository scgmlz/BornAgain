// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamDistributionItem.cpp
//! @brief     Implements class BeamDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/BeamDistributionItem.h"
#include "Core/Basics/Assert.h"
#include "Core/Basics/Units.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterDistribution.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ParameterTranslators.h"
#include "GUI/coregui/Models/RealLimitsItems.h"

const QString BeamDistributionItem::P_DISTRIBUTION = "Distribution";

BeamDistributionItem::BeamDistributionItem(const QString& name, bool show_mean) : SessionItem(name)
{
    addTranslator(DistributionNoneTranslator());

    mapper()->setOnChildPropertyChange([this, show_mean](SessionItem* item, const QString&) {
        if (item->modelType() == "GroupProperty" && item->parent() == this)
            initDistributionItem(show_mean);
    });
}

//! returns parameter distribution to add into the Simulation
std::unique_ptr<ParameterDistribution>
BeamDistributionItem::getParameterDistributionForName(const std::string& parameter_name) const
{
    std::unique_ptr<ParameterDistribution> P_par_distr{};
    if (auto distributionItem = dynamic_cast<DistributionItem*>(getGroupItem(P_DISTRIBUTION))) {
        auto P_distribution = createDistribution1D();

        if (P_distribution) {
            int nbr_samples =
                distributionItem->getItemValue(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
            double sigma_factor(0);
            if (distributionItem->isTag(DistributionItem::P_SIGMA_FACTOR)) {
                sigma_factor =
                    distributionItem->getItemValue(DistributionItem::P_SIGMA_FACTOR).toInt();
            }

            RealLimitsItem* limitsItem = dynamic_cast<RealLimitsItem*>(
                distributionItem->getGroupItem(DistributionItem::P_LIMITS));
            ASSERT(limitsItem);

            RealLimits limits = limitsItem->createRealLimits(scaleFactor());

            P_par_distr = std::make_unique<ParameterDistribution>(
                parameter_name, *P_distribution, nbr_samples, sigma_factor, limits);
        }
    }
    return P_par_distr;
}

//! Propagates the value and limits stored in DistributionNone type into alls distributions.

void BeamDistributionItem::initDistributionItem(bool show_mean)
{
    GroupItem* groupItem = dynamic_cast<GroupItem*>(getItem(P_DISTRIBUTION));
    ASSERT(groupItem);

    SessionItem* distributionNone = nullptr;
    for (auto item : groupItem->getItems(GroupItem::T_ITEMS)) {
        if (item->modelType() == "DistributionNone") {
            distributionNone = item;
            break;
        }
    }

    if (!distributionNone)
        return;

    const RealLimits limits = distributionNone->getItem(DistributionNoneItem::P_MEAN)->limits();
    const QString editor_type =
        distributionNone->getItem(DistributionNoneItem::P_MEAN)->editorType();

    for (auto item : groupItem->getItems(GroupItem::T_ITEMS)) {
        DistributionItem* distrItem = dynamic_cast<DistributionItem*>(item);
        distrItem->showMean(show_mean);

        if (item == distributionNone)
            continue;

        distrItem->init_parameters(
            distributionNone->getItemValue(DistributionNoneItem::P_MEAN).toDouble(), limits);
        if (auto symmetric_distr = dynamic_cast<SymmetricDistributionItem*>(distrItem))
            symmetric_distr->getItem(SymmetricDistributionItem::P_MEAN)
                ->setEditorType(editor_type)
                .setLimits(limits);

        // hiding limits from the editor
        if (distrItem->isTag(DistributionItem::P_LIMITS))
            distrItem->getItem(DistributionItem::P_LIMITS)->setVisible(false);
    }
}

//! Returns mean value of the distribution.

double BeamDistributionItem::meanValue() const
{
    std::unique_ptr<IDistribution1D> domainDistr = createDistribution1D();
    if (domainDistr)
        return domainDistr->getMean() / scaleFactor();
    else
        return getGroupItem(P_DISTRIBUTION)->getItemValue(DistributionNoneItem::P_MEAN).toDouble();
}

void BeamDistributionItem::resetToValue(double value)
{
    SessionItem* distributionItem =
        setGroupProperty(BeamDistributionItem::P_DISTRIBUTION, "DistributionNone");
    ASSERT(distributionItem);
    distributionItem->setItemValue(DistributionNoneItem::P_MEAN, value);
}

//! Scales the values provided by distribution (to perform deg->rad conversion in the case
//! of AngleDistributionItems.

double BeamDistributionItem::scaleFactor() const
{
    return 1.0;
}

void BeamDistributionItem::register_distribution_group(const QString& group_type)
{
    ASSERT(group_type == "Distribution extended group"
           || group_type == "Symmetric distribution group");
    addGroupProperty(P_DISTRIBUTION, group_type);
}

std::unique_ptr<IDistribution1D> BeamDistributionItem::createDistribution1D() const
{
    if (auto distItem = dynamic_cast<DistributionItem*>(getGroupItem(P_DISTRIBUTION)))
        return distItem->createDistribution(scaleFactor());

    return {};
}
