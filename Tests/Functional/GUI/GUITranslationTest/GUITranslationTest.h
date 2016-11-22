// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITranslationTest/GUITranslationTest.h
//! @brief     Defines GUI translation functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUITRANSLATIONTEST_H
#define GUITRANSLATIONTEST_H

#include "IFunctionalTest.h"
#include <memory>
#include <vector>
#include <string>
#include <map>

class GISASSimulation;
class ApplicationModels;

//! Functional test to validate translation mechanism of GUI names into domain fit parameter names.
//! * Constructs domain simulation using given sample builder and simulation name.
//! * Converts domain simulation into GUI model presentation.
//! * Constructs list of GUI fittable parameters, and then translate their names into domain names.
//! * Complains, if translated names doesn't match registered parameters of domain simulation.
//! * Complains, if simulation contains parameters which do not have translations.

class GUITranslationTest : public IFunctionalTest
{
public:
    GUITranslationTest(const std::string &simName, const std::string &sampleName);

    ~GUITranslationTest();
    bool runTest();

private:
    struct name_pair {
        std::string guiName;
        std::string translatedName;
    };

    void processParameterTree();
    bool checkExistingTranslations();
    bool checkMissedTranslations();
    std::unique_ptr<GISASSimulation> m_simulation;
    std::unique_ptr<ApplicationModels> m_models;
    //!< Vector of GUI parameter names and their translations to domain parameter names.
    std::vector<name_pair> m_translations;
    std::string m_simulationName, m_sampleName;
};

#endif // GUITRANSLATIONTEST_H
