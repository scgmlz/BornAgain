// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainCore.i
//! @brief     SWIG interface file for libBornAgainCore
//!
//!            Configuration is done in Core/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainCore"

%feature("autodoc");

/**/
%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_shared_ptr.i"

// TODO CLARIFY WHY THIS IS INCLUDED
%include "../../auto/Wrap/doxygen_core.i"

// include the list of smart pointers (common between Core and Fit)
%include "shared_pointers.i"

%include "warnings.i"
%include "deprecated.i"
%include "ignores.i"
%include "renameCore.i"
%include "directors.i"

%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector<std::vector<double>>;
%template(vector_integer_t) std::vector<int>;
%template(vinteger2d_t) std::vector<std::vector<int>>;
%template(vector_longinteger_t) std::vector<unsigned long int>;
%template(vector_complex_t) std::vector< std::complex<double>>;
%template(vector_string_t) std::vector<std::string>;
%template(map_string_double_t) std::map<std::string, double>;
%template(pair_double_t) std::pair<double, double>;
%template(vector_pair_double_t) std::vector<std::pair<double, double>>;
%nodefaultctor ParameterPool;

#define SWIG_FILE_WITH_INIT

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
%}

%include "numpy.i"
%init %{
    import_array();
%}

#define GCC_DIAG_OFF(x)
#define GCC_DIAG_ON(x)

#ifndef BORNAGAIN_PYTHON
#define BORNAGAIN_PYTHON
#endif

%import "WinDllMacros.h"

