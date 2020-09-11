// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SampleModel.h
//! @brief     Defines class SampleModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SAMPLEMODEL_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SAMPLEMODEL_H

#include "GUI/coregui/Models/SessionModel.h"

class MultiLayerItem;

//! Main model to hold sample items.

class BA_CORE_API_ SampleModel : public SessionModel
{
    Q_OBJECT

public:
    explicit SampleModel(QObject* parent = nullptr);

    SampleModel* createCopy(SessionItem* parent = nullptr);

    MultiLayerItem* multiLayerItem();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SAMPLEMODEL_H
