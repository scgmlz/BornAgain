
// File: index.xml

// File: classBasicVector3D.xml
%feature("docstring") BasicVector3D "

Three-dimensional vector template, for use with integer, double, or complex components.

C++ includes: BasicVector3D.h
";

%feature("docstring")  BasicVector3D::BasicVector3D "BasicVector3D< T >::BasicVector3D()

Constructs the null vector. 
";

%feature("docstring")  BasicVector3D::BasicVector3D "BasicVector3D< T >::BasicVector3D(const T x1, const T y1, const T z1)

Constructs a vector from cartesian components. 
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

%feature("docstring")  BasicVector3D::complex "BasicVector3D<complex_t> BasicVector3D< T >::complex() const

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


// File: structBin1D.xml
%feature("docstring") Bin1D "";

%feature("docstring")  Bin1D::Bin1D "Bin1D::Bin1D()
";

%feature("docstring")  Bin1D::Bin1D "Bin1D::Bin1D(double lower, double upper)
";

%feature("docstring")  Bin1D::center "double Bin1D::center() const
";

%feature("docstring")  Bin1D::binSize "double Bin1D::binSize() const
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

%feature("docstring")  Bin1DCVector::center "cvector_t Bin1DCVector::center() const
";

%feature("docstring")  Bin1DCVector::span "cvector_t Bin1DCVector::span() const
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

%feature("docstring")  Bin1DKVector::center "kvector_t Bin1DKVector::center() const
";

%feature("docstring")  Bin1DKVector::span "kvector_t Bin1DKVector::span() const
";


// File: structIntegratorMCMiser_1_1CallBackHolder.xml
%feature("docstring") IntegratorMCMiser::CallBackHolder "

structure holding the object and possible extra parameters

C++ includes: IntegratorMCMiser.h
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

C++ includes: IntegratorGK.h
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

%feature("docstring")  ConstKBinAxis::~ConstKBinAxis "ConstKBinAxis::~ConstKBinAxis() override
";

%feature("docstring")  ConstKBinAxis::clone "ConstKBinAxis * ConstKBinAxis::clone() const override

clone function 
";

%feature("docstring")  ConstKBinAxis::createClippedAxis "ConstKBinAxis * ConstKBinAxis::createClippedAxis(double left, double right) const override

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

%feature("docstring")  CustomBinAxis::bin "Bin1D CustomBinAxis::bin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  CustomBinAxis::binCenters "std::vector< double > CustomBinAxis::binCenters() const
";

%feature("docstring")  CustomBinAxis::createClippedAxis "CustomBinAxis * CustomBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
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


// File: classDirection.xml
%feature("docstring") Direction "

A direction in three-dimensional space.

C++ includes: Direction.h
";

%feature("docstring")  Direction::Direction "Direction::Direction(double alpha, double phi)
";

%feature("docstring")  Direction::Direction "Direction::Direction()
";

%feature("docstring")  Direction::setAlpha "void Direction::setAlpha(double alpha)
";

%feature("docstring")  Direction::setPhi "void Direction::setPhi(double phi)
";

%feature("docstring")  Direction::alpha "double Direction::alpha() const
";

%feature("docstring")  Direction::phi "double Direction::phi() const
";

%feature("docstring")  Direction::vector "kvector_t Direction::vector() const

Returns Cartesian 3D vector. 
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

%feature("docstring")  FixedBinAxis::bin "Bin1D FixedBinAxis::bin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  FixedBinAxis::lowerBound "double FixedBinAxis::lowerBound() const

Returns value of first point of axis. 
";

%feature("docstring")  FixedBinAxis::upperBound "double FixedBinAxis::upperBound() const

Returns value of last point of axis. 
";

%feature("docstring")  FixedBinAxis::binCenter "double FixedBinAxis::binCenter(size_t index) const
";

%feature("docstring")  FixedBinAxis::findClosestIndex "size_t FixedBinAxis::findClosestIndex(double value) const

