// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ViewTypes.h
//! @brief     Defines namespace ViewTypes with enum EWidgetTypes (nothing to implement)
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_VIEWTYPES_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_VIEWTYPES_H

#include <QGraphicsItem>

//! Type definition for graphics items.

namespace ViewTypes
{

enum EWidgetTypes {
    IVIEW = QGraphicsItem::UserType + 1, // = 65537
    ISAMPLE_RECT,
    NODE_EDITOR_PORT,
    NODE_EDITOR_CONNECTION,
    MULTILAYER,
    LAYER,
    PARTICLE_LAYOUT,
    INTERFERENCE_FUNCTION,
    INTERFERENCE_FUNCTION_1D_LATTICE,
    INTERFERENCE_FUNCTION_2D_LATTICE,
    INTERFERENCE_FUNCTION_2D_PARA,
    INTERFERENCE_FUNCTION_FINITE_2D_LATTICE,
    INTERFERENCE_FUNCTION_HARD_DISK,
    INTERFERENCE_FUNCTION_RADIAL_PARA,
    PARTICLE,
    TRANSFORMATION,
};

}

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_VIEWTYPES_H
