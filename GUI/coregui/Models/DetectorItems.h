// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DetectorItems.h
//! @brief     Defines classes DetectorItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DETECTORITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DETECTORITEMS_H

#include "GUI/coregui/Models/SessionItem.h"

class MaskContainerItem;
class IDetector2D;
class IResolutionFunction2D;
class DetectorItem;

class BA_CORE_API_ DetectorItem : public SessionItem
{
public:
    static const QString T_MASKS;
    static const QString P_RESOLUTION_FUNCTION;
    static const QString P_ANALYZER_DIRECTION;
    static const QString P_ANALYZER_EFFICIENCY;
    static const QString P_ANALYZER_TOTAL_TRANSMISSION;
    explicit DetectorItem(const QString& modelType);

    std::unique_ptr<IDetector2D> createDetector() const;

    // TODO: consider using index-based access functions

    //! returns the size of x-axis of the detector
    virtual int xSize() const = 0;

    //! returns the size of y-axis of the detector
    virtual int ySize() const = 0;

    //! sets the size of x-axis of the detector
    virtual void setXSize(int nx) = 0;

    //! sets the size of y-axis of the detector
    virtual void setYSize(int ny) = 0;

    void clearMasks();

    MaskContainerItem* maskContainerItem() const;

    void createMaskContainer();

    void importMasks(const MaskContainerItem* maskContainer);

protected:
    void register_resolution_function();
    void update_resolution_function_tooltips();

    virtual std::unique_ptr<IDetector2D> createDomainDetector() const = 0;
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction() const;

    //! Scales the values provided by axes (to perform deg->rad conversion on the way to domain).
    virtual double axesToDomainUnitsFactor() const { return 1.0; }

    void addMasksToDomain(IDetector2D* detector) const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DETECTORITEMS_H
