//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AutomaticDataLoader1D.h
//! @brief     Defines class AutomaticDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICDATALOADER1D_H
#define BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICDATALOADER1D_H

#include "Device/Data/OutputData.h"
#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"

//! Implements the legacy importer from BornAgain with no user interaction
class AutomaticDataLoader1D : public AbstractDataLoader1D {
public:
    virtual QString name() const override;
    virtual QString info() const override;
    virtual QString persistentClassName() const override;
    virtual QString preview(const QString& filepath, QCustomPlot* plotWidget) const override;
    virtual AbstractDataLoader* clone() const override;

private:
    QString outputDataToTable(const OutputData<double>& outputData) const;
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICDATALOADER1D_H
