// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModel.h
//! @brief     Defines class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SESSIONMODEL_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SESSIONMODEL_H

#include "GUI/coregui/Models/SessionFlags.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionXML.h"
#include <QStringList>

class BA_CORE_API_ SessionModel : public QAbstractItemModel
{
    Q_OBJECT
    friend class SessionItem;

public:
    explicit SessionModel(QString model_tag, QObject* parent = 0);
    virtual ~SessionModel();
    void createRootItem();

    // Begin overriden methods from QAbstractItemModel
    virtual Qt::ItemFlags flags(const QModelIndex& index) const;
    virtual QVariant data(const QModelIndex& index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex& parent) const;
    virtual int columnCount(const QModelIndex& parent) const;
    virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
    virtual QModelIndex parent(const QModelIndex& child) const;

    virtual bool setHeaderData(int, Qt::Orientation, const QVariant&, int = Qt::EditRole);
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role);
    virtual bool removeRows(int row, int count, const QModelIndex& parent);

    virtual Qt::DropActions supportedDragActions() const;
    virtual Qt::DropActions supportedDropActions() const;
    virtual QStringList mimeTypes() const;
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const;
    virtual bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent) const;
    virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                              const QModelIndex& parent);
    // End overridden methods from QAbstractItemModel

    QModelIndex indexOfItem(SessionItem* item) const;
    SessionItem* insertNewItem(QString model_type, const QModelIndex& parent = {}, int row = -1,
                               QString tag = "");

    QString getModelTag() const;
    QString getModelName() const;

    QVector<QString> acceptableDefaultItemTypes(const QModelIndex& parent) const;

    virtual void clear();
    void load(const QString& filename = "");
    void save(const QString& filename = "");

    // Sets mimedata pointer of item being dragged
    void setDraggedItemType(const QString& type);

    // Returns root item if index is not valid
    SessionItem* itemForIndex(const QModelIndex& index) const;

    void readFrom(QXmlStreamReader* reader, MessageService* messageService = 0);
    void writeTo(QXmlStreamWriter* writer, SessionItem* parent = 0);

    SessionItem* moveItem(SessionItem* item, SessionItem* new_parent = 0, int row = -1,
                          const QString& tag = "");

    SessionItem* copyItem(const SessionItem* item_to_copy, SessionItem* new_parent = 0,
                          const QString& tag = "");

    virtual SessionModel* createCopy(SessionItem* parent = 0);

    template <typename T = SessionItem> T* topItem() const;
    template <typename T = SessionItem> QVector<T*> topItems() const;

    virtual void initFrom(SessionModel* model, SessionItem* parent);
    SessionItem* rootItem() const;

    virtual QVector<SessionItem*> nonXMLData() const;

signals:
    void modelLoaded();

protected:
    void setRootItem(SessionItem* root) { m_root_item = root; }

private:
    SessionItem* m_root_item;
    QString m_dragged_item_type;
    QString m_name;      //!< model name
    QString m_model_tag; //!< model tag (SampleModel, InstrumentModel)
};

template <typename T> T* SessionModel::topItem() const
{
    auto items = topItems<T>();
    return items.isEmpty() ? nullptr : items.front();
}

template <typename T> QVector<T*> SessionModel::topItems() const
{
    QVector<T*> result;

    QModelIndex parentIndex;
    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);
        if (auto item = dynamic_cast<T*>(itemForIndex(itemIndex)))
            result.push_back(item);
    }

    return result;
}

inline bool SessionModel::setHeaderData(int, Qt::Orientation, const QVariant&, int)
{
    return false;
}

inline Qt::DropActions SessionModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

inline Qt::DropActions SessionModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

inline QString SessionModel::getModelTag() const
{
    return m_model_tag;
}

inline QString SessionModel::getModelName() const
{
    return m_name;
}

inline void SessionModel::setDraggedItemType(const QString& type)
{
    m_dragged_item_type = type;
}

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SESSIONMODEL_H
