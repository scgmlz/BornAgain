
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

Sets angle-defined specular scan. The first parameter is always a wavelength in nm. Second parameter is either a numpy array of incident angles in radians or an IAxis object with angle values. Alternatively an axis can be defined in-place, then the second passed parameter is the number of bins, third - minimum on-axis angle value, fourth - maximum on-axis angle value. 
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

Sets wavelength resolution values via RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets wavelength resolution values via RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAngleResolution "void AngularSpecScan::setAngleResolution(const ScanResolution &resolution)

Sets angle resolution values via  ScanResolution object. 
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution &distr, double rel_dev)
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution &distr, const std::vector< double > &rel_dev)

Sets angular resolution values via RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets angular resolution values via RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";


// File: classAxes.xml
%feature("docstring") Axes "

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


// File: classBeam.xml
%feature("docstring") Beam "

Beam defined by wavelength, direction and intensity.

C++ includes: Beam.h
";

%feature("docstring")  Beam::Beam "Beam::Beam(double wavelength, double alpha, double phi, double intensity)
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
";

%feature("docstring")  Beam::getChildren "std::vector< const INode * > Beam::getChildren() const override
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
";

%feature("docstring")  ConvolutionDetectorResolution::getResolutionFunction2D "const IResolutionFunction2D * ConvolutionDetectorResolution::getResolutionFunction2D() const
";

%feature("docstring")  ConvolutionDetectorResolution::getChildren "std::vector< const INode * > ConvolutionDetectorResolution::getChildren() const
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


// File: classArrayUtils_1_1CreateDataImpl.xml
%feature("docstring") ArrayUtils::CreateDataImpl "";


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


// File: classDepthProbeConverter.xml
%feature("docstring") DepthProbeConverter "

DepthProbeConverter class handles the unit translations for depth probe simulations Its default units are radians for x-axis and nm for y-axis

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  DepthProbeConverter::DepthProbeConverter "DepthProbeConverter::DepthProbeConverter(const Beam &beam, const IAxis &alpha_axis, const IAxis &z_axis)
";

%feature("docstring")  DepthProbeConverter::~DepthProbeConverter "DepthProbeConverter::~DepthProbeConverter() final
";

%feature("docstring")  DepthProbeConverter::clone "DepthProbeConverter * DepthProbeConverter::clone() const final
";

%feature("docstring")  DepthProbeConverter::availableUnits "std::vector< Axes::Units > DepthProbeConverter::availableUnits() const final

Returns the list of all available units. 
";

%feature("docstring")  DepthProbeConverter::defaultUnits "Axes::Units DepthProbeConverter::defaultUnits() const final
";


// File: classDetectionProperties.xml
%feature("docstring") DetectionProperties "

Detector properties (efficiency, transmission).

C++ includes: DetectionProperties.h
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties(kvector_t direction, double efficiency, double total_transmission)
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties()
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties(const DetectionProperties &other)
";

%feature("docstring")  DetectionProperties::~DetectionProperties "virtual DetectionProperties::~DetectionProperties()=default
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
";


// File: classDetectorContext.xml
%feature("docstring") DetectorContext "

Holds precalculated information for faster SimulationElement generation.

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


// File: classFootprintGauss.xml
%feature("docstring") FootprintGauss "

Calculates footprint coefficient for a gaussian beam  Beam width is interpreted as the full width on the level of  \\\\[ \\\\exp{-1/2} \\\\] from the peak intensity.

C++ includes: FootprintGauss.h
";

%feature("docstring")  FootprintGauss::FootprintGauss "FootprintGauss::FootprintGauss(const std::vector< double > P)
";

%feature("docstring")  FootprintGauss::FootprintGauss "FootprintGauss::FootprintGauss(double width_ratio)
";

%feature("docstring")  FootprintGauss::accept "void FootprintGauss::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FootprintGauss::clone "FootprintGauss * FootprintGauss::clone() const override
";

%feature("docstring")  FootprintGauss::calculate "double FootprintGauss::calculate(double alpha) const override

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  FootprintGauss::print "std::string FootprintGauss::print() const override

