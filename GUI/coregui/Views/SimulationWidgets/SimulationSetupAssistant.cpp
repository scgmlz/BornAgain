// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationSetupAssistant.cpp
//! @brief     Implements class SimulationSetupAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SimulationWidgets/SimulationSetupAssistant.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SampleValidator.h"
#include "GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h"
#include <QMessageBox>

//! Returns true if given setup is valid for submitting the job

SimulationSetupAssistant::SimulationSetupAssistant() : m_isValid(false) {}

bool SimulationSetupAssistant::isValidSimulationSetup(const MultiLayerItem* multiLayerItem,
                                                      const InstrumentItem* instrumentItem,
                                                      const RealDataItem* realData)
{
    clear();

    checkMultiLayerItem(multiLayerItem);
    checkInstrumentItem(instrumentItem);
    checkFittingSetup(instrumentItem, realData);

    if (!m_isValid)
        QMessageBox::warning(nullptr, "Can't run the job", composeMessage());

    return m_isValid;
}

void SimulationSetupAssistant::clear()
{
    m_isValid = true;
    m_messages.clear();
}

void SimulationSetupAssistant::checkMultiLayerItem(const MultiLayerItem* multiLayerItem)
{
    if (!multiLayerItem) {
        m_messages.append("No sample selected");
        m_isValid = false;
    } else {
        SampleValidator sampleValidator;
        if (!sampleValidator.isValidMultiLayer(multiLayerItem)) {
            m_isValid = false;
            m_messages.append(sampleValidator.getValidationMessage());
        }
    }
}

void SimulationSetupAssistant::checkInstrumentItem(const InstrumentItem* instrumentItem)
{
    if (!instrumentItem) {
        m_messages.append("No instrument selected");
        m_isValid = false;
    }
}

//! Check if setup is suitable for fitting. In the case when there is a realData defined,
//! its axes will be compared with current detector item.

void SimulationSetupAssistant::checkFittingSetup(const InstrumentItem* instrumentItem,
                                                 const RealDataItem* realData)
{
    if (!realData || !instrumentItem || instrumentItem->alignedWith(realData))
        return;

    m_isValid = false;
    m_messages.append("The experimental data does not fit in the selected instrument. Try linking "
                      "them in Import Tab.");
}

//! Composes the error message for message box.

QString SimulationSetupAssistant::composeMessage()
{
    QString result("Can't run the job with current settings\n\n");
    for (auto message : m_messages) {
        QString text = QString("- %1 \n").arg(message);
        result.append(text);
    }
    return result;
}
