// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/Translate/GUITranslationTest.h
//! @brief     Defines GUI translation functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_GUI_TRANSLATE_GUITRANSLATIONTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_GUI_TRANSLATE_GUITRANSLATIONTEST_H

#include <map>
#include <memory>
#include <string>
#include <vector>

class GISASSimulation;
class ApplicationModels;

//! Functional test to validate translation mechanism of GUI names into domain fit parameter names.
//! * Constructs domain simulation using given sample builder and simulation name.
//! * Converts domain simulation into GUI model presentation.
//! * Constructs list of GUI fittable parameters, and then translate their names into domain names.
//! * Complains, if translated names doesn't match registered parameters of domain simulation.
//! * Complains, if simulation contains parameters which do not have translations.

class GUITranslationTest
{
public:
    GUITranslationTest(const std::string& simName, const std::string& sampleName);

    ~GUITranslationTest();
    bool runTest();

private:
    struct ParItem {
        std::string sampleParLink;  //!< Link to GUI sample parameter
        std::string parPath;        //!< Path of corresponding ParameterItem
        std::string translatedName; //!< It's name translated to domain name
    };

    void processParameterTree();

    std::string translationResultsToString() const;

    bool isValidDomainName(const std::string& domainName) const;
    bool isValidGUIName(const std::string& guiName) const;

    bool checkExistingTranslations();
    bool checkMissedTranslations();

    std::unique_ptr<GISASSimulation> m_simulation;
    std::unique_ptr<ApplicationModels> m_models;
    //!< Vector of GUI parameter names and their translations to domain parameter names.
    std::vector<ParItem> m_translations;
    std::string m_simulationName, m_sampleName;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_GUI_TRANSLATE_GUITRANSLATIONTEST_H
