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

#include "GUI/coregui/Models/SessionModel.h"

//! The RealDataModel class is a model to store all imported RealDataItem's.

class RealDataModel : public SessionModel {
    Q_OBJECT

public:
    explicit RealDataModel(QObject* parent = 0);

    virtual QVector<SessionItem*> nonXMLItems() const override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) override;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_REALDATAMODEL_H
