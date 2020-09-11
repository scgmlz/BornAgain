// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItem.h
//! @brief     Defines class MaterialItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MATERIALITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MATERIALITEM_H

#include "GUI/coregui/Models/SessionItem.h"

class Material;

class BA_CORE_API_ MaterialItem : public SessionItem
{
public:
    static const QString P_COLOR;
    static const QString P_MATERIAL_DATA;
    static const QString P_MAGNETIZATION;
    static const QString P_IDENTIFIER;

    MaterialItem();

    void setRefractiveData(double delta, double beta);
    void setSLDData(double sld_real, double sld_imag);

    QString identifier() const;
    QColor color() const;
    std::unique_ptr<Material> createMaterial() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MATERIALITEM_H
