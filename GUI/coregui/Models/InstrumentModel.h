//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/InstrumentModel.h
//! @brief     Defines class InstrumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_INSTRUMENTMODEL_H
#define BORNAGAIN_GUI_COREGUI_MODELS_INSTRUMENTMODEL_H

#include "GUI/coregui/Models/SessionModel.h"

class InstrumentItem;

class InstrumentModel : public SessionModel {
    Q_OBJECT

public:
    explicit InstrumentModel(QObject* parent = nullptr);
    ~InstrumentModel() override;

    InstrumentModel* createCopy(SessionItem* parent = nullptr) override;
    QVector<SessionItem*> nonXMLItems() const override;

    QVector<InstrumentItem*> instrumentItems() const;

    InstrumentItem* findInstrumentById(const QString& instrumentId) const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_INSTRUMENTMODEL_H
