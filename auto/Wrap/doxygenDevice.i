
// File: index.xml

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

An incident neutron or x-ray beam.

C++ includes: Beam.h
";

%feature("docstring")  Beam::Beam "Beam::Beam(double intensity, double wavelength, const Direction &direction)
";

%feature("docstring")  Beam::Beam "Beam::Beam(const Beam &other)
";

%feature("docstring")  Beam::~Beam "Beam::~Beam()
";

%feature("docstring")  Beam::accept "void Beam::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  Beam::getChildren "std::vector< const INode * > Beam::getChildren() const override
";

%feature("docstring")  Beam::intensity "double Beam::intensity() const

Returns the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::wavelength "double Beam::wavelength() const
";

%feature("docstring")  Beam::direction "Direction Beam::direction() const
";

%feature("docstring")  Beam::getCentralK "kvector_t Beam::getCentralK() const

Returns the wavevector. 
";

%feature("docstring")  Beam::getBlochVector "kvector_t Beam::getBlochVector() const
";

%feature("docstring")  Beam::footprintFactor "const IFootprintFactor * Beam::footprintFactor() const

Returns footprint factor. 
";

%feature("docstring")  Beam::getPolarization "Eigen::Matrix2cd Beam::getPolarization() const

Returns the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  Beam::setWavelength "void Beam::setWavelength(double wavelength)
";

%feature("docstring")  Beam::setDirection "void Beam::setDirection(const Direction &direction)
";

%feature("docstring")  Beam::setInclination "void Beam::setInclination(const double alpha)
";

%feature("docstring")  Beam::setIntensity "void Beam::setIntensity(double intensity)

Sets the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::setFootprintFactor "void Beam::setFootprintFactor(const IFootprintFactor &shape_factor)

Sets footprint factor to the beam. 
";

%feature("docstring")  Beam::setPolarization "void Beam::setPolarization(const kvector_t bloch_vector)

Sets the polarization density matrix according to the given Bloch vector. 
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

%feature("docstring")  DepthProbeConverter::~DepthProbeConverter "DepthProbeConverter::~DepthProbeConverter() override
";

%feature("docstring")  DepthProbeConverter::clone "DepthProbeConverter * DepthProbeConverter::clone() const override
";

%feature("docstring")  DepthProbeConverter::availableUnits "std::vector< Axes::Units > DepthProbeConverter::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  DepthProbeConverter::defaultUnits "Axes::Units DepthProbeConverter::defaultUnits() const override
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

An ellipse, for use in detector masks.

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

Gaussian beam footprint.

Beam width is the full width at half maximum.

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

%feature("docstring")  FootprintGauss::name "std::string FootprintGauss::name() const override
";


// File: classFootprintSquare.xml
%feature("docstring") FootprintSquare "

Rectangular beam footprint.

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

%feature("docstring")  FootprintSquare::name "std::string FootprintSquare::name() const override
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

%feature("docstring")  Histogram1D::rank "size_t Histogram1D::rank() const

Returns the number of histogram dimensions. 
";

%feature("docstring")  Histogram1D::fill "int Histogram1D::fill(double x, double weight=1.0)

Increment bin with abscissa x with a weight. 
";

%feature("docstring")  Histogram1D::binCenters "std::vector< double > Histogram1D::binCenters() const

returns vector of histogram bin centers 
";

%feature("docstring")  Histogram1D::binValues "std::vector< double > Histogram1D::binValues() const

returns vector of bin content (the value accumulated by bins) 
";

%feature("docstring")  Histogram1D::binErrors "std::vector< double > Histogram1D::binErrors() const

returns vector of bin errors 
";

%feature("docstring")  Histogram1D::binCentersNumpy "PyObject * Histogram1D::binCentersNumpy() const
";

%feature("docstring")  Histogram1D::binValuesNumpy "PyObject * Histogram1D::binValuesNumpy() const
";

%feature("docstring")  Histogram1D::binErrorsNumpy "PyObject * Histogram1D::binErrorsNumpy() const
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

%feature("docstring")  Histogram2D::rank "size_t Histogram2D::rank() const

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

%feature("docstring")  IDetector::setAnalyzerProperties "void IDetector::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  IDetector::setDetectorResolution "void IDetector::setDetectorResolution(const IDetectorResolution &p_detector_resolution)

Sets the detector resolution. 
";

%feature("docstring")  IDetector::setResolutionFunction "void IDetector::setResolutionFunction(const IResolutionFunction2D &resFunc)
";

%feature("docstring")  IDetector::resetRegionOfInterest "virtual void IDetector::resetRegionOfInterest()=0

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  IDetector::detectorMask "virtual const DetectorMask* IDetector::detectorMask() const =0

Returns detector masks container. 
";

%feature("docstring")  IDetector::getChildren "std::vector< const INode * > IDetector::getChildren() const override
";

%feature("docstring")  IDetector::iterate "void IDetector::iterate(std::function< void(const_iterator)> func, bool visit_masks=false) const
";

%feature("docstring")  IDetector::axis "const IAxis & IDetector::axis(size_t index) const
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

%feature("docstring")  IDetector::applyDetectorResolution "void IDetector::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Applies the detector resolution to the given intensity maps. 
";

%feature("docstring")  IDetector::detectorResolution "const IDetectorResolution * IDetector::detectorResolution() const

Returns a pointer to detector resolution object. 
";

%feature("docstring")  IDetector::createDetectorMap "std::unique_ptr< OutputData< double > > IDetector::createDetectorMap() const

Returns empty detector map in given axes units. 
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

%feature("docstring")  IDetector::regionOfInterest "virtual const RegionOfInterest* IDetector::regionOfInterest() const =0

Returns region of interest if exists. 
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

%feature("docstring")  IFootprintFactor::name "virtual std::string IFootprintFactor::name() const =0
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

%feature("docstring")  IHistogram::~IHistogram "virtual IHistogram::~IHistogram()=default
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IAxis &axis_x)
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IAxis &axis_x, const IAxis &axis_y)
";

%feature("docstring")  IHistogram::clone "virtual IHistogram* IHistogram::clone() const =0
";

%feature("docstring")  IHistogram::rank "virtual size_t IHistogram::rank() const =0

Returns number of histogram dimensions. 
";

%feature("docstring")  IHistogram::getTotalNumberOfBins "size_t IHistogram::getTotalNumberOfBins() const

Returns total number of histogram bins. For 2D histograms the result will be the product of bin numbers along X and Y axes. 
";

%feature("docstring")  IHistogram::xAxis "const IAxis & IHistogram::xAxis() const

returns x-axis 
";

%feature("docstring")  IHistogram::yAxis "const IAxis & IHistogram::yAxis() const

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

%feature("docstring")  IHistogram::xAxisIndex "size_t IHistogram::xAxisIndex(size_t i) const

Returns x-axis index for global bin index i. 
";

%feature("docstring")  IHistogram::yAxisIndex "size_t IHistogram::yAxisIndex(size_t i) const

Returns y-axis index for global bin index i. 
";

%feature("docstring")  IHistogram::xAxisValue "double IHistogram::xAxisValue(size_t i)

Returns the center of bin i of the x axis. 
";

%feature("docstring")  IHistogram::yAxisValue "double IHistogram::yAxisValue(size_t i)

Returns the center of bin i of the y axis. 
";

%feature("docstring")  IHistogram::getData "const OutputData< CumulativeValue > & IHistogram::getData() const
";

%feature("docstring")  IHistogram::getData "OutputData< CumulativeValue > & IHistogram::getData()
";

%feature("docstring")  IHistogram::binContent "double IHistogram::binContent(size_t i) const

Returns content (accumulated value) of bin i. 
";

%feature("docstring")  IHistogram::binContent "double IHistogram::binContent(size_t binx, size_t biny) const

Returns content (accumulated value) of the 2D histogram bin. 
";

%feature("docstring")  IHistogram::setBinContent "void IHistogram::setBinContent(size_t i, double value)

Sets content of the bin corresponding to the globalbin number. 
";

%feature("docstring")  IHistogram::addBinContent "void IHistogram::addBinContent(size_t i, double value)

Add the value to the bin. 
";

%feature("docstring")  IHistogram::binError "double IHistogram::binError(size_t i) const

Returns error of the bin with given index. 
";

%feature("docstring")  IHistogram::binError "double IHistogram::binError(size_t binx, size_t biny) const

Returns error of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::binAverage "double IHistogram::binAverage(size_t i) const

Returns average value in the bin with given index. 
";

%feature("docstring")  IHistogram::binAverage "double IHistogram::binAverage(size_t binx, size_t biny) const

Returns average value of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::binNumberOfEntries "int IHistogram::binNumberOfEntries(size_t i) const

Returns number of entries in the bin with given index. 
";

