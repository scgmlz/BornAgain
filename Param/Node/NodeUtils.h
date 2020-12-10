//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Node/NodeUtils.h
//! @brief     Defines collection of utility functions for INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_PARAM_NODE_NODEUTILS_H
#define BORNAGAIN_PARAM_NODE_NODEUTILS_H

#include <string>
#include <vector>

class INode;

namespace NodeUtils {

//! Returns a vector of triples (descendant, depth, parent)
std::vector<std::tuple<const INode*, int, const INode*>> progenyPlus(const INode* node,
                                                                     int level = 0);

//! Returns multiline string representing tree structure starting from given node.
std::string nodeToString(const INode* node);

//! Returns path composed of node's displayName, with respect to root node
std::string nodePath(const INode* node, const INode* root = nullptr);

} // namespace NodeUtils

#endif // BORNAGAIN_PARAM_NODE_NODEUTILS_H
#endif // USER_API
