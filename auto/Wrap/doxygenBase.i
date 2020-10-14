
// File: index.xml

// File: classBasicVector3D.xml
%feature("docstring") BasicVector3D "

Forked from CLHEP/Geometry by E. Chernyaev Evgueni.Tcherniaev@cern.ch, then reworked beyond recognition. Removed split of point and vector semantics. Transforms are relegated to a separate class  Transform3D. Three-dimensional vector template, for use with integer, double, or complex components.

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

%feature("docstring")  BasicVector3D::dot "auto BasicVector3D< T >::dot(const BasicVector3D< U > &v) const

Returns dot product of vectors (antilinear in the first [=self] argument).

Returns dot product of (complex) vectors (antilinear in the first [=self] argument). 
";

%feature("docstring")  BasicVector3D::cross "auto BasicVector3D< T >::cross(const BasicVector3D< U > &v) const

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


// File: structIntegratorMCMiser_1_1CallBackHolder.xml
%feature("docstring") IntegratorMCMiser::CallBackHolder "

structure holding the object and possible extra parameters

C++ includes: IntegratorMCMiser.h
";


// File: classExceptions_1_1ClassInitializationException.xml
%feature("docstring") Exceptions::ClassInitializationException "";

%feature("docstring")  Exceptions::ClassInitializationException::ClassInitializationException "Exceptions::ClassInitializationException::ClassInitializationException(const std::string &message)
";


// File: classCloneableVector.xml
%feature("docstring") CloneableVector "

The objects pointed to must posses a clone() function.

A vector of unique pointers to objects that are cloneable.

Equips vector<unique_ptr<T>> with copy constructor. For use with polymorphic objects, or in pimpl idiom.

C++ includes: CloneableVector.h
";

%feature("docstring")  CloneableVector::CloneableVector "CloneableVector< T >::CloneableVector()
";

%feature("docstring")  CloneableVector::CloneableVector "CloneableVector< T >::CloneableVector(const CloneableVector &other)
";

%feature("docstring")  CloneableVector::push_back "void CloneableVector< T >::push_back(T *t)
";

%feature("docstring")  CloneableVector::emplace_back "void CloneableVector< T >::emplace_back(std::unique_ptr< T > &&t)
";


// File: classComplexIntegrator.xml
%feature("docstring") ComplexIntegrator "

To integrate a complex function of a real variable.

C++ includes: Integrator.h
";

%feature("docstring")  ComplexIntegrator::integrate "complex_t ComplexIntegrator::integrate(const std::function< complex_t(double)> &f, double lmin, double lmax)
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


// File: classExceptions_1_1DivisionByZeroException.xml
%feature("docstring") Exceptions::DivisionByZeroException "";

%feature("docstring")  Exceptions::DivisionByZeroException::DivisionByZeroException "Exceptions::DivisionByZeroException::DivisionByZeroException(const std::string &message)
";


// File: classExceptions_1_1DomainErrorException.xml
%feature("docstring") Exceptions::DomainErrorException "";

%feature("docstring")  Exceptions::DomainErrorException::DomainErrorException "Exceptions::DomainErrorException::DomainErrorException(const std::string &message)
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


// File: classExceptions_1_1FormatErrorException.xml
%feature("docstring") Exceptions::FormatErrorException "";

%feature("docstring")  Exceptions::FormatErrorException::FormatErrorException "Exceptions::FormatErrorException::FormatErrorException(const std::string &message)
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


// File: classICloneable.xml
%feature("docstring") ICloneable "

Interface for polymorphic classes that should not be copied, except by explicit cloning.

Child classes of  ICloneable must provide clone().

C++ includes: ICloneable.h
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable()=default
";

%feature("docstring")  ICloneable::~ICloneable "virtual ICloneable::~ICloneable()=default
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable(const ICloneable &)=delete
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable(ICloneable &&)=default
";

%feature("docstring")  ICloneable::clone "virtual ICloneable* ICloneable::clone() const =0
";

%feature("docstring")  ICloneable::transferToCPP "virtual void ICloneable::transferToCPP()

Used for Python overriding of clone (see swig/tweaks.py) 
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


