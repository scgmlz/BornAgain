//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/UserDefinedDataLoader1D.h
//! @brief     Defines class UserDefinedDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef GUI_COREGUI_DATALOADERS_USERDEFINEDDATALOADER1D_H
#define GUI_COREGUI_DATALOADERS_USERDEFINEDDATALOADER1D_H

#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"

class UserDefinedDataLoader1D : public AbstractDataLoader1D {
public:
    UserDefinedDataLoader1D(AbstractDataLoader1D* wrappedLoader, const QString& name,
                            const QByteArray& defaultProperties);

    virtual QString name() const override;
    virtual QString info() const override;
    virtual void populatePropertiesWidget(QWidget* parent) override;
    virtual void initWithDefaultProperties() override;
    virtual QString persistentClassName() const override;
    virtual QByteArray serialize() const override;
    virtual void deserialize(const QByteArray& data) override;
    virtual void previewOfGraph(QCustomPlot* plotWidget) const override;
    virtual AbstractDataLoader* clone() const override;
    virtual void importFile(const QString& filename, RealDataItem* item, QStringList* errors,
                            QStringList* warnings) const override;

private:
    QString m_name;
    AbstractDataLoader1D* m_wrappedLoader;
    QByteArray m_defaultProperties;
};

#endif // GUI_COREGUI_DATALOADERS_USERDEFINEDDATALOADER1D_H