Print python-formatted footprint definition. 
";


// File: classFootprintSquare.xml
%feature("docstring") FootprintSquare "

Calculates footprint coefficient for a square beam

C++ includes: FootprintSquare.h
";

%feature("docstring")  FootprintSquare::FootprintSquare "FootprintSquare::FootprintSquare(const std::vector< double > P)
";

%feature("docstring")  FootprintSquare::FootprintSquare "FootprintSquare::FootprintSquare(double width_ratio)
";

%feature("docstring")  FootprintSquare::accept "void FootprintSquare::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FootprintSquare::clone "FootprintSquare * FootprintSquare::clone() const override
";

%feature("docstring")  FootprintSquare::calculate "double FootprintSquare::calculate(double alpha) const override

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  FootprintSquare::print "std::string FootprintSquare::print() const override

Print python-formatted footprint definition. 
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

Creates new histogram by applying crop on axis. 
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

Creates new histogram by applying rectangular clip. 
";

%feature("docstring")  Histogram2D::setContent "void Histogram2D::setContent(const std::vector< std::vector< double >> &data)

Sets the values in histograms channels from numpy array,. 
";

%feature("docstring")  Histogram2D::addContent "void Histogram2D::addContent(const std::vector< std::vector< double >> &data)

Add to values in histograms channels from numpy array,. 
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

%feature("docstring")  IDetector::defaultAxesUnits "virtual Axes::Units IDetector::defaultAxesUnits() const

Return default axes units. 
";

%feature("docstring")  IDetector::numberOfSimulationElements "size_t IDetector::numberOfSimulationElements() const

Returns number of simulation elements. 
";

%feature("docstring")  IDetector::getChildren "std::vector< const INode * > IDetector::getChildren() const override
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

Creates an IPixel for the given  OutputData object and index. 
";

%feature("docstring")  IDetector2D::indexOfSpecular "virtual size_t IDetector2D::indexOfSpecular(const Beam &beam) const =0

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


// File: classIFootprintFactor.xml
%feature("docstring") IFootprintFactor "

Abstract base for classes that calculate the beam footprint factor

C++ includes: IFootprintFactor.h
";

%feature("docstring")  IFootprintFactor::IFootprintFactor "IFootprintFactor::IFootprintFactor(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFootprintFactor::IFootprintFactor "IFootprintFactor::IFootprintFactor()=delete
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

Returns global bin index for given axes indices. For 1D, just returns binx. 
";

%feature("docstring")  IHistogram::findGlobalBin "size_t IHistogram::findGlobalBin(double x, double y) const

Returns closest global bin index for given axes coordinates. 
";

%feature("docstring")  IHistogram::getXaxisIndex "size_t IHistogram::getXaxisIndex(size_t i) const

Returns x-axis index for global bin index i. 
";

%feature("docstring")  IHistogram::getYaxisIndex "size_t IHistogram::getYaxisIndex(size_t i) const

Returns y-axis index for global bin index i. 
";

%feature("docstring")  IHistogram::getXaxisValue "double IHistogram::getXaxisValue(size_t i)

Returns the center of bin i of the x axis. 
";

%feature("docstring")  IHistogram::getYaxisValue "double IHistogram::getYaxisValue(size_t i)

Returns the center of bin i of the y axis. 
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t i) const

Returns content (accumulated value) of bin i. 
";

%feature("docstring")  IHistogram::getData "const OutputData<CumulativeValue>& IHistogram::getData() const
";

%feature("docstring")  IHistogram::getData "OutputData<CumulativeValue>& IHistogram::getData()
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t binx, size_t biny) const

Returns content (accumulated value) of the 2D histogram bin. 
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
";

%feature("docstring")  Instrument::setBeamPolarization "void Instrument::setBeamPolarization(const kvector_t bloch_vector)

Sets the beam's polarization according to the given Bloch vector. 
";

%feature("docstring")  Instrument::getBeamIntensity "double Instrument::getBeamIntensity() const
";

%feature("docstring")  Instrument::getDetector "const IDetector * Instrument::getDetector() const
";

%feature("docstring")  Instrument::detector "IDetector & Instrument::detector()
";

