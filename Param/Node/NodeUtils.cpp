//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Node/NodeUtils.cpp
//! @brief     Implements collection of utility functions for INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Param/Node/NodeUtils.h"
#include "Base/Utils/Assert.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Param/Node/INode.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>

namespace {

// Returns string filled with '.'
std::string s_indent(int depth) {
    const int multiplier = 4;
    return std::string(multiplier * depth, '.');
}

// Returns single line string representing pool parameters of given node.
std::string poolToString(const INode& node) {
    std::ostringstream result;

    const std::vector<RealParameter*> pars = node.parameterPool()->parameters();
    if (pars.empty())
        return {};

    result << " (";
    size_t index(0);
    for (auto par : pars) {
        result << "'" << par->getName() << "':" << par->value();
        ++index;
        if (index != pars.size())
            result << " ";
    }
    result << ")";

    return result.str();
}

// Returns a string representing given node.
std::string nodeString(const INode& node, int depth) {
    std::ostringstream result;
    result << s_indent(depth) << node.displayName() << poolToString(node) << "\n";
    return result.str();
}
} // namespace

//  ************************************************************************************************
//  namespace NodeUtils
//  ************************************************************************************************

std::vector<std::tuple<const INode*, int, const INode*>> NodeUtils::progenyPlus(const INode* node,
                                                                                int level) {
    std::vector<std::tuple<const INode*, int, const INode*>> result;
    result.push_back({node, level, nullptr});
    for (const auto* child : node->getChildren()) {
        for (const auto& [subchild, sublevel, subparent] : progenyPlus(child, level + 1))
            result.push_back({subchild, sublevel, child});
    }
    return result;
}

std::string NodeUtils::nodeToString(const INode* node) {
    std::ostringstream result;
    for (const auto& [child, depth, parent] : progenyPlus(node))
        result << nodeString(*child, depth);
    return result.str();
}

std::string NodeUtils::nodePath(const INode* node, const INode* root) {
    std::vector<std::string> pathElements;
    const INode* current = node;
    while (current && current != root) {
        pathElements.push_back(current->displayName());
        pathElements.push_back("/");
        current = current->parent();
    }
    if (root != nullptr && current != root)
        throw std::runtime_error("NodeUtils::nodePath() -> Error. Node doesn't "
                                 "belong to root's branch");
    std::reverse(pathElements.begin(), pathElements.end());
    std::ostringstream result;
    std::copy(pathElements.begin(), pathElements.end(), std::ostream_iterator<std::string>(result));
    return result.str();
}
