//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/ConfigurableDataLoader1D.h
//! @brief     Defines class ConfigurableDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_DATALOADERS_CONFIGURABLEDATALOADER1D_H
#define BORNAGAIN_GUI_COREGUI_DATALOADERS_CONFIGURABLEDATALOADER1D_H

#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"

//! Implements the new UI2 free configurable importer
class ConfigurableDataLoader1D : public AbstractDataLoader1D {
public:
    virtual QString name() const override;
    virtual QString info() const override;
    virtual QString persistentClassName() const override;
    virtual QVector<QVector<QString>> parsedData() const override;

    QString preview(const QString& filepath, QCustomPlot* plotWidget) const override;
    virtual void fillPropertiesGroupBox(QGroupBox* parent) override;

    virtual QByteArray serialize() const override;
    virtual void deserialize(const QByteArray& data) override;

    // #TODO: Rename members
private:
    QString m_header_prefix = ""; //!< prefix denoting header line
    QString m_separator = "";     //!< column separator
    QString m_skip_index_pattern; //!< pattern denoting line to skip (i.e. '1,10-12,42')
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_CONFIGURABLEDATALOADER1D_H
