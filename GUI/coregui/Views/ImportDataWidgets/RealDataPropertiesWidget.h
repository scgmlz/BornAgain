//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.h
//! @brief     Defines class RealDataPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATAPROPERTIESWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATAPROPERTIESWIDGET_H

#include <QWidget>

class RealDataItem;
class QComboBox;
class QLabel;

//! The RealDataPropertiesWidget class holds instrument selector to link with RealDataItem.
//! Part of RealDataSelectorWidget, resides at lower left corner of ImportDataView.

class RealDataPropertiesWidget : public QWidget {
    Q_OBJECT
public:
    explicit RealDataPropertiesWidget(QWidget* parent = 0);

    QSize sizeHint() const { return QSize(64, 135); }
    QSize minimumSizeHint() const { return QSize(64, 128); }

    void setItem(RealDataItem* item);

public slots:
    void onInstrumentComboIndexChanged(int index);
    void updateInstrumentComboEntries();
    void onRealDataPropertyChanged(const QString& name);

private:
    void setComboToIdentifier(const QString& instrumentId);
    void setPropertiesEnabled(bool enabled);

    QComboBox* m_instrumentCombo;
    RealDataItem* m_currentDataItem;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATAPROPERTIESWIDGET_H
