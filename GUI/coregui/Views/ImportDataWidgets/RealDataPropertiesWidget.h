// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.h
//! @brief     Defines class RealDataPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATAPROPERTIESWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATAPROPERTIESWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class LinkInstrumentManager;
class SessionItem;
class InstrumentModel;
class RealDataModel;
class RealDataItem;
class QDataWidgetMapper;
class QLineEdit;
class QComboBox;
class QLabel;

//! The RealDataPropertiesWidget class holds instrument selector to link with RealDataItem.
//! Part of RealDataSelectorWidget, resides at lower left corner of ImportDataView.

class BA_CORE_API_ RealDataPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RealDataPropertiesWidget(QWidget* parent = 0);

    QSize sizeHint() const { return QSize(64, 135); }
    QSize minimumSizeHint() const { return QSize(64, 128); }

    void setModels(InstrumentModel* instrumentModel, RealDataModel* realDataModel);
    void setItem(SessionItem* item);

public slots:
    void onInstrumentComboIndexChanged(int index);
    void onInstrumentMapUpdate();
    void onRealDataPropertyChanged(const QString& name);

private:
    void setComboToIdentifier(const QString& identifier);
    void setComboConnected(bool isConnected);
    void setPropertiesEnabled(bool enabled);

    LinkInstrumentManager* m_linkManager;
    QDataWidgetMapper* m_dataNameMapper;
    QLabel* m_dataNameLabel;
    QLineEdit* m_dataNameEdit;
    QLabel* m_instrumentLabel;
    QComboBox* m_instrumentCombo;
    QString m_current_id;
    RealDataItem* m_currentDataItem;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATAPROPERTIESWIDGET_H
