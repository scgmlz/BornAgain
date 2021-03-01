//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h
//! @brief     Defines class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

// #migration move this file to better folder

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_LINKINSTRUMENTMANAGER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_LINKINSTRUMENTMANAGER_H

#include <QList>
#include <QObject>
#include <QStringList>
#include <QVector>

class InstrumentModel;
class RealDataModel;
class SessionItem;
class InstrumentItem;
class RealDataItem;

//! The LinkInstrumentManager class provides communication between InstrumentModel and
//! RealDataModel. Particularly, it notifies RealDataItem about changes in linked instruments
//! to adjust axes of IntensityDataItem.

class LinkInstrumentManager : public QObject {
    Q_OBJECT

public:
    explicit LinkInstrumentManager(QObject* parent = nullptr);

    void setModels(InstrumentModel* instrumentModel, RealDataModel* realDataModel);

    //! quiet defines whether a "not possible" message box is shown if link is not possible. Use
    //! this e.g. for unit tests. The question for adjusting the instrument is not suppressed by
    //! this flag.
    bool canLinkDataToInstrument(const RealDataItem* realDataItem, const QString& identifier,
                                 bool quiet = false);

    QList<RealDataItem*> linkedRealDataItems(InstrumentItem* instrumentItem);

private slots:
    void onInstrumentChildChange(InstrumentItem* instrument, SessionItem* child);
    void onInstrumentAddedOrRemoved();

    void updateInstrumentSubscriptions();

private:
    InstrumentModel* m_instrumentModel;
    RealDataModel* m_realDataModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_LINKINSTRUMENTMANAGER_H
