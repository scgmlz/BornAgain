// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h
//! @brief     Defines class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_LINKINSTRUMENTMANAGER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_LINKINSTRUMENTMANAGER_H

#include "Wrap/WinDllMacros.h"
#include <QList>
#include <QObject>
#include <QStringList>
#include <QVector>

class InstrumentModel;
class RealDataModel;
class SessionItem;
class InstrumentItem;
class RealDataItem;
class SessionModel;

//! The LinkInstrumentManager class provides communication between InstrumentModel and
//! RealDataModel. Particularly, it notifies RealDataItem about changes in linked instruments
//! to adjust axes of IntensityDataItem.

class BA_CORE_API_ LinkInstrumentManager : public QObject
{
    Q_OBJECT

public:
    class InstrumentInfo
    {
    public:
        InstrumentInfo();
        QString m_identifier;
        QString m_name;
        InstrumentItem* m_instrument;
    };

    explicit LinkInstrumentManager(QObject* parent = nullptr);

    void setModels(InstrumentModel* instrumentModel, RealDataModel* realDataModel);

    InstrumentItem* getInstrument(const QString& identifier);
    QStringList instrumentNames() const;
    int instrumentComboIndex(const QString& identifier);
    QString instrumentIdentifier(int comboIndex);
    bool canLinkDataToInstrument(const RealDataItem* realDataItem, const QString& identifier);

    QList<RealDataItem*> linkedItems(InstrumentItem* instrumentItem);

signals:
    void instrumentMapUpdated();

private slots:
    void setOnInstrumentPropertyChange(SessionItem* instrument, const QString& property);
    void setOnRealDataPropertyChange(SessionItem* dataItem, const QString& property);
    void onInstrumentChildChange(InstrumentItem* instrument, SessionItem* child);
    void onInstrumentRowsChange(const QModelIndex& parent, int, int);
    void onRealDataRowsChange(const QModelIndex& parent, int, int);

    void updateLinks();
    void updateInstrumentMap();
    void updateRealDataMap();
    void onInstrumentLayoutChange(InstrumentItem* changedInstrument);

private:
    void setInstrumentModel(InstrumentModel* model);
    void setRealDataModel(RealDataModel* model);

    InstrumentModel* m_instrumentModel;
    RealDataModel* m_realDataModel;
    QVector<InstrumentInfo> m_instrumentVec;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_LINKINSTRUMENTMANAGER_H
