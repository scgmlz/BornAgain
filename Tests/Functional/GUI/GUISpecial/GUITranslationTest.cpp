// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/GUITranslationTest.cpp
//! @brief     Includes GUI translation functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUITranslationTest.h"
#include "ApplicationModels.h"
#include "BeamItem.h"
#include "DocumentModel.h"
#include "FitParameterHelper.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "JobItem.h"
#include "JobModel.h"
#include "ModelPath.h"
#include "MultiLayer.h"
#include "MultiLayerItem.h"
#include "ParameterPool.h"
#include "ParameterTreeItems.h"
#include "ParameterTreeUtils.h"
#include "SampleBuilderFactory.h"
#include "SampleModel.h"
#include "SimulationFactory.h"
#include "StringUtils.h"
#include <QStack>

namespace {
    std::string header(size_t width=80) { return std::string(width, '-'); }
}

GUITranslationTest::GUITranslationTest(const std::string& simName, const std::string& sampleName)
    : m_models(new ApplicationModels(0))
    , m_simulationName(simName)
    , m_sampleName(sampleName)
{
    SimulationFactory simFactory;
    std::unique_ptr<Simulation> simulation = simFactory.create(m_simulationName);
    if (GISASSimulation* gisas = dynamic_cast<GISASSimulation*>(simulation.get())) {
        m_simulation.reset(gisas);
        simulation.release();
    } else
        throw std::runtime_error("Error in GUITranslationTest: wrong simulation type.");

    SampleBuilderFactory sampleFactory;
    m_simulation->setSample(*sampleFactory.createSample(m_sampleName));
}

GUITranslationTest::~GUITranslationTest()
{

}

bool GUITranslationTest::runTest()
{
    processParameterTree();
    std::cout << translationResultsToString() << std::endl;

    bool success = checkExistingTranslations();
    success &= checkMissedTranslations();

    if(!success) {
        std::cout << "GUITranslationTest failed: " << m_simulationName
                  << " " << m_sampleName << std::endl;
    }

    return success;
}

//! Runs through GUI models and constructs list of available domain fit parameters names.

void GUITranslationTest::processParameterTree()
{
    m_models->instrumentModel()->clear();
    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_models->sampleModel(), *m_simulation);
    guiBuilder.populateInstrumentModel(m_models->instrumentModel(), *m_simulation);
    guiBuilder.populateDocumentModel(m_models->documentModel(), *m_simulation);

    JobItem *jobItem = m_models->jobModel()->addJob(
                m_models->sampleModel()->multiLayerItem(),
                m_models->instrumentModel()->instrumentItem(),
                0,
                m_models->documentModel()->getSimulationOptionsItem());

    SessionItem *container = jobItem->parameterContainerItem();

    ParameterTreeUtils::visitParameterContainer(container, [&](ParameterItem *parItem){
        if(parItem->isFittable()) {
            std::string sampleParLink =
                    parItem->getItemValue(ParameterItem::P_LINK).toString().toStdString();

            std::string parPath = FitParameterHelper::getParameterItemPath(parItem).toStdString();

            std::string domainName = std::string("*") +
                    parItem->getItemValue(ParameterItem::P_DOMAIN).toString().toStdString();

            QString translation = ModelPath::itemPathTranslation(*parItem->linkedItem(), jobItem);
            domainName = std::string("*/") + translation.toStdString();

            m_translations.push_back({sampleParLink, parPath, domainName});
        }
    });
}

//! Returns multiline string representing results of translation

std::string GUITranslationTest::translationResultsToString() const
{
    std::ostringstream ostr;

    ostr << "\n" << header() << "\n";
    ostr << m_sampleName << "\n";
    ostr << header() << "\n";

    ostr << m_simulation->treeToString();

    auto domainPars = m_simulation->parametersToString();
    domainPars.pop_back(); // to remove extra "\n"
    ostr << domainPars;
    ostr << header(10) << "\n";

    for(auto guiPar : m_translations) {
        ostr << "GUI sampleLink : " << guiPar.sampleParLink << "\n";
        ostr << "GUI parPath    : " << guiPar.parPath << "\n";
        ostr << "Translated     : " << guiPar.translatedName << "\n\n";
    }
    return ostr.str();
}

//! Returns true, if it makes sence to look for GUI translation for given domain name.
//! Intended to supress warnings about not-yet implemented translations.

bool GUITranslationTest::isValidDomainName(const std::string& domainName) const
{
    std::vector<std::string> invalidNames {
        BornAgain::Direction,
        BornAgain::Efficiency,
        BornAgain::Transmission };
    for (auto name : invalidNames) {
        if (domainName.find(name) != std::string::npos)
            return false;
    }
    return true;
}

//! Returns true, if it makes sence to look for domain translation for given GUI name.
//! Intended to supress warnings about not-yet implemented translations.

bool GUITranslationTest::isValidGUIName(const std::string&) const
{
    return true;
}

//! Validates GUI translations against simulation parameters. Tries to retrieve fit parameter
//! from domain parameter pool using translated name.

bool GUITranslationTest::checkExistingTranslations()
{
    if(m_translations.empty())
        throw GUIHelpers::Error("GUITranslationTest::validateParameterTree() -> Error. "
                                "Empty list of translations.");

    std::unique_ptr<ParameterPool> pool(m_simulation->createParameterTree());
    std::vector<ParItem> wrong_translations;
    for(auto guiPar : m_translations) {
        if (!isValidGUIName(guiPar.parPath))
            continue;
        try {
            pool->getMatchedParameters(guiPar.translatedName);
        } catch (const std::runtime_error &/*ex*/) {
            wrong_translations.push_back(guiPar);
        }
    }

    std::ostringstream ostr;
    if(wrong_translations.size() > 0) {
        ostr << header() << std::endl;
        ostr << "Translation doesn't match domain parameters:" << std::endl;
        ostr << header() << std::endl;
        for(auto guiPar : wrong_translations) {
            ostr << "GUI sampleLink : " << guiPar.sampleParLink << "\n";
            ostr << "GUI parPath    : " << guiPar.parPath << "\n";
            ostr << "Translated     : " << guiPar.translatedName << "\n";
            ostr << header(8) << std::endl;
        }
    }
    std::cout << ostr.str();

    bool isSuccess = (wrong_translations.empty() ? true : false);
    return isSuccess;
}

//! Checks if all simulation parameters have translation.

bool GUITranslationTest::checkMissedTranslations()
{
    if(m_translations.empty())
        throw GUIHelpers::Error("GUITranslationTest::validateParameterTree() -> Error. "
                                "Empty list of translations.");

    std::unique_ptr<ParameterPool> pool(m_simulation->createParameterTree());
    std::vector<std::string> domainNames = pool->parameterNames();
    std::vector<std::string> missedNames;
    for(auto name : domainNames) {
        std::string domainName = "*" + StringUtils::removeSubstring(name, "/GISASSimulation");

        bool translationFound(false);
        for(auto pair : m_translations) {
            if(pair.translatedName == domainName) {
                translationFound = true;
                break;
            }
        }
        if(!translationFound && isValidDomainName(domainName)) {
            missedNames.push_back(name);
        }
    }

    if(missedNames.size()) {
        std::cout << header() << std::endl;
        std::cout << "Translation doesn't exist:" << std::endl;
        std::cout << header() << std::endl;
        for(auto name : missedNames)
            std::cout << "domain : " << name << std::endl;
    }

    bool isSuccess = (missedNames.empty() ? true : false);
    return isSuccess;
}