find bin index which is best match for given value 
";

%feature("docstring")  FixedBinAxis::binCenters "std::vector< double > FixedBinAxis::binCenters() const
";

%feature("docstring")  FixedBinAxis::binBoundaries "std::vector< double > FixedBinAxis::binBoundaries() const
";

%feature("docstring")  FixedBinAxis::createClippedAxis "FixedBinAxis * FixedBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
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

%feature("docstring")  IAxis::bin "virtual Bin1D IAxis::bin(size_t index) const =0

retrieve a 1d bin for the given index 
";

%feature("docstring")  IAxis::lowerBound "virtual double IAxis::lowerBound() const =0

Returns value of first point of axis. 
";

%feature("docstring")  IAxis::upperBound "virtual double IAxis::upperBound() const =0

Returns value of last point of axis. 
";

%feature("docstring")  IAxis::span "double IAxis::span() const

Returns distance from first to last point. 
";

%feature("docstring")  IAxis::center "double IAxis::center() const

Returns midpoint of axis. 
";

%feature("docstring")  IAxis::binCenter "virtual double IAxis::binCenter(size_t index) const =0
";

%feature("docstring")  IAxis::findClosestIndex "virtual size_t IAxis::findClosestIndex(double value) const =0

find bin index which is best match for given value 
";

%feature("docstring")  IAxis::binCenters "std::vector< double > IAxis::binCenters() const
";

%feature("docstring")  IAxis::binBoundaries "std::vector< double > IAxis::binBoundaries() const
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


// File: classIFactory.xml
%feature("docstring") IFactory "

Base class for all factories.

C++ includes: IFactory.h
";

%feature("docstring")  IFactory::createItem "AbstractProduct* IFactory< Key, AbstractProduct >::createItem(const Key &item_key) const

Creates object by calling creation function corresponded to given identifier. 
";

%feature("docstring")  IFactory::createItemPtr "std::unique_ptr<AbstractProduct> IFactory< Key, AbstractProduct >::createItemPtr(const Key &item_key) const
";

%feature("docstring")  IFactory::registerItem "bool IFactory< Key, AbstractProduct >::registerItem(const Key &item_key, CreateItemCallback CreateFn)

Registers object's creation function. 
";

%feature("docstring")  IFactory::contains "bool IFactory< Key, AbstractProduct >::contains(const Key &item_key) const
";

%feature("docstring")  IFactory::size "size_t IFactory< Key, AbstractProduct >::size() const

Returns number of registered objects. 
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

Interface for a function that maps [0,1]x[0,1] to the kvectors in a pixel. Abstract base class for SphericalPixel and RectangularPixel.

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

%feature("docstring")  IPixel::integrationFactor "virtual double IPixel::integrationFactor(double x, double y) const =0
";

%feature("docstring")  IPixel::solidAngle "virtual double IPixel::solidAngle() const =0
";


// File: classPointwiseAxis.xml
%feature("docstring") PointwiseAxis "

Axis containing arbitrary (non-equidistant) coordinate values. Lower boundary of the first bin and upper boundary of the last bin correspond to first and last passed coordinates. Other bin boundaries are computed as arithmetical mean of two adjacent coordinates. One should be aware, that bin centers reported by  PointwiseAxis::binCenter do not coincide with the values produced by Bin1D::getMidPoint. On-axis values are bounded by minimum/maximum values passed to the constructor.

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

%feature("docstring")  PointwiseAxis::bin "Bin1D PointwiseAxis::bin(size_t index) const override

retrieve a 1d bin for the given index 
";

%feature("docstring")  PointwiseAxis::lowerBound "double PointwiseAxis::lowerBound() const override

Returns value of first on-axis point. 
";

%feature("docstring")  PointwiseAxis::upperBound "double PointwiseAxis::upperBound() const override

Returns value of last on-axis point. 
";

%feature("docstring")  PointwiseAxis::binCenter "double PointwiseAxis::binCenter(size_t index) const override

