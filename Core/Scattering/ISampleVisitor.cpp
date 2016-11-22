// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ISampleVisitor.cpp
//! @brief     Implements class ISampleVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISampleIteratorStrategy.h"
#include "Exceptions.h"
#include "SampleTreeIterator.h"

void VisitSampleTreePreorder(const ISample& sample, ISampleVisitor& visitor)
{
    SampleTreeIterator<SampleIteratorPreorderStrategy> it(&sample);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const ISample *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void VisitSampleTreePostorder(const ISample& sample, ISampleVisitor& visitor)
{
    SampleTreeIterator<SampleIteratorPostorderStrategy> it(&sample);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const ISample *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void ISampleVisitor::visit(const ISample*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const ISample*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ICompositeSample*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const ICompositeSample*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IClusteredParticles*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IClusteredParticles*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const Crystal*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const Crystal*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ILayout*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IDecoration*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleLayout*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const ParticleLayout*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const Layer*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const Layer*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const LayerInterface*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const LayerInterface*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const MultiLayer*)
{
    throw Exceptions::NotImplementedException(
                "ISampleVisitor::visit(const MultiLayer*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IAbstractParticle*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IAbstractParticle*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IParticle*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IParticle*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const Particle*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const Particle*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleDistribution*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const ParticleDistribution*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleComposition*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const ParticleComposition*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const MesoCrystal*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const MesoCrystal*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleCoreShell*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const ParticleCoreShell*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IFormFactor*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IFormFactor*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDWBAPol*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDWBAPol*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorWeighted*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorWeighted*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IFormFactorBorn*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IFormFactorBorn*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorAnisoPyramid*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorAnisoPyramid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorBox*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorBox*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCone*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCone*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCone6*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCone6*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCuboctahedron*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCuboctahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCrystal*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCrystal*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCylinder*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCylinder*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDodecahedron*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDodecahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorEllipsoidalCylinder*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorEllipsoid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorFullSphere*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorFullSphere*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorFullSpheroid*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorFullSpheroid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorGauss*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorGauss*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorHemiEllipsoid*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit const FormFactorHemiEllipsoid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorIcosahedron*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorIcosahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorLongBoxGauss*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorLongBoxGauss*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorLongBoxLorentz*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorLongBoxLorentz*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorLorentz*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorLorentz*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorPrism3*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorPrism3*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorPrism6*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorPrism6*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorPyramid*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorPyramid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorRipple1*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorRipple1*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorRipple2*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorRipple2*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorSphereGaussianRadius*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorSphereGaussianRadius*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorSphereLogNormalRadius*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorSphereLogNormalRadius*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTetrahedron*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTetrahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTrivial*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTrivial*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTruncatedCube*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTruncatedCube*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTruncatedSphere*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTruncatedSphere*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTruncatedSpheroid*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTruncatedSpheroid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IFormFactorDecorator*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IFormFactorDecorator*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDWBA*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDWBA*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorDebyeWaller*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorDebyeWaller*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorFactor*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorFactor*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorMaterial*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorMaterial*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorPositionFactor*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorPositionFactor "
        "*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorRotation*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorRotation "
        "*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IInterferenceFunction*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IInterferenceFunction*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunction1DLattice*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const InterferenceFunction1DLattice*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunctionRadialParaCrystal*)
{
    throw Exceptions::NotImplementedException("ISampleVisitor::visit(const "
                                  "InterferenceFunctionRadialParaCrystal*) -> Error. Not "
                                  "implemented.");
}

void ISampleVisitor::visit(const InterferenceFunction2DLattice*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const InterferenceFunction2DLattice*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunction2DParaCrystal*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const InterferenceFunction2DParaCrystal "
        "*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunctionNone*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const InterferenceFunctionNone*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IRoughness*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IRoughness*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const LayerRoughness*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const LayerRoughness*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IRotation*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const IRotation*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationX*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const RotationX*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationY*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const RotationY*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationZ*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const RotationZ*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationEuler*)
{
    throw Exceptions::NotImplementedException(
        "ISampleVisitor::visit(const RotationEuler*) -> Error. Not implemented.");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool ISampleVisitor::visitEnter(const ICompositeSample*)
{
    m_depth++;
    return false;
}

bool ISampleVisitor::visitLeave(const ICompositeSample*)
{
    m_depth--;
    return false;
}