%feature("docstring")  IHistogram::binNumberOfEntries "int IHistogram::binNumberOfEntries(size_t binx, size_t biny) const

Returns number of entries in the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getMaximum "double IHistogram::getMaximum() const

Returns histogram maximum value (maximum of  binContent() over all bins) 
";

%feature("docstring")  IHistogram::getMaximumBinIndex "size_t IHistogram::getMaximumBinIndex() const

Returns globalbin index with maximum content. 
";

%feature("docstring")  IHistogram::getMinimum "double IHistogram::getMinimum() const

Returns histogram minimum value (minimum of  binContent() over all bins) 
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


// File: classInfinitePlane.xml
%feature("docstring") InfinitePlane "

The infinite plane is used for masking the entire detector.

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

%feature("docstring")  Instrument::Instrument "Instrument::Instrument(const Beam &beam, const IDetector &detector)
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument(const Instrument &other)
";

%feature("docstring")  Instrument::~Instrument "Instrument::~Instrument()
";

%feature("docstring")  Instrument::accept "void Instrument::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  Instrument::beam "Beam& Instrument::beam()
";

%feature("docstring")  Instrument::beam "const Beam& Instrument::beam() const
";

%feature("docstring")  Instrument::setBeam "void Instrument::setBeam(const Beam &beam)
";

%feature("docstring")  Instrument::setBeamParameters "void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets the beam wavelength and incoming angles. 
";

%feature("docstring")  Instrument::getDetector "IDetector * Instrument::getDetector()
";

%feature("docstring")  Instrument::getDetector "const IDetector * Instrument::getDetector() const
";

%feature("docstring")  Instrument::detector "IDetector & Instrument::detector()
";

%feature("docstring")  Instrument::detector "const IDetector & Instrument::detector() const
";

%feature("docstring")  Instrument::setDetector "void Instrument::setDetector(const IDetector &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  Instrument::initDetector "void Instrument::initDetector()

init detector with beam settings 
";

%feature("docstring")  Instrument::getChildren "std::vector< const INode * > Instrument::getChildren() const
";


// File: classIntensityDataIOFactory.xml
%feature("docstring") IntensityDataIOFactory "

Provides users with possibility to read and write IntensityData from/to files in different format. Type of the file will be deduced from file name. *.txt - ASCII file with 2D array [nrow][ncol], layout as in numpy. *.int - BornAgain internal ASCII format. *.tif - 32-bits tiff file. If file name ends with \"*.gz\" or \"*.bz2\" the file will be zipped on the fly using appropriate algorithm.

Usage:

C++ includes: IntensityDataIOFactory.h
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


// File: classLine.xml
%feature("docstring") Line "

A line segment, for use in detector masks.

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

%feature("docstring")  LLData::rank "size_t LLData< T >::rank() const
";

%feature("docstring")  LLData::dimensions "const int* LLData< T >::dimensions() const
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

%feature("docstring")  OffSpecularConverter::~OffSpecularConverter "OffSpecularConverter::~OffSpecularConverter() override
";

%feature("docstring")  OffSpecularConverter::clone "OffSpecularConverter * OffSpecularConverter::clone() const override
";

%feature("docstring")  OffSpecularConverter::defaultUnits "Axes::Units OffSpecularConverter::defaultUnits() const override
";


// File: classOutputData.xml
%feature("docstring") OutputData "

Templated class to store data of type double or  CumulativeValue in multi-dimensional space.

C++ includes: OutputData.h
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData()
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData(const OutputData &)=delete
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData(OutputData &&)
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

%feature("docstring")  OutputData::axis "const IAxis & OutputData< T >::axis(size_t serial_number) const

returns axis with given serial number 
";

%feature("docstring")  OutputData::rank "size_t OutputData< T >::rank() const

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


// File: classOutputDataReadReflectometry.xml
%feature("docstring") OutputDataReadReflectometry "

Class for reading reflectometry data from ASCII file.

C++ includes: OutputDataReadReflectometry.h
";

%feature("docstring")  OutputDataReadReflectometry::readOutputData "OutputData< double > * OutputDataReadReflectometry::readOutputData(std::istream &input_stream)
";


// File: classOutputDataReadWriteINT.xml
%feature("docstring") OutputDataReadWriteINT "

Class for reading and writing BornAgain native IntensityData from ASCII file.

C++ includes: OutputDataReadWriteINT.h
";

