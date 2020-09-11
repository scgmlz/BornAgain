// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIDomainSampleVisitor.h
//! @brief     Defines class GUIDomainSampleVisitor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_GUIDOMAINSAMPLEVISITOR_H
#define BORNAGAIN_GUI_COREGUI_MODELS_GUIDOMAINSAMPLEVISITOR_H

#include "Core/Parametrization/INodeVisitor.h"
#include <QMap>
#include <QString>

class SampleModel;
class MaterialModel;
class SessionItem;
class ExternalProperty;
class Material;
class Simulation;
class MultiLayer;

//! Visits domain sample tree to build GUI presentation.

class BA_CORE_API_ GUIDomainSampleVisitor : public INodeVisitor
{
public:
    GUIDomainSampleVisitor();
    ~GUIDomainSampleVisitor();

    SessionItem* populateSampleModel(SampleModel* sampleModel, MaterialModel* materialModel,
                                     const MultiLayer& sample, const QString& sample_name = "");

    using INodeVisitor::visit;

    void visit(const ParticleLayout*);

    void visit(const Layer*);

    void visit(const MultiLayer*);

    void visit(const Particle*);
    void visit(const ParticleDistribution*);
    void visit(const ParticleCoreShell*);
    void visit(const ParticleComposition*);
    void visit(const MesoCrystal*);
    void visit(const Crystal*);

    void visit(const FormFactorAnisoPyramid*);
    void visit(const FormFactorBarGauss*);
    void visit(const FormFactorBarLorentz*);
    void visit(const FormFactorBox*);
    void visit(const FormFactorCone*);
    void visit(const FormFactorCone6*);
    void visit(const FormFactorCuboctahedron*);
    void visit(const FormFactorCylinder*);
    void visit(const FormFactorDodecahedron*);
    void visit(const FormFactorEllipsoidalCylinder*);
    void visit(const FormFactorFullSphere*);
    void visit(const FormFactorFullSpheroid*);
    void visit(const FormFactorHemiEllipsoid*);
    void visit(const FormFactorIcosahedron*);
    void visit(const FormFactorPrism3*);
    void visit(const FormFactorPrism6*);
    void visit(const FormFactorPyramid*);
    void visit(const FormFactorCosineRippleBox*);
    void visit(const FormFactorCosineRippleGauss*);
    void visit(const FormFactorCosineRippleLorentz*);
    void visit(const FormFactorSawtoothRippleBox*);
    void visit(const FormFactorSawtoothRippleGauss*);
    void visit(const FormFactorSawtoothRippleLorentz*);
    void visit(const FormFactorTetrahedron*);
    void visit(const FormFactorDot*);
    void visit(const FormFactorTruncatedCube*);
    void visit(const FormFactorTruncatedSphere*);
    void visit(const FormFactorTruncatedSpheroid*);

    void visit(const InterferenceFunction1DLattice*);
    void visit(const InterferenceFunction2DLattice*);
    void visit(const InterferenceFunction2DParaCrystal*);
    void visit(const InterferenceFunctionFinite2DLattice*);
    void visit(const InterferenceFunctionHardDisk*);
    void visit(const InterferenceFunctionRadialParaCrystal*);

    void visit(const RotationX*);
    void visit(const RotationY*);
    void visit(const RotationZ*);
    void visit(const RotationEuler*);

private:
    void buildAbundanceInfo(SessionItem* particleItem);
    void buildPositionInfo(SessionItem* particleItem, const IParticle* sample);
    ExternalProperty createMaterialFromDomain(const Material*);
    SessionItem* InsertIParticle(const IParticle* p_particle, QString model_type);

    QMap<int, SessionItem*> m_levelToParentItem;
    QMap<QString, double> m_propertyToValue;
    QMap<QString, bool> m_sample_encountered;
    QMap<SessionItem*, const ISample*> m_itemToSample;
    QString m_topSampleName;

    SampleModel* m_sampleModel;
    MaterialModel* m_materialModel;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_GUIDOMAINSAMPLEVISITOR_H
