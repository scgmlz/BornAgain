// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceView.h
//! @brief     Defines class RealSpaceView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEVIEW_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class RealSpaceModel;

namespace RealSpace
{
class Widget3D;
class Camera;
} // namespace RealSpace

//! Contains 3D view.

class BA_CORE_API_ RealSpaceView : public QWidget
{
    Q_OBJECT

public:
    RealSpaceView(QWidget* parent = 0);

    void setModel(RealSpaceModel* model);

    void defaultView();
    void sideView();
    void topView();

    RealSpace::Camera& getCamera();

private:
    RealSpace::Widget3D* m_3dview;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEVIEW_H
