// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Node/INodeVisitor.cpp
//! @brief     Implements class INodeVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Param/Base/IterationStrategy.h"
#include "Param/Node/NodeIterator.h"

void VisitNodesPreorder(const INode& node, INodeVisitor& visitor)
{
    NodeIterator<PreorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode* child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void VisitNodesPostorder(const INode& node, INodeVisitor& visitor)
{
    NodeIterator<PostorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode* child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}
