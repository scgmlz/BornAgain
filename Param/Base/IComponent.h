//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Base/IComponent.h
//! @brief     Defines interface IComponent.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_PARAM_BASE_ICOMPONENT_H
#define BORNAGAIN_PARAM_BASE_ICOMPONENT_H

//! Root of class hierarchy for sample and instrument model.

class IComponent {
public:
    virtual ~IComponent() {}
};

#endif // BORNAGAIN_PARAM_BASE_ICOMPONENT_H
#endif // USER_API
