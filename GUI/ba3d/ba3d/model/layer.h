// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/ba3d/model/layer.h
//! @brief     Defines Layer class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_LAYER_H
#define BA3D_LAYER_H

#include "object.h"

namespace RealSpace {

// particle layer: a transparent box
class Layer : public Object
{
public:
    Layer(VectorRange);
};
}  // namespace RealSpace
#endif  // BA3D_LAYER_H