%feature("docstring")  Instrument::detector "const IDetector & Instrument::detector() const
";

%feature("docstring")  Instrument::detector2D "IDetector2D & Instrument::detector2D()
";

%feature("docstring")  Instrument::detector2D "const IDetector2D & Instrument::detector2D() const
";

%feature("docstring")  Instrument::getDetectorMask "const DetectorMask * Instrument::getDetectorMask() const
";

%feature("docstring")  Instrument::getDetectorAxis "const IAxis & Instrument::getDetectorAxis(size_t index) const
";

%feature("docstring")  Instrument::getDetectorDimension "size_t Instrument::getDetectorDimension() const
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

%feature("docstring")  Instrument::initDetector "void Instrument::initDetector()

init detector with beam settings 
";

%feature("docstring")  Instrument::getChildren "std::vector< const INode * > Instrument::getChildren() const
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


// File: classIResolutionFunction2D.xml
%feature("docstring") IResolutionFunction2D "

Interface providing two-dimensional resolution function.

C++ includes: IResolutionFunction2D.h
";

%feature("docstring")  IResolutionFunction2D::IResolutionFunction2D "IResolutionFunction2D::IResolutionFunction2D()=default
";

%feature("docstring")  IResolutionFunction2D::IResolutionFunction2D "IResolutionFunction2D::IResolutionFunction2D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IResolutionFunction2D::~IResolutionFunction2D "virtual IResolutionFunction2D::~IResolutionFunction2D()
";

%feature("docstring")  IResolutionFunction2D::evaluateCDF "virtual double IResolutionFunction2D::evaluateCDF(double x, double y) const =0
";

%feature("docstring")  IResolutionFunction2D::clone "virtual IResolutionFunction2D* IResolutionFunction2D::clone() const =0
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
";


// File: classIShape2D.xml
%feature("docstring") IShape2D "

Basic class for all shapes in 2D.

C++ includes: IShape2D.h
";

%feature("docstring")  IShape2D::IShape2D "IShape2D::IShape2D(const char *name)
";

%feature("docstring")  IShape2D::clone "virtual IShape2D* IShape2D::clone() const =0
";

%feature("docstring")  IShape2D::contains "virtual bool IShape2D::contains(double x, double y) const =0

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  IShape2D::contains "virtual bool IShape2D::contains(const Bin1D &binx, const Bin1D &biny) const =0

Returns true if area defined by two bins is inside or on border of polygon (more precisely, if mid point of two bins satisfy this condition). 
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

%feature("docstring")  IUnitConverter::calculateMin "virtual double IUnitConverter::calculateMin(size_t i_axis, Axes::Units units_type) const =0
";

%feature("docstring")  IUnitConverter::calculateMax "virtual double IUnitConverter::calculateMax(size_t i_axis, Axes::Units units_type) const =0
";

%feature("docstring")  IUnitConverter::axisSize "virtual size_t IUnitConverter::axisSize(size_t i_axis) const =0
";

%feature("docstring")  IUnitConverter::axisName "std::string IUnitConverter::axisName(size_t i_axis, Axes::Units units_type=Axes::Units::DEFAULT) const
";

%feature("docstring")  IUnitConverter::availableUnits "virtual std::vector<Axes::Units> IUnitConverter::availableUnits() const =0
";

%feature("docstring")  IUnitConverter::defaultUnits "virtual Axes::Units IUnitConverter::defaultUnits() const =0
";

%feature("docstring")  IUnitConverter::substituteDefaultUnits "Axes::Units IUnitConverter::substituteDefaultUnits(Axes::Units units) const
";

%feature("docstring")  IUnitConverter::createConvertedAxis "virtual std::unique_ptr<IAxis> IUnitConverter::createConvertedAxis(size_t i_axis, Axes::Units units) const =0
";

%feature("docstring")  IUnitConverter::createConvertedData "std::unique_ptr< OutputData< double > > IUnitConverter::createConvertedData(const OutputData< double > &data, Axes::Units units) const

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


// File: structArrayUtils_1_1CreateDataImpl_1_1nDim.xml


