//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/RealDataModel.h
//! @brief     Defines class RealDataModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_REALDATAMODEL_H
#define BORNAGAIN_GUI_COREGUI_MODELS_REALDATAMODEL_H

#include "GUI/coregui/Models/InstrumentModel.h"
#include <QPointer>

class RealDataItem;
class InstrumentModel;

//! The RealDataModel class is a model to store all imported RealDataItem's.

class RealDataModel : public SessionModel {
    Q_OBJECT

public:
    explicit RealDataModel(QObject* parent = 0);
    void setInstrumentModel(InstrumentModel* instrumentModel);

    virtual QVector<SessionItem*> nonXMLItems() const override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    virtual void readFrom(QXmlStreamReader* reader, MessageService* messageService = 0) override;

    RealDataItem* insertRealDataItem();
    RealDataItem* insertSpecularDataItem();
    RealDataItem* insertIntensityDataItem();
    QVector<RealDataItem*> realDataItems() const;

    InstrumentModel* instrumentModel() const;

signals:
    void realDataAddedOrRemoved();

private:
    void onRowsChange(const QModelIndex& parent, int, int);

private:
    QPointer<InstrumentModel> m_instrumentModel;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_REALDATAMODEL_H
