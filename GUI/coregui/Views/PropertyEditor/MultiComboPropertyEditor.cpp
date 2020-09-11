// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/MultiComboPropertyEditor.cpp
//! @brief     Defines MultiComboPropertyEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/MultiComboPropertyEditor.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/utils/CustomEventFilters.h"
#include <QComboBox>
#include <QEvent>
#include <QLineEdit>
#include <QListView>
#include <QMouseEvent>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QVBoxLayout>

QCheckListStyledItemDelegate::QCheckListStyledItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void QCheckListStyledItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    QStyleOptionViewItem& styleOption = const_cast<QStyleOptionViewItem&>(option);
    styleOption.showDecorationSelected = false;
    QStyledItemDelegate::paint(painter, styleOption, index);
}

// ----------------------------------------------------------------------------
// https://stackoverflow.com/questions/8422760/combobox-of-checkboxes
// https://stackoverflow.com/questions/21186779/catch-mouse-button-pressed-signal-from-qcombobox-popup-menu
// https://gist.github.com/mistic100/c3b7f3eabc65309687153fe3e0a9a720
// ----------------------------------------------------------------------------

MultiComboPropertyEditor::MultiComboPropertyEditor(QWidget* parent)
    : CustomEditor(parent), m_box(new QComboBox), m_wheel_event_filter(new WheelEventEater(this)),
      m_model(new QStandardItemModel(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_box->installEventFilter(m_wheel_event_filter);
    m_box->view()->viewport()->installEventFilter(this);

    // Editable mode will be used to have None/Multiple labels on top
    m_box->setEditable(true);
    m_box->lineEdit()->setReadOnly(true);
    m_box->lineEdit()->installEventFilter(this);
    connect(m_box->lineEdit(), &QLineEdit::selectionChanged, m_box->lineEdit(),
            &QLineEdit::deselect);

    // transforms ordinary combo box into check list
    m_box->setItemDelegate(new QCheckListStyledItemDelegate(this));
    m_box->setModel(m_model);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);
    setConnected(true);
}

QSize MultiComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize MultiComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

//! Propagate check state from the model to ComboProperty.

void MultiComboPropertyEditor::onModelDataChanged(const QModelIndex& topLeft, const QModelIndex&,
                                                  const QVector<int>&)
{
    // on Qt 5.9 roles remains empty for checked state. It will stop working if uncomment.
    //    if (!roles.contains(Qt::CheckStateRole))
    //        return;

    auto item = m_model->itemFromIndex(topLeft);
    if (!item)
        return;

    ComboProperty comboProperty = m_data.value<ComboProperty>();
    auto state = item->checkState() == Qt::Checked ? true : false;
    comboProperty.setSelected(topLeft.row(), state);

    updateBoxLabel();
    setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
}

//! Processes press event in QComboBox's underlying list view.

void MultiComboPropertyEditor::onClickedList(const QModelIndex& index)
{
    if (auto item = m_model->itemFromIndex(index)) {
        auto state = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
        item->setCheckState(state);
    }
}

//! Handles mouse clicks on QComboBox elements.

bool MultiComboPropertyEditor::eventFilter(QObject* obj, QEvent* event)
{
    if (isClickToSelect(obj, event)) {
        // Handles mouse clicks on QListView when it is expanded from QComboBox
        // 1) Prevents list from closing while selecting items.
        // 2) Correctly calculates underlying model index when mouse is over check box style
        // element.
        const auto mouseEvent = static_cast<const QMouseEvent*>(event);
        auto index = m_box->view()->indexAt(mouseEvent->pos());
        onClickedList(index);
        return true;

    } else if (isClickToExpand(obj, event)) {
        // Expands box when clicking on None/Multiple label
        m_box->showPopup();
        return true;

    } else {
        // Propagate to the parent class.
        return QObject::eventFilter(obj, event);
    }
}

void MultiComboPropertyEditor::initEditor()
{
    if (!m_data.canConvert<ComboProperty>())
        return;

    ComboProperty property = m_data.value<ComboProperty>();

    setConnected(false);
    m_model->clear();

    auto labels = property.getValues();
    auto selectedIndices = property.selectedIndices();

    for (int i = 0; i < labels.size(); ++i) {
        auto item = new QStandardItem(labels[i]);
        m_model->invisibleRootItem()->appendRow(item);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setCheckable(true);

        auto state = selectedIndices.contains(i) ? Qt::Checked : Qt::Unchecked;
        item->setData(state, Qt::CheckStateRole);
    }

    setConnected(true);
    updateBoxLabel();
}

void MultiComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_model, &QStandardItemModel::dataChanged, this,
                &MultiComboPropertyEditor::onModelDataChanged);
    } else {
        disconnect(m_model, &QStandardItemModel::dataChanged, this,
                   &MultiComboPropertyEditor::onModelDataChanged);
    }
}

//! Update text on QComboBox with the label provided by combo property.

void MultiComboPropertyEditor::updateBoxLabel()
{
    ComboProperty combo = m_data.value<ComboProperty>();
    m_box->setCurrentText(combo.label());
}

bool MultiComboPropertyEditor::isClickToSelect(QObject* obj, QEvent* event) const
{
    return obj == m_box->view()->viewport() && event->type() == QEvent::MouseButtonRelease;
}

bool MultiComboPropertyEditor::isClickToExpand(QObject* obj, QEvent* event) const
{
    return obj == m_box->lineEdit() && event->type() == QEvent::MouseButtonRelease;
}
