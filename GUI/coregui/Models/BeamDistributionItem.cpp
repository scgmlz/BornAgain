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

#include "BeamDistributionItem.h"
#include "Distributions.h"
#include "GroupItem.h"
#include "ParameterDistribution.h"
#include "ParameterTranslators.h"
#include "RealLimitsItems.h"
#include "Units.h"


const QString BeamDistributionItem::P_DISTRIBUTION = "Distribution";

BeamDistributionItem::BeamDistributionItem(const QString& name)
    : SessionItem(name)
{
    addTranslator(DistributionNoneTranslator());

    mapper()->setOnChildPropertyChange(
                [this](SessionItem* item, const QString &)
    {
        if(item->modelType() == Constants::GroupItemType && item->parent() == this)
            initDistributionItem();
    });

}

//! returns parameter distribution to add into the Simulation
std::unique_ptr<ParameterDistribution>
BeamDistributionItem::getParameterDistributionForName(const std::string& parameter_name)
{
    std::unique_ptr<ParameterDistribution> P_par_distr{};
    if (auto distributionItem = dynamic_cast<DistributionItem*>(getGroupItem(P_DISTRIBUTION))) {
        auto P_distribution = createDistribution1D();

        if (P_distribution) {
            int nbr_samples
                = distributionItem->getItemValue(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
            double sigma_factor(0);
            if (distributionItem->isTag(DistributionItem::P_SIGMA_FACTOR)) {
                sigma_factor
                    = distributionItem->getItemValue(DistributionItem::P_SIGMA_FACTOR).toInt();
            }

            RealLimitsItem* limitsItem = dynamic_cast<RealLimitsItem*>(
                        distributionItem->getGroupItem(DistributionItem::P_LIMITS));
            Q_ASSERT(limitsItem);

            RealLimits limits = limitsItem->createRealLimits(scaleFactor());

            P_par_distr = std::make_unique<ParameterDistribution>(
                parameter_name, *P_distribution, nbr_samples, sigma_factor, limits);
        }
    }
    return P_par_distr;
}

//! Propagates the value and limits stored in DistributionNone type into alls distributions.

void BeamDistributionItem::initDistributionItem()
{
    GroupItem* groupItem = dynamic_cast<GroupItem*>(getItem(P_DISTRIBUTION));
    Q_ASSERT(groupItem);

    SessionItem* distributionNone(0);
    foreach (SessionItem* item, groupItem->getItems(GroupItem::T_ITEMS)) {
        if (item->modelType() == Constants::DistributionNoneType) {
            distributionNone = item;
            break;
        }
    }

    if (!distributionNone)
        return;

    foreach (SessionItem* item, groupItem->getItems(GroupItem::T_ITEMS)) {
        if (item != distributionNone) {
            DistributionItem* distrItem = dynamic_cast<DistributionItem*>(item);
            RealLimits limits = distributionNone->getItem(DistributionNoneItem::P_VALUE)->limits();

            distrItem->init_parameters(
                distributionNone->getItemValue(DistributionNoneItem::P_VALUE).toDouble(), limits);

            // hiding limits from the editor
            if (distrItem->isTag(DistributionItem::P_LIMITS))
                distrItem->getItem(DistributionItem::P_LIMITS)->setVisible(false);
        }
    }
}

//! Returns mean value of the distribution.

double BeamDistributionItem::meanValue() const
{
    std::unique_ptr<IDistribution1D> domainDistr = createDistribution1D();
    if (domainDistr)
        return domainDistr->getMean()/scaleFactor();
    else
        return getGroupItem(P_DISTRIBUTION)->getItemValue(DistributionNoneItem::P_VALUE).toDouble();
}

//! Scales the values provided by distribution (to perform deg->rad conversion in the case
//! of AngleDistributionItems.

double BeamDistributionItem::scaleFactor() const
{
    return 1.0;
}

void BeamDistributionItem::register_distribution_group()
{
    addGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
}

std::unique_ptr<IDistribution1D> BeamDistributionItem::createDistribution1D() const
{
    if (auto distItem = dynamic_cast<DistributionItem*>(getGroupItem(P_DISTRIBUTION)))
        return distItem->createDistribution(scaleFactor());

    return {};
}
