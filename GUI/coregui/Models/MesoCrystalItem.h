// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MesoCrystalItem.h
//! @brief     Defines class MesoCrystalItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MESOCRYSTALITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MESOCRYSTALITEM_H

#include "Core/Lattice/Lattice.h"
#include "GUI/coregui/Models/SessionGraphicsItem.h"

class IFormFactor;
class IParticle;
class MesoCrystal;

class BA_CORE_API_ MesoCrystalItem : public SessionGraphicsItem
{
public:
    static const QString P_OUTER_SHAPE;
    static const QString T_BASIS_PARTICLE;
    static const QString P_VECTOR_A;
    static const QString P_VECTOR_B;
    static const QString P_VECTOR_C;

    MesoCrystalItem();

    std::unique_ptr<MesoCrystal> createMesoCrystal() const;

    QStringList translateList(const QStringList& list) const override;

    Lattice getLattice() const;
    std::unique_ptr<IParticle> getBasis() const;
    std::unique_ptr<IFormFactor> getOuterShape() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MESOCRYSTALITEM_H
