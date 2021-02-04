//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AutomaticMultiRowDataLoader1D.h
//! @brief     Defines class AutomaticMultiRowDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef _GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1D_H_
#define _GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1D_H_

#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"
#include <QVector>

class QString;

class AutomaticMultiColumnDataLoader1D : public AbstractDataLoader1D {
public:
    virtual QString name() const override;
    virtual QString info() const override;
    virtual QString persistentClassName() const override;
    virtual QVector<QVector<QString>> parsedData() const override;
    virtual QString preview(const QString& filepath, QCustomPlot* plotWidget) const override;
};

#endif // _GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1D_H_
