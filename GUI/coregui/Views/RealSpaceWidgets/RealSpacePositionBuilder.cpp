// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpacePositionBuilder.cpp
//! @brief     Implements class RealSpacePositionBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/RealSpaceWidgets/RealSpacePositionBuilder.h"
#include "GUI/coregui/Views/RealSpaceWidgets/IPositionBuilder.h"

RealSpacePositionBuilder::RealSpacePositionBuilder() : mP_pos_builder{new DefaultPositionBuilder()}
{
}

RealSpacePositionBuilder::~RealSpacePositionBuilder() = default;

void RealSpacePositionBuilder::visit(const InterferenceFunction1DLattice* p_iff)
{
    mP_pos_builder.reset(new Lattice1DPositionBuilder(p_iff));
}

void RealSpacePositionBuilder::visit(const InterferenceFunction2DLattice* p_iff)
{
    mP_pos_builder.reset(new Lattice2DPositionBuilder(p_iff));
}

void RealSpacePositionBuilder::visit(const InterferenceFunction2DParaCrystal* p_iff)
{
    mP_pos_builder.reset(new ParaCrystal2DPositionBuilder(p_iff));
}

void RealSpacePositionBuilder::visit(const InterferenceFunctionFinite2DLattice* p_iff)
{
    mP_pos_builder.reset(new Finite2DLatticePositionBuilder(p_iff));
}

void RealSpacePositionBuilder::visit(const InterferenceFunctionRadialParaCrystal* p_iff)
{
    mP_pos_builder.reset(new RadialParacrystalPositionBuilder(p_iff));
}

void RealSpacePositionBuilder::visit(const InterferenceFunctionNone*)
{
    mP_pos_builder.reset(new RandomPositionBuilder());
}

std::vector<std::vector<double>> RealSpacePositionBuilder::generatePositions(double layer_size,
                                                                             double density) const
{
    return mP_pos_builder->generatePositions(layer_size, density);
}
