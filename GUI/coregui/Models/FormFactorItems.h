// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FormFactorItems.h
//! @brief     Defines FormFactorItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORITEMS_H
#define FORMFACTORITEMS_H

#include "SessionItem.h"

class IFormFactor;

class BA_CORE_API_ FormFactorItem : public SessionItem
{
public:
    explicit FormFactorItem(const QString& model_type) : SessionItem(model_type) {}
    virtual std::unique_ptr<IFormFactor> createFormFactor() const = 0;
};

class BA_CORE_API_ AnisoPyramidItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    AnisoPyramidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ BoxItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    BoxItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ ConeItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    ConeItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ Cone6Item : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    Cone6Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ CuboctahedronItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_HEIGHT;
    static const QString P_HEIGHT_RATIO;
    static const QString P_ALPHA;
    CuboctahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ CylinderItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    CylinderItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ DodecahedronItem : public FormFactorItem
{
public:
    static const QString P_EDGE;
    DodecahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ DotItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    DotItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ EllipsoidalCylinderItem : public FormFactorItem
{
public:
    static const QString P_RADIUS_X;
    static const QString P_RADIUS_Y;
    static const QString P_HEIGHT;
    EllipsoidalCylinderItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ FullSphereItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    FullSphereItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ FullSpheroidItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    FullSpheroidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ HemiEllipsoidItem : public FormFactorItem
{
public:
    static const QString P_RADIUS_X;
    static const QString P_RADIUS_Y;
    static const QString P_HEIGHT;
    HemiEllipsoidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ IcosahedronItem : public FormFactorItem
{
public:
    static const QString P_EDGE;
    IcosahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ Prism3Item : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    Prism3Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ Prism6Item : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    Prism6Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ PyramidItem : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    PyramidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ Ripple1BoxItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    Ripple1BoxItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ Ripple1GaussItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    Ripple1GaussItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ Ripple1LorentzItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    Ripple1LorentzItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ Ripple2Item : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_ASYMMETRY;
    Ripple2Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ TetrahedronItem : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    TetrahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ TruncatedCubeItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_REMOVED_LENGTH;
    TruncatedCubeItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ TruncatedSphereItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    static const QString P_REMOVED_TOP;
    TruncatedSphereItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

class BA_CORE_API_ TruncatedSpheroidItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    static const QString P_HFC;
    static const QString P_REMOVED_TOP;
    TruncatedSpheroidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};

#endif // FORMFACTORITEMS_H
