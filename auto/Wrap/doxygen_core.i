
// File: index.xml

// File: classAngularSpecScan.xml
%feature("docstring") AngularSpecScan "

Scan type with inclination angles as coordinate values and a unique wavelength. Features footprint correction.

C++ includes: AngularSpecScan.h
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, std::vector< double > inc_angle)
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, const IAxis &inc_angle)
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max)

Sets angle-defined specular scan. The first parameter is always a wavelength in nm. Second parameter is either a numpy array of incident angles in radians or an  IAxis object with angle values. Alternatively an axis can be defined in-place, then the second passed parameter is the number of bins, third - minimum on-axis angle value, fourth - maximum on-axis angle value. 
";

%feature("docstring")  AngularSpecScan::~AngularSpecScan "AngularSpecScan::~AngularSpecScan() override
";

%feature("docstring")  AngularSpecScan::clone "AngularSpecScan * AngularSpecScan::clone() const override
";

%feature("docstring")  AngularSpecScan::generateSimulationElements "std::vector< SpecularSimulationElement > AngularSpecScan::generateSimulationElements() const override

Generates simulation elements for specular simulations. 
";

%feature("docstring")  AngularSpecScan::coordinateAxis "virtual const IAxis* AngularSpecScan::coordinateAxis() const override

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  AngularSpecScan::footprintFactor "virtual const IFootprintFactor* AngularSpecScan::footprintFactor() const override

Returns  IFootprintFactor object pointer. 
";

%feature("docstring")  AngularSpecScan::footprint "std::vector< double > AngularSpecScan::footprint(size_t i, size_t n_elements) const override

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  AngularSpecScan::numberOfSimulationElements "size_t AngularSpecScan::numberOfSimulationElements() const override

Returns the number of simulation elements. 
";

%feature("docstring")  AngularSpecScan::createIntensities "std::vector< double > AngularSpecScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const override

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  AngularSpecScan::print "std::string AngularSpecScan::print() const override

Print scan definition in python format. 
";

%feature("docstring")  AngularSpecScan::wavelength "double AngularSpecScan::wavelength() const
";

%feature("docstring")  AngularSpecScan::wavelengthResolution "const ScanResolution* AngularSpecScan::wavelengthResolution() const
";

%feature("docstring")  AngularSpecScan::angleResolution "const ScanResolution* AngularSpecScan::angleResolution() const
";

%feature("docstring")  AngularSpecScan::setFootprintFactor "void AngularSpecScan::setFootprintFactor(const IFootprintFactor *f_factor)

Sets footprint correction factor. 
";

%feature("docstring")  AngularSpecScan::setWavelengthResolution "void AngularSpecScan::setWavelengthResolution(const ScanResolution &resolution)

Sets wavelength resolution values via  ScanResolution object. 
";

%feature("docstring")  AngularSpecScan::setRelativeWavelengthResolution "void AngularSpecScan::setRelativeWavelengthResolution(const RangedDistribution &distr, double rel_dev)
";

%feature("docstring")  AngularSpecScan::setRelativeWavelengthResolution "void AngularSpecScan::setRelativeWavelengthResolution(const RangedDistribution &distr, const std::vector< double > &rel_dev)

Sets wavelength resolution values via  RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets wavelength resolution values via  RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAngleResolution "void AngularSpecScan::setAngleResolution(const ScanResolution &resolution)

Sets angle resolution values via  ScanResolution object. 
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution &distr, double rel_dev)
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution &distr, const std::vector< double > &rel_dev)

Sets angular resolution values via  RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets angular resolution values via  RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";


// File: classAnisoPyramid.xml
%feature("docstring") AnisoPyramid "";

%feature("docstring")  AnisoPyramid::AnisoPyramid "AnisoPyramid::AnisoPyramid(double length, double width, double height, double alpha)
";

%feature("docstring")  AnisoPyramid::~AnisoPyramid "AnisoPyramid::~AnisoPyramid()
";


// File: classAsymRippleBuilder.xml
%feature("docstring") AsymRippleBuilder "";

%feature("docstring")  AsymRippleBuilder::buildSample "MultiLayer * AsymRippleBuilder::buildSample() const
";


// File: classAveragedSlicedCylindersBuilder.xml
%feature("docstring") AveragedSlicedCylindersBuilder "

Provides exactly the same sample as  SLDSlicedCylindersBuilder, but with cylinders represented as homogeneous layers. SLD-based materials used. Assumed wavelength is 1.54 Angstrom.

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  AveragedSlicedCylindersBuilder::AveragedSlicedCylindersBuilder "AveragedSlicedCylindersBuilder::AveragedSlicedCylindersBuilder()
";

%feature("docstring")  AveragedSlicedCylindersBuilder::buildSample "MultiLayer * AveragedSlicedCylindersBuilder::buildSample() const override
";


// File: structAxesUnitsWrap.xml
%feature("docstring") AxesUnitsWrap "

Wrapper for detector axes units, required for a better representation of detector axes units in python

C++ includes: IUnitConverter.h
";


// File: structUnitConverterSimple_1_1AxisData.xml


// File: structAxisInfo.xml
%feature("docstring") AxisInfo "

Information about an axis in specific units. Can be used for plotting.

C++ includes: SimulationResult.h
";


// File: structArrayUtils_1_1CreateDataImpl_1_1baseClass.xml


// File: structArrayUtils_1_1CreateDataImpl_1_1baseClass_3_01std_1_1vector_3_01T_00_01A_01_4_01_4.xml


// File: classBaseMaterialImpl.xml
%feature("docstring") BaseMaterialImpl "";

%feature("docstring")  BaseMaterialImpl::BaseMaterialImpl "BaseMaterialImpl::BaseMaterialImpl(const std::string &name)

Constructs basic material with name. 
";

%feature("docstring")  BaseMaterialImpl::~BaseMaterialImpl "virtual BaseMaterialImpl::~BaseMaterialImpl()=default
";

%feature("docstring")  BaseMaterialImpl::clone "virtual BaseMaterialImpl* BaseMaterialImpl::clone() const =0

Returns pointer to a copy of material. 
";

%feature("docstring")  BaseMaterialImpl::inverted "virtual BaseMaterialImpl* BaseMaterialImpl::inverted() const =0

Constructs a material with inverted magnetization. 
";

%feature("docstring")  BaseMaterialImpl::refractiveIndex "virtual complex_t BaseMaterialImpl::refractiveIndex(double wavelength) const =0

Returns refractive index. 
";

%feature("docstring")  BaseMaterialImpl::refractiveIndex2 "virtual complex_t BaseMaterialImpl::refractiveIndex2(double wavelength) const =0

Returns squared refractive index. 
";

%feature("docstring")  BaseMaterialImpl::isScalarMaterial "virtual bool BaseMaterialImpl::isScalarMaterial() const =0

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  BaseMaterialImpl::isMagneticMaterial "virtual bool BaseMaterialImpl::isMagneticMaterial() const =0
";

%feature("docstring")  BaseMaterialImpl::magnetization "virtual kvector_t BaseMaterialImpl::magnetization() const =0

Returns the magnetization (in A/m) 
";

%feature("docstring")  BaseMaterialImpl::materialData "virtual complex_t BaseMaterialImpl::materialData() const =0

Returns underlying material data. 
";

%feature("docstring")  BaseMaterialImpl::typeID "virtual MATERIAL_TYPES BaseMaterialImpl::typeID() const =0

Returns type of material implementation. 
";

%feature("docstring")  BaseMaterialImpl::scalarSubtrSLD "virtual complex_t BaseMaterialImpl::scalarSubtrSLD(const WavevectorInfo &wavevectors) const =0

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld being the scattering length density. 
";

%feature("docstring")  BaseMaterialImpl::polarizedSubtrSLD "virtual Eigen::Matrix2cd BaseMaterialImpl::polarizedSubtrSLD(const WavevectorInfo &wavevectors) const =0

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld) matrix with magnetization corrections. 
";

%feature("docstring")  BaseMaterialImpl::transformedMaterial "virtual BaseMaterialImpl* BaseMaterialImpl::transformedMaterial(const Transform3D &transform) const =0
";

%feature("docstring")  BaseMaterialImpl::print "virtual void BaseMaterialImpl::print(std::ostream &ostr) const =0

Prints object data. 
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

%feature("docstring")  Basic2DParaCrystalBuilder::createSample "MultiLayer * Basic2DParaCrystalBuilder::createSample(size_t index=0)
";

%feature("docstring")  Basic2DParaCrystalBuilder::size "size_t Basic2DParaCrystalBuilder::size()
";


// File: classBasicLattice.xml
%feature("docstring") BasicLattice "";

%feature("docstring")  BasicLattice::BasicLattice "BasicLattice::BasicLattice(double length1, double length2, double angle, double rotation_angle=0.0)
";

%feature("docstring")  BasicLattice::clone "BasicLattice * BasicLattice::clone() const
";

%feature("docstring")  BasicLattice::accept "void BasicLattice::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  BasicLattice::length1 "virtual double BasicLattice::length1() const
";

%feature("docstring")  BasicLattice::length2 "virtual double BasicLattice::length2() const
";

%feature("docstring")  BasicLattice::latticeAngle "virtual double BasicLattice::latticeAngle() const
";

%feature("docstring")  BasicLattice::unitCellArea "double BasicLattice::unitCellArea() const
";


// File: classBasicVector3D.xml
%feature("docstring") BasicVector3D "

Forked from CLHEP/Geometry by E. Chernyaev Evgueni.Tcherniaev@cern.ch, then reworked beyond recongnition. Removed split of point and vector semantics. Transforms are relegated to a separate class  Transform3D. Three-dimensional vector template, for use with integer, double, or complex components.

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

Returns magnitude squared of the vector. 
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
";

%feature("docstring")  BasicVector3D::real "BasicVector3D< double > BasicVector3D< complex_t >::real() const
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D< complex_t > BasicVector3D< complex_t >::unit() const
";


// File: classBeam.xml
%feature("docstring") Beam "

Beam defined by wavelength, direction and intensity.

C++ includes: Beam.h
";

%feature("docstring")  Beam::Beam "Beam::Beam()
";

%feature("docstring")  Beam::Beam "Beam::Beam(const Beam &other)
";

%feature("docstring")  Beam::~Beam "Beam::~Beam()
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

%feature("docstring")  Beam::footprintFactor "const IFootprintFactor * Beam::footprintFactor() const

Returns footprint factor. 
";

%feature("docstring")  Beam::setFootprintFactor "void Beam::setFootprintFactor(const IFootprintFactor &shape_factor)

Sets footprint factor to the beam. 
";

%feature("docstring")  Beam::setWidthRatio "void Beam::setWidthRatio(double width_ratio)

Sets beam to sample width ratio in footprint factor. 
";

%feature("docstring")  Beam::setPolarization "void Beam::setPolarization(const kvector_t bloch_vector)

Sets the polarization density matrix according to the given Bloch vector. 
";

%feature("docstring")  Beam::getBlochVector "kvector_t Beam::getBlochVector() const
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

%feature("docstring")  Beam::accept "void Beam::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  Beam::getChildren "std::vector< const INode * > Beam::getChildren() const override

Returns a vector of children (const). 
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

%feature("docstring")  Bin1DCVector::Bin1DCVector "Bin1DCVector::Bin1DCVector(cvector_t lower, cvector_t upper)
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


// File: classBiPyramid.xml
%feature("docstring") BiPyramid "";

%feature("docstring")  BiPyramid::BiPyramid "BiPyramid::BiPyramid(double length, double height, double height_ratio, double alpha)
";

%feature("docstring")  BiPyramid::~BiPyramid "BiPyramid::~BiPyramid()
";


// File: classBox.xml
%feature("docstring") Box "";

%feature("docstring")  Box::Box "Box::Box(double length, double width, double height)
";

%feature("docstring")  Box::~Box "Box::~Box()
";


// File: classBoxCompositionBuilder.xml
%feature("docstring") BoxCompositionBuilder "

Parent class to test all kind of compositions made out of boxes. Reproduces Python functional test transform_BoxComposition.py

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


// File: classBoxesSquareLatticeBuilder.xml
%feature("docstring") BoxesSquareLatticeBuilder "

Builds sample: square boxes in a square lattice

C++ includes: BoxesSquareLatticeBuilder.h
";

%feature("docstring")  BoxesSquareLatticeBuilder::BoxesSquareLatticeBuilder "BoxesSquareLatticeBuilder::BoxesSquareLatticeBuilder()
";

%feature("docstring")  BoxesSquareLatticeBuilder::buildSample "MultiLayer * BoxesSquareLatticeBuilder::buildSample() const
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


// File: classCenteredSquareLatticeBuilder.xml
%feature("docstring") CenteredSquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  CenteredSquareLatticeBuilder::CenteredSquareLatticeBuilder "CenteredSquareLatticeBuilder::CenteredSquareLatticeBuilder()
";

%feature("docstring")  CenteredSquareLatticeBuilder::buildSample "MultiLayer * CenteredSquareLatticeBuilder::buildSample() const
";


// File: classChi2Metric.xml
%feature("docstring") Chi2Metric "

Implementation of the standard  $ \\\\chi^2 $ metric derived from maximum likelihood with Gaussian uncertainties. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(I - D)^2}{\\\\delta_D^2}\\\\]

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  Chi2Metric::Chi2Metric "Chi2Metric::Chi2Metric()
";

%feature("docstring")  Chi2Metric::clone "Chi2Metric * Chi2Metric::clone() const override
";

%feature("docstring")  Chi2Metric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  Chi2Metric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classChiModuleWrapper.xml
%feature("docstring") ChiModuleWrapper "

Metric wrapper for back-compaptibility with old scripts. 
";

%feature("docstring")  ChiModuleWrapper::ChiModuleWrapper "ChiModuleWrapper::ChiModuleWrapper(std::unique_ptr< IChiSquaredModule > module)
";

%feature("docstring")  ChiModuleWrapper::compute "double ChiModuleWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const override
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

%feature("docstring")  ChiSquaredModule::residual "double ChiSquaredModule::residual(double a, double b, double weight)
";


// File: classExceptions_1_1ClassInitializationException.xml
%feature("docstring") Exceptions::ClassInitializationException "";

%feature("docstring")  Exceptions::ClassInitializationException::ClassInitializationException "Exceptions::ClassInitializationException::ClassInitializationException(const std::string &message)
";


// File: classComplexIntegrator.xml
%feature("docstring") ComplexIntegrator "

To integrate a complex function of a real variable.

C++ includes: Integrator.h
";

%feature("docstring")  ComplexIntegrator::integrate "complex_t ComplexIntegrator::integrate(const std::function< complex_t(double)> &f, double lmin, double lmax)
";


// File: classComputationStatus.xml
%feature("docstring") ComputationStatus "

Completion status (flag and text) of a numeric computation.

C++ includes: ComputationStatus.h
";

%feature("docstring")  ComputationStatus::ComputationStatus "ComputationStatus::ComputationStatus()
";

%feature("docstring")  ComputationStatus::isCompleted "bool ComputationStatus::isCompleted() const
";

%feature("docstring")  ComputationStatus::errorMessage "std::string ComputationStatus::errorMessage() const
";

%feature("docstring")  ComputationStatus::setRunning "void ComputationStatus::setRunning()
";

%feature("docstring")  ComputationStatus::setCompleted "void ComputationStatus::setCompleted()
";

%feature("docstring")  ComputationStatus::setFailed "void ComputationStatus::setFailed()
";

%feature("docstring")  ComputationStatus::setErrorMessage "void ComputationStatus::setErrorMessage(const std::string &message)
";


// File: classConesWithLimitsDistributionBuilder.xml
%feature("docstring") ConesWithLimitsDistributionBuilder "

Cones with the distribution applied to the angle and RealLimits defined.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  ConesWithLimitsDistributionBuilder::ConesWithLimitsDistributionBuilder "ConesWithLimitsDistributionBuilder::ConesWithLimitsDistributionBuilder()
";

%feature("docstring")  ConesWithLimitsDistributionBuilder::buildSample "MultiLayer * ConesWithLimitsDistributionBuilder::buildSample() const
";


// File: classConstantBackground.xml
%feature("docstring") ConstantBackground "

Class representing a constant background signal

C++ includes: ConstantBackground.h
";

%feature("docstring")  ConstantBackground::ConstantBackground "ConstantBackground::ConstantBackground(double background_value)
";

%feature("docstring")  ConstantBackground::~ConstantBackground "ConstantBackground::~ConstantBackground()
";

%feature("docstring")  ConstantBackground::clone "ConstantBackground * ConstantBackground::clone() const override final
";

%feature("docstring")  ConstantBackground::backgroundValue "double ConstantBackground::backgroundValue() const
";

%feature("docstring")  ConstantBackground::accept "void ConstantBackground::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ConstantBackground::addBackGround "double ConstantBackground::addBackGround(double intensity) const override final
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

%feature("docstring")  ConstKBinAxis::~ConstKBinAxis "ConstKBinAxis::~ConstKBinAxis() final
";

%feature("docstring")  ConstKBinAxis::clone "ConstKBinAxis * ConstKBinAxis::clone() const final

clone function 
";

%feature("docstring")  ConstKBinAxis::createClippedAxis "ConstKBinAxis * ConstKBinAxis::createClippedAxis(double left, double right) const final

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

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(const IResolutionFunction2D &p_res_function_2d)

Constructor taking a 2 dimensional resolution function as argument. 
";

%feature("docstring")  ConvolutionDetectorResolution::~ConvolutionDetectorResolution "ConvolutionDetectorResolution::~ConvolutionDetectorResolution()
";

%feature("docstring")  ConvolutionDetectorResolution::applyDetectorResolution "void ConvolutionDetectorResolution::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Convolve given intensities with the encapsulated resolution. 
";

%feature("docstring")  ConvolutionDetectorResolution::clone "ConvolutionDetectorResolution * ConvolutionDetectorResolution::clone() const
";

%feature("docstring")  ConvolutionDetectorResolution::accept "void ConvolutionDetectorResolution::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ConvolutionDetectorResolution::getResolutionFunction2D "const IResolutionFunction2D * ConvolutionDetectorResolution::getResolutionFunction2D() const
";

%feature("docstring")  ConvolutionDetectorResolution::getChildren "std::vector< const INode * > ConvolutionDetectorResolution::getChildren() const

Returns a vector of children (const). 
";


// File: classConvolve.xml
%feature("docstring") Convolve "

Convolution of two real vectors (in 1D or 2D) using Fast Fourier Transform.

Usage: std::vector<double> signal, kernel, result;  Convolve cv; cv.fftconvolve(signal, kernel, result)

Given code rely on code from Jeremy Fix page, http://jeremy.fix.free.fr/spip.php?article15, see also \"Efficient convolution using the Fast Fourier Transform, Application in C++\" by Jeremy Fix, May 30, 2011

C++ includes: Convolve.h
";

%feature("docstring")  Convolve::Convolve "Convolve::Convolve()
";

%feature("docstring")  Convolve::fftconvolve "void Convolve::fftconvolve(const double1d_t &source, const double1d_t &kernel, double1d_t &result)

convolution in 1D 
";

%feature("docstring")  Convolve::fftconvolve "void Convolve::fftconvolve(const double2d_t &source, const double2d_t &kernel, double2d_t &result)

convolution in 2D 
";

%feature("docstring")  Convolve::init "void Convolve::init(int h_src, int w_src, int h_kernel, int w_kernel)

prepare arrays for 2D convolution of given vectors 
";

%feature("docstring")  Convolve::setMode "void Convolve::setMode(EConvolutionMode mode)

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


// File: classArrayUtils_1_1CreateDataImpl.xml
%feature("docstring") ArrayUtils::CreateDataImpl "";


// File: classCrystal.xml
%feature("docstring") Crystal "

A crystal structure with a  ParticleComposition as a basis. Used in  MesoCrystal, where it is given an outer shape.

C++ includes: Crystal.h
";

%feature("docstring")  Crystal::Crystal "Crystal::Crystal(const IParticle &lattice_basis, const Lattice &lattice)
";

%feature("docstring")  Crystal::~Crystal "Crystal::~Crystal()
";

%feature("docstring")  Crystal::clone "Crystal * Crystal::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  Crystal::accept "void Crystal::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  Crystal::createTotalFormFactor "IFormFactor * Crystal::createTotalFormFactor(const IFormFactor &meso_crystal_form_factor, const IRotation *p_rotation, const kvector_t &translation) const override final

Creates a total form factor for the mesocrystal with a specific shape and content The bulk content of the mesocrystal is encapsulated by the  IClusteredParticles object itself 
";

%feature("docstring")  Crystal::homogeneousRegions "std::vector< HomogeneousRegion > Crystal::homogeneousRegions() const override final

Creates region information with volumetric densities instead of absolute volume These densities need to be multiplied by the total mesocrystal volume 
";

%feature("docstring")  Crystal::transformedLattice "Lattice Crystal::transformedLattice(const IRotation *p_rotation=nullptr) const
";

%feature("docstring")  Crystal::setPositionVariance "void Crystal::setPositionVariance(double position_variance)
";

%feature("docstring")  Crystal::getChildren "std::vector< const INode * > Crystal::getChildren() const override final

Returns a vector of children (const). 
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

Builds sample: mixture of different particles (IsGISAXS example #7).

C++ includes: CustomMorphologyBuilder.h
";

%feature("docstring")  CustomMorphologyBuilder::CustomMorphologyBuilder "CustomMorphologyBuilder::CustomMorphologyBuilder()
";

%feature("docstring")  CustomMorphologyBuilder::buildSample "MultiLayer * CustomMorphologyBuilder::buildSample() const
";


// File: classCylindersAndPrismsBuilder.xml
%feature("docstring") CylindersAndPrismsBuilder "

Builds sample: mixture of cylinders and prisms without interference (IsGISAXS example #1).

C++ includes: CylindersAndPrismsBuilder.h
";

%feature("docstring")  CylindersAndPrismsBuilder::CylindersAndPrismsBuilder "CylindersAndPrismsBuilder::CylindersAndPrismsBuilder()
";

%feature("docstring")  CylindersAndPrismsBuilder::buildSample "MultiLayer * CylindersAndPrismsBuilder::buildSample() const
";


// File: classCylindersInBABuilder.xml
%feature("docstring") CylindersInBABuilder "

Builds sample: cylinder form factor in BA (IsGISAXS example #3, part II).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInBABuilder::CylindersInBABuilder "CylindersInBABuilder::CylindersInBABuilder()
";

%feature("docstring")  CylindersInBABuilder::buildSample "MultiLayer * CylindersInBABuilder::buildSample() const
";


// File: classCylindersInDWBABuilder.xml
%feature("docstring") CylindersInDWBABuilder "

Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).

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


// File: classDecouplingApproximationStrategy.xml
%feature("docstring") DecouplingApproximationStrategy "

Strategy class to compute the total scattering from a particle layout in the decoupling approximation.

C++ includes: DecouplingApproximationStrategy.h
";

%feature("docstring")  DecouplingApproximationStrategy::DecouplingApproximationStrategy "DecouplingApproximationStrategy::DecouplingApproximationStrategy(SimulationOptions sim_params, bool polarized)
";


// File: classDelayedProgressCounter.xml
%feature("docstring") DelayedProgressCounter "

Counter for reporting progress (with delay interval) in a threaded computation.

C++ includes: DelayedProgressCounter.h
";

%feature("docstring")  DelayedProgressCounter::DelayedProgressCounter "DelayedProgressCounter::DelayedProgressCounter(ProgressHandler *p_progress, size_t interval)
";

%feature("docstring")  DelayedProgressCounter::~DelayedProgressCounter "DelayedProgressCounter::~DelayedProgressCounter()
";

%feature("docstring")  DelayedProgressCounter::stepProgress "void DelayedProgressCounter::stepProgress()

Increments inner counter; at regular intervals updates progress handler. 
";


// File: classDepthProbeComputation.xml
%feature("docstring") DepthProbeComputation "

Performs a single-threaded depth probe computation with given sample.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: DepthProbeComputation.h
";

%feature("docstring")  DepthProbeComputation::DepthProbeComputation "DepthProbeComputation::DepthProbeComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, DepthProbeElementIter begin_it, DepthProbeElementIter end_it)
";

%feature("docstring")  DepthProbeComputation::~DepthProbeComputation "DepthProbeComputation::~DepthProbeComputation() override
";


// File: classDepthProbeComputationTerm.xml
%feature("docstring") DepthProbeComputationTerm "";

%feature("docstring")  DepthProbeComputationTerm::DepthProbeComputationTerm "DepthProbeComputationTerm::DepthProbeComputationTerm(const ProcessedSample *p_sample)
";

%feature("docstring")  DepthProbeComputationTerm::~DepthProbeComputationTerm "DepthProbeComputationTerm::~DepthProbeComputationTerm()
";

%feature("docstring")  DepthProbeComputationTerm::setProgressHandler "void DepthProbeComputationTerm::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  DepthProbeComputationTerm::compute "void DepthProbeComputationTerm::compute(DepthProbeElement &elem) const
";


// File: classDepthProbeConverter.xml
%feature("docstring") DepthProbeConverter "

DepthProbeConverter class handles the unit translations for depth probe simulations Its default units are radians for x-axis and nm for y-axis

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  DepthProbeConverter::DepthProbeConverter "DepthProbeConverter::DepthProbeConverter(const Beam &beam, const IAxis &alpha_axis, const IAxis &z_axis)
";

%feature("docstring")  DepthProbeConverter::~DepthProbeConverter "DepthProbeConverter::~DepthProbeConverter() override
";

%feature("docstring")  DepthProbeConverter::clone "DepthProbeConverter * DepthProbeConverter::clone() const override
";

%feature("docstring")  DepthProbeConverter::availableUnits "std::vector< AxesUnits > DepthProbeConverter::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  DepthProbeConverter::defaultUnits "AxesUnits DepthProbeConverter::defaultUnits() const override
";


// File: classDepthProbeElement.xml
%feature("docstring") DepthProbeElement "";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(double wavelength, double alpha_i, const IAxis *z_positions)
";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(const DepthProbeElement &other)
";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(DepthProbeElement &&other) noexcept
";

%feature("docstring")  DepthProbeElement::~DepthProbeElement "DepthProbeElement::~DepthProbeElement()
";

%feature("docstring")  DepthProbeElement::getWavelength "double DepthProbeElement::getWavelength() const
";

%feature("docstring")  DepthProbeElement::getAlphaI "double DepthProbeElement::getAlphaI() const
";

%feature("docstring")  DepthProbeElement::getKi "kvector_t DepthProbeElement::getKi() const
";

%feature("docstring")  DepthProbeElement::setIntensities "void DepthProbeElement::setIntensities(T &&intensities)
";

%feature("docstring")  DepthProbeElement::getIntensities "const std::valarray<double>& DepthProbeElement::getIntensities() const
";

%feature("docstring")  DepthProbeElement::setZPositions "void DepthProbeElement::setZPositions(const IAxis *z_positions)
";

%feature("docstring")  DepthProbeElement::getZPositions "const IAxis* DepthProbeElement::getZPositions() const
";

%feature("docstring")  DepthProbeElement::size "size_t DepthProbeElement::size() const
";

%feature("docstring")  DepthProbeElement::setCalculationFlag "void DepthProbeElement::setCalculationFlag(bool calculation_flag)

Set calculation flag (if it's false, zero intensity is assigned to the element) 
";

%feature("docstring")  DepthProbeElement::isCalculated "bool DepthProbeElement::isCalculated() const
";


// File: classDepthProbeSimulation.xml
%feature("docstring") DepthProbeSimulation "";

%feature("docstring")  DepthProbeSimulation::DepthProbeSimulation "DepthProbeSimulation::DepthProbeSimulation()
";

%feature("docstring")  DepthProbeSimulation::DepthProbeSimulation "DepthProbeSimulation::DepthProbeSimulation(const MultiLayer &sample)
";

%feature("docstring")  DepthProbeSimulation::DepthProbeSimulation "DepthProbeSimulation::DepthProbeSimulation(const std::shared_ptr< IMultiLayerBuilder > sample_builder)
";

%feature("docstring")  DepthProbeSimulation::~DepthProbeSimulation "DepthProbeSimulation::~DepthProbeSimulation() override
";

%feature("docstring")  DepthProbeSimulation::clone "DepthProbeSimulation * DepthProbeSimulation::clone() const override
";

%feature("docstring")  DepthProbeSimulation::accept "void DepthProbeSimulation::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  DepthProbeSimulation::result "SimulationResult DepthProbeSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  DepthProbeSimulation::setBeamParameters "void DepthProbeSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max, const IFootprintFactor *beam_shape=nullptr)

Sets beam parameters with alpha_i of the beam defined in the range. 
";

%feature("docstring")  DepthProbeSimulation::setZSpan "void DepthProbeSimulation::setZSpan(size_t n_bins, double z_min, double z_max)

Set z positions for intensity calculations. Negative z's correspond to the area under sample surface. The more negative z is, the deeper layer corresponds to it. 
";

%feature("docstring")  DepthProbeSimulation::getAlphaAxis "const IAxis * DepthProbeSimulation::getAlphaAxis() const

Returns a pointer to incident angle axis. 
";

%feature("docstring")  DepthProbeSimulation::getZAxis "const IAxis * DepthProbeSimulation::getZAxis() const

Returns a pointer to z-position axis. 
";

%feature("docstring")  DepthProbeSimulation::intensityMapSize "size_t DepthProbeSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  DepthProbeSimulation::createUnitConverter "std::unique_ptr< IUnitConverter > DepthProbeSimulation::createUnitConverter() const
";


// File: classDetectionProperties.xml
%feature("docstring") DetectionProperties "

Detector properties (efficiency, transmission).

C++ includes: DetectionProperties.h
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties()
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties(const DetectionProperties &other)
";

%feature("docstring")  DetectionProperties::~DetectionProperties "DetectionProperties::~DetectionProperties()
";

%feature("docstring")  DetectionProperties::setAnalyzerProperties "void DetectionProperties::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  DetectionProperties::analyzerOperator "Eigen::Matrix2cd DetectionProperties::analyzerOperator() const

Return the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  DetectionProperties::analyzerDirection "kvector_t DetectionProperties::analyzerDirection() const

Retrieve the analyzer characteristics. 
";

%feature("docstring")  DetectionProperties::analyzerEfficiency "double DetectionProperties::analyzerEfficiency() const

will always return positive value 
";

%feature("docstring")  DetectionProperties::analyzerTotalTransmission "double DetectionProperties::analyzerTotalTransmission() const
";

%feature("docstring")  DetectionProperties::accept "void DetectionProperties::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classDetectorContext.xml
%feature("docstring") DetectorContext "

Holds precalculated information for faster  SimulationElement generation.

C++ includes: DetectorContext.h
";

%feature("docstring")  DetectorContext::DetectorContext "DetectorContext::DetectorContext(const IDetector2D *detector)
";

%feature("docstring")  DetectorContext::DetectorContext "DetectorContext::DetectorContext(const DetectorContext &other)=delete
";

%feature("docstring")  DetectorContext::numberOfSimulationElements "size_t DetectorContext::numberOfSimulationElements() const
";

%feature("docstring")  DetectorContext::createPixel "std::unique_ptr< IPixel > DetectorContext::createPixel(size_t element_index) const

Creates pixel for given element index. Element index is sequetial index in a vector of SimulationElements. Corresponds to sequence of detector bins inside ROI and outside of masked areas. 
";

%feature("docstring")  DetectorContext::detectorIndex "size_t DetectorContext::detectorIndex(size_t element_index) const
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

%feature("docstring")  DetectorMask::addMask "void DetectorMask::addMask(const IShape2D &shape, bool mask_value)

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

%feature("docstring")  DetectorMask::getMaskShape "const IShape2D * DetectorMask::getMaskShape(size_t mask_index, bool &mask_value) const
";


// File: classDistribution1DCauchySampler.xml
%feature("docstring") Distribution1DCauchySampler "";

%feature("docstring")  Distribution1DCauchySampler::Distribution1DCauchySampler "Distribution1DCauchySampler::Distribution1DCauchySampler(double lambda)
";

%feature("docstring")  Distribution1DCauchySampler::randomSample "double Distribution1DCauchySampler::randomSample() const final
";


// File: classDistribution1DCosineSampler.xml
%feature("docstring") Distribution1DCosineSampler "";

%feature("docstring")  Distribution1DCosineSampler::Distribution1DCosineSampler "Distribution1DCosineSampler::Distribution1DCosineSampler(double omega)
";

%feature("docstring")  Distribution1DCosineSampler::randomSample "double Distribution1DCosineSampler::randomSample() const final
";


// File: classDistribution1DGateSampler.xml
%feature("docstring") Distribution1DGateSampler "";

%feature("docstring")  Distribution1DGateSampler::Distribution1DGateSampler "Distribution1DGateSampler::Distribution1DGateSampler(double a, double b)
";

%feature("docstring")  Distribution1DGateSampler::randomSample "double Distribution1DGateSampler::randomSample() const final
";


// File: classDistribution1DGaussSampler.xml
%feature("docstring") Distribution1DGaussSampler "";

%feature("docstring")  Distribution1DGaussSampler::Distribution1DGaussSampler "Distribution1DGaussSampler::Distribution1DGaussSampler(double mean, double stddev)
";

%feature("docstring")  Distribution1DGaussSampler::randomSample "double Distribution1DGaussSampler::randomSample() const final
";


// File: classDistribution1DTriangleSampler.xml
%feature("docstring") Distribution1DTriangleSampler "";

%feature("docstring")  Distribution1DTriangleSampler::Distribution1DTriangleSampler "Distribution1DTriangleSampler::Distribution1DTriangleSampler(double omega)
";

%feature("docstring")  Distribution1DTriangleSampler::randomSample "double Distribution1DTriangleSampler::randomSample() const final
";


// File: classDistribution2DCauchySampler.xml
%feature("docstring") Distribution2DCauchySampler "";

%feature("docstring")  Distribution2DCauchySampler::Distribution2DCauchySampler "Distribution2DCauchySampler::Distribution2DCauchySampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DCauchySampler::randomSample "std::pair< double, double > Distribution2DCauchySampler::randomSample() const final
";


// File: classDistribution2DConeSampler.xml
%feature("docstring") Distribution2DConeSampler "";

%feature("docstring")  Distribution2DConeSampler::Distribution2DConeSampler "Distribution2DConeSampler::Distribution2DConeSampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DConeSampler::randomSample "std::pair< double, double > Distribution2DConeSampler::randomSample() const final
";


// File: classDistribution2DGateSampler.xml
%feature("docstring") Distribution2DGateSampler "";

%feature("docstring")  Distribution2DGateSampler::Distribution2DGateSampler "Distribution2DGateSampler::Distribution2DGateSampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DGateSampler::randomSample "std::pair< double, double > Distribution2DGateSampler::randomSample() const final
";


// File: classDistribution2DGaussSampler.xml
%feature("docstring") Distribution2DGaussSampler "";

%feature("docstring")  Distribution2DGaussSampler::Distribution2DGaussSampler "Distribution2DGaussSampler::Distribution2DGaussSampler(double omega_x, double omega_y)
";

%feature("docstring")  Distribution2DGaussSampler::randomSample "std::pair< double, double > Distribution2DGaussSampler::randomSample() const final
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

%feature("docstring")  DistributionCosine::clone "DistributionCosine* DistributionCosine::clone() const final
";

%feature("docstring")  DistributionCosine::probabilityDensity "double DistributionCosine::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionCosine::getMean "double DistributionCosine::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionCosine::getSigma "double DistributionCosine::getSigma() const
";

%feature("docstring")  DistributionCosine::equidistantPoints "std::vector< double > DistributionCosine::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionCosine::isDelta "bool DistributionCosine::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionCosine::accept "void DistributionCosine::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  DistributionGate::clone "DistributionGate* DistributionGate::clone() const final
";

%feature("docstring")  DistributionGate::probabilityDensity "double DistributionGate::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionGate::getMean "double DistributionGate::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionGate::getMin "double DistributionGate::getMin() const
";

%feature("docstring")  DistributionGate::getMax "double DistributionGate::getMax() const
";

%feature("docstring")  DistributionGate::equidistantPoints "std::vector< double > DistributionGate::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

Returns list of sample values. 
";

%feature("docstring")  DistributionGate::isDelta "bool DistributionGate::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionGate::accept "void DistributionGate::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  DistributionGaussian::clone "DistributionGaussian* DistributionGaussian::clone() const final
";

%feature("docstring")  DistributionGaussian::probabilityDensity "double DistributionGaussian::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionGaussian::getMean "double DistributionGaussian::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionGaussian::getStdDev "double DistributionGaussian::getStdDev() const
";

%feature("docstring")  DistributionGaussian::equidistantPoints "std::vector< double > DistributionGaussian::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionGaussian::isDelta "bool DistributionGaussian::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionGaussian::accept "void DistributionGaussian::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  DistributionHandler::setParameterToMeans "void DistributionHandler::setParameterToMeans(ParameterPool *p_parameter_pool) const

Sets mean distribution values to the parameter pool. 
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

%feature("docstring")  DistributionLogNormal::clone "DistributionLogNormal* DistributionLogNormal::clone() const final
";

%feature("docstring")  DistributionLogNormal::probabilityDensity "double DistributionLogNormal::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionLogNormal::getMean "double DistributionLogNormal::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionLogNormal::getMedian "double DistributionLogNormal::getMedian() const
";

%feature("docstring")  DistributionLogNormal::getScalePar "double DistributionLogNormal::getScalePar() const
";

%feature("docstring")  DistributionLogNormal::equidistantPoints "std::vector< double > DistributionLogNormal::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionLogNormal::isDelta "bool DistributionLogNormal::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionLogNormal::accept "void DistributionLogNormal::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  DistributionLogNormal::setUnits "void DistributionLogNormal::setUnits(const std::string &units)

Sets distribution units. 
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

%feature("docstring")  DistributionLorentz::clone "DistributionLorentz* DistributionLorentz::clone() const final
";

%feature("docstring")  DistributionLorentz::probabilityDensity "double DistributionLorentz::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionLorentz::getMean "double DistributionLorentz::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionLorentz::getHWHM "double DistributionLorentz::getHWHM() const
";

%feature("docstring")  DistributionLorentz::equidistantPoints "std::vector< double > DistributionLorentz::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionLorentz::isDelta "bool DistributionLorentz::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionLorentz::accept "void DistributionLorentz::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classDistributionTrapezoid.xml
%feature("docstring") DistributionTrapezoid "

Trapezoidal distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionTrapezoid::DistributionTrapezoid "DistributionTrapezoid::DistributionTrapezoid()
";

%feature("docstring")  DistributionTrapezoid::DistributionTrapezoid "DistributionTrapezoid::DistributionTrapezoid(double center, double left_width, double middle_width, double right_width)
";

%feature("docstring")  DistributionTrapezoid::~DistributionTrapezoid "virtual DistributionTrapezoid::~DistributionTrapezoid()
";

%feature("docstring")  DistributionTrapezoid::clone "DistributionTrapezoid* DistributionTrapezoid::clone() const final
";

%feature("docstring")  DistributionTrapezoid::probabilityDensity "double DistributionTrapezoid::probabilityDensity(double x) const final

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  DistributionTrapezoid::getMean "double DistributionTrapezoid::getMean() const final

Returns the distribution-specific mean. 
";

%feature("docstring")  DistributionTrapezoid::getLeftWidth "double DistributionTrapezoid::getLeftWidth() const
";

%feature("docstring")  DistributionTrapezoid::getMiddleWidth "double DistributionTrapezoid::getMiddleWidth() const
";

%feature("docstring")  DistributionTrapezoid::getRightWidth "double DistributionTrapezoid::getRightWidth() const
";

%feature("docstring")  DistributionTrapezoid::equidistantPoints "std::vector< double > DistributionTrapezoid::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const

generate list of sample values 
";

%feature("docstring")  DistributionTrapezoid::isDelta "bool DistributionTrapezoid::isDelta() const final

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  DistributionTrapezoid::accept "void DistributionTrapezoid::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classExceptions_1_1DivisionByZeroException.xml
%feature("docstring") Exceptions::DivisionByZeroException "";

%feature("docstring")  Exceptions::DivisionByZeroException::DivisionByZeroException "Exceptions::DivisionByZeroException::DivisionByZeroException(const std::string &message)
";


// File: classDodecahedron.xml
%feature("docstring") Dodecahedron "";

%feature("docstring")  Dodecahedron::Dodecahedron "Dodecahedron::Dodecahedron(double edge)
";

%feature("docstring")  Dodecahedron::~Dodecahedron "Dodecahedron::~Dodecahedron()
";


// File: classExceptions_1_1DomainErrorException.xml
%feature("docstring") Exceptions::DomainErrorException "";

%feature("docstring")  Exceptions::DomainErrorException::DomainErrorException "Exceptions::DomainErrorException::DomainErrorException(const std::string &message)
";


// File: classDot.xml
%feature("docstring") Dot "";

%feature("docstring")  Dot::Dot "Dot::Dot()
";

%feature("docstring")  Dot::~Dot "Dot::~Dot()
";


// File: classDoubleEllipse.xml
%feature("docstring") DoubleEllipse "";

%feature("docstring")  DoubleEllipse::DoubleEllipse "DoubleEllipse::DoubleEllipse(double r0_x, double r0_y, double z, double rz_x, double rz_y)
";

%feature("docstring")  DoubleEllipse::~DoubleEllipse "DoubleEllipse::~DoubleEllipse()
";


// File: classDWBAComputation.xml
%feature("docstring") DWBAComputation "

Performs a single-threaded DWBA computation with given sample and simulation parameters.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: DWBAComputation.h
";

%feature("docstring")  DWBAComputation::DWBAComputation "DWBAComputation::DWBAComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, std::vector< SimulationElement >::iterator begin_it, std::vector< SimulationElement >::iterator end_it)
";

%feature("docstring")  DWBAComputation::~DWBAComputation "DWBAComputation::~DWBAComputation() override
";


// File: classDWBASingleComputation.xml
%feature("docstring") DWBASingleComputation "

Class that handles all the computations involved in GISAS (particles, roughness,...) for a single detector bin.

Called by DWBASimulation on each detector bin.

C++ includes: DWBASingleComputation.h
";

%feature("docstring")  DWBASingleComputation::DWBASingleComputation "DWBASingleComputation::DWBASingleComputation()
";

%feature("docstring")  DWBASingleComputation::~DWBASingleComputation "DWBASingleComputation::~DWBASingleComputation()
";

%feature("docstring")  DWBASingleComputation::DWBASingleComputation "DWBASingleComputation::DWBASingleComputation(DWBASingleComputation &&other)
";

%feature("docstring")  DWBASingleComputation::setProgressHandler "void DWBASingleComputation::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  DWBASingleComputation::addLayoutComputation "void DWBASingleComputation::addLayoutComputation(ParticleLayoutComputation *p_layout_comp)
";

%feature("docstring")  DWBASingleComputation::setRoughnessComputation "void DWBASingleComputation::setRoughnessComputation(RoughMultiLayerComputation *p_roughness_comp)
";

%feature("docstring")  DWBASingleComputation::setSpecularBinComputation "void DWBASingleComputation::setSpecularBinComputation(GISASSpecularComputation *p_spec_comp)
";

%feature("docstring")  DWBASingleComputation::compute "void DWBASingleComputation::compute(SimulationElement &elem) const
";

%feature("docstring")  DWBASingleComputation::regionMap "const std::map< size_t, std::vector< HomogeneousRegion > > & DWBASingleComputation::regionMap() const

Retrieves a map of regions for the calculation of averaged layers. 
";


// File: classEllipse.xml
%feature("docstring") Ellipse "

Ellipse shape.

C++ includes: Ellipse.h
";

%feature("docstring")  Ellipse::Ellipse "Ellipse::Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta=0.0)

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

%feature("docstring")  Ellipse::clone "Ellipse* Ellipse::clone() const
";

%feature("docstring")  Ellipse::contains "bool Ellipse::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Ellipse::contains "bool Ellipse::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of ellipse; more precisely, if mid point of two bins satisfy this condition. 
";

%feature("docstring")  Ellipse::getCenterX "double Ellipse::getCenterX() const
";

%feature("docstring")  Ellipse::getCenterY "double Ellipse::getCenterY() const
";

%feature("docstring")  Ellipse::getRadiusX "double Ellipse::getRadiusX() const
";

%feature("docstring")  Ellipse::getRadiusY "double Ellipse::getRadiusY() const
";

%feature("docstring")  Ellipse::getTheta "double Ellipse::getTheta() const
";


// File: classExceptions_1_1ExistingClassRegistrationException.xml
%feature("docstring") Exceptions::ExistingClassRegistrationException "";

%feature("docstring")  Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException "Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string &message)
";


// File: classExceptions_1_1FileIsBadException.xml
%feature("docstring") Exceptions::FileIsBadException "";

%feature("docstring")  Exceptions::FileIsBadException::FileIsBadException "Exceptions::FileIsBadException::FileIsBadException(const std::string &message)
";


// File: classExceptions_1_1FileNotIsOpenException.xml
%feature("docstring") Exceptions::FileNotIsOpenException "";

%feature("docstring")  Exceptions::FileNotIsOpenException::FileNotIsOpenException "Exceptions::FileNotIsOpenException::FileNotIsOpenException(const std::string &message)
";


// File: classFiniteSquareLatticeBuilder.xml
%feature("docstring") FiniteSquareLatticeBuilder "

Builds sample: 2D finite lattice with thermal disorder.

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  FiniteSquareLatticeBuilder::FiniteSquareLatticeBuilder "FiniteSquareLatticeBuilder::FiniteSquareLatticeBuilder()
";

%feature("docstring")  FiniteSquareLatticeBuilder::buildSample "MultiLayer * FiniteSquareLatticeBuilder::buildSample() const
";


// File: classFitObjective.xml
%feature("docstring") FitObjective "

Holds vector of   SimDataPairs (experimental data and simulation results) for use in fitting.

C++ includes: FitObjective.h
";

%feature("docstring")  FitObjective::FitObjective "FitObjective::FitObjective()
";

%feature("docstring")  FitObjective::~FitObjective "FitObjective::~FitObjective()
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

builder: 
simulation builder capable of producing simulations

data: 
experimental data array

uncertainties: 
data uncertainties array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(PyBuilderCallback &callback, const T &data, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

callback: 
simulation builder capable of producing simulations

data: 
experimental data array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(PyBuilderCallback &callback, const T &data, const T &uncertainties, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

callback: 
simulation builder capable of producing simulations

data: 
experimental data array

uncertainties: 
data uncertainties array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::evaluate "double FitObjective::evaluate(const Fit::Parameters &params)
";

%feature("docstring")  FitObjective::evaluate_residuals "std::vector< double > FitObjective::evaluate_residuals(const Fit::Parameters &params)
";

%feature("docstring")  FitObjective::numberOfFitElements "size_t FitObjective::numberOfFitElements() const
";

%feature("docstring")  FitObjective::simulationResult "SimulationResult FitObjective::simulationResult(size_t i_item=0) const

Returns simulation result in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::experimentalData "SimulationResult FitObjective::experimentalData(size_t i_item=0) const

Returns experimental data in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::uncertaintyData "SimulationResult FitObjective::uncertaintyData(size_t i_item=0) const

Returns experimental data uncertainties in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::relativeDifference "SimulationResult FitObjective::relativeDifference(size_t i_item=0) const

Returns relative difference between simulation and experimental data in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::absoluteDifference "SimulationResult FitObjective::absoluteDifference(size_t i_item=0) const

Returns absolute value of difference between simulation and experimental data in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::experimental_array "std::vector< double > FitObjective::experimental_array() const

Returns one dimensional array representing merged experimental data. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::simulation_array "std::vector< double > FitObjective::simulation_array() const

Returns one dimensional array representing merged simulated intensities data. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::uncertainties "std::vector< double > FitObjective::uncertainties() const

Returns one-dimensional array representing merged data uncertainties. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::weights_array "std::vector< double > FitObjective::weights_array() const

Returns one-dimensional array representing merged user weights. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::initPrint "void FitObjective::initPrint(int every_nth)

Initializes printing to standard output during the fitting.

Parameters:
-----------

every_nth: 
Print every n'th iteration. 
";

%feature("docstring")  FitObjective::initPlot "void FitObjective::initPlot(int every_nth, PyObserverCallback &callback)

Initializes plotting during the fitting using Python callable.

Parameters:
-----------

every_nth: 
Called on every n'th iteration. 
";

%feature("docstring")  FitObjective::iterationInfo "IterationInfo FitObjective::iterationInfo() const
";

%feature("docstring")  FitObjective::minimizerResult "Fit::MinimizerResult FitObjective::minimizerResult() const
";

%feature("docstring")  FitObjective::finalize "void FitObjective::finalize(const Fit::MinimizerResult &result)

Should be explicitely called on last iteration to notify all observers. 
";

%feature("docstring")  FitObjective::fitObjectCount "unsigned FitObjective::fitObjectCount() const
";

%feature("docstring")  FitObjective::run_simulations "void FitObjective::run_simulations(const Fit::Parameters &params)
";

%feature("docstring")  FitObjective::setChiSquaredModule "void FitObjective::setChiSquaredModule(const IChiSquaredModule &module)
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(const std::string &metric)
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(const std::string &metric, const std::string &norm)

Sets objective metric to the  FitObjective.

Parameters:
-----------

metric: 
metric name

norm: 
metric norm name (defaults to L2-norm) 
";

%feature("docstring")  FitObjective::containsUncertainties "bool FitObjective::containsUncertainties(size_t i_item) const

Returns true if the specified DataPair element contains uncertainties. 
";

%feature("docstring")  FitObjective::allPairsHaveUncertainties "bool FitObjective::allPairsHaveUncertainties() const

Returns true if all the data pairs in  FitObjective instance contain uncertainties. 
";

%feature("docstring")  FitObjective::dataPair "const SimDataPair & FitObjective::dataPair(size_t i_item=0) const

Returns a reference to i-th  SimDataPair. 
";

%feature("docstring")  FitObjective::initPlot "void FitObjective::initPlot(int every_nth, fit_observer_t observer)
";

%feature("docstring")  FitObjective::isCompleted "bool FitObjective::isCompleted() const
";

%feature("docstring")  FitObjective::interruptFitting "void FitObjective::interruptFitting()
";

%feature("docstring")  FitObjective::isInterrupted "bool FitObjective::isInterrupted() const
";

%feature("docstring")  FitObjective::isFirstIteration "bool FitObjective::isFirstIteration() const
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(std::unique_ptr< ObjectiveMetric > metric)
";


// File: classFitObserver.xml
%feature("docstring") FitObserver "

Contains collection of observers and call them at specified intervals. Each observer will be called at first iteration and every-nth iterations.

C++ includes: FitObserver.h
";

%feature("docstring")  FitObserver::FitObserver "FitObserver< T >::FitObserver()
";

%feature("docstring")  FitObserver::addObserver "void FitObserver< T >::addObserver(int every_nth, observer_t observer)

Adds observer to the list.

Parameters:
-----------

every_nth: 
An observer function will be called every_nth iterations.

observer: 
Observer function to be called. 
";

%feature("docstring")  FitObserver::notify "void FitObserver< T >::notify(const T &data)

Notifies all observers at their personally specified intervals.

Parameters:
-----------

data: 
The data which will be passed to the observer. 
";

%feature("docstring")  FitObserver::notify_all "void FitObserver< T >::notify_all(const T &data)
";


// File: classFitPrintService.xml
%feature("docstring") FitPrintService "

Prints fit statistics to standard output during minimizer iterations.

C++ includes: FitPrintService.h
";

%feature("docstring")  FitPrintService::FitPrintService "FitPrintService::FitPrintService()
";

%feature("docstring")  FitPrintService::print "void FitPrintService::print(const FitObjective &objective)
";


// File: classFitStatus.xml
%feature("docstring") FitStatus "

Contains status of the fitting (running, interupted etc) and all intermediate information which has to be collected during the fit. Owned by  FitObjective.

C++ includes: FitStatus.h
";

%feature("docstring")  FitStatus::FitStatus "FitStatus::FitStatus(const FitObjective *fit_objective)
";

%feature("docstring")  FitStatus::~FitStatus "FitStatus::~FitStatus()
";

%feature("docstring")  FitStatus::setInterrupted "void FitStatus::setInterrupted()
";

%feature("docstring")  FitStatus::isInterrupted "bool FitStatus::isInterrupted() const
";

%feature("docstring")  FitStatus::isCompleted "bool FitStatus::isCompleted() const
";

%feature("docstring")  FitStatus::update "void FitStatus::update(const Fit::Parameters &params, double chi2)
";

%feature("docstring")  FitStatus::initPrint "void FitStatus::initPrint(int every_nth)
";

%feature("docstring")  FitStatus::addObserver "void FitStatus::addObserver(int every_nth, fit_observer_t)
";

%feature("docstring")  FitStatus::iterationInfo "IterationInfo FitStatus::iterationInfo() const
";

%feature("docstring")  FitStatus::minimizerResult "Fit::MinimizerResult FitStatus::minimizerResult() const
";

%feature("docstring")  FitStatus::finalize "void FitStatus::finalize(const Fit::MinimizerResult &result)

Should be explicitely called on last iteration to notify all observers. 
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


// File: classFootprintFactorGaussian.xml
%feature("docstring") FootprintFactorGaussian "

Calculates footprint coefficient for a gaussian beam  Beam width is interpreted as the full width on the level of  \\\\[ \\\\exp{-1/2} \\\\] from the peak intensity.

C++ includes: FootprintFactorGaussian.h
";

%feature("docstring")  FootprintFactorGaussian::FootprintFactorGaussian "FootprintFactorGaussian::FootprintFactorGaussian(double width_ratio)
";

%feature("docstring")  FootprintFactorGaussian::accept "void FootprintFactorGaussian::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FootprintFactorGaussian::clone "FootprintFactorGaussian * FootprintFactorGaussian::clone() const override
";

%feature("docstring")  FootprintFactorGaussian::calculate "double FootprintFactorGaussian::calculate(double alpha) const override

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  FootprintFactorGaussian::print "std::string FootprintFactorGaussian::print() const override

Print python-formatted footprint definition. 
";


// File: classFootprintFactorSquare.xml
%feature("docstring") FootprintFactorSquare "

Calculates footprint coefficient for a square beam

C++ includes: FootprintFactorSquare.h
";

%feature("docstring")  FootprintFactorSquare::FootprintFactorSquare "FootprintFactorSquare::FootprintFactorSquare(double width_ratio)
";

%feature("docstring")  FootprintFactorSquare::accept "void FootprintFactorSquare::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FootprintFactorSquare::clone "FootprintFactorSquare * FootprintFactorSquare::clone() const override
";

%feature("docstring")  FootprintFactorSquare::calculate "double FootprintFactorSquare::calculate(double alpha) const override

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  FootprintFactorSquare::print "std::string FootprintFactorSquare::print() const override

Print python-formatted footprint definition. 
";


// File: classExceptions_1_1FormatErrorException.xml
%feature("docstring") Exceptions::FormatErrorException "";

%feature("docstring")  Exceptions::FormatErrorException::FormatErrorException "Exceptions::FormatErrorException::FormatErrorException(const std::string &message)
";


// File: classFormFactorAnisoPyramid.xml
%feature("docstring") FormFactorAnisoPyramid "

A frustum (truncated pyramid) with rectangular base.

C++ includes: FormFactorAnisoPyramid.h
";

%feature("docstring")  FormFactorAnisoPyramid::FormFactorAnisoPyramid "FormFactorAnisoPyramid::FormFactorAnisoPyramid(double length, double width, double height, double alpha)

Constructor of a truncated pyramid with a rectangular base.

Parameters:
-----------

length: 
length of the rectangular base in nm

width: 
width of the rectangular base in nm

height: 
height of pyramid in nm

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorAnisoPyramid::clone "FormFactorAnisoPyramid* FormFactorAnisoPyramid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorAnisoPyramid::accept "void FormFactorAnisoPyramid::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorAnisoPyramid::getLength "double FormFactorAnisoPyramid::getLength() const
";

%feature("docstring")  FormFactorAnisoPyramid::getWidth "double FormFactorAnisoPyramid::getWidth() const
";

%feature("docstring")  FormFactorAnisoPyramid::getHeight "double FormFactorAnisoPyramid::getHeight() const
";

%feature("docstring")  FormFactorAnisoPyramid::getAlpha "double FormFactorAnisoPyramid::getAlpha() const
";


// File: classFormFactorBAPol.xml
%feature("docstring") FormFactorBAPol "

Evaluates the matrix BA term in a polarized  IFormFactor.

C++ includes: FormFactorBAPol.h
";

%feature("docstring")  FormFactorBAPol::FormFactorBAPol "FormFactorBAPol::FormFactorBAPol(const IFormFactor &form_factor)
";

%feature("docstring")  FormFactorBAPol::~FormFactorBAPol "FormFactorBAPol::~FormFactorBAPol() override
";

%feature("docstring")  FormFactorBAPol::clone "FormFactorBAPol * FormFactorBAPol::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorBAPol::accept "void FormFactorBAPol::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorBAPol::setAmbientMaterial "void FormFactorBAPol::setAmbientMaterial(Material material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorBAPol::evaluate "complex_t FormFactorBAPol::evaluate(const WavevectorInfo &wavevectors) const override

Throws not-implemented exception. 
";

%feature("docstring")  FormFactorBAPol::evaluatePol "Eigen::Matrix2cd FormFactorBAPol::evaluatePol(const WavevectorInfo &wavevectors) const override

Calculates and returns a polarized form factor calculation in BA. 
";

%feature("docstring")  FormFactorBAPol::volume "double FormFactorBAPol::volume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorBAPol::radialExtension "double FormFactorBAPol::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorBAPol::bottomZ "double FormFactorBAPol::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorBAPol::topZ "double FormFactorBAPol::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";


// File: classFormFactorBarGauss.xml
%feature("docstring") FormFactorBarGauss "

The form factor of an elongated bar, with Gaussian profile in elongation direction.

C++ includes: FormFactorBar.h
";

%feature("docstring")  FormFactorBarGauss::FormFactorBarGauss "FormFactorBarGauss::FormFactorBarGauss(double length, double width, double height)
";

%feature("docstring")  FormFactorBarGauss::clone "FormFactorBarGauss * FormFactorBarGauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorBarGauss::accept "void FormFactorBarGauss::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classFormFactorBarLorentz.xml
%feature("docstring") FormFactorBarLorentz "

The form factor of an elongated, with Lorentz form factor in elongation direction.

C++ includes: FormFactorBar.h
";

%feature("docstring")  FormFactorBarLorentz::FormFactorBarLorentz "FormFactorBarLorentz::FormFactorBarLorentz(double length, double width, double height)
";

%feature("docstring")  FormFactorBarLorentz::clone "FormFactorBarLorentz * FormFactorBarLorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorBarLorentz::accept "void FormFactorBarLorentz::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classFormFactorBox.xml
%feature("docstring") FormFactorBox "

A rectangular prism (parallelepiped).

C++ includes: FormFactorBox.h
";

%feature("docstring")  FormFactorBox::FormFactorBox "FormFactorBox::FormFactorBox(double length, double width, double height)

Constructor of a rectangular cuboid.

Parameters:
-----------

length: 
length of the base in nanometers

width: 
width of the base in nanometers

height: 
height of the box in nanometers 
";

%feature("docstring")  FormFactorBox::clone "FormFactorBox* FormFactorBox::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorBox::accept "void FormFactorBox::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorBox::getLength "double FormFactorBox::getLength() const
";

%feature("docstring")  FormFactorBox::getHeight "double FormFactorBox::getHeight() const
";

%feature("docstring")  FormFactorBox::getWidth "double FormFactorBox::getWidth() const
";

%feature("docstring")  FormFactorBox::radialExtension "double FormFactorBox::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorBox::evaluate_for_q "complex_t FormFactorBox::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorCantellatedCube.xml
%feature("docstring") FormFactorCantellatedCube "

A cube, with truncation of all edges and corners, as in Croset (2017) Fig 7

C++ includes: FormFactorCantellatedCube.h
";

%feature("docstring")  FormFactorCantellatedCube::FormFactorCantellatedCube "FormFactorCantellatedCube::FormFactorCantellatedCube(double length, double removed_length)

Constructor of a truncated cube.

Parameters:
-----------

length: 
length of the full cube's edge in nanometers

removed_length: 
removed length from each edge of the cube in nanometers 
";

%feature("docstring")  FormFactorCantellatedCube::clone "FormFactorCantellatedCube* FormFactorCantellatedCube::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCantellatedCube::accept "void FormFactorCantellatedCube::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorCantellatedCube::getLength "double FormFactorCantellatedCube::getLength() const
";

%feature("docstring")  FormFactorCantellatedCube::getRemovedLength "double FormFactorCantellatedCube::getRemovedLength() const
";


// File: classFormFactorCoherentPart.xml
%feature("docstring") FormFactorCoherentPart "

Information about single particle form factor and specular info of the embedding layer.

C++ includes: FormFactorCoherentPart.h
";

%feature("docstring")  FormFactorCoherentPart::FormFactorCoherentPart "FormFactorCoherentPart::FormFactorCoherentPart(IFormFactor *p_ff)
";

%feature("docstring")  FormFactorCoherentPart::FormFactorCoherentPart "FormFactorCoherentPart::FormFactorCoherentPart(const FormFactorCoherentPart &other)
";

%feature("docstring")  FormFactorCoherentPart::FormFactorCoherentPart "FormFactorCoherentPart::FormFactorCoherentPart(FormFactorCoherentPart &&other)
";

%feature("docstring")  FormFactorCoherentPart::~FormFactorCoherentPart "FormFactorCoherentPart::~FormFactorCoherentPart()
";

%feature("docstring")  FormFactorCoherentPart::evaluate "complex_t FormFactorCoherentPart::evaluate(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentPart::evaluatePol "Eigen::Matrix2cd FormFactorCoherentPart::evaluatePol(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentPart::setSpecularInfo "void FormFactorCoherentPart::setSpecularInfo(const IFresnelMap *p_fresnel_map, size_t layer_index)
";

%feature("docstring")  FormFactorCoherentPart::radialExtension "double FormFactorCoherentPart::radialExtension() const
";


// File: classFormFactorCoherentSum.xml
%feature("docstring") FormFactorCoherentSum "

Information about particle form factor and abundance.

C++ includes: FormFactorCoherentSum.h
";

%feature("docstring")  FormFactorCoherentSum::FormFactorCoherentSum "FormFactorCoherentSum::FormFactorCoherentSum(double abundance)
";

%feature("docstring")  FormFactorCoherentSum::addCoherentPart "void FormFactorCoherentSum::addCoherentPart(const FormFactorCoherentPart &part)
";

%feature("docstring")  FormFactorCoherentSum::evaluate "complex_t FormFactorCoherentSum::evaluate(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentSum::evaluatePol "Eigen::Matrix2cd FormFactorCoherentSum::evaluatePol(const SimulationElement &sim_element) const
";

%feature("docstring")  FormFactorCoherentSum::relativeAbundance "double FormFactorCoherentSum::relativeAbundance() const
";

%feature("docstring")  FormFactorCoherentSum::scaleRelativeAbundance "void FormFactorCoherentSum::scaleRelativeAbundance(double total_abundance)
";

%feature("docstring")  FormFactorCoherentSum::radialExtension "double FormFactorCoherentSum::radialExtension() const
";


// File: classFormFactorComponents.xml
%feature("docstring") FormFactorComponents "

Predefined form factors for functional tests.

C++ includes: SampleComponents.h
";

%feature("docstring")  FormFactorComponents::FormFactorComponents "FormFactorComponents::FormFactorComponents()
";


// File: classFormFactorCone.xml
%feature("docstring") FormFactorCone "

A conical frustum (cone truncated parallel to the base) with circular base.

C++ includes: FormFactorCone.h
";

%feature("docstring")  FormFactorCone::FormFactorCone "FormFactorCone::FormFactorCone(double radius, double height, double alpha)

Constructor of a truncated cone with circular base.

Parameters:
-----------

radius: 
radius of the base in nanometers

height: 
height of the cone in nanometers

alpha: 
angle between the base and the side surface in radians 
";

%feature("docstring")  FormFactorCone::clone "FormFactorCone* FormFactorCone::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCone::accept "void FormFactorCone::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorCone::getHeight "double FormFactorCone::getHeight() const
";

%feature("docstring")  FormFactorCone::getAlpha "double FormFactorCone::getAlpha() const
";

%feature("docstring")  FormFactorCone::getRadius "double FormFactorCone::getRadius() const
";

%feature("docstring")  FormFactorCone::radialExtension "double FormFactorCone::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCone::evaluate_for_q "complex_t FormFactorCone::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorCone6.xml
%feature("docstring") FormFactorCone6 "

A frustum (truncated pyramid) with regular hexagonal base.

C++ includes: FormFactorCone6.h
";

%feature("docstring")  FormFactorCone6::FormFactorCone6 "FormFactorCone6::FormFactorCone6(double base_edge, double height, double alpha)

Constructor of a truncated pyramid, based on a regular hexagon

Parameters:
-----------

base_edge: 
Edge of the regular hexagonal base in nanometers

height: 
height of a truncated pyramid in nanometers

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorCone6::clone "FormFactorCone6* FormFactorCone6::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCone6::accept "void FormFactorCone6::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorCone6::getBaseEdge "double FormFactorCone6::getBaseEdge() const
";

%feature("docstring")  FormFactorCone6::getHeight "double FormFactorCone6::getHeight() const
";

%feature("docstring")  FormFactorCone6::getAlpha "double FormFactorCone6::getAlpha() const
";


// File: classFormFactorCoreShell.xml
%feature("docstring") FormFactorCoreShell "

Form Factor for a core shell particle.

Used by  ParticleCoreShell.

C++ includes: FormFactorCoreShell.h
";

%feature("docstring")  FormFactorCoreShell::FormFactorCoreShell "FormFactorCoreShell::FormFactorCoreShell(IFormFactor *core, IFormFactor *shell)
";

%feature("docstring")  FormFactorCoreShell::~FormFactorCoreShell "FormFactorCoreShell::~FormFactorCoreShell() override final
";

%feature("docstring")  FormFactorCoreShell::clone "FormFactorCoreShell * FormFactorCoreShell::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCoreShell::accept "void FormFactorCoreShell::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorCoreShell::radialExtension "double FormFactorCoreShell::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCoreShell::bottomZ "double FormFactorCoreShell::bottomZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorCoreShell::topZ "double FormFactorCoreShell::topZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorCoreShell::setAmbientMaterial "void FormFactorCoreShell::setAmbientMaterial(Material material) override final

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorCoreShell::evaluate "complex_t FormFactorCoreShell::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorCoreShell::evaluatePol "Eigen::Matrix2cd FormFactorCoreShell::evaluatePol(const WavevectorInfo &wavevectors) const override final

Calculates and returns a polarized form factor calculation in DWBA. 
";


// File: classFormFactorCrystal.xml
%feature("docstring") FormFactorCrystal "

The form factor of a  MesoCrystal.

C++ includes: FormFactorCrystal.h
";

%feature("docstring")  FormFactorCrystal::FormFactorCrystal "FormFactorCrystal::FormFactorCrystal(const Lattice &lattice, const IFormFactor &basis_form_factor, const IFormFactor &meso_form_factor, double position_variance=0.0)
";

%feature("docstring")  FormFactorCrystal::~FormFactorCrystal "FormFactorCrystal::~FormFactorCrystal() override final
";

%feature("docstring")  FormFactorCrystal::clone "FormFactorCrystal* FormFactorCrystal::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCrystal::accept "void FormFactorCrystal::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorCrystal::setAmbientMaterial "void FormFactorCrystal::setAmbientMaterial(Material material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorCrystal::volume "double FormFactorCrystal::volume() const override final

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorCrystal::radialExtension "double FormFactorCrystal::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCrystal::bottomZ "double FormFactorCrystal::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorCrystal::topZ "double FormFactorCrystal::topZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
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

Constructor of cuboctahedron (compound of two truncated pyramids with a common square base and opposite orientations).

Parameters:
-----------

length: 
side length of the common square base in nanometers

height: 
height of the lower pyramid in nanometers

height_ratio: 
ratio of heights of top to bottom pyramids

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorCuboctahedron::clone "FormFactorCuboctahedron* FormFactorCuboctahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCuboctahedron::accept "void FormFactorCuboctahedron::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
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

Constructor of a cylinder with a circular base.

Parameters:
-----------

radius: 
radius of the circular base in nanometers

height: 
height of the cylinder in nanometers 
";

%feature("docstring")  FormFactorCylinder::clone "FormFactorCylinder* FormFactorCylinder::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCylinder::accept "void FormFactorCylinder::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorCylinder::getHeight "double FormFactorCylinder::getHeight() const
";

%feature("docstring")  FormFactorCylinder::getRadius "double FormFactorCylinder::getRadius() const
";

%feature("docstring")  FormFactorCylinder::radialExtension "double FormFactorCylinder::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCylinder::evaluate_for_q "complex_t FormFactorCylinder::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorDebyeBueche.xml
%feature("docstring") FormFactorDebyeBueche "

The form factor of a Debye-Bueche (see doi:10.1038/pj.2010.110).

C++ includes: FormFactorDebyeBueche.h
";

%feature("docstring")  FormFactorDebyeBueche::FormFactorDebyeBueche "FormFactorDebyeBueche::FormFactorDebyeBueche(double I0, double xi)
";

%feature("docstring")  FormFactorDebyeBueche::clone "FormFactorDebyeBueche* FormFactorDebyeBueche::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDebyeBueche::accept "void FormFactorDebyeBueche::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDebyeBueche::radialExtension "double FormFactorDebyeBueche::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDebyeBueche::evaluate_for_q "complex_t FormFactorDebyeBueche::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
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

%feature("docstring")  FormFactorDecoratorMaterial::accept "void FormFactorDecoratorMaterial::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorMaterial::setMaterial "void FormFactorDecoratorMaterial::setMaterial(Material material)

Sets the material of the scatterer. 
";

%feature("docstring")  FormFactorDecoratorMaterial::setAmbientMaterial "void FormFactorDecoratorMaterial::setAmbientMaterial(Material material) override

Sets the ambient material. 
";

%feature("docstring")  FormFactorDecoratorMaterial::evaluate "complex_t FormFactorDecoratorMaterial::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorMaterial::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorPositionFactor.xml
%feature("docstring") FormFactorDecoratorPositionFactor "

Decorates a form factor with a position dependent phase factor.

C++ includes: FormFactorDecoratorPositionFactor.h
";

%feature("docstring")  FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor "FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(const IFormFactor &form_factor, const kvector_t &position)
";

%feature("docstring")  FormFactorDecoratorPositionFactor::clone "FormFactorDecoratorPositionFactor* FormFactorDecoratorPositionFactor::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::accept "void FormFactorDecoratorPositionFactor::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::bottomZ "double FormFactorDecoratorPositionFactor::bottomZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::topZ "double FormFactorDecoratorPositionFactor::topZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluate "complex_t FormFactorDecoratorPositionFactor::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorPositionFactor::evaluatePol(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorRotation.xml
%feature("docstring") FormFactorDecoratorRotation "

Equips a form factor with a rotation.

C++ includes: FormFactorDecoratorRotation.h
";

%feature("docstring")  FormFactorDecoratorRotation::FormFactorDecoratorRotation "FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor &form_factor, const IRotation &rotation)

Constructor, setting form factor and rotation. 
";

%feature("docstring")  FormFactorDecoratorRotation::clone "FormFactorDecoratorRotation * FormFactorDecoratorRotation::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorRotation::accept "void FormFactorDecoratorRotation::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorRotation::bottomZ "double FormFactorDecoratorRotation::bottomZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDecoratorRotation::topZ "double FormFactorDecoratorRotation::topZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
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

Constructor of a dodecahedron.

Parameters:
-----------

edge: 
length of the edge in nanometers 
";

%feature("docstring")  FormFactorDodecahedron::clone "FormFactorDodecahedron* FormFactorDodecahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDodecahedron::accept "void FormFactorDodecahedron::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDodecahedron::getEdge "double FormFactorDodecahedron::getEdge() const
";


// File: classFormFactorDot.xml
%feature("docstring") FormFactorDot "

A dot, with scattering power as a sphere of radius rscat, but with F(q)=const.

C++ includes: FormFactorDot.h
";

%feature("docstring")  FormFactorDot::FormFactorDot "FormFactorDot::FormFactorDot(double radius)

Constructor.

Parameters:
-----------

rscat: 
radius of a sphere with same forward scattering power, in nanometers 
";

%feature("docstring")  FormFactorDot::clone "FormFactorDot* FormFactorDot::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDot::accept "void FormFactorDot::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDot::getRadius "double FormFactorDot::getRadius() const
";

%feature("docstring")  FormFactorDot::radialExtension "double FormFactorDot::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDot::bottomZ "double FormFactorDot::bottomZ(const IRotation &) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDot::topZ "double FormFactorDot::topZ(const IRotation &) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDot::evaluate_for_q "complex_t FormFactorDot::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
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

%feature("docstring")  FormFactorDWBA::accept "void FormFactorDWBA::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDWBA::setAmbientMaterial "void FormFactorDWBA::setAmbientMaterial(Material material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorDWBA::evaluate "complex_t FormFactorDWBA::evaluate(const WavevectorInfo &wavevectors) const override

Calculates and returns a form factor calculation in DWBA. 
";

%feature("docstring")  FormFactorDWBA::volume "double FormFactorDWBA::volume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorDWBA::radialExtension "double FormFactorDWBA::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDWBA::bottomZ "double FormFactorDWBA::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDWBA::topZ "double FormFactorDWBA::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDWBA::setSpecularInfo "void FormFactorDWBA::setSpecularInfo(std::unique_ptr< const ILayerRTCoefficients > p_in_coeffs, std::unique_ptr< const ILayerRTCoefficients > p_out_coeffs) override

Sets reflection/transmission info. 
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

%feature("docstring")  FormFactorDWBAPol::accept "void FormFactorDWBAPol::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorDWBAPol::setAmbientMaterial "void FormFactorDWBAPol::setAmbientMaterial(Material material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorDWBAPol::evaluate "complex_t FormFactorDWBAPol::evaluate(const WavevectorInfo &wavevectors) const override

Throws not-implemented exception. 
";

%feature("docstring")  FormFactorDWBAPol::evaluatePol "Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const WavevectorInfo &wavevectors) const override

Calculates and returns a polarized form factor calculation in DWBA. 
";

%feature("docstring")  FormFactorDWBAPol::volume "double FormFactorDWBAPol::volume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorDWBAPol::radialExtension "double FormFactorDWBAPol::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDWBAPol::bottomZ "double FormFactorDWBAPol::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDWBAPol::topZ "double FormFactorDWBAPol::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorDWBAPol::setSpecularInfo "void FormFactorDWBAPol::setSpecularInfo(std::unique_ptr< const ILayerRTCoefficients > p_in_coeffs, std::unique_ptr< const ILayerRTCoefficients > p_out_coeffs) override

Sets reflection/transmission info. 
";


// File: classFormFactorEllipsoidalCylinder.xml
%feature("docstring") FormFactorEllipsoidalCylinder "

A cylinder with elliptical base.

C++ includes: FormFactorEllipsoidalCylinder.h
";

%feature("docstring")  FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder "FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_x, double radius_y, double height)

Constructor of a cylinder with an ellipse cross section.

Parameters:
-----------

radius_x: 
radius of the ellipse base in the x-direction, in nanometers

radius_y: 
radius of the ellipse base in the y-direction, in nanometers

height: 
height of the ellipsoidal cylinder in nanometers 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::clone "FormFactorEllipsoidalCylinder* FormFactorEllipsoidalCylinder::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::accept "void FormFactorEllipsoidalCylinder::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusX "double FormFactorEllipsoidalCylinder::getRadiusX() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusY "double FormFactorEllipsoidalCylinder::getRadiusY() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getHeight "double FormFactorEllipsoidalCylinder::getHeight() const
";

%feature("docstring")  FormFactorEllipsoidalCylinder::radialExtension "double FormFactorEllipsoidalCylinder::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::evaluate_for_q "complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorFullSphere.xml
%feature("docstring") FormFactorFullSphere "

A full sphere.

C++ includes: FormFactorFullSphere.h
";

%feature("docstring")  FormFactorFullSphere::FormFactorFullSphere "FormFactorFullSphere::FormFactorFullSphere(double radius, bool position_at_center=false)

Constructor of a full sphere.

Parameters:
-----------

radius: 
radius of the sphere in nanometers 
";

%feature("docstring")  FormFactorFullSphere::clone "FormFactorFullSphere* FormFactorFullSphere::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorFullSphere::accept "void FormFactorFullSphere::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorFullSphere::getRadius "double FormFactorFullSphere::getRadius() const
";

%feature("docstring")  FormFactorFullSphere::radialExtension "double FormFactorFullSphere::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorFullSphere::bottomZ "double FormFactorFullSphere::bottomZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorFullSphere::topZ "double FormFactorFullSphere::topZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorFullSphere::evaluate_for_q "complex_t FormFactorFullSphere::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorFullSpheroid.xml
%feature("docstring") FormFactorFullSpheroid "

A full spheroid (an ellipsoid with two equal axes, hence with circular cross section)

C++ includes: FormFactorFullSpheroid.h
";

%feature("docstring")  FormFactorFullSpheroid::FormFactorFullSpheroid "FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height)

Constructor of full spheroid.

Parameters:
-----------

radius: 
radius of the circular cross section in nanometers

height: 
height of the full spheroid in nanometers 
";

%feature("docstring")  FormFactorFullSpheroid::clone "FormFactorFullSpheroid* FormFactorFullSpheroid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorFullSpheroid::accept "void FormFactorFullSpheroid::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorFullSpheroid::getHeight "double FormFactorFullSpheroid::getHeight() const
";

%feature("docstring")  FormFactorFullSpheroid::getRadius "double FormFactorFullSpheroid::getRadius() const
";

%feature("docstring")  FormFactorFullSpheroid::radialExtension "double FormFactorFullSpheroid::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorFullSpheroid::evaluate_for_q "complex_t FormFactorFullSpheroid::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorGauss.xml
%feature("docstring") FormFactorGauss "

The form factor of a gaussian.

C++ includes: FormFactorGauss.h
";

%feature("docstring")  FormFactorGauss::FormFactorGauss "FormFactorGauss::FormFactorGauss(double length)
";

%feature("docstring")  FormFactorGauss::FormFactorGauss "FormFactorGauss::FormFactorGauss(double width, double height)
";

%feature("docstring")  FormFactorGauss::clone "FormFactorGauss* FormFactorGauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorGauss::accept "void FormFactorGauss::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorGauss::getWidth "double FormFactorGauss::getWidth() const
";

%feature("docstring")  FormFactorGauss::getHeight "double FormFactorGauss::getHeight() const
";

%feature("docstring")  FormFactorGauss::radialExtension "double FormFactorGauss::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorGauss::evaluate_for_q "complex_t FormFactorGauss::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorHemiEllipsoid.xml
%feature("docstring") FormFactorHemiEllipsoid "

An hemi ellipsoid, obtained by truncating a full ellipsoid in the middle plane spanned by two principal axes.

C++ includes: FormFactorHemiEllipsoid.h
";

%feature("docstring")  FormFactorHemiEllipsoid::FormFactorHemiEllipsoid "FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(double radius_x, double radius_y, double height)

Constructor of horizontally oriented ellipsoid, truncated at the central plane.

Parameters:
-----------

radius_x: 
radius of the ellipse base in the x-direction, in nanometers

radius_y: 
radius of the ellipse base in the y-direction, in nanometers

height: 
height of the hemi ellipsoid in nanometers 
";

%feature("docstring")  FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid "virtual FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid()
";

%feature("docstring")  FormFactorHemiEllipsoid::clone "FormFactorHemiEllipsoid* FormFactorHemiEllipsoid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorHemiEllipsoid::accept "void FormFactorHemiEllipsoid::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorHemiEllipsoid::getHeight "double FormFactorHemiEllipsoid::getHeight() const
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusX "double FormFactorHemiEllipsoid::getRadiusX() const
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusY "double FormFactorHemiEllipsoid::getRadiusY() const
";

%feature("docstring")  FormFactorHemiEllipsoid::radialExtension "double FormFactorHemiEllipsoid::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorHemiEllipsoid::evaluate_for_q "complex_t FormFactorHemiEllipsoid::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorIcosahedron.xml
%feature("docstring") FormFactorIcosahedron "

A regular icosahedron.

C++ includes: FormFactorIcosahedron.h
";

%feature("docstring")  FormFactorIcosahedron::FormFactorIcosahedron "FormFactorIcosahedron::FormFactorIcosahedron(double edge)

Constructor of a icosahedron.

Parameters:
-----------

edge: 
length of the edge in nanometers 
";

%feature("docstring")  FormFactorIcosahedron::clone "FormFactorIcosahedron* FormFactorIcosahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorIcosahedron::accept "void FormFactorIcosahedron::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorIcosahedron::getEdge "double FormFactorIcosahedron::getEdge() const
";


// File: classFormFactorLongBoxGauss.xml
%feature("docstring") FormFactorLongBoxGauss "

The form factor for a long rectangular box.

C++ includes: FormFactorLongBoxGauss.h
";

%feature("docstring")  FormFactorLongBoxGauss::FormFactorLongBoxGauss "FormFactorLongBoxGauss::FormFactorLongBoxGauss(double length, double width, double height)

Box constructor.

Parameters:
-----------

length: 
of  Box's base

width: 
of  Box's base

height: 
of  Box
";

%feature("docstring")  FormFactorLongBoxGauss::clone "FormFactorLongBoxGauss* FormFactorLongBoxGauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongBoxGauss::accept "void FormFactorLongBoxGauss::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorLongBoxGauss::getLength "double FormFactorLongBoxGauss::getLength() const
";

%feature("docstring")  FormFactorLongBoxGauss::getHeight "double FormFactorLongBoxGauss::getHeight() const
";

%feature("docstring")  FormFactorLongBoxGauss::getWidth "double FormFactorLongBoxGauss::getWidth() const
";

%feature("docstring")  FormFactorLongBoxGauss::radialExtension "double FormFactorLongBoxGauss::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongBoxGauss::evaluate_for_q "complex_t FormFactorLongBoxGauss::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorLongBoxLorentz.xml
%feature("docstring") FormFactorLongBoxLorentz "

The form factor for a long rectangular box.

C++ includes: FormFactorLongBoxLorentz.h
";

%feature("docstring")  FormFactorLongBoxLorentz::FormFactorLongBoxLorentz "FormFactorLongBoxLorentz::FormFactorLongBoxLorentz(double length, double width, double height)

Box constructor.

Parameters:
-----------

length: 
of  Box's base

width: 
of  Box's base

height: 
of  Box
";

%feature("docstring")  FormFactorLongBoxLorentz::clone "FormFactorLongBoxLorentz* FormFactorLongBoxLorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongBoxLorentz::accept "void FormFactorLongBoxLorentz::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorLongBoxLorentz::getLength "double FormFactorLongBoxLorentz::getLength() const
";

%feature("docstring")  FormFactorLongBoxLorentz::getHeight "double FormFactorLongBoxLorentz::getHeight() const
";

%feature("docstring")  FormFactorLongBoxLorentz::getWidth "double FormFactorLongBoxLorentz::getWidth() const
";

%feature("docstring")  FormFactorLongBoxLorentz::radialExtension "double FormFactorLongBoxLorentz::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongBoxLorentz::evaluate_for_q "complex_t FormFactorLongBoxLorentz::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorLorentz.xml
%feature("docstring") FormFactorLorentz "

The form factor of a lorentzian.

C++ includes: FormFactorLorentz.h
";

%feature("docstring")  FormFactorLorentz::FormFactorLorentz "FormFactorLorentz::FormFactorLorentz(double length)
";

%feature("docstring")  FormFactorLorentz::FormFactorLorentz "FormFactorLorentz::FormFactorLorentz(double width, double height)
";

%feature("docstring")  FormFactorLorentz::clone "FormFactorLorentz* FormFactorLorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLorentz::accept "void FormFactorLorentz::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorLorentz::getWidth "double FormFactorLorentz::getWidth() const
";

%feature("docstring")  FormFactorLorentz::getHeight "double FormFactorLorentz::getHeight() const
";

%feature("docstring")  FormFactorLorentz::radialExtension "double FormFactorLorentz::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLorentz::evaluate_for_q "complex_t FormFactorLorentz::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorOrnsteinZernike.xml
%feature("docstring") FormFactorOrnsteinZernike "

The form factor of a Ornstein-Zernike (see doi:10.1038/pj.2010.110).

C++ includes: FormFactorOrnsteinZernike.h
";

%feature("docstring")  FormFactorOrnsteinZernike::FormFactorOrnsteinZernike "FormFactorOrnsteinZernike::FormFactorOrnsteinZernike(double I0, double xi_xy, double xi_z)
";

%feature("docstring")  FormFactorOrnsteinZernike::clone "FormFactorOrnsteinZernike* FormFactorOrnsteinZernike::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorOrnsteinZernike::accept "void FormFactorOrnsteinZernike::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorOrnsteinZernike::radialExtension "double FormFactorOrnsteinZernike::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorOrnsteinZernike::evaluate_for_q "complex_t FormFactorOrnsteinZernike::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorPolygonalPrism.xml
%feature("docstring") FormFactorPolygonalPrism "

A prism with a polygonal base, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolygonalPrism::FormFactorPolygonalPrism "FormFactorPolygonalPrism::FormFactorPolygonalPrism(double height)
";

%feature("docstring")  FormFactorPolygonalPrism::evaluate_for_q "complex_t FormFactorPolygonalPrism::evaluate_for_q(cvector_t q) const override final

Returns the form factor F(q) of this polyhedron, respecting the offset height/2. 
";

%feature("docstring")  FormFactorPolygonalPrism::volume "double FormFactorPolygonalPrism::volume() const override final

Returns the volume of this prism. 
";

%feature("docstring")  FormFactorPolygonalPrism::getHeight "double FormFactorPolygonalPrism::getHeight() const
";

%feature("docstring")  FormFactorPolygonalPrism::radialExtension "double FormFactorPolygonalPrism::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";


// File: classFormFactorPolygonalSurface.xml
%feature("docstring") FormFactorPolygonalSurface "

A polygonal surface, for testing form factor computations.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolygonalSurface::FormFactorPolygonalSurface "FormFactorPolygonalSurface::FormFactorPolygonalSurface()
";

%feature("docstring")  FormFactorPolygonalSurface::evaluate_for_q "complex_t FormFactorPolygonalSurface::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";

%feature("docstring")  FormFactorPolygonalSurface::volume "double FormFactorPolygonalSurface::volume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorPolygonalSurface::radialExtension "double FormFactorPolygonalSurface::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";


// File: classFormFactorPolyhedron.xml
%feature("docstring") FormFactorPolyhedron "

A polyhedron, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolyhedron::FormFactorPolyhedron "FormFactorPolyhedron::FormFactorPolyhedron()
";

%feature("docstring")  FormFactorPolyhedron::evaluate_for_q "complex_t FormFactorPolyhedron::evaluate_for_q(cvector_t q) const override final

Returns the form factor F(q) of this polyhedron, respecting the offset z_origin. 
";

%feature("docstring")  FormFactorPolyhedron::evaluate_centered "complex_t FormFactorPolyhedron::evaluate_centered(cvector_t q) const

Returns the form factor F(q) of this polyhedron, with origin at z=0. 
";

%feature("docstring")  FormFactorPolyhedron::volume "double FormFactorPolyhedron::volume() const override final

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorPolyhedron::radialExtension "double FormFactorPolyhedron::radialExtension() const override final

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

%feature("docstring")  FormFactorPrism3::FormFactorPrism3 "FormFactorPrism3::FormFactorPrism3(double base_edge, double height)

Constructor of a prism with an equilaterial triangle base.

Parameters:
-----------

base_edge: 
length of the base edge in nanometers

height: 
height in nanometers 
";

%feature("docstring")  FormFactorPrism3::clone "FormFactorPrism3* FormFactorPrism3::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPrism3::accept "void FormFactorPrism3::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorPrism3::getBaseEdge "double FormFactorPrism3::getBaseEdge() const
";


// File: classFormFactorPrism6.xml
%feature("docstring") FormFactorPrism6 "

A prism based on a regular hexagonal.

C++ includes: FormFactorPrism6.h
";

%feature("docstring")  FormFactorPrism6::FormFactorPrism6 "FormFactorPrism6::FormFactorPrism6(double base_edge, double height)

Constructor of a prism with a regular hexagonal base.

Parameters:
-----------

base_edge: 
length of the hexagonal base in nanometers

height: 
height in nanometers 
";

%feature("docstring")  FormFactorPrism6::clone "FormFactorPrism6* FormFactorPrism6::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPrism6::accept "void FormFactorPrism6::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorPrism6::getBaseEdge "double FormFactorPrism6::getBaseEdge() const
";


// File: classFormFactorPyramid.xml
%feature("docstring") FormFactorPyramid "

A frustum with a quadratic base.

C++ includes: FormFactorPyramid.h
";

%feature("docstring")  FormFactorPyramid::FormFactorPyramid "FormFactorPyramid::FormFactorPyramid(double base_edge, double height, double alpha)

Constructor of a truncated pyramid with a square base

Parameters:
-----------

base_edge: 
length of the square base in nanometers

height: 
height of the pyramid in nanometers

alpha: 
dihedral angle between the base and a side face in radians 
";

%feature("docstring")  FormFactorPyramid::clone "FormFactorPyramid* FormFactorPyramid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPyramid::accept "void FormFactorPyramid::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorPyramid::getHeight "double FormFactorPyramid::getHeight() const
";

%feature("docstring")  FormFactorPyramid::getBaseEdge "double FormFactorPyramid::getBaseEdge() const
";

%feature("docstring")  FormFactorPyramid::getAlpha "double FormFactorPyramid::getAlpha() const
";


// File: classFormFactorRipple1Box.xml
%feature("docstring") FormFactorRipple1Box "

The form factor for a cosine ripple, with box profile in elongation direction.

C++ includes: FormFactorRipple1.h
";

%feature("docstring")  FormFactorRipple1Box::FormFactorRipple1Box "FormFactorRipple1Box::FormFactorRipple1Box(double length, double width, double height)
";

%feature("docstring")  FormFactorRipple1Box::clone "FormFactorRipple1Box * FormFactorRipple1Box::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple1Box::accept "void FormFactorRipple1Box::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classFormFactorRipple1Gauss.xml
%feature("docstring") FormFactorRipple1Gauss "

The form factor for a cosine ripple, with Gaussian profile in elongation direction.

C++ includes: FormFactorRipple1.h
";

%feature("docstring")  FormFactorRipple1Gauss::FormFactorRipple1Gauss "FormFactorRipple1Gauss::FormFactorRipple1Gauss(double length, double width, double height)
";

%feature("docstring")  FormFactorRipple1Gauss::clone "FormFactorRipple1Gauss * FormFactorRipple1Gauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple1Gauss::accept "void FormFactorRipple1Gauss::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classFormFactorRipple1Lorentz.xml
%feature("docstring") FormFactorRipple1Lorentz "

The form factor for a cosine ripple, with Lorentz form factor in elongation direction.

C++ includes: FormFactorRipple1.h
";

%feature("docstring")  FormFactorRipple1Lorentz::FormFactorRipple1Lorentz "FormFactorRipple1Lorentz::FormFactorRipple1Lorentz(double length, double width, double height)
";

%feature("docstring")  FormFactorRipple1Lorentz::clone "FormFactorRipple1Lorentz * FormFactorRipple1Lorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple1Lorentz::accept "void FormFactorRipple1Lorentz::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classFormFactorRipple2Box.xml
%feature("docstring") FormFactorRipple2Box "

The form factor for a cosine ripple, with box profile in elongation direction.

C++ includes: FormFactorRipple2.h
";

%feature("docstring")  FormFactorRipple2Box::FormFactorRipple2Box "FormFactorRipple2Box::FormFactorRipple2Box(double length, double width, double height, double asymmetry)
";

%feature("docstring")  FormFactorRipple2Box::clone "FormFactorRipple2Box * FormFactorRipple2Box::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple2Box::accept "void FormFactorRipple2Box::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classFormFactorRipple2Gauss.xml
%feature("docstring") FormFactorRipple2Gauss "

The form factor for a cosine ripple, with Gaussian profile in elongation direction.

C++ includes: FormFactorRipple2.h
";

%feature("docstring")  FormFactorRipple2Gauss::FormFactorRipple2Gauss "FormFactorRipple2Gauss::FormFactorRipple2Gauss(double length, double width, double height, double asymmetry)
";

%feature("docstring")  FormFactorRipple2Gauss::clone "FormFactorRipple2Gauss * FormFactorRipple2Gauss::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple2Gauss::accept "void FormFactorRipple2Gauss::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classFormFactorRipple2Lorentz.xml
%feature("docstring") FormFactorRipple2Lorentz "

The form factor for a cosine ripple, with Lorentz form factor in elongation direction.

C++ includes: FormFactorRipple2.h
";

%feature("docstring")  FormFactorRipple2Lorentz::FormFactorRipple2Lorentz "FormFactorRipple2Lorentz::FormFactorRipple2Lorentz(double length, double width, double height, double asymmetry)
";

%feature("docstring")  FormFactorRipple2Lorentz::clone "FormFactorRipple2Lorentz * FormFactorRipple2Lorentz::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple2Lorentz::accept "void FormFactorRipple2Lorentz::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  FormFactorSphereGaussianRadius::accept "void FormFactorSphereGaussianRadius::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereGaussianRadius::radialExtension "double FormFactorSphereGaussianRadius::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereGaussianRadius::evaluate_for_q "complex_t FormFactorSphereGaussianRadius::evaluate_for_q(cvector_t q) const override final

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

%feature("docstring")  FormFactorSphereLogNormalRadius::accept "void FormFactorSphereLogNormalRadius::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::radialExtension "double FormFactorSphereLogNormalRadius::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::evaluate_for_q "complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(cvector_t q) const override final

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

%feature("docstring")  FormFactorSphereUniformRadius::accept "void FormFactorSphereUniformRadius::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereUniformRadius::radialExtension "double FormFactorSphereUniformRadius::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereUniformRadius::evaluate_for_q "complex_t FormFactorSphereUniformRadius::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorTetrahedron.xml
%feature("docstring") FormFactorTetrahedron "

A frustum with equilateral trigonal base.

C++ includes: FormFactorTetrahedron.h
";

%feature("docstring")  FormFactorTetrahedron::FormFactorTetrahedron "FormFactorTetrahedron::FormFactorTetrahedron(double base_edge, double height, double alpha)

Constructor of a truncated tethrahedron.

Parameters:
-----------

base_edge: 
length of one edge of the equilateral triangular base in nanometers

height: 
height of the tetrahedron in nanometers

alpha: 
dihedral angle in radians between base and facet 
";

%feature("docstring")  FormFactorTetrahedron::clone "FormFactorTetrahedron* FormFactorTetrahedron::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTetrahedron::accept "void FormFactorTetrahedron::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  FormFactorTriangle::accept "void FormFactorTriangle::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorTriangle::getBaseEdge "double FormFactorTriangle::getBaseEdge() const
";


// File: classFormFactorTruncatedCube.xml
%feature("docstring") FormFactorTruncatedCube "

A cube, with tetrahedral truncation of all corners

C++ includes: FormFactorTruncatedCube.h
";

%feature("docstring")  FormFactorTruncatedCube::FormFactorTruncatedCube "FormFactorTruncatedCube::FormFactorTruncatedCube(double length, double removed_length)

Constructor of a truncated cube.

Parameters:
-----------

length: 
length of the full cube's edge in nanometers

removed_length: 
removed length from each edge of the cube in nanometers 
";

%feature("docstring")  FormFactorTruncatedCube::clone "FormFactorTruncatedCube* FormFactorTruncatedCube::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedCube::accept "void FormFactorTruncatedCube::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  FormFactorTruncatedSphere::FormFactorTruncatedSphere "FormFactorTruncatedSphere::FormFactorTruncatedSphere(double radius, double height, double dh=0.0)

Constructor of a spherical dome.

Parameters:
-----------

radius: 
radius of the truncated sphere in nanometers

height: 
height of the truncated sphere in nanometers

dh: 
length of cup truncated from the top 
";

%feature("docstring")  FormFactorTruncatedSphere::clone "FormFactorTruncatedSphere* FormFactorTruncatedSphere::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedSphere::accept "void FormFactorTruncatedSphere::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedSphere::getHeight "double FormFactorTruncatedSphere::getHeight() const
";

%feature("docstring")  FormFactorTruncatedSphere::getRadius "double FormFactorTruncatedSphere::getRadius() const
";

%feature("docstring")  FormFactorTruncatedSphere::getRemovedTop "double FormFactorTruncatedSphere::getRemovedTop() const
";

%feature("docstring")  FormFactorTruncatedSphere::radialExtension "double FormFactorTruncatedSphere::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSphere::evaluate_for_q "complex_t FormFactorTruncatedSphere::evaluate_for_q(cvector_t q) const override final

Complex form factor. 
";


// File: classFormFactorTruncatedSpheroid.xml
%feature("docstring") FormFactorTruncatedSpheroid "

A truncated spheroid. An ellipsoid with two equal axis, truncated by a plane perpendicular to the third axis.

C++ includes: FormFactorTruncatedSpheroid.h
";

%feature("docstring")  FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid "FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(double radius, double height, double height_flattening, double dh=0.0)

Constructor of a spheroidal dome.

Parameters:
-----------

radius: 
radius of the truncated spheroid in nanometers

height: 
height of the truncated spheroid in nanometers

height_flattening: 
ratio of the height of the corresponding full spheroid to its diameter

dh: 
length of cup truncated from the top 
";

%feature("docstring")  FormFactorTruncatedSpheroid::clone "FormFactorTruncatedSpheroid* FormFactorTruncatedSpheroid::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedSpheroid::accept "void FormFactorTruncatedSpheroid::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedSpheroid::getRadius "double FormFactorTruncatedSpheroid::getRadius() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeight "double FormFactorTruncatedSpheroid::getHeight() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeightFlattening "double FormFactorTruncatedSpheroid::getHeightFlattening() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::getRemovedTop "double FormFactorTruncatedSpheroid::getRemovedTop() const
";

%feature("docstring")  FormFactorTruncatedSpheroid::radialExtension "double FormFactorTruncatedSpheroid::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSpheroid::evaluate_for_q "complex_t FormFactorTruncatedSpheroid::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classFormFactorWeighted.xml
%feature("docstring") FormFactorWeighted "

Coherent sum of different scalar  IFormFactor's with different weights.

Used by  ParticleComposition. If same particles are at different positions, then consider FormFactorDecoratorMultiPositionFactor (restore from commit 0500a26de76).

C++ includes: FormFactorWeighted.h
";

%feature("docstring")  FormFactorWeighted::FormFactorWeighted "FormFactorWeighted::FormFactorWeighted()
";

%feature("docstring")  FormFactorWeighted::~FormFactorWeighted "FormFactorWeighted::~FormFactorWeighted() override final
";

%feature("docstring")  FormFactorWeighted::clone "FormFactorWeighted * FormFactorWeighted::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorWeighted::accept "void FormFactorWeighted::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FormFactorWeighted::radialExtension "double FormFactorWeighted::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorWeighted::bottomZ "double FormFactorWeighted::bottomZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorWeighted::topZ "double FormFactorWeighted::topZ(const IRotation &rotation) const override final

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  FormFactorWeighted::addFormFactor "void FormFactorWeighted::addFormFactor(const IFormFactor &form_factor, double weight=1.0)
";

%feature("docstring")  FormFactorWeighted::setAmbientMaterial "void FormFactorWeighted::setAmbientMaterial(Material material) override final

Passes the material in which this particle is embedded. 
";

%feature("docstring")  FormFactorWeighted::evaluate "complex_t FormFactorWeighted::evaluate(const WavevectorInfo &wavevectors) const override final

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  FormFactorWeighted::evaluatePol "Eigen::Matrix2cd FormFactorWeighted::evaluatePol(const WavevectorInfo &wavevectors) const override final

Calculates and returns a polarized form factor calculation in DWBA. 
";


// File: classFourierTransform.xml
%feature("docstring") FourierTransform "

Fourier transform of vectors (in 1D or 2D) using Fast Fourier Transform (fftw package).

Usage: std::vector<double> signal, result;  FourierTransform ft; ft.fft(signal, result)

Given code rely on code from Jeremy Fix page, http://jeremy.fix.free.fr/spip.php?article15, see also \"Efficient convolution using the Fast Fourier Transform, Application in C++\" by Jeremy Fix, May 30, 2011

C++ includes: FourierTransform.h
";

%feature("docstring")  FourierTransform::FourierTransform "FourierTransform::FourierTransform()
";

%feature("docstring")  FourierTransform::fft "void FourierTransform::fft(const double1d_t &source, double1d_t &result)

FT in 1D. 
";

%feature("docstring")  FourierTransform::fftshift "void FourierTransform::fftshift(double1d_t &result)

Shift low frequency to the center of 1D FT array. 
";

%feature("docstring")  FourierTransform::fft "void FourierTransform::fft(const double2d_t &source, double2d_t &result)

FT in 2D. 
";

%feature("docstring")  FourierTransform::fftshift "void FourierTransform::fftshift(double2d_t &result)

Shift low frequency to the center of 2D FT array. 
";

%feature("docstring")  FourierTransform::init "void FourierTransform::init(int h_src, int w_src)

prepare arrays for 2D Fourier Transformation (FT) of the given vector 
";


// File: classFTDecayFunction1DCauchy.xml
%feature("docstring") FTDecayFunction1DCauchy "

One-dimensional Cauchy decay function in reciprocal space; corresponds to exp(-|x|/decay_length) in real space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DCauchy::FTDecayFunction1DCauchy "FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double decay_length)
";

%feature("docstring")  FTDecayFunction1DCauchy::clone "FTDecayFunction1DCauchy * FTDecayFunction1DCauchy::clone() const
";

%feature("docstring")  FTDecayFunction1DCauchy::accept "void FTDecayFunction1DCauchy::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDecayFunction1DCauchy::evaluate "double FTDecayFunction1DCauchy::evaluate(double q) const final
";


// File: classFTDecayFunction1DGauss.xml
%feature("docstring") FTDecayFunction1DGauss "

One-dimensional Gauss decay function in reciprocal space; corresponds to exp[-x^2/(2*decay_length^2)] in real space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DGauss::FTDecayFunction1DGauss "FTDecayFunction1DGauss::FTDecayFunction1DGauss(double decay_length)
";

%feature("docstring")  FTDecayFunction1DGauss::clone "FTDecayFunction1DGauss * FTDecayFunction1DGauss::clone() const
";

%feature("docstring")  FTDecayFunction1DGauss::accept "void FTDecayFunction1DGauss::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDecayFunction1DGauss::evaluate "double FTDecayFunction1DGauss::evaluate(double q) const final
";


// File: classFTDecayFunction1DTriangle.xml
%feature("docstring") FTDecayFunction1DTriangle "

One-dimensional triangle decay function in reciprocal space; corresponds to 1-|x|/decay_length if |x|<decay_length (and 0 otherwise) in real space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DTriangle::FTDecayFunction1DTriangle "FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double decay_length)
";

%feature("docstring")  FTDecayFunction1DTriangle::clone "FTDecayFunction1DTriangle * FTDecayFunction1DTriangle::clone() const
";

%feature("docstring")  FTDecayFunction1DTriangle::accept "void FTDecayFunction1DTriangle::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDecayFunction1DTriangle::evaluate "double FTDecayFunction1DTriangle::evaluate(double q) const final
";


// File: classFTDecayFunction1DVoigt.xml
%feature("docstring") FTDecayFunction1DVoigt "

One-dimensional pseudo-Voigt decay function in reciprocal space; corresponds to eta*Gauss + (1-eta)*Cauchy.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DVoigt::FTDecayFunction1DVoigt "FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double decay_length, double eta)

Constructor of pseudo-Voigt decay function.

Parameters:
-----------

decay_length: 
half-width of the distribution in nanometers

eta: 
parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0) 
";

%feature("docstring")  FTDecayFunction1DVoigt::clone "FTDecayFunction1DVoigt * FTDecayFunction1DVoigt::clone() const
";

%feature("docstring")  FTDecayFunction1DVoigt::accept "void FTDecayFunction1DVoigt::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDecayFunction1DVoigt::evaluate "double FTDecayFunction1DVoigt::evaluate(double q) const final
";

%feature("docstring")  FTDecayFunction1DVoigt::eEta "double FTDecayFunction1DVoigt::eEta() const
";


// File: classFTDecayFunction2DCauchy.xml
%feature("docstring") FTDecayFunction2DCauchy "

Two-dimensional Cauchy decay function in reciprocal space; corresponds to exp(-r) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DCauchy::FTDecayFunction2DCauchy "FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y, double gamma=0)
";

%feature("docstring")  FTDecayFunction2DCauchy::clone "FTDecayFunction2DCauchy * FTDecayFunction2DCauchy::clone() const
";

%feature("docstring")  FTDecayFunction2DCauchy::accept "void FTDecayFunction2DCauchy::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDecayFunction2DCauchy::evaluate "double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DGauss.xml
%feature("docstring") FTDecayFunction2DGauss "

Two-dimensional Gauss decay function in reciprocal space; corresponds to exp(-r^2/2) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DGauss::FTDecayFunction2DGauss "FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y, double gamma=0)
";

%feature("docstring")  FTDecayFunction2DGauss::clone "FTDecayFunction2DGauss * FTDecayFunction2DGauss::clone() const
";

%feature("docstring")  FTDecayFunction2DGauss::accept "void FTDecayFunction2DGauss::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDecayFunction2DGauss::evaluate "double FTDecayFunction2DGauss::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DVoigt.xml
%feature("docstring") FTDecayFunction2DVoigt "

Two-dimensional pseudo-Voigt decay function in reciprocal space; corresponds to eta*Gauss + (1-eta)*Cauchy.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DVoigt::FTDecayFunction2DVoigt "FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y, double eta, double gamma=0)

Constructor of two-dimensional pseudo-Voigt decay function in reciprocal space.

Parameters:
-----------

decay_length_x: 
the decay length in nanometers along x-axis of the distribution

decay_length_y: 
the decay length in nanometers along y-axis of the distribution

eta: 
parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)

gamma: 
distribution orientation with respect to the first lattice vector in radians 
";

%feature("docstring")  FTDecayFunction2DVoigt::clone "FTDecayFunction2DVoigt * FTDecayFunction2DVoigt::clone() const
";

%feature("docstring")  FTDecayFunction2DVoigt::accept "void FTDecayFunction2DVoigt::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDecayFunction2DVoigt::evaluate "double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const final

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  FTDecayFunction2DVoigt::eta "double FTDecayFunction2DVoigt::eta() const
";


// File: classFTDistribution1DCauchy.xml
%feature("docstring") FTDistribution1DCauchy "

Exponential  IFTDistribution1D exp(-|omega*x|); its Fourier transform evaluate(q) is a Cauchy-Lorentzian starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DCauchy::FTDistribution1DCauchy "FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
";

%feature("docstring")  FTDistribution1DCauchy::clone "FTDistribution1DCauchy * FTDistribution1DCauchy::clone() const override final
";

%feature("docstring")  FTDistribution1DCauchy::accept "void FTDistribution1DCauchy::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution1DCauchy::evaluate "double FTDistribution1DCauchy::evaluate(double q) const override final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DCauchy::qSecondDerivative "double FTDistribution1DCauchy::qSecondDerivative() const override final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DCauchy::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DCauchy::createSampler() const override final
";


// File: classFTDistribution1DCosine.xml
%feature("docstring") FTDistribution1DCosine "

IFTDistribution1D consisting of one cosine wave [1+cos(pi*x/omega) if |x|<omega, and 0 otherwise]; its Fourier transform evaluate(q) starts at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DCosine::FTDistribution1DCosine "FTDistribution1DCosine::FTDistribution1DCosine(double omega)
";

%feature("docstring")  FTDistribution1DCosine::clone "FTDistribution1DCosine * FTDistribution1DCosine::clone() const override final
";

%feature("docstring")  FTDistribution1DCosine::accept "void FTDistribution1DCosine::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution1DCosine::evaluate "double FTDistribution1DCosine::evaluate(double q) const override final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DCosine::qSecondDerivative "double FTDistribution1DCosine::qSecondDerivative() const override final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DCosine::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DCosine::createSampler() const override final
";


// File: classFTDistribution1DGate.xml
%feature("docstring") FTDistribution1DGate "

Square gate  IFTDistribution1D; its Fourier transform evaluate(q) is a sinc function starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DGate::FTDistribution1DGate "FTDistribution1DGate::FTDistribution1DGate(double omega)
";

%feature("docstring")  FTDistribution1DGate::clone "FTDistribution1DGate * FTDistribution1DGate::clone() const override final
";

%feature("docstring")  FTDistribution1DGate::accept "void FTDistribution1DGate::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution1DGate::evaluate "double FTDistribution1DGate::evaluate(double q) const override final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DGate::qSecondDerivative "double FTDistribution1DGate::qSecondDerivative() const override final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DGate::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DGate::createSampler() const override final
";


// File: classFTDistribution1DGauss.xml
%feature("docstring") FTDistribution1DGauss "

Gaussian  IFTDistribution1D; its Fourier transform evaluate(q) is a Gaussian starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DGauss::FTDistribution1DGauss "FTDistribution1DGauss::FTDistribution1DGauss(double omega)
";

%feature("docstring")  FTDistribution1DGauss::clone "FTDistribution1DGauss * FTDistribution1DGauss::clone() const override final
";

%feature("docstring")  FTDistribution1DGauss::accept "void FTDistribution1DGauss::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution1DGauss::evaluate "double FTDistribution1DGauss::evaluate(double q) const override final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DGauss::qSecondDerivative "double FTDistribution1DGauss::qSecondDerivative() const override final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DGauss::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DGauss::createSampler() const override final
";


// File: classFTDistribution1DTriangle.xml
%feature("docstring") FTDistribution1DTriangle "

Triangle IFTDistribution1D [1-|x|/omega if |x|<omega, and 0 otherwise]; its Fourier transform evaluate(q) is a squared sinc function starting at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DTriangle::FTDistribution1DTriangle "FTDistribution1DTriangle::FTDistribution1DTriangle(double omega)
";

%feature("docstring")  FTDistribution1DTriangle::clone "FTDistribution1DTriangle * FTDistribution1DTriangle::clone() const override final
";

%feature("docstring")  FTDistribution1DTriangle::accept "void FTDistribution1DTriangle::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution1DTriangle::evaluate "double FTDistribution1DTriangle::evaluate(double q) const override final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DTriangle::qSecondDerivative "double FTDistribution1DTriangle::qSecondDerivative() const override final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DTriangle::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DTriangle::createSampler() const override final
";


// File: classFTDistribution1DVoigt.xml
%feature("docstring") FTDistribution1DVoigt "

IFTDistribution1D that provides a Fourier transform evaluate(q) in form of a pseudo-Voigt decay function eta*Gauss + (1-eta)*Cauchy, with both components starting at 1 for q=0.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  FTDistribution1DVoigt::FTDistribution1DVoigt "FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)

Constructor of one-dimensional pseudo-Voigt probability distribution.

Parameters:
-----------

omega: 
half-width of the distribution in nanometers

eta: 
parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0) 
";

%feature("docstring")  FTDistribution1DVoigt::clone "FTDistribution1DVoigt * FTDistribution1DVoigt::clone() const override final
";

%feature("docstring")  FTDistribution1DVoigt::accept "void FTDistribution1DVoigt::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution1DVoigt::evaluate "double FTDistribution1DVoigt::evaluate(double q) const override final

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  FTDistribution1DVoigt::eta "double FTDistribution1DVoigt::eta() const
";

%feature("docstring")  FTDistribution1DVoigt::qSecondDerivative "double FTDistribution1DVoigt::qSecondDerivative() const override final

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  FTDistribution1DVoigt::createSampler "std::unique_ptr< IDistribution1DSampler > FTDistribution1DVoigt::createSampler() const override final
";


// File: classFTDistribution2DCauchy.xml
%feature("docstring") FTDistribution2DCauchy "

Two-dimensional Cauchy distribution in Fourier space; corresponds to a normalized exp(-r) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DCauchy::FTDistribution2DCauchy "FTDistribution2DCauchy::FTDistribution2DCauchy(double omega_x, double omega_y, double gamma=0)
";

%feature("docstring")  FTDistribution2DCauchy::clone "FTDistribution2DCauchy * FTDistribution2DCauchy::clone() const final
";

%feature("docstring")  FTDistribution2DCauchy::accept "void FTDistribution2DCauchy::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution2DCauchy::evaluate "double FTDistribution2DCauchy::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DCauchy::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DCauchy::createSampler() const final
";


// File: classFTDistribution2DComponents.xml
%feature("docstring") FTDistribution2DComponents "

Predefined Fourier transformed distributions for functional tests.

C++ includes: SampleComponents.h
";

%feature("docstring")  FTDistribution2DComponents::FTDistribution2DComponents "FTDistribution2DComponents::FTDistribution2DComponents()
";


// File: classFTDistribution2DCone.xml
%feature("docstring") FTDistribution2DCone "

Two-dimensional cone distribution in Fourier space; corresponds to 1-r if r<1 (and 0 otherwise) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DCone::FTDistribution2DCone "FTDistribution2DCone::FTDistribution2DCone(double omega_x, double omega_y, double gamma=0)
";

%feature("docstring")  FTDistribution2DCone::clone "FTDistribution2DCone * FTDistribution2DCone::clone() const final
";

%feature("docstring")  FTDistribution2DCone::accept "void FTDistribution2DCone::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution2DCone::evaluate "double FTDistribution2DCone::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DCone::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DCone::createSampler() const final
";


// File: classFTDistribution2DGate.xml
%feature("docstring") FTDistribution2DGate "

Two-dimensional gate distribution in Fourier space; corresponds to normalized constant if r<1 (and 0 otherwise) in real space, with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DGate::FTDistribution2DGate "FTDistribution2DGate::FTDistribution2DGate(double omega_x, double omega_y, double gamma=0)
";

%feature("docstring")  FTDistribution2DGate::clone "FTDistribution2DGate * FTDistribution2DGate::clone() const final
";

%feature("docstring")  FTDistribution2DGate::accept "void FTDistribution2DGate::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution2DGate::evaluate "double FTDistribution2DGate::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DGate::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DGate::createSampler() const final
";


// File: classFTDistribution2DGauss.xml
%feature("docstring") FTDistribution2DGauss "

Two-dimensional Gauss distribution in Fourier space; corresponds to normalized exp(-r^2/2) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DGauss::FTDistribution2DGauss "FTDistribution2DGauss::FTDistribution2DGauss(double omega_x, double omega_y, double gamma=0)
";

%feature("docstring")  FTDistribution2DGauss::clone "FTDistribution2DGauss * FTDistribution2DGauss::clone() const final
";

%feature("docstring")  FTDistribution2DGauss::accept "void FTDistribution2DGauss::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution2DGauss::evaluate "double FTDistribution2DGauss::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DGauss::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DGauss::createSampler() const final
";


// File: classFTDistribution2DVoigt.xml
%feature("docstring") FTDistribution2DVoigt "

Two-dimensional Voigt distribution in Fourier space; corresponds to eta*Gauss + (1-eta)*Cauchy

C++ includes: FTDistributions2D.h
";

%feature("docstring")  FTDistribution2DVoigt::FTDistribution2DVoigt "FTDistribution2DVoigt::FTDistribution2DVoigt(double omega_x, double omega_y, double eta, double gamma=0)

Constructor of two-dimensional pseudo-Voigt probability distribution.

Parameters:
-----------

omega_x: 
half-width of the distribution along its x-axis in nanometers

omega_y: 
half-width of the distribution along its y-axis in nanometers

eta: 
parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)

gamma: 
angle in direct space between first lattice vector and x-axis of the distribution in radians 
";

%feature("docstring")  FTDistribution2DVoigt::clone "FTDistribution2DVoigt * FTDistribution2DVoigt::clone() const final
";

%feature("docstring")  FTDistribution2DVoigt::accept "void FTDistribution2DVoigt::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  FTDistribution2DVoigt::evaluate "double FTDistribution2DVoigt::evaluate(double qx, double qy) const final

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DVoigt::eta "double FTDistribution2DVoigt::eta() const
";

%feature("docstring")  FTDistribution2DVoigt::createSampler "std::unique_ptr< IDistribution2DSampler > FTDistribution2DVoigt::createSampler() const final
";


// File: classGaussFisherPeakShape.xml
%feature("docstring") GaussFisherPeakShape "

Class that implements a peak shape that is Gaussian in the radial direction and uses the von Mises-Fisher distribution in the angular direction.

C++ includes: IPeakShape.h
";

%feature("docstring")  GaussFisherPeakShape::GaussFisherPeakShape "GaussFisherPeakShape::GaussFisherPeakShape(double max_intensity, double radial_size, double kappa)
";

%feature("docstring")  GaussFisherPeakShape::~GaussFisherPeakShape "GaussFisherPeakShape::~GaussFisherPeakShape() override
";

%feature("docstring")  GaussFisherPeakShape::clone "GaussFisherPeakShape * GaussFisherPeakShape::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  GaussFisherPeakShape::accept "void GaussFisherPeakShape::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  GaussFisherPeakShape::evaluate "double GaussFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  GaussFisherPeakShape::angularDisorder "bool GaussFisherPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
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

%feature("docstring")  GISASSimulation::~GISASSimulation "GISASSimulation::~GISASSimulation()
";

%feature("docstring")  GISASSimulation::clone "GISASSimulation* GISASSimulation::clone() const override
";

%feature("docstring")  GISASSimulation::accept "void GISASSimulation::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  GISASSimulation::prepareSimulation "void GISASSimulation::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  GISASSimulation::result "SimulationResult GISASSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  GISASSimulation::setBeamParameters "void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets beam parameters from here (forwarded to  Instrument) 
";

%feature("docstring")  GISASSimulation::intensityMapSize "size_t GISASSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";


// File: classGISASSpecularComputation.xml
%feature("docstring") GISASSpecularComputation "

Computes the specular signal in the bin where q_parallel = 0. Used by  DWBAComputation.

C++ includes: GISASSpecularComputation.h
";

%feature("docstring")  GISASSpecularComputation::GISASSpecularComputation "GISASSpecularComputation::GISASSpecularComputation(const IFresnelMap *p_fresnel_map)
";

%feature("docstring")  GISASSpecularComputation::compute "void GISASSpecularComputation::compute(SimulationElement &elem) const
";


// File: classHardDiskBuilder.xml
%feature("docstring") HardDiskBuilder "

Builds sample: cylinders with hard disk Percus-Yevick interference.

C++ includes: PercusYevickBuilder.h
";

%feature("docstring")  HardDiskBuilder::HardDiskBuilder "HardDiskBuilder::HardDiskBuilder()
";

%feature("docstring")  HardDiskBuilder::buildSample "MultiLayer * HardDiskBuilder::buildSample() const
";


// File: classScalarFresnelMap_1_1Hash2Doubles.xml


// File: classMatrixFresnelMap_1_1HashKVector.xml


// File: classHexagonalLattice.xml
%feature("docstring") HexagonalLattice "";

%feature("docstring")  HexagonalLattice::HexagonalLattice "HexagonalLattice::HexagonalLattice(double length, double rotation_angle=0.0)
";

%feature("docstring")  HexagonalLattice::clone "HexagonalLattice * HexagonalLattice::clone() const
";

%feature("docstring")  HexagonalLattice::accept "void HexagonalLattice::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  HexagonalLattice::length1 "virtual double HexagonalLattice::length1() const
";

%feature("docstring")  HexagonalLattice::length2 "virtual double HexagonalLattice::length2() const
";

%feature("docstring")  HexagonalLattice::latticeAngle "double HexagonalLattice::latticeAngle() const
";

%feature("docstring")  HexagonalLattice::unitCellArea "double HexagonalLattice::unitCellArea() const
";


// File: classHexParaCrystalBuilder.xml
%feature("docstring") HexParaCrystalBuilder "

Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  HexParaCrystalBuilder::HexParaCrystalBuilder "HexParaCrystalBuilder::HexParaCrystalBuilder()
";

%feature("docstring")  HexParaCrystalBuilder::buildSample "MultiLayer * HexParaCrystalBuilder::buildSample() const
";


// File: classHistogram1D.xml
%feature("docstring") Histogram1D "

One dimensional histogram.

C++ includes: Histogram1D.h
";

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

%feature("docstring")  Histogram1D::getBinCentersNumpy "PyObject * Histogram1D::getBinCentersNumpy() const
";

%feature("docstring")  Histogram1D::getBinValuesNumpy "PyObject * Histogram1D::getBinValuesNumpy() const
";

%feature("docstring")  Histogram1D::getBinErrorsNumpy "PyObject * Histogram1D::getBinErrorsNumpy() const
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

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(std::vector< std::vector< double >> data)

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


// File: classHomogeneousMultilayerBuilder.xml
%feature("docstring") HomogeneousMultilayerBuilder "

Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate. Ti is 70 angstroms thick, Ni is 30 angstroms thick. No absorption, no roughness, target wavelength is 1.54 angstroms.

C++ includes: HomogeneousMultilayerBuilder.h
";

%feature("docstring")  HomogeneousMultilayerBuilder::HomogeneousMultilayerBuilder "HomogeneousMultilayerBuilder::HomogeneousMultilayerBuilder()
";

%feature("docstring")  HomogeneousMultilayerBuilder::buildSample "MultiLayer * HomogeneousMultilayerBuilder::buildSample() const
";


// File: structHomogeneousRegion.xml
%feature("docstring") HomogeneousRegion "

Struct that contains information on a single homogeneous region of a particle inside a single layer. This information is needed for calculating the average of a material, used in the Fresnel calculations.

C++ includes: HomogeneousRegion.h
";


// File: classHorizontalLine.xml
%feature("docstring") HorizontalLine "

An infinite horizontal line.

C++ includes: Line.h
";

%feature("docstring")  HorizontalLine::HorizontalLine "HorizontalLine::HorizontalLine(double y)

Parameters:
-----------

y: 
The value at which it crosses y-axes 
";

%feature("docstring")  HorizontalLine::clone "HorizontalLine* HorizontalLine::clone() const
";

%feature("docstring")  HorizontalLine::contains "bool HorizontalLine::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  HorizontalLine::contains "bool HorizontalLine::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  HorizontalLine::getYpos "double HorizontalLine::getYpos() const
";


// File: classIAbstractParticle.xml
%feature("docstring") IAbstractParticle "

Interface for a generic particle.

Inherited by  IParticle and  ParticleDistribution.

C++ includes: IAbstractParticle.h
";

%feature("docstring")  IAbstractParticle::IAbstractParticle "IAbstractParticle::IAbstractParticle()
";

%feature("docstring")  IAbstractParticle::~IAbstractParticle "IAbstractParticle::~IAbstractParticle()
";

%feature("docstring")  IAbstractParticle::clone "virtual IAbstractParticle* IAbstractParticle::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IAbstractParticle::accept "void IAbstractParticle::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IAbstractParticle::abundance "double IAbstractParticle::abundance() const
";

%feature("docstring")  IAbstractParticle::setAbundance "void IAbstractParticle::setAbundance(double abundance)

Sets particle abundance.

Parameters:
-----------

abundance: 
proportion of this type of particles normalized to the total number of particles in the layout. 
";

%feature("docstring")  IAbstractParticle::translate "virtual void IAbstractParticle::translate(kvector_t translation)=0

Translates the particle with the given vector. 
";

%feature("docstring")  IAbstractParticle::rotate "virtual void IAbstractParticle::rotate(const IRotation &rotation)=0

Applies the given rotation to the particle. 
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


// File: classIBackground.xml
%feature("docstring") IBackground "

Interface for a simulating the background signal

C++ includes: IBackground.h
";

%feature("docstring")  IBackground::~IBackground "IBackground::~IBackground()
";

%feature("docstring")  IBackground::clone "virtual IBackground* IBackground::clone() const =0
";

%feature("docstring")  IBackground::addBackGround "virtual double IBackground::addBackGround(double element) const =0
";


// File: classIChiSquaredModule.xml
%feature("docstring") IChiSquaredModule "

Interface residual calculations.

C++ includes: IChiSquaredModule.h
";

%feature("docstring")  IChiSquaredModule::IChiSquaredModule "IChiSquaredModule::IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::~IChiSquaredModule "IChiSquaredModule::~IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::clone "virtual IChiSquaredModule* IChiSquaredModule::clone() const =0

clone method 
";

%feature("docstring")  IChiSquaredModule::varianceFunction "const IVarianceFunction * IChiSquaredModule::varianceFunction() const

Returns squared function. 
";

%feature("docstring")  IChiSquaredModule::setVarianceFunction "void IChiSquaredModule::setVarianceFunction(const IVarianceFunction &variance_function)

Sets squared function. 
";

%feature("docstring")  IChiSquaredModule::getIntensityFunction "const IIntensityFunction * IChiSquaredModule::getIntensityFunction() const

Returns data rescaler. 
";

%feature("docstring")  IChiSquaredModule::setIntensityFunction "void IChiSquaredModule::setIntensityFunction(const IIntensityFunction &intensity_function)

Sets data rescaler. 
";

%feature("docstring")  IChiSquaredModule::residual "virtual double IChiSquaredModule::residual(double a, double b, double weight)=0
";


// File: classICloneable.xml
%feature("docstring") ICloneable "

Interface for polymorphic classes that should not be copied, except by explicit cloning.

Child classes of  ICloneable must provide clone().

C++ includes: ICloneable.h
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable()
";

%feature("docstring")  ICloneable::~ICloneable "ICloneable::~ICloneable()
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable(const ICloneable &)=delete
";

%feature("docstring")  ICloneable::clone "virtual ICloneable* ICloneable::clone() const =0
";


// File: classIClusteredParticles.xml
%feature("docstring") IClusteredParticles "

An ordered assembly of particles. Currently, the only child class is  Crystal.

C++ includes: IClusteredParticles.h
";

%feature("docstring")  IClusteredParticles::clone "IClusteredParticles* IClusteredParticles::clone() const override=0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IClusteredParticles::accept "void IClusteredParticles::accept(INodeVisitor *visitor) const override=0

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IClusteredParticles::createTotalFormFactor "virtual IFormFactor* IClusteredParticles::createTotalFormFactor(const IFormFactor &, const IRotation *, const kvector_t &) const =0

Creates a total form factor for the mesocrystal with a specific shape and content The bulk content of the mesocrystal is encapsulated by the  IClusteredParticles object itself 
";

%feature("docstring")  IClusteredParticles::homogeneousRegions "virtual std::vector<HomogeneousRegion> IClusteredParticles::homogeneousRegions() const =0

Creates region information with volumetric densities instead of absolute volume These densities need to be multiplied by the total mesocrystal volume 
";


// File: classIComputation.xml
%feature("docstring") IComputation "

Interface for a single-threaded computation with given range of SimulationElements and  ProgressHandler.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: IComputation.h
";

%feature("docstring")  IComputation::IComputation "IComputation::IComputation(const MultiLayer &sample, const SimulationOptions &options, ProgressHandler &progress)
";

%feature("docstring")  IComputation::~IComputation "IComputation::~IComputation()
";

%feature("docstring")  IComputation::run "void IComputation::run()
";

%feature("docstring")  IComputation::isCompleted "bool IComputation::isCompleted() const
";

%feature("docstring")  IComputation::errorMessage "std::string IComputation::errorMessage() const
";


// File: classIcosahedron.xml
%feature("docstring") Icosahedron "";

%feature("docstring")  Icosahedron::Icosahedron "Icosahedron::Icosahedron(double edge)
";

%feature("docstring")  Icosahedron::~Icosahedron "Icosahedron::~Icosahedron()
";


// File: classIdentityRotation.xml
%feature("docstring") IdentityRotation "";

%feature("docstring")  IdentityRotation::IdentityRotation "IdentityRotation::IdentityRotation()=default
";

%feature("docstring")  IdentityRotation::clone "IdentityRotation* IdentityRotation::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  IdentityRotation::createInverse "IdentityRotation* IdentityRotation::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  IdentityRotation::accept "void IdentityRotation::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IdentityRotation::getTransform3D "Transform3D IdentityRotation::getTransform3D() const

Returns transformation. 
";

%feature("docstring")  IdentityRotation::isIdentity "bool IdentityRotation::isIdentity() const

Returns true if rotation matrix is identity matrix (no rotations) 
";


// File: classIDetector.xml
%feature("docstring") IDetector "

Abstract detector interface.

C++ includes: IDetector.h
";

%feature("docstring")  IDetector::IDetector "IDetector::IDetector()
";

%feature("docstring")  IDetector::clone "IDetector* IDetector::clone() const override=0
";

%feature("docstring")  IDetector::~IDetector "IDetector::~IDetector()
";

%feature("docstring")  IDetector::init "virtual void IDetector::init(const Beam &)

Inits detector with the beam settings. 
";

%feature("docstring")  IDetector::clear "void IDetector::clear()
";

%feature("docstring")  IDetector::addAxis "void IDetector::addAxis(const IAxis &axis)
";

%feature("docstring")  IDetector::getAxis "const IAxis & IDetector::getAxis(size_t index) const
";

%feature("docstring")  IDetector::dimension "size_t IDetector::dimension() const

Returns actual dimensionality of the detector (number of defined axes) 
";

%feature("docstring")  IDetector::axisBinIndex "size_t IDetector::axisBinIndex(size_t index, size_t selected_axis) const

Calculate axis index for given global index. 
";

%feature("docstring")  IDetector::totalSize "size_t IDetector::totalSize() const

Returns total number of pixels. 
";

%feature("docstring")  IDetector::detectorMask "virtual const DetectorMask* IDetector::detectorMask() const =0

Returns detector masks container. 
";

%feature("docstring")  IDetector::setAnalyzerProperties "void IDetector::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  IDetector::setDetectorResolution "void IDetector::setDetectorResolution(const IDetectorResolution &p_detector_resolution)

Sets the detector resolution. 
";

%feature("docstring")  IDetector::setResolutionFunction "void IDetector::setResolutionFunction(const IResolutionFunction2D &resFunc)
";

%feature("docstring")  IDetector::applyDetectorResolution "void IDetector::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Applies the detector resolution to the given intensity maps. 
";

%feature("docstring")  IDetector::removeDetectorResolution "void IDetector::removeDetectorResolution()

Removes detector resolution function. 
";

%feature("docstring")  IDetector::detectorResolution "const IDetectorResolution * IDetector::detectorResolution() const

Returns a pointer to detector resolution object. 
";

%feature("docstring")  IDetector::createDetectorMap "std::unique_ptr< OutputData< double > > IDetector::createDetectorMap() const

Returns empty detector map in given axes units. 
";

%feature("docstring")  IDetector::regionOfInterest "virtual const RegionOfInterest* IDetector::regionOfInterest() const =0

Returns region of interest if exists. 
";

%feature("docstring")  IDetector::resetRegionOfInterest "virtual void IDetector::resetRegionOfInterest()=0

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  IDetector::detectionProperties "const DetectionProperties& IDetector::detectionProperties() const

Returns detection properties. 
";

%feature("docstring")  IDetector::createDetectorIntensity "OutputData< double > * IDetector::createDetectorIntensity(const std::vector< SimulationElement > &elements) const

Returns new intensity map with detector resolution applied. Map will be cropped to ROI if ROI is present. 
";

%feature("docstring")  IDetector::defaultAxesUnits "virtual AxesUnits IDetector::defaultAxesUnits() const

Return default axes units. 
";

%feature("docstring")  IDetector::numberOfSimulationElements "size_t IDetector::numberOfSimulationElements() const

Returns number of simulation elements. 
";

%feature("docstring")  IDetector::getChildren "std::vector< const INode * > IDetector::getChildren() const override

Returns a vector of children (const). 
";

%feature("docstring")  IDetector::iterate "void IDetector::iterate(std::function< void(const_iterator)> func, bool visit_masks=false) const
";


// File: classIDetector2D.xml
%feature("docstring") IDetector2D "

Abstract 2D detector interface.

C++ includes: IDetector2D.h
";

%feature("docstring")  IDetector2D::IDetector2D "IDetector2D::IDetector2D()
";

%feature("docstring")  IDetector2D::clone "IDetector2D* IDetector2D::clone() const override=0
";

%feature("docstring")  IDetector2D::~IDetector2D "IDetector2D::~IDetector2D()
";

%feature("docstring")  IDetector2D::setDetectorParameters "void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  IDetector2D::setDetectorAxes "void IDetector2D::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)

Sets detector parameters using axes. 
";

%feature("docstring")  IDetector2D::removeMasks "void IDetector2D::removeMasks()

Removes all masks from the detector. 
";

%feature("docstring")  IDetector2D::detectorMask "const DetectorMask * IDetector2D::detectorMask() const override

Returns detector masks container. 
";

%feature("docstring")  IDetector2D::addMask "void IDetector2D::addMask(const IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask ( Rectangle,  Polygon,  Line,  Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  IDetector2D::maskAll "void IDetector2D::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  IDetector2D::regionOfInterest "const RegionOfInterest * IDetector2D::regionOfInterest() const override

Returns region of interest if exists. 
";

%feature("docstring")  IDetector2D::setRegionOfInterest "void IDetector2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)

Sets rectangular region of interest with lower left and upper right corners defined. 
";

%feature("docstring")  IDetector2D::resetRegionOfInterest "void IDetector2D::resetRegionOfInterest() override

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  IDetector2D::active_indices "std::vector< size_t > IDetector2D::active_indices() const

Returns vector of unmasked detector indices. 
";

%feature("docstring")  IDetector2D::createPixel "virtual IPixel* IDetector2D::createPixel(size_t index) const =0

Create an  IPixel for the given  OutputData object and index. 
";

%feature("docstring")  IDetector2D::getIndexOfSpecular "virtual size_t IDetector2D::getIndexOfSpecular(const Beam &beam) const =0

Returns index of pixel that contains the specular wavevector. If no pixel contains this specular wavevector, the number of pixels is returned. This corresponds to an overflow index. 
";

%feature("docstring")  IDetector2D::createContext "std::unique_ptr< DetectorContext > IDetector2D::createContext() const
";


// File: classIDetectorResolution.xml
%feature("docstring") IDetectorResolution "

Interface for detector resolution algorithms

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

Interface for one-dimensional distributions.

C++ includes: Distributions.h
";

%feature("docstring")  IDistribution1D::IDistribution1D "IDistribution1D::IDistribution1D()
";

%feature("docstring")  IDistribution1D::~IDistribution1D "virtual IDistribution1D::~IDistribution1D()
";

%feature("docstring")  IDistribution1D::clone "virtual IDistribution1D* IDistribution1D::clone() const =0
";

%feature("docstring")  IDistribution1D::probabilityDensity "virtual double IDistribution1D::probabilityDensity(double x) const =0

Returns the distribution-specific probability density for value x. 
";

%feature("docstring")  IDistribution1D::getMean "virtual double IDistribution1D::getMean() const =0

Returns the distribution-specific mean. 
";

%feature("docstring")  IDistribution1D::equidistantSamples "std::vector< ParameterSample > IDistribution1D::equidistantSamples(size_t nbr_samples, double sigma_factor=0., const RealLimits &limits=RealLimits()) const

Returns equidistant samples, using intrinsic parameters, weighted with  probabilityDensity(). 
";

%feature("docstring")  IDistribution1D::equidistantSamplesInRange "std::vector< ParameterSample > IDistribution1D::equidistantSamplesInRange(size_t nbr_samples, double xmin, double xmax) const

Returns equidistant samples from xmin to xmax, weighted with  probabilityDensity(). 
";

%feature("docstring")  IDistribution1D::equidistantPoints "virtual std::vector<double> IDistribution1D::equidistantPoints(size_t nbr_samples, double sigma_factor, const RealLimits &limits=RealLimits()) const =0

Returns equidistant interpolation points, with range computed in distribution-specific way from mean and width parameter, taking into account limits and sigma_factor. 
";

%feature("docstring")  IDistribution1D::equidistantPointsInRange "std::vector< double > IDistribution1D::equidistantPointsInRange(size_t nbr_samples, double xmin, double xmax) const

Returns equidistant interpolation points from xmin to xmax. 
";

%feature("docstring")  IDistribution1D::isDelta "virtual bool IDistribution1D::isDelta() const =0

Returns true if the distribution is in the limit case of a Dirac delta distribution. 
";

%feature("docstring")  IDistribution1D::setUnits "void IDistribution1D::setUnits(const std::string &units)

Sets distribution units. 
";


// File: classIDistribution1DSampler.xml
%feature("docstring") IDistribution1DSampler "";

%feature("docstring")  IDistribution1DSampler::IDistribution1DSampler "IDistribution1DSampler::IDistribution1DSampler()
";

%feature("docstring")  IDistribution1DSampler::~IDistribution1DSampler "IDistribution1DSampler::~IDistribution1DSampler()
";

%feature("docstring")  IDistribution1DSampler::randomSample "virtual double IDistribution1DSampler::randomSample() const =0
";


// File: classIDistribution2DSampler.xml
%feature("docstring") IDistribution2DSampler "";

%feature("docstring")  IDistribution2DSampler::IDistribution2DSampler "IDistribution2DSampler::IDistribution2DSampler()
";

%feature("docstring")  IDistribution2DSampler::~IDistribution2DSampler "IDistribution2DSampler::~IDistribution2DSampler()
";

%feature("docstring")  IDistribution2DSampler::randomSample "virtual std::pair<double, double> IDistribution2DSampler::randomSample() const =0
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

%feature("docstring")  IFactory::create "std::unique_ptr<AbstractProduct> IFactory< Key, AbstractProduct >::create(const Key &item_key) const
";

%feature("docstring")  IFactory::registerItem "bool IFactory< Key, AbstractProduct >::registerItem(const Key &item_key, CreateItemCallback CreateFn, const std::string &itemDescription=\"\")

Registers object's creation function and store object description. 
";

%feature("docstring")  IFactory::contains "bool IFactory< Key, AbstractProduct >::contains(const Key &item_key) const
";

%feature("docstring")  IFactory::~IFactory "IFactory< Key, AbstractProduct >::~IFactory()
";

%feature("docstring")  IFactory::size "size_t IFactory< Key, AbstractProduct >::size() const

Returns number of registered objects. 
";

%feature("docstring")  IFactory::begin "const_iterator IFactory< Key, AbstractProduct >::begin() const
";

%feature("docstring")  IFactory::end "const_iterator IFactory< Key, AbstractProduct >::end() const
";


// File: classIFootprintFactor.xml
%feature("docstring") IFootprintFactor "

Abstract base for classes that calculate the beam footprint factor

C++ includes: IFootprintFactor.h
";

%feature("docstring")  IFootprintFactor::IFootprintFactor "IFootprintFactor::IFootprintFactor()=delete
";

%feature("docstring")  IFootprintFactor::IFootprintFactor "IFootprintFactor::IFootprintFactor(double width_ratio)
";

%feature("docstring")  IFootprintFactor::~IFootprintFactor "IFootprintFactor::~IFootprintFactor()
";

%feature("docstring")  IFootprintFactor::clone "virtual IFootprintFactor* IFootprintFactor::clone() const =0
";

%feature("docstring")  IFootprintFactor::setWidthRatio "void IFootprintFactor::setWidthRatio(double width_ratio)
";

%feature("docstring")  IFootprintFactor::widthRatio "double IFootprintFactor::widthRatio() const
";

%feature("docstring")  IFootprintFactor::calculate "virtual double IFootprintFactor::calculate(double alpha) const =0

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  IFootprintFactor::print "virtual std::string IFootprintFactor::print() const =0

Print python-formatted footprint definition. 
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

%feature("docstring")  IFormFactor::createSlicedFormFactor "IFormFactor * IFormFactor::createSlicedFormFactor(ZLimits limits, const IRotation &rot, kvector_t translation) const

Creates a (possibly sliced) form factor with the given rotation and translation. 
";

%feature("docstring")  IFormFactor::setAmbientMaterial "virtual void IFormFactor::setAmbientMaterial(Material)=0

Passes the material in which this particle is embedded. 
";

%feature("docstring")  IFormFactor::evaluate "virtual complex_t IFormFactor::evaluate(const WavevectorInfo &wavevectors) const =0

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  IFormFactor::evaluatePol "Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions. 
";

%feature("docstring")  IFormFactor::volume "double IFormFactor::volume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactor::radialExtension "virtual double IFormFactor::radialExtension() const =0

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactor::bottomZ "virtual double IFormFactor::bottomZ(const IRotation &rotation) const =0

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactor::topZ "virtual double IFormFactor::topZ(const IRotation &rotation) const =0

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactor::setSpecularInfo "void IFormFactor::setSpecularInfo(std::unique_ptr< const ILayerRTCoefficients >, std::unique_ptr< const ILayerRTCoefficients >)

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

%feature("docstring")  IFormFactorBorn::setAmbientMaterial "void IFormFactorBorn::setAmbientMaterial(Material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  IFormFactorBorn::evaluate "complex_t IFormFactorBorn::evaluate(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for complex wavevectors ki, kf. 
";

%feature("docstring")  IFormFactorBorn::evaluatePol "Eigen::Matrix2cd IFormFactorBorn::evaluatePol(const WavevectorInfo &wavevectors) const override

Returns scattering amplitude for matrix interactions. 
";

%feature("docstring")  IFormFactorBorn::bottomZ "double IFormFactorBorn::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorBorn::topZ "double IFormFactorBorn::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorBorn::evaluate_for_q "virtual complex_t IFormFactorBorn::evaluate_for_q(cvector_t q) const =0

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classIFormFactorDecorator.xml
%feature("docstring") IFormFactorDecorator "

Encapsulates another formfactor and adds extra functionality (a scalar factor, a position-dependent phase factor, ...).

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

%feature("docstring")  IFormFactorDecorator::accept "void IFormFactorDecorator::accept(INodeVisitor *visitor) const override=0

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IFormFactorDecorator::setAmbientMaterial "void IFormFactorDecorator::setAmbientMaterial(Material material) override

Passes the material in which this particle is embedded. 
";

%feature("docstring")  IFormFactorDecorator::volume "double IFormFactorDecorator::volume() const override

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactorDecorator::radialExtension "double IFormFactorDecorator::radialExtension() const override

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactorDecorator::bottomZ "double IFormFactorDecorator::bottomZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorDecorator::topZ "double IFormFactorDecorator::topZ(const IRotation &rotation) const override

Returns the z-coordinate of the lowest point in this shape after a given rotation. 
";

%feature("docstring")  IFormFactorDecorator::getFormFactor "const IFormFactor* IFormFactorDecorator::getFormFactor() const
";


// File: classIFresnelMap.xml
%feature("docstring") IFresnelMap "

Holds the necessary information to calculate the radiation wavefunction in every layer for different incoming (outgoing) angles of the beam in the top layer (these amplitudes correspond to the specular part of the wavefunction).

C++ includes: IFresnelMap.h
";

%feature("docstring")  IFresnelMap::IFresnelMap "IFresnelMap::IFresnelMap(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  IFresnelMap::~IFresnelMap "IFresnelMap::~IFresnelMap()
";

%feature("docstring")  IFresnelMap::getOutCoefficients "virtual std::unique_ptr<const ILayerRTCoefficients> IFresnelMap::getOutCoefficients(const SimulationElement &sim_element, size_t layer_index) const =0

Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector. 
";

%feature("docstring")  IFresnelMap::getInCoefficients "std::unique_ptr<const ILayerRTCoefficients> IFresnelMap::getInCoefficients(const T &sim_element, size_t layer_index) const

Retrieves the amplitude coefficients for an incoming wavevector. 
";

%feature("docstring")  IFresnelMap::setSlices "void IFresnelMap::setSlices(const std::vector< Slice > &slices)
";

%feature("docstring")  IFresnelMap::slices "const std::vector< Slice > & IFresnelMap::slices() const
";

%feature("docstring")  IFresnelMap::disableCaching "void IFresnelMap::disableCaching()

Disables caching of previously computed Fresnel coefficients. 
";


// File: classIFTDecayFunction1D.xml
%feature("docstring") IFTDecayFunction1D "

Interface for a one-dimensional decay function, with evaluate(q) returning the Fourier transform, normalized to  $\\\\int dq\\\\; {\\\\rm evaluate}(q) = 1$.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  IFTDecayFunction1D::IFTDecayFunction1D "IFTDecayFunction1D::IFTDecayFunction1D(double decay_length)

Constructor of one-dimensional decay function.

Parameters:
-----------

decay_length: 
half-width of the distribution in nanometers 
";

%feature("docstring")  IFTDecayFunction1D::clone "virtual IFTDecayFunction1D* IFTDecayFunction1D::clone() const =0
";

%feature("docstring")  IFTDecayFunction1D::evaluate "virtual double IFTDecayFunction1D::evaluate(double q) const =0
";

%feature("docstring")  IFTDecayFunction1D::decayLength "double IFTDecayFunction1D::decayLength() const
";


// File: classIFTDecayFunction2D.xml
%feature("docstring") IFTDecayFunction2D "

Interface for two-dimensional decay function in reciprocal space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  IFTDecayFunction2D::IFTDecayFunction2D "IFTDecayFunction2D::IFTDecayFunction2D(double decay_length_x, double decay_length_y, double gamma=0)

Constructor of two-dimensional decay function in reciprocal space.

Parameters:
-----------

decay_length_x: 
the decay length in nanometers along x-axis of the distribution

decay_length_y: 
the decay length in nanometers along y-axis of the distribution

gamma: 
distribution orientation with respect to the corresponding lattice vector in radians 
";

%feature("docstring")  IFTDecayFunction2D::clone "virtual IFTDecayFunction2D* IFTDecayFunction2D::clone() const =0
";

%feature("docstring")  IFTDecayFunction2D::setGamma "void IFTDecayFunction2D::setGamma(double gamma)

set angle between first lattice vector and X-axis of distribution (both in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::gamma "double IFTDecayFunction2D::gamma() const

get angle between first lattice vector and X-axis of distribution (both in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::decayLengthX "double IFTDecayFunction2D::decayLengthX() const

get decay length in distribution's X-direction 
";

%feature("docstring")  IFTDecayFunction2D::decayLengthY "double IFTDecayFunction2D::decayLengthY() const

get decay length in distribution's Y-direction 
";

%feature("docstring")  IFTDecayFunction2D::evaluate "virtual double IFTDecayFunction2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  IFTDecayFunction2D::boundingReciprocalLatticeCoordinates "std::pair< double, double > IFTDecayFunction2D::boundingReciprocalLatticeCoordinates(double qX, double qY, double a, double b, double alpha) const

transform back to a*, b* basis:

Calculates bounding values of reciprocal lattice coordinates that contain the centered rectangle with a corner defined by qX and qY 
";


// File: classIFTDistribution1D.xml
%feature("docstring") IFTDistribution1D "

Interface for a one-dimensional distribution, with normalization adjusted so that the Fourier transform evaluate(q) is a decay function that starts at evaluate(0)=1.

C++ includes: FTDistributions1D.h
";

%feature("docstring")  IFTDistribution1D::IFTDistribution1D "IFTDistribution1D::IFTDistribution1D(double omega)

Constructor of one-dimensional probability distribution.

Parameters:
-----------

omega: 
half-width of the distribution in nanometers 
";

%feature("docstring")  IFTDistribution1D::~IFTDistribution1D "IFTDistribution1D::~IFTDistribution1D()
";

%feature("docstring")  IFTDistribution1D::clone "virtual IFTDistribution1D* IFTDistribution1D::clone() const =0
";

%feature("docstring")  IFTDistribution1D::evaluate "virtual double IFTDistribution1D::evaluate(double q) const =0

Returns Fourier transform of this distribution; is a decay function starting at evaluate(0)=1. 
";

%feature("docstring")  IFTDistribution1D::setOmega "void IFTDistribution1D::setOmega(double omega)
";

%feature("docstring")  IFTDistribution1D::omega "double IFTDistribution1D::omega() const
";

%feature("docstring")  IFTDistribution1D::qSecondDerivative "virtual double IFTDistribution1D::qSecondDerivative() const =0

Returns the negative of the second order derivative in q space around q=0. 
";

%feature("docstring")  IFTDistribution1D::createSampler "virtual std::unique_ptr<IDistribution1DSampler> IFTDistribution1D::createSampler() const =0
";


// File: classIFTDistribution2D.xml
%feature("docstring") IFTDistribution2D "

Interface for two-dimensional distributions in Fourier space.

C++ includes: FTDistributions2D.h
";

%feature("docstring")  IFTDistribution2D::IFTDistribution2D "IFTDistribution2D::IFTDistribution2D(double omega_x, double omega_y, double gamma=0)

Constructor of two-dimensional probability distribution.

Parameters:
-----------

omega_x: 
half-width of the distribution along its x-axis in nanometers

omega_y: 
half-width of the distribution along its y-axis in nanometers

gamma: 
angle in direct space between first lattice vector and x-axis of the distribution 
";

%feature("docstring")  IFTDistribution2D::clone "IFTDistribution2D* IFTDistribution2D::clone() const =0
";

%feature("docstring")  IFTDistribution2D::setGamma "void IFTDistribution2D::setGamma(double gamma)
";

%feature("docstring")  IFTDistribution2D::gamma "double IFTDistribution2D::gamma() const
";

%feature("docstring")  IFTDistribution2D::delta "double IFTDistribution2D::delta() const
";

%feature("docstring")  IFTDistribution2D::omegaX "double IFTDistribution2D::omegaX() const
";

%feature("docstring")  IFTDistribution2D::omegaY "double IFTDistribution2D::omegaY() const
";

%feature("docstring")  IFTDistribution2D::evaluate "virtual double IFTDistribution2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  IFTDistribution2D::createSampler "virtual std::unique_ptr<IDistribution2DSampler> IFTDistribution2D::createSampler() const =0
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

%feature("docstring")  IHistogram::getXaxisIndex "size_t IHistogram::getXaxisIndex(size_t i) const

Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide with globalbin value. 
";

%feature("docstring")  IHistogram::getYaxisIndex "size_t IHistogram::getYaxisIndex(size_t i) const

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

%feature("docstring")  IHistogram::array "PyObject * IHistogram::array(DataType dataType=DataType::INTEGRAL) const

Returns numpy array with bin content (accumulated values). 
";

%feature("docstring")  IHistogram::getArray "PyObject * IHistogram::getArray(DataType dataType=DataType::INTEGRAL) const

Deprecated
Use  array() instead. 
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

%feature("docstring")  IIntensityFunction::~IIntensityFunction "IIntensityFunction::~IIntensityFunction()
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

%feature("docstring")  IInterferenceFunction::IInterferenceFunction "IInterferenceFunction::IInterferenceFunction()
";

%feature("docstring")  IInterferenceFunction::IInterferenceFunction "IInterferenceFunction::IInterferenceFunction(const IInterferenceFunction &other)
";

%feature("docstring")  IInterferenceFunction::~IInterferenceFunction "IInterferenceFunction::~IInterferenceFunction()
";

%feature("docstring")  IInterferenceFunction::clone "virtual IInterferenceFunction* IInterferenceFunction::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IInterferenceFunction::accept "virtual void IInterferenceFunction::accept(INodeVisitor *visitor) const =0

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IInterferenceFunction::evaluate "double IInterferenceFunction::evaluate(const kvector_t q, double outer_iff=1.0) const

Evaluates the interference function for a given wavevector transfer. 
";

%feature("docstring")  IInterferenceFunction::setPositionVariance "void IInterferenceFunction::setPositionVariance(double var)

Sets the variance of the position for the calculation of the DW factor It is defined as the variance in each relevant dimension 
";

%feature("docstring")  IInterferenceFunction::positionVariance "double IInterferenceFunction::positionVariance() const

Returns the position variance. 
";

%feature("docstring")  IInterferenceFunction::getParticleDensity "virtual double IInterferenceFunction::getParticleDensity() const

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";

%feature("docstring")  IInterferenceFunction::supportsMultilayer "virtual bool IInterferenceFunction::supportsMultilayer() const

Indicates if this interference function can be used with a multilayer (DWBA mode) 
";

%feature("docstring")  IInterferenceFunction::DWfactor "double IInterferenceFunction::DWfactor(kvector_t q) const

Evaluates the Debye-Waller factor for a given wavevector transfer. 
";


// File: classIInterferenceFunctionStrategy.xml
%feature("docstring") IInterferenceFunctionStrategy "

Base class of all interference function strategy classes. Provides an 'evaluate' function that computes the total scattering intensity from a decorated layer, taking into account a specific inter-particle interference function. This function uses the low-level functions scalarCalculation and polarizedCalculation that are to be overriden in the derived classes. Inheritance is used to support different approximation schemes ( DecouplingApproximationStrategy,  SSCApproximationStrategy).

Instantiation of child classes takes place in LayoutStrategyBuilder::createStrategy, which is called from ParticleLayoutComputation::eval.

C++ includes: IInterferenceFunctionStrategy.h
";

%feature("docstring")  IInterferenceFunctionStrategy::IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(const SimulationOptions &sim_params, bool polarized)
";

%feature("docstring")  IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy()
";

%feature("docstring")  IInterferenceFunctionStrategy::init "void IInterferenceFunctionStrategy::init(const std::vector< FormFactorCoherentSum > &weighted_formfactors, const IInterferenceFunction *p_iff)

Initializes the object with form factors and an interference function. 
";

%feature("docstring")  IInterferenceFunctionStrategy::evaluate "double IInterferenceFunctionStrategy::evaluate(const SimulationElement &sim_element) const

Calculates the intensity for scalar particles/interactions. 
";


// File: classILatticeOrientation.xml
%feature("docstring") ILatticeOrientation "";

%feature("docstring")  ILatticeOrientation::~ILatticeOrientation "ILatticeOrientation::~ILatticeOrientation()
";

%feature("docstring")  ILatticeOrientation::clone "virtual ILatticeOrientation* ILatticeOrientation::clone() const =0
";

%feature("docstring")  ILatticeOrientation::usePrimitiveLattice "virtual void ILatticeOrientation::usePrimitiveLattice(const Lattice &lattice)=0
";

%feature("docstring")  ILatticeOrientation::transformationMatrix "virtual Transform3D ILatticeOrientation::transformationMatrix() const =0
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

%feature("docstring")  ILayout::~ILayout "ILayout::~ILayout()
";

%feature("docstring")  ILayout::clone "virtual ILayout* ILayout::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ILayout::accept "virtual void ILayout::accept(INodeVisitor *visitor) const =0

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ILayout::particles "virtual SafePointerVector<IParticle> ILayout::particles() const =0

Returns information on all particles (type and abundance) and generates new particles if an  IAbstractParticle denotes a collection 
";

%feature("docstring")  ILayout::interferenceFunction "virtual const IInterferenceFunction* ILayout::interferenceFunction() const =0

Returns the interference function. 
";

%feature("docstring")  ILayout::getTotalAbundance "virtual double ILayout::getTotalAbundance() const =0

Get total abundance of all particles. 
";

%feature("docstring")  ILayout::totalParticleSurfaceDensity "virtual double ILayout::totalParticleSurfaceDensity() const =0

Returns surface density of all particles. 
";

%feature("docstring")  ILayout::setTotalParticleSurfaceDensity "virtual void ILayout::setTotalParticleSurfaceDensity(double particle_density)=0

Sets surface density of all particles. 
";

%feature("docstring")  ILayout::weight "double ILayout::weight() const

Returns the relative weight of this layout. 
";

%feature("docstring")  ILayout::setWeight "void ILayout::setWeight(double weight)

Sets the relative weight of this layout. 
";


// File: classIMetricWrapper.xml
%feature("docstring") IMetricWrapper "";

%feature("docstring")  IMetricWrapper::~IMetricWrapper "IMetricWrapper::~IMetricWrapper()
";

%feature("docstring")  IMetricWrapper::compute "virtual double IMetricWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const =0
";


// File: classIMultiLayerBuilder.xml
%feature("docstring") IMultiLayerBuilder "

Interface to the class capable to build samples to simulate.

C++ includes: IMultiLayerBuilder.h
";

%feature("docstring")  IMultiLayerBuilder::IMultiLayerBuilder "IMultiLayerBuilder::IMultiLayerBuilder()
";

%feature("docstring")  IMultiLayerBuilder::buildSample "virtual MultiLayer* IMultiLayerBuilder::buildSample() const =0
";

%feature("docstring")  IMultiLayerBuilder::createSample "virtual MultiLayer* IMultiLayerBuilder::createSample(size_t index=0)
";

%feature("docstring")  IMultiLayerBuilder::size "virtual size_t IMultiLayerBuilder::size()
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

%feature("docstring")  INamed::~INamed "INamed::~INamed()
";

%feature("docstring")  INamed::getName "std::string INamed::getName() const
";


// File: classInfinitePlane.xml
%feature("docstring") InfinitePlane "

The infinite plane is used for masking everything once and forever.

C++ includes: InfinitePlane.h
";

%feature("docstring")  InfinitePlane::InfinitePlane "InfinitePlane::InfinitePlane()
";

%feature("docstring")  InfinitePlane::clone "InfinitePlane* InfinitePlane::clone() const
";

%feature("docstring")  InfinitePlane::contains "bool InfinitePlane::contains(double, double) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  InfinitePlane::contains "bool InfinitePlane::contains(const Bin1D &, const Bin1D &) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";


// File: classINode.xml
%feature("docstring") INode "

Base class for tree-like structures containing parameterized objects.

C++ includes: INode.h
";

%feature("docstring")  INode::INode "INode::INode()
";

%feature("docstring")  INode::~INode "virtual INode::~INode()
";

%feature("docstring")  INode::accept "virtual void INode::accept(INodeVisitor *visitor) const =0

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  INode::treeToString "std::string INode::treeToString() const

Returns multiline string representing tree structure below the node. 
";

%feature("docstring")  INode::registerChild "void INode::registerChild(INode *node)
";

%feature("docstring")  INode::getChildren "std::vector< const INode * > INode::getChildren() const

Returns a vector of children (const). 
";

%feature("docstring")  INode::setParent "void INode::setParent(const INode *newParent)
";

%feature("docstring")  INode::parent "INode * INode::parent() const
";

%feature("docstring")  INode::parent "INode* INode::parent()
";

%feature("docstring")  INode::copyNumber "int INode::copyNumber(const INode *node) const

Returns copyNumber of child, which takes into account existence of children with same name. 
";

%feature("docstring")  INode::displayName "std::string INode::displayName() const

Returns display name, composed from the name of node and it's copy number. 
";

%feature("docstring")  INode::createParameterTree "ParameterPool * INode::createParameterTree() const

Creates new parameter pool, with all local parameters and those of its children. 
";


// File: classINodeVisitor.xml
%feature("docstring") INodeVisitor "

From visitor pattern to achieve double dispatch.

Visitor interface to visit  ISample objects.

C++ includes: INodeVisitor.h
";

%feature("docstring")  INodeVisitor::INodeVisitor "INodeVisitor::INodeVisitor()
";

%feature("docstring")  INodeVisitor::~INodeVisitor "virtual INodeVisitor::~INodeVisitor()
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const BasicLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Beam *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ConstantBackground *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ConvolutionDetectorResolution *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Crystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionCosine *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionGaussian *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionLogNormal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const DistributionTrapezoid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FootprintFactorGaussian *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FootprintFactorSquare *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorAnisoPyramid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBarGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBarLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorBox *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCantellatedCube *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCone6 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCoreShell *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCuboctahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorCylinder *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDWBA *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDWBAPol *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorMaterial *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorPositionFactor *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDecoratorRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDodecahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorDot *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorEllipsoidalCylinder *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorFullSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorFullSpheroid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorHemiEllipsoid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorIcosahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorLongBoxGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorLongBoxLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorLorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPrism3 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPrism6 *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorPyramid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorRipple1Box *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorRipple1Gauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorRipple1Lorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorRipple2Box *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorRipple2Gauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorRipple2Lorentz *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSphereGaussianRadius *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorSphereLogNormalRadius *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTetrahedron *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedCube *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedSphere *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorTruncatedSpheroid *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FormFactorWeighted *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DTriangle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction1DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDecayFunction2DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DCosine *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DTriangle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution1DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DCauchy *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DCone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DGate *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DGauss *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const FTDistribution2DVoigt *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const GISASSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const HexagonalLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IAbstractParticle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IClusteredParticles *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IdentityRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactor *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactorBorn *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IFormFactorDecorator *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IInterferenceFunction *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ILayout *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const INode *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Instrument *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IntensityNormalizer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IntensityScaleAndShiftNormalizer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction1DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DParaCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction2DSuperLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunction3DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionFinite2DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionFinite3DLattice *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionHardDisk *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionRadialParaCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionTwin *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const InterferenceFunctionNone *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IParticle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IPeakShape *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IRotation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ISample *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const IsGISAXSDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Layer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const LayerInterface *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const LayerRoughness *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const MesoCrystal *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const MultiLayer *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const OffSpecSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const Particle *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleComposition *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleCoreShell *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleDistribution *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ParticleLayout *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const PoissonNoiseBackground *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RectangularDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const ResolutionFunction2DGaussian *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationEuler *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationX *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationY *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const RotationZ *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SpecularDetector1D *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SpecularSimulation *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SphericalDetector *)
";

%feature("docstring")  INodeVisitor::visit "virtual void INodeVisitor::visit(const SquareLattice *)
";

%feature("docstring")  INodeVisitor::depth "int INodeVisitor::depth() const

Returns depth of the visitor in the composite hierarchy. 
";

%feature("docstring")  INodeVisitor::setDepth "void INodeVisitor::setDepth(int depth)

Sets depth of the visitor in the composite hierarchy. 
";


// File: classInstrument.xml
%feature("docstring") Instrument "

Assembles beam, detector and their relative positions with respect to the sample.

C++ includes: Instrument.h
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument()
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument(const Instrument &other)
";

%feature("docstring")  Instrument::~Instrument "Instrument::~Instrument()
";

%feature("docstring")  Instrument::accept "void Instrument::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  Instrument::getDetector "IDetector * Instrument::getDetector() const

Returns the detector data. 
";

%feature("docstring")  Instrument::getDetector "IDetector* Instrument::getDetector()
";

%feature("docstring")  Instrument::getDetectorMask "const DetectorMask * Instrument::getDetectorMask() const
";

%feature("docstring")  Instrument::getDetectorAxis "const IAxis & Instrument::getDetectorAxis(size_t index) const

Returns a detector axis. 
";

%feature("docstring")  Instrument::getDetectorDimension "size_t Instrument::getDetectorDimension() const

Returns the detector's dimension. 
";

%feature("docstring")  Instrument::setDetector "void Instrument::setDetector(const IDetector &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  Instrument::setDetectorResolutionFunction "void Instrument::setDetectorResolutionFunction(const IResolutionFunction2D &p_resolution_function)

Sets detector resolution function. 
";

%feature("docstring")  Instrument::removeDetectorResolution "void Instrument::removeDetectorResolution()

Removes detector resolution function. 
";

%feature("docstring")  Instrument::setAnalyzerProperties "void Instrument::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  Instrument::applyDetectorResolution "void Instrument::applyDetectorResolution(OutputData< double > *p_intensity_map) const

apply the detector resolution to the given intensity map 
";

%feature("docstring")  Instrument::createDetectorIntensity "OutputData< double > * Instrument::createDetectorIntensity(const std::vector< SimulationElement > &elements) const

Returns new intensity map with detector resolution applied and axes in requested units. 
";

%feature("docstring")  Instrument::initDetector "void Instrument::initDetector()

init detector with beam settings 
";

%feature("docstring")  Instrument::getChildren "std::vector< const INode * > Instrument::getChildren() const

Returns a vector of children (const). 
";


// File: classIntegratorMCMiser.xml
%feature("docstring") IntegratorMCMiser "

Template class to use Monte Carlo MISER integration of class member functions.

Wraps an integrator from GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_miser(this, mem_function, dimension)'

Call: 'integrator.integrate(lmin, lmax, data, nbr_points)'

C++ includes: IntegratorMCMiser.h
";

%feature("docstring")  IntegratorMCMiser::IntegratorMCMiser "IntegratorMCMiser< T >::IntegratorMCMiser(const T *p_object, miser_integrand< T > p_member_function, size_t dim)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorMCMiser::~IntegratorMCMiser "IntegratorMCMiser< T >::~IntegratorMCMiser()
";

%feature("docstring")  IntegratorMCMiser::integrate "double IntegratorMCMiser< T >::integrate(double *min_array, double *max_array, void *params, size_t nbr_points)

perform the actual integration over the ranges [min_array, max_array] 
";


// File: classIntensityDataIOFactory.xml
%feature("docstring") IntensityDataIOFactory "

Provides users with possibility to read and write IntensityData from/to files in different format. Type of the file will be deduced from file name. *.txt - ASCII file with 2D array [nrow][ncol], layout as in numpy. *.int -  BornAgain internal ASCII format. *.tif - 32-bits tiff file. If file name ends woth \"*.gz\" or \"*.bz2\" the file will be zipped on the fly using appropriate algorithm.

Usage:

C++ includes: IntensityDataIOFactory.h
";


// File: classIntensityFunctionLog.xml
%feature("docstring") IntensityFunctionLog "

Algorithm for applying log function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionLog::clone "IntensityFunctionLog * IntensityFunctionLog::clone() const
";

%feature("docstring")  IntensityFunctionLog::evaluate "double IntensityFunctionLog::evaluate(double value) const
";


// File: classIntensityFunctionSqrt.xml
%feature("docstring") IntensityFunctionSqrt "

Algorithm for applying sqrt function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionSqrt::clone "IntensityFunctionSqrt * IntensityFunctionSqrt::clone() const
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

%feature("docstring")  IntensityNormalizer::accept "void IntensityNormalizer::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  IntensityScaleAndShiftNormalizer::accept "void IntensityScaleAndShiftNormalizer::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::setMaximumIntensity "void IntensityScaleAndShiftNormalizer::setMaximumIntensity(double) final
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::clone "IntensityScaleAndShiftNormalizer* IntensityScaleAndShiftNormalizer::clone() const final
";


// File: classInterferenceFunction1DLattice.xml
%feature("docstring") InterferenceFunction1DLattice "

Interference function of a 1D lattice.

C++ includes: InterferenceFunction1DLattice.h
";

%feature("docstring")  InterferenceFunction1DLattice::InterferenceFunction1DLattice "InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length, double xi)

Constructor of interference function of one-dimensional lattice.

Parameters:
-----------

length: 
lattice constant in nanometers

xi: 
rotation of lattice with respect to x-axis in radians 
";

%feature("docstring")  InterferenceFunction1DLattice::~InterferenceFunction1DLattice "InterferenceFunction1DLattice::~InterferenceFunction1DLattice() final
";

%feature("docstring")  InterferenceFunction1DLattice::clone "InterferenceFunction1DLattice * InterferenceFunction1DLattice::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction1DLattice::accept "void InterferenceFunction1DLattice::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction1DLattice::setDecayFunction "void InterferenceFunction1DLattice::setDecayFunction(const IFTDecayFunction1D &decay)

Sets one-dimensional decay function.

Parameters:
-----------

decay: 
one-dimensional decay function in reciprocal space 
";

%feature("docstring")  InterferenceFunction1DLattice::getLatticeParameters "Lattice1DParameters InterferenceFunction1DLattice::getLatticeParameters() const
";

%feature("docstring")  InterferenceFunction1DLattice::getChildren "std::vector< const INode * > InterferenceFunction1DLattice::getChildren() const override final

Returns a vector of children (const). 
";


// File: classInterferenceFunction2DLattice.xml
%feature("docstring") InterferenceFunction2DLattice "

Interference function of a 2D lattice.

C++ includes: InterferenceFunction2DLattice.h
";

%feature("docstring")  InterferenceFunction2DLattice::InterferenceFunction2DLattice "InterferenceFunction2DLattice::InterferenceFunction2DLattice(const Lattice2D &lattice)
";

%feature("docstring")  InterferenceFunction2DLattice::InterferenceFunction2DLattice "InterferenceFunction2DLattice::InterferenceFunction2DLattice(double length_1, double length_2, double alpha, double xi=0.0)

Constructor of two-dimensional interference function.

Parameters:
-----------

length_1: 
length of the first basis vector in nanometers

length_2: 
length of the second basis vector in nanometers

alpha: 
angle between the basis vectors in radians

xi: 
rotation of the lattice with respect to the x-axis (beam direction) in radians 
";

%feature("docstring")  InterferenceFunction2DLattice::~InterferenceFunction2DLattice "InterferenceFunction2DLattice::~InterferenceFunction2DLattice() final
";

%feature("docstring")  InterferenceFunction2DLattice::clone "InterferenceFunction2DLattice * InterferenceFunction2DLattice::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction2DLattice::accept "void InterferenceFunction2DLattice::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction2DLattice::setDecayFunction "void InterferenceFunction2DLattice::setDecayFunction(const IFTDecayFunction2D &decay)

Sets two-dimensional decay function.

Parameters:
-----------

decay: 
two-dimensional decay function in reciprocal space 
";

%feature("docstring")  InterferenceFunction2DLattice::setIntegrationOverXi "void InterferenceFunction2DLattice::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunction2DLattice::integrationOverXi "bool InterferenceFunction2DLattice::integrationOverXi() const
";

%feature("docstring")  InterferenceFunction2DLattice::lattice "const Lattice2D & InterferenceFunction2DLattice::lattice() const
";

%feature("docstring")  InterferenceFunction2DLattice::getParticleDensity "double InterferenceFunction2DLattice::getParticleDensity() const override final

Returns the particle density associated with this 2d lattice. 
";

%feature("docstring")  InterferenceFunction2DLattice::getChildren "std::vector< const INode * > InterferenceFunction2DLattice::getChildren() const override final

Returns a vector of children (const). 
";

%feature("docstring")  InterferenceFunction2DLattice::onChange "void InterferenceFunction2DLattice::onChange() override final

Action to be taken in inherited class when a parameter has changed. 
";


// File: classInterferenceFunction2DParaCrystal.xml
%feature("docstring") InterferenceFunction2DParaCrystal "

Interference function of a 2D paracrystal.

C++ includes: InterferenceFunction2DParaCrystal.h
";

%feature("docstring")  InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(const Lattice2D &lattice, double damping_length=0.0, double domain_size_1=0.0, double domain_size_2=0.0)
";

%feature("docstring")  InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(double length_1, double length_2, double alpha, double xi=0.0, double damping_length=0.0)

Constructor of interference function of two-dimensional paracrystal.

Parameters:
-----------

length_1: 
length of first lattice vector in nanometers

length_2: 
length of second lattice vector in nanometers

alpha: 
angle between lattice vectors in radians

xi: 
rotation of lattice with respect to x-axis (beam direction) in radians

damping_length: 
the damping (coherence) length of the paracrystal in nanometers 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal() final
";

%feature("docstring")  InterferenceFunction2DParaCrystal::clone "InterferenceFunction2DParaCrystal * InterferenceFunction2DParaCrystal::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::accept "void InterferenceFunction2DParaCrystal::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setDomainSizes "void InterferenceFunction2DParaCrystal::setDomainSizes(double size_1, double size_2)

Sets the sizes of coherence domains.

Parameters:
-----------

size_1: 
coherence domain size along the first basis vector in nanometers

size_2: 
coherence domain size along the second basis vector in nanometers 
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

%feature("docstring")  InterferenceFunction2DParaCrystal::setDampingLength "void InterferenceFunction2DParaCrystal::setDampingLength(double damping_length)

Sets the damping length.

Parameters:
-----------

damping_length: 
the damping (coherence) length of the paracrystal in nanometers 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::domainSizes "std::vector< double > InterferenceFunction2DParaCrystal::domainSizes() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setIntegrationOverXi "void InterferenceFunction2DParaCrystal::setIntegrationOverXi(bool integrate_xi)

Enables/disables averaging over the lattice rotation angle.

Parameters:
-----------

integrate_xi: 
integration flag 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::integrationOverXi "bool InterferenceFunction2DParaCrystal::integrationOverXi() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::dampingLength "double InterferenceFunction2DParaCrystal::dampingLength() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::lattice "const Lattice2D & InterferenceFunction2DParaCrystal::lattice() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getParticleDensity "double InterferenceFunction2DParaCrystal::getParticleDensity() const override final

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getChildren "std::vector< const INode * > InterferenceFunction2DParaCrystal::getChildren() const override final

Returns a vector of children (const). 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::pdf1 "const IFTDistribution2D* InterferenceFunction2DParaCrystal::pdf1() const
";

%feature("docstring")  InterferenceFunction2DParaCrystal::pdf2 "const IFTDistribution2D* InterferenceFunction2DParaCrystal::pdf2() const
";


// File: classInterferenceFunction2DSuperLattice.xml
%feature("docstring") InterferenceFunction2DSuperLattice "

Interference function of a 2D superlattice with a configurable interference function for each lattice site.

C++ includes: InterferenceFunction2DSuperLattice.h
";

%feature("docstring")  InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice "InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(const Lattice2D &lattice, unsigned size_1, unsigned size_2)
";

%feature("docstring")  InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice "InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(double length_1, double length_2, double alpha, double xi, unsigned size_1, unsigned size_2)

Constructor of two-dimensional interference function.

Parameters:
-----------

length_1: 
length of first lattice vector in nanometers

length_2: 
length of second lattice vector in nanometers

alpha: 
angle between lattice vectors in radians

xi: 
rotation of lattice with respect to x-axis (beam direction) in radians 
";

%feature("docstring")  InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice "InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice() final
";

%feature("docstring")  InterferenceFunction2DSuperLattice::clone "InterferenceFunction2DSuperLattice * InterferenceFunction2DSuperLattice::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction2DSuperLattice::accept "void InterferenceFunction2DSuperLattice::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction2DSuperLattice::setSubstructureIFF "void InterferenceFunction2DSuperLattice::setSubstructureIFF(const IInterferenceFunction &sub_iff)
";

%feature("docstring")  InterferenceFunction2DSuperLattice::substructureIFF "const IInterferenceFunction & InterferenceFunction2DSuperLattice::substructureIFF() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::evaluate "double InterferenceFunction2DSuperLattice::evaluate(const kvector_t q, double outer_iff=1.0) const override final

Evaluates the interference function for a given wavevector transfer. 
";

%feature("docstring")  InterferenceFunction2DSuperLattice::domainSize1 "unsigned InterferenceFunction2DSuperLattice::domainSize1() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::domainSize2 "unsigned InterferenceFunction2DSuperLattice::domainSize2() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::setIntegrationOverXi "void InterferenceFunction2DSuperLattice::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunction2DSuperLattice::integrationOverXi "bool InterferenceFunction2DSuperLattice::integrationOverXi() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::lattice "const Lattice2D & InterferenceFunction2DSuperLattice::lattice() const
";

%feature("docstring")  InterferenceFunction2DSuperLattice::getChildren "std::vector< const INode * > InterferenceFunction2DSuperLattice::getChildren() const override final

Returns a vector of children (const). 
";


// File: classInterferenceFunction3DLattice.xml
%feature("docstring") InterferenceFunction3DLattice "

Interference function of a 3D lattice.

C++ includes: InterferenceFunction3DLattice.h
";

%feature("docstring")  InterferenceFunction3DLattice::InterferenceFunction3DLattice "InterferenceFunction3DLattice::InterferenceFunction3DLattice(const Lattice &lattice)
";

%feature("docstring")  InterferenceFunction3DLattice::~InterferenceFunction3DLattice "InterferenceFunction3DLattice::~InterferenceFunction3DLattice() final
";

%feature("docstring")  InterferenceFunction3DLattice::clone "InterferenceFunction3DLattice * InterferenceFunction3DLattice::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction3DLattice::accept "void InterferenceFunction3DLattice::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction3DLattice::setPeakShape "void InterferenceFunction3DLattice::setPeakShape(const IPeakShape &peak_shape)
";

%feature("docstring")  InterferenceFunction3DLattice::lattice "const Lattice & InterferenceFunction3DLattice::lattice() const
";

%feature("docstring")  InterferenceFunction3DLattice::supportsMultilayer "bool InterferenceFunction3DLattice::supportsMultilayer() const override final

Indicates if this interference function can be used with a multilayer (DWBA mode) 
";

%feature("docstring")  InterferenceFunction3DLattice::getChildren "std::vector< const INode * > InterferenceFunction3DLattice::getChildren() const override final

Returns a vector of children (const). 
";

%feature("docstring")  InterferenceFunction3DLattice::onChange "void InterferenceFunction3DLattice::onChange() override final

Action to be taken in inherited class when a parameter has changed. 
";


// File: classInterferenceFunctionFinite2DLattice.xml
%feature("docstring") InterferenceFunctionFinite2DLattice "

Interference function of a finite 2D lattice.

C++ includes: InterferenceFunctionFinite2DLattice.h
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice "InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice(const Lattice2D &lattice, unsigned N_1, unsigned N_2)

Constructor of two-dimensional finite lattice interference function.

Parameters:
-----------

lattice: 
object specifying a 2d lattice structure

N_1: 
number of lattice cells in the first lattice direction

N_2: 
number of lattice cells in the second lattice direction 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice "InterferenceFunctionFinite2DLattice::InterferenceFunctionFinite2DLattice(double length_1, double length_2, double alpha, double xi, unsigned N_1, unsigned N_2)

Constructor of two-dimensional finite lattice interference function.

Parameters:
-----------

length_1: 
length of first lattice vector in nanometers

length_2: 
length of second lattice vector in nanometers

alpha: 
angle between lattice vectors in radians

xi: 
rotation of lattice with respect to x-axis (beam direction) in radians

N_1: 
number of lattice cells in the first lattice direction

N_2: 
number of lattice cells in the second lattice direction 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::~InterferenceFunctionFinite2DLattice "InterferenceFunctionFinite2DLattice::~InterferenceFunctionFinite2DLattice() final
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::clone "InterferenceFunctionFinite2DLattice * InterferenceFunctionFinite2DLattice::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::accept "void InterferenceFunctionFinite2DLattice::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::numberUnitCells1 "unsigned InterferenceFunctionFinite2DLattice::numberUnitCells1() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::numberUnitCells2 "unsigned InterferenceFunctionFinite2DLattice::numberUnitCells2() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::setIntegrationOverXi "void InterferenceFunctionFinite2DLattice::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::integrationOverXi "bool InterferenceFunctionFinite2DLattice::integrationOverXi() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::lattice "const Lattice2D & InterferenceFunctionFinite2DLattice::lattice() const
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::getParticleDensity "double InterferenceFunctionFinite2DLattice::getParticleDensity() const override final

Returns the particle density associated with this 2d lattice. 
";

%feature("docstring")  InterferenceFunctionFinite2DLattice::getChildren "std::vector< const INode * > InterferenceFunctionFinite2DLattice::getChildren() const override final

Returns a vector of children (const). 
";


// File: classInterferenceFunctionFinite3DLattice.xml
%feature("docstring") InterferenceFunctionFinite3DLattice "

Interference function of a finite 3D lattice.

C++ includes: InterferenceFunctionFinite3DLattice.h
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::InterferenceFunctionFinite3DLattice "InterferenceFunctionFinite3DLattice::InterferenceFunctionFinite3DLattice(const Lattice &lattice, unsigned N_1, unsigned N_2, unsigned N_3)

Constructor of three-dimensional finite lattice interference function.

Parameters:
-----------

lattice: 
object specifying a 2d lattice structure

N_1: 
number of lattice cells in the first lattice direction

N_2: 
number of lattice cells in the second lattice direction 
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::~InterferenceFunctionFinite3DLattice "InterferenceFunctionFinite3DLattice::~InterferenceFunctionFinite3DLattice() final
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::clone "InterferenceFunctionFinite3DLattice * InterferenceFunctionFinite3DLattice::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::accept "void InterferenceFunctionFinite3DLattice::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::numberUnitCells1 "unsigned InterferenceFunctionFinite3DLattice::numberUnitCells1() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::numberUnitCells2 "unsigned InterferenceFunctionFinite3DLattice::numberUnitCells2() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::numberUnitCells3 "unsigned InterferenceFunctionFinite3DLattice::numberUnitCells3() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::lattice "const Lattice & InterferenceFunctionFinite3DLattice::lattice() const
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::supportsMultilayer "bool InterferenceFunctionFinite3DLattice::supportsMultilayer() const override final

Indicates if this interference function can be used with a multilayer (DWBA mode) 
";

%feature("docstring")  InterferenceFunctionFinite3DLattice::getChildren "std::vector< const INode * > InterferenceFunctionFinite3DLattice::getChildren() const override final

Returns a vector of children (const). 
";


// File: classInterferenceFunctionHardDisk.xml
%feature("docstring") InterferenceFunctionHardDisk "

Percus-Yevick hard disk interference function.

M.S. Ripoll & C.F. Tejero (1995) Approximate analytical expression for the direct correlation function of hard discs within the Percus-Yevick equation, Molecular Physics, 85:2, 423-428, DOI: 10.1080/00268979500101211

C++ includes: InterferenceFunctionHardDisk.h
";

%feature("docstring")  InterferenceFunctionHardDisk::InterferenceFunctionHardDisk "InterferenceFunctionHardDisk::InterferenceFunctionHardDisk(double radius, double density)
";

%feature("docstring")  InterferenceFunctionHardDisk::~InterferenceFunctionHardDisk "InterferenceFunctionHardDisk::~InterferenceFunctionHardDisk() final
";

%feature("docstring")  InterferenceFunctionHardDisk::clone "InterferenceFunctionHardDisk * InterferenceFunctionHardDisk::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionHardDisk::accept "void InterferenceFunctionHardDisk::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionHardDisk::getParticleDensity "double InterferenceFunctionHardDisk::getParticleDensity() const override final

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";

%feature("docstring")  InterferenceFunctionHardDisk::radius "double InterferenceFunctionHardDisk::radius() const
";

%feature("docstring")  InterferenceFunctionHardDisk::density "double InterferenceFunctionHardDisk::density() const
";


// File: classInterferenceFunctionNone.xml
%feature("docstring") InterferenceFunctionNone "

Default interference function (i.e. absence of any interference).

C++ includes: InterferenceFunctionNone.h
";

%feature("docstring")  InterferenceFunctionNone::InterferenceFunctionNone "InterferenceFunctionNone::InterferenceFunctionNone()
";

%feature("docstring")  InterferenceFunctionNone::clone "InterferenceFunctionNone * InterferenceFunctionNone::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionNone::accept "void InterferenceFunctionNone::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";


// File: classInterferenceFunctionRadialParaCrystal.xml
%feature("docstring") InterferenceFunctionRadialParaCrystal "

Interference function of radial paracrystal.

C++ includes: InterferenceFunctionRadialParaCrystal.h
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal "InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal(double peak_distance, double damping_length=0.0)

Constructor of interference function of radial paracrystal.

Parameters:
-----------

peak_distance: 
average distance to the next neighbor in nanometers

damping_length: 
the damping (coherence) length of the paracrystal in nanometers 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::clone "InterferenceFunctionRadialParaCrystal * InterferenceFunctionRadialParaCrystal::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::accept "void InterferenceFunctionRadialParaCrystal::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setKappa "void InterferenceFunctionRadialParaCrystal::setKappa(double kappa)

Sets size spacing coupling parameter of the Size Spacing Correlation Approximation.

Parameters:
-----------

size: 
spacing coupling parameter 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::kappa "double InterferenceFunctionRadialParaCrystal::kappa() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setDomainSize "void InterferenceFunctionRadialParaCrystal::setDomainSize(double size)

Sets domain size (finite size corrections).

Parameters:
-----------

size: 
size of coherence domain along the lattice main axis in nanometers 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::domainSize "double InterferenceFunctionRadialParaCrystal::domainSize() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::FTPDF "complex_t InterferenceFunctionRadialParaCrystal::FTPDF(double qpar) const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setProbabilityDistribution "void InterferenceFunctionRadialParaCrystal::setProbabilityDistribution(const IFTDistribution1D &pdf)

Sets one-dimensional probability distribution.

Parameters:
-----------

pdf: 
probability distribution (Fourier transform of probability density) 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::peakDistance "double InterferenceFunctionRadialParaCrystal::peakDistance() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::dampingLength "double InterferenceFunctionRadialParaCrystal::dampingLength() const
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getChildren "std::vector< const INode * > InterferenceFunctionRadialParaCrystal::getChildren() const override final

Returns a vector of children (const). 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::randomSample "double InterferenceFunctionRadialParaCrystal::randomSample() const
";


// File: classInterferenceFunctionTwin.xml
%feature("docstring") InterferenceFunctionTwin "

Interference function for two particles at a mean distance and given standard deviation from each other in a given direction.

C++ includes: InterferenceFunctionTwin.h
";

%feature("docstring")  InterferenceFunctionTwin::InterferenceFunctionTwin "InterferenceFunctionTwin::InterferenceFunctionTwin(const kvector_t &direction, double mean_distance, double std_dev)
";

%feature("docstring")  InterferenceFunctionTwin::clone "InterferenceFunctionTwin * InterferenceFunctionTwin::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionTwin::accept "void InterferenceFunctionTwin::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionTwin::direction "kvector_t InterferenceFunctionTwin::direction() const
";

%feature("docstring")  InterferenceFunctionTwin::meanDistance "double InterferenceFunctionTwin::meanDistance() const
";

%feature("docstring")  InterferenceFunctionTwin::stdDev "double InterferenceFunctionTwin::stdDev() const
";


// File: classIObservable.xml
%feature("docstring") IObservable "

Observable interface from Observer pattern

C++ includes: IObserver.h
";

%feature("docstring")  IObservable::~IObservable "IObservable::~IObservable()
";

%feature("docstring")  IObservable::attachObserver "void IObservable::attachObserver(observer_t obj)

attach observer to the list of observers 
";

%feature("docstring")  IObservable::notifyObservers "void IObservable::notifyObservers()

notify observers about change in status 
";


// File: classIObserver.xml
%feature("docstring") IObserver "

Observer interface from Observer pattern.

C++ includes: IObserver.h
";

%feature("docstring")  IObserver::~IObserver "IObserver::~IObserver()
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

Strategy interface to write OututData in file

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

%feature("docstring")  IParameter::IParameter "IParameter< T >::IParameter(const std::string &name, T *data, const std::string &parent_name, const std::function< void()> &onChange)
";

%feature("docstring")  IParameter::clone "virtual IParameter* IParameter< T >::clone(const std::string &new_name=\"\") const =0
";

%feature("docstring")  IParameter::isNull "virtual bool IParameter< T >::isNull() const

Returns true if wrapped parameter was not initialized with proper real value. 
";

%feature("docstring")  IParameter::getData "T& IParameter< T >::getData() const
";

%feature("docstring")  IParameter::setData "void IParameter< T >::setData(T &data)
";

%feature("docstring")  IParameter::hasSameData "bool IParameter< T >::hasSameData(const IParameter &other)

Returns true if two parameters are pointing to the same raw data. 
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

%feature("docstring")  IParameterized::~IParameterized "IParameterized::~IParameterized()
";

%feature("docstring")  IParameterized::parameterPool "ParameterPool* IParameterized::parameterPool() const

Returns pointer to the parameter pool. 
";

%feature("docstring")  IParameterized::createParameterTree "ParameterPool * IParameterized::createParameterTree() const

Creates new parameter pool, with all local parameters and those of its children. 
";

%feature("docstring")  IParameterized::parametersToString "std::string IParameterized::parametersToString() const

Returns multiline string representing available parameters. 
";

%feature("docstring")  IParameterized::registerParameter "RealParameter & IParameterized::registerParameter(const std::string &name, double *parpointer)
";

%feature("docstring")  IParameterized::registerVector "void IParameterized::registerVector(const std::string &base_name, kvector_t *p_vec, const std::string &units=BornAgain::UnitsNm)
";

%feature("docstring")  IParameterized::setParameterValue "void IParameterized::setParameterValue(const std::string &name, double value)
";

%feature("docstring")  IParameterized::setVectorValue "void IParameterized::setVectorValue(const std::string &base_name, kvector_t value)
";

%feature("docstring")  IParameterized::parameter "RealParameter * IParameterized::parameter(const std::string &name) const

Returns parameter with given 'name'. 
";

%feature("docstring")  IParameterized::onChange "virtual void IParameterized::onChange()

Action to be taken in inherited class when a parameter has changed. 
";

%feature("docstring")  IParameterized::removeParameter "void IParameterized::removeParameter(const std::string &name)
";

%feature("docstring")  IParameterized::removeVector "void IParameterized::removeVector(const std::string &base_name)
";


// File: classIParticle.xml
%feature("docstring") IParticle "

Pure virtual base class for  Particle,  ParticleComposition,  ParticleCoreShell,  MesoCrystal. Provides position/rotation and form factor. Abundance is inherited from  IAbstractParticle.

C++ includes: IParticle.h
";

%feature("docstring")  IParticle::~IParticle "IParticle::~IParticle()
";

%feature("docstring")  IParticle::clone "IParticle* IParticle::clone() const override=0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IParticle::accept "void IParticle::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IParticle::createFormFactor "IFormFactor * IParticle::createFormFactor() const

Create a form factor for this particle. 
";

%feature("docstring")  IParticle::createSlicedParticle "SlicedParticle IParticle::createSlicedParticle(ZLimits limits) const

Create a sliced form factor for this particle. 
";

%feature("docstring")  IParticle::position "kvector_t IParticle::position() const

Returns particle position. 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(kvector_t position)

Sets relative position of the particle's reference point in the coordinate system of parent.

Parameters:
-----------

position: 
relative position vector (components are in nanometers) 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(double x, double y, double z)

Sets relative position of the particle's reference point in the coordinate system of parent.

Parameters:
-----------

x: 
x-coordinate in nanometers

y: 
y-coordinate in nanometers

z: 
z-coordinate in nanometers 
";

%feature("docstring")  IParticle::translate "void IParticle::translate(kvector_t translation) override final

Translates the particle. 
";

%feature("docstring")  IParticle::rotation "const IRotation * IParticle::rotation() const

Returns rotation object. 
";

%feature("docstring")  IParticle::setRotation "void IParticle::setRotation(const IRotation &rotation)

Sets transformation. 
";

%feature("docstring")  IParticle::rotate "void IParticle::rotate(const IRotation &rotation) override final

Rotates the particle. 
";

%feature("docstring")  IParticle::getChildren "std::vector< const INode * > IParticle::getChildren() const override

Returns a vector of children (const). 
";

%feature("docstring")  IParticle::registerAbundance "void IParticle::registerAbundance(bool make_registered=true)
";

%feature("docstring")  IParticle::registerPosition "void IParticle::registerPosition(bool make_registered=true)

Registers the three components of its position. 
";

%feature("docstring")  IParticle::decompose "SafePointerVector< IParticle > IParticle::decompose() const

Decompose in constituent  IParticle objects. 
";

%feature("docstring")  IParticle::bottomTopZ "ParticleLimits IParticle::bottomTopZ() const

Top and bottom z-coordinate. 
";


// File: classIPeakShape.xml
%feature("docstring") IPeakShape "

Pure virtual interface class that defines the peak shape of a Bragg peak.

C++ includes: IPeakShape.h
";

%feature("docstring")  IPeakShape::~IPeakShape "IPeakShape::~IPeakShape()
";

%feature("docstring")  IPeakShape::clone "virtual IPeakShape* IPeakShape::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IPeakShape::evaluate "virtual double IPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const =0

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  IPeakShape::angularDisorder "virtual bool IPeakShape::angularDisorder() const

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classIPixel.xml
%feature("docstring") IPixel "

Interface for a function that maps [0,1]x[0,1] to the kvectors in a pixel.

C++ includes: IPixel.h
";

%feature("docstring")  IPixel::~IPixel "virtual IPixel::~IPixel()
";

%feature("docstring")  IPixel::clone "virtual IPixel* IPixel::clone() const =0
";

%feature("docstring")  IPixel::createZeroSizePixel "virtual IPixel* IPixel::createZeroSizePixel(double x, double y) const =0
";

%feature("docstring")  IPixel::getK "virtual kvector_t IPixel::getK(double x, double y, double wavelength) const =0
";

%feature("docstring")  IPixel::getIntegrationFactor "virtual double IPixel::getIntegrationFactor(double x, double y) const =0
";

%feature("docstring")  IPixel::getSolidAngle "virtual double IPixel::getSolidAngle() const =0
";


// File: classIRegistry.xml
%feature("docstring") IRegistry "

Templated object registry.

C++ includes: IRegistry.h
";

%feature("docstring")  IRegistry::getItem "const ValueType* IRegistry< ValueType >::getItem(const std::string &key) const
";

%feature("docstring")  IRegistry::keys "std::vector<std::string> IRegistry< ValueType >::keys()
";

%feature("docstring")  IRegistry::size "size_t IRegistry< ValueType >::size() const
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

Pure virtual interface for rotations.

C++ includes: Rotations.h
";

%feature("docstring")  IRotation::~IRotation "virtual IRotation::~IRotation()
";

%feature("docstring")  IRotation::clone "virtual IRotation* IRotation::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IRotation::createInverse "virtual IRotation* IRotation::createInverse() const =0

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  IRotation::accept "void IRotation::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IRotation::getTransform3D "virtual Transform3D IRotation::getTransform3D() const =0

Returns transformation. 
";

%feature("docstring")  IRotation::isIdentity "bool IRotation::isIdentity() const

Returns true if rotation matrix is identity matrix (no rotations) 
";


// File: classISample.xml
%feature("docstring") ISample "

Pure virtual base class for sample components and properties related to scattering.

C++ includes: ISample.h
";

%feature("docstring")  ISample::clone "ISample* ISample::clone() const override=0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ISample::material "virtual const Material* ISample::material() const

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  ISample::containedMaterials "std::vector< const Material * > ISample::containedMaterials() const

Returns set of unique materials contained in this  ISample. 
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

%feature("docstring")  IsGISAXSDetector::accept "void IsGISAXSDetector::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";


// File: classIShape.xml
%feature("docstring") IShape "

Pure virtual base class for different shapes.

In contrast to the form factors, these shapes only provide an intereface for returning a set of vertices.

C++ includes: IShape.h
";

%feature("docstring")  IShape::IShape "IShape::IShape()
";

%feature("docstring")  IShape::~IShape "virtual IShape::~IShape()
";

%feature("docstring")  IShape::vertices "std::vector< kvector_t > IShape::vertices() const

Retrieves a list of the vertices constituting this concrete shape. 
";


// File: classIShape2D.xml
%feature("docstring") IShape2D "

Basic class for all shapes in 2D.

C++ includes: IShape2D.h
";

%feature("docstring")  IShape2D::IShape2D "IShape2D::IShape2D(const std::string &name)
";

%feature("docstring")  IShape2D::clone "virtual IShape2D* IShape2D::clone() const =0
";

%feature("docstring")  IShape2D::contains "virtual bool IShape2D::contains(double x, double y) const =0

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  IShape2D::contains "virtual bool IShape2D::contains(const Bin1D &binx, const Bin1D &biny) const =0

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";


// File: classISingleton.xml
%feature("docstring") ISingleton "

Base class for singletons.

C++ includes: ISingleton.h
";


// File: classIsotropicGaussPeakShape.xml
%feature("docstring") IsotropicGaussPeakShape "

Class that implements an isotropic Gaussian peak shape of a Bragg peak.

C++ includes: IPeakShape.h
";

%feature("docstring")  IsotropicGaussPeakShape::IsotropicGaussPeakShape "IsotropicGaussPeakShape::IsotropicGaussPeakShape(double max_intensity, double domainsize)
";

%feature("docstring")  IsotropicGaussPeakShape::~IsotropicGaussPeakShape "IsotropicGaussPeakShape::~IsotropicGaussPeakShape() override
";

%feature("docstring")  IsotropicGaussPeakShape::clone "IsotropicGaussPeakShape * IsotropicGaussPeakShape::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  IsotropicGaussPeakShape::accept "void IsotropicGaussPeakShape::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IsotropicGaussPeakShape::evaluate "double IsotropicGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";


// File: classIsotropicLorentzPeakShape.xml
%feature("docstring") IsotropicLorentzPeakShape "

Class that implements an isotropic Lorentzian peak shape of a Bragg peak.

C++ includes: IPeakShape.h
";

%feature("docstring")  IsotropicLorentzPeakShape::IsotropicLorentzPeakShape "IsotropicLorentzPeakShape::IsotropicLorentzPeakShape(double max_intensity, double domainsize)
";

%feature("docstring")  IsotropicLorentzPeakShape::~IsotropicLorentzPeakShape "IsotropicLorentzPeakShape::~IsotropicLorentzPeakShape() override
";

%feature("docstring")  IsotropicLorentzPeakShape::clone "IsotropicLorentzPeakShape * IsotropicLorentzPeakShape::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  IsotropicLorentzPeakShape::accept "void IsotropicLorentzPeakShape::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  IsotropicLorentzPeakShape::evaluate "double IsotropicLorentzPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";


// File: classISpecularScan.xml
%feature("docstring") ISpecularScan "

Base abstract class for all types of specular scans.

C++ includes: ISpecularScan.h
";

%feature("docstring")  ISpecularScan::ISpecularScan "ISpecularScan::ISpecularScan(SPECULAR_DATA_TYPE data_type)
";

%feature("docstring")  ISpecularScan::~ISpecularScan "ISpecularScan::~ISpecularScan() override
";

%feature("docstring")  ISpecularScan::clone "ISpecularScan* ISpecularScan::clone() const override=0
";

%feature("docstring")  ISpecularScan::generateSimulationElements "virtual std::vector<SpecularSimulationElement> ISpecularScan::generateSimulationElements() const =0

Generates simulation elements for specular simulations. 
";

%feature("docstring")  ISpecularScan::coordinateAxis "virtual const IAxis* ISpecularScan::coordinateAxis() const =0

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  ISpecularScan::footprintFactor "virtual const IFootprintFactor* ISpecularScan::footprintFactor() const =0

Returns  IFootprintFactor object pointer. 
";

%feature("docstring")  ISpecularScan::footprint "virtual std::vector<double> ISpecularScan::footprint(size_t i, size_t n_elements) const =0

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  ISpecularScan::numberOfSimulationElements "virtual size_t ISpecularScan::numberOfSimulationElements() const =0

Returns the number of simulation elements. 
";

%feature("docstring")  ISpecularScan::createIntensities "virtual std::vector<double> ISpecularScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const =0

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  ISpecularScan::print "virtual std::string ISpecularScan::print() const =0

Print scan definition in python format. 
";

%feature("docstring")  ISpecularScan::dataType "SPECULAR_DATA_TYPE ISpecularScan::dataType() const
";


// File: classISpecularStrategy.xml
%feature("docstring") ISpecularStrategy "";

%feature("docstring")  ISpecularStrategy::~ISpecularStrategy "virtual ISpecularStrategy::~ISpecularStrategy()=default
";

%feature("docstring")  ISpecularStrategy::Execute "virtual coeffs_t ISpecularStrategy::Execute(const std::vector< Slice > &slices, const kvector_t &k) const =0
";

%feature("docstring")  ISpecularStrategy::Execute "virtual coeffs_t ISpecularStrategy::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const =0
";


// File: classIterationInfo.xml
%feature("docstring") IterationInfo "

Stores fit iteration info to track fit flow from various observers. Used in context of  FitObjective.

C++ includes: IterationInfo.h
";

%feature("docstring")  IterationInfo::IterationInfo "IterationInfo::IterationInfo()
";

%feature("docstring")  IterationInfo::update "void IterationInfo::update(const Fit::Parameters &params, double chi2)
";

%feature("docstring")  IterationInfo::iterationCount "unsigned IterationInfo::iterationCount() const

Returns current number of minimizer iterations. 
";

%feature("docstring")  IterationInfo::chi2 "double IterationInfo::chi2() const
";

%feature("docstring")  IterationInfo::parameters "Fit::Parameters IterationInfo::parameters() const
";

%feature("docstring")  IterationInfo::parameterMap "std::map< std::string, double > IterationInfo::parameterMap() const

Returns map of fit parameter names and its current values. 
";


// File: classIterationStrategy.xml
%feature("docstring") IterationStrategy "

Abstract base class for tree traversal strategies, for use in  INodeVisitor.

For definition of different strategies see https://en.wikipedia.org/wiki/Tree_traversal.

C++ includes: IterationStrategy.h
";

%feature("docstring")  IterationStrategy::~IterationStrategy "virtual IterationStrategy::~IterationStrategy()
";

%feature("docstring")  IterationStrategy::clone "virtual IterationStrategy* IterationStrategy::clone() const =0
";

%feature("docstring")  IterationStrategy::first "virtual IteratorMemento IterationStrategy::first(const INode *p_root)=0
";

%feature("docstring")  IterationStrategy::next "virtual void IterationStrategy::next(IteratorMemento &iterator_stack) const =0
";

%feature("docstring")  IterationStrategy::isDone "virtual bool IterationStrategy::isDone(IteratorMemento &iterator_stack) const =0
";


// File: classIteratorMemento.xml
%feature("docstring") IteratorMemento "

Holds all iterator states encountered for SampleTreeIterator.

C++ includes: NodeIterator.h
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

%feature("docstring")  IteratorMemento::getCurrent "const INode* IteratorMemento::getCurrent()
";

%feature("docstring")  IteratorMemento::next "void IteratorMemento::next()
";

%feature("docstring")  IteratorMemento::size "size_t IteratorMemento::size() const
";


// File: classIteratorState.xml
%feature("docstring") IteratorState "

Holds state of iterator at single level for SampleTreeIterator.

C++ includes: NodeIterator.h
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(const INode *single_element)
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(std::vector< const INode * > samples)
";

%feature("docstring")  IteratorState::~IteratorState "virtual IteratorState::~IteratorState()
";

%feature("docstring")  IteratorState::getCurrent "const INode* IteratorState::getCurrent() const
";

%feature("docstring")  IteratorState::isEnd "bool IteratorState::isEnd() const
";

%feature("docstring")  IteratorState::next "void IteratorState::next()
";


// File: classIUnitConverter.xml
%feature("docstring") IUnitConverter "

Interface to provide axis translations to different units for simulation output

C++ includes: IUnitConverter.h
";

%feature("docstring")  IUnitConverter::~IUnitConverter "IUnitConverter::~IUnitConverter()
";

%feature("docstring")  IUnitConverter::clone "virtual IUnitConverter* IUnitConverter::clone() const =0
";

%feature("docstring")  IUnitConverter::dimension "virtual size_t IUnitConverter::dimension() const =0
";

%feature("docstring")  IUnitConverter::calculateMin "virtual double IUnitConverter::calculateMin(size_t i_axis, AxesUnits units_type) const =0
";

%feature("docstring")  IUnitConverter::calculateMax "virtual double IUnitConverter::calculateMax(size_t i_axis, AxesUnits units_type) const =0
";

%feature("docstring")  IUnitConverter::axisSize "virtual size_t IUnitConverter::axisSize(size_t i_axis) const =0
";

%feature("docstring")  IUnitConverter::axisName "std::string IUnitConverter::axisName(size_t i_axis, AxesUnits units_type=AxesUnits::DEFAULT) const
";

%feature("docstring")  IUnitConverter::availableUnits "virtual std::vector<AxesUnits> IUnitConverter::availableUnits() const =0
";

%feature("docstring")  IUnitConverter::defaultUnits "virtual AxesUnits IUnitConverter::defaultUnits() const =0
";

%feature("docstring")  IUnitConverter::createConvertedAxis "virtual std::unique_ptr<IAxis> IUnitConverter::createConvertedAxis(size_t i_axis, AxesUnits units) const =0
";

%feature("docstring")  IUnitConverter::createConvertedData "std::unique_ptr< OutputData< double > > IUnitConverter::createConvertedData(const OutputData< double > &data, AxesUnits units) const

Creates  OutputData array in converter units. 
";


// File: classIVarianceFunction.xml
%feature("docstring") IVarianceFunction "

Variance function interface.

C++ includes: VarianceFunctions.h
";

%feature("docstring")  IVarianceFunction::IVarianceFunction "IVarianceFunction::IVarianceFunction()
";

%feature("docstring")  IVarianceFunction::~IVarianceFunction "IVarianceFunction::~IVarianceFunction()
";

%feature("docstring")  IVarianceFunction::clone "virtual IVarianceFunction* IVarianceFunction::clone() const =0
";

%feature("docstring")  IVarianceFunction::variance "virtual double IVarianceFunction::variance(double real_value, double simulated_value) const =0
";

%feature("docstring")  IVarianceFunction::IVarianceFunction "IVarianceFunction::IVarianceFunction(const IVarianceFunction &)=delete
";


// File: classLabelMap.xml
%feature("docstring") LabelMap "";


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

%feature("docstring")  Lattice::Lattice "Lattice::Lattice()
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice(const kvector_t a1, const kvector_t a2, const kvector_t a3)
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice(const Lattice &lattice)
";

%feature("docstring")  Lattice::~Lattice "Lattice::~Lattice() override
";

%feature("docstring")  Lattice::accept "void Lattice::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  Lattice::resetBasis "void Lattice::resetBasis(const kvector_t a1, const kvector_t a2, const kvector_t a3)

Resets the basis vectors. 
";

%feature("docstring")  Lattice::getMillerDirection "kvector_t Lattice::getMillerDirection(double h, double k, double l) const

Returns normalized direction corresponding to the given Miller indices. 
";

%feature("docstring")  Lattice::volume "double Lattice::volume() const

Returns the volume of the unit cell. 
";

%feature("docstring")  Lattice::getReciprocalLatticeBasis "void Lattice::getReciprocalLatticeBasis(kvector_t &b1, kvector_t &b2, kvector_t &b3) const

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

%feature("docstring")  Lattice::onChange "void Lattice::onChange() override

Action to be taken in inherited class when a parameter has changed. 
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
 Lattice rotation angle. 
";


// File: classLattice2D.xml
%feature("docstring") Lattice2D "";

%feature("docstring")  Lattice2D::Lattice2D "Lattice2D::Lattice2D(double rotation_angle=0.0)
";

%feature("docstring")  Lattice2D::clone "Lattice2D* Lattice2D::clone() const =0
";

%feature("docstring")  Lattice2D::length1 "virtual double Lattice2D::length1() const =0
";

%feature("docstring")  Lattice2D::length2 "virtual double Lattice2D::length2() const =0
";

%feature("docstring")  Lattice2D::latticeAngle "virtual double Lattice2D::latticeAngle() const =0
";

%feature("docstring")  Lattice2D::unitCellArea "virtual double Lattice2D::unitCellArea() const =0
";

%feature("docstring")  Lattice2D::rotationAngle "double Lattice2D::rotationAngle() const
";

%feature("docstring")  Lattice2D::reciprocalBases "Lattice2D::ReciprocalBases Lattice2D::reciprocalBases() const
";

%feature("docstring")  Lattice2D::setRotationEnabled "void Lattice2D::setRotationEnabled(bool enabled)
";


// File: classLayer.xml
%feature("docstring") Layer "

A layer, with thickness (in nanometer) and material.

C++ includes: Layer.h
";

%feature("docstring")  Layer::Layer "Layer::Layer(Material material, double thickness=0)

Constructor of a layer with thickness and material

Parameters:
-----------

material: 
material the layer is made of

thickness: 
thickness of a layer in nanometers 
";

%feature("docstring")  Layer::~Layer "Layer::~Layer() override
";

%feature("docstring")  Layer::clone "Layer * Layer::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  Layer::accept "void Layer::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  Layer::setThickness "void Layer::setThickness(double thickness)

Sets layer thickness in nanometers. 
";

%feature("docstring")  Layer::thickness "double Layer::thickness() const
";

%feature("docstring")  Layer::material "const Material* Layer::material() const override final

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Layer::setMaterial "void Layer::setMaterial(Material material)
";

%feature("docstring")  Layer::addLayout "void Layer::addLayout(const ILayout &decoration)
";

%feature("docstring")  Layer::numberOfLayouts "size_t Layer::numberOfLayouts() const
";

%feature("docstring")  Layer::layouts "std::vector< const ILayout * > Layer::layouts() const
";

%feature("docstring")  Layer::getChildren "std::vector< const INode * > Layer::getChildren() const override final

Returns a vector of children (const). 
";

%feature("docstring")  Layer::registerThickness "void Layer::registerThickness(bool make_registered=true)
";

%feature("docstring")  Layer::setNumberOfSlices "void Layer::setNumberOfSlices(unsigned int n_slices)
";

%feature("docstring")  Layer::numberOfSlices "unsigned int Layer::numberOfSlices() const
";


// File: classLayerFillLimits.xml
%feature("docstring") LayerFillLimits "

Helper class for the graded layer approximation. Generates limits for each layer, indicating the region of the layer (along z) that contains particle(s)

The constructor takes the bottom layer z-coordinates as parameter. This means that for N layers, only N-1 coordinates need to be passed (the last layer is assumed to be semi-infinite).

C++ includes: LayerFillLimits.h
";

%feature("docstring")  LayerFillLimits::LayerFillLimits "LayerFillLimits::LayerFillLimits(std::vector< double > layers_bottomz)
";

%feature("docstring")  LayerFillLimits::update "void LayerFillLimits::update(ParticleLimits particle_limits, double offset=0.0)

Particle limits are given in global coordinates. 
";

%feature("docstring")  LayerFillLimits::layerZLimits "std::vector< ZLimits > LayerFillLimits::layerZLimits() const

Returns the filled region limits for each layer (in local layer coordinates) 
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

%feature("docstring")  LayerInterface::accept "virtual void LayerInterface::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  LayerInterface::setRoughness "void LayerInterface::setRoughness(const LayerRoughness &roughness)

Sets roughness of the interface. 
";

%feature("docstring")  LayerInterface::getRoughness "const LayerRoughness * LayerInterface::getRoughness() const

Returns roughness of the interface. 
";

%feature("docstring")  LayerInterface::topLayer "const Layer * LayerInterface::topLayer() const
";

%feature("docstring")  LayerInterface::bottomLayer "const Layer * LayerInterface::bottomLayer() const
";

%feature("docstring")  LayerInterface::getChildren "std::vector< const INode * > LayerInterface::getChildren() const

Returns a vector of children (const). 
";


// File: classLayerRoughness.xml
%feature("docstring") LayerRoughness "

A roughness of interface between two layers.

Based on the article D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995 \"X-ray reflection and transmission by rough surfaces\"

C++ includes: LayerRoughness.h
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness()
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength)

Constructor of layer roughness.

Parameters:
-----------

sigma: 
rms of the roughness in nanometers

hurstParameter: 
hurst parameter which describes how jagged the interface, dimensionless [0.0, 1.0], where 0.0 gives more spikes, 1.0 more smoothness

lateralCorrLength: 
lateral correlation length of the roughness in nanometers 
";

%feature("docstring")  LayerRoughness::clone "LayerRoughness* LayerRoughness::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  LayerRoughness::accept "virtual void LayerRoughness::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  LayerRoughness::setLatteralCorrLength "void LayerRoughness::setLatteralCorrLength(double lateralCorrLength)

Sets lateral correlation length. 
";

%feature("docstring")  LayerRoughness::getLatteralCorrLength "double LayerRoughness::getLatteralCorrLength() const

Returns lateral correlation length. 
";


// File: classLayersWithAbsorptionBuilder.xml
%feature("docstring") LayersWithAbsorptionBuilder "

The  LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part). The middle layer is populated with particles. Requires IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: LayersWithAbsorptionBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::buildSample "MultiLayer * LayersWithAbsorptionBuilder::buildSample() const
";

%feature("docstring")  LayersWithAbsorptionBuilder::createSample "MultiLayer * LayersWithAbsorptionBuilder::createSample(size_t index=0)
";

%feature("docstring")  LayersWithAbsorptionBuilder::size "size_t LayersWithAbsorptionBuilder::size()
";


// File: classLayersWithAbsorptionBySLDBuilder.xml
%feature("docstring") LayersWithAbsorptionBySLDBuilder "

The  LayersWithAbsorptionBySLDBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part). //! The middle layer is populated with particles. MaterialBySLD is used to generate maaterials

C++ includes: LayersWithAbsorptionBySLDBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBySLDBuilder::LayersWithAbsorptionBySLDBuilder "LayersWithAbsorptionBySLDBuilder::LayersWithAbsorptionBySLDBuilder()
";

%feature("docstring")  LayersWithAbsorptionBySLDBuilder::~LayersWithAbsorptionBySLDBuilder "LayersWithAbsorptionBySLDBuilder::~LayersWithAbsorptionBySLDBuilder()
";

%feature("docstring")  LayersWithAbsorptionBySLDBuilder::buildSample "MultiLayer * LayersWithAbsorptionBySLDBuilder::buildSample() const
";


// File: classLayoutStrategyBuilder.xml
%feature("docstring") LayoutStrategyBuilder "

Methods to generate a simulation strategy for a  ParticleLayoutComputation.

C++ includes: LayoutStrategyBuilder.h
";

%feature("docstring")  LayoutStrategyBuilder::LayoutStrategyBuilder "LayoutStrategyBuilder::LayoutStrategyBuilder(const ProcessedLayout *p_layout, const SimulationOptions &sim_params, bool polarized)
";

%feature("docstring")  LayoutStrategyBuilder::~LayoutStrategyBuilder "LayoutStrategyBuilder::~LayoutStrategyBuilder()
";

%feature("docstring")  LayoutStrategyBuilder::releaseStrategy "IInterferenceFunctionStrategy * LayoutStrategyBuilder::releaseStrategy()
";


// File: classLine.xml
%feature("docstring") Line "

A line segment.

C++ includes: Line.h
";

%feature("docstring")  Line::Line "Line::Line(double x1, double y1, double x2, double y2)
";

%feature("docstring")  Line::clone "Line* Line::clone() const
";

%feature("docstring")  Line::contains "bool Line::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Line::contains "bool Line::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";


// File: classLinkedBoxDistributionBuilder.xml
%feature("docstring") LinkedBoxDistributionBuilder "

Distribution of boxes with main parameter and two linked parameters.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  LinkedBoxDistributionBuilder::LinkedBoxDistributionBuilder "LinkedBoxDistributionBuilder::LinkedBoxDistributionBuilder()=default
";

%feature("docstring")  LinkedBoxDistributionBuilder::buildSample "MultiLayer * LinkedBoxDistributionBuilder::buildSample() const
";


// File: classLLData.xml
%feature("docstring") LLData "

Template class to store data of any type in multi-dimensional space (low-level).

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


// File: classExceptions_1_1LogicErrorException.xml
%feature("docstring") Exceptions::LogicErrorException "";

%feature("docstring")  Exceptions::LogicErrorException::LogicErrorException "Exceptions::LogicErrorException::LogicErrorException(const std::string &message)
";


// File: classLogMetric.xml
%feature("docstring") LogMetric "

Implementation of the standard  $ \\\\chi^2 $ metric with intensity  $I$ and experimental data  $D$ being replaced by  $ \\\\log_{10} I $ and  $\\\\log_{10} D$ accordingly. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(\\\\log_{10} I - log_{10} D)^2 D^2 \\\\ln^2{10}}{\\\\delta_D^2}\\\\]

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  LogMetric::LogMetric "LogMetric::LogMetric()
";

%feature("docstring")  LogMetric::clone "LogMetric * LogMetric::clone() const override
";

%feature("docstring")  LogMetric::computeFromArrays "double LogMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  LogMetric::computeFromArrays "double LogMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classLorentzFisherPeakShape.xml
%feature("docstring") LorentzFisherPeakShape "

Class that implements a peak shape that is Lorentzian in the radial direction and uses the von Mises-Fisher distribution in the angular direction.

C++ includes: IPeakShape.h
";

%feature("docstring")  LorentzFisherPeakShape::LorentzFisherPeakShape "LorentzFisherPeakShape::LorentzFisherPeakShape(double max_intensity, double radial_size, double kappa)
";

%feature("docstring")  LorentzFisherPeakShape::~LorentzFisherPeakShape "LorentzFisherPeakShape::~LorentzFisherPeakShape() override
";

%feature("docstring")  LorentzFisherPeakShape::clone "LorentzFisherPeakShape * LorentzFisherPeakShape::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  LorentzFisherPeakShape::accept "void LorentzFisherPeakShape::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  LorentzFisherPeakShape::evaluate "double LorentzFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  LorentzFisherPeakShape::angularDisorder "bool LorentzFisherPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
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


// File: classMagneticLayerBuilder.xml
%feature("docstring") MagneticLayerBuilder "

Builds sample: magnetic spheres in a magnetized layer on a non-magnetized substrate.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticLayerBuilder::MagneticLayerBuilder "MagneticLayerBuilder::MagneticLayerBuilder()
";

%feature("docstring")  MagneticLayerBuilder::buildSample "MultiLayer * MagneticLayerBuilder::buildSample() const
";


// File: classMagneticMaterialImpl.xml
%feature("docstring") MagneticMaterialImpl "

Basic implementation for magnetized material. Incorporates data and methods required to handle material magnetization.

C++ includes: MagneticMaterialImpl.h
";

%feature("docstring")  MagneticMaterialImpl::MagneticMaterialImpl "MagneticMaterialImpl::MagneticMaterialImpl(const std::string &name, kvector_t magnetization)

Constructs basic material with name and magnetization. 
";

%feature("docstring")  MagneticMaterialImpl::~MagneticMaterialImpl "virtual MagneticMaterialImpl::~MagneticMaterialImpl()=default
";

%feature("docstring")  MagneticMaterialImpl::clone "MagneticMaterialImpl* MagneticMaterialImpl::clone() const override=0

Returns pointer to a copy of material. 
";

%feature("docstring")  MagneticMaterialImpl::inverted "MagneticMaterialImpl * MagneticMaterialImpl::inverted() const override final

Constructs a material with inverted magnetization. 
";

%feature("docstring")  MagneticMaterialImpl::isScalarMaterial "bool MagneticMaterialImpl::isScalarMaterial() const override final

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  MagneticMaterialImpl::isMagneticMaterial "bool MagneticMaterialImpl::isMagneticMaterial() const override final
";

%feature("docstring")  MagneticMaterialImpl::magnetization "kvector_t MagneticMaterialImpl::magnetization() const override final

Returns the magnetization (in A/m) 
";

%feature("docstring")  MagneticMaterialImpl::polarizedSubtrSLD "Eigen::Matrix2cd MagneticMaterialImpl::polarizedSubtrSLD(const WavevectorInfo &wavevectors) const override final

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld) matrix with magnetization corrections. 
";

%feature("docstring")  MagneticMaterialImpl::transformedMaterial "MagneticMaterialImpl * MagneticMaterialImpl::transformedMaterial(const Transform3D &transform) const override final
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


// File: classMagneticRotationBuilder.xml
%feature("docstring") MagneticRotationBuilder "

Builds sample: rotated magnetic spheres in substrate layer with a unit magnetic field.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticRotationBuilder::MagneticRotationBuilder "MagneticRotationBuilder::MagneticRotationBuilder()
";

%feature("docstring")  MagneticRotationBuilder::buildSample "MultiLayer * MagneticRotationBuilder::buildSample() const
";


// File: classMagneticSpheresBuilder.xml
%feature("docstring") MagneticSpheresBuilder "

Builds sample: spheres with magnetization inside substrate.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticSpheresBuilder::MagneticSpheresBuilder "MagneticSpheresBuilder::MagneticSpheresBuilder()
";

%feature("docstring")  MagneticSpheresBuilder::buildSample "MultiLayer * MagneticSpheresBuilder::buildSample() const
";


// File: classMagneticSubstrateZeroFieldBuilder.xml
%feature("docstring") MagneticSubstrateZeroFieldBuilder "

Builds sample: spheres in substrate layer with a zero magnetic field.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticSubstrateZeroFieldBuilder::MagneticSubstrateZeroFieldBuilder "MagneticSubstrateZeroFieldBuilder::MagneticSubstrateZeroFieldBuilder()
";

%feature("docstring")  MagneticSubstrateZeroFieldBuilder::buildSample "MultiLayer * MagneticSubstrateZeroFieldBuilder::buildSample() const
";


// File: classMaterial.xml
%feature("docstring") Material "

A wrapper for underlying material implementation

C++ includes: Material.h
";

%feature("docstring")  Material::Material "Material::Material(const Material &material)

Material copy-constructor. 
";

%feature("docstring")  Material::Material "Material::Material(Material &&material)=default

Material move-constructor. 
";

%feature("docstring")  Material::Material "Material::Material(std::unique_ptr< BaseMaterialImpl > material_impl)

Creates material with particular material implementation. 
";

%feature("docstring")  Material::inverted "Material Material::inverted() const

Constructs a material with inverted magnetization. 
";

%feature("docstring")  Material::refractiveIndex "complex_t Material::refractiveIndex(double wavelength) const

Returns refractive index. 
";

%feature("docstring")  Material::refractiveIndex2 "complex_t Material::refractiveIndex2(double wavelength) const

Returns squared refractive index. 
";

%feature("docstring")  Material::isScalarMaterial "bool Material::isScalarMaterial() const

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  Material::isMagneticMaterial "bool Material::isMagneticMaterial() const
";

%feature("docstring")  Material::getName "std::string Material::getName() const

Returns the name of material. 
";

%feature("docstring")  Material::typeID "MATERIAL_TYPES Material::typeID() const

Returns the type of underlying material implementation. 
";

%feature("docstring")  Material::magnetization "kvector_t Material::magnetization() const

Get the magnetization (in A/m) 
";

%feature("docstring")  Material::materialData "complex_t Material::materialData() const

Returns underlying material data. The units of returned values are the same as the ones passed to material factory functions 
";

%feature("docstring")  Material::isEmpty "bool Material::isEmpty() const

Returns true if material underlying data is nullptr. 
";

%feature("docstring")  Material::isDefaultMaterial "bool Material::isDefaultMaterial() const

Returns true if material has refractive index of (1.0, 0.0) and zero magnetization. 
";

%feature("docstring")  Material::scalarSubtrSLD "complex_t Material::scalarSubtrSLD(const WavevectorInfo &wavevectors) const

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld (in  $nm^{-2}$) being the scattering length density 
";

%feature("docstring")  Material::polarizedSubtrSLD "Eigen::Matrix2cd Material::polarizedSubtrSLD(const WavevectorInfo &wavevectors) const

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld) matrix with magnetization corrections. 
";

%feature("docstring")  Material::transformedMaterial "Material Material::transformedMaterial(const Transform3D &transform) const
";


// File: classMaterialBySLDImpl.xml
%feature("docstring") MaterialBySLDImpl "

Material implementation based on wavelength-independent data (valid for a range of wavelengths)

C++ includes: MaterialBySLDImpl.h
";

%feature("docstring")  MaterialBySLDImpl::~MaterialBySLDImpl "virtual MaterialBySLDImpl::~MaterialBySLDImpl()=default
";

%feature("docstring")  MaterialBySLDImpl::clone "MaterialBySLDImpl * MaterialBySLDImpl::clone() const override

Returns pointer to a copy of material. 
";

%feature("docstring")  MaterialBySLDImpl::refractiveIndex "complex_t MaterialBySLDImpl::refractiveIndex(double wavelength) const override

Returns refractive index. 
";

%feature("docstring")  MaterialBySLDImpl::refractiveIndex2 "complex_t MaterialBySLDImpl::refractiveIndex2(double wavelength) const override

Returns squared refractive index. 
";

%feature("docstring")  MaterialBySLDImpl::materialData "complex_t MaterialBySLDImpl::materialData() const override

Returns underlying material data. 
";

%feature("docstring")  MaterialBySLDImpl::typeID "MATERIAL_TYPES MaterialBySLDImpl::typeID() const override

Returns type of material implementation. 
";

%feature("docstring")  MaterialBySLDImpl::scalarSubtrSLD "complex_t MaterialBySLDImpl::scalarSubtrSLD(const WavevectorInfo &wavevectors) const override

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld (in  $nm^{-2}$) being the scattering length density 
";

%feature("docstring")  MaterialBySLDImpl::print "void MaterialBySLDImpl::print(std::ostream &ostr) const override

Prints object data. 
";


// File: structPlainMultiLayerBySLDBuilder_1_1MaterialData.xml


// File: classMatrixFresnelMap.xml
%feature("docstring") MatrixFresnelMap "

Implementation of  IFresnelMap for matrix valued reflection/transmission coefficients.

C++ includes: MatrixFresnelMap.h
";

%feature("docstring")  MatrixFresnelMap::MatrixFresnelMap "MatrixFresnelMap::MatrixFresnelMap(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  MatrixFresnelMap::~MatrixFresnelMap "MatrixFresnelMap::~MatrixFresnelMap() override
";

%feature("docstring")  MatrixFresnelMap::MatrixFresnelMap "MatrixFresnelMap::MatrixFresnelMap(const MatrixFresnelMap &other)=delete
";

%feature("docstring")  MatrixFresnelMap::getOutCoefficients "std::unique_ptr< const ILayerRTCoefficients > MatrixFresnelMap::getOutCoefficients(const SimulationElement &sim_element, size_t layer_index) const final override

Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector. 
";

%feature("docstring")  MatrixFresnelMap::setSlices "void MatrixFresnelMap::setSlices(const std::vector< Slice > &slices) final override
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

%feature("docstring")  MatrixRTCoefficients::getKz "virtual Eigen::Vector2cd MatrixRTCoefficients::getKz() const

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  MatrixRTCoefficients::calculateTRMatrices "void MatrixRTCoefficients::calculateTRMatrices()
";

%feature("docstring")  MatrixRTCoefficients::calculateTRWithoutMagnetization "void MatrixRTCoefficients::calculateTRWithoutMagnetization()
";

%feature("docstring")  MatrixRTCoefficients::initializeBottomLayerPhiPsi "void MatrixRTCoefficients::initializeBottomLayerPhiPsi()
";


// File: classMatrixRTCoefficients__v2.xml
%feature("docstring") MatrixRTCoefficients_v2 "

Specular reflection and transmission coefficients in a layer in case of magnetic interactions between the scattered particle and the layer.

C++ includes: MatrixRTCoefficients_v2.h
";

%feature("docstring")  MatrixRTCoefficients_v2::MatrixRTCoefficients_v2 "MatrixRTCoefficients_v2::MatrixRTCoefficients_v2(double kz_sign, Eigen::Vector2cd eigenvalues, kvector_t b)
";

%feature("docstring")  MatrixRTCoefficients_v2::MatrixRTCoefficients_v2 "MatrixRTCoefficients_v2::MatrixRTCoefficients_v2(const MatrixRTCoefficients_v2 &other)
";

%feature("docstring")  MatrixRTCoefficients_v2::~MatrixRTCoefficients_v2 "MatrixRTCoefficients_v2::~MatrixRTCoefficients_v2() override
";

%feature("docstring")  MatrixRTCoefficients_v2::clone "MatrixRTCoefficients_v2 * MatrixRTCoefficients_v2::clone() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T1plus "Eigen::Vector2cd MatrixRTCoefficients_v2::T1plus() const override

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  MatrixRTCoefficients_v2::R1plus "Eigen::Vector2cd MatrixRTCoefficients_v2::R1plus() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T2plus "Eigen::Vector2cd MatrixRTCoefficients_v2::T2plus() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::R2plus "Eigen::Vector2cd MatrixRTCoefficients_v2::R2plus() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T1min "Eigen::Vector2cd MatrixRTCoefficients_v2::T1min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::R1min "Eigen::Vector2cd MatrixRTCoefficients_v2::R1min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::T2min "Eigen::Vector2cd MatrixRTCoefficients_v2::T2min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::R2min "Eigen::Vector2cd MatrixRTCoefficients_v2::R2min() const override
";

%feature("docstring")  MatrixRTCoefficients_v2::getKz "Eigen::Vector2cd MatrixRTCoefficients_v2::getKz() const override

Returns z-part of the two wavevector eigenmodes. 
";


// File: classMesoCrystal.xml
%feature("docstring") MesoCrystal "

A particle with an internal structure of smaller particles.

C++ includes: MesoCrystal.h
";

%feature("docstring")  MesoCrystal::MesoCrystal "MesoCrystal::MesoCrystal(const IClusteredParticles &particle_structure, const IFormFactor &form_factor)
";

%feature("docstring")  MesoCrystal::~MesoCrystal "MesoCrystal::~MesoCrystal()
";

%feature("docstring")  MesoCrystal::clone "MesoCrystal * MesoCrystal::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  MesoCrystal::accept "void MesoCrystal::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  MesoCrystal::createSlicedParticle "SlicedParticle MesoCrystal::createSlicedParticle(ZLimits limits) const override final

Create a sliced form factor for this particle. 
";

%feature("docstring")  MesoCrystal::getChildren "std::vector< const INode * > MesoCrystal::getChildren() const override final

Returns a vector of children (const). 
";


// File: classMesoCrystalBuilder.xml
%feature("docstring") MesoCrystalBuilder "

Builds sample: cylindrical mesocrystal composed of spheres in a cubic lattice.

C++ includes: MesoCrystalBuilder.h
";

%feature("docstring")  MesoCrystalBuilder::MesoCrystalBuilder "MesoCrystalBuilder::MesoCrystalBuilder()
";

%feature("docstring")  MesoCrystalBuilder::buildSample "MultiLayer * MesoCrystalBuilder::buildSample() const
";


// File: structMillerIndex.xml
%feature("docstring") MillerIndex "

A direction in reciprocal space, specified by double-valued indices hkl.

C++ includes: ILatticeOrientation.h
";

%feature("docstring")  MillerIndex::MillerIndex "MillerIndex::MillerIndex(double h_, double k_, double l_)
";


// File: classMillerIndexOrientation.xml
%feature("docstring") MillerIndexOrientation "

Specifies a rotation of a lattice through the Miller indices of two coordinate axes.

C++ includes: ILatticeOrientation.h
";

%feature("docstring")  MillerIndexOrientation::MillerIndexOrientation "MillerIndexOrientation::MillerIndexOrientation(QComponent q1, MillerIndex index1, QComponent q2, MillerIndex index2)

This constructor is best explained by an example. Arguments QX, (1,1,0), QY, (0,2,1) mean: Rotate the lattice such that the axis [110] points into x direction, and the axis [021], projected into the yz plane, points into z direction. 
";

%feature("docstring")  MillerIndexOrientation::~MillerIndexOrientation "MillerIndexOrientation::~MillerIndexOrientation() override
";

%feature("docstring")  MillerIndexOrientation::clone "MillerIndexOrientation * MillerIndexOrientation::clone() const override
";

%feature("docstring")  MillerIndexOrientation::usePrimitiveLattice "void MillerIndexOrientation::usePrimitiveLattice(const Lattice &lattice) override
";

%feature("docstring")  MillerIndexOrientation::transformationMatrix "Transform3D MillerIndexOrientation::transformationMatrix() const override
";


// File: classMPISimulation.xml
%feature("docstring") MPISimulation "";

%feature("docstring")  MPISimulation::runSimulation "void MPISimulation::runSimulation(Simulation *simulation)
";


// File: classMultiLayer.xml
%feature("docstring") MultiLayer "

Our sample model: a stack of layers one below the other. Example of system of 4 layers (3 interfaces):

ambience layer #0 ------ interface #0 z=0.0 Fe, 20A layer #1 ------ interface #1 z=-20.0 Cr, 40A layer #2 ------ interface #2 z=-60.0 substrate layer #3

C++ includes: MultiLayer.h
";

%feature("docstring")  MultiLayer::MultiLayer "MultiLayer::MultiLayer()
";

%feature("docstring")  MultiLayer::~MultiLayer "MultiLayer::~MultiLayer() override
";

%feature("docstring")  MultiLayer::clone "MultiLayer * MultiLayer::clone() const final override

Returns a clone of multilayer with clones of all layers and interfaces between layers 
";

%feature("docstring")  MultiLayer::accept "void MultiLayer::accept(INodeVisitor *visitor) const final override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  MultiLayer::numberOfLayers "size_t MultiLayer::numberOfLayers() const
";

%feature("docstring")  MultiLayer::addLayer "void MultiLayer::addLayer(const Layer &layer)

Adds object to multilayer.

Adds layer with default (zero) roughness. 
";

%feature("docstring")  MultiLayer::addLayerWithTopRoughness "void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)

Adds layer with top roughness. 
";

%feature("docstring")  MultiLayer::layer "const Layer * MultiLayer::layer(size_t i_layer) const

Returns layer with given index. 
";

%feature("docstring")  MultiLayer::layerInterface "const LayerInterface * MultiLayer::layerInterface(size_t i_interface) const

Returns interface with given index. 
";

%feature("docstring")  MultiLayer::setCrossCorrLength "void MultiLayer::setCrossCorrLength(double crossCorrLength)

Sets cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::crossCorrLength "double MultiLayer::crossCorrLength() const

Returns cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::setExternalField "void MultiLayer::setExternalField(kvector_t ext_field)

Sets the external field applied to the multilayer (units: A/m) 
";

%feature("docstring")  MultiLayer::externalField "kvector_t MultiLayer::externalField() const

Returns the external field applied to the multilayer (units: A/m) 
";

%feature("docstring")  MultiLayer::getChildren "std::vector< const INode * > MultiLayer::getChildren() const final override

Returns a vector of children (const). 
";

%feature("docstring")  MultiLayer::setRoughnessModel "void MultiLayer::setRoughnessModel(RoughnessModel roughnessModel)
";

%feature("docstring")  MultiLayer::roughnessModel "RoughnessModel MultiLayer::roughnessModel() const
";


// File: classMultiLayerWithNCRoughnessBuilder.xml
%feature("docstring") MultiLayerWithNCRoughnessBuilder "

Builds sample: layers with correlated roughness.

C++ includes: MultiLayerWithNCRoughnessBuilder.h
";

%feature("docstring")  MultiLayerWithNCRoughnessBuilder::MultiLayerWithNCRoughnessBuilder "MultiLayerWithNCRoughnessBuilder::MultiLayerWithNCRoughnessBuilder()
";

%feature("docstring")  MultiLayerWithNCRoughnessBuilder::buildSample "MultiLayer * MultiLayerWithNCRoughnessBuilder::buildSample() const override
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

Builds sample: mixture of cylinders and prisms without interference, using multiple particle layouts

C++ includes: MultipleLayoutBuilder.h
";

%feature("docstring")  MultipleLayoutBuilder::MultipleLayoutBuilder "MultipleLayoutBuilder::MultipleLayoutBuilder()
";

%feature("docstring")  MultipleLayoutBuilder::buildSample "MultiLayer * MultipleLayoutBuilder::buildSample() const
";


// File: structArrayUtils_1_1CreateDataImpl_1_1nDim.xml


// File: structArrayUtils_1_1CreateDataImpl_1_1nDim_3_01std_1_1vector_3_01T_00_01A_01_4_01_4.xml


// File: classNodeIterator.xml
%feature("docstring") NodeIterator "

Iterator through  INode tree of objects.

Usage example: SampleTreeIterator<Strategy> it(&sample); it.first(); while( !it.is_done() ) {  INode *p_sample = it.get_current(); it.next(); }

C++ includes: NodeIterator.h
";

%feature("docstring")  NodeIterator::NodeIterator "NodeIterator< Strategy >::NodeIterator(const INode *root)
";

%feature("docstring")  NodeIterator::~NodeIterator "virtual NodeIterator< Strategy >::~NodeIterator()
";

%feature("docstring")  NodeIterator::first "void NodeIterator< Strategy >::first()
";

%feature("docstring")  NodeIterator::next "void NodeIterator< Strategy >::next()
";

%feature("docstring")  NodeIterator::getCurrent "const INode * NodeIterator< Strategy >::getCurrent()
";

%feature("docstring")  NodeIterator::isDone "bool NodeIterator< Strategy >::isDone() const
";

%feature("docstring")  NodeIterator::depth "int NodeIterator< Strategy >::depth() const
";


// File: classExceptions_1_1NotImplementedException.xml
%feature("docstring") Exceptions::NotImplementedException "";

%feature("docstring")  Exceptions::NotImplementedException::NotImplementedException "Exceptions::NotImplementedException::NotImplementedException(const std::string &message)
";


// File: classExceptions_1_1NullPointerException.xml
%feature("docstring") Exceptions::NullPointerException "";

%feature("docstring")  Exceptions::NullPointerException::NullPointerException "Exceptions::NullPointerException::NullPointerException(const std::string &message)
";


// File: classObjectiveMetric.xml
%feature("docstring") ObjectiveMetric "

Base class for metric implementations.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  ObjectiveMetric::ObjectiveMetric "ObjectiveMetric::ObjectiveMetric(std::function< double(double)> norm)
";

%feature("docstring")  ObjectiveMetric::clone "ObjectiveMetric* ObjectiveMetric::clone() const override=0
";

%feature("docstring")  ObjectiveMetric::compute "double ObjectiveMetric::compute(const SimDataPair &data_pair, bool use_weights) const

Computes metric value from  SimDataPair object. Calls computeFromArrays internally.

Parameters:
-----------

data_pair: 
 SimDataPair object. Can optionally contain data uncertainties

use_weights: 
boolean, defines if data uncertainties should be taken into account 
";

%feature("docstring")  ObjectiveMetric::computeFromArrays "virtual double ObjectiveMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const =0

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  ObjectiveMetric::computeFromArrays "virtual double ObjectiveMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const =0

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  ObjectiveMetric::setNorm "void ObjectiveMetric::setNorm(std::function< double(double)> norm)
";

%feature("docstring")  ObjectiveMetric::norm "auto ObjectiveMetric::norm() const

Returns a copy of the normalization function used. 
";


// File: classObjectiveMetricWrapper.xml
%feature("docstring") ObjectiveMetricWrapper "";

%feature("docstring")  ObjectiveMetricWrapper::ObjectiveMetricWrapper "ObjectiveMetricWrapper::ObjectiveMetricWrapper(std::unique_ptr< ObjectiveMetric > module)
";

%feature("docstring")  ObjectiveMetricWrapper::compute "double ObjectiveMetricWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const override
";


// File: classFitObserver_1_1ObserverData.xml


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

%feature("docstring")  OffSpecSimulation::clone "OffSpecSimulation* OffSpecSimulation::clone() const override
";

%feature("docstring")  OffSpecSimulation::accept "void OffSpecSimulation::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  OffSpecSimulation::prepareSimulation "void OffSpecSimulation::prepareSimulation() final

Put into a clean state for running a simulation. 
";

%feature("docstring")  OffSpecSimulation::result "SimulationResult OffSpecSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  OffSpecSimulation::setBeamParameters "void OffSpecSimulation::setBeamParameters(double wavelength, const IAxis &alpha_axis, double phi_i)

Sets beam parameters from here (forwarded to  Instrument) 
";

%feature("docstring")  OffSpecSimulation::beamAxis "const IAxis * OffSpecSimulation::beamAxis() const

Returns axis of the beam. 
";

%feature("docstring")  OffSpecSimulation::createUnitConverter "std::unique_ptr< IUnitConverter > OffSpecSimulation::createUnitConverter() const
";

%feature("docstring")  OffSpecSimulation::intensityMapSize "size_t OffSpecSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";


// File: classOffSpecularConverter.xml
%feature("docstring") OffSpecularConverter "

IUnitConverter class that handles the unit translations for off-specular simulations with a spherical detector Its default units are radians for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  OffSpecularConverter::OffSpecularConverter "OffSpecularConverter::OffSpecularConverter(const IDetector2D &detector, const Beam &beam, const IAxis &alpha_axis)
";

%feature("docstring")  OffSpecularConverter::~OffSpecularConverter "OffSpecularConverter::~OffSpecularConverter() override
";

%feature("docstring")  OffSpecularConverter::clone "OffSpecularConverter * OffSpecularConverter::clone() const override
";

%feature("docstring")  OffSpecularConverter::defaultUnits "AxesUnits OffSpecularConverter::defaultUnits() const override
";


// File: structOneSidedLimit.xml
%feature("docstring") OneSidedLimit "

Helper class that represents a onesided limit

C++ includes: ZLimits.h
";


// File: classOrderedMap.xml
%feature("docstring") OrderedMap "

Ordered map which saves the order of insertion.

C++ includes: OrderedMap.h
";

%feature("docstring")  OrderedMap::OrderedMap "OrderedMap< Key, Object >::OrderedMap()
";

%feature("docstring")  OrderedMap::~OrderedMap "virtual OrderedMap< Key, Object >::~OrderedMap()
";

%feature("docstring")  OrderedMap::clear "void OrderedMap< Key, Object >::clear()
";

%feature("docstring")  OrderedMap::begin "const_iterator OrderedMap< Key, Object >::begin() const
";

%feature("docstring")  OrderedMap::end "const_iterator OrderedMap< Key, Object >::end() const
";

%feature("docstring")  OrderedMap::begin "iterator OrderedMap< Key, Object >::begin()
";

%feature("docstring")  OrderedMap::end "iterator OrderedMap< Key, Object >::end()
";

%feature("docstring")  OrderedMap::size "size_t OrderedMap< Key, Object >::size()
";

%feature("docstring")  OrderedMap::insert "void OrderedMap< Key, Object >::insert(const Key &key, const Object &object)
";

%feature("docstring")  OrderedMap::find "iterator OrderedMap< Key, Object >::find(const Key &key)
";

%feature("docstring")  OrderedMap::find "const_iterator OrderedMap< Key, Object >::find(const Key &key) const
";

%feature("docstring")  OrderedMap::erase "size_t OrderedMap< Key, Object >::erase(const Key &key)
";

%feature("docstring")  OrderedMap::value "const Object& OrderedMap< Key, Object >::value(const Key &key)
";


// File: classExceptions_1_1OutOfBoundsException.xml
%feature("docstring") Exceptions::OutOfBoundsException "";

%feature("docstring")  Exceptions::OutOfBoundsException::OutOfBoundsException "Exceptions::OutOfBoundsException::OutOfBoundsException(const std::string &message)
";


// File: classOutputData.xml
%feature("docstring") OutputData "

Template class to store data of any type in multi-dimensional space.

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

%feature("docstring")  OutputData::totalSum "T OutputData< T >::totalSum() const

Returns sum of all values in the data structure. 
";

%feature("docstring")  OutputData::begin "OutputData< T >::const_iterator OutputData< T >::begin()

Returns read/write iterator that points to the first element. 
";

%feature("docstring")  OutputData::begin "const_iterator OutputData< T >::begin() const

Returns read-only iterator that points to the first element. 
";

%feature("docstring")  OutputData::end "iterator OutputData< T >::end()

Returns read/write iterator that points to the one past last element. 
";

%feature("docstring")  OutputData::end "const_iterator OutputData< T >::end() const

Returns read-only iterator that points to the one past last element. 
";

%feature("docstring")  OutputData::getAxesBinIndices "std::vector< int > OutputData< T >::getAxesBinIndices(size_t global_index) const

Returns vector of axes indices for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

Vector of bin indices for all axes defined 
";

%feature("docstring")  OutputData::getAxisBinIndex "size_t OutputData< T >::getAxisBinIndex(size_t global_index, size_t i_selected_axis) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::getAxisBinIndex "size_t OutputData< T >::getAxisBinIndex(size_t global_index, const std::string &axis_name) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::toGlobalIndex "size_t OutputData< T >::toGlobalIndex(const std::vector< unsigned > &axes_indices) const

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

%feature("docstring")  OutputData::getArray "PyObject* OutputData< T >::getArray() const

returns data as Python numpy array 
";

%feature("docstring")  OutputData::isInitialized "bool OutputData< T >::isInitialized() const

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

Strategy to read  BornAgain native IntensityData from ASCII file.

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


// File: classOutputDataReadReflectometryStrategy.xml
%feature("docstring") OutputDataReadReflectometryStrategy "

Strategy to read Reflectometry data from ASCII file.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  OutputDataReadReflectometryStrategy::readOutputData "OutputData< double > * OutputDataReadReflectometryStrategy::readOutputData(std::istream &input_stream)
";


// File: classOutputDataWriteFactory.xml
%feature("docstring") OutputDataWriteFactory "

Creates writer appropariate for given type of files.

C++ includes: OutputDataWriteFactory.h
";


// File: classOutputDataWriteINTStrategy.xml
%feature("docstring") OutputDataWriteINTStrategy "

Strategy to write  OutputData to special  BornAgain ASCII format

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  OutputDataWriteINTStrategy::writeOutputData "void OutputDataWriteINTStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classOutputDataWriteNumpyTXTStrategy.xml
%feature("docstring") OutputDataWriteNumpyTXTStrategy "

Strategy to write  OutputData to simple ASCII file with the layout as in numpy.savetxt

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

Writes output data to file. 
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

%feature("docstring")  ParameterDistribution::getDistribution "IDistribution1D * ParameterDistribution::getDistribution() const
";

%feature("docstring")  ParameterDistribution::getDistribution "IDistribution1D* ParameterDistribution::getDistribution()
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

Container with parameters for  IParameterized object.

C++ includes: ParameterPool.h
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool()

Constructs an empty parameter pool. 
";

%feature("docstring")  ParameterPool::~ParameterPool "ParameterPool::~ParameterPool()
";

%feature("docstring")  ParameterPool::clone "ParameterPool * ParameterPool::clone() const

Returns a literal clone. 
";

%feature("docstring")  ParameterPool::copyToExternalPool "void ParameterPool::copyToExternalPool(const std::string &prefix, ParameterPool *other_pool) const

Copies parameters of given pool to  other pool, prepeding  prefix to the parameter names. 
";

%feature("docstring")  ParameterPool::clear "void ParameterPool::clear()

Clears the parameter map. 
";

%feature("docstring")  ParameterPool::size "size_t ParameterPool::size() const

Returns number of parameters in the pool. 
";

%feature("docstring")  ParameterPool::addParameter "RealParameter & ParameterPool::addParameter(RealParameter *newPar)

Adds parameter to the pool, and returns reference to the input pointer.

Returning the input pointer allows us to concatenate function calls like pool->addParameter( new RealParameter(...) ).setLimits(-1,+1).setFixed().setUnit(\"nm\") 
";

%feature("docstring")  ParameterPool::parameter "RealParameter * ParameterPool::parameter(const std::string &name)

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::parameter "const RealParameter * ParameterPool::parameter(const std::string &name) const

Returns parameter with given  name. 
";

%feature("docstring")  ParameterPool::parameters "const std::vector<RealParameter*> ParameterPool::parameters() const

Returns full vector of parameters. 
";

%feature("docstring")  ParameterPool::getMatchedParameters "std::vector< RealParameter * > ParameterPool::getMatchedParameters(const std::string &pattern) const

Returns nonempty vector of parameters that match the  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::getUniqueMatch "RealParameter * ParameterPool::getUniqueMatch(const std::string &pattern) const

Returns the one parameter that matches the  pattern (wildcards '*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::setParameterValue "void ParameterPool::setParameterValue(const std::string &name, double value)

Sets parameter value. 
";

%feature("docstring")  ParameterPool::setMatchedParametersValue "int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)

Sets value of the nonzero parameters that match  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::setUniqueMatchValue "void ParameterPool::setUniqueMatchValue(const std::string &pattern, double value)

Sets value of the one parameter that matches  pattern ('*' allowed), or throws. 
";

%feature("docstring")  ParameterPool::parameterNames "std::vector< std::string > ParameterPool::parameterNames() const
";

%feature("docstring")  ParameterPool::removeParameter "void ParameterPool::removeParameter(const std::string &name)

Removes parameter with given name from the pool. 
";


// File: classParameterSample.xml
%feature("docstring") ParameterSample "

A parameter value with a weight, as obtained when sampling from a distribution.

C++ includes: ParameterSample.h
";

%feature("docstring")  ParameterSample::ParameterSample "ParameterSample::ParameterSample(double _value=0., double _weight=1.)
";


// File: classParticle.xml
%feature("docstring") Particle "

A particle with a form factor and refractive index.

C++ includes: Particle.h
";

%feature("docstring")  Particle::Particle "Particle::Particle()
";

%feature("docstring")  Particle::Particle "Particle::Particle(Material material)
";

%feature("docstring")  Particle::Particle "Particle::Particle(Material material, const IFormFactor &form_factor)
";

%feature("docstring")  Particle::Particle "Particle::Particle(Material material, const IFormFactor &form_factor, const IRotation &rotation)
";

%feature("docstring")  Particle::clone "Particle * Particle::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  Particle::accept "void Particle::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  Particle::createSlicedParticle "SlicedParticle Particle::createSlicedParticle(ZLimits limits) const override final

Create a sliced form factor for this particle. 
";

%feature("docstring")  Particle::setMaterial "void Particle::setMaterial(Material material)
";

%feature("docstring")  Particle::material "const Material* Particle::material() const override final

Returns nullptr, unless overwritten to return a specific material. 
";

%feature("docstring")  Particle::setFormFactor "void Particle::setFormFactor(const IFormFactor &form_factor)
";

%feature("docstring")  Particle::getChildren "std::vector< const INode * > Particle::getChildren() const override final

Returns a vector of children (const). 
";


// File: classParticleComposition.xml
%feature("docstring") ParticleComposition "

A composition of particles at fixed positions

C++ includes: ParticleComposition.h
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition()
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::~ParticleComposition "ParticleComposition::~ParticleComposition()
";

%feature("docstring")  ParticleComposition::clone "ParticleComposition * ParticleComposition::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleComposition::accept "void ParticleComposition::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ParticleComposition::createFormFactor "IFormFactor * ParticleComposition::createFormFactor() const override final

Create a form factor for this particle. 
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle)
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle, kvector_t position)
";

%feature("docstring")  ParticleComposition::addParticles "void ParticleComposition::addParticles(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::nbrParticles "size_t ParticleComposition::nbrParticles() const

Returns number of different particles. 
";

%feature("docstring")  ParticleComposition::getChildren "std::vector< const INode * > ParticleComposition::getChildren() const override final

Returns a vector of children (const). 
";

%feature("docstring")  ParticleComposition::decompose "SafePointerVector< IParticle > ParticleComposition::decompose() const override final

Decompose in constituent  IParticle objects. 
";

%feature("docstring")  ParticleComposition::bottomTopZ "ParticleLimits ParticleComposition::bottomTopZ() const override final

Top and bottom z-coordinate. 
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

%feature("docstring")  ParticleCoreShell::clone "ParticleCoreShell * ParticleCoreShell::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleCoreShell::accept "void ParticleCoreShell::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ParticleCoreShell::createSlicedParticle "SlicedParticle ParticleCoreShell::createSlicedParticle(ZLimits limits) const override final

Create a sliced form factor for this particle. 
";

%feature("docstring")  ParticleCoreShell::coreParticle "const Particle * ParticleCoreShell::coreParticle() const
";

%feature("docstring")  ParticleCoreShell::shellParticle "const Particle * ParticleCoreShell::shellParticle() const
";

%feature("docstring")  ParticleCoreShell::getChildren "std::vector< const INode * > ParticleCoreShell::getChildren() const override final

Returns a vector of children (const). 
";


// File: classParticleDistribution.xml
%feature("docstring") ParticleDistribution "

A particle type that is a parametric distribution of  IParticle's.

C++ includes: ParticleDistribution.h
";

%feature("docstring")  ParticleDistribution::ParticleDistribution "ParticleDistribution::ParticleDistribution(const IParticle &prototype, const ParameterDistribution &par_distr)
";

%feature("docstring")  ParticleDistribution::clone "ParticleDistribution * ParticleDistribution::clone() const override final

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleDistribution::accept "void ParticleDistribution::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ParticleDistribution::translate "void ParticleDistribution::translate(kvector_t translation) override final

Translates the particle with the given vector. 
";

%feature("docstring")  ParticleDistribution::rotate "void ParticleDistribution::rotate(const IRotation &rotation) override final

Applies the given rotation to the particle. 
";

%feature("docstring")  ParticleDistribution::generateParticles "SafePointerVector< IParticle > ParticleDistribution::generateParticles() const

Returns list of new particles generated according to a distribution.

Returns particle clones with parameter values drawn from distribution. 
";

%feature("docstring")  ParticleDistribution::prototype "const IParticle& ParticleDistribution::prototype() const

Returns the prototype particle, used for generating multiple ones. 
";

%feature("docstring")  ParticleDistribution::parameterDistribution "ParameterDistribution ParticleDistribution::parameterDistribution() const

Returns the distributed parameter data. 
";

%feature("docstring")  ParticleDistribution::getChildren "std::vector< const INode * > ParticleDistribution::getChildren() const override final

Returns a vector of children (const). 
";


// File: classParticleInTheAirBuilder.xml
%feature("docstring") ParticleInTheAirBuilder "

The  ParticleInTheAirBuilder class generates a multilayer with single air layer populated with particles of certain types. Requires IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: ParticleInTheAirBuilder.h
";

%feature("docstring")  ParticleInTheAirBuilder::ParticleInTheAirBuilder "ParticleInTheAirBuilder::ParticleInTheAirBuilder()
";

%feature("docstring")  ParticleInTheAirBuilder::~ParticleInTheAirBuilder "ParticleInTheAirBuilder::~ParticleInTheAirBuilder()
";

%feature("docstring")  ParticleInTheAirBuilder::buildSample "MultiLayer * ParticleInTheAirBuilder::buildSample() const
";

%feature("docstring")  ParticleInTheAirBuilder::createSample "MultiLayer * ParticleInTheAirBuilder::createSample(size_t index=0)
";

%feature("docstring")  ParticleInTheAirBuilder::size "size_t ParticleInTheAirBuilder::size()
";


// File: classParticleLayout.xml
%feature("docstring") ParticleLayout "

Decorator class that adds particles to  ISample objects.

C++ includes: ParticleLayout.h
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout()
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout(const IAbstractParticle &particle, double abundance=-1.0)
";

%feature("docstring")  ParticleLayout::~ParticleLayout "ParticleLayout::~ParticleLayout() override
";

%feature("docstring")  ParticleLayout::clone "ParticleLayout * ParticleLayout::clone() const final override

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleLayout::accept "void ParticleLayout::accept(INodeVisitor *visitor) const final override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IAbstractParticle &particle, double abundance=-1.0, const kvector_t position=kvector_t(), const IRotation &rotation=IdentityRotation())

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

%feature("docstring")  ParticleLayout::particles "SafePointerVector< IParticle > ParticleLayout::particles() const final override

Returns information on all particles (type and abundance) and generates new particles if an  IAbstractParticle denotes a collection 
";

%feature("docstring")  ParticleLayout::interferenceFunction "const IInterferenceFunction * ParticleLayout::interferenceFunction() const final override

Returns the interference function. 
";

%feature("docstring")  ParticleLayout::getTotalAbundance "double ParticleLayout::getTotalAbundance() const final override

Get total abundance of all particles. 
";

%feature("docstring")  ParticleLayout::setInterferenceFunction "void ParticleLayout::setInterferenceFunction(const IInterferenceFunction &interference_function)

Adds interference functions. 
";

%feature("docstring")  ParticleLayout::totalParticleSurfaceDensity "double ParticleLayout::totalParticleSurfaceDensity() const final override

Returns surface density of all particles. 
";

%feature("docstring")  ParticleLayout::setTotalParticleSurfaceDensity "void ParticleLayout::setTotalParticleSurfaceDensity(double particle_density) final override

Sets total particle surface density.

Parameters:
-----------

particle_density: 
number of particles per square nanometer 
";

%feature("docstring")  ParticleLayout::getChildren "std::vector< const INode * > ParticleLayout::getChildren() const final override

Returns a vector of children (const). 
";


// File: classParticleLayoutComputation.xml
%feature("docstring") ParticleLayoutComputation "

Computes the scattering contribution from one particle layout. Used by  DWBAComputation.

C++ includes: ParticleLayoutComputation.h
";

%feature("docstring")  ParticleLayoutComputation::ParticleLayoutComputation "ParticleLayoutComputation::ParticleLayoutComputation(const ProcessedLayout *p_layout, const SimulationOptions &options, bool polarized)
";

%feature("docstring")  ParticleLayoutComputation::~ParticleLayoutComputation "ParticleLayoutComputation::~ParticleLayoutComputation()
";

%feature("docstring")  ParticleLayoutComputation::compute "void ParticleLayoutComputation::compute(SimulationElement &elem) const
";

%feature("docstring")  ParticleLayoutComputation::mergeRegionMap "void ParticleLayoutComputation::mergeRegionMap(std::map< size_t, std::vector< HomogeneousRegion >> &region_map) const

Merges its region map into the given one (notice non-const reference parameter) 
";


// File: structParticleLimits.xml
%feature("docstring") ParticleLimits "

Vertical extension of a particle, specified by bottom and top z coordinate.

C++ includes: IParticle.h
";


// File: classPlainMultiLayerBySLDBuilder.xml
%feature("docstring") PlainMultiLayerBySLDBuilder "

Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate. Ti is 70 angstroms thick, Ni is 30 angstroms thick.

C++ includes: PlainMultiLayerBySLDBuilder.h
";

%feature("docstring")  PlainMultiLayerBySLDBuilder::PlainMultiLayerBySLDBuilder "PlainMultiLayerBySLDBuilder::PlainMultiLayerBySLDBuilder(int n_layers=10)
";

%feature("docstring")  PlainMultiLayerBySLDBuilder::buildSample "MultiLayer * PlainMultiLayerBySLDBuilder::buildSample() const override
";


// File: classPointwiseAxis.xml
%feature("docstring") PointwiseAxis "

Axis containing arbitrary (non-equidistant) coordinate values. Lower boundary of the first bin and upper boundary of the last bin correspond to first and last passed coordinates. Other bin boundaries are computed as arithmetical mean of two adjacent coordinates. One should be aware, that bin centers reported by  PointwiseAxis::getBinCenter do not coincide with the values produced by Bin1D::getMidPoint. On-axis values are bounded by minimum/maximum values passed to the constructor.

C++ includes: PointwiseAxis.h
";

%feature("docstring")  PointwiseAxis::PointwiseAxis "PointwiseAxis::PointwiseAxis(String &&name, Vector &&coordinate_values)
";

%feature("docstring")  PointwiseAxis::clone "PointwiseAxis * PointwiseAxis::clone() const override

clone function 
";

%feature("docstring")  PointwiseAxis::~PointwiseAxis "PointwiseAxis::~PointwiseAxis() override=default
";

%feature("docstring")  PointwiseAxis::size "size_t PointwiseAxis::size() const override

retrieve the number of bins 
";

%feature("docstring")  PointwiseAxis::getBin "Bin1D PointwiseAxis::getBin(size_t index) const override

retrieve a 1d bin for the given index 
";

%feature("docstring")  PointwiseAxis::getMin "double PointwiseAxis::getMin() const override

Returns value of first on-axis point. 
";

%feature("docstring")  PointwiseAxis::getMax "double PointwiseAxis::getMax() const override

Returns value of last on-axis point. 
";

%feature("docstring")  PointwiseAxis::getBinCenter "double PointwiseAxis::getBinCenter(size_t index) const override

Returns the coordinate corresponding to the given index. 
";

%feature("docstring")  PointwiseAxis::findClosestIndex "size_t PointwiseAxis::findClosestIndex(double value) const override

find index of the coordinate closest to the given value 
";

%feature("docstring")  PointwiseAxis::getBinCenters "std::vector<double> PointwiseAxis::getBinCenters() const override
";

%feature("docstring")  PointwiseAxis::getBinBoundaries "std::vector< double > PointwiseAxis::getBinBoundaries() const override
";

%feature("docstring")  PointwiseAxis::createClippedAxis "PointwiseAxis * PointwiseAxis::createClippedAxis(double left, double right) const override

Creates a new clipped axis. 
";


// File: classPoissonLikeMetric.xml
%feature("docstring") PoissonLikeMetric "

Implementation of  $ \\\\chi^2 $ metric with standard deviation  $\\\\sigma = max(\\\\sqrt{I}, 1)$, where  $I$ is the simulated intensity. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(I - D)^2}{max(I, 1)}\\\\] for unweighted experimental data. Falls to standard  Chi2Metric when data uncertainties are taken into account.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  PoissonLikeMetric::PoissonLikeMetric "PoissonLikeMetric::PoissonLikeMetric()
";

%feature("docstring")  PoissonLikeMetric::clone "PoissonLikeMetric * PoissonLikeMetric::clone() const override
";

%feature("docstring")  PoissonLikeMetric::computeFromArrays "double PoissonLikeMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  PoissonLikeMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  PoissonLikeMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classPoissonNoiseBackground.xml
%feature("docstring") PoissonNoiseBackground "

Class representing Poisson noise on top of the scattered intensity

C++ includes: PoissonNoiseBackground.h
";

%feature("docstring")  PoissonNoiseBackground::PoissonNoiseBackground "PoissonNoiseBackground::PoissonNoiseBackground()
";

%feature("docstring")  PoissonNoiseBackground::~PoissonNoiseBackground "PoissonNoiseBackground::~PoissonNoiseBackground()
";

%feature("docstring")  PoissonNoiseBackground::clone "PoissonNoiseBackground * PoissonNoiseBackground::clone() const override final
";

%feature("docstring")  PoissonNoiseBackground::accept "void PoissonNoiseBackground::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  PoissonNoiseBackground::addBackGround "double PoissonNoiseBackground::addBackGround(double intensity) const override final
";


// File: classPolarizationHandler.xml
%feature("docstring") PolarizationHandler "

Convenience class for handling polarization density matrix and polarization analyzer operator

C++ includes: PolarizationHandler.h
";

%feature("docstring")  PolarizationHandler::PolarizationHandler "PolarizationHandler::PolarizationHandler()
";

%feature("docstring")  PolarizationHandler::PolarizationHandler "PolarizationHandler::PolarizationHandler(const Eigen::Matrix2cd &polarization, const Eigen::Matrix2cd &analyzer)
";

%feature("docstring")  PolarizationHandler::setPolarization "void PolarizationHandler::setPolarization(const Eigen::Matrix2cd &polarization)

Sets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  PolarizationHandler::getPolarization "Eigen::Matrix2cd PolarizationHandler::getPolarization() const

Gets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  PolarizationHandler::setAnalyzerOperator "void PolarizationHandler::setAnalyzerOperator(const Eigen::Matrix2cd &analyzer)

Sets the polarization analyzer operator (in spin basis along z-axis) 
";

%feature("docstring")  PolarizationHandler::getAnalyzerOperator "Eigen::Matrix2cd PolarizationHandler::getAnalyzerOperator() const

Gets the polarization analyzer operator (in spin basis along z-axis) 
";

%feature("docstring")  PolarizationHandler::swapContent "void PolarizationHandler::swapContent(PolarizationHandler &other)
";


// File: classPolygon.xml
%feature("docstring") Polygon "

A polygon in 2D space.  Polygon defined by two arrays with x and y coordinates of points. Sizes of arrays should coincide. If polygon is unclosed (the last point doesn't repeat the first one), it will be closed automatically.

C++ includes: Polygon.h
";

%feature("docstring")  Polygon::Polygon "Polygon::Polygon(const std::vector< double > x, const std::vector< double > y)

Parameters:
-----------

x: 
Vector of x-coordinates of polygon points.

y: 
Vector of y-coordinates of polygon points. 
";

%feature("docstring")  Polygon::Polygon "Polygon::Polygon(const std::vector< std::vector< double >> points)

Polygon defined by two dimensional array with (x,y) coordinates of polygon points. The size of second dimension should be 2. If polygon is unclosed (the last point doesn't repeat the first one), it will be closed automatically.

Parameters:
-----------

points: 
Two dimensional vector of (x,y) coordinates of polygon points. 
";

%feature("docstring")  Polygon::Polygon "Polygon::Polygon(const PolygonPrivate *d)
";

%feature("docstring")  Polygon::~Polygon "Polygon::~Polygon()
";

%feature("docstring")  Polygon::clone "virtual Polygon* Polygon::clone() const
";

%feature("docstring")  Polygon::contains "bool Polygon::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Polygon::contains "bool Polygon::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  Polygon::getArea "double Polygon::getArea() const
";

%feature("docstring")  Polygon::getPoints "void Polygon::getPoints(std::vector< double > &xpos, std::vector< double > &ypos) const
";


// File: classPolygonalTopology.xml
%feature("docstring") PolygonalTopology "

For internal use in  PolyhedralFace.

C++ includes: FormFactorPolyhedron.h
";


// File: classPolygonPrivate.xml
%feature("docstring") PolygonPrivate "

The private data for polygons to hide boost dependency from the header. 
";

%feature("docstring")  PolygonPrivate::init_from "void PolygonPrivate::init_from(const std::vector< double > &x, const std::vector< double > &y)
";

%feature("docstring")  PolygonPrivate::get_points "void PolygonPrivate::get_points(std::vector< double > &xpos, std::vector< double > &ypos)
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

%feature("docstring")  PolyhedralEdge::contrib "complex_t PolyhedralEdge::contrib(int m, cvector_t qpa, complex_t qrperp) const

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

%feature("docstring")  PolyhedralFace::ff_n "complex_t PolyhedralFace::ff_n(int m, cvector_t q) const

Returns contribution qn*f_n [of order q^(n+1)] from this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff "complex_t PolyhedralFace::ff(cvector_t q, bool sym_Ci) const

Returns the contribution ff(q) of this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff_2D "complex_t PolyhedralFace::ff_2D(cvector_t qpa) const

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


// File: classPostorderStrategy.xml
%feature("docstring") PostorderStrategy "

Traverse tree; visit children before their parents.

C++ includes: IterationStrategy.h
";

%feature("docstring")  PostorderStrategy::PostorderStrategy "PostorderStrategy::PostorderStrategy()
";

%feature("docstring")  PostorderStrategy::clone "PostorderStrategy * PostorderStrategy::clone() const
";

%feature("docstring")  PostorderStrategy::~PostorderStrategy "PostorderStrategy::~PostorderStrategy()
";

%feature("docstring")  PostorderStrategy::first "IteratorMemento PostorderStrategy::first(const INode *p_root)
";

%feature("docstring")  PostorderStrategy::next "void PostorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  PostorderStrategy::isDone "bool PostorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classPreorderStrategy.xml
%feature("docstring") PreorderStrategy "

Traverse tree; visit parents before their children.

C++ includes: IterationStrategy.h
";

%feature("docstring")  PreorderStrategy::PreorderStrategy "PreorderStrategy::PreorderStrategy()
";

%feature("docstring")  PreorderStrategy::clone "PreorderStrategy * PreorderStrategy::clone() const
";

%feature("docstring")  PreorderStrategy::~PreorderStrategy "PreorderStrategy::~PreorderStrategy()
";

%feature("docstring")  PreorderStrategy::first "IteratorMemento PreorderStrategy::first(const INode *p_root)
";

%feature("docstring")  PreorderStrategy::next "void PreorderStrategy::next(IteratorMemento &iterator_stack) const
";

%feature("docstring")  PreorderStrategy::isDone "bool PreorderStrategy::isDone(IteratorMemento &iterator_stack) const
";


// File: classProcessedLayout.xml
%feature("docstring") ProcessedLayout "

Data structure that contains preprocessed data for a single layout.

If particles in the layout crossed the limits of the layer slices, these particles will be sliced themselves.

C++ includes: ProcessedLayout.h
";

%feature("docstring")  ProcessedLayout::ProcessedLayout "ProcessedLayout::ProcessedLayout(const ILayout &layout, const std::vector< Slice > &slices, double z_ref, const IFresnelMap *p_fresnel_map, bool polarized)
";

%feature("docstring")  ProcessedLayout::ProcessedLayout "ProcessedLayout::ProcessedLayout(ProcessedLayout &&other)
";

%feature("docstring")  ProcessedLayout::~ProcessedLayout "ProcessedLayout::~ProcessedLayout()
";

%feature("docstring")  ProcessedLayout::numberOfSlices "size_t ProcessedLayout::numberOfSlices() const
";

%feature("docstring")  ProcessedLayout::surfaceDensity "double ProcessedLayout::surfaceDensity() const
";

%feature("docstring")  ProcessedLayout::formFactorList "const std::vector< FormFactorCoherentSum > & ProcessedLayout::formFactorList() const
";

%feature("docstring")  ProcessedLayout::interferenceFunction "const IInterferenceFunction * ProcessedLayout::interferenceFunction() const
";

%feature("docstring")  ProcessedLayout::regionMap "std::map< size_t, std::vector< HomogeneousRegion > > ProcessedLayout::regionMap() const
";


// File: classProcessedSample.xml
%feature("docstring") ProcessedSample "

Data structure that contains all the necessary data for scattering calculations.

If the usage of average materials is requested, layers and particles are sliced into multiple slices and the average material is calculated for each slice.

C++ includes: ProcessedSample.h
";

%feature("docstring")  ProcessedSample::ProcessedSample "ProcessedSample::ProcessedSample(const MultiLayer &sample, const SimulationOptions &options)
";

%feature("docstring")  ProcessedSample::~ProcessedSample "ProcessedSample::~ProcessedSample()
";

%feature("docstring")  ProcessedSample::numberOfSlices "size_t ProcessedSample::numberOfSlices() const
";

%feature("docstring")  ProcessedSample::slices "const std::vector< Slice > & ProcessedSample::slices() const
";

%feature("docstring")  ProcessedSample::averageSlices "const std::vector< Slice > & ProcessedSample::averageSlices() const
";

%feature("docstring")  ProcessedSample::layouts "const std::vector< ProcessedLayout > & ProcessedSample::layouts() const
";

%feature("docstring")  ProcessedSample::fresnelMap "const IFresnelMap * ProcessedSample::fresnelMap() const
";

%feature("docstring")  ProcessedSample::crossCorrelationLength "double ProcessedSample::crossCorrelationLength() const
";

%feature("docstring")  ProcessedSample::externalField "kvector_t ProcessedSample::externalField() const
";

%feature("docstring")  ProcessedSample::bottomRoughness "const LayerRoughness * ProcessedSample::bottomRoughness(size_t i) const
";

%feature("docstring")  ProcessedSample::sliceTopZ "double ProcessedSample::sliceTopZ(size_t i) const
";

%feature("docstring")  ProcessedSample::sliceBottomZ "double ProcessedSample::sliceBottomZ(size_t i) const
";

%feature("docstring")  ProcessedSample::containsMagneticMaterial "bool ProcessedSample::containsMagneticMaterial() const
";

%feature("docstring")  ProcessedSample::hasRoughness "bool ProcessedSample::hasRoughness() const
";

%feature("docstring")  ProcessedSample::crossCorrSpectralFun "double ProcessedSample::crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const

Fourier transform of the correlation function of roughnesses between the interfaces 
";


// File: classProfileBar.xml
%feature("docstring") ProfileBar "

Base class for form factors with a cosine ripple profile in the yz plane.

C++ includes: ProfileBar.h
";

%feature("docstring")  ProfileBar::ProfileBar "ProfileBar::ProfileBar(double length, double width, double height)

Constructor of elongated bar.

Parameters:
-----------

length: 
length of the rectangular base in nanometers

width: 
width of the rectangular base in nanometers

height: 
height of the ripple in nanometers 
";

%feature("docstring")  ProfileBar::getLength "double ProfileBar::getLength() const
";

%feature("docstring")  ProfileBar::getHeight "double ProfileBar::getHeight() const
";

%feature("docstring")  ProfileBar::getWidth "double ProfileBar::getWidth() const
";

%feature("docstring")  ProfileBar::radialExtension "double ProfileBar::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  ProfileBar::evaluate_for_q "complex_t ProfileBar::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classProfileHelper.xml
%feature("docstring") ProfileHelper "";

%feature("docstring")  ProfileHelper::ProfileHelper "ProfileHelper::ProfileHelper(const ProcessedSample &sample)
";

%feature("docstring")  ProfileHelper::~ProfileHelper "ProfileHelper::~ProfileHelper()
";

%feature("docstring")  ProfileHelper::calculateProfile "std::vector< complex_t > ProfileHelper::calculateProfile(const std::vector< double > &z_values) const
";

%feature("docstring")  ProfileHelper::defaultLimits "std::pair< double, double > ProfileHelper::defaultLimits() const
";


// File: classProfileRipple1.xml
%feature("docstring") ProfileRipple1 "

Base class for form factors with a cosine ripple profile in the yz plane.

C++ includes: ProfileRipple1.h
";

%feature("docstring")  ProfileRipple1::ProfileRipple1 "ProfileRipple1::ProfileRipple1(double length, double width, double height)

Constructor of cosine ripple.

Parameters:
-----------

length: 
length of the rectangular base in nanometers

width: 
width of the rectangular base in nanometers

height: 
height of the ripple in nanometers 
";

%feature("docstring")  ProfileRipple1::getLength "double ProfileRipple1::getLength() const
";

%feature("docstring")  ProfileRipple1::getHeight "double ProfileRipple1::getHeight() const
";

%feature("docstring")  ProfileRipple1::getWidth "double ProfileRipple1::getWidth() const
";

%feature("docstring")  ProfileRipple1::radialExtension "double ProfileRipple1::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  ProfileRipple1::evaluate_for_q "complex_t ProfileRipple1::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
";


// File: classProfileRipple2.xml
%feature("docstring") ProfileRipple2 "

Base class for form factors with a cosine ripple profile in the yz plane.

C++ includes: ProfileRipple2.h
";

%feature("docstring")  ProfileRipple2::ProfileRipple2 "ProfileRipple2::ProfileRipple2(double length, double width, double height, double asymmetry)

Constructor of triangular ripple.

Parameters:
-----------

length: 
length of the rectangular base in nanometers

width: 
width of the rectangular base in nanometers

height: 
height of the ripple in nanometers 
";

%feature("docstring")  ProfileRipple2::getLength "double ProfileRipple2::getLength() const
";

%feature("docstring")  ProfileRipple2::getHeight "double ProfileRipple2::getHeight() const
";

%feature("docstring")  ProfileRipple2::getWidth "double ProfileRipple2::getWidth() const
";

%feature("docstring")  ProfileRipple2::getAsymmetry "double ProfileRipple2::getAsymmetry() const
";

%feature("docstring")  ProfileRipple2::radialExtension "double ProfileRipple2::radialExtension() const override final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  ProfileRipple2::evaluate_for_q "complex_t ProfileRipple2::evaluate_for_q(cvector_t q) const override final

Returns scattering amplitude for complex scattering wavevector q=k_i-k_f. This method is public only for convenience of plotting form factors in Python. 
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


// File: classPyBuilderCallback.xml
%feature("docstring") PyBuilderCallback "

Builds simulation object using a Python callable. Base class to wrap Python callable and pass it to C++. Used in swig interface file, intended to be overloaded from Python.

C++ includes: PyFittingCallbacks.h
";

%feature("docstring")  PyBuilderCallback::PyBuilderCallback "PyBuilderCallback::PyBuilderCallback()
";

%feature("docstring")  PyBuilderCallback::~PyBuilderCallback "PyBuilderCallback::~PyBuilderCallback()
";

%feature("docstring")  PyBuilderCallback::build_simulation "Simulation * PyBuilderCallback::build_simulation(Fit::Parameters)
";


// File: classPyObserverCallback.xml
%feature("docstring") PyObserverCallback "

Observer for  FitObjective based on Python callable. Base class to wrap Python callable and pass it to C++. Used in swig interface file, intended to be overloaded from Python.

C++ includes: PyFittingCallbacks.h
";

%feature("docstring")  PyObserverCallback::PyObserverCallback "PyObserverCallback::PyObserverCallback()
";

%feature("docstring")  PyObserverCallback::~PyObserverCallback "PyObserverCallback::~PyObserverCallback()
";

%feature("docstring")  PyObserverCallback::update "void PyObserverCallback::update(const FitObjective &)
";


// File: classPyramid3.xml
%feature("docstring") Pyramid3 "";

%feature("docstring")  Pyramid3::Pyramid3 "Pyramid3::Pyramid3(double length, double height, double alpha)
";

%feature("docstring")  Pyramid3::~Pyramid3 "Pyramid3::~Pyramid3()
";


// File: classPyramid6.xml
%feature("docstring") Pyramid6 "";

%feature("docstring")  Pyramid6::Pyramid6 "Pyramid6::Pyramid6(double length, double height, double alpha)
";

%feature("docstring")  Pyramid6::~Pyramid6 "Pyramid6::~Pyramid6()
";


// File: classQSpecScan.xml
%feature("docstring") QSpecScan "

Scan type with z-components of scattering vector as coordinate values. Wavelength and incident angles are not accessible separately.

C++ includes: QSpecScan.h
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(std::vector< double > qs_nm)

Accepts qz-value vector (in inverse nm) 
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(const IAxis &qs_nm)
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(int nbins, double qz_min, double qz_max)

Sets q-defined specular scan. Accepts either numpy array of q-values sorted in ascending order or an  IAxis object with q-values. Alternatively an axis can be defined in-place, then the first passed parameter is the number of bins, second - minimum on-axis q-value, third - maximum on-axis q_value. 
";

%feature("docstring")  QSpecScan::~QSpecScan "QSpecScan::~QSpecScan() override
";

%feature("docstring")  QSpecScan::clone "QSpecScan * QSpecScan::clone() const override
";

%feature("docstring")  QSpecScan::generateSimulationElements "std::vector< SpecularSimulationElement > QSpecScan::generateSimulationElements() const override

Generates simulation elements for specular simulations. 
";

%feature("docstring")  QSpecScan::coordinateAxis "virtual const IAxis* QSpecScan::coordinateAxis() const override

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  QSpecScan::footprintFactor "virtual const IFootprintFactor* QSpecScan::footprintFactor() const override

Returns  IFootprintFactor object pointer. 
";

%feature("docstring")  QSpecScan::footprint "std::vector< double > QSpecScan::footprint(size_t i, size_t n_elements) const override

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  QSpecScan::numberOfSimulationElements "size_t QSpecScan::numberOfSimulationElements() const override

Returns the number of simulation elements. 
";

%feature("docstring")  QSpecScan::createIntensities "std::vector< double > QSpecScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const override

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  QSpecScan::print "std::string QSpecScan::print() const override

Print scan definition in python format. 
";

%feature("docstring")  QSpecScan::setQResolution "void QSpecScan::setQResolution(const ScanResolution &resolution)

Sets q resolution values via  ScanResolution object. 
";

%feature("docstring")  QSpecScan::setRelativeQResolution "void QSpecScan::setRelativeQResolution(const RangedDistribution &distr, double rel_dev)
";

%feature("docstring")  QSpecScan::setRelativeQResolution "void QSpecScan::setRelativeQResolution(const RangedDistribution &distr, const std::vector< double > &rel_dev)

Sets qz resolution values via  RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets qz resolution values via  RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
";


// File: classRadialParaCrystalBuilder.xml
%feature("docstring") RadialParaCrystalBuilder "

Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RadialParaCrystalBuilder::RadialParaCrystalBuilder "RadialParaCrystalBuilder::RadialParaCrystalBuilder()
";

%feature("docstring")  RadialParaCrystalBuilder::buildSample "MultiLayer * RadialParaCrystalBuilder::buildSample() const
";


// File: classRangedDistribution.xml
%feature("docstring") RangedDistribution "

Interface for one-dimensional ranged distributions. All derived distributions allow for generating samples in-place for known mean and standard deviation (except for  RangedDistributionLorentz which uses median and hwhm).

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistribution::RangedDistribution "RangedDistribution::RangedDistribution()
";

%feature("docstring")  RangedDistribution::RangedDistribution "RangedDistribution::RangedDistribution(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistribution::RangedDistribution "RangedDistribution::RangedDistribution(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistribution::clone "RangedDistribution* RangedDistribution::clone() const override=0
";

%feature("docstring")  RangedDistribution::~RangedDistribution "RangedDistribution::~RangedDistribution() override
";

%feature("docstring")  RangedDistribution::generateSamples "std::vector< ParameterSample > RangedDistribution::generateSamples(double mean, double stddev) const
";

%feature("docstring")  RangedDistribution::generateSamples "std::vector< std::vector< ParameterSample > > RangedDistribution::generateSamples(const std::vector< double > &mean, const std::vector< double > &stddev) const

Generates list of sampled values with their weights from given means and standard deviations. 
";

%feature("docstring")  RangedDistribution::distribution "std::unique_ptr< IDistribution1D > RangedDistribution::distribution(double mean, double stddev) const

Public interface function to underlying  IDistribution1D object. 
";

%feature("docstring")  RangedDistribution::limits "RealLimits RangedDistribution::limits() const

Returns current limits of the distribution. 
";

%feature("docstring")  RangedDistribution::sigmaFactor "double RangedDistribution::sigmaFactor() const

Returns sigma factor to use during sampling. 
";

%feature("docstring")  RangedDistribution::nSamples "size_t RangedDistribution::nSamples() const

Returns number of samples to generate. 
";

%feature("docstring")  RangedDistribution::setLimits "void RangedDistribution::setLimits(const RealLimits &limits)
";

%feature("docstring")  RangedDistribution::print "std::string RangedDistribution::print() const

Prints python-formatted definition of the distribution. 
";


// File: classRangedDistributionCosine.xml
%feature("docstring") RangedDistributionCosine "

Cosine distribution.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionCosine::RangedDistributionCosine "RangedDistributionCosine::RangedDistributionCosine()
";

%feature("docstring")  RangedDistributionCosine::RangedDistributionCosine "RangedDistributionCosine::RangedDistributionCosine(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionCosine::RangedDistributionCosine "RangedDistributionCosine::RangedDistributionCosine(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionCosine::clone "RangedDistributionCosine * RangedDistributionCosine::clone() const override
";

%feature("docstring")  RangedDistributionCosine::~RangedDistributionCosine "RangedDistributionCosine::~RangedDistributionCosine() override=default
";


// File: classRangedDistributionGate.xml
%feature("docstring") RangedDistributionGate "

Uniform distribution function.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionGate::RangedDistributionGate "RangedDistributionGate::RangedDistributionGate()
";

%feature("docstring")  RangedDistributionGate::RangedDistributionGate "RangedDistributionGate::RangedDistributionGate(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionGate::RangedDistributionGate "RangedDistributionGate::RangedDistributionGate(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionGate::clone "RangedDistributionGate * RangedDistributionGate::clone() const override
";

%feature("docstring")  RangedDistributionGate::~RangedDistributionGate "RangedDistributionGate::~RangedDistributionGate() override=default
";


// File: classRangedDistributionGaussian.xml
%feature("docstring") RangedDistributionGaussian "

Gaussian distribution with standard deviation std_dev.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionGaussian::RangedDistributionGaussian "RangedDistributionGaussian::RangedDistributionGaussian()
";

%feature("docstring")  RangedDistributionGaussian::RangedDistributionGaussian "RangedDistributionGaussian::RangedDistributionGaussian(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionGaussian::RangedDistributionGaussian "RangedDistributionGaussian::RangedDistributionGaussian(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionGaussian::clone "RangedDistributionGaussian * RangedDistributionGaussian::clone() const override
";

%feature("docstring")  RangedDistributionGaussian::~RangedDistributionGaussian "RangedDistributionGaussian::~RangedDistributionGaussian() override=default
";


// File: classRangedDistributionLogNormal.xml
%feature("docstring") RangedDistributionLogNormal "

Log-normal distribution.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionLogNormal::RangedDistributionLogNormal "RangedDistributionLogNormal::RangedDistributionLogNormal()
";

%feature("docstring")  RangedDistributionLogNormal::RangedDistributionLogNormal "RangedDistributionLogNormal::RangedDistributionLogNormal(size_t n_samples, double sigma_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionLogNormal::RangedDistributionLogNormal "RangedDistributionLogNormal::RangedDistributionLogNormal(size_t n_samples, double sigma_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  sigma_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionLogNormal::clone "RangedDistributionLogNormal * RangedDistributionLogNormal::clone() const override
";

%feature("docstring")  RangedDistributionLogNormal::~RangedDistributionLogNormal "RangedDistributionLogNormal::~RangedDistributionLogNormal() override=default
";


// File: classRangedDistributionLorentz.xml
%feature("docstring") RangedDistributionLorentz "

Lorentz distribution with median and hwhm.

C++ includes: RangedDistributions.h
";

%feature("docstring")  RangedDistributionLorentz::RangedDistributionLorentz "RangedDistributionLorentz::RangedDistributionLorentz()
";

%feature("docstring")  RangedDistributionLorentz::RangedDistributionLorentz "RangedDistributionLorentz::RangedDistributionLorentz(size_t n_samples, double hwhm_factor, const RealLimits &limits=RealLimits::limitless())
";

%feature("docstring")  RangedDistributionLorentz::RangedDistributionLorentz "RangedDistributionLorentz::RangedDistributionLorentz(size_t n_samples, double hwhm_factor, double min, double max)

Initializes Ranged distribution with given number of samples, sigma factor (range in standard deviations to take into account during sample generation) and limits (either RealLimits object or just min and max limits). By default  n_samples = 5,  hwhm_factor = 2.0, while the limits are (-inf, +inf). 
";

%feature("docstring")  RangedDistributionLorentz::clone "RangedDistributionLorentz * RangedDistributionLorentz::clone() const override
";

%feature("docstring")  RangedDistributionLorentz::~RangedDistributionLorentz "RangedDistributionLorentz::~RangedDistributionLorentz() override=default
";


// File: classRealIntegrator.xml
%feature("docstring") RealIntegrator "

To integrate a real function of a real variable.

C++ includes: Integrator.h
";

%feature("docstring")  RealIntegrator::RealIntegrator "RealIntegrator::RealIntegrator()
";

%feature("docstring")  RealIntegrator::~RealIntegrator "RealIntegrator::~RealIntegrator()
";

%feature("docstring")  RealIntegrator::integrate "double RealIntegrator::integrate(const std::function< double(double)> &f, double lmin, double lmax)
";


// File: classRealParameter.xml
%feature("docstring") RealParameter "

Wraps a parameter of type double. In addition to name and on-change callback held by the parent class  IParameter, this class holds Limits, Attributes (currently only fixed or not), and a  Unit.

C++ includes: RealParameter.h
";

%feature("docstring")  RealParameter::RealParameter "RealParameter::RealParameter(const std::string &name, double *par, const std::string &parent_name=std::string(), const std::function< void()> &onChange=std::function< void()>(), const RealLimits &limits=RealLimits::limitless(), const Attributes &attr=Attributes::free())
";

%feature("docstring")  RealParameter::clone "RealParameter * RealParameter::clone(const std::string &new_name=\"\") const
";

%feature("docstring")  RealParameter::setValue "void RealParameter::setValue(double value)

Sets value of wrapped parameter and emit signal. 
";

%feature("docstring")  RealParameter::value "double RealParameter::value() const

Returns value of wrapped parameter. 
";

%feature("docstring")  RealParameter::setLimits "RealParameter & RealParameter::setLimits(const RealLimits &limits)
";

%feature("docstring")  RealParameter::limits "RealLimits RealParameter::limits() const
";

%feature("docstring")  RealParameter::setLimited "RealParameter & RealParameter::setLimited(double lower, double upper)
";

%feature("docstring")  RealParameter::setPositive "RealParameter & RealParameter::setPositive()
";

%feature("docstring")  RealParameter::setNonnegative "RealParameter & RealParameter::setNonnegative()
";

%feature("docstring")  RealParameter::setUnit "RealParameter & RealParameter::setUnit(const std::string &name)
";

%feature("docstring")  RealParameter::unit "std::string RealParameter::unit() const
";


// File: structLattice2D_1_1ReciprocalBases.xml
%feature("docstring") Lattice2D::ReciprocalBases "";


// File: structPrecomputed_1_1ReciprocalFactorial.xml
%feature("docstring") Precomputed::ReciprocalFactorial "";


// File: structPrecomputed_1_1ReciprocalFactorial_3_010_01_4.xml
%feature("docstring") Precomputed::ReciprocalFactorial< 0 > "
";


// File: classRectangle.xml
%feature("docstring") Rectangle "

The rectangle shape having its axis aligned to the (non-rotated) coordinate system.

C++ includes: Rectangle.h
";

%feature("docstring")  Rectangle::Rectangle "Rectangle::Rectangle(double xlow, double ylow, double xup, double yup)

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

%feature("docstring")  Rectangle::clone "Rectangle* Rectangle::clone() const
";

%feature("docstring")  Rectangle::contains "bool Rectangle::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Rectangle::contains "bool Rectangle::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  Rectangle::getArea "double Rectangle::getArea() const
";

%feature("docstring")  Rectangle::getXlow "double Rectangle::getXlow() const
";

%feature("docstring")  Rectangle::getYlow "double Rectangle::getYlow() const
";

%feature("docstring")  Rectangle::getXup "double Rectangle::getXup() const
";

%feature("docstring")  Rectangle::getYup "double Rectangle::getYup() const
";


// File: classRectangularConverter.xml
%feature("docstring") RectangularConverter "

IUnitConverter class that handles the unit translations for rectangular detectors Its default units are mm for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  RectangularConverter::RectangularConverter "RectangularConverter::RectangularConverter(const RectangularDetector &detector, const Beam &beam)
";

%feature("docstring")  RectangularConverter::~RectangularConverter "RectangularConverter::~RectangularConverter() override
";

%feature("docstring")  RectangularConverter::clone "RectangularConverter * RectangularConverter::clone() const override
";

%feature("docstring")  RectangularConverter::availableUnits "std::vector< AxesUnits > RectangularConverter::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  RectangularConverter::defaultUnits "AxesUnits RectangularConverter::defaultUnits() const override
";


// File: classRectangularDetector.xml
%feature("docstring") RectangularDetector "

A flat rectangular detector with axes and resolution function.

C++ includes: RectangularDetector.h
";

%feature("docstring")  RectangularDetector::RectangularDetector "RectangularDetector::RectangularDetector(size_t nxbins, double width, size_t nybins, double height)

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

%feature("docstring")  RectangularDetector::accept "void RectangularDetector::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
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

%feature("docstring")  RectangularDetector::defaultAxesUnits "AxesUnits RectangularDetector::defaultAxesUnits() const override

return default axes units 
";

%feature("docstring")  RectangularDetector::regionOfInterestPixel "RectangularPixel * RectangularDetector::regionOfInterestPixel() const
";


// File: classRectangularPixel.xml
%feature("docstring") RectangularPixel "";

%feature("docstring")  RectangularPixel::RectangularPixel "RectangularPixel::RectangularPixel(kvector_t corner_pos, kvector_t width, kvector_t height)
";

%feature("docstring")  RectangularPixel::clone "RectangularPixel * RectangularPixel::clone() const override
";

%feature("docstring")  RectangularPixel::createZeroSizePixel "RectangularPixel * RectangularPixel::createZeroSizePixel(double x, double y) const override
";

%feature("docstring")  RectangularPixel::getK "kvector_t RectangularPixel::getK(double x, double y, double wavelength) const override
";

%feature("docstring")  RectangularPixel::getPosition "kvector_t RectangularPixel::getPosition(double x, double y) const
";

%feature("docstring")  RectangularPixel::getIntegrationFactor "double RectangularPixel::getIntegrationFactor(double x, double y) const override
";

%feature("docstring")  RectangularPixel::getSolidAngle "double RectangularPixel::getSolidAngle() const override
";


// File: classRectParaCrystalBuilder.xml
%feature("docstring") RectParaCrystalBuilder "

Builds sample: 2D paracrystal lattice (IsGISAXS example #8).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RectParaCrystalBuilder::RectParaCrystalBuilder "RectParaCrystalBuilder::RectParaCrystalBuilder()
";

%feature("docstring")  RectParaCrystalBuilder::buildSample "MultiLayer * RectParaCrystalBuilder::buildSample() const
";


// File: classRefractiveMaterialImpl.xml
%feature("docstring") RefractiveMaterialImpl "

Material implementation based on refractive coefficiencts (valid for one wavelength value only)

C++ includes: RefractiveMaterialImpl.h
";

%feature("docstring")  RefractiveMaterialImpl::~RefractiveMaterialImpl "virtual RefractiveMaterialImpl::~RefractiveMaterialImpl()=default
";

%feature("docstring")  RefractiveMaterialImpl::clone "RefractiveMaterialImpl * RefractiveMaterialImpl::clone() const override

Returns pointer to a copy of material. 
";

%feature("docstring")  RefractiveMaterialImpl::refractiveIndex "complex_t RefractiveMaterialImpl::refractiveIndex(double wavelength) const override

Returns refractive index For this particular implementation returned value does not depend on passed wavelength 
";

%feature("docstring")  RefractiveMaterialImpl::refractiveIndex2 "complex_t RefractiveMaterialImpl::refractiveIndex2(double wavelength) const override

Returns squared refractive index. For this particular implementation returned value does not depend on passed wavelength. 
";

%feature("docstring")  RefractiveMaterialImpl::materialData "complex_t RefractiveMaterialImpl::materialData() const override

Returns underlying material data. 
";

%feature("docstring")  RefractiveMaterialImpl::typeID "MATERIAL_TYPES RefractiveMaterialImpl::typeID() const override

Returns type of material implementation. 
";

%feature("docstring")  RefractiveMaterialImpl::scalarSubtrSLD "complex_t RefractiveMaterialImpl::scalarSubtrSLD(const WavevectorInfo &wavevectors) const override

Returns (  $ \\\\pi/\\\\lambda^2 $ - sld), sld (in  $nm^{-2}$) being the scattering length density. If the wavelength associated with passed wavevector is different from the one associated with refractive coefficients used during the object construction, provided result is inconsistent. 
";

%feature("docstring")  RefractiveMaterialImpl::print "void RefractiveMaterialImpl::print(std::ostream &ostr) const override

Prints object data. 
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


// File: classRelativeDifferenceMetric.xml
%feature("docstring") RelativeDifferenceMetric "

Implementation of relative difference metric. With default L2 norm and weighting off corresponds to the formula  \\\\[Result = \\\\sum \\\\frac{(I - D)^2}{(I + D)^2}\\\\] where  $I$ is the simulated intensity,  $D$ - experimental data. If weighting is on, falls back to the standard  $\\\\chi^2$ metric.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  RelativeDifferenceMetric::RelativeDifferenceMetric "RelativeDifferenceMetric::RelativeDifferenceMetric()
";

%feature("docstring")  RelativeDifferenceMetric::clone "RelativeDifferenceMetric * RelativeDifferenceMetric::clone() const override
";

%feature("docstring")  RelativeDifferenceMetric::computeFromArrays "double RelativeDifferenceMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  RelativeDifferenceMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  RelativeDifferenceMetric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
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

%feature("docstring")  ResolutionFunction2DGaussian::accept "void ResolutionFunction2DGaussian::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaX "double ResolutionFunction2DGaussian::getSigmaX() const
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaY "double ResolutionFunction2DGaussian::getSigmaY() const
";


// File: classResonatorBuilder.xml
%feature("docstring") ResonatorBuilder "

Builds sample: multilayer with Ti/Pt layers sequence.

C++ includes: ResonatorBuilder.h
";

%feature("docstring")  ResonatorBuilder::ResonatorBuilder "ResonatorBuilder::ResonatorBuilder()
";

%feature("docstring")  ResonatorBuilder::buildSample "MultiLayer * ResonatorBuilder::buildSample() const
";


// File: classRippleCosine.xml
%feature("docstring") RippleCosine "";

%feature("docstring")  RippleCosine::RippleCosine "RippleCosine::RippleCosine(double length, double width, double height)
";

%feature("docstring")  RippleCosine::~RippleCosine "RippleCosine::~RippleCosine()
";


// File: classRippleSawtooth.xml
%feature("docstring") RippleSawtooth "";

%feature("docstring")  RippleSawtooth::RippleSawtooth "RippleSawtooth::RippleSawtooth(double length, double width, double height, double asymmetry)
";

%feature("docstring")  RippleSawtooth::~RippleSawtooth "RippleSawtooth::~RippleSawtooth()
";


// File: classRotatedCylindersBuilder.xml
%feature("docstring") RotatedCylindersBuilder "

Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  RotatedCylindersBuilder::RotatedCylindersBuilder "RotatedCylindersBuilder::RotatedCylindersBuilder()
";

%feature("docstring")  RotatedCylindersBuilder::buildSample "MultiLayer * RotatedCylindersBuilder::buildSample() const
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


// File: classRotatedPyramidsDistributionBuilder.xml
%feature("docstring") RotatedPyramidsDistributionBuilder "

Rotated Pyramids with the distribution applied to the rotation angle.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  RotatedPyramidsDistributionBuilder::RotatedPyramidsDistributionBuilder "RotatedPyramidsDistributionBuilder::RotatedPyramidsDistributionBuilder()
";

%feature("docstring")  RotatedPyramidsDistributionBuilder::buildSample "MultiLayer * RotatedPyramidsDistributionBuilder::buildSample() const
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

Constructor of Euler rotation (sequence of three rotations following Euler angles notation z-x'-z').

Parameters:
-----------

alpha: 
first Euler angle in radians

beta: 
second Euler angle in radians

gamma: 
third Euler angle in radians 
";

%feature("docstring")  RotationEuler::clone "RotationEuler* RotationEuler::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationEuler::createInverse "IRotation * RotationEuler::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationEuler::accept "void RotationEuler::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
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

Constructor of rotation around x-axis

Parameters:
-----------

angle: 
rotation angle around x-axis in radians 
";

%feature("docstring")  RotationX::clone "RotationX* RotationX::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationX::createInverse "RotationX* RotationX::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationX::accept "void RotationX::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  RotationX::getAngle "double RotationX::getAngle() const
";

%feature("docstring")  RotationX::getTransform3D "Transform3D RotationX::getTransform3D() const

Returns transformation. 
";


// File: classRotationY.xml
%feature("docstring") RotationY "";

%feature("docstring")  RotationY::RotationY "RotationY::RotationY(double angle)

Constructor of rotation around y-axis

Parameters:
-----------

angle: 
rotation angle around y-axis in radians 
";

%feature("docstring")  RotationY::clone "RotationY* RotationY::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationY::createInverse "RotationY* RotationY::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationY::accept "void RotationY::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  RotationY::getAngle "double RotationY::getAngle() const
";

%feature("docstring")  RotationY::getTransform3D "Transform3D RotationY::getTransform3D() const

Returns transformation. 
";


// File: classRotationZ.xml
%feature("docstring") RotationZ "";

%feature("docstring")  RotationZ::RotationZ "RotationZ::RotationZ(double angle=0.0)

Constructor of rotation around z-axis

Parameters:
-----------

angle: 
rotation angle around z-axis in radians 
";

%feature("docstring")  RotationZ::clone "RotationZ* RotationZ::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  RotationZ::createInverse "RotationZ* RotationZ::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationZ::accept "void RotationZ::accept(INodeVisitor *visitor) const

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  RotationZ::getAngle "double RotationZ::getAngle() const
";

%feature("docstring")  RotationZ::getTransform3D "Transform3D RotationZ::getTransform3D() const

Returns transformation. 
";


// File: classRoughMultiLayerComputation.xml
%feature("docstring") RoughMultiLayerComputation "

Computes the diffuse reflection from the rough interfaces of a multilayer. Used by  DWBAComputation.

C++ includes: RoughMultiLayerComputation.h
";

%feature("docstring")  RoughMultiLayerComputation::RoughMultiLayerComputation "RoughMultiLayerComputation::RoughMultiLayerComputation(const ProcessedSample *p_sample)
";

%feature("docstring")  RoughMultiLayerComputation::compute "void RoughMultiLayerComputation::compute(SimulationElement &elem) const
";


// File: structRoughnessModelWrap.xml
%feature("docstring") RoughnessModelWrap "";


// File: classRQ4Metric.xml
%feature("docstring") RQ4Metric "

Implementation of relative difference metric. With default L2 norm and weighting off corresponds to the formula  \\\\[Result = \\\\sum (I \\\\cdot Q^4 - D \\\\cdot Q^4)^2\\\\] where  $Q$ is the scattering vector magnitude. If weighting is on, coincides with the metric provided by  Chi2Metric class.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  RQ4Metric::RQ4Metric "RQ4Metric::RQ4Metric()
";

%feature("docstring")  RQ4Metric::clone "RQ4Metric * RQ4Metric::clone() const override
";

%feature("docstring")  RQ4Metric::compute "double RQ4Metric::compute(const SimDataPair &data_pair, bool use_weights) const override

Computes metric value from  SimDataPair object. Calls computeFromArrays internally.

Parameters:
-----------

data_pair: 
 SimDataPair object. Can optionally contain data uncertainties

use_weights: 
boolean, defines if data uncertainties should be taken into account 
";


// File: classExceptions_1_1RuntimeErrorException.xml
%feature("docstring") Exceptions::RuntimeErrorException "";

%feature("docstring")  Exceptions::RuntimeErrorException::RuntimeErrorException "Exceptions::RuntimeErrorException::RuntimeErrorException(const std::string &message)
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

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector(SafePointerVector &&other)
";

%feature("docstring")  SafePointerVector::~SafePointerVector "SafePointerVector< T >::~SafePointerVector()
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

Factory to create standard pre-defined samples

C++ includes: SampleBuilderFactory.h
";

%feature("docstring")  SampleBuilderFactory::SampleBuilderFactory "SampleBuilderFactory::SampleBuilderFactory()
";

%feature("docstring")  SampleBuilderFactory::createSample "MultiLayer * SampleBuilderFactory::createSample(const std::string &name)

Retrieves a SampleBuilder from the registry, does the build, and returns the result. 
";


// File: classSampleBuilderNode.xml
%feature("docstring") SampleBuilderNode "

Enfolds MultiLayerBuilder to have it in  INode tree.

C++ includes: SampleBuilderNode.h
";

%feature("docstring")  SampleBuilderNode::SampleBuilderNode "SampleBuilderNode::SampleBuilderNode()
";

%feature("docstring")  SampleBuilderNode::SampleBuilderNode "SampleBuilderNode::SampleBuilderNode(const SampleBuilderNode &other)
";

%feature("docstring")  SampleBuilderNode::setSampleBuilder "void SampleBuilderNode::setSampleBuilder(builder_t sample_builder)

Sets sample builder and borrows its parameters. 
";

%feature("docstring")  SampleBuilderNode::reset "void SampleBuilderNode::reset()

Resets to initial state by removing builder and its borrowed parameters. 
";

%feature("docstring")  SampleBuilderNode::accept "void SampleBuilderNode::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  SampleBuilderNode::createMultiLayer "std::unique_ptr< MultiLayer > SampleBuilderNode::createMultiLayer()

Creates a multilayer using sample builder. 
";

%feature("docstring")  SampleBuilderNode::builder "SampleBuilderNode::builder_t SampleBuilderNode::builder() const

Returns current sample builder. 
";


// File: classSampleLabelHandler.xml
%feature("docstring") SampleLabelHandler "

The handler which construct labels for sample variables during python script generation.

C++ includes: SampleLabelHandler.h
";

%feature("docstring")  SampleLabelHandler::SampleLabelHandler "SampleLabelHandler::SampleLabelHandler()
";

%feature("docstring")  SampleLabelHandler::crystalMap "crystals_t* SampleLabelHandler::crystalMap()
";

%feature("docstring")  SampleLabelHandler::formFactorMap "formfactors_t* SampleLabelHandler::formFactorMap()
";

%feature("docstring")  SampleLabelHandler::interferenceFunctionMap "interferences_t* SampleLabelHandler::interferenceFunctionMap()
";

%feature("docstring")  SampleLabelHandler::layerMap "layers_t* SampleLabelHandler::layerMap()
";

%feature("docstring")  SampleLabelHandler::particleLayoutMap "layouts_t* SampleLabelHandler::particleLayoutMap()
";

%feature("docstring")  SampleLabelHandler::materialMap "materials_t* SampleLabelHandler::materialMap()
";

%feature("docstring")  SampleLabelHandler::latticeMap "lattices_t* SampleLabelHandler::latticeMap()
";

%feature("docstring")  SampleLabelHandler::mesocrystalMap "mesocrystals_t* SampleLabelHandler::mesocrystalMap()
";

%feature("docstring")  SampleLabelHandler::multiLayerMap "multilayers_t* SampleLabelHandler::multiLayerMap()
";

%feature("docstring")  SampleLabelHandler::particleCompositionMap "particlecompositions_t* SampleLabelHandler::particleCompositionMap()
";

%feature("docstring")  SampleLabelHandler::particleDistributionsMap "particledistributions_t* SampleLabelHandler::particleDistributionsMap()
";

%feature("docstring")  SampleLabelHandler::particleMap "particles_t* SampleLabelHandler::particleMap()
";

%feature("docstring")  SampleLabelHandler::particleCoreShellMap "particlescoreshell_t* SampleLabelHandler::particleCoreShellMap()
";

%feature("docstring")  SampleLabelHandler::rotationsMap "rotations_t* SampleLabelHandler::rotationsMap()
";

%feature("docstring")  SampleLabelHandler::layerRoughnessMap "roughnesses_t* SampleLabelHandler::layerRoughnessMap()
";

%feature("docstring")  SampleLabelHandler::labelCrystal "std::string SampleLabelHandler::labelCrystal(const Crystal *sample)
";

%feature("docstring")  SampleLabelHandler::labelFormFactor "std::string SampleLabelHandler::labelFormFactor(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::labelInterferenceFunction "std::string SampleLabelHandler::labelInterferenceFunction(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::labelLayer "std::string SampleLabelHandler::labelLayer(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::labelLayout "std::string SampleLabelHandler::labelLayout(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::labelMaterial "std::string SampleLabelHandler::labelMaterial(const Material *sample)
";

%feature("docstring")  SampleLabelHandler::labelLattice "std::string SampleLabelHandler::labelLattice(const Lattice *sample)
";

%feature("docstring")  SampleLabelHandler::labelMultiLayer "std::string SampleLabelHandler::labelMultiLayer(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::labelParticle "std::string SampleLabelHandler::labelParticle(const IAbstractParticle *sample)
";

%feature("docstring")  SampleLabelHandler::labelRotation "std::string SampleLabelHandler::labelRotation(const IRotation *sample)
";

%feature("docstring")  SampleLabelHandler::labelRoughness "std::string SampleLabelHandler::labelRoughness(const LayerRoughness *sample)
";

%feature("docstring")  SampleLabelHandler::insertCrystal "void SampleLabelHandler::insertCrystal(const Crystal *sample)
";

%feature("docstring")  SampleLabelHandler::insertFormFactor "void SampleLabelHandler::insertFormFactor(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::insertInterferenceFunction "void SampleLabelHandler::insertInterferenceFunction(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::insertLayer "void SampleLabelHandler::insertLayer(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::insertLayout "void SampleLabelHandler::insertLayout(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::insertMaterial "void SampleLabelHandler::insertMaterial(const Material *sample)
";

%feature("docstring")  SampleLabelHandler::insertLattice "void SampleLabelHandler::insertLattice(const Lattice *sample)
";

%feature("docstring")  SampleLabelHandler::insertMesoCrystal "void SampleLabelHandler::insertMesoCrystal(const MesoCrystal *sample)
";

%feature("docstring")  SampleLabelHandler::insertMultiLayer "void SampleLabelHandler::insertMultiLayer(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleComposition "void SampleLabelHandler::insertParticleComposition(const ParticleComposition *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleDistribution "void SampleLabelHandler::insertParticleDistribution(const ParticleDistribution *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticle "void SampleLabelHandler::insertParticle(const Particle *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleCoreShell "void SampleLabelHandler::insertParticleCoreShell(const ParticleCoreShell *sample)
";

%feature("docstring")  SampleLabelHandler::insertRotation "void SampleLabelHandler::insertRotation(const IRotation *sample)
";

%feature("docstring")  SampleLabelHandler::insertRoughness "void SampleLabelHandler::insertRoughness(const LayerRoughness *sample)
";


// File: classSampleProvider.xml
%feature("docstring") SampleProvider "

Gives access to the sample to simulate. Sample can come either directly from the user or from SampleBuilder.

C++ includes: SampleProvider.h
";

%feature("docstring")  SampleProvider::SampleProvider "SampleProvider::SampleProvider()
";

%feature("docstring")  SampleProvider::SampleProvider "SampleProvider::SampleProvider(const SampleProvider &other)
";

%feature("docstring")  SampleProvider::~SampleProvider "SampleProvider::~SampleProvider()
";

%feature("docstring")  SampleProvider::setSample "void SampleProvider::setSample(const MultiLayer &multilayer)
";

%feature("docstring")  SampleProvider::setSampleBuilder "void SampleProvider::setSampleBuilder(const std::shared_ptr< IMultiLayerBuilder > sample_builder)
";

%feature("docstring")  SampleProvider::sample "const MultiLayer * SampleProvider::sample() const

Returns current sample. 
";

%feature("docstring")  SampleProvider::updateSample "void SampleProvider::updateSample()

Generates new sample if sample builder defined. 
";

%feature("docstring")  SampleProvider::getChildren "std::vector< const INode * > SampleProvider::getChildren() const override

Returns a vector of children (const). 
";

%feature("docstring")  SampleProvider::accept "void SampleProvider::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  SampleProvider::setParent "void SampleProvider::setParent(const INode *newParent) override
";


// File: classSampleToPython.xml
%feature("docstring") SampleToPython "

Generates Python code snippet from domain (C++) objects representing sample construction.

C++ includes: SampleToPython.h
";

%feature("docstring")  SampleToPython::SampleToPython "SampleToPython::SampleToPython()
";

%feature("docstring")  SampleToPython::~SampleToPython "SampleToPython::~SampleToPython()
";

%feature("docstring")  SampleToPython::generateSampleCode "std::string SampleToPython::generateSampleCode(const MultiLayer &multilayer)
";


// File: classScalarFresnelMap.xml
%feature("docstring") ScalarFresnelMap "

Implementation of  IFresnelMap for scalar valued reflection/transmission coefficients.

C++ includes: ScalarFresnelMap.h
";

%feature("docstring")  ScalarFresnelMap::ScalarFresnelMap "ScalarFresnelMap::ScalarFresnelMap(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  ScalarFresnelMap::~ScalarFresnelMap "ScalarFresnelMap::~ScalarFresnelMap() final
";

%feature("docstring")  ScalarFresnelMap::ScalarFresnelMap "ScalarFresnelMap::ScalarFresnelMap(const ScalarFresnelMap &other)=delete
";

%feature("docstring")  ScalarFresnelMap::getOutCoefficients "std::unique_ptr< const ILayerRTCoefficients > ScalarFresnelMap::getOutCoefficients(const SimulationElement &sim_element, size_t layer_index) const override

Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector. 
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


// File: classScanResolution.xml
%feature("docstring") ScanResolution "

Container for reflectivity resolution data.

C++ includes: ScanResolution.h
";

%feature("docstring")  ScanResolution::~ScanResolution "ScanResolution::~ScanResolution() override
";

%feature("docstring")  ScanResolution::clone "ScanResolution* ScanResolution::clone() const override=0
";

%feature("docstring")  ScanResolution::distribution "const RangedDistribution* ScanResolution::distribution() const
";

%feature("docstring")  ScanResolution::nSamples "size_t ScanResolution::nSamples() const
";

%feature("docstring")  ScanResolution::generateSamples "virtual DistrOutput ScanResolution::generateSamples(double mean, size_t n_times) const =0
";

%feature("docstring")  ScanResolution::generateSamples "virtual DistrOutput ScanResolution::generateSamples(const std::vector< double > &mean) const =0
";

%feature("docstring")  ScanResolution::stdDevs "virtual std::vector<double> ScanResolution::stdDevs(double mean, size_t n_times) const =0
";

%feature("docstring")  ScanResolution::stdDevs "virtual std::vector<double> ScanResolution::stdDevs(const std::vector< double > &mean) const =0
";

%feature("docstring")  ScanResolution::empty "bool ScanResolution::empty() const
";

%feature("docstring")  ScanResolution::print "std::string ScanResolution::print() const

Prints object definition in python format. 
";


// File: classSimDataPair.xml
%feature("docstring") SimDataPair "

Holds pair of simulation/experimental data to fit.

C++ includes: SimDataPair.h
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, double user_weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

simulation: 
simulation builder capable of producing simulations

data: 
experimental data

uncertainties: 
uncertainties associated with experimental data

user_weight: 
weight of dataset in objective metric computations 
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, std::unique_ptr< OutputData< double >> user_weights)

Constructs simulation/data pair for later fit.

Parameters:
-----------

simulation: 
simulation builder capable of producing simulations

data: 
experimental data

uncertainties: 
uncertainties associated with experimental data

user_weights: 
user weights associated with experimental data 
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(SimDataPair &&other)
";

%feature("docstring")  SimDataPair::~SimDataPair "SimDataPair::~SimDataPair()
";

%feature("docstring")  SimDataPair::runSimulation "void SimDataPair::runSimulation(const Fit::Parameters &params)
";

%feature("docstring")  SimDataPair::containsUncertainties "bool SimDataPair::containsUncertainties() const
";

%feature("docstring")  SimDataPair::numberOfFitElements "size_t SimDataPair::numberOfFitElements() const

Returns the number of elements in the fit area. 
";

%feature("docstring")  SimDataPair::simulationResult "SimulationResult SimDataPair::simulationResult() const

Returns the result of last computed simulation. 
";

%feature("docstring")  SimDataPair::experimentalData "SimulationResult SimDataPair::experimentalData() const

Returns the experimental data cut to the ROI area. 
";

%feature("docstring")  SimDataPair::uncertainties "SimulationResult SimDataPair::uncertainties() const

Returns the data uncertainties cut to the ROI area If no uncertainties present, returns zero-filled  SimulationResult. 
";

%feature("docstring")  SimDataPair::userWeights "SimulationResult SimDataPair::userWeights() const

Returns the user uncertainties cut to the ROI area. 
";

%feature("docstring")  SimDataPair::relativeDifference "SimulationResult SimDataPair::relativeDifference() const

Returns relative difference between simulation and experimental data.

Returns the relative difference between simulated and expeimental data cut to the ROI area 
";

%feature("docstring")  SimDataPair::absoluteDifference "SimulationResult SimDataPair::absoluteDifference() const

Returns the absolute difference between simulated and expeimental data cut to the ROI area 
";

%feature("docstring")  SimDataPair::simulation_array "std::vector< double > SimDataPair::simulation_array() const

Returns the flattened simulated intensities cut to the ROI area 
";

%feature("docstring")  SimDataPair::experimental_array "std::vector< double > SimDataPair::experimental_array() const

Returns the flattened experimental data cut to the ROI area 
";

%feature("docstring")  SimDataPair::uncertainties_array "std::vector< double > SimDataPair::uncertainties_array() const

Returns the flattened experimental uncertainties cut to the ROI area. If no uncertainties are available, returns a zero-filled array sized to the ROI area. 
";

%feature("docstring")  SimDataPair::user_weights_array "std::vector< double > SimDataPair::user_weights_array() const

Returns a flat array of user weights cut to the ROI area. 
";


// File: classSimpleMagneticLayerBuilder.xml
%feature("docstring") SimpleMagneticLayerBuilder "

Builds sample: ambient and one magnetized layer on a non-magnetized substrate.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  SimpleMagneticLayerBuilder::SimpleMagneticLayerBuilder "SimpleMagneticLayerBuilder::SimpleMagneticLayerBuilder()
";

%feature("docstring")  SimpleMagneticLayerBuilder::buildSample "MultiLayer * SimpleMagneticLayerBuilder::buildSample() const
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

Pure virtual base class of OffSpecularSimulation,  GISASSimulation and  SpecularSimulation. Holds the common infrastructure to run a simulation: multithreading, batch processing, weighting over parameter distributions, ...

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

%feature("docstring")  Simulation::runMPISimulation "void Simulation::runMPISimulation()

Run a simulation in a MPI environment. 
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

%feature("docstring")  Simulation::sample "const MultiLayer * Simulation::sample() const
";

%feature("docstring")  Simulation::setSampleBuilder "void Simulation::setSampleBuilder(const std::shared_ptr< IMultiLayerBuilder > sample_builder)
";

%feature("docstring")  Simulation::setBackground "void Simulation::setBackground(const IBackground &bg)
";

%feature("docstring")  Simulation::background "const IBackground* Simulation::background() const
";

%feature("docstring")  Simulation::intensityMapSize "virtual size_t Simulation::intensityMapSize() const =0

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  Simulation::result "virtual SimulationResult Simulation::result() const =0

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
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

%feature("docstring")  Simulation::getChildren "std::vector< const INode * > Simulation::getChildren() const

Returns a vector of children (const). 
";


// File: classSimulation2D.xml
%feature("docstring") Simulation2D "

Pure virtual base class of OffSpecularSimulation and  GISASSimulation. Holds the common implementations for simulations with a 2D detector

C++ includes: Simulation2D.h
";

%feature("docstring")  Simulation2D::Simulation2D "Simulation2D::Simulation2D()
";

%feature("docstring")  Simulation2D::Simulation2D "Simulation2D::Simulation2D(const MultiLayer &p_sample)
";

%feature("docstring")  Simulation2D::Simulation2D "Simulation2D::Simulation2D(const std::shared_ptr< IMultiLayerBuilder > p_sample_builder)
";

%feature("docstring")  Simulation2D::~Simulation2D "Simulation2D::~Simulation2D() override
";

%feature("docstring")  Simulation2D::clone "Simulation2D* Simulation2D::clone() const override=0
";

%feature("docstring")  Simulation2D::prepareSimulation "void Simulation2D::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  Simulation2D::setDetectorParameters "void Simulation2D::setDetectorParameters(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

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

%feature("docstring")  Simulation2D::setDetector "void Simulation2D::setDetector(const IDetector2D &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  Simulation2D::removeMasks "void Simulation2D::removeMasks()

removes all masks from the detector 
";

%feature("docstring")  Simulation2D::addMask "void Simulation2D::addMask(const IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask ( Rectangle,  Polygon,  Line,  Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  Simulation2D::maskAll "void Simulation2D::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  Simulation2D::setRegionOfInterest "void Simulation2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)

Sets rectangular region of interest with lower left and upper right corners defined. 
";


// File: classSimulationArea.xml
%feature("docstring") SimulationArea "

Holds iteration logic over active detector channels in the presence of masked areas and  RegionOfInterest defined.

C++ includes: SimulationArea.h
";

%feature("docstring")  SimulationArea::SimulationArea "SimulationArea::SimulationArea(const IDetector *detector)
";

%feature("docstring")  SimulationArea::~SimulationArea "virtual SimulationArea::~SimulationArea()
";

%feature("docstring")  SimulationArea::begin "SimulationAreaIterator SimulationArea::begin()
";

%feature("docstring")  SimulationArea::end "SimulationAreaIterator SimulationArea::end()
";

%feature("docstring")  SimulationArea::isMasked "bool SimulationArea::isMasked(size_t index) const

returns true if given iterator index correspond to masked detector channel 
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

%feature("docstring")  SimulationAreaIterator::roiIndex "size_t SimulationAreaIterator::roiIndex() const
";

%feature("docstring")  SimulationAreaIterator::detectorIndex "size_t SimulationAreaIterator::detectorIndex() const
";


// File: classSimulationElement.xml
%feature("docstring") SimulationElement "

Data stucture containing both input and output of a single detector cell.

C++ includes: SimulationElement.h
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i, std::unique_ptr< IPixel > pixel)
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

%feature("docstring")  SimulationElement::setAnalyzerOperator "void SimulationElement::setAnalyzerOperator(const Eigen::Matrix2cd &polarization_operator)

Sets the polarization analyzer operator (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::polarizationHandler "const PolarizationHandler& SimulationElement::polarizationHandler() const

Returns assigned  PolarizationHandler. 
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

%feature("docstring")  SimulationElement::getKi "kvector_t SimulationElement::getKi() const
";

%feature("docstring")  SimulationElement::getMeanKf "kvector_t SimulationElement::getMeanKf() const
";

%feature("docstring")  SimulationElement::getMeanQ "kvector_t SimulationElement::getMeanQ() const
";

%feature("docstring")  SimulationElement::getQ "kvector_t SimulationElement::getQ(double x, double y) const

Returns scattering vector Q, with Kf determined from in-pixel coordinates x,y. In-pixel coordinates take values from 0 to 1. 
";

%feature("docstring")  SimulationElement::getIntegrationFactor "double SimulationElement::getIntegrationFactor(double x, double y) const
";

%feature("docstring")  SimulationElement::getSolidAngle "double SimulationElement::getSolidAngle() const
";

%feature("docstring")  SimulationElement::getAlpha "double SimulationElement::getAlpha(double x, double y) const
";

%feature("docstring")  SimulationElement::getPhi "double SimulationElement::getPhi(double x, double y) const
";

%feature("docstring")  SimulationElement::setSpecular "void SimulationElement::setSpecular(bool is_specular)

Set specularity indication on/off. 
";

%feature("docstring")  SimulationElement::isSpecular "bool SimulationElement::isSpecular() const

Tells if simulation element corresponds to a specular peak. 
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

Collect the different options for simulation.

SimulationOptions

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

%feature("docstring")  SimulationOptions::getNumberOfThreads "unsigned SimulationOptions::getNumberOfThreads() const
";

%feature("docstring")  SimulationOptions::setNumberOfBatches "void SimulationOptions::setNumberOfBatches(int nbatches)

Sets number of batches to split. 
";

%feature("docstring")  SimulationOptions::getNumberOfBatches "unsigned SimulationOptions::getNumberOfBatches() const
";

%feature("docstring")  SimulationOptions::getCurrentBatch "unsigned SimulationOptions::getCurrentBatch() const
";

%feature("docstring")  SimulationOptions::setThreadInfo "void SimulationOptions::setThreadInfo(const ThreadInfo &thread_info)

Sets the batch and thread information to be used. 
";

%feature("docstring")  SimulationOptions::getHardwareConcurrency "unsigned SimulationOptions::getHardwareConcurrency() const
";

%feature("docstring")  SimulationOptions::setIncludeSpecular "void SimulationOptions::setIncludeSpecular(bool include_specular)
";

%feature("docstring")  SimulationOptions::includeSpecular "bool SimulationOptions::includeSpecular() const
";

%feature("docstring")  SimulationOptions::setUseAvgMaterials "void SimulationOptions::setUseAvgMaterials(bool use_avg_materials)
";

%feature("docstring")  SimulationOptions::useAvgMaterials "bool SimulationOptions::useAvgMaterials() const
";


// File: classSimulationResult.xml
%feature("docstring") SimulationResult "

Wrapper around  OutputData<double> that also provides unit conversions.

C++ includes: SimulationResult.h
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult()=default
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult(const OutputData< double > &data, const IUnitConverter &unit_converter)
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult(const SimulationResult &other)
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult(SimulationResult &&other)
";

%feature("docstring")  SimulationResult::data "std::unique_ptr< OutputData< double > > SimulationResult::data(AxesUnits units=AxesUnits::DEFAULT) const
";

%feature("docstring")  SimulationResult::histogram2d "Histogram2D * SimulationResult::histogram2d(AxesUnits units=AxesUnits::DEFAULT) const
";

%feature("docstring")  SimulationResult::axisInfo "std::vector< AxisInfo > SimulationResult::axisInfo(AxesUnits units=AxesUnits::DEFAULT) const

Provide  AxisInfo for each axis and the given units. 
";

%feature("docstring")  SimulationResult::converter "const IUnitConverter & SimulationResult::converter() const

Returns underlying unit converter. 
";

%feature("docstring")  SimulationResult::size "size_t SimulationResult::size() const
";

%feature("docstring")  SimulationResult::array "PyObject * SimulationResult::array(AxesUnits units=AxesUnits::DEFAULT) const

returns intensity data as Python numpy array 
";

%feature("docstring")  SimulationResult::axis "std::vector< double > SimulationResult::axis(AxesUnits units=AxesUnits::DEFAULT) const
";

%feature("docstring")  SimulationResult::axis "std::vector< double > SimulationResult::axis(size_t i_axis, AxesUnits units=AxesUnits::DEFAULT) const

Returns axis coordinates as a numpy array. With no parameters given returns coordinates of x-axis in default units. 
";


// File: classSimulationRoiArea.xml
%feature("docstring") SimulationRoiArea "

Holds iteration logic over active detector channels in the presence of ROI. On the contrary to  SimulationArea class, iterates also over masked areas.

C++ includes: SimulationArea.h
";

%feature("docstring")  SimulationRoiArea::SimulationRoiArea "SimulationRoiArea::SimulationRoiArea(const IDetector *detector)
";

%feature("docstring")  SimulationRoiArea::isMasked "bool SimulationRoiArea::isMasked(size_t) const

returns true if given iterator index correspond to masked detector channel 
";


// File: classSimulationToPython.xml
%feature("docstring") SimulationToPython "

Write a Python script that allows to run the current simulation.

C++ includes: SimulationToPython.h
";

%feature("docstring")  SimulationToPython::generateSimulationCode "std::string SimulationToPython::generateSimulationCode(const Simulation &simulation, EMainType mainType)

Returns a Python script that sets up a simulation and runs it if invoked as main program. 
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


// File: classSLDSlicedCylindersBuilder.xml
%feature("docstring") SLDSlicedCylindersBuilder "

Provides exactly the same sample as  SlicedCylindersBuilder, but with sld-based materials. Assumed wavelength is 1.54 Angstrom.

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  SLDSlicedCylindersBuilder::SLDSlicedCylindersBuilder "SLDSlicedCylindersBuilder::SLDSlicedCylindersBuilder()
";

%feature("docstring")  SLDSlicedCylindersBuilder::buildSample "MultiLayer * SLDSlicedCylindersBuilder::buildSample() const override
";


// File: classSlice.xml
%feature("docstring") Slice "

Data structure containing the data of a single slice, for calculating the Fresnel coefficients.

C++ includes: Slice.h
";

%feature("docstring")  Slice::Slice "Slice::Slice(double thickness, const Material &material)
";

%feature("docstring")  Slice::Slice "Slice::Slice(double thickness, const Material &material, const LayerRoughness &top_roughness)
";

%feature("docstring")  Slice::Slice "Slice::Slice(const Slice &other)
";

%feature("docstring")  Slice::Slice "Slice::Slice(Slice &&other)
";

%feature("docstring")  Slice::~Slice "Slice::~Slice()
";

%feature("docstring")  Slice::setMaterial "void Slice::setMaterial(const Material &material)
";

%feature("docstring")  Slice::material "Material Slice::material() const
";

%feature("docstring")  Slice::thickness "double Slice::thickness() const
";

%feature("docstring")  Slice::topRoughness "const LayerRoughness * Slice::topRoughness() const
";

%feature("docstring")  Slice::scalarReducedPotential "complex_t Slice::scalarReducedPotential(kvector_t k, double n_ref) const

Return the potential term that is used in the one-dimensional Fresnel calculations. 
";

%feature("docstring")  Slice::polarizedReducedPotential "Eigen::Matrix2cd Slice::polarizedReducedPotential(kvector_t k, double n_ref) const

Return the potential term that is used in the one-dimensional Fresnel calculations in the presence of magnetization 
";

%feature("docstring")  Slice::initBField "void Slice::initBField(kvector_t h_field, double b_z)

Initializes the magnetic B field from a given ambient field strength H. 
";

%feature("docstring")  Slice::bField "kvector_t Slice::bField() const
";

%feature("docstring")  Slice::invertBField "void Slice::invertBField()
";


// File: classSlicedCompositionBuilder.xml
%feature("docstring") SlicedCompositionBuilder "

Builds sample: spherical composition made of top+bottom spherical cups

C++ includes: SlicedParticleBuilder.h
";

%feature("docstring")  SlicedCompositionBuilder::SlicedCompositionBuilder "SlicedCompositionBuilder::SlicedCompositionBuilder()
";

%feature("docstring")  SlicedCompositionBuilder::buildSample "MultiLayer * SlicedCompositionBuilder::buildSample() const
";


// File: classSlicedCylindersBuilder.xml
%feature("docstring") SlicedCylindersBuilder "

Builds sample: cylinders on a silicon substrate

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  SlicedCylindersBuilder::SlicedCylindersBuilder "SlicedCylindersBuilder::SlicedCylindersBuilder()
";

%feature("docstring")  SlicedCylindersBuilder::buildSample "MultiLayer * SlicedCylindersBuilder::buildSample() const override
";


// File: classSlicedFormFactorList.xml
%feature("docstring") SlicedFormFactorList "

Class that contains and owns a list of form factors and the index of their containing layer. This class also handles the slicing of form factors if they cross layer interfaces.

C++ includes: SlicedFormFactorList.h
";

%feature("docstring")  SlicedFormFactorList::SlicedFormFactorList "SlicedFormFactorList::SlicedFormFactorList()=default
";

%feature("docstring")  SlicedFormFactorList::SlicedFormFactorList "SlicedFormFactorList::SlicedFormFactorList(SlicedFormFactorList &&other)=default
";

%feature("docstring")  SlicedFormFactorList::~SlicedFormFactorList "SlicedFormFactorList::~SlicedFormFactorList()=default
";

%feature("docstring")  SlicedFormFactorList::size "size_t SlicedFormFactorList::size() const
";

%feature("docstring")  SlicedFormFactorList::regionMap "std::map< size_t, std::vector< HomogeneousRegion > > SlicedFormFactorList::regionMap() const
";


// File: structSlicedParticle.xml
%feature("docstring") SlicedParticle "

Struct that contains information on a sliced particle. This information is needed for evaluating the sliced form factor and the average of a material, used in the Fresnel calculations.

C++ includes: SlicedParticle.h
";


// File: structSlicingEffects.xml
%feature("docstring") SlicingEffects "

Nested structure that holds slicing effects on position and removed parts.

C++ includes: IFormFactorBorn.h
";


// File: classSpecularComputation.xml
%feature("docstring") SpecularComputation "

Performs a single-threaded specular computation with given sample.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: SpecularComputation.h
";

%feature("docstring")  SpecularComputation::SpecularComputation "SpecularComputation::SpecularComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, SpecularElementIter begin_it, SpecularElementIter end_it)
";

%feature("docstring")  SpecularComputation::~SpecularComputation "SpecularComputation::~SpecularComputation() override
";


// File: classSpecularComputationTerm.xml
%feature("docstring") SpecularComputationTerm "

Computes the specular scattering. Used by  SpecularComputation.

C++ includes: SpecularComputationTerm.h
";

%feature("docstring")  SpecularComputationTerm::SpecularComputationTerm "SpecularComputationTerm::SpecularComputationTerm(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  SpecularComputationTerm::~SpecularComputationTerm "SpecularComputationTerm::~SpecularComputationTerm()
";

%feature("docstring")  SpecularComputationTerm::SpecularComputationTerm "SpecularComputationTerm::SpecularComputationTerm(const SpecularComputationTerm &other)=delete
";

%feature("docstring")  SpecularComputationTerm::setProgressHandler "void SpecularComputationTerm::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  SpecularComputationTerm::compute "void SpecularComputationTerm::compute(SpecularSimulationElement &elem, const std::vector< Slice > &slices) const
";


// File: classSpecularDetector1D.xml
%feature("docstring") SpecularDetector1D "

1D detector for specular simulations. Use of this detector is deprecated.

C++ includes: SpecularDetector1D.h
";

%feature("docstring")  SpecularDetector1D::SpecularDetector1D "SpecularDetector1D::SpecularDetector1D(const IAxis &axis)
";

%feature("docstring")  SpecularDetector1D::~SpecularDetector1D "SpecularDetector1D::~SpecularDetector1D()
";

%feature("docstring")  SpecularDetector1D::clone "SpecularDetector1D * SpecularDetector1D::clone() const override
";

%feature("docstring")  SpecularDetector1D::accept "void SpecularDetector1D::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  SpecularDetector1D::detectorMask "const DetectorMask* SpecularDetector1D::detectorMask() const override

Returns detector masks container. 
";

%feature("docstring")  SpecularDetector1D::regionOfInterest "const RegionOfInterest* SpecularDetector1D::regionOfInterest() const override

Returns region of interest if exists. 
";

%feature("docstring")  SpecularDetector1D::resetRegionOfInterest "void SpecularDetector1D::resetRegionOfInterest() override

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  SpecularDetector1D::defaultAxesUnits "AxesUnits SpecularDetector1D::defaultAxesUnits() const override

Return default axes units. 
";


// File: classSpecularMagneticOldStrategy.xml
%feature("docstring") SpecularMagneticOldStrategy "

Implements the matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization.

C++ includes: SpecularMagneticOldStrategy.h
";

%feature("docstring")  SpecularMagneticOldStrategy::Execute "ISpecularStrategy::coeffs_t SpecularMagneticOldStrategy::Execute(const std::vector< Slice > &slices, const kvector_t &k) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and wavevector k 
";

%feature("docstring")  SpecularMagneticOldStrategy::Execute "ISpecularStrategy::coeffs_t SpecularMagneticOldStrategy::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const
";


// File: classSpecularMagneticStrategy.xml
%feature("docstring") SpecularMagneticStrategy "

Implements the matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization.

C++ includes: SpecularMagneticStrategy.h
";

%feature("docstring")  SpecularMagneticStrategy::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy::Execute(const std::vector< Slice > &slices, const kvector_t &k) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and wavevector k 
";

%feature("docstring")  SpecularMagneticStrategy::Execute "ISpecularStrategy::coeffs_t SpecularMagneticStrategy::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const

Computes refraction angle reflection/transmission coefficients for given sliced multilayer and a set of kz projections corresponding to each slice 
";


// File: classSpecularMatrixTerm.xml
%feature("docstring") SpecularMatrixTerm "";

%feature("docstring")  SpecularMatrixTerm::SpecularMatrixTerm "SpecularMatrixTerm::SpecularMatrixTerm(std::unique_ptr< ISpecularStrategy > strategy)
";


// File: classSpecularScalarNCStrategy.xml
%feature("docstring") SpecularScalarNCStrategy "

Implements method 'execute' to compute refraction angles and transmission/reflection coefficients for coherent wave propagation in a multilayer.

C++ includes: SpecularScalarNCStrategy.h
";


// File: classSpecularScalarStrategy.xml
%feature("docstring") SpecularScalarStrategy "

Implements method 'execute' to compute refraction angles and transmission/reflection coefficients for coherent wave propagation in a multilayer.

C++ includes: SpecularScalarStrategy.h
";

%feature("docstring")  SpecularScalarStrategy::Execute "ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector< Slice > &slices, const kvector_t &k) const override

Computes refraction angles and transmission/reflection coefficients for given coherent wave propagation in a multilayer. 
";

%feature("docstring")  SpecularScalarStrategy::Execute "ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector< Slice > &slices, const std::vector< complex_t > &kz) const override
";


// File: classSpecularScalarTanhStrategy.xml
%feature("docstring") SpecularScalarTanhStrategy "

Implements method 'execute' to compute refraction angles and transmission/reflection coefficients for coherent wave propagation in a multilayer.

C++ includes: SpecularScalarTanhStrategy.h
";


// File: classSpecularScalarTerm.xml
%feature("docstring") SpecularScalarTerm "";

%feature("docstring")  SpecularScalarTerm::SpecularScalarTerm "SpecularScalarTerm::SpecularScalarTerm(std::unique_ptr< ISpecularStrategy > strategy)
";


// File: classSpecularSimulation.xml
%feature("docstring") SpecularSimulation "

Main class to run a specular simulation.

C++ includes: SpecularSimulation.h
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation()
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation(const MultiLayer &sample)
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation(const std::shared_ptr< IMultiLayerBuilder > sample_builder)
";

%feature("docstring")  SpecularSimulation::~SpecularSimulation "SpecularSimulation::~SpecularSimulation() override
";

%feature("docstring")  SpecularSimulation::clone "SpecularSimulation * SpecularSimulation::clone() const override
";

%feature("docstring")  SpecularSimulation::prepareSimulation "void SpecularSimulation::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  SpecularSimulation::accept "void SpecularSimulation::accept(INodeVisitor *visitor) const override final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  SpecularSimulation::result "SimulationResult SpecularSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays. If simulation was not run, returns an array of proper size filled with zeros. 
";

%feature("docstring")  SpecularSimulation::setScan "void SpecularSimulation::setScan(const ISpecularScan &scan)

Sets chosen specular scan to the simulation. 
";

%feature("docstring")  SpecularSimulation::coordinateAxis "const IAxis * SpecularSimulation::coordinateAxis() const

Returns a pointer to coordinate axis. 
";

%feature("docstring")  SpecularSimulation::footprintFactor "const IFootprintFactor * SpecularSimulation::footprintFactor() const

Returns a pointer to footprint factor holder. 
";

%feature("docstring")  SpecularSimulation::intensityMapSize "size_t SpecularSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  SpecularSimulation::dataHandler "const ISpecularScan* SpecularSimulation::dataHandler() const

Returns internal data handler. 
";


// File: classSpecularSimulationElement.xml
%feature("docstring") SpecularSimulationElement "

Data stucture containing both input and output of a single image pixel for specular simulation.

C++ includes: SpecularSimulationElement.h
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(double kz)
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(double wavelength, double alpha)
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(const SpecularSimulationElement &other)
";

%feature("docstring")  SpecularSimulationElement::SpecularSimulationElement "SpecularSimulationElement::SpecularSimulationElement(SpecularSimulationElement &&other) noexcept
";

%feature("docstring")  SpecularSimulationElement::~SpecularSimulationElement "SpecularSimulationElement::~SpecularSimulationElement()
";

%feature("docstring")  SpecularSimulationElement::setPolarizationHandler "void SpecularSimulationElement::setPolarizationHandler(PolarizationHandler handler)

Assigns  PolarizationHandler. 
";

%feature("docstring")  SpecularSimulationElement::polarizationHandler "const PolarizationHandler& SpecularSimulationElement::polarizationHandler() const

Returns assigned  PolarizationHandler. 
";

%feature("docstring")  SpecularSimulationElement::getIntensity "double SpecularSimulationElement::getIntensity() const
";

%feature("docstring")  SpecularSimulationElement::setIntensity "void SpecularSimulationElement::setIntensity(double intensity)
";

%feature("docstring")  SpecularSimulationElement::setCalculationFlag "void SpecularSimulationElement::setCalculationFlag(bool calculation_flag)

Set calculation flag (if it's false, zero intensity is assigned to the element) 
";

%feature("docstring")  SpecularSimulationElement::isCalculated "bool SpecularSimulationElement::isCalculated() const
";

%feature("docstring")  SpecularSimulationElement::produceKz "std::vector< complex_t > SpecularSimulationElement::produceKz(const std::vector< Slice > &slices)

Returns kz values for Abeles computation of reflection/transition coefficients. 
";


// File: classSpecularStrategyBuilder.xml
%feature("docstring") SpecularStrategyBuilder "";


// File: classSpheresWithLimitsDistributionBuilder.xml
%feature("docstring") SpheresWithLimitsDistributionBuilder "

Spherical particles with the distribution applied to the radius and RealLimits defined.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  SpheresWithLimitsDistributionBuilder::SpheresWithLimitsDistributionBuilder "SpheresWithLimitsDistributionBuilder::SpheresWithLimitsDistributionBuilder()
";

%feature("docstring")  SpheresWithLimitsDistributionBuilder::buildSample "MultiLayer * SpheresWithLimitsDistributionBuilder::buildSample() const
";


// File: classSphericalConverter.xml
%feature("docstring") SphericalConverter "

IUnitConverter class that handles the unit translations for spherical detectors Its default units are radians for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  SphericalConverter::SphericalConverter "SphericalConverter::SphericalConverter(const SphericalDetector &detector, const Beam &beam)
";

%feature("docstring")  SphericalConverter::~SphericalConverter "SphericalConverter::~SphericalConverter() override
";

%feature("docstring")  SphericalConverter::clone "SphericalConverter * SphericalConverter::clone() const override
";

%feature("docstring")  SphericalConverter::availableUnits "std::vector< AxesUnits > SphericalConverter::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  SphericalConverter::defaultUnits "AxesUnits SphericalConverter::defaultUnits() const override
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

%feature("docstring")  SphericalDetector::accept "void SphericalDetector::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  SphericalDetector::~SphericalDetector "SphericalDetector::~SphericalDetector() override
";

%feature("docstring")  SphericalDetector::defaultAxesUnits "AxesUnits SphericalDetector::defaultAxesUnits() const override

return default axes units 
";


// File: classSphericalPixel.xml
%feature("docstring") SphericalPixel "";

%feature("docstring")  SphericalPixel::SphericalPixel "SphericalPixel::SphericalPixel(const Bin1D &alpha_bin, const Bin1D &phi_bin)
";

%feature("docstring")  SphericalPixel::clone "SphericalPixel * SphericalPixel::clone() const override
";

%feature("docstring")  SphericalPixel::createZeroSizePixel "SphericalPixel * SphericalPixel::createZeroSizePixel(double x, double y) const override
";

%feature("docstring")  SphericalPixel::getK "kvector_t SphericalPixel::getK(double x, double y, double wavelength) const override
";

%feature("docstring")  SphericalPixel::getIntegrationFactor "double SphericalPixel::getIntegrationFactor(double x, double y) const override
";

%feature("docstring")  SphericalPixel::getSolidAngle "double SphericalPixel::getSolidAngle() const override
";


// File: classSquareLattice.xml
%feature("docstring") SquareLattice "";

%feature("docstring")  SquareLattice::SquareLattice "SquareLattice::SquareLattice(double length, double rotation_angle=0.0)
";

%feature("docstring")  SquareLattice::clone "SquareLattice * SquareLattice::clone() const
";

%feature("docstring")  SquareLattice::accept "void SquareLattice::accept(INodeVisitor *visitor) const final

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  SquareLattice::length1 "virtual double SquareLattice::length1() const
";

%feature("docstring")  SquareLattice::length2 "virtual double SquareLattice::length2() const
";

%feature("docstring")  SquareLattice::latticeAngle "double SquareLattice::latticeAngle() const
";

%feature("docstring")  SquareLattice::unitCellArea "double SquareLattice::unitCellArea() const
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


// File: classSSCAHelper.xml
%feature("docstring") SSCAHelper "

Helper class for  SSCApproximationStrategy, offering some methods, shared between the scalar and polarized scattering calculations

C++ includes: SSCAHelper.h
";

%feature("docstring")  SSCAHelper::SSCAHelper "SSCAHelper::SSCAHelper(double kappa)
";

%feature("docstring")  SSCAHelper::init "void SSCAHelper::init(const std::vector< FormFactorCoherentSum > &ff_wrappers)
";

%feature("docstring")  SSCAHelper::getCharacteristicSizeCoupling "complex_t SSCAHelper::getCharacteristicSizeCoupling(double qp, const std::vector< FormFactorCoherentSum > &ff_wrappers) const
";

%feature("docstring")  SSCAHelper::getCharacteristicDistribution "complex_t SSCAHelper::getCharacteristicDistribution(double qp, const IInterferenceFunction *p_iff) const
";

%feature("docstring")  SSCAHelper::calculatePositionOffsetPhase "complex_t SSCAHelper::calculatePositionOffsetPhase(double qp, double radial_extension) const
";

%feature("docstring")  SSCAHelper::getMeanFormfactorNorm "complex_t SSCAHelper::getMeanFormfactorNorm(double qp, const std::vector< complex_t > &precomputed_ff, const std::vector< FormFactorCoherentSum > &ff_wrappers) const
";

%feature("docstring")  SSCAHelper::getMeanFormfactors "void SSCAHelper::getMeanFormfactors(double qp, Eigen::Matrix2cd &ff_orig, Eigen::Matrix2cd &ff_conj, const InterferenceFunctionUtils::matrixFFVector_t &precomputed_ff, const std::vector< FormFactorCoherentSum > &ff_wrappers) const
";


// File: classSSCApproximationStrategy.xml
%feature("docstring") SSCApproximationStrategy "

Strategy class to compute the total scattering from a particle layout in the size-spacing correlation approximation.

C++ includes: SSCApproximationStrategy.h
";

%feature("docstring")  SSCApproximationStrategy::SSCApproximationStrategy "SSCApproximationStrategy::SSCApproximationStrategy(SimulationOptions sim_params, double kappa, bool polarized)
";


// File: classSuperLatticeBuilder.xml
%feature("docstring") SuperLatticeBuilder "

Builds sample: 2D finite lattice of 2D finite lattices (superlattice).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  SuperLatticeBuilder::SuperLatticeBuilder "SuperLatticeBuilder::SuperLatticeBuilder()
";

%feature("docstring")  SuperLatticeBuilder::buildSample "MultiLayer * SuperLatticeBuilder::buildSample() const
";


// File: classThickAbsorptiveSampleBuilder.xml
%feature("docstring") ThickAbsorptiveSampleBuilder "";

%feature("docstring")  ThickAbsorptiveSampleBuilder::ThickAbsorptiveSampleBuilder "ThickAbsorptiveSampleBuilder::ThickAbsorptiveSampleBuilder()
";

%feature("docstring")  ThickAbsorptiveSampleBuilder::buildSample "MultiLayer * ThickAbsorptiveSampleBuilder::buildSample() const override
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

%feature("docstring")  Transform3D::Transform3D "Transform3D::Transform3D(const Eigen::Matrix3d &matrix)

Constructor from matrix (no checks if this is an element of SO(3)!) 
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

%feature("docstring")  Transform3D::calculateRotateXAngle "double Transform3D::calculateRotateXAngle() const

Calculates the rotation angle for a rotation around the x-axis alone Only meaningfull if the actual rotation is around the x-axis 
";

%feature("docstring")  Transform3D::calculateRotateYAngle "double Transform3D::calculateRotateYAngle() const

Calculates the rotation angle for a rotation around the y-axis alone Only meaningfull if the actual rotation is around the y-axis 
";

%feature("docstring")  Transform3D::calculateRotateZAngle "double Transform3D::calculateRotateZAngle() const

Calculates the rotation angle for a rotation around the z-axis alone Only meaningfull if the actual rotation is around the z-axis 
";

%feature("docstring")  Transform3D::getInverse "Transform3D Transform3D::getInverse() const

Returns the inverse transformation. 
";

%feature("docstring")  Transform3D::transformed "template BA_CORE_API_ cvector_t Transform3D::transformed< cvector_t >(const ivector_t &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::transformedInverse "template BA_CORE_API_ cvector_t Transform3D::transformedInverse< cvector_t >(const ivector_t &v) const

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

%feature("docstring")  Transform3D::isXRotation "bool Transform3D::isXRotation() const
";

%feature("docstring")  Transform3D::isYRotation "bool Transform3D::isYRotation() const
";

%feature("docstring")  Transform3D::isZRotation "bool Transform3D::isZRotation() const
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


// File: classTriangle.xml
%feature("docstring") Triangle "";

%feature("docstring")  Triangle::Triangle "Triangle::Triangle(double length, double z)
";

%feature("docstring")  Triangle::~Triangle "Triangle::~Triangle()
";


// File: classTriangularRippleBuilder.xml
%feature("docstring") TriangularRippleBuilder "

Builds sample: triangular ripple within the 1D-paracrystal model (from PRB 85, 235415, 2012).

C++ includes: RipplesBuilder.h
";

%feature("docstring")  TriangularRippleBuilder::TriangularRippleBuilder "TriangularRippleBuilder::TriangularRippleBuilder()
";

%feature("docstring")  TriangularRippleBuilder::buildSample "MultiLayer * TriangularRippleBuilder::buildSample() const
";


// File: classTruncatedCube.xml
%feature("docstring") TruncatedCube "";

%feature("docstring")  TruncatedCube::TruncatedCube "TruncatedCube::TruncatedCube(double length, double removed_length)
";

%feature("docstring")  TruncatedCube::~TruncatedCube "TruncatedCube::~TruncatedCube()
";


// File: classTruncatedEllipsoid.xml
%feature("docstring") TruncatedEllipsoid "";

%feature("docstring")  TruncatedEllipsoid::TruncatedEllipsoid "TruncatedEllipsoid::TruncatedEllipsoid(double r_x, double r_y, double r_z, double height, double dh)
";

%feature("docstring")  TruncatedEllipsoid::~TruncatedEllipsoid "TruncatedEllipsoid::~TruncatedEllipsoid()
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


// File: classTwoLayerRoughnessBuilder.xml
%feature("docstring") TwoLayerRoughnessBuilder "

Builds sample: two layers with rough interface.

C++ includes: TwoLayerRoughnessBuilder.h
";

%feature("docstring")  TwoLayerRoughnessBuilder::TwoLayerRoughnessBuilder "TwoLayerRoughnessBuilder::TwoLayerRoughnessBuilder()
";

%feature("docstring")  TwoLayerRoughnessBuilder::buildSample "MultiLayer * TwoLayerRoughnessBuilder::buildSample() const
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


// File: classUnitConverter1D.xml
%feature("docstring") UnitConverter1D "

Conversion of axis units for the case of 1D simulation result.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverter1D::~UnitConverter1D "UnitConverter1D::~UnitConverter1D() override=default
";

%feature("docstring")  UnitConverter1D::clone "UnitConverter1D* UnitConverter1D::clone() const override=0
";

%feature("docstring")  UnitConverter1D::dimension "size_t UnitConverter1D::dimension() const override

Returns dimensionality of converted canvas. 
";

%feature("docstring")  UnitConverter1D::calculateMin "double UnitConverter1D::calculateMin(size_t i_axis, AxesUnits units_type) const override

Calculates minimum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::calculateMax "double UnitConverter1D::calculateMax(size_t i_axis, AxesUnits units_type) const override

Calculates maximum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::createConvertedAxis "std::unique_ptr< IAxis > UnitConverter1D::createConvertedAxis(size_t i_axis, AxesUnits units) const override

Creates axis in converted units. 
";

%feature("docstring")  UnitConverter1D::createConvertedData "std::unique_ptr< OutputData< double > > UnitConverter1D::createConvertedData(const OutputData< double > &data, AxesUnits units) const override

Creates  OutputData array in converter units. 
";


// File: classUnitConverterConvSpec.xml
%feature("docstring") UnitConverterConvSpec "

Conversion of axis units for the case of conventional (angle-based) reflectometry.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverterConvSpec::UnitConverterConvSpec "UnitConverterConvSpec::UnitConverterConvSpec(const Beam &beam, const IAxis &axis, AxesUnits axis_units=AxesUnits::RADIANS)

Constructs the object for unit conversion. 
";

%feature("docstring")  UnitConverterConvSpec::UnitConverterConvSpec "UnitConverterConvSpec::UnitConverterConvSpec(const AngularSpecScan &handler)
";

%feature("docstring")  UnitConverterConvSpec::~UnitConverterConvSpec "UnitConverterConvSpec::~UnitConverterConvSpec() override
";

%feature("docstring")  UnitConverterConvSpec::clone "UnitConverterConvSpec * UnitConverterConvSpec::clone() const override
";

%feature("docstring")  UnitConverterConvSpec::axisSize "size_t UnitConverterConvSpec::axisSize(size_t i_axis) const override

Returns the size of underlying axis. 
";

%feature("docstring")  UnitConverterConvSpec::availableUnits "std::vector< AxesUnits > UnitConverterConvSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterConvSpec::defaultUnits "AxesUnits UnitConverterConvSpec::defaultUnits() const override

Returns default units to convert to. 
";


// File: classUnitConverterQSpec.xml
%feature("docstring") UnitConverterQSpec "

Conversion of axis units for the case of q-defined reflectometry.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverterQSpec::UnitConverterQSpec "UnitConverterQSpec::UnitConverterQSpec(const QSpecScan &handler)
";

%feature("docstring")  UnitConverterQSpec::~UnitConverterQSpec "UnitConverterQSpec::~UnitConverterQSpec() override
";

%feature("docstring")  UnitConverterQSpec::clone "UnitConverterQSpec * UnitConverterQSpec::clone() const override
";

%feature("docstring")  UnitConverterQSpec::axisSize "size_t UnitConverterQSpec::axisSize(size_t i_axis) const override

Returns the size of underlying axis. 
";

%feature("docstring")  UnitConverterQSpec::availableUnits "std::vector< AxesUnits > UnitConverterQSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterQSpec::defaultUnits "AxesUnits UnitConverterQSpec::defaultUnits() const override

Returns default units to convert to. 
";


// File: classUnitConverterSimple.xml
%feature("docstring") UnitConverterSimple "

Interface for objects that provide axis translations to different units for  IDetector objects

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  UnitConverterSimple::UnitConverterSimple "UnitConverterSimple::UnitConverterSimple(const Beam &beam)
";

%feature("docstring")  UnitConverterSimple::~UnitConverterSimple "UnitConverterSimple::~UnitConverterSimple() override=default
";

%feature("docstring")  UnitConverterSimple::dimension "size_t UnitConverterSimple::dimension() const override
";

%feature("docstring")  UnitConverterSimple::calculateMin "double UnitConverterSimple::calculateMin(size_t i_axis, AxesUnits units_type) const override
";

%feature("docstring")  UnitConverterSimple::calculateMax "double UnitConverterSimple::calculateMax(size_t i_axis, AxesUnits units_type) const override
";

%feature("docstring")  UnitConverterSimple::axisSize "size_t UnitConverterSimple::axisSize(size_t i_axis) const override
";

%feature("docstring")  UnitConverterSimple::availableUnits "std::vector< AxesUnits > UnitConverterSimple::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterSimple::createConvertedAxis "std::unique_ptr< IAxis > UnitConverterSimple::createConvertedAxis(size_t i_axis, AxesUnits units) const override
";


// File: classExceptions_1_1UnknownClassRegistrationException.xml
%feature("docstring") Exceptions::UnknownClassRegistrationException "";

%feature("docstring")  Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException "Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
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


// File: classVarianceConstantFunction.xml
%feature("docstring") VarianceConstantFunction "

Returns 1.0 as variance value

C++ includes: VarianceFunctions.h
";

%feature("docstring")  VarianceConstantFunction::clone "VarianceConstantFunction * VarianceConstantFunction::clone() const override
";

%feature("docstring")  VarianceConstantFunction::variance "double VarianceConstantFunction::variance(double, double) const override
";


// File: classVarianceSimFunction.xml
%feature("docstring") VarianceSimFunction "

Returns max(sim, epsilon)

C++ includes: VarianceFunctions.h
";

%feature("docstring")  VarianceSimFunction::VarianceSimFunction "VarianceSimFunction::VarianceSimFunction(double epsilon=1.0)
";

%feature("docstring")  VarianceSimFunction::clone "VarianceSimFunction * VarianceSimFunction::clone() const override
";

%feature("docstring")  VarianceSimFunction::variance "double VarianceSimFunction::variance(double exp, double sim) const override
";


// File: classVerticalLine.xml
%feature("docstring") VerticalLine "

An infinite vertical line.

C++ includes: Line.h
";

%feature("docstring")  VerticalLine::VerticalLine "VerticalLine::VerticalLine(double x)

Parameters:
-----------

x: 
The value at which it crosses x-axes 
";

%feature("docstring")  VerticalLine::clone "VerticalLine* VerticalLine::clone() const
";

%feature("docstring")  VerticalLine::contains "bool VerticalLine::contains(double x, double y) const

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  VerticalLine::contains "bool VerticalLine::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
";

%feature("docstring")  VerticalLine::getXpos "double VerticalLine::getXpos() const
";


// File: classVonMisesFisherGaussPeakShape.xml
%feature("docstring") VonMisesFisherGaussPeakShape "

Class that implements a peak shape that is Gaussian in the radial direction and a convolution of a von Mises-Fisher distribution with a von Mises distribution on the two-sphere

C++ includes: IPeakShape.h
";

%feature("docstring")  VonMisesFisherGaussPeakShape::VonMisesFisherGaussPeakShape "VonMisesFisherGaussPeakShape::VonMisesFisherGaussPeakShape(double max_intensity, double radial_size, kvector_t zenith, double kappa_1, double kappa_2)
";

%feature("docstring")  VonMisesFisherGaussPeakShape::~VonMisesFisherGaussPeakShape "VonMisesFisherGaussPeakShape::~VonMisesFisherGaussPeakShape() override
";

%feature("docstring")  VonMisesFisherGaussPeakShape::clone "VonMisesFisherGaussPeakShape * VonMisesFisherGaussPeakShape::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  VonMisesFisherGaussPeakShape::accept "void VonMisesFisherGaussPeakShape::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  VonMisesFisherGaussPeakShape::evaluate "double VonMisesFisherGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  VonMisesFisherGaussPeakShape::angularDisorder "bool VonMisesFisherGaussPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classVonMisesGaussPeakShape.xml
%feature("docstring") VonMisesGaussPeakShape "

Class that implements a peak shape that is a convolution of a von Mises-Fisher distribution with a 3d Gaussian

C++ includes: IPeakShape.h
";

%feature("docstring")  VonMisesGaussPeakShape::VonMisesGaussPeakShape "VonMisesGaussPeakShape::VonMisesGaussPeakShape(double max_intensity, double radial_size, kvector_t zenith, double kappa)
";

%feature("docstring")  VonMisesGaussPeakShape::~VonMisesGaussPeakShape "VonMisesGaussPeakShape::~VonMisesGaussPeakShape() override
";

%feature("docstring")  VonMisesGaussPeakShape::clone "VonMisesGaussPeakShape * VonMisesGaussPeakShape::clone() const override

Returns a clone of this  ISample object. 
";

%feature("docstring")  VonMisesGaussPeakShape::accept "void VonMisesGaussPeakShape::accept(INodeVisitor *visitor) const override

Calls the  INodeVisitor's visit method. 
";

%feature("docstring")  VonMisesGaussPeakShape::evaluate "double VonMisesGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const override

Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point. 
";

%feature("docstring")  VonMisesGaussPeakShape::angularDisorder "bool VonMisesGaussPeakShape::angularDisorder() const override

Indicates if the peak shape encodes angular disorder, in which case all peaks in a spherical shell are needed 
";


// File: classWavevectorInfo.xml
%feature("docstring") WavevectorInfo "

Holds all wavevector information relevant for calculating form factors.

C++ includes: WavevectorInfo.h
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo(cvector_t ki, cvector_t kf, double wavelength)
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo(kvector_t ki, kvector_t kf, double wavelength)
";

%feature("docstring")  WavevectorInfo::transformed "WavevectorInfo WavevectorInfo::transformed(const Transform3D &transform) const
";

%feature("docstring")  WavevectorInfo::getKi "cvector_t WavevectorInfo::getKi() const
";

%feature("docstring")  WavevectorInfo::getKf "cvector_t WavevectorInfo::getKf() const
";

%feature("docstring")  WavevectorInfo::getQ "cvector_t WavevectorInfo::getQ() const
";

%feature("docstring")  WavevectorInfo::getWavelength "double WavevectorInfo::getWavelength() const
";


// File: classConvolve_1_1Workspace.xml


// File: classFourierTransform_1_1Workspace.xml


// File: classZLimits.xml
%feature("docstring") ZLimits "

Class that contains upper and lower limits of the z-coordinate for the slicing of form factors.

C++ includes: ZLimits.h
";

%feature("docstring")  ZLimits::ZLimits "ZLimits::ZLimits()
";

%feature("docstring")  ZLimits::ZLimits "ZLimits::ZLimits(double min, double max)
";

%feature("docstring")  ZLimits::ZLimits "ZLimits::ZLimits(OneSidedLimit lower_limit, OneSidedLimit upper_limit)
";

%feature("docstring")  ZLimits::isFinite "bool ZLimits::isFinite() const
";

%feature("docstring")  ZLimits::lowerLimit "OneSidedLimit ZLimits::lowerLimit() const
";

%feature("docstring")  ZLimits::upperLimit "OneSidedLimit ZLimits::upperLimit() const
";


// File: namespace_0d104.xml


// File: namespace_0d106.xml


// File: namespace_0d108.xml


// File: namespace_0d112.xml


// File: namespace_0d12.xml


// File: namespace_0d127.xml


// File: namespace_0d136.xml


// File: namespace_0d141.xml


// File: namespace_0d150.xml


// File: namespace_0d152.xml


// File: namespace_0d156.xml


// File: namespace_0d18.xml


// File: namespace_0d192.xml


// File: namespace_0d20.xml


// File: namespace_0d227.xml


// File: namespace_0d235.xml


// File: namespace_0d241.xml


// File: namespace_0d245.xml


// File: namespace_0d295.xml


// File: namespace_0d304.xml


// File: namespace_0d312.xml


// File: namespace_0d316.xml


// File: namespace_0d318.xml


// File: namespace_0d32.xml


// File: namespace_0d330.xml


// File: namespace_0d336.xml


// File: namespace_0d357.xml


// File: namespace_0d361.xml


// File: namespace_0d363.xml


// File: namespace_0d365.xml


// File: namespace_0d375.xml


// File: namespace_0d387.xml


// File: namespace_0d391.xml


// File: namespace_0d40.xml


// File: namespace_0d403.xml


// File: namespace_0d409.xml


// File: namespace_0d414.xml


// File: namespace_0d416.xml


// File: namespace_0d42.xml


// File: namespace_0d420.xml


// File: namespace_0d422.xml


// File: namespace_0d432.xml


// File: namespace_0d445.xml


// File: namespace_0d454.xml


// File: namespace_0d456.xml


// File: namespace_0d490.xml


// File: namespace_0d497.xml


// File: namespace_0d535.xml


// File: namespace_0d543.xml


// File: namespace_0d545.xml


// File: namespace_0d547.xml


// File: namespace_0d6.xml


// File: namespace_0d631.xml


// File: namespace_0d635.xml


// File: namespace_0d659.xml


// File: namespace_0d98.xml


// File: namespacealgo.xml
%feature("docstring")  algo::min_value "double algo::min_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the minimum value of function evaluate as applied to the elements of an iterator range. 
";

%feature("docstring")  algo::max_value "double algo::max_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the maximum value of function evaluate as applied to the elements of an iterator range. 
";


// File: namespaceArrayUtils.xml
%feature("docstring")  ArrayUtils::getShape "std::pair< size_t, size_t > ArrayUtils::getShape(const T &data)

Returns shape nrows, ncols of 2D array. 
";

%feature("docstring")  ArrayUtils::createData "CreateDataImpl::ReturnType<T> ArrayUtils::createData(const T &vec)

Creates  OutputData array from input vector.

Parameters:
-----------

vec: 
input vector 
";

%feature("docstring")  ArrayUtils::createNumpyArray "PyObject * ArrayUtils::createNumpyArray(const std::vector< double > &data)
";

%feature("docstring")  ArrayUtils::createVector1D "decltype(auto) ArrayUtils::createVector1D(const T &data)

Creates 1D vector from  OutputData.

Parameters:
-----------

vec: 
 OutputData<double>

vector<double> 
";

%feature("docstring")  ArrayUtils::createVector2D "decltype(auto) ArrayUtils::createVector2D(const T &data)

Creates 2D vector from  OutputData.

Parameters:
-----------

vec: 
 OutputData<double>

vector<vector<double>> 
";


// File: namespaceAxisNames.xml
%feature("docstring")  AxisNames::InitSphericalAxis0 "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitSphericalAxis0()
";

%feature("docstring")  AxisNames::InitSphericalAxis1 "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitSphericalAxis1()
";

%feature("docstring")  AxisNames::InitRectangularAxis0 "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitRectangularAxis0()
";

%feature("docstring")  AxisNames::InitRectangularAxis1 "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitRectangularAxis1()
";

%feature("docstring")  AxisNames::InitOffSpecAxis0 "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitOffSpecAxis0()
";

%feature("docstring")  AxisNames::InitOffSpecAxis1 "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitOffSpecAxis1()
";

%feature("docstring")  AxisNames::InitSpecAxis "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitSpecAxis()
";

%feature("docstring")  AxisNames::InitSpecAxisQ "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitSpecAxisQ()
";

%feature("docstring")  AxisNames::InitSampleDepthAxis "BA_CORE_API_ std::map< AxesUnits, std::string > AxisNames::InitSampleDepthAxis()
";


// File: namespaceboost_1_1geometry.xml


// File: namespaceBornAgain.xml


// File: namespaceDataFormatUtils.xml
%feature("docstring")  DataFormatUtils::isCompressed "bool DataFormatUtils::isCompressed(const std::string &name)

Returns true if name contains *.gz extension. 
";

%feature("docstring")  DataFormatUtils::isGZipped "bool DataFormatUtils::isGZipped(const std::string &name)

Returns true if name contains *.gz extension.

Does name contain *.gz extension? 
";

%feature("docstring")  DataFormatUtils::isBZipped "bool DataFormatUtils::isBZipped(const std::string &name)

Returns true if name contains *.bz2 extension. 
";

%feature("docstring")  DataFormatUtils::GetFileMainExtension "std::string DataFormatUtils::GetFileMainExtension(const std::string &name)

Returns file extension after stripping '.gz' if any.

Returns file main extension (without .gz). 
";

%feature("docstring")  DataFormatUtils::isIntFile "bool DataFormatUtils::isIntFile(const std::string &file_name)

returns true if file name corresponds to  BornAgain native format (compressed or not) 
";

%feature("docstring")  DataFormatUtils::isTiffFile "bool DataFormatUtils::isTiffFile(const std::string &file_name)

returns true if file name corresponds to tiff file (can be also compressed) 
";

%feature("docstring")  DataFormatUtils::createAxis "std::unique_ptr< IAxis > DataFormatUtils::createAxis(std::istream &input_stream)

Creates axis of certain type from input stream. 
";

%feature("docstring")  DataFormatUtils::fillOutputData "void DataFormatUtils::fillOutputData(OutputData< double > *data, std::istream &input_stream)

Fills output data raw buffer from input stream. 
";

%feature("docstring")  DataFormatUtils::parse_doubles "std::vector< double > DataFormatUtils::parse_doubles(const std::string &str)

Parse double values from string to vector of double. 
";

%feature("docstring")  DataFormatUtils::readLineOfDoubles "void DataFormatUtils::readLineOfDoubles(std::vector< double > &buffer, std::istringstream &iss)
";


// File: namespaceDetectorFunctions.xml
%feature("docstring")  DetectorFunctions::hasSameDimensions "bool DetectorFunctions::hasSameDimensions(const IDetector &detector, const OutputData< double > &data)

Returns true if the data has same axes size (nx,ny) with the detector. 
";

%feature("docstring")  DetectorFunctions::axesToString "std::string DetectorFunctions::axesToString(const IDetector &detector)

Returns string representation of axes dimension in the form \"(nx,ny)\". 
";

%feature("docstring")  DetectorFunctions::axesToString "std::string DetectorFunctions::axesToString(const OutputData< double > &data)

Returns string representation of axes dimension in the form \"(nx,ny)\". 
";


// File: namespaceExceptions.xml
%feature("docstring")  Exceptions::LogExceptionMessage "void Exceptions::LogExceptionMessage(const std::string &)
";


// File: namespaceExportToPython.xml
%feature("docstring")  ExportToPython::generateSampleCode "std::string ExportToPython::generateSampleCode(const MultiLayer &multilayer)
";

%feature("docstring")  ExportToPython::generateSimulationCode "std::string ExportToPython::generateSimulationCode(const Simulation &simulation)
";

%feature("docstring")  ExportToPython::generatePyExportTest "std::string ExportToPython::generatePyExportTest(const Simulation &simulation)
";


// File: namespaceFileSystemUtils.xml
%feature("docstring")  FileSystemUtils::extension "std::string FileSystemUtils::extension(const std::string &path)

Returns extension of given filename. \"/home/user/filename.int\" -> \".int\", \"/home/user/filename.int.gz\" -> \".gz\" 
";

%feature("docstring")  FileSystemUtils::extensions "std::string FileSystemUtils::extensions(const std::string &path)

Returns extension(s) of given filename. \"/home/user/filename.int\" -> \".int\", \"/home/user/filename.int.gz\" -> \".int.gz\" 
";

%feature("docstring")  FileSystemUtils::createDirectory "bool FileSystemUtils::createDirectory(const std::string &dir_name)

Creates directory in current directory. 
";

%feature("docstring")  FileSystemUtils::createDirectories "bool FileSystemUtils::createDirectories(const std::string &dir_name)

Creates directories in current directory for any element of dir_name which doesn't exist. 
";

%feature("docstring")  FileSystemUtils::filesInDirectory "std::vector< std::string > FileSystemUtils::filesInDirectory(const std::string &dir_name)

Returns filenames of files in directory. 
";

%feature("docstring")  FileSystemUtils::jointPath "std::string FileSystemUtils::jointPath(const std::string &spath1, const std::string &spath2)

Returns joint path name. 
";

%feature("docstring")  FileSystemUtils::filename "std::string FileSystemUtils::filename(const std::string &path)

Returns path without directory part (\"Foo/Bar/Doz.int.gz\" -> \"Doz.int.gz\") 
";

%feature("docstring")  FileSystemUtils::stem "std::string FileSystemUtils::stem(const std::string &path)

Returns filename without extension. \"/home/user/filename.int\" -> \"filename\", \"/home/user/filename.int.gz\" -> \"filename.int\" 
";

%feature("docstring")  FileSystemUtils::stem_ext "std::string FileSystemUtils::stem_ext(const std::string &path)

Returns filename without extension(s). \"/home/user/filename.int\" -> \"filename\", \"/home/user/filename.int.gz\" -> \"filename\" 
";

%feature("docstring")  FileSystemUtils::glob "std::vector< std::string > FileSystemUtils::glob(const std::string &dir, const std::string &pattern)

Returns file names that agree with a regex glob pattern. 
";

%feature("docstring")  FileSystemUtils::convert_utf8_to_utf16 "std::wstring FileSystemUtils::convert_utf8_to_utf16(const std::string &str)

Converts utf8 string represented by std::string to utf16 string represented by std::wstring. 
";

%feature("docstring")  FileSystemUtils::IsFileExists "bool FileSystemUtils::IsFileExists(const std::string &str)

Returns true if file with given name exists on disk. 
";


// File: namespaceFit.xml


// File: namespaceINodeUtils.xml
%feature("docstring")  INodeUtils::ChildNodesOfType "std::vector<const T*> INodeUtils::ChildNodesOfType(const INode &node)
";

%feature("docstring")  INodeUtils::OnlyChildOfType "const T* INodeUtils::OnlyChildOfType(const INode &node)
";

%feature("docstring")  INodeUtils::AllDescendantsOfType "std::vector<const T*> INodeUtils::AllDescendantsOfType(const INode &node)
";


// File: namespaceIntensityDataFunctions.xml
%feature("docstring")  IntensityDataFunctions::RelativeDifference "double IntensityDataFunctions::RelativeDifference(const SimulationResult &dat, const SimulationResult &ref)

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(a + b) ( and zero if a-b=0 )

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(|a| + |b|) ( and zero if a=b=0 within epsilon ) 
";

%feature("docstring")  IntensityDataFunctions::getRelativeDifference "double IntensityDataFunctions::getRelativeDifference(const OutputData< double > &dat, const OutputData< double > &ref)

Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]). 
";

%feature("docstring")  IntensityDataFunctions::getRelativeDifference "double IntensityDataFunctions::getRelativeDifference(const IHistogram &dat, const IHistogram &ref)
";

%feature("docstring")  IntensityDataFunctions::coordinateToBinf "double IntensityDataFunctions::coordinateToBinf(double coordinate, const IAxis &axis)

Transforms coordinate on axis into the bin-fraction-coordinate. 
";

%feature("docstring")  IntensityDataFunctions::coordinateFromBinf "double IntensityDataFunctions::coordinateFromBinf(double value, const IAxis &axis)

Transforms bin-fraction-coordinate into axis coordinate. 
";

%feature("docstring")  IntensityDataFunctions::coordinateToBinf "void IntensityDataFunctions::coordinateToBinf(double &x, double &y, const OutputData< double > &data)

Transforms x,y coordinate from  OutputData axes coordinates to bin-fraction-coordinates. 
";

%feature("docstring")  IntensityDataFunctions::coordinateFromBinf "void IntensityDataFunctions::coordinateFromBinf(double &x, double &y, const OutputData< double > &data)

Transforms x,y coordinate from bin-fraction-coordinates to  OutputData's axes coordinates. 
";

%feature("docstring")  IntensityDataFunctions::create2DArrayfromOutputData "std::vector< std::vector< double > > IntensityDataFunctions::create2DArrayfromOutputData(const OutputData< double > &data)

Creates a vector of vectors of double (2D Array) from  OutputData. 
";

%feature("docstring")  IntensityDataFunctions::FT2DArray "std::vector< std::vector< double > > IntensityDataFunctions::FT2DArray(const std::vector< std::vector< double >> &signal)

Creates a Fourier Transform of a 2D Array (vector of vectors). 
";

%feature("docstring")  IntensityDataFunctions::createRelativeDifferenceData "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createRelativeDifferenceData(const OutputData< double > &data, const OutputData< double > &reference)
";

%feature("docstring")  IntensityDataFunctions::createRearrangedDataSet "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createRearrangedDataSet(const OutputData< double > &data, int n)

Returns new object with input data rotated by n*90 deg counterclockwise (n > 0) or clockwise (n < 0) Axes are swapped if the data is effectively rotated by 90 or 270 degrees Applicable to 2D arrays only 
";

%feature("docstring")  IntensityDataFunctions::createClippedDataSet "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createClippedDataSet(const OutputData< double > &origin, double x1, double y1, double x2, double y2)

Returns new IntensityData objects which axes clipped to represent the specified rectangle. 
";

%feature("docstring")  IntensityDataFunctions::createOutputDatafrom2DArray "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createOutputDatafrom2DArray(const std::vector< std::vector< double >> &array_2d)

Creates  OutputData from a 2D Array. 
";

%feature("docstring")  IntensityDataFunctions::createFFT "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createFFT(const OutputData< double > &data)

Creates Fourier Transform ( OutputData format) of intensity map ( OutputData format). 
";

%feature("docstring")  IntensityDataFunctions::ConvertData "SimulationResult IntensityDataFunctions::ConvertData(const Simulation &simulation, const OutputData< double > &data, bool put_masked_areas_to_zero=true)

Convert user data to  SimulationResult object for later drawing in various axes units. User data will be cropped to the ROI defined in the simulation, amplitudes in areas corresponding to the masked areas of the detector will be set to zero.

Parameters:
-----------

simulation: 
 Simulation object with possible ROI and masks defined.

data: 
User data with amplitudes with the shape of data matching the detector.

SimulationResult object. 
";

%feature("docstring")  IntensityDataFunctions::ConvertData "SimulationResult IntensityDataFunctions::ConvertData(const Simulation &simulation, const std::vector< std::vector< double >> &data, bool put_masked_areas_to_zero=true)
";


// File: namespaceInterferenceFunctionUtils.xml
%feature("docstring")  InterferenceFunctionUtils::PrecomputeScalarFormFactors "std::vector< complex_t > InterferenceFunctionUtils::PrecomputeScalarFormFactors(const SimulationElement &sim_element, const std::vector< FormFactorCoherentSum > &ff_wrappers)
";

%feature("docstring")  InterferenceFunctionUtils::PrecomputePolarizedFormFactors "matrixFFVector_t InterferenceFunctionUtils::PrecomputePolarizedFormFactors(const SimulationElement &sim_element, const std::vector< FormFactorCoherentSum > &ff_wrappers)
";


// File: namespaceKzComputation.xml
%feature("docstring")  KzComputation::computeReducedKz "std::vector< complex_t > KzComputation::computeReducedKz(const std::vector< Slice > &slices, kvector_t k)
";

%feature("docstring")  KzComputation::computeKzFromSLDs "std::vector< complex_t > KzComputation::computeKzFromSLDs(const std::vector< Slice > &slices, double kz)
";

%feature("docstring")  KzComputation::computeKzFromRefIndices "std::vector< complex_t > KzComputation::computeKzFromRefIndices(const std::vector< Slice > &slices, kvector_t k)
";


// File: namespaceLatticeUtils.xml
%feature("docstring")  LatticeUtils::CreateFCCLattice "Lattice LatticeUtils::CreateFCCLattice(double lattice_constant, const ILatticeOrientation &orientation)
";

%feature("docstring")  LatticeUtils::CreateHCPLattice "Lattice LatticeUtils::CreateHCPLattice(double a, double c, const ILatticeOrientation &orientation)
";

%feature("docstring")  LatticeUtils::CreateBCTLattice "Lattice LatticeUtils::CreateBCTLattice(double a, double c, const ILatticeOrientation &orientation)
";


// File: namespaceMaterialUtils.xml
%feature("docstring")  MaterialUtils::ScalarReducedPotential "complex_t MaterialUtils::ScalarReducedPotential(complex_t n, kvector_t k, double n_ref)

Function for calculating the reduced potential, used for obtaining the Fresnel coefficients (non-polarized material case) 
";

%feature("docstring")  MaterialUtils::PolarizedReducedPotential "Eigen::Matrix2cd MaterialUtils::PolarizedReducedPotential(complex_t n, kvector_t b_field, kvector_t k, double n_ref)

Function for calculating the reduced potential, used for obtaining the Fresnel coefficients (polarized material case) 
";

%feature("docstring")  MaterialUtils::MagnetizationCorrection "BA_CORE_API_ Eigen::Matrix2cd MaterialUtils::MagnetizationCorrection(complex_t unit_factor, double magnetic_factor, BasicVector3D< T > polarization)

Utility to compute magnetization correction for reduced potential and scattering length density. 
";

%feature("docstring")  MaterialUtils::checkMaterialTypes "MATERIAL_TYPES MaterialUtils::checkMaterialTypes(const std::vector< const Material * > &materials)

Checks if all non-default materials in  materials are of the same type and returns this type. If several types of materials are involved, InvalidMaterialType identifier is returned. 
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

%feature("docstring")  MathFunctions::Laue "double MathFunctions::Laue(const double x, size_t N)

Real Laue function:  $Laue(x,N)\\\\equiv\\\\sin(Nx)/sin(x)$. 
";

%feature("docstring")  MathFunctions::erf "double MathFunctions::erf(double arg)

Error function of real-valued argument. 
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

%feature("docstring")  MathFunctions::Bessel_I0 "double MathFunctions::Bessel_I0(double x)

Modified Bessel function of the first kind and order 0. 
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

%feature("docstring")  MathFunctions::GeneratePoissonRandom "double MathFunctions::GeneratePoissonRandom(double average)
";


// File: namespaceMultiLayerUtils.xml
%feature("docstring")  MultiLayerUtils::LayerThickness "double MultiLayerUtils::LayerThickness(const MultiLayer &multilayer, size_t i)

Returns thickness of layer. 
";

%feature("docstring")  MultiLayerUtils::LayerTopInterface "const LayerInterface * MultiLayerUtils::LayerTopInterface(const MultiLayer &multilayer, size_t i)

Returns top interface of layer. 
";

%feature("docstring")  MultiLayerUtils::LayerBottomInterface "const LayerInterface * MultiLayerUtils::LayerBottomInterface(const MultiLayer &multilayer, size_t i)

Returns bottom interface of layer. 
";

%feature("docstring")  MultiLayerUtils::LayerTopRoughness "const LayerRoughness * MultiLayerUtils::LayerTopRoughness(const MultiLayer &multilayer, size_t i)

Returns top roughness of layer. 
";

%feature("docstring")  MultiLayerUtils::IndexOfLayer "size_t MultiLayerUtils::IndexOfLayer(const MultiLayer &multilayer, const Layer *p_layer)

Returns the index of the given layer. 
";

%feature("docstring")  MultiLayerUtils::ContainsCompatibleMaterials "bool MultiLayerUtils::ContainsCompatibleMaterials(const MultiLayer &multilayer)

Returns true if the multilayer contains non-default materials of one type only. 
";

%feature("docstring")  MultiLayerUtils::ParticleRegions "std::vector< ZLimits > MultiLayerUtils::ParticleRegions(const MultiLayer &multilayer, bool use_slicing)

Calculate z-regions occupied by particles. 
";

%feature("docstring")  MultiLayerUtils::hasRoughness "bool MultiLayerUtils::hasRoughness(const MultiLayer &sample)
";


// File: namespaceNodeUtils.xml
%feature("docstring")  NodeUtils::nodeToString "std::string NodeUtils::nodeToString(const INode &node)

Returns multiline string representing tree structure starting from given node. 
";

%feature("docstring")  NodeUtils::nodePath "std::string NodeUtils::nodePath(const INode &node, const INode *root=nullptr)

Returns path composed of node's displayName, with respect to root node. 
";


// File: namespaceNumeric.xml
%feature("docstring")  Numeric::AreAlmostEqual "bool BA_CORE_API_ Numeric::AreAlmostEqual(double a, double b, double tolerance)

Returns true if two doubles agree within epsilon*tolerance. 
";

%feature("docstring")  Numeric::GetAbsoluteDifference "double BA_CORE_API_ Numeric::GetAbsoluteDifference(double a, double b)

Returns the absolute value of the difference between a and b. 
";

%feature("docstring")  Numeric::GetRelativeDifference "double BA_CORE_API_ Numeric::GetRelativeDifference(double a, double b)

Returns the safe relative difference, which is 2(|a-b|)/(|a|+|b|) except in special cases. 
";

%feature("docstring")  Numeric::GetLogDifference "double BA_CORE_API_ Numeric::GetLogDifference(double a, double b)

Returns the difference of the logarithm; input values are truncated at the minimum positive value 
";


// File: namespaceObjectiveMetricUtils.xml
%feature("docstring")  ObjectiveMetricUtils::l1Norm "const std::function< double(double)> ObjectiveMetricUtils::l1Norm()

Returns L1 normalization function. 
";

%feature("docstring")  ObjectiveMetricUtils::l2Norm "const std::function< double(double)> ObjectiveMetricUtils::l2Norm()

Returns L2 normalization function. 
";

%feature("docstring")  ObjectiveMetricUtils::createMetric "std::unique_ptr< ObjectiveMetric > ObjectiveMetricUtils::createMetric(const std::string &metric)

Creates the specified metric with the default norm. 
";

%feature("docstring")  ObjectiveMetricUtils::createMetric "std::unique_ptr< ObjectiveMetric > ObjectiveMetricUtils::createMetric(std::string metric, std::string norm)

Creates the metric with the specified norm. 
";

%feature("docstring")  ObjectiveMetricUtils::availableMetricOptions "std::string ObjectiveMetricUtils::availableMetricOptions()

Prints available metric options. 
";

%feature("docstring")  ObjectiveMetricUtils::normNames "std::vector< std::string > ObjectiveMetricUtils::normNames()

Returns the names of the norms used by  ObjectiveMetric. 
";

%feature("docstring")  ObjectiveMetricUtils::metricNames "std::vector< std::string > ObjectiveMetricUtils::metricNames()

Returns the names of the objective metrics used. 
";

%feature("docstring")  ObjectiveMetricUtils::defaultNormName "std::string ObjectiveMetricUtils::defaultNormName()

Returns default norm name. 
";

%feature("docstring")  ObjectiveMetricUtils::defaultMetricName "std::string ObjectiveMetricUtils::defaultMetricName()

Returns default metric name. 
";


// File: namespaceParameterUtils.xml
%feature("docstring")  ParameterUtils::isAngleRelated "bool ParameterUtils::isAngleRelated(const std::string &par_name)

Returns true if given parameter name is related to angles. 
";

%feature("docstring")  ParameterUtils::mainParUnits "std::string ParameterUtils::mainParUnits(const ParticleDistribution &distr)

Returns units of main parameter. 
";

%feature("docstring")  ParameterUtils::poolParameterUnits "std::string ParameterUtils::poolParameterUnits(const IParameterized &node, const std::string &parName)

Returns units of main parameter. 
";


// File: namespacePhysConsts.xml


// File: namespacePrecomputed.xml
%feature("docstring")  Precomputed::GenerateArrayHelper "constexpr std::array<double, sizeof...(I)> Precomputed::GenerateArrayHelper(std::index_sequence< I... >)
";

%feature("docstring")  Precomputed::GenerateReciprocalFactorialArray "constexpr std::array<double, N> Precomputed::GenerateReciprocalFactorialArray()
";


// File: namespacePyArrayImport.xml
%feature("docstring")  PyArrayImport::importArrayToOutputData "OutputData< double > * PyArrayImport::importArrayToOutputData(const std::vector< double > &vec)

for importing 1D array of doubles from python into  OutputData
";

%feature("docstring")  PyArrayImport::importArrayToOutputData "OutputData< double > * PyArrayImport::importArrayToOutputData(const std::vector< std::vector< double >> &vec)

for importing 2D array of doubles from python into  OutputData
";


// File: namespacePyEmbeddedUtils.xml
%feature("docstring")  PyEmbeddedUtils::toString "std::string PyEmbeddedUtils::toString(PyObject *obj)

Converts PyObject into string, if possible, or throws exception. 
";

%feature("docstring")  PyEmbeddedUtils::toVectorString "std::vector< std::string > PyEmbeddedUtils::toVectorString(PyObject *obj)

Converts PyObject into vector of strings, if possible, or throws exception. 
";

%feature("docstring")  PyEmbeddedUtils::toString "std::string PyEmbeddedUtils::toString(char *c)

Converts char to string. In the case of nullptr will return an empty string. 
";

%feature("docstring")  PyEmbeddedUtils::toString "std::string PyEmbeddedUtils::toString(wchar_t *c)
";

%feature("docstring")  PyEmbeddedUtils::import_bornagain "void PyEmbeddedUtils::import_bornagain(const std::string &path=std::string())

Imports  BornAgain from given location. If path is empty, tries to rely on PYTHONPATH. 
";

%feature("docstring")  PyEmbeddedUtils::pythonRuntimeInfo "std::string PyEmbeddedUtils::pythonRuntimeInfo()

Returns multi-line string representing PATH, PYTHONPATH, sys.path and other info. 
";

%feature("docstring")  PyEmbeddedUtils::pythonStackTrace "std::string PyEmbeddedUtils::pythonStackTrace()

Returns string representing python stack trace. 
";


// File: namespacePyImport.xml
%feature("docstring")  PyImport::createFromPython "std::unique_ptr< MultiLayer > PyImport::createFromPython(const std::string &script, const std::string &functionName, const std::string &path=std::string())

Creates a multi layer by running python code in embedded interpreter.

Parameters:
-----------

script: 
Python script

functionName: 
A function name in this script which produces a  MultiLayer

path: 
A path to import  BornAgain library. If empty, relies on PYTHONPATH 
";

%feature("docstring")  PyImport::listOfFunctions "std::vector< std::string > PyImport::listOfFunctions(const std::string &script, const std::string &path=std::string())

Returns list of functions defined in the script.

Parameters:
-----------

script: 
Python script

path: 
A path to import  BornAgain library. If empty, relies on PYTHONPATH 
";


// File: namespacePythonFormatting.xml
%feature("docstring")  PythonFormatting::scriptPreamble "BA_CORE_API_ std::string PythonFormatting::scriptPreamble()
";

%feature("docstring")  PythonFormatting::getSampleFunctionName "BA_CORE_API_ std::string PythonFormatting::getSampleFunctionName()
";

%feature("docstring")  PythonFormatting::representShape2D "BA_CORE_API_ std::string PythonFormatting::representShape2D(const std::string &indent, const IShape2D *ishape, bool mask_value, std::function< std::string(double)> printValueFunc)

Returns fixed Python code snippet that defines the function \"runSimulation\". 
";

%feature("docstring")  PythonFormatting::printBool "BA_CORE_API_ std::string PythonFormatting::printBool(double value)
";

%feature("docstring")  PythonFormatting::printDouble "BA_CORE_API_ std::string PythonFormatting::printDouble(double input)
";

%feature("docstring")  PythonFormatting::printNm "BA_CORE_API_ std::string PythonFormatting::printNm(double input)
";

%feature("docstring")  PythonFormatting::printNm2 "BA_CORE_API_ std::string PythonFormatting::printNm2(double input)
";

%feature("docstring")  PythonFormatting::printScientificDouble "BA_CORE_API_ std::string PythonFormatting::printScientificDouble(double input)
";

%feature("docstring")  PythonFormatting::printDegrees "BA_CORE_API_ std::string PythonFormatting::printDegrees(double input)
";

%feature("docstring")  PythonFormatting::printValue "BA_CORE_API_ std::string PythonFormatting::printValue(double value, const std::string &units)
";

%feature("docstring")  PythonFormatting::printString "BA_CORE_API_ std::string PythonFormatting::printString(const std::string &value)
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

%feature("docstring")  PythonFormatting::printDistribution "BA_CORE_API_ std::string PythonFormatting::printDistribution(const IDistribution1D &par_distr, const std::string &units)

Prints distribution with constructor parameters in given units. ba.DistributionGaussian(2.0*deg, 0.02*deg) 
";

%feature("docstring")  PythonFormatting::printRealLimits "BA_CORE_API_ std::string PythonFormatting::printRealLimits(const RealLimits &limits, const std::string &units)
";

%feature("docstring")  PythonFormatting::printRealLimitsArg "BA_CORE_API_ std::string PythonFormatting::printRealLimitsArg(const RealLimits &limits, const std::string &units)

Prints RealLimits in the form of argument (in the context of  ParameterDistribution and similar). Default RealLimits will not be printed, any other will be printed as \", ba.RealLimits.limited(1*deg, 2*deg)\" 
";

%feature("docstring")  PythonFormatting::printParameterDistribution "BA_CORE_API_ std::string PythonFormatting::printParameterDistribution(const ParameterDistribution &par_distr, const std::string &distVarName, const std::string &units)

Prints  ParameterDistribution. distVarName is a string representing  IDistribution1D variable, e.g. \"distr_1\"

ba.ParameterDistribution(\"/Particle/Height\", distr_1, 10, 0.0, ba.RealLimits.limited(1*nm,2*nm)) 
";

%feature("docstring")  PythonFormatting::printAxis "BA_CORE_API_ std::string PythonFormatting::printAxis(const IAxis &axis, const std::string &units, size_t offset)

Prints python-script definition for given axis. offset is used for alignment and indentation in multiple-line definitions 
";

%feature("docstring")  PythonFormatting::indent "BA_CORE_API_ std::string PythonFormatting::indent(size_t width)

Returns a string of blanks with given width. By default the width equals standard offset in python files. 
";

%feature("docstring")  PythonFormatting::printInt "BA_CORE_API_ std::string PythonFormatting::printInt(int value)
";


// File: namespaceripples.xml
%feature("docstring")  ripples::factor_x_box "complex_t ripples::factor_x_box(complex_t q, double l)
";

%feature("docstring")  ripples::factor_x_Gauss "complex_t ripples::factor_x_Gauss(complex_t q, double l)
";

%feature("docstring")  ripples::factor_x_Lorentz "complex_t ripples::factor_x_Lorentz(complex_t q, double l)
";


// File: namespaceSpectrumUtils.xml
%feature("docstring")  SpectrumUtils::FindPeaks "std::vector< std::pair< double, double > > SpectrumUtils::FindPeaks(const Histogram2D &hist, double sigma=2, const std::string &option={}, double threshold=0.05)
";


// File: namespaceStandardSimulations.xml
%feature("docstring")  StandardSimulations::BasicGISAS "GISASSimulation * StandardSimulations::BasicGISAS()

Basic GISAS simulation with the detector phi[0,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::BasicGISAS00 "GISASSimulation * StandardSimulations::BasicGISAS00()

Basic GISAS for polarization studies. 
";

%feature("docstring")  StandardSimulations::BasicPolarizedGISAS "GISASSimulation * StandardSimulations::BasicPolarizedGISAS()

Basic GISAS simulation for spin flip channel. 
";

%feature("docstring")  StandardSimulations::MiniGISAS "GISASSimulation * StandardSimulations::MiniGISAS()

GISAS simulation with small detector and phi[-2,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::MiniGISAS_v2 "GISASSimulation * StandardSimulations::MiniGISAS_v2()

GISAS simulation with small detector and phi[-1,1], theta[0,1]. 
";

%feature("docstring")  StandardSimulations::MiniGISASBeamDivergence "GISASSimulation * StandardSimulations::MiniGISASBeamDivergence()

GISAS simulation with beam divergence applied. 
";

%feature("docstring")  StandardSimulations::MiniGISASDetectorResolution "GISASSimulation * StandardSimulations::MiniGISASDetectorResolution()

GISAS simulation with detector resolution. 
";

%feature("docstring")  StandardSimulations::MiniGISASSpecularPeak "GISASSimulation * StandardSimulations::MiniGISASSpecularPeak()

GISAS simulation with small detector and including specular peak. 
";

%feature("docstring")  StandardSimulations::GISASWithMasks "GISASSimulation * StandardSimulations::GISASWithMasks()

GISAS simulation with multiple masks on the detector plane. 
";

%feature("docstring")  StandardSimulations::MaxiGISAS "GISASSimulation * StandardSimulations::MaxiGISAS()

GISAS simulation with large detector to test performance. 
";

%feature("docstring")  StandardSimulations::MaxiGISAS00 "GISASSimulation * StandardSimulations::MaxiGISAS00()

Basic GISAS for polarization studies. 
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation1 "GISASSimulation * StandardSimulations::IsGISAXSSimulation1()

Typical IsGISAXS simulation with the detector phi[-1,1], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation2 "GISASSimulation * StandardSimulations::IsGISAXSSimulation2()

Typical IsGISAXS simulation with the detector phi[0,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::RectDetectorGeneric "GISASSimulation * StandardSimulations::RectDetectorGeneric()

GISAS simulation with generic rectangular detector. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToSample "GISASSimulation * StandardSimulations::RectDetectorPerpToSample()

GISAS simulation with the rectangular detector perpendicular to the sample. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToDirectBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToDirectBeam()

GISAS simulation with the rectangular detector perpendicular to the direct beam. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeam()

GISAS simulation with the rectangular detector perpendicular to the reflected beam. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeamDpos "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeamDpos()

GISAS simulation with the rectangular detector perpendicular to the reflected beam when the coordinates of direct beam are known. 
";

%feature("docstring")  StandardSimulations::MiniGISASMonteCarlo "GISASSimulation * StandardSimulations::MiniGISASMonteCarlo()

GISAS simulation with Monte-Carlo integration switched ON. 
";

%feature("docstring")  StandardSimulations::SphericalDetWithRoi "GISASSimulation * StandardSimulations::SphericalDetWithRoi()

GISAS simulation with spherical detector, region of interest and mask. 
";

%feature("docstring")  StandardSimulations::RectDetWithRoi "GISASSimulation * StandardSimulations::RectDetWithRoi()

GISAS simulation with rectangular detector, region of interest and mask. 
";

%feature("docstring")  StandardSimulations::ConstantBackgroundGISAS "GISASSimulation * StandardSimulations::ConstantBackgroundGISAS()
";

%feature("docstring")  StandardSimulations::MiniGISASFit "GISASSimulation * StandardSimulations::MiniGISASFit()

Simulation with fitting.  Beam intensity set to provide reasonably large values in detector channels. 
";

%feature("docstring")  StandardSimulations::ExtraLongWavelengthGISAS "GISASSimulation * StandardSimulations::ExtraLongWavelengthGISAS()

GISAS simulation with an extra long wavelength. 
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationPP "GISASSimulation * StandardSimulations::MiniGISASPolarizationPP()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationPM "GISASSimulation * StandardSimulations::MiniGISASPolarizationPM()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationMP "GISASSimulation * StandardSimulations::MiniGISASPolarizationMP()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationMM "GISASSimulation * StandardSimulations::MiniGISASPolarizationMM()
";

%feature("docstring")  StandardSimulations::BasicSpecular "SpecularSimulation * StandardSimulations::BasicSpecular()
";

%feature("docstring")  StandardSimulations::BasicSpecularQ "SpecularSimulation * StandardSimulations::BasicSpecularQ()
";

%feature("docstring")  StandardSimulations::SpecularWithGaussianBeam "SpecularSimulation * StandardSimulations::SpecularWithGaussianBeam()
";

%feature("docstring")  StandardSimulations::SpecularWithSquareBeam "SpecularSimulation * StandardSimulations::SpecularWithSquareBeam()
";

%feature("docstring")  StandardSimulations::SpecularDivergentBeam "SpecularSimulation * StandardSimulations::SpecularDivergentBeam()
";

%feature("docstring")  StandardSimulations::TOFRWithRelativeResolution "SpecularSimulation * StandardSimulations::TOFRWithRelativeResolution()
";

%feature("docstring")  StandardSimulations::TOFRWithPointwiseResolution "SpecularSimulation * StandardSimulations::TOFRWithPointwiseResolution()
";

%feature("docstring")  StandardSimulations::BasicSpecularPP "SpecularSimulation * StandardSimulations::BasicSpecularPP()
";

%feature("docstring")  StandardSimulations::BasicSpecularMM "SpecularSimulation * StandardSimulations::BasicSpecularMM()
";

%feature("docstring")  StandardSimulations::BasicSpecularQPP "SpecularSimulation * StandardSimulations::BasicSpecularQPP()
";

%feature("docstring")  StandardSimulations::BasicSpecularQMM "SpecularSimulation * StandardSimulations::BasicSpecularQMM()
";

%feature("docstring")  StandardSimulations::MiniOffSpec "OffSpecSimulation * StandardSimulations::MiniOffSpec()
";

%feature("docstring")  StandardSimulations::BasicDepthProbe "DepthProbeSimulation * StandardSimulations::BasicDepthProbe()
";


// File: namespaceSysUtils.xml
%feature("docstring")  SysUtils::getCurrentDateAndTime "std::string SysUtils::getCurrentDateAndTime()
";

%feature("docstring")  SysUtils::enableFloatingPointExceptions "void SysUtils::enableFloatingPointExceptions()

Enables exception throw in the case of NaN, Inf.

enables exception throw in the case of NaN, Inf 
";

%feature("docstring")  SysUtils::getenv "std::string SysUtils::getenv(const std::string &name)

Returns environment variable. 
";

%feature("docstring")  SysUtils::isWindowsHost "bool SysUtils::isWindowsHost()

Returns true if operation system is Windows. 
";


// File: namespaceUnitConverterUtils.xml
%feature("docstring")  UnitConverterUtils::substituteDefaultUnits "AxesUnits UnitConverterUtils::substituteDefaultUnits(const IUnitConverter &converter, AxesUnits units)
";

%feature("docstring")  UnitConverterUtils::createOutputData "std::unique_ptr< OutputData< double > > UnitConverterUtils::createOutputData(const IUnitConverter &converter, AxesUnits units)

Returns zero-valued output data array in specified units. 
";

%feature("docstring")  UnitConverterUtils::createConverterForGISAS "std::unique_ptr< IUnitConverter > UnitConverterUtils::createConverterForGISAS(const Instrument &instrument)

Helper factory function to use in  GISASSimulation. Depending on the type of detector, returns either  RectangularConverter or  SphericalConverter. 
";

%feature("docstring")  UnitConverterUtils::createConverter "std::unique_ptr< IUnitConverter > UnitConverterUtils::createConverter(const Simulation &simulation)
";


// File: namespaceUnits.xml
%feature("docstring")  Units::rad2deg "double Units::rad2deg(double angle)
";

%feature("docstring")  Units::deg2rad "double Units::deg2rad(double angle)
";


// File: FormFactorCoherentPart_8cpp.xml


// File: FormFactorCoherentPart_8h.xml


// File: FormFactorCoherentSum_8cpp.xml


// File: FormFactorCoherentSum_8h.xml


// File: FTDecayFunctions_8cpp.xml


// File: FTDecayFunctions_8h.xml


// File: FTDistributions1D_8cpp.xml


// File: FTDistributions1D_8h.xml


// File: FTDistributions2D_8cpp.xml


// File: FTDistributions2D_8h.xml


// File: IDistribution1DSampler_8cpp.xml


// File: IDistribution1DSampler_8h.xml


// File: IDistribution2DSampler_8cpp.xml


// File: IDistribution2DSampler_8h.xml


// File: IInterferenceFunction_8cpp.xml


// File: IInterferenceFunction_8h.xml


// File: ILayout_8cpp.xml


// File: ILayout_8h.xml


// File: InterferenceFunction1DLattice_8cpp.xml


// File: InterferenceFunction1DLattice_8h.xml


// File: InterferenceFunction2DLattice_8cpp.xml


// File: InterferenceFunction2DLattice_8h.xml


// File: InterferenceFunction2DParaCrystal_8cpp.xml


// File: InterferenceFunction2DParaCrystal_8h.xml


// File: InterferenceFunction2DSuperLattice_8cpp.xml


// File: InterferenceFunction2DSuperLattice_8h.xml


// File: InterferenceFunction3DLattice_8cpp.xml


// File: InterferenceFunction3DLattice_8h.xml


// File: InterferenceFunctionFinite2DLattice_8cpp.xml


// File: InterferenceFunctionFinite2DLattice_8h.xml


// File: InterferenceFunctionFinite3DLattice_8cpp.xml


// File: InterferenceFunctionFinite3DLattice_8h.xml


// File: InterferenceFunctionHardDisk_8cpp.xml


// File: InterferenceFunctionHardDisk_8h.xml


// File: InterferenceFunctionNone_8cpp.xml


// File: InterferenceFunctionNone_8h.xml


// File: InterferenceFunctionRadialParaCrystal_8cpp.xml


// File: InterferenceFunctionRadialParaCrystal_8h.xml


// File: InterferenceFunctionTwin_8cpp.xml


// File: InterferenceFunctionTwin_8h.xml


// File: IPeakShape_8cpp.xml


// File: IPeakShape_8h.xml


// File: ParticleLayout_8cpp.xml


// File: ParticleLayout_8h.xml


// File: Algorithms_8h.xml


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


// File: ICloneable_8cpp.xml


// File: ICloneable_8h.xml


// File: INamed_8cpp.xml


// File: INamed_8h.xml


// File: ISingleton_8h.xml


// File: MathConstants_8h.xml


// File: PhysicalConstants_8h.xml


// File: Beam_8cpp.xml


// File: Beam_8h.xml


// File: FootprintFactorGaussian_8cpp.xml


// File: FootprintFactorGaussian_8h.xml


// File: FootprintFactorSquare_8cpp.xml


// File: FootprintFactorSquare_8h.xml


// File: IFootprintFactor_8cpp.xml


// File: IFootprintFactor_8h.xml


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


// File: IPixel_8h.xml


// File: PointwiseAxis_8cpp.xml


// File: PointwiseAxis_8h.xml


// File: VariableBinAxis_8cpp.xml


// File: VariableBinAxis_8h.xml


// File: ComputationStatus_8h.xml


// File: ConstantBackground_8cpp.xml


// File: ConstantBackground_8h.xml


// File: DelayedProgressCounter_8cpp.xml


// File: DelayedProgressCounter_8h.xml


// File: DepthProbeComputation_8cpp.xml


// File: DepthProbeComputation_8h.xml


// File: DepthProbeComputationTerm_8cpp.xml


// File: DepthProbeComputationTerm_8h.xml


// File: DWBAComputation_8cpp.xml


// File: DWBAComputation_8h.xml


// File: DWBASingleComputation_8cpp.xml


// File: DWBASingleComputation_8h.xml


// File: GISASSpecularComputation_8cpp.xml


// File: GISASSpecularComputation_8h.xml


// File: IBackground_8cpp.xml


// File: IBackground_8h.xml


// File: IComputation_8cpp.xml


// File: IComputation_8h.xml


// File: MultiLayerUtils_8cpp.xml


// File: MultiLayerUtils_8h.xml


// File: ParticleLayoutComputation_8cpp.xml


// File: ParticleLayoutComputation_8h.xml


// File: PoissonNoiseBackground_8cpp.xml


// File: PoissonNoiseBackground_8h.xml


// File: ProcessedLayout_8cpp.xml


// File: ProcessedLayout_8h.xml


// File: ProcessedSample_8cpp.xml


// File: ProcessedSample_8h.xml


// File: ProfileHelper_8cpp.xml


// File: ProfileHelper_8h.xml


// File: ProgressHandler_8cpp.xml


// File: ProgressHandler_8h.xml


// File: RoughMultiLayerComputation_8cpp.xml


// File: RoughMultiLayerComputation_8h.xml


// File: Slice_8cpp.xml


// File: Slice_8h.xml


// File: SpecularComputation_8cpp.xml


// File: SpecularComputation_8h.xml


// File: SpecularComputationTerm_8cpp.xml


// File: SpecularComputationTerm_8h.xml


// File: FormFactorDecoratorMaterial_8cpp.xml


// File: FormFactorDecoratorMaterial_8h.xml


// File: FormFactorDecoratorPositionFactor_8cpp.xml


// File: FormFactorDecoratorPositionFactor_8h.xml


// File: FormFactorDecoratorRotation_8cpp.xml


// File: FormFactorDecoratorRotation_8h.xml


// File: IFormFactorDecorator_8h.xml


// File: ExportToPython_8cpp.xml


// File: ExportToPython_8h.xml


// File: INodeUtils_8h.xml


// File: PythonFormatting_8cpp.xml


// File: PythonFormatting_8h.xml


// File: SampleLabelHandler_8cpp.xml


// File: SampleLabelHandler_8h.xml


// File: SampleToPython_8cpp.xml


// File: SampleToPython_8h.xml


// File: SimulationToPython_8cpp.xml


// File: SimulationToPython_8h.xml


// File: FitObjective_8cpp.xml


// File: FitObjective_8h.xml


// File: FitObserver_8h.xml


// File: FitPrintService_8cpp.xml


// File: FitPrintService_8h.xml


// File: FitStatus_8cpp.xml


// File: FitStatus_8h.xml


// File: FitTypes_8h.xml


// File: IObserver_8cpp.xml


// File: IObserver_8h.xml


// File: IterationInfo_8cpp.xml


// File: IterationInfo_8h.xml


// File: ObjectiveMetric_8cpp.xml


// File: ObjectiveMetric_8h.xml


// File: ObjectiveMetricUtils_8cpp.xml


// File: ObjectiveMetricUtils_8h.xml


// File: PyFittingCallbacks_8cpp.xml


// File: PyFittingCallbacks_8h.xml


// File: SimDataPair_8cpp.xml


// File: SimDataPair_8h.xml


// File: FormFactorAnisoPyramid_8cpp.xml


// File: FormFactorAnisoPyramid_8h.xml


// File: FormFactorBar_8cpp.xml


// File: FormFactorBar_8h.xml


// File: FormFactorBox_8cpp.xml


// File: FormFactorBox_8h.xml


// File: FormFactorCantellatedCube_8cpp.xml


// File: FormFactorCantellatedCube_8h.xml


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


// File: FormFactorDot_8cpp.xml


// File: FormFactorDot_8h.xml


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


// File: FormFactorPolyhedron_8cpp.xml


// File: FormFactorPolyhedron_8h.xml


// File: FormFactorPrism3_8cpp.xml


// File: FormFactorPrism3_8h.xml


// File: FormFactorPrism6_8cpp.xml


// File: FormFactorPrism6_8h.xml


// File: FormFactorPyramid_8cpp.xml


// File: FormFactorPyramid_8h.xml


// File: FormFactorRipple1_8cpp.xml


// File: FormFactorRipple1_8h.xml


// File: FormFactorRipple2_8cpp.xml


// File: FormFactorRipple2_8h.xml


// File: FormFactorTetrahedron_8cpp.xml


// File: FormFactorTetrahedron_8h.xml


// File: FormFactorTriangle_8cpp.xml


// File: FormFactorTriangle_8h.xml


// File: FormFactorTruncatedCube_8cpp.xml


// File: FormFactorTruncatedCube_8h.xml


// File: FormFactorTruncatedSphere_8cpp.xml


// File: FormFactorTruncatedSphere_8h.xml


// File: FormFactorTruncatedSpheroid_8cpp.xml


// File: FormFactorTruncatedSpheroid_8h.xml


// File: ProfileBar_8cpp.xml


// File: ProfileBar_8h.xml


// File: ProfileRipple1_8cpp.xml


// File: ProfileRipple1_8h.xml


// File: ProfileRipple2_8cpp.xml


// File: ProfileRipple2_8h.xml


// File: Ripples_8cpp.xml


// File: Ripples_8h.xml


// File: FormFactors_8h.xml


// File: HardParticles_8h.xml


// File: InterferenceFunctions_8h.xml


// File: SoftParticles_8h.xml


// File: boost__streams_8h.xml


// File: DataFormatUtils_8cpp.xml


// File: DataFormatUtils_8h.xml


// File: IntensityDataIOFactory_8cpp.xml


// File: IntensityDataIOFactory_8h.xml


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


// File: OutputDataWriteStrategy_8h.xml


// File: TiffHandler_8cpp.xml


// File: TiffHandler_8h.xml


// File: AngularSpecScan_8cpp.xml


// File: AngularSpecScan_8h.xml


// File: ArrayUtils_8cpp.xml


// File: ArrayUtils_8h.xml


// File: AxisNames_8cpp.xml


// File: AxisNames_8h.xml


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


// File: DetectorContext_8cpp.xml


// File: DetectorContext_8h.xml


// File: DetectorFunctions_8cpp.xml


// File: DetectorFunctions_8h.xml


// File: DetectorMask_8cpp.xml


// File: DetectorMask_8h.xml


// File: FourierTransform_8cpp.xml


// File: FourierTransform_8h.xml


// File: Histogram1D_8cpp.xml


// File: Histogram1D_8h.xml


// File: Histogram2D_8cpp.xml


// File: Histogram2D_8h.xml


// File: IChiSquaredModule_8cpp.xml


// File: IChiSquaredModule_8h.xml


// File: IDetector_8cpp.xml


// File: IDetector_8h.xml


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


// File: ISpecularScan_8cpp.xml


// File: ISpecularScan_8h.xml


// File: IUnitConverter_8cpp.xml


// File: IUnitConverter_8h.xml


// File: LLData_8cpp.xml


// File: LLData_8h.xml
%feature("docstring")  HaveSameDimensions "bool HaveSameDimensions(const LLData< T > &left, const LLData< T > &right)
";


// File: OutputData_8cpp.xml


// File: OutputData_8h.xml


// File: OutputDataIterator_8h.xml
%feature("docstring")  swap "void swap(OutputDataIterator< TValue, TContainer > &left, OutputDataIterator< TValue, TContainer > &right)

make Swappable 
";


// File: PyArrayImportUtils_8cpp.xml


// File: PyArrayImportUtils_8h.xml


// File: QSpecScan_8cpp.xml


// File: QSpecScan_8h.xml


// File: RectangularDetector_8cpp.xml


// File: RectangularDetector_8h.xml


// File: RegionOfInterest_8cpp.xml


// File: RegionOfInterest_8h.xml


// File: ResolutionFunction2DGaussian_8cpp.xml


// File: ResolutionFunction2DGaussian_8h.xml


// File: SampleBuilderNode_8cpp.xml


// File: SampleBuilderNode_8h.xml


// File: SampleProvider_8cpp.xml


// File: SampleProvider_8h.xml


// File: ScanResolution_8cpp.xml


// File: ScanResolution_8h.xml


// File: SimpleUnitConverters_8cpp.xml


// File: SimpleUnitConverters_8h.xml


// File: SimulationArea_8cpp.xml


// File: SimulationArea_8h.xml


// File: SimulationAreaIterator_8cpp.xml


// File: SimulationAreaIterator_8h.xml


// File: SimulationResult_8cpp.xml


// File: SimulationResult_8h.xml


// File: SpecularDetector1D_8cpp.xml


// File: SpecularDetector1D_8h.xml


// File: SphericalDetector_8cpp.xml


// File: SphericalDetector_8h.xml


// File: UnitConverter1D_8cpp.xml


// File: UnitConverter1D_8h.xml


// File: UnitConverterUtils_8cpp.xml


// File: UnitConverterUtils_8h.xml


// File: VarianceFunctions_8cpp.xml


// File: VarianceFunctions_8h.xml


// File: ILatticeOrientation_8cpp.xml


// File: ILatticeOrientation_8h.xml


// File: ISelectionRule_8h.xml


// File: Lattice_8cpp.xml


// File: Lattice_8h.xml


// File: Lattice1DParameters_8h.xml


// File: Lattice2D_8cpp.xml


// File: Lattice2D_8h.xml


// File: LatticeUtils_8cpp.xml


// File: LatticeUtils_8h.xml


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


// File: BaseMaterialImpl_8h.xml


// File: MagneticMaterialImpl_8cpp.xml


// File: MagneticMaterialImpl_8h.xml


// File: Material_8cpp.xml


// File: Material_8h.xml


// File: MaterialBySLDImpl_8cpp.xml


// File: MaterialBySLDImpl_8h.xml


// File: MaterialFactoryFuncs_8cpp.xml
%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial(const std::string &name, complex_t refractive_index, kvector_t magnetization)

Constructs a material with  name,  refractive_index and  magnetization (in A/m). Alternatively,  $\\\\delta$ and  $\\\\beta$ for refractive index  $n = 1 - \\\\delta + i \\\\beta$ can be passed directly. With no parameters given, constructs default (vacuum) material with  $n = 1$ and zero magnetization. 
";

%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial(const std::string &name, double delta, double beta, kvector_t magnetization)
";

%feature("docstring")  HomogeneousMaterial "Material HomogeneousMaterial()
";

%feature("docstring")  MaterialBySLD "Material MaterialBySLD()
";

%feature("docstring")  MaterialBySLD "Material MaterialBySLD(const std::string &name, double sld_real, double sld_imag, kvector_t magnetization)

Constructs a wavelength-independent material with a given complex-valued scattering length density (SLD). SLD values for a wide variety of materials can be found on https://sld-calculator.appspot.com/ and https://www.ncnr.nist.gov/resources/activation/ By convention, SLD imaginary part is treated as negative by default, which corresponds to attenuation of the signal. With no parameters given, MaterialBySLD constructs default (vacuum) material with zero sld and zero magnetization.

Parameters:
-----------

name: 
material name

sld_real: 
real part of the scattering length density, inverse square angstroms

sld_imag: 
imaginary part of the scattering length density, inverse square angstroms

magnetization: 
magnetization (in A/m) 
";

%feature("docstring")  CreateAveragedMaterial "Material CreateAveragedMaterial(const Material &layer_mat, const std::vector< HomogeneousRegion > &regions)

Creates averaged material. Square refractive index of returned material is arithmetic mean over  regions and  layer_mat. Magnetization (if present) is averaged linearly. 
";


// File: MaterialFactoryFuncs_8h.xml
%feature("docstring")  HomogeneousMaterial "BA_CORE_API_ Material HomogeneousMaterial()
";

%feature("docstring")  HomogeneousMaterial "BA_CORE_API_ Material HomogeneousMaterial(const std::string &name, double delta, double beta, kvector_t magnetization=kvector_t())
";

%feature("docstring")  HomogeneousMaterial "BA_CORE_API_ Material HomogeneousMaterial(const std::string &name, complex_t refractive_index, kvector_t magnetization=kvector_t())

Constructs a material with  name,  refractive_index and  magnetization (in A/m). Alternatively,  $\\\\delta$ and  $\\\\beta$ for refractive index  $n = 1 - \\\\delta + i \\\\beta$ can be passed directly. With no parameters given, constructs default (vacuum) material with  $n = 1$ and zero magnetization. 
";

%feature("docstring")  MaterialBySLD "BA_CORE_API_ Material MaterialBySLD()
";

%feature("docstring")  MaterialBySLD "BA_CORE_API_ Material MaterialBySLD(const std::string &name, double sld_real, double sld_imag, kvector_t magnetization=kvector_t())

Constructs a wavelength-independent material with a given complex-valued scattering length density (SLD). SLD values for a wide variety of materials can be found on https://sld-calculator.appspot.com/ and https://www.ncnr.nist.gov/resources/activation/ By convention, SLD imaginary part is treated as negative by default, which corresponds to attenuation of the signal. With no parameters given, MaterialBySLD constructs default (vacuum) material with zero sld and zero magnetization.

Parameters:
-----------

name: 
material name

sld_real: 
real part of the scattering length density, inverse square angstroms

sld_imag: 
imaginary part of the scattering length density, inverse square angstroms

magnetization: 
magnetization (in A/m) 
";

%feature("docstring")  CreateAveragedMaterial "BA_CORE_API_ Material CreateAveragedMaterial(const Material &layer_mat, const std::vector< HomogeneousRegion > &regions)

Creates averaged material. Square refractive index of returned material is arithmetic mean over  regions and  layer_mat. Magnetization (if present) is averaged linearly. 
";


// File: MaterialUtils_8cpp.xml
%feature("docstring")  Unit_Matrix "const Eigen::Matrix2cd Unit_Matrix(Eigen::Matrix2cd::Identity())
";


// File: MaterialUtils_8h.xml


// File: RefractiveMaterialImpl_8cpp.xml


// File: RefractiveMaterialImpl_8h.xml


// File: DecouplingApproximationStrategy_8cpp.xml


// File: DecouplingApproximationStrategy_8h.xml


// File: FormFactorBAPol_8cpp.xml


// File: FormFactorBAPol_8h.xml


// File: FormFactorDWBA_8cpp.xml


// File: FormFactorDWBA_8h.xml


// File: FormFactorDWBAPol_8cpp.xml


// File: FormFactorDWBAPol_8h.xml


// File: IFresnelMap_8cpp.xml


// File: IFresnelMap_8h.xml


// File: IInterferenceFunctionStrategy_8cpp.xml


// File: IInterferenceFunctionStrategy_8h.xml


// File: ILayerRTCoefficients_8h.xml


// File: IMultiLayerBuilder_8cpp.xml


// File: IMultiLayerBuilder_8h.xml


// File: InterferenceFunctionUtils_8cpp.xml


// File: InterferenceFunctionUtils_8h.xml


// File: ISpecularStrategy_8h.xml


// File: KzComputation_8cpp.xml


// File: KzComputation_8h.xml


// File: Layer_8cpp.xml


// File: Layer_8h.xml


// File: LayerFillLimits_8cpp.xml


// File: LayerFillLimits_8h.xml


// File: LayerInterface_8cpp.xml


// File: LayerInterface_8h.xml


// File: LayerRoughness_8cpp.xml


// File: LayerRoughness_8h.xml


// File: LayoutStrategyBuilder_8cpp.xml


// File: LayoutStrategyBuilder_8h.xml


// File: MatrixFresnelMap_8cpp.xml


// File: MatrixFresnelMap_8h.xml


// File: MatrixRTCoefficients_8cpp.xml


// File: MatrixRTCoefficients_8h.xml


// File: MatrixRTCoefficients__v2_8cpp.xml


// File: MatrixRTCoefficients__v2_8h.xml


// File: MultiLayer_8cpp.xml


// File: MultiLayer_8h.xml


// File: MultiLayerFuncs_8cpp.xml
%feature("docstring")  MaterialProfile "std::vector<complex_t> MaterialProfile(const MultiLayer &multilayer, int n_points, double z_min, double z_max)

Calculate average material profile for given multilayer. 
";

%feature("docstring")  DefaultMaterialProfileLimits "std::pair<double, double> DefaultMaterialProfileLimits(const MultiLayer &multilayer)

Get default z limits for generating a material profile. 
";

%feature("docstring")  GenerateZValues "std::vector<double> GenerateZValues(int n_points, double z_min, double z_max)

Generate z values (equidistant) for use in MaterialProfile. 
";


// File: MultiLayerFuncs_8h.xml
%feature("docstring")  MaterialProfile "BA_CORE_API_ std::vector<complex_t> MaterialProfile(const MultiLayer &multilayer, int n_points, double z_min, double z_max)

Calculate average material profile for given multilayer. 
";

%feature("docstring")  DefaultMaterialProfileLimits "BA_CORE_API_ std::pair<double, double> DefaultMaterialProfileLimits(const MultiLayer &multilayer)

Get default z limits for generating a material profile. 
";

%feature("docstring")  GenerateZValues "BA_CORE_API_ std::vector<double> GenerateZValues(int n_points, double z_min, double z_max)

Generate z values (equidistant) for use in MaterialProfile. 
";


// File: RoughnessModels_8cpp.xml


// File: RoughnessModels_8h.xml


// File: ScalarFresnelMap_8cpp.xml


// File: ScalarFresnelMap_8h.xml


// File: ScalarRTCoefficients_8h.xml


// File: SpecularMagneticOldStrategy_8cpp.xml


// File: SpecularMagneticOldStrategy_8h.xml


// File: SpecularMagneticStrategy_8cpp.xml


// File: SpecularMagneticStrategy_8h.xml


// File: SpecularScalarNCStrategy_8cpp.xml


// File: SpecularScalarNCStrategy_8h.xml


// File: SpecularScalarStrategy_8cpp.xml


// File: SpecularScalarStrategy_8h.xml


// File: SpecularScalarTanhStrategy_8cpp.xml


// File: SpecularScalarTanhStrategy_8h.xml


// File: SpecularStrategyBuilder_8cpp.xml


// File: SpecularStrategyBuilder_8h.xml


// File: SSCAHelper_8cpp.xml


// File: SSCAHelper_8h.xml


// File: SSCApproximationStrategy_8cpp.xml


// File: SSCApproximationStrategy_8h.xml


// File: DistributionHandler_8cpp.xml


// File: DistributionHandler_8h.xml


// File: Distributions_8cpp.xml


// File: Distributions_8h.xml


// File: INode_8cpp.xml


// File: INode_8h.xml


// File: INodeVisitor_8cpp.xml
%feature("docstring")  VisitNodesPreorder "void VisitNodesPreorder(const INode &node, INodeVisitor &visitor)
";

%feature("docstring")  VisitNodesPostorder "void VisitNodesPostorder(const INode &node, INodeVisitor &visitor)
";


// File: INodeVisitor_8h.xml
%feature("docstring")  VisitNodesPreorder "BA_CORE_API_ void VisitNodesPreorder(const INode &node, INodeVisitor &visitor)
";

%feature("docstring")  VisitNodesPostorder "BA_CORE_API_ void VisitNodesPostorder(const INode &node, INodeVisitor &visitor)
";


// File: IParameter_8h.xml


// File: IParameterized_8cpp.xml


// File: IParameterized_8h.xml


// File: IterationStrategy_8cpp.xml


// File: IterationStrategy_8h.xml


// File: NodeIterator_8cpp.xml


// File: NodeIterator_8h.xml


// File: NodeUtils_8cpp.xml


// File: NodeUtils_8h.xml


// File: ParameterDistribution_8cpp.xml


// File: ParameterDistribution_8h.xml


// File: ParameterPattern_8cpp.xml


// File: ParameterPattern_8h.xml


// File: ParameterPool_8cpp.xml


// File: ParameterPool_8h.xml


// File: ParameterSample_8h.xml


// File: ParameterUtils_8cpp.xml


// File: ParameterUtils_8h.xml


// File: RangedDistributions_8cpp.xml


// File: RangedDistributions_8h.xml


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


// File: FormFactorCoreShell_8cpp.xml


// File: FormFactorCoreShell_8h.xml


// File: FormFactorCrystal_8cpp.xml


// File: FormFactorCrystal_8h.xml


// File: FormFactorWeighted_8cpp.xml


// File: FormFactorWeighted_8h.xml


// File: HomogeneousRegion_8h.xml


// File: IAbstractParticle_8cpp.xml


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


// File: SlicedFormFactorList_8cpp.xml


// File: SlicedFormFactorList_8h.xml


// File: SlicedParticle_8cpp.xml


// File: SlicedParticle_8h.xml


// File: TRange_8h.xml


// File: ZLimits_8cpp.xml
%feature("docstring")  MinLimit "OneSidedLimit MinLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  MaxLimit "OneSidedLimit MaxLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  ConvexHull "ZLimits ConvexHull(const ZLimits &left, const ZLimits &right)
";


// File: ZLimits_8h.xml
%feature("docstring")  MinLimit "OneSidedLimit MinLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  MaxLimit "OneSidedLimit MaxLimit(const OneSidedLimit &left, const OneSidedLimit &right)
";

%feature("docstring")  ConvexHull "BA_CORE_API_ ZLimits ConvexHull(const ZLimits &left, const ZLimits &right)
";


// File: IFormFactor_8cpp.xml
%feature("docstring")  CreateTransformedFormFactor "IFormFactor* CreateTransformedFormFactor(const IFormFactor &formfactor, const IRotation &rot, kvector_t translation)
";


// File: IFormFactor_8h.xml
%feature("docstring")  CreateTransformedFormFactor "IFormFactor* CreateTransformedFormFactor(const IFormFactor &formfactor, const IRotation &rot, kvector_t translation)
";


// File: IFormFactorBorn_8cpp.xml


// File: IFormFactorBorn_8h.xml


// File: ISample_8cpp.xml


// File: ISample_8h.xml


// File: Rotations_8cpp.xml
%feature("docstring")  createProduct "IRotation* createProduct(const IRotation &left, const IRotation &right)

Returns concatenated rotation (first right, then left). 
";

%feature("docstring")  IsZRotation "bool IsZRotation(const IRotation &rot)
";


// File: Rotations_8h.xml
%feature("docstring")  createProduct "BA_CORE_API_ IRotation* createProduct(const IRotation &left, const IRotation &right)

Returns concatenated rotation (first right, then left). 
";

%feature("docstring")  IsZRotation "bool IsZRotation(const IRotation &rot)
";


// File: AnisoPyramid_8cpp.xml


// File: AnisoPyramid_8h.xml


// File: BiPyramid_8cpp.xml


// File: BiPyramid_8h.xml


// File: Box_8cpp.xml


// File: Box_8h.xml


// File: Dodecahedron_8cpp.xml


// File: Dodecahedron_8h.xml


// File: Dot_8cpp.xml


// File: Dot_8h.xml


// File: DoubleEllipse_8cpp.xml


// File: DoubleEllipse_8h.xml


// File: Icosahedron_8cpp.xml


// File: Icosahedron_8h.xml


// File: IShape_8cpp.xml
%feature("docstring")  RectangleVertices "std::vector<kvector_t> RectangleVertices(double length, double width, double z)

Helper functions to construct lists of vertices

Generate vertices of centered rectangle at height z 
";

%feature("docstring")  TriangleVertices "std::vector<kvector_t> TriangleVertices(double length, double z)

Generate vertices of centered regular triangle with vertex on x-axis at height z. 
";

%feature("docstring")  HexagonVertices "std::vector<kvector_t> HexagonVertices(double length, double z)

Generate vertices of centered regular hexagon with vertex on x-axis at height z. 
";

%feature("docstring")  EllipseVertices "std::vector<kvector_t> EllipseVertices(double r_x, double r_y, double z)

Generate vertices of centered ellipse with given semi-axes at height z. 
";


// File: IShape_8h.xml
%feature("docstring")  RectangleVertices "std::vector<kvector_t> RectangleVertices(double length, double width, double z)

Helper functions to construct lists of vertices

Generate vertices of centered rectangle at height z 
";

%feature("docstring")  TriangleVertices "std::vector<kvector_t> TriangleVertices(double length, double z)

Generate vertices of centered regular triangle with vertex on x-axis at height z. 
";

%feature("docstring")  HexagonVertices "std::vector<kvector_t> HexagonVertices(double length, double z)

Generate vertices of centered regular hexagon with vertex on x-axis at height z. 
";

%feature("docstring")  EllipseVertices "std::vector<kvector_t> EllipseVertices(double r_x, double r_y, double z)

Generate vertices of centered ellipse with given semi-axes at height z. 
";


// File: Pyramid3_8cpp.xml


// File: Pyramid3_8h.xml


// File: Pyramid6_8cpp.xml


// File: Pyramid6_8h.xml


// File: RippleCosine_8cpp.xml


// File: RippleCosine_8h.xml


// File: RippleSawtooth_8cpp.xml


// File: RippleSawtooth_8h.xml


// File: Triangle_8cpp.xml


// File: Triangle_8h.xml


// File: TruncatedCube_8cpp.xml


// File: TruncatedCube_8h.xml


// File: TruncatedEllipsoid_8cpp.xml


// File: TruncatedEllipsoid_8h.xml


// File: DepthProbeSimulation_8cpp.xml


// File: DepthProbeSimulation_8h.xml


// File: GISASSimulation_8cpp.xml


// File: GISASSimulation_8h.xml


// File: MPISimulation_8cpp.xml


// File: MPISimulation_8h.xml


// File: OffSpecSimulation_8cpp.xml


// File: OffSpecSimulation_8h.xml


// File: Simulation_8cpp.xml


// File: Simulation_8h.xml


// File: Simulation2D_8cpp.xml


// File: Simulation2D_8h.xml


// File: SpecularSimulation_8cpp.xml


// File: SpecularSimulation_8h.xml


// File: DepthProbeElement_8cpp.xml


// File: DepthProbeElement_8h.xml


// File: PolarizationHandler_8cpp.xml


// File: PolarizationHandler_8h.xml


// File: SimulationElement_8cpp.xml


// File: SimulationElement_8h.xml


// File: SpecularSimulationElement_8cpp.xml


// File: SpecularSimulationElement_8h.xml


// File: FormFactorDebyeBueche_8cpp.xml


// File: FormFactorDebyeBueche_8h.xml


// File: FormFactorGauss_8cpp.xml


// File: FormFactorGauss_8h.xml


// File: FormFactorLorentz_8cpp.xml


// File: FormFactorLorentz_8h.xml


// File: FormFactorOrnsteinZernike_8cpp.xml


// File: FormFactorOrnsteinZernike_8h.xml


// File: FormFactorSphereGaussianRadius_8cpp.xml


// File: FormFactorSphereGaussianRadius_8h.xml


// File: FormFactorSphereLogNormalRadius_8cpp.xml


// File: FormFactorSphereLogNormalRadius_8h.xml


// File: FormFactorSphereUniformRadius_8cpp.xml


// File: FormFactorSphereUniformRadius_8h.xml


// File: BoxCompositionBuilder_8cpp.xml


// File: BoxCompositionBuilder_8h.xml


// File: BoxesSquareLatticeBuilder_8cpp.xml


// File: BoxesSquareLatticeBuilder_8h.xml


// File: CoreShellParticleBuilder_8cpp.xml


// File: CoreShellParticleBuilder_8h.xml


// File: CustomMorphologyBuilder_8cpp.xml


// File: CustomMorphologyBuilder_8h.xml


// File: CylindersAndPrismsBuilder_8cpp.xml


// File: CylindersAndPrismsBuilder_8h.xml


// File: CylindersBuilder_8cpp.xml


// File: CylindersBuilder_8h.xml


// File: HomogeneousMultilayerBuilder_8cpp.xml


// File: HomogeneousMultilayerBuilder_8h.xml


// File: IFactory_8h.xml
%feature("docstring")  create_new "T* create_new()

Returns new instance of class T.

This templated function is used in catalogues in form of a function pointer 'create_new<T>', with no function arguments supplied. Equivalently, we could use a lambda function '[](){return new T;}'. 
";


// File: IRegistry_8h.xml


// File: LatticeBuilder_8cpp.xml


// File: LatticeBuilder_8h.xml


// File: LayersWithAbsorptionBuilder_8cpp.xml


// File: LayersWithAbsorptionBuilder_8h.xml


// File: LayersWithAbsorptionBySLDBuilder_8cpp.xml
%feature("docstring")  middle_layer_thickness "const double middle_layer_thickness(60.0 *Units::nanometer)
";


// File: LayersWithAbsorptionBySLDBuilder_8h.xml


// File: MagneticLayersBuilder_8cpp.xml


// File: MagneticLayersBuilder_8h.xml


// File: MagneticParticlesBuilder_8cpp.xml


// File: MagneticParticlesBuilder_8h.xml


// File: MesoCrystalBuilder_8cpp.xml


// File: MesoCrystalBuilder_8h.xml


// File: MultiLayerWithNCRoughnessBuilder_8cpp.xml


// File: MultiLayerWithNCRoughnessBuilder_8h.xml


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


// File: PercusYevickBuilder_8cpp.xml


// File: PercusYevickBuilder_8h.xml


// File: PlainMultiLayerBySLDBuilder_8cpp.xml


// File: PlainMultiLayerBySLDBuilder_8h.xml


// File: ResonatorBuilder_8cpp.xml


// File: ResonatorBuilder_8h.xml


// File: RipplesBuilder_8cpp.xml


// File: RipplesBuilder_8h.xml


// File: RotatedPyramidsBuilder_8cpp.xml


// File: RotatedPyramidsBuilder_8h.xml


// File: SampleBuilderFactory_8cpp.xml


// File: SampleBuilderFactory_8h.xml


// File: SampleComponents_8cpp.xml


// File: SampleComponents_8h.xml


// File: SimulationFactory_8cpp.xml


// File: SimulationFactory_8h.xml


// File: SizeDistributionModelsBuilder_8cpp.xml


// File: SizeDistributionModelsBuilder_8h.xml


// File: SlicedCylindersBuilder_8cpp.xml


// File: SlicedCylindersBuilder_8h.xml


// File: SlicedParticleBuilder_8cpp.xml


// File: SlicedParticleBuilder_8h.xml


// File: StandardSimulations_8cpp.xml


// File: StandardSimulations_8h.xml


// File: ThickAbsorptiveSampleBuilder_8cpp.xml


// File: ThickAbsorptiveSampleBuilder_8h.xml


// File: TransformationsBuilder_8cpp.xml


// File: TransformationsBuilder_8h.xml


// File: TwoDimLatticeBuilder_8cpp.xml


// File: TwoDimLatticeBuilder_8h.xml


// File: TwoLayerRoughnessBuilder_8cpp.xml


// File: TwoLayerRoughnessBuilder_8h.xml


// File: FileSystemUtils_8cpp.xml


// File: FileSystemUtils_8h.xml


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


// File: Integrator_8cpp.xml


// File: Integrator_8h.xml


// File: IntegratorMCMiser_8h.xml
%feature("docstring")  make_integrator_miser "P_integrator_miser<T> make_integrator_miser(const T *object, miser_integrand< T > mem_function, size_t dim)

Template function to create an integrator object 
";


// File: MathFunctions_8cpp.xml


// File: MathFunctions_8h.xml


// File: Numeric_8cpp.xml


// File: Numeric_8h.xml


// File: OrderedMap_8h.xml


// File: Precomputed_8h.xml


// File: PyEmbeddedUtils_8cpp.xml


// File: PyEmbeddedUtils_8h.xml


// File: PyImport_8cpp.xml


// File: PyImport_8h.xml


// File: PyObject_8h.xml


// File: PythonCore_8h.xml


// File: SafePointerVector_8h.xml


// File: SpectrumUtils_8cpp.xml


// File: SpectrumUtils_8h.xml


// File: SysUtils_8cpp.xml


// File: SysUtils_8h.xml


// File: w32pragma_8h.xml


// File: BasicVector3D_8cpp.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BasicVector3D<double> vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: BasicVector3D_8h.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BA_CORE_API_ BasicVector3D<double> vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: EigenCore_8h.xml


// File: Transform3D_8cpp.xml
%feature("docstring")  BottomZ "double BottomZ(const std::vector< kvector_t > &vertices, const Transform3D &rotation)

Calculates the z-coordinate of the lowest vertex after rotation. 
";

%feature("docstring")  TopZ "double TopZ(const std::vector< kvector_t > &vertices, const Transform3D &rotation)

Calculates the z-coordinate of the highest vertex after rotation. 
";


// File: Transform3D_8h.xml
%feature("docstring")  BottomZ "double BottomZ(const std::vector< kvector_t > &vertices, const Transform3D &rotation)

Calculates the z-coordinate of the lowest vertex after rotation. 
";

%feature("docstring")  TopZ "double TopZ(const std::vector< kvector_t > &vertices, const Transform3D &rotation)

Calculates the z-coordinate of the highest vertex after rotation. 
";


// File: Vectors3D_8h.xml


// File: WavevectorInfo_8cpp.xml


// File: WavevectorInfo_8h.xml


// File: deprecated.xml


// File: dir_5f1a4a05eca575eab319839347bb4113.xml


// File: dir_f2db70b1039b2dc98a7a13a1758f382f.xml


// File: dir_2afd61a498231c74441502b63b50f75c.xml


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


// File: dir_39b907ea01a3fff6bda4d39415594941.xml


// File: dir_d7a24665a95cfc15308ebd7b07b5ebd6.xml


// File: dir_98377dc177883022b630a05f6f34fc13.xml


// File: dir_bf872a709c84554e66a8525bb546523f.xml


// File: dir_5d2259b43612a5a0ff7512df653d7370.xml


// File: dir_e120110860f9b345e7b3217e8b15cbb8.xml


// File: dir_19cd2158bba3b9a051f8f27403820580.xml

