// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIObjectBuilder.h
//! @brief     Defines GUIObjectBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_GUIOBJECTBUILDER_H
#define BORNAGAIN_GUI_COREGUI_MODELS_GUIOBJECTBUILDER_H

#include "Core/Parametrization/INodeVisitor.h"
#include <QMap>
#include <QString>

class Material;
class InstrumentModel;
class SampleModel;
class SessionItem;
class MaterialModel;
class DocumentModel;
class Simulation;
class ExternalProperty;

//! Contains set of methods to populate GUI models with content from domain.

namespace GUIObjectBuilder
{
SessionItem* populateSampleModelFromSim(SampleModel* sampleModel, MaterialModel* materialModel,
                                        const Simulation& simulation);

SessionItem* populateSampleModel(SampleModel* sampleModel, MaterialModel* materialModel,
                                 const MultiLayer& sample, const QString& sample_name = "");

SessionItem* populateInstrumentModel(InstrumentModel* p_instrument_model,
                                     const Simulation& simulation,
                                     const QString& instrument_name = "");

SessionItem* populateDocumentModel(DocumentModel* p_documentModel, const Simulation& simulation);
}; // namespace GUIObjectBuilder

#endif // BORNAGAIN_GUI_COREGUI_MODELS_GUIOBJECTBUILDER_H
