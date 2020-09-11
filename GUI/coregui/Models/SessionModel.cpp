// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModel.cpp
//! @brief     Implements class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/ItemFactory.h"
#include "GUI/coregui/Models/SessionItemTags.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QFile>
#include <QMimeData>
#include <QtCore/QXmlStreamWriter>

using SessionItemUtils::ParentRow;

namespace
{
const int MaxCompression = 9;
}

SessionModel::SessionModel(QString model_tag, QObject* parent)
    : QAbstractItemModel(parent), m_root_item(0), m_name("DefaultName"), m_model_tag(model_tag)
{
    createRootItem();
}

void SessionModel::createRootItem()
{
    m_root_item = ItemFactory::CreateEmptyItem();
    m_root_item->setModel(this);
    m_root_item->registerTag("rootTag");
    m_root_item->setDefaultTag("rootTag");
}

SessionModel::~SessionModel()
{
    delete m_root_item;
}

// TODO make it relying on SessionItem::flags

Qt::ItemFlags SessionModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags result_flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        result_flags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled;
        SessionItem* item = itemForIndex(index);
        if (index.column() == SessionFlags::ITEM_VALUE && item->value().isValid()
            && item->isEditable() && item->isEnabled())
            result_flags |= Qt::ItemIsEditable;
        QVector<QString> acceptable_child_items = acceptableDefaultItemTypes(index);
        if (acceptable_child_items.contains(m_dragged_item_type)) {
            result_flags |= Qt::ItemIsDropEnabled;
        }
    } else {
        result_flags |= Qt::ItemIsDropEnabled;
    }
    return result_flags;
}

QVariant SessionModel::data(const QModelIndex& index, int role) const
{
    if (!m_root_item || !index.isValid() || index.column() < 0
        || index.column() >= columnCount(QModelIndex())) {
        return QVariant();
    }
    if (SessionItem* item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (index.column() == SessionFlags::ITEM_VALUE)
                return item->value();
            if (index.column() == SessionFlags::ITEM_NAME)
                return item->itemName();
        } else if (role == Qt::ToolTipRole) {
            return SessionItemUtils::ToolTipRole(*item, index.column());

        } else if (role == Qt::TextColorRole) {
            return SessionItemUtils::TextColorRole(*item);
        } else if (role == Qt::DecorationRole && index.column() == SessionFlags::ITEM_VALUE) {
            return SessionItemUtils::DecorationRole(*item);
        } else if (role == Qt::CheckStateRole && index.column() == SessionFlags::ITEM_VALUE) {
            return SessionItemUtils::CheckStateRole(*item);
        } else {
            return item->roleProperty(role);
        }
    }
    return QVariant();
}

QVariant SessionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case SessionFlags::ITEM_NAME:
            return "Name";
        case SessionFlags::ITEM_VALUE:
            return "Value";
        }
    }
    return QVariant();
}

int SessionModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    SessionItem* parent_item = itemForIndex(parent);
    return parent_item ? parent_item->numberOfChildren() : 0;
}

int SessionModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    return SessionFlags::MAX_COLUMNS;
}

QModelIndex SessionModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= columnCount(QModelIndex())
        || (parent.isValid() && parent.column() != 0))
        return QModelIndex();

    SessionItem* parent_item = itemForIndex(parent);

    if (SessionItem* item = parent_item->childAt(row))
        return createIndex(row, column, item);
    return QModelIndex();
}

QModelIndex SessionModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    if (SessionItem* child_item = itemForIndex(child)) {
        if (SessionItem* parent_item = child_item->parent()) {
            if (parent_item == m_root_item)
                return QModelIndex();

            return createIndex(ParentRow(*parent_item), 0, parent_item);
        }
    }
    return QModelIndex();
}

bool SessionModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    QModelIndex dataIndex = index;
    if (SessionItem* item = itemForIndex(dataIndex))
        if (item->setRoleProperty(role, value))
            return true;

    return false;
}