%feature("docstring")  OutputDataReadWriteINT::readOutputData "OutputData< double > * OutputDataReadWriteINT::readOutputData(std::istream &input_stream)
";

%feature("docstring")  OutputDataReadWriteINT::writeOutputData "void OutputDataReadWriteINT::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classOutputDataReadWriteNumpyTXT.xml
%feature("docstring") OutputDataReadWriteNumpyTXT "

Class for reading and writing  OutputData from simple ASCII file with the layout as in numpy.savetxt.

C++ includes: OutputDataReadWriteNumpyTXT.h
";

%feature("docstring")  OutputDataReadWriteNumpyTXT::readOutputData "OutputData< double > * OutputDataReadWriteNumpyTXT::readOutputData(std::istream &input_stream)
";

%feature("docstring")  OutputDataReadWriteNumpyTXT::writeOutputData "void OutputDataReadWriteNumpyTXT::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classPolygon.xml
%feature("docstring") Polygon "

A polygon, for use in detector masks.  Polygon defined by two arrays with x and y coordinates of points. Sizes of arrays should coincide. If polygon is unclosed (the last point doesn't repeat the first one), it will be closed automatically.

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


// File: classRectangle.xml
%feature("docstring") Rectangle "

A rectangle, for use in detector masks.

Edges are along the coordinate axes.

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

%feature("docstring")  RectangularConverter::availableUnits "std::vector< Axes::Units > RectangularConverter::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  RectangularConverter::defaultUnits "Axes::Units RectangularConverter::defaultUnits() const override
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

%feature("docstring")  RectangularPixel::RectangularPixel "RectangularPixel::RectangularPixel(const kvector_t &corner_pos, const kvector_t &width, const kvector_t &height)
";

%feature("docstring")  RectangularPixel::clone "RectangularPixel * RectangularPixel::clone() const override
";

%feature("docstring")  RectangularPixel::createZeroSizePixel "RectangularPixel * RectangularPixel::createZeroSizePixel(double x, double y) const override
";

%feature("docstring")  RectangularPixel::getK "kvector_t RectangularPixel::getK(double x, double y, double wavelength) const override
";

%feature("docstring")  RectangularPixel::getPosition "kvector_t RectangularPixel::getPosition(double x, double y) const
";

%feature("docstring")  RectangularPixel::integrationFactor "double RectangularPixel::integrationFactor(double x, double y) const override
";

%feature("docstring")  RectangularPixel::solidAngle "double RectangularPixel::solidAngle() const override
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

%feature("docstring")  ScanResolution::distribution "const IRangedDistribution* ScanResolution::distribution() const
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

%feature("docstring")  ScanResolution::name "virtual std::string ScanResolution::name() const =0
";

%feature("docstring")  ScanResolution::delta "virtual double ScanResolution::delta() const =0
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

%feature("docstring")  SimulationResult::max "double SimulationResult::max() const
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

%feature("docstring")  SphericalConverter::~SphericalConverter "SphericalConverter::~SphericalConverter() override
";

%feature("docstring")  SphericalConverter::clone "SphericalConverter * SphericalConverter::clone() const override
";

%feature("docstring")  SphericalConverter::availableUnits "std::vector< Axes::Units > SphericalConverter::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  SphericalConverter::defaultUnits "Axes::Units SphericalConverter::defaultUnits() const override
";


// File: classSphericalDetector.xml
%feature("docstring") SphericalDetector "

A detector with coordinate axes along angles phi and alpha.

C++ includes: SphericalDetector.h
";

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector()
";

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

Returns a detector with given phi and alpha axes.

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

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector(size_t n_bin, double width, double phi, double alpha)

Returns a detector with phi and alpha axes that have equal width and binning.

Parameters:
-----------

n_bin: 
number of bins per direction

width: 
full width of angular range in phi or alpha

phi: 
central phi angle

alpha: 
central alpha angle 
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

%feature("docstring")  SphericalPixel::integrationFactor "double SphericalPixel::integrationFactor(double x, double y) const override
";

%feature("docstring")  SphericalPixel::solidAngle "double SphericalPixel::solidAngle() const override
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

%feature("docstring")  UnitConverterSimple::calculateMin "double UnitConverterSimple::calculateMin(size_t i_axis, Axes::Units units_type) const override
";

%feature("docstring")  UnitConverterSimple::calculateMax "double UnitConverterSimple::calculateMax(size_t i_axis, Axes::Units units_type) const override
";

%feature("docstring")  UnitConverterSimple::axisSize "size_t UnitConverterSimple::axisSize(size_t i_axis) const override
";

%feature("docstring")  UnitConverterSimple::availableUnits "std::vector< Axes::Units > UnitConverterSimple::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterSimple::createConvertedAxis "std::unique_ptr< IAxis > UnitConverterSimple::createConvertedAxis(size_t i_axis, Axes::Units units) const override
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


// File: namespace_0d11.xml


// File: namespace_0d38.xml


// File: namespace_0d63.xml


// File: namespace_0d69.xml


// File: namespace_0d94.xml


// File: namespaceArrayUtils.xml
%feature("docstring")  ArrayUtils::getShape "std::pair< size_t, size_t > ArrayUtils::getShape(const T &data)

Returns shape nrows, ncols of 2D array. 
";

%feature("docstring")  ArrayUtils::createData "CreateDataImpl::ReturnType<T> ArrayUtils::createData(const T &vec)

Creates  OutputData array from input vector. 
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

%feature("docstring")  AxisNames::InitOffSpecularAxis0 "std::map< Axes::Units, std::string > AxisNames::InitOffSpecularAxis0()
";

%feature("docstring")  AxisNames::InitOffSpecularAxis1 "std::map< Axes::Units, std::string > AxisNames::InitOffSpecularAxis1()
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


// File: namespaceDataUtils.xml
%feature("docstring")  DataUtils::relativeDataDifference "double DataUtils::relativeDataDifference(const OutputData< double > &dat, const OutputData< double > &ref)

Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]). 
";

