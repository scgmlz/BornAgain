// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionDecorationModel.h
//! @brief     Defines class SessionDecorationModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SESSIONDECORATIONMODEL_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SESSIONDECORATIONMODEL_H

#include "Wrap/WinDllMacros.h"
#include <QIdentityProxyModel>

class SessionModel;
class SessionItem;

//! Provides decorations (text color, icons, etc) for SessionModel in SessionModelView context.
//! It is implemented as identity proxy model, so it has one-to-one data structure as in
//! source SessionModel.

class BA_CORE_API_ SessionDecorationModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit SessionDecorationModel(QObject* parent, SessionModel* model = nullptr);

    void setSessionModel(SessionModel* model);

    QVariant data(const QModelIndex& index, int role) const;

private:
    QVariant createIcon(const QModelIndex& index) const;
    QVariant textColor(const QModelIndex& index) const;

    SessionModel* m_model;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SESSIONDECORATIONMODEL_H
