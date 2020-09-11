// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/widget.h
//! @brief     Defines Widget class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_BA3D_WIDGET_H
#define BORNAGAIN_GUI_BA3D_WIDGET_H

#include "GUI/ba3d/def.h"
#include <QWidget>

namespace RealSpace
{
//------------------------------------------------------------------------------

class Model;
class Canvas;
class Camera;
class Program;

class Widget3D : public QWidget
{
    Q_OBJECT
public:
    Widget3D();
    ~Widget3D();

    Camera& cam();

    void setBackground(QColor const&);
    void setModel(Model*); // model owned elsewhere, may be nullptr

    void defaultView();
    void sideView();
    void topView();

    Model* model();

private:
    Canvas* canvas;
};

//------------------------------------------------------------------------------
} // namespace RealSpace
#endif // BORNAGAIN_GUI_BA3D_WIDGET_H
