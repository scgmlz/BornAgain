// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditor.cpp
//! @brief     Implements class ComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "ComponentEditor.h"
#include "ComponentEditorPrivate.h"
#include "qtpropertybrowser.h"
#include "PropertyVariantManager.h"
#include "GUIHelpers.h"
#include "ParameterizedItem.h"
#include "SessionModel.h"
#include "GroupItem.h"
#include "GroupProperty.h"

#include <QVBoxLayout>
#include <QVariant>
#include <QDebug>


ComponentEditor::ComponentEditor(QWidget *parent)
    : QWidget(parent)
    , m_d(new ComponentEditorPrivate(this))
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("ComponentEditor"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_d->m_browser);

    connectManager();
}

ComponentEditor::~ComponentEditor()
{

}

void ComponentEditor::setItem(ParameterizedItem *item)
{
    clearEditor();
    m_item = item;
    updateEditor(m_item);
}


void ComponentEditor::updateEditor(ParameterizedItem *item, QtVariantProperty *parentProperty)
{
    Q_ASSERT(item);
    connectModel(item->model());

    qDebug() << "  ";
    qDebug() << "  ";
    qDebug() << "ComponentEditor::updateEditor" << item->modelType() << item->itemName() << item->model()->indexOfItem(item);

    if(QtVariantProperty *childProperty = m_d->processPropertyForItem(item, parentProperty)) {
        parentProperty = childProperty;
    }
//    QtVariantProperty *newParentProperty = childProperty ? childProperty : parentProperty;
    foreach(ParameterizedItem *childItem, componentItems(item)) {
        qDebug() << "       ComponentEditor::updateEditor -> childItem" << childItem->modelType() << childItem->itemName() << childItem->model()->indexOfItem(childItem);
        updateEditor(childItem, parentProperty);
    }
}



void ComponentEditor::clearEditor()
{
    disconnect();
    disconnectManager();

    m_d->clear();

    connectManager();
}

void ComponentEditor::setPresentationType(ComponentEditorFlags::PresentationType presentationType)
{
    m_d->setPresentationType(presentationType);
    layout()->addWidget(m_d->m_browser);
}

//! Propagates data from ParameterizedItem to editor
void ComponentEditor::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
//    qDebug() << "ComponentEditor::onDataChanged" << topLeft << bottomRight << roles;
    qDebug() << " ComponentEditor::onDataChanged";
    qDebug() << " ComponentEditor::onDataChanged";
    qDebug() << " ComponentEditor::onDataChanged";
    qDebug() << " ComponentEditor::onDataChanged" << m_d->m_presentationType << topLeft << roles;

    if(topLeft != bottomRight) return;

    SessionModel *model = qobject_cast<SessionModel *>(sender());


//    const SessionModel *model = dynamic_cast<const SessionModel*>(topLeft.model());
//    qDebug() << "OOO" << model->itemForIndex(topLeft) << model->itemForIndex(bottomRight);

//    QMap<QModelIndex, QtVariantProperty *>::iterator it = m_d->m_index_to_qtvariantproperty.begin();
//    while(it!=m_d->m_index_to_qtvariantproperty.end()) {
//        qDebug() << it.key() << it.value();
//        ++it;
//    }

    ParameterizedItem *item = model->itemForIndex(topLeft);
    Q_ASSERT(item);

    if(QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        qDebug() << "   ComponentEditor::onDataChanged -> set value for variant_property" << property << roles;
        qDebug() << "   ComponentEditor::onDataChanged -> " << item->value() << property->value();


        if(roles.contains(Qt::UserRole)) {
            qDebug() << "AAAA UserRole";
            m_d->updateQtVariantPropertyAppearance(property, item->getAttribute());
        } else {
            disconnectManager();
            property->setValue(item->value());
            connectManager();
        }

//       if(item->modelType() == Constants::GroupItemType && m_d->isShowCondensed()) {
//            foreach(ParameterizedItem *child, item->childItems()) {
//                if(child->getAttribute().isVisible()) continue;
//                if(QtVariantProperty *childProperty = m_d->getPropertyForItem(child)) {
//                    m_d->removeQtVariantProperty(childProperty);
//                }
//            }
//        }


    }

}

