// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SampleValidator.h
//! @brief     Defines class SampleValidator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SAMPLEVALIDATOR_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SAMPLEVALIDATOR_H

#include <QModelIndex>

class SessionItem;
class MultiLayerItem;

//! Validates SampleModel for MultiLayerItem suitable for simulation
class SampleValidator
{
public:
    SampleValidator();

    bool isValidMultiLayer(const MultiLayerItem* multilayer);

    QString getValidationMessage() const { return m_validation_message; }

private:
    void initValidator();

    void iterateItems(const SessionItem* parentItem);
    void validateItem(const SessionItem* item);

    QString validateMultiLayerItem(const SessionItem* item);
    QString validateParticleLayoutItem(const SessionItem* item);
    QString validateParticleCoreShellItem(const SessionItem* item);
    QString validateParticleCompositionItem(const SessionItem* item);
    QString validateParticleDistributionItem(const SessionItem* item);

    bool m_valid_sample;
    QString m_validation_message;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SAMPLEVALIDATOR_H
