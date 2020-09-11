// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemCatalog.h
//! @brief     Defines class ItemCatalog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_ITEMCATALOG_H
#define BORNAGAIN_GUI_COREGUI_MODELS_ITEMCATALOG_H

#include "Fit/TestEngine/IFactory.h"
#include "Wrap/WinDllMacros.h"
#include <QStringList>
#include <memory>

class SessionItem;

//! Catalog of SessionItem%s. A single instance is created and used in ItemFactory.cpp.

class BA_CORE_API_ ItemCatalog
{
public:
    ItemCatalog();

    std::unique_ptr<SessionItem> createItemPtr(const QString& modelType) const;

    static QStringList validTopItemTypes();

private:
    void add(const QString& modelType, std::function<SessionItem*()> f);

    IFactory<QString, SessionItem> m_data;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_ITEMCATALOG_H
