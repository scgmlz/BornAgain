// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/NodeUtils.h
//! @brief     Defines collection of utility functions for INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_NODEUTILS_H
#define BORNAGAIN_CORE_PARAMETRIZATION_NODEUTILS_H

#include "Wrap/WinDllMacros.h"
#include <string>

class INode;

namespace NodeUtils
{

//! Returns multiline string representing tree structure starting from given node.
BA_CORE_API_ std::string nodeToString(const INode& node);

//! Returns path composed of node's displayName, with respect to root node
BA_CORE_API_ std::string nodePath(const INode& node, const INode* root = nullptr);

} // namespace NodeUtils

#endif // BORNAGAIN_CORE_PARAMETRIZATION_NODEUTILS_H
