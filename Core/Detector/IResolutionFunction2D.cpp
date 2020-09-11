// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IResolutionFunction2D.cpp
//! @brief     Defines interface class IResolutionFunction2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/IResolutionFunction2D.h"

IResolutionFunction2D::IResolutionFunction2D(const NodeMeta& meta,
                                             const std::vector<double>& PValues)
    : INode(meta, PValues)
{
}
