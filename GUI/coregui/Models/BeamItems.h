// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamItems.h
//! @brief     Defines BeamItem hierarchy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_BEAMITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_BEAMITEMS_H

#include "GUI/coregui/Models/SessionItem.h"

class BasicAxisItem;
class Beam;
class FootprintItem;
class GroupItem;
class IAxis;

class BA_CORE_API_ BeamItem : public SessionItem
{
public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    static const QString P_INCLINATION_ANGLE;
    static const QString P_AZIMUTHAL_ANGLE;
    static const QString P_POLARIZATION;

    ~BeamItem() override;

    double getIntensity() const;
    void setIntensity(double value);

    double getWavelength() const;
    void setWavelength(double value);

    virtual double getInclinationAngle() const = 0;
    virtual void setInclinationAngle(double value);

    double getAzimuthalAngle() const;
    void setAzimuthalAngle(double value);

    std::unique_ptr<Beam> createBeam() const;

protected:
    explicit BeamItem(const QString& beam_model);

    void setInclinationProperty(const QString& inclination_type);
    void setWavelengthProperty(const QString& wavelength_type);
};

class BA_CORE_API_ SpecularBeamItem : public BeamItem
{
public:
    static const QString P_FOOPTPRINT;

    SpecularBeamItem();
    ~SpecularBeamItem() override;

    double getInclinationAngle() const override;
    void setInclinationAngle(double value) override;

    GroupItem* inclinationAxisGroup();
    BasicAxisItem* currentInclinationAxisItem();
    FootprintItem* currentFootprintItem() const;

    void updateFileName(const QString& filename);
    void updateToData(const IAxis& axis, QString units);

private:
    void updateWavelength();
};

class BA_CORE_API_ GISASBeamItem : public BeamItem
{
public:
    GISASBeamItem();
    ~GISASBeamItem() override;

    double getInclinationAngle() const override;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_BEAMITEMS_H