%{
#include "AngularSpecScan.h"
#include "BAVersion.h"
#include "BasicVector3D.h"
#include "Beam.h"
#include "Bin.h"
#include "ChiSquaredModule.h"
#include "Complex.h"
#include "ConstantBackground.h"
#include "ConstKBinAxis.h"
#include "Crystal.h"
#include "CustomBinAxis.h"
#include "DepthProbeSimulation.h"
#include "DetectorMask.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "FTDecayFunctions.h"
#include "FTDistributions1D.h"
#include "FTDistributions2D.h"
#include "FitOptions.h"
#include "PyFittingCallbacks.h"
#include "FitObjective.h"
#include "FixedBinAxis.h"
#include "FootprintFactorGaussian.h"
#include "FootprintFactorSquare.h"
#include "FormFactorAnisoPyramid.h"
#include "FormFactorBox.h"
#include "FormFactorCone.h"
#include "FormFactorCone6.h"
#include "FormFactorCrystal.h"
#include "FormFactorCuboctahedron.h"
#include "FormFactorCylinder.h"
#include "FormFactorDebyeBueche.h"
#include "FormFactorDodecahedron.h"
#include "FormFactorDot.h"
#include "FormFactorEllipsoidalCylinder.h"
#include "FormFactorFullSphere.h"
#include "FormFactorFullSpheroid.h"
#include "FormFactorGauss.h"
#include "FormFactorHemiEllipsoid.h"
#include "FormFactorIcosahedron.h"
#include "FormFactorLongBoxGauss.h"
#include "FormFactorLongBoxLorentz.h"
#include "FormFactorLorentz.h"
#include "FormFactorOrnsteinZernike.h"
#include "FormFactorPolyhedron.h"
#include "FormFactorPolyhedron.h"
#include "FormFactorPrism3.h"
#include "FormFactorPrism6.h"
#include "FormFactorPyramid.h"
#include "FormFactorRipple1.h"
#include "FormFactorRipple2.h"
#include "FormFactorSphereGaussianRadius.h"
#include "FormFactorSphereLogNormalRadius.h"
#include "FormFactorSphereUniformRadius.h"
#include "FormFactorTetrahedron.h"
#include "FormFactorTruncatedCube.h"
#include "FormFactorTruncatedSphere.h"
#include "FormFactorTruncatedSpheroid.h"
#include "FormFactorWeighted.h"
#include "GISASSimulation.h"
#include "Histogram1D.h"
#include "Histogram2D.h"
#include "IAbstractParticle.h"
#include "IBackground.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "IDetector2D.h"
#include "IDetectorResolution.h"
#include "IFormFactorDecorator.h"
#include "IHistogram.h"
#include "IIntensityFunction.h"
#include "IInterferenceFunction.h"
#include "ILayout.h"
#include "INamed.h"
#include "INode.h"
#include "IObserver.h"
#include "IParameterized.h"
#include "IParticle.h"
#include "IPeakShape.h"
#include "IResolutionFunction2D.h"
#include "ISample.h"
#include "IMultiLayerBuilder.h"
#include "INodeVisitor.h"
#include "ISelectionRule.h"
#include "IShape2D.h"
#include "ISingleton.h"
#include "Instrument.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "InterferenceFunction1DLattice.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunction2DSuperLattice.h"
#include "InterferenceFunction3DLattice.h"
#include "InterferenceFunctionFinite2DLattice.h"
#include "InterferenceFunctionFinite3DLattice.h"
#include "InterferenceFunctionHardDisk.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunctionTwin.h"
#include "IsGISAXSDetector.h"
#include "ILatticeOrientation.h"
#include "Lattice.h"
#include "LatticeUtils.h"
#include "Lattice1DParameters.h"
#include "Lattice2D.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "Line.h"
#include "MaterialFactoryFuncs.h"
#include "MathFunctions.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "MultiLayerFuncs.h"
#include "OffSpecSimulation.h"
#include "OutputData.h"
#include "ParameterDistribution.h"
#include "ParameterPool.h"
#include "ParameterSample.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "PoissonNoiseBackground.h"
#include "Polygon.h"
#include "PyArrayImportUtils.h"
#include "QSpecScan.h"
#include "RangedDistributions.h"
#include "RealParameter.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "ResolutionFunction2DGaussian.h"
#include "Ripples.h"
#include "Rotations.h"
#include "SampleBuilderFactory.h"
#include "ScanResolution.h"
#include "Simulation.h"
#include "Simulation2D.h"
#include "SimulationFactory.h"
#include "SimulationOptions.h"
#include "SimulationResult.h"
#include "SlicedParticle.h"
#include "SpecularSimulation.h"
#include "SphericalDetector.h"
#include "ThreadInfo.h"
#include "Units.h"
#include "VariableBinAxis.h"
#include "Vectors3D.h"
#include "WavevectorInfo.h"
#include "IChiSquaredModule.h"
#include "IIntensityFunction.h"
#include "IIntensityNormalizer.h"
#include "VarianceFunctions.h"
#include "IterationInfo.h"
#include "SpectrumUtils.h"
%}

// ownership

%newobject ScanResolution::scanRelativeResolution;
%newobject ScanResolution::scanAbsoluteResolution;

%newobject SimulationResult::histogram2d(AxesUnits units_type = AxesUnits::DEFAULT) const;

%newobject IntensityDataIOFactory::readOutputData(const std::string& file_name);
%newobject IntensityDataIOFactory::readIntensityData(const std::string& file_name);

%newobject DetectorMask::createHistogram() const;

%newobject PyArrayImport::importArrayToOutputData;
%newobject IHistogram::createFrom(const std::string& filename);
%newobject IHistogram::createFrom(const std::vector<std::vector<double>>& data);

%newobject InterferenceFunction2DLattice::createSquare(double lattice_length, double xi);
%newobject InterferenceFunction2DLattice::createHexagonal(double lattice_length, double xi);
%newobject InterferenceFunction2DParaCrystal::createSquare(
        double lattice_length, double damping_length, double domain_size_1, double domain_size_2);
%newobject InterferenceFunction2DParaCrystal::createHexagonal(
        double lattice_length, double damping_length, double domain_size_1, double domain_size_2);
