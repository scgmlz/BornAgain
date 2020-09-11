// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/model.h
//! @brief     Defines Model class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_BA3D_MODEL_MODEL_H
#define BORNAGAIN_GUI_BA3D_MODEL_MODEL_H

#include "GUI/ba3d/model/object.h"
#include "GUI/ba3d/model/particles.h"
#include "GUI/ba3d/view/camera.h"
#include <QVector>

namespace RealSpace
{
//------------------------------------------------------------------------------

class Canvas;
class Object;

class Model : public QObject
{
    Q_OBJECT
    friend class Canvas;
    friend class Camera;
    friend class Object;

public:
    Model();
    virtual ~Model();

    void clearOpaque();
    void clearBlend();

    static Particles::Particle* newParticle(Particles::EShape k, float R);

    void add(Object*);      // add an opaque object, the model takes ownership
    void addBlend(Object*); // add a transparent object, the model takes ownership
    void rem(Object*);      // removes an object, the caller becomes responsible

    void releaseGeometries(); // may be called any time

    bool modelIsEmpty();

    virtual void cameraUpdated(Camera const&) {}

    Camera::Position defCamPos; // default camera params

signals:
    void updated(bool withEye);

private:
    QVector<Object*> objects, objectsBlend;

    void draw(Canvas&) const;
    void drawBlend(Canvas&) const;
};

} // namespace RealSpace
#endif // BORNAGAIN_GUI_BA3D_MODEL_MODEL_H
