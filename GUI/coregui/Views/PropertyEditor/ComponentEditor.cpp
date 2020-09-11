// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentEditor.cpp
//! @brief     Implements ComponentEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/Views/InfoWidgets/GroupInfoBox.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentFlatView.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentTreeView.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentView.h"
#include <QBoxLayout>
#include <QGroupBox>

namespace
{

template <typename T> T* createGroupBox(ComponentView* componentView, QString title)
{
    auto box = new T(title);
    auto boxlayout = new QVBoxLayout;
    boxlayout->setContentsMargins(0, 0, 0, 0);
    boxlayout->addWidget(componentView);
    box->setLayout(boxlayout);
    return box;
}
} // namespace

ComponentEditor::ComponentEditor(EditorType editorType, const QString& title)
    : m_type(editorType), m_componentView(nullptr), m_item(nullptr), m_title(title)
{
    m_componentView = createComponentView();

    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    if (m_type.testFlag(GroupLayout)) {
        auto box = createGroupBox<QGroupBox>(m_componentView, title);
        mainLayout->addWidget(box);
        mainLayout->setMargin(4);
        mainLayout->addStretch();

    } else if (m_type.testFlag(InfoLayout)) {
        auto box = createGroupBox<GroupInfoBox>(m_componentView, title);
        connect(box, &GroupInfoBox::clicked, this, &ComponentEditor::onDialogRequest);
        mainLayout->addWidget(box);
        mainLayout->setMargin(4);
        mainLayout->addStretch();

    } else {
        mainLayout->addWidget(m_componentView);
    }

    setLayout(mainLayout);
}

void ComponentEditor::setItem(SessionItem* item)
{
    m_item = item;
    m_componentView->setItem(item);
}

void ComponentEditor::clearEditor()
{
    m_item = nullptr;
    m_componentView->clearEditor();
}

void ComponentEditor::addItem(SessionItem* item)
{
    if (!m_item)
        m_item = item;
    m_componentView->addItem(item);
}

void ComponentEditor::onDialogRequest()
{
    emit dialogRequest(m_item, m_title);
}

ComponentView* ComponentEditor::createComponentView()
{
    ComponentView* result(nullptr);

    if (m_type.testFlag(Tree)) {
        auto view = new ComponentTreeView;
        view->setShowHeader(m_type.testFlag(T_Header));
        view->setShowRootItem(m_type.testFlag(T_Root));
        result = view;
    } else {
        auto view = new ComponentFlatView;
        view->setShowChildren(!m_type.testFlag(W_NoChildren));
        result = view;
    }

    return result;
}
