// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIExamplesFactory.h
//! @brief     Defines class GUIExamplesFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_GUIEXAMPLESFACTORY_H
#define BORNAGAIN_GUI_COREGUI_MODELS_GUIEXAMPLESFACTORY_H

#include "Wrap/WinDllMacros.h"
#include <QMap>

class SessionItem;
class SampleModel;
class MaterialModel;

//! Class that generates GUI model from
class BA_CORE_API_ GUIExamplesFactory
{
public:
    static bool isValidExampleName(const QString& name);

    static SessionItem* createSampleItems(const QString& name, SampleModel* sampleModel,
                                          MaterialModel* materialModel);
    //    static SessionItem *createInstrumentItems(const QString &name, InstrumentModel
    //    *instrumentModel);

private:
    static QMap<QString, QString> m_name_to_registry;
    //!< correspondance of GUI example name and name from StandardSamples registry
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_GUIEXAMPLESFACTORY_H
