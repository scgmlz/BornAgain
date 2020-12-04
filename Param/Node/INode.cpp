//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Node/INode.cpp
//! @brief     Implements interface INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Param/Node/INode.h"
#include "Base/Utils/Algorithms.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Param/Node/NodeUtils.h"
#include <algorithm>
#include <exception>

NodeMeta nodeMetaUnion(const std::vector<ParaMeta>& base, const NodeMeta& other) {
    return {other.className, other.tooltip, algo::concat(base, other.paraMeta)};
}

INode::INode(const NodeMeta& meta, const std::vector<double>& PValues)
    : /*m_tooltip(meta.tooltip),*/
    m_NP(meta.paraMeta.size()) {
    m_P.resize(m_NP);
    setName(meta.className);
    parameterPool()->clear(); // non-trivially needed by a few children
    for (size_t i = 0; i < m_NP; ++i) {
        m_P[i] = PValues[i];
        const ParaMeta& pm = meta.paraMeta[i];
        auto& reg = registerParameter(pm.name, &m_P[i]);
        reg.setUnit(pm.unit);
        if (pm.vMin == -INF) {
            ASSERT(pm.vMax == +INF);
            // nothing to do
        } else if (pm.vMax == +INF) {
            ASSERT(pm.vMin == 0);
            reg.setNonnegative();
        } else {
            reg.setLimited(pm.vMin, pm.vMax);
        }
    }
}

std::string INode::treeToString() const {
    return NodeUtils::nodeToString(*this);
}

void INode::registerChild(INode* node) {
    ASSERT(node);
    node->setParent(this);
}

std::vector<const INode*> INode::getChildren() const {
    return {};
}

std::vector<const INode*> INode::progeny() const {
    std::vector<const INode*> result;
    result.push_back(this);
    for (const auto* child : getChildren()) {
        for (const auto* p : child->progeny())
            result.push_back(p);
    }
    return result;
}

std::vector<std::pair<const INode*, const INode*>> INode::progenyWithParent() const {
    std::vector<std::pair<const INode*, const INode*>> result;
    result.push_back({this, nullptr});
    for (const auto* child : getChildren()) {
        for (const auto* p : child->progeny())
            result.push_back({p, child});
    }
    return result;
}

void INode::setParent(const INode* newParent) {
    m_parent = newParent;
}

const INode* INode::parent() const {
    return m_parent;
}

INode* INode::parent() {
    return const_cast<INode*>(m_parent);
}

int INode::copyNumber(const INode* node) const {
    if (node->parent() != this)
        return -1;

    int result(-1), count(0);
    for (auto child : getChildren()) {

        if (child == nullptr)
            throw std::runtime_error("INode::copyNumber() -> Error. Nullptr as child.");

        if (child == node)
            result = count;

        if (child->getName() == node->getName())
            ++count;
    }

    return count > 1 ? result : -1;
}

std::string INode::displayName() const {
    std::string result = getName();
    if (m_parent) {
        int index = m_parent->copyNumber(this);
        if (index >= 0)
            result = result + std::to_string(index);
    }
    return result;
}

ParameterPool* INode::createParameterTree() const {
    std::unique_ptr<ParameterPool> result(new ParameterPool);

    for (const INode* child : progeny()) {
        const std::string path = NodeUtils::nodePath(*child, this->parent()) + "/";
        child->parameterPool()->copyToExternalPool(path, result.get());
    }

    return result.release();
}
