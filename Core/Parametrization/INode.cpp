// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INode.cpp
//! @brief     Implements class INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/INode.h"
#include "Core/Basics/Algorithms.h"
#include "Core/Basics/Assert.h"
#include "Core/Parametrization/IterationStrategy.h"
#include "Core/Parametrization/NodeIterator.h"
#include "Core/Parametrization/NodeUtils.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include <algorithm>
#include <exception>

NodeMeta nodeMetaUnion(const std::vector<ParaMeta>& base, const NodeMeta& other)
{
    return {other.className, other.tooltip, algo::concat(base, other.paraMeta)};
}

INode::INode(const NodeMeta& meta, const std::vector<double>& PValues)
    : /*m_tooltip(meta.tooltip),*/
      m_NP(meta.paraMeta.size())
{
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

std::string INode::treeToString() const
{
    return NodeUtils::nodeToString(*this);
}

void INode::registerChild(INode* node)
{
    ASSERT(node);
    node->setParent(this);
}

std::vector<const INode*> INode::getChildren() const
{
    return {};
}

void INode::setParent(const INode* newParent)
{
    m_parent = newParent;
}

const INode* INode::parent() const
{
    return m_parent;
}

INode* INode::parent()
{
    return const_cast<INode*>(m_parent);
}

int INode::copyNumber(const INode* node) const
{
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

std::string INode::displayName() const
{
    std::string result = getName();
    if (m_parent) {
        int index = m_parent->copyNumber(this);
        if (index >= 0)
            result = result + std::to_string(index);
    }
    return result;
}

ParameterPool* INode::createParameterTree() const
{
    std::unique_ptr<ParameterPool> result(new ParameterPool);

    NodeIterator<PreorderStrategy> it(this);
    it.first();
    while (!it.isDone()) {
        const INode* child = it.getCurrent();
        const std::string path = NodeUtils::nodePath(*child, this->parent()) + "/";
        child->parameterPool()->copyToExternalPool(path, result.get());
        it.next();
    }

    return result.release();
}