// File: structArrayUtils_1_1CreateDataImpl_1_1nDim_3_01std_1_1vector_3_01T_00_01A_01_4_01_4.xml


// File: classOffSpecularConverter.xml
%feature("docstring") OffSpecularConverter "

IUnitConverter class that handles the unit translations for off-specular simulations with a spherical detector Its default units are radians for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  OffSpecularConverter::OffSpecularConverter "OffSpecularConverter::OffSpecularConverter(const IDetector2D &detector, const Beam &beam, const IAxis &alpha_axis)
";

%feature("docstring")  OffSpecularConverter::~OffSpecularConverter "OffSpecularConverter::~OffSpecularConverter() final
";

%feature("docstring")  OffSpecularConverter::clone "OffSpecularConverter * OffSpecularConverter::clone() const final
";

%feature("docstring")  OffSpecularConverter::defaultUnits "Axes::Units OffSpecularConverter::defaultUnits() const final
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

Corresponding Bin1D object 
";

%feature("docstring")  OutputData::getAxisBin "Bin1D OutputData< T >::getAxisBin(size_t global_index, const std::string &axis_name) const

Returns bin of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding Bin1D object 
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

%feature("docstring")  OutputData::getArray "PyObject * OutputData< double >::getArray() const
";

%feature("docstring")  OutputData::getValue "double OutputData< double >::getValue(size_t index) const
";

%feature("docstring")  OutputData::getArray "PyObject * OutputData< double >::getArray() const

returns data as Python numpy array 
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

Strategy to write  OutputData to special BornAgain ASCII format

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


// File: classPolygonPrivate.xml
%feature("docstring") PolygonPrivate "

The private data for polygons to hide boost dependency from the header. 
";

%feature("docstring")  PolygonPrivate::init_from "void PolygonPrivate::init_from(const std::vector< double > &x, const std::vector< double > &y)
";

%feature("docstring")  PolygonPrivate::get_points "void PolygonPrivate::get_points(std::vector< double > &xpos, std::vector< double > &ypos)
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

Sets q-defined specular scan. Accepts either numpy array of q-values sorted in ascending order or an IAxis object with q-values. Alternatively an axis can be defined in-place, then the first passed parameter is the number of bins, second - minimum on-axis q-value, third - maximum on-axis q_value. 
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

Sets qz resolution values via RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets qz resolution values via RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
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

%feature("docstring")  RectangularConverter::~RectangularConverter "RectangularConverter::~RectangularConverter() final
";

%feature("docstring")  RectangularConverter::clone "RectangularConverter * RectangularConverter::clone() const final
";

%feature("docstring")  RectangularConverter::availableUnits "std::vector< Axes::Units > RectangularConverter::availableUnits() const final

Returns the list of all available units. 
";

%feature("docstring")  RectangularConverter::defaultUnits "Axes::Units RectangularConverter::defaultUnits() const final
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

%feature("docstring")  RectangularDetector::defaultAxesUnits "Axes::Units RectangularDetector::defaultAxesUnits() const override

return default axes units 
";

%feature("docstring")  RectangularDetector::regionOfInterestPixel "RectangularPixel * RectangularDetector::regionOfInterestPixel() const
";


// File: classRectangularPixel.xml
%feature("docstring") RectangularPixel "

A pixel in a  RectangularDetector.

C++ includes: RectangularPixel.h
";

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

%feature("docstring")  ResolutionFunction2DGaussian::accept "void ResolutionFunction2DGaussian::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaX "double ResolutionFunction2DGaussian::getSigmaX() const
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaY "double ResolutionFunction2DGaussian::getSigmaY() const
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


// File: classSimulationResult.xml
%feature("docstring") SimulationResult "

Wrapper around OutputData<double> that also provides unit conversions.

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

%feature("docstring")  SimulationResult::data "std::unique_ptr< OutputData< double > > SimulationResult::data(Axes::Units units=Axes::Units::DEFAULT) const
";

%feature("docstring")  SimulationResult::histogram2d "Histogram2D * SimulationResult::histogram2d(Axes::Units units=Axes::Units::DEFAULT) const
";

