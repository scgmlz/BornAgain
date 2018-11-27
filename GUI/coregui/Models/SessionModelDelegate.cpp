// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModelDelegate.cpp
//! @brief     Implements class SessionModelDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SessionModelDelegate.h"
#include "CustomEditors.h"
#include "CustomEventFilters.h"
#include "PropertyEditorFactory.h"
#include "ScientificSpinBox.h"
#include "SessionFlags.h"
#include "SessionItem.h"
#include <QApplication>
#include <QLocale>

namespace {

bool isDoubleProperty(const QModelIndex& index, Qt::ItemDataRole role = Qt::DisplayRole);
QWidget* createEditorFromIndex(const QModelIndex& index, QWidget* parent);
double getStep(double val);
}  // unnamed namespace

SessionModelDelegate::SessionModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void SessionModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const
{
    if (PropertyEditorFactory::IsCustomVariant(index.data())) {
        QString text = PropertyEditorFactory::ToString(index.data());
        paintCustomLabel(painter, option, index, text);
    } else if (isDoubleProperty(index)) {
        auto item = static_cast<SessionItem*>(index.internalPointer());
        paintCustomLabel(painter, option, index,
                         ScientificSpinBox::toString(item->value().toDouble(), item->decimals()));
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget* SessionModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                            const QModelIndex& index) const
{
    auto result = createEditorFromIndex(index, parent);

    if (result) {
        new TabFromFocusProxy(result);
        if(auto customEditor = dynamic_cast<CustomEditor*>(result)) {
            customEditor->setData(index.data());
            connect(customEditor, &CustomEditor::dataChanged,
                    this, &SessionModelDelegate::onCustomEditorDataChanged);
        }
    } else if (isDoubleProperty(index, Qt::EditRole)) {
        //compatible with default QStyledItemDelegate machinery
        result = new ScientificSpinBox(parent);
    } else
        result = QStyledItemDelegate::createEditor(parent, option, index);
    return result;
}

//! Propagates changed data from the editor to the model.

void SessionModelDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                        const QModelIndex& index) const
{
    auto customEditor = qobject_cast<CustomEditor*>(editor);
    if (index.column() == SessionFlags::ITEM_VALUE && customEditor)
        model->setData(index, customEditor->editorData());
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

//! Propagates the data change from the model to the editor (if it is still opened).

void SessionModelDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    auto customEditor = dynamic_cast<CustomEditor*>(editor);
    if (index.column() == SessionFlags::ITEM_VALUE && customEditor) {
        customEditor->setData(index.data());
        return;
    }

    if (auto spin_box = dynamic_cast<ScientificSpinBox*>(editor))
        spin_box->setSingleStep(getStep(index.data(Qt::EditRole).toDouble()));
    QStyledItemDelegate::setEditorData(editor, index);
}

//! Increases height of the row by 20% wrt the default.

QSize SessionModelDelegate::sizeHint(const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(static_cast<int>(result.height() * 1.2));
    return result;
}

//! Makes an editor occupying whole available space in a cell. If cell contains an icon
//! as a decoration (i.e. icon of material property), it will be hidden as soon as editor
//! up and running.

void SessionModelDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                                const QModelIndex& index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    editor->setGeometry(option.rect);
}

//! Notifies everyone that the editor has completed editing the data.

void SessionModelDelegate::onCustomEditorDataChanged(const QVariant& )
{
    CustomEditor* editor = qobject_cast<CustomEditor*>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);
}

//! Paints custom text in a a place corresponding given index.

void SessionModelDelegate::paintCustomLabel(QPainter* painter, const QStyleOptionViewItem& option,
                                            const QModelIndex& index, const QString& text) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index); // calling original method to take into accounts colors etc
    opt.text = displayText(text, option.locale); // by overriding text with ours
    const QWidget* widget = opt.widget;
    QStyle* style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
}

namespace {

bool isDoubleProperty(const QModelIndex& index, Qt::ItemDataRole role)
{
    return index.data(role).type() == QVariant::Double;
}

QWidget* createEditorFromIndex(const QModelIndex& index, QWidget* parent) {
    if (index.column() == SessionFlags::ITEM_VALUE && index.internalPointer()) {
        auto item = static_cast<SessionItem*>(index.internalPointer());
        return PropertyEditorFactory::CreateEditor(*item, parent);
    }
    return nullptr;
}

double getStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}
}  // unnamed namespace
