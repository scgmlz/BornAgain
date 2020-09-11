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

%import "Wrap/WinDllMacros.h"

%{
#include "BAVersion.h"
#include "Core/Correlations/FTDecay1D.h"
#include "Core/Correlations/FTDecay2D.h"
#include "Core/Correlations/FTDistributions1D.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "Core/Correlations/ILayout.h"
#include "Core/Correlations/IPeakShape.h"
#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Aggregate/InterferenceFunction1DLattice.h"
#include "Core/Aggregate/InterferenceFunction2DLattice.h"
#include "Core/Aggregate/InterferenceFunction2DParaCrystal.h"
#include "Core/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Core/Aggregate/InterferenceFunction3DLattice.h"
#include "Core/Aggregate/InterferenceFunctionFinite2DLattice.h"
#include "Core/Aggregate/InterferenceFunctionFinite3DLattice.h"
#include "Core/Aggregate/InterferenceFunctionHardDisk.h"
#include "Core/Aggregate/InterferenceFunctionNone.h"
#include "Core/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Core/Aggregate/InterferenceFunctionTwin.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Complex.h"
#include "Core/Basics/ICloneable.h"
#include "Core/Basics/ISingleton.h"
#include "Core/Beam/Beam.h"
#include "Core/Beam/FootprintGauss.h"
#include "Core/Beam/FootprintSquare.h"
#include "Core/Binning/Bin.h"
#include "Core/Binning/ConstKBinAxis.h"
#include "Core/Binning/CustomBinAxis.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/VariableBinAxis.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Computation/IBackground.h"
#include "Core/Computation/MultiLayerFuncs.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Detector/DetectorMask.h"
#include "Core/Detector/IDetector2D.h"
#include "Core/Detector/IDetectorResolution.h"
#include "Core/Detector/IResolutionFunction2D.h"
#include "Core/Detector/IsGISAXSDetector.h"
#include "Core/Detector/RectangularDetector.h"
#include "Core/Detector/ResolutionFunction2DGaussian.h"
#include "Core/Detector/ScanResolution.h"
#include "Core/Detector/SphericalDetector.h"
#include "Core/Fitting/FitObjective.h"
#include "Core/Fitting/IObserver.h"
#include "Core/Fitting/IterationInfo.h"
#include "Core/Fitting/PyFittingCallbacks.h"
#include "Core/HardParticle/FormFactorAnisoPyramid.h"
#include "Core/HardParticle/FormFactorBar.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/HardParticle/FormFactorCantellatedCube.h"
#include "Core/HardParticle/FormFactorCone.h"
#include "Core/HardParticle/FormFactorCone6.h"
#include "Core/HardParticle/FormFactorCosineRipple.h"
#include "Core/HardParticle/FormFactorCuboctahedron.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/HardParticle/FormFactorDodecahedron.h"
#include "Core/HardParticle/FormFactorDot.h"
#include "Core/HardParticle/FormFactorEllipsoidalCylinder.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/HardParticle/FormFactorFullSpheroid.h"
#include "Core/HardParticle/FormFactorHemiEllipsoid.h"
#include "Core/HardParticle/FormFactorHollowSphere.h"
#include "Core/HardParticle/FormFactorIcosahedron.h"
#include "Core/HardParticle/FormFactorLongBoxGauss.h"
#include "Core/HardParticle/FormFactorLongBoxLorentz.h"
#include "Core/HardParticle/FormFactorPolyhedron.h"
#include "Core/HardParticle/FormFactorPolyhedron.h"
#include "Core/HardParticle/FormFactorPrism3.h"
#include "Core/HardParticle/FormFactorPrism6.h"
#include "Core/HardParticle/FormFactorPyramid.h"
#include "Core/HardParticle/FormFactorSawtoothRipple.h"
#include "Core/HardParticle/FormFactorTetrahedron.h"
#include "Core/HardParticle/FormFactorTruncatedCube.h"
#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/HardParticle/FormFactorTruncatedSpheroid.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Instrument/ChiSquaredModule.h"
#include "Core/Instrument/IChiSquaredModule.h"
#include "Core/Instrument/Instrument.h"
#include "Core/Instrument/PyArrayImportUtils.h"
#include "Core/Instrument/QSpecScan.h"
#include "Core/Instrument/SimulationResult.h"
#include "Core/Instrument/SpectrumUtils.h"
#include "Core/Instrument/VarianceFunctions.h"
#include "Core/Intensity/Histogram1D.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/Intensity/IHistogram.h"
#include "Core/Intensity/IIntensityFunction.h"
#include "Core/Intensity/IIntensityFunction.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Lattice/ILatticeOrientation.h"
#include "Core/Lattice/ISelectionRule.h"
#include "Core/Lattice/Lattice.h"
#include "Core/Lattice/Lattice2D.h"
#include "Core/Lattice/LatticeUtils.h"
#include "Core/Mask/Ellipse.h"
#include "Core/Mask/IShape2D.h"
#include "Core/Mask/Line.h"
#include "Core/Mask/Polygon.h"
#include "Core/Mask/Rectangle.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/INode.h"
#include "Core/Parametrization/INodeVisitor.h"
#include "Core/Parametrization/IParameterized.h"
#include "Core/Parametrization/ParameterDistribution.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Parametrization/SimulationOptions.h"
#include "Core/Parametrization/ThreadInfo.h"
#include "Core/Basics/Units.h"
#include "Core/Particle/Crystal.h"
#include "Core/Particle/FormFactorCrystal.h"
#include "Core/Particle/FormFactorWeighted.h"
#include "Core/Particle/IAbstractParticle.h"
#include "Core/Particle/IClusteredParticles.h"
#include "Core/Particle/IParticle.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/Particle/SlicedParticle.h"
#include "Core/Scattering/IFormFactorDecorator.h"
#include "Core/Scattering/ISample.h"
#include "Core/Scattering/Rotations.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/Simulation2D.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/SoftParticle/FormFactorGauss.h"
#include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
#include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/Tools/MathFunctions.h"
#include "Core/Vector/BasicVector3D.h"
#include "Core/Vector/Vectors3D.h"
#include "Core/Vector/WavevectorInfo.h"
#include "Fit/Kernel/FitOptions.h"
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

%import(module="libBornAgainFit") "Fit/Tools/AttLimits.h"
%import(module="libBornAgainFit") "Fit/Tools/Attributes.h"
%import(module="libBornAgainFit") "Fit/Tools/RealLimits.h"
%import(module="libBornAgainFit") "Fit/Kernel/Parameters.h"
%import(module="libBornAgainFit") "Fit/Kernel/Parameter.h"

%rename(AxesUnits) AxesUnitsWrap;
%template(swig_dummy_type_axisinfo_vector) std::vector<AxisInfo>;

%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;

%template(vector_IFormFactorPtr_t) std::vector<IFormFactor*>;

%include "Fit/TestEngine/IFactory.h"
%template(SampleBuilderFactoryTemp) IFactory<std::string, IMultiLayerBuilder>;
%template(SimulationFactoryTemp) IFactory<std::string, Simulation>;

%include "Core/Vector/BasicVector3D.h"
%template(kvector_t) BasicVector3D<double>;
%template(vector_kvector_t) std::vector<BasicVector3D<double>>;
%template(cvector_t) BasicVector3D<std::complex<double>>;
%template(vector_cvector_t) std::vector<BasicVector3D<std::complex<double>>>;

%include "Core/Parametrization/IParameter.h" // needed?
%template(IParameterReal) IParameter<double>; // needed to avoid warning 401?

%include "Core/Parametrization/ParameterSample.h"
%template(ParameterSampleVector) std::vector<ParameterSample>;

%include "Core/Intensity/OutputData.h"
%template(IntensityData) OutputData<double>;

%include "Core/Fitting/FitObjective.h"
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<double>>;
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<std::vector<double>>>;

%include "BAVersion.h"

%include "Core/Binning/Bin.h"
%include "Core/Binning/IPixel.h"
%include "Core/Binning/IAxis.h"
%include "Core/Binning/VariableBinAxis.h"

%include "Core/Binning/ConstKBinAxis.h"
%include "Core/Binning/CustomBinAxis.h"
%include "Core/Binning/FixedBinAxis.h"

// need to tell SWIG explicitly to instantiate these templates with given types
%include "Core/Basics/ICloneable.h"
%include "Core/Basics/ISingleton.h"
%include "Core/Basics/Complex.h"
%include "Core/Basics/Units.h"

%include "Core/Vector/Vectors3D.h"
%include "Core/Vector/WavevectorInfo.h"

%include "Core/Tools/MathFunctions.h"

%include "Core/Mask/IShape2D.h"
%include "Core/Mask/Ellipse.h"
%include "Core/Mask/Line.h"
%include "Core/Mask/Polygon.h"
%include "Core/Mask/Rectangle.h"

%include "Core/Parametrization/IParameterized.h"
%include "Core/Parametrization/INode.h"
%include "Core/Parametrization/INodeVisitor.h"
%include "Core/Parametrization/RealParameter.h"

%include "Core/Parametrization/Distributions.h"
%include "Core/Parametrization/Distributions.h"
%include "Core/Parametrization/ParameterDistribution.h"
%include "Core/Parametrization/ParameterPool.h"
%include "Core/Parametrization/RangedDistributions.h"
%include "Core/Parametrization/SimulationOptions.h"
%include "Core/Parametrization/ThreadInfo.h"

%include "Core/Scattering/ISample.h"
%include "Core/Scattering/IFormFactor.h"
%include "Core/Scattering/IFormFactorBorn.h"
%include "Core/Scattering/IFormFactorDecorator.h"

%include "Core/Scattering/Rotations.h"

%include "Fit/Kernel/FitOptions.h"

%include "Core/Fitting/IObserver.h"
%include "Core/Fitting/IterationInfo.h"
%include "Core/Fitting/PyFittingCallbacks.h"

%include "Core/Particle/FormFactorCrystal.h"
%include "Core/Particle/FormFactorWeighted.h"
%include "Core/Particle/IAbstractParticle.h"
%include "Core/Particle/IClusteredParticles.h"
%include "Core/Particle/Crystal.h"
%include "Core/Particle/IParticle.h"
%include "Core/Particle/MesoCrystal.h"
%include "Core/Particle/Particle.h"
%include "Core/Particle/ParticleComposition.h"
%include "Core/Particle/ParticleCoreShell.h"
%include "Core/Particle/ParticleDistribution.h"

%include "Core/Correlations/FTDecay1D.h"
%include "Core/Correlations/FTDecay2D.h"
%include "Core/Correlations/FTDistributions1D.h"
%include "Core/Correlations/FTDistributions2D.h"
%include "Core/Correlations/FTDecay1D.h"
%include "Core/Correlations/FTDecay2D.h"
%include "Core/Correlations/ILayout.h"
%include "Core/Correlations/IPeakShape.h"

%include "Core/Aggregate/IInterferenceFunction.h"
%include "Core/Aggregate/InterferenceFunction1DLattice.h"
%include "Core/Aggregate/InterferenceFunction2DLattice.h"
%include "Core/Aggregate/InterferenceFunction2DParaCrystal.h"
%include "Core/Aggregate/InterferenceFunction2DSuperLattice.h"
%include "Core/Aggregate/InterferenceFunction3DLattice.h"
%include "Core/Aggregate/InterferenceFunctionFinite2DLattice.h"
%include "Core/Aggregate/InterferenceFunctionFinite3DLattice.h"
%include "Core/Aggregate/InterferenceFunctionHardDisk.h"
%include "Core/Aggregate/InterferenceFunctionNone.h"
%include "Core/Aggregate/InterferenceFunctionRadialParaCrystal.h"
%include "Core/Aggregate/InterferenceFunctionTwin.h"
%include "Core/Aggregate/ParticleLayout.h"

%include "Core/Beam/Beam.h"
%include "Core/Beam/IFootprintFactor.h"
%include "Core/Beam/FootprintGauss.h"
%include "Core/Beam/FootprintSquare.h"

%include "Core/Multilayer/IMultiLayerBuilder.h"
%include "Core/Multilayer/Layer.h"
%include "Core/Multilayer/LayerRoughness.h"
%include "Core/Multilayer/MultiLayer.h"

// SWIG workaround for using axes units the same way as they are used in cpp files
%rename(RoughnessModel) RoughnessModelWrap;
%include "Core/Multilayer/RoughnessModels.h"

%include "Core/HardParticle/FormFactorPolyhedron.h"
%include "Core/HardParticle/FormFactorPolyhedron.h"
%include "Core/HardParticle/IProfileRipple.h"

%include "Core/HardParticle/FormFactorAnisoPyramid.h"
%include "Core/HardParticle/FormFactorBox.h"
%include "Core/HardParticle/FormFactorCantellatedCube.h"
%include "Core/HardParticle/FormFactorCone.h"
%include "Core/HardParticle/FormFactorCone6.h"
%include "Core/HardParticle/FormFactorCosineRipple.h"
%include "Core/HardParticle/FormFactorCuboctahedron.h"
%include "Core/HardParticle/FormFactorCylinder.h"
%include "Core/HardParticle/FormFactorDodecahedron.h"
%include "Core/HardParticle/FormFactorDot.h"
%include "Core/HardParticle/FormFactorEllipsoidalCylinder.h"
%include "Core/HardParticle/FormFactorFullSphere.h"
%include "Core/HardParticle/FormFactorFullSpheroid.h"
%include "Core/HardParticle/FormFactorHemiEllipsoid.h"
%include "Core/HardParticle/FormFactorHollowSphere.h"
%include "Core/HardParticle/FormFactorIcosahedron.h"
%include "Core/HardParticle/FormFactorLongBoxGauss.h"
%include "Core/HardParticle/FormFactorLongBoxLorentz.h"
%include "Core/HardParticle/FormFactorPrism3.h"
%include "Core/HardParticle/FormFactorPrism6.h"
%include "Core/HardParticle/FormFactorPyramid.h"
%include "Core/HardParticle/FormFactorSawtoothRipple.h"
%include "Core/HardParticle/FormFactorTetrahedron.h"
%include "Core/HardParticle/FormFactorTruncatedCube.h"
%include "Core/HardParticle/FormFactorTruncatedSphere.h"
%include "Core/HardParticle/FormFactorTruncatedSpheroid.h"

%include "Core/SoftParticle/FormFactorGauss.h"
%include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
%include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"

%include "Core/Simulation/Simulation.h"
%include "Core/Simulation/Simulation2D.h"
%include "Core/Simulation/GISASSimulation.h"
%include "Core/Simulation/DepthProbeSimulation.h"
%include "Core/Simulation/SpecularSimulation.h"
%include "Core/Simulation/OffSpecSimulation.h"

%include "Core/Computation/IBackground.h"
%include "Core/Computation/ConstantBackground.h"
%include "Core/Computation/PoissonNoiseBackground.h"
%include "Core/Computation/MultiLayerFuncs.h"

%include "Core/InputOutput/IntensityDataIOFactory.h"

%include "Core/Detector/IDetector.h"
%include "Core/Detector/IDetector2D.h"
%include "Core/Detector/SphericalDetector.h"
%include "Core/Detector/DetectorMask.h"
%include "Core/Detector/IsGISAXSDetector.h"
%include "Core/Detector/RectangularDetector.h"

%include "Core/Detector/IDetectorResolution.h"
%include "Core/Detector/IResolutionFunction2D.h"
%include "Core/Detector/ResolutionFunction2DGaussian.h"
%include "Core/Detector/ScanResolution.h"

%include "Core/Intensity/IHistogram.h"
%include "Core/Intensity/IIntensityFunction.h"
%include "Core/Intensity/IUnitConverter.h"

%include "Core/Intensity/Histogram1D.h"
%include "Core/Intensity/Histogram2D.h"
%include "Core/Intensity/IntensityDataFunctions.h"

%include "Core/Instrument/IChiSquaredModule.h"
%include "Core/Instrument/ISpecularScan.h"

%include "Core/Instrument/AngularSpecScan.h"
%include "Core/Instrument/ChiSquaredModule.h"
%include "Core/Instrument/Instrument.h"
%include "Core/Instrument/PyArrayImportUtils.h"
%include "Core/Instrument/QSpecScan.h"
%include "Core/Instrument/SimulationResult.h"
%include "Core/Instrument/SpectrumUtils.h"
%include "Core/Instrument/VarianceFunctions.h"

%include "Core/Lattice/ILatticeOrientation.h"
%include "Core/Lattice/ISelectionRule.h"
%include "Core/Lattice/Lattice.h"
%include "Core/Lattice/Lattice2D.h"
%include "Core/Lattice/LatticeUtils.h"

%include "Core/Material/Material.h"
%include "Core/Material/MaterialFactoryFuncs.h"

%include "Core/StandardSamples/SampleBuilderFactory.h"
%include "Core/Simulation/SimulationFactory.h"

%include "extendCore.i"
