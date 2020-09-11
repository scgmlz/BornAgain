// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.h
//! @brief     Defines class RealDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class RealDataPropertiesWidget;
class ItemSelectorWidget;
class RealDataPropertiesWidget;
class InstrumentModel;
class RealDataModel;
class SessionItem;
class RealDataSelectorActions;
class RealDataSelectorToolBar;
class RealDataSelectorHBar;
namespace Manhattan
{
class MiniSplitter;
}

//! The RealDataSelectorWidget represents left panel of ImportDataView. Contains a widget to
//! select data set (ItemSelectorWidget) and properties of currently selected data
//! (RealDataPropertiesWidget).

class BA_CORE_API_ RealDataSelectorWidget : public QWidget
{
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

private:
    RealDataSelectorActions* m_selectorActions;
    RealDataSelectorToolBar* m_toolBar;
    RealDataSelectorHBar* m_hamBar;
    Manhattan::MiniSplitter* m_splitter;
    ItemSelectorWidget* m_selectorWidget;
    RealDataPropertiesWidget* m_propertiesWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORWIDGET_H