%feature("docstring")  DataUtils::checkRelativeDifference "bool DataUtils::checkRelativeDifference(const OutputData< double > &dat, const OutputData< double > &ref, const double threshold)

Returns true is relative difference is below threshold; prints informative output. 
";

%feature("docstring")  DataUtils::coordinateToBinf "double DataUtils::coordinateToBinf(double coordinate, const IAxis &axis)

Transforms coordinate on axis into the bin-fraction-coordinate. 
";

%feature("docstring")  DataUtils::coordinateFromBinf "double DataUtils::coordinateFromBinf(double value, const IAxis &axis)

Transforms bin-fraction-coordinate into axis coordinate. 
";

%feature("docstring")  DataUtils::coordinateToBinf "void DataUtils::coordinateToBinf(double &x, double &y, const OutputData< double > &data)

Transforms x,y coordinate from  OutputData axes coordinates to bin-fraction-coordinates. 
";

%feature("docstring")  DataUtils::coordinateFromBinf "void DataUtils::coordinateFromBinf(double &x, double &y, const OutputData< double > &data)

Transforms x,y coordinate from bin-fraction-coordinates to  OutputData's axes coordinates. 
";

%feature("docstring")  DataUtils::create2DArrayfromOutputData "std::vector< std::vector< double > > DataUtils::create2DArrayfromOutputData(const OutputData< double > &data)

Creates a vector of vectors of double (2D Array) from  OutputData. 
";

%feature("docstring")  DataUtils::importArrayToOutputData "OutputData< double > * DataUtils::importArrayToOutputData(const std::vector< double > &vec)

Reads 1D array of doubles to Python, for use in persistence test. 
";

%feature("docstring")  DataUtils::importArrayToOutputData "OutputData< double > * DataUtils::importArrayToOutputData(const std::vector< std::vector< double >> &vec)

Reads 2D array of doubles to Python, for use in persistence test. 
";

%feature("docstring")  DataUtils::createRelativeDifferenceData "std::unique_ptr< OutputData< double > > DataUtils::createRelativeDifferenceData(const OutputData< double > &data, const OutputData< double > &reference)
";

%feature("docstring")  DataUtils::createRearrangedDataSet "std::unique_ptr< OutputData< double > > DataUtils::createRearrangedDataSet(const OutputData< double > &data, int n)

Returns new object with input data rotated by n*90 deg counterclockwise (n > 0) or clockwise (n < 0)  Axes are swapped if the data is effectively rotated by 90 or 270 degrees Applicable to 2D arrays only 
";

%feature("docstring")  DataUtils::createClippedDataSet "std::unique_ptr< OutputData< double > > DataUtils::createClippedDataSet(const OutputData< double > &origin, double x1, double y1, double x2, double y2)

Returns new IntensityData objects which axes clipped to represent the specified rectangle. 
";

