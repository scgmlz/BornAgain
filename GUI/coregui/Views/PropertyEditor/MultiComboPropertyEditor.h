// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/MultiComboPropertyEditor.h
//! @brief     Defines MultiComboPropertyEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_MULTICOMBOPROPERTYEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_MULTICOMBOPROPERTYEDITOR_H

#include "GUI/coregui/Views/PropertyEditor/CustomEditors.h"
#include <QStyledItemDelegate>
#include <memory>

class QStandardItemModel;
class QModelIndex;
class QStyleOptionViewItem;

//! Provides custom editor for ComboProperty with multi-select option.

class BA_CORE_API_ MultiComboPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit MultiComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected slots:
    void onModelDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&);

    void onClickedList(const QModelIndex& index);

protected:
    void initEditor();

private:
    bool eventFilter(QObject* obj, QEvent* event);
    void setConnected(bool isConnected);
    void updateBoxLabel();

    bool isClickToSelect(QObject* obj, QEvent* event) const;
    bool isClickToExpand(QObject* obj, QEvent* event) const;

    QComboBox* m_box;
    class WheelEventEater* m_wheel_event_filter;
    QStandardItemModel* m_model;
};

//! Provides custom style delegate for QComboBox to allow checkboxes.

class QCheckListStyledItemDelegate : public QStyledItemDelegate
{
public:
    QCheckListStyledItemDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_MULTICOMBOPROPERTYEDITOR_H
