// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FilterPropertyProxy.h
//! @brief     Defines class FilterPropertyProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //
#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FILTERPROPERTYPROXY_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FILTERPROPERTYPROXY_H

#include "Wrap/WinDllMacros.h"
#include <QSortFilterProxyModel>

//!
//! \brief The FilterPropertyProxy class filters out all PropertyItem's and similar from
//! SessionModel to have only top level items
//!

class BA_CORE_API_ FilterPropertyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterPropertyProxy(int columns, QObject* parent = 0)
        : QSortFilterProxyModel(parent), m_columns(columns)
    {
    }
    int columnCount(const QModelIndex& parent) const;

    static QModelIndex toSourceIndex(QModelIndex index);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;

private:
    int m_columns;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FILTERPROPERTYPROXY_H
