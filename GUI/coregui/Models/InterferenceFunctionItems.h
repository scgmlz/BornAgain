// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InterferenceFunctionItems.h
//! @brief     Defines InterferenceFunctionItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_INTERFERENCEFUNCTIONITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_INTERFERENCEFUNCTIONITEMS_H

#include "GUI/coregui/Models/SessionGraphicsItem.h"
class IInterferenceFunction;

class BA_CORE_API_ InterferenceFunctionItem : public SessionGraphicsItem
{
public:
    static const QString P_POSITION_VARIANCE;
    explicit InterferenceFunctionItem(const QString& modelType);
    virtual ~InterferenceFunctionItem();
    virtual std::unique_ptr<IInterferenceFunction> createInterferenceFunction() const = 0;

protected:
    void setPositionVariance(IInterferenceFunction* p_iff) const;
};

class BA_CORE_API_ InterferenceFunction1DLatticeItem : public InterferenceFunctionItem
{
public:
    static const QString P_LENGTH;
    static const QString P_ROTATION_ANGLE;
    static const QString P_DECAY_FUNCTION;
    InterferenceFunction1DLatticeItem();
    std::unique_ptr<IInterferenceFunction> createInterferenceFunction() const;
};

class BA_CORE_API_ InterferenceFunction2DLatticeItem : public InterferenceFunctionItem
{
public:
    static const QString P_LATTICE_TYPE;
    static const QString P_DECAY_FUNCTION;
    static const QString P_XI_INTEGRATION;
    InterferenceFunction2DLatticeItem();
    std::unique_ptr<IInterferenceFunction> createInterferenceFunction() const;

private:
    void update_rotation_availability();
};

class BA_CORE_API_ InterferenceFunction2DParaCrystalItem : public InterferenceFunctionItem
{
public:
    static const QString P_DAMPING_LENGTH;
    static const QString P_DOMAIN_SIZE1;
    static const QString P_DOMAIN_SIZE2;
    static const QString P_XI_INTEGRATION;
    static const QString P_PDF1;
    static const QString P_PDF2;
    InterferenceFunction2DParaCrystalItem();
    std::unique_ptr<IInterferenceFunction> createInterferenceFunction() const;

private:
    void update_rotation_availability();
    void update_distribution_displaynames();
};

class BA_CORE_API_ InterferenceFunctionFinite2DLatticeItem : public InterferenceFunctionItem
{
public:
    static const QString P_XI_INTEGRATION;
    static const QString P_DOMAIN_SIZE_1;
    static const QString P_DOMAIN_SIZE_2;
    InterferenceFunctionFinite2DLatticeItem();
    std::unique_ptr<IInterferenceFunction> createInterferenceFunction() const;

private:
    void update_rotation_availability();
};

class BA_CORE_API_ InterferenceFunctionHardDiskItem : public InterferenceFunctionItem
{
public:
    static const QString P_RADIUS;
    static const QString P_DENSITY;
    InterferenceFunctionHardDiskItem();
    std::unique_ptr<IInterferenceFunction> createInterferenceFunction() const;
};

class BA_CORE_API_ InterferenceFunctionRadialParaCrystalItem : public InterferenceFunctionItem
{
public:
    static const QString P_PEAK_DISTANCE;
    static const QString P_DAMPING_LENGTH;
    static const QString P_DOMAIN_SIZE;
    static const QString P_KAPPA;
    static const QString P_PDF;
    InterferenceFunctionRadialParaCrystalItem();
    std::unique_ptr<IInterferenceFunction> createInterferenceFunction() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_INTERFERENCEFUNCTIONITEMS_H
