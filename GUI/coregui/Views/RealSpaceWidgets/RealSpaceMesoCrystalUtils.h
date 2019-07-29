// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceMesoCrystalUtils.h
//! @brief     Defines RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACEMESOCRYSTALUTILS_H
#define REALSPACEMESOCRYSTALUTILS_H

#include "Rotations.h"
#include "WinDllMacros.h"
#include <QVector3D>

class Particle;
class MesoCrystal;
class MesoCrystalItem;
class Particle3DContainer;

class RealSpaceMesoCrystal
{
public:
    ~RealSpaceMesoCrystal();

    RealSpaceMesoCrystal(const MesoCrystalItem* mesoCrystalItem, double total_abundance,
                         const QVector3D& origin);

    Particle3DContainer populateMesoCrystal();

private:
    const MesoCrystalItem* m_mesoCrystalItem;
    double m_total_abundance;
    QVector3D m_origin;
};

#endif // REALSPACEMESOCRYSTALUTILS_H
