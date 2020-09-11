// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTranslators.cpp
//! @brief     Implements subclasses of IParameterTranslator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ParameterTranslators.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
const QStringList expectedRoughnessPars =
    QStringList() << QString::fromStdString("Sigma") << QString::fromStdString("Hurst")
                  << QString::fromStdString("CorrelationLength");
}

IPathTranslator::~IPathTranslator() {}

ModelTypeTranslator::ModelTypeTranslator(QString gui_model_type, QString domain_name)
    : m_gui_model_type{std::move(gui_model_type)}, m_domain_name{std::move(domain_name)}
{
}

ModelTypeTranslator* ModelTypeTranslator::clone() const
{
    return new ModelTypeTranslator(m_gui_model_type, m_domain_name);
}

QStringList ModelTypeTranslator::translate(const QStringList& list) const
{
    if (list.back() != m_gui_model_type)
        return list;

    QStringList result = list;
    result.removeLast();
    result << m_domain_name;
    return result;
}

AddElementTranslator::AddElementTranslator(QString gui_name, QString additional_name)
    : m_gui_name{std::move(gui_name)}, m_additional_name{std::move(additional_name)}
{
}

AddElementTranslator* AddElementTranslator::clone() const
{
    return new AddElementTranslator(m_gui_name, m_additional_name);
}

QStringList AddElementTranslator::translate(const QStringList& list) const
{
    if (list.back() != m_gui_name)
        return list;

    QStringList result = list;
    result << m_additional_name;
    return result;
}

QStringList RotationTranslator::translate(const QStringList& list) const
{
    if (list.back() != "Rotation")
        return list;

    ASSERT(list.size() == 3);
    QStringList result = list;
    result.removeLast();
    return result;
}

QStringList DistributionNoneTranslator::translate(const QStringList& list) const
{
    if (list.back() != "DistributionNone")
        return list;

    Q_UNUSED(list);
    return QStringList(); // removing "DistributionNone/Value"
}

//! Converts "/Layer1/LayerBasicRoughness/Sigma" into "/LayerInterface0/LayerBasicRoughness/Sigma"

RoughnessTranslator::RoughnessTranslator(const SessionItem* p_parent) : mp_parent(p_parent) {}

RoughnessTranslator* RoughnessTranslator::clone() const
{
    return new RoughnessTranslator(mp_parent);
}

QStringList RoughnessTranslator::translate(const QStringList& list) const
{
    if (list.empty())
        return {};

    if (!list.back().contains("Layer") || !expectedRoughnessPars.contains(list.front()))
        return list;

    QStringList result = list;

    QString layerName = result.takeLast();
    int layerIndex = getLayerIndex(layerName);
    QString postfix = numberOfLayers() == 2 ? QString() : QString::number(layerIndex - 1);

    result.push_back(QString::fromStdString("LayerInterface") + postfix);
    return result;
}

//! Extract layer index from the string "Layer11"

int RoughnessTranslator::getLayerIndex(QString layerName) const
{
    layerName.remove("Layer");
    bool ok(true);
    int layerIndex = layerName.toInt(&ok);
    if (!ok)
        throw GUIHelpers::Error("RoughnessTranslator::getLayerIndex() -> Error. Can't parse.");
    return layerIndex;
}

int RoughnessTranslator::numberOfLayers() const
{
    QVector<SessionItem*> list = mp_parent->getChildrenOfType("Layer");
    return list.size();
}

VectorParameterTranslator::VectorParameterTranslator(QString gui_name, std::string base_name,
                                                     QStringList additional_names)
    : m_gui_name{std::move(gui_name)}, m_base_name{std::move(base_name)},
      m_additional_names{std::move(additional_names)}
{
}

VectorParameterTranslator* VectorParameterTranslator::clone() const
{
    return new VectorParameterTranslator(m_gui_name, m_base_name, m_additional_names);
}

QStringList VectorParameterTranslator::translate(const QStringList& list) const
{
    if (list.empty())
        return {};

    if (list.back() != m_gui_name)
        return list;

    ASSERT(list.size() == 2);

    QStringList result;
    if (list.front() == VectorItem::P_X) {
        result << QString::fromStdString(IParameterized::XComponentName(m_base_name));
    } else if (list.front() == VectorItem::P_Y) {
        result << QString::fromStdString(IParameterized::YComponentName(m_base_name));
    } else if (list.front() == VectorItem::P_Z) {
        result << QString::fromStdString(IParameterized::ZComponentName(m_base_name));
    } else {
        GUIHelpers::Error("VectorParameterTranslator::translate() -> Unexpected list structure");
    }
    for (auto add_name : m_additional_names) {
        result << add_name;
    }
    return result;
}
