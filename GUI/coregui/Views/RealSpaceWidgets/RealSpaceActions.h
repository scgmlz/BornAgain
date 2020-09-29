// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceActions.h
//! @brief     Defines class RealSpaceActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEACTIONS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEACTIONS_H

#include <QObject>

//! Collection of actions for RealSpaceWidget.

class RealSpaceActions : public QObject
{
    Q_OBJECT

public:
    RealSpaceActions(QObject* parent = 0);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEACTIONS_H
