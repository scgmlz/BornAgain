// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SpecularBeamInclinationItem.h
//! @brief     Declares the class SpecularBeamInclinationItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SPECULARBEAMINCLINATIONITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SPECULARBEAMINCLINATIONITEM_H

#include "GUI/coregui/Models/BeamDistributionItem.h"

//! BeamInclinationAxisItem contains inclination angle axis for specular/off-specular
//! simulations and also provides distribution functionality.
//! Considering distribution, differs from BeamInclinationAngleItem
//! by any distribution mean value being always zero.

class BA_CORE_API_ SpecularBeamInclinationItem : public BeamDistributionItem
{
public:
    static const QString P_ALPHA_AXIS;

    SpecularBeamInclinationItem();
    ~SpecularBeamInclinationItem() override;

    double scaleFactor() const override;

    void updateFileName(const QString& filename);

private:
    void setupAxisGroup();
    static const bool m_show_mean = false;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SPECULARBEAMINCLINATIONITEM_H
