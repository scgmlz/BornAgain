// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INode.cpp
//! @brief     Implements class INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "INode.h"
#include "Exceptions.h"
#include "NodeUtils.h"
#include "NodeIterator.h"
#include "IterationStrategy.h"
#include "ParameterPool.h"
#include <algorithm>

INode::INode()
    : m_parent(nullptr)
{}

std::string INode::treeToString() const
{
    return NodeUtils::nodeToString(*this);
}

void INode::registerChild(INode *node)
{
    if(!node)
        throw Exceptions::NullPointerException("INode::registerChild -> Error. Null pointer.");
    node->setParent(this);
}

std::vector<const INode *> INode::getChildren() const
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
    if(node->parent() != this)
        return -1;

    int result(-1), count(0);
    for (auto child : getChildren()) {

        if(child == nullptr)
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
        const INode *child = it.getCurrent();
        const std::string path = NodeUtils::nodePath(*child, this->parent()) + "/";
        child->parameterPool()->copyToExternalPool(path, result.get());
        it.next();
    }

    return result.release();
}
