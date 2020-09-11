// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialModel.h
//! @brief     Defines class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MATERIALMODEL_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MATERIALMODEL_H

#include "GUI/coregui/Models/SessionModel.h"

class MaterialItem;
class ExternalProperty;

class BA_CORE_API_ MaterialModel : public SessionModel
{
    Q_OBJECT

public:
    explicit MaterialModel(QObject* parent = nullptr);
    ~MaterialModel();

    MaterialModel* createCopy(SessionItem* parent = nullptr);

    MaterialItem* addRefractiveMaterial(const QString& name, double delta, double beta);
    MaterialItem* addSLDMaterial(const QString& name, double sld, double abs_term);

    MaterialItem* materialFromIndex(const QModelIndex& index);
    MaterialItem* materialFromName(const QString& name);
    MaterialItem* materialFromIdentifier(const QString& identifier);

    MaterialItem* cloneMaterial(const QModelIndex& index);

private:
    MaterialItem* createMaterial(const QString& name);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MATERIALMODEL_H
