// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/PointwiseAxisItem.h
//! @brief     Defines pointwise axis item
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_POINTWISEAXISITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_POINTWISEAXISITEM_H

#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/mainwindow/SaveLoadInterface.h"

class PointwiseAxis;
class SpecularInstrumentItem;

//! Item for non-uniform axis with specified coordinates.
class BA_CORE_API_ PointwiseAxisItem : public BasicAxisItem, public SaveLoadInterface
{
    static const QString P_NATIVE_AXIS_UNITS;

public:
    static const QString P_FILE_NAME;

    explicit PointwiseAxisItem();
    ~PointwiseAxisItem() override;

    // setters, getters
    void init(const IAxis& axis, const QString& units_label);
    const IAxis* getAxis() const;
    const QString getUnitsLabel() const;

    // virtual function overloads
    bool containsNonXMLData() const override;
    QDateTime lastModified() const override;
    QString fileName() const override;
    std::unique_ptr<IAxis> createAxis(double scale) const override;

    void updateIndicators();

private:
    bool load(const QString& projectDir) override;
    bool save(const QString& projectDir) override;
    void setLastModified(const QDateTime& dtime);

    bool checkValidity() const;
    void findInstrument();

    const SpecularInstrumentItem* m_instrument;
    std::unique_ptr<IAxis> m_axis;
    QDateTime m_last_modified;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_POINTWISEAXISITEM_H