%newobject InterferenceFunction2DSuperLattice::createSquare(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunction2DSuperLattice::createHexagonal(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunctionFinite2DLattice::createSquare(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunctionFinite2DLattice::createHexagonal(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);

// The following goes verbatim from libBornAgainCore.i to libBornAgainCore_wrap.cxx.
// Note that the order matters, as base classes must be included before derived classes.

%import(module="libBornAgainFit") "AttLimits.h"
%import(module="libBornAgainFit") "Attributes.h"
%import(module="libBornAgainFit") "RealLimits.h"
%import(module="libBornAgainFit") "Parameters.h"
%import(module="libBornAgainFit") "Parameter.h"

%include "BAVersion.h"
%include "BasicVector3D.h"
%include "ICloneable.h"
%include "INamed.h"
%include "IParameterized.h"
%include "INode.h"

// need to tell SWIG explicitly to instantiate these templates with given types
%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;
%template(swig_dummy_type_axisinfo_vector) std::vector<AxisInfo>;

// SWIG does not automatically instantiate templates, so we declare these by hand
%template(kvector_t) BasicVector3D<double>;
%template(vector_kvector_t) std::vector<BasicVector3D<double>>;
%template(cvector_t) BasicVector3D<std::complex<double>>;
%template(vector_cvector_t) std::vector<BasicVector3D<std::complex<double>>>;

// SWIG workaround for using axes units the same way as they are used in cpp files
%rename(AxesUnits) AxesUnitsWrap;
%rename(RoughnessModel) RoughnessModelWrap;

%include "Complex.h"
%include "Units.h"
%include "Vectors3D.h"
%include "WavevectorInfo.h"

%include "Beam.h"
%include "Bin.h"

%include "IAxis.h"
%include "VariableBinAxis.h"
%include "ConstKBinAxis.h"
%include "CustomBinAxis.h"

%include "IShape2D.h"
%include "ISample.h"
%include "IChiSquaredModule.h"
%include "IObserver.h"
%include "IIntensityFunction.h"
%include "IIntensityNormalizer.h"
%include "VarianceFunctions.h"
%include "ChiSquaredModule.h"
%include "FitOptions.h"
%include "PyFittingCallbacks.h"

%include "FitObjective.h"
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<double>>;
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<std::vector<double>>>;

%include "MathFunctions.h"
%include "IFactory.h"
%include "IMultiLayerBuilder.h"
%include "INodeVisitor.h"
%include "IClusteredParticles.h"
%include "Crystal.h"
%include "Distributions.h"
%include "DetectorMask.h"
%include "Ellipse.h"
%include "FTDecayFunctions.h"
%include "FTDistributions1D.h"
%include "FTDistributions2D.h"
%include "FixedBinAxis.h"
%include "IFormFactor.h"
%template(vector_IFormFactorPtr_t) std::vector<IFormFactor*>;
%include "IFormFactorBorn.h"
%include "IFormFactorDecorator.h"
%include "FormFactorPolyhedron.h"
%include "ProfileRipple1.h"
%include "Ripples.h"

%include "FormFactorAnisoPyramid.h"
%include "FormFactorBox.h"
%include "FormFactorCone.h"
%include "FormFactorCone6.h"
%include "FormFactorCrystal.h"
%include "FormFactorCuboctahedron.h"
%include "FormFactorCylinder.h"
%include "FormFactorDebyeBueche.h"
%include "FormFactorDodecahedron.h"
%include "FormFactorDot.h"
%include "FormFactorEllipsoidalCylinder.h"
%include "FormFactorFullSphere.h"
%include "FormFactorFullSpheroid.h"
%include "FormFactorGauss.h"
%include "FormFactorHemiEllipsoid.h"
%include "FormFactorIcosahedron.h"
%include "FormFactorLongBoxGauss.h"
%include "FormFactorLongBoxLorentz.h"
%include "FormFactorRipple1.h"
%include "FormFactorLorentz.h"
%include "FormFactorOrnsteinZernike.h"
%include "FormFactorPolyhedron.h"
%include "FormFactorPrism3.h"
%include "FormFactorPrism6.h"
%include "FormFactorPyramid.h"
%include "FormFactorRipple2.h"
%include "FormFactorSphereGaussianRadius.h"
%include "FormFactorSphereLogNormalRadius.h"
%include "FormFactorSphereUniformRadius.h"
%include "FormFactorTetrahedron.h"
%include "FormFactorTruncatedCube.h"
%include "FormFactorTruncatedSphere.h"
%include "FormFactorTruncatedSpheroid.h"
%include "FormFactorWeighted.h"

%include "IFootprintFactor.h"
%include "FootprintFactorGaussian.h"
%include "FootprintFactorSquare.h"

%include "Simulation.h"
%include "Simulation2D.h"
%include "SimulationOptions.h"
%include "GISASSimulation.h"
%include "IHistogram.h"
%include "Histogram1D.h"
%include "Histogram2D.h"
%include "SimulationResult.h"
%include "IBackground.h"
%include "ConstantBackground.h"
%include "IDetector.h"
%include "IDetector2D.h"
%include "IDetectorResolution.h"
%include "Distributions.h"
%include "FTDecayFunctions.h"
%include "IInterferenceFunction.h"
%include "ILayout.h"
%include "IAbstractParticle.h"
%include "IParameter.h" // needed?
%template(IParameterReal) IParameter<double>; // needed to avoid warning 401?
%include "IParticle.h"
%include "IPeakShape.h"
%include "IResolutionFunction2D.h"
%include "Rotations.h"
%include "ISelectionRule.h"
%include "ISingleton.h"
%include "Instrument.h"
%include "IntensityDataFunctions.h"
%include "IntensityDataIOFactory.h"
%include "InterferenceFunction1DLattice.h"
%include "InterferenceFunction2DLattice.h"
%include "InterferenceFunction2DParaCrystal.h"
%include "InterferenceFunction2DSuperLattice.h"
%include "InterferenceFunction3DLattice.h"
%include "InterferenceFunctionFinite2DLattice.h"
%include "InterferenceFunctionFinite3DLattice.h"
%include "InterferenceFunctionHardDisk.h"
%include "InterferenceFunctionNone.h"
%include "InterferenceFunctionRadialParaCrystal.h"
%include "InterferenceFunctionTwin.h"
%include "IPixel.h"
%include "SphericalDetector.h"
%include "IsGISAXSDetector.h"
%include "ILatticeOrientation.h"
%include "Lattice.h"
%include "LatticeUtils.h"
%include "Lattice1DParameters.h"
%include "Lattice2D.h"
%include "Layer.h"
%include "LayerRoughness.h"
%include "Line.h"
%include "Material.h"
%include "MaterialFactoryFuncs.h"
%include "MesoCrystal.h"
%include "MultiLayer.h"
%include "MultiLayerFuncs.h"
%include "OffSpecSimulation.h"
%include "IIntensityFunction.h"
%include "OutputData.h"
%template(IntensityData) OutputData<double>;
%include "ParameterDistribution.h"
%include "ParameterPool.h"
%include "ParameterSample.h"
%template(ParameterSampleVector) std::vector<ParameterSample>;
%include "Particle.h"
%include "ParticleComposition.h"
%include "ParticleCoreShell.h"
%include "ParticleDistribution.h"
%include "ParticleLayout.h"
%include "PyArrayImportUtils.h"
%include "PoissonNoiseBackground.h"
%include "Polygon.h"
%include "RangedDistributions.h"
%include "RealParameter.h"
%include "Rectangle.h"
%include "RectangularDetector.h"
%include "ResolutionFunction2DGaussian.h"
%include "Rotations.h"
%include "RoughnessModels.h"
%include "ISelectionRule.h"
%include "DepthProbeSimulation.h"
%include "SpecularSimulation.h"
%include "ThreadInfo.h"
%template(SampleBuilderFactoryTemp) IFactory<std::string, IMultiLayerBuilder>;
%include "SampleBuilderFactory.h"
%template(SimulationFactoryTemp) IFactory<std::string, Simulation>;
%include "SimulationFactory.h"
%include "IUnitConverter.h"
%include "IterationInfo.h"
%include "SpectrumUtils.h"

%include "ScanResolution.h"

%include "ISpecularScan.h"
%include "AngularSpecScan.h"
%include "QSpecScan.h"

%include "extendCore.i"
