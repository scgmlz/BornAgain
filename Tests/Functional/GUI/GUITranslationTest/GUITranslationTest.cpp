// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITranslationTest/GUITranslationTest.cpp
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
#include "SimulationFactory.h"
#include "SampleBuilderFactory.h"
#include "GISASSimulation.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "GUIObjectBuilder.h"
#include "ApplicationModels.h"
#include "JobModel.h"
#include "DocumentModel.h"
#include "JobItem.h"
#include "ParameterTreeBuilder.h"
#include "ParameterTreeItems.h"
#include "ParameterPool.h"
#include "GUIHelpers.h"
#include "StringUtils.h"
#include <QStack>
#include <QDebug>


GUITranslationTest::GUITranslationTest(const std::string &simName, const std::string &sampleName)
    : m_models(new ApplicationModels(0))
    , m_simulationName(simName)
    , m_sampleName(sampleName)
{
    SimulationFactory simFactory;
    m_simulation.reset(simFactory.createItem(m_simulationName));

    SampleBuilderFactory sampleFactory;
    m_simulation->setSample(*sampleFactory.createSample(m_sampleName));
}

GUITranslationTest::~GUITranslationTest()
{

}

bool GUITranslationTest::runTest()
{
    processParameterTree();
    bool success = checkExistingTranslations();

    // Uncomment line below to check missed translation (i.e. when fit parameter exist in domain
    // but doesn't exist in GUI (like thickness of top layer)
    //success &= checkMissedTranslations();

    if(!success) {
        std::cout << "GUITranslationTest failed: " << m_simulationName
                  << " " << m_sampleName << std::endl;
        std::cout << "Available simulation parameters" << std::endl;
        m_simulation->printParameters();
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

    ParameterTreeBuilder::populateDomainLinks(jobItem, JobItem::T_PARAMETER_TREE);

    SessionItem *current = jobItem->getItem(JobItem::T_PARAMETER_TREE);

    QStack<SessionItem *> stack;
    stack.push(current);
    while (!stack.empty()) {
        current = stack.pop();
        if (current->modelType() == Constants::ParameterLabelType
                || current->modelType() == Constants::ParameterContainerType) {
            for (SessionItem *child : current->getItems())
                stack.push(child);

        } else {
            if (ParameterItem *parItem = dynamic_cast<ParameterItem *>(current)) {
                if(parItem->isFittable()) {
                    std::string guiName =
                            parItem->getItemValue(ParameterItem::P_LINK).toString().toStdString();
                    std::string domainName = std::string("*") +
                            parItem->getItemValue(ParameterItem::P_DOMAIN).toString().toStdString();
                    m_translations.push_back({guiName, domainName});
                }
            }
        }
    }

}

//! Validates GUI translations against simulation parameters. Tries to retrieve fit parameter
//! from domain parameter pool using translated name.

bool GUITranslationTest::checkExistingTranslations()
{
    if(m_translations.empty())
        throw GUIHelpers::Error("GUITranslationTest::validateParameterTree() -> Error. "
                                "Empty list of translations.");

    std::unique_ptr<ParameterPool> pool(m_simulation->createParameterTree());
    std::vector<name_pair> wrong_translations;
    for(auto pair : m_translations) {
        try {
            pool->getMatchedParameters(pair.translatedName);
        } catch (const std::runtime_error &/*ex*/) {
            wrong_translations.push_back(pair);
        }
    }

    if(wrong_translations.size() > 0) {
        std::cout << std::string(80, '-') << std::endl;
        std::cout << "Translation doesn't match domain parameters:" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        for(auto pair : wrong_translations) {
            std::cout << "gui         : " << pair.guiName << std::endl;
            std::cout << "translation : " << pair.translatedName << std::endl;
            std::cout << std::string(8, '-') << std::endl;
        }
    }

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
    std::vector<std::string> domainNames = pool->getParameterNames();
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
        if(!translationFound) {
            missedNames.push_back(name);
        }
    }

    if(missedNames.size() > 1) {
        std::cout << std::string(80, '-') << std::endl;
        std::cout << "Translation doesn't exist:" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        for(auto name : missedNames) {
            std::cout << "domain : " << name << std::endl;
        }
    }

    bool isSuccess = (missedNames.empty() ? true : false);
    return isSuccess;
}
