// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SphericalDetectorItem.h
//! @brief     Defines class SphericalDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SPHERICALDETECTORITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SPHERICALDETECTORITEM_H

#include "GUI/coregui/Models/DetectorItems.h"

class BA_CORE_API_ SphericalDetectorItem : public DetectorItem
{
public:
    static const QString P_PHI_AXIS;
    static const QString P_ALPHA_AXIS;
    SphericalDetectorItem();

    int xSize() const override;
    int ySize() const override;
    void setXSize(int nx) override;
    void setYSize(int ny) override;

protected:
    std::unique_ptr<IDetector2D> createDomainDetector() const override;
    double axesToDomainUnitsFactor() const override;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SPHERICALDETECTORITEM_H
