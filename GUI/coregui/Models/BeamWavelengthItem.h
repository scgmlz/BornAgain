// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamWavelengthItem.h
//! @brief     Defines class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_BEAMWAVELENGTHITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_BEAMWAVELENGTHITEM_H

#include "GUI/coregui/Models/BeamDistributionItem.h"

class BA_CORE_API_ BeamWavelengthItem : public BeamDistributionItem
{
public:
    BeamWavelengthItem(const QString& model_type = "BeamWavelength",
                       const QString& distribution_group = "Distribution extended group");

    double wavelength() const;

private:
    static const bool m_show_mean = true;
};

class BA_CORE_API_ SpecularBeamWavelengthItem : public BeamWavelengthItem
{
public:
    SpecularBeamWavelengthItem();
    void setToRange(const RealLimits& limits);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_BEAMWAVELENGTHITEM_H
