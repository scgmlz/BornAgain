// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataView.h
//! @brief     Defines class ImportDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAVIEW_H

#include "GUI/coregui/Views/CommonWidgets/ItemStackPresenter.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataPresenter.h"

class RealDataModel;
class RealDataSelectorWidget;
namespace Manhattan
{
class MiniSplitter;
}

//! The ImportDataView class is a main view for importing experimental data.

class BA_CORE_API_ ImportDataView : public QWidget
{
    Q_OBJECT

public:
    ImportDataView(class MainWindow* mainWindow);

public slots:
    void onSelectionChanged(SessionItem* item);

private:
    void setupConnections();

    Manhattan::MiniSplitter* m_splitter;
    RealDataSelectorWidget* m_selectorWidget;
    ItemStackPresenter<RealDataPresenter>* m_stackedWidget;
    RealDataModel* m_realDataModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAVIEW_H
