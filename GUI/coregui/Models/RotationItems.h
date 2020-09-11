// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RotationItems.h
//! @brief     Defines class RotationItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_ROTATIONITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_ROTATIONITEMS_H

#include "GUI/coregui/Models/SessionItem.h"
#include "Wrap/WinDllMacros.h"

class IRotation;

class BA_CORE_API_ RotationItem : public SessionItem
{
public:
    explicit RotationItem(const QString& name) : SessionItem(name) {}
    virtual std::unique_ptr<IRotation> createRotation() const = 0;
};

class BA_CORE_API_ XRotationItem : public RotationItem
{
public:
    static const QString P_ANGLE;
    XRotationItem();
    std::unique_ptr<IRotation> createRotation() const;
};

class BA_CORE_API_ YRotationItem : public RotationItem
{
public:
    static const QString P_ANGLE;
    YRotationItem();
    std::unique_ptr<IRotation> createRotation() const;
};

class BA_CORE_API_ ZRotationItem : public RotationItem
{
public:
    static const QString P_ANGLE;
    ZRotationItem();
    std::unique_ptr<IRotation> createRotation() const;
};

class BA_CORE_API_ EulerRotationItem : public RotationItem
{
public:
    static const QString P_ALPHA;
    static const QString P_BETA;
    static const QString P_GAMMA;
    EulerRotationItem();
    std::unique_ptr<IRotation> createRotation() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_ROTATIONITEMS_H
