// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentFlatView.cpp
//! @brief     Implements class ComponentFlatView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/ComponentFlatView.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentUtils.h"
#include "GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.h"
#include "GUI/coregui/Views/PropertyEditor/PropertyWidgetItem.h"
#include "GUI/coregui/utils/LayoutUtils.h"
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

ComponentFlatView::ComponentFlatView(QWidget* parent)
    : ComponentView(parent), m_mainLayout(new QVBoxLayout), m_gridLayout(nullptr), m_model(nullptr),
      m_show_children(true)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_mainLayout->setMargin(10);
    m_mainLayout->setSpacing(0);

    initGridLayout();

    setLayout(m_mainLayout);
}

ComponentFlatView::~ComponentFlatView() = default;

void ComponentFlatView::setItem(SessionItem* item)
{
    clearEditor();

    m_topItems.push_back(item);
    setModel(item->model());
    updateItemProperties();
}

void ComponentFlatView::addItem(SessionItem* item)
{
    if (m_topItems.isEmpty()) {
        setItem(item);
        return;
    }
    m_topItems.push_back(item);
    updateItemProperties();
}

void ComponentFlatView::setModel(SessionModel* model)
{
    if (m_model) {
        disconnect(m_model, &SessionModel::dataChanged, this, &ComponentFlatView::onDataChanged);
    }
    m_model = model;
    if (m_model) {
        connect(m_model, &SessionModel::dataChanged, this, &ComponentFlatView::onDataChanged);
    }
}

void ComponentFlatView::clearLayout()
{
    ASSERT(m_gridLayout);
    LayoutUtils::clearGridLayout(m_gridLayout, false);

    for (auto widget : m_widgetItems)
        widget->deleteLater();
    m_widgetItems.clear();
}

void ComponentFlatView::setShowChildren(bool show)
{
    m_show_children = show;
}

void ComponentFlatView::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                                      const QVector<int>& roles)
{
    Q_UNUSED(bottomRight);
    SessionItem* item = m_model->itemForIndex(topLeft);
    ASSERT(item);
    if (item->modelType() == "GroupProperty")
        updateItemProperties();

    if (roles.contains(SessionFlags::FlagRole))
        updateItemRoles(item);
}

void ComponentFlatView::clearEditor()
{
    m_topItems.clear();
    clearLayout();
}

void ComponentFlatView::updateItemProperties()
{
    clearLayout();

    QList<const SessionItem*> allitems;
    for (auto item : m_topItems)
        allitems += ComponentUtils::componentItems(*item);

    int nrow(0);
    for (auto child : allitems) {
        auto widget = createWidget(child);
        if (!widget)
            continue;
        widget->addToGrid(m_gridLayout, ++nrow);
        m_widgetItems.push_back(widget);
        if (!m_show_children)
            break;
    }
}

void ComponentFlatView::updateItemRoles(SessionItem* item)
{
    for (auto widget : m_widgetItems)
        if (widget->item() == item)
            widget->updateItemRoles();
}

void ComponentFlatView::initGridLayout()
{
    delete m_gridLayout;
    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(6);
    m_mainLayout->addLayout(m_gridLayout);
    m_mainLayout->addStretch(1);
}

PropertyWidgetItem* ComponentFlatView::createWidget(const SessionItem* item)
{
    auto editor = PropertyEditorFactory::CreateEditor(*item);
    if (!editor)
        return nullptr;

    auto result = new PropertyWidgetItem(this);
    result->setItemEditor(item, editor);

    return result;
}
