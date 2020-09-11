// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItem.h
//! @brief     Declares class DataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DATAITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DATAITEM_H

#include "Core/Intensity/OutputData.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/mainwindow/SaveLoadInterface.h"
#include <QDateTime>
#include <mutex>

class ImportDataInfo;
class InstrumentItem;

//! Provides common functionality for IntensityDataItem and SpecularDataItem

class BA_CORE_API_ DataItem : public SessionItem, public SaveLoadInterface
{
public:
    static const QString P_FILE_NAME;
    static const QString P_AXES_UNITS;

    OutputData<double>* getOutputData() { return m_data.get(); }
    const OutputData<double>* getOutputData() const { return m_data.get(); }
    virtual void setOutputData(OutputData<double>* data) = 0;

    //! Sets the raw data vector from external source
    //! Checks only the equality of data size,
    //! no dimension checks are applied.
    void setRawDataVector(std::vector<double> data);

    using SaveLoadInterface::fileName;
    QString fileName() const override;
    QDateTime lastModified() const override;
    bool containsNonXMLData() const override;
    bool load(const QString& projectDir) override;
    bool save(const QString& projectDir) override;

    void setLastModified(const QDateTime& dtime);

    QString selectedAxesUnits() const;

    virtual void setXaxisTitle(QString xtitle) = 0;
    virtual void setYaxisTitle(QString ytitle) = 0;
    virtual void setAxesRangeToData() = 0;
    virtual void updateAxesUnits(const InstrumentItem* instrument) = 0;
    virtual std::vector<int> shape() const = 0;

    //! Returns data to the state defined by user (imported)
    //! data.
    virtual void reset(ImportDataInfo data) = 0;

protected:
    DataItem(const QString& modelType);

    std::unique_ptr<OutputData<double>> m_data; //!< simulation results
    QDateTime m_last_modified;
    std::mutex m_update_data_mutex;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DATAITEM_H