Returns the coordinate corresponding to the given index. 
";

%feature("docstring")  PointwiseAxis::findClosestIndex "size_t PointwiseAxis::findClosestIndex(double value) const override

find index of the coordinate closest to the given value 
";

%feature("docstring")  PointwiseAxis::binCenters "std::vector<double> PointwiseAxis::binCenters() const override
";

%feature("docstring")  PointwiseAxis::binBoundaries "std::vector< double > PointwiseAxis::binBoundaries() const override
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


// File: classRealIntegrator.xml
%feature("docstring") RealIntegrator "

To integrate a real function of a real variable.

C++ includes: IntegratorGK.h
";

%feature("docstring")  RealIntegrator::RealIntegrator "RealIntegrator::RealIntegrator()
";

%feature("docstring")  RealIntegrator::~RealIntegrator "RealIntegrator::~RealIntegrator()
";

%feature("docstring")  RealIntegrator::integrate "double RealIntegrator::integrate(const std::function< double(double)> &f, double lmin, double lmax)
";


// File: structMath_1_1internal_1_1ReciprocalFactorial.xml
%feature("docstring") Math::internal::ReciprocalFactorial "";


// File: structMath_1_1internal_1_1ReciprocalFactorial_3_010_01_4.xml
%feature("docstring") Math::internal::ReciprocalFactorial< 0 > "
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

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement()=delete
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i, std::unique_ptr< IPixel > pixel, const Eigen::Matrix2cd &beam_polarization, const Eigen::Matrix2cd &analyzer, bool isSpecular_)
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(const SimulationElement &other)
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(SimulationElement &&other)
";

%feature("docstring")  SimulationElement::~SimulationElement "SimulationElement::~SimulationElement()
";

%feature("docstring")  SimulationElement::pointElement "SimulationElement SimulationElement::pointElement(double x, double y) const

Returns copy of this  SimulationElement with k_f given by in-pixel coordinate x,y. 
";

%feature("docstring")  SimulationElement::polarizationHandler "const PolarizationHandler& SimulationElement::polarizationHandler() const

Returns assigned  PolarizationHandler. 
";

%feature("docstring")  SimulationElement::wavelength "double SimulationElement::wavelength() const
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

%feature("docstring")  SimulationElement::intensity "double SimulationElement::intensity() const
";

%feature("docstring")  SimulationElement::getKi "kvector_t SimulationElement::getKi() const
";

%feature("docstring")  SimulationElement::getMeanKf "kvector_t SimulationElement::getMeanKf() const
";

%feature("docstring")  SimulationElement::meanQ "kvector_t SimulationElement::meanQ() const
";

%feature("docstring")  SimulationElement::getQ "kvector_t SimulationElement::getQ(double x, double y) const

Returns scattering vector Q, with Kf determined from in-pixel coordinates x,y. In-pixel coordinates take values from 0 to 1. 
";

%feature("docstring")  SimulationElement::integrationFactor "double SimulationElement::integrationFactor(double x, double y) const
";

%feature("docstring")  SimulationElement::solidAngle "double SimulationElement::solidAngle() const
";

%feature("docstring")  SimulationElement::getAlpha "double SimulationElement::getAlpha(double x, double y) const
";

%feature("docstring")  SimulationElement::getPhi "double SimulationElement::getPhi(double x, double y) const
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

%feature("docstring")  VariableBinAxis::bin "Bin1D VariableBinAxis::bin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  VariableBinAxis::lowerBound "double VariableBinAxis::lowerBound() const

Returns value of first point of axis. 
";

%feature("docstring")  VariableBinAxis::upperBound "double VariableBinAxis::upperBound() const

Returns value of last point of axis. 
";

%feature("docstring")  VariableBinAxis::binCenter "double VariableBinAxis::binCenter(size_t index) const
";

%feature("docstring")  VariableBinAxis::findClosestIndex "size_t VariableBinAxis::findClosestIndex(double value) const

find bin index which is best match for given value 
";

