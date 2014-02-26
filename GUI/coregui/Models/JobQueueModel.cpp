#include "JobQueueModel.h"
#include "mainwindow_constants.h"
#include <QMimeData>
#include <iostream>


//JobQueueModel::JobQueueModel(QObject *parent) :
//    QStandardItemModel(parent)
//{



//}


JobQueueModel::JobQueueModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(0)
{
    m_root_item = new JobQueueItem("root");
}

JobQueueModel::~JobQueueModel()
{
    delete m_root_item;
}


Qt::ItemFlags JobQueueModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result_flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        result_flags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled
                     |Qt::ItemIsEditable|Qt::ItemIsDragEnabled
                     |Qt::ItemIsDropEnabled;
    }
    return result_flags;
}


QVariant JobQueueModel::data(const QModelIndex &index, int role) const
{
    if (!m_root_item || !index.isValid() || index.column() < 0
            || index.column() >= MaxColumns) {
        return QVariant();
    }
    if (JobQueueItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            switch (index.column()) {
            case ItemName: return item->itemName();
            case ModelType: return item->modelType();
            default: return QVariant();
            }
        }
    }
    return QVariant();
}


int JobQueueModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return 0;
    JobQueueItem *parent_item = itemForIndex(parent);
    return parent_item ? parent_item->childItemCount() : 0;
}


int JobQueueModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return 0;
    return MaxColumns;
}

QModelIndex JobQueueModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) return QModelIndex();
    if (JobQueueItem *child_item = itemForIndex(child)) {
        if (JobQueueItem *parent_item = child_item->parent()) {
            if (parent_item == m_root_item) return QModelIndex();
            if (JobQueueItem *grandparent_item = parent_item->parent())
            {
                int row = grandparent_item->rowOfChild(parent_item);
                return createIndex(row, 0, parent_item);
            }
        }
    }
    return QModelIndex();
}


QModelIndex JobQueueModel::index(int row, int column,
                                const QModelIndex &parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= MaxColumns
            || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    JobQueueItem *parent_item = itemForIndex(parent);
    if (JobQueueItem *item = parent_item->childAt(row)) {
        return createIndex(row, column, item);
    }
    return QModelIndex();
}


//JobQueueItem *JobQueueModel::insertNewItem(QString model_type,
//                                               const QModelIndex &parent,
//                                               int row)
//{
//    if (!m_root_item) {
//        m_root_item = new JobQueueItem;
//    }
//    JobQueueItem *parent_item = itemForIndex(parent);
//    if (row==-1) row = parent_item->childItemCount();
//    beginInsertRows(parent, row, row);
//    JobQueueItem *new_item = insertNewItem(model_type, parent_item, row);
//    endInsertRows();
//    return new_item;
//}



JobQueueItem *JobQueueModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (JobQueueItem *item = static_cast<JobQueueItem *>(
                    index.internalPointer()))
            return item;
    }
    return m_root_item;
}


QStringList JobQueueModel::mimeTypes() const
{
    return QStringList() << Constants::MIME_JOBQUEUE;
}


QMimeData *JobQueueModel::mimeData(const QModelIndexList &indices) const
{
    qDebug() << "JobQueueModel::mimeData()" << std::endl;
    const int MaxCompression = 9;
    if (indices.count() != 2) return 0;
    if (JobQueueItem *item = itemForIndex(indices.at(0))) {
        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        writeItemAndChildItems(&writer, item);
        mime_data->setData(Constants::MIME_JOBQUEUE, qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;
}


bool JobQueueModel::canDropMimeData(const QMimeData *data, Qt::DropAction action,
                                   int row, int column,
                                   const QModelIndex &parent) const
{
    (void)row;
    if (action == Qt::IgnoreAction) return true;
    if (action != Qt::MoveAction || column > 0 || !data
            || !data->hasFormat(Constants::MIME_JOBQUEUE)) return false;
    if (!parent.isValid()) return true;

//    QList<QString> acceptable_child_items = getAcceptableChildItems(parent);

//    QByteArray xml_data = qUncompress(data->data(Constants::MIME_JOBQUEUE));
//    QXmlStreamReader reader(xml_data);
//    while (!reader.atEnd()) {
//        reader.readNext();
//        if (reader.isStartElement()) {
//            if (reader.name() == JobQueueXML::ItemTag) {
//                const QString model_type = reader.attributes()
//                        .value(JobQueueXML::ModelTypeAttribute).toString();
//                return acceptable_child_items.contains(model_type);
//            }
//        }
//    }
//    return false;
    return true;
}


bool JobQueueModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction) return true;
    if (action != Qt::MoveAction || column > 0 || !data
            || !data->hasFormat(Constants::MIME_JOBQUEUE)) return false;
    if (!canDropMimeData(data, action, row, column, parent)) return false;
    if (JobQueueItem *item = itemForIndex(parent)) {
        QByteArray xml_data = qUncompress(data->data(Constants::MIME_JOBQUEUE));
        QXmlStreamReader reader(xml_data);
        if (row == -1) row = item->childItemCount();
        beginInsertRows(parent, row, row);
        readItems(&reader, item, row);
        endInsertRows();
        return true;
    }
    return false;
}


void JobQueueModel::writeItemAndChildItems(QXmlStreamWriter *writer,
                                          JobQueueItem *item) const
{
    if (item != m_root_item) {
        writer->writeStartElement(JobQueueXML::ItemTag);
        writer->writeAttribute(JobQueueXML::ModelTypeAttribute,
                               item->modelType());
        writer->writeAttribute(JobQueueXML::ItemNameAttribute,
                               item->itemName());
//        QMapIterator<QString, double> it(item->parameters());
//        while (it.hasNext()) {
//            it.next();
//            writer->writeStartElement(JobQueueXML::ParameterTag);
//            writer->writeAttribute(JobQueueXML::ParameterNameAttribute,
//                                   it.key());
//            writer->writeAttribute(JobQueueXML::ParameterValueAttribute,
//                                   QString::number(it.value(), 'g', 12) );
//            writer->writeEndElement(); // ParameterTag
//        }
    }
    foreach (JobQueueItem *child_item, item->childItems()) {
        writeItemAndChildItems(writer, child_item);
    }
    if (item != m_root_item) {
        writer->writeEndElement(); // ItemTag
    }
}


void JobQueueModel::readItems(QXmlStreamReader *reader, JobQueueItem *item,
                             int row)
{
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == JobQueueXML::ItemTag) {
                const QString model_type = reader->attributes()
                        .value(JobQueueXML::ModelTypeAttribute).toString();

//                item = insertNewItem(model_type, item, row);
                std::cout << "AAA " << std::endl;

                const QString item_name = reader->attributes()
                        .value(JobQueueXML::ItemNameAttribute).toString();
                item->setItemName(item_name);
                row = -1; // all but the first item should be appended
            }
            else if (reader->name() == JobQueueXML::ParameterTag) {
//                const QString parameter_name = reader->attributes()
//                        .value(JobQueueXML::ParameterNameAttribute)
//                        .toString();
//                double parameter_value = reader->attributes()
//                        .value(JobQueueXML::ParameterValueAttribute)
//                        .toDouble();
//                item->setParameter(parameter_name, parameter_value);
            }
        }
        else if (reader->isEndElement()) {
            if (reader->name() == JobQueueXML::ItemTag) {
                item = item->parent();
            }
        }
    }
}

