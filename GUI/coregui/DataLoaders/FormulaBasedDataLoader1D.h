//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      M:/BornAgain/GUI/coregui/DataLoaders/FormulaBasedDataLoader1D.h
//! @brief     Defines class FormulaBasedDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_DATALOADERS_FORMULABASEDDATALOADER1D_H
#define BORNAGAIN_GUI_COREGUI_DATALOADERS_FORMULABASEDDATALOADER1D_H

#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"

class FormulaBasedDataLoader1D : public AbstractDataLoader1D {
public:
    virtual QString name() const override;
    virtual QString persistentClassName() const override;
    virtual QString preview(const QString& filepath, QCustomPlot* plotWidget) const override;
    virtual void populatePropertiesWidget(QWidget* parent) override;
    virtual void initWithDefaultProperties() override;
    virtual void applyProperties() override;
    virtual QByteArray serialize() const override;
    virtual void deserialize(const QByteArray& data) override;
    virtual AbstractDataLoader* clone() const override;

private:
    QPointer<QWidget> m_propertiesWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_FORMULABASEDDATALOADER1D_H