%feature("docstring")  VariableBinAxis::binCenters "std::vector< double > VariableBinAxis::binCenters() const
";

%feature("docstring")  VariableBinAxis::binBoundaries "std::vector<double> VariableBinAxis::binBoundaries() const
";

%feature("docstring")  VariableBinAxis::createClippedAxis "VariableBinAxis * VariableBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classFourierTransform_1_1Workspace.xml


// File: namespace_0d16.xml


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

%feature("docstring")  FileSystemUtils::jointPath "std::string FileSystemUtils::jointPath(const std::string &path1, const std::string &path2)

Returns joint path name. 
";

%feature("docstring")  FileSystemUtils::filename "std::string FileSystemUtils::filename(const std::string &path)

Returns path without directory part (\"Foo/Bar/Doz.int.gz\" -> \"Doz.int.gz\") 
";

%feature("docstring")  FileSystemUtils::stem "std::string FileSystemUtils::stem(const std::string &path)

Returns filename without (last) extension. \"/home/user/filename.int\" -> \"filename\", \"/home/user/filename.int.gz\" -> \"filename.int\" 
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

%feature("docstring")  FileSystemUtils::IsFileExists "bool FileSystemUtils::IsFileExists(const std::string &path)

Returns true if file with given name exists on disk. 
";


// File: namespaceMath.xml
%feature("docstring")  Math::Bessel::StandardNormal "double Math::StandardNormal(double x)
";

%feature("docstring")  Math::Bessel::Gaussian "double Math::Gaussian(double x, double average, double std_dev)
";

%feature("docstring")  Math::Bessel::IntegratedGaussian "double Math::IntegratedGaussian(double x, double average, double std_dev)
";

%feature("docstring")  Math::Bessel::cot "double Math::cot(double x)

cotangent function:  $cot(x)\\\\equiv1/tan(x)$
";

%feature("docstring")  Math::Bessel::sinc "double Math::sinc(double x)

sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$
";

%feature("docstring")  Math::Bessel::sinc "complex_t Math::sinc(const complex_t z)

Complex sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$. 
";

%feature("docstring")  Math::Bessel::tanhc "complex_t Math::tanhc(const complex_t z)

Complex tanhc function:  $tanhc(x)\\\\equiv\\\\tanh(x)/x$. 
";

%feature("docstring")  Math::Bessel::Laue "double Math::Laue(const double x, size_t N)

Real Laue function:  $Laue(x,N)\\\\equiv\\\\sin(Nx)/sin(x)$. 
";

%feature("docstring")  Math::Bessel::erf "double Math::erf(double arg)

Error function of real-valued argument. 
";

%feature("docstring")  Math::Bessel::GeneratePoissonRandom "double Math::GeneratePoissonRandom(double average)
";

%feature("docstring")  Math::Bessel::generateReciprocalFactorialArray "constexpr std::array<double, N> Math::generateReciprocalFactorialArray()

Returns a compile-time generated std::array of reciprocal factorials. 
";


// File: namespaceMath_1_1Bessel.xml
%feature("docstring")  Math::Bessel::J0 "double Math::Bessel::J0(double x)

Bessel function of the first kind and order 0. 
";

%feature("docstring")  Math::Bessel::J1 "double Math::Bessel::J1(double x)

Bessel function of the first kind and order 1. 
";

%feature("docstring")  Math::Bessel::J1c "double Math::Bessel::J1c(double x)

Bessel function J1(x)/x. 
";

%feature("docstring")  Math::Bessel::I0 "double Math::Bessel::I0(double x)

Modified  Bessel function of the first kind and order 0. 
";

%feature("docstring")  Math::Bessel::J0 "complex_t Math::Bessel::J0(const complex_t z)

Complex  Bessel function of the first kind and order 0. 
";

%feature("docstring")  Math::Bessel::J1 "complex_t Math::Bessel::J1(const complex_t z)

Complex  Bessel function of the first kind and order 1. 
";

%feature("docstring")  Math::Bessel::J1c "complex_t Math::Bessel::J1c(const complex_t z)

Complex  Bessel function J1(x)/x. 
";


// File: namespaceMath_1_1internal.xml
%feature("docstring")  Math::internal::generateArrayHelper "constexpr std::array<double, sizeof...(I)> Math::internal::generateArrayHelper(std::index_sequence< I... >)
";


// File: namespaceNumeric.xml
%feature("docstring")  Numeric::GetAbsoluteDifference "double Numeric::GetAbsoluteDifference(double a, double b)

Returns the absolute value of the difference between a and b. 
";

%feature("docstring")  Numeric::GetRelativeDifference "double Numeric::GetRelativeDifference(double a, double b)

Returns the safe relative difference, which is 2(|a-b|)/(|a|+|b|) except in special cases. 
";

%feature("docstring")  Numeric::GetLogDifference "double Numeric::GetLogDifference(double a, double b)

Returns the difference of the logarithm; input values are truncated at the minimum positive value 
";


// File: namespacePhysConsts.xml


// File: namespacePyUtils.xml
%feature("docstring")  PyUtils::toString "std::string PyUtils::toString(PyObject *obj)

Converts PyObject into string, if possible, or throws exception. 
";

%feature("docstring")  PyUtils::toVectorString "std::vector< std::string > PyUtils::toVectorString(PyObject *obj)

Converts PyObject into vector of strings, if possible, or throws exception. 
";

%feature("docstring")  PyUtils::toString "std::string PyUtils::toString(char *c)

Converts char to string. In the case of nullptr will return an empty string. 
";

%feature("docstring")  PyUtils::toString "std::string PyUtils::toString(wchar_t *c)
";

%feature("docstring")  PyUtils::import_bornagain "void PyUtils::import_bornagain(const std::string &path=\"\")

Imports BornAgain from given location. If path is empty, tries to rely on PYTHONPATH. 
";

%feature("docstring")  PyUtils::pythonRuntimeInfo "std::string PyUtils::pythonRuntimeInfo()

Returns multi-line string representing PATH, PYTHONPATH, sys.path and other info. 
";

%feature("docstring")  PyUtils::pythonStackTrace "std::string PyUtils::pythonStackTrace()

Returns string representing python stack trace. 
";

%feature("docstring")  PyUtils::createNumpyArray "PyObject * PyUtils::createNumpyArray(const std::vector< double > &data)
";


// File: namespaceStringUtils.xml
%feature("docstring")  StringUtils::matchesPattern "bool StringUtils::matchesPattern(const std::string &text, const std::string &wildcardPattern)

Returns true if text matches pattern with wildcards '*' and '?'. 
";

%feature("docstring")  StringUtils::padRight "std::string StringUtils::padRight(const std::string &name, size_t length)

Returns string right-padded with blanks. 
";

%feature("docstring")  StringUtils::split "std::vector< std::string > StringUtils::split(const std::string &text, const std::string &delimeter)

Split string into vector of string using delimeter.

Returns token vector obtained by splitting string at delimiters. 
";

%feature("docstring")  StringUtils::replaceItemsFromString "void StringUtils::replaceItemsFromString(std::string &text, const std::vector< std::string > &items, const std::string &replacement=\"\")

Replaces all occurrences of items from string text with delimiter. 
";

%feature("docstring")  StringUtils::join "std::string StringUtils::join(const std::vector< std::string > &joinable, const std::string &joint)

Returns string obtain by joining vector elements. 
";

%feature("docstring")  StringUtils::removeSubstring "std::string StringUtils::removeSubstring(const std::string &text, const std::string &substr)

Removes multiple occurrences of given substring from a string and returns result. 
";

%feature("docstring")  StringUtils::scientific "std::string StringUtils::scientific(const T value, int n=10)

Returns scientific string representing given value of any numeric type. 
";

%feature("docstring")  StringUtils::to_lower "std::string StringUtils::to_lower(std::string text)

Returns new string which is lower case of text. 
";

%feature("docstring")  StringUtils::trim "std::string StringUtils::trim(const std::string &str, const std::string &whitespace=\" \\\\t\")

Cuts any of the chars given in whitespace from start and end of str. 
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


// File: PhysicalConstants_8h.xml


// File: Units_8h.xml


// File: Bessel_8cpp.xml


// File: Bessel_8h.xml


// File: Constants_8h.xml


// File: FourierTransform_8cpp.xml


// File: FourierTransform_8h.xml


// File: Functions_8cpp.xml


// File: Functions_8h.xml


// File: IntegratorGK_8cpp.xml


// File: IntegratorGK_8h.xml


// File: IntegratorMCMiser_8h.xml
%feature("docstring")  make_integrator_miser "P_integrator_miser<T> make_integrator_miser(const T *object, miser_integrand< T > mem_function, size_t dim)

Template function to create an integrator object 
";


// File: Numeric_8cpp.xml


// File: Numeric_8h.xml


// File: Precomputed_8h.xml


// File: IPixel_8h.xml


// File: PolarizationHandler_8cpp.xml


// File: PolarizationHandler_8h.xml


// File: SimulationElement_8cpp.xml


// File: SimulationElement_8h.xml


// File: DelayedProgressCounter_8cpp.xml


// File: DelayedProgressCounter_8h.xml


// File: ProgressHandler_8cpp.xml


// File: ProgressHandler_8h.xml


// File: PyCore_8h.xml


// File: PyObject_8h.xml


// File: PyUtils_8cpp.xml


// File: PyUtils_8h.xml


// File: CloneableVector_8h.xml


// File: Complex_8h.xml
%feature("docstring")  mul_I "complex_t mul_I(complex_t z)

Returns product I*z, where I is the imaginary unit. 
";

%feature("docstring")  exp_I "complex_t exp_I(complex_t z)

Returns exp(I*z), where I is the imaginary unit. 
";


// File: ICloneable_8h.xml


// File: SafePointerVector_8h.xml


// File: Algorithms_8h.xml


// File: Assert_8h.xml


// File: FileSystemUtils_8cpp.xml


// File: FileSystemUtils_8h.xml


// File: IFactory_8h.xml
%feature("docstring")  create_new "T* create_new()

Returns new instance of class T.

This templated function is used in catalogs in form of a function pointer 'create_new<T>', with no function arguments supplied. Equivalently, we could use a lambda function '[](){return new T;}'. 
";


// File: StringUtils_8cpp.xml


// File: StringUtils_8h.xml


// File: SysUtils_8cpp.xml


// File: SysUtils_8h.xml


// File: ThreadInfo_8h.xml


// File: BasicVector3D_8cpp.xml


// File: BasicVector3D_8h.xml


// File: Direction_8cpp.xml
%feature("docstring")  vecOfLambdaAlphaPhi "kvector_t vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)
";


// File: Direction_8h.xml
%feature("docstring")  vecOfLambdaAlphaPhi "kvector_t vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)
";


// File: EigenCore_8h.xml


// File: Transform3D_8cpp.xml


// File: Transform3D_8h.xml


// File: Vectors3D_8h.xml


// File: dir_601becd875582af070010d10b4fc90ee.xml


// File: dir_628593db0cdce5a76fb85526ae5aa762.xml


// File: dir_53458346a71374f205070d8bd3d865f1.xml


// File: dir_1deae888303a1f34152fb62b13af5143.xml


// File: dir_ec49f598ebf9445998ce86a14e7c0417.xml


// File: dir_218b7a826f06e97e45b5c3355c035233.xml


// File: dir_85d2541e5e50049c186ff9970a3b8ef5.xml


// File: dir_38a5ec4dd9a60e867dacdb92549a13e0.xml


// File: dir_ddfc3031126aa7182b75ced37b3eee2b.xml


// File: dir_3d1c6f3819a4cd7ba7fe36c1c1e379fe.xml

