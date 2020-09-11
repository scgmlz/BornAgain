// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/Translate/GUITranslationTest.cpp
//! @brief     Includes GUI translation functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/Translate/GUITranslationTest.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Fit/Tools/StringUtils.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/FitParameterHelper.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/ParameterTreeUtils.h"
#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SphericalDetectorItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QStack>

namespace
{

bool containsNames(const QString& text, const QStringList& names)
{
    for (const auto& name : names)
        if (text.contains(name))
            return true;
    return false;
}

const QVector<QPair<QStringList, QStringList>> black_list{
    {// Global scope
     {""},
     {"Sigma factor", "MaterialRefractiveData", "MaterialSLDData", MaterialItem::P_MAGNETIZATION}},
    {// Instrument scope
     {"GISASInstrument", "OffSpecInstrument", "SpecularInstrument"},
     {// Distribution types
      "DistributionGate", "DistributionLorentz", "DistributionGaussian", "DistributionLogNormal",
      "DistributionCosine", "DistributionTrapezoid",

      // Detector axes
      SphericalDetectorItem::P_PHI_AXIS, SphericalDetectorItem::P_ALPHA_AXIS,
      RectangularDetectorItem::P_X_AXIS, RectangularDetectorItem::P_Y_AXIS,
      OffSpecInstrumentItem::P_ALPHA_AXIS,

      // Rectangular detector positioning
      RectangularDetectorItem::P_ALIGNMENT, RectangularDetectorItem::P_NORMAL,
      RectangularDetectorItem::P_DIRECTION, RectangularDetectorItem::P_U0,
      RectangularDetectorItem::P_V0, RectangularDetectorItem::P_DBEAM_U0,
      RectangularDetectorItem::P_DBEAM_V0, RectangularDetectorItem::P_DISTANCE,

      // Detector resolution
      "ResolutionFunction2DGaussian",

      // Beam angle parameters
      BeamItem::P_INCLINATION_ANGLE, BeamItem::P_AZIMUTHAL_ANGLE}}};

//! Returns true, if it makes sence to look for GUI translation for given domain name.
//! Intended to supress warnings about not-yet implemented translations.
bool requiresTranslation(ParameterItem* parItem)
{
    if (!parItem)
        return false;

    const QString& par_path = FitParameterHelper::getParameterItemPath(parItem);

    for (const auto& item : black_list) {
        if (item.first.size() == 1 && item.first[0].isNull()) { // checking global scope
            if (containsNames(par_path, item.second))
                return false;
        } else { // checking everything else
            if (containsNames(par_path, item.first) && containsNames(par_path, item.second))
                return false;
        }
    }
    return true;
}

std::string header(size_t width = 80)
{
    return std::string(width, '-');
}

} // namespace

GUITranslationTest::GUITranslationTest(const std::string& simName, const std::string& sampleName)
    : m_models(new ApplicationModels(nullptr)), m_simulationName(simName), m_sampleName(sampleName)
{
    SimulationFactory simFactory;
    std::unique_ptr<Simulation> simulation = simFactory.createItemPtr(m_simulationName);
    if (GISASSimulation* gisas = dynamic_cast<GISASSimulation*>(simulation.get())) {
        m_simulation.reset(gisas);
        simulation.release();
    } else
        throw std::runtime_error("Error in GUITranslationTest: wrong simulation type.");

    SampleBuilderFactory sampleFactory;
    m_simulation->setSample(*sampleFactory.createSample(m_sampleName));
}

GUITranslationTest::~GUITranslationTest() {}

bool GUITranslationTest::runTest()
{
    processParameterTree();
    std::cout << translationResultsToString() << std::endl;

    bool success = checkExistingTranslations();
    success &= checkMissedTranslations();

    if (!success) {
        std::cout << "GUITranslationTest failed: " << m_simulationName << " " << m_sampleName
                  << std::endl;
    }

    return success;
}

//! Runs through GUI models and constructs list of available domain fit parameters names.

