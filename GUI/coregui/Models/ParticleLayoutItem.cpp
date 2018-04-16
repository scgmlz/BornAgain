// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleLayoutItem.cpp
//! @brief     Implements class ParticleLayoutItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParticleLayoutItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "InterferenceFunctionItems.h"
#include "Lattice2DItems.h"
#include <QDebug>

namespace
{

//! Returns true if name is related to 2D interference functions.
bool isInterference2D(const QString& name)
{
    if (name == Constants::InterferenceFunction2DLatticeType
        || name == Constants::InterferenceFunctionFinite2DLatticeType
        || name == Constants::InterferenceFunction2DParaCrystalType)
        return true;
    return false;
}

//! Returns true if name is related to 2D interference functions.
bool isLattice2D(SessionItem* item) { return dynamic_cast<Lattice2DItem*>(item) ? true : false; }

const QString density_tooltip
    = "Number of particles per square nanometer (particle surface density).\n "
      "Should be defined for disordered and 1d-ordered particle collections.";
}

const QString ParticleLayoutItem::P_APPROX = "Approximation";
const QString ParticleLayoutItem::P_TOTAL_DENSITY
    = QString::fromStdString(BornAgain::TotalParticleDensity);
const QString ParticleLayoutItem::T_PARTICLES = "Particle Tag";
const QString ParticleLayoutItem::T_INTERFERENCE = "Interference Tag";

ParticleLayoutItem::ParticleLayoutItem() : SessionGraphicsItem(Constants::ParticleLayoutType)
{
    setToolTip(QStringLiteral("A layout of particles"));

    ComboProperty approx = ComboProperty() << Constants::LAYOUT_DA << Constants::LAYOUT_SSCA;
    addProperty(P_APPROX, approx.variant())
        ->setToolTip(QStringLiteral("Approximation used to distribute the particles"));
    addProperty(P_TOTAL_DENSITY, 1.0)->setToolTip(density_tooltip);
    getItem(P_TOTAL_DENSITY)->setDecimals(10);

    registerTag(T_PARTICLES, 0, -1,
                QStringList() << Constants::ParticleType << Constants::ParticleCoreShellType
                              << Constants::ParticleCompositionType << Constants::MesoCrystalType
                              << Constants::ParticleDistributionType);
    setDefaultTag(T_PARTICLES);
    registerTag(T_INTERFERENCE, 0, 1,
                QStringList() << Constants::InterferenceFunctionRadialParaCrystalType
                              << Constants::InterferenceFunction2DParaCrystalType
                              << Constants::InterferenceFunction1DLatticeType
                              << Constants::InterferenceFunction2DLatticeType
                              << Constants::InterferenceFunctionFinite2DLatticeType);

    mapper()->setOnChildrenChange([this](SessionItem*) {
        updateDensityAppearance();
        updateDensityValue();
    });

    mapper()->setOnAnyChildChange([this](SessionItem* item) {
        if (isLattice2D(item) || (item && isLattice2D(item->parent())))
            updateDensityValue();
    });
}

//! Disables/enables total density property, depending on type of interference function.
//! Two dimensional interference calculates density automatically, so property should
//! be disabled.

void ParticleLayoutItem::updateDensityAppearance()
{
    getItem(P_TOTAL_DENSITY)->setEnabled(true);
    if (auto interferenceItem = getItem(T_INTERFERENCE))
        if (isInterference2D(interferenceItem->modelType()))
            getItem(P_TOTAL_DENSITY)->setEnabled(false);
}

//! Updates the value of TotalSurfaceDensity on lattice type change.

void ParticleLayoutItem::updateDensityValue()
{
    if (auto interferenceItem = getItem(T_INTERFERENCE)) {
        if (interferenceItem->isTag(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)) {
            auto& latticeItem = interferenceItem->groupItem<Lattice2DItem>(
                InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
            double area = latticeItem.unitCellArea();
            setItemValue(P_TOTAL_DENSITY, area == 0.0 ? 0.0 : 1.0 / area);
        }
    }
}
