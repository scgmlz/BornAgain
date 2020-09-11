// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterProxyModel.h
//! @brief     Defines class FitParameterProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERPROXYMODEL_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERPROXYMODEL_H

#include "Wrap/WinDllMacros.h"
#include <QAbstractItemModel>
#include <QStringList>

class SessionModel;
class FitParameterContainerItem;
class SessionItem;

//! The FitParameterProxyModel adapts the original JobModel to show items from FitParameterContainer
//! in 5 column tree view.
//! It is derived from QAbstractItemModel (and not from QAbstractProxyModel).

class BA_CORE_API_ FitParameterProxyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit FitParameterProxyModel(FitParameterContainerItem* fitParContainer,
                                    QObject* parent = 0);

    ~FitParameterProxyModel();

    enum EColumn { PAR_NAME, PAR_TYPE, PAR_VALUE, PAR_MIN, PAR_MAX, MAX_COLUMNS };

    Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex& parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex& child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex& parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex& index, const QVariant& value, int role) Q_DECL_OVERRIDE;

    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    Qt::DropActions supportedDragActions() const Q_DECL_OVERRIDE;
    Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;
    QMimeData* mimeData(const QModelIndexList& indexes) const Q_DECL_OVERRIDE;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                         const QModelIndex& parent) const Q_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                      const QModelIndex& parent) Q_DECL_OVERRIDE;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    QModelIndex indexOfItem(SessionItem* item) const;
    SessionItem* itemForIndex(const QModelIndex& index) const;

    SessionModel* sourceModel() const;

    bool isValidSourceItem(SessionItem* item) const;

private slots:
    void onSourceDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                             const QVector<int>& roles);
    void onSourceRowsRemoved(const QModelIndex& parent, int first, int last);
    void onSourceAboutToBeReset();

private:
    void connectModel(QAbstractItemModel* sourceModel, bool isConnect = true);
    void addColumn(EColumn id, const QString& name, const QString& tooltip);

    FitParameterContainerItem* m_root_item;
    QMap<int, QString> m_columnNames;
    QMap<int, QString> m_columnToolTips;
};

inline Qt::DropActions FitParameterProxyModel::supportedDragActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

inline Qt::DropActions FitParameterProxyModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERPROXYMODEL_H