%feature("docstring")  SimulationResult::axisInfo "std::vector< AxisInfo > SimulationResult::axisInfo(Axes::Units units=Axes::Units::DEFAULT) const

Provide  AxisInfo for each axis and the given units. 
";

%feature("docstring")  SimulationResult::converter "const IUnitConverter & SimulationResult::converter() const

Returns underlying unit converter. 
";

%feature("docstring")  SimulationResult::size "size_t SimulationResult::size() const
";

%feature("docstring")  SimulationResult::empty "bool SimulationResult::empty() const
";

%feature("docstring")  SimulationResult::array "PyObject * SimulationResult::array(Axes::Units units=Axes::Units::DEFAULT) const

returns intensity data as Python numpy array 
";

%feature("docstring")  SimulationResult::axis "std::vector< double > SimulationResult::axis(Axes::Units units=Axes::Units::DEFAULT) const
";

%feature("docstring")  SimulationResult::axis "std::vector< double > SimulationResult::axis(size_t i_axis, Axes::Units units=Axes::Units::DEFAULT) const

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

%feature("docstring")  SpecularDetector1D::defaultAxesUnits "Axes::Units SpecularDetector1D::defaultAxesUnits() const override

Return default axes units. 
";


// File: classSphericalConverter.xml
%feature("docstring") SphericalConverter "

IUnitConverter class that handles the unit translations for spherical detectors Its default units are radians for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  SphericalConverter::SphericalConverter "SphericalConverter::SphericalConverter(const SphericalDetector &detector, const Beam &beam)
";

%feature("docstring")  SphericalConverter::~SphericalConverter "SphericalConverter::~SphericalConverter() final
";

%feature("docstring")  SphericalConverter::clone "SphericalConverter * SphericalConverter::clone() const final
";

%feature("docstring")  SphericalConverter::availableUnits "std::vector< Axes::Units > SphericalConverter::availableUnits() const final

Returns the list of all available units. 
";

%feature("docstring")  SphericalConverter::defaultUnits "Axes::Units SphericalConverter::defaultUnits() const final
";


// File: classSphericalDetector.xml
%feature("docstring") SphericalDetector "

A spherical detector with axes and resolution function.

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
";

%feature("docstring")  SphericalDetector::~SphericalDetector "SphericalDetector::~SphericalDetector() override
";

%feature("docstring")  SphericalDetector::defaultAxesUnits "Axes::Units SphericalDetector::defaultAxesUnits() const override

return default axes units 
";


// File: classSphericalPixel.xml
%feature("docstring") SphericalPixel "

A pixel in a  SphericalDetector.

C++ includes: SphericalPixel.h
";

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

%feature("docstring")  UnitConverter1D::calculateMin "double UnitConverter1D::calculateMin(size_t i_axis, Axes::Units units_type) const override

Calculates minimum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::calculateMax "double UnitConverter1D::calculateMax(size_t i_axis, Axes::Units units_type) const override

Calculates maximum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::createConvertedAxis "std::unique_ptr< IAxis > UnitConverter1D::createConvertedAxis(size_t i_axis, Axes::Units units) const override

Creates axis in converted units. 
";

%feature("docstring")  UnitConverter1D::createConvertedData "std::unique_ptr< OutputData< double > > UnitConverter1D::createConvertedData(const OutputData< double > &data, Axes::Units units) const override

Creates  OutputData array in converter units. 
";


// File: classUnitConverterConvSpec.xml
%feature("docstring") UnitConverterConvSpec "

Conversion of axis units for the case of conventional (angle-based) reflectometry.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverterConvSpec::UnitConverterConvSpec "UnitConverterConvSpec::UnitConverterConvSpec(const Beam &beam, const IAxis &axis, Axes::Units axis_units=Axes::Units::RADIANS)

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

%feature("docstring")  UnitConverterConvSpec::availableUnits "std::vector< Axes::Units > UnitConverterConvSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterConvSpec::defaultUnits "Axes::Units UnitConverterConvSpec::defaultUnits() const override

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

