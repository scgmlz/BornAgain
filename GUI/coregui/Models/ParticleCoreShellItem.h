// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleCoreShellItem.h
//! @brief     Defines class ParticleCoreShellItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARTICLECORESHELLITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARTICLECORESHELLITEM_H

#include "GUI/coregui/Models/SessionGraphicsItem.h"

class ParticleCoreShell;

class BA_CORE_API_ ParticleCoreShellItem : public SessionGraphicsItem
{
public:
    const static QString T_CORE;
    const static QString T_SHELL;
    ParticleCoreShellItem();
    std::unique_ptr<ParticleCoreShell> createParticleCoreShell() const;
    QVector<SessionItem*> materialPropertyItems();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARTICLECORESHELLITEM_H
