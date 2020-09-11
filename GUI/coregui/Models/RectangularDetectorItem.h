// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RectangularDetectorItem.h
//! @brief     Defines class RectangularDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_RECTANGULARDETECTORITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_RECTANGULARDETECTORITEM_H

#include "Core/Vector/Vectors3D.h"
#include "GUI/coregui/Models/DetectorItems.h"

class BA_CORE_API_ RectangularDetectorItem : public DetectorItem
{
public:
    static const QString P_X_AXIS;
    static const QString P_Y_AXIS;
    static const QString P_ALIGNMENT;
    static const QString P_NORMAL;
    static const QString P_DIRECTION;
    static const QString P_U0;
    static const QString P_V0;
    static const QString P_DBEAM_U0;
    static const QString P_DBEAM_V0;
    static const QString P_DISTANCE;

    RectangularDetectorItem();

    void setDetectorAlignment(const QString& alignment);

    int xSize() const override;
    int ySize() const override;
    void setXSize(int nx) override;
    void setYSize(int ny) override;

private:
    std::unique_ptr<IDetector2D> createDomainDetector() const override;
    void update_properties_appearance();
    kvector_t normalVector() const;
    kvector_t directionVector() const;

    bool m_is_constructed;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_RECTANGULARDETECTORITEM_H
