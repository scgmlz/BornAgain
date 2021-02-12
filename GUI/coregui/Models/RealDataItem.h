//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/RealDataItem.h
//! @brief     Defines class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_REALDATAITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_REALDATAITEM_H

#include "GUI/coregui/Models/SessionItem.h"

class DataItem;
class InstrumentItem;
class IntensityDataItem;
class SpecularDataItem;
class MaskContainerItem;
template <class T> class OutputData;
class ImportDataInfo;

//! The RealDataItem class represents intensity data imported from file and intended for fitting.

class BA_CORE_API_ RealDataItem : public SessionItem {
public:
    static const QString T_INTENSITY_DATA;
    static const QString P_INSTRUMENT_ID;
    static const QString P_INSTRUMENT_NAME;
    static const QString T_NATIVE_DATA;
    static const QString P_NATIVE_DATA_UNITS;

    RealDataItem();

    IntensityDataItem* intensityDataItem();
    const IntensityDataItem* intensityDataItem() const;

    SpecularDataItem* specularDataItem();
    const SpecularDataItem* specularDataItem() const;

    DataItem* dataItem();
    const DataItem* dataItem() const;

    DataItem* nativeData();
    const DataItem* nativeData() const;

    void setOutputData(OutputData<double>* data);
    void setImportData(ImportDataInfo data);
    bool holdsDimensionalData() const;

    void linkToInstrument(const InstrumentItem* instrument, bool make_update = true);

    //! Returns the shape of underlying data item
    std::vector<int> shape() const;

    bool isIntensityData() const;
    bool isSpecularData() const;

    //! Returns mask container item
    MaskContainerItem* maskContainerItem();

    //! Settings for importing data from a file
    QByteArray importSettings() const;
    void setImportSettings(const QByteArray& a);

private:
    void initDataItem(size_t data_rank, const QString& tag);
    void updateNonXMLDataFileNames();
    void updateToInstrument();
    const InstrumentItem* m_linkedInstrument;
    QByteArray m_deserializationSettings;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_REALDATAITEM_H
