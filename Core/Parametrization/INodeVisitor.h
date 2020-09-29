// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INodeVisitor.h
//! @brief     Defines interface class INodeVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_INODEVISITOR_H
#define BORNAGAIN_CORE_PARAMETRIZATION_INODEVISITOR_H

class BasicLattice;
class Beam;
class ConstantBackground;
class ConvolutionDetectorResolution;
class Crystal;
class DistributionCosine;
class DistributionGate;
class DistributionGaussian;
class DistributionLogNormal;
class DistributionLorentz;
class DistributionTrapezoid;
class FootprintGauss;
class FootprintSquare;
class FormFactorAnisoPyramid;
class FormFactorBarGauss;
class FormFactorBarLorentz;
class FormFactorBox;
class FormFactorCantellatedCube;
class FormFactorCone;
class FormFactorCone6;
class FormFactorCoreShell;
class FormFactorCrystal;
class FormFactorCuboctahedron;
class FormFactorCylinder;
class FormFactorDWBA;
class FormFactorDWBAPol;
class FormFactorDecoratorMaterial;
class FormFactorDecoratorPositionFactor;
class FormFactorDecoratorRotation;
class FormFactorDodecahedron;
class FormFactorDot;
class FormFactorEllipsoidalCylinder;
class FormFactorFullSphere;
class FormFactorFullSpheroid;
class FormFactorGaussSphere;
class FormFactorHollowSphere;
class FormFactorHemiEllipsoid;
class FormFactorIcosahedron;
class FormFactorLongBoxGauss;
class FormFactorLongBoxLorentz;
class FormFactorPrism3;
class FormFactorPrism6;
class FormFactorPyramid;
class FormFactorCosineRippleBox;
class FormFactorCosineRippleGauss;
class FormFactorCosineRippleLorentz;
class FormFactorSawtoothRippleBox;
class FormFactorSawtoothRippleGauss;
class FormFactorSawtoothRippleLorentz;
class FormFactorSphereGaussianRadius;
class FormFactorSphereLogNormalRadius;
class FormFactorTetrahedron;
class FormFactorTruncatedCube;
class FormFactorTruncatedSphere;
class FormFactorTruncatedSpheroid;
class FormFactorWeighted;
class FTDecayFunction1DCauchy;
class FTDecayFunction1DGauss;
class FTDecayFunction1DTriangle;
class FTDecayFunction1DVoigt;
class FTDecayFunction2DCauchy;
class FTDecayFunction2DGauss;
class FTDecayFunction2DVoigt;
class FTDistribution1DCauchy;
class FTDistribution1DCosine;
class FTDistribution1DGate;
class FTDistribution1DGauss;
class FTDistribution1DTriangle;
class FTDistribution1DVoigt;
class FTDistribution2DCauchy;
class FTDistribution2DCone;
class FTDistribution2DGate;
class FTDistribution2DGauss;
class FTDistribution2DVoigt;
class GISASSimulation;
class HexagonalLattice;
class IAbstractParticle;
class IClusteredParticles;
class IdentityRotation;
class IFormFactor;
class IFormFactorBorn;
class IFormFactorDecorator;
class IInterferenceFunction;
class ILayout;
class INode;
class Instrument;
class InterferenceFunction1DLattice;
class InterferenceFunction2DLattice;
class InterferenceFunction2DParaCrystal;
class InterferenceFunction2DSuperLattice;
class InterferenceFunction3DLattice;
class InterferenceFunctionFinite2DLattice;
class InterferenceFunctionFinite3DLattice;
class InterferenceFunctionHardDisk;
class InterferenceFunctionRadialParaCrystal;
class InterferenceFunctionTwin;
class InterferenceFunctionNone;
class IParticle;
class IPeakShape;
class IRotation;
class ISample;
class IsGISAXSDetector;
class Layer;
class LayerInterface;
class LayerRoughness;
class MesoCrystal;
class MultiLayer;
class OffSpecSimulation;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;
class ParticleLayout;
class PoissonNoiseBackground;
class RectangularDetector;
class ResolutionFunction2DGaussian;
class RotationEuler;
class RotationX;
class RotationY;
class RotationZ;
class SpecularDetector1D;
class SpecularSimulation;
class SphericalDetector;
class SquareLattice;

