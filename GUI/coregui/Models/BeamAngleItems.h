// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamAngleItems.h
//! @brief     Defines class BeamAngleItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_BEAMANGLEITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_BEAMANGLEITEMS_H

#include "GUI/coregui/Models/BeamDistributionItem.h"

class BA_CORE_API_ BeamAzimuthalAngleItem : public BeamDistributionItem
{
public:
    BeamAzimuthalAngleItem();

    double azimuthalAngle() const;

    double scaleFactor() const override;

private:
    static const bool m_show_mean = true;
};

class BA_CORE_API_ BeamInclinationAngleItem : public BeamDistributionItem
{
public:
    BeamInclinationAngleItem();

    double inclinationAngle() const;

    double scaleFactor() const override;

private:
    static const bool m_show_mean = true;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_BEAMANGLEITEMS_H
