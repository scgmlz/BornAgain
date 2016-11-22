
// File: index.xml

// File: classAdjustMinimizerStrategy.xml
%feature("docstring") AdjustMinimizerStrategy "

Strategy modifies mimimizer settings before running minimization round.

C++ includes: AdjustMinimizerStrategy.h
";

%feature("docstring")  AdjustMinimizerStrategy::AdjustMinimizerStrategy "AdjustMinimizerStrategy::AdjustMinimizerStrategy()
";

%feature("docstring")  AdjustMinimizerStrategy::AdjustMinimizerStrategy "AdjustMinimizerStrategy::AdjustMinimizerStrategy(const std::string &minimizerName, const std::string &algorithmName=std::string(), const std::string &optionString=std::string())
";

%feature("docstring")  AdjustMinimizerStrategy::clone "AdjustMinimizerStrategy * AdjustMinimizerStrategy::clone() const
";

%feature("docstring")  AdjustMinimizerStrategy::setMinimizer "void AdjustMinimizerStrategy::setMinimizer(const std::string &minimizerName, const std::string &algorithmName=std::string(), const std::string &optionString=std::string())
";

%feature("docstring")  AdjustMinimizerStrategy::execute "void AdjustMinimizerStrategy::execute()
";


// File: classAngularPixelMap.xml
%feature("docstring") AngularPixelMap "";

%feature("docstring")  AngularPixelMap::AngularPixelMap "AngularPixelMap::AngularPixelMap(Bin1D alpha_bin, Bin1D phi_bin)
";

%feature("docstring")  AngularPixelMap::~AngularPixelMap "virtual AngularPixelMap::~AngularPixelMap()
";

%feature("docstring")  AngularPixelMap::clone "AngularPixelMap * AngularPixelMap::clone() const override
";

%feature("docstring")  AngularPixelMap::createZeroSizeMap "AngularPixelMap * AngularPixelMap::createZeroSizeMap(double x, double y) const override
";

%feature("docstring")  AngularPixelMap::getK "kvector_t AngularPixelMap::getK(double x, double y, double wavelength) const override
";

%feature("docstring")  AngularPixelMap::getIntegrationFactor "double AngularPixelMap::getIntegrationFactor(double x, double y) const override
";

%feature("docstring")  AngularPixelMap::getSolidAngle "double AngularPixelMap::getSolidAngle() const override
";


// File: classBasic2DLatticeBuilder.xml
%feature("docstring") Basic2DLatticeBuilder "

Builds sample: 2D lattice with arbitrary angle and different lattice length_1 and length_2.

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  Basic2DLatticeBuilder::Basic2DLatticeBuilder "Basic2DLatticeBuilder::Basic2DLatticeBuilder()
";

%feature("docstring")  Basic2DLatticeBuilder::buildSample "MultiLayer * Basic2DLatticeBuilder::buildSample() const
";


// File: classBasic2DParaCrystalBuilder.xml
%feature("docstring") Basic2DParaCrystalBuilder "

Builds sample: basic two dimensional paracrystal with various probability distribution functions (PDF's). They are initialized via component service.

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder "Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder()
";

%feature("docstring")  Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder "Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder()
";

%feature("docstring")  Basic2DParaCrystalBuilder::buildSample "MultiLayer * Basic2DParaCrystalBuilder::buildSample() const
";


// File: classBasicVector3D.xml
%feature("docstring") BasicVector3D "

Three-dimensional vector template, for use with integer, double, or complex components.

C++ includes: BasicVector3D.h
";

%feature("docstring")  BasicVector3D::BasicVector3D "BasicVector3D< T >::BasicVector3D()

Default constructor. 
";

%feature("docstring")  BasicVector3D::BasicVector3D "BasicVector3D< T >::BasicVector3D(const T x1, const T y1, const T z1)

Constructor from cartesian components. 
";

%feature("docstring")  BasicVector3D::x "T BasicVector3D< T >::x() const

Returns x-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::y "T BasicVector3D< T >::y() const

Returns y-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::z "T BasicVector3D< T >::z() const

Returns z-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::setX "void BasicVector3D< T >::setX(const T &a)

Sets x-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::setY "void BasicVector3D< T >::setY(const T &a)

Sets y-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::setZ "void BasicVector3D< T >::setZ(const T &a)

Sets z-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::conj "BasicVector3D<T> BasicVector3D< T >::conj() const

Returns complex conjugate vector. 
";

%feature("docstring")  BasicVector3D::mag2 "double BasicVector3D< T >::mag2() const

Returns squared magnitude squared of the vector. 
";

%feature("docstring")  BasicVector3D::mag "double BasicVector3D< T >::mag() const

Returns magnitude of the vector. 
";

%feature("docstring")  BasicVector3D::magxy2 "double BasicVector3D< T >::magxy2() const

Returns squared distance from z axis. 
";

%feature("docstring")  BasicVector3D::magxy "double BasicVector3D< T >::magxy() const

Returns distance from z axis. 
";

%feature("docstring")  BasicVector3D::phi "double BasicVector3D< T >::phi() const

Returns azimuth angle. 
";

%feature("docstring")  BasicVector3D::theta "double BasicVector3D< T >::theta() const

Returns polar angle. 
";

%feature("docstring")  BasicVector3D::cosTheta "double BasicVector3D< T >::cosTheta() const

Returns cosine of polar angle. 
";

%feature("docstring")  BasicVector3D::sin2Theta "double BasicVector3D< T >::sin2Theta() const

Returns squared sine of polar angle. 
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D<T> BasicVector3D< T >::unit() const

Returns unit vector in direction of this. Throws for null vector. 
";

%feature("docstring")  BasicVector3D::complex "BasicVector3D<std::complex<double> > BasicVector3D< T >::complex() const

Returns this, trivially converted to complex type. 
";

%feature("docstring")  BasicVector3D::real "BasicVector3D<double> BasicVector3D< T >::real() const

Returns real parts. 
";

%feature("docstring")  BasicVector3D::dot "auto BasicVector3D< T >::dot(const BasicVector3D< U > &v) const -> decltype(this->x() *v.x())

Returns dot product of vectors (antilinear in the first [=self] argument).

Returns dot product of (complex) vectors (antilinear in the first [=self] argument). 
";

%feature("docstring")  BasicVector3D::cross "auto BasicVector3D< T >::cross(const BasicVector3D< U > &v) const -> BasicVector3D< decltype(this->x() *v.x())>

Returns cross product of vectors (linear in both arguments).

Returns cross product of (complex) vectors. 
";

%feature("docstring")  BasicVector3D::angle "double BasicVector3D< T >::angle(const BasicVector3D< T > &v) const

Returns angle with respect to another vector. 
";

%feature("docstring")  BasicVector3D::project "BasicVector3D<T> BasicVector3D< T >::project(const BasicVector3D< T > &v) const

Returns projection of this onto other vector: (this*v)*v/|v|^2. 
";

%feature("docstring")  BasicVector3D::rotatedX "BasicVector3D<T> BasicVector3D< T >::rotatedX(double a) const

Returns result of rotation around x-axis. 
";

%feature("docstring")  BasicVector3D::rotatedY "BasicVector3D<T> BasicVector3D< T >::rotatedY(double a) const

Returns result of rotation around y-axis. 
";

%feature("docstring")  BasicVector3D::rotatedZ "BasicVector3D<T> BasicVector3D< T >::rotatedZ(double a) const

Returns result of rotation around z-axis. 
";

%feature("docstring")  BasicVector3D::rotated "BasicVector3D<T> BasicVector3D< T >::rotated(double a, const BasicVector3D< T > &v) const

Returns result of rotation around the axis specified by another vector. 
";

%feature("docstring")  BasicVector3D::conj "BasicVector3D< complex_t > BasicVector3D< complex_t >::conj() const

Returns complex conjugate vector. 
";

%feature("docstring")  BasicVector3D::real "BasicVector3D< double > BasicVector3D< complex_t >::real() const

Returns real parts. 
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D< complex_t > BasicVector3D< complex_t >::unit() const
";


// File: classBeam.xml
%feature("docstring") Beam "

Ideal collimated beam defined by wavelength, direction and intensity.

C++ includes: Beam.h
";

%feature("docstring")  Beam::Beam "Beam::Beam()
";

%feature("docstring")  Beam::Beam "Beam::Beam(const Beam &other)
";

%feature("docstring")  Beam::~Beam "virtual Beam::~Beam()
";

%feature("docstring")  Beam::getCentralK "kvector_t Beam::getCentralK() const

Returns the wavevector. 
";

%feature("docstring")  Beam::setCentralK "void Beam::setCentralK(double wavelength, double alpha_i, double phi_i)

Sets the wavevector in terms of wavelength and incoming angles. 
";

%feature("docstring")  Beam::getIntensity "double Beam::getIntensity() const

Returns the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::setIntensity "void Beam::setIntensity(double intensity)

Sets the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::setPolarization "void Beam::setPolarization(const kvector_t bloch_vector)

Sets the polarization density matrix according to the given Bloch vector. 
";

%feature("docstring")  Beam::getPolarization "Eigen::Matrix2cd Beam::getPolarization() const

Returns the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  Beam::getWavelength "double Beam::getWavelength() const
";

%feature("docstring")  Beam::getAlpha "double Beam::getAlpha() const
";

%feature("docstring")  Beam::getPhi "double Beam::getPhi() const
";


// File: structBin1D.xml
%feature("docstring") Bin1D "";

%feature("docstring")  Bin1D::Bin1D "Bin1D::Bin1D()
";

%feature("docstring")  Bin1D::Bin1D "Bin1D::Bin1D(double lower, double upper)
";

%feature("docstring")  Bin1D::getMidPoint "double Bin1D::getMidPoint() const
";

%feature("docstring")  Bin1D::getBinSize "double Bin1D::getBinSize() const
";


// File: classBin1DCVector.xml
%feature("docstring") Bin1DCVector "

An one-dimensional range of cvector_t's.

C++ includes: Bin.h
";

%feature("docstring")  Bin1DCVector::Bin1DCVector "Bin1DCVector::Bin1DCVector()
";

%feature("docstring")  Bin1DCVector::Bin1DCVector "Bin1DCVector::Bin1DCVector(const cvector_t lower, const cvector_t upper)
";

%feature("docstring")  Bin1DCVector::Bin1DCVector "Bin1DCVector::Bin1DCVector(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin)

creation on  Bin1DCVector from alpha and phi bins 
";

%feature("docstring")  Bin1DCVector::getMidPoint "cvector_t Bin1DCVector::getMidPoint() const
";

%feature("docstring")  Bin1DCVector::getDelta "cvector_t Bin1DCVector::getDelta() const
";


// File: structBin1DKVector.xml
%feature("docstring") Bin1DKVector "

An one-dimensional range of kvector_t's.

C++ includes: Bin.h
";

%feature("docstring")  Bin1DKVector::Bin1DKVector "Bin1DKVector::Bin1DKVector()
";

%feature("docstring")  Bin1DKVector::Bin1DKVector "Bin1DKVector::Bin1DKVector(const kvector_t lower, const kvector_t upper)
";

%feature("docstring")  Bin1DKVector::Bin1DKVector "Bin1DKVector::Bin1DKVector(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin)

creation on  Bin1DKVector from alpha and phi bins 
";

%feature("docstring")  Bin1DKVector::getMidPoint "kvector_t Bin1DKVector::getMidPoint() const
";

%feature("docstring")  Bin1DKVector::getDelta "kvector_t Bin1DKVector::getDelta() const
";


// File: classBoxCompositionBuilder.xml
%feature("docstring") BoxCompositionBuilder "

Parent class to test all kind of compositions made out of boxes. Reproduces Python functional test transform_BoxComposition.py.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionBuilder::BoxCompositionBuilder "BoxCompositionBuilder::BoxCompositionBuilder()
";

%feature("docstring")  BoxCompositionBuilder::~BoxCompositionBuilder "BoxCompositionBuilder::~BoxCompositionBuilder()
";


// File: classBoxCompositionRotateXBuilder.xml
%feature("docstring") BoxCompositionRotateXBuilder "

Two boxes in particle composition rotated in X by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateXBuilder::BoxCompositionRotateXBuilder "BoxCompositionRotateXBuilder::BoxCompositionRotateXBuilder()
";

%feature("docstring")  BoxCompositionRotateXBuilder::buildSample "MultiLayer * BoxCompositionRotateXBuilder::buildSample() const
";


// File: classBoxCompositionRotateYBuilder.xml
%feature("docstring") BoxCompositionRotateYBuilder "

Two boxes in particle composition rotated in Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateYBuilder::BoxCompositionRotateYBuilder "BoxCompositionRotateYBuilder::BoxCompositionRotateYBuilder()
";

%feature("docstring")  BoxCompositionRotateYBuilder::buildSample "MultiLayer * BoxCompositionRotateYBuilder::buildSample() const
";


// File: classBoxCompositionRotateZandYBuilder.xml
%feature("docstring") BoxCompositionRotateZandYBuilder "

Two boxes in particle composition rotated in Z and Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZandYBuilder::BoxCompositionRotateZandYBuilder "BoxCompositionRotateZandYBuilder::BoxCompositionRotateZandYBuilder()
";

%feature("docstring")  BoxCompositionRotateZandYBuilder::buildSample "MultiLayer * BoxCompositionRotateZandYBuilder::buildSample() const
";


// File: classBoxCompositionRotateZBuilder.xml
%feature("docstring") BoxCompositionRotateZBuilder "

Two boxes in particle composition rotated in Z by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZBuilder::BoxCompositionRotateZBuilder "BoxCompositionRotateZBuilder::BoxCompositionRotateZBuilder()
";

%feature("docstring")  BoxCompositionRotateZBuilder::buildSample "MultiLayer * BoxCompositionRotateZBuilder::buildSample() const
";


// File: classBoxStackCompositionBuilder.xml
%feature("docstring") BoxStackCompositionBuilder "

Two different boxes are first rotated and then composed, composition is then rotated.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxStackCompositionBuilder::BoxStackCompositionBuilder "BoxStackCompositionBuilder::BoxStackCompositionBuilder()
";

%feature("docstring")  BoxStackCompositionBuilder::buildSample "MultiLayer * BoxStackCompositionBuilder::buildSample() const
";


// File: structIntegratorMCMiser_1_1CallBackHolder.xml
%feature("docstring") IntegratorMCMiser::CallBackHolder "

structure holding the object and possible extra parameters

C++ includes: IntegratorMCMiser.h
";


// File: structIntegratorReal_1_1CallBackHolder.xml
%feature("docstring") IntegratorReal::CallBackHolder "

structure holding the object and possible extra parameters

C++ includes: IntegratorReal.h
";


// File: classCenteredSquareLatticeBuilder.xml
%feature("docstring") CenteredSquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  CenteredSquareLatticeBuilder::CenteredSquareLatticeBuilder "CenteredSquareLatticeBuilder::CenteredSquareLatticeBuilder()
";

%feature("docstring")  CenteredSquareLatticeBuilder::buildSample "MultiLayer * CenteredSquareLatticeBuilder::buildSample() const
";


// File: classChiSquaredModule.xml
%feature("docstring") ChiSquaredModule "

Calculation of chi2 between two data sets.

C++ includes: ChiSquaredModule.h
";

%feature("docstring")  ChiSquaredModule::ChiSquaredModule "ChiSquaredModule::ChiSquaredModule()
";

%feature("docstring")  ChiSquaredModule::ChiSquaredModule "ChiSquaredModule::ChiSquaredModule(const ChiSquaredModule &other)
";

%feature("docstring")  ChiSquaredModule::~ChiSquaredModule "virtual ChiSquaredModule::~ChiSquaredModule()
";

%feature("docstring")  ChiSquaredModule::clone "virtual ChiSquaredModule* ChiSquaredModule::clone() const

clone method 
";

%feature("docstring")  ChiSquaredModule::processFitElements "void ChiSquaredModule::processFitElements(std::vector< FitElement >::iterator first, std::vector< FitElement >::iterator last)
";


// File: classException_1_1ClassInitializationException.xml
%feature("docstring") Exception::ClassInitializationException "";

%feature("docstring")  Exception::ClassInitializationException::ClassInitializationException "Exception::ClassInitializationException::ClassInitializationException(const std::string &message)
";


// File: classComputationOutcome.xml
%feature("docstring") ComputationOutcome "

Completion status (flag and text) of a numeric computation. Pure virtual base class for our model evaluation routines. Currently, the only child is Computations, which is the base for some more classes.

C++ includes: ComputationOutcome.h
";

%feature("docstring")  ComputationOutcome::ComputationOutcome "ComputationOutcome::ComputationOutcome()
";

%feature("docstring")  ComputationOutcome::isCompleted "bool ComputationOutcome::isCompleted() const
";

%feature("docstring")  ComputationOutcome::getRunMessage "std::string ComputationOutcome::getRunMessage() const
";

%feature("docstring")  ComputationOutcome::setRunning "void ComputationOutcome::setRunning()
";

%feature("docstring")  ComputationOutcome::setCompleted "void ComputationOutcome::setCompleted()
";

%feature("docstring")  ComputationOutcome::setFailed "void ComputationOutcome::setFailed()
";

%feature("docstring")  ComputationOutcome::setRunMessage "void ComputationOutcome::setRunMessage(const std::string &message)
";


// File: classConstKBinAxis.xml
%feature("docstring") ConstKBinAxis "

Axis with fixed bin size in sin(angle) space.

C++ includes: ConstKBinAxis.h
";

%feature("docstring")  ConstKBinAxis::ConstKBinAxis "ConstKBinAxis::ConstKBinAxis(const std::string &name, size_t nbins, double start, double end)

ConstKBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

start: 
low edge of first bin

end: 
upper edge of last bin 
";

%feature("docstring")  ConstKBinAxis::~ConstKBinAxis "virtual ConstKBinAxis::~ConstKBinAxis()
";

%feature("docstring")  ConstKBinAxis::clone "ConstKBinAxis * ConstKBinAxis::clone() const

clone function 
";

%feature("docstring")  ConstKBinAxis::createClippedAxis "ConstKBinAxis * ConstKBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classConvolutionDetectorResolution.xml
%feature("docstring") ConvolutionDetectorResolution "

Limitation: this class assumes that the data points are evenly distributed on each axis.

Convolutes the intensity in 1 or 2 dimensions with a resolution function.

C++ includes: ConvolutionDetectorResolution.h
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(cumulative_DF_1d res_function_1d)

Constructor taking a 1 dimensional resolution function as argument. 
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(IResolutionFunction2D *p_res_function_2d)

Constructor taking a 2 dimensional resolution function as argument. 
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(const IResolutionFunction2D &p_res_function_2d)
";

%feature("docstring")  ConvolutionDetectorResolution::~ConvolutionDetectorResolution "ConvolutionDetectorResolution::~ConvolutionDetectorResolution()
";

%feature("docstring")  ConvolutionDetectorResolution::applyDetectorResolution "void ConvolutionDetectorResolution::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Convolve given intensities with the encapsulated resolution. 
";

%feature("docstring")  ConvolutionDetectorResolution::addParametersToExternalPool "std::string ConvolutionDetectorResolution::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively call children. 
";

%feature("docstring")  ConvolutionDetectorResolution::clone "ConvolutionDetectorResolution * ConvolutionDetectorResolution::clone() const

clone object 
";

%feature("docstring")  ConvolutionDetectorResolution::getResolutionFunction2D "const IResolutionFunction2D * ConvolutionDetectorResolution::getResolutionFunction2D() const
";


// File: classMathFunctions_1_1Convolve.xml
%feature("docstring") MathFunctions::Convolve "

Convolution of two real vectors (in 1D or 2D) using Fast Fourier Transform.

Usage: std::vector<double> signal, kernel, result;  Convolve cv; cv.fftconvolve(signal, kernel, result)

Given code rely on code from Jeremy Fix page http://jeremy.fix.free.fr/spip.php?article15 see also \"Efficient convolution using the Fast Fourier Transform, Application in C++\" by Jeremy Fix, May 30, 2011

C++ includes: Convolve.h
";

%feature("docstring")  MathFunctions::Convolve::Convolve "MathFunctions::Convolve::Convolve()
";

%feature("docstring")  MathFunctions::Convolve::fftconvolve "void MathFunctions::Convolve::fftconvolve(const double1d_t &source, const double1d_t &kernel, double1d_t &result)

convolution in 1D 
";

%feature("docstring")  MathFunctions::Convolve::fftconvolve "void MathFunctions::Convolve::fftconvolve(const double2d_t &source, const double2d_t &kernel, double2d_t &result)

convolution in 2D 
";

%feature("docstring")  MathFunctions::Convolve::init "void MathFunctions::Convolve::init(int h_src, int w_src, int h_kernel, int w_kernel)

prepare arrays for 2D convolution of given vectors 
";

%feature("docstring")  MathFunctions::Convolve::setMode "void MathFunctions::Convolve::setMode(EConvolutionMode mode)

Sets convolution mode. 
";


// File: classCoreShellBoxRotateZandYBuilder.xml
%feature("docstring") CoreShellBoxRotateZandYBuilder "

Rotation and translation of core shell box particle in 3 layers system.

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellBoxRotateZandYBuilder::CoreShellBoxRotateZandYBuilder "CoreShellBoxRotateZandYBuilder::CoreShellBoxRotateZandYBuilder()
";

%feature("docstring")  CoreShellBoxRotateZandYBuilder::buildSample "MultiLayer * CoreShellBoxRotateZandYBuilder::buildSample() const
";


// File: classCoreShellParticleBuilder.xml
%feature("docstring") CoreShellParticleBuilder "

Builds sample: Core Shell Nanoparticles (IsGISAXS example #11).

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellParticleBuilder::CoreShellParticleBuilder "CoreShellParticleBuilder::CoreShellParticleBuilder()
";

%feature("docstring")  CoreShellParticleBuilder::buildSample "MultiLayer * CoreShellParticleBuilder::buildSample() const
";


// File: classCosineRippleBuilder.xml
%feature("docstring") CosineRippleBuilder "

Builds sample: cosine ripple within the 1D-paracrystal model.

C++ includes: RipplesBuilder.h
";

%feature("docstring")  CosineRippleBuilder::CosineRippleBuilder "CosineRippleBuilder::CosineRippleBuilder()
";

%feature("docstring")  CosineRippleBuilder::buildSample "MultiLayer * CosineRippleBuilder::buildSample() const
";


// File: classCrystal.xml
%feature("docstring") Crystal "

A crystal structure with a  ParticleComposition as a basis. Used in  MesoCrystal, where it is given an outer shape.

C++ includes: Crystal.h
";

%feature("docstring")  Crystal::Crystal "Crystal::Crystal(const ParticleComposition &lattice_basis, const Lattice &lattice)
";

%feature("docstring")  Crystal::~Crystal "Crystal::~Crystal()
";

%feature("docstring")  Crystal::clone "Crystal * Crystal::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  Crystal::cloneInvertB "Crystal * Crystal::cloneInvertB() const final

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  Crystal::accept "void Crystal::accept(ISampleVisitor *visitor) const final

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  Crystal::setAmbientMaterial "void Crystal::setAmbientMaterial(const IMaterial &material) final
";

%feature("docstring")  Crystal::getAmbientMaterial "const IMaterial * Crystal::getAmbientMaterial() const final

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Crystal::createTotalFormFactor "IFormFactor * Crystal::createTotalFormFactor(const IFormFactor &meso_crystal_form_factor, const IRotation *p_rotation, const kvector_t &translation) const

Creates a total form factor for the mesocrystal with a specific shape and content The bulk content of the mesocrystal is encapsulated by the  IClusteredParticles object itself 
";

%feature("docstring")  Crystal::getTransformedLattice "Lattice Crystal::getTransformedLattice(const IRotation *p_rotation) const
";

%feature("docstring")  Crystal::getLatticeBasis "const ParticleComposition* Crystal::getLatticeBasis() const
";

%feature("docstring")  Crystal::setDWFactor "void Crystal::setDWFactor(double dw_factor)
";


// File: classCumulativeValue.xml
%feature("docstring") CumulativeValue "

The cumulative value with average and rms on-the-flight calculations.

C++ includes: CumulativeValue.h
";

%feature("docstring")  CumulativeValue::CumulativeValue "CumulativeValue::CumulativeValue()
";

%feature("docstring")  CumulativeValue::clear "void CumulativeValue::clear()
";

%feature("docstring")  CumulativeValue::setContent "void CumulativeValue::setContent(double value)
";

%feature("docstring")  CumulativeValue::add "void CumulativeValue::add(double value, double weight=1.0)
";

%feature("docstring")  CumulativeValue::getNumberOfEntries "int CumulativeValue::getNumberOfEntries() const
";

%feature("docstring")  CumulativeValue::getContent "double CumulativeValue::getContent() const
";

%feature("docstring")  CumulativeValue::getAverage "double CumulativeValue::getAverage() const
";

%feature("docstring")  CumulativeValue::getRMS "double CumulativeValue::getRMS() const
";


// File: classCustomBinAxis.xml
%feature("docstring") CustomBinAxis "

Axis with fixed bin size in sin(angle) space used for numerical comparison with IsGisaxs. The main feature of the axis is that it produces zero bin sizes.

C++ includes: CustomBinAxis.h
";

%feature("docstring")  CustomBinAxis::CustomBinAxis "CustomBinAxis::CustomBinAxis(const std::string &name, size_t nbins, double start, double end)

CustomBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

start: 
center of first bin (IsGisaxs convention)

end: 
center of last bin (IsGisaxs convention) 
";

%feature("docstring")  CustomBinAxis::~CustomBinAxis "virtual CustomBinAxis::~CustomBinAxis()
";

%feature("docstring")  CustomBinAxis::clone "CustomBinAxis * CustomBinAxis::clone() const

clone function 
";

%feature("docstring")  CustomBinAxis::getBin "Bin1D CustomBinAxis::getBin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  CustomBinAxis::getBinCenters "std::vector< double > CustomBinAxis::getBinCenters() const
";

%feature("docstring")  CustomBinAxis::createClippedAxis "CustomBinAxis * CustomBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classCustomMorphologyBuilder.xml
%feature("docstring") CustomMorphologyBuilder "

Builds sample: mixture of different particles (IsGISAXS example #7)

C++ includes: CustomMorphologyBuilder.h
";

%feature("docstring")  CustomMorphologyBuilder::CustomMorphologyBuilder "CustomMorphologyBuilder::CustomMorphologyBuilder()
";

%feature("docstring")  CustomMorphologyBuilder::buildSample "MultiLayer * CustomMorphologyBuilder::buildSample() const
";


// File: classCylindersAndPrismsBuilder.xml
%feature("docstring") CylindersAndPrismsBuilder "

Builds sample: mixture of cylinders and prisms without interference (IsGISAXS example #1)

C++ includes: CylindersAndPrismsBuilder.h
";

%feature("docstring")  CylindersAndPrismsBuilder::CylindersAndPrismsBuilder "CylindersAndPrismsBuilder::CylindersAndPrismsBuilder()
";

%feature("docstring")  CylindersAndPrismsBuilder::buildSample "MultiLayer * CylindersAndPrismsBuilder::buildSample() const
";


// File: classCylindersInBABuilder.xml
%feature("docstring") CylindersInBABuilder "

Builds sample: cylinder formfactor in BA (IsGISAXS example #3, part II)

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInBABuilder::CylindersInBABuilder "CylindersInBABuilder::CylindersInBABuilder()
";

%feature("docstring")  CylindersInBABuilder::buildSample "MultiLayer * CylindersInBABuilder::buildSample() const
";


// File: classCylindersInDWBABuilder.xml
%feature("docstring") CylindersInDWBABuilder "

Builds sample: cylinder formfactor in DWBA (IsGISAXS example #3, part I)

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInDWBABuilder::CylindersInDWBABuilder "CylindersInDWBABuilder::CylindersInDWBABuilder()
";

%feature("docstring")  CylindersInDWBABuilder::buildSample "MultiLayer * CylindersInDWBABuilder::buildSample() const
";


// File: classCylindersInSSCABuilder.xml
%feature("docstring") CylindersInSSCABuilder "

Builds sample: size spacing correlation approximation (IsGISAXS example #15).

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  CylindersInSSCABuilder::CylindersInSSCABuilder "CylindersInSSCABuilder::CylindersInSSCABuilder()
";

%feature("docstring")  CylindersInSSCABuilder::buildSample "MultiLayer * CylindersInSSCABuilder::buildSample() const
";


// File: classCylindersWithSizeDistributionBuilder.xml
%feature("docstring") CylindersWithSizeDistributionBuilder "

Cylinders in BA with size distributions (IsGISAXS example #3, part II).

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  CylindersWithSizeDistributionBuilder::CylindersWithSizeDistributionBuilder "CylindersWithSizeDistributionBuilder::CylindersWithSizeDistributionBuilder()
";

%feature("docstring")  CylindersWithSizeDistributionBuilder::buildSample "MultiLayer * CylindersWithSizeDistributionBuilder::buildSample() const
";


// File: classException_1_1DeadReferenceException.xml
%feature("docstring") Exception::DeadReferenceException "";

%feature("docstring")  Exception::DeadReferenceException::DeadReferenceException "Exception::DeadReferenceException::DeadReferenceException(const std::string &message)
";


// File: classDecoratedLayerComputation.xml
%feature("docstring") DecoratedLayerComputation "

Computes the scattering contribution from one layer with particles in/on it. Controlled by  MainComputation.

C++ includes: DecoratedLayerComputation.h
";

%feature("docstring")  DecoratedLayerComputation::DecoratedLayerComputation "DecoratedLayerComputation::DecoratedLayerComputation(const Layer *p_layer, size_t layout_index=0)
";

%feature("docstring")  DecoratedLayerComputation::setSpecularInfo "void DecoratedLayerComputation::setSpecularInfo(const LayerSpecularInfo &specular_info)
";

%feature("docstring")  DecoratedLayerComputation::eval "void DecoratedLayerComputation::eval(const SimulationOptions &options, ProgressHandler *progress, bool polarized, const std::vector< SimulationElement >::iterator &begin_it, const std::vector< SimulationElement >::iterator &end_it) const

Computes scattering intensity for given range of simulation elements. 
";


// File: classDecouplingApproximationStrategy1.xml
%feature("docstring") DecouplingApproximationStrategy1 "

Strategy class to compute the total scalar scattering from a decorated layer in decoupling approximation.

C++ includes: DecouplingApproximationStrategy.h
";

%feature("docstring")  DecouplingApproximationStrategy1::DecouplingApproximationStrategy1 "DecouplingApproximationStrategy1::DecouplingApproximationStrategy1(SimulationOptions sim_params)
";


// File: classDecouplingApproximationStrategy2.xml
%feature("docstring") DecouplingApproximationStrategy2 "

Strategy class to compute the total polarized scattering from a decorated layer in decoupling approximation.

C++ includes: DecouplingApproximationStrategy.h
";

%feature("docstring")  DecouplingApproximationStrategy2::DecouplingApproximationStrategy2 "DecouplingApproximationStrategy2::DecouplingApproximationStrategy2(SimulationOptions sim_params)
";


// File: classDetectionProperties.xml
%feature("docstring") DetectionProperties "

Detector properties (efficiency, transmission).

C++ includes: DetectionProperties.h
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties()
";

%feature("docstring")  DetectionProperties::setAnalyzerProperties "void DetectionProperties::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  DetectionProperties::analyzerOperator "Eigen::Matrix2cd DetectionProperties::analyzerOperator() const

Gets the polarization density matrix (in spin basis along z-axis) 
";


// File: classDetectorMask.xml
%feature("docstring") DetectorMask "

Collection of detector masks.

C++ includes: DetectorMask.h
";

%feature("docstring")  DetectorMask::DetectorMask "DetectorMask::DetectorMask()
";

%feature("docstring")  DetectorMask::DetectorMask "DetectorMask::DetectorMask(const DetectorMask &other)
";

%feature("docstring")  DetectorMask::addMask "void DetectorMask::addMask(const Geometry::IShape2D &shape, bool mask_value)

Add mask to the stack of detector masks. The value \"true\" means that the area will be excluded from the analysis.

Parameters:
-----------

shape: 
The shape of mask.

mask_value: 
The value of mask 
";

%feature("docstring")  DetectorMask::initMaskData "void DetectorMask::initMaskData(const IDetector2D &detector)

Init the map of masks for the given detector plane. 
";

%feature("docstring")  DetectorMask::initMaskData "void DetectorMask::initMaskData(const OutputData< double > &data)
";

%feature("docstring")  DetectorMask::isMasked "bool DetectorMask::isMasked(size_t index) const
";

%feature("docstring")  DetectorMask::getMaskData "const OutputData<bool>* DetectorMask::getMaskData() const
";

%feature("docstring")  DetectorMask::createHistogram "Histogram2D * DetectorMask::createHistogram() const
";

%feature("docstring")  DetectorMask::removeMasks "void DetectorMask::removeMasks()

remove all masks and return object to initial state 
";

%feature("docstring")  DetectorMask::hasMasks "bool DetectorMask::hasMasks() const

returns true if has masks 
";

%feature("docstring")  DetectorMask::numberOfMaskedChannels "int DetectorMask::numberOfMaskedChannels() const
";

%feature("docstring")  DetectorMask::numberOfMasks "size_t DetectorMask::numberOfMasks() const
";

%feature("docstring")  DetectorMask::getMaskShape "const Geometry::IShape2D * DetectorMask::getMaskShape(size_t mask_index, bool &mask_value) const
";


// File: classDistributionCosine.xml
%feature("docstring") DistributionCosine "

Cosine distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionCosine::DistributionCosine "DistributionCosine::DistributionCosine()
";

%feature("docstring")  DistributionCosine::DistributionCosine "DistributionCosine::DistributionCosine(double mean, double sigma)
";

%feature("docstring")  DistributionCosine::~DistributionCosine "virtual DistributionCosine::~DistributionCosine()
";

%feature("docstring")  DistributionCosine::clone "virtual DistributionCosine* DistributionCosine::clone() const

clone method 
";

%feature("docstring")  DistributionCosine::probabilityDensity "double DistributionCosine::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionCosine::getMean "virtual double DistributionCosine::getMean() const

Returns the mean of the distribution. 
";

%feature("docstring")  DistributionCosine::getSigma "double DistributionCosine::getSigma() const

Returns the sigma parameter of the distribution. 
";

%feature("docstring")  DistributionCosine::generateValueList "std::vector< double > DistributionCosine::generateValueList(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionCosine::isDelta "bool DistributionCosine::isDelta() const

signals that the distribution is in the limit case of a delta distribution 
";


// File: classDistributionGate.xml
%feature("docstring") DistributionGate "

Uniform distribution function with half width hwhm.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionGate::DistributionGate "DistributionGate::DistributionGate()
";

%feature("docstring")  DistributionGate::DistributionGate "DistributionGate::DistributionGate(double min, double max)
";

%feature("docstring")  DistributionGate::~DistributionGate "virtual DistributionGate::~DistributionGate()
";

%feature("docstring")  DistributionGate::clone "virtual DistributionGate* DistributionGate::clone() const

clone method 
";

%feature("docstring")  DistributionGate::probabilityDensity "double DistributionGate::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionGate::getMean "virtual double DistributionGate::getMean() const

get the mean of the distribution 
";

%feature("docstring")  DistributionGate::getMin "double DistributionGate::getMin() const

Returns the minimum value of the distribution. 
";

%feature("docstring")  DistributionGate::getMax "double DistributionGate::getMax() const

Returns the maximum value of the distribution. 
";

%feature("docstring")  DistributionGate::generateValueList "std::vector< double > DistributionGate::generateValueList(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

Returns list of sample values. 
";

%feature("docstring")  DistributionGate::isDelta "bool DistributionGate::isDelta() const

signals that the distribution is in the limit case of a delta distribution 
";


// File: classDistributionGaussian.xml
%feature("docstring") DistributionGaussian "

Gaussian distribution with standard deviation std_dev.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionGaussian::DistributionGaussian "DistributionGaussian::DistributionGaussian()
";

%feature("docstring")  DistributionGaussian::DistributionGaussian "DistributionGaussian::DistributionGaussian(double mean, double std_dev)
";

%feature("docstring")  DistributionGaussian::~DistributionGaussian "virtual DistributionGaussian::~DistributionGaussian()
";

%feature("docstring")  DistributionGaussian::clone "virtual DistributionGaussian* DistributionGaussian::clone() const

clone method 
";

%feature("docstring")  DistributionGaussian::probabilityDensity "double DistributionGaussian::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionGaussian::getMean "virtual double DistributionGaussian::getMean() const

Returns the mean of the distribution. 
";

%feature("docstring")  DistributionGaussian::getStdDev "double DistributionGaussian::getStdDev() const

Returns the standard deviation. 
";

%feature("docstring")  DistributionGaussian::generateValueList "std::vector< double > DistributionGaussian::generateValueList(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionGaussian::isDelta "bool DistributionGaussian::isDelta() const

signals that the distribution is in the limit case of a delta distribution 
";


// File: classDistributionHandler.xml
%feature("docstring") DistributionHandler "

Provides the functionality to average over parameter distributions with weights.

C++ includes: DistributionHandler.h
";

%feature("docstring")  DistributionHandler::DistributionHandler "DistributionHandler::DistributionHandler()
";

%feature("docstring")  DistributionHandler::~DistributionHandler "DistributionHandler::~DistributionHandler()
";

%feature("docstring")  DistributionHandler::addParameterDistribution "void DistributionHandler::addParameterDistribution(const std::string &param_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits())

add a sampled parameter distribution 
";

%feature("docstring")  DistributionHandler::addParameterDistribution "void DistributionHandler::addParameterDistribution(const ParameterDistribution &par_distr)
";

%feature("docstring")  DistributionHandler::getTotalNumberOfSamples "size_t DistributionHandler::getTotalNumberOfSamples() const

get the total number of parameter value combinations (product of the individual sizes of each parameter distribution 
";

%feature("docstring")  DistributionHandler::setParameterValues "double DistributionHandler::setParameterValues(ParameterPool *p_parameter_pool, size_t index)

set the parameter values of the simulation object to a specific combination of values, determined by the index (which must be smaller than the total number of combinations) and returns the weight associated with this combination of parameter values 
";

%feature("docstring")  DistributionHandler::getDistributions "const DistributionHandler::Distributions_t & DistributionHandler::getDistributions() const
";


// File: classDistributionLogNormal.xml
%feature("docstring") DistributionLogNormal "

Log-normal distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionLogNormal::DistributionLogNormal "DistributionLogNormal::DistributionLogNormal(double scale_param)
";

%feature("docstring")  DistributionLogNormal::DistributionLogNormal "DistributionLogNormal::DistributionLogNormal(double median, double scale_param)
";

%feature("docstring")  DistributionLogNormal::~DistributionLogNormal "virtual DistributionLogNormal::~DistributionLogNormal()
";

%feature("docstring")  DistributionLogNormal::clone "virtual DistributionLogNormal* DistributionLogNormal::clone() const

clone method 
";

%feature("docstring")  DistributionLogNormal::probabilityDensity "double DistributionLogNormal::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionLogNormal::getMean "double DistributionLogNormal::getMean() const

get the mean of the distribution 
";

%feature("docstring")  DistributionLogNormal::getMedian "double DistributionLogNormal::getMedian() const

Returns the median of the distribution. 
";

%feature("docstring")  DistributionLogNormal::getScalePar "double DistributionLogNormal::getScalePar() const

Returns the scale parameter of the distribution. 
";

%feature("docstring")  DistributionLogNormal::generateValueList "std::vector< double > DistributionLogNormal::generateValueList(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionLogNormal::isDelta "bool DistributionLogNormal::isDelta() const

signals that the distribution is in the limit case of a delta distribution 
";


// File: classDistributionLorentz.xml
%feature("docstring") DistributionLorentz "

Lorentz distribution with half width hwhm.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionLorentz::DistributionLorentz "DistributionLorentz::DistributionLorentz()
";

%feature("docstring")  DistributionLorentz::DistributionLorentz "DistributionLorentz::DistributionLorentz(double mean, double hwhm)
";

%feature("docstring")  DistributionLorentz::~DistributionLorentz "virtual DistributionLorentz::~DistributionLorentz()
";

%feature("docstring")  DistributionLorentz::clone "virtual DistributionLorentz* DistributionLorentz::clone() const
";

%feature("docstring")  DistributionLorentz::probabilityDensity "double DistributionLorentz::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionLorentz::getMean "virtual double DistributionLorentz::getMean() const

Returns the mean of the distribution. 
";

%feature("docstring")  DistributionLorentz::getHWHM "double DistributionLorentz::getHWHM() const

Returns the half width at half maximum. 
";

%feature("docstring")  DistributionLorentz::generateValueList "std::vector< double > DistributionLorentz::generateValueList(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionLorentz::isDelta "bool DistributionLorentz::isDelta() const

signals that the distribution is in the limit case of a delta distribution 
";


// File: classException_1_1DivisionByZeroException.xml
%feature("docstring") Exception::DivisionByZeroException "";

%feature("docstring")  Exception::DivisionByZeroException::DivisionByZeroException "Exception::DivisionByZeroException::DivisionByZeroException(const std::string &message)
";


// File: classException_1_1DomainErrorException.xml
%feature("docstring") Exception::DomainErrorException "";

%feature("docstring")  Exception::DomainErrorException::DomainErrorException "Exception::DomainErrorException::DomainErrorException(const std::string &message)
";


// File: classDWBADiffuseReflection.xml
%feature("docstring") DWBADiffuseReflection "

Calculation of diffuse (aka off-specular) reflection from multilayers.

C++ includes: DWBADiffuseReflection.h
";

%feature("docstring")  DWBADiffuseReflection::DWBADiffuseReflection "DWBADiffuseReflection::DWBADiffuseReflection()
";

%feature("docstring")  DWBADiffuseReflection::execute "void DWBADiffuseReflection::execute(const MultiLayer &sample, const kvector_t ki, const kvector_t kf)
";

%feature("docstring")  DWBADiffuseReflection::setSample "void DWBADiffuseReflection::setSample(const MultiLayer &sample)
";

%feature("docstring")  DWBADiffuseReflection::getDiffuseAutocorr "double DWBADiffuseReflection::getDiffuseAutocorr() const
";

%feature("docstring")  DWBADiffuseReflection::getDiffuseCrosscorr "double DWBADiffuseReflection::getDiffuseCrosscorr() const
";

%feature("docstring")  DWBADiffuseReflection::setKvectors "void DWBADiffuseReflection::setKvectors(const kvector_t ki, const kvector_t kf)
";


// File: classGeometry_1_1Ellipse.xml
%feature("docstring") Geometry::Ellipse "

Ellipse shape.

C++ includes: Ellipse.h
";

%feature("docstring")  Geometry::Ellipse::Ellipse "Geometry::Ellipse::Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta=0.0)

Parameters:
-----------

xcenter: 
x-coordinate of  Ellipse's center

ycenter: 
y-coordinate of  Ellipse's center

xradius: 
Radius along x-axis

yradius: 
Radius along y-axis

theta: 
Angle of  Ellipse rotation in radians 
";

%feature("docstring")  Geometry::Ellipse::clone "Ellipse* Geometry::Ellipse::clone() const
";

%feature("docstring")  Geometry::Ellipse::contains "bool Geometry::Ellipse::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::Ellipse::contains "bool Geometry::Ellipse::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of ellipse; more precisely, if mid point of two bins satisfy this condition. 
";

%feature("docstring")  Geometry::Ellipse::getCenterX "double Geometry::Ellipse::getCenterX() const
";

%feature("docstring")  Geometry::Ellipse::getCenterY "double Geometry::Ellipse::getCenterY() const
";

%feature("docstring")  Geometry::Ellipse::getRadiusX "double Geometry::Ellipse::getRadiusX() const
";

%feature("docstring")  Geometry::Ellipse::getRadiusY "double Geometry::Ellipse::getRadiusY() const
";

%feature("docstring")  Geometry::Ellipse::getTheta "double Geometry::Ellipse::getTheta() const
";


// File: classException_1_1ExistingClassRegistrationException.xml
%feature("docstring") Exception::ExistingClassRegistrationException "";

%feature("docstring")  Exception::ExistingClassRegistrationException::ExistingClassRegistrationException "Exception::ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string &message)
";


// File: classExportToPython.xml
%feature("docstring") ExportToPython "

Write a Python script that allows to run the current simulation.

C++ includes: ExportToPython.h
";

%feature("docstring")  ExportToPython::ExportToPython "ExportToPython::ExportToPython(const MultiLayer &multilayer)
";

%feature("docstring")  ExportToPython::~ExportToPython "ExportToPython::~ExportToPython()
";

%feature("docstring")  ExportToPython::simulationToPythonLowlevel "std::string ExportToPython::simulationToPythonLowlevel(const GISASSimulation *simulation)

Returns a Python script that sets up a simulation and runs it if invoked as main program. 
";

%feature("docstring")  ExportToPython::defineGetSample "std::string ExportToPython::defineGetSample() const
";


// File: classException_1_1FileIsBadException.xml
%feature("docstring") Exception::FileIsBadException "";

%feature("docstring")  Exception::FileIsBadException::FileIsBadException "Exception::FileIsBadException::FileIsBadException(const std::string &message)
";


// File: classException_1_1FileNotIsOpenException.xml
%feature("docstring") Exception::FileNotIsOpenException "";

%feature("docstring")  Exception::FileNotIsOpenException::FileNotIsOpenException "Exception::FileNotIsOpenException::FileNotIsOpenException(const std::string &message)
";


// File: classFitElement.xml
%feature("docstring") FitElement "

Measured (\"real\") and simulated scattering intensity value for one detector cell. Used for chi2/residual calculations.

C++ includes: FitElement.h
";

%feature("docstring")  FitElement::FitElement "FitElement::FitElement()
";

%feature("docstring")  FitElement::FitElement "FitElement::FitElement(size_t index, double simul_value, double real_value, double weight=1.0)
";

%feature("docstring")  FitElement::FitElement "FitElement::FitElement(const FitElement &other)
";

%feature("docstring")  FitElement::getIndex "size_t FitElement::getIndex() const
";

%feature("docstring")  FitElement::getSimulValue "double FitElement::getSimulValue() const
";

%feature("docstring")  FitElement::getRealValue "double FitElement::getRealValue() const
";

%feature("docstring")  FitElement::getWeight "double FitElement::getWeight() const
";

%feature("docstring")  FitElement::getSquaredDifference "double FitElement::getSquaredDifference() const
";

%feature("docstring")  FitElement::setSquaredDifference "void FitElement::setSquaredDifference(double value)
";

%feature("docstring")  FitElement::getResidual "double FitElement::getResidual() const
";

%feature("docstring")  FitElement::setResidual "void FitElement::setResidual(double value)
";


// File: classFitObject.xml
%feature("docstring") FitObject "

Holds simulation description and real data to run the fit.

C++ includes: FitObject.h
";

%feature("docstring")  FitObject::FitObject "FitObject::FitObject(const GISASSimulation &simulation, const OutputData< double > &real_data, double weight=1)

FitObject constructor

Parameters:
-----------

simulation: 
The simulation to run

real_data: 
The real data

weight: 
Weight of dataset in chi2 calculations

adjust_detector_to_data: 
Detector axes will be adjusted to real data axes, if true 
";

%feature("docstring")  FitObject::~FitObject "FitObject::~FitObject()
";

%feature("docstring")  FitObject::realData "const OutputData< double > & FitObject::realData() const

Returns real (experimental) data. 
";

%feature("docstring")  FitObject::simulationData "const OutputData< double > & FitObject::simulationData() const

Returns simulated data. 
";

%feature("docstring")  FitObject::chiSquaredMap "const OutputData< double > & FitObject::chiSquaredMap() const

Returns chi2 map. 
";

%feature("docstring")  FitObject::simulation "const GISASSimulation & FitObject::simulation() const

Returns simulation. 
";

%feature("docstring")  FitObject::weight "double FitObject::weight() const

Returns weight of data set in chi2 calculations. 
";

%feature("docstring")  FitObject::numberOfFitElements "size_t FitObject::numberOfFitElements() const

Returns the size of the data. It is equal to the number of non-masked detector channels which will participate in chi2 calculations. 
";

%feature("docstring")  FitObject::prepareFitElements "void FitObject::prepareFitElements(std::vector< FitElement > &fit_elements, double weight, IIntensityNormalizer *normalizer=0)

Runs simulation and put results (the real and simulated intensities) into external vector. Masked channels will be excluded from the vector. 
";

%feature("docstring")  FitObject::transferToChi2Map "void FitObject::transferToChi2Map(std::vector< FitElement >::const_iterator first, std::vector< FitElement >::const_iterator last) const

Updates ChiSquared map from external vector and returns const reference to it. Used from Python in FitSuiteDrawObserver. 
";

%feature("docstring")  FitObject::addParametersToExternalPool "std::string FitObject::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children.

Adds parameters from local pool to external pool. 
";


// File: classFitParameterLinked.xml
%feature("docstring") FitParameterLinked "

Fittable parameter, linked to other parameters from pools.

C++ includes: FitParameterLinked.h
";

%feature("docstring")  FitParameterLinked::FitParameterLinked "FitParameterLinked::FitParameterLinked()
";

%feature("docstring")  FitParameterLinked::FitParameterLinked "FitParameterLinked::FitParameterLinked(const std::string &name, double value, const AttLimits &lim=AttLimits::limitless(), double step=0.0)
";

%feature("docstring")  FitParameterLinked::~FitParameterLinked "FitParameterLinked::~FitParameterLinked() final
";

%feature("docstring")  FitParameterLinked::clone "FitParameterLinked * FitParameterLinked::clone() const
";

%feature("docstring")  FitParameterLinked::setValue "void FitParameterLinked::setValue(double value) final

Sets given value for all bound parameters. 
";

%feature("docstring")  FitParameterLinked::addParameter "void FitParameterLinked::addParameter(RealParameter *par)

Adds real parameter to the collection. 
";

%feature("docstring")  FitParameterLinked::addMatchedParametersFromPool "void FitParameterLinked::addMatchedParametersFromPool(const ParameterPool *pool, const std::string &wildcard=std::string())

Adds parameters from pool which match given wildcard. 
";


// File: classFitStrategyAdjustParameters.xml
%feature("docstring") FitStrategyAdjustParameters "

Strategy which fixes/releases fit parameters and call minimizer.

C++ includes: FitStrategyAdjustParameters.h
";

%feature("docstring")  FitStrategyAdjustParameters::FitStrategyAdjustParameters "FitStrategyAdjustParameters::FitStrategyAdjustParameters(const std::string &name)
";

%feature("docstring")  FitStrategyAdjustParameters::FitStrategyAdjustParameters "FitStrategyAdjustParameters::FitStrategyAdjustParameters()
";

%feature("docstring")  FitStrategyAdjustParameters::~FitStrategyAdjustParameters "virtual FitStrategyAdjustParameters::~FitStrategyAdjustParameters()
";

%feature("docstring")  FitStrategyAdjustParameters::clone "virtual FitStrategyAdjustParameters* FitStrategyAdjustParameters::clone() const
";

%feature("docstring")  FitStrategyAdjustParameters::execute "void FitStrategyAdjustParameters::execute()

strategy which fixes/releases fit parameters and then call minimizer 
";

%feature("docstring")  FitStrategyAdjustParameters::fix_all "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::fix_all()
";

%feature("docstring")  FitStrategyAdjustParameters::release_all "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::release_all()
";

%feature("docstring")  FitStrategyAdjustParameters::fix "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::fix(std::string parname)
";

%feature("docstring")  FitStrategyAdjustParameters::release "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::release(std::string parname)
";

%feature("docstring")  FitStrategyAdjustParameters::setPreserveOriginalValues "virtual void FitStrategyAdjustParameters::setPreserveOriginalValues(bool preserve_values)
";

%feature("docstring")  FitStrategyAdjustParameters::clear "virtual void FitStrategyAdjustParameters::clear()
";


// File: classFitStrategyDefault.xml
%feature("docstring") FitStrategyDefault "

Default fit strategy just let  FitSuite to run it's minimization round.

C++ includes: IFitStrategy.h
";

%feature("docstring")  FitStrategyDefault::FitStrategyDefault "FitStrategyDefault::FitStrategyDefault()
";

%feature("docstring")  FitStrategyDefault::clone "FitStrategyDefault * FitStrategyDefault::clone() const
";

%feature("docstring")  FitStrategyDefault::execute "void FitStrategyDefault::execute()
";


// File: classFitStrategyFixParameters.xml
%feature("docstring") FitStrategyFixParameters "

Strategy which fixes certain fit parameters leaving other released.

C++ includes: FitStrategyAdjustParameters.h
";

%feature("docstring")  FitStrategyFixParameters::FitStrategyFixParameters "FitStrategyFixParameters::FitStrategyFixParameters()
";

%feature("docstring")  FitStrategyFixParameters::FitStrategyFixParameters "FitStrategyFixParameters::FitStrategyFixParameters(const std::vector< std::string > &pars)
";

%feature("docstring")  FitStrategyFixParameters::~FitStrategyFixParameters "virtual FitStrategyFixParameters::~FitStrategyFixParameters()
";

%feature("docstring")  FitStrategyFixParameters::clone "virtual FitStrategyFixParameters* FitStrategyFixParameters::clone() const
";

%feature("docstring")  FitStrategyFixParameters::clear "virtual void FitStrategyFixParameters::clear()
";

%feature("docstring")  FitStrategyFixParameters::setFixed "virtual void FitStrategyFixParameters::setFixed(const std::vector< std::string > &pars)
";


// File: classFitStrategyReleaseParameters.xml
%feature("docstring") FitStrategyReleaseParameters "

Strategy which releases certain fit parameters leaving other fixed.

C++ includes: FitStrategyAdjustParameters.h
";

%feature("docstring")  FitStrategyReleaseParameters::FitStrategyReleaseParameters "FitStrategyReleaseParameters::FitStrategyReleaseParameters()
";

%feature("docstring")  FitStrategyReleaseParameters::FitStrategyReleaseParameters "FitStrategyReleaseParameters::FitStrategyReleaseParameters(const std::vector< std::string > &pars)
";

%feature("docstring")  FitStrategyReleaseParameters::~FitStrategyReleaseParameters "virtual FitStrategyReleaseParameters::~FitStrategyReleaseParameters()
";

%feature("docstring")  FitStrategyReleaseParameters::clone "virtual FitStrategyReleaseParameters* FitStrategyReleaseParameters::clone() const
";

%feature("docstring")  FitStrategyReleaseParameters::clear "virtual void FitStrategyReleaseParameters::clear()
";

%feature("docstring")  FitStrategyReleaseParameters::setReleased "virtual void FitStrategyReleaseParameters::setReleased(const std::vector< std::string > &pars)
";


// File: classFitSuite.xml
%feature("docstring") FitSuite "

User interface class that wraps all fit methods.

C++ includes: FitSuite.h
";

%feature("docstring")  FitSuite::FitSuite "FitSuite::FitSuite()
";

%feature("docstring")  FitSuite::FitSuite "FitSuite::FitSuite(const FitSuite &)=delete
";

%feature("docstring")  FitSuite::~FitSuite "FitSuite::~FitSuite()
";

%feature("docstring")  FitSuite::addSimulationAndRealData "void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation, const OutputData< double > &real_data, double weight=1)

Assigns pair of (simulation, real data) for fitting. More than one pair can be added. 
";

%feature("docstring")  FitSuite::addSimulationAndRealData "void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation, const IHistogram &real_data, double weight=1)

Assigns pair of (simulation, real data) for fitting. More than one pair can be added. 
";

%feature("docstring")  FitSuite::addSimulationAndRealData "void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation, const std::vector< std::vector< double >> &real_data, double weight=1)

Assigns pair of (simulation, real data) for fitting. Numpy array is used to provide intensities. Shape of array (nrows, ncols) should coinside with detector's axes (n_alpha, n_phi). 
";

%feature("docstring")  FitSuite::addFitParameter "FitParameterLinked * FitSuite::addFitParameter(const std::string &name, double value, const AttLimits &limits=AttLimits::limitless(), double step=0.0)

Adds fit parameter

Parameters:
-----------

name: 
The name of fit parameter

value: 
Parameter's starting value

limits: 
Limits attribute

step: 
Initial parameter's step (some minimizers don't use it) 
";

%feature("docstring")  FitSuite::setMinimizer "void FitSuite::setMinimizer(const std::string &minimizer_name, const std::string &algorithm_name=std::string(), const std::string &minimizer_options=std::string())

Sets minimizer with given name and algorithm type

Parameters:
-----------

minimizer_name: 
The name of the minimizer

algorithm_name: 
Optional name of the minimizer's algorithm

minimizer_options: 
Optional string with additional minimizer settings 
";

%feature("docstring")  FitSuite::setChiSquaredModule "void FitSuite::setChiSquaredModule(const IChiSquaredModule &chi2_module)

Replaces default  ChiSquaredModule with new one. 
";

%feature("docstring")  FitSuite::addFitStrategy "void FitSuite::addFitStrategy(const IFitStrategy &strategy)

Adds fit strategy. 
";

%feature("docstring")  FitSuite::setMinimizer "void FitSuite::setMinimizer(IMinimizer *minimizer)

Sets minimizer. 
";

%feature("docstring")  FitSuite::minimizer "const IMinimizer * FitSuite::minimizer() const

Returns minimizer. 
";

%feature("docstring")  FitSuite::initPrint "void FitSuite::initPrint(int print_every_nth)

Initializes printing to standard output during the fitting. Prints also the summary when completed.

Parameters:
-----------

print_every_nth: 
Print every n'th iteration 
";

%feature("docstring")  FitSuite::runFit "void FitSuite::runFit()

main method to run the fitting 
";

%feature("docstring")  FitSuite::numberOfFitObjects "int FitSuite::numberOfFitObjects() const

Returns number of fit objects, where fit object stands for (real, simulated) pair. 
";

%feature("docstring")  FitSuite::getRealData "IHistogram * FitSuite::getRealData(size_t i_item=0) const

returns real data histogram

Parameters:
-----------

i_item: 
The index of fit object 
";

%feature("docstring")  FitSuite::getSimulationData "IHistogram * FitSuite::getSimulationData(size_t i_item=0) const

returns simulated data histogram

Parameters:
-----------

i_item: 
The index of fit object 
";

%feature("docstring")  FitSuite::getChiSquaredMap "IHistogram * FitSuite::getChiSquaredMap(size_t i_item=0) const

returns chi2 histogram calculated for (real, simulated) data pair

Parameters:
-----------

i_item: 
The index of fit object 
";

%feature("docstring")  FitSuite::fitObjects "FitSuiteObjects * FitSuite::fitObjects()

returns  FitObject (pair of simulation/real data) 
";

%feature("docstring")  FitSuite::fitParameters "FitParameterSet * FitSuite::fitParameters()

Returns reference to fit parameters. 
";

%feature("docstring")  FitSuite::fitStrategies "FitSuiteStrategies * FitSuite::fitStrategies()

Returns reference to fit parameters. 
";

%feature("docstring")  FitSuite::isLastIteration "bool FitSuite::isLastIteration() const

if the last iteration is done (used by observers to print summary) 
";

%feature("docstring")  FitSuite::numberOfIterations "size_t FitSuite::numberOfIterations() const

Returns current number of minimization function calls. 
";

%feature("docstring")  FitSuite::currentStrategyIndex "size_t FitSuite::currentStrategyIndex() const

Returns the number of current strategy. 
";

%feature("docstring")  FitSuite::printResults "void FitSuite::printResults() const

Prints results of the minimization to the standard output. 
";

%feature("docstring")  FitSuite::reportResults "std::string FitSuite::reportResults() const

Reports results of minimization in the form of multi-line string. 
";

%feature("docstring")  FitSuite::getChi2 "double FitSuite::getChi2() const

Returns minimum chi squared value found. 
";

%feature("docstring")  FitSuite::interruptFitting "void FitSuite::interruptFitting()
";

%feature("docstring")  FitSuite::resetInterrupt "void FitSuite::resetInterrupt()
";

%feature("docstring")  FitSuite::isInterrupted "bool FitSuite::isInterrupted()
";

%feature("docstring")  FitSuite::getRealOutputData "const OutputData< double > * FitSuite::getRealOutputData(size_t i_item=0) const
";

%feature("docstring")  FitSuite::getSimulationOutputData "const OutputData< double > * FitSuite::getSimulationOutputData(size_t i_item=0) const
";

%feature("docstring")  FitSuite::getChiSquaredOutputData "const OutputData< double > * FitSuite::getChiSquaredOutputData(size_t i_item=0) const
";


// File: classFitSuiteChiSquaredFunction.xml
%feature("docstring") FitSuiteChiSquaredFunction "

Chi squared fitting function for minimizer.

C++ includes: FitSuiteFunctions.h
";

%feature("docstring")  FitSuiteChiSquaredFunction::FitSuiteChiSquaredFunction "FitSuiteChiSquaredFunction::FitSuiteChiSquaredFunction()
";

%feature("docstring")  FitSuiteChiSquaredFunction::~FitSuiteChiSquaredFunction "virtual FitSuiteChiSquaredFunction::~FitSuiteChiSquaredFunction()
";

%feature("docstring")  FitSuiteChiSquaredFunction::evaluate "double FitSuiteChiSquaredFunction::evaluate(const std::vector< double > &pars)

evaluate method for chi2 value called directly from the minimizer

evaluate chi squared value 
";


// File: classFitSuiteGradientFunction.xml
%feature("docstring") FitSuiteGradientFunction "

Gradient fitting function for minimizer.

C++ includes: FitSuiteFunctions.h
";

%feature("docstring")  FitSuiteGradientFunction::FitSuiteGradientFunction "FitSuiteGradientFunction::FitSuiteGradientFunction()
";

%feature("docstring")  FitSuiteGradientFunction::~FitSuiteGradientFunction "virtual FitSuiteGradientFunction::~FitSuiteGradientFunction()
";

%feature("docstring")  FitSuiteGradientFunction::evaluate "double FitSuiteGradientFunction::evaluate(const std::vector< double > &pars, unsigned int index, std::vector< double > &gradients)

evaluate method for gradients and residuals called directly from the minimizer

evaluate residual and derivative for given data element 
";

%feature("docstring")  FitSuiteGradientFunction::getNCallsTotal "virtual size_t FitSuiteGradientFunction::getNCallsTotal() const
";

%feature("docstring")  FitSuiteGradientFunction::getNCallsGradient "virtual size_t FitSuiteGradientFunction::getNCallsGradient() const
";


// File: classFitSuiteImpl.xml
%feature("docstring") FitSuiteImpl "

Fitting kernel for  FitSuite.

C++ includes: FitSuiteImpl.h
";

%feature("docstring")  FitSuiteImpl::FitSuiteImpl "FitSuiteImpl::FitSuiteImpl(const std::function< void()> &notifyObservers)
";

%feature("docstring")  FitSuiteImpl::FitSuiteImpl "FitSuiteImpl::FitSuiteImpl(const FitSuiteImpl &)=delete
";

%feature("docstring")  FitSuiteImpl::~FitSuiteImpl "FitSuiteImpl::~FitSuiteImpl()
";

%feature("docstring")  FitSuiteImpl::clear "void FitSuiteImpl::clear()

Resets most state variables, to get prepared for the next fit.

Clears all data. 
";

%feature("docstring")  FitSuiteImpl::addSimulationAndRealData "void FitSuiteImpl::addSimulationAndRealData(const GISASSimulation &simulation, const OutputData< double > &real_data, double weight)

Adds pair of (simulation, real data) for consecutive simulation. 
";

%feature("docstring")  FitSuiteImpl::addFitParameter "FitParameterLinked * FitSuiteImpl::addFitParameter(const std::string &name, double value, const AttLimits &limits, double step=0.0)

Adds fit parameter.

Adds fit parameter, step is calculated from initial parameter value. 
";

%feature("docstring")  FitSuiteImpl::addFitStrategy "void FitSuiteImpl::addFitStrategy(const IFitStrategy &strategy)

Adds fit strategy. 
";

%feature("docstring")  FitSuiteImpl::setMinimizer "void FitSuiteImpl::setMinimizer(IMinimizer *minimizer)

Sets minimizer. 
";

%feature("docstring")  FitSuiteImpl::runFit "void FitSuiteImpl::runFit()

Runs a fit, which may consist of several minimization rounds. 
";

%feature("docstring")  FitSuiteImpl::minimize "void FitSuiteImpl::minimize()

Runs a single minimization round (called by FitSuiteStrategy) 
";

%feature("docstring")  FitSuiteImpl::fitObjects "FitSuiteObjects* FitSuiteImpl::fitObjects()

Returns reference to the kit with data. 
";

%feature("docstring")  FitSuiteImpl::fitObjects "const FitSuiteObjects* FitSuiteImpl::fitObjects() const
";

%feature("docstring")  FitSuiteImpl::fitParameters "FitParameterSet * FitSuiteImpl::fitParameters()

Returns reference to fit parameters. 
";

%feature("docstring")  FitSuiteImpl::fitStrategies "FitSuiteStrategies* FitSuiteImpl::fitStrategies()

Returns reference to fit parameters. 
";

%feature("docstring")  FitSuiteImpl::isLastIteration "bool FitSuiteImpl::isLastIteration() const

Returns true if the last iteration is done (used by observers to print summary) 
";

%feature("docstring")  FitSuiteImpl::numberOfIterations "size_t FitSuiteImpl::numberOfIterations() const

Returns current number of minimization function calls. 
";

%feature("docstring")  FitSuiteImpl::currentStrategyIndex "size_t FitSuiteImpl::currentStrategyIndex() const

Returns the number of current strategy. 
";

%feature("docstring")  FitSuiteImpl::reportResults "std::string FitSuiteImpl::reportResults() const

Reports results of minimization in the form of multi-line string. 
";

%feature("docstring")  FitSuiteImpl::getOptions "FitOptions& FitSuiteImpl::getOptions()

Returns current fit options. 
";

%feature("docstring")  FitSuiteImpl::setOptions "void FitSuiteImpl::setOptions(const FitOptions &fit_options)

Sets fit options. 
";

%feature("docstring")  FitSuiteImpl::notifyObservers "void FitSuiteImpl::notifyObservers()
";

%feature("docstring")  FitSuiteImpl::interruptFitting "void FitSuiteImpl::interruptFitting()
";

%feature("docstring")  FitSuiteImpl::resetInterrupt "void FitSuiteImpl::resetInterrupt()
";

%feature("docstring")  FitSuiteImpl::isInterrupted "bool FitSuiteImpl::isInterrupted() const
";

%feature("docstring")  FitSuiteImpl::kernel "const FitKernel * FitSuiteImpl::kernel() const
";


// File: classFitSuiteObjects.xml
%feature("docstring") FitSuiteObjects "

Holds vector of  FitObject's (simulation and real data) to fit

C++ includes: FitSuiteObjects.h
";

%feature("docstring")  FitSuiteObjects::FitSuiteObjects "FitSuiteObjects::FitSuiteObjects()
";

%feature("docstring")  FitSuiteObjects::~FitSuiteObjects "FitSuiteObjects::~FitSuiteObjects()
";

%feature("docstring")  FitSuiteObjects::add "void FitSuiteObjects::add(const GISASSimulation &simulation, const OutputData< double > &real_data, double weight=1.0)

Adds to kit pair of (simulation, real data) for consecutive simulation. 
";

%feature("docstring")  FitSuiteObjects::getNumberOfFitObjects "size_t FitSuiteObjects::getNumberOfFitObjects() const

Returns number of fit objects (simulation/real data pairs) 
";

%feature("docstring")  FitSuiteObjects::getSizeOfDataSet "size_t FitSuiteObjects::getSizeOfDataSet() const

Returns total number of data points (number of all non-masked channels in all fit objects)

Returns total number of data points. 
";

%feature("docstring")  FitSuiteObjects::setChiSquaredModule "void FitSuiteObjects::setChiSquaredModule(const IChiSquaredModule &chi2_module)

Replaces default  ChiSquaredModule with new one. 
";

%feature("docstring")  FitSuiteObjects::getRealData "const OutputData< double > & FitSuiteObjects::getRealData(size_t i_item=0) const

Returns real data from corresponding  FitObject

Parameters:
-----------

i_item: 
Index of  FitObject
";

%feature("docstring")  FitSuiteObjects::getSimulationData "const OutputData< double > & FitSuiteObjects::getSimulationData(size_t i_item=0) const

Returns simulated data from corresponding  FitObject

Parameters:
-----------

i_item: 
Index of  FitObject
";

%feature("docstring")  FitSuiteObjects::getChiSquaredMap "const OutputData< double > & FitSuiteObjects::getChiSquaredMap(size_t i_item=0) const

Returns new chi-squared map from corresponding  FitObject

Parameters:
-----------

i_item: 
Index of  FitObject
";

%feature("docstring")  FitSuiteObjects::runSimulations "void FitSuiteObjects::runSimulations()

run all simulation defined in fit pairs

loop through all defined simulations and run them 
";

%feature("docstring")  FitSuiteObjects::getChiSquaredValue "double FitSuiteObjects::getChiSquaredValue() const

Returns chi2 calculated over whole dataset. 
";

%feature("docstring")  FitSuiteObjects::getResidualValue "double FitSuiteObjects::getResidualValue(size_t global_index)

Returns residuals for single data element

Parameters:
-----------

global_index: 
index accross all element in  FitElement vector 
";

%feature("docstring")  FitSuiteObjects::addParametersToExternalPool "std::string FitSuiteObjects::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and call recursion over direct children.

Adds parameters from local pool to external pool. 
";

%feature("docstring")  FitSuiteObjects::setNfreeParameters "void FitSuiteObjects::setNfreeParameters(int nfree_parameters)
";

%feature("docstring")  FitSuiteObjects::clear "void FitSuiteObjects::clear()

clear all data 
";


// File: classFitSuitePrintObserver.xml
%feature("docstring") FitSuitePrintObserver "

Prints fit progress at the end of each  FitSuite's iteration.

C++ includes: FitSuitePrintObserver.h
";

%feature("docstring")  FitSuitePrintObserver::FitSuitePrintObserver "FitSuitePrintObserver::FitSuitePrintObserver(int print_every_nth=1)
";

%feature("docstring")  FitSuitePrintObserver::~FitSuitePrintObserver "virtual FitSuitePrintObserver::~FitSuitePrintObserver()
";

%feature("docstring")  FitSuitePrintObserver::update "void FitSuitePrintObserver::update(FitSuite *fit_suite)

Here Onserver will do actuall job when he thinks that it is a right moment. 
";


// File: classFitSuiteStrategies.xml
%feature("docstring") FitSuiteStrategies "

Collection of strategies to fit.

C++ includes: FitSuiteStrategies.h
";

%feature("docstring")  FitSuiteStrategies::FitSuiteStrategies "FitSuiteStrategies::FitSuiteStrategies()
";

%feature("docstring")  FitSuiteStrategies::~FitSuiteStrategies "FitSuiteStrategies::~FitSuiteStrategies()
";

%feature("docstring")  FitSuiteStrategies::FitSuiteStrategies "FitSuiteStrategies::FitSuiteStrategies(const FitSuiteStrategies &other)=delete
";

%feature("docstring")  FitSuiteStrategies::init "void FitSuiteStrategies::init(FitSuiteImpl *fit_suite)
";

%feature("docstring")  FitSuiteStrategies::addStrategy "void FitSuiteStrategies::addStrategy(const IFitStrategy &strategy)
";

%feature("docstring")  FitSuiteStrategies::minimize "void FitSuiteStrategies::minimize()
";

%feature("docstring")  FitSuiteStrategies::currentStrategyIndex "size_t FitSuiteStrategies::currentStrategyIndex() const
";

%feature("docstring")  FitSuiteStrategies::size "size_t FitSuiteStrategies::size() const
";

%feature("docstring")  FitSuiteStrategies::clear "void FitSuiteStrategies::clear()
";

%feature("docstring")  FitSuiteStrategies::currentStrategy "IFitStrategy * FitSuiteStrategies::currentStrategy()
";


// File: classFixedBinAxis.xml
%feature("docstring") FixedBinAxis "

Axis with fixed bin size.

C++ includes: FixedBinAxis.h
";

%feature("docstring")  FixedBinAxis::FixedBinAxis "FixedBinAxis::FixedBinAxis(const std::string &name, size_t nbins, double start, double end)

FixedBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

start: 
low edge of first bin

end: 
upper edge of last bin 
";

%feature("docstring")  FixedBinAxis::~FixedBinAxis "virtual FixedBinAxis::~FixedBinAxis()
";

%feature("docstring")  FixedBinAxis::clone "FixedBinAxis * FixedBinAxis::clone() const

clone function 
";

%feature("docstring")  FixedBinAxis::size "size_t FixedBinAxis::size() const

retrieve the number of bins 
";

%feature("docstring")  FixedBinAxis::getBin "Bin1D FixedBinAxis::getBin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  FixedBinAxis::getMin "double FixedBinAxis::getMin() const

Returns value of first point of axis. 
";

%feature("docstring")  FixedBinAxis::getMax "double FixedBinAxis::getMax() const

Returns value of last point of axis. 
";

%feature("docstring")  FixedBinAxis::getBinCenter "double FixedBinAxis::getBinCenter(size_t index) const
";

%feature("docstring")  FixedBinAxis::findClosestIndex "size_t FixedBinAxis::findClosestIndex(double value) const

find bin index which is best match for given value 
";

%feature("docstring")  FixedBinAxis::getBinCenters "std::vector< double > FixedBinAxis::getBinCenters() const
";

%feature("docstring")  FixedBinAxis::getBinBoundaries "std::vector< double > FixedBinAxis::getBinBoundaries() const
";

%feature("docstring")  FixedBinAxis::createClippedAxis "FixedBinAxis * FixedBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classException_1_1FormatErrorException.xml
%feature("docstring") Exception::FormatErrorException "";

%feature("docstring")  Exception::FormatErrorException::FormatErrorException "Exception::FormatErrorException::FormatErrorException(const std::string &message)
";


// File: classFormFactorAnisoPyramid.xml
%feature("docstring") FormFactorAnisoPyramid "

A frustum (truncated pyramid) with rectangular base.

C++ includes: FormFactorAnisoPyramid.h
";

%feature("docstring")  FormFactorAnisoPyramid::FormFactorAnisoPyramid "FormFactorAnisoPyramid::FormFactorAnisoPyramid(double length, double width, double height, double alpha)

Parameters:
-----------

length: 
of one side of the rectangular base

width: 
of other side of the rectangular base

height: 
of frustum

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorAnisoPyramid::clone "FormFactorAnisoPyramid* FormFactorAnisoPyramid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorAnisoPyramid::accept "void FormFactorAnisoPyramid::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorAnisoPyramid::getLength "double FormFactorAnisoPyramid::getLength() const
";

%feature("docstring")  FormFactorAnisoPyramid::getWidth "double FormFactorAnisoPyramid::getWidth() const
";

%feature("docstring")  FormFactorAnisoPyramid::getHeight "double FormFactorAnisoPyramid::getHeight() const
";

%feature("docstring")  FormFactorAnisoPyramid::getAlpha "double FormFactorAnisoPyramid::getAlpha() const
";


// File: classFormFactorBox.xml
%feature("docstring") FormFactorBox "

A rectangular prism (parallelepiped).

C++ includes: FormFactorBox.h
";

%feature("docstring")  FormFactorBox::FormFactorBox "FormFactorBox::FormFactorBox(double length, double width, double height)

Parameters:
-----------

length: 
of rectangular base

width: 
of rectangular base

height: 
of prism 
";

%feature("docstring")  FormFactorBox::clone "FormFactorBox* FormFactorBox::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorBox::accept "void FormFactorBox::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorBox::getLength "double FormFactorBox::getLength() const
";

%feature("docstring")  FormFactorBox::getHeight "double FormFactorBox::getHeight() const
";

%feature("docstring")  FormFactorBox::getWidth "double FormFactorBox::getWidth() const
";

%feature("docstring")  FormFactorBox::getRadialExtension "double FormFactorBox::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorBox::evaluate_for_q "complex_t FormFactorBox::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorCone.xml
%feature("docstring") FormFactorCone "

A conical frustum (cone truncated parallel to the base) with circular base.

C++ includes: FormFactorCone.h
";

%feature("docstring")  FormFactorCone::FormFactorCone "FormFactorCone::FormFactorCone(double radius, double height, double alpha)

Parameters:
-----------

radius: 
of circular base

height: 
of frustum

alpha: 
angle in radians between base and lateral surface 
";

%feature("docstring")  FormFactorCone::clone "FormFactorCone* FormFactorCone::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCone::accept "void FormFactorCone::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCone::getHeight "double FormFactorCone::getHeight() const
";

%feature("docstring")  FormFactorCone::getAlpha "double FormFactorCone::getAlpha() const
";

%feature("docstring")  FormFactorCone::getRadius "double FormFactorCone::getRadius() const
";

%feature("docstring")  FormFactorCone::getRadialExtension "double FormFactorCone::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCone::evaluate_for_q "complex_t FormFactorCone::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorCone6.xml
%feature("docstring") FormFactorCone6 "

A frustum (truncated pyramid) with regular hexagonal base.

C++ includes: FormFactorCone6.h
";

%feature("docstring")  FormFactorCone6::FormFactorCone6 "FormFactorCone6::FormFactorCone6(double base_edge, double height, double alpha)

Parameters:
-----------

base_edge: 
of hexagonal base

height: 
of frustum

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorCone6::clone "FormFactorCone6* FormFactorCone6::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCone6::accept "void FormFactorCone6::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCone6::getBaseEdge "double FormFactorCone6::getBaseEdge() const
";

%feature("docstring")  FormFactorCone6::getHeight "double FormFactorCone6::getHeight() const
";

%feature("docstring")  FormFactorCone6::getAlpha "double FormFactorCone6::getAlpha() const
";


// File: classFormFactorCrystal.xml
%feature("docstring") FormFactorCrystal "

The formfactor of a  MesoCrystal.

C++ includes: FormFactorCrystal.h
";

%feature("docstring")  FormFactorCrystal::FormFactorCrystal "FormFactorCrystal::FormFactorCrystal(const Lattice &lattice, const IFormFactor &basis_form_factor, const IFormFactor &meso_form_factor)
";

%feature("docstring")  FormFactorCrystal::~FormFactorCrystal "FormFactorCrystal::~FormFactorCrystal() override final
";

%feature("docstring")  FormFactorCrystal::clone "FormFactorCrystal* FormFactorCrystal::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCrystal::accept "void FormFactorCrystal::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCrystal::getVolume "double FormFactorCrystal::getVolume() const override final

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorCrystal::getRadialExtension "double FormFactorCrystal::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCrystal::evaluate "complex_t FormFactorCrystal::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorCrystal::evaluatePol "Eigen::Matrix2cd FormFactorCrystal::evaluatePol(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorCuboctahedron.xml
%feature("docstring") FormFactorCuboctahedron "

A truncated bifrustum with quadratic base.

C++ includes: FormFactorCuboctahedron.h
";

%feature("docstring")  FormFactorCuboctahedron::FormFactorCuboctahedron "FormFactorCuboctahedron::FormFactorCuboctahedron(double length, double height, double height_ratio, double alpha)

Parameters:
-----------

length: 
of one side of the square base

height: 
of bottom frustum

height_ratio: 
ratio of heights of top to bottom frustum

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorCuboctahedron::clone "FormFactorCuboctahedron* FormFactorCuboctahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCuboctahedron::accept "void FormFactorCuboctahedron::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCuboctahedron::getLength "double FormFactorCuboctahedron::getLength() const
";

%feature("docstring")  FormFactorCuboctahedron::getHeight "double FormFactorCuboctahedron::getHeight() const
";

%feature("docstring")  FormFactorCuboctahedron::getHeightRatio "double FormFactorCuboctahedron::getHeightRatio() const
";

%feature("docstring")  FormFactorCuboctahedron::getAlpha "double FormFactorCuboctahedron::getAlpha() const
";


// File: classFormFactorCylinder.xml
%feature("docstring") FormFactorCylinder "

A circular cylinder.

C++ includes: FormFactorCylinder.h
";

%feature("docstring")  FormFactorCylinder::FormFactorCylinder "FormFactorCylinder::FormFactorCylinder(double radius, double height)
";

%feature("docstring")  FormFactorCylinder::clone "FormFactorCylinder* FormFactorCylinder::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCylinder::accept "void FormFactorCylinder::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCylinder::getHeight "double FormFactorCylinder::getHeight() const
";

%feature("docstring")  FormFactorCylinder::getRadius "double FormFactorCylinder::getRadius() const
";

%feature("docstring")  FormFactorCylinder::getRadialExtension "double FormFactorCylinder::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCylinder::evaluate_for_q "complex_t FormFactorCylinder::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorDecoratorDebyeWaller.xml
%feature("docstring") FormFactorDecoratorDebyeWaller "

Debye-Waller factors in radial and z directions.

C++ includes: FormFactorDecoratorDebyeWaller.h
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller "FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor, double dw_h_factor, double dw_r_factor)

Anisotropic Debye-Waller factor. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller "FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor, double dw_factor)

Isotropic Debye-Waller factor. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::clone "FormFactorDecoratorDebyeWaller* FormFactorDecoratorDebyeWaller::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::accept "void FormFactorDecoratorDebyeWaller::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::evaluate "complex_t FormFactorDecoratorDebyeWaller::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorDebyeWaller::evaluatePol(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorFactor.xml
%feature("docstring") FormFactorDecoratorFactor "

Decorates a formfactor with a constant factor. Base class of  FormFactorDecoratorMaterial.

C++ includes: FormFactorDecoratorFactor.h
";

%feature("docstring")  FormFactorDecoratorFactor::FormFactorDecoratorFactor "FormFactorDecoratorFactor::FormFactorDecoratorFactor(const IFormFactor &form_factor, const complex_t factor)
";

%feature("docstring")  FormFactorDecoratorFactor::clone "FormFactorDecoratorFactor* FormFactorDecoratorFactor::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorFactor::accept "void FormFactorDecoratorFactor::accept(ISampleVisitor *visitor) const override

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorFactor::evaluate "complex_t FormFactorDecoratorFactor::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorFactor::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorFactor::evaluatePol(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorMaterial.xml
%feature("docstring") FormFactorDecoratorMaterial "

Decorates a scalar formfactor with the correct factor for the material's refractive index and that of its surrounding material.

C++ includes: FormFactorDecoratorMaterial.h
";

%feature("docstring")  FormFactorDecoratorMaterial::FormFactorDecoratorMaterial "FormFactorDecoratorMaterial::FormFactorDecoratorMaterial(const IFormFactor &form_factor)
";

%feature("docstring")  FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial "FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial() override final
";

%feature("docstring")  FormFactorDecoratorMaterial::clone "FormFactorDecoratorMaterial * FormFactorDecoratorMaterial::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorMaterial::accept "void FormFactorDecoratorMaterial::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorMaterial::setMaterial "void FormFactorDecoratorMaterial::setMaterial(const IMaterial &material)

Sets the material of the scatterer. 
";

%feature("docstring")  FormFactorDecoratorMaterial::setAmbientMaterial "void FormFactorDecoratorMaterial::setAmbientMaterial(const IMaterial &material) override

Sets the ambient material. 
";

%feature("docstring")  FormFactorDecoratorMaterial::getAmbientRefractiveIndex "complex_t FormFactorDecoratorMaterial::getAmbientRefractiveIndex() const
";

%feature("docstring")  FormFactorDecoratorMaterial::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorPositionFactor.xml
%feature("docstring") FormFactorDecoratorPositionFactor "

Decorates a formfactor with a position dependent phase factor.

C++ includes: FormFactorDecoratorPositionFactor.h
";

%feature("docstring")  FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor "FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(const IFormFactor &form_factor, const kvector_t &position)
";

%feature("docstring")  FormFactorDecoratorPositionFactor::clone "FormFactorDecoratorPositionFactor* FormFactorDecoratorPositionFactor::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::accept "void FormFactorDecoratorPositionFactor::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluate "complex_t FormFactorDecoratorPositionFactor::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorPositionFactor::evaluatePol(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorRotation.xml
%feature("docstring") FormFactorDecoratorRotation "

Equips a formfactor with a rotation.

C++ includes: FormFactorDecoratorRotation.h
";

%feature("docstring")  FormFactorDecoratorRotation::FormFactorDecoratorRotation "FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor &form_factor, const IRotation &rotation)

Constructor, setting form factor and rotation. 
";

%feature("docstring")  FormFactorDecoratorRotation::clone "FormFactorDecoratorRotation * FormFactorDecoratorRotation::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorRotation::accept "void FormFactorDecoratorRotation::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorRotation::evaluate "complex_t FormFactorDecoratorRotation::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorRotation::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorRotation::evaluatePol(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDodecahedron.xml
%feature("docstring") FormFactorDodecahedron "

A regular dodecahedron.

C++ includes: FormFactorDodecahedron.h
";

%feature("docstring")  FormFactorDodecahedron::FormFactorDodecahedron "FormFactorDodecahedron::FormFactorDodecahedron(double edge)

Constructs a regular dodecahedron.

Parameters:
-----------

edge: 
length 
";

%feature("docstring")  FormFactorDodecahedron::clone "FormFactorDodecahedron* FormFactorDodecahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDodecahedron::accept "void FormFactorDodecahedron::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDodecahedron::getEdge "double FormFactorDodecahedron::getEdge() const
";


// File: classFormFactorDWBA.xml
%feature("docstring") FormFactorDWBA "

Evaluates the coherent sum of the four DWBA terms in a scalar  IFormFactor.

C++ includes: FormFactorDWBA.h
";

%feature("docstring")  FormFactorDWBA::FormFactorDWBA "FormFactorDWBA::FormFactorDWBA(const IFormFactor &form_factor)
";

%feature("docstring")  FormFactorDWBA::~FormFactorDWBA "FormFactorDWBA::~FormFactorDWBA() override
";

%feature("docstring")  FormFactorDWBA::clone "FormFactorDWBA * FormFactorDWBA::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDWBA::accept "void FormFactorDWBA::accept(ISampleVisitor *visitor) const override

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDWBA::evaluate "complex_t FormFactorDWBA::evaluate(const WavevectorInfo &wavevectors) const override

Calculates and returns a form factor calculation in DWBA. 
";

%feature("docstring")  FormFactorDWBA::getVolume "double FormFactorDWBA::getVolume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorDWBA::getRadialExtension "double FormFactorDWBA::getRadialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDWBA::setSpecularInfo "void FormFactorDWBA::setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs, const ILayerRTCoefficients *p_out_coeffs) override

Sets reflection/transmission info for scalar DWBA simulation. 
";


// File: classFormFactorDWBAPol.xml
%feature("docstring") FormFactorDWBAPol "

Evaluates the coherent sum of the 16 matrix DWBA terms in a polarized  IFormFactor.

C++ includes: FormFactorDWBAPol.h
";

%feature("docstring")  FormFactorDWBAPol::FormFactorDWBAPol "FormFactorDWBAPol::FormFactorDWBAPol(const IFormFactor &form_factor)
";

%feature("docstring")  FormFactorDWBAPol::~FormFactorDWBAPol "FormFactorDWBAPol::~FormFactorDWBAPol() override
";

%feature("docstring")  FormFactorDWBAPol::clone "FormFactorDWBAPol * FormFactorDWBAPol::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDWBAPol::accept "void FormFactorDWBAPol::accept(ISampleVisitor *visitor) const override

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDWBAPol::evaluate "complex_t FormFactorDWBAPol::evaluate(const WavevectorInfo &wavevectors) const override

Throws not-implemented exception. 
";

%feature("docstring")  FormFactorDWBAPol::evaluatePol "Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const WavevectorInfo &wavevectors) const override

Calculates and returns a polarized form factor calculation in DWBA. 
";

%feature("docstring")  FormFactorDWBAPol::getVolume "double FormFactorDWBAPol::getVolume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorDWBAPol::getRadialExtension "double FormFactorDWBAPol::getRadialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDWBAPol::setSpecularInfo "void FormFactorDWBAPol::setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs, const ILayerRTCoefficients *p_out_coeffs) override

Sets reflection/transmission info for scalar DWBA simulation. 
";


// File: classFormFactorEllipsoidalCylinder.xml
%feature("docstring") FormFactorEllipsoidalCylinder "

A cylinder with elliptical base.

C++ includes: FormFactorEllipsoidalCylinder.h
";

%feature("docstring")  FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder "FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_x, double radius_y, double height)

Parameters:
-----------

radius_x: 
half length of one horizontal main axes

radius_y: 
half length of the other horizontal main axes

height: 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::clone "FormFactorEllipsoidalCylinder* FormFactorEllipsoidalCylinder::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::accept "void FormFactorEllipsoidalCylinder::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusX "double FormFactorEllipsoidalCylinder::getRadiusX() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusY "double FormFactorEllipsoidalCylinder::getRadiusY() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getHeight "double FormFactorEllipsoidalCylinder::getHeight() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadialExtension "double FormFactorEllipsoidalCylinder::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::evaluate_for_q "complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorFullSphere.xml
%feature("docstring") FormFactorFullSphere "

A full sphere.

C++ includes: FormFactorFullSphere.h
";

%feature("docstring")  FormFactorFullSphere::FormFactorFullSphere "FormFactorFullSphere::FormFactorFullSphere(double radius)
";

%feature("docstring")  FormFactorFullSphere::clone "FormFactorFullSphere* FormFactorFullSphere::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorFullSphere::accept "void FormFactorFullSphere::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorFullSphere::getRadius "double FormFactorFullSphere::getRadius() const
";

%feature("docstring")  FormFactorFullSphere::getRadialExtension "double FormFactorFullSphere::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorFullSphere::evaluate_for_q "complex_t FormFactorFullSphere::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorFullSpheroid.xml
%feature("docstring") FormFactorFullSpheroid "

A full spheroid (an ellipsoid with two equal axes, hence with circular cross section)

C++ includes: FormFactorFullSpheroid.h
";

%feature("docstring")  FormFactorFullSpheroid::FormFactorFullSpheroid "FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height)

Parameters:
-----------

radius: 
of the two equal axes

height: 
total height of the spheroid, i.e. twice the radius of the third axis 
";

%feature("docstring")  FormFactorFullSpheroid::clone "FormFactorFullSpheroid* FormFactorFullSpheroid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorFullSpheroid::accept "void FormFactorFullSpheroid::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorFullSpheroid::getHeight "double FormFactorFullSpheroid::getHeight() const
";

%feature("docstring")  FormFactorFullSpheroid::getRadius "double FormFactorFullSpheroid::getRadius() const
";

%feature("docstring")  FormFactorFullSpheroid::getRadialExtension "double FormFactorFullSpheroid::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorFullSpheroid::evaluate_for_q "complex_t FormFactorFullSpheroid::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorGauss.xml
%feature("docstring") FormFactorGauss "

The formfactor of a gaussian.

C++ includes: FormFactorGauss.h
";

%feature("docstring")  FormFactorGauss::FormFactorGauss "FormFactorGauss::FormFactorGauss(double length)
";

%feature("docstring")  FormFactorGauss::FormFactorGauss "FormFactorGauss::FormFactorGauss(double width, double height)
";

%feature("docstring")  FormFactorGauss::clone "FormFactorGauss* FormFactorGauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorGauss::accept "void FormFactorGauss::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorGauss::getWidth "double FormFactorGauss::getWidth() const
";

%feature("docstring")  FormFactorGauss::getHeight "double FormFactorGauss::getHeight() const
";

%feature("docstring")  FormFactorGauss::getRadialExtension "double FormFactorGauss::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorGauss::evaluate_for_q "complex_t FormFactorGauss::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorHemiEllipsoid.xml
%feature("docstring") FormFactorHemiEllipsoid "

An hemi ellipsoid, obtained by truncating a full ellipsoid in the middle plane spanned by two principal axes.

C++ includes: FormFactorHemiEllipsoid.h
";

%feature("docstring")  FormFactorHemiEllipsoid::FormFactorHemiEllipsoid "FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(double radius_x, double radius_y, double height)

Parameters:
-----------

radius_x: 
half length of one horizontal main axes

radius_y: 
half length of the other horizontal main axes

height: 
of the hemi ellipsoid 
";

%feature("docstring")  FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid "virtual FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid()
";

%feature("docstring")  FormFactorHemiEllipsoid::clone "FormFactorHemiEllipsoid* FormFactorHemiEllipsoid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorHemiEllipsoid::accept "void FormFactorHemiEllipsoid::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorHemiEllipsoid::getHeight "double FormFactorHemiEllipsoid::getHeight() const
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusX "double FormFactorHemiEllipsoid::getRadiusX() const
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusY "double FormFactorHemiEllipsoid::getRadiusY() const
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadialExtension "double FormFactorHemiEllipsoid::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorHemiEllipsoid::evaluate_for_q "complex_t FormFactorHemiEllipsoid::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorIcosahedron.xml
%feature("docstring") FormFactorIcosahedron "

A regular icosahedron.

C++ includes: FormFactorIcosahedron.h
";

%feature("docstring")  FormFactorIcosahedron::FormFactorIcosahedron "FormFactorIcosahedron::FormFactorIcosahedron(double edge)
";

%feature("docstring")  FormFactorIcosahedron::clone "FormFactorIcosahedron* FormFactorIcosahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorIcosahedron::accept "void FormFactorIcosahedron::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorIcosahedron::getEdge "double FormFactorIcosahedron::getEdge() const
";


// File: classFormFactorLongBoxGauss.xml
%feature("docstring") FormFactorLongBoxGauss "

The formfactor for a long rectangular box.

C++ includes: FormFactorLongBoxGauss.h
";

%feature("docstring")  FormFactorLongBoxGauss::FormFactorLongBoxGauss "FormFactorLongBoxGauss::FormFactorLongBoxGauss(double length, double width, double height)

Box constructor.

Parameters:
-----------

length: 
of Box's base

width: 
of Box's base

height: 
of Box 
";

%feature("docstring")  FormFactorLongBoxGauss::clone "FormFactorLongBoxGauss* FormFactorLongBoxGauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongBoxGauss::accept "void FormFactorLongBoxGauss::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongBoxGauss::getLength "double FormFactorLongBoxGauss::getLength() const
";

%feature("docstring")  FormFactorLongBoxGauss::getHeight "double FormFactorLongBoxGauss::getHeight() const
";

%feature("docstring")  FormFactorLongBoxGauss::getWidth "double FormFactorLongBoxGauss::getWidth() const
";

%feature("docstring")  FormFactorLongBoxGauss::getRadialExtension "double FormFactorLongBoxGauss::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongBoxGauss::evaluate_for_q "complex_t FormFactorLongBoxGauss::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorLongBoxLorentz.xml
%feature("docstring") FormFactorLongBoxLorentz "

The formfactor for a long rectangular box.

C++ includes: FormFactorLongBoxLorentz.h
";

%feature("docstring")  FormFactorLongBoxLorentz::FormFactorLongBoxLorentz "FormFactorLongBoxLorentz::FormFactorLongBoxLorentz(double length, double width, double height)

Box constructor.

Parameters:
-----------

length: 
of Box's base

width: 
of Box's base

height: 
of Box 
";

%feature("docstring")  FormFactorLongBoxLorentz::clone "FormFactorLongBoxLorentz* FormFactorLongBoxLorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongBoxLorentz::accept "void FormFactorLongBoxLorentz::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongBoxLorentz::getLength "double FormFactorLongBoxLorentz::getLength() const
";

%feature("docstring")  FormFactorLongBoxLorentz::getHeight "double FormFactorLongBoxLorentz::getHeight() const
";

%feature("docstring")  FormFactorLongBoxLorentz::getWidth "double FormFactorLongBoxLorentz::getWidth() const
";

%feature("docstring")  FormFactorLongBoxLorentz::getRadialExtension "double FormFactorLongBoxLorentz::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongBoxLorentz::evaluate_for_q "complex_t FormFactorLongBoxLorentz::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorLongRipple1Gauss.xml
%feature("docstring") FormFactorLongRipple1Gauss "

The formfactor for a cosine ripple.

C++ includes: FormFactorLongRipple1Gauss.h
";

%feature("docstring")  FormFactorLongRipple1Gauss::FormFactorLongRipple1Gauss "FormFactorLongRipple1Gauss::FormFactorLongRipple1Gauss(double length, double width, double height)

Ripple1 constructor.

Parameters:
-----------

length: 
of Ripple1

width: 
of cosine cross section

height: 
of cosine cross section 
";

%feature("docstring")  FormFactorLongRipple1Gauss::clone "FormFactorLongRipple1Gauss* FormFactorLongRipple1Gauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple1Gauss::accept "void FormFactorLongRipple1Gauss::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple1Gauss::getHeight "double FormFactorLongRipple1Gauss::getHeight() const
";

%feature("docstring")  FormFactorLongRipple1Gauss::getWidth "double FormFactorLongRipple1Gauss::getWidth() const
";

%feature("docstring")  FormFactorLongRipple1Gauss::getLength "double FormFactorLongRipple1Gauss::getLength() const
";

%feature("docstring")  FormFactorLongRipple1Gauss::getRadialExtension "double FormFactorLongRipple1Gauss::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple1Gauss::evaluate_for_q "complex_t FormFactorLongRipple1Gauss::evaluate_for_q(const cvector_t q) const override final

Complex formfactor. 
";


// File: classFormFactorLongRipple1Lorentz.xml
%feature("docstring") FormFactorLongRipple1Lorentz "

The formfactor for a cosine ripple.

C++ includes: FormFactorLongRipple1Lorentz.h
";

%feature("docstring")  FormFactorLongRipple1Lorentz::FormFactorLongRipple1Lorentz "FormFactorLongRipple1Lorentz::FormFactorLongRipple1Lorentz(double length, double width, double height)

FormFactorLongRipple1Lorentz constructor.

Parameters:
-----------

length: 
of Ripple1

width: 
of cosine cross section

height: 
of cosine cross section 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::clone "FormFactorLongRipple1Lorentz* FormFactorLongRipple1Lorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::accept "void FormFactorLongRipple1Lorentz::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getRadialExtension "double FormFactorLongRipple1Lorentz::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getHeight "double FormFactorLongRipple1Lorentz::getHeight() const
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getWidth "double FormFactorLongRipple1Lorentz::getWidth() const
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getLength "double FormFactorLongRipple1Lorentz::getLength() const
";

%feature("docstring")  FormFactorLongRipple1Lorentz::evaluate_for_q "complex_t FormFactorLongRipple1Lorentz::evaluate_for_q(const cvector_t q) const override final

Complex formfactor. 
";


// File: classFormFactorLongRipple2Gauss.xml
%feature("docstring") FormFactorLongRipple2Gauss "

The formfactor for a triangular ripple.

C++ includes: FormFactorLongRipple2Gauss.h
";

%feature("docstring")  FormFactorLongRipple2Gauss::FormFactorLongRipple2Gauss "FormFactorLongRipple2Gauss::FormFactorLongRipple2Gauss(double length, double width, double height, double asymmetry)

FormFactorLongRipple2Gauss constructor.

Parameters:
-----------

length: 
of Ripple2

width: 
of triangular cross section

height: 
of triangular cross section

asymmetry: 
length of triangular cross section 
";

%feature("docstring")  FormFactorLongRipple2Gauss::clone "FormFactorLongRipple2Gauss* FormFactorLongRipple2Gauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple2Gauss::accept "void FormFactorLongRipple2Gauss::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple2Gauss::getHeight "double FormFactorLongRipple2Gauss::getHeight() const
";

%feature("docstring")  FormFactorLongRipple2Gauss::getWidth "double FormFactorLongRipple2Gauss::getWidth() const
";

%feature("docstring")  FormFactorLongRipple2Gauss::getLength "double FormFactorLongRipple2Gauss::getLength() const
";

%feature("docstring")  FormFactorLongRipple2Gauss::getAsymmetry "double FormFactorLongRipple2Gauss::getAsymmetry() const
";

%feature("docstring")  FormFactorLongRipple2Gauss::getRadialExtension "double FormFactorLongRipple2Gauss::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple2Gauss::evaluate_for_q "complex_t FormFactorLongRipple2Gauss::evaluate_for_q(const cvector_t q) const override final

Complex formfactor. 
";


// File: classFormFactorLongRipple2Lorentz.xml
%feature("docstring") FormFactorLongRipple2Lorentz "

The formfactor for a triangular ripple.

C++ includes: FormFactorLongRipple2Lorentz.h
";

%feature("docstring")  FormFactorLongRipple2Lorentz::FormFactorLongRipple2Lorentz "FormFactorLongRipple2Lorentz::FormFactorLongRipple2Lorentz(double length, double width, double height, double asymmetry)

Parameters:
-----------

length: 
of Ripple2

width: 
of triangular cross section

height: 
of triangular cross section

asymmetry: 
length of triangular cross section 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::clone "FormFactorLongRipple2Lorentz* FormFactorLongRipple2Lorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::accept "void FormFactorLongRipple2Lorentz::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getHeight "double FormFactorLongRipple2Lorentz::getHeight() const
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getWidth "double FormFactorLongRipple2Lorentz::getWidth() const
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getLength "double FormFactorLongRipple2Lorentz::getLength() const
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getAsymmetry "double FormFactorLongRipple2Lorentz::getAsymmetry() const
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getRadialExtension "double FormFactorLongRipple2Lorentz::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::evaluate_for_q "complex_t FormFactorLongRipple2Lorentz::evaluate_for_q(const cvector_t q) const override final

Complex formfactor. 
";


// File: classFormFactorLorentz.xml
%feature("docstring") FormFactorLorentz "

The formfactor of a lorentzian.

C++ includes: FormFactorLorentz.h
";

%feature("docstring")  FormFactorLorentz::FormFactorLorentz "FormFactorLorentz::FormFactorLorentz(double length)
";

%feature("docstring")  FormFactorLorentz::FormFactorLorentz "FormFactorLorentz::FormFactorLorentz(double width, double height)
";

%feature("docstring")  FormFactorLorentz::clone "FormFactorLorentz* FormFactorLorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLorentz::accept "void FormFactorLorentz::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLorentz::getWidth "double FormFactorLorentz::getWidth() const
";

%feature("docstring")  FormFactorLorentz::getHeight "double FormFactorLorentz::getHeight() const
";

%feature("docstring")  FormFactorLorentz::getRadialExtension "double FormFactorLorentz::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLorentz::evaluate_for_q "complex_t FormFactorLorentz::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorPolygonalPrism.xml
%feature("docstring") FormFactorPolygonalPrism "

A prism with a polygonal base, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolygonalPrism::FormFactorPolygonalPrism "FormFactorPolygonalPrism::FormFactorPolygonalPrism(const double height)
";

%feature("docstring")  FormFactorPolygonalPrism::evaluate_for_q "complex_t FormFactorPolygonalPrism::evaluate_for_q(const cvector_t q) const override final

Returns the form factor F(q) of this polyhedron, respecting the offset height/2. 
";

%feature("docstring")  FormFactorPolygonalPrism::getVolume "double FormFactorPolygonalPrism::getVolume() const override final

Returns the volume of this prism. 
";

%feature("docstring")  FormFactorPolygonalPrism::getHeight "double FormFactorPolygonalPrism::getHeight() const
";

%feature("docstring")  FormFactorPolygonalPrism::getRadialExtension "double FormFactorPolygonalPrism::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";


// File: classFormFactorPolygonalSurface.xml
%feature("docstring") FormFactorPolygonalSurface "

A polygonal surface, for testing form factor computations.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolygonalSurface::FormFactorPolygonalSurface "FormFactorPolygonalSurface::FormFactorPolygonalSurface()
";

%feature("docstring")  FormFactorPolygonalSurface::evaluate_for_q "complex_t FormFactorPolygonalSurface::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";

%feature("docstring")  FormFactorPolygonalSurface::getVolume "double FormFactorPolygonalSurface::getVolume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorPolygonalSurface::getRadialExtension "double FormFactorPolygonalSurface::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";


// File: classFormFactorPolyhedron.xml
%feature("docstring") FormFactorPolyhedron "

A polyhedron, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolyhedron::FormFactorPolyhedron "FormFactorPolyhedron::FormFactorPolyhedron()
";

%feature("docstring")  FormFactorPolyhedron::evaluate_for_q "complex_t FormFactorPolyhedron::evaluate_for_q(const cvector_t q) const override final

Returns the form factor F(q) of this polyhedron, respecting the offset z_origin. 
";

%feature("docstring")  FormFactorPolyhedron::evaluate_centered "complex_t FormFactorPolyhedron::evaluate_centered(const cvector_t q) const

Returns the form factor F(q) of this polyhedron, with origin at z=0. 
";

%feature("docstring")  FormFactorPolyhedron::getVolume "double FormFactorPolyhedron::getVolume() const override final

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorPolyhedron::getRadialExtension "double FormFactorPolyhedron::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorPolyhedron::assert_platonic "void FormFactorPolyhedron::assert_platonic() const

Assertions for Platonic solid. 
";


// File: classFormFactorPrism3.xml
%feature("docstring") FormFactorPrism3 "

A prism based on an equilateral triangle.

C++ includes: FormFactorPrism3.h
";

%feature("docstring")  FormFactorPrism3::FormFactorPrism3 "FormFactorPrism3::FormFactorPrism3(const double base_edge, const double height)
";

%feature("docstring")  FormFactorPrism3::clone "FormFactorPrism3* FormFactorPrism3::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPrism3::accept "void FormFactorPrism3::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorPrism3::getBaseEdge "double FormFactorPrism3::getBaseEdge() const
";


// File: classFormFactorPrism6.xml
%feature("docstring") FormFactorPrism6 "

A prism based on a regular hexagonal.

C++ includes: FormFactorPrism6.h
";

%feature("docstring")  FormFactorPrism6::FormFactorPrism6 "FormFactorPrism6::FormFactorPrism6(const double base_edge, const double height)
";

%feature("docstring")  FormFactorPrism6::clone "FormFactorPrism6* FormFactorPrism6::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPrism6::accept "void FormFactorPrism6::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorPrism6::getBaseEdge "double FormFactorPrism6::getBaseEdge() const
";


// File: classFormFactorPyramid.xml
%feature("docstring") FormFactorPyramid "

A frustum with a quadratic base.

C++ includes: FormFactorPyramid.h
";

%feature("docstring")  FormFactorPyramid::FormFactorPyramid "FormFactorPyramid::FormFactorPyramid(double base_edge, double height, double alpha)

Parameters:
-----------

base_edge: 
of one side of the square base

height: 
of the frustum

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorPyramid::clone "FormFactorPyramid* FormFactorPyramid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPyramid::accept "void FormFactorPyramid::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorPyramid::getHeight "double FormFactorPyramid::getHeight() const
";

%feature("docstring")  FormFactorPyramid::getBaseEdge "double FormFactorPyramid::getBaseEdge() const
";

%feature("docstring")  FormFactorPyramid::getAlpha "double FormFactorPyramid::getAlpha() const
";


// File: classFormFactorRipple1.xml
%feature("docstring") FormFactorRipple1 "

The formfactor for a cosine ripple.

C++ includes: FormFactorRipple1.h
";

%feature("docstring")  FormFactorRipple1::FormFactorRipple1 "FormFactorRipple1::FormFactorRipple1(double length, double width, double height)

Ripple1 constructor.

Parameters:
-----------

length: 
of Ripple1

width: 
of cosine cross section

height: 
of cosine cross section 
";

%feature("docstring")  FormFactorRipple1::clone "FormFactorRipple1* FormFactorRipple1::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple1::accept "void FormFactorRipple1::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorRipple1::getLength "double FormFactorRipple1::getLength() const
";

%feature("docstring")  FormFactorRipple1::getHeight "double FormFactorRipple1::getHeight() const
";

%feature("docstring")  FormFactorRipple1::getWidth "double FormFactorRipple1::getWidth() const
";

%feature("docstring")  FormFactorRipple1::getRadialExtension "double FormFactorRipple1::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorRipple1::evaluate_for_q "complex_t FormFactorRipple1::evaluate_for_q(const cvector_t q) const override final

Complex formfactor. 
";


// File: classFormFactorRipple2.xml
%feature("docstring") FormFactorRipple2 "

The formfactor for a triangular ripple.

C++ includes: FormFactorRipple2.h
";

%feature("docstring")  FormFactorRipple2::FormFactorRipple2 "FormFactorRipple2::FormFactorRipple2(double length, double width, double height, double asymmetry)

Ripple2 constructor.

Parameters:
-----------

length: 
of Ripple2

width: 
of triangular cross section

height: 
of triangular cross section

asymmetry: 
length of triangular cross section 
";

%feature("docstring")  FormFactorRipple2::clone "FormFactorRipple2* FormFactorRipple2::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple2::accept "void FormFactorRipple2::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorRipple2::getHeight "double FormFactorRipple2::getHeight() const
";

%feature("docstring")  FormFactorRipple2::getWidth "double FormFactorRipple2::getWidth() const
";

%feature("docstring")  FormFactorRipple2::getLength "double FormFactorRipple2::getLength() const
";

%feature("docstring")  FormFactorRipple2::getAsymmetry "double FormFactorRipple2::getAsymmetry() const
";

%feature("docstring")  FormFactorRipple2::getRadialExtension "double FormFactorRipple2::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorRipple2::evaluate_for_q "complex_t FormFactorRipple2::evaluate_for_q(const cvector_t q) const override final

Complex formfactor. 
";


// File: classFormFactorSphereGaussianRadius.xml
%feature("docstring") FormFactorSphereGaussianRadius "

A sphere with gaussian radius distribution.

C++ includes: FormFactorSphereGaussianRadius.h
";

%feature("docstring")  FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius "FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean, double sigma)
";

%feature("docstring")  FormFactorSphereGaussianRadius::clone "FormFactorSphereGaussianRadius* FormFactorSphereGaussianRadius::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorSphereGaussianRadius::accept "void FormFactorSphereGaussianRadius::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereGaussianRadius::getRadialExtension "double FormFactorSphereGaussianRadius::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereGaussianRadius::evaluate_for_q "complex_t FormFactorSphereGaussianRadius::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorSphereLogNormalRadius.xml
%feature("docstring") FormFactorSphereLogNormalRadius "

A sphere with log normal radius distribution.

C++ includes: FormFactorSphereLogNormalRadius.h
";

%feature("docstring")  FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius "FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(double mean, double scale_param, size_t n_samples)
";

%feature("docstring")  FormFactorSphereLogNormalRadius::clone "FormFactorSphereLogNormalRadius* FormFactorSphereLogNormalRadius::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::accept "void FormFactorSphereLogNormalRadius::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::getRadialExtension "double FormFactorSphereLogNormalRadius::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::evaluate_for_q "complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorSphereUniformRadius.xml
%feature("docstring") FormFactorSphereUniformRadius "

Integrated full sphere form factor over a uniform distribution of radii.

C++ includes: FormFactorSphereUniformRadius.h
";

%feature("docstring")  FormFactorSphereUniformRadius::FormFactorSphereUniformRadius "FormFactorSphereUniformRadius::FormFactorSphereUniformRadius(double mean, double full_width)
";

%feature("docstring")  FormFactorSphereUniformRadius::clone "FormFactorSphereUniformRadius* FormFactorSphereUniformRadius::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorSphereUniformRadius::accept "void FormFactorSphereUniformRadius::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereUniformRadius::getRadialExtension "double FormFactorSphereUniformRadius::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereUniformRadius::evaluate_for_q "complex_t FormFactorSphereUniformRadius::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorTetrahedron.xml
%feature("docstring") FormFactorTetrahedron "

A frustum with equilateral trigonal base.

C++ includes: FormFactorTetrahedron.h
";

%feature("docstring")  FormFactorTetrahedron::FormFactorTetrahedron "FormFactorTetrahedron::FormFactorTetrahedron(double base_edge, double height, double alpha)

Parameters:
-----------

base_edge: 
of a side of the base

height: 
of the frustum

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorTetrahedron::clone "FormFactorTetrahedron* FormFactorTetrahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTetrahedron::accept "void FormFactorTetrahedron::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTetrahedron::getBaseEdge "double FormFactorTetrahedron::getBaseEdge() const
";

%feature("docstring")  FormFactorTetrahedron::getHeight "double FormFactorTetrahedron::getHeight() const
";

%feature("docstring")  FormFactorTetrahedron::getAlpha "double FormFactorTetrahedron::getAlpha() const
";


// File: classFormFactorTriangle.xml
%feature("docstring") FormFactorTriangle "

A planar equilateral triangle, for testing form factor computations.

C++ includes: FormFactorTriangle.h
";

%feature("docstring")  FormFactorTriangle::FormFactorTriangle "FormFactorTriangle::FormFactorTriangle(const double base_edge)
";

%feature("docstring")  FormFactorTriangle::clone "FormFactorTriangle* FormFactorTriangle::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTriangle::accept "void FormFactorTriangle::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTriangle::getBaseEdge "double FormFactorTriangle::getBaseEdge() const
";


// File: classFormFactorTrivial.xml
%feature("docstring") FormFactorTrivial "

A dot, with trivial formfactor F(q)=1.

C++ includes: FormFactorTrivial.h
";

%feature("docstring")  FormFactorTrivial::FormFactorTrivial "FormFactorTrivial::FormFactorTrivial()
";

%feature("docstring")  FormFactorTrivial::clone "FormFactorTrivial* FormFactorTrivial::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTrivial::accept "void FormFactorTrivial::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTrivial::getRadialExtension "double FormFactorTrivial::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTrivial::evaluate_for_q "complex_t FormFactorTrivial::evaluate_for_q(const cvector_t) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorTruncatedCube.xml
%feature("docstring") FormFactorTruncatedCube "

A cube, with tetrahedral truncation of all edges.

C++ includes: FormFactorTruncatedCube.h
";

%feature("docstring")  FormFactorTruncatedCube::FormFactorTruncatedCube "FormFactorTruncatedCube::FormFactorTruncatedCube(double length, double removed_length)

Parameters:
-----------

length: 
of the full cube

removed_length: 
as removed from each edge of the cube 
";

%feature("docstring")  FormFactorTruncatedCube::clone "FormFactorTruncatedCube* FormFactorTruncatedCube::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedCube::accept "void FormFactorTruncatedCube::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedCube::getLength "double FormFactorTruncatedCube::getLength() const
";

%feature("docstring")  FormFactorTruncatedCube::getRemovedLength "double FormFactorTruncatedCube::getRemovedLength() const
";


// File: classFormFactorTruncatedSphere.xml
%feature("docstring") FormFactorTruncatedSphere "

A truncated Sphere.

C++ includes: FormFactorTruncatedSphere.h
";

%feature("docstring")  FormFactorTruncatedSphere::FormFactorTruncatedSphere "FormFactorTruncatedSphere::FormFactorTruncatedSphere(double radius, double height)
";

%feature("docstring")  FormFactorTruncatedSphere::clone "FormFactorTruncatedSphere* FormFactorTruncatedSphere::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedSphere::accept "void FormFactorTruncatedSphere::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedSphere::getHeight "double FormFactorTruncatedSphere::getHeight() const
";

%feature("docstring")  FormFactorTruncatedSphere::getRadius "double FormFactorTruncatedSphere::getRadius() const
";

%feature("docstring")  FormFactorTruncatedSphere::getRadialExtension "double FormFactorTruncatedSphere::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSphere::evaluate_for_q "complex_t FormFactorTruncatedSphere::evaluate_for_q(const cvector_t q) const override final

Complex formfactor. 
";


// File: classFormFactorTruncatedSpheroid.xml
%feature("docstring") FormFactorTruncatedSpheroid "

A truncated spheroid. An ellipsoid with two equal axis, truncated by a plane perpendicular to the third axis.

C++ includes: FormFactorTruncatedSpheroid.h
";

%feature("docstring")  FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid "FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(double radius, double height, double height_flattening)
";

%feature("docstring")  FormFactorTruncatedSpheroid::clone "FormFactorTruncatedSpheroid* FormFactorTruncatedSpheroid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedSpheroid::accept "void FormFactorTruncatedSpheroid::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedSpheroid::getRadius "double FormFactorTruncatedSpheroid::getRadius() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeight "double FormFactorTruncatedSpheroid::getHeight() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeightFlattening "double FormFactorTruncatedSpheroid::getHeightFlattening() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getRadialExtension "double FormFactorTruncatedSpheroid::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSpheroid::evaluate_for_q "complex_t FormFactorTruncatedSpheroid::evaluate_for_q(const cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorWeighted.xml
%feature("docstring") FormFactorWeighted "

Coherent sum of different scalar  IFormFactor's with different weights.

Used by  ParticleComposition and  ParticleCoreShell. If same particles are at different positions, then consider FormFactorDecoratorMultiPositionFactor (restore from commit 0500a26de76).

C++ includes: FormFactorWeighted.h
";

%feature("docstring")  FormFactorWeighted::FormFactorWeighted "FormFactorWeighted::FormFactorWeighted()
";

%feature("docstring")  FormFactorWeighted::~FormFactorWeighted "FormFactorWeighted::~FormFactorWeighted() override final
";

%feature("docstring")  FormFactorWeighted::clone "FormFactorWeighted * FormFactorWeighted::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorWeighted::accept "void FormFactorWeighted::accept(ISampleVisitor *visitor) const override final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorWeighted::getRadialExtension "double FormFactorWeighted::getRadialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorWeighted::addFormFactor "void FormFactorWeighted::addFormFactor(const IFormFactor &form_factor, double weight=1.0)
";

%feature("docstring")  FormFactorWeighted::setAmbientMaterial "void FormFactorWeighted::setAmbientMaterial(const IMaterial &material) override final

Passes the refractive index of the ambient material in which this particle is embedded. 
";

%feature("docstring")  FormFactorWeighted::evaluate "complex_t FormFactorWeighted::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorWeighted::evaluatePol "Eigen::Matrix2cd FormFactorWeighted::evaluatePol(const WavevectorInfo &wavevectors) const override final

Calculates and returns a polarized form factor calculation in DWBA. 
";


// File: classFormFactorWrapper.xml
%feature("docstring") FormFactorWrapper "

Information about particle form factor and abundance.

C++ includes: FormFactorWrapper.h
";

%feature("docstring")  FormFactorWrapper::FormFactorWrapper "FormFactorWrapper::FormFactorWrapper(IFormFactor *ff, double abundance)
";

%feature("docstring")  FormFactorWrapper::~FormFactorWrapper "FormFactorWrapper::~FormFactorWrapper()
";

%feature("docstring")  FormFactorWrapper::clone "FormFactorWrapper * FormFactorWrapper::clone() const
";


// File: classFTDecayFunction1DCauchy.xml
%feature("docstring") FTDecayFunction1DCauchy "

One-dimensional Cauchy decay function in reciprocal space; corresponds to exp(-|x|/omega) in real space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DCauchy::FTDecayFunction1DCauchy "FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double omega)
";

%feature("docstring")  FTDecayFunction1DCauchy::clone "virtual FTDecayFunction1DCauchy* FTDecayFunction1DCauchy::clone() const
";

%feature("docstring")  FTDecayFunction1DCauchy::evaluate "double FTDecayFunction1DCauchy::evaluate(double q) const final
";


// File: classFTDecayFunction1DGauss.xml
%feature("docstring") FTDecayFunction1DGauss "

One-dimensional Gauss decay function in reciprocal space; corresponds to exp[-x^2/(2*omega^2)] in real space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DGauss::FTDecayFunction1DGauss "FTDecayFunction1DGauss::FTDecayFunction1DGauss(double omega)
";

%feature("docstring")  FTDecayFunction1DGauss::clone "virtual FTDecayFunction1DGauss* FTDecayFunction1DGauss::clone() const
";

%feature("docstring")  FTDecayFunction1DGauss::evaluate "double FTDecayFunction1DGauss::evaluate(double q) const final
";


// File: classFTDecayFunction1DTriangle.xml
%feature("docstring") FTDecayFunction1DTriangle "

One-dimensional triangle decay function in reciprocal space; corresponds to 1-|x|/omega if |x|<omega (and 0 otherwise) in real space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DTriangle::FTDecayFunction1DTriangle "FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double omega)
";

%feature("docstring")  FTDecayFunction1DTriangle::clone "virtual FTDecayFunction1DTriangle* FTDecayFunction1DTriangle::clone() const
";

%feature("docstring")  FTDecayFunction1DTriangle::evaluate "double FTDecayFunction1DTriangle::evaluate(double q) const final
";


// File: classFTDecayFunction1DVoigt.xml
%feature("docstring") FTDecayFunction1DVoigt "

One-dimensional pseudo-Voigt decay function in reciprocal space; corresponds to eta*Gauss + (1-eta)*Cauchy.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DVoigt::FTDecayFunction1DVoigt "FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double omega, double eta)
";

%feature("docstring")  FTDecayFunction1DVoigt::clone "virtual FTDecayFunction1DVoigt* FTDecayFunction1DVoigt::clone() const
";

%feature("docstring")  FTDecayFunction1DVoigt::evaluate "double FTDecayFunction1DVoigt::evaluate(double q) const final
";

%feature("docstring")  FTDecayFunction1DVoigt::getEta "double FTDecayFunction1DVoigt::getEta() const
";


// File: classFTDecayFunction2DCauchy.xml
%feature("docstring") FTDecayFunction2DCauchy "

Two-dimensional Cauchy decay function in reciprocal space; corresponds to exp(-r) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DCauchy::FTDecayFunction2DCauchy "FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDecayFunction2DCauchy::clone "virtual FTDecayFunction2DCauchy* FTDecayFunction2DCauchy::clone() const
";

%feature("docstring")  FTDecayFunction2DCauchy::evaluate "double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DGauss.xml
%feature("docstring") FTDecayFunction2DGauss "

Two-dimensional Gauss decay function in reciprocal space; corresponds to exp(-r^2/2) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DGauss::FTDecayFunction2DGauss "FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDecayFunction2DGauss::clone "virtual FTDecayFunction2DGauss* FTDecayFunction2DGauss::clone() const
";

%feature("docstring")  FTDecayFunction2DGauss::evaluate "double FTDecayFunction2DGauss::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DVoigt.xml
%feature("docstring") FTDecayFunction2DVoigt "

Two-dimensional pseudo-Voigt decay function in reciprocal space; corresponds to eta*Gauss + (1-eta)*Cauchy.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DVoigt::FTDecayFunction2DVoigt "FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y, double eta, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDecayFunction2DVoigt::clone "virtual FTDecayFunction2DVoigt* FTDecayFunction2DVoigt::clone() const
";

%feature("docstring")  FTDecayFunction2DVoigt::evaluate "double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  FTDecayFunction2DVoigt::getEta "virtual double FTDecayFunction2DVoigt::getEta() const
";


// File: classFTDistribution1DCauchy.xml
%feature("docstring") FTDistribution1DCauchy "

Exponential  IFTDistribution1D exp(-|omega*x|); its Fourier transform evaluate(q) is a Cauchy-Lorentzian starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DCauchy::FTDistribution1DCauchy "FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
";

%feature("docstring")  FTDistribution1DCauchy::clone "FTDistribution1DCauchy* FTDistribution1DCauchy::clone() const final
";

%feature("docstring")  FTDistribution1DCauchy::evaluate "double FTDistribution1DCauchy::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";


// File: classFTDistribution1DCosine.xml
%feature("docstring") FTDistribution1DCosine "

IFTDistribution1D consisting of one cosine wave [1+cos(pi*x/omega) if |x|<omega, and 0 otherwise]; its Fourier transform evaluate(q) starts at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DCosine::FTDistribution1DCosine "FTDistribution1DCosine::FTDistribution1DCosine(double omega)
";

%feature("docstring")  FTDistribution1DCosine::clone "FTDistribution1DCosine* FTDistribution1DCosine::clone() const final
";

%feature("docstring")  FTDistribution1DCosine::evaluate "double FTDistribution1DCosine::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";


// File: classFTDistribution1DGate.xml
%feature("docstring") FTDistribution1DGate "

Square gate  IFTDistribution1D; its Fourier transform evaluate(q) is a sinc function starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DGate::FTDistribution1DGate "FTDistribution1DGate::FTDistribution1DGate(double omega)
";

%feature("docstring")  FTDistribution1DGate::clone "FTDistribution1DGate* FTDistribution1DGate::clone() const final
";

%feature("docstring")  FTDistribution1DGate::evaluate "double FTDistribution1DGate::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";


// File: classFTDistribution1DGauss.xml
%feature("docstring") FTDistribution1DGauss "

Gaussian  IFTDistribution1D; its Fourier transform evaluate(q) is a Gaussian starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DGauss::FTDistribution1DGauss "FTDistribution1DGauss::FTDistribution1DGauss(double omega)
";

%feature("docstring")  FTDistribution1DGauss::clone "FTDistribution1DGauss* FTDistribution1DGauss::clone() const final
";

%feature("docstring")  FTDistribution1DGauss::evaluate "double FTDistribution1DGauss::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";


// File: classFTDistribution1DTriangle.xml
%feature("docstring") FTDistribution1DTriangle "

Triangle  IFTDistribution1D [1-|x|/omega if |x|<omega, and 0 otherwise]; its Fourier transform evaluate(q) is a squared sinc function starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DTriangle::FTDistribution1DTriangle "FTDistribution1DTriangle::FTDistribution1DTriangle(double omega)
";

%feature("docstring")  FTDistribution1DTriangle::~FTDistribution1DTriangle "virtual FTDistribution1DTriangle::~FTDistribution1DTriangle()
";

%feature("docstring")  FTDistribution1DTriangle::clone "FTDistribution1DTriangle* FTDistribution1DTriangle::clone() const final
";

%feature("docstring")  FTDistribution1DTriangle::evaluate "double FTDistribution1DTriangle::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";


// File: classFTDistribution1DVoigt.xml
%feature("docstring") FTDistribution1DVoigt "

IFTDistribution1D that provides a Fourier transform evaluate(q) in form of a pseudo-Voigt decay function eta*Gauss + (1-eta)*Cauchy, with both components starting at 1 for q=0.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DVoigt::FTDistribution1DVoigt "FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
";

%feature("docstring")  FTDistribution1DVoigt::clone "FTDistribution1DVoigt* FTDistribution1DVoigt::clone() const final
";

%feature("docstring")  FTDistribution1DVoigt::evaluate "double FTDistribution1DVoigt::evaluate(double q) const final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DVoigt::getEta "double FTDistribution1DVoigt::getEta() const
";


// File: classFTDistribution2DCauchy.xml
%feature("docstring") FTDistribution2DCauchy "

Two-dimensional Cauchy distribution in Fourier space; corresponds to a normalized exp(-r) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DCauchy::FTDistribution2DCauchy "FTDistribution2DCauchy::FTDistribution2DCauchy(double coherence_length_x, double coherence_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDistribution2DCauchy::clone "FTDistribution2DCauchy* FTDistribution2DCauchy::clone() const final
";

%feature("docstring")  FTDistribution2DCauchy::evaluate "double FTDistribution2DCauchy::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DCone.xml
%feature("docstring") FTDistribution2DCone "

Two-dimensional cone distribution in Fourier space; corresponds to 1-r if r<1 (and 0 otherwise) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DCone::FTDistribution2DCone "FTDistribution2DCone::FTDistribution2DCone(double coherence_length_x, double coherence_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDistribution2DCone::clone "FTDistribution2DCone* FTDistribution2DCone::clone() const final
";

%feature("docstring")  FTDistribution2DCone::evaluate "double FTDistribution2DCone::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DGate.xml
%feature("docstring") FTDistribution2DGate "

Two-dimensional gate distribution in Fourier space; corresponds to normalized constant if r<1 (and 0 otherwise) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DGate::FTDistribution2DGate "FTDistribution2DGate::FTDistribution2DGate(double coherence_length_x, double coherence_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDistribution2DGate::clone "FTDistribution2DGate* FTDistribution2DGate::clone() const final
";

%feature("docstring")  FTDistribution2DGate::evaluate "double FTDistribution2DGate::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DGauss.xml
%feature("docstring") FTDistribution2DGauss "

Two-dimensional Gauss distribution in Fourier space; corresponds to normalized exp(-r^2/2) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DGauss::FTDistribution2DGauss "FTDistribution2DGauss::FTDistribution2DGauss(double coherence_length_x, double coherence_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDistribution2DGauss::clone "FTDistribution2DGauss* FTDistribution2DGauss::clone() const final
";

%feature("docstring")  FTDistribution2DGauss::evaluate "double FTDistribution2DGauss::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DVoigt.xml
%feature("docstring") FTDistribution2DVoigt "

Two-dimensional Voigt distribution in Fourier space; corresponds to eta*Gauss + (1-eta)*Cauchy

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DVoigt::FTDistribution2DVoigt "FTDistribution2DVoigt::FTDistribution2DVoigt(double coherence_length_x, double coherence_length_y, double eta, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  FTDistribution2DVoigt::clone "FTDistribution2DVoigt* FTDistribution2DVoigt::clone() const final
";

%feature("docstring")  FTDistribution2DVoigt::evaluate "double FTDistribution2DVoigt::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DVoigt::getEta "double FTDistribution2DVoigt::getEta() const
";


// File: classGISASSimulation.xml
%feature("docstring") GISASSimulation "

Main class to run a Grazing-Incidence Small-Angle Scattering simulation.

C++ includes: GISASSimulation.h
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation()
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation(const MultiLayer &p_sample)
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation(const std::shared_ptr< IMultiLayerBuilder > p_sample_builder)
";

%feature("docstring")  GISASSimulation::~GISASSimulation "GISASSimulation::~GISASSimulation() final
";

%feature("docstring")  GISASSimulation::clone "GISASSimulation* GISASSimulation::clone() const
";

%feature("docstring")  GISASSimulation::prepareSimulation "void GISASSimulation::prepareSimulation() final

Put into a clean state for running a simulation. 
";

%feature("docstring")  GISASSimulation::numberOfSimulationElements "int GISASSimulation::numberOfSimulationElements() const final

Gets the number of elements this simulation needs to calculate. 
";

%feature("docstring")  GISASSimulation::getDetectorIntensity "OutputData< double > * GISASSimulation::getDetectorIntensity(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns clone of the detector intensity map with detector resolution applied. 
";

%feature("docstring")  GISASSimulation::getIntensityData "Histogram2D * GISASSimulation::getIntensityData(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns histogram representing intensity map in requested axes units. 
";

%feature("docstring")  GISASSimulation::setBeamParameters "void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets beam parameters from here (forwarded to  Instrument) 
";

%feature("docstring")  GISASSimulation::setDetector "void GISASSimulation::setDetector(const IDetector2D &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  GISASSimulation::setDetectorParameters "void GISASSimulation::setDetectorParameters(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

Sets spherical detector parameters using angle ranges

Parameters:
-----------

n_phi: 
number of phi-axis bins

phi_min: 
low edge of first phi-bin

phi_max: 
upper edge of last phi-bin

n_alpha: 
number of alpha-axis bins

alpha_min: 
low edge of first alpha-bin

alpha_max: 
upper edge of last alpha-bin 
";

%feature("docstring")  GISASSimulation::removeMasks "void GISASSimulation::removeMasks()

removes all masks from the detector 
";

%feature("docstring")  GISASSimulation::addMask "void GISASSimulation::addMask(const Geometry::IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask (Rectangle, Polygon, Line, Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  GISASSimulation::maskAll "void GISASSimulation::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  GISASSimulation::addParametersToExternalPool "std::string GISASSimulation::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const final

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  GISASSimulation::setRegionOfInterest "void GISASSimulation::setRegionOfInterest(double xlow, double ylow, double xup, double yup)

Sets rectangular region of interest with lower left and upper right corners defined. 
";

%feature("docstring")  GISASSimulation::resetRegionOfInterest "void GISASSimulation::resetRegionOfInterest()

Resets region of interest making whole detector plane available for the simulation. 
";


// File: classHexParaCrystalBuilder.xml
%feature("docstring") HexParaCrystalBuilder "

Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4)

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  HexParaCrystalBuilder::HexParaCrystalBuilder "HexParaCrystalBuilder::HexParaCrystalBuilder()
";

%feature("docstring")  HexParaCrystalBuilder::buildSample "MultiLayer * HexParaCrystalBuilder::buildSample() const
";


// File: classHistogram1D.xml
%feature("docstring") Histogram1D "";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(int nbinsx, double xlow, double xup)

Constructor for fix bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins

xlow: 
low edge of the first bin

xup: 
upper edge of the last bin 
";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(int nbinsx, const std::vector< double > &xbins)

Constructor for variable bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins

xbins: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin. 
";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(const IAxis &axis)

Constructor for 1D histogram with custom axis. 
";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(const OutputData< double > &data)

Constructor for 1D histograms from basic  OutputData object. 
";

%feature("docstring")  Histogram1D::clone "Histogram1D * Histogram1D::clone() const

Returns clone of other histogram. 
";

%feature("docstring")  Histogram1D::getRank "size_t Histogram1D::getRank() const

Returns the number of histogram dimensions. 
";

%feature("docstring")  Histogram1D::fill "int Histogram1D::fill(double x, double weight=1.0)

Increment bin with abscissa x with a weight. 
";

%feature("docstring")  Histogram1D::getBinCenters "std::vector< double > Histogram1D::getBinCenters() const

returns vector of histogram bin centers 
";

%feature("docstring")  Histogram1D::getBinValues "std::vector< double > Histogram1D::getBinValues() const

returns vector of bin content (the value accumulated by bins) 
";

%feature("docstring")  Histogram1D::getBinErrors "std::vector< double > Histogram1D::getBinErrors() const

returns vector of bin errors 
";

%feature("docstring")  Histogram1D::crop "Histogram1D * Histogram1D::crop(double xmin, double xmax)

Create new histogram by applying crop on axis. 
";


// File: classHistogram2D.xml
%feature("docstring") Histogram2D "

Two dimensional histogram.

C++ includes: Histogram2D.h
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(int nbinsx, double xlow, double xup, int nbinsy, double ylow, double yup)

Constructor for fix bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins on X-axis

xlow: 
low edge of the first bin of X-axis

xup: 
upper edge of the last bin of X-axis

nbinsy: 
number of bins on Y axis

ylow: 
low edge of the first bin of Y-axis

yup: 
upper edge of the last bin of Y-axis 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(int nbinsx, const std::vector< double > &xbins, int nbinsy, const std::vector< double > &ybins)

Constructor for variable bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins on X-axis

xbins: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin.

nbinsy: 
number of bins on Y-axis

ybins: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin. 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(const IAxis &axis_x, const IAxis &axis_y)

Constructor for 2D histogram with custom axes. 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(const OutputData< double > &data)

Constructor for 2D histograms from basic  OutputData object. 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(const std::vector< std::vector< double >> &data)

Constructor for 2D histograms from numpy array (thanks to swig) 
";

%feature("docstring")  Histogram2D::clone "Histogram2D * Histogram2D::clone() const

Returns clone of other histogram. 
";

%feature("docstring")  Histogram2D::getRank "size_t Histogram2D::getRank() const

Returns the number of histogram dimensions. 
";

%feature("docstring")  Histogram2D::fill "int Histogram2D::fill(double x, double y, double weight=1.0)

Increment bin with abscissa x and ordinate y with a weight. 
";

%feature("docstring")  Histogram2D::projectionX "Histogram1D * Histogram2D::projectionX()

Project a 2D histogram into 1D histogram along X. The projection is made from all bins along y-axis. 
";

%feature("docstring")  Histogram2D::projectionX "Histogram1D * Histogram2D::projectionX(double yvalue)

Project a 2D histogram into 1D histogram along X. The projection is made from the y-bin closest to given ordinate yvalue.

Parameters:
-----------

yvalue: 
the value on y-axis at which projection is taken 
";

%feature("docstring")  Histogram2D::projectionX "Histogram1D * Histogram2D::projectionX(double ylow, double yup)

Project a 2D histogram into 1D histogram along X. The projection is made from all y-bins corresponding to ordinate between ylow and yup.

Parameters:
-----------

ylow: 
lower edje on y-axis

yup: 
upper edje on y-axis 
";

%feature("docstring")  Histogram2D::projectionY "Histogram1D * Histogram2D::projectionY()

Project a 2D histogram into 1D histogram along Y. The projection is made from all bins along x-axis. 
";

%feature("docstring")  Histogram2D::projectionY "Histogram1D * Histogram2D::projectionY(double xvalue)

Project a 2D histogram into 1D histogram along Y. The projection is made from the x-bin closest to given abscissa xvalue.

Parameters:
-----------

xvalue: 
the value on x-axis at which projection is taken 
";

%feature("docstring")  Histogram2D::projectionY "Histogram1D * Histogram2D::projectionY(double xlow, double xup)

Project a 2D histogram into 1D histogram along Y. The projection is made from all x-bins corresponding to abscissa between xlow and xup.

Parameters:
-----------

xlow: 
lower edje on x-axis

xup: 
upper edje on x-axis 
";

%feature("docstring")  Histogram2D::crop "Histogram2D * Histogram2D::crop(double xmin, double ymin, double xmax, double ymax)

Create new histogram by applying rectangular clip. 
";

%feature("docstring")  Histogram2D::setContent "void Histogram2D::setContent(const std::vector< std::vector< double >> &data)

Sets the values in histograms channels from numpy array,. 
";

%feature("docstring")  Histogram2D::addContent "void Histogram2D::addContent(const std::vector< std::vector< double >> &data)

Add to values in histograms channels from numpy array,. 
";


// File: classHomogeneousMagneticMaterial.xml
%feature("docstring") HomogeneousMagneticMaterial "

A homogeneous material with magnetization.

C++ includes: HomogeneousMagneticMaterial.h
";

%feature("docstring")  HomogeneousMagneticMaterial::HomogeneousMagneticMaterial "HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(const std::string &name, const complex_t refractive_index, const kvector_t magnetic_field)

Constructs a material with  name,  refractive_index and  magnetic_field
";

%feature("docstring")  HomogeneousMagneticMaterial::HomogeneousMagneticMaterial "HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(const std::string &name, double refractive_index_delta, double refractive_index_beta, const kvector_t magnetic_field)

Constructs a material with  name, refractive_index parameters and  magnetic_field
";

%feature("docstring")  HomogeneousMagneticMaterial::clone "HomogeneousMagneticMaterial * HomogeneousMagneticMaterial::clone() const

Clone. 
";

%feature("docstring")  HomogeneousMagneticMaterial::getMagneticField "kvector_t HomogeneousMagneticMaterial::getMagneticField() const

Get the magnetic field (in Tesla) 
";

%feature("docstring")  HomogeneousMagneticMaterial::setMagneticField "void HomogeneousMagneticMaterial::setMagneticField(const kvector_t magnetic_field)

Set the magnetic field (in Tesla) 
";

%feature("docstring")  HomogeneousMagneticMaterial::isScalarMaterial "virtual bool HomogeneousMagneticMaterial::isScalarMaterial() const

Indicates that the material is not scalar. This means that different polarization states will be diffracted differently 
";

%feature("docstring")  HomogeneousMagneticMaterial::getScatteringMatrix "Eigen::Matrix2cd HomogeneousMagneticMaterial::getScatteringMatrix(double k_mag2) const

Get the scattering matrix (~potential V) from the material. This matrix appears in the full three-dimensional Schroedinger equation. 
";

%feature("docstring")  HomogeneousMagneticMaterial::createTransformedMaterial "const IMaterial * HomogeneousMagneticMaterial::createTransformedMaterial(const Transform3D &transform) const

Create a new material that is transformed with respect to this one. 
";


// File: classHomogeneousMaterial.xml
%feature("docstring") HomogeneousMaterial "

An homogeneous material with a refractive index.

C++ includes: HomogeneousMaterial.h
";

%feature("docstring")  HomogeneousMaterial::HomogeneousMaterial "HomogeneousMaterial::HomogeneousMaterial(const std::string &name, const complex_t refractive_index)

Constructs a material with  name and  refractive_index. 
";

%feature("docstring")  HomogeneousMaterial::HomogeneousMaterial "HomogeneousMaterial::HomogeneousMaterial(const std::string &name, double refractive_index_delta, double refractive_index_beta)

Constructs a material with  name and refractive_index parameters delta and beta (n = 1 - delta + i*beta). 
";

%feature("docstring")  HomogeneousMaterial::~HomogeneousMaterial "virtual HomogeneousMaterial::~HomogeneousMaterial()
";

%feature("docstring")  HomogeneousMaterial::clone "virtual HomogeneousMaterial* HomogeneousMaterial::clone() const
";

%feature("docstring")  HomogeneousMaterial::getRefractiveIndex "virtual complex_t HomogeneousMaterial::getRefractiveIndex() const
";

%feature("docstring")  HomogeneousMaterial::setRefractiveIndex "void HomogeneousMaterial::setRefractiveIndex(const complex_t refractive_index)
";

%feature("docstring")  HomogeneousMaterial::getScatteringMatrix "virtual Eigen::Matrix2cd HomogeneousMaterial::getScatteringMatrix(double) const

Get the scattering matrix (~potential V) from the material. This matrix appears in the full three-dimensional Schroedinger equation. 
";

%feature("docstring")  HomogeneousMaterial::createTransformedMaterial "virtual const IMaterial* HomogeneousMaterial::createTransformedMaterial(const Transform3D &) const

Create a new material that is transformed with respect to this one. 
";


// File: classGeometry_1_1HorizontalLine.xml
%feature("docstring") Geometry::HorizontalLine "

An infinite horizontal line.

C++ includes: Line.h
";

%feature("docstring")  Geometry::HorizontalLine::HorizontalLine "Geometry::HorizontalLine::HorizontalLine(double y)

Parameters:
-----------

y: 
The value at which it crosses y-axes 
";

%feature("docstring")  Geometry::HorizontalLine::clone "HorizontalLine* Geometry::HorizontalLine::clone() const
";

%feature("docstring")  Geometry::HorizontalLine::contains "bool Geometry::HorizontalLine::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::HorizontalLine::contains "bool Geometry::HorizontalLine::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  Geometry::HorizontalLine::getYpos "double Geometry::HorizontalLine::getYpos() const
";


// File: classIAbstractParticle.xml
%feature("docstring") IAbstractParticle "

Interface for a generic particle.

Inherited by  IParticle and  ParticleDistribution.

C++ includes: IAbstractParticle.h
";

%feature("docstring")  IAbstractParticle::IAbstractParticle "IAbstractParticle::IAbstractParticle()
";

%feature("docstring")  IAbstractParticle::~IAbstractParticle "virtual IAbstractParticle::~IAbstractParticle()
";

%feature("docstring")  IAbstractParticle::clone "virtual IAbstractParticle* IAbstractParticle::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IAbstractParticle::cloneInvertB "virtual IAbstractParticle* IAbstractParticle::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IAbstractParticle::accept "virtual void IAbstractParticle::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IAbstractParticle::setAmbientMaterial "virtual void IAbstractParticle::setAmbientMaterial(const IMaterial &)=0

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  IAbstractParticle::getAbundance "double IAbstractParticle::getAbundance() const
";

%feature("docstring")  IAbstractParticle::setAbundance "void IAbstractParticle::setAbundance(double abundance)
";

%feature("docstring")  IAbstractParticle::getAmbientMaterial "virtual const IMaterial* IAbstractParticle::getAmbientMaterial() const =0

Returns nullptr, unless overwritten to return a specific material. 
";


// File: classIAxis.xml
%feature("docstring") IAxis "

Interface for one-dimensional axes.

C++ includes: IAxis.h
";

%feature("docstring")  IAxis::IAxis "IAxis::IAxis(const std::string &name)

constructors 
";

%feature("docstring")  IAxis::clone "virtual IAxis* IAxis::clone() const =0

clone function 
";

%feature("docstring")  IAxis::createDoubleBinSize "IAxis * IAxis::createDoubleBinSize() const

Creates a new axis with half the number of bins. 
";

%feature("docstring")  IAxis::~IAxis "virtual IAxis::~IAxis()

destructor 
";

%feature("docstring")  IAxis::size "virtual size_t IAxis::size() const =0

retrieve the number of bins 
";

%feature("docstring")  IAxis::getName "std::string IAxis::getName() const

retrieve the label of the axis 
";

%feature("docstring")  IAxis::setName "void IAxis::setName(std::string name)

Sets the axis label. 
";

%feature("docstring")  IAxis::getBin "virtual Bin1D IAxis::getBin(size_t index) const =0

retrieve a 1d bin for the given index 
";

%feature("docstring")  IAxis::getMin "virtual double IAxis::getMin() const =0

Returns value of first point of axis. 
";

%feature("docstring")  IAxis::getMax "virtual double IAxis::getMax() const =0

Returns value of last point of axis. 
";

%feature("docstring")  IAxis::getBinCenter "virtual double IAxis::getBinCenter(size_t index) const =0
";

%feature("docstring")  IAxis::findClosestIndex "virtual size_t IAxis::findClosestIndex(double value) const =0

find bin index which is best match for given value 
";

%feature("docstring")  IAxis::findIndex "size_t IAxis::findIndex(double value) const

find index of bin that contains the given value returns  size() when value is not found 
";

%feature("docstring")  IAxis::getBinCenters "std::vector< double > IAxis::getBinCenters() const
";

%feature("docstring")  IAxis::getBinBoundaries "std::vector< double > IAxis::getBinBoundaries() const
";

%feature("docstring")  IAxis::createClippedAxis "IAxis * IAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";

%feature("docstring")  IAxis::contains "bool IAxis::contains(double value) const

Returns true if axis contains given point. 
";


// File: classIChiSquaredModule.xml
%feature("docstring") IChiSquaredModule "

Interface for  ChiSquaredModule for chi2 calculations.

Until BornAgain-1.1, there was another child, ChiSquaredFrequency.

C++ includes: IChiSquaredModule.h
";

%feature("docstring")  IChiSquaredModule::IChiSquaredModule "IChiSquaredModule::IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::~IChiSquaredModule "IChiSquaredModule::~IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::clone "virtual IChiSquaredModule* IChiSquaredModule::clone() const =0

clone method 
";

%feature("docstring")  IChiSquaredModule::getSquaredFunction "const ISquaredFunction* IChiSquaredModule::getSquaredFunction() const

Returns squared function. 
";

%feature("docstring")  IChiSquaredModule::setChiSquaredFunction "void IChiSquaredModule::setChiSquaredFunction(ISquaredFunction *squared_function)

Sets squared function // TODO: merge these two functions (SWIG warning 509) 
";

%feature("docstring")  IChiSquaredModule::setChiSquaredFunction "void IChiSquaredModule::setChiSquaredFunction(const ISquaredFunction &squared_function)
";

%feature("docstring")  IChiSquaredModule::getIntensityNormalizer "virtual const IIntensityNormalizer* IChiSquaredModule::getIntensityNormalizer() const

Returns data normalizer. 
";

%feature("docstring")  IChiSquaredModule::getIntensityNormalizer "virtual IIntensityNormalizer* IChiSquaredModule::getIntensityNormalizer()

Returns data normalizer, non-const version needed to set internals. 
";

%feature("docstring")  IChiSquaredModule::setIntensityNormalizer "void IChiSquaredModule::setIntensityNormalizer(const IIntensityNormalizer &data_normalizer)

Sets data normalizer. 
";

%feature("docstring")  IChiSquaredModule::getIntensityFunction "virtual const IIntensityFunction* IChiSquaredModule::getIntensityFunction() const

Returns data rescaler. 
";

%feature("docstring")  IChiSquaredModule::setIntensityFunction "void IChiSquaredModule::setIntensityFunction(const IIntensityFunction &intensity_function)

Sets data rescaler. 
";

%feature("docstring")  IChiSquaredModule::processFitElements "virtual void IChiSquaredModule::processFitElements(std::vector< FitElement >::iterator, std::vector< FitElement >::iterator)
";


// File: classICloneable.xml
%feature("docstring") ICloneable "

Mix-in for objects that must not be copied, except by cloning.

The base class  INoncopyable disables the copy constructor and the operator= in all its child classes. Child classes of  ICloneable should provide clone().

C++ includes: ICloneable.h
";

%feature("docstring")  ICloneable::clone "virtual ICloneable* ICloneable::clone() const =0
";

%feature("docstring")  ICloneable::transferToCPP "virtual void ICloneable::transferToCPP()

Used for Python overriding of clone. 
";


// File: classIClusteredParticles.xml
%feature("docstring") IClusteredParticles "

An ordered assembly of particles. Currently, the only child class is  Crystal.

C++ includes: IClusteredParticles.h
";

%feature("docstring")  IClusteredParticles::IClusteredParticles "IClusteredParticles::IClusteredParticles()
";

%feature("docstring")  IClusteredParticles::clone "virtual IClusteredParticles* IClusteredParticles::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IClusteredParticles::cloneInvertB "virtual IClusteredParticles* IClusteredParticles::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IClusteredParticles::accept "virtual void IClusteredParticles::accept(ISampleVisitor *visitor) const =0

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  IClusteredParticles::setAmbientMaterial "virtual void IClusteredParticles::setAmbientMaterial(const IMaterial &material)=0
";

%feature("docstring")  IClusteredParticles::getAmbientMaterial "virtual const IMaterial* IClusteredParticles::getAmbientMaterial() const =0

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  IClusteredParticles::createTotalFormFactor "virtual IFormFactor* IClusteredParticles::createTotalFormFactor(const IFormFactor &, const IRotation *, const kvector_t &) const =0

Creates a total form factor for the mesocrystal with a specific shape and content The bulk content of the mesocrystal is encapsulated by the  IClusteredParticles object itself 
";

%feature("docstring")  IClusteredParticles::applyRotation "virtual void IClusteredParticles::applyRotation(const IRotation &)=delete

Composes transformation with existing one. 
";


// File: classICompositeSample.xml
%feature("docstring") ICompositeSample "

Pure virtual base class for tree-like composite samples.

Inherited by  IAbstractParticle, IClusteredParticle,  ILayout, ILayer, IMultiLayer.

C++ includes: ICompositeSample.h
";

%feature("docstring")  ICompositeSample::ICompositeSample "ICompositeSample::ICompositeSample()
";

%feature("docstring")  ICompositeSample::~ICompositeSample "ICompositeSample::~ICompositeSample()
";

%feature("docstring")  ICompositeSample::clone "virtual ICompositeSample* ICompositeSample::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ICompositeSample::accept "virtual void ICompositeSample::accept(ISampleVisitor *visitor) const =0

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  ICompositeSample::registerChild "void ICompositeSample::registerChild(ISample *sample)

Registers child in the container. 
";

%feature("docstring")  ICompositeSample::deregisterChild "void ICompositeSample::deregisterChild(ISample *sample)

Removes registered child from the container.

remove registered child from the container 
";

%feature("docstring")  ICompositeSample::getChildren "std::vector< const ISample * > ICompositeSample::getChildren() const final

Returns a vector of children (const). 
";

%feature("docstring")  ICompositeSample::size "size_t ICompositeSample::size() const final

Returns number of children. 
";

%feature("docstring")  ICompositeSample::addParametersToExternalPool "std::string ICompositeSample::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";


// File: classIDetector.xml
%feature("docstring") IDetector "

The detector interface.

C++ includes: IDetector2D.h
";


// File: classIDetector2D.xml
%feature("docstring") IDetector2D "";

%feature("docstring")  IDetector2D::IDetector2D "IDetector2D::IDetector2D()
";

%feature("docstring")  IDetector2D::clone "virtual IDetector2D* IDetector2D::clone() const =0
";

%feature("docstring")  IDetector2D::~IDetector2D "IDetector2D::~IDetector2D()
";

%feature("docstring")  IDetector2D::init "virtual void IDetector2D::init(const Beam &)

Inits detector with the beam settings. 
";

%feature("docstring")  IDetector2D::addAxis "void IDetector2D::addAxis(const IAxis &axis)
";

%feature("docstring")  IDetector2D::getAxis "const IAxis & IDetector2D::getAxis(size_t index) const
";

%feature("docstring")  IDetector2D::getDimension "size_t IDetector2D::getDimension() const
";

%feature("docstring")  IDetector2D::clear "void IDetector2D::clear()
";

%feature("docstring")  IDetector2D::setDetectorParameters "void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  IDetector2D::setDetectorAxes "void IDetector2D::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)

Sets detector parameters using axes. 
";

%feature("docstring")  IDetector2D::setDetectorResolution "void IDetector2D::setDetectorResolution(IDetectorResolution *p_detector_resolution)

Sets the detector resolution. 
";

%feature("docstring")  IDetector2D::applyDetectorResolution "void IDetector2D::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Applies the detector resolution to the given intensity maps. 
";

%feature("docstring")  IDetector2D::getDetectorResolutionFunction "const IDetectorResolution * IDetector2D::getDetectorResolutionFunction() const
";

%feature("docstring")  IDetector2D::setAnalyzerProperties "void IDetector2D::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  IDetector2D::removeMasks "void IDetector2D::removeMasks()

removes all masks from the detector 
";

%feature("docstring")  IDetector2D::addMask "void IDetector2D::addMask(const Geometry::IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask (Rectangle, Polygon, Line, Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  IDetector2D::maskAll "void IDetector2D::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  IDetector2D::getDetectorMask "const DetectorMask * IDetector2D::getDetectorMask() const
";

%feature("docstring")  IDetector2D::numberOfMaskedChannels "size_t IDetector2D::numberOfMaskedChannels() const
";

%feature("docstring")  IDetector2D::isMasked "bool IDetector2D::isMasked(size_t index) const
";

%feature("docstring")  IDetector2D::hasMasks "bool IDetector2D::hasMasks() const

return true if has masks 
";

%feature("docstring")  IDetector2D::createSimulationElements "std::vector< SimulationElement > IDetector2D::createSimulationElements(const Beam &beam)

Create a vector of  SimulationElement objects according to the detector and its mask. 
";

%feature("docstring")  IDetector2D::getSimulationElement "SimulationElement IDetector2D::getSimulationElement(size_t index, const Beam &beam) const

Creates single simulation element. 
";

%feature("docstring")  IDetector2D::addParametersToExternalPool "std::string IDetector2D::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  IDetector2D::createDetectorIntensity "OutputData< double > * IDetector2D::createDetectorIntensity(const std::vector< SimulationElement > &elements, const Beam &beam, IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns new intensity map with detector resolution applied and axes in requested units. 
";

%feature("docstring")  IDetector2D::createDetectorMap "OutputData< double > * IDetector2D::createDetectorMap(const Beam &beam, EAxesUnits units) const

Returns empty detector map in given axes units. 
";

%feature("docstring")  IDetector2D::initOutputData "void IDetector2D::initOutputData(OutputData< double > &data) const

Inits axes of  OutputData to match the detector and sets values to zero. 
";

%feature("docstring")  IDetector2D::getValidAxesUnits "std::vector< IDetector2D::EAxesUnits > IDetector2D::getValidAxesUnits() const

returns vector of valid axes units 
";

%feature("docstring")  IDetector2D::getDefaultAxesUnits "virtual EAxesUnits IDetector2D::getDefaultAxesUnits() const

return default axes units 
";

%feature("docstring")  IDetector2D::regionOfInterest "const RegionOfInterest * IDetector2D::regionOfInterest() const

Returns region of interest if exists. 
";

%feature("docstring")  IDetector2D::setRegionOfInterest "void IDetector2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)

Sets rectangular region of interest with lower left and upper right corners defined. 
";

%feature("docstring")  IDetector2D::resetRegionOfInterest "void IDetector2D::resetRegionOfInterest()

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  IDetector2D::getTotalSize "size_t IDetector2D::getTotalSize() const

Returns total number of pixels. 
";

%feature("docstring")  IDetector2D::getAxisBinIndex "size_t IDetector2D::getAxisBinIndex(size_t index, size_t selected_axis) const

Calculate axis index for given global index. 
";

%feature("docstring")  IDetector2D::numberOfSimulationElements "size_t IDetector2D::numberOfSimulationElements() const

Returns number of simulation elements. 
";


// File: classIDetectorResolution.xml
%feature("docstring") IDetectorResolution "

Interface for detector resolution algorithms.

C++ includes: IDetectorResolution.h
";

%feature("docstring")  IDetectorResolution::~IDetectorResolution "virtual IDetectorResolution::~IDetectorResolution()
";

%feature("docstring")  IDetectorResolution::applyDetectorResolution "virtual void IDetectorResolution::applyDetectorResolution(OutputData< double > *p_intensity_map) const =0

Apply the resolution function to the intensity data. 
";

%feature("docstring")  IDetectorResolution::applyDetectorResolutionPol "void IDetectorResolution::applyDetectorResolutionPol(OutputData< Eigen::Matrix2d > *p_matrix_intensity) const

Applies the detector resolution to the matrix-valued intensity data. 
";

%feature("docstring")  IDetectorResolution::clone "virtual IDetectorResolution* IDetectorResolution::clone() const =0
";


// File: classIDistribution1D.xml
%feature("docstring") IDistribution1D "

Interface for 1 dimensional distributions.

C++ includes: Distributions.h
";

%feature("docstring")  IDistribution1D::IDistribution1D "IDistribution1D::IDistribution1D()
";

%feature("docstring")  IDistribution1D::~IDistribution1D "virtual IDistribution1D::~IDistribution1D()
";

%feature("docstring")  IDistribution1D::clone "IDistribution1D * IDistribution1D::clone() const
";

%feature("docstring")  IDistribution1D::probabilityDensity "virtual double IDistribution1D::probabilityDensity(double x) const =0

get the probability density for value x 
";

%feature("docstring")  IDistribution1D::getMean "virtual double IDistribution1D::getMean() const =0

get the mean of the distribution 
";

%feature("docstring")  IDistribution1D::generateSamples "std::vector< ParameterSample > IDistribution1D::generateSamples(size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits()) const

generate list of sampled values with their weight xmin, xmax for sample generations are deduced from sigma_factor and possible limits 
";

%feature("docstring")  IDistribution1D::generateSamples "std::vector< ParameterSample > IDistribution1D::generateSamples(size_t nbr_samples, double xmin, double xmax) const

generate list of sampled values with their weight within given xmin, xmax 
";

%feature("docstring")  IDistribution1D::generateValueList "virtual std::vector<double> IDistribution1D::generateValueList(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const =0

generate list of sample values

Parameters:
-----------

nbr_samples: 
number of values to generate

sigma_factor: 
parameter to derive min,max range for sample values

limits:

vector of generated values 
";

%feature("docstring")  IDistribution1D::generateValues "std::vector< double > IDistribution1D::generateValues(size_t nbr_samples, double xmin, double xmax) const

Interface.

generate list of sample values

Parameters:
-----------

nbr_samples: 
number of values to generate

xmin: 
xmax: 
start and end value of the generated samples

vector of generated values 
";

%feature("docstring")  IDistribution1D::getMeanSample "ParameterSample IDistribution1D::getMeanSample() const

generate a single sample containing the mean value and weight 1 
";

%feature("docstring")  IDistribution1D::isDelta "virtual bool IDistribution1D::isDelta() const =0

signals that the distribution is in the limit case of a delta distribution 
";


// File: classIFactory.xml
%feature("docstring") IFactory "

Base class for all factories.

C++ includes: IFactory.h
";

%feature("docstring")  IFactory::IFactory "IFactory< Key, AbstractProduct >::IFactory()
";

%feature("docstring")  IFactory::createItem "AbstractProduct* IFactory< Key, AbstractProduct >::createItem(const Key &item_key)

Creates object by calling creation function corresponded to given identifier. 
";

%feature("docstring")  IFactory::registerItem "bool IFactory< Key, AbstractProduct >::registerItem(const Key &item_key, CreateItemCallback CreateFn, const std::string &itemDescription=\"\")

Registers object's creation function and store object description. 
";

%feature("docstring")  IFactory::~IFactory "IFactory< Key, AbstractProduct >::~IFactory()
";

%feature("docstring")  IFactory::getNumberOfRegistered "size_t IFactory< Key, AbstractProduct >::getNumberOfRegistered() const

Returns number of registered objects. 
";

%feature("docstring")  IFactory::begin "const_iterator IFactory< Key, AbstractProduct >::begin() const
";

%feature("docstring")  IFactory::end "const_iterator IFactory< Key, AbstractProduct >::end() const
";


// File: classIFitObserver.xml
%feature("docstring") IFitObserver "

Base class for all fit observers. Calls update method in following cases: first iteration, every n-th iteration, last iteration and when fit strategy has changed.

C++ includes: IFitObserver.h
";

%feature("docstring")  IFitObserver::IFitObserver "IFitObserver::IFitObserver(int update_every_nth)
";

%feature("docstring")  IFitObserver::notify "void IFitObserver::notify(IObservable *subject)

The method used by Ovservable when he wants to be observed by this. 
";

%feature("docstring")  IFitObserver::update "void IFitObserver::update(FitSuite *fit_suite)

Here Onserver will do actuall job when he thinks that it is a right moment. 
";


// File: classIFitStrategy.xml
%feature("docstring") IFitStrategy "

Interface to concrete fit strategy.

Concrete implementation should manipulate with fit parameters/data and then call minimizer.

C++ includes: IFitStrategy.h
";

%feature("docstring")  IFitStrategy::IFitStrategy "IFitStrategy::IFitStrategy(const std::string &name)
";

%feature("docstring")  IFitStrategy::~IFitStrategy "virtual IFitStrategy::~IFitStrategy()
";

%feature("docstring")  IFitStrategy::clone "virtual IFitStrategy* IFitStrategy::clone() const =0
";

%feature("docstring")  IFitStrategy::init "void IFitStrategy::init(FitSuiteImpl *fit_suite)
";

%feature("docstring")  IFitStrategy::execute "virtual void IFitStrategy::execute()=0
";


// File: classIFitSuiteFunction.xml
%feature("docstring") IFitSuiteFunction "

Fitting functions interface to be used by Minimizer.

C++ includes: FitSuiteFunctions.h
";

%feature("docstring")  IFitSuiteFunction::IFitSuiteFunction "IFitSuiteFunction::IFitSuiteFunction()
";

%feature("docstring")  IFitSuiteFunction::~IFitSuiteFunction "virtual IFitSuiteFunction::~IFitSuiteFunction()
";

%feature("docstring")  IFitSuiteFunction::init "virtual void IFitSuiteFunction::init(FitSuiteImpl *fit_suite)
";

%feature("docstring")  IFitSuiteFunction::getNCalls "virtual size_t IFitSuiteFunction::getNCalls() const
";


// File: classIFormFactor.xml
%feature("docstring") IFormFactor "

Pure virtual base class for all form factors.

The actual form factor is returned by the complex valued function  IFormFactor::evaluate, which depends on the incoming and outgoing wave vectors ki and kf. If it only depends on the scattering vector q=ki-kf, then it is a IBornFormFactor.

Other children besides IBornFormFactor are  IFormFactorDecorator,  FormFactorWeighted,  FormFactorDWBA,  FormFactorDWBAPol and  FormFactorCrystal.

C++ includes: IFormFactor.h
";

%feature("docstring")  IFormFactor::IFormFactor "IFormFactor::IFormFactor()
";

%feature("docstring")  IFormFactor::~IFormFactor "IFormFactor::~IFormFactor() override
";

%feature("docstring")  IFormFactor::clone "IFormFactor* IFormFactor::clone() const override=0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IFormFactor::accept "void IFormFactor::accept(ISampleVisitor *visitor) const override=0

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IFormFactor::setAmbientMaterial "virtual void IFormFactor::setAmbientMaterial(const IMaterial &)

Passes the refractive index of the ambient material in which this particle is embedded. 
";

%feature("docstring")  IFormFactor::evaluate "virtual complex_t IFormFactor::evaluate(const WavevectorInfo &wavevectors) const =0

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  IFormFactor::evaluatePol "Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions. 
";

%feature("docstring")  IFormFactor::getVolume "double IFormFactor::getVolume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactor::getRadialExtension "virtual double IFormFactor::getRadialExtension() const =0

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactor::setSpecularInfo "virtual void IFormFactor::setSpecularInfo(const ILayerRTCoefficients *, const ILayerRTCoefficients *)

Sets reflection/transmission info. 
";


// File: classIFormFactorBorn.xml
%feature("docstring") IFormFactorBorn "

Pure virtual base class for Born form factors.

In contrast to the generic  IFormFactor, a Born form factor does not depend on the incoming and outgoing wave vectors ki and kf, except through their difference, the scattering vector q=ki-kf.

C++ includes: IFormFactorBorn.h
";

%feature("docstring")  IFormFactorBorn::IFormFactorBorn "IFormFactorBorn::IFormFactorBorn()
";

%feature("docstring")  IFormFactorBorn::~IFormFactorBorn "IFormFactorBorn::~IFormFactorBorn() override
";

%feature("docstring")  IFormFactorBorn::clone "IFormFactorBorn* IFormFactorBorn::clone() const override=0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IFormFactorBorn::evaluate "complex_t IFormFactorBorn::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  IFormFactorBorn::evaluatePol "Eigen::Matrix2cd IFormFactorBorn::evaluatePol(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for matrix interactions. 
";

%feature("docstring")  IFormFactorBorn::evaluate_for_q "virtual complex_t IFormFactorBorn::evaluate_for_q(const cvector_t q) const =0

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classIFormFactorDecorator.xml
%feature("docstring") IFormFactorDecorator "

Encapsulates another formfactor and adds extra functionality (a scalar factor, a Debye-Waller factor, a position-dependent phase factor, ...).

This class is designed according to the Decorator Pattern. It inherits from  IFormFactor and has a member of type IFormFactor*.

C++ includes: IFormFactorDecorator.h
";

%feature("docstring")  IFormFactorDecorator::IFormFactorDecorator "IFormFactorDecorator::IFormFactorDecorator(const IFormFactor &form_factor)
";

%feature("docstring")  IFormFactorDecorator::~IFormFactorDecorator "IFormFactorDecorator::~IFormFactorDecorator() override
";

%feature("docstring")  IFormFactorDecorator::clone "IFormFactorDecorator* IFormFactorDecorator::clone() const override=0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IFormFactorDecorator::accept "void IFormFactorDecorator::accept(ISampleVisitor *visitor) const override=0

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IFormFactorDecorator::setAmbientMaterial "void IFormFactorDecorator::setAmbientMaterial(const IMaterial &material) override

Passes the refractive index of the ambient material in which this particle is embedded. 
";

%feature("docstring")  IFormFactorDecorator::getVolume "double IFormFactorDecorator::getVolume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactorDecorator::getRadialExtension "double IFormFactorDecorator::getRadialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";


// File: classIFTDecayFunction1D.xml
%feature("docstring") IFTDecayFunction1D "

Interface for a one-dimensional decay function, with evaluate(q) returning the Fourier transform, normalized to  $\\\\int dq\\\\; {\\\\rm evaluate}(q) = 1$.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  IFTDecayFunction1D::IFTDecayFunction1D "IFTDecayFunction1D::IFTDecayFunction1D(double omega)
";

%feature("docstring")  IFTDecayFunction1D::clone "virtual IFTDecayFunction1D* IFTDecayFunction1D::clone() const =0
";

%feature("docstring")  IFTDecayFunction1D::evaluate "virtual double IFTDecayFunction1D::evaluate(double q) const =0
";

%feature("docstring")  IFTDecayFunction1D::setOmega "void IFTDecayFunction1D::setOmega(double omega)
";

%feature("docstring")  IFTDecayFunction1D::getOmega "double IFTDecayFunction1D::getOmega() const
";


// File: classIFTDecayFunction2D.xml
%feature("docstring") IFTDecayFunction2D "

Interface for two-dimensional decay function in reciprocal space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  IFTDecayFunction2D::IFTDecayFunction2D "IFTDecayFunction2D::IFTDecayFunction2D(double decay_length_x, double decay_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  IFTDecayFunction2D::clone "virtual IFTDecayFunction2D* IFTDecayFunction2D::clone() const =0
";

%feature("docstring")  IFTDecayFunction2D::setGamma "void IFTDecayFunction2D::setGamma(double gamma)

set angle between first lattice vector and X-axis of distribution (both in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::getGamma "double IFTDecayFunction2D::getGamma() const

get angle between first lattice vector and X-axis of distribution (both in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::getDelta "double IFTDecayFunction2D::getDelta() const

get angle between X- and Y-axis of distribution (in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::getDecayLengthX "double IFTDecayFunction2D::getDecayLengthX() const

get coherence length in X-direction 
";

%feature("docstring")  IFTDecayFunction2D::getDecayLengthY "double IFTDecayFunction2D::getDecayLengthY() const

get coherence length in Y-direction 
";

%feature("docstring")  IFTDecayFunction2D::evaluate "virtual double IFTDecayFunction2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  IFTDecayFunction2D::transformToStarBasis "void IFTDecayFunction2D::transformToStarBasis(double qX, double qY, double alpha, double a, double b, double &qa, double &qb) const

transform back to a*, b* basis: 
";


// File: classIFTDistribution1D.xml
%feature("docstring") IFTDistribution1D "

Interface for a one-dimensional distribution, with normalization adjusted so that the Fourier transform evaluate(q) is a decay function that starts at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  IFTDistribution1D::IFTDistribution1D "IFTDistribution1D::IFTDistribution1D(double omega)
";

%feature("docstring")  IFTDistribution1D::clone "virtual IFTDistribution1D* IFTDistribution1D::clone() const =0
";

%feature("docstring")  IFTDistribution1D::evaluate "virtual double IFTDistribution1D::evaluate(double q) const =0

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  IFTDistribution1D::setOmega "void IFTDistribution1D::setOmega(double omega)
";

%feature("docstring")  IFTDistribution1D::getOmega "double IFTDistribution1D::getOmega() const
";


// File: classIFTDistribution2D.xml
%feature("docstring") IFTDistribution2D "

Interface for two-dimensional distributions in Fourier space.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  IFTDistribution2D::IFTDistribution2D "IFTDistribution2D::IFTDistribution2D(double coherence_length_x, double coherence_length_y, double gamma=0, double delta=M_PI_2)
";

%feature("docstring")  IFTDistribution2D::clone "virtual IFTDistribution2D* IFTDistribution2D::clone() const =0
";

%feature("docstring")  IFTDistribution2D::setGamma "void IFTDistribution2D::setGamma(double gamma)
";

%feature("docstring")  IFTDistribution2D::getGamma "double IFTDistribution2D::getGamma() const
";

%feature("docstring")  IFTDistribution2D::getDelta "double IFTDistribution2D::getDelta() const
";

%feature("docstring")  IFTDistribution2D::getCoherenceLengthX "double IFTDistribution2D::getCoherenceLengthX() const
";

%feature("docstring")  IFTDistribution2D::getCoherenceLengthY "double IFTDistribution2D::getCoherenceLengthY() const
";

%feature("docstring")  IFTDistribution2D::evaluate "virtual double IFTDistribution2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classIHistogram.xml
%feature("docstring") IHistogram "

Base class for 1D and 2D histograms holding values of double type.

C++ includes: IHistogram.h
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram()
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IHistogram &other)
";

%feature("docstring")  IHistogram::~IHistogram "virtual IHistogram::~IHistogram()
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IAxis &axis_x)
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IAxis &axis_x, const IAxis &axis_y)
";

%feature("docstring")  IHistogram::clone "virtual IHistogram* IHistogram::clone() const =0
";

%feature("docstring")  IHistogram::getRank "virtual size_t IHistogram::getRank() const =0

Returns number of histogram dimensions. 
";

%feature("docstring")  IHistogram::getTotalNumberOfBins "size_t IHistogram::getTotalNumberOfBins() const

Returns total number of histogram bins. For 2D histograms the result will be the product of bin numbers along X and Y axes. 
";

%feature("docstring")  IHistogram::getXaxis "const IAxis & IHistogram::getXaxis() const

returns x-axis 
";

%feature("docstring")  IHistogram::getYaxis "const IAxis & IHistogram::getYaxis() const

returns y-axis for 2D histograms 
";

%feature("docstring")  IHistogram::getXmin "double IHistogram::getXmin() const

Returns x-axis min (lower edge of first bin). 
";

%feature("docstring")  IHistogram::getXmax "double IHistogram::getXmax() const

Returns x-axis max (upper edge of last bin). 
";

%feature("docstring")  IHistogram::getNbinsX "size_t IHistogram::getNbinsX() const

Returns number of bins on x-axis. 
";

%feature("docstring")  IHistogram::getYmin "double IHistogram::getYmin() const

Returns y-axis min (lower edge of first bin) for 2D histograms. 
";

%feature("docstring")  IHistogram::getYmax "double IHistogram::getYmax() const

Returns y-axis max (upper edge of last bin) for 2D histograms. 
";

%feature("docstring")  IHistogram::getNbinsY "size_t IHistogram::getNbinsY() const

Returns number of bins on y-axis. 
";

%feature("docstring")  IHistogram::getGlobalBin "size_t IHistogram::getGlobalBin(size_t binx, size_t biny=0) const

Returns global bin index for given axes indices. For 1D histogram the global bin index coinside with x-axis index.

Parameters:
-----------

binx: 
x-axis bin index

biny: 
y-axis bin index (for 2D histograms)

The global bin index 
";

%feature("docstring")  IHistogram::findGlobalBin "size_t IHistogram::findGlobalBin(double x, double y) const

Returns closest global bin index for given axes coordinates. For 1D.

Parameters:
-----------

x: 
Value on x-axis

y: 
Value on y-axis (for 2D histograms)

Closest global bin index 
";

%feature("docstring")  IHistogram::getXaxisIndex "int IHistogram::getXaxisIndex(size_t i) const

Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide with globalbin value. 
";

%feature("docstring")  IHistogram::getYaxisIndex "int IHistogram::getYaxisIndex(size_t i) const

Returns y-axis bin index for given globalbin (for 2D histograms). 
";

%feature("docstring")  IHistogram::getXaxisValue "double IHistogram::getXaxisValue(size_t i)

Returns the value on x-axis corresponding to the global bin index.

Parameters:
-----------

globalbin: 
The global bin index

The center of corresponding bin of the axis 
";

%feature("docstring")  IHistogram::getYaxisValue "double IHistogram::getYaxisValue(size_t i)

Returns the value on y-axis corresponding to the 2D histogram global bin index.

Parameters:
-----------

globalbin: 
The global bin index

The center of corresponding bin of the axis 
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t i) const

Returns content (accumulated value) of the bin with given index.

Parameters:
-----------

globalbin: 
The global bin index

The value accumulated by the bin (integral) 
";

%feature("docstring")  IHistogram::getData "const OutputData<CumulativeValue>& IHistogram::getData() const
";

%feature("docstring")  IHistogram::getData "OutputData<CumulativeValue>& IHistogram::getData()
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t binx, size_t biny) const

Returns content (accumulated value) of the 2D histogram bin with given indices.

Parameters:
-----------

binx: 
x-axis bin index

biny: 
y-axis bin index

The value accumulated by the bin (integral) 
";

%feature("docstring")  IHistogram::setBinContent "void IHistogram::setBinContent(size_t i, double value)

Sets content of the bin corresponding to the globalbin number. 
";

%feature("docstring")  IHistogram::addBinContent "void IHistogram::addBinContent(size_t i, double value)

Add the value to the bin. 
";

%feature("docstring")  IHistogram::getBinError "double IHistogram::getBinError(size_t i) const

Returns error of the bin with given index. 
";

%feature("docstring")  IHistogram::getBinError "double IHistogram::getBinError(size_t binx, size_t biny) const

Returns error of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getBinAverage "double IHistogram::getBinAverage(size_t i) const

Returns average value in the bin with given index. 
";

%feature("docstring")  IHistogram::getBinAverage "double IHistogram::getBinAverage(size_t binx, size_t biny) const

Returns average value of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getBinNumberOfEntries "int IHistogram::getBinNumberOfEntries(size_t i) const

Returns number of entries in the bin with given index. 
";

%feature("docstring")  IHistogram::getBinNumberOfEntries "int IHistogram::getBinNumberOfEntries(size_t binx, size_t biny) const

Returns number of entries in the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getMaximum "double IHistogram::getMaximum() const

Returns histogram maximum value (maximum of  getBinContent() over all bins) 
";

%feature("docstring")  IHistogram::getMaximumBinIndex "size_t IHistogram::getMaximumBinIndex() const

Returns globalbin index with maximum content. 
";

%feature("docstring")  IHistogram::getMinimum "double IHistogram::getMinimum() const

Returns histogram minimum value (minimum of  getBinContent() over all bins) 
";

%feature("docstring")  IHistogram::getMinimumBinIndex "size_t IHistogram::getMinimumBinIndex() const

Returns globalbin index with minimum content. 
";

%feature("docstring")  IHistogram::scale "void IHistogram::scale(double value)

Multiply this histogram (every bin content value) by a constant. 
";

%feature("docstring")  IHistogram::integral "double IHistogram::integral() const

Returns integral of bins content (computed as a sum of all bin content). 
";

%feature("docstring")  IHistogram::reset "void IHistogram::reset()

Reset histogram content (axes remains) 
";

%feature("docstring")  IHistogram::createOutputData "OutputData< double > * IHistogram::createOutputData(DataType dataType=DataType::INTEGRAL) const

creates new  OutputData with histogram's shape and values corresponding to DataType

creates new  OutputData with histogram's shape and put there values corresponding to DataType 
";

%feature("docstring")  IHistogram::hasSameShape "bool IHistogram::hasSameShape(const IHistogram &other) const

Returns true if objects a) have same dimensions b) bin boundaries of axes coincide. 
";

%feature("docstring")  IHistogram::hasSameDimensions "bool IHistogram::hasSameDimensions(const IHistogram &other) const

Returns true if object have same rank and number of axes bins. 
";

%feature("docstring")  IHistogram::relativeDifferenceHistogram "IHistogram * IHistogram::relativeDifferenceHistogram(const IHistogram &rhs)

returns histogram representing relative difference of two histograms. 
";

%feature("docstring")  IHistogram::save "void IHistogram::save(const std::string &filename)

Saves histogram in file Following formats are available: *.txt, *.tif, *.int (*.txt.gz, *.tif.gz, *.int.gz) 
";

%feature("docstring")  IHistogram::load "void IHistogram::load(const std::string &filename)

Loads histogram from file, the shape of array in file should match Following formats are available: *.txt, *.tif, *.int (*.txt.gz, *.tif.gz, *.int.gz) Only bin content will be loaded, histogram axes remain the same. 
";


// File: classIIntensityFunction.xml
%feature("docstring") IIntensityFunction "

Interface for applying arbitrary function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IIntensityFunction::~IIntensityFunction "virtual IIntensityFunction::~IIntensityFunction()
";

%feature("docstring")  IIntensityFunction::clone "virtual IIntensityFunction* IIntensityFunction::clone() const =0
";

%feature("docstring")  IIntensityFunction::evaluate "virtual double IIntensityFunction::evaluate(double value) const =0
";


// File: classIIntensityNormalizer.xml
%feature("docstring") IIntensityNormalizer "

Interface to  OutputData normalizers.

C++ includes: IIntensityNormalizer.h
";

%feature("docstring")  IIntensityNormalizer::~IIntensityNormalizer "virtual IIntensityNormalizer::~IIntensityNormalizer()
";

%feature("docstring")  IIntensityNormalizer::clone "virtual IIntensityNormalizer* IIntensityNormalizer::clone() const =0
";

%feature("docstring")  IIntensityNormalizer::createNormalizedData "virtual OutputData<double>* IIntensityNormalizer::createNormalizedData(const OutputData< double > &data) const =0
";

%feature("docstring")  IIntensityNormalizer::apply "virtual void IIntensityNormalizer::apply(OutputData< double > &data) const =0
";

%feature("docstring")  IIntensityNormalizer::setMaximumIntensity "virtual void IIntensityNormalizer::setMaximumIntensity(double)=0
";


// File: classIInterferenceFunction.xml
%feature("docstring") IInterferenceFunction "

Pure virtual base class of interference functions.

C++ includes: IInterferenceFunction.h
";

%feature("docstring")  IInterferenceFunction::~IInterferenceFunction "virtual IInterferenceFunction::~IInterferenceFunction()
";

%feature("docstring")  IInterferenceFunction::clone "virtual IInterferenceFunction* IInterferenceFunction::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IInterferenceFunction::accept "virtual void IInterferenceFunction::accept(ISampleVisitor *visitor) const =0

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IInterferenceFunction::evaluate "virtual double IInterferenceFunction::evaluate(const kvector_t q) const =0

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  IInterferenceFunction::getKappa "virtual double IInterferenceFunction::getKappa() const

Retrieves the size-distance coupling constant (default 0.0) 
";

%feature("docstring")  IInterferenceFunction::getParticleDensity "virtual double IInterferenceFunction::getParticleDensity() const

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";


// File: classIInterferenceFunctionStrategy.xml
%feature("docstring") IInterferenceFunctionStrategy "

Pure virtual base class of all interference function strategy classes. Provides an 'evaluate' function that computes the total scattering intensity from a decorated layer, taking into account a specific inter-particle interference function. This function uses low-level functions precomputeParticleFormfactors, evaluateForList that are implemented differently in different inheriting classes. Multiple inheritance is used to support scalar and polarized scattering (through  IInterferenceFunctionStrategy1,  IInterferenceFunctionStrategy2) and to implement different approximation schemes ( DecouplingApproximationStrategy1,  SSCApproximationStrategy1, and their polarized counterparts).

Instantiation of child classes takes place in  LayerStrategyBuilder::createStrategy, which is called from  DecoratedLayerComputation::eval.

C++ includes: IInterferenceFunctionStrategy.h
";

%feature("docstring")  IInterferenceFunctionStrategy::IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::IInterferenceFunctionStrategy()
";

%feature("docstring")  IInterferenceFunctionStrategy::IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(const SimulationOptions &sim_params)
";

%feature("docstring")  IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy()
";

%feature("docstring")  IInterferenceFunctionStrategy::init "void IInterferenceFunctionStrategy::init(const SafePointerVector< FormFactorWrapper > &weighted_formfactors, const IInterferenceFunction &iff, const LayerSpecularInfo &specular_info)

Initializes the object with form factors and interference functions. 
";

%feature("docstring")  IInterferenceFunctionStrategy::evaluate "double IInterferenceFunctionStrategy::evaluate(const SimulationElement &sim_element) const

Calculates the intensity for scalar particles/interactions. 
";


// File: classIInterferenceFunctionStrategy1.xml
%feature("docstring") IInterferenceFunctionStrategy1 "

Pure virtual base class of all scalar interference function strategy classes. Provides the precomputation of particle form factors.

C++ includes: IInterferenceFunctionStrategy.h
";


// File: classIInterferenceFunctionStrategy2.xml
%feature("docstring") IInterferenceFunctionStrategy2 "

Pure virtual base class of all polarized interference function strategy classes. Provides the precomputation of particle form factors.

C++ includes: IInterferenceFunctionStrategy.h
";


// File: classILayerRTCoefficients.xml
%feature("docstring") ILayerRTCoefficients "

Interface to access reflection/transmission coefficients.

C++ includes: ILayerRTCoefficients.h
";

%feature("docstring")  ILayerRTCoefficients::~ILayerRTCoefficients "virtual ILayerRTCoefficients::~ILayerRTCoefficients()
";

%feature("docstring")  ILayerRTCoefficients::clone "virtual ILayerRTCoefficients* ILayerRTCoefficients::clone() const =0
";

%feature("docstring")  ILayerRTCoefficients::T1plus "virtual Eigen::Vector2cd ILayerRTCoefficients::T1plus() const =0

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  ILayerRTCoefficients::R1plus "virtual Eigen::Vector2cd ILayerRTCoefficients::R1plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::T2plus "virtual Eigen::Vector2cd ILayerRTCoefficients::T2plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::R2plus "virtual Eigen::Vector2cd ILayerRTCoefficients::R2plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::T1min "virtual Eigen::Vector2cd ILayerRTCoefficients::T1min() const =0
";

%feature("docstring")  ILayerRTCoefficients::R1min "virtual Eigen::Vector2cd ILayerRTCoefficients::R1min() const =0
";

%feature("docstring")  ILayerRTCoefficients::T2min "virtual Eigen::Vector2cd ILayerRTCoefficients::T2min() const =0
";

%feature("docstring")  ILayerRTCoefficients::R2min "virtual Eigen::Vector2cd ILayerRTCoefficients::R2min() const =0
";

%feature("docstring")  ILayerRTCoefficients::getKz "virtual Eigen::Vector2cd ILayerRTCoefficients::getKz() const =0

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  ILayerRTCoefficients::getScalarT "virtual complex_t ILayerRTCoefficients::getScalarT() const

Scalar value getters; these throw errors by default as they should only be used when the derived object is really scalar 
";

%feature("docstring")  ILayerRTCoefficients::getScalarR "virtual complex_t ILayerRTCoefficients::getScalarR() const
";

%feature("docstring")  ILayerRTCoefficients::getScalarKz "virtual complex_t ILayerRTCoefficients::getScalarKz() const
";


// File: classILayout.xml
%feature("docstring") ILayout "

Pure virtual interface class to equip a sample layer with scattering properties. Currently only inherited by  ParticleLayout; in the future also by domain structure.

C++ includes: ILayout.h
";

%feature("docstring")  ILayout::ILayout "ILayout::ILayout()
";

%feature("docstring")  ILayout::~ILayout "virtual ILayout::~ILayout()
";

%feature("docstring")  ILayout::clone "virtual ILayout* ILayout::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ILayout::accept "virtual void ILayout::accept(ISampleVisitor *visitor) const =0

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ILayout::cloneInvertB "virtual ILayout* ILayout::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ILayout::getNumberOfParticles "virtual size_t ILayout::getNumberOfParticles() const =0

Returns number of particles. 
";

%feature("docstring")  ILayout::getParticle "virtual const IAbstractParticle* ILayout::getParticle(size_t index) const =0

Returns information about particle with index. 
";

%feature("docstring")  ILayout::getParticles "virtual SafePointerVector<const IParticle> ILayout::getParticles() const =0

Returns information on all particles (type and abundance) and generates new particles if an  IAbstractParticle denotes a collection 
";

%feature("docstring")  ILayout::getAbundanceOfParticle "virtual double ILayout::getAbundanceOfParticle(size_t index) const =0

Get abundance fraction of particle with index. 
";

%feature("docstring")  ILayout::getTotalAbundance "double ILayout::getTotalAbundance() const

Get total abundance of all particles. 
";

%feature("docstring")  ILayout::getInterferenceFunction "virtual const IInterferenceFunction* ILayout::getInterferenceFunction() const =0

Returns interference function. 
";

%feature("docstring")  ILayout::cloneInterferenceFunction "virtual IInterferenceFunction* ILayout::cloneInterferenceFunction() const =0
";

%feature("docstring")  ILayout::getTotalParticleSurfaceDensity "virtual double ILayout::getTotalParticleSurfaceDensity() const =0

Returns surface density of all particles. 
";

%feature("docstring")  ILayout::setTotalParticleSurfaceDensity "virtual void ILayout::setTotalParticleSurfaceDensity(double particle_density)=0

Sets surface density of all particles. 
";

%feature("docstring")  ILayout::getApproximation "EInterferenceApproximation ILayout::getApproximation() const

Gets the used approximation for particles and interference functions. 
";

%feature("docstring")  ILayout::setApproximation "void ILayout::setApproximation(EInterferenceApproximation approximation)

Sets the used approximation for particles and interference functions. 
";


// File: classIMaterial.xml
%feature("docstring") IMaterial "

Interface to a named material.

C++ includes: IMaterial.h
";

%feature("docstring")  IMaterial::IMaterial "IMaterial::IMaterial(const std::string &name)
";

%feature("docstring")  IMaterial::~IMaterial "virtual IMaterial::~IMaterial()
";

%feature("docstring")  IMaterial::clone "IMaterial * IMaterial::clone() const
";

%feature("docstring")  IMaterial::isScalarMaterial "virtual bool IMaterial::isScalarMaterial() const

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  IMaterial::isMagneticMaterial "bool IMaterial::isMagneticMaterial() const
";

%feature("docstring")  IMaterial::getRefractiveIndex "virtual complex_t IMaterial::getRefractiveIndex() const
";

%feature("docstring")  IMaterial::getSpecularScatteringMatrix "Eigen::Matrix2cd IMaterial::getSpecularScatteringMatrix(const kvector_t k) const

Get the effective scattering matrix from the refractive index and a given wavevector used for the specular calculation. This matrix appears in the one-dimensional Schroedinger equation in the z-direction 
";

%feature("docstring")  IMaterial::getScatteringMatrix "Eigen::Matrix2cd IMaterial::getScatteringMatrix(double k_mag2) const

Get the scattering matrix (~potential V) from the material. This matrix appears in the full three-dimensional Schroedinger equation. 
";

%feature("docstring")  IMaterial::createTransformedMaterial "virtual const IMaterial* IMaterial::createTransformedMaterial(const Transform3D &transform) const =0

Create a new material that is transformed with respect to this one. 
";


// File: classIMultiLayerBuilder.xml
%feature("docstring") IMultiLayerBuilder "

Interface to the class capable to build samples to simulate.

C++ includes: IMultiLayerBuilder.h
";

%feature("docstring")  IMultiLayerBuilder::IMultiLayerBuilder "IMultiLayerBuilder::IMultiLayerBuilder()
";

%feature("docstring")  IMultiLayerBuilder::~IMultiLayerBuilder "virtual IMultiLayerBuilder::~IMultiLayerBuilder()
";

%feature("docstring")  IMultiLayerBuilder::buildSample "virtual MultiLayer* IMultiLayerBuilder::buildSample() const =0
";

%feature("docstring")  IMultiLayerBuilder::set_subtest "void IMultiLayerBuilder::set_subtest(const IParameterized *subtest_item)
";

%feature("docstring")  IMultiLayerBuilder::getFormFactor "const IFormFactor * IMultiLayerBuilder::getFormFactor() const
";

%feature("docstring")  IMultiLayerBuilder::getFTDistribution2D "const IFTDistribution2D * IMultiLayerBuilder::getFTDistribution2D() const
";


// File: classINamed.xml
%feature("docstring") INamed "

Interface for named objects.

C++ includes: INamed.h
";

%feature("docstring")  INamed::INamed "INamed::INamed()
";

%feature("docstring")  INamed::INamed "INamed::INamed(const std::string &name)
";

%feature("docstring")  INamed::~INamed "virtual INamed::~INamed()
";

%feature("docstring")  INamed::getName "std::string INamed::getName() const
";


// File: classGeometry_1_1InfinitePlane.xml
%feature("docstring") Geometry::InfinitePlane "

The infinite plane is used for masking everything once and forever.

C++ includes: InfinitePlane.h
";

%feature("docstring")  Geometry::InfinitePlane::InfinitePlane "Geometry::InfinitePlane::InfinitePlane()
";

%feature("docstring")  Geometry::InfinitePlane::clone "InfinitePlane* Geometry::InfinitePlane::clone() const
";

%feature("docstring")  Geometry::InfinitePlane::contains "bool Geometry::InfinitePlane::contains(double, double) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::InfinitePlane::contains "bool Geometry::InfinitePlane::contains(const Bin1D &, const Bin1D &) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";


// File: classInnerCounter.xml
%feature("docstring") InnerCounter "

Base class for threaded computation; keeps count of progress.

C++ includes: InnerCounter.h
";

%feature("docstring")  InnerCounter::InnerCounter "InnerCounter::InnerCounter()
";

%feature("docstring")  InnerCounter::stepProgress "void InnerCounter::stepProgress(ProgressHandler *progress)

Increments progress count; at regular intervals updates main progress handler. 
";


// File: classINoncopyable.xml
%feature("docstring") INoncopyable "

Mix-in for objects that must not be copied.

This virtual base class disables the copy constructor and the operator= in all its child classes.

C++ includes: INoncopyable.h
";

%feature("docstring")  INoncopyable::INoncopyable "INoncopyable::INoncopyable()
";

%feature("docstring")  INoncopyable::~INoncopyable "virtual INoncopyable::~INoncopyable()
";

%feature("docstring")  INoncopyable::INoncopyable "INoncopyable::INoncopyable(const INoncopyable &)=delete
";


// File: classInstrument.xml
%feature("docstring") Instrument "

Assembles beam, detector and their relative positions wrt the sample.

C++ includes: Instrument.h
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument()
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument(const Instrument &other)
";

%feature("docstring")  Instrument::~Instrument "Instrument::~Instrument()
";

%feature("docstring")  Instrument::getBeam "Beam& Instrument::getBeam()
";

%feature("docstring")  Instrument::getBeam "const Beam& Instrument::getBeam() const
";

%feature("docstring")  Instrument::setBeam "void Instrument::setBeam(const Beam &beam)
";

%feature("docstring")  Instrument::setBeamParameters "void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets the beam wavelength and incoming angles. 
";

%feature("docstring")  Instrument::setBeamIntensity "void Instrument::setBeamIntensity(double intensity)

Sets the beam's intensity. 
";

%feature("docstring")  Instrument::setBeamPolarization "void Instrument::setBeamPolarization(const kvector_t bloch_vector)

Sets the beam's polarization according to the given Bloch vector. 
";

%feature("docstring")  Instrument::getBeamIntensity "double Instrument::getBeamIntensity() const

Returns the beam's intensity. 
";

%feature("docstring")  Instrument::getDetector "const IDetector2D * Instrument::getDetector() const

Returns the detector data. 
";

%feature("docstring")  Instrument::getDetector "IDetector2D * Instrument::getDetector()
";

%feature("docstring")  Instrument::getDetectorMask "const DetectorMask * Instrument::getDetectorMask() const
";

%feature("docstring")  Instrument::getDetectorAxis "const IAxis & Instrument::getDetectorAxis(size_t index) const

Returns a detector axis. 
";

%feature("docstring")  Instrument::getDetectorDimension "size_t Instrument::getDetectorDimension() const

Returns the detector's dimension. 
";

%feature("docstring")  Instrument::setDetector "void Instrument::setDetector(const IDetector2D &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  Instrument::setDetectorParameters "void Instrument::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  Instrument::setDetectorAxes "void Instrument::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)

Sets detector parameters using axes. 
";

%feature("docstring")  Instrument::setDetectorResolutionFunction "void Instrument::setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function)

Sets detector resolution function. 
";

%feature("docstring")  Instrument::setDetectorResolutionFunction "void Instrument::setDetectorResolutionFunction(const IResolutionFunction2D &p_resolution_function)
";

%feature("docstring")  Instrument::setAnalyzerProperties "void Instrument::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  Instrument::applyDetectorResolution "void Instrument::applyDetectorResolution(OutputData< double > *p_intensity_map) const

apply the detector resolution to the given intensity map 
";

%feature("docstring")  Instrument::createDetectorIntensity "OutputData< double > * Instrument::createDetectorIntensity(const std::vector< SimulationElement > &elements, IDetector2D::EAxesUnits units=IDetector2D::DEFAULT) const

Returns new intensity map with detector resolution applied and axes in requested units. 
";

%feature("docstring")  Instrument::createDetectorMap "OutputData< double > * Instrument::createDetectorMap(IDetector2D::EAxesUnits units=IDetector2D::DEFAULT) const

Returns empty detector map in given axes units. 
";

%feature("docstring")  Instrument::createSimulationElements "std::vector< SimulationElement > Instrument::createSimulationElements()

Create a vector of  SimulationElement objects according to the beam, detector and its mask. 
";

%feature("docstring")  Instrument::addParametersToExternalPool "std::string Instrument::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  Instrument::initDetector "void Instrument::initDetector()

init detector with beam settings 
";


// File: classIntegratorComplex.xml
%feature("docstring") IntegratorComplex "

Template class to integrate complex class member functions.

Wraps an two integrators from the GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_complex(this, mem_function)'

Call: 'integrator.integrate(lmin, lmax)'

C++ includes: IntegratorComplex.h
";

%feature("docstring")  IntegratorComplex::IntegratorComplex "IntegratorComplex< T >::IntegratorComplex(const T *p_object, complex_integrand< T > p_member_function)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorComplex::~IntegratorComplex "IntegratorComplex< T >::~IntegratorComplex()
";

%feature("docstring")  IntegratorComplex::integrate "complex_t IntegratorComplex< T >::integrate(double lmin, double lmax)

perform the actual integration over the range [lmin, lmax] 
";


// File: classIntegratorMCMiser.xml
%feature("docstring") IntegratorMCMiser "";

%feature("docstring")  IntegratorMCMiser::IntegratorMCMiser "IntegratorMCMiser< T >::IntegratorMCMiser(const T *p_object, miser_integrand< T > p_member_function, size_t dim)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorMCMiser::~IntegratorMCMiser "IntegratorMCMiser< T >::~IntegratorMCMiser()
";

%feature("docstring")  IntegratorMCMiser::integrate "double IntegratorMCMiser< T >::integrate(double *min_array, double *max_array, void *params, size_t nbr_points)

perform the actual integration over the ranges [min_array, max_array] 
";


// File: classIntegratorReal.xml
%feature("docstring") IntegratorReal "

Template class to integrate class member functions.

Wraps an integrator from the GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_real(this, mem_function)'

Call: 'integrator.integrate(lmin, lmax)'

C++ includes: IntegratorReal.h
";

%feature("docstring")  IntegratorReal::IntegratorReal "IntegratorReal< T >::IntegratorReal(const T *p_object, real_integrand< T > p_member_function)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorReal::~IntegratorReal "IntegratorReal< T >::~IntegratorReal()
";

%feature("docstring")  IntegratorReal::integrate "double IntegratorReal< T >::integrate(double lmin, double lmax)

perform the actual integration over the range [lmin, lmax] 
";


// File: classIntensityDataFunctions.xml
%feature("docstring") IntensityDataFunctions "

Class holding collection of static methods to work with intensity data.

C++ includes: IntensityDataFunctions.h
";


// File: classIntensityDataIOFactory.xml
%feature("docstring") IntensityDataIOFactory "

Provides users with possibility to read and write IntensityData from/to files in different format. Type of the file will be deduced from file name. *.txt - ASCII file with 2D array [nrow][ncol], layout as in numpy. *.int - BornAgain internal ASCII format. *.tif - 32-bits tiff file. If file name ends woth \"*.gz\" or \"*.bz2\" the file will be zipped on the fly using appropriate algorithm.

Usage:

C++ includes: IntensityDataIOFactory.h
";


// File: classIntensityFunctionLog.xml
%feature("docstring") IntensityFunctionLog "

Algorithm for applying log function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionLog::~IntensityFunctionLog "virtual IntensityFunctionLog::~IntensityFunctionLog()
";

%feature("docstring")  IntensityFunctionLog::clone "virtual IntensityFunctionLog* IntensityFunctionLog::clone() const
";

%feature("docstring")  IntensityFunctionLog::evaluate "double IntensityFunctionLog::evaluate(double value) const
";


// File: classIntensityFunctionSqrt.xml
%feature("docstring") IntensityFunctionSqrt "

Algorithm for applying sqrt function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionSqrt::~IntensityFunctionSqrt "virtual IntensityFunctionSqrt::~IntensityFunctionSqrt()
";

%feature("docstring")  IntensityFunctionSqrt::clone "virtual IntensityFunctionSqrt* IntensityFunctionSqrt::clone() const
";

%feature("docstring")  IntensityFunctionSqrt::evaluate "double IntensityFunctionSqrt::evaluate(double value) const
";


// File: classIntensityNormalizer.xml
%feature("docstring") IntensityNormalizer "

Standard  OutputData normalizer, with configurable max_intensity.

C++ includes: IIntensityNormalizer.h
";

%feature("docstring")  IntensityNormalizer::IntensityNormalizer "IntensityNormalizer::IntensityNormalizer(double scale=1.0, double shift=0.0)
";

%feature("docstring")  IntensityNormalizer::~IntensityNormalizer "virtual IntensityNormalizer::~IntensityNormalizer()
";

%feature("docstring")  IntensityNormalizer::clone "IntensityNormalizer * IntensityNormalizer::clone() const
";

%feature("docstring")  IntensityNormalizer::createNormalizedData "OutputData< double > * IntensityNormalizer::createNormalizedData(const OutputData< double > &data) const
";

%feature("docstring")  IntensityNormalizer::apply "void IntensityNormalizer::apply(OutputData< double > &data) const final
";

%feature("docstring")  IntensityNormalizer::setMaximumIntensity "virtual void IntensityNormalizer::setMaximumIntensity(double max_intensity)
";


// File: classIntensityScaleAndShiftNormalizer.xml
%feature("docstring") IntensityScaleAndShiftNormalizer "

Simplified  OutputData normalizer, with max_intensity=1.

C++ includes: IIntensityNormalizer.h
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::IntensityScaleAndShiftNormalizer "IntensityScaleAndShiftNormalizer::IntensityScaleAndShiftNormalizer(double scale=1.0, double shift=0.0)
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::~IntensityScaleAndShiftNormalizer "IntensityScaleAndShiftNormalizer::~IntensityScaleAndShiftNormalizer() final
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::setMaximumIntensity "void IntensityScaleAndShiftNormalizer::setMaximumIntensity(double) final
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::clone "IntensityScaleAndShiftNormalizer* IntensityScaleAndShiftNormalizer::clone() const final
";


// File: classInterferenceFunction1DLattice.xml
%feature("docstring") InterferenceFunction1DLattice "

Interference function of 1D lattice.

C++ includes: InterferenceFunction1DLattice.h
";

%feature("docstring")  InterferenceFunction1DLattice::InterferenceFunction1DLattice "InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length, double xi)

Parameters:
-----------

length: 
 Lattice length

xi: 
rotation of lattice with respect to x-axis 
";

%feature("docstring")  InterferenceFunction1DLattice::~InterferenceFunction1DLattice "InterferenceFunction1DLattice::~InterferenceFunction1DLattice() final
";

%feature("docstring")  InterferenceFunction1DLattice::clone "InterferenceFunction1DLattice * InterferenceFunction1DLattice::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction1DLattice::accept "void InterferenceFunction1DLattice::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction1DLattice::setDecayFunction "void InterferenceFunction1DLattice::setDecayFunction(const IFTDecayFunction1D &pdf)
";

%feature("docstring")  InterferenceFunction1DLattice::getLatticeParameters "Lattice1DParameters InterferenceFunction1DLattice::getLatticeParameters() const
";

%feature("docstring")  InterferenceFunction1DLattice::getDecayFunction "const IFTDecayFunction1D* InterferenceFunction1DLattice::getDecayFunction() const
";

%feature("docstring")  InterferenceFunction1DLattice::evaluate "double InterferenceFunction1DLattice::evaluate(const kvector_t q) const final

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";


// File: classInterferenceFunction2DLattice.xml
%feature("docstring") InterferenceFunction2DLattice "

Interference function of 2D lattice.

C++ includes: InterferenceFunction2DLattice.h
";

%feature("docstring")  InterferenceFunction2DLattice::InterferenceFunction2DLattice "InterferenceFunction2DLattice::InterferenceFunction2DLattice(double length_1, double length_2, double angle, double xi=0.0)

Parameters:
-----------

length_1: 
 Lattice length 1

length_2: 
 Lattice length 2

angle: 
angle between lattice vectors

xi: 
rotation of lattice with respect to x-axis 
";

%feature("docstring")  InterferenceFunction2DLattice::~InterferenceFunction2DLattice "InterferenceFunction2DLattice::~InterferenceFunction2DLattice() final
";

%feature("docstring")  InterferenceFunction2DLattice::clone "InterferenceFunction2DLattice * InterferenceFunction2DLattice::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction2DLattice::accept "void InterferenceFunction2DLattice::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction2DLattice::setDecayFunction "void InterferenceFunction2DLattice::setDecayFunction(const IFTDecayFunction2D &pdf)
";

%feature("docstring")  InterferenceFunction2DLattice::getDecayFunction "const IFTDecayFunction2D* InterferenceFunction2DLattice::getDecayFunction() const
";

%feature("docstring")  InterferenceFunction2DLattice::evaluate "double InterferenceFunction2DLattice::evaluate(const kvector_t q) const final

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  InterferenceFunction2DLattice::getLatticeParameters "Lattice2DParameters InterferenceFunction2DLattice::getLatticeParameters() const
";

%feature("docstring")  InterferenceFunction2DLattice::addParametersToExternalPool "std::string InterferenceFunction2DLattice::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const final

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  InterferenceFunction2DLattice::getParticleDensity "double InterferenceFunction2DLattice::getParticleDensity() const final

Returns the particle density associated with this 2d lattice. 
";


// File: classInterferenceFunction2DParaCrystal.xml
%feature("docstring") InterferenceFunction2DParaCrystal "

Interference function of 2D paracrystal.

C++ includes: InterferenceFunction2DParaCrystal.h
";

%feature("docstring")  InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(double length_1, double length_2, double alpha_lattice, double xi=0.0, double damping_length=0.0)

Parameters:
-----------

length_1: 
Length of first lattice basis vector.

length_2: 
Length of second lattice basis vector.

alpha_lattice: 
Angle between the lattice basis vectors.

xi: 
Angle between first basis vector and the x-axis of incoming beam.

damping_length: 
Damping length for removing delta function singularity at q=0. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal() final
";

%feature("docstring")  InterferenceFunction2DParaCrystal::clone "InterferenceFunction2DParaCrystal * InterferenceFunction2DParaCrystal::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::accept "void InterferenceFunction2DParaCrystal::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::to_str "std::string InterferenceFunction2DParaCrystal::to_str(int indent=0) const final

Returns textual representation of this and its descendants. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setDomainSizes "void InterferenceFunction2DParaCrystal::setDomainSizes(double size_1, double size_2)

Sets the sizes of coherence domains.

Parameters:
-----------

size_1: 
size in first lattice direction

size_2: 
size in second lattice direction 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setProbabilityDistributions "void InterferenceFunction2DParaCrystal::setProbabilityDistributions(const IFTDistribution2D &pdf_1, const IFTDistribution2D &pdf_2)

Sets the probability distributions (Fourier transformed) for the two lattice directions.

Parameters:
-----------

pdf_1: 
probability distribution in first lattice direction

pdf_2: 
probability distribution in second lattice direction 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::evaluate "double InterferenceFunction2DParaCrystal::evaluate(const kvector_t q) const final

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getDomainSizes "std::vector< double > InterferenceFunction2DParaCrystal::getDomainSizes() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getProbabilityDistributions "std::vector< const IFTDistribution2D * > InterferenceFunction2DParaCrystal::getProbabilityDistributions() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setIntegrationOverXi "void InterferenceFunction2DParaCrystal::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getIntegrationOverXi "bool InterferenceFunction2DParaCrystal::getIntegrationOverXi() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getDampingLength "double InterferenceFunction2DParaCrystal::getDampingLength() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getLatticeParameters "Lattice2DParameters InterferenceFunction2DParaCrystal::getLatticeParameters() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::addParametersToExternalPool "std::string InterferenceFunction2DParaCrystal::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const final

Adds parameters from local pool to external pool and recursively calls its direct children.

Copies local parameters to external_pool, under name \"path/<name>copy_number/\". 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getParticleDensity "double InterferenceFunction2DParaCrystal::getParticleDensity() const final

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";


// File: classInterferenceFunctionNone.xml
%feature("docstring") InterferenceFunctionNone "

Default interference function (i.e. absence of any interference).

C++ includes: InterferenceFunctionNone.h
";

%feature("docstring")  InterferenceFunctionNone::InterferenceFunctionNone "InterferenceFunctionNone::InterferenceFunctionNone()
";

%feature("docstring")  InterferenceFunctionNone::clone "InterferenceFunctionNone* InterferenceFunctionNone::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionNone::accept "void InterferenceFunctionNone::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionNone::evaluate "double InterferenceFunctionNone::evaluate(const kvector_t) const final

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";


// File: classInterferenceFunctionRadialParaCrystal.xml
%feature("docstring") InterferenceFunctionRadialParaCrystal "

Interference function of radial paracrystal.

C++ includes: InterferenceFunctionRadialParaCrystal.h
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal "InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal(double peak_distance, double damping_length=0.0)
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::clone "InterferenceFunctionRadialParaCrystal * InterferenceFunctionRadialParaCrystal::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::accept "void InterferenceFunctionRadialParaCrystal::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::to_str "std::string InterferenceFunctionRadialParaCrystal::to_str(int indent=0) const final

Returns textual representation of this and its descendants. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setKappa "void InterferenceFunctionRadialParaCrystal::setKappa(double kappa)
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getKappa "double InterferenceFunctionRadialParaCrystal::getKappa() const final

Retrieves the size-distance coupling constant (default 0.0) 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setDomainSize "void InterferenceFunctionRadialParaCrystal::setDomainSize(double size)
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getDomainSize "double InterferenceFunctionRadialParaCrystal::getDomainSize() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::evaluate "double InterferenceFunctionRadialParaCrystal::evaluate(const kvector_t q) const final

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::FTPDF "complex_t InterferenceFunctionRadialParaCrystal::FTPDF(double qpar) const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setProbabilityDistribution "void InterferenceFunctionRadialParaCrystal::setProbabilityDistribution(const IFTDistribution1D &pdf)
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getProbabilityDistribution "const IFTDistribution1D* InterferenceFunctionRadialParaCrystal::getProbabilityDistribution() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getPeakDistance "double InterferenceFunctionRadialParaCrystal::getPeakDistance() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getDampingLength "double InterferenceFunctionRadialParaCrystal::getDampingLength() const
";


// File: classIObservable.xml
%feature("docstring") IObservable "

Observable interface from Observer pattern, for 1:n object dependencies.

C++ includes: IObserver.h
";

%feature("docstring")  IObservable::~IObservable "virtual IObservable::~IObservable()
";

%feature("docstring")  IObservable::attachObserver "void IObservable::attachObserver(observer_t obj)

attach observer to the list of observers 
";

%feature("docstring")  IObservable::notifyObservers "void IObservable::notifyObservers()

notify observers about change in status 
";


// File: classIObserver.xml
%feature("docstring") IObserver "

Observer interface from Observer pattern, for 1:n object dependencies.

C++ includes: IObserver.h
";

%feature("docstring")  IObserver::~IObserver "virtual IObserver::~IObserver()
";

%feature("docstring")  IObserver::notify "virtual void IObserver::notify(IObservable *subject)=0

method which is used by observable subject to notify change in status 
";


// File: classIOutputDataReadStrategy.xml
%feature("docstring") IOutputDataReadStrategy "

Interface for reading strategy of  OutputData from file.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  IOutputDataReadStrategy::~IOutputDataReadStrategy "virtual IOutputDataReadStrategy::~IOutputDataReadStrategy()
";

%feature("docstring")  IOutputDataReadStrategy::readOutputData "virtual OutputData<double>* IOutputDataReadStrategy::readOutputData(std::istream &input_stream)=0
";


// File: classIOutputDataWriteStrategy.xml
%feature("docstring") IOutputDataWriteStrategy "

Strategy interface to write OututData in file.

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  IOutputDataWriteStrategy::IOutputDataWriteStrategy "IOutputDataWriteStrategy::IOutputDataWriteStrategy()
";

%feature("docstring")  IOutputDataWriteStrategy::~IOutputDataWriteStrategy "virtual IOutputDataWriteStrategy::~IOutputDataWriteStrategy()
";

%feature("docstring")  IOutputDataWriteStrategy::writeOutputData "virtual void IOutputDataWriteStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)=0
";


// File: classIParameter.xml
%feature("docstring") IParameter "

Pure virtual base class for parameter wrapper classes  RealParameter, ComponentParameter. Holds a pointer to the wrapped parameter, a name, and a callback function to be called when the parameter is changed. This class is templated on the data type of the wrapped parameter.

C++ includes: IParameter.h
";

%feature("docstring")  IParameter::IParameter "IParameter< T >::IParameter()=delete
";

%feature("docstring")  IParameter::IParameter "IParameter< T >::IParameter(const std::string &name, volatile T *data, const std::string &parent_name, const std::function< void()> &onChange)
";

%feature("docstring")  IParameter::clone "virtual IParameter* IParameter< T >::clone(const std::string &new_name=\"\") const =0
";

%feature("docstring")  IParameter::isNull "virtual bool IParameter< T >::isNull() const

Returns true if wrapped parameter was not initialized with proper real value. 
";

%feature("docstring")  IParameter::getData "volatile T& IParameter< T >::getData() const
";

%feature("docstring")  IParameter::setData "void IParameter< T >::setData(volatile T &data)
";


// File: classIParameterized.xml
%feature("docstring") IParameterized "

Manages a local parameter pool, and a tree of child pools.

C++ includes: IParameterized.h
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const std::string &name=\"\")
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const IParameterized &other)
";

%feature("docstring")  IParameterized::~IParameterized "IParameterized::~IParameterized() override
";

%feature("docstring")  IParameterized::getParameterPool "ParameterPool* IParameterized::getParameterPool() const

Returns pointer to the parameter pool. 
";

%feature("docstring")  IParameterized::createParameterTree "ParameterPool * IParameterized::createParameterTree()

Creates new parameter pool, with all local parameters and those of its children. 
";

%feature("docstring")  IParameterized::printParameters "void IParameterized::printParameters()
";

%feature("docstring")  IParameterized::registerParameter "RealParameter & IParameterized::registerParameter(const std::string &name, double *parpointer)
";

%feature("docstring")  IParameterized::setParameterValue "void IParameterized::setParameterValue(const std::string &name, double value)
";

%feature("docstring")  IParameterized::getParameter "RealParameter * IParameterized::getParameter(const std::string &name) const

Returns parameter with given 'name'. 
";

%feature("docstring")  IParameterized::addParametersToExternalPool "std::string IParameterized::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children.

Copies local parameters to external_pool, under name \"path/<name>copy_number/\". 
";


// File: classIParticle.xml
%feature("docstring") IParticle "

Pure virtual base class for  Particle,  ParticleComposition,  ParticleCoreShell,  MesoCrystal. Provides position/rotation and form factor. Abundance is inherited from  IAbstractParticle.

C++ includes: IParticle.h
";

%feature("docstring")  IParticle::~IParticle "virtual IParticle::~IParticle()
";

%feature("docstring")  IParticle::clone "virtual IParticle* IParticle::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IParticle::cloneInvertB "virtual IParticle* IParticle::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IParticle::accept "virtual void IParticle::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  IParticle::createFormFactor "IFormFactor * IParticle::createFormFactor() const

Create a form factor for this particle. 
";

%feature("docstring")  IParticle::createTransformedFormFactor "virtual IFormFactor* IParticle::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const =0

Create a form factor for this particle with an extra transformation. 
";

%feature("docstring")  IParticle::getPosition "kvector_t IParticle::getPosition() const

Returns particle position. 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(kvector_t position)

Sets particle position. 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(double x, double y, double z)

Sets particle position. 
";

%feature("docstring")  IParticle::getRotation "const IRotation * IParticle::getRotation() const

Returns rotation object. 
";

%feature("docstring")  IParticle::setRotation "void IParticle::setRotation(const IRotation &rotation)

Sets transformation. 
";

%feature("docstring")  IParticle::applyRotation "void IParticle::applyRotation(const IRotation &rotation)

Applies transformation by composing it with the existing one. 
";

%feature("docstring")  IParticle::applyTranslation "void IParticle::applyTranslation(kvector_t displacement)

Applies extra translation by adding it to the current one. 
";


// File: classIPixelMap.xml
%feature("docstring") IPixelMap "

Interface for a function that maps [0,1]x[0,1] to the kvectors in a pixel.

C++ includes: IPixelMap.h
";

%feature("docstring")  IPixelMap::~IPixelMap "virtual IPixelMap::~IPixelMap()
";

%feature("docstring")  IPixelMap::clone "virtual IPixelMap* IPixelMap::clone() const =0
";

%feature("docstring")  IPixelMap::createZeroSizeMap "virtual IPixelMap* IPixelMap::createZeroSizeMap(double x, double y) const =0
";

%feature("docstring")  IPixelMap::getK "virtual kvector_t IPixelMap::getK(double x, double y, double wavelength) const =0
";

%feature("docstring")  IPixelMap::getIntegrationFactor "virtual double IPixelMap::getIntegrationFactor(double x, double y) const =0
";

%feature("docstring")  IPixelMap::getSolidAngle "virtual double IPixelMap::getSolidAngle() const =0
";


// File: classIResolutionFunction2D.xml
%feature("docstring") IResolutionFunction2D "

Interface providing two-dimensional resolution function.

C++ includes: IResolutionFunction2D.h
";

%feature("docstring")  IResolutionFunction2D::~IResolutionFunction2D "virtual IResolutionFunction2D::~IResolutionFunction2D()
";

%feature("docstring")  IResolutionFunction2D::evaluateCDF "virtual double IResolutionFunction2D::evaluateCDF(double x, double y) const =0
";

%feature("docstring")  IResolutionFunction2D::clone "virtual IResolutionFunction2D* IResolutionFunction2D::clone() const =0
";


// File: classIRotation.xml
%feature("docstring") IRotation "

must be subclass of sample, because it can be registered as a child in  ICompositeSample

An interface for classes representing a rotation.

C++ includes: Rotations.h
";

%feature("docstring")  IRotation::~IRotation "virtual IRotation::~IRotation()
";

%feature("docstring")  IRotation::clone "virtual IRotation* IRotation::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IRotation::cloneInvertB "IRotation* IRotation::cloneInvertB() const final

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IRotation::createInverse "virtual IRotation* IRotation::createInverse() const =0

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  IRotation::accept "void IRotation::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IRotation::getTransform3D "virtual Transform3D IRotation::getTransform3D() const =0

Returns transformation. 
";

%feature("docstring")  IRotation::isIdentity "bool IRotation::isIdentity() const

Returns true if roation matrix is identity matrix (no rotations) 
";


// File: classIRoughness.xml
%feature("docstring") IRoughness "

Interface to equip an interface with a roughness.

C++ includes: IRoughness.h
";

%feature("docstring")  IRoughness::IRoughness "IRoughness::IRoughness()
";

%feature("docstring")  IRoughness::~IRoughness "virtual IRoughness::~IRoughness()
";

%feature("docstring")  IRoughness::accept "virtual void IRoughness::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";


// File: classISample.xml
%feature("docstring") ISample "

Pure virtual base class for sample components and properties related to scattering.

Inherited by  ICompositeSample,  IFormFactor,  IInterferenceFunction,  IRoughness,  IRotation. So it is much more basic and abstract than the name \"ISample\" suggests.

Since  ICompositeSample contains a vector of  ISample's, we provide here some machinery for iterating through a tree (getMaterial, containedMaterials, containedSubclasses, ..). The functions getChildren and size, completely trivial here, become meaningful through their overloads in  ICompositeSample.

C++ includes: ISample.h
";

%feature("docstring")  ISample::clone "ISample* ISample::clone() const override=0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ISample::cloneInvertB "ISample * ISample::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ISample::accept "virtual void ISample::accept(ISampleVisitor *p_visitor) const =0

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  ISample::to_str "std::string ISample::to_str(int indent=0) const

Returns textual representation of this and its descendants. 
";

%feature("docstring")  ISample::getMaterial "virtual const IMaterial* ISample::getMaterial() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  ISample::getAmbientMaterial "virtual const IMaterial* ISample::getAmbientMaterial() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  ISample::containedMaterials "std::vector< const IMaterial * > ISample::containedMaterials() const

Returns set of unique materials contained in this  ISample. 
";

%feature("docstring")  ISample::getChildren "virtual std::vector<const ISample*> ISample::getChildren() const

Returns a vector of children. 
";

%feature("docstring")  ISample::size "virtual size_t ISample::size() const

Returns number of children. 
";

%feature("docstring")  ISample::containedSubclass "std::vector< const T * > ISample::containedSubclass() const

Returns vector of children of type T. 
";


// File: classISampleIteratorStrategy.xml
%feature("docstring") ISampleIteratorStrategy "";

%feature("docstring")  ISampleIteratorStrategy::~ISampleIteratorStrategy "virtual ISampleIteratorStrategy::~ISampleIteratorStrategy()
";

%feature("docstring")  ISampleIteratorStrategy::clone "virtual ISampleIteratorStrategy* ISampleIteratorStrategy::clone() const =0
";

%feature("docstring")  ISampleIteratorStrategy::first "virtual IteratorMemento ISampleIteratorStrategy::first(const ISample *p_root)=0
";

%feature("docstring")  ISampleIteratorStrategy::next "virtual void ISampleIteratorStrategy::next(IteratorMemento &iterator_stack) const =0
";

%feature("docstring")  ISampleIteratorStrategy::isDone "virtual bool ISampleIteratorStrategy::isDone(IteratorMemento &iterator_stack) const =0
";


// File: classISampleVisitor.xml
%feature("docstring") ISampleVisitor "

From visitor pattern to achieve double dispatch.

Visitor interface to visit  ISample objects.

C++ includes: ISampleVisitor.h
";

%feature("docstring")  ISampleVisitor::ISampleVisitor "ISampleVisitor::ISampleVisitor()
";

%feature("docstring")  ISampleVisitor::~ISampleVisitor "virtual ISampleVisitor::~ISampleVisitor()
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ISample *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ICompositeSample *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IClusteredParticles *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const Crystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ILayout *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleLayout *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const Layer *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const LayerInterface *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const MultiLayer *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IAbstractParticle *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IParticle *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const Particle *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleDistribution *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleComposition *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const MesoCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleCoreShell *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IFormFactor *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IFormFactorBorn *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IFormFactorDecorator *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorAnisoPyramid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorBox *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCone *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCone6 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCuboctahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCylinder *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDodecahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorEllipsoidalCylinder *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorFullSphere *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorFullSpheroid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorGauss *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorHemiEllipsoid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorIcosahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorLongBoxGauss *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorLongBoxLorentz *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorLorentz *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorPrism3 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorPrism6 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorPyramid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorRipple1 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorRipple2 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorSphereGaussianRadius *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorSphereLogNormalRadius *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTetrahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTrivial *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTruncatedCube *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTruncatedSphere *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTruncatedSpheroid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDWBA *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDWBAPol *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorWeighted *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorDebyeWaller *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorFactor *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorMaterial *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorPositionFactor *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorRotation *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IInterferenceFunction *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunction1DLattice *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunctionRadialParaCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunction2DLattice *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunction2DParaCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunctionNone *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IRoughness *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const LayerRoughness *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IRotation *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationX *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationY *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationZ *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationEuler *)
";

%feature("docstring")  ISampleVisitor::visitEnter "bool ISampleVisitor::visitEnter(const ICompositeSample *)
";

%feature("docstring")  ISampleVisitor::visitLeave "bool ISampleVisitor::visitLeave(const ICompositeSample *)
";

%feature("docstring")  ISampleVisitor::getLevel "int ISampleVisitor::getLevel() const

return current level of the visitor in the composite hierarchy 
";

%feature("docstring")  ISampleVisitor::setLevel "void ISampleVisitor::setLevel(int level)

set current level of the visitor in the composite hierarchy 
";


// File: classISelectionRule.xml
%feature("docstring") ISelectionRule "

Pure virtual base class for selection rules.

C++ includes: ISelectionRule.h
";

%feature("docstring")  ISelectionRule::~ISelectionRule "virtual ISelectionRule::~ISelectionRule()
";

%feature("docstring")  ISelectionRule::clone "virtual ISelectionRule* ISelectionRule::clone() const =0
";

%feature("docstring")  ISelectionRule::coordinateSelected "virtual bool ISelectionRule::coordinateSelected(const ivector_t &coordinate) const =0
";


// File: classIsGISAXS08BBuilder.xml
%feature("docstring") IsGISAXS08BBuilder "

Builds sample: 2D paracrystal lattice with isotropic pdfs (IsGISAXS example #8)

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  IsGISAXS08BBuilder::IsGISAXS08BBuilder "IsGISAXS08BBuilder::IsGISAXS08BBuilder()
";

%feature("docstring")  IsGISAXS08BBuilder::buildSample "MultiLayer * IsGISAXS08BBuilder::buildSample() const
";


// File: classIsGISAXSDetector.xml
%feature("docstring") IsGISAXSDetector "

A spherical detector used for validation with IsGISAXS results.

C++ includes: IsGISAXSDetector.h
";

%feature("docstring")  IsGISAXSDetector::IsGISAXSDetector "IsGISAXSDetector::IsGISAXSDetector()
";

%feature("docstring")  IsGISAXSDetector::IsGISAXSDetector "IsGISAXSDetector::IsGISAXSDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)
";

%feature("docstring")  IsGISAXSDetector::IsGISAXSDetector "IsGISAXSDetector::IsGISAXSDetector(const IsGISAXSDetector &other)
";

%feature("docstring")  IsGISAXSDetector::clone "IsGISAXSDetector * IsGISAXSDetector::clone() const override
";


// File: classGeometry_1_1IShape2D.xml
%feature("docstring") Geometry::IShape2D "

Basic class for all shapes in 2D.

C++ includes: IShape2D.h
";

%feature("docstring")  Geometry::IShape2D::IShape2D "Geometry::IShape2D::IShape2D(const std::string &name)
";

%feature("docstring")  Geometry::IShape2D::clone "virtual IShape2D* Geometry::IShape2D::clone() const =0
";

%feature("docstring")  Geometry::IShape2D::contains "virtual bool Geometry::IShape2D::contains(double x, double y) const =0

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::IShape2D::contains "virtual bool Geometry::IShape2D::contains(const Bin1D &binx, const Bin1D &biny) const =0

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";


// File: classIShareable.xml
%feature("docstring") IShareable "

Dummy interface used to construct INamedShared and IParameterizedShared.

C++ includes: IShareable.h
";


// File: classISingleton.xml
%feature("docstring") ISingleton "

Base class for singletons.

C++ includes: ISingleton.h
";


// File: classISpecularInfoMap.xml
%feature("docstring") ISpecularInfoMap "

Interface class providing access to the reflection and transmittion coefficients.

C++ includes: ISpecularInfoMap.h
";

%feature("docstring")  ISpecularInfoMap::ISpecularInfoMap "ISpecularInfoMap::ISpecularInfoMap()
";

%feature("docstring")  ISpecularInfoMap::ISpecularInfoMap "ISpecularInfoMap::ISpecularInfoMap(const ISpecularInfoMap &other)=delete
";

%feature("docstring")  ISpecularInfoMap::~ISpecularInfoMap "virtual ISpecularInfoMap::~ISpecularInfoMap()
";

%feature("docstring")  ISpecularInfoMap::clone "virtual ISpecularInfoMap* ISpecularInfoMap::clone() const =0
";

%feature("docstring")  ISpecularInfoMap::getOutCoefficients "virtual const ILayerRTCoefficients* ISpecularInfoMap::getOutCoefficients(const SimulationElement &sim_element) const =0

Retrieves the amplitude coefficients for the given angles. 
";

%feature("docstring")  ISpecularInfoMap::getInCoefficients "virtual const ILayerRTCoefficients* ISpecularInfoMap::getInCoefficients(const SimulationElement &sim_element) const =0

Retrieves the amplitude coefficients for the given angles. 
";


// File: classISquaredFunction.xml
%feature("docstring") ISquaredFunction "

Interface providing measures for deviation between two values.

Used By  ChiSquaredModule for chi2 calculations

C++ includes: ISquaredFunction.h
";

%feature("docstring")  ISquaredFunction::ISquaredFunction "ISquaredFunction::ISquaredFunction()
";

%feature("docstring")  ISquaredFunction::~ISquaredFunction "virtual ISquaredFunction::~ISquaredFunction()
";

%feature("docstring")  ISquaredFunction::clone "virtual ISquaredFunction* ISquaredFunction::clone() const =0
";

%feature("docstring")  ISquaredFunction::calculateSquaredDifference "virtual double ISquaredFunction::calculateSquaredDifference(double real_value, double simulated_value) const =0
";

%feature("docstring")  ISquaredFunction::calculateSquaredError "virtual double ISquaredFunction::calculateSquaredError(double real_value, double simulated_value=0.0) const =0
";


// File: classIteratorMemento.xml
%feature("docstring") IteratorMemento "

Holds all iterator states encountered for  SampleTreeIterator.

C++ includes: SampleTreeIterator.h
";

%feature("docstring")  IteratorMemento::IteratorMemento "IteratorMemento::IteratorMemento()
";

%feature("docstring")  IteratorMemento::~IteratorMemento "virtual IteratorMemento::~IteratorMemento()
";

%feature("docstring")  IteratorMemento::push_state "void IteratorMemento::push_state(const IteratorState &state)
";

%feature("docstring")  IteratorMemento::pop_state "void IteratorMemento::pop_state()
";

%feature("docstring")  IteratorMemento::get_state "IteratorState& IteratorMemento::get_state()
";

%feature("docstring")  IteratorMemento::empty "bool IteratorMemento::empty() const
";

%feature("docstring")  IteratorMemento::reset "void IteratorMemento::reset()
";

%feature("docstring")  IteratorMemento::getCurrent "const ISample* IteratorMemento::getCurrent()
";

%feature("docstring")  IteratorMemento::next "void IteratorMemento::next()
";

%feature("docstring")  IteratorMemento::size "size_t IteratorMemento::size() const
";


// File: classIteratorState.xml
%feature("docstring") IteratorState "

Holds state of iterator at single level for  SampleTreeIterator.

C++ includes: SampleTreeIterator.h
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(const ISample *single_element)
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(std::vector< const ISample *> samples)
";

%feature("docstring")  IteratorState::~IteratorState "virtual IteratorState::~IteratorState()
";

%feature("docstring")  IteratorState::getCurrent "const ISample* IteratorState::getCurrent() const
";

%feature("docstring")  IteratorState::isEnd "bool IteratorState::isEnd() const
";

%feature("docstring")  IteratorState::next "void IteratorState::next()
";


// File: classLabelMap.xml
%feature("docstring") LabelMap "";

%feature("docstring")  LabelMap::LabelMap "LabelMap< Key >::LabelMap()
";

%feature("docstring")  LabelMap::~LabelMap "virtual LabelMap< Key >::~LabelMap()
";

%feature("docstring")  LabelMap::clear "void LabelMap< Key >::clear()
";

%feature("docstring")  LabelMap::begin "const_iterator LabelMap< Key >::begin() const
";

%feature("docstring")  LabelMap::end "const_iterator LabelMap< Key >::end() const
";

%feature("docstring")  LabelMap::begin "iterator LabelMap< Key >::begin()
";

%feature("docstring")  LabelMap::end "iterator LabelMap< Key >::end()
";

%feature("docstring")  LabelMap::size "size_t LabelMap< Key >::size()
";

%feature("docstring")  LabelMap::insert "void LabelMap< Key >::insert(const Key &key, const std::string &object)
";

%feature("docstring")  LabelMap::find "const iterator LabelMap< Key >::find(const Key &key) const
";

%feature("docstring")  LabelMap::find "iterator LabelMap< Key >::find(const Key &key)
";

%feature("docstring")  LabelMap::erase "void LabelMap< Key >::erase(const Key &key)
";

%feature("docstring")  LabelMap::value "const std::string& LabelMap< Key >::value(const Key &key)
";


// File: classLargeCylindersInDWBABuilder.xml
%feature("docstring") LargeCylindersInDWBABuilder "

Builds sample with large cylinders for MC integration tests.

C++ includes: CylindersBuilder.h
";

%feature("docstring")  LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder "LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder()
";

%feature("docstring")  LargeCylindersInDWBABuilder::buildSample "MultiLayer * LargeCylindersInDWBABuilder::buildSample() const
";


// File: classLattice.xml
%feature("docstring") Lattice "

A lattice with three basis vectors.

C++ includes: Lattice.h
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice()=delete
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice(const kvector_t a1, const kvector_t a2, const kvector_t a3)
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice(const Lattice &lattice)
";

%feature("docstring")  Lattice::~Lattice "Lattice::~Lattice()
";

%feature("docstring")  Lattice::createTransformedLattice "Lattice Lattice::createTransformedLattice(const Transform3D &transform) const

Create transformed lattice. 
";

%feature("docstring")  Lattice::initialize "void Lattice::initialize() const

Initializes cached data. 
";

%feature("docstring")  Lattice::getBasisVectorA "kvector_t Lattice::getBasisVectorA() const

Returns basis vector a. 
";

%feature("docstring")  Lattice::getBasisVectorB "kvector_t Lattice::getBasisVectorB() const

Returns basis vector b. 
";

%feature("docstring")  Lattice::getBasisVectorC "kvector_t Lattice::getBasisVectorC() const

Returns basis vector c. 
";

%feature("docstring")  Lattice::getVolume "double Lattice::getVolume() const

Returns the volume of the unit cell. 
";

%feature("docstring")  Lattice::getReciprocalLatticeBasis "void Lattice::getReciprocalLatticeBasis(kvector_t b1, kvector_t b2, kvector_t b3) const

Returns the reciprocal basis vectors. 
";

%feature("docstring")  Lattice::getNearestLatticeVectorCoordinates "ivector_t Lattice::getNearestLatticeVectorCoordinates(const kvector_t vector_in) const

Returns the nearest lattice point from a given vector. 
";

%feature("docstring")  Lattice::getNearestReciprocalLatticeVectorCoordinates "ivector_t Lattice::getNearestReciprocalLatticeVectorCoordinates(const kvector_t vector_in) const

Returns the nearest reciprocal lattice point from a given vector. 
";

%feature("docstring")  Lattice::reciprocalLatticeVectorsWithinRadius "std::vector< kvector_t > Lattice::reciprocalLatticeVectorsWithinRadius(const kvector_t input_vector, double radius) const

Computes a list of reciprocal lattice vectors within a specified distance of a given vector. 
";

%feature("docstring")  Lattice::setSelectionRule "void Lattice::setSelectionRule(const ISelectionRule &p_selection_rule)

Sets a selection rule for the reciprocal vectors. 
";


// File: classLattice1DBuilder.xml
%feature("docstring") Lattice1DBuilder "

Builds sample: cylinders with 1DDL structure factor.

C++ includes: LatticeBuilder.h
";

%feature("docstring")  Lattice1DBuilder::Lattice1DBuilder "Lattice1DBuilder::Lattice1DBuilder()
";

%feature("docstring")  Lattice1DBuilder::buildSample "MultiLayer * Lattice1DBuilder::buildSample() const
";


// File: classLattice1DParameters.xml
%feature("docstring") Lattice1DParameters "

Basic parameters of a one-dimensional lattice.

C++ includes: Lattice1DParameters.h
";

%feature("docstring")  Lattice1DParameters::Lattice1DParameters "Lattice1DParameters::Lattice1DParameters()
";

%feature("docstring")  Lattice1DParameters::Lattice1DParameters "Lattice1DParameters::Lattice1DParameters(double length, double xi)

Parameters:
-----------

length: 
 Lattice constant.

xi: 
TODO: seems unused; explain or remove 
";


// File: classLattice2DParameters.xml
%feature("docstring") Lattice2DParameters "

Additional parameters for 2D lattice.

C++ includes: Lattice2DParameters.h
";

%feature("docstring")  Lattice2DParameters::Lattice2DParameters "Lattice2DParameters::Lattice2DParameters()
";

%feature("docstring")  Lattice2DParameters::getUnitCellArea "double Lattice2DParameters::getUnitCellArea() const
";


// File: classLayer.xml
%feature("docstring") Layer "

A layer, with thickness (in nanometer) and material.

C++ includes: Layer.h
";

%feature("docstring")  Layer::Layer "Layer::Layer()
";

%feature("docstring")  Layer::Layer "Layer::Layer(const IMaterial &material, double thickness=0)
";

%feature("docstring")  Layer::~Layer "Layer::~Layer() final
";

%feature("docstring")  Layer::clone "Layer* Layer::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  Layer::cloneInvertB "Layer * Layer::cloneInvertB() const final

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  Layer::accept "void Layer::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  Layer::to_str "std::string Layer::to_str(int indent=0) const final

Returns textual representation of this and its descendants. 
";

%feature("docstring")  Layer::setThickness "void Layer::setThickness(double thickness)

Sets layer thickness in nanometers. 
";

%feature("docstring")  Layer::getThickness "double Layer::getThickness() const
";

%feature("docstring")  Layer::setMaterial "void Layer::setMaterial(const IMaterial &material)

Sets  material of the layer. 
";

%feature("docstring")  Layer::getMaterial "const IMaterial* Layer::getMaterial() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Layer::getRefractiveIndex "complex_t Layer::getRefractiveIndex() const
";

%feature("docstring")  Layer::getRefractiveIndex2 "complex_t Layer::getRefractiveIndex2() const

squared refractive index 
";

%feature("docstring")  Layer::addLayout "void Layer::addLayout(const ILayout &decoration)
";

%feature("docstring")  Layer::getNumberOfLayouts "size_t Layer::getNumberOfLayouts() const
";

%feature("docstring")  Layer::getLayout "const ILayout * Layer::getLayout(size_t i) const
";

%feature("docstring")  Layer::hasComputation "bool Layer::hasComputation() const

Returns true if decoration is present. 
";

%feature("docstring")  Layer::getTotalParticleSurfaceDensity "double Layer::getTotalParticleSurfaceDensity(size_t layout_index) const
";

%feature("docstring")  Layer::getTotalAbundance "double Layer::getTotalAbundance() const
";

%feature("docstring")  Layer::setNumberOfLayers "void Layer::setNumberOfLayers(size_t n_layers)
";

%feature("docstring")  Layer::getNumberOfLayers "size_t Layer::getNumberOfLayers() const
";


// File: classLayerInterface.xml
%feature("docstring") LayerInterface "

Interface between two layers, possibly with roughness.

C++ includes: LayerInterface.h
";

%feature("docstring")  LayerInterface::~LayerInterface "LayerInterface::~LayerInterface()
";

%feature("docstring")  LayerInterface::clone "LayerInterface * LayerInterface::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  LayerInterface::accept "virtual void LayerInterface::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  LayerInterface::setLayerTop "void LayerInterface::setLayerTop(const Layer *p_layer_top)

Sets link to the layer above the interface. 
";

%feature("docstring")  LayerInterface::setLayerBottom "void LayerInterface::setLayerBottom(const Layer *p_layer_bottom)

Sets link to the layer below the interface. 
";

%feature("docstring")  LayerInterface::setLayersTopBottom "void LayerInterface::setLayersTopBottom(const Layer *p_layer_top, const Layer *p_layer_bottom)

Sets links to the layers above and below the interface. 
";

%feature("docstring")  LayerInterface::setRoughness "void LayerInterface::setRoughness(const LayerRoughness &roughness)

Sets roughness of the interface. 
";

%feature("docstring")  LayerInterface::getRoughness "const LayerRoughness* LayerInterface::getRoughness() const

Returns roughness of the interface. 
";

%feature("docstring")  LayerInterface::getLayerTop "const Layer* LayerInterface::getLayerTop() const

Returns top layer. 
";

%feature("docstring")  LayerInterface::getLayerBottom "const Layer* LayerInterface::getLayerBottom() const

Returns bottom layer. 
";


// File: classLayerRoughness.xml
%feature("docstring") LayerRoughness "

A Roughness of interface between two layers.

Based on the article D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995 \"X-ray reflection and transmission by rough surfaces\"

C++ includes: LayerRoughness.h
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness()
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness(double sigma, double hurstParameter, double latteralCorrLength)
";

%feature("docstring")  LayerRoughness::clone "LayerRoughness* LayerRoughness::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  LayerRoughness::accept "virtual void LayerRoughness::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  LayerRoughness::getSpectralFun "double LayerRoughness::getSpectralFun(const kvector_t kvec) const

Returns power spectral density of the surface roughness.

Power spectral density of the surface roughness is a result of two-dimensional Fourier transform of the correlation function of the roughness profile.

Based on the article D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995 \"X-ray reflection and transmission by rough surfaces\" 
";

%feature("docstring")  LayerRoughness::getCorrFun "double LayerRoughness::getCorrFun(const kvector_t k) const

Correlation function of the roughness profile. 
";

%feature("docstring")  LayerRoughness::setSigma "void LayerRoughness::setSigma(double sigma)

Sets rms of roughness. 
";

%feature("docstring")  LayerRoughness::getSigma "double LayerRoughness::getSigma() const

Returns rms of roughness. 
";

%feature("docstring")  LayerRoughness::setHurstParameter "void LayerRoughness::setHurstParameter(double hurstParameter)

Sets hurst parameter. It describes how jagged the surface is. 
";

%feature("docstring")  LayerRoughness::getHurstParameter "double LayerRoughness::getHurstParameter() const

Returns hurst parameter. 
";

%feature("docstring")  LayerRoughness::setLatteralCorrLength "void LayerRoughness::setLatteralCorrLength(double latteralCorrLength)

Sets lateral correlation length. 
";

%feature("docstring")  LayerRoughness::getLatteralCorrLength "double LayerRoughness::getLatteralCorrLength() const

Returns latteral correlation length. 
";


// File: classLayerSpecularInfo.xml
%feature("docstring") LayerSpecularInfo "

Holds the amplitude information of the radiation wavefunction in a specific layer for different incoming (outgoing) angles of the beam in the top layer (these amplitudes correspond to the specular part of the neutron wavefunction).

C++ includes: LayerSpecularInfo.h
";

%feature("docstring")  LayerSpecularInfo::LayerSpecularInfo "LayerSpecularInfo::LayerSpecularInfo()
";

%feature("docstring")  LayerSpecularInfo::~LayerSpecularInfo "LayerSpecularInfo::~LayerSpecularInfo() final
";

%feature("docstring")  LayerSpecularInfo::clone "LayerSpecularInfo * LayerSpecularInfo::clone() const final
";

%feature("docstring")  LayerSpecularInfo::addRTCoefficients "void LayerSpecularInfo::addRTCoefficients(ISpecularInfoMap *rt_coefficient_map)

Adds the amplitude coefficients for the (time-reversed) outgoing wavevector with the given angles 
";

%feature("docstring")  LayerSpecularInfo::getOutCoefficients "const ILayerRTCoefficients * LayerSpecularInfo::getOutCoefficients(const SimulationElement &sim_element) const

Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector. 
";

%feature("docstring")  LayerSpecularInfo::getInCoefficients "const ILayerRTCoefficients * LayerSpecularInfo::getInCoefficients(const SimulationElement &sim_element) const

Retrieves the amplitude coefficients for an incoming wavevector. 
";


// File: classLayerStrategyBuilder.xml
%feature("docstring") LayerStrategyBuilder "

Methods to generate a simulation strategy for  DecoratedLayerComputation.

C++ includes: LayerStrategyBuilder.h
";

%feature("docstring")  LayerStrategyBuilder::LayerStrategyBuilder "LayerStrategyBuilder::LayerStrategyBuilder(const Layer &decorated_layer, bool polarized, const SimulationOptions &sim_params, size_t layout_index, const LayerSpecularInfo *specular_info)
";

%feature("docstring")  LayerStrategyBuilder::~LayerStrategyBuilder "LayerStrategyBuilder::~LayerStrategyBuilder()
";

%feature("docstring")  LayerStrategyBuilder::createStrategy "IInterferenceFunctionStrategy * LayerStrategyBuilder::createStrategy() const

Returns a new strategy object that is able to calculate the scattering for fixed k_f. 
";


// File: classLayersWithAbsorptionBuilder.xml
%feature("docstring") LayersWithAbsorptionBuilder "

The  LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part).The middle layer is populated with particles. Requires IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: LayersWithAbsorptionBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder "virtual LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::buildSample "MultiLayer * LayersWithAbsorptionBuilder::buildSample() const
";


// File: classGeometry_1_1Line.xml
%feature("docstring") Geometry::Line "

A line segment.

C++ includes: Line.h
";

%feature("docstring")  Geometry::Line::Line "Geometry::Line::Line(double x1, double y1, double x2, double y2)
";

%feature("docstring")  Geometry::Line::clone "Line* Geometry::Line::clone() const
";

%feature("docstring")  Geometry::Line::contains "bool Geometry::Line::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::Line::contains "bool Geometry::Line::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";


// File: classLLData.xml
%feature("docstring") LLData "

Template class to store data of any type in multi-dimensional space (low-level)

C++ includes: LLData.h
";

%feature("docstring")  LLData::LLData "LLData< T >::LLData(size_t rank, const int *dimensions)
";

%feature("docstring")  LLData::LLData "LLData< T >::LLData(const LLData< T > &right)
";

%feature("docstring")  LLData::~LLData "LLData< T >::~LLData()
";

%feature("docstring")  LLData::meanValues "LLData<double> LLData< T >::meanValues() const
";

%feature("docstring")  LLData::atCoordinate "T & LLData< T >::atCoordinate(int *coordinate)
";

%feature("docstring")  LLData::atCoordinate "const T & LLData< T >::atCoordinate(int *coordinate) const
";

%feature("docstring")  LLData::setAll "void LLData< T >::setAll(const T &value)
";

%feature("docstring")  LLData::scaleAll "void LLData< T >::scaleAll(const T &factor)
";

%feature("docstring")  LLData::getTotalSize "size_t LLData< T >::getTotalSize() const
";

%feature("docstring")  LLData::getRank "size_t LLData< T >::getRank() const
";

%feature("docstring")  LLData::getDimensions "const int* LLData< T >::getDimensions() const
";

%feature("docstring")  LLData::getTotalSum "T LLData< T >::getTotalSum() const
";


// File: classException_1_1LogicErrorException.xml
%feature("docstring") Exception::LogicErrorException "";

%feature("docstring")  Exception::LogicErrorException::LogicErrorException "Exception::LogicErrorException::LogicErrorException(const std::string &message)
";


// File: classMagneticCylindersBuilder.xml
%feature("docstring") MagneticCylindersBuilder "

Builds sample: cylinders with magnetic material and non-zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticCylindersBuilder::MagneticCylindersBuilder "MagneticCylindersBuilder::MagneticCylindersBuilder()
";

%feature("docstring")  MagneticCylindersBuilder::buildSample "MultiLayer * MagneticCylindersBuilder::buildSample() const
";


// File: classMagneticParticleZeroFieldBuilder.xml
%feature("docstring") MagneticParticleZeroFieldBuilder "

Builds sample: cylinders with magnetic material and zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticParticleZeroFieldBuilder::MagneticParticleZeroFieldBuilder "MagneticParticleZeroFieldBuilder::MagneticParticleZeroFieldBuilder()
";

%feature("docstring")  MagneticParticleZeroFieldBuilder::buildSample "MultiLayer * MagneticParticleZeroFieldBuilder::buildSample() const
";


// File: classMainComputation.xml
%feature("docstring") MainComputation "

Performs a single-threaded DWBA computation with given sample and simulation parameters, for a given span of detector bins.

Controlled by the multi-threading machinery in  Simulation::runSingleSimulation().

C++ includes: MainComputation.h
";

%feature("docstring")  MainComputation::MainComputation "MainComputation::MainComputation(const MultiLayer *p_multi_layer, const SimulationOptions &options, ProgressHandler &progress, const std::vector< SimulationElement >::iterator &begin_it, const std::vector< SimulationElement >::iterator &end_it)
";

%feature("docstring")  MainComputation::~MainComputation "MainComputation::~MainComputation()
";

%feature("docstring")  MainComputation::run "void MainComputation::run()
";

%feature("docstring")  MainComputation::isCompleted "bool MainComputation::isCompleted() const
";

%feature("docstring")  MainComputation::getRunMessage "std::string MainComputation::getRunMessage() const
";


// File: classMatrixRTCoefficients.xml
%feature("docstring") MatrixRTCoefficients "

Specular reflection and transmission coefficients in a layer in case of 2x2 matrix interactions between the layers and the scattered particle.

C++ includes: MatrixRTCoefficients.h
";

%feature("docstring")  MatrixRTCoefficients::MatrixRTCoefficients "MatrixRTCoefficients::MatrixRTCoefficients()
";

%feature("docstring")  MatrixRTCoefficients::~MatrixRTCoefficients "virtual MatrixRTCoefficients::~MatrixRTCoefficients()
";

%feature("docstring")  MatrixRTCoefficients::clone "MatrixRTCoefficients * MatrixRTCoefficients::clone() const
";

%feature("docstring")  MatrixRTCoefficients::T1plus "Eigen::Vector2cd MatrixRTCoefficients::T1plus() const

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  MatrixRTCoefficients::R1plus "Eigen::Vector2cd MatrixRTCoefficients::R1plus() const
";

%feature("docstring")  MatrixRTCoefficients::T2plus "Eigen::Vector2cd MatrixRTCoefficients::T2plus() const
";

%feature("docstring")  MatrixRTCoefficients::R2plus "Eigen::Vector2cd MatrixRTCoefficients::R2plus() const
";

%feature("docstring")  MatrixRTCoefficients::T1min "Eigen::Vector2cd MatrixRTCoefficients::T1min() const
";

%feature("docstring")  MatrixRTCoefficients::R1min "Eigen::Vector2cd MatrixRTCoefficients::R1min() const
";

%feature("docstring")  MatrixRTCoefficients::T2min "Eigen::Vector2cd MatrixRTCoefficients::T2min() const
";

%feature("docstring")  MatrixRTCoefficients::R2min "Eigen::Vector2cd MatrixRTCoefficients::R2min() const
";

%feature("docstring")  MatrixRTCoefficients::getKz "Eigen::Vector2cd MatrixRTCoefficients::getKz() const

Returns z-part of the two wavevector eigenmodes. 
";


// File: classMatrixSpecularInfoMap.xml
%feature("docstring") MatrixSpecularInfoMap "

Implementation of  ISpecularInfoMap for matrix valued reflection/transmission coefficients.

C++ includes: MatrixSpecularInfoMap.h
";

%feature("docstring")  MatrixSpecularInfoMap::MatrixSpecularInfoMap "MatrixSpecularInfoMap::MatrixSpecularInfoMap(const MultiLayer *multilayer, int layer)
";

%feature("docstring")  MatrixSpecularInfoMap::~MatrixSpecularInfoMap "MatrixSpecularInfoMap::~MatrixSpecularInfoMap() final
";

%feature("docstring")  MatrixSpecularInfoMap::clone "MatrixSpecularInfoMap * MatrixSpecularInfoMap::clone() const final
";

%feature("docstring")  MatrixSpecularInfoMap::getOutCoefficients "const ILayerRTCoefficients * MatrixSpecularInfoMap::getOutCoefficients(const SimulationElement &sim_element) const final

Retrieves the amplitude coefficients for the given angles. 
";

%feature("docstring")  MatrixSpecularInfoMap::getInCoefficients "const ILayerRTCoefficients * MatrixSpecularInfoMap::getInCoefficients(const SimulationElement &sim_element) const final

Retrieves the amplitude coefficients for the given angles. 
";


// File: classMCMiserIntegrator.xml
%feature("docstring") MCMiserIntegrator "

Template class to use Monte Carlo MISER integration of class member functions.

Wraps an integrator from GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_miser(this, mem_function, dimension)'

Call: 'integrator.integrate(lmin, lmax, data, nbr_points)'

C++ includes: IntegratorMCMiser.h
";


// File: classMesoCrystal.xml
%feature("docstring") MesoCrystal "

A particle with an internal structure of smaller particles.

C++ includes: MesoCrystal.h
";

%feature("docstring")  MesoCrystal::MesoCrystal "MesoCrystal::MesoCrystal(IClusteredParticles *p_particle_structure, IFormFactor *p_form_factor)
";

%feature("docstring")  MesoCrystal::MesoCrystal "MesoCrystal::MesoCrystal(const IClusteredParticles &particle_structure, IFormFactor &form_factor)
";

%feature("docstring")  MesoCrystal::~MesoCrystal "MesoCrystal::~MesoCrystal()
";

%feature("docstring")  MesoCrystal::clone "MesoCrystal * MesoCrystal::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  MesoCrystal::cloneInvertB "MesoCrystal * MesoCrystal::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  MesoCrystal::accept "void MesoCrystal::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  MesoCrystal::setAmbientMaterial "void MesoCrystal::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  MesoCrystal::getAmbientMaterial "const IMaterial * MesoCrystal::getAmbientMaterial() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  MesoCrystal::createTransformedFormFactor "IFormFactor * MesoCrystal::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  MesoCrystal::getClusteredParticles "const IClusteredParticles* MesoCrystal::getClusteredParticles() const

get the internal structure, which is in principle unbounded in space (e.g. an infinite crystal) 
";


// File: classMesoCrystalBuilder.xml
%feature("docstring") MesoCrystalBuilder "

Builds sample: mesocrystals of cylindrical shape composed by spherical nanoparticles.

C++ includes: MesoCrystalBuilder.h
";

%feature("docstring")  MesoCrystalBuilder::MesoCrystalBuilder "MesoCrystalBuilder::MesoCrystalBuilder()
";

%feature("docstring")  MesoCrystalBuilder::~MesoCrystalBuilder "virtual MesoCrystalBuilder::~MesoCrystalBuilder()
";

%feature("docstring")  MesoCrystalBuilder::buildSample "MultiLayer * MesoCrystalBuilder::buildSample() const
";


// File: classMultiLayer.xml
%feature("docstring") MultiLayer "

Our sample model: a stack of layers one below the other.Example of system of 4 layers (3 interfaces):

ambience layer #0 z=getLayerBottomZ(0)=0.0 ------ interface #0 Fe, 20A layer #1 z=getLayerBottomZ(1)=-20.0 ------ interface #1 Cr, 40A layer #2 z=getLayerBottomZ(2)=-60.0 ------ interface #2 substrate layer #3 z=getLayerBottomZ(3)=-60.0

C++ includes: MultiLayer.h
";

%feature("docstring")  MultiLayer::MultiLayer "MultiLayer::MultiLayer()
";

%feature("docstring")  MultiLayer::~MultiLayer "MultiLayer::~MultiLayer()
";

%feature("docstring")  MultiLayer::accept "virtual void MultiLayer::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  MultiLayer::to_str "std::string MultiLayer::to_str(int indent=0) const

Returns textual representation of this and its descendants. 
";

%feature("docstring")  MultiLayer::getNumberOfLayers "size_t MultiLayer::getNumberOfLayers() const
";

%feature("docstring")  MultiLayer::getNumberOfInterfaces "size_t MultiLayer::getNumberOfInterfaces() const
";

%feature("docstring")  MultiLayer::addLayer "void MultiLayer::addLayer(const Layer &p_child)

Adds object to multilayer, overrides from  ISample.

Adds layer with default (zero) roughness. 
";

%feature("docstring")  MultiLayer::addLayerWithTopRoughness "void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)

Adds layer with top roughness. 
";

%feature("docstring")  MultiLayer::getLayer "const Layer* MultiLayer::getLayer(size_t i_layer) const

Returns layer with given index. 
";

%feature("docstring")  MultiLayer::getLayerInterface "const LayerInterface* MultiLayer::getLayerInterface(size_t i_interface) const

Returns layer with given index. 
";

%feature("docstring")  MultiLayer::getLayerBottomZ "double MultiLayer::getLayerBottomZ(size_t i_layer) const

Returns z-coordinate of the layer's bottom. 
";

%feature("docstring")  MultiLayer::getLayerThickness "double MultiLayer::getLayerThickness(size_t i_layer) const

Returns thickness of layer. 
";

%feature("docstring")  MultiLayer::getLayerTopInterface "const LayerInterface * MultiLayer::getLayerTopInterface(size_t i_layer) const

Returns top interface of layer.

Returns pointer to the top interface of the layer. nInterfaces = nLayers-1, first layer in multilayer doesn't have interface. 
";

%feature("docstring")  MultiLayer::getLayerBottomInterface "const LayerInterface * MultiLayer::getLayerBottomInterface(size_t i_layer) const

Returns bottom interface of layer.

Returns pointer to the bottom interface of the layer. 
";

%feature("docstring")  MultiLayer::clear "void MultiLayer::clear()

Destructs allocated objects. 
";

%feature("docstring")  MultiLayer::clone "MultiLayer * MultiLayer::clone() const

Returns alone of multilayer with clones of all layers and recreated interfaces between layers 
";

%feature("docstring")  MultiLayer::cloneInvertB "MultiLayer * MultiLayer::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  MultiLayer::setCrossCorrLength "void MultiLayer::setCrossCorrLength(double crossCorrLength)

Sets cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::getCrossCorrLength "double MultiLayer::getCrossCorrLength() const

Returns cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::getCrossCorrSpectralFun "double MultiLayer::getCrossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const

! correlation function of roughnesses between the interfaces

Fourier transform of the correlation function of roughnesses between the interfaces

Fourier transform of the correlation function of roughnesses between the interfaces j,k - indexes of layers in multilayer whose bottom interfaces we are considering 
";

%feature("docstring")  MultiLayer::setLayerThickness "void MultiLayer::setLayerThickness(size_t i_layer, double thickness)

Sets thickness of layer. 
";

%feature("docstring")  MultiLayer::getIndexOfLayer "int MultiLayer::getIndexOfLayer(const Layer *layer) const

returns layer index 
";

%feature("docstring")  MultiLayer::requiresMatrixRTCoefficients "bool MultiLayer::requiresMatrixRTCoefficients() const

returns true if contains magnetic materials and matrix calculations are required 
";

%feature("docstring")  MultiLayer::zToLayerIndex "size_t MultiLayer::zToLayerIndex(double z_value)

returns layer index corresponding to given global z coordinate 
";

%feature("docstring")  MultiLayer::containsMagneticMaterial "bool MultiLayer::containsMagneticMaterial() const
";

%feature("docstring")  MultiLayer::hasRoughness "bool MultiLayer::hasRoughness() const
";

%feature("docstring")  MultiLayer::totalNofLayouts "size_t MultiLayer::totalNofLayouts() const
";


// File: classMultiLayerWithRoughnessBuilder.xml
%feature("docstring") MultiLayerWithRoughnessBuilder "

Builds sample: layers with correlated roughness.

C++ includes: MultiLayerWithRoughnessBuilder.h
";

%feature("docstring")  MultiLayerWithRoughnessBuilder::MultiLayerWithRoughnessBuilder "MultiLayerWithRoughnessBuilder::MultiLayerWithRoughnessBuilder()
";

%feature("docstring")  MultiLayerWithRoughnessBuilder::buildSample "MultiLayer * MultiLayerWithRoughnessBuilder::buildSample() const
";


// File: classMultipleLayoutBuilder.xml
%feature("docstring") MultipleLayoutBuilder "

Builds sample: mixture of cylinders and prisms without interference using multiple particle layouts.

C++ includes: MultipleLayoutBuilder.h
";

%feature("docstring")  MultipleLayoutBuilder::MultipleLayoutBuilder "MultipleLayoutBuilder::MultipleLayoutBuilder()
";

%feature("docstring")  MultipleLayoutBuilder::buildSample "MultiLayer * MultipleLayoutBuilder::buildSample() const
";


// File: classException_1_1NotImplementedException.xml
%feature("docstring") Exception::NotImplementedException "";

%feature("docstring")  Exception::NotImplementedException::NotImplementedException "Exception::NotImplementedException::NotImplementedException(const std::string &message)
";


// File: classException_1_1NullPointerException.xml
%feature("docstring") Exception::NullPointerException "";

%feature("docstring")  Exception::NullPointerException::NullPointerException "Exception::NullPointerException::NullPointerException(const std::string &message)
";


// File: classOffSpecSimulation.xml
%feature("docstring") OffSpecSimulation "

Main class to run an off-specular simulation.

C++ includes: OffSpecSimulation.h
";

%feature("docstring")  OffSpecSimulation::OffSpecSimulation "OffSpecSimulation::OffSpecSimulation()
";

%feature("docstring")  OffSpecSimulation::OffSpecSimulation "OffSpecSimulation::OffSpecSimulation(const MultiLayer &p_sample)
";

%feature("docstring")  OffSpecSimulation::OffSpecSimulation "OffSpecSimulation::OffSpecSimulation(const std::shared_ptr< class IMultiLayerBuilder > p_sample_builder)
";

%feature("docstring")  OffSpecSimulation::~OffSpecSimulation "OffSpecSimulation::~OffSpecSimulation() final
";

%feature("docstring")  OffSpecSimulation::clone "OffSpecSimulation* OffSpecSimulation::clone() const
";

%feature("docstring")  OffSpecSimulation::prepareSimulation "void OffSpecSimulation::prepareSimulation() final

Put into a clean state for running a simulation. 
";

%feature("docstring")  OffSpecSimulation::numberOfSimulationElements "int OffSpecSimulation::numberOfSimulationElements() const final

Gets the number of elements this simulation needs to calculate. 
";

%feature("docstring")  OffSpecSimulation::getDetectorIntensity "OutputData<double>* OffSpecSimulation::getDetectorIntensity(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns clone of the detector intensity map. 
";

%feature("docstring")  OffSpecSimulation::getIntensityData "Histogram2D * OffSpecSimulation::getIntensityData() const

Returns clone of the detector intensity map in the form of 2D histogram. 
";

%feature("docstring")  OffSpecSimulation::setBeamParameters "void OffSpecSimulation::setBeamParameters(double lambda, const IAxis &alpha_axis, double phi_i)

Sets beam parameters from here (forwarded to  Instrument) 
";

%feature("docstring")  OffSpecSimulation::setDetectorParameters "void OffSpecSimulation::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  OffSpecSimulation::addParametersToExternalPool "std::string OffSpecSimulation::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const final

Adds parameters from local pool to external pool and recursively calls its direct children. 
";


// File: classException_1_1OutOfBoundsException.xml
%feature("docstring") Exception::OutOfBoundsException "";

%feature("docstring")  Exception::OutOfBoundsException::OutOfBoundsException "Exception::OutOfBoundsException::OutOfBoundsException(const std::string &message)
";


// File: classOutputData.xml
%feature("docstring") OutputData "

Template class to store data of any type in multi-dimensional space.Used with data type double to hold simulation results. Used with data type  CumulativeValue in  IHistogram classes. Used with data type bool to hold a detector mask (-> class  DetectorMask)

C++ includes: OutputData.h
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData()
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData(const OutputData &)=delete
";

%feature("docstring")  OutputData::~OutputData "OutputData< T >::~OutputData()
";

%feature("docstring")  OutputData::clone "OutputData< T > * OutputData< T >::clone() const
";

%feature("docstring")  OutputData::copyFrom "void OutputData< T >::copyFrom(const OutputData< T > &x)
";

%feature("docstring")  OutputData::copyShapeFrom "void OutputData< T >::copyShapeFrom(const OutputData< U > &other)
";

%feature("docstring")  OutputData::meanValues "OutputData< double > * OutputData< T >::meanValues() const
";

%feature("docstring")  OutputData::addAxis "void OutputData< T >::addAxis(const IAxis &new_axis)
";

%feature("docstring")  OutputData::addAxis "void OutputData< T >::addAxis(const std::string &name, size_t size, double start, double end)
";

%feature("docstring")  OutputData::getAxis "const IAxis & OutputData< T >::getAxis(size_t serial_number) const

returns axis with given serial number 
";

%feature("docstring")  OutputData::getAxis "const IAxis & OutputData< T >::getAxis(const std::string &axis_name) const

returns axis with given name 
";

%feature("docstring")  OutputData::getRank "size_t OutputData< T >::getRank() const

Returns number of dimensions. 
";

%feature("docstring")  OutputData::getAllocatedSize "size_t OutputData< T >::getAllocatedSize() const

Returns total size of data buffer (product of bin number in every dimension). 
";

%feature("docstring")  OutputData::getAllSizes "std::vector< size_t > OutputData< T >::getAllSizes() const

Returns all sizes of its axes. 
";

%feature("docstring")  OutputData::getRawDataVector "std::vector< T > OutputData< T >::getRawDataVector() const

Returns copy of raw data vector. 
";

%feature("docstring")  OutputData::fillRawDataArray "void OutputData< T >::fillRawDataArray(T *destination) const

fill raw array with data 
";

%feature("docstring")  OutputData::totalSum "T OutputData< T >::totalSum() const

Returns sum of all values in the data structure. 
";

%feature("docstring")  OutputData::begin "OutputData< T >::iterator OutputData< T >::begin()

Returns read/write iterator that points to the first element. 
";

%feature("docstring")  OutputData::begin "OutputData< T >::const_iterator OutputData< T >::begin() const

Returns read-only iterator that points to the first element. 
";

%feature("docstring")  OutputData::end "iterator OutputData< T >::end()

Returns read/write iterator that points to the one past last element. 
";

%feature("docstring")  OutputData::end "const_iterator OutputData< T >::end() const

Returns read-only iterator that points to the one past last element. 
";

%feature("docstring")  OutputData::setVariability "void OutputData< T >::setVariability(double variability)
";

%feature("docstring")  OutputData::getVariability "double OutputData< T >::getVariability() const
";

%feature("docstring")  OutputData::getAxesBinIndices "std::vector< int > OutputData< T >::getAxesBinIndices(size_t global_index) const

Returns vector of axes indices for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

Vector of bin indices for all axes defined 
";

%feature("docstring")  OutputData::getAxisBinIndex "int OutputData< T >::getAxisBinIndex(size_t global_index, size_t i_selected_axis) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::getAxisBinIndex "int OutputData< T >::getAxisBinIndex(size_t global_index, const std::string &axis_name) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::toGlobalIndex "size_t OutputData< T >::toGlobalIndex(const std::vector< int > &axes_indices) const

Returns global index for specified indices of axes

Parameters:
-----------

axes_indices: 
Vector of axes indices for all specified axes in this dataset

Corresponding global index 
";

%feature("docstring")  OutputData::findGlobalIndex "size_t OutputData< T >::findGlobalIndex(const std::vector< double > &coordinates) const

Returns global index for specified axes values

Parameters:
-----------

coordinates: 
Vector of axes coordinates for all specified axes in this dataset

Closest global index 
";

%feature("docstring")  OutputData::getAxisValue "double OutputData< T >::getAxisValue(size_t global_index, size_t i_selected_axis) const

Returns the value of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

corresponding bin center of selected axis 
";

%feature("docstring")  OutputData::getAxisValue "double OutputData< T >::getAxisValue(size_t global_index, const std::string &axis_name) const

Returns the value of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

corresponding bin center of selected axis 
";

%feature("docstring")  OutputData::getAxesValues "std::vector< double > OutputData< T >::getAxesValues(size_t global_index) const

Returns values on all defined axes for given globalbin number

Parameters:
-----------

global_index: 
The global index of this data structure.

Vector of corresponding bin centers 
";

%feature("docstring")  OutputData::getAxisBin "Bin1D OutputData< T >::getAxisBin(size_t global_index, size_t i_selected_axis) const

Returns bin of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

Corresponding  Bin1D object 
";

%feature("docstring")  OutputData::getAxisBin "Bin1D OutputData< T >::getAxisBin(size_t global_index, const std::string &axis_name) const

Returns bin of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding  Bin1D object 
";

%feature("docstring")  OutputData::clear "void OutputData< T >::clear()

Sets object into initial state (no dimensions, data) 
";

%feature("docstring")  OutputData::setAllTo "void OutputData< T >::setAllTo(const T &value)

Sets content of output data to specific value. 
";

%feature("docstring")  OutputData::scaleAll "void OutputData< T >::scaleAll(const T &factor)

multiply every item of this output data by value 
";

%feature("docstring")  OutputData::setAxisSizes "void OutputData< T >::setAxisSizes(size_t rank, int *n_dims)

Adds 'rank' axes with indicated sizes. 
";

%feature("docstring")  OutputData::setRawDataVector "void OutputData< T >::setRawDataVector(const std::vector< T > &data_vector)

Sets new values to raw data vector. 
";

%feature("docstring")  OutputData::setRawDataArray "void OutputData< T >::setRawDataArray(const T *source)

Sets new values to raw data array. 
";

%feature("docstring")  OutputData::getValue "double OutputData< T >::getValue(size_t index) const

Returns value or summed value, depending on T. 
";

%feature("docstring")  OutputData::hasSameDimensions "bool OutputData< T >::hasSameDimensions(const OutputData< U > &right) const

Returns true if object have same dimensions and number of axes bins.

Returns true if object have same dimensions. 
";

%feature("docstring")  OutputData::hasSameShape "bool OutputData< T >::hasSameShape(const OutputData< U > &right) const

Returns true if objects a) have same dimensions b) bin boundaries of axes coincide.

Returns true if object have same dimensions and shape of axis. 
";

%feature("docstring")  OutputData::isInitialized "bool OutputData< T >::isInitialized() const

returns data as Python numpy array

returns true if object is correctly initialized 
";

%feature("docstring")  OutputData::allocate "void OutputData< T >::allocate()

memory allocation for current dimensions configuration 
";


// File: classOutputDataIterator.xml
%feature("docstring") OutputDataIterator "

Iterator for underlying  OutputData container.

C++ includes: OutputDataIterator.h
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator()

Empty constructor to comply with stl forward iterators. 
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator(TContainer *p_output_data, size_t start_at_index=0)

constructor 
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator(const OutputDataIterator< TValue2, TContainer2 > &other)

templated copy construction 
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator(const OutputDataIterator< TValue, TContainer > &other)

non-templated copy construction 
";

%feature("docstring")  OutputDataIterator::~OutputDataIterator "OutputDataIterator< TValue, TContainer >::~OutputDataIterator()
";

%feature("docstring")  OutputDataIterator::getIndex "size_t OutputDataIterator< TValue, TContainer >::getIndex() const

Returns current index. 
";

%feature("docstring")  OutputDataIterator::getContainer "TContainer* OutputDataIterator< TValue, TContainer >::getContainer() const

Returns container pointer. 
";

%feature("docstring")  OutputDataIterator::swap "void OutputDataIterator< TValue, TContainer >::swap(OutputDataIterator< TValue, TContainer > &other)

Swaps iterators. 
";


// File: classOutputDataReader.xml
%feature("docstring") OutputDataReader "

Reads  OutputData from file using different reading strategies.

C++ includes: OutputDataReader.h
";

%feature("docstring")  OutputDataReader::OutputDataReader "OutputDataReader::OutputDataReader(const std::string &file_name)
";

%feature("docstring")  OutputDataReader::getOutputData "OutputData< double > * OutputDataReader::getOutputData()

read output data from file (file name was set already from OutputDataIOFactory) 
";

%feature("docstring")  OutputDataReader::setStrategy "void OutputDataReader::setStrategy(IOutputDataReadStrategy *read_strategy)

Sets concrete reading strategy. 
";


// File: classOutputDataReadFactory.xml
%feature("docstring") OutputDataReadFactory "

Creates reader appropariate for given type of files.

C++ includes: OutputDataReadFactory.h
";


// File: classOutputDataReadINTStrategy.xml
%feature("docstring") OutputDataReadINTStrategy "

Strategy to read BornAgain native IntensityData from ASCII file.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  OutputDataReadINTStrategy::readOutputData "OutputData< double > * OutputDataReadINTStrategy::readOutputData(std::istream &input_stream)
";


// File: classOutputDataReadNumpyTXTStrategy.xml
%feature("docstring") OutputDataReadNumpyTXTStrategy "

Strategy to read  OutputData from simple ASCII file with the layout as in numpy.savetxt.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  OutputDataReadNumpyTXTStrategy::readOutputData "OutputData< double > * OutputDataReadNumpyTXTStrategy::readOutputData(std::istream &input_stream)
";


// File: classOutputDataWriteFactory.xml
%feature("docstring") OutputDataWriteFactory "

Creates writer appropariate for given type of files.

C++ includes: OutputDataWriteFactory.h
";


// File: classOutputDataWriteINTStrategy.xml
%feature("docstring") OutputDataWriteINTStrategy "

Strategy to write  OutputData to special BornAgain ASCII format.

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  OutputDataWriteINTStrategy::writeOutputData "void OutputDataWriteINTStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classOutputDataWriteNumpyTXTStrategy.xml
%feature("docstring") OutputDataWriteNumpyTXTStrategy "

Strategy to write  OutputData to simple ASCII file with the layout as in numpy.savetxt.

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  OutputDataWriteNumpyTXTStrategy::writeOutputData "void OutputDataWriteNumpyTXTStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classOutputDataWriter.xml
%feature("docstring") OutputDataWriter "

Write  OutputData to file using different witing strategies.

C++ includes: OutputDataWriter.h
";

%feature("docstring")  OutputDataWriter::OutputDataWriter "OutputDataWriter::OutputDataWriter(const std::string &file_name)
";

%feature("docstring")  OutputDataWriter::writeOutputData "void OutputDataWriter::writeOutputData(const OutputData< double > &data)

write output data to file 
";

%feature("docstring")  OutputDataWriter::setStrategy "void OutputDataWriter::setStrategy(IOutputDataWriteStrategy *write_strategy)

Sets concrete writing strategy. 
";


// File: classParameterDistribution.xml
%feature("docstring") ParameterDistribution "";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const std::string &par_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits())
";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const std::string &par_name, const IDistribution1D &distribution, size_t nbr_samples, double xmin, double xmax)
";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const ParameterDistribution &other)
";

%feature("docstring")  ParameterDistribution::~ParameterDistribution "ParameterDistribution::~ParameterDistribution()
";

%feature("docstring")  ParameterDistribution::linkParameter "ParameterDistribution & ParameterDistribution::linkParameter(std::string par_name)
";

%feature("docstring")  ParameterDistribution::getMainParameterName "std::string ParameterDistribution::getMainParameterName() const

get the main parameter's name 
";

%feature("docstring")  ParameterDistribution::getNbrSamples "size_t ParameterDistribution::getNbrSamples() const

get number of samples for this distribution 
";

%feature("docstring")  ParameterDistribution::getSigmaFactor "double ParameterDistribution::getSigmaFactor() const

get the sigma factor 
";

%feature("docstring")  ParameterDistribution::getDistribution "const IDistribution1D * ParameterDistribution::getDistribution() const
";

%feature("docstring")  ParameterDistribution::generateSamples "std::vector< ParameterSample > ParameterDistribution::generateSamples() const

generate list of sampled values with their weight 
";

%feature("docstring")  ParameterDistribution::getLinkedParameterNames "std::vector<std::string> ParameterDistribution::getLinkedParameterNames() const

get list of linked parameter names 
";

%feature("docstring")  ParameterDistribution::getLimits "RealLimits ParameterDistribution::getLimits() const
";

%feature("docstring")  ParameterDistribution::getMinValue "double ParameterDistribution::getMinValue() const
";

%feature("docstring")  ParameterDistribution::getMaxValue "double ParameterDistribution::getMaxValue() const
";


// File: classParameterPattern.xml
%feature("docstring") ParameterPattern "

Helper class for constructing parameter patterns.

C++ includes: ParameterPattern.h
";

%feature("docstring")  ParameterPattern::ParameterPattern "ParameterPattern::ParameterPattern()
";

%feature("docstring")  ParameterPattern::ParameterPattern "ParameterPattern::ParameterPattern(std::string root_object)
";

%feature("docstring")  ParameterPattern::beginsWith "ParameterPattern & ParameterPattern::beginsWith(std::string start_type)
";

%feature("docstring")  ParameterPattern::add "ParameterPattern & ParameterPattern::add(std::string object_type)
";

%feature("docstring")  ParameterPattern::toStdString "std::string ParameterPattern::toStdString() const
";


// File: classParameterPool.xml
%feature("docstring") ParameterPool "

Holds a map of pointers to parameters.Used in  IParameterized, which has a member ParameterPool* m_pool. So this is pimpl (pointer to implementation) idiom, with  ParameterPool providing the implementation of all the nontrivial functionality of  IParameterized.

Parameter names must be unique since we use them as map keys.

C++ includes: ParameterPool.h
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool(const std::string &name, const std::function< void()> &onChange)

Constructs an empty parameter pool. 
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool(const ParameterPool &)=delete
";

%feature("docstring")  ParameterPool::~ParameterPool "ParameterPool::~ParameterPool()
";

%feature("docstring")  ParameterPool::clone "ParameterPool * ParameterPool::clone() const

Returns a literal clone. 
";

%feature("docstring")  ParameterPool::cloneWithPrefix "ParameterPool * ParameterPool::cloneWithPrefix(const std::string &prefix) const

Returns a clone with  prefix prepended to every parameter key. 
";

%feature("docstring")  ParameterPool::copyToExternalPool "void ParameterPool::copyToExternalPool(const std::string &prefix, ParameterPool *external_pool) const

Copies parameters of given pool to  other pool, prepeding  prefix to the parameter names. 
";

%feature("docstring")  ParameterPool::clear "void ParameterPool::clear()

Clears the parameter map. 
";

%feature("docstring")  ParameterPool::getName "std::string ParameterPool::getName() const
";

%feature("docstring")  ParameterPool::size "size_t ParameterPool::size() const

Returns number of parameters in the pool. 
";

%feature("docstring")  ParameterPool::addParameter "RealParameter & ParameterPool::addParameter(RealParameter *par)

Adds parameter to the pool, and returns reference to the input pointer.

Returning the input pointer allows us to concatenate function calls like pool->addParameter( new  RealParameter(...) ).setLimits(-1,+1).setFixed().setUnit(\"nm\") 
";

%feature("docstring")  ParameterPool::getParameter "RealParameter * ParameterPool::getParameter(const std::string &name)

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::getParameter "const RealParameter * ParameterPool::getParameter(const std::string &name) const

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::getParameters "const std::vector<RealParameter*> ParameterPool::getParameters() const

Returns full vector of parameters. 
";

%feature("docstring")  ParameterPool::getMatchedParameters "std::vector< RealParameter * > ParameterPool::getMatchedParameters(const std::string &wildcards) const

Returns vector of parameters that match the  pattern (wildcards '*' allowed). 
";

%feature("docstring")  ParameterPool::setParameterValue "void ParameterPool::setParameterValue(const std::string &name, double value)

Sets parameter value. 
";

%feature("docstring")  ParameterPool::setMatchedParametersValue "int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)

Sets parameter value. 
";

%feature("docstring")  ParameterPool::getParameterNames "std::vector< std::string > ParameterPool::getParameterNames() const
";


// File: classParameterSample.xml
%feature("docstring") ParameterSample "

Represents a sampled parameter value with its weight.

C++ includes: ParameterSample.h
";


// File: classParticle.xml
%feature("docstring") Particle "

A particle with a form factor and refractive index.

C++ includes: Particle.h
";

%feature("docstring")  Particle::Particle "Particle::Particle()
";

%feature("docstring")  Particle::Particle "Particle::Particle(const IMaterial &p_material)
";

%feature("docstring")  Particle::Particle "Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor)
";

%feature("docstring")  Particle::Particle "Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor, const IRotation &rotation)
";

%feature("docstring")  Particle::clone "Particle * Particle::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  Particle::cloneInvertB "Particle * Particle::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  Particle::accept "virtual void Particle::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  Particle::to_str "std::string Particle::to_str(int indent=0) const

Returns textual representation of this and its descendants. 
";

%feature("docstring")  Particle::setAmbientMaterial "void Particle::setAmbientMaterial(const IMaterial &material) final

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  Particle::getAmbientMaterial "const IMaterial* Particle::getAmbientMaterial() const final

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Particle::createTransformedFormFactor "IFormFactor * Particle::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  Particle::setMaterial "void Particle::setMaterial(const IMaterial &material)
";

%feature("docstring")  Particle::getMaterial "const IMaterial* Particle::getMaterial() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Particle::getRefractiveIndex "complex_t Particle::getRefractiveIndex() const
";

%feature("docstring")  Particle::setFormFactor "void Particle::setFormFactor(const IFormFactor &form_factor)
";

%feature("docstring")  Particle::getFormFactor "const IFormFactor* Particle::getFormFactor() const
";


// File: classParticleComposition.xml
%feature("docstring") ParticleComposition "

A composition of particles at fixed positions

C++ includes: ParticleComposition.h
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition()
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle)
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle, kvector_t position)
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::~ParticleComposition "ParticleComposition::~ParticleComposition()
";

%feature("docstring")  ParticleComposition::clone "ParticleComposition * ParticleComposition::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleComposition::cloneInvertB "ParticleComposition * ParticleComposition::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleComposition::accept "virtual void ParticleComposition::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle)
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle, kvector_t position)
";

%feature("docstring")  ParticleComposition::addParticles "void ParticleComposition::addParticles(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::setAmbientMaterial "void ParticleComposition::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  ParticleComposition::getAmbientMaterial "const IMaterial * ParticleComposition::getAmbientMaterial() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  ParticleComposition::createTransformedFormFactor "IFormFactor * ParticleComposition::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  ParticleComposition::getNbrParticles "size_t ParticleComposition::getNbrParticles() const

Returns number of different particles. 
";

%feature("docstring")  ParticleComposition::getParticle "const IParticle * ParticleComposition::getParticle(size_t index) const

Returns particle with given index. 
";

%feature("docstring")  ParticleComposition::getParticlePosition "kvector_t ParticleComposition::getParticlePosition(size_t index) const
";


// File: classParticleCompositionBuilder.xml
%feature("docstring") ParticleCompositionBuilder "

Builds sample: two layers of spheres at hex lattice.

C++ includes: ParticleCompositionBuilder.h
";

%feature("docstring")  ParticleCompositionBuilder::ParticleCompositionBuilder "ParticleCompositionBuilder::ParticleCompositionBuilder()
";

%feature("docstring")  ParticleCompositionBuilder::buildSample "MultiLayer * ParticleCompositionBuilder::buildSample() const
";


// File: classParticleCoreShell.xml
%feature("docstring") ParticleCoreShell "

A particle with a core/shell geometry.

C++ includes: ParticleCoreShell.h
";

%feature("docstring")  ParticleCoreShell::ParticleCoreShell "ParticleCoreShell::ParticleCoreShell(const Particle &shell, const Particle &core, kvector_t relative_core_position=kvector_t(0.0, 0.0, 0.0))
";

%feature("docstring")  ParticleCoreShell::~ParticleCoreShell "ParticleCoreShell::~ParticleCoreShell()
";

%feature("docstring")  ParticleCoreShell::clone "ParticleCoreShell * ParticleCoreShell::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleCoreShell::cloneInvertB "ParticleCoreShell * ParticleCoreShell::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleCoreShell::accept "virtual void ParticleCoreShell::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  ParticleCoreShell::setAmbientMaterial "void ParticleCoreShell::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  ParticleCoreShell::getAmbientMaterial "const IMaterial * ParticleCoreShell::getAmbientMaterial() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  ParticleCoreShell::createTransformedFormFactor "IFormFactor * ParticleCoreShell::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  ParticleCoreShell::getCoreParticle "const Particle* ParticleCoreShell::getCoreParticle() const

Returns the core particle. 
";

%feature("docstring")  ParticleCoreShell::getShellParticle "const Particle* ParticleCoreShell::getShellParticle() const

Returns the shell particle. 
";


// File: classParticleDistribution.xml
%feature("docstring") ParticleDistribution "

A particle type that is a parametric distribution of  IParticle's.

C++ includes: ParticleDistribution.h
";

%feature("docstring")  ParticleDistribution::ParticleDistribution "ParticleDistribution::ParticleDistribution(const IParticle &prototype, const ParameterDistribution &par_distr)
";

%feature("docstring")  ParticleDistribution::clone "ParticleDistribution * ParticleDistribution::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleDistribution::cloneInvertB "ParticleDistribution * ParticleDistribution::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleDistribution::accept "void ParticleDistribution::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ParticleDistribution::to_str "std::string ParticleDistribution::to_str(int indent=0) const

Returns textual representation of* this and its descendants. 
";

%feature("docstring")  ParticleDistribution::setAmbientMaterial "void ParticleDistribution::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  ParticleDistribution::getAmbientMaterial "const IMaterial * ParticleDistribution::getAmbientMaterial() const

Returns particle's material. 
";

%feature("docstring")  ParticleDistribution::generateParticles "void ParticleDistribution::generateParticles(std::vector< const IParticle * > &particle_vector) const

Initializes list of new particles generated according to a distribution. 
";

%feature("docstring")  ParticleDistribution::getParameterDistribution "ParameterDistribution ParticleDistribution::getParameterDistribution() const

Returns the distributed parameter data. 
";

%feature("docstring")  ParticleDistribution::createDistributedParameterPool "ParameterPool * ParticleDistribution::createDistributedParameterPool() const

Returns the parameter pool that can be used for parameter distributions. 
";

%feature("docstring")  ParticleDistribution::getParticle "const IParticle * ParticleDistribution::getParticle() const

Returns particle. 
";


// File: classParticleInTheAirBuilder.xml
%feature("docstring") ParticleInTheAirBuilder "

The  ParticleInTheAirBuilder class generates a multilayer with single air layer populated with particles of certain types. Requires IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: ParticleInTheAirBuilder.h
";

%feature("docstring")  ParticleInTheAirBuilder::ParticleInTheAirBuilder "ParticleInTheAirBuilder::ParticleInTheAirBuilder()
";

%feature("docstring")  ParticleInTheAirBuilder::~ParticleInTheAirBuilder "virtual ParticleInTheAirBuilder::~ParticleInTheAirBuilder()
";

%feature("docstring")  ParticleInTheAirBuilder::buildSample "MultiLayer * ParticleInTheAirBuilder::buildSample() const
";


// File: classParticleLayout.xml
%feature("docstring") ParticleLayout "

Decorator class that adds particles to  ISample objects.

C++ includes: ParticleLayout.h
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout()
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout(const IAbstractParticle &particle)
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout(const IAbstractParticle &particle, double abundance)
";

%feature("docstring")  ParticleLayout::~ParticleLayout "ParticleLayout::~ParticleLayout() final
";

%feature("docstring")  ParticleLayout::clone "ParticleLayout * ParticleLayout::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleLayout::cloneInvertB "ParticleLayout * ParticleLayout::cloneInvertB() const final

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleLayout::accept "void ParticleLayout::accept(ISampleVisitor *visitor) const final

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IAbstractParticle &particle)

Adds generic particle to the layout. 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IAbstractParticle &particle, double abundance)

Adds generic particle to the layout with only abundance defined.

Parameters:
-----------

particle: 
to be added

abundance: 
 Particle abundance 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IParticle &particle, double abundance, const kvector_t position)

Adds particle to the layout with abundance and position defined.

Parameters:
-----------

particle: 
to be added

abundance: 
 Particle abundance

position: 
 Particle position 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IParticle &particle, double abundance, const kvector_t position, const IRotation &rotation)

Adds particle to the layout with abundance, position and the rotation defined.

Parameters:
-----------

particle: 
to be added

abundance: 
 Particle abundance

position: 
 Particle position

rotation: 
 Particle rotation 
";

%feature("docstring")  ParticleLayout::getNumberOfParticles "size_t ParticleLayout::getNumberOfParticles() const final

Returns number of particles. 
";

%feature("docstring")  ParticleLayout::getParticle "const IAbstractParticle * ParticleLayout::getParticle(size_t index) const final

Returns particle info. 
";

%feature("docstring")  ParticleLayout::getParticles "SafePointerVector< const IParticle > ParticleLayout::getParticles() const final

Returns information on all particles (type and abundance) and generates new particles if an  IAbstractParticle denotes a collection 
";

%feature("docstring")  ParticleLayout::getAbundanceOfParticle "double ParticleLayout::getAbundanceOfParticle(size_t index) const

Returns the abundance fraction of particle at given index. 
";

%feature("docstring")  ParticleLayout::getInterferenceFunction "const IInterferenceFunction* ParticleLayout::getInterferenceFunction() const final

Returns interference function. 
";

%feature("docstring")  ParticleLayout::cloneInterferenceFunction "IInterferenceFunction * ParticleLayout::cloneInterferenceFunction() const final

Returns a clone, or an  InterferenceFunctionNone. 
";

%feature("docstring")  ParticleLayout::addInterferenceFunction "void ParticleLayout::addInterferenceFunction(const IInterferenceFunction &interference_function)

Adds interference functions. 
";

%feature("docstring")  ParticleLayout::getTotalParticleSurfaceDensity "double ParticleLayout::getTotalParticleSurfaceDensity() const final

Returns surface density of all particles. 
";

%feature("docstring")  ParticleLayout::setTotalParticleSurfaceDensity "void ParticleLayout::setTotalParticleSurfaceDensity(double particle_density) final

Sets surface density of all particles. 
";


// File: classGeometry_1_1Polygon.xml
%feature("docstring") Geometry::Polygon "

A polygon in 2D space.Polygon defined by two arrays with x and y coordinates of points. Sizes of arrays should coincide. If polygon is unclosed (the last point doesn't repeat the first one), it will be closed automatically.

C++ includes: Polygon.h
";

%feature("docstring")  Geometry::Polygon::Polygon "Geometry::Polygon::Polygon(const std::vector< double > &x, const std::vector< double > &y)

Parameters:
-----------

x: 
Vector of x-coordinates of polygon points.

y: 
Vector of y-coordinates of polygon points. 
";

%feature("docstring")  Geometry::Polygon::Polygon "Geometry::Polygon::Polygon(const std::vector< std::vector< double >> &points)

Polygon defined by two dimensional array with (x,y) coordinates of polygon points. The size of second dimension should be 2. If polygon is unclosed (the last point doesn't repeat the first one), it will be closed automatically.

Parameters:
-----------

points: 
Two dimensional vector of (x,y) coordinates of polygon points. 
";

%feature("docstring")  Geometry::Polygon::Polygon "Geometry::Polygon::Polygon(const PolygonPrivate *d)
";

%feature("docstring")  Geometry::Polygon::~Polygon "Geometry::Polygon::~Polygon()
";

%feature("docstring")  Geometry::Polygon::clone "virtual Polygon* Geometry::Polygon::clone() const
";

%feature("docstring")  Geometry::Polygon::contains "bool Geometry::Polygon::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::Polygon::contains "bool Geometry::Polygon::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  Geometry::Polygon::getArea "double Geometry::Polygon::getArea() const
";

%feature("docstring")  Geometry::Polygon::getPoints "void Geometry::Polygon::getPoints(std::vector< double > &xpos, std::vector< double > &ypos) const
";


// File: classPolygonalTopology.xml
%feature("docstring") PolygonalTopology "

For internal use in  PolyhedralFace.

C++ includes: FormFactorPolyhedron.h
";


// File: classGeometry_1_1PolygonPrivate.xml
%feature("docstring") Geometry::PolygonPrivate "

The private data for polygons to hide boost dependency from the header. 
";

%feature("docstring")  Geometry::PolygonPrivate::init_from "void Geometry::PolygonPrivate::init_from(const std::vector< double > &x, const std::vector< double > &y)
";

%feature("docstring")  Geometry::PolygonPrivate::get_points "void Geometry::PolygonPrivate::get_points(std::vector< double > &xpos, std::vector< double > &ypos)
";


// File: classPolyhedralEdge.xml
%feature("docstring") PolyhedralEdge "

One edge of a polygon, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  PolyhedralEdge::PolyhedralEdge "PolyhedralEdge::PolyhedralEdge(const kvector_t _Vlow, const kvector_t _Vhig)
";

%feature("docstring")  PolyhedralEdge::E "kvector_t PolyhedralEdge::E() const
";

%feature("docstring")  PolyhedralEdge::R "kvector_t PolyhedralEdge::R() const
";

%feature("docstring")  PolyhedralEdge::qE "complex_t PolyhedralEdge::qE(cvector_t q) const
";

%feature("docstring")  PolyhedralEdge::qR "complex_t PolyhedralEdge::qR(cvector_t q) const
";

%feature("docstring")  PolyhedralEdge::contrib "complex_t PolyhedralEdge::contrib(int m, const cvector_t qpa, complex_t qrperp) const

Returns sum_l=0^M/2 u^2l v^(M-2l) / (2l+1)!(M-2l)! - vperp^M/M! 
";


// File: classPolyhedralFace.xml
%feature("docstring") PolyhedralFace "

A polygon, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  PolyhedralFace::PolyhedralFace "PolyhedralFace::PolyhedralFace(const std::vector< kvector_t > &_V=std::vector< kvector_t >(), bool _sym_S2=false)

Sets internal variables for given vertex chain.

Parameters:
-----------

V: 
oriented vertex list

_sym_S2: 
true if face has a perpedicular two-fold symmetry axis 
";

%feature("docstring")  PolyhedralFace::area "double PolyhedralFace::area() const
";

%feature("docstring")  PolyhedralFace::center "kvector_t PolyhedralFace::center() const
";

%feature("docstring")  PolyhedralFace::pyramidalVolume "double PolyhedralFace::pyramidalVolume() const
";

%feature("docstring")  PolyhedralFace::radius3d "double PolyhedralFace::radius3d() const
";

%feature("docstring")  PolyhedralFace::normalProjectionConj "complex_t PolyhedralFace::normalProjectionConj(cvector_t q) const

Returns conj(q)*normal [ BasicVector3D::dot is antilinear in 'this' argument]. 
";

%feature("docstring")  PolyhedralFace::ff_n "complex_t PolyhedralFace::ff_n(int m, const cvector_t q) const

Returns contribution qn*f_n [of order q^(n+1)] from this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff "complex_t PolyhedralFace::ff(const cvector_t q, const bool sym_Ci) const

Returns the contribution ff(q) of this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff_2D "complex_t PolyhedralFace::ff_2D(const cvector_t qpa) const

Returns the two-dimensional form factor of this face, for use in a prism. 
";

%feature("docstring")  PolyhedralFace::assert_Ci "void PolyhedralFace::assert_Ci(const PolyhedralFace &other) const

Throws if deviation from inversion symmetry is detected. Does not check vertices. 
";


// File: classPolyhedralTopology.xml
%feature("docstring") PolyhedralTopology "

For internal use in  FormFactorPolyhedron.

C++ includes: FormFactorPolyhedron.h
";


// File: classPrecomputed.xml
%feature("docstring") Precomputed "

This class contains precomputed constants.

C++ includes: Precomputed.h
";


// File: classProgressHandler.xml
%feature("docstring") ProgressHandler "

Maintains information about progress of a computation. Owner is the computation, which periodically calls the thread-safe function incrementDone(..). An application (GUI or script) may subscribe(..) to be informed about progress. It is then periodically called back by inform(..). The return value of inform(..) can be used to request termination of the computation.

C++ includes: ProgressHandler.h
";

%feature("docstring")  ProgressHandler::ProgressHandler "ProgressHandler::ProgressHandler()
";

%feature("docstring")  ProgressHandler::ProgressHandler "ProgressHandler::ProgressHandler(const ProgressHandler &other)
";

%feature("docstring")  ProgressHandler::subscribe "void ProgressHandler::subscribe(ProgressHandler::Callback_t callback)
";

%feature("docstring")  ProgressHandler::reset "void ProgressHandler::reset()
";

%feature("docstring")  ProgressHandler::setExpectedNTicks "void ProgressHandler::setExpectedNTicks(size_t n)
";

%feature("docstring")  ProgressHandler::incrementDone "void ProgressHandler::incrementDone(size_t ticks_done)

Increments number of completed computation steps (ticks). Performs callback (method m_inform) to inform the subscriber about the state of the computation and to obtain as return value a flag that indicates whether to continue the computation. 
";

%feature("docstring")  ProgressHandler::alive "bool ProgressHandler::alive()
";


// File: classRadialParaCrystalBuilder.xml
%feature("docstring") RadialParaCrystalBuilder "

Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4)

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RadialParaCrystalBuilder::RadialParaCrystalBuilder "RadialParaCrystalBuilder::RadialParaCrystalBuilder()
";

%feature("docstring")  RadialParaCrystalBuilder::buildSample "MultiLayer * RadialParaCrystalBuilder::buildSample() const
";


// File: classRealParameter.xml
%feature("docstring") RealParameter "

Wraps a parameter of type double. In addition to name and on-change callback held by the parent class  IParameter, this class holds Limits, Attributes (currently only fixed or not), and a  Unit.

C++ includes: RealParameter.h
";

%feature("docstring")  RealParameter::RealParameter "RealParameter::RealParameter(const std::string &name, volatile double *par, const std::string &parent_name, const std::function< void()> &onChange, const RealLimits &limits=RealLimits::limitless(), const Attributes &attr=Attributes::free())
";

%feature("docstring")  RealParameter::clone "RealParameter * RealParameter::clone(const std::string &new_name=\"\") const
";

%feature("docstring")  RealParameter::setValue "void RealParameter::setValue(double value)

Sets value of wrapped parameter and emit signal. 
";

%feature("docstring")  RealParameter::getValue "double RealParameter::getValue() const

Returns value of wrapped parameter. 
";

%feature("docstring")  RealParameter::setLimits "RealParameter& RealParameter::setLimits(const RealLimits &limits)
";

%feature("docstring")  RealParameter::getLimits "RealLimits RealParameter::getLimits() const
";

%feature("docstring")  RealParameter::setLimited "RealParameter & RealParameter::setLimited(double lower, double upper)
";

%feature("docstring")  RealParameter::setPositive "RealParameter & RealParameter::setPositive()
";

%feature("docstring")  RealParameter::setNonnegative "RealParameter & RealParameter::setNonnegative()
";

%feature("docstring")  RealParameter::setUnit "RealParameter& RealParameter::setUnit(const std::string &name)
";

%feature("docstring")  RealParameter::unit "std::string RealParameter::unit() const
";


// File: classGeometry_1_1Rectangle.xml
%feature("docstring") Geometry::Rectangle "

The rectangle shape having its axis aligned to the (non-rotated) coordinate system.

C++ includes: Rectangle.h
";

%feature("docstring")  Geometry::Rectangle::Rectangle "Geometry::Rectangle::Rectangle(double xlow, double ylow, double xup, double yup)

Parameters:
-----------

xlow: 
x-coordinate of lower left corner

ylow: 
y-coordinate of lower left corner

xup: 
x-coordinate of upper right corner

yup: 
y-coordinate of upper right corner 
";

%feature("docstring")  Geometry::Rectangle::clone "Rectangle* Geometry::Rectangle::clone() const
";

%feature("docstring")  Geometry::Rectangle::contains "bool Geometry::Rectangle::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::Rectangle::contains "bool Geometry::Rectangle::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  Geometry::Rectangle::getArea "double Geometry::Rectangle::getArea() const
";

%feature("docstring")  Geometry::Rectangle::getXlow "double Geometry::Rectangle::getXlow() const
";

%feature("docstring")  Geometry::Rectangle::getYlow "double Geometry::Rectangle::getYlow() const
";

%feature("docstring")  Geometry::Rectangle::getXup "double Geometry::Rectangle::getXup() const
";

%feature("docstring")  Geometry::Rectangle::getYup "double Geometry::Rectangle::getYup() const
";


// File: classRectangularDetector.xml
%feature("docstring") RectangularDetector "

A rectangular plane detector with axes and resolution function.

C++ includes: RectangularDetector.h
";

%feature("docstring")  RectangularDetector::RectangularDetector "RectangularDetector::RectangularDetector(int nxbins, double width, int nybins, double height)

Rectangular detector constructor

Parameters:
-----------

nxbins: 
Number of bins (pixels) in x-direction

width: 
Width of the detector in mm along x-direction

nybins: 
Number of bins (pixels) in y-direction

height: 
Height of the detector in mm along y-direction 
";

%feature("docstring")  RectangularDetector::RectangularDetector "RectangularDetector::RectangularDetector(const RectangularDetector &other)
";

%feature("docstring")  RectangularDetector::clone "RectangularDetector * RectangularDetector::clone() const override
";

%feature("docstring")  RectangularDetector::~RectangularDetector "RectangularDetector::~RectangularDetector()
";

%feature("docstring")  RectangularDetector::init "void RectangularDetector::init(const Beam &beam) override

Inits detector with the beam settings. 
";

%feature("docstring")  RectangularDetector::setPosition "void RectangularDetector::setPosition(const kvector_t normal_to_detector, double u0, double v0, const kvector_t direction=kvector_t(0.0, -1.0, 0.0))
";

%feature("docstring")  RectangularDetector::setPerpendicularToSampleX "void RectangularDetector::setPerpendicularToSampleX(double distance, double u0, double v0)
";

%feature("docstring")  RectangularDetector::setPerpendicularToDirectBeam "void RectangularDetector::setPerpendicularToDirectBeam(double distance, double u0, double v0)
";

%feature("docstring")  RectangularDetector::setPerpendicularToReflectedBeam "void RectangularDetector::setPerpendicularToReflectedBeam(double distance, double u0=0.0, double v0=0.0)
";

%feature("docstring")  RectangularDetector::setDirectBeamPosition "void RectangularDetector::setDirectBeamPosition(double u0, double v0)
";

%feature("docstring")  RectangularDetector::addParametersToExternalPool "std::string RectangularDetector::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const override

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  RectangularDetector::getWidth "double RectangularDetector::getWidth() const
";

%feature("docstring")  RectangularDetector::getHeight "double RectangularDetector::getHeight() const
";

%feature("docstring")  RectangularDetector::getNbinsX "size_t RectangularDetector::getNbinsX() const
";

%feature("docstring")  RectangularDetector::getNbinsY "size_t RectangularDetector::getNbinsY() const
";

%feature("docstring")  RectangularDetector::getNormalVector "kvector_t RectangularDetector::getNormalVector() const
";

%feature("docstring")  RectangularDetector::getU0 "double RectangularDetector::getU0() const
";

%feature("docstring")  RectangularDetector::getV0 "double RectangularDetector::getV0() const
";

%feature("docstring")  RectangularDetector::getDirectionVector "kvector_t RectangularDetector::getDirectionVector() const
";

%feature("docstring")  RectangularDetector::getDistance "double RectangularDetector::getDistance() const
";

%feature("docstring")  RectangularDetector::getDirectBeamU0 "double RectangularDetector::getDirectBeamU0() const
";

%feature("docstring")  RectangularDetector::getDirectBeamV0 "double RectangularDetector::getDirectBeamV0() const
";

%feature("docstring")  RectangularDetector::getDetectorArrangment "RectangularDetector::EDetectorArrangement RectangularDetector::getDetectorArrangment() const
";

%feature("docstring")  RectangularDetector::getValidAxesUnits "std::vector< IDetector2D::EAxesUnits > RectangularDetector::getValidAxesUnits() const override

returns vector of valid axes units 
";

%feature("docstring")  RectangularDetector::getDefaultAxesUnits "IDetector2D::EAxesUnits RectangularDetector::getDefaultAxesUnits() const override

return default axes units 
";


// File: classRectParaCrystalBuilder.xml
%feature("docstring") RectParaCrystalBuilder "

Builds sample: 2D paracrystal lattice (IsGISAXS example #8)

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RectParaCrystalBuilder::RectParaCrystalBuilder "RectParaCrystalBuilder::RectParaCrystalBuilder()
";

%feature("docstring")  RectParaCrystalBuilder::buildSample "MultiLayer * RectParaCrystalBuilder::buildSample() const
";


// File: classRectPixelMap.xml
%feature("docstring") RectPixelMap "";

%feature("docstring")  RectPixelMap::RectPixelMap "RectPixelMap::RectPixelMap(kvector_t corner_pos, kvector_t width, kvector_t height)
";

%feature("docstring")  RectPixelMap::~RectPixelMap "virtual RectPixelMap::~RectPixelMap()
";

%feature("docstring")  RectPixelMap::clone "RectPixelMap * RectPixelMap::clone() const override
";

%feature("docstring")  RectPixelMap::createZeroSizeMap "RectPixelMap * RectPixelMap::createZeroSizeMap(double x, double y) const override
";

%feature("docstring")  RectPixelMap::getK "kvector_t RectPixelMap::getK(double x, double y, double wavelength) const override
";

%feature("docstring")  RectPixelMap::getIntegrationFactor "double RectPixelMap::getIntegrationFactor(double x, double y) const override
";

%feature("docstring")  RectPixelMap::getSolidAngle "double RectPixelMap::getSolidAngle() const override
";


// File: classRegionOfInterest.xml
%feature("docstring") RegionOfInterest "

Defines rectangular area for the detector which will be simulated/fitted.

C++ includes: RegionOfInterest.h
";

%feature("docstring")  RegionOfInterest::RegionOfInterest "RegionOfInterest::RegionOfInterest(const IDetector2D &detector, double xlow, double ylow, double xup, double yup)
";

%feature("docstring")  RegionOfInterest::RegionOfInterest "RegionOfInterest::RegionOfInterest(const OutputData< double > &data, double xlow, double ylow, double xup, double yup)
";

%feature("docstring")  RegionOfInterest::clone "RegionOfInterest * RegionOfInterest::clone() const
";

%feature("docstring")  RegionOfInterest::~RegionOfInterest "RegionOfInterest::~RegionOfInterest()
";

%feature("docstring")  RegionOfInterest::getXlow "double RegionOfInterest::getXlow() const
";

%feature("docstring")  RegionOfInterest::getYlow "double RegionOfInterest::getYlow() const
";

%feature("docstring")  RegionOfInterest::getXup "double RegionOfInterest::getXup() const
";

%feature("docstring")  RegionOfInterest::getYup "double RegionOfInterest::getYup() const
";

%feature("docstring")  RegionOfInterest::detectorIndex "size_t RegionOfInterest::detectorIndex(size_t roiIndex) const

Converts roi index to the detector index. 
";

%feature("docstring")  RegionOfInterest::roiIndex "size_t RegionOfInterest::roiIndex(size_t detectorIndex) const

Converts global detector index to ROI index. 
";

%feature("docstring")  RegionOfInterest::roiSize "size_t RegionOfInterest::roiSize() const

Number of detector bins in ROI area. 
";

%feature("docstring")  RegionOfInterest::detectorSize "size_t RegionOfInterest::detectorSize() const

Number of detector bins. 
";

%feature("docstring")  RegionOfInterest::isInROI "bool RegionOfInterest::isInROI(size_t detectorIndex) const
";

%feature("docstring")  RegionOfInterest::clipAxisToRoi "std::unique_ptr< IAxis > RegionOfInterest::clipAxisToRoi(size_t axis_index, const IAxis &axis) const
";


// File: classResolutionFunction2DGaussian.xml
%feature("docstring") ResolutionFunction2DGaussian "

Simple gaussian two-dimensional resolution function.

C++ includes: ResolutionFunction2DGaussian.h
";

%feature("docstring")  ResolutionFunction2DGaussian::ResolutionFunction2DGaussian "ResolutionFunction2DGaussian::ResolutionFunction2DGaussian(double sigma_x, double sigma_y)
";

%feature("docstring")  ResolutionFunction2DGaussian::evaluateCDF "double ResolutionFunction2DGaussian::evaluateCDF(double x, double y) const
";

%feature("docstring")  ResolutionFunction2DGaussian::clone "ResolutionFunction2DGaussian* ResolutionFunction2DGaussian::clone() const
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaX "double ResolutionFunction2DGaussian::getSigmaX() const
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaY "double ResolutionFunction2DGaussian::getSigmaY() const
";


// File: classRotatedPyramidsBuilder.xml
%feature("docstring") RotatedPyramidsBuilder "

Builds sample: Pyramids, rotated pyramids on top of substrate (IsGISAXS example #9)

C++ includes: RotatedPyramidsBuilder.h
";

%feature("docstring")  RotatedPyramidsBuilder::RotatedPyramidsBuilder "RotatedPyramidsBuilder::RotatedPyramidsBuilder()
";

%feature("docstring")  RotatedPyramidsBuilder::buildSample "MultiLayer * RotatedPyramidsBuilder::buildSample() const
";


// File: classRotatedSquareLatticeBuilder.xml
%feature("docstring") RotatedSquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  RotatedSquareLatticeBuilder::RotatedSquareLatticeBuilder "RotatedSquareLatticeBuilder::RotatedSquareLatticeBuilder()
";

%feature("docstring")  RotatedSquareLatticeBuilder::buildSample "MultiLayer * RotatedSquareLatticeBuilder::buildSample() const
";


// File: classRotationEuler.xml
%feature("docstring") RotationEuler "";

%feature("docstring")  RotationEuler::RotationEuler "RotationEuler::RotationEuler(double alpha, double beta, double gamma)
";

%feature("docstring")  RotationEuler::clone "RotationEuler* RotationEuler::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationEuler::createInverse "IRotation * RotationEuler::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationEuler::accept "void RotationEuler::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationEuler::getAlpha "double RotationEuler::getAlpha() const
";

%feature("docstring")  RotationEuler::getBeta "double RotationEuler::getBeta() const
";

%feature("docstring")  RotationEuler::getGamma "double RotationEuler::getGamma() const
";

%feature("docstring")  RotationEuler::getTransform3D "Transform3D RotationEuler::getTransform3D() const

Returns transformation. 
";


// File: classRotationX.xml
%feature("docstring") RotationX "";

%feature("docstring")  RotationX::RotationX "RotationX::RotationX(double angle)
";

%feature("docstring")  RotationX::clone "RotationX* RotationX::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationX::createInverse "RotationX* RotationX::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationX::accept "void RotationX::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationX::getAngle "double RotationX::getAngle() const
";

%feature("docstring")  RotationX::getTransform3D "Transform3D RotationX::getTransform3D() const

Returns transformation. 
";


// File: classRotationY.xml
%feature("docstring") RotationY "";

%feature("docstring")  RotationY::RotationY "RotationY::RotationY(double angle)
";

%feature("docstring")  RotationY::clone "RotationY* RotationY::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationY::createInverse "RotationY* RotationY::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationY::accept "void RotationY::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationY::getAngle "double RotationY::getAngle() const
";

%feature("docstring")  RotationY::getTransform3D "Transform3D RotationY::getTransform3D() const

Returns transformation. 
";


// File: classRotationZ.xml
%feature("docstring") RotationZ "";

%feature("docstring")  RotationZ::RotationZ "RotationZ::RotationZ(double angle=0.0)
";

%feature("docstring")  RotationZ::clone "RotationZ* RotationZ::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationZ::createInverse "RotationZ* RotationZ::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationZ::accept "void RotationZ::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationZ::getAngle "double RotationZ::getAngle() const
";

%feature("docstring")  RotationZ::getTransform3D "Transform3D RotationZ::getTransform3D() const

Returns transformation. 
";


// File: classRoughMultiLayerComputation.xml
%feature("docstring") RoughMultiLayerComputation "

Computes the diffuse reflection from the rough interfaces of a multilayer. Controlled by  MainComputation.

C++ includes: RoughMultiLayerComputation.h
";

%feature("docstring")  RoughMultiLayerComputation::RoughMultiLayerComputation "RoughMultiLayerComputation::RoughMultiLayerComputation(const MultiLayer *p_multi_layer)
";

%feature("docstring")  RoughMultiLayerComputation::~RoughMultiLayerComputation "RoughMultiLayerComputation::~RoughMultiLayerComputation()
";

%feature("docstring")  RoughMultiLayerComputation::eval "void RoughMultiLayerComputation::eval(ProgressHandler *progress, const std::vector< SimulationElement >::iterator &begin_it, const std::vector< SimulationElement >::iterator &end_it)

Calls evaluate on range of simulation elements; returns true if computation shall continue. 
";

%feature("docstring")  RoughMultiLayerComputation::setSpecularInfo "void RoughMultiLayerComputation::setSpecularInfo(size_t i_layer, const LayerSpecularInfo &specular_info)

Sets magnetic reflection/transmission info for specific layer. 
";

%feature("docstring")  RoughMultiLayerComputation::evaluate "double RoughMultiLayerComputation::evaluate(const SimulationElement &sim_element)
";


// File: classException_1_1RuntimeErrorException.xml
%feature("docstring") Exception::RuntimeErrorException "";

%feature("docstring")  Exception::RuntimeErrorException::RuntimeErrorException "Exception::RuntimeErrorException::RuntimeErrorException(const std::string &message)
";


// File: classSafePointerVector.xml
%feature("docstring") SafePointerVector "

The objects pointed to must support the  ICloneable interface.

A vector of pointers, owned by *this, with methods to handle them safely.

C++ includes: SafePointerVector.h
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector()
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector(const SafePointerVector &other)
";

%feature("docstring")  SafePointerVector::~SafePointerVector "virtual SafePointerVector< T >::~SafePointerVector()
";

%feature("docstring")  SafePointerVector::size "size_t SafePointerVector< T >::size() const
";

%feature("docstring")  SafePointerVector::empty "bool SafePointerVector< T >::empty() const
";

%feature("docstring")  SafePointerVector::push_back "void SafePointerVector< T >::push_back(T *pointer)
";

%feature("docstring")  SafePointerVector::begin "iterator SafePointerVector< T >::begin()
";

%feature("docstring")  SafePointerVector::begin "const_iterator SafePointerVector< T >::begin() const
";

%feature("docstring")  SafePointerVector::end "iterator SafePointerVector< T >::end()
";

%feature("docstring")  SafePointerVector::end "const_iterator SafePointerVector< T >::end() const
";

%feature("docstring")  SafePointerVector::deleteElement "bool SafePointerVector< T >::deleteElement(T *pointer)
";

%feature("docstring")  SafePointerVector::back "T* SafePointerVector< T >::back()
";

%feature("docstring")  SafePointerVector::back "const T* SafePointerVector< T >::back() const
";

%feature("docstring")  SafePointerVector::clear "void SafePointerVector< T >::clear()
";


// File: classSampleBuilderFactory.xml
%feature("docstring") SampleBuilderFactory "

Factory to create standard pre-defined samples.

C++ includes: SampleBuilderFactory.h
";

%feature("docstring")  SampleBuilderFactory::SampleBuilderFactory "SampleBuilderFactory::SampleBuilderFactory()
";

%feature("docstring")  SampleBuilderFactory::createSample "MultiLayer * SampleBuilderFactory::createSample(const std::string &name)

Retrieves a SampleBuilder from the registry, does the build, and returns the result. 
";


// File: classSampleIteratorPostorderStrategy.xml
%feature("docstring") SampleIteratorPostorderStrategy "";

%feature("docstring")  SampleIteratorPostorderStrategy::SampleIteratorPostorderStrategy "SampleIteratorPostorderStrategy::SampleIteratorPostorderStrategy()
";

%feature("docstring")  SampleIteratorPostorderStrategy::clone "SampleIteratorPostorderStrategy * SampleIteratorPostorderStrategy::clone() const
";

%feature("docstring")  SampleIteratorPostorderStrategy::~SampleIteratorPostorderStrategy "SampleIteratorPostorderStrategy::~SampleIteratorPostorderStrategy()
";

%feature("docstring")  SampleIteratorPostorderStrategy::first "IteratorMemento SampleIteratorPostorderStrategy::first(const ISample *p_root)
";

%feature("docstring")  SampleIteratorPostorderStrategy::next "void SampleIteratorPostorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  SampleIteratorPostorderStrategy::isDone "bool SampleIteratorPostorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classSampleIteratorPreorderStrategy.xml
%feature("docstring") SampleIteratorPreorderStrategy "";

%feature("docstring")  SampleIteratorPreorderStrategy::SampleIteratorPreorderStrategy "SampleIteratorPreorderStrategy::SampleIteratorPreorderStrategy()
";

%feature("docstring")  SampleIteratorPreorderStrategy::clone "SampleIteratorPreorderStrategy * SampleIteratorPreorderStrategy::clone() const
";

%feature("docstring")  SampleIteratorPreorderStrategy::~SampleIteratorPreorderStrategy "SampleIteratorPreorderStrategy::~SampleIteratorPreorderStrategy()
";

%feature("docstring")  SampleIteratorPreorderStrategy::first "IteratorMemento SampleIteratorPreorderStrategy::first(const ISample *p_root)
";

%feature("docstring")  SampleIteratorPreorderStrategy::next "void SampleIteratorPreorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  SampleIteratorPreorderStrategy::isDone "bool SampleIteratorPreorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classSampleLabelHandler.xml
%feature("docstring") SampleLabelHandler "

The handler which construct labels for sample variables during python script generation.

C++ includes: SampleLabelHandler.h
";

%feature("docstring")  SampleLabelHandler::SampleLabelHandler "SampleLabelHandler::SampleLabelHandler()
";

%feature("docstring")  SampleLabelHandler::getFormFactorMap "formfactors_t* SampleLabelHandler::getFormFactorMap()
";

%feature("docstring")  SampleLabelHandler::getInterferenceFunctionMap "interferences_t* SampleLabelHandler::getInterferenceFunctionMap()
";

%feature("docstring")  SampleLabelHandler::getLayerMap "layers_t* SampleLabelHandler::getLayerMap()
";

%feature("docstring")  SampleLabelHandler::getParticleLayoutMap "layouts_t* SampleLabelHandler::getParticleLayoutMap()
";

%feature("docstring")  SampleLabelHandler::getMaterialMap "materials_t* SampleLabelHandler::getMaterialMap()
";

%feature("docstring")  SampleLabelHandler::getMultiLayerMap "multilayers_t* SampleLabelHandler::getMultiLayerMap()
";

%feature("docstring")  SampleLabelHandler::getParticleCompositionMap "particlecompositions_t* SampleLabelHandler::getParticleCompositionMap()
";

%feature("docstring")  SampleLabelHandler::getParticleDistributionsMap "particledistributions_t* SampleLabelHandler::getParticleDistributionsMap()
";

%feature("docstring")  SampleLabelHandler::getParticleMap "particles_t* SampleLabelHandler::getParticleMap()
";

%feature("docstring")  SampleLabelHandler::getParticleCoreShellMap "particlescoreshell_t* SampleLabelHandler::getParticleCoreShellMap()
";

%feature("docstring")  SampleLabelHandler::getRotationsMap "rotations_t* SampleLabelHandler::getRotationsMap()
";

%feature("docstring")  SampleLabelHandler::getLayerRoughnessMap "roughnesses_t* SampleLabelHandler::getLayerRoughnessMap()
";

%feature("docstring")  SampleLabelHandler::getLabelParticle "std::string SampleLabelHandler::getLabelParticle(const IAbstractParticle *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelFormFactor "std::string SampleLabelHandler::getLabelFormFactor(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelInterferenceFunction "std::string SampleLabelHandler::getLabelInterferenceFunction(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelLayout "std::string SampleLabelHandler::getLabelLayout(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelMaterial "std::string SampleLabelHandler::getLabelMaterial(const IMaterial *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelRotation "std::string SampleLabelHandler::getLabelRotation(const IRotation *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelLayer "std::string SampleLabelHandler::getLabelLayer(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelRoughness "std::string SampleLabelHandler::getLabelRoughness(const LayerRoughness *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelMultiLayer "std::string SampleLabelHandler::getLabelMultiLayer(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelParticleComposition "std::string SampleLabelHandler::getLabelParticleComposition(const ParticleComposition *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelParticleCoreShell "std::string SampleLabelHandler::getLabelParticleCoreShell(const ParticleCoreShell *sample)
";

%feature("docstring")  SampleLabelHandler::getLabelParticleDistribution "std::string SampleLabelHandler::getLabelParticleDistribution(const ParticleDistribution *sample)
";

%feature("docstring")  SampleLabelHandler::insertMaterial "void SampleLabelHandler::insertMaterial(const IMaterial *sample)
";

%feature("docstring")  SampleLabelHandler::insertFormFactor "void SampleLabelHandler::insertFormFactor(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::insertInterferenceFunction "void SampleLabelHandler::insertInterferenceFunction(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::insertLayout "void SampleLabelHandler::insertLayout(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::insertRotation "void SampleLabelHandler::insertRotation(const IRotation *sample)
";

%feature("docstring")  SampleLabelHandler::insertLayer "void SampleLabelHandler::insertLayer(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::insertRoughness "void SampleLabelHandler::insertRoughness(const LayerRoughness *sample)
";

%feature("docstring")  SampleLabelHandler::insertMultiLayer "void SampleLabelHandler::insertMultiLayer(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticle "void SampleLabelHandler::insertParticle(const Particle *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleComposition "void SampleLabelHandler::insertParticleComposition(const ParticleComposition *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleCoreShell "void SampleLabelHandler::insertParticleCoreShell(const ParticleCoreShell *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleDistribution "void SampleLabelHandler::insertParticleDistribution(const ParticleDistribution *sample)
";


// File: classSampleTreeIterator.xml
%feature("docstring") SampleTreeIterator "

Iterator through  ISample tree of objects inside  ISample object.

Usage example: SampleTreeIterator<Strategy> it(&sample); it.first(); while( !it.is_done() ) {  ISample *p_sample = it.get_current(); it.next(); }

C++ includes: SampleTreeIterator.h
";

%feature("docstring")  SampleTreeIterator::SampleTreeIterator "SampleTreeIterator< Strategy >::SampleTreeIterator(const ISample *root)
";

%feature("docstring")  SampleTreeIterator::~SampleTreeIterator "virtual SampleTreeIterator< Strategy >::~SampleTreeIterator()
";

%feature("docstring")  SampleTreeIterator::first "void SampleTreeIterator< Strategy >::first()
";

%feature("docstring")  SampleTreeIterator::next "void SampleTreeIterator< Strategy >::next()
";

%feature("docstring")  SampleTreeIterator::getCurrent "const ISample * SampleTreeIterator< Strategy >::getCurrent()
";

%feature("docstring")  SampleTreeIterator::isDone "bool SampleTreeIterator< Strategy >::isDone() const
";

%feature("docstring")  SampleTreeIterator::getLevel "size_t SampleTreeIterator< Strategy >::getLevel() const
";


// File: classScalarRTCoefficients.xml
%feature("docstring") ScalarRTCoefficients "

Specular reflection and transmission coefficients in a layer in case of scalar interactions between the layers and the scattered particle.

C++ includes: ScalarRTCoefficients.h
";

%feature("docstring")  ScalarRTCoefficients::ScalarRTCoefficients "ScalarRTCoefficients::ScalarRTCoefficients()
";

%feature("docstring")  ScalarRTCoefficients::~ScalarRTCoefficients "virtual ScalarRTCoefficients::~ScalarRTCoefficients()
";

%feature("docstring")  ScalarRTCoefficients::clone "ScalarRTCoefficients * ScalarRTCoefficients::clone() const
";

%feature("docstring")  ScalarRTCoefficients::T1plus "Eigen::Vector2cd ScalarRTCoefficients::T1plus() const

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  ScalarRTCoefficients::R1plus "Eigen::Vector2cd ScalarRTCoefficients::R1plus() const
";

%feature("docstring")  ScalarRTCoefficients::T2plus "Eigen::Vector2cd ScalarRTCoefficients::T2plus() const
";

%feature("docstring")  ScalarRTCoefficients::R2plus "Eigen::Vector2cd ScalarRTCoefficients::R2plus() const
";

%feature("docstring")  ScalarRTCoefficients::T1min "Eigen::Vector2cd ScalarRTCoefficients::T1min() const
";

%feature("docstring")  ScalarRTCoefficients::R1min "Eigen::Vector2cd ScalarRTCoefficients::R1min() const
";

%feature("docstring")  ScalarRTCoefficients::T2min "Eigen::Vector2cd ScalarRTCoefficients::T2min() const
";

%feature("docstring")  ScalarRTCoefficients::R2min "Eigen::Vector2cd ScalarRTCoefficients::R2min() const
";

%feature("docstring")  ScalarRTCoefficients::getKz "Eigen::Vector2cd ScalarRTCoefficients::getKz() const

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  ScalarRTCoefficients::getScalarT "complex_t ScalarRTCoefficients::getScalarT() const

Scalar value getters; these throw errors by default as they should only be used when the derived object is really scalar 
";

%feature("docstring")  ScalarRTCoefficients::getScalarR "complex_t ScalarRTCoefficients::getScalarR() const
";

%feature("docstring")  ScalarRTCoefficients::getScalarKz "virtual complex_t ScalarRTCoefficients::getScalarKz() const
";


// File: classScalarSpecularInfoMap.xml
%feature("docstring") ScalarSpecularInfoMap "

Implementation of  ISpecularInfoMap for scalar valued reflection/transmission coefficients.

C++ includes: ScalarSpecularInfoMap.h
";

%feature("docstring")  ScalarSpecularInfoMap::ScalarSpecularInfoMap "ScalarSpecularInfoMap::ScalarSpecularInfoMap(const MultiLayer *multilayer, int layer)
";

%feature("docstring")  ScalarSpecularInfoMap::~ScalarSpecularInfoMap "ScalarSpecularInfoMap::~ScalarSpecularInfoMap() final
";

%feature("docstring")  ScalarSpecularInfoMap::clone "ScalarSpecularInfoMap* ScalarSpecularInfoMap::clone() const final
";

%feature("docstring")  ScalarSpecularInfoMap::getOutCoefficients "const ILayerRTCoefficients * ScalarSpecularInfoMap::getOutCoefficients(const SimulationElement &sim_element) const final

Retrieves the amplitude coefficients for the given angles. 
";

%feature("docstring")  ScalarSpecularInfoMap::getInCoefficients "const ILayerRTCoefficients * ScalarSpecularInfoMap::getInCoefficients(const SimulationElement &sim_element) const final

Retrieves the amplitude coefficients for the given angles. 
";


// File: classException_1_1SelfReferenceException.xml
%feature("docstring") Exception::SelfReferenceException "";

%feature("docstring")  Exception::SelfReferenceException::SelfReferenceException "Exception::SelfReferenceException::SelfReferenceException(const std::string &message)
";


// File: classSimpleSelectionRule.xml
%feature("docstring") SimpleSelectionRule "

Selection rule (v*q)modulus!=0, defined by vector v(a,b,c) and modulus.

C++ includes: ISelectionRule.h
";

%feature("docstring")  SimpleSelectionRule::SimpleSelectionRule "SimpleSelectionRule::SimpleSelectionRule(int a, int b, int c, int modulus)
";

%feature("docstring")  SimpleSelectionRule::~SimpleSelectionRule "virtual SimpleSelectionRule::~SimpleSelectionRule()
";

%feature("docstring")  SimpleSelectionRule::clone "SimpleSelectionRule * SimpleSelectionRule::clone() const
";

%feature("docstring")  SimpleSelectionRule::coordinateSelected "bool SimpleSelectionRule::coordinateSelected(const ivector_t &coordinate) const
";


// File: classSimulation.xml
%feature("docstring") Simulation "

Pure virtual base class of OffSpecularSimulation and  GISASSimulation, holds common infrastructure to run a simulation.

C++ includes: Simulation.h
";

%feature("docstring")  Simulation::Simulation "Simulation::Simulation()
";

%feature("docstring")  Simulation::Simulation "Simulation::Simulation(const MultiLayer &p_sample)
";

%feature("docstring")  Simulation::Simulation "Simulation::Simulation(const std::shared_ptr< IMultiLayerBuilder > p_sample_builder)
";

%feature("docstring")  Simulation::~Simulation "Simulation::~Simulation()
";

%feature("docstring")  Simulation::clone "virtual Simulation* Simulation::clone() const =0
";

%feature("docstring")  Simulation::prepareSimulation "void Simulation::prepareSimulation()

Put into a clean state for running a simulation. 
";

%feature("docstring")  Simulation::runSimulation "void Simulation::runSimulation()

Run a simulation, possibly averaged over parameter distributions.

Run simulation with possible averaging over parameter distributions. 
";

%feature("docstring")  Simulation::setInstrument "void Simulation::setInstrument(const Instrument &instrument)
";

%feature("docstring")  Simulation::getInstrument "const Instrument& Simulation::getInstrument() const
";

%feature("docstring")  Simulation::getInstrument "Instrument& Simulation::getInstrument()
";

%feature("docstring")  Simulation::setBeamIntensity "void Simulation::setBeamIntensity(double intensity)
";

%feature("docstring")  Simulation::getBeamIntensity "double Simulation::getBeamIntensity() const
";

%feature("docstring")  Simulation::setBeamPolarization "void Simulation::setBeamPolarization(const kvector_t bloch_vector)

Sets the beam polarization according to the given Bloch vector. 
";

%feature("docstring")  Simulation::setDetectorResolutionFunction "void Simulation::setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function)
";

%feature("docstring")  Simulation::removeDetectorResolutionFunction "void Simulation::removeDetectorResolutionFunction()
";

%feature("docstring")  Simulation::setAnalyzerProperties "void Simulation::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  Simulation::setSample "void Simulation::setSample(const MultiLayer &sample)

The  MultiLayer object will not be owned by the  Simulation object. 
";

%feature("docstring")  Simulation::getSample "MultiLayer* Simulation::getSample() const
";

%feature("docstring")  Simulation::setSampleBuilder "void Simulation::setSampleBuilder(const std::shared_ptr< IMultiLayerBuilder > sample_builder)
";

%feature("docstring")  Simulation::getSampleBuilder "std::shared_ptr<IMultiLayerBuilder> Simulation::getSampleBuilder() const
";

%feature("docstring")  Simulation::numberOfSimulationElements "virtual int Simulation::numberOfSimulationElements() const =0
";

%feature("docstring")  Simulation::getDetectorIntensity "virtual OutputData<double>* Simulation::getDetectorIntensity(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const =0

Clone simulated intensity map. 
";

%feature("docstring")  Simulation::addSimulationParametersToExternalPool "std::string Simulation::addSimulationParametersToExternalPool(const std::string &path, ParameterPool *external_pool) const

Adds parameters defined in this class the to external pool. 
";

%feature("docstring")  Simulation::addParameterDistribution "void Simulation::addParameterDistribution(const std::string &param_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits())
";

%feature("docstring")  Simulation::addParameterDistribution "void Simulation::addParameterDistribution(const ParameterDistribution &par_distr)
";

%feature("docstring")  Simulation::getDistributionHandler "const DistributionHandler& Simulation::getDistributionHandler() const
";

%feature("docstring")  Simulation::setOptions "void Simulation::setOptions(const SimulationOptions &options)
";

%feature("docstring")  Simulation::getOptions "const SimulationOptions& Simulation::getOptions() const
";

%feature("docstring")  Simulation::getOptions "SimulationOptions& Simulation::getOptions()
";

%feature("docstring")  Simulation::subscribe "void Simulation::subscribe(ProgressHandler::Callback_t inform)
";

%feature("docstring")  Simulation::setTerminalProgressMonitor "void Simulation::setTerminalProgressMonitor()

Initializes a progress monitor that prints to stdout. 
";


// File: classSimulationArea.xml
%feature("docstring") SimulationArea "

Holds iteration logic over active detector channels in the presence of masked areas and  RegionOfInterest defined.

C++ includes: SimulationArea.h
";

%feature("docstring")  SimulationArea::SimulationArea "SimulationArea::SimulationArea(const IDetector2D *detector)
";

%feature("docstring")  SimulationArea::~SimulationArea "virtual SimulationArea::~SimulationArea()
";

%feature("docstring")  SimulationArea::begin "SimulationAreaIterator SimulationArea::begin()
";

%feature("docstring")  SimulationArea::end "SimulationAreaIterator SimulationArea::end()
";

%feature("docstring")  SimulationArea::isMasked "bool SimulationArea::isMasked(size_t index) const

returns trus if given iterator index correspond to masked detector channel 
";

%feature("docstring")  SimulationArea::totalSize "size_t SimulationArea::totalSize() const
";

%feature("docstring")  SimulationArea::roiIndex "size_t SimulationArea::roiIndex(size_t index) const

Return index in ROI map from iterator index. 
";

%feature("docstring")  SimulationArea::detectorIndex "size_t SimulationArea::detectorIndex(size_t index) const

Return detector index from iterator index. 
";


// File: classSimulationAreaIterator.xml
%feature("docstring") SimulationAreaIterator "

An iterator for  SimulationArea.

C++ includes: SimulationAreaIterator.h
";

%feature("docstring")  SimulationAreaIterator::SimulationAreaIterator "SimulationAreaIterator::SimulationAreaIterator(const SimulationArea *area, size_t start_at_index)
";

%feature("docstring")  SimulationAreaIterator::index "size_t SimulationAreaIterator::index() const
";

%feature("docstring")  SimulationAreaIterator::elementIndex "size_t SimulationAreaIterator::elementIndex() const
";

%feature("docstring")  SimulationAreaIterator::roiIndex "int SimulationAreaIterator::roiIndex() const
";

%feature("docstring")  SimulationAreaIterator::detectorIndex "int SimulationAreaIterator::detectorIndex() const
";


// File: classSimulationElement.xml
%feature("docstring") SimulationElement "

Data stucture containing both input and output of a single detector cell.

C++ includes: SimulationElement.h
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i, std::unique_ptr< IPixelMap > pixelmap)
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(const SimulationElement &other)
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(const SimulationElement &other, double x, double y)

Construct  SimulationElement from other element and restrict k_f to specific value in the original detector pixel 
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(SimulationElement &&other) noexcept
";

%feature("docstring")  SimulationElement::~SimulationElement "SimulationElement::~SimulationElement()
";

%feature("docstring")  SimulationElement::setPolarization "void SimulationElement::setPolarization(const Eigen::Matrix2cd &polarization)

Sets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::getPolarization "Eigen::Matrix2cd SimulationElement::getPolarization() const

Gets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::setAnalyzerOperator "void SimulationElement::setAnalyzerOperator(const Eigen::Matrix2cd &polarization_operator)

Sets the polarization analyzer operator (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::getAnalyzerOperator "Eigen::Matrix2cd SimulationElement::getAnalyzerOperator() const

Gets the polarization analyzer operator (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::getWavelength "double SimulationElement::getWavelength() const
";

%feature("docstring")  SimulationElement::getAlphaI "double SimulationElement::getAlphaI() const
";

%feature("docstring")  SimulationElement::getPhiI "double SimulationElement::getPhiI() const
";

%feature("docstring")  SimulationElement::getAlphaMean "double SimulationElement::getAlphaMean() const
";

%feature("docstring")  SimulationElement::getPhiMean "double SimulationElement::getPhiMean() const
";

%feature("docstring")  SimulationElement::setIntensity "void SimulationElement::setIntensity(double intensity)
";

%feature("docstring")  SimulationElement::addIntensity "void SimulationElement::addIntensity(double intensity)
";

%feature("docstring")  SimulationElement::getIntensity "double SimulationElement::getIntensity() const
";

%feature("docstring")  SimulationElement::getKI "kvector_t SimulationElement::getKI() const
";

%feature("docstring")  SimulationElement::getMeanKF "kvector_t SimulationElement::getMeanKF() const
";

%feature("docstring")  SimulationElement::getMeanQ "kvector_t SimulationElement::getMeanQ() const
";

%feature("docstring")  SimulationElement::getQ "kvector_t SimulationElement::getQ(double x, double y) const
";

%feature("docstring")  SimulationElement::getK "kvector_t SimulationElement::getK(double x, double y) const
";

%feature("docstring")  SimulationElement::getIntegrationFactor "double SimulationElement::getIntegrationFactor(double x, double y) const
";

%feature("docstring")  SimulationElement::getSolidAngle "double SimulationElement::getSolidAngle() const
";

%feature("docstring")  SimulationElement::getAlpha "double SimulationElement::getAlpha(double x, double y) const
";

%feature("docstring")  SimulationElement::getPhi "double SimulationElement::getPhi(double x, double y) const
";

%feature("docstring")  SimulationElement::containsSpecularWavevector "bool SimulationElement::containsSpecularWavevector() const

check if element contains given wavevector 
";

%feature("docstring")  SimulationElement::setSpecular "void SimulationElement::setSpecular(bool contains_specular)

indicate that this element contains the specular wavevector 
";


// File: classSimulationFactory.xml
%feature("docstring") SimulationFactory "

Registry to create standard pre-defined simulations. Used in functional tests, performance measurements, etc.

C++ includes: SimulationFactory.h
";

%feature("docstring")  SimulationFactory::SimulationFactory "SimulationFactory::SimulationFactory()
";


// File: classSimulationOptions.xml
%feature("docstring") SimulationOptions "

Collect the different options for simulation  SimulationOptions.

C++ includes: SimulationOptions.h
";

%feature("docstring")  SimulationOptions::SimulationOptions "SimulationOptions::SimulationOptions()
";

%feature("docstring")  SimulationOptions::isIntegrate "bool SimulationOptions::isIntegrate() const
";

%feature("docstring")  SimulationOptions::getMcPoints "size_t SimulationOptions::getMcPoints() const
";

%feature("docstring")  SimulationOptions::setMonteCarloIntegration "void SimulationOptions::setMonteCarloIntegration(bool flag=true, size_t mc_points=50)

Enables/disables MonetCarlo integration.

Parameters:
-----------

flag: 
If true, MonteCarlo integration will be used, otherwise analytical calculations

mc_points: 
Number of points for MonteCarlo integrator 
";

%feature("docstring")  SimulationOptions::setNumberOfThreads "void SimulationOptions::setNumberOfThreads(int nthreads)

Sets number of threads to use during the simulation (0 - take the default value from the hardware) 
";

%feature("docstring")  SimulationOptions::getNumberOfThreads "int SimulationOptions::getNumberOfThreads() const
";

%feature("docstring")  SimulationOptions::setNumberOfBatches "void SimulationOptions::setNumberOfBatches(int nbatches)

Sets number of batches to split. 
";

%feature("docstring")  SimulationOptions::getNumberOfBatches "int SimulationOptions::getNumberOfBatches() const
";

%feature("docstring")  SimulationOptions::getCurrentBatch "int SimulationOptions::getCurrentBatch() const
";

%feature("docstring")  SimulationOptions::setThreadInfo "void SimulationOptions::setThreadInfo(const ThreadInfo &thread_info)

Sets the batch and thread information to be used. 
";

%feature("docstring")  SimulationOptions::getHardwareConcurrency "int SimulationOptions::getHardwareConcurrency() const
";

%feature("docstring")  SimulationOptions::getDefaultVariability "double SimulationOptions::getDefaultVariability() const
";

%feature("docstring")  SimulationOptions::setIncludeSpecular "void SimulationOptions::setIncludeSpecular(bool include_specular)
";

%feature("docstring")  SimulationOptions::includeSpecular "bool SimulationOptions::includeSpecular() const
";


// File: classSimulationRoiArea.xml
%feature("docstring") SimulationRoiArea "

Holds iteration logic over active detector channels in the presence of ROI. On the contrary to  SimulationArea class, iterates also over masked areas.

C++ includes: SimulationArea.h
";

%feature("docstring")  SimulationRoiArea::SimulationRoiArea "SimulationRoiArea::SimulationRoiArea(const IDetector2D *detector)
";

%feature("docstring")  SimulationRoiArea::isMasked "bool SimulationRoiArea::isMasked(size_t) const

returns trus if given iterator index correspond to masked detector channel 
";


// File: classSizeDistributionDAModelBuilder.xml
%feature("docstring") SizeDistributionDAModelBuilder "

Creates the sample demonstrating size distribution model in decoupling approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationDA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionDAModelBuilder::SizeDistributionDAModelBuilder "SizeDistributionDAModelBuilder::SizeDistributionDAModelBuilder()
";

%feature("docstring")  SizeDistributionDAModelBuilder::buildSample "MultiLayer * SizeDistributionDAModelBuilder::buildSample() const
";


// File: classSizeDistributionLMAModelBuilder.xml
%feature("docstring") SizeDistributionLMAModelBuilder "

Creates the sample demonstrating size distribution model in local monodisperse approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationLMA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionLMAModelBuilder::SizeDistributionLMAModelBuilder "SizeDistributionLMAModelBuilder::SizeDistributionLMAModelBuilder()
";

%feature("docstring")  SizeDistributionLMAModelBuilder::buildSample "MultiLayer * SizeDistributionLMAModelBuilder::buildSample() const
";


// File: classSizeDistributionSSCAModelBuilder.xml
%feature("docstring") SizeDistributionSSCAModelBuilder "

Creates the sample demonstrating size distribution model in size space coupling approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationSSCA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionSSCAModelBuilder::SizeDistributionSSCAModelBuilder "SizeDistributionSSCAModelBuilder::SizeDistributionSSCAModelBuilder()
";

%feature("docstring")  SizeDistributionSSCAModelBuilder::buildSample "MultiLayer * SizeDistributionSSCAModelBuilder::buildSample() const
";


// File: classSpecularComputation.xml
%feature("docstring") SpecularComputation "

Computes the specular scattering. Controlled by  MainComputation.

C++ includes: SpecularComputation.h
";

%feature("docstring")  SpecularComputation::SpecularComputation "SpecularComputation::SpecularComputation()
";

%feature("docstring")  SpecularComputation::eval "void SpecularComputation::eval(ProgressHandler *progress, bool polarized, const std::vector< SimulationElement >::iterator &begin_it, const std::vector< SimulationElement >::iterator &end_it)
";

%feature("docstring")  SpecularComputation::setSpecularInfo "void SpecularComputation::setSpecularInfo(const LayerSpecularInfo &specular_info)
";


// File: classSpecularMagnetic.xml
%feature("docstring") SpecularMagnetic "

Implements the matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization.

C++ includes: SpecularMagnetic.h
";


// File: classSpecularMatrix.xml
%feature("docstring") SpecularMatrix "

Implements method 'execute' to compute refraction angles and transmission/reflection coefficients for coherent wave propagation in a multilayer.

C++ includes: SpecularMatrix.h
";


// File: classSpecularSimulation.xml
%feature("docstring") SpecularSimulation "

Main class to run a specular simulation.

C++ includes: SpecularSimulation.h
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation()
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation(const ISample &sample)
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation(const std::shared_ptr< IMultiLayerBuilder > sample_builder)
";

%feature("docstring")  SpecularSimulation::~SpecularSimulation "SpecularSimulation::~SpecularSimulation()
";

%feature("docstring")  SpecularSimulation::clone "SpecularSimulation * SpecularSimulation::clone() const
";

%feature("docstring")  SpecularSimulation::runSimulation "void SpecularSimulation::runSimulation()

Run a simulation with the current parameter settings. 
";

%feature("docstring")  SpecularSimulation::setSample "void SpecularSimulation::setSample(const ISample &sample)

Sets the sample to be tested. 
";

%feature("docstring")  SpecularSimulation::getSample "ISample* SpecularSimulation::getSample() const

Returns the sample. 
";

%feature("docstring")  SpecularSimulation::setSampleBuilder "void SpecularSimulation::setSampleBuilder(std::shared_ptr< IMultiLayerBuilder > sample_builder)

Sets the sample builder. 
";

%feature("docstring")  SpecularSimulation::getSampleBuilder "std::shared_ptr<IMultiLayerBuilder> SpecularSimulation::getSampleBuilder() const

return sample builder 
";

%feature("docstring")  SpecularSimulation::setBeamParameters "void SpecularSimulation::setBeamParameters(double lambda, const IAxis &alpha_axis)

Sets beam parameters with alpha_i of the beam defined in the range. 
";

%feature("docstring")  SpecularSimulation::setBeamParameters "void SpecularSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max)
";

%feature("docstring")  SpecularSimulation::setEvanescentWaveAxis "void SpecularSimulation::setEvanescentWaveAxis(const IAxis &z_axis)

set axis for evanescent wave axis 
";

%feature("docstring")  SpecularSimulation::setEvanescentWaveAxis "void SpecularSimulation::setEvanescentWaveAxis(int nbins, double z_min, double z_max)
";

%feature("docstring")  SpecularSimulation::getAlphaAxis "const IAxis * SpecularSimulation::getAlphaAxis() const

returns alpha_i axis 
";

%feature("docstring")  SpecularSimulation::getScalarR "std::vector< complex_t > SpecularSimulation::getScalarR(size_t i_layer) const

returns vector of reflection coefficients for all alpha_i angles for given layer index 
";

%feature("docstring")  SpecularSimulation::getScalarT "std::vector< complex_t > SpecularSimulation::getScalarT(size_t i_layer) const

returns vector of transmission coefficients for all alpha_i angles for given layer index 
";

%feature("docstring")  SpecularSimulation::getScalarKz "std::vector< complex_t > SpecularSimulation::getScalarKz(size_t i_layer) const

returns vector of Kz coefficients for all alpha_i angles for given layer index 
";

%feature("docstring")  SpecularSimulation::getLayerRTCoefficients "SpecularSimulation::LayerRTCoefficients_t SpecularSimulation::getLayerRTCoefficients(size_t i_alpha, size_t i_layer) const
";

%feature("docstring")  SpecularSimulation::prepareSimulation "void SpecularSimulation::prepareSimulation()

Put into a clean state for running a simulation. 
";


// File: classSphericalDetector.xml
%feature("docstring") SphericalDetector "

A spherical detector with axes and resolution function.  SphericalDetector

C++ includes: SphericalDetector.h
";

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector()
";

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

Spherical detector constructor using angle ranges

Parameters:
-----------

n_phi: 
number of phi-axis bins

phi_min: 
low edge of first phi-bin

phi_max: 
upper edge of last phi-bin

n_alpha: 
number of alpha-axis bins

alpha_min: 
low edge of first alpha-bin

alpha_max: 
upper edge of last alpha-bin 
";

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector(const SphericalDetector &other)
";

%feature("docstring")  SphericalDetector::clone "SphericalDetector * SphericalDetector::clone() const override
";

%feature("docstring")  SphericalDetector::~SphericalDetector "SphericalDetector::~SphericalDetector() override
";

%feature("docstring")  SphericalDetector::addParametersToExternalPool "std::string SphericalDetector::addParametersToExternalPool(const std::string &path, ParameterPool *external_pool, int copy_number=-1) const override

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  SphericalDetector::getValidAxesUnits "std::vector< IDetector2D::EAxesUnits > SphericalDetector::getValidAxesUnits() const override

returns vector of valid axes units 
";

%feature("docstring")  SphericalDetector::getDefaultAxesUnits "IDetector2D::EAxesUnits SphericalDetector::getDefaultAxesUnits() const override

return default axes units 
";


// File: classSquaredFunctionDefault.xml
%feature("docstring") SquaredFunctionDefault "

Squared difference between two values.

value = (a-b)*(a-b)/norm, where norm = max(b, 1.0) a - simulated values, b - real_values

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionDefault::SquaredFunctionDefault "SquaredFunctionDefault::SquaredFunctionDefault()
";

%feature("docstring")  SquaredFunctionDefault::~SquaredFunctionDefault "virtual SquaredFunctionDefault::~SquaredFunctionDefault()
";

%feature("docstring")  SquaredFunctionDefault::clone "virtual SquaredFunctionDefault* SquaredFunctionDefault::clone() const
";

%feature("docstring")  SquaredFunctionDefault::calculateSquaredDifference "virtual double SquaredFunctionDefault::calculateSquaredDifference(double real_value, double simulated_value) const
";

%feature("docstring")  SquaredFunctionDefault::calculateSquaredError "virtual double SquaredFunctionDefault::calculateSquaredError(double real_value, double simulated_value=0) const
";


// File: classSquaredFunctionGaussianError.xml
%feature("docstring") SquaredFunctionGaussianError "

Squared difference between two values with gaussian error.

value = (a-b)*(a-b)/norm, where norm = sigma*sigma, sigma - is set by user

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionGaussianError::SquaredFunctionGaussianError "SquaredFunctionGaussianError::SquaredFunctionGaussianError(double sigma=0.01)
";

%feature("docstring")  SquaredFunctionGaussianError::~SquaredFunctionGaussianError "virtual SquaredFunctionGaussianError::~SquaredFunctionGaussianError()
";

%feature("docstring")  SquaredFunctionGaussianError::clone "virtual SquaredFunctionGaussianError* SquaredFunctionGaussianError::clone() const
";

%feature("docstring")  SquaredFunctionGaussianError::calculateSquaredDifference "virtual double SquaredFunctionGaussianError::calculateSquaredDifference(double real_value, double simulated_value) const
";

%feature("docstring")  SquaredFunctionGaussianError::calculateSquaredError "virtual double SquaredFunctionGaussianError::calculateSquaredError(double, double) const
";


// File: classSquaredFunctionMeanSquaredError.xml
%feature("docstring") SquaredFunctionMeanSquaredError "

Squared difference between two values normalized by mean squared error.

value = (a-b)*(a-b)/norm, where norm = sqrt(sigma1*sigma1 + sigma2*sigma2), sigma1=max(a, 1.0), sigma2=max(b,1.0)

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionMeanSquaredError::SquaredFunctionMeanSquaredError "SquaredFunctionMeanSquaredError::SquaredFunctionMeanSquaredError()
";

%feature("docstring")  SquaredFunctionMeanSquaredError::~SquaredFunctionMeanSquaredError "virtual SquaredFunctionMeanSquaredError::~SquaredFunctionMeanSquaredError()
";

%feature("docstring")  SquaredFunctionMeanSquaredError::clone "virtual SquaredFunctionMeanSquaredError* SquaredFunctionMeanSquaredError::clone() const
";

%feature("docstring")  SquaredFunctionMeanSquaredError::calculateSquaredDifference "virtual double SquaredFunctionMeanSquaredError::calculateSquaredDifference(double real_value, double simulated_value) const
";

%feature("docstring")  SquaredFunctionMeanSquaredError::calculateSquaredError "virtual double SquaredFunctionMeanSquaredError::calculateSquaredError(double real_value, double simulated_value) const
";


// File: classSquaredFunctionSimError.xml
%feature("docstring") SquaredFunctionSimError "

Squared difference between two values.

value = (a-b)*(a-b)/norm, where norm = max(a, 1.0) a - simulated values, b - real_values

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionSimError::SquaredFunctionSimError "SquaredFunctionSimError::SquaredFunctionSimError()
";

%feature("docstring")  SquaredFunctionSimError::~SquaredFunctionSimError "virtual SquaredFunctionSimError::~SquaredFunctionSimError()
";

%feature("docstring")  SquaredFunctionSimError::clone "virtual SquaredFunctionSimError* SquaredFunctionSimError::clone() const
";

%feature("docstring")  SquaredFunctionSimError::calculateSquaredDifference "virtual double SquaredFunctionSimError::calculateSquaredDifference(double real_value, double simulated_value) const
";

%feature("docstring")  SquaredFunctionSimError::calculateSquaredError "virtual double SquaredFunctionSimError::calculateSquaredError(double, double simulated_value) const
";


// File: classSquaredFunctionSystematicError.xml
%feature("docstring") SquaredFunctionSystematicError "

Squared difference between two values normalized by systematic error.

value = (a-b)*(a-b)/norm, where norm = max(error, 1.0), error = b + (epsilon*b)**2

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionSystematicError::SquaredFunctionSystematicError "SquaredFunctionSystematicError::SquaredFunctionSystematicError(double epsilon=0.08)
";

%feature("docstring")  SquaredFunctionSystematicError::~SquaredFunctionSystematicError "virtual SquaredFunctionSystematicError::~SquaredFunctionSystematicError()
";

%feature("docstring")  SquaredFunctionSystematicError::clone "virtual SquaredFunctionSystematicError* SquaredFunctionSystematicError::clone() const
";

%feature("docstring")  SquaredFunctionSystematicError::calculateSquaredDifference "virtual double SquaredFunctionSystematicError::calculateSquaredDifference(double real_value, double simulated_value) const
";

%feature("docstring")  SquaredFunctionSystematicError::calculateSquaredError "virtual double SquaredFunctionSystematicError::calculateSquaredError(double real_value, double) const
";


// File: classSquareLatticeBuilder.xml
%feature("docstring") SquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  SquareLatticeBuilder::SquareLatticeBuilder "SquareLatticeBuilder::SquareLatticeBuilder()
";

%feature("docstring")  SquareLatticeBuilder::buildSample "MultiLayer * SquareLatticeBuilder::buildSample() const
";


// File: classSSCApproximationStrategy.xml
%feature("docstring") SSCApproximationStrategy "

Virtual base class for  SSCApproximationStrategy1 and  SSCApproximationStrategy2, which compute the total scalar/polarized scattering from a decorated layer in size-spacing correlation approximation.

C++ includes: SSCApproximationStrategy.h
";

%feature("docstring")  SSCApproximationStrategy::SSCApproximationStrategy "SSCApproximationStrategy::SSCApproximationStrategy(double kappa)
";


// File: classSSCApproximationStrategy1.xml
%feature("docstring") SSCApproximationStrategy1 "

Strategy class to compute the total scalar scattering from a decorated layer in size-spacing correlation approximation.

C++ includes: SSCApproximationStrategy.h
";

%feature("docstring")  SSCApproximationStrategy1::SSCApproximationStrategy1 "SSCApproximationStrategy1::SSCApproximationStrategy1(SimulationOptions sim_params, double kappa)
";


// File: classSSCApproximationStrategy2.xml
%feature("docstring") SSCApproximationStrategy2 "

Strategy class to compute the total polarized scattering from a decorated layer in size-spacing correlation approximation.

C++ includes: SSCApproximationStrategy.h
";

%feature("docstring")  SSCApproximationStrategy2::SSCApproximationStrategy2 "SSCApproximationStrategy2::SSCApproximationStrategy2(SimulationOptions sim_params, double kappa)
";


// File: classStringUsageMap.xml
%feature("docstring") StringUsageMap "

Counts how often a string is used.

C++ includes: StringUsageMap.h
";

%feature("docstring")  StringUsageMap::StringUsageMap "StringUsageMap::StringUsageMap()
";

%feature("docstring")  StringUsageMap::~StringUsageMap "StringUsageMap::~StringUsageMap()
";

%feature("docstring")  StringUsageMap::add "void StringUsageMap::add(const std::string &name)

Adds string to the map, or increments usage counter. 
";

%feature("docstring")  StringUsageMap::begin "iterator_t StringUsageMap::begin()

access to the map of strings 
";

%feature("docstring")  StringUsageMap::end "iterator_t StringUsageMap::end()
";

%feature("docstring")  StringUsageMap::get_current "std::string StringUsageMap::get_current() const

Returns current string. 
";


// File: structThreadInfo.xml
%feature("docstring") ThreadInfo "

Information to run simulation with dedicated number of threads.

C++ includes: ThreadInfo.h
";

%feature("docstring")  ThreadInfo::ThreadInfo "ThreadInfo::ThreadInfo()
";


// File: classTRange.xml
%feature("docstring") TRange "

An interval [lowerBound..upperBound[.

C++ includes: TRange.h
";

%feature("docstring")  TRange::TRange "TRange< T >::TRange(T lowerBound, T upperBound)
";

%feature("docstring")  TRange::~TRange "virtual TRange< T >::~TRange()
";

%feature("docstring")  TRange::getLowerBound "T TRange< T >::getLowerBound() const
";

%feature("docstring")  TRange::getUpperBound "T TRange< T >::getUpperBound() const
";

%feature("docstring")  TRange::getDifference "T TRange< T >::getDifference() const
";

%feature("docstring")  TRange::inRange "bool TRange< T >::inRange(T value) const
";


// File: classTransform3D.xml
%feature("docstring") Transform3D "

Vector transformations in three dimensions.

C++ includes: Transform3D.h
";

%feature("docstring")  Transform3D::Transform3D "Transform3D::Transform3D()

Constructs unit transformation. 
";

%feature("docstring")  Transform3D::Transform3D "Transform3D::Transform3D(const Transform3D &other)

Copy constructor. 
";

%feature("docstring")  Transform3D::~Transform3D "Transform3D::~Transform3D()

Destructor. 
";

%feature("docstring")  Transform3D::clone "Transform3D * Transform3D::clone() const

Clones the transformation. 
";

%feature("docstring")  Transform3D::calculateEulerAngles "void Transform3D::calculateEulerAngles(double *p_alpha, double *p_beta, double *p_gamma) const

Calculates the Euler angles corresponding to the rotation. 
";

%feature("docstring")  Transform3D::getInverse "Transform3D Transform3D::getInverse() const

Returns the inverse transformation. 
";

%feature("docstring")  Transform3D::transformed "BasicVector3D< double > Transform3D::transformed(const BasicVector3D< double > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::transformed "BasicVector3D< complex_t > Transform3D::transformed(const BasicVector3D< complex_t > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::transformedInverse "BasicVector3D< double > Transform3D::transformedInverse(const BasicVector3D< double > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::transformedInverse "BasicVector3D< complex_t > Transform3D::transformedInverse(const BasicVector3D< complex_t > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::getRotationType "Transform3D::ERotationType Transform3D::getRotationType() const

Retrieve the rotation type (general, around x, y or z-axis) 
";

%feature("docstring")  Transform3D::isIdentity "bool Transform3D::isIdentity() const

Determine if the transformation is trivial (identity) 
";

%feature("docstring")  Transform3D::print "void Transform3D::print(std::ostream &ostr) const
";


// File: classTransformBoxBuilder.xml
%feature("docstring") TransformBoxBuilder "

Rotated box in 3 layers system.

C++ includes: TransformationsBuilder.h
";

%feature("docstring")  TransformBoxBuilder::TransformBoxBuilder "TransformBoxBuilder::TransformBoxBuilder()
";

%feature("docstring")  TransformBoxBuilder::buildSample "MultiLayer * TransformBoxBuilder::buildSample() const
";


// File: classTriangularRippleBuilder.xml
%feature("docstring") TriangularRippleBuilder "

Builds sample: triangular ripple within the 1D-paracrystal model (from PRB 85, 235415, 2012)

C++ includes: RipplesBuilder.h
";

%feature("docstring")  TriangularRippleBuilder::TriangularRippleBuilder "TriangularRippleBuilder::TriangularRippleBuilder()
";

%feature("docstring")  TriangularRippleBuilder::buildSample "MultiLayer * TriangularRippleBuilder::buildSample() const
";


// File: classTSampledRange.xml
%feature("docstring") TSampledRange "

An interval [lowerBound..upperBound[, and a number of samples.

C++ includes: TRange.h
";

%feature("docstring")  TSampledRange::TSampledRange "TSampledRange< T >::TSampledRange(size_t n_samples, T lowerBound, T upperBound)
";

%feature("docstring")  TSampledRange::getNSamples "size_t TSampledRange< T >::getNSamples() const
";


// File: classTwoTypesCylindersDistributionBuilder.xml
%feature("docstring") TwoTypesCylindersDistributionBuilder "

Builds mixture of cylinder particles with different size distribution (IsGISAXS example #2)

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder "TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder()
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::buildSample "MultiLayer * TwoTypesCylindersDistributionBuilder::buildSample() const
";


// File: classUnit.xml
%feature("docstring") Unit "

A physical unit.

C++ includes: Unit.h
";

%feature("docstring")  Unit::Unit "Unit::Unit(const std::string &name=\"\")
";

%feature("docstring")  Unit::setUnit "void Unit::setUnit(const std::string &name)
";


// File: classException_1_1UnknownClassRegistrationException.xml
%feature("docstring") Exception::UnknownClassRegistrationException "";

%feature("docstring")  Exception::UnknownClassRegistrationException::UnknownClassRegistrationException "Exception::UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
";


// File: classVariableBinAxis.xml
%feature("docstring") VariableBinAxis "

Axis with variable bin size.

C++ includes: VariableBinAxis.h
";

%feature("docstring")  VariableBinAxis::VariableBinAxis "VariableBinAxis::VariableBinAxis(const std::string &name, size_t nbins, const std::vector< double > &bin_boundaries)

VariableBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

bin_boundaries: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin. 
";

%feature("docstring")  VariableBinAxis::~VariableBinAxis "virtual VariableBinAxis::~VariableBinAxis()
";

%feature("docstring")  VariableBinAxis::clone "VariableBinAxis * VariableBinAxis::clone() const

clone function 
";

%feature("docstring")  VariableBinAxis::size "size_t VariableBinAxis::size() const

retrieve the number of bins 
";

%feature("docstring")  VariableBinAxis::getBin "Bin1D VariableBinAxis::getBin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  VariableBinAxis::getMin "double VariableBinAxis::getMin() const

Returns value of first point of axis. 
";

%feature("docstring")  VariableBinAxis::getMax "double VariableBinAxis::getMax() const

Returns value of last point of axis. 
";

%feature("docstring")  VariableBinAxis::getBinCenter "double VariableBinAxis::getBinCenter(size_t index) const
";

%feature("docstring")  VariableBinAxis::findClosestIndex "size_t VariableBinAxis::findClosestIndex(double value) const

find bin index which is best match for given value 
";

%feature("docstring")  VariableBinAxis::getBinCenters "std::vector< double > VariableBinAxis::getBinCenters() const
";

%feature("docstring")  VariableBinAxis::getBinBoundaries "std::vector<double> VariableBinAxis::getBinBoundaries() const
";

%feature("docstring")  VariableBinAxis::createClippedAxis "VariableBinAxis * VariableBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classGeometry_1_1VerticalLine.xml
%feature("docstring") Geometry::VerticalLine "

An infinite vertical line.

C++ includes: Line.h
";

%feature("docstring")  Geometry::VerticalLine::VerticalLine "Geometry::VerticalLine::VerticalLine(double x)

Parameters:
-----------

x: 
The value at which it crosses x-axes 
";

%feature("docstring")  Geometry::VerticalLine::clone "VerticalLine* Geometry::VerticalLine::clone() const
";

%feature("docstring")  Geometry::VerticalLine::contains "bool Geometry::VerticalLine::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::VerticalLine::contains "bool Geometry::VerticalLine::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  Geometry::VerticalLine::getXpos "double Geometry::VerticalLine::getXpos() const
";


// File: classWavevectorInfo.xml
%feature("docstring") WavevectorInfo "

Holds all wavevector information relevant for calculating form factors.

C++ includes: WavevectorInfo.h
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo()
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo(cvector_t ki, cvector_t kf, double wavelength)
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo(kvector_t ki, kvector_t kf, double wavelength)
";

%feature("docstring")  WavevectorInfo::getKi "cvector_t WavevectorInfo::getKi() const
";

%feature("docstring")  WavevectorInfo::getKf "cvector_t WavevectorInfo::getKf() const
";

%feature("docstring")  WavevectorInfo::getQ "cvector_t WavevectorInfo::getQ() const
";

%feature("docstring")  WavevectorInfo::getWavelength "double WavevectorInfo::getWavelength() const
";


// File: classMathFunctions_1_1Convolve_1_1Workspace.xml


// File: namespace_0D276.xml


// File: namespace_0D306.xml


// File: namespace_0D429.xml


// File: namespace_0D57.xml


// File: namespace_0D72.xml


// File: namespaceboost_1_1geometry.xml


// File: namespaceBornAgain.xml


// File: namespaceDetectorFunctions.xml
%feature("docstring")  DetectorFunctions::hasSameDimensions "bool DetectorFunctions::hasSameDimensions(const IDetector2D &detector, const OutputData< double > &data)

Returns true if the data has same axes size (nx,ny) with the detector. 
";

%feature("docstring")  DetectorFunctions::axesToString "std::string DetectorFunctions::axesToString(const IDetector2D &detector)

Returns string representation of axes dimension in the form \"(nx,ny)\". 
";

%feature("docstring")  DetectorFunctions::axesToString "std::string DetectorFunctions::axesToString(const OutputData< double > &data)

Returns string representation of axes dimension in the form \"(nx,ny)\". 
";

%feature("docstring")  DetectorFunctions::createDataSet "std::unique_ptr< OutputData< double > > DetectorFunctions::createDataSet(const Instrument &instrument, const OutputData< double > &data, bool put_masked_areas_to_zero=true, IDetector2D::EAxesUnits units=IDetector2D::DEFAULT)

Creates real data containing original user data clipped to the ROI area of the detector. If put_masked_areas_to_zero==true: resulting data will have 0.0 in all masked areas If put_masked_areas_to_zero==false: resulting data will be only cropped, masked areas will still contain intensities TODO: what users will like more (this appears on FitSuitePlotObserver)? 
";


// File: namespaceException.xml
%feature("docstring")  Exception::LogExceptionMessage "void Exception::LogExceptionMessage(const std::string &message)
";


// File: namespaceFileSystem.xml
%feature("docstring")  FileSystem::extension "std::string FileSystem::extension(const std::string &fname)

Returns extension of given filename. 
";

%feature("docstring")  FileSystem::createDirectory "bool FileSystem::createDirectory(const std::string &dir_name)

Creates directory in current directory. 
";

%feature("docstring")  FileSystem::filesInDirectory "std::vector< std::string > FileSystem::filesInDirectory(const std::string &dir_name)

Returns filenames of files in directory. 
";

%feature("docstring")  FileSystem::jointPath "std::string FileSystem::jointPath(const std::string &spath1, const std::string &spath2)

Returns joint path name. 
";

%feature("docstring")  FileSystem::filename "std::string FileSystem::filename(const std::string &path)

Returns path without directory part (\"Foo/Bar/Doz.int.gz\" -> \"Doz.int.gz\") 
";

%feature("docstring")  FileSystem::glob "std::vector< std::string > FileSystem::glob(const std::string &dir, const std::string &pattern)

Returns file names that agree with a regex glob pattern. 
";


// File: namespaceGeometry.xml


// File: namespaceIntensityDataFunctions.xml
%feature("docstring")  IntensityDataFunctions::getRelativeDifference "BA_CORE_API_ double IntensityDataFunctions::getRelativeDifference(const OutputData< double > &dat, const OutputData< double > &ref)
";

%feature("docstring")  IntensityDataFunctions::getRelativeDifference "BA_CORE_API_ double IntensityDataFunctions::getRelativeDifference(const IHistogram &dat, const IHistogram &ref)
";

%feature("docstring")  IntensityDataFunctions::createRelativeDifferenceData "BA_CORE_API_ OutputData<double>* IntensityDataFunctions::createRelativeDifferenceData(const OutputData< double > &data, const OutputData< double > &reference)
";

%feature("docstring")  IntensityDataFunctions::createClippedDataSet "BA_CORE_API_ OutputData<double>* IntensityDataFunctions::createClippedDataSet(const OutputData< double > &origin, double x1, double y1, double x2, double y2)

Returns new IntensityData objects which axes clipped to represent the specified rectangle 
";

%feature("docstring")  IntensityDataFunctions::applyDetectorResolution "BA_CORE_API_ OutputData<double>* IntensityDataFunctions::applyDetectorResolution(const OutputData< double > &origin, const IResolutionFunction2D &resolution_function)

Applies detector resolution function and returns new IntensityData object. 
";

%feature("docstring")  IntensityDataFunctions::coordinateToBinf "BA_CORE_API_ double IntensityDataFunctions::coordinateToBinf(double coordinate, const IAxis &axis)

Transforms coordinate on axis into the bin-fraction-coordinate. 
";

%feature("docstring")  IntensityDataFunctions::coordinateFromBinf "BA_CORE_API_ double IntensityDataFunctions::coordinateFromBinf(double value, const IAxis &axis)

Transforms bin-fraction-coordinate into axis coordinate. 
";

%feature("docstring")  IntensityDataFunctions::coordinateToBinf "BA_CORE_API_ void IntensityDataFunctions::coordinateToBinf(double &x, double &y, const OutputData< double > &data)

Transform x,y coordinate from  OutputData axes coordinates to bin-fraction-coordinates 
";

%feature("docstring")  IntensityDataFunctions::coordinateFromBinf "BA_CORE_API_ void IntensityDataFunctions::coordinateFromBinf(double &x, double &y, const OutputData< double > &data)

Transform x,y coordinate from bin-fraction-coordinates to  OutputData's axes coordinates 
";


// File: namespaceMaterials.xml
%feature("docstring")  Materials::createInvertedMaterial "IMaterial * Materials::createInvertedMaterial(const IMaterial *material)
";


// File: namespaceMathFunctions.xml
%feature("docstring")  MathFunctions::Bessel_J0_PowSer "complex_t MathFunctions::Bessel_J0_PowSer(const complex_t z)

Computes complex Bessel function J0(z), using power series and asymptotic expansion.

Computes the complex Bessel function J0(z), using power series and asymptotic expansion.

Forked from unoptimized code at http://www.crbond.com/math.htm, who refers to \"Computation of Special Functions\", Zhang and Jin, John Wiley and Sons, 1996. 
";

%feature("docstring")  MathFunctions::Bessel_J1_PowSer "complex_t MathFunctions::Bessel_J1_PowSer(const complex_t z)

Computes complex Bessel function J0(z), using power series and asymptotic expansion.

Computes the complex Bessel function J1(z), using power series and asymptotic expansion.

Forked from same source as for Bessel_J0_PowSer 
";

%feature("docstring")  MathFunctions::StandardNormal "double MathFunctions::StandardNormal(double x)
";

%feature("docstring")  MathFunctions::Gaussian "double MathFunctions::Gaussian(double x, double average, double std_dev)
";

%feature("docstring")  MathFunctions::IntegratedGaussian "double MathFunctions::IntegratedGaussian(double x, double average, double std_dev)
";

%feature("docstring")  MathFunctions::cot "double MathFunctions::cot(double x)

cotangent function:  $cot(x)\\\\equiv1/tan(x)$
";

%feature("docstring")  MathFunctions::Si "double MathFunctions::Si(double x)

Sine integral function:  $Si(x)\\\\equiv\\\\int_0^x du \\\\sin(u)/u$. 
";

%feature("docstring")  MathFunctions::sinc "double MathFunctions::sinc(double x)

sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$
";

%feature("docstring")  MathFunctions::sinc "complex_t MathFunctions::sinc(const complex_t z)

Complex sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$. 
";

%feature("docstring")  MathFunctions::tanhc "complex_t MathFunctions::tanhc(const complex_t z)

Complex tanhc function:  $tanhc(x)\\\\equiv\\\\tanh(x)/x$. 
";

%feature("docstring")  MathFunctions::Laue "complex_t MathFunctions::Laue(const complex_t z, size_t N)
";

%feature("docstring")  MathFunctions::Bessel_J0 "double MathFunctions::Bessel_J0(double x)

Bessel function of the first kind and order 0. 
";

%feature("docstring")  MathFunctions::Bessel_J1 "double MathFunctions::Bessel_J1(double x)

Bessel function of the first kind and order 1. 
";

%feature("docstring")  MathFunctions::Bessel_J1c "double MathFunctions::Bessel_J1c(double x)

Bessel function Bessel_J1(x)/x. 
";

%feature("docstring")  MathFunctions::Bessel_J0 "complex_t MathFunctions::Bessel_J0(const complex_t z)

Complex Bessel function of the first kind and order 0. 
";

%feature("docstring")  MathFunctions::Bessel_J1 "complex_t MathFunctions::Bessel_J1(const complex_t z)

Complex Bessel function of the first kind and order 1. 
";

%feature("docstring")  MathFunctions::Bessel_J1c "complex_t MathFunctions::Bessel_J1c(const complex_t z)

Complex Bessel function Bessel_J1(x)/x. 
";

%feature("docstring")  MathFunctions::FastFourierTransform "std::vector< complex_t > MathFunctions::FastFourierTransform(const std::vector< complex_t > &data, EFFTDirection tcase)

simple (and unoptimized) wrapper function for the discrete fast Fourier transformation library (fftw3) 
";

%feature("docstring")  MathFunctions::FastFourierTransform "std::vector< complex_t > MathFunctions::FastFourierTransform(const std::vector< double > &data, EFFTDirection tcase)

simple (and unoptimized) wrapper function for the discrete fast Fourier transformation library (fftw3); transforms real to complex 
";

%feature("docstring")  MathFunctions::ConvolveFFT "std::vector< complex_t > MathFunctions::ConvolveFFT(const std::vector< double > &signal, const std::vector< double > &resfunc)

convolution of two real vectors of equal size 
";

%feature("docstring")  MathFunctions::GenerateUniformRandom "double MathFunctions::GenerateUniformRandom()
";

%feature("docstring")  MathFunctions::GenerateStandardNormalRandom "double MathFunctions::GenerateStandardNormalRandom()
";

%feature("docstring")  MathFunctions::GenerateNormalRandom "double MathFunctions::GenerateNormalRandom(double average, double std_dev)
";


// File: namespaceNumeric.xml
%feature("docstring")  Numeric::areAlmostEqual "bool BA_CORE_API_ Numeric::areAlmostEqual(double a, double b, double tolerance)

Returns true if two doubles agree within epsilon*tolerance. 
";

%feature("docstring")  Numeric::get_relative_difference "double BA_CORE_API_ Numeric::get_relative_difference(double a, double b)

Returns the safe relative difference, which is |(a-b)/b| except in special cases. 
";


// File: namespaceOutputDataIOHelper.xml
%feature("docstring")  OutputDataIOHelper::isCompressed "bool OutputDataIOHelper::isCompressed(const std::string &name)

Returns true if name contains *.gz extension. 
";

%feature("docstring")  OutputDataIOHelper::isGZipped "bool OutputDataIOHelper::isGZipped(const std::string &name)

Returns true if name contains *.gz extension.

Does name contain *.gz extension? 
";

%feature("docstring")  OutputDataIOHelper::isBZipped "bool OutputDataIOHelper::isBZipped(const std::string &name)

Returns true if name contains *.bz2 extension. 
";

%feature("docstring")  OutputDataIOHelper::GetFileMainExtension "std::string OutputDataIOHelper::GetFileMainExtension(const std::string &name)

Returns file extension after stripping '.gz' if any.

Returns file main extension (without .gz). 
";

%feature("docstring")  OutputDataIOHelper::isBinaryFile "bool OutputDataIOHelper::isBinaryFile(const std::string &file_name)

returns true if file name corresponds to a binary file 
";

%feature("docstring")  OutputDataIOHelper::isIntFile "bool OutputDataIOHelper::isIntFile(const std::string &file_name)

returns true if file name corresponds to BornAgain native format (compressed or not) 
";

%feature("docstring")  OutputDataIOHelper::isTxtFile "bool OutputDataIOHelper::isTxtFile(const std::string &file_name)

returns true if file name corresponds to simple numpy-style ASCII file 
";

%feature("docstring")  OutputDataIOHelper::isTiffFile "bool OutputDataIOHelper::isTiffFile(const std::string &file_name)

returns true if file name corresponds to tiff file (can be also compressed) 
";

%feature("docstring")  OutputDataIOHelper::isSimilarToFixedBinAxisType "bool OutputDataIOHelper::isSimilarToFixedBinAxisType(const std::string &line)

Returns true if string representation of the axis contains one of  FixedBinAxis,  ConstKBinAxis or  CustomBinAxis to parse it later in similar way. 
";

%feature("docstring")  OutputDataIOHelper::isVariableBinAxisType "bool OutputDataIOHelper::isVariableBinAxisType(const std::string &line)
";

%feature("docstring")  OutputDataIOHelper::createAxis "IAxis * OutputDataIOHelper::createAxis(std::istream &input_stream)

Creates axis of certain type from input stream. 
";

%feature("docstring")  OutputDataIOHelper::createFixedBinAxis "IAxis * OutputDataIOHelper::createFixedBinAxis(std::string line)

Create one of  FixedBinAxis from string representation  FixedBinAxis(\"axis0\", 10, -1, 1)  ConstKBinAxis(\"axis0\", 10, -1, 1)  CustomBinAxis(\"axis0\", 10, -1, 1) 
";

%feature("docstring")  OutputDataIOHelper::createVariableBinAxis "IAxis * OutputDataIOHelper::createVariableBinAxis(std::string line)

Create  VariableBinAxis from string representation  VariableBinAxis(\"axis0\", 4, [-1, -0.5, 0.5, 1, 2]) 
";

%feature("docstring")  OutputDataIOHelper::fillOutputData "void OutputDataIOHelper::fillOutputData(OutputData< double > *data, std::istream &input_stream)

Fills output data raw buffer from input stream. 
";

%feature("docstring")  OutputDataIOHelper::parse_doubles "std::vector< double > OutputDataIOHelper::parse_doubles(const std::string &str)

Parse double values from string to vector of double. 
";

%feature("docstring")  OutputDataIOHelper::readLineOfDoubles "void OutputDataIOHelper::readLineOfDoubles(std::vector< double > &buffer, std::istringstream &iss)
";


// File: namespacePythonFormatting.xml
%feature("docstring")  PythonFormatting::representShape2D "BA_CORE_API_ std::string PythonFormatting::representShape2D(const std::string &indent, const Geometry::IShape2D *ishape, bool mask_value, std::function< std::string(double)> printValueFunc)

Returns fixed Python code snippet that defines the function \"runSimulation\". 
";

%feature("docstring")  PythonFormatting::printBool "BA_CORE_API_ std::string PythonFormatting::printBool(double value)
";

%feature("docstring")  PythonFormatting::printDouble "BA_CORE_API_ std::string PythonFormatting::printDouble(double input)
";

%feature("docstring")  PythonFormatting::printNm "BA_CORE_API_ std::string PythonFormatting::printNm(double input)
";

%feature("docstring")  PythonFormatting::printScientificDouble "BA_CORE_API_ std::string PythonFormatting::printScientificDouble(double input)
";

%feature("docstring")  PythonFormatting::printDegrees "BA_CORE_API_ std::string PythonFormatting::printDegrees(double input)
";

%feature("docstring")  PythonFormatting::isSquare "BA_CORE_API_ bool PythonFormatting::isSquare(double length1, double length2, double angle)
";

%feature("docstring")  PythonFormatting::isHexagonal "BA_CORE_API_ bool PythonFormatting::isHexagonal(double length1, double length2, double angle)
";

%feature("docstring")  PythonFormatting::printKvector "BA_CORE_API_ std::string PythonFormatting::printKvector(const kvector_t value)
";

%feature("docstring")  PythonFormatting::isDefaultDirection "BA_CORE_API_ bool PythonFormatting::isDefaultDirection(const kvector_t direction)

returns true if it is (0, -1, 0) vector 
";

%feature("docstring")  PythonFormatting::valueTimesUnit "BA_CORE_API_ std::string PythonFormatting::valueTimesUnit(const RealParameter *par)

Returns parameter value, followed by its unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  PythonFormatting::argumentList "BA_CORE_API_ std::string PythonFormatting::argumentList(const IParameterized *ip)

Returns comma-separated list of parameter values, including unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  PythonFormatting::simulationToPython "std::string PythonFormatting::simulationToPython(GISASSimulation *simulation)
";


// File: namespaceStandardSimulations.xml
%feature("docstring")  StandardSimulations::PolarizedDWBAMagCylinders2 "GISASSimulation* StandardSimulations::PolarizedDWBAMagCylinders2()
";

%feature("docstring")  StandardSimulations::BasicGISAS "GISASSimulation* StandardSimulations::BasicGISAS()
";

%feature("docstring")  StandardSimulations::BasicGISAS00 "GISASSimulation* StandardSimulations::BasicGISAS00()
";

%feature("docstring")  StandardSimulations::MiniGISAS "GISASSimulation* StandardSimulations::MiniGISAS()
";

%feature("docstring")  StandardSimulations::MiniGISAS_v2 "GISASSimulation* StandardSimulations::MiniGISAS_v2()
";

%feature("docstring")  StandardSimulations::MiniGISASBeamDivergence "GISASSimulation* StandardSimulations::MiniGISASBeamDivergence()
";

%feature("docstring")  StandardSimulations::MiniGISASDetectorResolution "GISASSimulation* StandardSimulations::MiniGISASDetectorResolution()
";

%feature("docstring")  StandardSimulations::GISASWithMasks "GISASSimulation* StandardSimulations::GISASWithMasks()
";

%feature("docstring")  StandardSimulations::MaxiGISAS "GISASSimulation* StandardSimulations::MaxiGISAS()
";

%feature("docstring")  StandardSimulations::MaxiGISAS00 "GISASSimulation* StandardSimulations::MaxiGISAS00()
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation1 "GISASSimulation* StandardSimulations::IsGISAXSSimulation1()
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation2 "GISASSimulation* StandardSimulations::IsGISAXSSimulation2()
";

%feature("docstring")  StandardSimulations::RectDetectorGeneric "GISASSimulation* StandardSimulations::RectDetectorGeneric()
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToSample "GISASSimulation* StandardSimulations::RectDetectorPerpToSample()
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToDirectBeam "GISASSimulation* StandardSimulations::RectDetectorPerpToDirectBeam()
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeam "GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeam()
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeamDpos "GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeamDpos()
";

%feature("docstring")  StandardSimulations::MiniGISASMonteCarlo "GISASSimulation* StandardSimulations::MiniGISASMonteCarlo()
";

%feature("docstring")  StandardSimulations::SphericalDetWithRoi "GISASSimulation* StandardSimulations::SphericalDetWithRoi()
";

%feature("docstring")  StandardSimulations::RectDetWithRoi "GISASSimulation* StandardSimulations::RectDetWithRoi()
";


// File: namespaceUnits.xml
%feature("docstring")  Units::rad2deg "double Units::rad2deg(double angle)
";

%feature("docstring")  Units::deg2rad "double Units::deg2rad(double angle)
";


// File: namespaceUtil.xml
%feature("docstring")  Util::getCurrentDateAndTime "std::string Util::getCurrentDateAndTime()
";

%feature("docstring")  Util::enableFloatingPointExceptions "void Util::enableFloatingPointExceptions()

enables exception throw in the case of NaN, Inf 
";

%feature("docstring")  Util::getShape "std::pair< size_t, size_t > Util::getShape(const std::vector< std::vector< double >> &data)

Returns shape nrows, ncols of 2D array. 
";


// File: FormFactorWrapper_8cpp.xml


// File: FormFactorWrapper_8h.xml


// File: FTDecayFunctions_8cpp.xml


// File: FTDecayFunctions_8h.xml


// File: FTDistributions1D_8cpp.xml


// File: FTDistributions1D_8h.xml


// File: FTDistributions2D_8cpp.xml


// File: FTDistributions2D_8h.xml


// File: IInterferenceFunction_8h.xml


// File: ILayout_8h.xml


// File: InterferenceFunction1DLattice_8cpp.xml


// File: InterferenceFunction1DLattice_8h.xml


// File: InterferenceFunction2DLattice_8cpp.xml


// File: InterferenceFunction2DLattice_8h.xml


// File: InterferenceFunction2DParaCrystal_8cpp.xml


// File: InterferenceFunction2DParaCrystal_8h.xml


// File: InterferenceFunctionNone_8cpp.xml


// File: InterferenceFunctionNone_8h.xml


// File: InterferenceFunctionRadialParaCrystal_8cpp.xml


// File: InterferenceFunctionRadialParaCrystal_8h.xml


// File: ParticleLayout_8cpp.xml


// File: ParticleLayout_8h.xml


// File: BornAgainNamespace_8h.xml


// File: Complex_8h.xml
%feature("docstring")  mul_I "complex_t mul_I(complex_t z)

Returns product I*z, where I is the imaginary unit. 
";

%feature("docstring")  exp_I "complex_t exp_I(complex_t z)

Returns exp(I*z), where I is the imaginary unit. 
";


// File: Exceptions_8cpp.xml


// File: Exceptions_8h.xml


// File: ICloneable_8h.xml


// File: INamed_8h.xml


// File: INoncopyable_8h.xml


// File: IShareable_8h.xml


// File: ISingleton_8h.xml


// File: Macros_8h.xml


// File: MathConstants_8h.xml


// File: Bin_8cpp.xml
%feature("docstring")  BinContains "bool BinContains(const Bin1D &bin, double value)

Checks if value is contained in bin: value in [m_lower, m_upper) 
";


// File: Bin_8h.xml
%feature("docstring")  BinContains "bool BinContains(const Bin1D &bin, double value)

Checks if value is contained in bin: value in [m_lower, m_upper) 
";


// File: ConstKBinAxis_8cpp.xml


// File: ConstKBinAxis_8h.xml


// File: CustomBinAxis_8cpp.xml


// File: CustomBinAxis_8h.xml


// File: FixedBinAxis_8cpp.xml


// File: FixedBinAxis_8h.xml


// File: IAxis_8cpp.xml


// File: IAxis_8h.xml
%feature("docstring")  HaveSameNameAndShape "bool HaveSameNameAndShape(const IAxis &left, const IAxis &right)

global helper function for comparison of axes 
";


// File: IPixelMap_8h.xml


// File: SimulationElement_8cpp.xml
%feature("docstring")  addElementsWithWeight "void addElementsWithWeight(std::vector< SimulationElement >::const_iterator first, std::vector< SimulationElement >::const_iterator last, std::vector< SimulationElement >::iterator result, double weight)

Add element vector to element vector with weight. 
";

%feature("docstring")  setAllElementIntensities "void setAllElementIntensities(std::vector< SimulationElement >::iterator first, std::vector< SimulationElement >::iterator last, double intensity)

Set all element intensities to given value. 
";


// File: SimulationElement_8h.xml
%feature("docstring")  addElementsWithWeight "void addElementsWithWeight(std::vector< SimulationElement >::const_iterator first, std::vector< SimulationElement >::const_iterator last, std::vector< SimulationElement >::iterator result, double weight)

Add element vector to element vector with weight. 
";

%feature("docstring")  setAllElementIntensities "void setAllElementIntensities(std::vector< SimulationElement >::iterator first, std::vector< SimulationElement >::iterator last, double intensity)

Set all element intensities to given value. 
";


// File: VariableBinAxis_8cpp.xml


// File: VariableBinAxis_8h.xml


// File: ComputationOutcome_8h.xml


// File: DecoratedLayerComputation_8cpp.xml


// File: DecoratedLayerComputation_8h.xml


// File: InnerCounter_8cpp.xml


// File: InnerCounter_8h.xml


// File: MainComputation_8cpp.xml


// File: MainComputation_8h.xml


// File: ProgressHandler_8cpp.xml


// File: ProgressHandler_8h.xml


// File: RoughMultiLayerComputation_8cpp.xml


// File: RoughMultiLayerComputation_8h.xml


// File: SpecularComputation_8cpp.xml


// File: SpecularComputation_8h.xml


// File: FormFactorDecoratorDebyeWaller_8cpp.xml


// File: FormFactorDecoratorDebyeWaller_8h.xml


// File: FormFactorDecoratorFactor_8cpp.xml


// File: FormFactorDecoratorFactor_8h.xml


// File: FormFactorDecoratorMaterial_8cpp.xml


// File: FormFactorDecoratorMaterial_8h.xml


// File: FormFactorDecoratorPositionFactor_8cpp.xml


// File: FormFactorDecoratorPositionFactor_8h.xml


// File: FormFactorDecoratorRotation_8cpp.xml


// File: FormFactorDecoratorRotation_8h.xml


// File: IFormFactorDecorator_8h.xml


// File: ExportToPython_8cpp.xml


// File: ExportToPython_8h.xml


// File: PythonFormatting_8cpp.xml


// File: PythonFormatting_8h.xml


// File: SampleLabelHandler_8cpp.xml


// File: SampleLabelHandler_8h.xml


// File: AdjustMinimizerStrategy_8cpp.xml


// File: AdjustMinimizerStrategy_8h.xml


// File: FitObject_8cpp.xml


// File: FitObject_8h.xml


// File: FitParameterLinked_8cpp.xml


// File: FitParameterLinked_8h.xml


// File: FitStrategyAdjustParameters_8cpp.xml


// File: FitStrategyAdjustParameters_8h.xml


// File: FitSuite_8cpp.xml


// File: FitSuite_8h.xml


// File: FitSuiteFunctions_8cpp.xml


// File: FitSuiteFunctions_8h.xml


// File: FitSuiteImpl_8cpp.xml


// File: FitSuiteImpl_8h.xml


// File: FitSuiteObjects_8cpp.xml


// File: FitSuiteObjects_8h.xml


// File: FitSuitePrintObserver_8cpp.xml


// File: FitSuitePrintObserver_8h.xml


// File: FitSuiteStrategies_8cpp.xml


// File: FitSuiteStrategies_8h.xml


// File: IFitObserver_8cpp.xml


// File: IFitObserver_8h.xml


// File: IFitStrategy_8cpp.xml


// File: IFitStrategy_8h.xml


// File: IObserver_8cpp.xml


// File: IObserver_8h.xml


// File: FormFactorAnisoPyramid_8cpp.xml


// File: FormFactorAnisoPyramid_8h.xml


// File: FormFactorBox_8cpp.xml


// File: FormFactorBox_8h.xml


// File: FormFactorCone_8cpp.xml


// File: FormFactorCone_8h.xml


// File: FormFactorCone6_8cpp.xml


// File: FormFactorCone6_8h.xml


// File: FormFactorCuboctahedron_8cpp.xml


// File: FormFactorCuboctahedron_8h.xml


// File: FormFactorCylinder_8cpp.xml


// File: FormFactorCylinder_8h.xml


// File: FormFactorDodecahedron_8cpp.xml


// File: FormFactorDodecahedron_8h.xml


// File: FormFactorEllipsoidalCylinder_8cpp.xml


// File: FormFactorEllipsoidalCylinder_8h.xml


// File: FormFactorFullSphere_8cpp.xml


// File: FormFactorFullSphere_8h.xml


// File: FormFactorFullSpheroid_8cpp.xml


// File: FormFactorFullSpheroid_8h.xml


// File: FormFactorHemiEllipsoid_8cpp.xml


// File: FormFactorHemiEllipsoid_8h.xml


// File: FormFactorIcosahedron_8cpp.xml


// File: FormFactorIcosahedron_8h.xml


// File: FormFactorLongBoxGauss_8cpp.xml


// File: FormFactorLongBoxGauss_8h.xml


// File: FormFactorLongBoxLorentz_8cpp.xml


// File: FormFactorLongBoxLorentz_8h.xml


// File: FormFactorLongRipple1Gauss_8cpp.xml


// File: FormFactorLongRipple1Gauss_8h.xml


// File: FormFactorLongRipple1Lorentz_8cpp.xml


// File: FormFactorLongRipple1Lorentz_8h.xml


// File: FormFactorLongRipple2Gauss_8cpp.xml


// File: FormFactorLongRipple2Gauss_8h.xml


// File: FormFactorLongRipple2Lorentz_8cpp.xml


// File: FormFactorLongRipple2Lorentz_8h.xml


// File: FormFactorPolyhedron_8cpp.xml
%feature("docstring")  I "static const complex_t I(0., 1.)

The mathematics implemented here is described in full detail in a paper by Joachim Wuttke, entitled \"Form factor (Fourier shape transform) of polygon and polyhedron.\" 
";

%feature("docstring")  eps "static const double eps(2e-16)
";


// File: FormFactorPolyhedron_8h.xml


// File: FormFactorPrism3_8cpp.xml


// File: FormFactorPrism3_8h.xml


// File: FormFactorPrism6_8cpp.xml


// File: FormFactorPrism6_8h.xml


// File: FormFactorPyramid_8cpp.xml


// File: FormFactorPyramid_8h.xml


// File: FormFactorRipple1_8cpp.xml
%feature("docstring")  I "static complex_t I(0., 1.)
";


// File: FormFactorRipple1_8h.xml


// File: FormFactorRipple2_8cpp.xml


// File: FormFactorRipple2_8h.xml


// File: FormFactorTetrahedron_8cpp.xml


// File: FormFactorTetrahedron_8h.xml


// File: FormFactorTriangle_8cpp.xml


// File: FormFactorTriangle_8h.xml


// File: FormFactorTrivial_8cpp.xml


// File: FormFactorTrivial_8h.xml


// File: FormFactorTruncatedCube_8cpp.xml


// File: FormFactorTruncatedCube_8h.xml


// File: FormFactorTruncatedSphere_8cpp.xml


// File: FormFactorTruncatedSphere_8h.xml


// File: FormFactorTruncatedSpheroid_8cpp.xml


// File: FormFactorTruncatedSpheroid_8h.xml


// File: FormFactors_8h.xml


// File: HardParticles_8h.xml


// File: InterferenceFunctions_8h.xml


// File: SoftParticles_8h.xml


// File: boost__streams_8h.xml


// File: IntensityDataIOFactory_8cpp.xml


// File: IntensityDataIOFactory_8h.xml


// File: OutputDataIOHelper_8cpp.xml


// File: OutputDataIOHelper_8h.xml


// File: OutputDataReader_8cpp.xml


// File: OutputDataReader_8h.xml


// File: OutputDataReadFactory_8cpp.xml


// File: OutputDataReadFactory_8h.xml


// File: OutputDataReadStrategy_8cpp.xml


// File: OutputDataReadStrategy_8h.xml


// File: OutputDataWriteFactory_8cpp.xml


// File: OutputDataWriteFactory_8h.xml


// File: OutputDataWriter_8cpp.xml


// File: OutputDataWriter_8h.xml


// File: OutputDataWriteStrategy_8cpp.xml
%feature("docstring")  IgnoreDenormalized "double IgnoreDenormalized(double value)
";

%feature("docstring")  WriteOutputDataDoubles "void WriteOutputDataDoubles(const OutputData< double > &data, std::ostream &output_stream, size_t n_columns)
";


// File: OutputDataWriteStrategy_8h.xml


// File: TiffHandler_8cpp.xml


// File: TiffHandler_8h.xml


// File: Beam_8cpp.xml


// File: Beam_8h.xml


// File: ChiSquaredModule_8cpp.xml


// File: ChiSquaredModule_8h.xml


// File: ConvolutionDetectorResolution_8cpp.xml


// File: ConvolutionDetectorResolution_8h.xml


// File: Convolve_8cpp.xml


// File: Convolve_8h.xml


// File: CumulativeValue_8cpp.xml


// File: CumulativeValue_8h.xml


// File: DetectionProperties_8cpp.xml


// File: DetectionProperties_8h.xml


// File: DetectorFunctions_8cpp.xml


// File: DetectorFunctions_8h.xml


// File: DetectorMask_8cpp.xml


// File: DetectorMask_8h.xml


// File: FitElement_8cpp.xml


// File: FitElement_8h.xml


// File: Histogram1D_8cpp.xml


// File: Histogram1D_8h.xml


// File: Histogram2D_8cpp.xml


// File: Histogram2D_8h.xml


// File: IChiSquaredModule_8cpp.xml


// File: IChiSquaredModule_8h.xml


// File: IDetector2D_8cpp.xml


// File: IDetector2D_8h.xml


// File: IDetectorResolution_8h.xml


// File: IHistogram_8cpp.xml


// File: IHistogram_8h.xml


// File: IIntensityFunction_8cpp.xml


// File: IIntensityFunction_8h.xml


// File: IIntensityNormalizer_8cpp.xml


// File: IIntensityNormalizer_8h.xml


// File: Instrument_8cpp.xml


// File: Instrument_8h.xml


// File: IntensityDataFunctions_8cpp.xml


// File: IntensityDataFunctions_8h.xml


// File: IResolutionFunction2D_8h.xml


// File: IsGISAXSDetector_8cpp.xml


// File: IsGISAXSDetector_8h.xml


// File: ISquaredFunction_8h.xml


// File: LLData_8cpp.xml


// File: LLData_8h.xml
%feature("docstring")  HaveSameDimensions "bool HaveSameDimensions(const LLData< T > &left, const LLData< T > &right)
";


// File: NumpyUtils_8cpp.xml


// File: NumpyUtils_8h.xml


// File: OutputData_8cpp.xml


// File: OutputData_8h.xml


// File: OutputDataIterator_8h.xml
%feature("docstring")  swap "void swap(OutputDataIterator< TValue, TContainer > &left, OutputDataIterator< TValue, TContainer > &right)

make Swappable 
";


// File: RectangularDetector_8cpp.xml


// File: RectangularDetector_8h.xml


// File: RegionOfInterest_8cpp.xml


// File: RegionOfInterest_8h.xml


// File: ResolutionFunction2DGaussian_8cpp.xml


// File: ResolutionFunction2DGaussian_8h.xml


// File: SimulationArea_8cpp.xml


// File: SimulationArea_8h.xml


// File: SimulationAreaIterator_8cpp.xml


// File: SimulationAreaIterator_8h.xml


// File: SphericalDetector_8cpp.xml


// File: SphericalDetector_8h.xml


// File: ISelectionRule_8h.xml


// File: Lattice_8cpp.xml


// File: Lattice_8h.xml


// File: Lattice1DParameters_8h.xml


// File: Lattice2DParameters_8cpp.xml


// File: Lattice2DParameters_8h.xml


// File: Ellipse_8cpp.xml


// File: Ellipse_8h.xml


// File: InfinitePlane_8h.xml


// File: IShape2D_8h.xml


// File: Line_8cpp.xml


// File: Line_8h.xml


// File: Polygon_8cpp.xml


// File: Polygon_8h.xml


// File: Rectangle_8cpp.xml


// File: Rectangle_8h.xml


// File: HomogeneousMagneticMaterial_8cpp.xml


// File: HomogeneousMagneticMaterial_8h.xml


// File: HomogeneousMaterial_8h.xml


// File: IMaterial_8cpp.xml


// File: IMaterial_8h.xml


// File: Materials_8cpp.xml


// File: Materials_8h.xml


// File: DecouplingApproximationStrategy_8cpp.xml


// File: DecouplingApproximationStrategy_8h.xml


// File: DWBADiffuseReflection_8cpp.xml


// File: DWBADiffuseReflection_8h.xml


// File: FormFactorDWBA_8cpp.xml


// File: FormFactorDWBA_8h.xml


// File: FormFactorDWBAPol_8cpp.xml


// File: FormFactorDWBAPol_8h.xml


// File: IInterferenceFunctionStrategy_8cpp.xml


// File: IInterferenceFunctionStrategy_8h.xml


// File: ILayerRTCoefficients_8h.xml


// File: IMultiLayerBuilder_8cpp.xml


// File: IMultiLayerBuilder_8h.xml


// File: IRoughness_8h.xml


// File: ISpecularInfoMap_8h.xml


// File: Layer_8cpp.xml


// File: Layer_8h.xml


// File: LayerInterface_8cpp.xml


// File: LayerInterface_8h.xml


// File: LayerRoughness_8cpp.xml


// File: LayerRoughness_8h.xml


// File: LayerSpecularInfo_8cpp.xml


// File: LayerSpecularInfo_8h.xml


// File: LayerStrategyBuilder_8cpp.xml


// File: LayerStrategyBuilder_8h.xml


// File: MatrixRTCoefficients_8cpp.xml


// File: MatrixRTCoefficients_8h.xml


// File: MatrixSpecularInfoMap_8cpp.xml


// File: MatrixSpecularInfoMap_8h.xml


// File: MultiLayer_8cpp.xml


// File: MultiLayer_8h.xml


// File: ScalarRTCoefficients_8h.xml


// File: ScalarSpecularInfoMap_8cpp.xml


// File: ScalarSpecularInfoMap_8h.xml


// File: SpecularMagnetic_8cpp.xml
%feature("docstring")  I "static complex_t I(0., 1.)
";


// File: SpecularMagnetic_8h.xml


// File: SpecularMatrix_8cpp.xml
%feature("docstring")  setZeroBelow "void setZeroBelow(SpecularMatrix::MultiLayerCoeff_t &coeff, size_t current_layer)
";

%feature("docstring")  calculateUpFromLayer "bool calculateUpFromLayer(SpecularMatrix::MultiLayerCoeff_t &coeff, const MultiLayer &sample, const kvector_t k, size_t layer_index)
";


// File: SpecularMatrix_8h.xml


// File: SSCApproximationStrategy_8cpp.xml


// File: SSCApproximationStrategy_8h.xml


// File: DistributionHandler_8cpp.xml


// File: DistributionHandler_8h.xml


// File: Distributions_8cpp.xml


// File: Distributions_8h.xml


// File: IParameter_8h.xml


// File: IParameterized_8cpp.xml


// File: IParameterized_8h.xml


// File: ParameterDistribution_8cpp.xml


// File: ParameterDistribution_8h.xml


// File: ParameterPattern_8cpp.xml


// File: ParameterPattern_8h.xml


// File: ParameterPool_8cpp.xml


// File: ParameterPool_8h.xml


// File: ParameterSample_8h.xml


// File: RealParameter_8cpp.xml


// File: RealParameter_8h.xml


// File: SimulationOptions_8cpp.xml


// File: SimulationOptions_8h.xml


// File: ThreadInfo_8h.xml


// File: Unit_8cpp.xml


// File: Unit_8h.xml


// File: Units_8h.xml


// File: Crystal_8cpp.xml


// File: Crystal_8h.xml


// File: FormFactorCrystal_8cpp.xml


// File: FormFactorCrystal_8h.xml


// File: FormFactorWeighted_8cpp.xml


// File: FormFactorWeighted_8h.xml


// File: IAbstractParticle_8h.xml


// File: IClusteredParticles_8h.xml


// File: IParticle_8cpp.xml


// File: IParticle_8h.xml


// File: MesoCrystal_8cpp.xml


// File: MesoCrystal_8h.xml


// File: Particle_8cpp.xml


// File: Particle_8h.xml


// File: ParticleComposition_8cpp.xml


// File: ParticleComposition_8h.xml


// File: ParticleCoreShell_8cpp.xml


// File: ParticleCoreShell_8h.xml


// File: ParticleDistribution_8cpp.xml


// File: ParticleDistribution_8h.xml


// File: TRange_8h.xml


// File: ICompositeSample_8cpp.xml


// File: ICompositeSample_8h.xml


// File: IFormFactor_8cpp.xml


// File: IFormFactor_8h.xml


// File: IFormFactorBorn_8cpp.xml


// File: IFormFactorBorn_8h.xml


// File: ISample_8cpp.xml


// File: ISample_8h.xml


// File: ISampleIteratorStrategy_8cpp.xml


// File: ISampleIteratorStrategy_8h.xml


// File: ISampleVisitor_8cpp.xml
%feature("docstring")  VisitSampleTreePreorder "void VisitSampleTreePreorder(const ISample &sample, ISampleVisitor &visitor)
";

%feature("docstring")  VisitSampleTreePostorder "void VisitSampleTreePostorder(const ISample &sample, ISampleVisitor &visitor)
";


// File: ISampleVisitor_8h.xml
%feature("docstring")  VisitSampleTreePreorder "BA_CORE_API_ void VisitSampleTreePreorder(const ISample &sample, ISampleVisitor &visitor)
";

%feature("docstring")  VisitSampleTreePostorder "BA_CORE_API_ void VisitSampleTreePostorder(const ISample &sample, ISampleVisitor &visitor)
";


// File: Rotations_8cpp.xml
%feature("docstring")  CreateProduct "IRotation* CreateProduct(const IRotation &left, const IRotation &right)

Returns concatenated rotation (first right, then left). 
";


// File: Rotations_8h.xml
%feature("docstring")  CreateProduct "BA_CORE_API_ IRotation* CreateProduct(const IRotation &left, const IRotation &right)

Returns concatenated rotation (first right, then left). 
";


// File: SampleTreeIterator_8cpp.xml


// File: SampleTreeIterator_8h.xml


// File: StringUsageMap_8h.xml


// File: GISASSimulation_8cpp.xml


// File: GISASSimulation_8h.xml


// File: OffSpecSimulation_8cpp.xml


// File: OffSpecSimulation_8h.xml


// File: Simulation_8cpp.xml


// File: Simulation_8h.xml


// File: SpecularSimulation_8cpp.xml


// File: SpecularSimulation_8h.xml


// File: FormFactorGauss_8cpp.xml


// File: FormFactorGauss_8h.xml


// File: FormFactorLorentz_8cpp.xml


// File: FormFactorLorentz_8h.xml


// File: FormFactorSphereGaussianRadius_8cpp.xml


// File: FormFactorSphereGaussianRadius_8h.xml


// File: FormFactorSphereLogNormalRadius_8cpp.xml


// File: FormFactorSphereLogNormalRadius_8h.xml


// File: FormFactorSphereUniformRadius_8cpp.xml


// File: FormFactorSphereUniformRadius_8h.xml


// File: BoxCompositionBuilder_8cpp.xml


// File: BoxCompositionBuilder_8h.xml


// File: CoreShellParticleBuilder_8cpp.xml


// File: CoreShellParticleBuilder_8h.xml


// File: CustomMorphologyBuilder_8cpp.xml


// File: CustomMorphologyBuilder_8h.xml


// File: CylindersAndPrismsBuilder_8cpp.xml


// File: CylindersAndPrismsBuilder_8h.xml


// File: CylindersBuilder_8cpp.xml


// File: CylindersBuilder_8h.xml


// File: IFactory_8h.xml
%feature("docstring")  create_new "T* create_new()
";


// File: LatticeBuilder_8cpp.xml


// File: LatticeBuilder_8h.xml


// File: LayersWithAbsorptionBuilder_8cpp.xml


// File: LayersWithAbsorptionBuilder_8h.xml


// File: MagneticParticlesBuilder_8cpp.xml


// File: MagneticParticlesBuilder_8h.xml


// File: MesoCrystalBuilder_8cpp.xml


// File: MesoCrystalBuilder_8h.xml


// File: MultiLayerWithRoughnessBuilder_8cpp.xml


// File: MultiLayerWithRoughnessBuilder_8h.xml


// File: MultipleLayoutBuilder_8cpp.xml


// File: MultipleLayoutBuilder_8h.xml


// File: ParaCrystalBuilder_8cpp.xml


// File: ParaCrystalBuilder_8h.xml


// File: ParticleCompositionBuilder_8cpp.xml


// File: ParticleCompositionBuilder_8h.xml


// File: ParticleDistributionsBuilder_8cpp.xml


// File: ParticleDistributionsBuilder_8h.xml


// File: ParticleInTheAirBuilder_8cpp.xml


// File: ParticleInTheAirBuilder_8h.xml


// File: RipplesBuilder_8cpp.xml


// File: RipplesBuilder_8h.xml


// File: RotatedPyramidsBuilder_8cpp.xml


// File: RotatedPyramidsBuilder_8h.xml


// File: SampleBuilderFactory_8cpp.xml


// File: SampleBuilderFactory_8h.xml


// File: SimulationFactory_8cpp.xml


// File: SimulationFactory_8h.xml


// File: SizeDistributionModelsBuilder_8cpp.xml


// File: SizeDistributionModelsBuilder_8h.xml


// File: StandardSimulations_8cpp.xml


// File: StandardSimulations_8h.xml


// File: TransformationsBuilder_8cpp.xml


// File: TransformationsBuilder_8h.xml


// File: TwoDimLatticeBuilder_8cpp.xml


// File: TwoDimLatticeBuilder_8h.xml


// File: FileSystem_8cpp.xml


// File: FileSystem_8h.xml


// File: fp__exception__glibc__extension_8h.xml
%feature("docstring")  fegetexcept "int fegetexcept(void)

License: Public Domain 
David N. Williams 
";

%feature("docstring")  feenableexcept "int feenableexcept(unsigned int excepts)
";

%feature("docstring")  fedisableexcept "int fedisableexcept(unsigned int excepts)
";

%feature("docstring")  fhdl "void fhdl(int sig, siginfo_t *sip, ucontext_t *scp)
";


// File: IntegratorComplex_8h.xml
%feature("docstring")  make_integrator_complex "P_integrator_complex<T> make_integrator_complex(const T *object, complex_integrand< T > mem_function)
";


// File: IntegratorMCMiser_8h.xml
%feature("docstring")  make_integrator_miser "P_integrator_miser<T> make_integrator_miser(const T *object, miser_integrand< T > mem_function, size_t dim)
";


// File: IntegratorReal_8h.xml
%feature("docstring")  make_integrator_real "P_integrator_real<T> make_integrator_real(const T *object, real_integrand< T > mem_function)
";


// File: MathFunctions_8cpp.xml


// File: MathFunctions_8h.xml


// File: Numeric_8cpp.xml


// File: Numeric_8h.xml


// File: Precomputed_8cpp.xml


// File: Precomputed_8h.xml


// File: SafePointerVector_8h.xml


// File: Utils_8cpp.xml


// File: Utils_8h.xml


// File: w32pragma_8h.xml


// File: BasicVector3D_8cpp.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BasicVector3D<double> vecOfLambdaAlphaPhi(const double _lambda, const double _alpha, const double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: BasicVector3D_8h.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BA_CORE_API_ BasicVector3D<double> vecOfLambdaAlphaPhi(const double _lambda, const double _alpha, const double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: EigenCore_8h.xml


// File: Transform3D_8cpp.xml


// File: Transform3D_8h.xml


// File: Vectors3D_8h.xml


// File: WavevectorInfo_8h.xml


// File: dir_5f1a4a05eca575eab319839347bb4113.xml


// File: dir_f2db70b1039b2dc98a7a13a1758f382f.xml


// File: dir_629bf8536959f2975d8caec326cd60c0.xml


// File: dir_7de90f35ae2a2c7b4fa95823d333cc96.xml


// File: dir_c6310732a22f63c0c2fc5595561e68f1.xml


// File: dir_e5c18127747cd9d7214e02067b529d74.xml


// File: dir_cca9b87b2505f372a6ce58947a507789.xml


// File: dir_4470199ae7eb44153ffe31d163ed0f28.xml


// File: dir_05b265732c0b4c8e8dad02f2f774744b.xml


// File: dir_72a38c5b455c03a72881c3c65e21783d.xml


// File: dir_d7044b5fc4daccc5700de9f07da81a11.xml


// File: dir_602d2305564088eb1fd2ee9e74929d48.xml


// File: dir_7f8c371d7d9c2d18aea541845cde06e7.xml


// File: dir_24998d15d4ee11ef081e71321705b47b.xml


// File: dir_0bf70e747e161ad6105733dd3b116e64.xml


// File: dir_c21740227f50b02f28bdacfb625f042a.xml


// File: dir_d4e34ce36424db6c5895519defe19e58.xml


// File: dir_3a34810b9fbc1682c26e767b1a1a5860.xml


// File: dir_6babb1605c026604526d064f820d612b.xml


// File: dir_d7a24665a95cfc15308ebd7b07b5ebd6.xml


// File: dir_bf872a709c84554e66a8525bb546523f.xml


// File: dir_5d2259b43612a5a0ff7512df653d7370.xml


// File: dir_e120110860f9b345e7b3217e8b15cbb8.xml


// File: dir_19cd2158bba3b9a051f8f27403820580.xml

