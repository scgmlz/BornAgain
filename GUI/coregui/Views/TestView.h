// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/TestView.h
//! @brief     Defines class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_TESTVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_TESTVIEW_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MainWindow;

class BA_CORE_API_ TestView : public QWidget
{
    Q_OBJECT
public:
    TestView(MainWindow* mainWindow = nullptr);

private:
    void test_ComponentProxyModel();
    void test_MaterialEditor();
    void test_MinimizerSettings();
    void test_AccordionWidget();
    void test_ba3d();
    void test_specular_data_widget();

    MainWindow* m_mainWindow;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_TESTVIEW_H