bool SessionModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (!m_root_item)
        return false;
    SessionItem* item = parent.isValid() ? itemForIndex(parent) : m_root_item;
    for (int i = 0; i < count; ++i)
        delete item->takeRow(row);
    return true;
}

QStringList SessionModel::mimeTypes() const
{
    return QStringList() << SessionXML::ItemMimeType;
}

QMimeData* SessionModel::mimeData(const QModelIndexList& indices) const
{
    if (indices.count() != 2)
        return 0;

    if (SessionItem* item = itemForIndex(indices.at(0))) {
        QMimeData* mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        SessionXML::writeItemAndChildItems(&writer, item);
        mime_data->setData(SessionXML::ItemMimeType, qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;
}

bool SessionModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row,
                                   int column, const QModelIndex& parent) const
{
    Q_UNUSED(row);

    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 || !data
        || !data->hasFormat(SessionXML::ItemMimeType))
        return false;
    if (!parent.isValid())
        return true;
    QVector<QString> acceptable_child_items = acceptableDefaultItemTypes(parent);
    QByteArray xml_data = qUncompress(data->data(SessionXML::ItemMimeType));
    QXmlStreamReader reader(xml_data);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ItemTag) {
                const QString model_type =
                    reader.attributes().value(SessionXML::ModelTypeAttribute).toString();
                return acceptable_child_items.contains(model_type);
            }
        }
    }
    return false;
}

bool SessionModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                const QModelIndex& parent)
{
    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 || !data
        || !data->hasFormat(SessionXML::ItemMimeType))
        return false;
    if (!canDropMimeData(data, action, row, column, parent))
        return false;
    if (SessionItem* item = itemForIndex(parent)) {
        QByteArray xml_data = qUncompress(data->data(SessionXML::ItemMimeType));
        QXmlStreamReader reader(xml_data);
        if (row == -1)
            row = item->numberOfChildren();
        beginInsertRows(parent, row, row);
        // this code block is currently not in use. The row parameter of the reader is removed
        // SessionReader::readItems(&reader, item, row);
        endInsertRows();
        return true;
    }
    return false;
}

QModelIndex SessionModel::indexOfItem(SessionItem* item) const
{
    if (!item || item == m_root_item || !item->parent())
        return QModelIndex();
    SessionItem* parent_item = item->parent();
    int row = parent_item->rowOfChild(item);
    return createIndex(row, 0, item);
}

SessionItem* SessionModel::insertNewItem(QString model_type, const QModelIndex& parent, int row,
                                         QString tag)
{
    SessionItem* parent_item = itemForIndex(parent);
    if (!parent_item)
        parent_item = m_root_item;
    if (row > parent_item->numberOfChildren())
        return nullptr;
    if (parent_item != m_root_item) {
        if (tag.isEmpty())
            tag = parent_item->defaultTag();

        if (!parent_item->sessionItemTags()->isValid(tag, model_type))
            return nullptr;
    }

    SessionItem* new_item = ItemFactory::CreateItem(model_type);

    if (!new_item)
        throw GUIHelpers::Error("SessionModel::insertNewItem() -> Wrong model type " + model_type);

    if (!parent_item->insertItem(row, new_item, tag))
        throw GUIHelpers::Error("SessionModel::insertNewItem -> Error. Can't insert item");

    return new_item;
}

QVector<QString> SessionModel::acceptableDefaultItemTypes(const QModelIndex& parent) const
{
    QVector<QString> result;
    if (SessionItem* parent_item = itemForIndex(parent))
        result = parent_item->acceptableDefaultItemTypes();

    return result;
}

void SessionModel::clear()
{
    beginResetModel();
    delete m_root_item;
    createRootItem();
    endResetModel();
}

void SessionModel::load(const QString& filename)
{
    beginResetModel();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());
    clear();
    m_root_item = ItemFactory::CreateEmptyItem();
    QXmlStreamReader reader(&file);
    SessionXML::readItems(&reader, m_root_item);
    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
    endResetModel();
}

