// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItem.cpp
//! @brief     Implements class SessionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Basics/Assert.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ItemFactory.h"
#include "GUI/coregui/Models/ParameterTranslators.h"
#include "GUI/coregui/Models/SessionItemData.h"
#include "GUI/coregui/Models/SessionItemTags.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"

const QString SessionItem::P_NAME = "Name";

//! Constructs new item with given model type. The type must be defined.
SessionItem::SessionItem(const QString& modelType)
    : m_parent(nullptr), m_model(nullptr), m_properties(new SessionItemData),
      m_tags(new SessionItemTags)
{
    ASSERT(!modelType.isEmpty());

    setRoleProperty(SessionFlags::ModelTypeRole, modelType);
    setDisplayName(modelType);
    setDecimals(3);
    setLimits(RealLimits::nonnegative());
}

//! Destructor deletes all its children and request parent to delete this item.

SessionItem::~SessionItem()
{
    if (m_mapper)
        m_mapper->callOnItemDestroy();

    QVector<SessionItem*>::const_iterator it;
    for (it = m_children.constBegin(); it != m_children.constEnd(); ++it) {
        SessionItem* child = *it;
        if (child)
            child->setModel(nullptr);
        delete child;
    }
    m_children.clear();
    if (m_parent && m_model)
        m_parent->childDeleted(this);

    for (IPathTranslator* translator : m_translators)
        delete translator;
}

//! Returns model of this item.

SessionModel* SessionItem::model() const
{
    return m_model;
}

//! Returns parent of this item.

SessionItem* SessionItem::parent() const
{
    return m_parent;
}

//! Returns model index of this item.

QModelIndex SessionItem::index() const
{
    return model() ? model()->indexOfItem(const_cast<SessionItem*>(this)) : QModelIndex();
}

//! Indicates whether this SessionItem has any child items

bool SessionItem::hasChildren() const
{
    return numberOfChildren() > 0;
}

//! Returns total number of children.

int SessionItem::numberOfChildren() const
{
    return m_children.size();
}

//! Returns vector of all children.

QVector<SessionItem*> SessionItem::children() const
{
    return m_children;
}

//! Returns the child at the given row.

SessionItem* SessionItem::childAt(int row) const
{
    return m_children.value(row, nullptr);
}

//! Returns row index of given child.

int SessionItem::rowOfChild(SessionItem* child) const
{
    return m_children.indexOf(child);
}

//! Returns the first child of the given type.

SessionItem* SessionItem::getChildOfType(const QString& type) const
{
    for (auto child : m_children)
        if (child->modelType() == type)
            return child;

    return nullptr;
}

//! Returns a vector of all children of the given type.

QVector<SessionItem*> SessionItem::getChildrenOfType(const QString& model_type) const
{
    QVector<SessionItem*> result;
    for (auto child : m_children)
        if (child->modelType() == model_type)
            result.append(child);

    return result;
}

//! Removes row from item and returns the item.

SessionItem* SessionItem::takeRow(int row)
{
    SessionItem* item = childAt(row);
    QString tag = tagFromItem(item);
    auto items = getItems(tag);
    return takeItem(items.indexOf(item), tag);
}

//! Add new tag to this item with given name, min, max and types.
//! max = -1 -> unlimited, modelTypes empty -> all types allowed

bool SessionItem::registerTag(const QString& name, int min, int max, QStringList modelTypes)
{
    return m_tags->registerTag(name, min, max, modelTypes);
}

//! Returns true if tag is available.

bool SessionItem::isTag(const QString& name) const
{
    return m_tags->isValid(name);
}

SessionItemTags* SessionItem::sessionItemTags()
{
    return m_tags.get();
}

//! Returns the tag name of given item when existing.

QString SessionItem::tagFromItem(const SessionItem* item) const
{
    int index = m_children.indexOf(const_cast<SessionItem*>(item));
    return m_tags->tagFromIndex(index);
}

//! Returns true if model type can be added to default tag.

bool SessionItem::acceptsAsDefaultItem(const QString& item_name) const
{
    return m_tags->isValid(defaultTag(), item_name);
}

//! Returns vector of acceptable default tag types.

QVector<QString> SessionItem::acceptableDefaultItemTypes() const
{
    return m_tags->modelTypesForTag(defaultTag()).toVector();
}

//! Returns item in given row of given tag.

SessionItem* SessionItem::getItem(const QString& tag, int row) const
{
    const QString tagName = tag.isEmpty() ? defaultTag() : tag;

    if (!m_tags->isValid(tagName))
        return nullptr;

    if (m_tags->childCount(tagName) == 0)
        return nullptr;

    if (row < 0 || row >= m_tags->childCount(tagName))
        return nullptr;

    int index = m_tags->indexFromTagRow(tagName, row);
    ASSERT(index >= 0);
    ASSERT(index < m_children.size());
    return m_children[index];
}

//! Returns vector of all items of given tag.

QVector<SessionItem*> SessionItem::getItems(const QString& tag) const
{
    const QString tagName = tag.isEmpty() ? defaultTag() : tag;
    if (!m_tags->isValid(tagName))
        return QVector<SessionItem*>();

    int index = m_tags->tagStartIndex(tagName);
    ASSERT(index >= 0 && index <= m_children.size());
    return m_children.mid(index, m_tags->childCount(tagName));
}

//! Insert item into given tag into given row.
bool SessionItem::insertItem(int row, SessionItem* item, const QString& tag)
{
    ASSERT(item);
    ASSERT(!item->parent());

    const QString tagName = tag.isEmpty() ? defaultTag() : tag;
    ASSERT(m_tags->isValid(tagName, item->modelType()));

    int index = m_tags->insertIndexFromTagRow(tagName, row);
    ASSERT(index >= 0);
    ASSERT(index <= m_children.size());

    if (m_model)
        m_model->beginInsertRows(this->index(), index, index);

    item->setParentAndModel(this, m_model);
    m_children.insert(index, item);

    m_tags->addChild(tagName);
    if (m_model)
        m_model->endInsertRows();

    return true;
}

//! Remove item from given row from given tag.

SessionItem* SessionItem::takeItem(int row, const QString& tag)
{
    const QString tagName = tag.isEmpty() ? defaultTag() : tag;
    ASSERT(m_tags->isValid(tagName));
    ASSERT(!m_tags->isSingleItemTag(tagName));

    int index = m_tags->indexFromTagRow(tagName, row);
    ASSERT(index >= 0 && index <= m_children.size());

    if (m_model)
        m_model->beginRemoveRows(this->index(), index, index);
    SessionItem* result = m_children.takeAt(index);
    result->setParentAndModel(nullptr, nullptr);

    m_tags->removeChild(tagName);
    if (m_model)
        m_model->endRemoveRows();
    return result;
}

//! Add new property item and register new tag.

SessionItem* SessionItem::addProperty(const QString& name, const QVariant& variant)
{
    ASSERT(!isTag(name));

    SessionItem* property = ItemFactory::CreateItem("Property");
    property->setDisplayName(name);
    registerTag(name, 1, 1, QStringList() << "Property");
    bool success = insertItem(0, property, name);
    ASSERT(success);

    property->setValue(variant);
    return property;
}

//! Directly access value of item under given tag.

QVariant SessionItem::getItemValue(const QString& tag) const
{
    ASSERT(isTag(tag));
    return getItem(tag)->value();
}

//! Directly set value of item under given tag.

void SessionItem::setItemValue(const QString& tag, const QVariant& variant)
{
    ASSERT(isTag(tag));
    getItem(tag)->setValue(variant);
}

//! Creates new group item and register new tag, returns GroupItem.