%feature("docstring")  UnitConverterQSpec::availableUnits "std::vector< Axes::Units > UnitConverterQSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterQSpec::defaultUnits "Axes::Units UnitConverterQSpec::defaultUnits() const override

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

%feature("docstring")  UnitConverterSimple::dimension "size_t UnitConverterSimple::dimension() const final
";

%feature("docstring")  UnitConverterSimple::calculateMin "double UnitConverterSimple::calculateMin(size_t i_axis, Axes::Units units_type) const final
";

%feature("docstring")  UnitConverterSimple::calculateMax "double UnitConverterSimple::calculateMax(size_t i_axis, Axes::Units units_type) const final
";

%feature("docstring")  UnitConverterSimple::axisSize "size_t UnitConverterSimple::axisSize(size_t i_axis) const final
";

%feature("docstring")  UnitConverterSimple::availableUnits "std::vector< Axes::Units > UnitConverterSimple::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterSimple::createConvertedAxis "std::unique_ptr< IAxis > UnitConverterSimple::createConvertedAxis(size_t i_axis, Axes::Units units) const final
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


// File: classConvolve_1_1Workspace.xml


// File: classFourierTransform_1_1Workspace.xml


// File: namespace_0d113.xml


// File: namespace_0d115.xml


// File: namespace_0d125.xml


// File: namespace_0d33.xml


// File: namespace_0d56.xml


// File: namespace_0d58.xml


// File: namespace_0d62.xml


// File: namespace_0d68.xml


// File: namespaceArrayUtils.xml
%feature("docstring")  ArrayUtils::getShape "std::pair< size_t, size_t > ArrayUtils::getShape(const T &data)

Returns shape nrows, ncols of 2D array. 
";

%feature("docstring")  ArrayUtils::createData "CreateDataImpl::ReturnType<T> ArrayUtils::createData(const T &vec)

Creates  OutputData array from input vector. 
";

%feature("docstring")  ArrayUtils::createNumpyArray "PyObject * ArrayUtils::createNumpyArray(const std::vector< double > &data)
";

%feature("docstring")  ArrayUtils::createVector1D "decltype(auto) ArrayUtils::createVector1D(const T &data)

Creates 1D vector from  OutputData. 
";

%feature("docstring")  ArrayUtils::createVector2D "decltype(auto) ArrayUtils::createVector2D(const T &data)

Creates 2D vector from  OutputData. 
";


// File: namespaceAxisNames.xml
%feature("docstring")  AxisNames::InitSphericalAxis0 "std::map< Axes::Units, std::string > AxisNames::InitSphericalAxis0()
";

%feature("docstring")  AxisNames::InitSphericalAxis1 "std::map< Axes::Units, std::string > AxisNames::InitSphericalAxis1()
";

%feature("docstring")  AxisNames::InitRectangularAxis0 "std::map< Axes::Units, std::string > AxisNames::InitRectangularAxis0()
";

%feature("docstring")  AxisNames::InitRectangularAxis1 "std::map< Axes::Units, std::string > AxisNames::InitRectangularAxis1()
";

%feature("docstring")  AxisNames::InitOffSpecAxis0 "std::map< Axes::Units, std::string > AxisNames::InitOffSpecAxis0()
";

%feature("docstring")  AxisNames::InitOffSpecAxis1 "std::map< Axes::Units, std::string > AxisNames::InitOffSpecAxis1()
";

%feature("docstring")  AxisNames::InitSpecAxis "std::map< Axes::Units, std::string > AxisNames::InitSpecAxis()
";

%feature("docstring")  AxisNames::InitSpecAxisQ "std::map< Axes::Units, std::string > AxisNames::InitSpecAxisQ()
";

%feature("docstring")  AxisNames::InitSampleDepthAxis "std::map< Axes::Units, std::string > AxisNames::InitSampleDepthAxis()
";


// File: namespaceboost_1_1geometry.xml


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

returns true if file name corresponds to BornAgain native format (compressed or not) 
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


// File: namespaceIntensityDataFunctions.xml
%feature("docstring")  IntensityDataFunctions::RelativeDifference "double IntensityDataFunctions::RelativeDifference(const SimulationResult &dat, const SimulationResult &ref)

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(a + b) ( and zero if a-b=0 )

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(|a| + |b|) ( and zero if a=b=0 within epsilon ) 
";

