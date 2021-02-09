//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.h
//! @brief     Defines class RealDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORWIDGET_H

#include <QWidget>

class RealDataPropertiesWidget;
class ItemSelectorWidget;
class InstrumentModel;
class RealDataModel;
class SessionItem;
class RealDataSelectorActions;
class RealDataItem;

//! The RealDataSelectorWidget represents left panel of ImportDataView. Contains a widget to
//! select data set (ItemSelectorWidget) and properties of currently selected data
//! (RealDataPropertiesWidget).

class RealDataSelectorWidget : public QWidget {
    Q_OBJECT

public:
    RealDataSelectorWidget(QWidget* parent = 0);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setModels(InstrumentModel* instrumentModel, RealDataModel* realDataModel);

signals:
    void selectionChanged(SessionItem*);

public slots:
    void onSelectionChanged(SessionItem* item);
    void onContextMenuRequest(const QPoint& point, const QModelIndex& indexAtPoint);
    void onRenameDataRequest();
    void updateActionEnabling();
    void updateActionEnabling(const RealDataItem* item);

private:
    RealDataItem* toRealDataItem(const QModelIndex& index) const;

private:
    RealDataSelectorActions* m_selectorActions;
    ItemSelectorWidget* m_selectorWidget;
    RealDataPropertiesWidget* m_propertiesWidget;
    QAction* m_renameDataAction;
    RealDataModel* m_realDataModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORWIDGET_H