void SessionModel::save(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", GUIHelpers::getBornAgainVersionString());
    SessionXML::writeItemAndChildItems(&writer, m_root_item);
    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();
}

SessionItem* SessionModel::itemForIndex(const QModelIndex& index) const
{
    if (index.isValid())
        if (SessionItem* item = static_cast<SessionItem*>(index.internalPointer()))
            return item;

    return m_root_item;
}

void SessionModel::readFrom(QXmlStreamReader* reader, MessageService* messageService)
{
    ASSERT(reader);

    if (reader->name() != m_model_tag)
        throw GUIHelpers::Error("SessionModel::readFrom() -> Format error in p1");

    beginResetModel();
    clear();

    m_name = reader->attributes().value(SessionXML::ModelNameAttribute).toString();

    SessionXML::readItems(reader, m_root_item, QString(), messageService);
    if (reader->hasError())
        throw GUIHelpers::Error(reader->errorString());
    endResetModel();
}

void SessionModel::writeTo(QXmlStreamWriter* writer, SessionItem* parent)
{
    if (!parent)
        parent = m_root_item;
    SessionXML::writeTo(writer, parent);
}

//! Move given parameterized item to the new_parent at given row. If new_parent is not defined,
//! use root_item as a new parent.

SessionItem* SessionModel::moveItem(SessionItem* item, SessionItem* new_parent, int row,
                                    const QString& tag)
{
    if (!new_parent)
        new_parent = m_root_item;

    const QString tagName = tag.isEmpty() ? new_parent->defaultTag() : tag;

    if (!new_parent->sessionItemTags()->isValid(tagName, item->modelType()))
        return 0;

    if (item->parent() == new_parent) {
        // take care of indexes when moving item within same parent
        int previousIndex = item->parent()->getItems(tagName).indexOf(item);
        if (row == previousIndex)
            return item;
        else if (previousIndex >= 0 && row > previousIndex)
            row--;
    }

    if (new_parent->sessionItemTags()->maximumReached(tagName)) {
        SessionItem* prev = new_parent->takeItem(0, tagName);
        m_root_item->insertItem(-1, prev);
    }

    // removing item from previous parent and inserting to the new one
    item->parent()->takeRow(item->parent()->rowOfChild(item));
    new_parent->insertItem(row, item, tagName);

    return item;
}

//! Copy given item to the new_parent at given row. Item indended for copying can belong to
//! another model and it will remains intact. Returns pointer to the new child.

SessionItem* SessionModel::copyItem(const SessionItem* item_to_copy, SessionItem* new_parent,
                                    const QString& tag)
{
    if (!new_parent)
        new_parent = m_root_item;

    const QString tagName = tag.isEmpty() ? new_parent->defaultTag() : tag;

    QByteArray xml_data;
    QXmlStreamWriter writer(&xml_data);
    SessionXML::writeItemAndChildItems(&writer, item_to_copy);

    QXmlStreamReader reader(xml_data);
    SessionXML::readItems(&reader, new_parent, tagName);

    return new_parent->getItems(tagName).back();
}

SessionModel* SessionModel::createCopy(SessionItem* parent)
{
    Q_UNUSED(parent);
    throw GUIHelpers::Error("SessionModel::createCopy() -> Error. Not implemented.");
}

void SessionModel::initFrom(SessionModel* model, SessionItem*)
{
    QByteArray byte_array;
    QXmlStreamWriter writer(&byte_array);
    writer.setAutoFormatting(true);

    model->writeTo(&writer);

    QXmlStreamReader reader(byte_array);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement())
            readFrom(&reader);
    }
    modelLoaded();
}

SessionItem* SessionModel::rootItem() const
{
    return m_root_item;
}

QVector<SessionItem*> SessionModel::nonXMLData() const
{
    return QVector<SessionItem*>();
}