//! Visitor interface to visit ISample objects.
//! @ingroup samples_internal

//! From visitor pattern to achieve double dispatch.

class INodeVisitor
{
public:
    INodeVisitor() : m_depth(0) {}
    virtual ~INodeVisitor() {}

    virtual void visit(const BasicLattice*) {}
    virtual void visit(const Beam*) {}
    virtual void visit(const ConstantBackground*) {}
    virtual void visit(const ConvolutionDetectorResolution*) {}
    virtual void visit(const Crystal*) {}
    virtual void visit(const DistributionCosine*) {}
    virtual void visit(const DistributionGate*) {}
    virtual void visit(const DistributionGaussian*) {}
    virtual void visit(const DistributionLogNormal*) {}
    virtual void visit(const DistributionLorentz*) {}
    virtual void visit(const DistributionTrapezoid*) {}
    virtual void visit(const FootprintGauss*) {}
    virtual void visit(const FootprintSquare*) {}
    virtual void visit(const FormFactorAnisoPyramid*) {}
    virtual void visit(const FormFactorBarGauss*) {}
    virtual void visit(const FormFactorBarLorentz*) {}
    virtual void visit(const FormFactorBox*) {}
    virtual void visit(const FormFactorCantellatedCube*) {}
    virtual void visit(const FormFactorCone*) {}
    virtual void visit(const FormFactorCone6*) {}
    virtual void visit(const FormFactorCoreShell*) {}
    virtual void visit(const FormFactorCrystal*) {}
    virtual void visit(const FormFactorCuboctahedron*) {}
    virtual void visit(const FormFactorCylinder*) {}
    virtual void visit(const FormFactorDWBA*) {}
    virtual void visit(const FormFactorDWBAPol*) {}
    virtual void visit(const FormFactorDecoratorMaterial*) {}
    virtual void visit(const FormFactorDecoratorPositionFactor*) {}
    virtual void visit(const FormFactorDecoratorRotation*) {}
    virtual void visit(const FormFactorDodecahedron*) {}
    virtual void visit(const FormFactorDot*) {}
    virtual void visit(const FormFactorEllipsoidalCylinder*) {}
    virtual void visit(const FormFactorFullSphere*) {}
    virtual void visit(const FormFactorFullSpheroid*) {}
    virtual void visit(const FormFactorGaussSphere*) {}
    virtual void visit(const FormFactorHemiEllipsoid*) {}
    virtual void visit(const FormFactorHollowSphere*) {}
    virtual void visit(const FormFactorIcosahedron*) {}
    virtual void visit(const FormFactorLongBoxGauss*) {}
    virtual void visit(const FormFactorLongBoxLorentz*) {}
    virtual void visit(const FormFactorPrism3*) {}
    virtual void visit(const FormFactorPrism6*) {}
    virtual void visit(const FormFactorPyramid*) {}
    virtual void visit(const FormFactorCosineRippleBox*) {}
    virtual void visit(const FormFactorCosineRippleGauss*) {}
    virtual void visit(const FormFactorCosineRippleLorentz*) {}
    virtual void visit(const FormFactorSawtoothRippleBox*) {}
    virtual void visit(const FormFactorSawtoothRippleGauss*) {}
    virtual void visit(const FormFactorSawtoothRippleLorentz*) {}
    virtual void visit(const FormFactorSphereGaussianRadius*) {}
    virtual void visit(const FormFactorSphereLogNormalRadius*) {}
    virtual void visit(const FormFactorTetrahedron*) {}
    virtual void visit(const FormFactorTruncatedCube*) {}
    virtual void visit(const FormFactorTruncatedSphere*) {}
    virtual void visit(const FormFactorTruncatedSpheroid*) {}
    virtual void visit(const FormFactorWeighted*) {}
    virtual void visit(const FTDecayFunction1DCauchy*) {}
    virtual void visit(const FTDecayFunction1DGauss*) {}
    virtual void visit(const FTDecayFunction1DTriangle*) {}
    virtual void visit(const FTDecayFunction1DVoigt*) {}
    virtual void visit(const FTDecayFunction2DCauchy*) {}
    virtual void visit(const FTDecayFunction2DGauss*) {}
    virtual void visit(const FTDecayFunction2DVoigt*) {}
    virtual void visit(const FTDistribution1DCauchy*) {}
    virtual void visit(const FTDistribution1DCosine*) {}
    virtual void visit(const FTDistribution1DGate*) {}
    virtual void visit(const FTDistribution1DGauss*) {}
    virtual void visit(const FTDistribution1DTriangle*) {}
    virtual void visit(const FTDistribution1DVoigt*) {}
    virtual void visit(const FTDistribution2DCauchy*) {}
    virtual void visit(const FTDistribution2DCone*) {}
    virtual void visit(const FTDistribution2DGate*) {}
    virtual void visit(const FTDistribution2DGauss*) {}
    virtual void visit(const FTDistribution2DVoigt*) {}
    virtual void visit(const GISASSimulation*) {}
    virtual void visit(const HexagonalLattice*) {}
    virtual void visit(const IAbstractParticle*) {}
    virtual void visit(const IClusteredParticles*) {}
    virtual void visit(const IdentityRotation*) {}
    virtual void visit(const IFormFactor*) {}
    virtual void visit(const IFormFactorBorn*) {}
    virtual void visit(const IFormFactorDecorator*) {}
    virtual void visit(const IInterferenceFunction*) {}
    virtual void visit(const ILayout*) {}
    virtual void visit(const INode*) {}
    virtual void visit(const Instrument*) {}
    virtual void visit(const InterferenceFunction1DLattice*) {}
    virtual void visit(const InterferenceFunction2DLattice*) {}
    virtual void visit(const InterferenceFunction2DParaCrystal*) {}
    virtual void visit(const InterferenceFunction2DSuperLattice*) {}
    virtual void visit(const InterferenceFunction3DLattice*) {}
    virtual void visit(const InterferenceFunctionFinite2DLattice*) {}
    virtual void visit(const InterferenceFunctionFinite3DLattice*) {}
    virtual void visit(const InterferenceFunctionHardDisk*) {}
    virtual void visit(const InterferenceFunctionRadialParaCrystal*) {}
    virtual void visit(const InterferenceFunctionTwin*) {}
    virtual void visit(const InterferenceFunctionNone*) {}
    virtual void visit(const IParticle*) {}
    virtual void visit(const IPeakShape*) {}
    virtual void visit(const IRotation*) {}
    virtual void visit(const ISample*) {}
    virtual void visit(const IsGISAXSDetector*) {}
    virtual void visit(const Layer*) {}
    virtual void visit(const LayerInterface*) {}
    virtual void visit(const LayerRoughness*) {}
    virtual void visit(const MesoCrystal*) {}
    virtual void visit(const MultiLayer*) {}
    virtual void visit(const OffSpecSimulation*) {}
    virtual void visit(const Particle*) {}
    virtual void visit(const ParticleComposition*) {}
    virtual void visit(const ParticleCoreShell*) {}
    virtual void visit(const ParticleDistribution*) {}
    virtual void visit(const ParticleLayout*) {}
    virtual void visit(const PoissonNoiseBackground*) {}
    virtual void visit(const RectangularDetector*) {}
    virtual void visit(const ResolutionFunction2DGaussian*) {}
    virtual void visit(const RotationEuler*) {}
    virtual void visit(const RotationX*) {}
    virtual void visit(const RotationY*) {}
    virtual void visit(const RotationZ*) {}
    virtual void visit(const SpecularDetector1D*) {}
    virtual void visit(const SpecularSimulation*) {}
    virtual void visit(const SphericalDetector*) {}
    virtual void visit(const SquareLattice*) {}

    //! Returns depth of the visitor in the composite hierarchy
    int depth() const { return m_depth; }

    //! Sets depth  of the visitor in the composite hierarchy
    void setDepth(int depth) { m_depth = depth; }

private:
    int m_depth;
};

void VisitNodesPreorder(const INode& node, INodeVisitor& visitor);
void VisitNodesPostorder(const INode& node, INodeVisitor& visitor);

#endif // BORNAGAIN_CORE_PARAMETRIZATION_INODEVISITOR_H
