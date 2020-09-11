// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/view/program.h
//! @brief     Defines Program class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_BA3D_VIEW_PROGRAM_H
#define BORNAGAIN_GUI_BA3D_VIEW_PROGRAM_H

#include "../def.h"
#include <QOpenGLShaderProgram>

namespace RealSpace
{

class Camera;
class Canvas;

class Program : public QOpenGLShaderProgram
{
    friend class Canvas;

public:
    Program();

private:
    void needsInit(); // mark as needed init
    void init();      // inits, if needed

    void set(Camera const&);
    void set(QColor const&);             // object color
    void set(QMatrix4x4 const&);         // set matObject
    void setMatModel(QMatrix4x4 const&); // set matModel
    void setAxis(bool const&);

    bool doInit;
    int locMatProj, locMatModel, locMatObject;
    int locLightPos1, locColor, ambient, eye;
    int locAxis;
};

} // namespace RealSpace
#endif // BORNAGAIN_GUI_BA3D_VIEW_PROGRAM_H