// File: classExceptions_1_1LogicErrorException.xml
%feature("docstring") Exceptions::LogicErrorException "";

%feature("docstring")  Exceptions::LogicErrorException::LogicErrorException "Exceptions::LogicErrorException::LogicErrorException(const std::string &message)
";


// File: classExceptions_1_1NotImplementedException.xml
%feature("docstring") Exceptions::NotImplementedException "";

%feature("docstring")  Exceptions::NotImplementedException::NotImplementedException "Exceptions::NotImplementedException::NotImplementedException(const std::string &message)
";


// File: classExceptions_1_1NullPointerException.xml
%feature("docstring") Exceptions::NullPointerException "";

%feature("docstring")  Exceptions::NullPointerException::NullPointerException "Exceptions::NullPointerException::NullPointerException(const std::string &message)
";


// File: classExceptions_1_1OutOfBoundsException.xml
%feature("docstring") Exceptions::OutOfBoundsException "";

%feature("docstring")  Exceptions::OutOfBoundsException::OutOfBoundsException "Exceptions::OutOfBoundsException::OutOfBoundsException(const std::string &message)
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


// File: structPrecomputed_1_1ReciprocalFactorial.xml
%feature("docstring") Precomputed::ReciprocalFactorial "";


// File: structPrecomputed_1_1ReciprocalFactorial_3_010_01_4.xml
%feature("docstring") Precomputed::ReciprocalFactorial< 0 > "
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


// File: structThreadInfo.xml
%feature("docstring") ThreadInfo "

Information to run simulation with dedicated number of threads.

C++ includes: ThreadInfo.h
";

%feature("docstring")  ThreadInfo::ThreadInfo "ThreadInfo::ThreadInfo()
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

%feature("docstring")  Transform3D::transformed "template cvector_t Transform3D::transformed< cvector_t >(const ivector_t &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::transformedInverse "template cvector_t Transform3D::transformedInverse< cvector_t >(const ivector_t &v) const

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


// File: namespacealgo.xml
%feature("docstring")  algo::almostEqual "bool algo::almostEqual(double a, double b)

Returns true if two doubles agree within machine epsilon. 
";

%feature("docstring")  algo::min_value "double algo::min_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the minimum value of function evaluate as applied to the elements of an iterator range. 
";

%feature("docstring")  algo::max_value "double algo::max_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the maximum value of function evaluate as applied to the elements of an iterator range. 
";

%feature("docstring")  algo::concat "std::vector< T > algo::concat(const std::vector< T > &v1, const std::vector< T > &v2)

Returns the concatenation of two std::vectors. 
";


// File: namespaceExceptions.xml
%feature("docstring")  Exceptions::LogExceptionMessage "void Exceptions::LogExceptionMessage(const std::string &)
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


// File: namespacePhysConsts.xml


// File: namespacePrecomputed.xml
%feature("docstring")  Precomputed::GenerateArrayHelper "constexpr std::array<double, sizeof...(I)> Precomputed::GenerateArrayHelper(std::index_sequence< I... >)
";

%feature("docstring")  Precomputed::GenerateReciprocalFactorialArray "constexpr std::array<double, N> Precomputed::GenerateReciprocalFactorialArray()
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

%feature("docstring")  PyEmbeddedUtils::import_bornagain "void PyEmbeddedUtils::import_bornagain(const std::string &path=\"\")

Imports BornAgain from given location. If path is empty, tries to rely on PYTHONPATH. 
";

%feature("docstring")  PyEmbeddedUtils::pythonRuntimeInfo "std::string PyEmbeddedUtils::pythonRuntimeInfo()

Returns multi-line string representing PATH, PYTHONPATH, sys.path and other info. 
";

%feature("docstring")  PyEmbeddedUtils::pythonStackTrace "std::string PyEmbeddedUtils::pythonStackTrace()

Returns string representing python stack trace. 
";


// File: namespacepyfmt.xml
%feature("docstring")  pyfmt::scriptPreamble "std::string pyfmt::scriptPreamble()
";

%feature("docstring")  pyfmt::getSampleFunctionName "std::string pyfmt::getSampleFunctionName()
";