%feature("docstring")  DataUtils::createOutputDatafrom2DArray "std::unique_ptr< OutputData< double > > DataUtils::createOutputDatafrom2DArray(const std::vector< std::vector< double >> &array_2d)

Creates  OutputData from a 2D Array. 
";

%feature("docstring")  DataUtils::createFFT "std::unique_ptr< OutputData< double > > DataUtils::createFFT(const OutputData< double > &data)

Creates Fourier Transform ( OutputData format) of intensity map ( OutputData format). 
";


// File: namespaceDetectorUtils.xml
%feature("docstring")  DetectorUtils::isQuadratic "bool DetectorUtils::isQuadratic(const IDetector2D &det)
";


// File: namespaceHistoUtils.xml
%feature("docstring")  HistoUtils::FindPeaks "std::vector< std::pair< double, double > > HistoUtils::FindPeaks(const Histogram2D &hist, double sigma=2, const std::string &option={}, double threshold=0.05)

Returns vector of peak center coordinates, for peaks in given histogram. 
";

%feature("docstring")  HistoUtils::RelativeDifference "double HistoUtils::RelativeDifference(const SimulationResult &dat, const SimulationResult &ref)

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(a + b) ( and zero if a-b=0 )

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(|a| + |b|) ( and zero if a=b=0 within epsilon ) 
";

%feature("docstring")  HistoUtils::getRelativeDifference "double HistoUtils::getRelativeDifference(const IHistogram &dat, const IHistogram &ref)
";

%feature("docstring")  HistoUtils::agreesWithReference "bool HistoUtils::agreesWithReference(const SimulationResult &dat, const std::string &refFileName, double tol)

Returns true if SimulatioResult agrees with data from reference file. 
";


// File: Beam_8cpp.xml


// File: Beam_8h.xml


// File: FootprintGauss_8cpp.xml


// File: FootprintGauss_8h.xml


// File: FootprintSquare_8cpp.xml


// File: FootprintSquare_8h.xml


// File: IFootprintFactor_8cpp.xml


// File: IFootprintFactor_8h.xml


// File: ArrayUtils_8h.xml


// File: CumulativeValue_8cpp.xml


// File: CumulativeValue_8h.xml


// File: DataUtils_8cpp.xml


// File: DataUtils_8h.xml


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


// File: DetectorUtils_8cpp.xml


// File: DetectorUtils_8h.xml


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


// File: HistoUtils_8cpp.xml


// File: HistoUtils_8h.xml


// File: IHistogram_8cpp.xml


// File: IHistogram_8h.xml


// File: IntensityDataIOFactory_8cpp.xml


// File: IntensityDataIOFactory_8h.xml


// File: SimulationResult_8cpp.xml


// File: SimulationResult_8h.xml


// File: boost__streams_8h.xml


// File: DataFormatUtils_8cpp.xml


// File: DataFormatUtils_8h.xml


// File: OutputDataReadReflectometry_8cpp.xml


// File: OutputDataReadReflectometry_8h.xml


// File: OutputDataReadWriteINT_8cpp.xml


// File: OutputDataReadWriteINT_8h.xml


// File: OutputDataReadWriteNumpyTXT_8cpp.xml


// File: OutputDataReadWriteNumpyTXT_8h.xml


// File: OutputDataReadWriteTiff_8cpp.xml


// File: OutputDataReadWriteTiff_8h.xml


// File: Instrument_8cpp.xml


// File: Instrument_8h.xml


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


// File: AxisNames_8cpp.xml


// File: AxisNames_8h.xml


// File: IUnitConverter_8cpp.xml


// File: IUnitConverter_8h.xml


// File: deprecated.xml


// File: dir_045b2146c1496d64c013dbede5cfb743.xml


// File: dir_dda0c63858d3307626c38e9d5a1e4058.xml


// File: dir_c3bac8c01fa2e2f8df2b6f9956445782.xml


// File: dir_4c76ddfc10a27668d6c42d3412320ee0.xml


// File: dir_79fd6aafcbcfabf60588d893417cf324.xml


// File: dir_9f013251ba980bff6504d6613b69183d.xml


// File: dir_550e786a97bd4c801929243ea9773c04.xml


// File: dir_4866552d576e04b61ad8ade47c8db877.xml


// File: dir_aa6451b5aab7f40a79bc1a0dc7cac3c6.xml


// File: dir_1129f0bc4b0b28573da786f6a995b6c2.xml

