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
class AutomaticMultiColumnDataLoader1DProperties;

class AutomaticMultiColumnDataLoader1D : public AbstractDataLoader1D {
public:
    AutomaticMultiColumnDataLoader1D();
    virtual QString name() const override;
    virtual QString info() const override;
    virtual QString persistentClassName() const override;
    virtual QVector<QVector<QString>> parsedData() const override;
    virtual QString preview(const QString& filepath, QCustomPlot* plotWidget) const override;
    virtual void fillPropertiesGroupBox(QGroupBox* parent) override;
    virtual void initWithDefaultProperties() override;
    virtual void applyProperties() override;
    virtual QByteArray serialize() const override;
    virtual void deserialize(const QByteArray& data) override;

private:
    QVector<QPair<int, int>> expandLineNumberPattern(const QString& pattern,
                                                     bool* ok = nullptr) const;

private:
    struct ColumnDefinition {
        int dataType; // #TODO: enum or ... (Q, R, dR, ...)
        QString unit;
        double factor;
    };
    QString m_separator;    //!< column separator
    QString m_headerPrefix; //!< prefix denoting header line
    QString m_linesToSkip;  //!< pattern denoting line to skip (i.e. '1,10-12,42')
    QMap<int, ColumnDefinition> m_columnDefinitions;
    QPointer<AutomaticMultiColumnDataLoader1DProperties> m_propertiesWidget;
};

#endif // _GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1D_H_
