// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleDistributionItem.h
//! @brief     Defines class ParticleDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARTICLEDISTRIBUTIONITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARTICLEDISTRIBUTIONITEM_H

#include "Core/Particle/ParticleDistribution.h"
#include "GUI/coregui/Models/SessionGraphicsItem.h"
#include <string>
#include <vector>

class BA_CORE_API_ ParticleDistributionItem : public SessionGraphicsItem
{
public:
    static const QString P_DISTRIBUTED_PARAMETER;
    static const QString P_LINKED_PARAMETER;
    static const QString P_DISTRIBUTION;
    static const QString NO_SELECTION;
    static const QString T_PARTICLES;
    ParticleDistributionItem();

    std::unique_ptr<ParticleDistribution> createParticleDistribution() const;

    void setDomainCacheNames(const QString& name, const QStringList& linked);

private:
    void updateMainParameterList();
    void updateLinkedParameterList();
    QStringList childParameterNames() const;
    QString translateParameterNameToGUI(const QString& domainName);
    const SessionItem* childParticle() const;

    std::string domainMainParameter() const;
    std::vector<std::string> domainLinkedParameters() const;

    QString m_domain_cache_name;
    QStringList m_linked_names;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARTICLEDISTRIBUTIONITEM_H
