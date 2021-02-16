//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/QREDataLoader.h
//! @brief     Defines class QREDataLoader
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef GUI_COREGUI_DATALOADERS_QREDATALOADER_H
#define GUI_COREGUI_DATALOADERS_QREDATALOADER_H

#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"
#include <QVector>

class QString;
class QREDataLoaderProperties;

class QREDataLoader : public AbstractDataLoader1D {
public:
    QREDataLoader();
    virtual QString name() const override;
    virtual QString info() const override;
    virtual QString persistentClassName() const override;
    virtual QString preview(const QString& filepath, QCustomPlot* plotWidget) const override;
    virtual void populatePropertiesWidget(QWidget* parent) override;
    virtual void initWithDefaultProperties() override;
    virtual void applyProperties() override;
    virtual QByteArray serialize() const override;
    virtual void deserialize(const QByteArray& data) override;
    virtual AbstractDataLoader* clone() const override;

private:
    enum class UnitInFile {
        none,
        perNanoMeter,
        perAngstrom,
        other
    };

    struct ColumnDefinition {
        bool enabled;
        int column;
        UnitInFile unit;
        double factor;
    };

    enum class DataType { Q, R, dR };

    QString m_separator;    //!< column separator
    QString m_headerPrefix; //!< prefix denoting header line
    QString m_linesToSkip;  //!< pattern denoting line to skip (i.e. '1,10-12,42')
    QPointer<QREDataLoaderProperties> m_propertiesWidget;

    QMap<DataType, ColumnDefinition> m_columnDefinitions;
};

#endif // GUI_COREGUI_DATALOADERS_QREDATALOADER_H
