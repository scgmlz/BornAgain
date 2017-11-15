// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeView.cpp
//! @brief     Implements class ComponentTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentTreeView.h"
#include "ComponentProxyModel.h"
#include "StyleUtils.h"
#include "SessionModelDelegate.h"
#include "SessionModel.h"
#include <QTreeView>
#include <QBoxLayout>

ComponentTreeView::ComponentTreeView(QWidget* parent)
    : QWidget(parent)
    , m_tree(new QTreeView)
    , m_delegate(new SessionModelDelegate(this))
    , m_proxyModel(new ComponentProxyModel(this))
{
    auto layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_tree);

    setLayout(layout);

    StyleUtils::setPropertyStyle(m_tree);
    m_tree->setRootIsDecorated(false);
    m_tree->setModel(m_proxyModel);
    m_tree->setItemDelegate(m_delegate);
}

void ComponentTreeView::setModel(SessionModel* model)
{
    m_proxyModel->setSessionModel(model);
}

void ComponentTreeView::setRootIndex(const QModelIndex& index)
{
    Q_ASSERT(m_proxyModel);
    m_proxyModel->setRootIndex(index);
}

QTreeView* ComponentTreeView::treeView()
{
    return m_tree;
}

