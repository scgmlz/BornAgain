// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/INodeUtils.h
//! @brief     Defines namespace INodeUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INODEUTILS_H
#define INODEUTILS_H

#include "INode.h"

namespace INodeUtils {
template<typename T> std::vector<const T*> ChildNodesOfType(const INode& node) {
    std::vector<const T*> result;
    for (auto p_child : node.getChildren()) {
        if (auto t = dynamic_cast<const T*>(p_child))
            result.push_back(t);
    }
    return result;
}

template<typename T> const T* OnlyChildOfType(const INode& node) {
    auto list = ChildNodesOfType<T>(node);
    if (list.size()!=1) return nullptr;
    return list.front();
}

template<typename T> std::vector<const T*> AllDescendantsOfType(const INode& node) {
    std::vector<const T*> result;
    for (auto p_child : node.getChildren()) {
        if (auto t = dynamic_cast<const T*>(p_child))
            result.push_back(t);
        for (auto t : AllDescendantsOfType<T>(*p_child))
            result.push_back(t);
    }
    return result;
}
}


#endif // INODEUTILS_H
