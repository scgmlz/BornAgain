// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo1/demo_model.h
//! @brief     Defines DemoModel class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_DEMOMODEL_H
#define BA3D_DEMOMODEL_H

#include "lattice.h"
#include <QAtomicInteger>
#include "GUI/ba3d/model/model.h"
#include "GUI/ba3d/model/particles.h"

class DemoModel : public RealSpace::Model
{
public:
    using super = RealSpace::Model;

    using Particle = RealSpace::Particles::Particle;
    using Camera = RealSpace::Camera;

    DemoModel();

    void switchBack();
    void switchFront();
    void switchOne();

    void square(float sigma);
    void one();
    void oneOut();
    void oneIn(RealSpace::Particles::EShape);

    void setCameraTop(bool animate = false);
    void setCameraSide(bool animate = false);
    void setCameraOne(bool animate = false);

    void setCamera(const Camera::Position&, bool animate = false);

    void cameraUpdated(Camera const&);

private:
    void addSubstrate();
    void addLayer();

    enum { backNONE, backSUBSTRATE, backLAYER } back = backNONE;
    enum {
        frontNONE,
        frontONE,
        frontSQUARELOW,
        frontSQUAREHIGH,
        frontSQUAREINSANE
    } front = frontNONE;

    float szSample = 400;
    float const spacing = 20; // of particles
    float const R = 6;
    float const hgtLayer = 20, hgtSubstrate = 35;

    Camera::Position camPos;

private:
    void addLayer(RealSpace::Range, QColor);

    QVector<Particle*> ps;
    Particle* p;
    RealSpace::Particles::EShape kind = RealSpace::Particles::EShape::None;

    Lattice activeMesh;

private:
    void snooze(bool withEye);
};

#endif // BA3D_DEMOMODEL_H
