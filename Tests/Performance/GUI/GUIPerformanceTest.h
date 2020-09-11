// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/GUI/GUIPerformanceTest.h
//! @brief     Defines GUI performance functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_PERFORMANCE_GUI_GUIPERFORMANCETEST_H
#define BORNAGAIN_TESTS_PERFORMANCE_GUI_GUIPERFORMANCETEST_H

#include <QString>
#include <memory>

class ApplicationModels;

//! Functional test to measure performance of GUI by mimicking activity typical for RealTimeView.

class GUIPerformanceTest
{
public:
    GUIPerformanceTest();

    void test_domain_to_gui();
    void test_gui_to_domain();
    void test_real_time();

    bool runTest();

private:
    std::unique_ptr<ApplicationModels> m_models;
    QString m_sample_name;
};

#endif // BORNAGAIN_TESTS_PERFORMANCE_GUI_GUIPERFORMANCETEST_H
