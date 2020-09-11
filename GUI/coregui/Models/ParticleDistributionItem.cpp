// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleDistributionItem.cpp
//! @brief     Implements class ParticleDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "Core/Basics/Units.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterUtils.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DistributionItems.h"
#include "GUI/coregui/Models/ParameterTreeUtils.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/RealLimitsItems.h"
#include "GUI/coregui/Models/TransformFromDomain.h"
#include "GUI/coregui/Models/TransformToDomain.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
const QString abundance_tooltip = "Proportion of this type of particles normalized to the \n"
                                  "total number of particles in the layout";
}

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER = "Distributed parameter";
const QString ParticleDistributionItem::P_LINKED_PARAMETER = "Linked parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::NO_SELECTION = "None";
const QString ParticleDistributionItem::T_PARTICLES = "Particle Tag";

ParticleDistributionItem::ParticleDistributionItem() : SessionGraphicsItem("ParticleDistribution")
{
    setToolTip("Collection of particles obtained via parametric distribution "
               "of particle prototype");

    addProperty(ParticleItem::P_ABUNDANCE, 1.0)
        ->setLimits(RealLimits::limited(0.0, 1.0))
        .setDecimals(3)
        .setToolTip(abundance_tooltip);

    addGroupProperty(P_DISTRIBUTION, "Distribution group")
        ->setToolTip("Distribution to apply to the specified parameter");

    registerTag(T_PARTICLES, 0, 1,
                QStringList() << "Particle"
                              << "ParticleCoreShell"
                              << "ParticleComposition"
                              << "MesoCrystal");
    setDefaultTag(T_PARTICLES);

    ComboProperty par_prop;
    addProperty(P_DISTRIBUTED_PARAMETER, par_prop.variant())->setToolTip("Parameter to distribute");

    addProperty(P_LINKED_PARAMETER, par_prop.variant())
        ->setToolTip("Linked parameter")
        .setEditorType("MultiSelectionComboEditor");

    updateMainParameterList();

    mapper()->setOnAnyChildChange([this](SessionItem* item) {
        // prevent infinit loop when item changes its own properties
        if (item && item->modelType() == "Property" && item->parent() == this)
            return;
        updateMainParameterList();
    });

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_DISTRIBUTED_PARAMETER)
            updateLinkedParameterList();
    });
}

std::unique_ptr<ParticleDistribution> ParticleDistributionItem::createParticleDistribution() const
{
    if (children().size() == 0)
        return nullptr;
    std::unique_ptr<IParticle> P_particle = TransformToDomain::createIParticle(*getItem());
    if (!P_particle)
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! No correct particle defined");
    auto& distr_item = groupItem<DistributionItem>(ParticleDistributionItem::P_DISTRIBUTION);

    std::string domain_par = domainMainParameter();

    double scale = ParameterUtils::isAngleRelated(domain_par) ? Units::degree : 1.0;
    auto P_distribution = distr_item.createDistribution(scale);

    RealLimits limits = RealLimits::limitless();
    if (distr_item.isTag(DistributionItem::P_LIMITS)) {
        auto& limitsItem = distr_item.groupItem<RealLimitsItem>(DistributionItem::P_LIMITS);
        limits = limitsItem.createRealLimits(scale);
    }

    int nbr_samples = distr_item.getItemValue(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigma_factor = distr_item.isTag(DistributionItem::P_SIGMA_FACTOR)
                              ? distr_item.getItemValue(DistributionItem::P_SIGMA_FACTOR).toDouble()
                              : 0.0;
    ParameterDistribution par_distr(domain_par, *P_distribution, static_cast<size_t>(nbr_samples),
                                    sigma_factor, limits);

    for (auto name : domainLinkedParameters())
        par_distr.linkParameter(name);

    auto result = std::make_unique<ParticleDistribution>(*P_particle, par_distr);
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    result->setAbundance(abundance);
    return result;
}

void ParticleDistributionItem::setDomainCacheNames(const QString& name, const QStringList& linked)
{
    m_domain_cache_name = name;
    m_linked_names = linked;
}

void ParticleDistributionItem::updateMainParameterList()
{
    if (!isTag(P_DISTRIBUTED_PARAMETER))
        return;

    QString currentValue = getItemValue(P_DISTRIBUTED_PARAMETER).value<ComboProperty>().getValue();

    if (!m_domain_cache_name.isEmpty() && childParticle()) {
        QString guiName = translateParameterNameToGUI(m_domain_cache_name);
        if (!guiName.isEmpty()) { // might be empty because item was not fully constructed yet
            currentValue = guiName;
            m_domain_cache_name.clear();
        }
    }

    QStringList par_names = QStringList() << NO_SELECTION << childParameterNames();
    ComboProperty newProp = ComboProperty::fromList(par_names, NO_SELECTION);

    if (newProp.getValues().contains(currentValue))
        newProp.setValue(currentValue);

    setItemValue(P_DISTRIBUTED_PARAMETER, newProp.variant());
}

void ParticleDistributionItem::updateLinkedParameterList()
{
    if (!isTag(P_LINKED_PARAMETER) || !isTag(P_DISTRIBUTED_PARAMETER))
        return;

    QString mainValue = getItemValue(P_DISTRIBUTED_PARAMETER).value<ComboProperty>().getValue();

    QStringList par_names = childParameterNames();
    par_names.removeAll(mainValue);

    ComboProperty linkedProp = getItemValue(P_LINKED_PARAMETER).value<ComboProperty>();
    QStringList currentValues = linkedProp.selectedValues();

    if (!m_linked_names.isEmpty() && childParticle()) {
        QStringList domainValues;
        for (auto par : m_linked_names) {
            QString guiName = translateParameterNameToGUI(par);
            if (!guiName.isEmpty())
                domainValues.append(guiName);
        }
        if (!domainValues.isEmpty()) {
            currentValues = domainValues;
            m_linked_names.clear();
        }
    }

    ComboProperty newProp = ComboProperty::fromList(par_names);
    for (auto name : currentValues)
        newProp.setSelected(name, true);

    setItemValue(P_LINKED_PARAMETER, newProp.variant());
}

QStringList ParticleDistributionItem::childParameterNames() const
{
    if (auto child = childParticle()) {
        auto result = ParameterTreeUtils::parameterTreeNames(child);
        result.removeAll(ParticleItem::P_ABUNDANCE);
        return result;
    }

    return {};
}

QString ParticleDistributionItem::translateParameterNameToGUI(const QString& domainName)
{
    if (auto child = childParticle())
        return ParameterTreeUtils::domainNameToParameterName(domainName, child);
    return {};
}

const SessionItem* ParticleDistributionItem::childParticle() const
{
    if (getItems(T_PARTICLES).size() == 0)
        return nullptr;

    ASSERT(getItems(T_PARTICLES).size() == 1);
    return getItems(T_PARTICLES).front();
}

std::string ParticleDistributionItem::domainMainParameter() const
{
    auto par_name = getItemValue(P_DISTRIBUTED_PARAMETER).value<ComboProperty>().getValue();
    return ParameterTreeUtils::parameterNameToDomainName(par_name, childParticle()).toStdString();
}

std::vector<std::string> ParticleDistributionItem::domainLinkedParameters() const
{
    std::vector<std::string> result;
    auto linked_names = getItemValue(P_LINKED_PARAMETER).value<ComboProperty>().selectedValues();
    for (auto name : linked_names) {
        auto translated = ParameterTreeUtils::parameterNameToDomainName(name, childParticle());
        if (!translated.isEmpty())
            result.push_back(translated.toStdString());
    }
    return result;
}
