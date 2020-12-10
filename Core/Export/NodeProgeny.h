//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/NodeProgeny.h
//! @brief     Defines namespace node_progeny.
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
#ifndef BORNAGAIN_CORE_EXPORT_NODEPROGENY_H
#define BORNAGAIN_CORE_EXPORT_NODEPROGENY_H

#include "Param/Node/INode.h"

namespace node_progeny {

template <typename T> std::vector<const T*> ChildNodesOfType(const INode& node) {
    std::vector<const T*> result;
    for (const auto& p_child : node.getChildren()) {
        if (const auto* t = dynamic_cast<const T*>(p_child))
            result.push_back(t);
    }
    return result;
}

template <typename T> const T* OnlyChildOfType(const INode& node) {
    const auto list = ChildNodesOfType<T>(node);
    if (list.size() != 1)
        return nullptr;
    return list.front();
}

template <typename T> std::vector<const T*> AllDescendantsOfType(const INode& node) {
    std::vector<const T*> result;
    for (const auto* p_child : node.getChildren()) {
        if (const auto* t = dynamic_cast<const T*>(p_child))
            result.push_back(t);
        for (const auto* t : AllDescendantsOfType<T>(*p_child))
            result.push_back(t);
    }
    return result;
}

} // namespace node_progeny

#endif // BORNAGAIN_CORE_EXPORT_NODEPROGENY_H
#endif // USER_API
