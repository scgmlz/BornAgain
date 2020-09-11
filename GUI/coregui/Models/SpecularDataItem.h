// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SpecularDataItem.h
//! @brief     Defines class SpecularDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SPECULARDATAITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SPECULARDATAITEM_H

#include "GUI/coregui/Models/DataItem.h"

class AmplitudeAxisItem;
class BasicAxisItem;

namespace SpecularDataAxesNames
{
const QString x_axis_default_name = "X [nbins]";
const QString y_axis_default_name = "Signal [a.u.]";
} // namespace SpecularDataAxesNames

class BA_CORE_API_ SpecularDataItem : public DataItem
{
public:
    static const QString P_TITLE;
    static const QString P_XAXIS;
    static const QString P_YAXIS;

    SpecularDataItem();

    void setOutputData(OutputData<double>* data) override;

    //! Number of bins in data
    int getNbins() const;

    //! returns lower and upper zoom ranges of x-axis
    double getLowerX() const;
    double getUpperX() const;

    //! returns min and max range of x-axis as given by IntensityData
    double getXmin() const;
    double getXmax() const;

    //! returns lower and upper zoom ranges of y-axis
    double getLowerY() const;
    double getUpperY() const;

    //! returns min and max range of y-axis as given by IntensityData
    double getYmin() const;
    double getYmax() const;

    bool isLog() const;
    QString getXaxisTitle() const;
    QString getYaxisTitle() const;

    QPair<double, double> dataRange() const;

    const BasicAxisItem* xAxisItem() const;
    BasicAxisItem* xAxisItem();
    const AmplitudeAxisItem* yAxisItem() const;

    void resetView();

    void setXaxisTitle(QString xtitle) override;
    void setYaxisTitle(QString ytitle) override;
    void setAxesRangeToData() override;
    void updateAxesUnits(const InstrumentItem* instrument) override;
    std::vector<int> shape() const override;

    //! Returns data to the state defined by user (imported)
    //! data.
    void reset(ImportDataInfo data) override;

public slots:
    void setLowerX(double xmin);
    void setUpperX(double xmax);
    void setLowerY(double ymin);
    void setUpperY(double ymax);
    void setLog(bool log_flag);

private:
    void updateAxesZoomLevel();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SPECULARDATAITEM_H
