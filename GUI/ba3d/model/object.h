// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/object.h
//! @brief     Defines Object class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_BA3D_MODEL_OBJECT_H
#define BORNAGAIN_GUI_BA3D_MODEL_OBJECT_H

#include "../def.h"
#include "GUI/ba3d/model/geometry_inc.h"
#include <QColor>
#include <QMatrix4x4>

namespace RealSpace
{

class Model;
class Canvas;

class Object
{
    friend class Model;

public:
    Object(GeometricID::Key);
    virtual ~Object();

    QColor color;

    void transform(float scale, Vector3D rotate, Vector3D translate);
    void transform(Vector3D scale, Vector3D rotate, Vector3D translate);
    void transform(Vector3D scale, QQuaternion, Vector3D translate);
    void transform(Vector3D turn, Vector3D scale, Vector3D rotate, Vector3D translate);

    void addExtrinsicRotation(Vector3D turn, Vector3D scale, Vector3D& rotate,
                              Vector3D rotateExtrinsic, Vector3D& translate);

protected:
    bool isNull;

private:
    Model* model;

    GeometricID::Key gky;
    GeometryHandle geo;     // retrieved on demand
    void releaseGeometry(); // can be released whenever

    QMatrix4x4 mat;
    void draw(Canvas&);
};

} // namespace RealSpace
#endif // BORNAGAIN_GUI_BA3D_MODEL_OBJECT_H