void GUITranslationTest::processParameterTree()
{
    m_models->instrumentModel()->clear();
    // populating GUI models from domain
    GUIObjectBuilder::populateSampleModelFromSim(m_models->sampleModel(), m_models->materialModel(),
                                                 *m_simulation);
    GUIObjectBuilder::populateInstrumentModel(m_models->instrumentModel(), *m_simulation);
    GUIObjectBuilder::populateDocumentModel(m_models->documentModel(), *m_simulation);

    JobItem* jobItem = m_models->jobModel()->addJob(
        m_models->sampleModel()->multiLayerItem(), m_models->instrumentModel()->instrumentItem(),
        nullptr, m_models->documentModel()->simulationOptionsItem());

    SessionItem* container = jobItem->parameterContainerItem();

    ParameterTreeUtils::visitParameterContainer(container, [&](ParameterItem* parItem) {
        if (requiresTranslation(parItem)) {
            std::string sampleParLink =
                parItem->getItemValue(ParameterItem::P_LINK).toString().toStdString();

            std::string parPath = FitParameterHelper::getParameterItemPath(parItem).toStdString();

            std::string domainName =
                std::string("*")
                + parItem->getItemValue(ParameterItem::P_DOMAIN).toString().toStdString();

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

    for (auto guiPar : m_translations) {
        ostr << "GUI sampleLink : " << guiPar.sampleParLink << "\n";
        ostr << "GUI parPath    : " << guiPar.parPath << "\n";
        ostr << "Translated     : " << guiPar.translatedName << "\n\n";
    }
    return ostr.str();
}

bool GUITranslationTest::isValidDomainName(const std::string& domainName) const
{
    std::vector<std::string> invalidNames{"Direction", "Efficiency", "Transmission",
                                          "InclinationAngle", "AzimuthalAngle"};
    for (auto name : invalidNames) {
        if (domainName.find(name) != std::string::npos)
            return false;
    }
    return true;
}

//! Returns true, if it makes sence to look for domain translation for given GUI name.
//! Intended to supress warnings about not-yet implemented translations.

bool GUITranslationTest::isValidGUIName(const std::string& guiName) const
{
    std::vector<std::string> invalidNames{};
    for (auto name : invalidNames) {
        if (guiName.find(name) != std::string::npos)
            return false;
    }
    return true;
}

//! Validates GUI translations against simulation parameters. Tries to retrieve fit parameter
//! from domain parameter pool using translated name.

bool GUITranslationTest::checkExistingTranslations()
{
    if (m_translations.empty())
        throw GUIHelpers::Error("GUITranslationTest::validateParameterTree() -> Error. "
                                "Empty list of translations.");

    std::unique_ptr<ParameterPool> pool(m_simulation->createParameterTree());
    std::vector<ParItem> wrong_translations;
    for (auto guiPar : m_translations) {
        if (!isValidGUIName(guiPar.parPath))
            continue;
        try {
            pool->getMatchedParameters(guiPar.translatedName);
        } catch (const std::runtime_error& /*ex*/) {
            wrong_translations.push_back(guiPar);
        }
    }

    std::ostringstream ostr;
    if (wrong_translations.size() > 0) {
        ostr << header() << std::endl;
        ostr << "Translation doesn't match domain parameters:" << std::endl;
        ostr << header() << std::endl;
        for (auto guiPar : wrong_translations) {
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
    if (m_translations.empty())
        throw GUIHelpers::Error("GUITranslationTest::validateParameterTree() -> Error. "
                                "Empty list of translations.");

    std::unique_ptr<ParameterPool> pool(m_simulation->createParameterTree());
    std::vector<std::string> domainNames = pool->parameterNames();
    std::vector<std::string> missedNames;
    for (auto name : domainNames) {
        std::string domainName = "*" + StringUtils::removeSubstring(name, "/GISASSimulation");

        bool translationFound(false);
        for (auto pair : m_translations) {
            if (pair.translatedName == domainName) {
                translationFound = true;
                break;
            }
        }
        if (!translationFound && isValidDomainName(domainName)) {
            missedNames.push_back(name);
        }
    }

    if (missedNames.size()) {
        std::cout << header() << std::endl;
        std::cout << "Translation doesn't exist:" << std::endl;
        std::cout << header() << std::endl;
        for (auto name : missedNames)
            std::cout << "domain : " << name << std::endl;
    }

    bool isSuccess = (missedNames.empty() ? true : false);
    return isSuccess;
}