%feature("docstring")  pyfmt::printBool "std::string pyfmt::printBool(double value)
";

%feature("docstring")  pyfmt::printDouble "std::string pyfmt::printDouble(double input)
";

%feature("docstring")  pyfmt::printNm "std::string pyfmt::printNm(double input)
";

%feature("docstring")  pyfmt::printNm2 "std::string pyfmt::printNm2(double input)
";

%feature("docstring")  pyfmt::printScientificDouble "std::string pyfmt::printScientificDouble(double input)
";

%feature("docstring")  pyfmt::printDegrees "std::string pyfmt::printDegrees(double input)
";

%feature("docstring")  pyfmt::printValue "std::string pyfmt::printValue(double value, const std::string &units)
";

%feature("docstring")  pyfmt::printString "std::string pyfmt::printString(const std::string &value)
";

%feature("docstring")  pyfmt::isSquare "bool pyfmt::isSquare(double length1, double length2, double angle)
";

%feature("docstring")  pyfmt::isHexagonal "bool pyfmt::isHexagonal(double length1, double length2, double angle)
";

%feature("docstring")  pyfmt::printKvector "std::string pyfmt::printKvector(const kvector_t value)
";

%feature("docstring")  pyfmt::indent "std::string pyfmt::indent(size_t width)

Returns a string of blanks with given width. By default the width equals standard offset in python files. 
";

%feature("docstring")  pyfmt::printInt "std::string pyfmt::printInt(int value)
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


// File: namespaceUnits.xml
%feature("docstring")  Units::rad2deg "double Units::rad2deg(double angle)
";

%feature("docstring")  Units::deg2rad "double Units::deg2rad(double angle)
";


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


// File: PointwiseAxis_8cpp.xml


// File: PointwiseAxis_8h.xml


// File: VariableBinAxis_8cpp.xml


// File: VariableBinAxis_8h.xml


// File: MathConstants_8h.xml


// File: PhysicalConstants_8h.xml


// File: Units_8h.xml


// File: IPixel_8h.xml


// File: PolarizationHandler_8cpp.xml


// File: PolarizationHandler_8h.xml


// File: SimulationElement_8cpp.xml


// File: SimulationElement_8h.xml


// File: CloneableVector_8h.xml


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


// File: SafePointerVector_8h.xml


// File: Algorithms_8h.xml


// File: Assert_8h.xml


// File: FileSystemUtils_8cpp.xml


// File: FileSystemUtils_8h.xml


// File: Integrator_8cpp.xml


// File: Integrator_8h.xml


// File: IntegratorMCMiser_8h.xml
%feature("docstring")  make_integrator_miser "P_integrator_miser<T> make_integrator_miser(const T *object, miser_integrand< T > mem_function, size_t dim)

Template function to create an integrator object 
";


// File: MathFunctions_8cpp.xml


// File: MathFunctions_8h.xml


// File: Precomputed_8h.xml


// File: PyEmbeddedUtils_8cpp.xml


// File: PyEmbeddedUtils_8h.xml


// File: PyFmt_8cpp.xml


// File: PyFmt_8h.xml


// File: PyObject_8h.xml


// File: PythonCore_8h.xml


// File: SysUtils_8cpp.xml


// File: SysUtils_8h.xml


// File: ThreadInfo_8h.xml


// File: BasicVector3D_8cpp.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BasicVector3D<double> vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: BasicVector3D_8h.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BasicVector3D<double> vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: EigenCore_8h.xml


// File: Transform3D_8cpp.xml


// File: Transform3D_8h.xml


// File: Vectors3D_8h.xml


// File: dir_601becd875582af070010d10b4fc90ee.xml


// File: dir_628593db0cdce5a76fb85526ae5aa762.xml


// File: dir_53458346a71374f205070d8bd3d865f1.xml


// File: dir_ec49f598ebf9445998ce86a14e7c0417.xml


// File: dir_38a5ec4dd9a60e867dacdb92549a13e0.xml


// File: dir_ddfc3031126aa7182b75ced37b3eee2b.xml


// File: dir_3d1c6f3819a4cd7ba7fe36c1c1e379fe.xml

