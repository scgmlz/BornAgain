// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h
//! @brief     Defines class RealSpaceBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACEBUILDER_H
#define REALSPACEBUILDER_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QVector3D>
#include "../../ba3d/ba3d/view/camera.h"

class SessionItem;
class RealSpaceModel;
class Shape3D;
class SceneGeometry;
class Particle3DType;

class BA_CORE_API_ RealSpaceBuilder : public QWidget
{
    Q_OBJECT

public:
    RealSpaceBuilder(QWidget* parent = nullptr);

    ~RealSpaceBuilder();

    void populate(RealSpaceModel* model, const SessionItem& item,
                  const SceneGeometry& sceneGeometry,
                  const RealSpace::Camera::Position &cameraPosition =
                            RealSpace::Camera::Position(RealSpace::Vector3D(0, -140, 90),  // eye
                                                        RealSpace::Vector3D(0, 0, 0),      // center
                                                        RealSpace::Vector3D::_z));         // up

    void populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                            const SceneGeometry& sceneGeometry,
                            const QVector3D& origin = QVector3D());

    void populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                       const SceneGeometry& sceneGeometry, const QVector3D& origin = QVector3D());

    void populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                        const SceneGeometry& sceneGeometry, const QVector3D& origin = QVector3D());

    void populateInterference(RealSpaceModel* model, const SessionItem& layoutItem,
                                QVector<Particle3DType> &particle3DType_vector,
                                const SceneGeometry& sceneGeometry);

    void populateParticleFromParticleItem(RealSpaceModel* model, const SessionItem& particleItem,
                                          const QVector3D& origin = QVector3D()) const;

    void populateParticleFromParticle3DType(RealSpaceModel* model,
                                            const Particle3DType &particle3DType,
                                            const QVector3D& lattice_position) const;

};

#endif // REALSPACEBUILDER_H
