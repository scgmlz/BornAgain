// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/layer.h
//! @brief     Defines Layer class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_BA3D_MODEL_LAYER_H
#define BORNAGAIN_GUI_BA3D_MODEL_LAYER_H

#include "GUI/ba3d/model/object.h"

namespace RealSpace
{

// particle layer: a transparent box
class Layer : public Object
{
public:
    Layer(VectorRange);
};
} // namespace RealSpace
#endif // BORNAGAIN_GUI_BA3D_MODEL_LAYER_H
