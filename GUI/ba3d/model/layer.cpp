// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/layer.cpp
//! @brief     Implements Layer class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/model/layer.h"

namespace RealSpace
{

Layer::Layer(VectorRange d) : Object(GeometricID::Key(GeometricID::BaseShape::Box))
{
    transform(d.size(), Vector3D::_0, d.mid());
}
} // namespace RealSpace