void ComponentEditor::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    qDebug() << "ComponentEditor::onRowsInserted" << parent << first << last;
    SessionModel *model = qobject_cast<SessionModel *>(sender());

    ParameterizedItem *item = model->itemForIndex(parent);
    qDebug() << "model " << item << item->modelType() << item->itemName();

    Q_ASSERT(m_d->m_item_to_qtvariantproperty.contains(item));

    // special case for "condensed" editor
    qDebug() << "AAAA onRowsInserted() -> special case";
//    if(item->modelType() == Constants::GroupItemType) {
//        foreach(ParameterizedItem *child, item->childItems()) {
//            if(m_d->m_item_to_qtvariantproperty.contains(child)) {
//                m_d->removeQtVariantProperty(m_d->m_item_to_qtvariantproperty[child]);
//            }
//        }
//    }

    updateEditor(item, m_d->m_item_to_qtvariantproperty[item]);

}

//! Propagates value from the editor to ParameterizedItem
void ComponentEditor::onQtPropertyChanged(QtProperty *property, const QVariant &value)
{
    qDebug() << "ComponentEditor::onQtPropertyChanged" << property << value;
    if(ParameterizedItem *item = m_d->getItemForProperty(property)) {
        disconnectModel(item->model());
        item->setValue(value);
        connectModel(item->model());
    }
}


//! Returns list of children suitable for displaying in ComponentEditor
QList<ParameterizedItem *> ComponentEditor::componentItems(ParameterizedItem *item) const
{
    QList<ParameterizedItem *> result;

    if(m_d->isShowDetailed()) {
        result = item->childItems();
    }

    else if (m_d->isShowCondensed()) {

        if(item->modelType() == Constants::GroupItemType) {
            GroupItem *groupItem = dynamic_cast<GroupItem *>(item);
            ParameterizedItem *currentItemInGroup = groupItem->group()->getCurrentItem();
            Q_ASSERT(currentItemInGroup);
            result.append(currentItemInGroup);

//            foreach(ParameterizedItem *child, item->childItems()) {
//                if(child != currentItemInGroup) {
//                    if(m_d->m_item_to_qtvariantproperty.contains(child)) {
//                        m_d->m_item_to_qtvariantproperty[child]->setEnabled(false);
//                    }
//                } else {
//                    if(m_d->m_item_to_qtvariantproperty.contains(child)) {
//                        m_d->m_item_to_qtvariantproperty[child]->setEnabled(true);
//                    }
//                }
//            }

        } else {

            foreach(ParameterizedItem *child, item->childItems()) {
                if(child->modelType() == Constants::PropertyType) {
                    result.append(child);
                }
                if(child->modelType() == Constants::GroupItemType) {
                    result.append(child);
                }
            }
        }

    }

    return result;
}

void ComponentEditor::disconnectModel(SessionModel *model)
{
    disconnect(model,
            SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this,
            SLOT(onDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));

    disconnect(model,
            SIGNAL(rowsInserted(const QModelIndex &, int, int)),
            this,
            SLOT(onRowsInserted(const QModelIndex &, int, int)));

}

void ComponentEditor::connectModel(SessionModel *model)
{
    connect(model,
            SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this,
            SLOT(onDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            Qt::UniqueConnection);

    connect(model,
            SIGNAL(rowsInserted(const QModelIndex &, int, int)),
            this,
            SLOT(onRowsInserted(const QModelIndex &, int, int)),
            Qt::UniqueConnection);

}

void ComponentEditor::disconnectManager()
{
    disconnect(m_d->m_manager,
               SIGNAL(valueChanged(QtProperty *, const QVariant &)),
               this,
               SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)));
}

void ComponentEditor::connectManager()
{
    connect(m_d->m_manager,
            SIGNAL(valueChanged(QtProperty *, const QVariant &)),
            this,
            SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)),
            Qt::UniqueConnection);
}