SessionItem* SessionItem::addGroupProperty(const QString& groupTag, const QString& groupType)
{
    SessionItem* result(0);

    if (SessionItemUtils::IsValidGroup(groupType)) {
        // create group item
        GroupInfo groupInfo = SessionItemUtils::GetGroupInfo(groupType);
        GroupItem* groupItem = dynamic_cast<GroupItem*>(ItemFactory::CreateItem("GroupProperty"));
        ASSERT(groupItem);
        groupItem->setGroupInfo(groupInfo);
        registerTag(groupTag, 1, 1, QStringList() << "GroupProperty");
        result = groupItem;
    } else {
        // create single item
        registerTag(groupTag, 1, 1, QStringList() << groupType);
        result = ItemFactory::CreateItem(groupType);
    }
    ASSERT(result);
    result->setDisplayName(groupTag);
    bool success = insertItem(0, result, groupTag);
    ASSERT(success);
    return result;
}

//! Set the current type of group item.

SessionItem* SessionItem::setGroupProperty(const QString& groupTag, const QString& modelType) const
{
    return item<GroupItem>(groupTag).setCurrentType(modelType);
}

//! Access subitem of group item.

SessionItem* SessionItem::getGroupItem(const QString& groupName) const
{
    return item<GroupItem>(groupName).currentItem();
}

//! Returns corresponding variant under given role, invalid variant when role is not present.

QVariant SessionItem::roleProperty(int role) const
{
    return m_properties->data(role);
}

//! Set variant to role, create role if not present yet.

bool SessionItem::setRoleProperty(int role, const QVariant& value)
{
    bool result = m_properties->setData(role, value);
    if (result)
        emitDataChanged(role);
    return result;
}

//! Returns vector of all present roles.

QVector<int> SessionItem::getRoles() const
{
    return m_properties->roles();
}

//! Notify model about data changes.

void SessionItem::emitDataChanged(int role)
{
    if (m_model) {
        QModelIndex index = m_model->indexOfItem(this);
        m_model->dataChanged(index, index.sibling(index.row(), 1), QVector<int>() << role);
    }
}

//! Get model type.

QString SessionItem::modelType() const
{
    return roleProperty(SessionFlags::ModelTypeRole).toString();
}

//! Get value.

QVariant SessionItem::value() const
{
    return roleProperty(Qt::DisplayRole);
}

//! Set value, ensure that variant types match.

bool SessionItem::setValue(QVariant value)
{
    ASSERT(SessionItemUtils::CompatibleVariantTypes(this->value(), value));
    return setRoleProperty(Qt::DisplayRole, value);
}

//! Get default tag

QString SessionItem::defaultTag() const
{
    return roleProperty(SessionFlags::DefaultTagRole).toString();
}

//! Set default tag

void SessionItem::setDefaultTag(const QString& tag)
{
    setRoleProperty(SessionFlags::DefaultTagRole, tag);
}

//! Get display name of item, append index if ambigue.

QString SessionItem::displayName() const
{
    QString result = roleProperty(SessionFlags::DisplayNameRole).toString();

    if (modelType() == "Property" || modelType() == "GroupProperty" || modelType() == "Parameter"
        || modelType() == "Parameter Label")
        return result;

    if (m_parent) {
        QString tag = m_parent->tagFromItem(this);
        // if only one child of this type is allowed, return name without change
        if (m_parent->sessionItemTags()->isSingleItemTag(tag))
            return result;

        int index = m_parent->getCopyNumberOfChild(this);
        if (index >= 0)
            return result + QString::number(index);
    }
    return result;
}

//! Set display name

void SessionItem::setDisplayName(const QString& display_name)
{
    setRoleProperty(SessionFlags::DisplayNameRole, display_name);
}

//! Get item name, return display name if no name is set.
QString SessionItem::itemName() const
{
    return isTag(P_NAME) ? getItemValue(P_NAME).toString() : displayName();
}

//! Set item name, add property if necessary.
void SessionItem::setItemName(const QString& name)
{
    if (isTag(P_NAME))
        setItemValue(P_NAME, name);
    else
        addProperty(P_NAME, name);
}

//! Flags accessors.

