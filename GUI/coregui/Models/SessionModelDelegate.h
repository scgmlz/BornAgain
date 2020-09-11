// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModelDelegate.h
//! @brief     Defines class SessionModelDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SESSIONMODELDELEGATE_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SESSIONMODELDELEGATE_H

#include "Wrap/WinDllMacros.h"
#include <QStyledItemDelegate>

//! The SessionModelDelegate class presents the content of SessionModel items in
//! standard QTreeView. Extents base QItemDelegate with possibility to show/edit
//! our custom QVariant's.

class BA_CORE_API_ SessionModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SessionModelDelegate(QObject* parent);

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

    void setEditorData(QWidget* editor, const QModelIndex& index) const;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const;

public slots:
    void onCustomEditorDataChanged(const QVariant&);

private:
    void paintCustomLabel(QPainter* painter, const QStyleOptionViewItem& option,
                          const QModelIndex& index, const QString& text) const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SESSIONMODELDELEGATE_H
