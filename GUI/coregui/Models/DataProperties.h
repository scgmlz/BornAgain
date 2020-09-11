// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataProperties.h
//! @brief     Defines class DataProperties and its descendants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DATAPROPERTIES_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DATAPROPERTIES_H

#include "GUI/coregui/Models/SessionItem.h"

class DataItem;

//! Implements a link to DataItem. If path name
//! of a DataItem changes, the link becomes invalid.
//! Also serves as a base for Data1DProperties
class BA_CORE_API_ DataProperties : public SessionItem
{
public:
    static const QString P_DATALINK;

    void setDataItem(DataItem* item);
    DataItem* dataItem();

protected:
    DataProperties(const QString& model_type);
};

//! Holds data required for 1D DataItem representation
class BA_CORE_API_ Data1DProperties : public DataProperties
{
public:
    static const QString P_COLOR;

    Data1DProperties();

    //! Creates and returns a color object from color name in Data1DPresentationProperties
    QColor color();

    //! Returns set up color ComboProperty.
    void setColorProperty(const QString& color_name);

    //! Returns the name of the color, which follows the color of passes property
    //! container. If the container is nullptr or has the last-in-queue color,
    //! returns default color.
    static const QString& nextColorName(Data1DProperties* properties);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DATAPROPERTIES_H