void SessionItem::setVisible(bool enabled)
{
    changeFlags(enabled, SessionFlags::VISIBLE);
}

void SessionItem::setEnabled(bool enabled)
{
    changeFlags(enabled, SessionFlags::ENABLED);
}

void SessionItem::setEditable(bool enabled)
{
    changeFlags(enabled, SessionFlags::EDITABLE);
}

bool SessionItem::isVisible() const
{
    return flags() & SessionFlags::VISIBLE;
}

bool SessionItem::isEnabled() const
{
    return flags() & SessionFlags::ENABLED;
}

bool SessionItem::isEditable() const
{
    return flags() & SessionFlags::EDITABLE;
}

RealLimits SessionItem::limits() const
{
    return roleProperty(SessionFlags::LimitsRole).value<RealLimits>();
}

SessionItem& SessionItem::setLimits(const RealLimits& value)
{
    setRoleProperty(SessionFlags::LimitsRole, QVariant::fromValue<RealLimits>(value));
    return *this;
}

int SessionItem::decimals() const
{
    return roleProperty(SessionFlags::DecimalRole).toInt();
}

SessionItem& SessionItem::setDecimals(int n)
{
    setRoleProperty(SessionFlags::DecimalRole, n);
    return *this;
}

QString SessionItem::toolTip() const
{
    return roleProperty(Qt::ToolTipRole).toString();
}

SessionItem& SessionItem::setToolTip(const QString& tooltip)
{
    setRoleProperty(Qt::ToolTipRole, tooltip);
    return *this;
}

QString SessionItem::editorType() const
{
    const auto variant = roleProperty(SessionFlags::CustomEditorRole);
    return variant.isValid() ? variant.toString() : "Default";
}

SessionItem& SessionItem::setEditorType(const QString& editorType)
{
    setRoleProperty(SessionFlags::CustomEditorRole, editorType);
    return *this;
}

//! Returns the current model mapper of this item. Creates new one if necessary.

ModelMapper* SessionItem::mapper()
{
    if (!m_mapper) {
        m_mapper = std::unique_ptr<ModelMapper>(new ModelMapper);
        m_mapper->setItem(this);
    }
    return m_mapper.get();
}

QStringList SessionItem::translateList(const QStringList& list) const
{
    QStringList result = list;
    for (const IPathTranslator* translator : m_translators)
        result = translator->translate(result);
    // TODO consider adding displayName before translators
    result << displayName();
    return result;
}

void SessionItem::addTranslator(const IPathTranslator& translator)
{
    m_translators.push_back(translator.clone());
}

void SessionItem::childDeleted(SessionItem* child)
{
    int index = rowOfChild(child);
    ASSERT(index != -1);
    m_children.replace(index, nullptr);
}

void SessionItem::setParentAndModel(SessionItem* parent, SessionModel* model)
{
    setModel(model);
    m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    m_model = model;

    if (m_mapper)
        m_mapper->setItem(this);

    for (auto& child : m_children)
        child->setModel(model);
}

int SessionItem::flags() const
{
    QVariant flags = roleProperty(SessionFlags::FlagRole);

    if (!flags.isValid())
        return SessionFlags::VISIBLE | SessionFlags::EDITABLE | SessionFlags::ENABLED;

    return flags.toInt();
}

//! internal
void SessionItem::changeFlags(bool enabled, int flag)
{
    int flags = this->flags();
    if (enabled)
        flags |= flag;
    else
        flags &= ~flag;

    setRoleProperty(SessionFlags::FlagRole, flags);
}

//! internal
int SessionItem::getCopyNumberOfChild(const SessionItem* item) const
{
    if (!item)
        return -1;
    int result = -1;
    int count = 0;
    QString model_type = item->modelType();
    // check child items:
    for (auto p_child_item : m_children) {
        QString child_type = p_child_item->modelType();
        if (p_child_item == item)
            result = count;
        if (child_type == model_type && !p_child_item->isTag(P_NAME))
            ++count;
    }
    if (count > 1)
        return result;
    return -1;
}