%feature("docstring")  IntensityDataFunctions::getRelativeDifference "double IntensityDataFunctions::getRelativeDifference(const OutputData< double > &dat, const OutputData< double > &ref)

Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]). 
";

%feature("docstring")  IntensityDataFunctions::checkRelativeDifference "bool IntensityDataFunctions::checkRelativeDifference(const OutputData< double > &dat, const OutputData< double > &ref, const double threshold)

Returns true is relative difference is below threshold; prints informative output. 
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

Returns new object with input data rotated by n*90 deg counterclockwise (n > 0) or clockwise (n < 0)  Axes are swapped if the data is effectively rotated by 90 or 270 degrees Applicable to 2D arrays only 
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


// File: namespacePyArrayImport.xml
%feature("docstring")  PyArrayImport::importArrayToOutputData "OutputData< double > * PyArrayImport::importArrayToOutputData(const std::vector< double > &vec)

for importing 1D array of doubles from python into  OutputData
";

%feature("docstring")  PyArrayImport::importArrayToOutputData "OutputData< double > * PyArrayImport::importArrayToOutputData(const std::vector< std::vector< double >> &vec)

for importing 2D array of doubles from python into  OutputData
";


// File: namespacepyfmt2.xml
%feature("docstring")  pyfmt2::representShape2D "std::string pyfmt2::representShape2D(const std::string &indent, const IShape2D *ishape, bool mask_value, std::function< std::string(double)> printValueFunc)

Returns fixed Python code snippet that defines the function \"runSimulation\". 
";

%feature("docstring")  pyfmt2::valueTimesUnit "std::string pyfmt2::valueTimesUnit(const RealParameter *par)

Returns parameter value, followed by its unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::argumentList "std::string pyfmt2::argumentList(const IParameterized *ip)

Returns comma-separated list of parameter values, including unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::printDistribution "std::string pyfmt2::printDistribution(const IDistribution1D &par_distr, const std::string &units)

Prints distribution with constructor parameters in given units. ba.DistributionGaussian(2.0*deg, 0.02*deg) 
";

%feature("docstring")  pyfmt2::printParameterDistribution "std::string pyfmt2::printParameterDistribution(const ParameterDistribution &par_distr, const std::string &distVarName, const std::string &units)
";


// File: namespaceSpectrumUtils.xml
%feature("docstring")  SpectrumUtils::FindPeaks "std::vector< std::pair< double, double > > SpectrumUtils::FindPeaks(const Histogram2D &hist, double sigma=2, const std::string &option={}, double threshold=0.05)
";


// File: Beam_8cpp.xml


// File: Beam_8h.xml


// File: FootprintGauss_8cpp.xml


// File: FootprintGauss_8h.xml


// File: FootprintSquare_8cpp.xml


// File: FootprintSquare_8h.xml


// File: IFootprintFactor_8cpp.xml


// File: IFootprintFactor_8h.xml


// File: CumulativeValue_8cpp.xml


// File: CumulativeValue_8h.xml


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


// File: DetectionProperties_8cpp.xml


// File: DetectionProperties_8h.xml


// File: DetectorContext_8cpp.xml


// File: DetectorContext_8h.xml


// File: DetectorMask_8cpp.xml


// File: DetectorMask_8h.xml


// File: IDetector_8cpp.xml


// File: IDetector_8h.xml


// File: IDetector2D_8cpp.xml


// File: IDetector2D_8h.xml


// File: IsGISAXSDetector_8cpp.xml


// File: IsGISAXSDetector_8h.xml


// File: RectangularDetector_8cpp.xml


// File: RectangularDetector_8h.xml


// File: RectangularPixel_8cpp.xml


// File: RectangularPixel_8h.xml


// File: RegionOfInterest_8cpp.xml


// File: RegionOfInterest_8h.xml


// File: SimpleUnitConverters_8cpp.xml


// File: SimpleUnitConverters_8h.xml


// File: SimulationArea_8cpp.xml


// File: SimulationArea_8h.xml


// File: SimulationAreaIterator_8cpp.xml


// File: SimulationAreaIterator_8h.xml


// File: SpecularDetector1D_8cpp.xml


// File: SpecularDetector1D_8h.xml


// File: SphericalDetector_8cpp.xml


// File: SphericalDetector_8h.xml


// File: SphericalPixel_8cpp.xml


// File: SphericalPixel_8h.xml


// File: Histogram1D_8cpp.xml


// File: Histogram1D_8h.xml


// File: Histogram2D_8cpp.xml


// File: Histogram2D_8h.xml


// File: IHistogram_8cpp.xml


// File: IHistogram_8h.xml


// File: IntensityDataIOFactory_8cpp.xml


// File: IntensityDataIOFactory_8h.xml


// File: SimulationResult_8cpp.xml


// File: SimulationResult_8h.xml


// File: boost__streams_8h.xml


// File: DataFormatUtils_8cpp.xml


// File: DataFormatUtils_8h.xml


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


// File: ChiSquaredModule_8cpp.xml


// File: ChiSquaredModule_8h.xml


// File: FourierTransform_8cpp.xml


// File: FourierTransform_8h.xml


// File: IChiSquaredModule_8cpp.xml


// File: IChiSquaredModule_8h.xml


// File: Instrument_8cpp.xml


// File: Instrument_8h.xml


// File: IntensityDataFunctions_8cpp.xml


// File: IntensityDataFunctions_8h.xml


// File: PyArrayImportUtils_8cpp.xml


// File: PyArrayImportUtils_8h.xml


// File: PyFmt2_8cpp.xml


// File: PyFmt2_8h.xml


// File: SpectrumUtils_8cpp.xml


// File: SpectrumUtils_8h.xml


// File: VarianceFunctions_8cpp.xml


// File: VarianceFunctions_8h.xml


// File: ArrayUtils_8cpp.xml


// File: ArrayUtils_8h.xml


// File: IIntensityFunction_8cpp.xml


// File: IIntensityFunction_8h.xml


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


// File: ConvolutionDetectorResolution_8cpp.xml


// File: ConvolutionDetectorResolution_8h.xml


// File: Convolve_8cpp.xml


// File: Convolve_8h.xml


// File: IDetectorResolution_8h.xml


// File: IResolutionFunction2D_8cpp.xml


// File: IResolutionFunction2D_8h.xml


// File: ResolutionFunction2DGaussian_8cpp.xml


// File: ResolutionFunction2DGaussian_8h.xml


// File: ScanResolution_8cpp.xml


// File: ScanResolution_8h.xml


// File: AngularSpecScan_8cpp.xml


// File: AngularSpecScan_8h.xml


// File: ISpecularScan_8cpp.xml


// File: ISpecularScan_8h.xml


// File: QSpecScan_8cpp.xml


// File: QSpecScan_8h.xml


// File: AxisNames_8cpp.xml


// File: AxisNames_8h.xml


// File: IUnitConverter_8cpp.xml


// File: IUnitConverter_8h.xml


// File: UnitConverter1D_8cpp.xml


// File: UnitConverter1D_8h.xml


// File: deprecated.xml


// File: dir_045b2146c1496d64c013dbede5cfb743.xml


// File: dir_dda0c63858d3307626c38e9d5a1e4058.xml


// File: dir_c3bac8c01fa2e2f8df2b6f9956445782.xml


// File: dir_4c76ddfc10a27668d6c42d3412320ee0.xml


// File: dir_79fd6aafcbcfabf60588d893417cf324.xml


// File: dir_9f013251ba980bff6504d6613b69183d.xml


// File: dir_550e786a97bd4c801929243ea9773c04.xml


// File: dir_401915efc9e4b0dfad0f4a62e1092d10.xml


// File: dir_4866552d576e04b61ad8ade47c8db877.xml


// File: dir_aa6451b5aab7f40a79bc1a0dc7cac3c6.xml


// File: dir_07fe00a841f74c01dc91ea0f813bfe61.xml


// File: dir_1129f0bc4b0b28573da786f6a995b6c2.xml

